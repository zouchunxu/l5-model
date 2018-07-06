#include "connect.h"
#include <stdlib.h>


connect_list * list;

connect_list * head;

connect_list * tail;




connect_list * add_connect(char *host, char *username, char *password, char *database, int port) {

    connect_list * tmp;
    if(list == NULL){
        list = emalloc(sizeof(connect_list));
        head  = tail = tmp = list;
        tmp->curr = emalloc(sizeof(connect_info));
        tmp->curr->host = host;
        tmp->curr->username = password;
        tmp->curr->database = database;
        tmp->curr->password = password;
        tmp->curr->port = port;
        tmp->next = NULL;
    } else {
        tmp = emalloc(sizeof(connect_list));
        tmp->curr = emalloc(sizeof(connect_info));
        tmp->curr->host = host;
        tmp->curr->username = password;
        tmp->curr->database = database;
        tmp->curr->password = password;
        tmp->curr->port = port;
        tmp->next = NULL;
        tail->next = tmp;
        tail = tmp;
    }




    return tail;


}

void * find_connect(char * host,char * username)
{
    connect_list * find = head;
}