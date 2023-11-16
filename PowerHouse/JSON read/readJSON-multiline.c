#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.c"
#include "cJSON.h"

char* powerparser();
char retval[32];
void removeChar();
char *jsonhandler();

int main(void) { 
        char *filename = "testfile-multiline.json";
        //open and get the file handle
        FILE* fh;
        fopen_s(&fh, filename, "r");

        //check if file exists
        if (fh == NULL){
            printf("file does not exists %s", filename);
            return 0;
        }


        //read line by line
        const size_t line_size = 1024;
        char* line = malloc(line_size);
        while (fgets(line, line_size, fh) != NULL)  {
            char* jsonline = jsonhandler(line);
            printf("%s\n", jsonline);
        }
        free(line);    // dont forget to free heap memory
}




char *jsonhandler(char *line) { 

    cJSON *json = cJSON_CreateObject();
    cJSON_AddRawToObject(json, "input", line);
    char *json_str = cJSON_Print(json); 
    //printf("%s\n", json_str);  

// parse the JSON data 
    cJSON *json_ = cJSON_Parse(json_str); 
    if (json_ == NULL) { 
        const char *error_ptr = cJSON_GetErrorPtr(); 
        if (error_ptr != NULL) { 
            printf("Error: %s\n", error_ptr); 
        } 
        cJSON_Delete(json_); 
        return "JSON ERROR"; 
    } 
    cJSON *input = cJSON_GetObjectItemCaseSensitive(json_, "input"); 
    cJSON *topic = cJSON_GetObjectItemCaseSensitive(input, "topic"); 
    cJSON *message = cJSON_GetObjectItemCaseSensitive(input, "message"); 
 
    char* topic_ = cJSON_Print(topic);
    removeChar(topic_, '"');
    //printf("%s", topic_);
    powerparser(message, topic_);
    return retval;
}

char* powerparser(cJSON *json, char *topic) { 

    
    //printf("%s\n", topic);
    
    //printf("%d, topic= %s, compare= %s\n\n", strcmp(topic, "solar/stats-batt"), topic, "solar/stats-batt");
    sprintf(retval,  "ERROR");
    if (strcmp(topic, "solar/stats-batt") == 0){
        //printf("BATTERY   ");
        cJSON *current = cJSON_GetObjectItemCaseSensitive(json, "current"); 
        cJSON *voltage = cJSON_GetObjectItemCaseSensitive(json, "voltage"); 
        char *current_ = cJSON_Print(current);
        char *voltage_ = cJSON_Print(voltage);
        char *ptr;
        double current__ = strtod(current_, &ptr);
        double voltage__ = strtod(voltage_, &ptr);
        double watts = (2*current__ )*voltage__;
        //printf("Powerflow is %f\n watts", watts);
        sprintf(retval, "Powerflow is %2f watts", watts);
    }
    else if (strcmp(topic, "solar/stats") == 0){
        //printf("solar_stats   ");
        cJSON *energy = cJSON_GetObjectItemCaseSensitive(json, "pv_power"); 
        char *energy_ = cJSON_Print(energy);
        int watts_solar = atoi(energy_);
        //printf("Producing %d Watts of energy\n", watts_solar);
        sprintf(retval,  "Producing %d Watts of energy", watts_solar);
    }
    //cJSON *input = cJSON_GetObjectItemCaseSensitive(json, "input"); 
    return "success";
}

void removeChar(char *str, char c) {
    int i, j;
    int len = strlen(str);
    for (i = j = 0; i < len; i++) {
        if (str[i] != c) {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}