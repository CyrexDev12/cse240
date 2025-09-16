#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

/**
 * CODE: ok, this is a bit scary, it's very empty in here. DON'T PANIC! 
 *       You got this! What function always starts our program? 
 *       Can  you copy it from your last program?
 *       After that, maybe focus on getting input from the keyboard.
 *       Don't forget to review C's c-string library functions!
 *       
*/

// Globals
char vowels[] = {'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U', '\0'};
void translate_word(char *origWord, char *resultingWord);

bool First_contains_vowel(char *word) {
    for (int i = 0; vowels[i] != '\0'; ++i) {
        if (vowels[i] == word[0]) {
            return true;
        }
    }
    return false; 
}

bool isVowel(char c) {
    for (int i = 0; vowels[i] != '\0'; ++i) {
        if (vowels[i] == c) {
            return true;
        }
    }
    return false;
}

int const_clusterCount(const char *word) {
    int idx = 0; 

    while (word[idx] != '\0' && !isVowel(word[idx])) {
        idx++;
    }

    return idx;

}

void populateCons_cluster(char *dest, char *src, int count) {

    for (int i = 0; i < count; ++i) {
        dest[i] = src[i];
    }

    dest[count] = '\0';
}


void handle_constCase(char *word) {
    size_t n = strlen(word);
    int clustCount = const_clusterCount(word);
    char Con_clust[clustCount + 1];

    populateCons_cluster(Con_clust, word, clustCount);

    for (size_t i = 0; i < n; i++) {
        word[i] = word[i + clustCount];
    }

    strcat(word, Con_clust);

    
    word[n] = '\0'; // Add back
}


void translate_words(char *origWord, char *resultingWord) {
    const char *appVowell = "way";
    const char *appCons = "ay"; 
    size_t L = strlen(origWord); // Dynamically allocate length size 

    // strcpy(resultingWord, origWord); // Copy over to resulting

    // We need to go word by word using strtok

    char *buff = malloc(L + 1);
    memcpy(buff, origWord, L + 1);

    int c = 0; 
    char *words[100];

    char *token = strtok(buff, " ");
    while (token != NULL && c < 99) {
    words[c++] = token;
    token = strtok(NULL, " ");
    }
    words[c] = NULL; 


    
    for (int i = 0; words[i] != NULL; ++i) {
        size_t wlen = strlen(words[i]);
        char transformed[wlen + 4];

    strncpy(transformed, words[i], sizeof(transformed) - 1);
    transformed[sizeof(transformed) - 1] = '\0';

    if (First_contains_vowel(transformed)) {
        strncat(transformed, appVowell, sizeof(transformed) - strlen(transformed) - 1);
    } else {
        handle_constCase(transformed);
        strncat(transformed, appCons, sizeof(transformed) - strlen(transformed) - 1);
    }
 

    if (i > 0) {
        strcat(resultingWord, " "); // Add space if not first word
    }

     strcat(resultingWord, transformed); // Append the token
    }

    free(buff);

}

int main() {
    char *line = NULL;
    size_t len = 0; // Capacity of Buffer
    __ssize_t nread;

    printf("Enter a single word: ");

    nread = getline(&line, &len, stdin);
    if (nread == -1) {
        free(line);
        fprintf(stderr, "No input \n");
        return 1;
    }

    line[strcspn(line, "\r\n")] = '\0'; // Skip trailing new line

    size_t outCap = (size_t)nread * 3 + 32;
    char *result = malloc(outCap);
    result[0] = '\0'; // Set first character to NULL TERM

    translate_words(line, result);

    printf("\n");

    printf("Translated paragraphs: \n");
    printf("%s\n", result);

    free(line); // Release the buffer

    free(result);

    return 0; 
}

