module pipelined_machine(clk, reset);
    input        clk, reset;

    wire [31:0]  PC;
    wire [31:2]  next_PC, PC_plus4, PC_target, new_PC_plus4;
    wire [31:0]  inst, old_inst;

    wire [31:0]  imm = {{ 16{inst[15]} }, inst[15:0] };  // sign-extended immediate
    wire [4:0]   rs = inst[25:21];
    wire [4:0]   rt = inst[20:16];
    wire [4:0]   rd = inst[15:11];
    wire [5:0]   opcode = inst[31:26];
    wire [5:0]   funct = inst[5:0];

    wire [4:0]   wr_regnum, wr_regnum_MW;
    wire [2:0]   ALUOp;

    wire         RegWrite, BEQ, ALUSrc, MemRead, MemWrite, MemToReg, RegDst, MemRead_MW, MemToReg_MW, RegWrite_MW, MemWrite_MW;
    wire         PCSrc, zero, stall;
    wire [31:0]  rd1_data, rd2_data, B_data, alu_out_data, load_data, wr_data, old_alu_out_data, new_rd2_data, new_rd1_data, mux_rd2_data;

    // implement forward
    wire forwardA = RegWrite_MW && (rs != 5'b00000) && (wr_regnum_MW == rs);
    wire forwardB = RegWrite_MW && (rt != 5'b00000) && (wr_regnum_MW == rt);

    // implement stall
    assign stall = MemRead_MW & ((wr_regnum_MW == rs & (rs != 5'b00000)) || (wr_regnum_MW == rt & (rt != 5'b00000)));

    // DO NOT comment out or rename this module
    // or the test bench will break
    register #(30, 30'h100000) PC_reg(PC[31:2], next_PC[31:2], clk, ~stall, reset);

    assign PC[1:0] = 2'b0;  // bottom bits hard coded to 00
    adder30 next_PC_adder(PC_plus4, PC[31:2], 30'h1);


    adder30 target_PC_adder(PC_target, new_PC_plus4, imm[29:0]);
    mux2v #(30) branch_mux(next_PC, PC_plus4, PC_target, PCSrc);
    assign PCSrc = BEQ & zero;

    // DO NOT comment out or rename this module
    // or the test bench will break
    instruction_memory imem(old_inst, PC[31:2]);
    mips_decode decode(ALUOp, RegWrite, BEQ, ALUSrc, MemRead, MemWrite, MemToReg, RegDst,
                      opcode, funct);

    // DO NOT comment out or rename this module
    // or the test bench will break
    regfile rf (rd1_data, rd2_data,
               rs, rt, wr_regnum_MW, wr_data,
               RegWrite_MW, clk, reset);


    mux2v #(32) imm_mux(B_data, mux_rd2_data, imm, ALUSrc);
    mux2v #(32) forward_b(mux_rd2_data, rd2_data, alu_out_data, forwardB);

    mux2v #(32) forward_a(new_rd1_data, rd1_data, alu_out_data, forwardA);
    alu32 alu(old_alu_out_data, zero, ALUOp, new_rd1_data, B_data);

    
    

    // DO NOT comment out or rename this module
    // or the test bench will break

    
    data_mem data_memory(load_data, alu_out_data, new_rd2_data, MemRead_MW, MemWrite_MW, clk, reset);

    mux2v #(32) wb_mux(wr_data, alu_out_data, load_data, MemToReg_MW);
    mux2v #(5) rd_mux(wr_regnum, rt, rd, RegDst);

    ////////////////
    register #(30) if_de_pc(new_PC_plus4, PC_plus4, clk, ~stall, reset | PCSrc);
    register #(32) if_de_ins(inst, old_inst, clk, ~stall, reset | PCSrc);

    register #(32) mw_result(alu_out_data, old_alu_out_data, clk, /* enable */1'b1, reset);
    register #(32) mw_data(new_rd2_data, mux_rd2_data, clk, /* enable */1'b1, reset);

    register #(1) de_memread(MemRead_MW, MemRead, clk, /* enable */1'b1, reset);
    register #(1) de_regwrite(RegWrite_MW, RegWrite, clk, /* enable */1'b1, reset);
    register #(1) de_memtoreg(MemToReg_MW, MemToReg, clk, /* enable */1'b1, reset);
    register #(1) de_memwrite(MemWrite_MW, MemWrite, clk, /* enable */1'b1, reset);
    register #(5) de_wrregnum(wr_regnum_MW, wr_regnum, clk, /* enable */1'b1, reset);


endmodule // pipelined_machine
