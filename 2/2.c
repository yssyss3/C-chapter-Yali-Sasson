#include <stdio.h>
#include <mem.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

void replaceFile (FILE * text, FILE* dict, FILE* out) ;
char* getAlt(FILE* dict, char* word);

int main(int argc, char** argv) {
    FILE* dict;
    FILE* text;
    FILE* out;

    srand(time(NULL));

    if(argc != 3){
        printf("Usage: 2.exe <text file> <dictionary file>\n");
        return 1;
    }

    text = fopen(argv[1], "r");
    if(text == NULL){
        printf("invalid text file\n");
        return 1;
    }

    dict= fopen(argv[2], "r");
    if(dict == NULL){
        printf("invalid dictionary file\n");
        fclose(text);
        return 1;
    }

    out = fopen("out.txt", "w");
    if(out == NULL){
        printf("error opening the output file");
        fclose(text);
        fclose(dict);
        return 1;
    }

    replaceFile(text, dict, out);

    fclose(dict);
    fclose(text);
    fclose(out);

    remove(argv[1]);
    rename("out.txt", argv[1]);

    return 0;
}

/*The function will read the input file word by word and change the words
 *in the output file according to the dictionary file*/
void replaceFile (FILE * text, FILE* dict, FILE* out) {
    char word[1024]; /*assuming a word is 1023 characters or shorter */
    while (fscanf(text, " %1023s", word) == 1) {
        char* alt = getAlt(dict, word);
        if(strcmp(alt,"") != 0){
            fprintf(out, "%s ", alt);
        }
        else {
            fprintf(out, "%s ", word);
        }
    }

}

/*the function will look for the given word in the dictionary
 * and will return an alternative word if found, or an empty
 * string if the word is not in the dictionary*/
char* getAlt(FILE* dict, char* word){
    char line[1024];
    char* firstWord;
    char* alts;
    char* altsArr[100]; /*assuming no more than a hundred alternative words */


    fseek(dict, SEEK_SET, 0);

    /*reading the dictionary line by line to find a matching word
     * the dictionary format is:
     * word1 alt1,alt2,alt3...*/
    while (fgets(line, 1024, dict) != NULL){
        if((firstWord = strtok(line, " ")) == NULL){
            fclose(dict);
            printf("ERROR: invalid format of the dictionary file\n");
            exit(1);
        }
        if(strcmp(firstWord,word) == 0){
            /*making a copy of the alts in case there is more than one option
             * so strtok will only change the copy and we keep the initial string */
            char*currentWord;
            char altscopy[1024];
            int altsNumber = 0;

            /*getting a string containing all alts int this format:
             * alt1,alt2,alt3...*/
            if((alts=strtok(NULL," ")) == NULL){
                fclose(dict);
                printf("ERROR: invalid format of the dictionary file\n");
                exit(1);
            }

            /*removing any useless characters from the end of the alternate word
             * like new lines and space */
            while(isalnum(alts[strlen(alts)-1]) == 0){
                alts[strlen(alts)-1] = 0;
            }

            strcpy(altscopy, alts);

            /*putting all options in array*/
            currentWord = strtok(altscopy,",");
            while(currentWord != NULL){
                altsArr[altsNumber] = (char*)(malloc(sizeof(char)*strlen(currentWord+1)));
                strcpy(altsArr[altsNumber], currentWord);
                altsNumber++;
                currentWord = strtok(NULL,",");
            }

            /*if Only one option then return it*/
            if(altsNumber != 0){
                int i;
                strcpy(alts,altsArr[rand()%altsNumber]);
                for(i = 0; i < altsNumber; i++){
                    free(altsArr[i]);
                }
            }
            return alts;
        }
    }
    return "";
}