module keypad(valid, number, a, b, c, d, e, f, g);
   output 	valid;
   output [3:0] number;
   input 	a, b, c, d, e, f, g;
   wire w1, w2, w3, w4, w5, w6, w7, w8, w9, w10;

   and a1(w1, a, d);
   and a2(w2, a, e);
   and a3(w3, a, f);

   and b1(w4, b, d);
   and b2(w5, b, e);
   and b3(w6, b, f);
   and b4(w7, b, g);

   and c1(w8, c, d);
   and c2(w9, c, e);
   and c3(w10, c, f);

   or o1(valid, w1, w2, w3, w4, w5, w6, w7, w8, w9, w10);

   assign number[3] = ((b && f) || (c && f));
   assign number[2] = ((a && e) || (b && e) || (c && e) || (a && f));
   assign number[1] = ((b && d) || (c && d) || (c && e) || (a && f));
   assign number[0] = ((a && d) || (c && d) || (b && e) || (c && f) || (a && f));

endmodule // keypad
