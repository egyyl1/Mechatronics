#include <stdio.h>
#include <stdlib.h>

#define NUM_ROWS 1027  // Number of rows in the file

// Define a struct to represent a row with 3 integer columns
struct DataRow {
    int xPos;
    int yPos;
    int penStatus;
};

// Function to read the file and store the data in the array
void readFile(const char *filename, struct DataRow *dataArray, int numRows) {
    FILE *inputFile = fopen(filename, "r");
    if (inputFile == NULL) {
        perror("Error opening font data file");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < numRows; i++) {
        fscanf(inputFile, "%d %d %d", &dataArray[i].xPos, &dataArray[i].yPos, &dataArray[i].penStatus);
    }

    fclose(inputFile);
}

// Function to display the first 50 rows of data
void displayFirst50Rows(struct DataRow *dataArray) {
    for (int i = 0; i < 50; i++) {
        printf("%d %d %d\n", dataArray[i].xPos, dataArray[i].yPos, dataArray[i].penStatus);
    }
}

int main() {
    struct DataRow *dataArray = (struct DataRow *)malloc(NUM_ROWS * sizeof(struct DataRow));
    if (dataArray == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    // Read the data from the file
    readFile("C:/Users/Horace Lee/Downloads/SingleStrokeFont.txt", dataArray, NUM_ROWS);

    // Display the first 50 rows
    displayFirst50Rows(dataArray);

    // Free allocated memory
    free(dataArray);

    return 0;
}
