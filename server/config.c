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

/* vim: set tabstop=4:softtabstop=4:shiftwidth=4:noexpandtab */ 

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "constants.h"
#include "config.h"
#include "globals.h"

void parse_file(char *config_file) {
    json_t *root;
    json_t *server;
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

    server = json_object_get(root, C_ELT_SERVER);

    if(!json_is_object(server)) {
        fprintf(stderr, "error: configuration for server is not an object\n");
        json_decref(server);
        exit(4);
    }

    /* Server Mode */

    tmp = json_object_get(server, C_ELT_SERVER_MODE);

    if(!json_is_string(tmp))
    {
        fprintf(stderr, "error: whatever is not a string\n");
        json_decref(tmp);
        exit(4);
    }

    tmp_str = json_string_value(tmp);

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

    tmp = json_object_get(server, C_ELT_SERVER_UDP);

    if(!json_is_string(tmp))
    {
        fprintf(stderr, "error: whatever is not a boolean\n");
        json_decref(tmp);
        exit(4);
    }

    config->server->udp = !strcmp(json_string_value(tmp), "false");
    free(tmp);

    tmp = json_object_get(server, C_ELT_SERVER_TCP);

    if(!json_is_string(tmp))
    {
        fprintf(stderr, "error: whatever is not a boolean\n");
        json_decref(tmp);
        exit(4);
    }

    config->server->tcp = !strcmp(json_string_value(tmp), "false");
    free(tmp);


}
