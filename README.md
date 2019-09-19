# MessageEncryptorDecryptor

This program uses a mapping scheme as one of the inputs, the input file which contains the text, and the mode of the program to either encrpt or decrpt the input file. output of the program is printed to the command line.

## How to use the program
After compiling the following command:
```
To compile the program:
make

To clean after program is finished being used:
make clean
```
You can either run the program with the following commands:
```
./encrpt -t <mappingfile> -i <inputfile> -m <encryption mode>

For encrption:
./encrpt -t mappingfile.csv -i inputfile.txt -m 1

For decryption:
./encrpt -t mappingfile.csv -i inputfile.txt -m 2
```

Each word to be encrpted/decrpted must be on a seperate line

## What I struggled with
- Began with a single file, but felt that the organization of the program could be better structured into multiple files
- Reading from the mapping scheme file and checking that there are no duplicate character when storing in an array

## What I learnt from this project
- Learned a verity of bash commands and their uses when using makefiles for linking multiple files together
- How to pass files and inputs and error check the inputs to return the correct error code if incorrect inputs were given
    - Error checking an input file (this case the mapping scheme) so that it meets the intended structure.
- Breaking up a program into multiple files for better
- Working with arrays and pointers
