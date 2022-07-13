// output is A (when control == 0) or B (when control == 1)
module mux2(out, A, B, control);
    output out;
    input  A, B;
    input  control;
    wire   wA, wB, not_control;

    not n1(not_control, control);
    and a1(wA, A, not_control);
    and a2(wB, B, control);
    or  o1(out, wA, wB);

endmodule // mux2


// output is A (when control == 00) or B (when control == 01) or
//           C (when control == 10) or D (when control == 11)
module mux4(out, A, B, C, D, control);
    output      out;
    input       A, B, C, D;
    input [1:0] control;
    wire double_not, not_control0, not_control1, wA, not_0, not_1, wB, wC, double_yes, wD, out_1, out_2;

    not n1(not_control0, control[0]);
    not n2(not_control1, control[1]);

    and a1(double_not, not_control0, not_control1);
    and a2(wA, A, double_not);
    and a3(not_0, not_control0, control[1]);
    and a4(not_1, not_control1, control[0]);
    and a5(wB, B, not_1);
    and a6(wC, C, not_0);
    and a7(double_yes, control[0], control[1]);
    and a8(wD, D, double_yes);
    or o1(out_1, wA, wB);
    or o2(out_2, out_1, wC);
    or o3(out, out_2, wD);



endmodule // mux4
