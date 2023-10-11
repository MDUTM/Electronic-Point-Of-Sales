#ifndef _JSONUTIL_H
#define _JSONUTIL_H 1

#include "cJSON.h"

int cJSON_GetIntObjectItem(const cJSON * const object, const char * const string);

double cJSON_GetDoubleObjectItem(const cJSON * const object, const char * const string);

char *cJSON_GetStringObjectItem(const cJSON * const object, const char * const string);

#endif /* _JSONUTIL_H */