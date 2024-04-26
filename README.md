# SIC-XE-Assembler
I have successfully implemented an assembler for SIC/XE that supports program blocks, literals, expressions as well as other basic functionalities. 
It is a two pass assembler.

# The following files are used in the project: 
1. pass1.hpp : logic of pass1 of assembler. 
2. pass2.hpp : logic of pass2 of assembler. 
3. Assembler.cpp : main file which you must run in order to avail the functionality. 
4. Input.txt: The input is given in this file. 
5. Output.txt: The final object program is written in this file. 
6. Intermediate.txt: The intermediate file includes block numbers and LOCCTR information of the instructions. It also includes the symbol table. 
7. Listing.txt : It contains the listing of the instructions and object codes.
   
# Error handling: 
Various errors are handled and printed in error.txt file: 
The errors handled include: 
- Checking whether we try to define a label twice. 
- Check whether we have an invalid expression(very basic errors) 
- Checking if a displacement of more than 2047 is tried to be done even when programmer does not write a BASE assembler directive flagging that base is not 
  available to use. 
- Trying to use indexing with immediate/indirect mode of assembly. 
- Trying to use invalid registers, etc.
- Checking presence of end statement.

# Reference:
- For understanding the exacting working look at the project report.
