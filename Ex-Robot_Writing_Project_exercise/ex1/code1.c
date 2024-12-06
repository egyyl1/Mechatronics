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

// Function to display the first N rows of data in the same format as the file
void displayFirstNRows(struct DataRow *dataArray, int numRows, int N) {
    // Ensure that N does not exceed the number of available rows
    int rowsToDisplay = (N > numRows) ? numRows : N;
    
    // Display the first N rows in the same format as the file
    for (int i = 0; i < rowsToDisplay; i++) {
        printf("%d %d %d\n", dataArray[i].col1, dataArray[i].col2, dataArray[i].col3);
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

    // Display the first 10 rows
    displayFirstNRows(dataArray, NUM_ROWS, 10);

    // Free the allocated memory
    free(dataArray);

    return 0;
}

