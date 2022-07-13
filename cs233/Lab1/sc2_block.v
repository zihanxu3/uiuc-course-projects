// Complete the sc2_block module in this file
// Don't put any code in this file besides the sc2_block
// Refer to sc_block.v for hints!

module sc2_block(s, c, a, b, cin);
    output s, c;
    input  a, b, cin;
    wire s1, c1, c2;

    sc_block block1(s1, c1, a, b);
    sc_block block2(s, c2, s1, cin);
    or o3(c, c2, c1);
endmodule // sc2_block
