#include "Db.h"

void connect_client(char* host, uint port, char* pwd, redisContext* c) {
    c = redisConnect(host, port);
    if (c != NULL && c->err) {
        printf("Connection Error: %s\n", c->errstr);
        // handle error
    } else {
        printf("Connecting to Redis\n");
    }

    redisReply* reply = redisCommand(c, "AUTH %s", pwd);
    if (reply == NULL) {
        printf("%s", c->errstr);
    }

    printf("%s", reply->str);
}


redisReply* run_command(redisContext* c, char* command, char* key, char* value) {
    return redisCommand(c,"%s %s %s",command, key, value);
}