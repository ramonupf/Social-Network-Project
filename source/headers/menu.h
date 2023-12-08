//
// Created by Feryjhon Bautista on 27/4/23.
//

#ifndef SOCNETWORK_MENU_H
#define SOCNETWORK_MENU_H

#include "common.h"
#include "../headers/community.h"
#include "../headers/utils.h"

#include "hash_table.h"
#include "stop_words.h"



void show_menu();
void user_menu(User_list* user, Community *community, hash_table_table *hash_table, hash_table_table *stopwords, hash_table_table *trendingtopics);


#endif //SOCNETWORK_MENU_H





