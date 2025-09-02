#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_LINE_LEN 1024
#define MAX_WORD_LEN 100

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    char keyword[MAX_WORD_LEN];

    printf("Enter keyword to highlight: ");
    
    /**
     * CODE: Read a keyword from the user to highlight in the text file.
     */
    scanf("%s", keyword);
    
    FILE *file;
    /** CODE: open the file  */
    file = fopen(filename, "r");
    
    if (!file) {
        printf("Error opening file\n");
        return 1;
    }

    char line[MAX_LINE_LEN];

    /** CODE: Loop through each line of the file using fgets */
    while (fgets(line, sizeof(line), file) != NULL) {
        char result[MAX_LINE_LEN * 2] = "";  // reset for each line

        /** CODE: 
         * Loop through the line character by character and extract each word:
         *   - If the current character is a whitespace, copy it directly to result
         *   - If it's part of a word, extract the word (use an array to build it)
         *     - If it matches the keyword, append **word** to result
         *     - Else, append the word as-is
         */
        char word[200];
        size_t wlen = 0;

       for (size_t i = 0; line[i] != '\0'; i++) {
           int c = (unsigned char)line[i]; // Take the unsigned char val 

           int is_word_char = (c != 0) && (isalnum(c)); // isalnum determines if the int val is alphabetic 

           if (is_word_char) {
                if (wlen + 1 < sizeof(word)) {
                    word[wlen++] = (char) c;
                    word[wlen] = '\0';
                }
                continue; // Tell system to continue 
           }

           if (wlen > 0) {
            word[wlen] = '\0';
            
            if (strcmp(word, keyword) == 0) {
                strcat(result, "**");
                strcat(result, word);
                strcat(result, "**");
            } else {
                strcat(result, word); // Append as is 
            }
            wlen = 0; 
           }

            // Preserve boundary 
           size_t len = strlen(result); 
           if (len + 1 < sizeof(result)) {
                result[len] = (char) c;
                result[len + 1] = '\0';
           }
       }

        if (wlen > 0) {
        word[wlen] = '\0';
        if (strcmp(word, keyword) == 0) {
            strcat(result, "**"); strcat(result, word); strcat(result, "**");
        } else {
            strcat(result, word);
        }
        // add a space if you want to mimic earlier behavior
        // strcat(result, " ");
    }

        fputs(result, stdout);
    }

    fclose(file);
    return 0;
}
