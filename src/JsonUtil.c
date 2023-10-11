#include <stdbool.h>
#include <stdlib.h>
#include "JsonUtil.h"

int cJSON_GetIntObjectItem(const cJSON * const object, const char * const string)
{
    cJSON * data= cJSON_GetObjectItem(object, string);

    return atoi(cJSON_Print(data));
}

double cJSON_GetDoubleObjectItem(const cJSON * const object, const char * const string)
{
    cJSON * data= cJSON_GetObjectItem(object, string);

    return atof(cJSON_Print(data));
}

char *cJSON_GetStringObjectItem(const cJSON * const object, const char * const string)
{
    cJSON * data= cJSON_GetObjectItem(object, string);

    return cJSON_Print(data);
}