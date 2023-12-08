//
// Created by ramon on 6/10/2023.
//

#ifndef SOCNETWORK2_STOP_WORDS_H
#define SOCNETWORK2_STOP_WORDS_H

#endif //SOCNETWORK2_STOP_WORDS_H

//char** read_stop_words_txt(char* filename);
void read_stop_words_txt(char* filename, hash_table_table *stopwords);
int is_a_stop_word(char* word,hash_table_table *stopwords);