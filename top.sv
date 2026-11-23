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
	CSRRW, CSRRS, CSRRC, CSRRWI, CSRRSI, CSRRCI,
	// RV64A: AMO_W/AMO_D cover every read-modify-write op; the op is instr[31:27].
	LR_W, LR_D, SC_W, SC_D, AMO_W, AMO_D
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
		// All-zero word: treat as NOP (same effect as addi x0, x0, 0).
		// Without this, opcode bits decode as LB from address 0.
		if (instr == 32'b0) begin
			codeword = ADDI;
			has_rd = 1'b0;
		end else if (instr[1:0] != 2'b11) begin
			codeword = UNKNOWN;
			has_rd = 1'b0;
		end else case (opcode[6:2])
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
			OPCODE_AMO: begin
				has_rd = 1'b1;
				if (funct3 == 3'b010 || funct3 == 3'b011) begin
					case (instr[31:27])
						5'b00010: if (funct3 == 3'b010) codeword = LR_W; else codeword = LR_D;
						5'b00011: if (funct3 == 3'b010) codeword = SC_W; else codeword = SC_D;
						5'b00001, 5'b00000, 5'b00100, 5'b01100, 5'b01000,
						5'b10000, 5'b10100, 5'b11000, 5'b11100:
							if (funct3 == 3'b010) codeword = AMO_W; else codeword = AMO_D;
						default: begin codeword = UNKNOWN; has_rd = 1'b0; end
					endcase
				end else begin
					codeword = UNKNOWN;
					has_rd = 1'b0;
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
	output logic [63:0] syscall_a0, syscall_a1, syscall_a2,
	output logic [63:0] syscall_a3, syscall_a4, syscall_a5,
	output logic [63:0] syscall_a6, syscall_a7,
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
	assign syscall_a0 = (10 < 32) ? regs[10] : 64'd0;
	assign syscall_a1 = (11 < 32) ? regs[11] : 64'd0;
	assign syscall_a2 = (12 < 32) ? regs[12] : 64'd0;
	assign syscall_a3 = (13 < 32) ? regs[13] : 64'd0;
	assign syscall_a4 = (14 < 32) ? regs[14] : 64'd0;
	assign syscall_a5 = (15 < 32) ? regs[15] : 64'd0;
	assign syscall_a6 = (16 < 32) ? regs[16] : 64'd0;
	assign syscall_a7 = (17 < 32) ? regs[17] : 64'd0;

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
			// Effective address: rs1 + immediate (alu_src selects the immediate).
			LB, LH, LW, LBU, LHU, LWU, LD,
			SB, SH, SW, SD: result = a + b;
			// Atomics have no offset: the address is rs1 and b carries rs2.
			LR_W, LR_D, SC_W, SC_D, AMO_W, AMO_D: result = a;
			default:   result = 64'b0;
		endcase
	end
endmodule

// Common blocking cache used by the instruction and data-cache wrappers.
// Default geometry matches the course memory model: 64-byte lines (8x8B beats).
module l1_cache #(
	parameter bit WRITE_ENABLE = 1'b0,
	parameter int ADDR_WIDTH = 64,
	parameter int DATA_WIDTH = 64,
	parameter int CACHE_BYTES = 8192,
	parameter int LINE_BYTES = 64,
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
	input logic mem_write_ready,
	input logic snoop_valid,
	input logic [ADDR_WIDTH-1:0] snoop_addr
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
	logic [DATA_WIDTH-1:0] response_data;

	wire [INDEX_BITS-1:0] snoop_set = snoop_addr[OFFSET_BITS +: INDEX_BITS];
	wire [TAG_BITS-1:0] snoop_tag = snoop_addr[ADDR_WIDTH-1 -: TAG_BITS];

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
		// Hold request high for the whole line transfer so the AXI arbiter
		// can stream an 8-beat burst without missing single-cycle pulses.
		mem_read_req = (state == S_REFILL);
		mem_read_addr = {req_addr[ADDR_WIDTH-1:OFFSET_BITS], {OFFSET_BITS{1'b0}}};
		mem_write_req = (state == S_WRITEBACK);
		mem_write_addr = {tag[req_set][victim_way], req_set, {OFFSET_BITS{1'b0}}};
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
			for (set_i = 0; set_i < SETS; set_i = set_i + 1) begin
				lru[set_i] = 1'b0;
				for (way_i = 0; way_i < WAYS; way_i = way_i + 1) begin
					valid[set_i][way_i] = 1'b0;
					dirty[set_i][way_i] = 1'b0;
					tag[set_i][way_i] = '0;
					for (beat_i = 0; beat_i < BEATS_PER_LINE; beat_i = beat_i + 1)
						line_data[set_i][way_i][beat_i] = '0;
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
						if (WRITE_ENABLE &&
						    valid[req_set][selected_victim_way] &&
						    dirty[req_set][selected_victim_way])
							state <= S_WRITEBACK;
						else
							state <= S_REFILL;
					end
				end

				S_WRITEBACK: begin
					if (mem_write_ready) begin
						if (transfer_beat == BEAT_BITS'(BEATS_PER_LINE-1)) begin
							transfer_beat <= '0;
							state <= S_REFILL;
						end else
							transfer_beat <= transfer_beat + 1'b1;
					end
				end

				S_REFILL: begin
					if (mem_read_valid) begin
						line_data[req_set][victim_way][transfer_beat] <= mem_read_data;
						if (transfer_beat == req_beat)
							response_data <= mem_read_data;
						if (transfer_beat == BEAT_BITS'(BEATS_PER_LINE-1)) begin
							valid[req_set][victim_way] <= 1'b1;
							dirty[req_set][victim_way] <= 1'b0;
							tag[req_set][victim_way] <= req_tag;
							lru[req_set] <= !victim_way;
							transfer_beat <= '0;
							state <= req_write ? S_LOOKUP : S_RESP;
						end else
							transfer_beat <= transfer_beat + 1'b1;
					end
				end

				S_RESP: state <= S_IDLE;
				default: state <= S_IDLE;
			endcase

			// The fake OS merges pending stores into RAM before a syscall touches
			// memory, so dropping a snooped line is safe even when it is dirty.
			if (snoop_valid)
				for (way_i = 0; way_i < WAYS; way_i = way_i + 1)
					if (tag[snoop_set][way_i] == snoop_tag) begin
						valid[snoop_set][way_i] <= 1'b0;
						dirty[snoop_set][way_i] <= 1'b0;
					end
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
	input logic [63:0] mem_read_data,
	input logic snoop_valid,
	input logic [63:0] snoop_addr
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
		.mem_write_strb(), .mem_write_ready(1'b0),
		.snoop_valid, .snoop_addr
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
	input logic mem_write_ready,
	input logic snoop_valid,
	input logic [63:0] snoop_addr
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
		.mem_write_strb, .mem_write_ready,
		.snoop_valid, .snoop_addr
	);
endmodule

typedef struct packed {
	logic reg_write;
	logic mem_read;
	logic mem_write;
	logic amo;        // read-modify-write atomic: read phase, then write phase
	logic branch;
	logic jump;
	logic alu_src;
	logic [1:0] mem_to_reg; // 00 ALU, 01 memory/atomic result, 10 ecall return
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
	logic [63:0] pc;
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
	logic [63:0] pc;
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
	logic [63:0] pc;
	logic [63:0] pc_plus_1;
	logic [63:0] alu_result;
	logic [63:0] pc_plus_1_plus_offset;
	logic [63:0] loaded_data;
	logic [4:0] rd;
	codeword_t codeword;
	control_t control;
} mem_wb_t;

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
	input  logic [63:0] entry,
	input  logic [63:0] stackptr,
	input  logic [63:0] satp,

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

	if_id_t if_id;
	id_ex_t id_ex;
	ex_mem_t ex_mem;
	mem_wb_t mem_wb;

	logic [63:0] pc;
	logic [63:0] if_req_pc; // next I-fetch address (decoupled from pipe PC updates)
	logic [63:0] fetch_pc;
	logic [31:0] fetch_instr;
	logic fetch_valid;
	logic [2:0] zero_instr_count;
	logic pipeline_all_zero;
	logic i_pending;
	logic [63:0] i_pending_pc;
	logic i_cancel_resp;

	logic [63:0] regA_value, regB_value;
	logic [63:0] id_regA, id_regB;
	logic [63:0] immediate;
	logic [4:0] rs1, rs2, rd;
	logic has_rd;
	codeword_t id_codeword;
	control_t decode_control;
	logic [63:0] execute_alu_result;
	logic [63:0] alu_raw_result;
	logic [63:0] execute_target;
	logic redirect;
	logic [63:0] redirect_pc;
	logic load_use_stall;
	logic pipeline_stall;

	logic [63:0] ecall_ret;
	logic [63:0] write_data;
	logic write_enable;
	logic [63:0] d_load_data;
	logic d_read_ready;
	logic d_write_ready;
	logic [63:0] syscall_args [0:7];
	logic [63:0] cycle_count;

	always_ff @(posedge clk) begin
		if (reset) cycle_count <= '0;
		else cycle_count <= cycle_count + 64'd1;
	end

	// Instruction cache
	logic i_cpu_req_valid, i_cpu_req_ready;
	logic i_cpu_resp_valid;
	logic [63:0] i_cpu_resp_rdata;
	logic i_mem_read_req;
	logic [63:0] i_mem_read_addr;
	logic i_mem_read_valid;
	logic [63:0] i_mem_read_data;

	l1_i_cache #(.CACHE_BYTES(16384)) i_cache (
		.clk(clk), .reset(reset),
		.cpu_req_valid(i_cpu_req_valid), .cpu_req_ready(i_cpu_req_ready),
		.cpu_req_addr(if_req_pc), .cpu_resp_valid(i_cpu_resp_valid),
		.cpu_resp_rdata(i_cpu_resp_rdata),
		.mem_read_req(i_mem_read_req), .mem_read_addr(i_mem_read_addr),
		.mem_read_valid(i_mem_read_valid), .mem_read_data(i_mem_read_data),
		.snoop_valid(m_axi_acvalid), .snoop_addr(m_axi_acaddr)
	);

	// Data cache
	logic d_cpu_req_valid, d_cpu_req_ready;
	logic d_cpu_req_write;
	logic [63:0] d_cpu_req_addr;
	logic [63:0] d_cpu_req_wdata;
	logic [7:0] d_cpu_req_wstrb;
	logic d_cpu_resp_valid;
	logic [63:0] d_cpu_resp_rdata;
	logic d_mem_read_req;
	logic [63:0] d_mem_read_addr;
	logic d_mem_read_valid;
	logic [63:0] d_mem_read_data;
	logic d_mem_write_req;
	logic [63:0] d_mem_write_addr;
	logic [63:0] d_mem_write_data;
	logic [7:0] d_mem_write_strb;
	logic d_mem_write_ready;
	logic d_pending;
	logic amo_phase;      // 0: read the old value, 1: write the new value
	logic [63:0] amo_old; // raw 64-bit cache word captured by the read phase
	logic resv_valid;     // LR/SC reservation
	logic [63:0] resv_addr;

	wire mem_is_amo = ex_mem.valid && ex_mem.control.amo;
	wire mem_is_lr = ex_mem.valid && (ex_mem.codeword == LR_W || ex_mem.codeword == LR_D);
	wire mem_is_sc = ex_mem.valid && (ex_mem.codeword == SC_W || ex_mem.codeword == SC_D);
	wire sc_fail = mem_is_sc && !(resv_valid && resv_addr == ex_mem.alu_result);
	// A failed SC never touches memory; it just writes 1 to rd.
	wire mem_op = ex_mem.valid && (ex_mem.control.mem_read || ex_mem.control.mem_write) && !sc_fail;
	logic [3:0] mem_size;
	always_comb begin
		case (ex_mem.codeword)
			LB, LBU, SB: mem_size = 4'd1;
			LH, LHU, SH: mem_size = 4'd2;
			LW, LWU, SW, LR_W, SC_W, AMO_W: mem_size = 4'd4;
			default: mem_size = 4'd8;
		endcase
	end
	// Misaligned accesses (hwprobe reports them as supported) that straddle an
	// 8-byte beat are done as two cache accesses: split_phase 0, then 1.
	logic split_phase;
	logic [63:0] split_lo; // first-beat read data
	wire [2:0] mem_off = ex_mem.alu_result[2:0];
	wire mem_cross = mem_op && !mem_is_amo && ({1'b0, mem_off} + mem_size > 4'd8);

	// An AMO finishes on the response to its write phase, a split access on its second beat.
	wire d_mem_done = d_cpu_resp_valid && (!mem_is_amo || amo_phase) && (!mem_cross || split_phase);
	wire d_mem_busy = mem_op && !d_mem_done;

	// Snoops for lines a syscall changed arrive one per cycle after the ecall;
	// keep new requests out of the D-cache until they have all landed.
	logic [1:0] ecall_guard;
	wire snoop_block = m_axi_acvalid || (ecall_guard != 2'd0);
	assign d_cpu_req_valid = mem_op && !d_pending && !snoop_block;
	assign d_cpu_req_write = mem_is_amo ? amo_phase : ex_mem.control.mem_write;
	assign d_cpu_req_addr = split_phase ? {ex_mem.alu_result[63:3] + 61'd1, 3'b000} : ex_mem.alu_result;

	wire [31:0] amo_old_word = ex_mem.alu_result[2] ? amo_old[63:32] : amo_old[31:0];
	wire [63:0] amo_old_val = (ex_mem.codeword == AMO_W) ? {{32{amo_old_word[31]}}, amo_old_word} : amo_old;
	wire [63:0] amo_src = (ex_mem.codeword == AMO_W) ? {{32{ex_mem.regB[31]}}, ex_mem.regB[31:0]} : ex_mem.regB;
	logic [63:0] amo_new;
	always_comb begin
		// Sign-extending .W operands keeps both signed and unsigned ordering intact.
		case (ex_mem.instr[31:27])
			5'b00001: amo_new = amo_src;
			5'b00000: amo_new = amo_old_val + amo_src;
			5'b00100: amo_new = amo_old_val ^ amo_src;
			5'b01100: amo_new = amo_old_val & amo_src;
			5'b01000: amo_new = amo_old_val | amo_src;
			5'b10000: amo_new = ($signed(amo_old_val) < $signed(amo_src)) ? amo_old_val : amo_src;
			5'b10100: amo_new = ($signed(amo_old_val) > $signed(amo_src)) ? amo_old_val : amo_src;
			5'b11000: amo_new = (amo_old_val < amo_src) ? amo_old_val : amo_src;
			5'b11100: amo_new = (amo_old_val > amo_src) ? amo_old_val : amo_src;
			default:  amo_new = amo_src;
		endcase
	end

	// Store value (unshifted, as the fake OS wants it) placed across two beats;
	// split_phase picks which beat goes to the cache.
	wire [63:0] st_raw = mem_is_amo ? amo_new : ex_mem.regB;
	wire [63:0] st_value = (mem_size == 4'd8) ? st_raw : (st_raw & ((64'd1 << {mem_size, 3'b000}) - 64'd1));
	wire [31:0] st_size = {28'b0, mem_size};
	wire [127:0] st_wide_data = {64'b0, st_value} << {mem_off, 3'b000};
	wire [15:0] st_wide_strb = ((16'd1 << mem_size) - 16'd1) << mem_off;
	assign d_cpu_req_wdata = split_phase ? st_wide_data[127:64] : st_wide_data[63:0];
	assign d_cpu_req_wstrb = split_phase ? st_wide_strb[15:8] : st_wide_strb[7:0];

	l1_d_cache #(.CACHE_BYTES(65536)) d_cache (
		.clk(clk), .reset(reset),
		.cpu_req_valid(d_cpu_req_valid), .cpu_req_ready(d_cpu_req_ready),
		.cpu_req_write(d_cpu_req_write), .cpu_req_addr(d_cpu_req_addr),
		.cpu_req_wdata(d_cpu_req_wdata), .cpu_req_wstrb(d_cpu_req_wstrb),
		.cpu_resp_valid(d_cpu_resp_valid), .cpu_resp_rdata(d_cpu_resp_rdata),
		.mem_read_req(d_mem_read_req), .mem_read_addr(d_mem_read_addr),
		.mem_read_valid(d_mem_read_valid), .mem_read_data(d_mem_read_data),
		.mem_write_req(d_mem_write_req), .mem_write_addr(d_mem_write_addr),
		.mem_write_data(d_mem_write_data), .mem_write_strb(d_mem_write_strb),
		.mem_write_ready(d_mem_write_ready),
		.snoop_valid(m_axi_acvalid), .snoop_addr(m_axi_acaddr)
	);

	decoder decode_if (
		.instr(if_id.instr), .codeword(id_codeword), .rd(), .has_rd(has_rd)
	);

	assign rs1 = if_id.instr[19:15];
	assign rs2 = if_id.instr[24:20];

	regfile registers (
		.rs1_data(regA_value), .rs2_data(regB_value),
		.syscall_a0(syscall_args[0]), .syscall_a1(syscall_args[1]),
		.syscall_a2(syscall_args[2]), .syscall_a3(syscall_args[3]),
		.syscall_a4(syscall_args[4]), .syscall_a5(syscall_args[5]),
		.syscall_a6(syscall_args[6]), .syscall_a7(syscall_args[7]),
		.clk(clk), .reset(reset), .initial_sp(stackptr),
		.rs1(rs1), .rs2(rs2), .rd(mem_wb.rd),
		.wdata(write_data), .write_enable(write_enable)
	);

	always_comb begin
		decode_control = '0;
		immediate = {{52{if_id.instr[31]}}, if_id.instr[31:20]};
		rd = if_id.instr[11:7];
		case (id_codeword)
			LUI: begin immediate={{32{if_id.instr[31]}},if_id.instr[31:12],12'b0}; decode_control.alu_src=1'b1; decode_control.reg_write=has_rd; end
			AUIPC: begin immediate={{32{if_id.instr[31]}},if_id.instr[31:12],12'b0}; decode_control.alu_src=1'b1; decode_control.reg_write=has_rd; end
			JAL: begin immediate={{43{if_id.instr[31]}},if_id.instr[31],if_id.instr[19:12],if_id.instr[20],if_id.instr[30:21],1'b0}; decode_control.jump=1'b1; decode_control.reg_write=has_rd; end
			JALR: begin immediate={{52{if_id.instr[31]}},if_id.instr[31:20]}; decode_control.jump=1'b1; decode_control.alu_src=1'b1; decode_control.reg_write=has_rd; end
			BEQ,BNE,BLT,BGE,BLTU,BGEU: begin immediate={{51{if_id.instr[31]}},if_id.instr[31],if_id.instr[7],if_id.instr[30:25],if_id.instr[11:8],1'b0}; decode_control.branch=1'b1; end
			LB,LH,LW,LBU,LHU,LWU,LD: begin immediate={{52{if_id.instr[31]}},if_id.instr[31:20]}; decode_control.alu_src=1'b1; decode_control.mem_read=1'b1; decode_control.mem_to_reg=2'b01; decode_control.reg_write=has_rd; end
			SB,SH,SW,SD: begin immediate={{52{if_id.instr[31]}},if_id.instr[31:25],if_id.instr[11:7]}; decode_control.alu_src=1'b1; decode_control.mem_write=1'b1; end
			ADDI,SLTI,SLTIU,XORI,ORI,ANDI,ADDIW: begin decode_control.alu_src=1'b1; decode_control.reg_write=has_rd; end
			SLLI,SRLI,SRAI: begin immediate={{58{1'b0}},if_id.instr[25:20]}; decode_control.alu_src=1'b1; decode_control.reg_write=has_rd; end
			SLLIW,SRLIW,SRAIW: begin immediate={{59{1'b0}},if_id.instr[24:20]}; decode_control.alu_src=1'b1; decode_control.reg_write=has_rd; end
			ADD,SUB,SLL,SLT,SLTU,XOR,SRL,SRA,OR,AND,
			MUL,MULH,MULHSU,MULHU,DIV,DIVU,REM,REMU,
			ADDW,SUBW,SLLW,SRLW,SRAW,MULW,DIVW,DIVUW,REMW,REMUW: decode_control.reg_write=has_rd;
			ECALL: begin decode_control.reg_write=1'b1; rd=5'd10; decode_control.mem_to_reg=2'b10; end
			LR_W,LR_D: begin decode_control.mem_read=1'b1; decode_control.mem_to_reg=2'b01; decode_control.reg_write=has_rd; end
			SC_W,SC_D: begin decode_control.mem_write=1'b1; decode_control.mem_to_reg=2'b01; decode_control.reg_write=has_rd; end
			AMO_W,AMO_D: begin decode_control.mem_read=1'b1; decode_control.mem_write=1'b1; decode_control.amo=1'b1; decode_control.mem_to_reg=2'b01; decode_control.reg_write=has_rd; end
			CSRRW,CSRRS,CSRRC,CSRRWI,CSRRSI,CSRRCI: decode_control.reg_write=has_rd;
			default: begin end
		endcase
	end

	// EX/MEM can only forward ALU results; memory, atomic and ecall results are
	// not known until MEM/WB (the hazard logic below stalls for those).
	wire ex_mem_fwd = ex_mem.valid && ex_mem.control.reg_write && ex_mem.rd != 0 &&
		ex_mem.control.mem_to_reg == 2'b00;
	wire mem_wb_fwd = mem_wb.valid && write_enable && mem_wb.rd != 0;

	// The younger EX/MEM result takes priority over MEM/WB.
	always_comb begin
		id_regA = regA_value;
		id_regB = regB_value;
		if (mem_wb_fwd && mem_wb.rd == rs1) id_regA = write_data;
		if (mem_wb_fwd && mem_wb.rd == rs2) id_regB = write_data;
		if (ex_mem_fwd && ex_mem.rd == rs1) id_regA = ex_mem.alu_result;
		if (ex_mem_fwd && ex_mem.rd == rs2) id_regB = ex_mem.alu_result;
	end

	logic [63:0] ex_operandA, ex_operandB;
	always_comb begin
		ex_operandA=id_ex.regA; ex_operandB=id_ex.regB;
		if (mem_wb_fwd && mem_wb.rd == id_ex.rs1) ex_operandA=write_data;
		if (mem_wb_fwd && mem_wb.rd == id_ex.rs2) ex_operandB=write_data;
		if (ex_mem_fwd && ex_mem.rd == id_ex.rs1) ex_operandA=ex_mem.alu_result;
		if (ex_mem_fwd && ex_mem.rd == id_ex.rs2) ex_operandB=ex_mem.alu_result;
	end

	logic [63:0] alu_a, alu_b;
	alu execute_alu (.result(alu_raw_result), .a(alu_a), .b(alu_b), .codeword(id_ex.codeword));
	always_comb begin
		alu_a=ex_operandA; alu_b=id_ex.control.alu_src?id_ex.immediate:ex_operandB;
		if (id_ex.codeword==AUIPC) begin alu_a=id_ex.pc; alu_b=id_ex.immediate; end
	end

	always_comb begin
		execute_alu_result = alu_raw_result;
		execute_target=id_ex.pc_plus_1+id_ex.immediate;
		redirect=1'b0;
		redirect_pc='0;
		if (id_ex.valid) begin
			case (id_ex.codeword)
				JAL: begin execute_target=id_ex.pc+id_ex.immediate; redirect=1'b1; redirect_pc=execute_target; execute_alu_result=id_ex.pc_plus_1; end
				JALR: begin execute_target=(ex_operandA+id_ex.immediate)&~64'b1; redirect=1'b1; redirect_pc=execute_target; execute_alu_result=id_ex.pc_plus_1; end
				AUIPC: execute_alu_result=id_ex.pc+id_ex.immediate;
				// No privileged state: cycle/time/instret read a cycle counter, other CSRs read 0.
				CSRRW,CSRRS,CSRRC,CSRRWI,CSRRSI,CSRRCI:
					case (id_ex.instr[31:20])
						12'hC00, 12'hC01, 12'hC02: execute_alu_result=cycle_count;
						default: execute_alu_result=64'b0;
					endcase
				BEQ: if (ex_operandA==ex_operandB) begin redirect=1'b1; redirect_pc=id_ex.pc+id_ex.immediate; end
				BNE: if (ex_operandA!=ex_operandB) begin redirect=1'b1; redirect_pc=id_ex.pc+id_ex.immediate; end
				BLT: if ($signed(ex_operandA)<$signed(ex_operandB)) begin redirect=1'b1; redirect_pc=id_ex.pc+id_ex.immediate; end
				BGE: if ($signed(ex_operandA)>= $signed(ex_operandB)) begin redirect=1'b1; redirect_pc=id_ex.pc+id_ex.immediate; end
				BLTU: if (ex_operandA<ex_operandB) begin redirect=1'b1; redirect_pc=id_ex.pc+id_ex.immediate; end
				BGEU: if (ex_operandA>=ex_operandB) begin redirect=1'b1; redirect_pc=id_ex.pc+id_ex.immediate; end
				default: begin end
			endcase
		end
	end

	// Dependences on a load in ID/EX are caught one stage later by ex_dep.
	assign load_use_stall = 1'b0;
	assign d_read_ready = d_cpu_resp_valid;
	assign d_write_ready = d_cpu_resp_valid;

	// EX/MEM holds a result EX cannot forward (load, atomic, ecall) that ID/EX
	// needs: retire it into MEM/WB first, then forward from there.
	wire ex_dep = ex_mem.valid && ex_mem.control.reg_write && (ex_mem.rd != 5'd0) &&
		(ex_mem.control.mem_to_reg != 2'b00) && id_ex.valid &&
		((ex_mem.rd == id_ex.rs1) || (ex_mem.rd == id_ex.rs2));

	assign pipeline_stall = d_mem_busy || ex_dep;

	// Do not redirect-flush while EX/MEM is still busy or the branch's operands are not ready.
	wire take_redirect = redirect && !d_mem_busy && !ex_dep;

	// On a split access the second response completes the load: split_lo holds the first beat.
	wire [127:0] load_raw = split_phase ? {d_cpu_resp_rdata, split_lo} : {64'b0, d_cpu_resp_rdata};
	wire [127:0] load_shifted = load_raw >> {mem_off, 3'b000};
	always_comb begin
		d_load_data='0;
		if (ex_mem.valid) begin
			case (ex_mem.codeword)
				LB: d_load_data={{56{load_shifted[7]}},load_shifted[7:0]};
				LH: d_load_data={{48{load_shifted[15]}},load_shifted[15:0]};
				LW, LR_W: d_load_data={{32{load_shifted[31]}},load_shifted[31:0]};
				LBU: d_load_data={56'b0,load_shifted[7:0]};
				LHU: d_load_data={48'b0,load_shifted[15:0]};
				LWU: d_load_data={32'b0,load_shifted[31:0]};
				LD, LR_D: d_load_data=load_shifted[63:0];
				SC_W, SC_D: d_load_data={63'b0, sc_fail};
				AMO_W, AMO_D: d_load_data=amo_old_val;
				default: d_load_data=d_cpu_resp_rdata;
			endcase
		end
	end

	always_ff @(posedge clk) begin
		if (reset) begin
			pc <= entry;
			if_req_pc <= entry;
			fetch_pc <= entry;
			fetch_instr <= '0;
			fetch_valid <= 1'b0;
			i_pending <= 1'b0;
			i_pending_pc <= entry;
			i_cancel_resp <= 1'b0;
			d_pending <= 1'b0;
			amo_phase <= 1'b0;
			amo_old <= '0;
			split_phase <= 1'b0;
			split_lo <= '0;
			resv_valid <= 1'b0;
			resv_addr <= '0;
			ecall_guard <= '0;
			if_id <= '0; id_ex <= '0; ex_mem <= '0; mem_wb <= '0;
		end else begin
			if (take_redirect) begin
				pc <= redirect_pc;
				if_req_pc <= redirect_pc;
				fetch_valid <= 1'b0;
				i_pending <= 1'b0;
				i_cancel_resp <= 1'b1;
				if_id <= '0;
				id_ex <= '0;
				// Older EX/MEM instruction retires (with real load data, not a struct cast).
				mem_wb.valid <= ex_mem.valid;
				mem_wb.instr <= ex_mem.instr;
				mem_wb.pc <= ex_mem.pc;
				mem_wb.pc_plus_1 <= ex_mem.pc_plus_1;
				mem_wb.alu_result <= ex_mem.alu_result;
				mem_wb.pc_plus_1_plus_offset <= ex_mem.pc_plus_1_plus_offset;
				mem_wb.loaded_data <= d_load_data;
				mem_wb.rd <= ex_mem.rd;
				mem_wb.codeword <= ex_mem.codeword;
				mem_wb.control <= ex_mem.control;
				// Branch/jump occupies EX/MEM after the flush.
				ex_mem.valid <= id_ex.valid;
				ex_mem.instr <= id_ex.instr;
				ex_mem.pc <= id_ex.pc;
				ex_mem.pc_plus_1 <= id_ex.pc_plus_1;
				ex_mem.alu_result <= execute_alu_result;
				ex_mem.pc_plus_1_plus_offset <= execute_target;
				ex_mem.regB <= ex_operandB;
				ex_mem.rd <= id_ex.rd;
				ex_mem.codeword <= id_ex.codeword;
				ex_mem.control <= id_ex.control;
			end else begin
				if (i_cpu_req_valid && i_cpu_req_ready) begin
					i_pending <= 1'b1;
					i_pending_pc <= if_req_pc;
				end
				if (i_cpu_resp_valid && i_pending && !i_cancel_resp) begin
					i_pending <= 1'b0;
					fetch_pc <= i_pending_pc;
					fetch_instr <= i_pending_pc[2] ?
						i_cpu_resp_rdata[63:32] :
						i_cpu_resp_rdata[31:0];
					fetch_valid <= 1'b1;
				end else if (i_cancel_resp && i_cpu_resp_valid) begin
					i_pending <= 1'b0;
					i_cancel_resp <= 1'b0;
				end else if (i_cancel_resp && !i_pending) begin
					// Redirect cancelled before a response was outstanding.
					i_cancel_resp <= 1'b0;
				end

				if (!pipeline_stall) begin
					if (fetch_valid) begin
						if_id.valid <= 1'b1;
						if_id.instr <= fetch_instr;
						if_id.pc <= fetch_pc;
						if_id.pc_plus_1 <= fetch_pc + 64'd4;
						pc <= fetch_pc + 64'd4;
						if_req_pc <= fetch_pc + 64'd4;
						fetch_valid <= 1'b0;
					end else begin
						if_id <= '0;
					end

					id_ex.valid <= if_id.valid;
					id_ex.instr <= if_id.instr;
					id_ex.pc <= if_id.pc;
					id_ex.pc_plus_1 <= if_id.pc_plus_1;
					id_ex.regA <= id_regA;
					id_ex.regB <= id_regB;
					id_ex.immediate <= immediate;
					id_ex.rd <= rd;
					id_ex.rs1 <= rs1;
					id_ex.rs2 <= rs2;
					id_ex.codeword <= id_codeword;
					id_ex.control <= decode_control;

					ex_mem.valid <= id_ex.valid;
					ex_mem.instr <= id_ex.instr;
					ex_mem.pc <= id_ex.pc;
					ex_mem.pc_plus_1 <= id_ex.pc_plus_1;
					ex_mem.alu_result <= execute_alu_result;
					ex_mem.pc_plus_1_plus_offset <= execute_target;
					ex_mem.regB <= ex_operandB;
					ex_mem.rd <= id_ex.rd;
					ex_mem.codeword <= id_ex.codeword;
					ex_mem.control <= id_ex.control;

					mem_wb.valid <= ex_mem.valid;
					mem_wb.instr <= ex_mem.instr;
					mem_wb.pc <= ex_mem.pc;
					mem_wb.pc_plus_1 <= ex_mem.pc_plus_1;
					mem_wb.alu_result <= ex_mem.alu_result;
					mem_wb.pc_plus_1_plus_offset <= ex_mem.pc_plus_1_plus_offset;
					mem_wb.loaded_data <= d_load_data;
					mem_wb.rd <= ex_mem.rd;
					mem_wb.codeword <= ex_mem.codeword;
					mem_wb.control <= ex_mem.control;
				end else if (!d_mem_busy) begin
					// ex_dep: retire EX/MEM into MEM/WB, bubble EX/MEM, hold ID/EX and IF/ID
					// so the dependent instruction forwards from MEM/WB next cycle.
					mem_wb.valid <= ex_mem.valid;
					mem_wb.instr <= ex_mem.instr;
					mem_wb.pc <= ex_mem.pc;
					mem_wb.pc_plus_1 <= ex_mem.pc_plus_1;
					mem_wb.alu_result <= ex_mem.alu_result;
					mem_wb.pc_plus_1_plus_offset <= ex_mem.pc_plus_1_plus_offset;
					mem_wb.loaded_data <= d_load_data;
					mem_wb.rd <= ex_mem.rd;
					mem_wb.codeword <= ex_mem.codeword;
					mem_wb.control <= ex_mem.control;
					ex_mem <= '0;
					id_ex.regA <= ex_operandA;
					id_ex.regB <= ex_operandB;
				end else begin
					// D-cache still busy: hold IF/ID, ID/EX and EX/MEM; WB has retired.
					mem_wb <= '0;
					// Capture values forwarded from WB now, since WB empties.
					id_ex.regA <= ex_operandA;
					id_ex.regB <= ex_operandB;
				end
			end

			if (d_cpu_req_valid && d_cpu_req_ready) d_pending <= 1'b1;
			if (d_cpu_resp_valid) d_pending <= 1'b0;

			if (mem_is_amo && d_cpu_resp_valid && !amo_phase) begin
				amo_old <= d_cpu_resp_rdata;
				amo_phase <= 1'b1;
			end else if (mem_is_amo && d_mem_done) begin
				amo_phase <= 1'b0;
			end

			if (mem_cross && d_cpu_resp_valid && !split_phase) begin
				split_lo <= d_cpu_resp_rdata;
				split_phase <= 1'b1;
			end else if (mem_cross && d_mem_done) begin
				split_phase <= 1'b0;
			end

			if (mem_is_lr && d_mem_done) begin
				resv_valid <= 1'b1;
				resv_addr <= ex_mem.alu_result;
			end else if (mem_is_sc && !d_mem_busy) begin
				resv_valid <= 1'b0;
			end

			if (ex_mem.valid && ex_mem.codeword == ECALL)
				ecall_guard <= 2'd3;
			else if (ecall_guard != 2'd0)
				ecall_guard <= ecall_guard - 2'd1;
		end
	end

	// Issue at most one I-fetch at a time, and never while a fetched insn is
	// waiting to enter IF/ID or a redirect cancel is in progress. This keeps
	// if_req_pc (starting at entry) aligned with the instruction stream.
	assign i_cpu_req_valid = !reset && !i_pending && !fetch_valid && !i_cancel_resp;

	// Shared AXI read/write arbiter
	typedef enum logic [2:0] {AR_IDLE, AR_D, AR_I, AR_DATA} ar_state_t;
	ar_state_t ar_state;
	logic ar_is_d;
	logic [63:0] ar_addr;
	logic [2:0] aw_wbeat;
	logic [63:0] aw_addr;

	typedef enum logic [2:0] {AW_IDLE, AW_ADDR, AW_DATA, AW_RESP} aw_state_t;
	aw_state_t aw_state;

	always_comb begin
		// Course memory model: 8-beat WRAP reads of 64-byte lines.
		m_axi_arid='0; m_axi_araddr='0; m_axi_arlen=8'd7;
		m_axi_arsize=3'b011; m_axi_arburst=2'b10; m_axi_arlock=1'b0;
		m_axi_arcache='0; m_axi_arprot='0; m_axi_arvalid=1'b0;
		m_axi_rready=1'b0;
		i_mem_read_valid=1'b0; i_mem_read_data='0;
		d_mem_read_valid=1'b0; d_mem_read_data='0;
		case (ar_state)
			AR_D: begin m_axi_arvalid=1'b1; m_axi_araddr=ar_addr; end
			AR_I: begin m_axi_arvalid=1'b1; m_axi_araddr=ar_addr; end
			AR_DATA: begin
				m_axi_rready=1'b1;
				if (m_axi_rvalid) begin
					if (ar_is_d) begin d_mem_read_valid=1'b1; d_mem_read_data=m_axi_rdata; end
					else begin i_mem_read_valid=1'b1; i_mem_read_data=m_axi_rdata; end
				end
			end
			default: begin end
		endcase
	end

	always_ff @(posedge clk or posedge reset) begin
		if (reset) begin ar_state<=AR_IDLE; ar_is_d<=1'b0; ar_addr<=0;
		end else begin
			case (ar_state)
				AR_IDLE: begin
					if (d_mem_read_req) begin ar_is_d<=1'b1; ar_addr<=d_mem_read_addr & ~64'h3f; ar_state<=AR_D; end
					else if (i_mem_read_req) begin ar_is_d<=1'b0; ar_addr<=i_mem_read_addr & ~64'h3f; ar_state<=AR_I; end
				end
				AR_D: if (m_axi_arvalid && m_axi_arready) ar_state<=AR_DATA;
				AR_I: if (m_axi_arvalid && m_axi_arready) ar_state<=AR_DATA;
				AR_DATA: if (m_axi_rvalid && m_axi_rready && m_axi_rlast) ar_state<=AR_IDLE;
				default: ar_state<=AR_IDLE;
			endcase
		end
	end

	always_comb begin
		// Course memory model: 8-beat INCR writes of 64-byte lines.
		m_axi_awid='0; m_axi_awaddr='0; m_axi_awlen=8'd7; m_axi_awsize=3'b011;
		m_axi_awburst=2'b01; m_axi_awlock=1'b0; m_axi_awcache='0; m_axi_awprot='0;
		m_axi_awvalid=1'b0; m_axi_wdata='0; m_axi_wstrb='0; m_axi_wlast=1'b0; m_axi_wvalid=1'b0;
		m_axi_bready=1'b0; d_mem_write_ready=1'b0;
		case (aw_state)
			AW_ADDR: begin m_axi_awvalid=1'b1; m_axi_awaddr=aw_addr; end
			AW_DATA: begin
				m_axi_wvalid=d_mem_write_req;
				m_axi_wdata=d_mem_write_data;
				m_axi_wstrb=d_mem_write_strb;
				m_axi_wlast=(aw_wbeat==3'd7);
				if (m_axi_wvalid && m_axi_wready) d_mem_write_ready=1'b1;
			end
			AW_RESP: m_axi_bready=1'b1;
			default: begin end
		endcase
	end

	always_ff @(posedge clk or posedge reset) begin
		if (reset) begin aw_state<=AW_IDLE; aw_wbeat<=0; aw_addr<=0;
		end else begin
			case (aw_state)
				AW_IDLE: if (d_mem_write_req) begin aw_addr<=d_mem_write_addr & ~64'h3f; aw_state<=AW_ADDR; end
				AW_ADDR: if (m_axi_awvalid && m_axi_awready) begin aw_wbeat<=0; aw_state<=AW_DATA; end
				AW_DATA: if (m_axi_wvalid && m_axi_wready) begin
					if (aw_wbeat==3'd7) aw_state<=AW_RESP; else aw_wbeat<=aw_wbeat+1'b1;
				end
				AW_RESP: if (m_axi_bvalid) aw_state<=AW_IDLE;
				default: aw_state<=AW_IDLE;
			endcase
		end
	end

	assign m_axi_acready = 1'b1;

	// Commit and DPI calls
	assign write_enable = mem_wb.valid && mem_wb.control.reg_write && mem_wb.rd != 5'd0;
	always_comb begin
		write_data=mem_wb.alu_result;
		case (mem_wb.control.mem_to_reg)
			2'b01: write_data=mem_wb.loaded_data;
			2'b10: write_data=ecall_ret;
			default: begin end
		endcase
	end

	// a0-a7 as seen by the ecall in EX/MEM: the instruction in MEM/WB has not
	// written the register file yet.
	logic [63:0] ecall_args [0:7];
	always_comb begin
		for (int i = 0; i < 8; i = i + 1)
			ecall_args[i] = (mem_wb_fwd && mem_wb.rd == 5'(10 + i)) ? write_data : syscall_args[i];
	end

	always_ff @(posedge clk) begin
		if (!reset && ex_mem.valid && ex_mem.codeword==ECALL) begin
			do_ecall(ecall_args[7],ecall_args[0],ecall_args[1],ecall_args[2],ecall_args[3],ecall_args[4],ecall_args[5],ecall_args[6],ecall_ret);
		end
		// Report every store the D-cache accepts; the testbench calls
		// do_finish_write itself when the line reaches DRAM.
		if (!reset && d_cpu_req_valid && d_cpu_req_ready && d_cpu_req_write && !split_phase)
			do_pending_write(ex_mem.alu_result, st_value, st_size);
	end

	// End simulation after falling into a run of all-zero words (treated as NOPs),
	// or once every in-flight pipeline stage is a zero instruction.
	assign pipeline_all_zero =
		fetch_valid && (fetch_instr == 32'b0) &&
		if_id.valid && (if_id.instr == 32'b0) &&
		id_ex.valid && (id_ex.instr == 32'b0) &&
		ex_mem.valid && (ex_mem.instr == 32'b0) &&
		mem_wb.valid && (mem_wb.instr == 32'b0);

	always_ff @(posedge clk) begin
		if (reset || take_redirect) begin
			zero_instr_count <= '0;
		end else begin
			if (!pipeline_stall && fetch_valid) begin
				if (fetch_instr == 32'b0)
					zero_instr_count <= zero_instr_count + 3'd1;
				else
					zero_instr_count <= '0;
			end

			// Finish on the 5th consecutive accepted zero, or when every stage is zero.
			if (pipeline_all_zero ||
			    (zero_instr_count >= 3'd4 && !pipeline_stall && fetch_valid && fetch_instr == 32'b0)) begin
				for (int reg_index = 0; reg_index < 32; reg_index = reg_index + 1)
					$display("Register %0d: %016x", reg_index, registers.read_reg(5'(reg_index)));
				$finish;
			end
		end
	end

	initial begin
		$display("Initializing top, entry point = 0x%x",entry);
	end
endmodule
