# logic-minimizer
##Description
C++ logic minimizer that uses the Quine-McCluskey algorightm and Petricks method for minimization. The purpose of this program was to gain experience with logic minimization techniques and concepts in hope of understanding other minimization algorithms such as the Espresso heuristic algorithm.

##Build
To build, use
```
make
```
##Usage
Proper usage:
```
./qmc [filename]
```
[filname] specifies the fie to be read containing the truth table for input. The file format required is the same file format for input files for the Espresso minimization program. Sample files are contained in the `samples/` folder.

##Samples
Some examples of the ouputs created from the given inputs:
###2-bit-adder:
```
f0 = (I1)(I2)

f1 = (I1)'(I2) + (I1)(I2)'
```
###2-output-test
```
f0 = (I1)'(I3) + (I1)'(I2)'(I3) + (I1)(I2)'

f1 = (I1)'(I2)'(I3) + (I2)(I3) + (I1)(I2)
```
###3-bit-comparator
```
L = (A0)'(A1)'(A2)'(A3)'(B3) + (A0)'(A1)'(A2)'(B2) + (A0)'(A1)'(B1) + (A0)'(B0) + (A0)'(A1)'(A3)'(B2)(B3) + (A0)'(A2)'(A3)'(B1)(B3) + (A0)'(A2)'(B1)(B2) + (A0)'(A3)'(B1)(B2)(B3) + (A1)'(A2)'(A3)'(B0)(B3) + (A1)'(A2)'(B0)(B2) + (A1)'(B0)(B1) + (A1)'(A3)'(B0)(B2)(B3) + (A2)'(A3)'(B0)(B1)(B3) + (A2)'(B0)(B1)(B2) + (A3)'(B0)(B1)(B2)(B3)

G = (A3)(B0)'(B1)'(B2)'(B3)' + (A2)(B0)'(B1)'(B2)' + (A2)(A3)(B0)'(B1)'(B3)' + (A1)(B0)'(B1)' + (A1)(A3)(B0)'(B2)'(B3)' + (A1)(A2)(B0)'(B2)' + (A1)(A2)(A3)(B0)'(B3)' + (A0)(B0)' + (A0)(A3)(B1)'(B2)'(B3)' + (A0)(A2)(B1)'(B2)' + (A0)(A2)(A3)(B1)'(B3)' + (A0)(A1)(B1)' + (A0)(A1)(A3)(B2)'(B3)' + (A0)(A1)(A2)(B2)' + (A0)(A1)(A2)(A3)(B3)'

E = (A0)'(A1)'(A2)'(A3)'(B0)'(B1)'(B2)'(B3)' + (A0)'(A1)'(A2)'(A3)(B0)'(B1)'(B2)'(B3) + (A0)'(A1)'(A2)(A3)'(B0)'(B1)'(B2)(B3)' + (A0)'(A1)'(A2)(A3)(B0)'(B1)'(B2)(B3) + (A0)'(A1)(A2)'(A3)'(B0)'(B1)(B2)'(B3)' + (A0)'(A1)(A2)'(A3)(B0)'(B1)(B2)'(B3) + (A0)'(A1)(A2)(A3)'(B0)'(B1)(B2)(B3)' + (A0)'(A1)(A2)(A3)(B0)'(B1)(B2)(B3) + (A0)(A1)'(A2)'(A3)'(B0)(B1)'(B2)'(B3)' + (A0)(A1)'(A2)'(A3)(B0)(B1)'(B2)'(B3) + (A0)(A1)'(A2)(A3)'(B0)(B1)'(B2)(B3)' + (A0)(A1)'(A2)(A3)(B0)(B1)'(B2)(B3) + (A0)(A1)(A2)'(A3)'(B0)(B1)(B2)'(B3)' + (A0)(A1)(A2)'(A3)(B0)(B1)(B2)'(B3) + (A0)(A1)(A2)(A3)'(B0)(B1)(B2)(B3)' + (A0)(A1)(A2)(A3)(B0)(B1)(B2)(B3)
```
