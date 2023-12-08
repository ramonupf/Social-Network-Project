

//
// Created by Feryjhon Bautista on 27/4/23.
//

#include "../headers/community.h"
#include "stop_words.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void init_user_list(User_list *node){
    node->next_user = NULL;
    node->prev_user = NULL;
}

void init_community(Community *community){
    //WE SET THE VARIABLES TO INITIAL VALUES AND WE ALLOCATE MEMORY FOR THE DYNAMIC DATA STRUCTURES
    community->first_node = NULL;
    community->last_node = NULL;
    community->historic_size = 0;
    community->current_size = 0;
    community->posts_number = 0;
    community->posts_capacity = 2;
    community->posts = (Post*)malloc(community->posts_capacity*sizeof(Post));
    for(int i = 0; i<community->posts_capacity; i++){
        community->posts[i].content = (char*)malloc(MAX_LENGTH*sizeof(char));
        strcpy(community->posts[i].content,"");
    }
}

int valid_username(char* username, Community community) {
    //WE SEARCH IF THAT USERRNAME IS ALREADY USED
    User_list *aux = linear_search(username, community); // search for the user in the community with the same name
    if (aux != NULL) {
        return FALSE; //IS NOT AVAILABLE
    }
    return TRUE; //IS AVAILABLE
}

User create_new_user(Community *community){
    User aux;
    init_user(&aux);

    //Read username
    printf("Enter your username (Type 'exit' to cancel registering):\n");
    char username[MAX_LENGTH];
    scanf("%s", username);
    remove_newline(username); //TAKES OUT THE CHARCATER THAT MAKES THE NEW LINE "\n"
    convertToLowercase(username);

    //To cancel registration
    if(strcmp(username,"exit")==0){
        strcpy(aux.username,username);
        return aux;
    }
    //Check if username is valid
    int test = valid_username(username, *community);
    while (test == FALSE) {
        setConsoleColor(COLOR_RED);
        printf("Invalid username. Please enter a different username:\n");
        setConsoleColor(COLOR_RESET);
        scanf("%s", username);
        remove_newline(username);
        convertToLowercase(username);

        //To cancel registration
        if(strcmp(username,"exit")==0){
            strcpy(aux.username,username);
            return aux;
        }
        test = valid_username(username, *community);
    }
    //Once username is valid add it to our aux user
    strcpy(aux.username,username);

    //Read birthyear
    int birthyear;
    printf("Enter your birth year:\n");
    //WE CHECK IF THE USER ENTERS AN INTEGER, IF NOT WE MAKE HIM DO IT AGAIN
    test = FALSE;
    while(test == FALSE){
        if(scanf("%d", &birthyear)==1 && birthyear > 0){
            test = TRUE;
        } else {
            printf("Invalid input, enter a valid year: ");
            while (getchar() != '\n'); //We remove the buffer
        }
    }
    //Once birthyear is valid add it to our aux user
    aux.birth_year = birthyear;
    //Read email
    printf("Enter your email:\n");
    scanf("%s", aux.email);
    //Read location
    printf("Enter your location:\n");
    scanf("%s",aux.location);
    aux.user_id = 0;
    while (getchar() != '\n'); //Clear the input buffer for next fgets
    //Read 5 tastes
    printf("Enter 5 tastes:\n");
    char user_input[MAX_LENGTH];
    for(int j=0;j<MAX_SIZE;j++){
        char temp;
        fgets(user_input,MAX_LENGTH,stdin);
        remove_newline(user_input);
        strcpy(aux.tastes[j],user_input);
    }
    return aux; //RETURNS THE USER VARIABLE
}

void add_new_user(User user, Community *community) {
    //this node will be the one that will be added to our linked list (to our community).
    // We have to allocate memory for the new node and also initialise it.
    // This function gets the data of the user that we want to add, so we assign those values to the node.
    User_list *new_node = (User_list *) malloc(sizeof(User_list));
    init_user_list(new_node);
    new_node->user = user;
    init_user(&new_node->user); //added init_user 02/06/23. This was the main problem that caused everyone to have the same friend list
    new_node->user.user_id = community->historic_size + 1; //we give that user the corresponding user_id.
    if (community->first_node == NULL) { //check if there is no one added yet, if there is no one we initialize our community declaring the first node as the head and the tail
        community->first_node = new_node;
        community->last_node = new_node;
    } else { //if there were users added we add the node to the final of the linked list
        community->last_node->next_user = new_node;
        community->last_node = new_node;
    }
    //as we added a user we update the size of our list
    community->current_size++;
    community->historic_size++;
}

void print_community(Community community){
    //we create a pointer to a node of the list in order to iterate through it. It starts being the first element of the list
    User_list* temp = community.first_node;
    int i = 0;
    while(temp != NULL){ //the condition to iterate is until it gets to an element which does not exist, meaning that it got to the final of the list
        if(i%2 == 0){
            setConsoleColor(COLOR_DARK_GREEN);
        } else{
            setConsoleColor(COLOR_YELLOW);
        }
        print_user(temp->user); //we print the data of the current user
        temp = temp->next_user; //we change to the next pointer
        i++;
    }
    setConsoleColor(COLOR_RESET);
}

void read_csv(char* filename,Community *community) {
    printf("Loading user data...\n");
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file %s\n", filename);
        return; //end function if there was a reading error
    }
    char line[MAX_LINE_LENGTH];
    User aux_user; //create aux user
    init_user(&aux_user);//init user
    int i = 0;
    fgets(line, MAX_LINE_LENGTH, fp); //line of headers
    fgets(line,MAX_LINE_LENGTH,fp); //line containing the number of users
    char* field = strtok(line,"\"");
    int user_number = atoi(field);
    while (i < user_number) {
        fgets(line, MAX_LINE_LENGTH, fp);
        if (strlen(line) <= 1) {  // skip empty lines
            continue;
        }
        field = strtok(line, ",\""); //USERNAME
        strcpy(aux_user.username, field);

        field = strtok(NULL, ",\""); //BIRTH YEAR
        aux_user.birth_year = atoi(field);

        field = strtok(NULL, ",\""); //EMAIL
        strcpy(aux_user.email, field);

        field = strtok(NULL, ",\""); //LOCATION
        strcpy(aux_user.location, field);

        field = strtok(NULL,""); //TASTES

        char *sub_field = strtok(field, ",\"");

        for(int j=0;j<MAX_SIZE;j++){
            if(j==MAX_SIZE-1){
                sub_field = strtok(NULL, ",\"");
                strcpy(aux_user.tastes[j],sub_field);
            } else if (j==0){
                strcpy(aux_user.tastes[j],sub_field);
            } else{
                sub_field = strtok(NULL, ",");
                strcpy(aux_user.tastes[j],sub_field);
            }
        }
        add_new_user(aux_user,community);
        i++;
    }
    fclose(fp);
    printf("User data successfully loaded.\n\n");
    //NOW WE CAN IMPORT THE FRIENDS AND THE REQUESTS
    printf("Loading friendship data...\n");
    fp = fopen(filename, "r");
    i = 0;
    fgets(line, MAX_LINE_LENGTH, fp); //first line
    fgets(line, MAX_LINE_LENGTH, fp); //second line
    while(i<community->current_size){
        fgets(line, MAX_LINE_LENGTH, fp);
        if (strlen(line) <= 1) {  // skip empty lines
            continue;
        }
        field = strtok(line, ",\""); //USERNAME
        char* username = field;
        field = strtok(NULL, ",\""); //SKIP BIRTH YEAR
        field = strtok(NULL, ",\""); //SKIP EMAIL
        field = strtok(NULL, ",\""); //SKIP LOCATION
        field = strtok(NULL,""); //SKIP TASTES
        char *sub_field = strtok(field, ",\"");

        for(int j=0;j<MAX_SIZE;j++){
            if(j==MAX_SIZE-1){
                sub_field = strtok(NULL, ",\"");
            } else if (j==0){
            } else{
                sub_field = strtok(NULL, ",");
            }
        }
        field = strtok(NULL, ",\""); //FRIENDS NUMBER

        int friends_number = atoi(field);

        User_list* aux_user_node;
        aux_user_node = linear_search(username,*community);
        User_list* aux_user_node_friend;

        if(friends_number>=1){
            field = strtok(NULL,""); //FRIENDS
            sub_field = strtok(field, ",\"");
            for(int j=0; j<friends_number;j++){
                if(j == 0){ //if it is the first one
                    aux_user_node_friend = linear_search(sub_field, *community);
                    add_friend(aux_user_node, aux_user_node_friend);
                } else if(j==friends_number-1){ //if it is the last one
                    sub_field = strtok(NULL, ",\"");
                    aux_user_node_friend = linear_search(sub_field, *community);
                    add_friend(aux_user_node, aux_user_node_friend);
                } else{ //if it is one of the middle ones
                    sub_field = strtok(NULL, ",");
                    aux_user_node_friend = linear_search(sub_field, *community);
                    add_friend(aux_user_node, aux_user_node_friend);
                }
            }
             //REQUESTS NUMBER.
            field = strtok(NULL, ",\"");
        } else{
            field = strtok(NULL, ",\"");
        }

        //READ and add to the user their pending friend requests
        int requests_number = 0;
        requests_number = atoi(field);
        if(requests_number>0) printf("Loading saved requests of %s...\n",username);
        User_list* aux_user_node_sender;
        if(requests_number == 1){
            field = strtok(NULL, ",");
            remove_newline(field);
            remove_quotes(field);
            aux_user_node_sender = linear_search(field, *community);
            printf("[%s] ",aux_user_node_sender->user.username);
            send_requests(aux_user_node_sender,username,*community);
        }else if(requests_number > 1){
            field = strtok(NULL, ""); //REQUESTS
            sub_field = strtok(field, ",\"");
            for(int j=0; j<requests_number;j++){
                if(j == 0){ //if it is the first one
                    aux_user_node_sender = linear_search(sub_field, *community);
                    printf("[%s] ",aux_user_node_sender->user.username);
                    send_requests(aux_user_node_sender,aux_user_node->user.username,*community);
                } else if(j==requests_number-1){ //if it is the last one
                    sub_field = strtok(NULL, ",\"");
                    aux_user_node_sender = linear_search(sub_field, *community);
                    printf("[%s] ",aux_user_node_sender->user.username);
                    send_requests(aux_user_node_sender,aux_user_node->user.username,*community);
                } else{ //if it is one of the middle ones
                    sub_field = strtok(NULL, ",");
                    aux_user_node_sender = linear_search(sub_field, *community);
                    printf("[%s] ",aux_user_node_sender->user.username);
                    send_requests(aux_user_node_sender,aux_user_node->user.username,*community);
                }
            }
        }
        i++;
    }
    printf("Friendship data successfully loaded. \n\n ");
    fclose(fp);
}

void read_posts_csv(char* filename,Community *community, hash_table_table *hash_table, hash_table_table *trendingtopics, hash_table_table *stopwords) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error opening file %s\n", filename);
        return; //end function if there was a reading error
    }
    char line[MAX_LINE_LENGTH];
    char username[MAX_LENGTH];
    char post[MAX_POST_LENGTH];
    char datetime[MAX_LENGTH];
    User_list* aux_user_node;

    int i = 0;
    fgets(line, MAX_LINE_LENGTH, fp); //skip line of headers
    fgets(line, MAX_LINE_LENGTH, fp); //skip line containing the number of posts
    char *field = strtok(line, "\"");
    int posts_number = atoi(field);
    while (i < posts_number) {
        fgets(line, MAX_LINE_LENGTH, fp);
        if (strlen(line) <= 1) {  // skip empty lines
            continue;
        }
        field = strtok(line, ",\""); //USERNAME
        strcpy(username, field);
        aux_user_node = linear_search(username,*community);

        field = strtok(NULL, ",\""); //TIME
        strcpy(datetime, field);

        field = strtok(NULL, "\""); //POST
        field = strtok(NULL, "\"");
        remove_newline(field);
        strcpy(post, field);
        //WE CALL THE HASH FUNCTIONS TO CREATE THE TENDING TOPICS
        words_to_hash(post,hash_table);
        words_to_hash_smart(post, trendingtopics,stopwords);
        add_post(aux_user_node, community, post, datetime);
        i++;
    }
}

void write_csv(char* filename, Community community){
    FILE* fp = fopen(filename, "w+"); // Open the file in write mode
    if (fp == NULL) {
        printf("Error opening file %s\n", filename);
        return; //End the function if there was a reading error
    }
    //Write the header line of the CSV file
    fprintf(fp, "\"username\",\"birthyear\",\"email\",\"location\",\"tastes\",\"friends_number\",\"friends_of_user\",\"requests_number\",\"requests_of_user\"\n");
    //Write the total number of users in the community
    fprintf(fp,"\"%d\"\n",community.current_size);
    //Iterate through users of the community
    int i = 0;
    User_list* aux = community.first_node;
    while(i < community.current_size){
        //Initialize auxiliary variables for storing tastes, friends, and requests
        char aux_tastes[200] = "";
        char aux_friends[1000] = "";
        char aux_requests[1000] = "";
        //Append all tastes of the user into a single string, separated by commas
        for(int j = 0; j < 5; j++){
            strcat(aux_tastes, aux->user.tastes[j]);
            if(j != 4){
                strcat(aux_tastes, ",");
            }
        }
        //Append all friends of the user into a single string, separated by commas
        for(int j = 0; j < aux->user.friends_number; j++){
            strcat(aux_friends, aux->user.friends_of_user[j]);
            if(j != aux->user.friends_number - 1){
                strcat(aux_friends, ",");
            }
        }
        //Append all requests of the user into a single string, separated by commas
        int num_requests = aux->user.requests.num_requests;
        if(num_requests == 1){
            strcpy(aux_requests, aux->user.requests.first_request->name);
        } else{
            for(int j = 0; j < num_requests; j++){
                strcat(aux_requests, aux->user.requests.first_request->name);
                if(j != num_requests - 1){
                    strcat(aux_requests, ",");
                }
                dequeue(&aux->user.requests);
            }
        }
        //Write the user information to the CSV file
        fprintf(fp, "\"%s\",\"%d\",\"%s\",\"%s\",\"%s\",\"%d\",\"%s\",\"%d\",\"%s\"\n",
                aux->user.username, aux->user.birth_year, aux->user.email, aux->user.location, aux_tastes,
                aux->user.friends_number, aux_friends, num_requests, aux_requests);
        aux = aux->next_user; //Move to the next user
        i++; //Increment the iterator
    }
    fclose(fp); //Close the file
}

void write_posts_csv(char* filename, Community community){
    FILE* fp = fopen(filename, "w+"); //Open the file in write mode
    if (fp == NULL) {
        printf("Error opening file %s\n", filename);
        return; //End the function if there was a reading error
    }
    //Write the header line of the CSV file
    fprintf(fp, "\"username\",\"datetime\",\"content\"\n");
    //Write the total number of posts in the community
    fprintf(fp,"\"%d\"\n", community.posts_number);
    //Iterate through the posts of the global array in the community
    for(int i = 0; i < community.posts_number; i++){
        //Write the post information to the CSV file
        fprintf(fp, "\"%s\",\"%s\",\"%s\"\n", community.posts[i].username, community.posts[i].datetime, community.posts[i].content);
    }
    fclose(fp); //Close the file
}


User_list* linear_search(char* user_name, Community community){
    User_list* temp = community.first_node; //This is like our iterator
    while(temp != NULL){
        if(strcmp(user_name,temp->user.username) == 0) {
            return temp;//When it finds the user it returns it
        }
        temp = temp->next_user; //Change to the next node of the linked list
    }
    return NULL;
}

User random_user_search(Community community,int random_number){
    User_list* temp = community.first_node;
    int i = 0;
    //we create a pointer to a node of the list in order to iterate through it. It starts being the first element of the list
    while(i < random_number && temp != NULL) {
        temp = temp->next_user; //we change to the next pointer
        ++i;
    }
    return temp->user;
}

void manage_requests(User_list *user_node, Community community){
    printf("You have %d pending requests.\n",user_node->user.requests.num_requests);
    int keep = TRUE;
    if(is_empty_queue(user_node->user.requests)){
        printf("You have no pending requests.\n");
    } else{
        while(keep == TRUE && is_empty_queue(user_node->user.requests) == FALSE){
            char option[MAX_LENGTH];
            char name_friend[MAX_LENGTH];
            strcpy(name_friend, first_queue(user_node->user.requests));
            printf("%s wants to be your friend, do you accept the friendship?\n",name_friend); //first_queue(user->requests)
            printf("Write [A] to accept the request, [D] to decline, anything else to stop.\n");
            scanf("%s", &option);
            if(strcmp(option,"A")==0){ //ACCEPT REQUEST
                if (first_queue(user_node->user.requests) != NULL){
                    User_list* other_user = linear_search(first_queue(user_node->user.requests), community);//As the users accepts we must add the friend to this user but also this user as friend of the other user.
                    add_friend(user_node, other_user); //We add them mutually
                    dequeue(&user_node->user.requests); //we delete the user from the queue
                }
            } else if (strcmp(option, "D") == 0){ //DECLINE REQUEST
                dequeue(&user_node->user.requests);
            } else{//QUIT
                keep = FALSE;
            }
        }
    }
}

int valid_send_request(char* name,User_list *sender, Community *community){
    if(linear_search(name,*community)==NULL){
        printf("The user doesn't exist.\n");
        return ERROR;
    }
    if(strcmp(name, sender->user.username) == 0){
        printf("You cannot add yourself as a friend.\n");//if the name of the sender is the same that his own name there is an error
        return ERROR;
    }
    else{
        for (int i = 0; i< sender->user.friends_number;i++){
            if(strcmp(name, sender->user.friends_of_user[i]) == 0){
                printf("This user is already your friend.\n");
                return ERROR; //if the sender is already friend of the user he wants to add there is Error
            }
        }
    }
    return TRUE;
}


void send_requests(User_list *sender, char* receiver_username, Community community){
    User_list* receiver = (User_list*) malloc(sizeof(User_list));
    init_user_list(receiver);
    receiver = linear_search(receiver_username, community);

    if (receiver == NULL){
        printf("This user is not registered in the network.\n");
    }
    else {
        Node_request *aux = (Node_request*)malloc(sizeof(Node_request));
        aux->next_request = NULL;
        strcpy(aux->name, sender->user.username);
        enqueue(&receiver->user.requests, aux); //we add the user request to the queue of the used that said the acting user
        printf("You have successfully sent a request to %s.\n", receiver->user.username);
    }
}

void add_friend(User_list* user1, User_list* user2){
    //First we check if these two users are already friends
    for(int i=0; i<user1->user.friends_number;i++){
        if(strcmp(user1->user.friends_of_user[i], user2->user.username)==0) return;
    }

    //Check if we have space for user1 to add friends, if not reallocate more memory
    if(user1->user.friends_capacity == user1->user.friends_number) {
        user1->user.friends_capacity = user1->user.friends_capacity + 2;//social network logic. The more friends a user has, the more popular it will be
        user1->user.friends_of_user = realloc(user1->user.friends_of_user, (user1->user.friends_capacity) * sizeof(char**));
        for(int i = user1->user.friends_number; i<user1->user.friends_capacity; i++){
            user1->user.friends_of_user[i] = (char*)malloc(MAX_LENGTH*sizeof(char));
            strcpy(user1->user.friends_of_user[i],"");
        }
    }
    //Check if we have space for user2 to add friends, if not reallocate more memory
    if(user2->user.friends_capacity == user2->user.friends_number) {
        user2->user.friends_capacity = user2->user.friends_capacity + 2;//social network logic. The more friends a user has, the more popular it will be
        user2->user.friends_of_user = realloc(user2->user.friends_of_user, (user2->user.friends_capacity) * sizeof(char**));
        for(int i = user2->user.friends_number; i<user2->user.friends_capacity; i++){
            user2->user.friends_of_user[i] = (char*)malloc(MAX_LENGTH*sizeof(char));
            strcpy(user2->user.friends_of_user[i],"");
        }
    }
    strcpy(user1->user.friends_of_user[user1->user.friends_number], user2->user.username);
    strcpy(user2->user.friends_of_user[user2->user.friends_number], user1->user.username);
    user1->user.friends_number++;
    user2->user.friends_number++;
}

void calculate_time(char* datetime){
    //Get the current time
    time_t currentTime = time(NULL);
    struct tm *localTime = localtime(&currentTime);
    strftime(datetime,DATE_TIME_LENGTH,"%Y-%m-%d %H:%M:%S", localTime);
}

//char* temps = READ DEL CSV;

void add_post(User_list* user,Community* community, char content[], char time[]){
    //Check if we have space for more posts, if not reallocate more memory
    if(user->user.posts_capacity == user->user.posts_number) {
        user->user.posts_capacity = user->user.posts_capacity + 2;//social network logic. The more friends a user has, the more popular it will be
        user->user.user_posts = realloc(user->user.user_posts, (user->user.posts_capacity) * sizeof(Post));

        for(int i = user->user.posts_number; i<user->user.posts_capacity; i++){
            user->user.user_posts[i].content = (char*)malloc(MAX_POST_LENGTH*sizeof(char));
            strcpy(user->user.user_posts[i].content,"");
        }
    }

    //Check if we have space for the community posts, if not reallocate more memory
    if(community->posts_capacity == community->posts_number) {
        community->posts_capacity = community->posts_capacity +2;
        community->posts = realloc(community->posts, (community->posts_capacity) * sizeof(Post));

        for(int i = community->posts_number; i<community->posts_capacity; i++){
            community->posts[i].content = (char*)malloc(MAX_POST_LENGTH*sizeof(char));
            strcpy(community->posts[i].content,"");

        }
    }


    //Create auxiliary post and add datetime and the given content
    Post *aux;
    aux = (Post*)malloc(sizeof(Post));
    init_post(aux);
    //Format the current time as a string and save it on the new post datetime
    strcpy(aux->username, user->user.username);
    strcpy(aux->datetime,time);
    strcpy(aux->content,content);

    //Add to user's posts and community post
    strcpy(user->user.user_posts[user->user.posts_number].username, aux->username);
    strcpy(user->user.user_posts[user->user.posts_number].datetime, time);
    strcpy(user->user.user_posts[user->user.posts_number].content, aux->content);
    //community->posts[community->posts_number] = *aux;

    strcpy(community->posts[community->posts_number].username, aux->username);
    strcpy(community->posts[community->posts_number].datetime, time);
    strcpy(community->posts[community->posts_number].content, aux->content);

    user->user.posts_number++;
    community->posts_number++;
    //printf("%d\n",community->posts_number);
}



void swap(hash_table_item **a, hash_table_item **b) { //swaps items in a hash table
    hash_table_item *temp = *a;
    *a = *b;
    *b = temp;
}

int partition(hash_table_item **array, int low, int high) {
    char* pivot = array[high]->value;
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (strcmp(array[j]->value, pivot) >= 0) { //Modified condition for descending order based on value
            i++;
            swap(&array[i], &array[j]);
        }
    }
    swap(&array[i + 1], &array[high]);
    return (i + 1);
}


void Quicksort(hash_table_item **array, int inf, int sup) { //quicksort function
    if (inf < sup) {
        int pivot = partition(array, inf, sup);
        Quicksort(array, inf, pivot - 1);
        Quicksort(array, pivot + 1, sup);
    }
}

void top_ten_words(hash_table_table *hash_table){ //shows top ten words of a hash table
    //Allocate memory for an array of hash_table_item pointers
    hash_table_item **items = malloc(sizeof(hash_table_item*) * hash_table->count);
    //Copy the items from the hash table into the array
    int itemsIndex = 0;
    for (int j = 0; j < hash_table->size; j++) {
        if (hash_table->items[j] != NULL) {
            items[itemsIndex] = hash_table->items[j];
            itemsIndex++;
        }
    }
    //Sort the array of items using the compare_items function
    Quicksort(items, 0, (hash_table->count)-1);
    //Print the top 10 items
    int topCount;

    if (hash_table->count < 10) topCount = hash_table->count;
    else topCount = 10;

    for (int i = 0; i < topCount; i++) {
        printf("Word: %s, Times mentioned: %s\n", items[i]->key, items[i]->value);
    }
    //Free the memory allocated for the array of items
    free(items);
}


void words_to_hash(char post_content[], hash_table_table *frequentwords) {
    //copy of post to iterate its words
    char post_to_analyze[MAX_POST_LENGTH];
    strcpy(post_to_analyze, post_content);
    //iterator for individual words
    char *word;
    word = strtok(post_to_analyze, " ");
    convertToLowercase(word);

    char *lookup;

    while (word != NULL) {
        //Search in the hash table for the word and retrieve its value
        lookup = hash_table_search(frequentwords, word);
        char string_value[MAX_LENGTH];
        if (lookup != NULL) {
            //Convert value retrieved from lookup into an integer
            int value_to_update = atoi(lookup);
            //Increment the value by one unit
            int new_value = ++value_to_update;
            //Insert same deleted key with new_value
            sprintf(string_value, "%d", new_value);
            //Update the value of the key in the hash table
            hash_table_insert(frequentwords, word, string_value);
        } else {
            //Convert integer into string
            int number = 1;
            sprintf(string_value, "%d", number);
            //Insert new word found in the hash table with value 1
            hash_table_insert(frequentwords, word, string_value);
        }
        //printf("Hash Table Size: %i, Maximum Capacity: %i.\n", hash_table->count, hash_table->size);

        //Go to next word
        word = strtok(NULL, " ");
    }
}

void words_to_hash_smart(char post_content[], hash_table_table *trending_topics, hash_table_table *stopwords) {
    //copy of post to iterate its words
    char post_to_analyze[MAX_POST_LENGTH];
    strcpy(post_to_analyze, post_content);
    //iterator for individual words
    char* word;
    word = strtok(post_to_analyze, " ");
    //convertToLowercase(word);
    char *lookup;

    while (word != NULL) {
        convertToLowercase(word);
        remove_final_dot(word);
        if (is_a_stop_word(word, stopwords) == FALSE) {
            //Search in the hash table for the word and retrieve its value
            lookup = hash_table_search(trending_topics, word);
            char string_value[MAX_LENGTH];
            if (lookup != NULL) {
                //Convert value retrieved from lookup into an integer
                int value_to_update = atoi(lookup);
                //Increment the value by one unit
                int new_value = ++value_to_update;
                //Insert same deleted key with new_value
                sprintf(string_value, "%d", new_value);
                //Update the value of the key in the hash table
                hash_table_insert(trending_topics, word, string_value);
            } else {
                //Insert new word found in the hash table with value 1
                hash_table_insert(trending_topics, word, "1");
            }
        }
        //Go to next word
        word = strtok(NULL, " ");
    }
}

void delete_user_list(User_list *user_list){
    User_list *current = user_list;
    User_list *next;

    while (current != NULL) {
        next = current->next_user;
        delete_user(&current->user);
        free(current);
        current = next;

        if (current != NULL) {
            current->prev_user = NULL; //Update the prev_user pointer of the next node
        }
    }
}

void delete_community(Community *community){
    delete_user_list(community->first_node);
    if (community->last_node != NULL) {
        delete_user_list(community->last_node->next_user);
    }
    for (int i = 0; i < community->posts_capacity; ++i){
        free_post(&community->posts[i]);
    }
}


void random_requests(Community *community,User_list *user) {
    char option_stack[MAX_LENGTH];
    Stack stack;
    init_stack(&stack);
    //FILL STACK WITH THREE RANDOM USERS
    for (int i = 0; i <3; i++){
        int random = 0;
        random = rand()%community->current_size;
        push(&stack, random_user_search(*community, random));
    }
    //ASK THE USER WHETHER TO SEND REQUESTS
    while(!is_empty(stack)){
        printf("Do you want to send %s a friend request?\n", top(stack).username);
        printf("You may want to consider his/her/their tastes: \n"); //print random user tastes
        for (int i = 0; i < MAX_SIZE; i++){
            if(i == MAX_SIZE -1 ){
                printf("%s",top(stack).tastes[i]);
            } else{
                printf("%s, ", top(stack).tastes[i]);
            }
        }
        printf("\n");
        printf("Write [A] to send the request or [any other key] to avoid sending it.\n");
        scanf("%s", &option_stack);
        if(strcmp(option_stack,"A")==0){
            //Generate request
            Node_request *aux = (Node_request*)malloc(sizeof(Node_request));
            aux->next_request = NULL;
            strcpy(aux->name, user->user.username);
            //Search receiver's user node
            User_list* receiver = (User_list *) malloc(sizeof(User_list));
            init_user_list(receiver);
            receiver = linear_search(top(stack).username, *community);
            enqueue(&receiver->user.requests, aux);
            //Print result
            printf("You have sent a request to %s\n", top(stack).username);
            pop(&stack);
        }  else { //DECLINE REQUEST
            printf("You have not sent a request to %s\n", top(stack).username);
            pop(&stack);
        }
    }
}

void write_new_post(User_list *user, Community *community, hash_table_table *hash_table, hash_table_table *trendingtopics, hash_table_table *stopwords) {
    char post[MAX_POST_LENGTH + 2]; //+2 to account for newline and null terminator
    setConsoleColor(COLOR_BLUE);
    printf("Write your post here, remember the maximum character number is 120: \n");
    setConsoleColor(COLOR_RESET);
    fgets(post, sizeof(post), stdin);
    //Remove the newline character
    remove_newline(post);
    //Post character limit handling
    if(strlen(post) > MAX_POST_LENGTH){
        setConsoleColor(COLOR_RED);
        printf("Too much text. Watch out for the number of characters, you exceeded the max of 120.");
        setConsoleColor(COLOR_RESET);
        clear_input_buffer();
        enter_to_exit();
    }
    else {
        words_to_hash(post, hash_table);
        words_to_hash_smart(post, trendingtopics, stopwords);
        char datetime[DATE_TIME_LENGTH];
        calculate_time(datetime);
        add_post(user, community, post, datetime);
    }
}

int are_friends(User_list *user1, char *user2, Community* community){
    for(int i=0;i<user1->user.friends_number;i++){
        if(strcmp(user1->user.friends_of_user[i],user2) == 0){
            return TRUE;
        }
    }
    return FALSE;
}

void user_feed(Community *community, User_list *user){
    for (int i = community->posts_number; i >= 0;--i) {
        if(are_friends(user,community->posts[i].username,community) == TRUE || strcmp(user->user.username, community->posts[i].username)==0){
            print_post(community->posts[i]);
        }
    }
}


