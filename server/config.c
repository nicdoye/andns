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
#include <string.h>
#include <errno.h>
#include "constants.h"
#include "config.h"
#include "globals.h"

/* Obviously A LOT of refactoring could go on in here! */
/*
 * root is the top level json object
 * json_object is the next level down the tree
 * tmp normally marks the level below that
 */
void parse_file(char *config_file) {
    json_t *root;
    json_t *json_object;
    json_t *tmp;
    json_error_t *error;
    size_t flags;
    char *tmp_str;

    config = (config_t *)malloc(sizeof(config_t));
    config->server = (server_t *)malloc(sizeof(server_t));


    /* Top level element */
    root = json_load_file(config_file, flags, error);

    if(!json_is_object(root)) {
        fprintf(stderr, "error: configuration data is not an object\n");
        json_decref(root);
        exit(4);
    }

    /* Server object */

    json_object = json_object_get(root, C_ELT_SERVER);

    if(!json_is_object(json_object)) {
        fprintf(stderr, "error: configuration for server is not an object\n");
        json_decref(json_object);
        exit(4);
    }

    /* Server Mode */

    tmp = json_object_get(json_object, C_ELT_SERVER_MODE);

    if(!json_is_string(tmp))
    {
        fprintf(stderr, "error: whatever is not a string\n");
        json_decref(tmp);
        exit(4);
    }

    tmp_str = strdup(json_string_value(tmp));

    if (!strcmp(tmp_str, C_ELT_SERVER_MODE_CACHE_ONLY)) {
        config->server->mode = AND_MODE_CACHE_ONLY;
    } 
    else if (!strcmp(tmp_str, C_ELT_SERVER_MODE_MASTER)) {
        config->server->mode = AND_MODE_MASTER;
        fprintf(stderr,"Not implemented yet.\nBye\n");
        exit(4);
    }
    else if (!strcmp(tmp_str, C_ELT_SERVER_MODE_MIXED)) {
        config->server->mode = AND_MODE_MIXED;;
        fprintf(stderr,"Not implemented yet.\nBye\n");
        exit(4);
    }
    else {
       fprintf(stderr, "error: server mode must be one of %s, %s or %s\n", C_ELT_SERVER_MODE_CACHE_ONLY, C_ELT_SERVER_MODE_MASTER, C_ELT_SERVER_MODE_MIXED);
       exit(4);
    }

    free(tmp_str);
    free(tmp);

    tmp = json_object_get(json_object, C_ELT_SERVER_UDP);

    if(!json_is_string(tmp))
    {
        fprintf(stderr, "error: whatever is not a boolean\n");
        json_decref(tmp);
        exit(4);
    }

    config->server->udp = !strcmp(json_string_value(tmp), "false");
    free(tmp);

    tmp = json_object_get(json_object, C_ELT_SERVER_TCP);

    if(!json_is_string(tmp))
    {
        fprintf(stderr, "error: whatever is not a boolean\n");
        json_decref(tmp);
        exit(4);
    }

    config->server->tcp = !strcmp(json_string_value(tmp), "false");
    free(tmp);
    free(json_object);

    if (config->server->mode == AND_MODE_MASTER || config->server->mode == AND_MODE_MIXED) {

        json_object = json_object_get(root, C_ELT_MASTER);

        if(!json_is_object(json_object)) {
            fprintf(stderr, "error: configuration for master is not an object\n");
            json_decref(json_object);
            exit(4);
        }

        /* Master Mode */

        tmp = json_object_get(json_object, C_ELT_MASTER_ROOT);

        if(!json_is_string(tmp))
        {
            fprintf(stderr, "error: whatever is not a string\n");
            json_decref(tmp);
            exit(4);
        }

        config->master_dir = strdup(json_string_value(tmp));

        if (NULL == config->master_dir) {
            fprintf(stderr,"Malloc error\n");
            exit(4);
        }

        free(tmp);
        free(json_object);
    }

    json_object = json_object_get(root, C_ELT_BACKEND);

    if(!json_is_object(json_object)) {
        fprintf(stderr, "error: configuration for master is not an object\n");
        json_decref(json_object);
        exit(4);
    }

    /* Only backend actually supported */
    tmp = json_object_get(json_object, C_ELT_BACKEND_REDIS);
    if (!json_is_array(tmp)) {
        fprintf(stderr, "error: configuration for redis is not an array\n");
        json_decref(json_object);
        exit(4);
    }

    for (int i = 0; i <= json_array_size(tmp); i++) {
        json_t *redis_server = json_array_get(tmp,i);
        json_t *tmp_object;

        config->redis[i] = (redis_t *)malloc(sizeof(redis_t));

        if(!json_is_object(redis_server)) {
            fprintf(stderr, "error: configuration for redis_server is not an object\n");
            json_decref(json_object);
            exit(4);
        }

        tmp_object = json_object_get(redis_server, C_ELT_BACKEND_SERVER);
        
        if(!json_is_string(tmp_object)) {
            fprintf(stderr, "error: configuration for server name is not an object\n");
            json_decref(json_object);
            exit(4);
        }

        config->redis[i]->server = strdup(json_string_value(tmp_object));
        free(tmp_object);
        
        tmp_object = json_object_get(redis_server, C_ELT_BACKEND_PORT);
        
        if(!json_is_integer(tmp_object)) {
            fprintf(stderr, "error: configuration for server name is not an object\n");
            exit(4);
        }

        config->redis[i]->port = json_integer_value(tmp_object);
        if (config->redis[i]->port == 0) {
            fprintf(stderr, "That's not an integer\n");
            exit(4);
        }

        free(tmp_object);
        free(redis_server);
    }

    free(tmp);
    free(json_object);

}
