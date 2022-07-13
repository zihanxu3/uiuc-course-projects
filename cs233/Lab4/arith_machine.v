// arith_machine: execute a series of arithmetic instructions from an instruction cache
//
// except (output) - set to 1 when an unrecognized instruction is to be executed.
// clock  (input)  - the clock signal
// reset  (input)  - set to 1 to set all registers to zero, set to 0 for normal execution.

module arith_machine(except, clock, reset);
    output      except;
    input       clock, reset;

    wire [31:0] inst;  
    wire [31:0] PC;
    wire [31:0] d;


    // DO NOT comment out or rename this module
    // or the test bench will break
    register #(32) PC_reg(PC, d, clock, 1'b1, reset);

    // DO NOT comment out or rename this module
    // or the test bench will break
    instruction_memory im(inst, PC[31:2]);

    alu32 malu(d, , , , PC, 32'h4, `ALU_ADD);

    wire [5:0] opcode = inst[31:26];
    wire [5:0] funct = inst[5:0];
    wire [4:0] rsNum = inst[25:21];
    wire [4:0] rtNum = inst[20:16];
    wire [4:0] rdNum = inst[15:11];
    wire [16:0] imm16 = inst[15:0];

    wire rd_src;
    wire writeenable; 
    wire [1:0] alu_src2;
    wire [2:0] alu_op;

    mips_decode dec(rd_src, writeenable, alu_src2, alu_op, except, opcode[5:0], funct[5:0]);

    wire [31:0] rdData;
    wire [4:0] wrNum;

    mux2v #(5) m1(wrNum, rdNum, rtNum, rd_src); 
    wire [31:0] sext = {{16{inst[15]}},imm16};
    wire [31:0] zext = {16'h0000,imm16};
    wire [31:0] A;
    wire [31:0] B;
    wire [31:0] rtData;
    wire [31:0] rsData;

    // DO NOT comment out or rename this module
    // or the test bench will break
    regfile rf(rsData, rtData,
                rsNum, rtNum, wrNum, rdData, 
                writeenable, clock, reset);

    
    mux3v mux3(B, rtData, sext, zext, alu_src2);

    alu32 talu(rdData, , , , rsData, B, alu_op);





    /* add other modules */
   
endmodule // arith_machine
