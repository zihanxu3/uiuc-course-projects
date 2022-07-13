`define STATUS_REGISTER 5'd12
`define CAUSE_REGISTER  5'd13
`define EPC_REGISTER    5'd14

module cp0(rd_data, EPC, TakenInterrupt,
           wr_data, regnum, next_pc,
           MTC0, ERET, TimerInterrupt, clock, reset);
    output [31:0] rd_data;
    output [29:0] EPC;
    output        TakenInterrupt;
    input  [31:0] wr_data;
    input   [4:0] regnum;
    input  [29:0] next_pc;
    input         MTC0, ERET, TimerInterrupt, clock, reset;

    wire [31:0] decoder_out, user_status, status_register, cause_register;
    wire exception_level;
    wire [29:0] epc_D;

    assign status_register[31:16] = 16'b0;
    assign status_register[15:8] = user_status[15:8];
    assign status_register[7:2] = 6'b0;
    assign status_register[1] = exception_level;
    assign status_register[0] = user_status[0];

    assign cause_register[31:16] = 16'b0;
    assign cause_register[15] = TimerInterrupt;
    assign cause_register[14:0] = 15'b0;

    // your Verilog for coprocessor 0 goes here
    register user_stat(user_status, wr_data, clock, decoder_out[12], reset);
    decoder32 decoder(decoder_out, regnum, MTC0);
    dffe exception_lev(exception_level, 1'b1, clock, TakenInterrupt, (ERET | reset));

    mux2v #(30) mux1(epc_D, wr_data[31:2], next_pc, TakenInterrupt);
    register #(30) epc_reg(EPC, epc_D, clock, (TakenInterrupt | decoder_out[14]), reset);

    mux32v #(32) mux32(rd_data, , , , , , , , , , , , , status_register, cause_register, {EPC, 2'b0}, , , , , , , , , , , , , , , , , , regnum);
    
    wire a1_out, a2_out;
    and a1(a1_out, cause_register[15], status_register[15]);
    and a2(a2_out, ~status_register[1], status_register[0]);

    assign TakenInterrupt = a1_out & a2_out;

        



endmodule
