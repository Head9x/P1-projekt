#include <stdio.h>
#include "cJSON.c"
#include "cJSON.h"

int readBatt() { 
    // open the file 
    FILE *fp = fopen("datafiler/log000", "r"); 
    if (fp == NULL) { 
        printf("Error: Unable to open the file.\n"); 
        return 1; 
    } 
    char line[1024];

    // Read and print each line of the file
    while (fgets(line, sizeof(line), fp) != NULL) {
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
        //printf("%s\n", json_str);  
    
        // access the JSON data 
        cJSON *message = cJSON_GetObjectItemCaseSensitive(json, "message"); 
    
    
        char *json_str2 = cJSON_Print(message);
        //printf("%s\n", json_str2);

        cJSON *current = cJSON_GetObjectItemCaseSensitive(message, "current"); 
        if (cJSON_IsNumber(current)) { 
            printf("Batt-I/O: %f\n", current->valuedouble); 
        } 
    
        // delete the JSON object 
        cJSON_Delete(json); 
    }

    fclose(fp); // Don't forget to close the file when done
    return 0;
}

int readSolar() { 
    // open the file 
    FILE *fp = fopen("datafiler/log000", "r"); 
    if (fp == NULL) { 
        printf("Error: Unable to open the file.\n"); 
        return 1; 
    } 
    char line[1024];
    while (fgets(line, sizeof(line), fp) != NULL) {
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
        //printf("%s\n", json_str);  
    
        // access the JSON data 
        cJSON *message = cJSON_GetObjectItemCaseSensitive(json, "message"); 
    
    
        char *json_str2 = cJSON_Print(message);
        //printf("%s\n", json_str2);

        cJSON *power_out = cJSON_GetObjectItemCaseSensitive(message, "pv_power"); 
        if (cJSON_IsNumber(power_out)) { 
            printf("Power_In: %i\n", power_out->valueint); 
        } 
    
        // delete the JSON object 
        cJSON_Delete(json); 
        }

        fclose(fp); // Don't forget to close the file when done
    return 0;
}


int main(void) { 
    readSolar();
}