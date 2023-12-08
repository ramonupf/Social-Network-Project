//
// Created by ramon on 6/10/2023.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "common.h"
#include "stop_words.h"


void read_stop_words_txt(char* filename, hash_table_table *stopwords) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file %s\n", filename);
    } else {
        char line[MAX_LINE_LENGTH];
        //Add all words from stop_words.txt to stopwords hash table
        while (fgets(line, MAX_LENGTH, fp) != NULL) {
            size_t len = strlen(line);
            if (len > 0 && line[len - 1] == '\n') {
                line[len - 1] = '\0';  // Replace newline with null terminator
            }
            //printf("line:%s\n", line);
            hash_table_insert(stopwords, line, "1");
        }
        //printf("Inserted stop words from txt to hash table size: %d capacity: %d\n", stopwords->count, stopwords->size); //DELETE

        fclose(fp);
    }
}

int is_a_stop_word(char* word,hash_table_table *stopwords){
    char *lookup = hash_table_search(stopwords, word);
    if (lookup != NULL){
        return TRUE;
    } else{
        return FALSE;
    }
}

