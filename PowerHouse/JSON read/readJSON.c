#include <stdio.h>
#include "cJSON.c"
#include "cJSON.h"


int main(void) { 
    // open the file 
    FILE *fp = fopen("testfile-multiline.json", "r"); 
    if (fp == NULL) { 
        printf("Error: Unable to open the file.\n"); 
        return 1; 
    } 
  
    // read the file contents into a string 
    char buffer[1024]; 
    int len = fread(buffer, 1, sizeof(buffer), fp); 
    fclose(fp); 
  
    // parse the JSON data 
    cJSON *json = cJSON_Parse(buffer); 
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
  
    // access the JSON data 
    cJSON *message = cJSON_GetObjectItemCaseSensitive(json, "message"); 
 
 
    char *json_str2 = cJSON_Print(message);
    printf("%s\n", json_str2);

    cJSON *power_out = cJSON_GetObjectItemCaseSensitive(message, "pv_power"); 
    if (cJSON_IsNumber(power_out)) { 
        printf("Power_In: %i\n", power_out->valueint); 
    } 
    cJSON *current = cJSON_GetObjectItemCaseSensitive(message, "current"); 
    if (cJSON_IsNumber(current)) { 
        printf("Amps_In: %f\n", power_out->valuedouble); 
    } 
  
    // delete the JSON object 
    cJSON_Delete(json); 
    return 0; 
}