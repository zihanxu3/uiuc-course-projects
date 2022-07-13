module timer(TimerInterrupt, cycle, TimerAddress,
             data, address, MemRead, MemWrite, clock, reset);
    output        TimerInterrupt;
    output [31:0] cycle;
    output        TimerAddress;
    input  [31:0] data, address, inter_q, cycle_q, cycle_d;
    input         MemRead, MemWrite, clock, reset;

    wire timer_write, acknowledge, timer_read;

    // complete the timer circuit here
    register #(32, 32'hffffffff) interr_cycle(inter_q, data, clock, timer_write, reset);

    register cycle_counter(cycle_q, cycle_d, clock, 1'b1, reset);

    alu32 a(cycle_d, , , `ALU_ADD, cycle_q, 32'd1);

    tristate tr_1(cycle, cycle_q, timer_read);

    dffe interr_line(TimerInterrupt, 1'b1, clock, (cycle_q == inter_q), (acknowledge | reset));

    wire first_eq, second_eq;

    assign first_eq = (32'hffff001c == address);
    assign second_eq = (32'hffff006c == address);

    or o1(TimerAddress, first_eq, second_eq);
    and a1(acknowledge, second_eq, MemWrite);
    and a2(timer_read, first_eq, MemRead);
    and a3(timer_write, first_eq, MemWrite);





    // HINT: make your interrupt cycle register reset to 32'hffffffff
    //       (using the reset_value parameter)
    //       to prevent an interrupt being raised the very first cycle
endmodule
