#ifndef DB_H
#define DB_H
#include <hiredis/hiredis.h>

typedef struct {
    char* host; 
    uint port; 
    char* pwd; 
    redisContext* c;
} Client;

typedef struct {
    redisContext* c;
    char* command;
    char* key;
    char* value;
} Query;

void connect_client(char* host, uint port, char* pwd, redisContext* c);
redisReply* run_command(redisContext* c, char* command, char* key, char* value);
#endif