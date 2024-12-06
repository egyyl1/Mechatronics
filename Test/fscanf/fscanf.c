#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>  // For isalpha() to check alphabetic characters

int main() {
    // Open the file for reading
    FILE *file = fopen("data.txt", "r");

    if (file == NULL) {
        fprintf(stderr, "Failed to open file\n");
        exit(1);  // Exit if the file can't be opened
    }

    char word[100];  // Array to hold each word
    int wordCount = 0;  // Initialize word count
    int charCount = 0;  // Initialize character count
    int firstWordAsciiDisplayed = 0;  // Flag to track if we've processed the first word

    // Read each word from the file, one by one
    while (fscanf(file, "%s", word) == 1) {  // fscanf reads a word
        wordCount++;  // Increment the word count each time a word is read
        
        // Loop through each character in the word
        for (int i = 0; word[i] != '\0'; i++) {
            if (isalpha(word[i])) {  // Check if the character is alphabetic
                charCount++;  // Increment the character count for alphabetic characters
            }
        }
        
        printf("%s\n", word);  // Print the word followed by a newline
        
        // If we haven't displayed the first word's ASCII values yet
        if (!firstWordAsciiDisplayed) {
            printf("The ASCII of first word is: ");
            for (int i = 0; word[i] != '\0'; i++) {
                printf("%d", word[i]);  // Print ASCII value of each character
                if (word[i + 1] != '\0') {
                    printf(",");  // Add a comma between ASCII values
                }
            }
            printf("\n");
            firstWordAsciiDisplayed = 1;  // Set the flag to true after displaying the first word
        }
    }

    // Print the total number of words and alphabetic characters
    printf("\nTotal number of words: %d\n", wordCount);
    printf("Total number of alphabetic characters (excluding spaces and punctuation): %d\n", charCount);

    // Close the file
    fclose(file);

    return 0;
}
