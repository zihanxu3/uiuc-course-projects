
module arraySortCheck_control(sorted, done, load_input, load_index, select_index, go, inversion_found, end_of_array, zero_length_array, clock, reset);
	output sorted, done, load_input, load_index, select_index;
	input go, inversion_found, end_of_array, zero_length_array;
	input clock, reset;

	wire sGarbage, sStart, sCheck, sSorted, sUnsorted, sGoOn;

	wire sGarbage_next = (sGarbage & ~go) | reset;
	wire sStart_next = ((sGarbage & go) | (sUnsorted & go) | (sStart & go) | (sSorted & go)) & ~reset;
	wire sCheck_next = ((sStart & ~go & ~end_of_array & ~zero_length_array) | (sGoOn & ~inversion_found & ~end_of_array & ~zero_length_array)) & ~reset;
	wire sGoOn_next = (sCheck & ~inversion_found & ~end_of_array & ~zero_length_array) & ~reset;
	wire sSorted_next = ((sCheck & end_of_array) | (sCheck & zero_length_array) | (sSorted & ~go)) & ~reset;
	wire sUnsorted_next = (sCheck & inversion_found | (sUnsorted & ~go)) & ~reset;


	dffe d1(sGarbage, sGarbage_next, clock, 1'b1, 1'b0);
	dffe d2(sStart, sStart_next, clock, 1'b1, 1'b0);
	dffe d3(sCheck, sCheck_next, clock, 1'b1, 1'b0);
	dffe d4(sGoOn, sGoOn_next, clock, 1'b1, 1'b0);
	dffe d5(sSorted, sSorted_next, clock, 1'b1, 1'b0);
	dffe d6(sUnsorted, sUnsorted_next, clock, 1'b1, 1'b0);

	assign sorted = sSorted;
	assign done = sSorted | sUnsorted;
	assign load_input = sStart;
	assign load_index = sStart | sGoOn;
	assign select_index = sGoOn;


endmodule
