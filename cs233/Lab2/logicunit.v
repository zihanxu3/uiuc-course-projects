// 00 -> AND, 01 -> OR, 10 -> NOR, 11 -> XOR
module logicunit(out, A, B, control);
    output      out;
    input       A, B;
    input [1:0] control;
    wire w_and, w_or, w_nor, w_xor;
    
    and a1(w_and, A, B);
    or o1(w_or, A, B);
    nor n1(w_nor, A, B);
    xor x1(w_xor, A, B);

    mux4 m1(out, w_and, w_or, w_nor, w_xor, control);
    
endmodule // logicunit
