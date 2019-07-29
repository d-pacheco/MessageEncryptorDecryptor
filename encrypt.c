#include <stdio.h>
#include <stdlib.h>

void reverseText(char *letter_1, char *letter_2){
    char temp;
    // Reverse string on place
    for ( ; letter_1 != letter_2 && letter_1 > letter_2 ;letter_1++, letter_2--){
        temp = *letter_1;
        *letter_1 = *letter_2;
        *letter_2 = temp;
    }
    return;
}

void encrypt (char plainText[], int inputLength, int mappingScheme[26]){
    int i, mappingIndex;
    // Turn plain text characters to the cypher characters
    for (i = 0; (i < 21 && plainText[i] != '\0' && plainText[i] != '\n'); i++){
        mappingIndex = plainText[i] - 'a';
        plainText[i] = mappingScheme[mappingIndex];
    }
    reverseText(&plainText[0], &plainText[inputLength-1]);
    
    // Print the output of the cyphered string:
    printf("%s", plainText);
    return;
}

void decrypt (char cypherText[], int inputLength, int mappingScheme[26]){
    int i, mappingIndex;
    // Turn cypher characters to the plain text characters
    for (i = 0; (i < 20 && cypherText[i] != '\0' && cypherText[i] != '\n'); i++){
        mappingIndex = cypherText[i] - 'a';
        cypherText[i] = mappingScheme[mappingIndex];
    }
    reverseText(&cypherText[0], &cypherText[inputLength-1]);  // reverse the order of the string

    // Print the output of the cyphered string
    printf("%s", cypherText);
    return;
}