/**
 * @file
 * Contains an implementation of the countOnes function.
 */

unsigned countOnes(unsigned input) {
	// TODO: write your code here
    
    unsigned rt = input & 0x55555555;
    unsigned lt = input & 0xAAAAAAAA;
    unsigned rs = (lt >> 1) + rt;
    
    unsigned r2 = rs & 0x33333333;
    unsigned l2 = rs & 0xcccccccc;
    unsigned rs2 = (l2 >> 2) + r2;
    
    unsigned r3 = rs2 & 0x0f0f0f0f;
    unsigned l3 = rs2 & 0xf0f0f0f0;
    unsigned rs3 = (l3 >> 4) + r3;
    
    unsigned r4 = rs3 & 0x00ff00ff;
    unsigned l4 = rs3 & 0xff00ff00;
    unsigned rs4 = (l4 >> 8) + r4;
    
    unsigned r5 = rs4 & 0x0000ffff;
    unsigned l5 = rs4 & 0xffff0000;
    unsigned rs5 = (l5 >> 16) + r5;
    

	return rs5;
}
