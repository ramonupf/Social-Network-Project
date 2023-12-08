//
// Created by Feryjhon Bautista on 27/4/23.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#include "../headers/menu.h"


//Function to show the menu
void show_menu() {

    User_list *user_list = (User_list*)malloc(sizeof(User_list));//Initialize a list of users
    init_user_list(user_list);
    Community *community = (Community*)malloc(sizeof(Community));//Initialize a community
    init_community(community);

    hash_table_table *frequentwords = hash_table_new(); //Initialize hash table for frequent words
    hash_table_table *stopwords = hash_table_new(); //Initialize stopwords hash table
    hash_table_table *trendingtopics = hash_table_new(); //Initialize hash table for trending topics

    read_stop_words_txt("../resources/stop_words.txt", stopwords); //read stopwords from file

    int option = INVALID_OPTION; //start with invalid option to enter the loop
    while (option == INVALID_OPTION) {
        setConsoleColor(COLOR_BLUE);
        printf("Please choose an option:\n\n");
        setConsoleColor(COLOR_RESET);

        printf("%d. Start from scratch", NEW_START_DELETE);
        setConsoleColor(COLOR_RED);
        printf("[THIS WILL DELETE ALL YOUR PROGRESS]\n");
        setConsoleColor(COLOR_RESET);

        printf("ANY KEY. ");
        setConsoleColor(COLOR_GREEN);
        printf("Premium Memory Mode\n\n");
        setConsoleColor(COLOR_RESET);
        printf("%d. Quit\n\n", OPTION_QUIT);
        option = read_int_option("Type the option number:");
        if(option == NEW_START_DELETE){
            read_csv("../resources/memory_saving_aux.csv", community);
        } else{
            read_csv("../resources/memory_saving.csv", community);
            read_posts_csv("../resources/posts.csv", community, frequentwords, trendingtopics, stopwords);
        }

        setConsoleColor(COLOR_GREEN);
        printf("FILE LOADING SUCCESSFUL. STARTING SOCIAL NETWORK\n");
        setConsoleColor(COLOR_RESET);
        clear_screen();
    }

    while (option != OPTION_QUIT) {
        splash_screen();
        welcome_message();
        printf("\n");
        printf("%d. Register\n", OPTION_NEW);
        printf("%d. Login\n", OPTION_LOGIN);
        printf("%d. List existing users\n", OPTION_USERS);
        printf("%d. Top 10 most frequent words\n", OPTION_FREQUENT_WORDS);
        printf("%d. Top 10 trending topics\n", OPTION_TRENDING_TOPICS);
        printf("%d. About Us\n", OPTION_ABOUT_US);
        printf("%d. Quit\n", OPTION_QUIT);
        option = read_int_option("Choose an option:\n");

        clear_screen_fast();

        if (option == OPTION_QUIT) {
            // Delete all hash tables
            hash_table_delete_table(frequentwords);
            hash_table_delete_table(trendingtopics);
            hash_table_delete_table(stopwords);

            //Dump all data into their respective .csv files
            write_csv("../resources/memory_saving.csv",*community);
            write_posts_csv("../resources/posts.csv", *community);

            //Delete community
            delete_community(community);
        } else if (option == OPTION_NEW) {
            register_screen();
            User new_user = create_new_user(community);
            if(strcmp(new_user.username,"exit") != 0){
                add_new_user(new_user, community);
                setConsoleColor(COLOR_GREEN);
                printf("You have successfully registered.\n"
                       "Welcome to Mung Bean: the place where Vegans and Vegetarians connect");
                setConsoleColor(COLOR_RESET);
            }
            enter_to_exit();
        } else if (option == OPTION_USERS) {
            print_community(*community);
            enter_to_exit();
        } else if (option == OPTION_LOGIN) {
            login_screen();
            char* login_input = malloc(MAX_LENGTH * sizeof(char)); ;// = *read_char_option("Write your user name: ");
            printf("Write your username: ");
            scanf("%s", login_input); //Ask username
            convertToLowercase(login_input);
            // declare empty user_node*
            User_list* user_node;
            user_node = linear_search(login_input,*community); //SEARCH ALGORITHM
            if(user_node != NULL){
                clear_screen_fast();
                user_menu(user_node, community,frequentwords,stopwords,trendingtopics);//IF FOUND RETURN USER_LIST IF
            }
            else {
                setConsoleColor(COLOR_RED);
                printf("You are not a registered user, please register.\n");
                setConsoleColor(COLOR_RESET);
                clear_screen();
            }

        } else if (option == OPTION_FREQUENT_WORDS) {
            top_ten_words(frequentwords);
            enter_to_exit();
        } else if (option == OPTION_TRENDING_TOPICS) {
            top_ten_words(trendingtopics);
            enter_to_exit();
        }   else if (option == OPTION_ABOUT_US) {
            splash_screen();
            about_us_message();
            enter_to_exit();
        }
        else {
            printf("Invalid option!\n");
            enter_to_exit();
        }
    }
}
void user_menu(User_list* user, Community *community, hash_table_table *hash_table, hash_table_table *stopwords, hash_table_table *trendingtopics){

    int option = INVALID_OPTION;
    while (option != OPTION_QUIT) {
        printf("\n");

        home_screen();

        printf("What do you want to do?\n");
        printf("%d. Send friend requests\n", OPTION_SEND_REQUESTS);
        printf("%d. Look for three random friends\n", OPTION_RANDOM_REQUESTS);
        printf("%d. Manage pending requests\n", OPTION_MANAGE_REQUESTS);
        printf("%d. Make a new post\n", OPTION_MAKE_POST);
        printf("%d. List your posts\n", OPTION_LIST_POSTS);
        printf("%d. List your friends\n", OPTION_SEE_FRIENDS);
        printf("%d. See FEED\n", OPTION_FEED);
        printf("%d. Quit\n", OPTION_QUIT);
        option = read_int_option("Choose an option: \n");
        clear_screen_fast();

        if (option == OPTION_QUIT) {
            setConsoleColor(COLOR_BLUE);
            printf("You logged out.\n");
            setConsoleColor(COLOR_RESET);
            clear_screen();

            // Do nothing, it will exit the loop
        } else if (option == OPTION_SEND_REQUESTS) {
            char receiver_username[MAX_LENGTH];
            printf("Write the username: ");
            scanf("%s", receiver_username); //SCANF TO ASK USERNAME
            //ERROR HANDLING FOR NOT ADDING ONESELF AS FRIEND OR TWO TIMES THE SAME PERSON
            int try = valid_send_request(receiver_username, user, community);
            while(try==ERROR){
                printf("Rewrite the username of the person you want to send a friend request to:");
                scanf("%s", receiver_username);
                try = valid_send_request(receiver_username, user, community);
                //send_requests(user,receiver_username,*community);
            }
            send_requests(user,receiver_username,*community);
            enter_to_exit();
        }else if (option == OPTION_RANDOM_REQUESTS){
            random_requests(community, user);
            enter_to_exit();
        }else if (option == OPTION_MANAGE_REQUESTS) {
            manage_requests(user, *community);
            enter_to_exit();
        } else if (option == OPTION_MAKE_POST) {
            write_new_post(user, community, hash_table, trendingtopics, stopwords);
            //enter_to_exit();
        } else if (option == OPTION_LIST_POSTS) {
            your_posts_screen();
            print_posts(user->user);
            enter_to_exit();
        } else if (option == OPTION_SEE_FRIENDS) {
            friends_screen();
            if (user->user.friends_number <= 0) {
                printf("You don't have friends yet\n");
            } else {
                for (int j = 0; j < user->user.friends_number; j++) {
                    printf("%s \n", user->user.friends_of_user[j]);
                }
            }
            enter_to_exit();
        } else if (option == OPTION_FEED) {
            feed_screen();
            user_feed(community,user);
            enter_to_exit();
        }else {
            printf("Invalid option!\n");
            enter_to_exit();
        }

    }
}