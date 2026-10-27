`include "Sysbus.defs"

module decoder (
	output string       codeword,
	output logic [4:0] rd,
	output logic       has_rd,
	input  logic [31:0] instr
);
	logic [6:0] opcode;
	logic [2:0] funct3;
	logic [6:0] funct7;

	typedef enum logic [4:0] { // Only the 5 MSB matter to determine opcode type in a 32bit ISA (ref table: p603 Chp 36)
		LOAD = 5'b00_000,
		LOAD_FP = 5'b00_001,
		MISC_MEM = 5'b00_011,
		OP_IMM = 5'b00_100,
		AUIPC = 5'b00_101,
		OP_IMM_32 = 5'b00_110,
		
		STORE = 5'b01_000,
		STORE_FP = 5'b01_001,
		AMO = 5'b01_011,
		OP = 5'b01_100,
		LUI = 5'b01_101,
		OP_32 = 5'b01_110,

		MADD = 5'b10_000,
		MSUB = 5'b10_001,
		NMSUB = 5'b10_010,
		NMADD = 5'b10_011,
		OP_FP = 5'b10_100,
		OP_V = 5'b10_101,
		
		BRANCH = 5'b11_000,
		JALR = 5'b11_001,
		JAL = 5'b11_011,
		SYSTEM = 5'b11_100,
		OP_VE = 5'b11_101
		
	} opcode_t;

	always_comb begin
		opcode = instr[6:0];
		rd = instr[11:7];
		funct3 = instr[14:12];
		funct7 = instr[31:25];

		has_rd = 1'b0;
		codeword = "unknown";

		case (opcode[6:2])
			// add all the cases for each opcode filling in what
			// codeword, and whether it has rd
			// RV32I
			LUI: begin codeword = "LUI"; has_rd = 1'b1; end
			AUIPC: begin codeword = "AUIPC"; has_rd = 1'b1; end
			JAL: begin codeword = "JAL"; has_rd = 1'b1; end
			JALR: begin
				if (funct3 == 3'b000) begin
					codeword = "JALR";
					has_rd = 1'b1;
				end else begin
					codeword = "unknown";
					has_rd = 1'b0;
				end
			end
			BRANCH: begin
				has_rd = 1'b0;
				case (funct3)
					3'b000: codeword = "BEQ";
					3'b001: codeword = "BNE";
					3'b100: codeword = "BLT";
					3'b101: codeword = "BGE";
					3'b110: codeword = "BLTU";
					3'b111: codeword = "BGEU";
					default: codeword = "unknown";
				endcase
			end
			LOAD: begin
				has_rd = 1'b1;
				case (funct3)
					3'b000: codeword = "LB";
					3'b001: codeword = "LH";
					3'b010: codeword = "LW";
					3'b100: codeword = "LBU";
					3'b101: codeword = "LHU";
					// RV64I
					3'b110: codeword = "LWU";
					3'b011: codeword = "LD";
					default: begin codeword = "unknown"; has_rd = 1'b0; end
				endcase
			end
			STORE: begin
				has_rd = 1'b0;
				case (funct3)
					3'b000: codeword = "SB";
					3'b001: codeword = "SH";
					3'b010: codeword = "SW";
					// RV64I
					3'b011: codeword = "SD";
					default: codeword = "unknown";
				endcase
			end
			OP_IMM: begin
				has_rd = 1'b1;
				case (funct3)
					// RV32I
					3'b000: codeword = "ADDI";
					3'b010: codeword = "SLTI";
					3'b011: codeword = "SLTIU";
					3'b100: codeword = "XORI";
					3'b110: codeword = "ORI";
					3'b111: codeword = "ANDI";
					// RV32I / RV64I
					3'b001: begin
						case (funct7[6:1])
							6'b000000: codeword = "SLLI";
							default: begin codeword = "unknown"; has_rd = 1'b0; end
						endcase
					end
					3'b101: begin
						case (funct7[6:1])
							6'b000000: codeword = "SRLI";
							6'b010000: codeword = "SRAI";
							default: begin codeword = "unknown"; has_rd = 1'b0; end
						endcase
					end
					default: begin codeword = "unknown"; has_rd = 1'b0; end
				endcase
			end
			OP: begin
				has_rd = 1'b1;
				// RV32I
				if (funct7 != 7'b0000001) begin
					case (funct3)
						3'b000: begin
							case (funct7)
								7'b0000000: codeword = "ADD";
								7'b0100000: codeword = "SUB";
								default: begin codeword = "unknown"; has_rd = 1'b0; end
							endcase
						end
						
						3'b001: if (funct7 == 7'b0000000) codeword = "SLL"; else begin codeword = "unknown"; has_rd = 1'b0; end
						3'b010: if (funct7 == 7'b0000000) codeword = "SLT"; else begin codeword = "unknown"; has_rd = 1'b0; end
						3'b011: if (funct7 == 7'b0000000) codeword = "SLTU"; else begin codeword = "unknown"; has_rd = 1'b0; end
						3'b100: if (funct7 == 7'b0000000) codeword = "XOR"; else begin codeword = "unknown"; has_rd = 1'b0; end
						3'b110: if (funct7 == 7'b0000000) codeword = "OR"; else begin codeword = "unknown"; has_rd = 1'b0; end
						3'b111: if (funct7 == 7'b0000000) codeword = "AND"; else begin codeword = "unknown"; has_rd = 1'b0; end
						
						3'b101: begin
							case (funct7)
								7'b0000000: codeword = "SRL";
								7'b0100000: codeword = "SRA";
								default: begin codeword = "unknown"; has_rd = 1'b0; end
							endcase
						end
						default: begin codeword = "unknown"; has_rd = 1'b0; end
					endcase
				end else begin
					// RV32M
					case (funct3)
						3'b000: codeword = "MUL";
						3'b001: codeword = "MULH";
						3'b010: codeword = "MULHSU";
						3'b011: codeword = "MULHU";
						3'b100: codeword = "DIV";
						3'b101: codeword = "DIVU";
						3'b110: codeword = "REM";
						3'b111: codeword = "REMU";
						default: begin codeword = "unknown"; has_rd = 1'b0; end
					endcase
				end
			end

			OP_IMM_32: begin
				has_rd = 1'b1;
				// RV64I
				case (funct3)
					3'b000: codeword = "ADDIW";
					3'b001: begin
						case (funct7)
							7'b0000000: codeword = "SLLIW";
							default: begin codeword = "unknown"; has_rd = 1'b0; end
						endcase
					end
					3'b101: begin
						case (funct7)
							7'b0000000: codeword = "SRLIW";
							7'b0100000: codeword = "SRAIW";
							default: begin codeword = "unknown"; has_rd = 1'b0; end
						endcase
					end
					default: begin codeword = "unknown"; has_rd = 1'b0; end
				endcase
			end
			OP_32: begin
				has_rd = 1'b1;
				// RV64I
				if (funct7 != 7'b0000001) begin
					case (funct3)
						3'b000: begin
							case (funct7)
								7'b0000000: codeword = "ADDW";
								7'b0100000: codeword = "SUBW";
								default: begin codeword = "unknown"; has_rd = 1'b0; end
							endcase
						end
						
						3'b001: begin
							if (funct7 == 7'b0000000) codeword = "SLLW"; else begin codeword = "unknown"; has_rd = 1'b0; end
						end
						3'b101: begin
							case (funct7)
								7'b0000000: codeword = "SRLW";
								7'b0100000: codeword = "SRAW";
								default: begin codeword = "unknown"; has_rd = 1'b0; end
							endcase
						end
						default: begin codeword = "unknown"; has_rd = 1'b0; end
					endcase
				end else begin
					// RV64M
					case (funct3)
						3'b000: codeword = "MULW";
						3'b100: codeword = "DIVW";
						3'b101: codeword = "DIVUW";
						3'b110: codeword = "REMW";
						3'b111: codeword = "REMUW";
						default: begin codeword = "unknown"; has_rd = 1'b0; end
					endcase
				end
			end
			MISC_MEM: begin
				has_rd = 1'b0;
				case (funct3)
					// RV32I
					3'b000: codeword = "FENCE";
					// RV32/64 Zifencei
					3'b001: codeword = "FENCE.I";
					default: codeword = "unknown";
				endcase
			end
			SYSTEM: begin
				// RV32I
				if (instr == 32'b000000000000_00000_000_00000_1110011) begin
					codeword = "ECALL";
					has_rd = 1'b0;
				end else if (instr == 32'b000000000001_00000_000_00000_1110011) begin
					codeword = "EBREAK";
					has_rd = 1'b0;
				end else begin
					// RV32/64 Zicsr
					has_rd = 1'b1;
					case (funct3)
						3'b001: codeword = "CSRRW";
						3'b010: codeword = "CSRRS";
						3'b011: codeword = "CSRRC";
						3'b101: codeword = "CSRRWI";
						3'b110: codeword = "CSRRSI";
						3'b111: codeword = "CSRRCI";
						default: begin codeword = "unknown"; has_rd = 1'b0; end
					endcase
				end
			end
			default: begin codeword = "unknown"; has_rd = 0; end
		endcase
	end
endmodule

module regfile (
	output logic [63:0] rs1_data, rs2_data,
	input logic clk,
	input logic [4:0] rs1, rs2, rd,
	input logic [63:0] wdata,
	input logic write_enable
);
	logic [63:0] regs [31:0];

	assign rs1_data = (rs1 == 5'd0) ? 64'd0 : regs[rs1];
	assign rs2_data = (rs2 == 5'd0) ? 64'd0 : regs[rs2];

	always_ff @(posedge clk) begin
		if (write_enable && rd != 5'd0)
			regs[rd] <= wdata;
	end

	// for the dump at the end
	function automatic logic [63:0] read_reg(input logic[4:0] idx);
		return (idx == 5'd0) ? 64'd0 : regs[idx];
	endfunction
endmodule

typedef enum logic [4:0] {
	ALU_ADD, ALU_SUB, ALU_SLL, ALU_SLT, ALU_SLTU, ALU_XOR, ALU_SRL, ALU_SRA, ALU_OR, ALU_AND, ALU_ADDW, ALU_SUBW, ALU_SLLW, ALU_SRLW,
	ALU_SRAW, ALU_MUL, ALU_MULH, ALU_MULHSU, ALU_MULHU, ALU_DIV, ALU_DIVU, ALU_REM, ALU_REMU, ALU_LUI, ALU_AUIPC, ALU_NONE
	} alu_op_t;

module alu (
	output logic [63:0] result,
	input logic [63:0] a, b,
	input alu_op_t op
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

		case (op)
			ALU_ADD:   result = a + b;
			ALU_SUB:   result = a - b;
			ALU_SLL:   result = a << b[5:0];
			ALU_SLT:   result = ($signed(a) < $signed(b)) ? 64'd1 : 64'd0;
			ALU_SLTU:  result = (a < b) ? 64'd1 : 64'd0;
			ALU_XOR:   result = a ^ b;
			ALU_SRL:   result = a >> b[5:0];
			ALU_SRA:   result = $signed(a) >>> b[5:0];
			ALU_OR:    result = a | b;
			ALU_AND:   result = a & b;
			ALU_ADDW: begin
				word_result = a[31:0] + b[31:0];
				result = {{32{word_result[31]}}, word_result};
			end
			ALU_SUBW: begin
				word_result = a[31:0] - b[31:0];
				result = {{32{word_result[31]}}, word_result};
			end
			ALU_SLLW: begin
				word_result = a[31:0] << b[4:0];
				result = {{32{word_result[31]}}, word_result};
			end
			ALU_SRLW: begin
				word_result = a[31:0] >> b[4:0];
				result = {{32{word_result[31]}}, word_result};
			end
			ALU_SRAW: begin
				word_result = $signed(a[31:0]) >>> b[4:0];
				result = {{32{word_result[31]}}, word_result};
			end
			ALU_MUL:    result = a * b;
			ALU_MULH:   result = signed_product[127:64];
			ALU_MULHSU: result = signed_unsigned_product[127:64];
			ALU_MULHU:  result = unsigned_product[127:64];
			ALU_DIV: begin
				if (b == 64'b0)
					result = 64'hffff_ffff_ffff_ffff;
				else if ((a == 64'h8000_0000_0000_0000) && (b == 64'hffff_ffff_ffff_ffff))
					result = a;
				else
					result = $signed(a) / $signed(b);
			end
			ALU_DIVU:  result = (b == 64'b0) ? 64'hffff_ffff_ffff_ffff : a / b;
			ALU_REM: begin
				if (b == 64'b0)
					result = a;
				else if ((a == 64'h8000_0000_0000_0000) && (b == 64'hffff_ffff_ffff_ffff))
					result = 64'b0;
				else
					result = $signed(a) % $signed(b);
			end
			ALU_REMU:  result = (b == 64'b0) ? a : a % b;
			ALU_LUI:   result = b;
			ALU_AUIPC: result = a + b;
			default:   result = 64'b0;
		endcase
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
  input  clk,
         reset,
         hz32768timer,

  // 64-bit addresses of the program entry point and initial stack pointer
  input  [63:0] entry,
  input  [63:0] stackptr,
  input  [63:0] satp,

  // interface to connect to the bus
  output  wire [ID_WIDTH-1:0]    m_axi_awid,
  output  wire [ADDR_WIDTH-1:0]  m_axi_awaddr,
  output  wire [7:0]             m_axi_awlen,
  output  wire [2:0]             m_axi_awsize,
  output  wire [1:0]             m_axi_awburst,
  output  wire                   m_axi_awlock,
  output  wire [3:0]             m_axi_awcache,
  output  wire [2:0]             m_axi_awprot,
  output  wire                   m_axi_awvalid,
  input   wire                   m_axi_awready,
  output  wire [DATA_WIDTH-1:0]  m_axi_wdata,
  output  wire [STRB_WIDTH-1:0]  m_axi_wstrb,
  output  wire                   m_axi_wlast,
  output  wire                   m_axi_wvalid,
  input   wire                   m_axi_wready,
  input   wire [ID_WIDTH-1:0]    m_axi_bid,
  input   wire [1:0]             m_axi_bresp,
  input   wire                   m_axi_bvalid,
  output  wire                   m_axi_bready,
  output  wire [ID_WIDTH-1:0]    m_axi_arid,
  output  wire [ADDR_WIDTH-1:0]  m_axi_araddr,
  output  wire [7:0]             m_axi_arlen,
  output  wire [2:0]             m_axi_arsize,
  output  wire [1:0]             m_axi_arburst,
  output  wire                   m_axi_arlock,
  output  wire [3:0]             m_axi_arcache,
  output  wire [2:0]             m_axi_arprot,
  output  wire                   m_axi_arvalid,
  input   wire                   m_axi_arready,
  input   wire [ID_WIDTH-1:0]    m_axi_rid,
  input   wire [DATA_WIDTH-1:0]  m_axi_rdata,
  input   wire [1:0]             m_axi_rresp,
  input   wire                   m_axi_rlast,
  input   wire                   m_axi_rvalid,
  output  wire                   m_axi_rready,
  input   wire                   m_axi_acvalid,
  output  wire                   m_axi_acready,
  input   wire [ADDR_WIDTH-1:0]  m_axi_acaddr,
  input   wire [3:0]             m_axi_acsnoop
);

  logic [63:0] pc;
  logic [63:0] next_pc;
  logic [511:0] fetched_line; // 8 * 64 bits = 512 bits
  logic [2:0] beat_count; // counter up to 8 beats 
  logic [31:0] instr;

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

  string codeword;
  logic [4:0] rd;
  logic has_rd;

  assign instr = fetched_line[(pc[5:2] * 32) +: 32]; // 32 bits of instruction from the fetched line based on pc[5:2] (which selects 1 of the 16 instructions within the 512-bit line) (pc[1:0] is ignored since instructions are 4-byte aligned pc += 4)

  logic [63:0] rs1_data, rs2_data, alu_b, alu_result;
  logic        reg_wen;

  decoder decode (
	  .instr (instr),
	  .codeword (codeword),
	  .rd (rd),
	  .has_rd (has_rd)
  );
  regfile rf (
  	.clk(clk), .rs1(rs1), .rs2(rs2), .rd(rd),
  	.wdata(alu_result), .wen(reg_wen),
  	.rs1_data(rs1_data), .rs2_data(rs2_data)
  );

  assign alu_b = (alu_op == ALU_AUIPC) ? pc :
               use_imm               ? imm :
                                        rs2_data;

  alu alu_inst (
	  .a((alu_op == ALU_AUIPC) ? pc : rs1_data),
	  .b(alu_b)

  always_comb begin
    next_pc = pc + 4;
  end

  always_ff @ (posedge clk) begin
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
		if (instr == 32'b0)
			$finish;
		if (has_rd)
			$display("%x: %s %0d", pc, codeword, rd);
		else
			$display("%x: %s", pc, codeword);

		pc <= next_pc;
		state <= ARADDR;
	end
	default: state<= ARADDR;
      endcase
    end
  end

  initial begin
    $display("Initializing top, entry point = 0x%x", entry);
  end
endmodule
