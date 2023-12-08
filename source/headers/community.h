//
// Created by Feryjhon Bautista on 27/4/23.
//

#ifndef SOCNETWORK_COMMUNITY_H
#define SOCNETWORK_COMMUNITY_H

#endif //SOCNETWORK_COMMUNITY_H

#include "user.h"


#define MAX_FIELD_LENGTH 500
#define MAX_USERS 20

//STRUCTURES IN COMMUNITY
//Linked List of users
typedef struct user_list{
    User user;
    struct user_list *next_user; // Pointer to next user
    struct user_list *prev_user; // Pointer to previous use
    //struct user_list *request_list; //friend request list
}User_list;
//COMMUNITY
typedef struct{
    User_list* first_node;
    User_list* last_node;
    int current_size;
    int historic_size;
    int posts_number;
    int posts_capacity;
    Post* posts;
}Community;

//DATA HANDLING FUNCTIONS
/*This function is used for reading data from csv file in order to initialize the users*/
void read_csv(char* filename,Community *community);
/*This function is used for reading the posts from the csv file and adding the to the corresponding user*/
void read_posts_csv(char* filename,Community *community, hash_table_table *hash_table, hash_table_table *trendingtopics, hash_table_table *stopwords);
/*Loads the new data created in the execution about the users to the csv file of users*/
void write_csv(char* filename, Community community);
/*Loads the new data of posts created while the execution into the csv file of posts*/
void write_posts_csv(char* filename, Community community);

//USER HANDLING FUNCTIONS

/*Allows us to sing up in the social networks as a new user. It prepares a valid user to send it to the function add_new_user*/
User create_new_user(Community *community);
/*An error handling function to check the data of a new user created*/
int valid_username(char* username, Community community);
/*Ads a node to the community with the information of the new user*/
void add_new_user(User user, Community *community);
/*Prints all the users of the community*/
void print_community(Community community);
/*Initializes a node*/
void init_user_list(User_list *user_node);
/*Initializes the community*/
void init_community(Community *community);

//SEARCH FUNCTIONS
/*Search in the community for an specific node and returns a pointer to that node*/
User_list* linear_search(char* username, Community community);
/*Chooses a random user in the community and returns it*/
User random_user_search(Community community,int random_number);

//RANDOM REQUESTS. USES STACK
/*This function uses the stack to provide three random options that the user can use to send friend requests*/
void random_requests(Community *community,User_list *user);

//REQUEST FUNCTIONS
/*Displays the queue of requests so that the user can accept or decline the friendship*/
void manage_requests(User_list *user_node, Community community);
/*Validation of the request sent*/
int valid_send_request(char* name,User_list *sender, Community *community);
/*send a friend request to another user*/
void send_requests(User_list *sender, char* receiver_username, Community community);
/*Ads the user as friend for both users involved in the friendship*/
void add_friend(User_list* user1, User_list* user2);
/*checks if two users are already friends and returns true or false*/
int are_friends(User_list *user1, char *user2, Community* community);

//POST FUNCTIONS
/*Allows to introduce text as a post to the user, to the community, and it is processes into the hash table*/
void write_new_post(User_list *user, Community *community, hash_table_table *hash_table, hash_table_table *trendingtopics, hash_table_table *stopwords);
/*Adds the post to the corresponding structures*/
void add_post(User_list* user,Community* community, char content[], char time[]);
/*Uses the hash tables in order to see the ten most used words in the posts*/
void top_ten_words(hash_table_table *hash_table);
/*Function used to save the day and hour that a post was made*/
void calculate_time(char datetime[]);
/*Function made to display to the user the posts of his friends*/
void user_feed(Community *community, User_list *user);

//HASH TABLE FUNCTIONS
void words_to_hash(char post_content[], hash_table_table *frequentwords);
void words_to_hash_smart(char post_content[], hash_table_table *trending_topics, hash_table_table *stopwords);

//QUICKSORT FUNCTIONS
void Quicksort(hash_table_item **array, int inf, int sup);
int partition(hash_table_item **array, int low, int high);
void swap(hash_table_item **a, hash_table_item **b);

//FUNCTIONS FOR FREEING THE DYNAMIC ALLOCATED MEMORY
void delete_user_list(User_list *user_list);
void delete_community(Community *community);

