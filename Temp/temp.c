#include <stdio.h>
#include <stdlib.h>

#define NUM_ROWS 1027  // The number of rows in the file
#define COLUMNS 3      // The number of columns in each row
#define ASCII_MARKER 999 // Marker indicating the start of a new batch
#define LINE_WIDTH 100   // Maximum width of a line

struct DataRow 
{
    int col1;
    int col2;
    int col3;
};

// Function to read the stroke data file and load font data into the array
void readFile(const char *filename, struct DataRow *dataArray, int numRows) 
{
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

//****NOTHING WRONG UP TO HERE***//


//*****Testing bit****/

// Function to find and display data for a specific ASCII value
void findAsciiData(struct DataRow *dataArray, int numRows, int asciiValue, int height, double xOffset, double yOffset) 
{
// Print the corresponding character instead of ASCII value
    printf("Data for character '%c' (height = %d):\n", (char)asciiValue, height);

    for (int i = 0; i < numRows; i++) 
    {
        if (dataArray[i].col1 == ASCII_MARKER && dataArray[i].col2 == asciiValue) 
        {
            // Start printing the rows after the marker
            for (int j = i + 1; j < numRows; j++) 
            {
                // Stop when encountering another marker
                if (dataArray[j].col1 == ASCII_MARKER) 
                {
                    break;
                }

                // Multiply the first two columns by the height and add the xOffset to the first column
                double adjustedCol1 = (dataArray[j].col1 / 18.0) * height + xOffset;
                double adjustedCol2 = (dataArray[j].col2 / 18.0) * height + yOffset;

                // Determine S and G values based on column 3
                const char *sValue = (dataArray[j].col3 == 1) ? "S1000" : "S0";
                const char *gValue = (dataArray[j].col3 == 1) ? "G1" : "G0";

                // Print the adjusted data
                printf("%s\n%s X%.1f Y%.1f\n", sValue, gValue, adjustedCol1, adjustedCol2);
            }
            break;
        }
    }
}

                    //****NOTHING WRONG FOR FIND ASCII DATA function***//
//*****Testing bit end */


// Function to open a text file and read the next word (one at a time)
int readNextWordFromFile(FILE *asciiFile, char *word) 
{
    if (fscanf(asciiFile, "%s", word) != 1) {
        return 0;  // Return 0 to indicate end of file or error
    }

    return 1;  // Return 1 if the word was successfully read
}


//*****Testing bit */

// Function to process a single word
void processWord(struct DataRow *dataArray, int numRows, char *word, int height, double *xOffset, double yOffset) 
{
    
    for (int i = 0; word[i] != '\0'; i++) 
    {
        // Convert character to ASCII value
        int asciiValue = (int)word[i];  

        // Find and display data for this character and apply current xOffset
        findAsciiData(dataArray, numRows, asciiValue, height, *xOffset, yOffset);  

        // Update the xOffset with the scaled width of the current character
        *xOffset += (18.0 / 18.0) * height;
    }
    //Add a space (ASCII 32) after each word
    findAsciiData(dataArray, NUM_ROWS, 32, height, *xOffset, yOffset);

    *xOffset += (18.0 / 18.0) * height;
}

//*****Testing bit end */


// Function to calculate the width of a word
int calculateWordWidth(const char *word, int height) 
{
    int width = 0;

    for (int i = 0; word[i] != '\0'; i++) 
    {
        if ((int)word[i] != 32) // Exclude space characters (ASCII 32)
        {
            width += 18;  // Base width for each character
        }
    }

    // Scale the width by the height multiplier
    width = (width / 18) * height;

    return width;
}


int main() {
    struct DataRow *dataArray = (struct DataRow *)malloc(NUM_ROWS * sizeof(struct DataRow));  // Allocate memory for NUM_ROWS rows
    if (dataArray == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    // Read the font data from the file
    readFile("SingleStrokeFont.txt", dataArray, NUM_ROWS);
    
    
    // Ask the user for the height multiplier
    int height;
    do 
    {
        printf("Enter a height value (between 4 and 10): ");
        scanf("%d", &height);

        if (height < 4 || height > 10) 
        {
            printf("Scale is out of limits. Please enter a value between 4 and 10.\n");
        }
    } 
    while (height < 4 || height > 10);


    // Open the text file that contains words
    FILE *asciiFile = fopen("text.txt", "r");
    if (asciiFile == NULL) 
    {
        perror("Error opening text file");
        free(dataArray);
        exit(EXIT_FAILURE);
    }

    char word[100];  // Buffer to store a word (assuming words are not longer than 100 characters)

    //Initialise xOffset to 0
    double xOffset = 0.0;
    // Start Y-offset at height
    double yOffset = 0 - height;  
    
    // Read and process words one by one
    while (readNextWordFromFile(asciiFile, word)) 
    {
         // Calculate the width of the word
        int wordWidth = calculateWordWidth(word, height);

        if (xOffset + wordWidth > LINE_WIDTH) 
        {
            printf("Remaining width not enough\n");
            xOffset = 0.0; // Move to the next line
            yOffset -= ((36.0 / 18.0) * height );           //change here
        }   
        
        // Process each word
        processWord(dataArray, NUM_ROWS, word, height, &xOffset, yOffset);

        // Print the width of the word
        printf("The width of the word '%s' is: %d\n", word, wordWidth);
    }

    // Close the text file
    fclose(asciiFile);


    // Free the allocated memory
    free(dataArray);

    return 0;
}