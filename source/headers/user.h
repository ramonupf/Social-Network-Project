//
// Created by Feryjhon Bautista on 27/4/23.
//

#ifndef SOCNETWORK_USER_H
#define SOCNETWORK_USER_H

#endif //SOCNETWORK_USER_H

#include <string.h>
#include "../headers/common.h"

//Linked List of requests
typedef struct node_request{
    char name[MAX_LENGTH];
    struct node_request *next_request; // Pointer to next user
}Node_request;

typedef struct{
    Node_request* first_request;
    Node_request* last_request;
    int num_requests;
}Requests;

//Data structure for a post
typedef struct {
    char username[MAX_LENGTH];
    char datetime[DATE_TIME_LENGTH];
    char* content;
} Post;

typedef struct{
    char username[MAX_LENGTH];
    int birth_year;
    char email[MAX_LENGTH];
    char location[MAX_LENGTH];
    int user_id;
    char tastes[MAX_SIZE][MAX_LENGTH];
    Requests requests;
    //USER FRIENDS
    int friends_number;
    int friends_capacity;
    char** friends_of_user;
    //USER POSTS
    int posts_number;
    int posts_capacity;
    //char** user_posts;
    Post* user_posts;
}User;

//stack of users to add unknown friends
typedef struct{
    User* users;
    int top;
}Stack;


void modify_user(User* user); //??????
void print_user(User user);
void delete_user(User *user);
void delete_friends(char** friends_of_user,int friends_capacity);

//POST FUNCTIONS
void print_post(Post post);
void print_posts(User user);
void free_post(Post* post);

//STACK FUNCTIONS
void delete_stack(Stack* stack);
void init_stack(Stack* stack);
int is_full(Stack stack); //??????
int is_empty(Stack stack);
User top(Stack stack);
void pop(Stack* stack);
void push(Stack* stack, User user);


//QUEUE AND REQUESTS FUNCTIONS
void init_queue(Requests* requests);
void dequeue(Requests* requests);
void enqueue(Requests* requests, Node_request* request);
int is_empty_queue(Requests requests);
char* first_queue(Requests requests);
void init_user(User* user);
void init_post(Post* post);

