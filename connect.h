typedef struct connect_info {
    char * host;
    char * username;
    char * password;
    char * database;
    int port;
} _connect_info;

typedef struct connect_list {
    connect_info * curr;
    struct _connect_list * next;
} _connect_list;



void * find_connect(char * host,char * username);

connect_list * add_connect(char * host,char * username,char * password,char * database,int port);

