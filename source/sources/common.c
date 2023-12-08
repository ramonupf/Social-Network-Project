//
// Created by ramon on 05/05/2023.
//

#include "common.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>


void convertToLowercase(char* str) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] + 32;  //Convert uppercase to lowercase
        }
        i++;
    }
}

void remove_newline(char* str){
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';  // Replace newline with null terminator
    }
}

void remove_quotes(char* str) {
    size_t len = strlen(str);
    if (len >= 2 && str[0] == '"' && str[len - 1] == '"') {
        memmove(str, str + 1, len - 1);  // Shift the characters one position to the left
        str[len - 2] = '\0';  // Set the new null terminator
    }
}

void remove_final_dot(char* str){
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '.') {
        str[len - 1] = '\0';  // Replace newline with null terminator
    }
}

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}


#ifdef _WIN32 //WINDOWS
void setConsoleColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}
#else //MACINTOSH OR LINUX

void setConsoleColor(const char* color) {
    printf("%s", color);
}
#endif

void splash_screen() {
    setConsoleColor(COLOR_DARK_GREEN);

    printf("                                            888                                 \n");
    printf("                                            888                                 \n");
    printf("                                            888                                 \n");
    printf("  88888b.d88b.  888  888 88888b.   .d88b.   88888b.   .d88b.   8888b.   88888b.  \n");
    printf("  888  888  88b 888  888 888  88b d88P 88b  888   88b d8P  Y8b      88b 888  88b\n");
    printf("  888  888  888 888  888 888  888 888  888  888   888 88888888 .d888888 888  888\n");
    printf("  888  888  888 Y88b 888 888  888 Y88b 888  888  d88P Y8b      888  888 888  888\n");
    printf("  888  888  888  Y88888  888  888  Y888888  888P Y8888Y8888888888888888 888  888\n");
    printf("                                       888\n");
    printf("                                  Y8bd88P\n\n");

    printf("                MUNGBEAN: WHERE VEGANS AND VEGETARIANS CONNECT\n\n");

    setConsoleColor(COLOR_RESET);
}

void home_screen() {
    setConsoleColor(COLOR_DARK_GREEN);
    printf("  |  |               \n");
    printf("  |--| ,-. ;-.-. ,-. \n");
    printf("  |  | | | | | | |-' \n");
    printf("  '  ' `-' ' ' ' `-' \n");
    printf("\n");
    setConsoleColor(COLOR_RESET);
}

void login_screen() {
    setConsoleColor(COLOR_DARK_GREEN);

    printf("  ,                  \n");
    printf("  |            o     \n");
    printf("  |    ,-. ,-: . ;-. \n");
    printf("  |    | | | | | | | \n");
    printf("  `--' `-' `-| ' ' ' \n");
    printf("           `-'      \n");
    printf("\n");
    setConsoleColor(COLOR_RESET);
}

void register_screen() {
    setConsoleColor(COLOR_DARK_GREEN);

    printf("  ,-.                .           \n");
    printf("  |  )         o     |           \n");
    printf("  |-<  ,-. ,-: . ,-. |-  ,-. ;-. \n");
    printf("  |  \\ |-' | | | `-. |   |-' |   \n");
    printf("  '  ' `-' `-| ' `-' `-' `-' '   \n");
    printf("           `-'                   \n");
    printf("\n");
    setConsoleColor(COLOR_RESET);
}

void feed_screen(){
    setConsoleColor(COLOR_DARK_GREEN);
    printf("  ,--.           . \n");
    printf("  |              | \n");
    printf("  |-   ,-. ,-. ,-| \n");
    printf("  |    |-' |-' | | \n");
    printf("  '    `-' `-' `-' \n");
    printf("                   \n");
    printf("\n");
    setConsoleColor(COLOR_RESET);
}

void your_posts_screen(){
    setConsoleColor(COLOR_DARK_GREEN);
    printf("  .   ,                           .       \n");
    printf("   \\ /                            |\n");
    printf("    Y   ,-. . . ;-.   ;-. ,-. ,-. |-  ,-.\n");
    printf("    |   | | | | |     | | | | `-. |   `-.\n");
    printf("    '   `-' `-` '     |-' `-' `-' `-' `-'\n");
    printf("                      '                   \n");
    setConsoleColor(COLOR_RESET);
}

void friends_screen(){
    setConsoleColor(COLOR_DARK_GREEN);
    printf("  ,--.                 .     \n");
    printf("  |        o           |     \n");
    printf("  |-   ;-. . ,-. ;-. ,-| ,-. \n");
    printf("  |    |   | |-' | | | | `-. \n");
    printf("  '    '   ' `-' ' ' `-' `-' \n");
    printf("                             \n");
    setConsoleColor(COLOR_RESET);
}


void welcome_message(){
    printf("Welcome to the social network! You are now a ");
    setConsoleColor(COLOR_GREEN);
    printf("beta tester ");
    setConsoleColor(COLOR_RESET);
    printf("for Mug Bean.\n"); //welcoming message

}


void about_us_message(){
    printf("Welcome to Mung Bean, the vibrant social network designed exclusively for vegans and vegetarians worldwide!\n\n");
    printf("At Mung Bean, we believe that connecting with like-minded individuals is the key to fostering a thriving and"
           " compassionate community. Whether you're a seasoned vegan, a passionate vegetarian, or someone exploring the "
           "plant-based lifestyle, this is the perfect platform for you to meet, share, and grow together.\n\n");
    printf("Join us in celebrating the beauty of plant-based living, where compassion meets culinary creativity, and "
           "sustainable choices pave the way to a brighter future. Connect with fellow members who share your values, "
           "and embark on a journey of delicious flavors, ethical choices, and endless possibilities.\n\n");
    printf("Discover a multitude of vibrant profiles, each representing a unique story and perspective. Share your "
           "favorite recipes, culinary adventures, and tips for embracing a plant-powered lifestyle. From savory "
           "delights to decadent desserts, from healthful tips to conscious living, Mung Bean is your go-to destination "
           "for all things vegan and vegetarian.\n\n");
    printf("Engage in meaningful conversations, seek support, and celebrate the positive impact your choices make on "
           "the planet, animals, and your own well-being. Let's inspire and empower each other to make a difference, "
           "one delicious meal at a time.\n\n");
    printf("Whether you're here to seek knowledge, share experiences, or simply make new friends, Mung Bean welcomes you "
           "with open arms. Together, we can create a compassionate, inclusive, and thriving community that spreads the "
           "message of kindness and sustainability far and wide.\n\n");
    printf("Join Mung Bean today and let the world know that a compassionate lifestyle is not just a trend, but a way "
           "of life. Let's sow the seeds of change and watch them grow into a flourishing garden of compassion and "
           "connection.\n\n");
    printf("Remember, at Mung Bean, every connection has the power to change lives, including your own. So come on in, "
           "share your passion, and let's make this world a better place, one plate and one connection at a time.\n\n");
    printf("We're thrilled to have you as part of our growing Mung Bean family. Let's embark on this incredible journey "
           "together!\n\n");
    printf("With green and leafy regards,\n\n");
    setConsoleColor(COLOR_GREEN);
    printf("THE MUNG BEAN TEAM");
    setConsoleColor(COLOR_RESET);




}

void clear_screen(){
    #ifdef _WIN32
        Sleep(1000);
        system("cls"); //windows
    #else
        sleep(1);
        system("clear"); //mac
    #endif
}
void clear_screen_fast(){
    #ifdef _WIN32
    system("cls"); //windows
    #else
    system("clear"); //mac
    #endif
}



void enter_to_exit(){
    setConsoleColor(COLOR_DARK_GREEN);
    printf("\nPress Enter to exit\n");
    setConsoleColor(COLOR_RESET);
    getchar();
    clear_screen_fast();
}