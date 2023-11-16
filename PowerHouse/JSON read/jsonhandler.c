#include <stdio.h>
#include "cJSON.c"
#include "cJSON.h"


int jsonhandler(char line) { 


// parse the JSON data 
    cJSON *json = cJSON_Parse(line); 
    if (json == NULL) { 
        const char *error_ptr = cJSON_GetErrorPtr(); 
        if (error_ptr != NULL) { 
            printf("Error: %s\n", error_ptr); 
        } 
        cJSON_Delete(json); 
        return 1; 
    } 

    char *json_str = cJSON_Print(json); 
    printf("%s\n", json_str);  

}