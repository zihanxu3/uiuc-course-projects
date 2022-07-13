## a code generator for the ALU chain in the 32-bit ALU
## look at example_generator.py for inspiration
## 
## python generator.py

for i in range(1, 32):
    print("alu1 a%d(out[%d], carryout[%d], A[%d], B[%d], carryout[%d], control);" % (i,i,i,i,i, i-1))
