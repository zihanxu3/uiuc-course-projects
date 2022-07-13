//implement a test bench for your 32-bit ALU
module alu32_test;
    reg [31:0] A = 0, B = 0;
    reg [2:0] control = 0;

    initial begin
        $dumpfile("alu32.vcd");
        $dumpvars(0, alu32_test);

             A = 8; B = 4; control = `ALU_ADD; // try adding 8 and 4
        # 10 A = 2; B = 5; control = `ALU_SUB; // try subtracting 5 from 2
        // add more test cases here!
        # 10 A = 0; B = 0; control = `ALU_ADD; // try 0+0
        # 10 A = 32'h7ffffff0; B = 36; control = `ALU_SUB; // try subtracting 5 from 2
        # 10 A = 32'h7fffffff; B = 32'h7ffffff2; control= `ALU_ADD;
        # 10 A = 32'h80000000; B = 32'h81000000; control= `ALU_ADD;
        # 10 A = 32'h7fffffff; B = 32'h7fffffff; control= `ALU_SUB;
        # 10 A = 32'hafffffff; B = 32'hefffffff; control= `ALU_UADD;
        # 10 A = 1; B = 1; control= `ALU_XOR;
        # 10 A = 0; B = 1; control= `ALU_XOR;

        # 10 $finish;
    end

    wire [31:0] out;
    wire overflow, zero, negative;
    alu32 a(out, overflow, zero, negative, A, B, control);  
endmodule // alu32_test
