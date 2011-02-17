CS6397_Programming Assignment 1:

Student names:
==============
Nithin Thomas (nxt054000 at utdallas dot edu)
Girish Deshpande (grd091020 at utdallas dot edu)

PART 1:java style stack based calculator
========================================
Sources:
---------
jcmain.cc 
jc.cc
stack.cc

headers
-------
jc.h
stack.h

The jcmain.cc is the stack based calculator that supports the following operations:
const,pop,store,load,add,sub,mul,div,p



Instructions to run and test the program:
-----------------------------------------
1) Run make jc to compile and create the jc executable
2) Run the executable ./jc
syntax:
> opcode operand
eg:
To add two numbers:
./jc
Enter a command(q to quit):const 10
Enter a command(q to quit):const 20
Enter a command(q to quit):add
Enter a command(q to quit):p
30
Enter a command(q to quit):q

2)The program will quit if sufficient number of operands are not entered.


PART 2: java virtual machine
============================
The jvm is the java virtual machine with support for 
conditional jump instructions

sources (in addition to those in part 1):
jvmmain.cc
jvm.cc
jvm.h


Instructions to run and test the program:
-----------------------------------------
1) Run make jvm to compile and create the executable jvm
2) Run the executable ./jvm
syntax:
./jvm filename.jvm



PART 3:extended java virtual machine
=====================================
The ejvm is the extended java virtual machine with support 
for subroutine calls.

sources (in addition to those in part 2):
ejvm.h
ejvm.cc
ejvmmain.cc

Instructions to run and test the program:
-----------------------------------------
1) Run make ejvm to compile and create the executable ejvm 
2)Run the executable ejvm
syntax:
./ejvm filename.jvm

Additional Notes:
------------------------------------------
1) To clean up all the output files, run make clean 
2) Run make all to build all 3 parts at once














