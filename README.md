# DC-SCS-MP2
Information of Correlation-driven spin-component-scaled second-order Møller-Plesset perturbation theory

There are two components in the electron correlation energy, Cos and Cs corresponding
to the correlation of opposite-spin and same-spin respectively. To get both amounts in the
ORCA software, the ORCA.input file must be used. 

On the other hand, to obtain IND/IT and ID/IT indixes, we write the program orbitals.c. 
To compile it you must write the following line in the terminal:

gccprogram.c − oprogram.x − lm

Later you will use the executable as follows:

./program.x file.out

where file.out is the ORCA output file. At the end of the described procedure you will have 
IND/IT and ID/IT. 
