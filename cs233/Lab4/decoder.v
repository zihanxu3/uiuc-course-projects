// mips_decode: a decoder for_ MIPS arithmetic instructions
//
// rd_src      (output) - should the destination register be rd (0) or_ rt (1)
// writeenable (output) - should a new value be captured by the register file
// alu_src2    (output) - should the 2nd ALU source be a register (0), zero extended immediate or_ sign extended immediate
// alu_op      (output) - control signal to be sent to the ALU
// except      (output) - set to 1 when the opcode/funct combination is unrecognized
// opcode      (input)  - the opcode field from the instruction
// funct       (input)  - the function field from the instruction
//

module mips_decode(rd_src, writeenable, alu_src2, alu_op, except, opcode, funct);
    output       rd_src, writeenable, except;
    output [1:0] alu_src2;
    output [2:0] alu_op;
    input  [5:0] opcode, funct;

    //set the types of op
    wire I_type = (opcode != 0);

    //set the rd_src
    assign rd_src = I_type; 

    //set opcode funct to wires
    wire add =  (funct == `OP0_ADD) & (opcode == `OP_OTHER0);
    wire addu = (funct == `OP0_ADDU) & (opcode == `OP_OTHER0);
    wire sub = (funct == `OP0_SUB) & (opcode == `OP_OTHER0);
    wire and_ = (funct == `OP0_AND) & (opcode == `OP_OTHER0);
    wire or_ = (funct == `OP0_OR) & (opcode == `OP_OTHER0);
    wire nor_ = (funct == `OP0_NOR) & (opcode == `OP_OTHER0);
    wire xor_ = (funct == `OP0_XOR) & (opcode == `OP_OTHER0);

    wire addi = (opcode == `OP_ADDI);
    wire addui = (opcode == `OP_ADDIU);
    wire and_i = (opcode == `OP_ANDI);
    wire or_i = (opcode == `OP_ORI);
    wire xor_i = (opcode == `OP_XORI);

    //assign alu_src2
    assign alu_src2[0] = addi | addui;
    assign alu_src2[1] = and_i | or_i | xor_i;

    //set alu_op
    assign alu_op[0] = sub | or_ | xor_ | or_i | xor_i;
    assign alu_op[1] = add | sub | nor_ | xor_ | addi | xor_i;
    assign alu_op[2] = and_ | or_ | nor_ | xor_ | and_i | or_i | xor_i;

    assign except = !(add | addu | sub | and_ | or_ | nor_ | xor_ | addi | addui | and_i | or_i | xor_i);
    assign writeenable = !except;



 endmodule // mips_decode
