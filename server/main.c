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
#include <hiredis/hiredis.h>

#include "main.h"
#include "constants.h"
#include "config.h"

int main(int argc, const char * const argv[])
{
    int option = 0;
    redisContext *c;
    redisReply *reply;
    /* clash */
    const char *hostname = (argc > 1) ? argv[1] : "127.0.0.1";
    int port = (argc > 2) ? atoi(argv[2]) : 6379;

    char *config_file = CONFIG_FILE;

    struct timeval timeout = { 1, 500000 }; // 1.5 seconds

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

    parse_yaml(config_file);

    c = redisConnectWithTimeout(hostname, port, timeout);

    if (c == NULL || c->err) {
        if (c) {
            printf("Connection error: %s\n", c->errstr);
            redisFree(c);
        } else {
            printf("Connection error: can't allocate redis context\n");
        }
        exit(1);
    }

    reply = redisCommand(c, "SET %s %s", "foo.com", "127.0.0.1");
    freeReplyObject(reply);
    reply = redisCommand(c, "EXPIRE %s %s", "foo.com", "10");
    freeReplyObject(reply);
    do {
        reply = redisCommand(c,"TTL foo.com");
        printf("TTL foo.com:  %lld\n", reply->integer);
        sleep(1);
    } while ( reply->integer >= 0 ) ;
    freeReplyObject(reply);

    /* Disconnects and frees the context */
    redisFree(c);
    exit(0);
}

void print_usage() {
    printf("whatever\n");
}

