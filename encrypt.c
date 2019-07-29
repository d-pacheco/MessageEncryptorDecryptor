#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void encrypt (char plainText[], int inputLength, int mappingScheme[26]);
void decrypt (char cypherText[], int inputLength, int mappingScheme[26]);


int main(int argc, char*argv[]){
    int i, argvIndex, encryptionMode, line_count, MappedLetter, MappingIndex, inputLength, arguments;
    char *mappingFileName, *inputFileName, inputText[25], MappingLine[5];
    int mappingScheme[26];  // if MappingScheme[mappingIndex] == 0, then we know that we havent changed anything. a to z == 97 to 122 in dec
    FILE *mappingFile;
    FILE *inputFile;

    // Error Checking Files and number of arguments given to program
    arguments = (argc-1)/2;
    if (arguments != 3){
        fprintf(stderr, "Usage: ./encrypt -t <mappingfile> -m <encryption mode> -i <inputfile>");
        exit(7);
    }
    
    argvIndex = 1;
    // Getting arguments provided to the program and assigning to correct variables
    for (i = 0; i<arguments; i++){
        if (strcmp(argv[argvIndex], "-t") == 0){
            mappingFileName = argv[argvIndex+1];
            }
        if (strcmp(argv[argvIndex], "-m") == 0){
            encryptionMode = atoi(argv[argvIndex+1]);
            }
        if (strcmp(argv[argvIndex], "-i") == 0){
            inputFileName = argv[argvIndex+1];
            }
        argvIndex = argvIndex + 2;
        }

    if (encryptionMode < 1 || encryptionMode > 2){
        fprintf(stderr, "You entered %d. Sorry, your mode must be 1 for encryption or 2 for decryption\n", encryptionMode);
        exit(6);
    }
    mappingFile = fopen(mappingFileName, "r");
    if (mappingFile == NULL){
        fprintf(stderr, "Error: Mapping file %s does not exist\n", mappingFileName);
        exit(3);
    }
    inputFile = fopen(inputFileName, "r");
    if (inputFile == NULL){
        fprintf(stderr, "Error: Input word file %s does not exist\n", inputFileName);
        exit(5);
    }
    if (argc != 7){
        fprintf(stderr, "Usage: ./encrypt -t <mappingfile> -m <encryption mode> -i <inputfile>");
        exit(7);
    }

    // Set all values in mappingScheme zero
    for (int i = 0; i < 26; i++){
        mappingScheme[i] = 0;
    }
    
    line_count = 0;
    while (fgets(MappingLine, 5, mappingFile) != NULL){
        // Mapping file contains characters that are not to be handled
        if (MappingLine[0] < 'a' || MappingLine[0] > 'z' || MappingLine[2] < 'a' || MappingLine[2] > 'z'){
            fprintf(stderr, "Error: The format of mapping file %s is incorrect\n", mappingFileName);
            fclose(mappingFile);
            fclose(inputFile);
            exit(4);
        }
        // Format of the mapping file is not correct
        if (MappingLine[1] != ',' && (MappingLine[3] != '\n' || MappingLine[3] != 0)){
            fprintf(stderr, "Error: The format of mapping file %s is incorrect\n", mappingFileName);
            fclose(mappingFile);
            fclose(inputFile);
            exit(4);
        }

        // Map which character is the plain text character and which is the cypher character based on encryption mode
        if (encryptionMode == 1){
            MappingIndex = MappingLine[0] - 'a';
            MappedLetter = MappingLine[2];
        }
        else if (encryptionMode == 2){
            MappingIndex = MappingLine[2] - 'a';
            MappedLetter = MappingLine[0];
        }

        // Checks to see if the current mapped letter has already appeared
        if (mappingScheme[MappingIndex] == 0){
            mappingScheme[MappingIndex] = MappedLetter;
        }
        else{ // Character has already appeared in the mapping scheme, format is not correct
            fprintf(stderr, "Error: The format of mapping file %s is incorrect\n", mappingFileName);
            fclose(mappingFile);
            fclose(inputFile);
            exit(4);
        }
        
        line_count++;
    }
    // To many or to few characters in the mapping file
    if (line_count != 26){
        fprintf(stderr, "Error: The format of mapping file %s is incorrect\n", mappingFileName);
        fclose(mappingFile);
        fclose(inputFile);
        exit(4);
    }
    fclose(mappingFile);

    while (fgets(inputText, 25, inputFile) != NULL){
        inputLength = 0;
        for (int x = 0; (x < 21 && inputText[x] != '\0' && inputText[x] != '\n'); x++) inputLength++;
        if (encryptionMode == 1)
            encrypt(inputText, inputLength, mappingScheme);
        else if (encryptionMode == 2)
            decrypt(inputText, inputLength, mappingScheme);
    }

    fclose(inputFile);
    return 0;
}

void encrypt (char plainText[], int inputLength, int mappingScheme[26]){
    int i, mappingIndex, num_of_recursions, x = inputLength-1;
    char letter_1, letter_2;
    for (i = 0; (i < 21 && plainText[i] != '\0' && plainText[i] != '\n'); i++){
        mappingIndex = plainText[i] - 'a';
        plainText[i] = mappingScheme[mappingIndex];
    }
    // reverse the order of the string:
    num_of_recursions = inputLength/2;
    for (i = 0; (i < num_of_recursions); i++){
        letter_1 = plainText[i];
        letter_2 = plainText[x];
        plainText[i] = letter_2;
        plainText[x] = letter_1;
        x--;
    }
    
    // Print the output of the cyphered string:
    printf("%s", plainText);
    return;
}

void decrypt (char cypherText[], int inputLength, int mappingScheme[26]){
    int i, mappingIndex, num_of_recursions, x = inputLength-1;
    char letter_1, letter_2;
    for (i = 0; (i < 20 && cypherText[i] != '\0' && cypherText[i] != '\n'); i++){
        mappingIndex = cypherText[i] - 'a';
        cypherText[i] = mappingScheme[mappingIndex];
    }
    // reverse the order of the string:
    num_of_recursions = inputLength/2;
    for (i = 0; (i < num_of_recursions); i++){
        letter_1 = cypherText[i];
        letter_2 = cypherText[x];
        cypherText[i] = letter_2;
        cypherText[x] = letter_1;
        x--;
    }
    
    // Print the output of the cyphered string:
    printf("%s", cypherText);
    return;
}
