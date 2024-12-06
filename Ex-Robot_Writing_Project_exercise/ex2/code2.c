#include <stdio.h>
#include <stdlib.h>

#define NUM_ROWS 1027  // The number of rows in the file
#define COLUMNS 3      // The number of columns in each row

// Define a struct to represent a row with 3 integer columns
struct DataRow {
    int col1;
    int col2;
    int col3;
};

// Function to read the file and store the data in the array
void readFile(const char *filename, struct DataRow *dataArray, int numRows) {
    FILE *inputFile = fopen(filename, "r");  // Open the file for reading
    if (inputFile == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Read the rows of the file
    for (int i = 0; i < numRows; i++) {
        fscanf(inputFile, "%d %d %d", &dataArray[i].col1, &dataArray[i].col2, &dataArray[i].col3);
    }

    fclose(inputFile);  // Close the file
}

// Function to display the drawing data for the selected character
void displayCharacterData(struct DataRow *dataArray, int numRows, int charCode) {
    int found = 0;
    
    // Loop through the dataArray to find the character's drawing data
    for (int i = 0; i < numRows; i++) {
        if (dataArray[i].col1 == 999 && dataArray[i].col2 == charCode) {
            printf("Character %d drawing data:\n", charCode);
            int numMovements = dataArray[i].col3; // Number of movements for the character

            // Display the drawing data for this character
            for (int j = 1; j <= numMovements; j++) {
                int index = i + j;
                if (index < numRows && dataArray[index].col1 != 999) {
                    printf("%d %d %d\n", dataArray[index].col1, dataArray[index].col2, dataArray[index].col3);
                }
            }
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Character %d not found.\n", charCode);
    }
}

int main() {
    struct DataRow *dataArray = (struct DataRow *)malloc(NUM_ROWS * sizeof(struct DataRow));  // Allocate memory for NUM_ROWS rows

    if (dataArray == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    // Read the data from the file (using the correct file path)
    readFile("C:/Users/Horace Lee/Downloads/SingleStrokeFont.txt", dataArray, NUM_ROWS);

    // Prompt user for the ASCII code of the character they want to display
    int charCode;
    printf("Enter the ASCII code of the character you want to display: ");
    scanf("%d", &charCode);

    // Display the drawing data for the selected character
    displayCharacterData(dataArray, NUM_ROWS, charCode);

    // Free the allocated memory
    free(dataArray);

    return 0;
}
