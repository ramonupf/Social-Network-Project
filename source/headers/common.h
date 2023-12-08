//
// Created by Feryjhon Bautista on 2/5/23.
//

#include "hash_table.h"

#ifndef SOCNETWORK_COMMON_H
#define SOCNETWORK_COMMON_H

#endif //SOCNETWORK_COMMON_H

#define TRUE 1
#define FALSE 0

//MAIN MENU OPTIONS
#define OPTION_NEW 1
#define OPTION_LOGIN 2
#define OPTION_USERS 3
#define OPTION_FREQUENT_WORDS 4
#define OPTION_TRENDING_TOPICS 5
#define OPTION_ABOUT_US 6
#define OPTION_QUIT 0
#define NEW_START_DELETE 100


//USER MENU OPTIONS
#define OPTION_SEND_REQUESTS 1
#define OPTION_RANDOM_REQUESTS 2
#define OPTION_MANAGE_REQUESTS 3
#define OPTION_MAKE_POST 4
#define OPTION_LIST_POSTS 5
#define OPTION_SEE_FRIENDS 6
#define OPTION_FEED 7

#define SUCCESS 1

//ERROR definition conflict with windows.h
#ifndef _WIN32
#define ERROR -1
#endif

#define INVALID_OPTION -3

#define MAX_LENGTH 100 //multiple lengths
#define MAX_POST_LENGTH 160
#define MAX_SIZE 5
#define MAX_LINE_LENGTH 1000

#define INITIAL_FRIENDS 2


#define MAX_SIZE_STACK 3

#define DATE_TIME_LENGTH 20
#define FOUND 1
#define NOT_FOUND 0

//INTERFACE DEFINITIONS
//For Windows
#ifdef _WIN32
#include <windows.h>
#define COLOR_GREEN 10
#define COLOR_DARK_GREEN 2
#define COLOR_LIME_GREEN 46
#define COLOR_FOREST_GREEN 34
#define COLOR_SEA_GREEN 29
#define COLOR_RESET 7
#define COLOR_RED 12
#define COLOR_LIGHT_RED 12
#define COLOR_DARK_RED 4
#define COLOR_CRIMSON 196
#define COLOR_MAROON 52
#define COLOR_SALMON 207
#define COLOR_BLUE 9
#define COLOR_YELLOW 14
#else
//For Mac/UNIX based systems

#define COLOR_GREEN "\033[1;32m"
#define COLOR_LIGHT_GREEN "\033[1;92m"
#define COLOR_DARK_GREEN "\033[0;32m"
#define COLOR_LIME_GREEN "\033[38;5;46m"
#define COLOR_FOREST_GREEN "\033[38;5;22m"
#define COLOR_SEA_GREEN "\033[38;5;29m"
#define COLOR_RESET "\033[0m"
#define COLOR_RED "\033[1;31m"
#define COLOR_LIGHT_RED "\033[1;91m"
#define COLOR_DARK_RED "\033[0;31m"
#define COLOR_CRIMSON "\033[38;5;196m"
#define COLOR_MAROON "\033[38;5;52m"
#define COLOR_SALMON "\033[38;5;9m"
#define COLOR_BLUE "\033[38;5;21m"
#define COLOR_YELLOW 14
#define COLOR_LIGHT_YELLOW 14

#endif

//MISC FUNCTIONS
void convertToLowercase(char* str);
void remove_newline(char* str);
void remove_quotes(char* str);
void remove_final_dot(char* str);
void clear_input_buffer();


//INTERFACE FUNCTIONS

void splash_screen();
void clear_screen();
void clear_screen_fast();
void enter_to_exit();
void home_screen();
void login_screen();
void register_screen();
void welcome_message();
void your_posts_screen();
void feed_screen();
void friends_screen();
void about_us_message();

//System specific
#ifdef _WIN32
void setConsoleColor(int color);
#else
void setConsoleColor(const char* color);
#endif
