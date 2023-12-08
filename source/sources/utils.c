//
// Created by Feryjhon Bautista on 2/5/23.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/utils.h"
#include "../headers/common.h"



void flush_input() {
    char c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

int read_int_option(const char* msg) {
    int option = INVALID_OPTION;
    printf("%s", msg);
    scanf("%d", &option);
    flush_input();
    return option;
}

char read_char_option(const char* msg) {
    char option = '\0';
    printf("%s", msg);
    scanf("%c", &option);
    flush_input();
    return option;
}



