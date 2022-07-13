module bb1_test;
    reg w, v, j;                           // these are inputs to "circuit under test"
                                              // use "reg" not "wire" so can assign a value
    wire c;                        // wires for the outputs of "circuit under test"

    blackbox bb1(c, w, v, j);  // the circuit under test

    initial begin                             // initial = run at beginning of simulation
                                              // begin/end = associate block with initial

        $dumpfile("bb1.vcd");                  // name of dump file to create
        $dumpvars(0,bb1_test);                 // record all signals of module "sc_test" and sub-modules
                                              // remember to change "sc_test" to the correct
                                              // module name when writing your own test benches

        // test all four input combinations
        // remember that 2 inputs means 2^2 = 4 combinations
        // 3 inputs would mean 2^3 = 8 combinations to test, and so on
        // this is very similar to the input columns of a truth table
        w = 0; v = 0; j = 0; # 10;             // set initial values and wait 10 time units
        w = 0; v = 0; j = 1; # 10;             // change inputs and then wait 10 time units
        w = 0; v = 1; j = 0; # 10;             // as above
        w = 0; v = 1; j = 1; # 10;
        w = 1; v = 0; j = 0; # 10;
        w = 1; v = 0; j = 1; # 10;
        w = 1; v = 1; j = 0; # 10;
        w = 1; v = 1; j = 1; # 10;

        $finish;                              // end the simulation
    end

    initial
        $monitor("At time %2t, w = %d v = %d j = %d c = %d",
                 $time, w, v, j, c);
endmodule // sc2_test
