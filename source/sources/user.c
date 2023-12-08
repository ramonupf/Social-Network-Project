//
// Created by Feryjhon Bautista on 27/4/23.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../headers/user.h"
#include "../headers/utils.h"


//initialize user
void init_user(User* user){
    user->requests.num_requests = 0;
    user->friends_capacity = 2;
    user->friends_number = 0;
    //initialize dynamic array of friends
    user->friends_of_user = (char**)malloc(user->friends_capacity*sizeof(char*));
    for(int i = 0; i<user->friends_capacity; i++){
        user->friends_of_user[i] = (char*)malloc(MAX_LENGTH*sizeof(char));
        strcpy(user->friends_of_user[i],"");
    }
    user->posts_capacity = 0; //0 or 1??
    user->posts_number = 0;
    //initialize dynamic array of posts
    //user->user_posts = (char**)malloc(user->posts_capacity*sizeof(char*));
    user->user_posts = malloc(user->posts_capacity * sizeof(Post)); //MALLOC OF O? THEN THE NEXT FOR WORKS?
    for(int i = 0; i<user->posts_capacity; i++){
        printf("init for malloc of content works :)\n"); //PD: DOESN'T WORK
        user->user_posts[i].content = (char*)malloc(MAX_POST_LENGTH*sizeof(char));
        strcpy(user->user_posts[i].content,"");
    }
    //initialize queue of requests
    init_queue(&user->requests);
}
//print user
void print_user(User user){
    printf("\nUserName: %s. Birth Year: %d. Email: %s. Location: %s. USER_ID: %d. \n", user.username, user.birth_year,user.email, user.location, user.user_id);
    printf("Tastes: ");
    for (int i = 0; i < MAX_SIZE; i++){
        printf("%s", user.tastes[i]);
        if(i < MAX_SIZE-1) printf(", ");
    }
    printf(". ");
    printf("Friends: ");
    for(int j = 0; j<user.friends_number;j++){
        printf("%s ", user.friends_of_user[j]);
    }
}

//POST FUNCTIONS
void print_post(Post post){
    printf("@%s said at %s:\n   ",post.username, post.datetime);
    printf("%s\n", post.content);
}

void print_posts(User user){
    printf("Posts:\n");
    for(int j = 0; j<user.posts_number;j++){
        printf("@%s said at %s:\n   ",user.username, user.user_posts[j].datetime);
        printf("%s\n", user.user_posts[j].content);
    }
}

void init_post(Post *post){

    post->content = (char*)malloc(MAX_POST_LENGTH*sizeof(char));
}

void delete_user(User *user){
    for (int i = 0; i <user->posts_capacity;i++){
            free_post(&user->user_posts[i]);
    }
    delete_friends(user->friends_of_user, user->friends_capacity);
}


void free_post(Post* post) {
    if (post == NULL) {
        return;
    }
    free(post->content);
}


void delete_friends(char** friends_of_user,int friends_capacity){
    for(int i = 0; i< friends_capacity;i++){
            free(friends_of_user[i]);
    }
}

//STACK FUNCTIONS
void init_stack(Stack* stack){
    stack->users = (User*)malloc(3*sizeof(User));
    stack->top = -1;
}
int is_empty(Stack stack) {
    if (stack.top < 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}
int is_full(Stack stack){
    if (stack.top == MAX_SIZE_STACK - 1){
        return TRUE;
    } else {
        return FALSE;
    }
} //not used but may need in the future
User top(Stack stack){
    if (!is_empty(stack)){
        return stack.users[stack.top];
    } else{
        User empty;
        init_user(&empty);
        return empty;
    }
}
void pop(Stack* stack){
    if (stack->top >= 0) stack->top -= 1;
}
void push(Stack* stack, User user){
    stack->top +=1;
    stack->users[stack->top] = user;
}



//QUEUE FUNCTIONS
void init_queue(Requests* requests){
    requests->first_request = NULL;
    requests->last_request = NULL;
    requests->num_requests = 0;
}
void dequeue(Requests* requests){
    if (is_empty_queue(*requests) == TRUE) {
        printf("No one wants to be your friend :(.");
    } else {
        requests->first_request = requests->first_request->next_request;
        requests->num_requests = requests->num_requests - 1;
        if(requests->num_requests==1){
            requests->last_request = requests->first_request;
        }
    }
}
void enqueue(Requests* requests, Node_request* request){
    if(requests->num_requests==0){
        requests->first_request = request;
        requests->last_request = request;
        requests->first_request->next_request = NULL;
        requests->num_requests = 1;
    } else {
        requests->last_request->next_request = request;
        requests->last_request = requests->last_request->next_request;
        requests->num_requests++;
    }
}
int is_empty_queue(Requests requests){
    if(requests.num_requests <= 0) return TRUE;
    return FALSE;
}
char* first_queue(Requests requests){
    if(is_empty_queue(requests)){
        return NULL;
    }else{
        return requests.first_request->name;
    }
}



