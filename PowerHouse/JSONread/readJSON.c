#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"

double *calculateAndAddToArray(double value, double *array, size_t *size) {
    // Calculate the new value
    double result = value / 2;

    // Increase the size of the array
    *size += 1;
    array = realloc(array, sizeof(double) * (*size));

    // Check if realloc was successful
    if (array == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // Add the new result to the array
    array[*size - 1] = result;

    return array;
}




int readBattIO() { 
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

        size_t arraySize = 0;
        double *resultArray = NULL;

        // Add the calculated value to the array
        resultArray = calculateAndAddToArray(current->valuedouble, resultArray, &arraySize);
    
        // delete the JSON object 
        cJSON_Delete(json); 
        return resultArray;
    }
    fclose(fp); // Don't forget to close the file when done
}

int readBattpercentage() { 
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

        cJSON *chargelvl = cJSON_GetObjectItemCaseSensitive(message, "remaining_charge"); 
        if (cJSON_IsNumber(chargelvl)) { 
            printf("RemainingCharge Percentage: %f\n", chargelvl->valuedouble/2); 
        } 
        
        size_t arraySize = 0;
        double *resultArray = NULL;

        // Add the calculated value to the array
        resultArray = calculateAndAddToArray(chargelvl->valuedouble, resultArray, &arraySize);
    
        // delete the JSON object 
        cJSON_Delete(json); 
        return resultArray;
    }
    fclose(fp); // Don't forget to close the file when done
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
    
        size_t arraySize = 0;
        double *resultArray = NULL;

        // Add the calculated value to the array
        resultArray = calculateAndAddToArray(power_out->valueint, resultArray, &arraySize);
    
        // delete the JSON object 
        cJSON_Delete(json); 
        return resultArray;
    }
    fclose(fp); // Don't forget to close the file when done
}