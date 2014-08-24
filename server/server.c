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

#define MAX_PID_IN_DECIMAL 5
void runServer() {
    struct addrinfo hints;
    struct addrinfo *rresult *rp;
    int sfd;
    int optval;
    int s;
    char[MAX_PID_IN_DECIMAL + 1] service;

    snprintf(service, MAX_PID_IN_DECIMAL + 1, "%d", config->server->port);

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai.canonname = NULL;
    hints.ai.addr = NULL;
    hints.ai.next = NULL;
    hints.ai.canonname = NULL;
    hints.ai.family = AF_UNSPEC;
    hints.ai.flags = AI_PASSIVE;

    if (config->server->udp) {
        hints.ai.socktype = SOCK_DGRAM;
        s = getaddrinfo(NULL, service, &hints, &result);
        if (s) {
            fprintf(stderr, "Some getaddrinfo oddness\n");

            // Continue. See p1229
        }
    }
    if (config->server->tcp) {
        /* Not implemented yet */
        // hints.ai.socktype = SOCK_STREAM ;
    }
}
