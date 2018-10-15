# HPC-tools-task2
QR.cpp optimization with compiler
Here you'll find a solver for n equation and n variable system with a QR decomposition
matrix BIG is the matrix of the vector you want to solve. A is the matrix corresponding of the system
remove all the //! to see the result on the terminal and see every iteration of the QR decomposition.
BIG can be (N,1) where N is the size of A
NOTE: THIS CODE IS FOR SQUARE MATRIX i havent try it with rectangular matrix
the QR part is from english QR decomposition from wikipedia .

the code is not well optimize YET. (i'll optimise it one day maybe when i'll have time)
please if anyone use one day this code tell me i would like to know if this thing will be one day usefull to someone.


if g++ QR.cpp dosen't work for compiling try that:
gcc -std=c++11 -O0 QR.cpp

to execute the program 
./a.out N
N is the size of A and BIG
i'll modify the code (one day) to separate those 2 paramaters


everyone can use this code for anything he want. i don't care not sure the code work in 100% of case
