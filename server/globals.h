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

#include <hiredis/hiredis.h>

typedef enum {
    AND_MODE_CACHE_ONLY,
    AND_MODE_MASTER,
    AND_MODE_MIXED
} and_mode_t;

typedef struct {
    and_mode_t mode;
    int udp; /* boolean */
    int tcp; /* boolean */
    short port;
} server_t;

typedef struct {
    char *server;
    short port;
} redis_t;

typedef struct {
    server_t *server;
    char *master_dir;
    redis_t **redis;
} config_t;

extern config_t *config;
extern redisContext *context;
