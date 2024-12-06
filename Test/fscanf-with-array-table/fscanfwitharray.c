#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>  // For isalpha() function

#define MAX_ROWS 26  // Assuming there are 52 rows in the data.txt (covering both uppercase and lowercase letters)
#define MAX_COLS 2   // Two values per pair (ASCII value and random number)

int main() {
    FILE *arrayFile = fopen("array_file.txt", "r");  // Open the array file for reading
    FILE *dataFile = fopen("data.txt", "r");         // Open the data file for reading

    if (arrayFile == NULL || dataFile == NULL) {
        fprintf(stderr, "Failed to open one of the files\n");
        exit(1);  // Exit if the file can't be opened
    }

    int data[MAX_ROWS][MAX_COLS];  // Array to store ASCII values and random numbers
    char word[100];  // Array to hold words from the array file
    int i = 0;
    int totalWords = 0;  // Counter for total words
    int totalAlphaChars = 0;  // Counter for alphabetic characters (excluding spaces and punctuation)

    // Read the data file into the array for easy access to random numbers
    while (fscanf(dataFile, "%d %d", &data[i][0], &data[i][1]) == 2) 
    {
        i++;  // Increment row index for each pair
        if (i >= MAX_ROWS) 
        {
            break;  // Stop reading if we've reached the maximum number of rows
        }
    }

    // Close the data file after reading
    fclose(dataFile);

    // Output the contents of the data array for verification
    printf("Data read from the data file:\n");
    //for (int j = 0; j < i; j++) {
    //    printf("ASCII Value: %d, Random Number: %d\n", data[j][0], data[j][1]);
    //}

    // Read the first word from the array file and display its ASCII values
    if (fscanf(arrayFile, "%s", word) == 1) {
        // Output the ASCII values of the first word
        printf("\nThe ASCII values of the first word are: ");
        
        for (int j = 0; word[j] != '\0'; j++) {
            int asciiValue = word[j];  // Get the ASCII value of the character
            printf("%d", asciiValue);  // Print the ASCII value
            if (word[j + 1] != '\0') {
                printf(",");  // Separate ASCII values with commas
            }
        }
        printf("\n");

        // Output the random numbers corresponding to the ASCII values
        printf("The two digit random numbers of the first word are: ");
        
        for (int j = 0; word[j] != '\0'; j++) {
            int asciiValue = word[j];  // Get the ASCII value of the character
            int randomNumber = -1;     // Default value for random number if not found
            
            // Search for the corresponding random number in the data array
            for (int k = 0; k < i; k++) {
                if (data[k][0] == asciiValue) {
                    randomNumber = data[k][1];  // Get the random number for the ASCII value
                    break;
                }
            }

            // Print the random number associated with this ASCII value
            printf("%02d", randomNumber);  // Print as two digits
            if (word[j + 1] != '\0') {
                printf(",");  // Separate numbers with commas
            }
        }
        printf("\n");
    } else {
        printf("No word found in the array file.\n");
    }

    // Close the array file after reading
    fclose(arrayFile);

    // Reset the file pointer to the beginning of the array file to read all words
    arrayFile = fopen("array_file.txt", "r");
    if (arrayFile == NULL) {
        fprintf(stderr, "Failed to open the array file again\n");
        exit(1);
    }



    // Read words from the array file and count them
    printf("\nWords in the file:\n");

    // Read each word from the file and process it
    while (fscanf(arrayFile, "%s", word) == 1) {
        // Print each word on a new line
        printf("%s\n", word);

        // Increment total word count
        totalWords++;

        // Count alphabetic characters in the word
        for (int j = 0; word[j] != '\0'; j++) {
            if (isalpha(word[j])) {
                totalAlphaChars++;
            }
        }
    }

    // Close the array file after reading
    fclose(arrayFile);

    // Print the total number of words and alphabetic characters
    printf("\nTotal number of words: %d\n", totalWords);
    printf("Total number of alphabetic characters (excluding spaces and punctuation): %d\n", totalAlphaChars);

    return 0;
}