// mips_decode: a decoder for MIPS arithmetic instructions
//
// alu_op       (output) - control signal to be sent to the ALU
// writeenable  (output) - should a new value be captured by the register file
// rd_src       (output) - should the destination register be rd (0) or rt (1)
// alu_src2     (output) - should the 2nd ALU source be a register (0) or an immediate (1)
// except       (output) - set to 1 when we don't recognize an opdcode & funct combination
// control_type (output) - 00 = fallthrough, 01 = branch_target, 10 = jump_target, 11 = jump_register 
// mem_read     (output) - the register value written is coming from the memory
// word_we      (output) - we're writing a word's worth of data
// byte_we      (output) - we're only writing a byte's worth of data
// byte_load    (output) - we're doing a byte load
// slt          (output) - the instruction is an slt
// lui          (output) - the instruction is a lui
// addm         (output) - the instruction is an addm
// opcode        (input) - the opcode field from the instruction
// funct         (input) - the function field from the instruction
// zero          (input) - from the ALU
//

module mips_decode(alu_op, writeenable, rd_src, alu_src2, except, control_type,
                   mem_read, word_we, byte_we, byte_load, slt, lui, addm,
                   opcode, funct, zero);
    output [2:0] alu_op;
    output [1:0] alu_src2;
    output       writeenable, rd_src, except;
    output [1:0] control_type;
    output       mem_read, word_we, byte_we, byte_load, slt, lui, addm;
    input  [5:0] opcode, funct;
    input        zero;

    //set the types of op
    wire I_type = (opcode != 0);


    //set opcode funct to wires
    wire add =  (funct == `OP0_ADD) & (opcode == `OP_OTHER0);
    wire addu = (funct == `OP0_ADDU) & (opcode == `OP_OTHER0);
    wire sub = (funct == `OP0_SUB) & (opcode == `OP_OTHER0);
    wire and_ = (funct == `OP0_AND) & (opcode == `OP_OTHER0);
    wire or_ = (funct == `OP0_OR) & (opcode == `OP_OTHER0);
    wire nor_ = (funct == `OP0_NOR) & (opcode == `OP_OTHER0);
    wire xor_ = (funct == `OP0_XOR) & (opcode == `OP_OTHER0);
    wire jr = (funct == `OP0_JR) & (opcode == `OP_OTHER0);
    wire slt_ = (funct == `OP0_SLT) & (opcode == `OP_OTHER0);
     //addm wire
    wire addm = (funct == `OP0_ADDM) & (opcode ==  `OP_OTHER0); 

    //I type
    wire addi = (opcode == `OP_ADDI);
    wire addui = (opcode == `OP_ADDIU);
    wire and_i = (opcode == `OP_ANDI);
    wire or_i = (opcode == `OP_ORI);
    wire xor_i = (opcode == `OP_XORI);

    wire beq = (opcode == `OP_BEQ);
    wire bne = (opcode == `OP_BNE);
    wire lui_ = (opcode == `OP_LUI);
    wire lw = (opcode == `OP_LW);
    wire lbu = (opcode == `OP_LBU);
    wire sw = (opcode == `OP_SW);
    wire sb = (opcode == `OP_SB);

    //J type
    wire j = (opcode == `OP_J);

    /**
    * MARK: From lab 4 below
    **/
    //assign alu_src2
    assign alu_src2[0] = addi | addui | lw | lbu | sw | sb | addm;
    assign alu_src2[1] = and_i | or_i | xor_i | addm;

    //set alu_op
    assign alu_op[0] = sub | or_ | xor_ | or_i | xor_i | beq | bne | slt_;
    assign alu_op[1] = add | sub | nor_ | xor_ | addi | xor_i | beq | bne | slt_ | lw | lbu | sw | sb | addm;
    assign alu_op[2] = and_ | or_ | nor_ | xor_ | and_i | or_i | xor_i;

    //set control_type
    assign control_type[0] = ((beq & zero) | (bne & !zero) | jr);
    assign control_type[1] = (j | jr); 

    //set the rd_src
    assign rd_src = addi | addui | and_i | or_i | xor_i | lui_ | lw | lbu; 

    //memrd wordwe
    assign mem_read = lw | lbu | addm;
    assign word_we = sw;
    assign byte_we = sb;
    assign byte_load = lbu;
    assign lui = lui_;
    assign slt = slt_;
    
    assign writeenable = add | addu | sub | and_ | or_ | nor_ | xor_ | addi | addui | and_i | or_i | xor_i | lui_ | slt_ | lw | lbu | addm;
    assign except = ~(add | addu | sub | and_ | or_ | nor_ | xor_ | addi | addui | and_i | or_i | xor_i | beq | bne | j | jr | lui_ | slt_ | lw | lbu | sw | sb | addm);



endmodule // mips_decode
