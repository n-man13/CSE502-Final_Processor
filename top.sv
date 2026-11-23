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

endmodule

module l1_i_cache #(
	parameter int CACHE_BYTES = 16384
) (
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
	l1_cache #(
		.WRITE_ENABLE(1'b0),
		.CACHE_BYTES(CACHE_BYTES)
	) cache (
		.clk, .reset, .cpu_req_valid, .cpu_req_ready,
		.cpu_req_write(1'b0), .cpu_req_addr,
		.cpu_req_wdata('0), .cpu_req_wstrb('0),
		.cpu_resp_valid, .cpu_resp_rdata,
		.mem_read_req, .mem_read_addr, .mem_read_valid, .mem_read_data,
		.mem_write_req(), .mem_write_addr(), .mem_write_data(),
		.mem_write_strb(), .mem_write_ready(1'b0)
	);
endmodule

module l1_d_cache #(
	parameter int CACHE_BYTES = 65536
) (
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
	l1_cache #(
		.WRITE_ENABLE(1'b1),
		.CACHE_BYTES(CACHE_BYTES)
	) cache (
		.clk, .reset, .cpu_req_valid, .cpu_req_ready,
		.cpu_req_write, .cpu_req_addr, .cpu_req_wdata, .cpu_req_wstrb,
		.cpu_resp_valid, .cpu_resp_rdata,
		.mem_read_req, .mem_read_addr, .mem_read_valid, .mem_read_data,
		.mem_write_req, .mem_write_addr, .mem_write_data,
		.mem_write_strb, .mem_write_ready
	);
endmodule

typedef struct packed {
	logic reg_write;
	logic mem_read;
	logic mem_write;
	logic branch;
	logic jump;
	logic alu_src;
	logic [3:0] alu_op;
	logic [1:0] mem_to_reg;
} control_t;

typedef struct packed {
	logic valid;
	logic [31:0] instr;
	logic [63:0] pc;
	logic [63:0] pc_plus_1;
} if_id_t;

typedef struct packed {
	logic valid;
	logic [31:0] instr;
	logic [63:0] pc_plus_1;
	logic [63:0] regA;
	logic [63:0] regB;
	logic [63:0] immediate;
	logic [4:0] rd;
	logic [4:0] rs1;
	logic [4:0] rs2;
	codeword_t codeword;
	control_t control;
} id_ex_t;

typedef struct packed {
	logic valid;
	logic [31:0] instr;
	logic [63:0] pc_plus_1;
	logic [63:0] alu_result;
	logic [63:0] pc_plus_1_plus_offset;
	logic [63:0] regB;
	logic [4:0] rd;
	codeword_t codeword;
	control_t control;
} ex_mem_t;

typedef struct packed {
	logic valid;
	logic [31:0] instr;
	logic [63:0] alu_result;
	logic [63:0] pc_plus_1_plus_offset;
	logic [63:0] loaded_data;
	logic [4:0] rd;
	codeword_t codeword;
	control_t control;
} mem_wb_t;

module pipeline_controller (
	input  logic clk,
	input  logic reset,
	input  logic stall,
	input  logic flush,
	input  logic [31:0] fetch_instr,
	input  logic [63:0] fetch_pc,
	input  logic [63:0] regA_in,
	input  logic [63:0] regB_in,
	input  logic [63:0] immediate_in,
	input logic [4:0] rd_in,
	input logic [4:0] rs1_in,
	input logic [4:0] rs2_in,
	input codeword_t codeword_in,
	input  control_t control_in,
	input  logic [63:0] alu_result_in,
	input  logic [63:0] pc_plus_offset_in,
	input  logic [63:0] loaded_data_in,
	output if_id_t if_id,
	output id_ex_t id_ex,
	output ex_mem_t ex_mem,
	output mem_wb_t mem_wb
);
	always_ff @(posedge clk) begin
		if (reset) begin
			if_id <= '0;
			id_ex <= '0;
			ex_mem <= '0;
			mem_wb <= '0;
		end else if (flush) begin
			// A redirect resolved in EX invalidates younger IF and ID work.
			// The resolving instruction remains in EX/MEM.
			if_id <= '0;
			id_ex <= '0;
			mem_wb <= ex_mem;
		end else if (stall) begin
			// Hold all in-flight state while the front end or a downstream
			// resource is unavailable.
			if_id <= if_id;
			id_ex <= id_ex;
			ex_mem <= ex_mem;
			mem_wb <= mem_wb;
		end else begin
			if_id.valid <= 1'b1;
			if_id.instr <= fetch_instr;
			if_id.pc_plus_1 <= fetch_pc + 64'd4;

			id_ex.valid <= if_id.valid;
			id_ex.instr <= if_id.instr;
			id_ex.pc_plus_1 <= if_id.pc_plus_1;
			id_ex.regA <= regA_in;
			id_ex.regB <= regB_in;
			id_ex.immediate <= immediate_in;
			id_ex.rd <= rd_in;
			id_ex.rs1 <= rs1_in;
			id_ex.rs2 <= rs2_in;
			id_ex.codeword <= codeword_in;
			id_ex.control <= control_in;

			ex_mem.valid <= id_ex.valid;
			ex_mem.instr <= id_ex.instr;
			ex_mem.pc_plus_1 <= id_ex.pc_plus_1;
			ex_mem.alu_result <= alu_result_in;
			ex_mem.pc_plus_1_plus_offset <= pc_plus_offset_in;
			ex_mem.regB <= id_ex.regB;
			ex_mem.rd <= id_ex.rd;
			ex_mem.codeword <= id_ex.codeword;
			ex_mem.control <= id_ex.control;

			mem_wb.valid <= ex_mem.valid;
			mem_wb.instr <= ex_mem.instr;
			mem_wb.alu_result <= ex_mem.alu_result;
			mem_wb.pc_plus_1_plus_offset <= ex_mem.pc_plus_1_plus_offset;
			mem_wb.loaded_data <= loaded_data_in;
			mem_wb.rd <= ex_mem.rd;
			mem_wb.codeword <= ex_mem.codeword;
			mem_wb.control <= ex_mem.control;
		end
	end
endmodule

module instruction_fetch #(
	ID_WIDTH = 13,
	ADDR_WIDTH = 64,
	DATA_WIDTH = 64,
	STRB_WIDTH = DATA_WIDTH/8
) (
	input logic clk,
	input logic reset,
	input logic [63:0] entry,
	input logic consume,
	output logic [63:0] fetch_pc,
	output logic [31:0] fetch_instr,
	output logic fetch_valid,

	output logic [ID_WIDTH-1:0]    m_axi_awid,
	output logic [ADDR_WIDTH-1:0]  m_axi_awaddr,
	output logic [7:0]             m_axi_awlen,
	output logic [2:0]             m_axi_awsize,
	output logic [1:0]             m_axi_awburst,
	output logic                   m_axi_awlock,
	output logic [3:0]             m_axi_awcache,
	output logic [2:0]             m_axi_awprot,
	output logic                   m_axi_awvalid,
	input logic                    m_axi_awready,
	output logic [DATA_WIDTH-1:0]  m_axi_wdata,
	output logic [STRB_WIDTH-1:0]  m_axi_wstrb,
	output logic                   m_axi_wlast,
	output logic                   m_axi_wvalid,
	input logic                    m_axi_wready,
	input logic [ID_WIDTH-1:0]     m_axi_bid,
	input logic [1:0]              m_axi_bresp,
	input logic                    m_axi_bvalid,
	output logic                   m_axi_bready,
	output logic [ID_WIDTH-1:0]    m_axi_arid,
	output logic [ADDR_WIDTH-1:0]  m_axi_araddr,
	output logic [7:0]             m_axi_arlen,
	output logic [2:0]             m_axi_arsize,
	output logic [1:0]              m_axi_arburst,
	output logic                   m_axi_arlock,
	output logic [3:0]             m_axi_arcache,
	output logic [2:0]             m_axi_arprot,
	output logic                   m_axi_arvalid,
	input logic                    m_axi_arready,
	input logic [ID_WIDTH-1:0]     m_axi_rid,
	input logic [DATA_WIDTH-1:0]  m_axi_rdata,
	input logic [1:0]              m_axi_rresp,
	input logic                    m_axi_rlast,
	input logic                    m_axi_rvalid,
	output logic                   m_axi_rready,
	input logic                    m_axi_acvalid,
	output logic                   m_axi_acready,
	input logic [ADDR_WIDTH-1:0]  m_axi_acaddr,
	input logic [3:0]              m_axi_acsnoop
);
	logic [63:0] pc;
	logic [511:0] fetched_line;
	logic [2:0] beat_count;

	typedef enum logic [1:0] {F_IDLE, F_ARADDR, F_RDATA, F_DECODE} fetch_state_t;
	fetch_state_t state;

	assign fetch_pc = pc;
	assign fetch_instr = fetched_line[(pc[5:2] * 32) +: 32];
	assign fetch_valid = (state == F_DECODE);

	assign m_axi_awid = '0;
	assign m_axi_awaddr = '0;
	assign m_axi_awlen = '0;
	assign m_axi_awsize = '0;
	assign m_axi_awburst = '0;
	assign m_axi_awlock = 1'b0;
	assign m_axi_awcache = '0;
	assign m_axi_awprot = '0;
	assign m_axi_awvalid = 1'b0;
	assign m_axi_wdata = '0;
	assign m_axi_wstrb = '0;
	assign m_axi_wlast = 1'b0;
	assign m_axi_wvalid = 1'b0;
	assign m_axi_bready = 1'b0;
	assign m_axi_acready = 1'b0;

	assign m_axi_araddr = pc & ~64'h3f;
	assign m_axi_arvalid = (state == F_ARADDR);
	assign m_axi_arlen = 8'd7;
	assign m_axi_arsize = 3'b011;
	assign m_axi_arburst = 2'b10;
	assign m_axi_arid = '0;
	assign m_axi_arlock = 1'b0;
	assign m_axi_arcache = '0;
	assign m_axi_arprot = '0;
	assign m_axi_rready = (state == F_RDATA);

	always_ff @(posedge clk) begin
		if (reset) begin
			pc <= entry;
			beat_count <= 3'b000;
			state <= F_IDLE;
			fetched_line <= '0;
		end else begin
			case (state)
				F_IDLE: state <= F_ARADDR;
				F_ARADDR: begin
					if (m_axi_arvalid && m_axi_arready) begin
						beat_count <= 3'b000;
						state <= F_RDATA;
					end
				end
				F_RDATA: begin
					if (m_axi_rvalid) begin
						fetched_line[beat_count * 64 +: 64] <= m_axi_rdata;
						if (m_axi_rlast)
							state <= F_DECODE;
						else
							beat_count <= beat_count + 1'b1;
					end
				end
				F_DECODE: begin
					if (consume) begin
						pc <= pc + 64'd4;
						state <= F_ARADDR;
					end
				end
				default: state <= F_IDLE;
			endcase
		end
	end
endmodule

module top
#(
	ID_WIDTH = 13,
	ADDR_WIDTH = 64,
	DATA_WIDTH = 64,
	STRB_WIDTH = DATA_WIDTH/8
)
(
	input  logic clk,
	input  logic reset,
	input  logic hz32768timer,

	// 64-bit addresses of the program entry point and initial stack pointer
	input  logic [63:0] entry,
	input  logic [63:0] stackptr,
	input  logic [63:0] satp,

	// interface to connect to the bus
	output logic [ID_WIDTH-1:0]    m_axi_awid,
	output logic [ADDR_WIDTH-1:0]  m_axi_awaddr,
	output logic [7:0]             m_axi_awlen,
	output logic [2:0]             m_axi_awsize,
	output logic [1:0]             m_axi_awburst,
	output logic                   m_axi_awlock,
	output logic [3:0]             m_axi_awcache,
	output logic [2:0]             m_axi_awprot,
	output logic                   m_axi_awvalid,
	input  logic                   m_axi_awready,
	output logic [DATA_WIDTH-1:0]  m_axi_wdata,
	output logic [STRB_WIDTH-1:0]  m_axi_wstrb,
	output logic                   m_axi_wlast,
	output logic                   m_axi_wvalid,
	input  logic                   m_axi_wready,
	input  logic [ID_WIDTH-1:0]    m_axi_bid,
	input  logic [1:0]             m_axi_bresp,
	input  logic                   m_axi_bvalid,
	output logic                   m_axi_bready,
	output logic [ID_WIDTH-1:0]    m_axi_arid,
	output logic [ADDR_WIDTH-1:0]  m_axi_araddr,
	output logic [7:0]             m_axi_arlen,
	output logic [2:0]             m_axi_arsize,
	output logic [1:0]             m_axi_arburst,
	output logic                   m_axi_arlock,
	output logic [3:0]             m_axi_arcache,
	output logic [2:0]             m_axi_arprot,
	output logic                   m_axi_arvalid,
	input  logic                   m_axi_arready,
	input  logic [ID_WIDTH-1:0]    m_axi_rid,
	input  logic [DATA_WIDTH-1:0]  m_axi_rdata,
	input  logic [1:0]             m_axi_rresp,
	input  logic                   m_axi_rlast,
	input  logic                   m_axi_rvalid,
	output logic                   m_axi_rready,
	input  logic                   m_axi_acvalid,
	output logic                   m_axi_acready,
	input  logic [ADDR_WIDTH-1:0]  m_axi_acaddr,
	input  logic [3:0]             m_axi_acsnoop
);

	logic [63:0] fetch_pc;
	logic [31:0] fetch_instr;
	logic fetch_valid;
	logic fetch_consume;
	logic [31:0] if_instr;

	// Register File connections
	logic [63:0] regA_value, regB_value;
	logic [4:0] rs1, rs2, rd;
	logic has_rd;

	// ALU connections
	logic [63:0] immediate;
	logic [63:0] alu_result;
	logic [63:0] pc_plus_offset;
	logic [63:0] mem_data;
	logic [63:0] write_data;
	logic write_enable;
	logic [4:0] wb_rd;
	logic id_has_rd;
	codeword_t id_codeword;
	logic fetch_valid;
	codeword_t codeword;
	control_t decode_control;
	if_id_t if_id;
	id_ex_t id_ex;
	ex_mem_t ex_mem;
	mem_wb_t mem_wb;
	logic pipeline_stall;
	logic pipeline_flush;
	assign if_instr = fetch_instr;
	assign rs1 = fetch_instr[19:15];
	assign rs2 = fetch_instr[24:20];
	assign pipeline_stall = !fetch_valid;
	assign pipeline_flush = 1'b0;
	assign fetch_consume = fetch_valid;

	instruction_fetch fetch (
		.clk (clk),
		.reset (reset),
		.entry (entry),
		.consume (fetch_consume),
		.fetch_pc (fetch_pc),
		.fetch_instr (fetch_instr),
		.fetch_valid (fetch_valid),
		.m_axi_awid (m_axi_awid),
		.m_axi_awaddr (m_axi_awaddr),
		.m_axi_awlen (m_axi_awlen),
		.m_axi_awsize (m_axi_awsize),
		.m_axi_awburst (m_axi_awburst),
		.m_axi_awlock (m_axi_awlock),
		.m_axi_awcache (m_axi_awcache),
		.m_axi_awprot (m_axi_awprot),
		.m_axi_awvalid (m_axi_awvalid),
		.m_axi_awready (m_axi_awready),
		.m_axi_wdata (m_axi_wdata),
		.m_axi_wstrb (m_axi_wstrb),
		.m_axi_wlast (m_axi_wlast),
		.m_axi_wvalid (m_axi_wvalid),
		.m_axi_wready (m_axi_wready),
		.m_axi_bid (m_axi_bid),
		.m_axi_bresp (m_axi_bresp),
		.m_axi_bvalid (m_axi_bvalid),
		.m_axi_bready (m_axi_bready),
		.m_axi_arid (m_axi_arid),
		.m_axi_araddr (m_axi_araddr),
		.m_axi_arlen (m_axi_arlen),
		.m_axi_arsize (m_axi_arsize),
		.m_axi_arburst (m_axi_arburst),
		.m_axi_arlock (m_axi_arlock),
		.m_axi_arcache (m_axi_arcache),
		.m_axi_arprot (m_axi_arprot),
		.m_axi_arvalid (m_axi_arvalid),
		.m_axi_arready (m_axi_arready),
		.m_axi_rid (m_axi_rid),
		.m_axi_rdata (m_axi_rdata),
		.m_axi_rresp (m_axi_rresp),
		.m_axi_rlast (m_axi_rlast),
		.m_axi_rvalid (m_axi_rvalid),
		.m_axi_rready (m_axi_rready),
		.m_axi_acvalid (m_axi_acvalid),
		.m_axi_acready (m_axi_acready),
		.m_axi_acaddr (m_axi_acaddr),
		.m_axi_acsnoop (m_axi_acsnoop)
	);

	decoder decode (
		.instr (if_instr),
		.codeword (codeword),
		.rd (rd),
		.has_rd (has_rd)
	);

	decoder decode_pipeline_instruction (
		.instr (if_id.instr),
		.codeword (id_codeword),
		.rd (),
		.has_rd (id_has_rd)
	);

	regfile registers (
		.rs1_data (regA_value),
		.rs2_data (regB_value),
		.clk (clk),
		.reset (reset),
		.initial_sp (stackptr),
		.rs1 (rs1),
		.rs2 (rs2),
		.rd (mem_wb.rd),
		.wdata (write_data),
		.write_enable (write_enable)
	);

	alu execute_alu (
		.result (alu_result),
		.a (id_ex.regA),
		.b (id_ex.control.alu_src ? id_ex.immediate : id_ex.regB),
		.codeword (id_ex.codeword)
	);

	always_comb begin
		decode_control = '0;
		immediate = {{52{if_id.instr[31]}}, if_id.instr[31:20]}; // Assuming Standard I-type immediate + sign extension
		pc_plus_offset = if_id.pc_plus_1 + immediate;
		write_enable = mem_wb.valid && mem_wb.control.reg_write;
		mem_data = ex_mem.alu_result;

		case (id_codeword)
			LUI: begin
				immediate = {{32{if_id.instr[31]}}, if_id.instr[31:12], 12'b0}; // U - type immediate + sign extension
				decode_control.alu_src = 1'b1;
				decode_control.reg_write = id_has_rd;
			end
			AUIPC: begin
				immediate = {{32{if_id.instr[31]}}, if_id.instr[31:12], 12'b0}; // U - type immediate + sign extension
				decode_control.alu_src = 1'b1;
				decode_control.reg_write = id_has_rd;
			end
			ADDI, SLTI, SLTIU, XORI, ORI, ANDI, ADDIW: begin // I - type immediate + sign extension
				immediate = {{52{if_id.instr[31]}}, if_id.instr[31:20]};
				decode_control.alu_src = 1'b1;
				decode_control.reg_write = id_has_rd;
			end
			SLLI, SRLI, SRAI: begin
				immediate = {{58{1'b0}}, if_id.instr[25:20]};
				decode_control.alu_src = 1'b1;
				decode_control.reg_write = id_has_rd;
			end
			SLLIW, SRLIW, SRAIW: begin // Shift amount uses instr[24:20] for word variants
				immediate = {{59{1'b0}}, if_id.instr[24:20]};
				decode_control.alu_src = 1'b1;
				decode_control.reg_write = id_has_rd;
			end
			ADD, SUB, SLL, SLT, SLTU, XOR, SRL, SRA, OR, AND,
			MUL, MULH, MULHSU, MULHU, DIV, DIVU, REM, REMU,
			ADDW, SUBW, SLLW, SRLW, SRAW, MULW, DIVW, DIVUW, REMW, REMUW: begin
				decode_control.reg_write = id_has_rd;
			end
			default: begin end
		endcase
	end

	pipeline_controller pipe (
		.clk (clk),
		.reset (reset),
		.stall (pipeline_stall),
		.flush (pipeline_flush),
		.fetch_instr (if_instr),
		.fetch_pc (fetch_pc),
		.regA_in ((id_codeword == AUIPC) ? if_id.pc : regA_value),
		.regB_in (regB_value),
		.immediate_in (immediate),
		.rd_in (rd),
		.rs1_in (rs1),
		.rs2_in (rs2),
		.codeword_in (id_codeword),
		.control_in (decode_control),
		.alu_result_in (alu_result),
		.pc_plus_offset_in (pc_plus_offset),
		.loaded_data_in (mem_data),
		.if_id (if_id),
		.id_ex (id_ex),
		.ex_mem (ex_mem),
		.mem_wb (mem_wb)
	);

	always_comb begin
		write_data = mem_wb.alu_result;
		if (mem_wb.control.mem_to_reg == 2'b01)
			write_data = mem_wb.loaded_data;
	end

	// Format the codeword name for display purposes to keep wp1 working
	function automatic string codeword_text(input codeword_t value);
		if (value == FENCE_I)
			return "FENCE.I";
		return value.name();
	endfunction

	always_ff @(posedge clk) begin
		if (!reset && fetch_valid) begin
			if (if_instr == 32'b0) begin
				for (int reg_index = 0; reg_index < 32; reg_index = reg_index + 1)
					$display("Register %0d: %016x", reg_index, registers.read_reg(reg_index));
				$finish;
			end else if (has_rd) begin
				$display("%x: %s %0d", fetch_pc, codeword_text(codeword), rd);
			end else begin
				$display("%x: %s", fetch_pc, codeword_text(codeword));
			end
		end
	end

	initial begin
		$display("Initializing top, entry point = 0x%x", entry);
	end
endmodule
