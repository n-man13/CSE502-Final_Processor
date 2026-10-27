`include "Sysbus.defs"

typedef enum logic [6:0] {
	UNKNOWN,
	LUI, AUIPC, JAL, JALR,
	BEQ, BNE, BLT, BGE, BLTU, BGEU,
	LB, LH, LW, LBU, LHU, LWU, LD,
	SB, SH, SW, SD,
	ADDI, SLTI, SLTIU, XORI, ORI, ANDI, SLLI, SRLI, SRAI,
	ADD, SUB, SLL, SLT, SLTU, XOR, SRL, SRA, OR, AND,
	MUL, MULH, MULHSU, MULHU, DIV, DIVU, REM, REMU,
	ADDIW, SLLIW, SRLIW, SRAIW,
	ADDW, SUBW, SLLW, SRLW, SRAW,
	MULW, DIVW, DIVUW, REMW, REMUW,
	FENCE, FENCE_I, ECALL, EBREAK,
	CSRRW, CSRRS, CSRRC, CSRRWI, CSRRSI, CSRRCI
} codeword_t;

module decoder (
	output codeword_t   codeword,
	output logic [4:0] rd,
	output logic       has_rd,
	input  logic [31:0] instr
);
	logic [6:0] opcode;
	logic [2:0] funct3;
	logic [6:0] funct7;

	typedef enum logic [4:0] { // Only the 5 MSB matter to determine opcode type in a 32bit ISA (ref table: p603 Chp 36)
		OPCODE_LOAD = 5'b00_000,
		OPCODE_LOAD_FP = 5'b00_001,
		OPCODE_MISC_MEM = 5'b00_011,
		OPCODE_OP_IMM = 5'b00_100,
		OPCODE_AUIPC = 5'b00_101,
		OPCODE_OP_IMM_32 = 5'b00_110,

		OPCODE_STORE = 5'b01_000,
		OPCODE_STORE_FP = 5'b01_001,
		OPCODE_AMO = 5'b01_011,
		OPCODE_OP = 5'b01_100,
		OPCODE_LUI = 5'b01_101,
		OPCODE_OP_32 = 5'b01_110,

		OPCODE_MADD = 5'b10_000,
		OPCODE_MSUB = 5'b10_001,
		OPCODE_NMSUB = 5'b10_010,
		OPCODE_NMADD = 5'b10_011,
		OPCODE_OP_FP = 5'b10_100,
		OPCODE_OP_V = 5'b10_101,

		OPCODE_BRANCH = 5'b11_000,
		OPCODE_JALR = 5'b11_001,
		OPCODE_JAL = 5'b11_011,
		OPCODE_SYSTEM = 5'b11_100,
		OPCODE_OP_VE = 5'b11_101

	} opcode_t;

	always_comb begin
		opcode = instr[6:0];
		rd = instr[11:7];
		funct3 = instr[14:12];
		funct7 = instr[31:25];

		has_rd = 1'b0;
		codeword = UNKNOWN;
		if (instr[1:0] != 2'b11) begin
			codeword = UNKNOWN;
			has_rd = 1'b0;
		end
		case (opcode[6:2])
			// add all the cases for each opcode filling in what
			// codeword, and whether it has rd
			// RV32I
			OPCODE_LUI: begin codeword = LUI; has_rd = 1'b1; end
			OPCODE_AUIPC: begin codeword = AUIPC; has_rd = 1'b1; end
			OPCODE_JAL: begin codeword = JAL; has_rd = 1'b1; end
			OPCODE_JALR: begin
				if (funct3 == 3'b000) begin
					codeword = JALR;
					has_rd = 1'b1;
				end else begin
					codeword = UNKNOWN;
					has_rd = 1'b0;
				end
			end
			OPCODE_BRANCH: begin
				has_rd = 1'b0;
				case (funct3)
					3'b000: codeword = BEQ;
					3'b001: codeword = BNE;
					3'b100: codeword = BLT;
					3'b101: codeword = BGE;
					3'b110: codeword = BLTU;
					3'b111: codeword = BGEU;
					default: codeword = UNKNOWN;
				endcase
			end
			OPCODE_LOAD: begin
				has_rd = 1'b1;
				case (funct3)
					3'b000: codeword = LB;
					3'b001: codeword = LH;
					3'b010: codeword = LW;
					3'b100: codeword = LBU;
					3'b101: codeword = LHU;
					// RV64I
					3'b110: codeword = LWU;
					3'b011: codeword = LD;
					default: begin codeword = UNKNOWN; has_rd = 1'b0; end
				endcase
			end
			OPCODE_STORE: begin
				has_rd = 1'b0;
				case (funct3)
					3'b000: codeword = SB;
					3'b001: codeword = SH;
					3'b010: codeword = SW;
					// RV64I
					3'b011: codeword = SD;
					default: codeword = UNKNOWN;
				endcase
			end
			OPCODE_OP_IMM: begin
				has_rd = 1'b1;
				case (funct3)
					// RV32I
					3'b000: codeword = ADDI;
					3'b010: codeword = SLTI;
					3'b011: codeword = SLTIU;
					3'b100: codeword = XORI;
					3'b110: codeword = ORI;
					3'b111: codeword = ANDI;
					// RV32I / RV64I
					3'b001: begin
						case (funct7[6:1])
							6'b000000: codeword = SLLI;
							default: begin codeword = UNKNOWN; has_rd = 1'b0; end
						endcase
					end
					3'b101: begin
						case (funct7[6:1])
							6'b000000: codeword = SRLI;
							6'b010000: codeword = SRAI;
							default: begin codeword = UNKNOWN; has_rd = 1'b0; end
						endcase
					end
					default: begin codeword = UNKNOWN; has_rd = 1'b0; end
				endcase
			end
			OPCODE_OP: begin
				has_rd = 1'b1;
				// RV32I
				if (funct7 != 7'b0000001) begin
					case (funct3)
						3'b000: begin
							case (funct7)
								7'b0000000: codeword = ADD;
								7'b0100000: codeword = SUB;
								default: begin codeword = UNKNOWN; has_rd = 1'b0; end
							endcase
						end

						3'b001: if (funct7 == 7'b0000000) codeword = SLL; else begin codeword = UNKNOWN; has_rd = 1'b0; end
						3'b010: if (funct7 == 7'b0000000) codeword = SLT; else begin codeword = UNKNOWN; has_rd = 1'b0; end
						3'b011: if (funct7 == 7'b0000000) codeword = SLTU; else begin codeword = UNKNOWN; has_rd = 1'b0; end
						3'b100: if (funct7 == 7'b0000000) codeword = XOR; else begin codeword = UNKNOWN; has_rd = 1'b0; end
						3'b110: if (funct7 == 7'b0000000) codeword = OR; else begin codeword = UNKNOWN; has_rd = 1'b0; end
						3'b111: if (funct7 == 7'b0000000) codeword = AND; else begin codeword = UNKNOWN; has_rd = 1'b0; end

						3'b101: begin
							case (funct7)
								7'b0000000: codeword = SRL;
								7'b0100000: codeword = SRA;
								default: begin codeword = UNKNOWN; has_rd = 1'b0; end
							endcase
						end
						default: begin codeword = UNKNOWN; has_rd = 1'b0; end
					endcase
				end else begin
					// RV32M
					case (funct3)
						3'b000: codeword = MUL;
						3'b001: codeword = MULH;
						3'b010: codeword = MULHSU;
						3'b011: codeword = MULHU;
						3'b100: codeword = DIV;
						3'b101: codeword = DIVU;
						3'b110: codeword = REM;
						3'b111: codeword = REMU;
						default: begin codeword = UNKNOWN; has_rd = 1'b0; end
					endcase
				end
			end

			OPCODE_OP_IMM_32: begin
				has_rd = 1'b1;
				// RV64I
				case (funct3)
					3'b000: codeword = ADDIW;
					3'b001: begin
						case (funct7)
							7'b0000000: codeword = SLLIW;
							default: begin codeword = UNKNOWN; has_rd = 1'b0; end
						endcase
					end
					3'b101: begin
						case (funct7)
							7'b0000000: codeword = SRLIW;
							7'b0100000: codeword = SRAIW;
							default: begin codeword = UNKNOWN; has_rd = 1'b0; end
						endcase
					end
					default: begin codeword = UNKNOWN; has_rd = 1'b0; end
				endcase
			end
			OPCODE_OP_32: begin
				has_rd = 1'b1;
				// RV64I
				if (funct7 != 7'b0000001) begin
					case (funct3)
						3'b000: begin
							case (funct7)
								7'b0000000: codeword = ADDW;
								7'b0100000: codeword = SUBW;
								default: begin codeword = UNKNOWN; has_rd = 1'b0; end
							endcase
						end

						3'b001: begin
							if (funct7 == 7'b0000000) codeword = SLLW; else begin codeword = UNKNOWN; has_rd = 1'b0; end
						end
						3'b101: begin
							case (funct7)
								7'b0000000: codeword = SRLW;
								7'b0100000: codeword = SRAW;
								default: begin codeword = UNKNOWN; has_rd = 1'b0; end
							endcase
						end
						default: begin codeword = UNKNOWN; has_rd = 1'b0; end
					endcase
				end else begin
					// RV64M
					case (funct3)
						3'b000: codeword = MULW;
						3'b100: codeword = DIVW;
						3'b101: codeword = DIVUW;
						3'b110: codeword = REMW;
						3'b111: codeword = REMUW;
						default: begin codeword = UNKNOWN; has_rd = 1'b0; end
					endcase
				end
			end
			OPCODE_MISC_MEM: begin
				has_rd = 1'b0;
				case (funct3)
					// RV32I
					3'b000: codeword = FENCE;
					// RV32/64 Zifencei
					3'b001: codeword = FENCE_I;
					default: codeword = UNKNOWN;
				endcase
			end
			OPCODE_SYSTEM: begin
				// RV32I
				if (instr == 32'b000000000000_00000_000_00000_1110011) begin
					codeword = ECALL;
					has_rd = 1'b0;
				end else if (instr == 32'b000000000001_00000_000_00000_1110011) begin
					codeword = EBREAK;
					has_rd = 1'b0;
				end else begin
					// RV32/64 Zicsr
					has_rd = 1'b1;
					case (funct3)
						3'b001: codeword = CSRRW;
						3'b010: codeword = CSRRS;
						3'b011: codeword = CSRRC;
						3'b101: codeword = CSRRWI;
						3'b110: codeword = CSRRSI;
						3'b111: codeword = CSRRCI;
						default: begin codeword = UNKNOWN; has_rd = 1'b0; end
					endcase
				end
			end
			default: begin codeword = UNKNOWN; has_rd = 0; end
		endcase
	end
endmodule

module regfile (
	output logic [63:0] rs1_data, rs2_data,
	input logic clk,
	input logic reset,
	input logic [63:0] initial_sp,
	input logic [4:0] rs1, rs2, rd,
	input logic [63:0] wdata,
	input logic write_enable
);
	logic [63:0] regs [31:0];

	assign rs1_data = (rs1 == 5'd0) ? 64'd0 : regs[rs1];
	assign rs2_data = (rs2 == 5'd0) ? 64'd0 : regs[rs2];

	always_ff @(posedge clk) begin
		if (reset) begin // On Reset: Sets all registers to 0, except for x2 (sp) which is set to initial_sp
			for (int i = 0; i < 32; i = i + 1)
				regs[i] <= 64'b0;
			regs[2] <= initial_sp;
		end else if (write_enable && rd != 5'd0)
			regs[rd] <= wdata;
	end

	// for the dump at the end
	function automatic logic [63:0] read_reg(input logic[4:0] idx);
		return (idx == 5'd0) ? 64'd0 : regs[idx];
	endfunction
endmodule

module alu (
	output logic [63:0] result,
	input logic [63:0] a, b,
	input codeword_t codeword
);
	logic signed [127:0] signed_product;
	logic signed [127:0] signed_unsigned_product;
	logic [127:0] unsigned_product;
	logic [31:0] word_result;

	always_comb begin
		result = 64'b0;
		word_result = 32'b0;
		signed_product = $signed({{64{a[63]}}, a}) * $signed({{64{b[63]}}, b});
		signed_unsigned_product = $signed({{64{a[63]}}, a}) * $signed({64'b0, b});
		unsigned_product = {64'b0, a} * {64'b0, b};

		case (codeword)
			ADDI, ADD: result = a + b;
			SUB:       result = a - b;
			SLLI, SLL: result = a << b[5:0];
			SLTI, SLT: result = ($signed(a) < $signed(b)) ? 64'd1 : 64'd0;
			SLTIU, SLTU: result = (a < b) ? 64'd1 : 64'd0;
			XORI, XOR: result = a ^ b;
			SRLI, SRL: result = a >> b[5:0];
			SRAI, SRA: result = $signed(a) >>> b[5:0];
			ORI, OR:  result = a | b;
			ANDI, AND: result = a & b;
			ADDIW, ADDW: begin
				word_result = a[31:0] + b[31:0];
				result = {{32{word_result[31]}}, word_result};
			end
			SUBW: begin
				word_result = a[31:0] - b[31:0];
				result = {{32{word_result[31]}}, word_result};
			end
			SLLIW, SLLW: begin
				word_result = a[31:0] << b[4:0];
				result = {{32{word_result[31]}}, word_result};
			end
			SRLIW, SRLW: begin
				word_result = a[31:0] >> b[4:0];
				result = {{32{word_result[31]}}, word_result};
			end
			SRAIW, SRAW: begin
				word_result = $signed(a[31:0]) >>> b[4:0];
				result = {{32{word_result[31]}}, word_result};
			end
			MUL:        result = a * b;
			MULH:       result = signed_product[127:64];
			MULHSU:     result = signed_unsigned_product[127:64];
			MULHU:      result = unsigned_product[127:64];
			DIV: begin
				if (b == 64'b0)
					result = 64'hffff_ffff_ffff_ffff;
				else if ((a == 64'h8000_0000_0000_0000) && (b == 64'hffff_ffff_ffff_ffff))
					result = a;
				else
					result = $signed(a) / $signed(b);
			end
			DIVU:  result = (b == 64'b0) ? 64'hffff_ffff_ffff_ffff : a / b;
			REM: begin
				if (b == 64'b0)
					result = a;
				else if ((a == 64'h8000_0000_0000_0000) && (b == 64'hffff_ffff_ffff_ffff))
					result = 64'b0;
				else
					result = $signed(a) % $signed(b);
			end
			REMU:  result = (b == 64'b0) ? a : a % b;

			// RV64M word variants: operate on the lower 32 bits of a/b,
			// then sign-extend the 32-bit result to 64 bits — same pattern
			// as ADDW/SUBW/etc above. Without these, MULW/DIVW/DIVUW/REMW/
			// REMUW fall through to `default` and silently write 0 to rd.
			MULW: begin
				word_result = a[31:0] * b[31:0];
				result = {{32{word_result[31]}}, word_result};
			end
			DIVW: begin
				if (b[31:0] == 32'b0)
					result = 64'hffff_ffff_ffff_ffff;
				else if ((a[31:0] == 32'h8000_0000) && (b[31:0] == 32'hffff_ffff))
					result = {{32{a[31]}}, a[31:0]};
				else begin
					word_result = $signed(a[31:0]) / $signed(b[31:0]);
					result = {{32{word_result[31]}}, word_result};
				end
			end
			DIVUW: begin
				if (b[31:0] == 32'b0)
					result = 64'hffff_ffff_ffff_ffff;
				else begin
					word_result = a[31:0] / b[31:0];
					result = {{32{word_result[31]}}, word_result}; // unsigned 32-bit result, sign-extended per RV64 spec
				end
			end
			REMW: begin
				if (b[31:0] == 32'b0)
					result = {{32{a[31]}}, a[31:0]};
				else if ((a[31:0] == 32'h8000_0000) && (b[31:0] == 32'hffff_ffff))
					result = 64'b0;
				else begin
					word_result = $signed(a[31:0]) % $signed(b[31:0]);
					result = {{32{word_result[31]}}, word_result};
				end
			end
			REMUW: begin
				if (b[31:0] == 32'b0)
					result = {{32{a[31]}}, a[31:0]};
				else begin
					word_result = a[31:0] % b[31:0];
					result = {{32{word_result[31]}}, word_result};
				end
			end

			LUI:   result = b;
			AUIPC: result = a + b;
			default:   result = 64'b0;
		endcase
	end
endmodule

// Common blocking cache used by the instruction and data-cache wrappers.
// Geometry is fixed to 8 KiB, two ways, and 32-byte lines by default.
module l1_cache #(
	parameter bit WRITE_ENABLE = 1'b0,
	parameter int ADDR_WIDTH = 64,
	parameter int DATA_WIDTH = 64,
	parameter int CACHE_BYTES = 8192,
	parameter int LINE_BYTES = 32,
	parameter int WAYS = 2
) (
	input  logic clk,
	input  logic reset,
	input  logic cpu_req_valid,
	output logic cpu_req_ready,
	input  logic cpu_req_write,
	input  logic [ADDR_WIDTH-1:0] cpu_req_addr,
	input  logic [DATA_WIDTH-1:0] cpu_req_wdata,
	input  logic [DATA_WIDTH/8-1:0] cpu_req_wstrb,
	output logic cpu_resp_valid,
	output logic [DATA_WIDTH-1:0] cpu_resp_rdata,
	output logic mem_read_req,
	output logic [ADDR_WIDTH-1:0] mem_read_addr,
	input logic mem_read_valid,
	input logic [DATA_WIDTH-1:0] mem_read_data,
	output logic mem_write_req,
	output logic [ADDR_WIDTH-1:0] mem_write_addr,
	output logic [DATA_WIDTH-1:0] mem_write_data,
	output logic [DATA_WIDTH/8-1:0] mem_write_strb,
	input logic mem_write_ready
);
	localparam int BYTES_PER_BEAT = DATA_WIDTH / 8;
	localparam int BEATS_PER_LINE = LINE_BYTES / BYTES_PER_BEAT;
	localparam int SETS = CACHE_BYTES / LINE_BYTES / WAYS;
	localparam int OFFSET_BITS = $clog2(LINE_BYTES);
	localparam int INDEX_BITS = $clog2(SETS);
	localparam int BEAT_BITS = (BEATS_PER_LINE <= 1) ? 1 : $clog2(BEATS_PER_LINE);
	localparam int BYTE_BITS = $clog2(BYTES_PER_BEAT);
	localparam int TAG_BITS = ADDR_WIDTH - OFFSET_BITS - INDEX_BITS;

	typedef enum logic [2:0] {S_IDLE, S_LOOKUP, S_WRITEBACK,
				  S_REFILL, S_RESP} state_t;
	state_t state;

	logic valid [0:SETS-1][0:WAYS-1];
	logic dirty [0:SETS-1][0:WAYS-1];
	logic [TAG_BITS-1:0] tag [0:SETS-1][0:WAYS-1];
	logic [DATA_WIDTH-1:0] line_data [0:SETS-1][0:WAYS-1][0:BEATS_PER_LINE-1];
	logic lru [0:SETS-1];

	logic [ADDR_WIDTH-1:0] req_addr;
	logic req_write;
	logic [DATA_WIDTH-1:0] req_wdata;
	logic [DATA_WIDTH/8-1:0] req_wstrb;
	logic [INDEX_BITS-1:0] req_set;
	logic [BEAT_BITS-1:0] req_beat;
	logic [TAG_BITS-1:0] req_tag;
	logic victim_way;
	logic [BEAT_BITS-1:0] transfer_beat;
	logic transfer_pending;
	logic [DATA_WIDTH-1:0] response_data;

	wire hit0 = valid[req_set][0] && (tag[req_set][0] == req_tag);
	wire hit1 = valid[req_set][1] && (tag[req_set][1] == req_tag);
	wire hit = hit0 || hit1;
	wire selected_hit_way = hit1 && !hit0;
	wire selected_victim_way = !valid[req_set][0] ? 1'b0 :
				    !valid[req_set][1] ? 1'b1 : lru[req_set];

	assign cpu_req_ready = (state == S_IDLE) &&
			       (!cpu_req_write || WRITE_ENABLE);
	assign cpu_resp_valid = (state == S_RESP);
	assign cpu_resp_rdata = response_data;

	always_comb begin
		mem_read_req = (state == S_REFILL) && !transfer_pending;
		mem_read_addr = {req_addr[ADDR_WIDTH-1:OFFSET_BITS],
				 transfer_beat, {BYTE_BITS{1'b0}}};
		mem_write_req = (state == S_WRITEBACK) && !transfer_pending;
		mem_write_addr = {tag[req_set][victim_way], req_set,
				  transfer_beat, {BYTE_BITS{1'b0}}};
		mem_write_data = line_data[req_set][victim_way][transfer_beat];
		mem_write_strb = {DATA_WIDTH/8{1'b1}};
	end

	integer set_i;
	integer way_i;
	integer beat_i;
	integer byte_i;
	always_ff @(posedge clk or posedge reset) begin
		if (reset) begin
			state <= S_IDLE;
			response_data <= '0;
			req_addr <= '0;
			req_write <= 1'b0;
			req_wdata <= '0;
			req_wstrb <= '0;
			req_set <= '0;
			req_beat <= '0;
			req_tag <= '0;
			victim_way <= 1'b0;
			transfer_beat <= '0;
			transfer_pending <= 1'b0;
			for (set_i = 0; set_i < SETS; set_i = set_i + 1) begin
				lru[set_i] <= 1'b0;
				for (way_i = 0; way_i < WAYS; way_i = way_i + 1) begin
					valid[set_i][way_i] <= 1'b0;
					dirty[set_i][way_i] <= 1'b0;
					tag[set_i][way_i] <= '0;
					for (beat_i = 0; beat_i < BEATS_PER_LINE; beat_i = beat_i + 1)
						line_data[set_i][way_i][beat_i] <= '0;
				end
			end
		end else begin
			case (state)
				S_IDLE: begin
					if (cpu_req_valid && cpu_req_ready) begin
						req_addr <= cpu_req_addr;
						req_write <= cpu_req_write;
						req_wdata <= cpu_req_wdata;
						req_wstrb <= cpu_req_wstrb;
						req_set <= cpu_req_addr[OFFSET_BITS +: INDEX_BITS];
						req_beat <= cpu_req_addr[BYTE_BITS +: BEAT_BITS];
						req_tag <= cpu_req_addr[ADDR_WIDTH-1 -: TAG_BITS];
						state <= S_LOOKUP;
					end
				end

				S_LOOKUP: begin
					if (hit) begin
						if (req_write) begin
							for (byte_i = 0; byte_i < DATA_WIDTH/8; byte_i = byte_i + 1)
								if (req_wstrb[byte_i])
									line_data[req_set][selected_hit_way][req_beat][byte_i*8 +: 8] <=
										req_wdata[byte_i*8 +: 8];
							dirty[req_set][selected_hit_way] <= 1'b1;
							lru[req_set] <= !selected_hit_way;
							state <= S_RESP;
						end else begin
							response_data <= line_data[req_set][selected_hit_way][req_beat];
							lru[req_set] <= !selected_hit_way;
							state <= S_RESP;
						end
					end else begin
						victim_way <= selected_victim_way;
						transfer_beat <= '0;
						transfer_pending <= 1'b0;
						if (WRITE_ENABLE &&
						    valid[req_set][selected_victim_way] &&
						    dirty[req_set][selected_victim_way])
							state <= S_WRITEBACK;
						else
							state <= S_REFILL;
					end
				end

				S_WRITEBACK: begin
					if (!transfer_pending) begin
						if (mem_write_ready)
							transfer_pending <= 1'b1;
					end else begin
						transfer_pending <= 1'b0;
						if (transfer_beat == BEATS_PER_LINE-1) begin
							transfer_beat <= '0;
							state <= S_REFILL;
						end else
							transfer_beat <= transfer_beat + 1'b1;
					end
				end

				S_REFILL: begin
					if (!transfer_pending) begin
						transfer_pending <= 1'b1;
					end else if (mem_read_valid) begin
						line_data[req_set][victim_way][transfer_beat] <= mem_read_data;
						if (transfer_beat == req_beat)
							response_data <= mem_read_data;
						transfer_pending <= 1'b0;
						if (transfer_beat == BEATS_PER_LINE-1) begin
							valid[req_set][victim_way] <= 1'b1;
							dirty[req_set][victim_way] <= 1'b0;
							tag[req_set][victim_way] <= req_tag;
							lru[req_set] <= !victim_way;
							state <= req_write ? S_LOOKUP : S_RESP;
						end else
							transfer_beat <= transfer_beat + 1'b1;
					end
				end

				S_RESP: state <= S_IDLE;
				default: state <= S_IDLE;
			endcase
		end
	end

	initial begin
		if ((WAYS != 2) || (CACHE_BYTES != 8192) ||
		    (LINE_BYTES != 32) || (DATA_WIDTH != 64))
			$error("Unsupported L1 cache geometry");
	end
endmodule

module l1_i_cache (
	input logic clk, reset,
	input logic cpu_req_valid,
	output logic cpu_req_ready,
	input logic [63:0] cpu_req_addr,
	output logic cpu_resp_valid,
	output logic [63:0] cpu_resp_rdata,
	output logic mem_read_req,
	output logic [63:0] mem_read_addr,
	input logic mem_read_valid,
	input logic [63:0] mem_read_data
);
	l1_cache #(.WRITE_ENABLE(1'b0)) cache (
		.clk, .reset, .cpu_req_valid, .cpu_req_ready,
		.cpu_req_write(1'b0), .cpu_req_addr,
		.cpu_req_wdata('0), .cpu_req_wstrb('0),
		.cpu_resp_valid, .cpu_resp_rdata,
		.mem_read_req, .mem_read_addr, .mem_read_valid, .mem_read_data,
		.mem_write_req(), .mem_write_addr(), .mem_write_data(),
		.mem_write_strb(), .mem_write_ready(1'b0)
	);
endmodule

module l1_d_cache (
	input logic clk, reset,
	input logic cpu_req_valid,
	output logic cpu_req_ready,
	input logic cpu_req_write,
	input logic [63:0] cpu_req_addr,
	input logic [63:0] cpu_req_wdata,
	input logic [7:0] cpu_req_wstrb,
	output logic cpu_resp_valid,
	output logic [63:0] cpu_resp_rdata,
	output logic mem_read_req,
	output logic [63:0] mem_read_addr,
	input logic mem_read_valid,
	input logic [63:0] mem_read_data,
	output logic mem_write_req,
	output logic [63:0] mem_write_addr,
	output logic [63:0] mem_write_data,
	output logic [7:0] mem_write_strb,
	input logic mem_write_ready
);
	l1_cache #(.WRITE_ENABLE(1'b1)) cache (
		.clk, .reset, .cpu_req_valid, .cpu_req_ready,
		.cpu_req_write, .cpu_req_addr, .cpu_req_wdata, .cpu_req_wstrb,
		.cpu_resp_valid, .cpu_resp_rdata,
		.mem_read_req, .mem_read_addr, .mem_read_valid, .mem_read_data,
		.mem_write_req, .mem_write_addr, .mem_write_data,
		.mem_write_strb, .mem_write_ready
	);
endmodule

module top
#(
	ID_WIDTH = 13,
	ADDR_WIDTH = 64,
	DATA_WIDTH = 64,
	STRB_WIDTH = DATA_WIDTH/8
)
(
	input  clk,
	input  reset,
	input  hz32768timer,

	// 64-bit addresses of the program entry point and initial stack pointer
	input  [63:0] entry,
	input  [63:0] stackptr,
	input  [63:0] satp,

	// interface to connect to the bus
	output wire [ID_WIDTH-1:0]    m_axi_awid,
	output wire [ADDR_WIDTH-1:0]  m_axi_awaddr,
	output wire [7:0]             m_axi_awlen,
	output wire [2:0]             m_axi_awsize,
	output wire [1:0]             m_axi_awburst,
	output wire                   m_axi_awlock,
	output wire [3:0]             m_axi_awcache,
	output wire [2:0]             m_axi_awprot,
	output wire                   m_axi_awvalid,
	input  wire                   m_axi_awready,
	output wire [DATA_WIDTH-1:0]  m_axi_wdata,
	output wire [STRB_WIDTH-1:0]  m_axi_wstrb,
	output wire                   m_axi_wlast,
	output wire                   m_axi_wvalid,
	input  wire                   m_axi_wready,
	input  wire [ID_WIDTH-1:0]    m_axi_bid,
	input  wire [1:0]             m_axi_bresp,
	input  wire                   m_axi_bvalid,
	output wire                   m_axi_bready,
	output wire [ID_WIDTH-1:0]    m_axi_arid,
	output wire [ADDR_WIDTH-1:0]  m_axi_araddr,
	output wire [7:0]             m_axi_arlen,
	output wire [2:0]             m_axi_arsize,
	output wire [1:0]             m_axi_arburst,
	output wire                   m_axi_arlock,
	output wire [3:0]             m_axi_arcache,
	output wire [2:0]             m_axi_arprot,
	output wire                   m_axi_arvalid,
	input  wire                   m_axi_arready,
	input  wire [ID_WIDTH-1:0]    m_axi_rid,
	input  wire [DATA_WIDTH-1:0]  m_axi_rdata,
	input  wire [1:0]             m_axi_rresp,
	input  wire                   m_axi_rlast,
	input  wire                   m_axi_rvalid,
	output wire                   m_axi_rready,
	input  wire                   m_axi_acvalid,
	output wire                   m_axi_acready,
	input  wire [ADDR_WIDTH-1:0]  m_axi_acaddr,
	input  wire [3:0]             m_axi_acsnoop
);

	logic [63:0] pc;
	logic [63:0] next_pc;
	logic [511:0] fetched_line; // 8 * 64 bits = 512 bits
	logic [2:0] beat_count; // counter up to 8 beats
	logic [31:0] instr;

	// Register File connections
	logic [4:0] rs1, rs2;
	logic [63:0] rs1_data, rs2_data;
	// ALU connections
	logic [63:0] immediate, alu_a, alu_b, alu_result, write_data;
	logic write_enable;

	assign m_axi_awid = '0;
	assign m_axi_awaddr = '0;
	assign m_axi_awlen = '0;
	assign m_axi_awsize = '0;
	assign m_axi_awburst = '0;
	assign m_axi_awlock = 0;
	assign m_axi_awcache = '0;
	assign m_axi_awprot = '0;
	assign m_axi_wvalid = 0;
	assign m_axi_wdata = '0;
	assign m_axi_wstrb = '0;
	assign m_axi_wlast = 0;
	assign m_axi_bready = '0;
	assign m_axi_acready = 0;

	typedef enum logic [1:0] {IDLE, ARADDR, RDATA, DECODE} state_type;
	state_type state;

	assign m_axi_araddr = pc & ~64'h3f; // address aligned to 64 bytes (512 bits) to get each line of instruction cache
	assign m_axi_arvalid = (state == ARADDR);
	assign m_axi_arlen = 8'd7; // Ref README
	assign m_axi_arsize = 3'b011;
	assign m_axi_arburst = 2'b10; // Ref README
	assign m_axi_arid = '0;
	assign m_axi_arlock = 1'b0;
	assign m_axi_arcache = '0;
	assign m_axi_arprot = '0;
	assign m_axi_rready = (state == RDATA);

	codeword_t codeword;
	logic [4:0] rd;
	logic has_rd;

	assign instr = fetched_line[(pc[5:2] * 32) +: 32]; // 32 bits of instruction from the fetched line based on pc[5:2] (which selects 1 of the 16 instructions within the 512-bit line) (pc[1:0] is ignored since instructions are 4-byte aligned pc += 4)

	decoder decode (
		.instr (instr),
		.codeword (codeword),
		.rd (rd),
		.has_rd (has_rd)
	);

	assign rs1 = instr[19:15];
	assign rs2 = instr[24:20];

	regfile registers (
		.rs1_data (rs1_data),
		.rs2_data (rs2_data),
		.clk (clk),
		.reset (reset),
		.initial_sp (stackptr),
		.rs1 (rs1),
		.rs2 (rs2),
		.rd (rd),
		.wdata (write_data),
		.write_enable (write_enable)
	);

	alu execute_alu (
		.result (alu_result),
		.a (alu_a),
		.b (alu_b),
		.codeword (codeword)
	);

	always_comb begin
		immediate = {{52{instr[31]}}, instr[31:20]}; // Assuming Standard I-type immediate + sign extension
		alu_a = rs1_data;
		alu_b = rs2_data;
		write_data = alu_result;

		case (codeword)
			LUI: begin
				immediate = {{32{instr[31]}}, instr[31:12], 12'b0}; // U - type immediate + sign extension
				alu_b = immediate;
			end
			AUIPC: begin
				immediate = {{32{instr[31]}}, instr[31:12], 12'b0}; // U - type immediate + sign extension
				alu_a = pc;
				alu_b = immediate;
			end
			ADDI, SLTI, SLTIU, XORI, ORI, ANDI, ADDIW: // I - type immediate + sign extension
				alu_b = immediate;
			SLLI, SRLI, SRAI:
				alu_b = {59'b0, instr[25:20]};
			SLLIW, SRLIW, SRAIW: // Shift Instructions shamt <- instr[24:20]
				alu_b = {59'b0, instr[24:20]};
			default: begin end // Skip other instructions for now
		endcase

		write_enable = (state == DECODE) && has_rd && (codeword != UNKNOWN);
	end

	always_comb begin
		next_pc = pc + 4;
	end

	// Format the codeword name for display purposes to keep wp1 working
	function automatic string codeword_text(input codeword_t value);
		if (value == FENCE_I)
			return "FENCE.I";
		return value.name();
	endfunction

	always_ff @(posedge clk) begin
		if (reset) begin
			pc <= entry;
			beat_count <= 3'b000;
			state <= IDLE;
		end else begin
			case (state)
				IDLE: begin // Init state, start fetching the first instruction line
					state <= ARADDR;
				end
				ARADDR: begin
					if (m_axi_arvalid && m_axi_arready) begin
						beat_count <= 3'b000; // Reset beat_count for the new line fetch
						state <= RDATA;
					end
				end
				RDATA: begin
					if (m_axi_rvalid) begin
						fetched_line[beat_count * 64 +: 64] <= m_axi_rdata; // Set each 64-bit beat of the fetched line based on beat_count
						if (m_axi_rlast) begin // Input signal for last beat
							state <= DECODE;
						end else begin
							beat_count <= beat_count + 1'b1;
						end
					end
				end
				DECODE: begin
					if (instr == 32'b0) begin
						for (int reg_index = 0; reg_index < 32; reg_index = reg_index + 1)
							$display("Register %0d: %016x", reg_index, registers.read_reg(reg_index));
						$finish;
					end else begin
						if (has_rd)
							$display("%x: %s %0d", pc, codeword_text(codeword), rd);
						else
							$display("%x: %s", pc, codeword_text(codeword));
						pc <= next_pc;
					end
					state <= ARADDR;
				end
				default: state <= ARADDR;
			endcase
		end
	end

	initial begin
		$display("Initializing top, entry point = 0x%x", entry);
	end
endmodule

