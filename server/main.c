/* Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

#include "main.h"
#include "constants.h"
#include "config.h"
#include "globals.h"

config_t *config = 0;
redisContext *context = 0;

int main(int argc, const char * const argv[])
{
    int option = 0;
    char *config_file = CONFIG_FILE;

    while ((option = getopt(argc, argv,"f:")) != -1) {
        switch (option) {
        case 'f' : 
            config_file = optarg;
            break;
        default: 
            print_usage(); 
            exit(EXIT_FAILURE);
        }
    }

    parse_file(config_file);
    /* dump_config(); */
    connectToRedis();
    runServer();
    disconnectFromRedis();
    exit(0);
}

void connectToRedis() {
    struct timeval timeout = { 1, 500000 }; // 1.5 seconds

    /* Assume one host for now */
    context = redisConnectWithTimeout(config->redis[0]->server, config->redis[0]->port, timeout);

    if (context == NULL || context->err) {
        if (context) {
            printf("Connection error: %s\n", context->errstr);
            redisFree(context);
        } else {
            printf("Connection error: can't allocate redis context\n");
        }
        exit(1);
    }
}

/*
void runServer() {
    redisReply *reply;

    reply = redisCommand(context, "SET %s %s", "foo.com", "127.0.0.1");
    freeReplyObject(reply);
    reply = redisCommand(context, "EXPIRE %s %s", "foo.com", "10");
    freeReplyObject(reply);
    do {
        reply = redisCommand(context,"TTL foo.com");
        printf("TTL foo.com:  %lld\n", reply->integer);
        sleep(1);
    } while ( reply->integer >= 0 ) ;
    freeReplyObject(reply);

}
*/

void runServer() {
}

void print_usage() {
    printf("whatever\n");
}

void disconnectFromRedis() {
    /* Disconnects and frees the context */
    redisFree(context);
}
