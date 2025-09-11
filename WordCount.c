#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_INPUT 1000
#define MAX_WORDS 100
#define MAX_WORD_LENGTH 50

/** CODE: to_lowercase(char *str) 
 *          loops through the string and changes all values to lowercase
*/

void to_lowercase(char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (isupper((unsigned char)str[i])) {
            str[i] =(char) tolower((unsigned char)str[i]);
        }
    }
}

void remove_newLineAtEnd(char str[]) {
    size_t len = strlen(str);
    
    for (int i = 0; i < MAX_INPUT; i++) {
        if (len > 0 && str[len - 1] == '\n') {
            str[len - 1] = '\0';
        }
    }
}



/** CODE: find_word(char words[][MAX_WORD_LENGTH], int size, char *word) 
 *          search through all the words already found and see if a match occurs
 *          if a match is found return the index of the match
 *          if no match is found then return -1    
*/


int find_word(char words[][MAX_WORD_LENGTH], int size, char *word) {
  for (int i = 0; i < size; ++i) {
    if (strcmp(words[i], word) == 0){
        return i; 
    }
  }
  return -1; 

}

/** CODE: main 
 *          prompt for user to enter a sentence
 *          receive standard input using fgets into the input variable
 *          if the last character of input is a newline, then remove it
 *          use strtok to tokenize the input based on spaces (" ")
 *          while strtok finds a new word continue to loop through the words in the sentence
 *              call find_words
 *              if the return is -1 
 *                  copy the word to the words array and set the count = 1
 *              if the return is not -1
 *                  increase the counter at the found index
 *          print out all the counts for each word
*/
int main() {
    char input[MAX_INPUT];
    char found_words[MAX_WORDS][MAX_WORD_LENGTH];
    int counts[MAX_WORDS] = {0};
    int word_count = 0;
    
    /** CODE: here */
    printf("Enter a line of text: "); 

    fgets(input, MAX_INPUT, stdin); 
    remove_newLineAtEnd(input);
    to_lowercase(input);

    char *tok = strtok(input, " ");

    while (tok != NULL) {
        to_lowercase(tok);

        int idx = find_word(found_words, word_count, tok);

        if (idx == -1) {
            if (word_count < MAX_WORDS) {
                strncpy(found_words[word_count], tok, MAX_WORD_LENGTH - 1);
                found_words[word_count][MAX_WORD_LENGTH - 1] = '\0';
                counts[word_count] = 1; 
                word_count++;
            } else {
                fprintf(stderr, "Warning: reached MAX_WORDS limit; ignoring \"%s\"\n", tok);
            }

        } else {
            counts[idx]++;
        }

        tok = strtok(NULL, " ");
    }

        // Print results
        printf("Word Counts:\n");
    for (int i = 0; i < word_count; i++) {
        printf("%s: %d\n", found_words[i], counts[i]);
    }
    

    return 0;
}
