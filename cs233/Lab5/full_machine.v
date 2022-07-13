
// full_machine: execute a series of MIPS instructions from an instruction cache
//
// except (output) - set to 1 when an unrecognized instruction is to be executed.
// clock   (input) - the clock signal
// reset   (input) - set to 1 to set all registers to zero, set to 0 for normal execution.

module full_machine(except, clock, reset);
    output      except;
    input       clock, reset;

    wire [31:0] inst;  
    wire [31:0] PC;
    wire [31:0] nextPC; 

    wire [31:0] ctrl_0;
    wire [31:0] ctrl_1;
    wire [31:0] ctrl_2;
    wire [31:0] ctrl_3;


    wire [4:0] wtAddr;

    //related to mips decoder
    wire [2:0] alu_op;
    wire writeenable;
    wire rd_src;
    wire [1:0] alu_src2;
    wire except;
    wire [1:0] control_type;
    wire mem_read;
    wire word_we;
    wire byte_we; 
    wire byte_load; 
    wire slt;
    wire lui; 
    wire addm;
    wire zero;

    wire [31:0] A;
    wire [31:0] B;
    wire [31:0] B_out;

    wire [31:0] addr;
    wire [31:0] data_out;
    wire [7:0] mux4_out;
    wire [31:0] byte_out;
    wire [31:0] mem_out;
    wire [31:0] rdData;
    wire [31:0] ad_out;
    wire [31:0] final_out;
    wire [31:0] slt_out;


    wire negative;

    wire [31:0] imm32 = {{16{inst[15]}},inst[15:0]};
    wire [31:0] branch_offset = {imm32[29:0], 2'b0};
    




    //setup ctrl 0
    alu32 alu_ct0(ctrl_0, , , , PC, 32'h4, `ALU_ADD);
    //ctrl 1
    alu32 alu_ct1(ctrl_1, , , , branch_offset, ctrl_0, `ALU_ADD);                                         //TODO: Branch offset
    //ctrl 2
    assign ctrl_2 = {ctrl_0[31:28], inst[25:0], 2'b0};
    //ctrl 3
    assign ctrl_3 = A;                                                                                    //TODO: setup ctrl3 after refile

    //set up ctrl mux
    mux4v mux_ctrl(nextPC, ctrl_0, ctrl_1, ctrl_2, ctrl_3, control_type);                                 //TODO: setup control type after decoder

    //set up rd rt mux
    mux2v #(5) mux_rdAddr(wtAddr, inst[15:11], inst[20:16], rd_src);                                       //TODO: setup read sources
    // DO NOT comment out or rename this module
    // or the test bench will break
    register #(32) PC_reg(PC, nextPC, clock, 1'b1, reset);   //program counter

    // DO NOT comment out or rename this module
    // or the test bench will break
    instruction_memory im(inst, PC[31:2]);

    // DO NOT comment out or rename this module
    // or the test bench will break
    regfile rf (A, B,
                inst[25:21], inst[20:16], wtAddr, rdData, 
                writeenable, clock, reset);                                                                //TODO: WRT addr, write enable; WRT data  

    /* add other modules */

    //mips decoder 
    mips_decode decoder(alu_op, writeenable, rd_src, alu_src2, except, control_type,
                   mem_read, word_we, byte_we, byte_load, slt, lui, addm,
                   inst[31:26], inst[5:0], zero);


    mux4v b_data(B_out, B, {{16{inst[15]}},inst[15:0]}, {16'b0, inst[15:0]}, 32'b0, alu_src2);

    alu32 alu_OP(addr, , zero, negative, A, B_out, alu_op);

    data_mem data_m(data_out, addr, B, word_we, byte_we, clock, reset);

    mux2v mux_slt(slt_out, addr, {31'b0, negative}, slt);

    //mux 4 
    mux4v #(8) mux_siv(mux4_out, data_out[7:0], data_out[15:8], data_out[23:16], data_out[31:24], addr[1:0]);

    mux2v mux_byte(byte_out, data_out[31:0], {24'b0, mux4_out}, byte_load);

    mux2v mux_mem(mem_out, slt_out, byte_out, mem_read);

    mux2v mux_lui(rdData, final_out, {inst[15:0],16'b0}, lui);

    alu32 alu_ADDM(ad_out, , , , B, mem_out, `ALU_ADD);

    mux2v mux_final(final_out, mem_out, ad_out, addm);



endmodule // full_machine
