#include <stdio.h>
#include <stdlib.h>

void readFileAndDisplayCharacters(const char *filename) {
    FILE *inputFile = fopen(filename, "r");  // Open the file for reading
    if (inputFile == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    int ch;  // Variable to hold each character
    while ((ch = fgetc(inputFile)) != EOF) {  // Read one character at a time until EOF
        printf("%d : %c\n", ch, ch);  // Display the ASCII value and the character
    }

    fclose(inputFile);  // Close the file
}

int main() {
    // Specify the file path
    const char *filePath = "C:/Users/Horace Lee/Downloads/SampleLines.txt";
    
    // Call the function to read and display characters from the file
    readFileAndDisplayCharacters(filePath);

    return 0;
}
