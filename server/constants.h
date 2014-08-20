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

#define CONFIG_FILE "/etc/and/config.json"

#define C_ELT_ROOT "config"

#define C_ELT_SERVER "server"

#define C_ELT_SERVER_MODE "mode"
#define C_ELT_SERVER_MODE_CACHE_ONLY "cache-only"
#define C_ELT_SERVER_MODE_MASTER "master"
#define C_ELT_SERVER_MODE_MIXED "mixed"

#define C_ELT_SERVER_UDP "udp"
#define C_ELT_SERVER_TCP "tcp"
#define C_ELT_SERVER_PORT "port"

#define C_ELT_MASTER "master"
#define C_ELT_MASTER_ROOT "root"

#define C_ELT_BACKEND "backend"
#define C_ELT_BACKEND_REDIS "redis"

/* Should be reasonably common across backend implementations */
#define C_ELT_BACKEND_SERVER "server"
#define C_ELT_BACKEND_PORT "port"

