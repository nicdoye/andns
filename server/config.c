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
#include "config.h"

void parse_file(char *config_file) {
    long fsize = 0;
    char *data;

    FILE *fh = fopen(config_file, "r");

    if (fh == NULL) {
        printf("Could not open file %s\n", config_file);
	exit(2);
    }

    if (fseek(fh, 0L, SEEK_END)) {
        printf("Error reading to end of file\n");
        exit(errno);
    }

    fsize = ftell(fh);

    if (fseek(fh, 0L, SEEK_SET)) {
        printf("Error returning to start of file\n");
        exit(errno);
    }

    data = (char *)malloc(fsize + 1);
    if (data == NULL) {
        printf("Malloc failed\n");
        exit(errno);
    }
    fread(data, fsize, 1, fh);

    if(ferror(fh)) {
        int e = ferror(fh);
        printf("Error %d reading entire file", e);
        exit(e);
    }

    fclose(fh);

    data[fsize] = 0;
}

