#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>


typedef struct fileRow
{
    time_t datetime;
    //long long int datetime;
    //char* country;
    //char* zone_name;
    //char* zone_id;
    double ci_direct;
    double ci_lca;
    //char* ci_direct;
    //char* ci_lca;
    double low_percent;
    double renew_percent;
    //float low_percent;
    //float renew_percent;
    //char* source;
    //char* method;
} fileRow;

fileRow* readData();

int main(void)
{
    fileRow *data = readData();
    
    if (data == NULL)
    {
        printf("Fejl\n");
    }
    
    
    
    
    for (int i = 0; i < 8760; i++)
    {
        //puts(data[i].datetime);
        //puts(data[i].country);
        printf("Time since EPOCH: %d\n", data[i].datetime);
        printf("CI direkt: %lf CI lca: %lf\n", data[i].ci_direct, data[i].ci_lca);
        printf("Low%%: %lf Renew%%: %lf\n\n", data[i].low_percent, data[i].renew_percent);
        //printf("%lf\n\n", strtod(data[i].ci_direct, NULL));
    }
    
    

    
}

fileRow* readData()
{
    FILE *fh = fopen("data.csv", "r");

    int row = 0;
    char buffer[1024];
    int column;
    fileRow *data = malloc(8760*sizeof(fileRow));


    while (fgets(buffer, 1024, fh) && row<9000)
    {
        column = 0;
        
        char *tok = strtok(buffer, ",");
        
        
        while (tok)
        {
            
            if (column == 0)
            {
                time_t year;
                time_t month;
                time_t day;
                time_t hours;
                time_t minutes;
                time_t seconds;

                struct tm datetime;
                sscanf(tok, "%d-%d-%d %d:%d:%d", &year, &month, &day, &hours, &minutes, &seconds);
                datetime.tm_year = year - 1900;
                datetime.tm_mon = month - 1;
                datetime.tm_mday = day;
                datetime.tm_hour = hours;
                datetime.tm_min = minutes;
                datetime.tm_sec = seconds;
                datetime.tm_isdst = -1;
                data[row].datetime = mktime(&datetime);
            

            }

            if (column == 4)
            {
                data[row].ci_direct = strtod(tok, NULL);
                
            }
            if (column == 5)
            {
                data[row].ci_lca = strtod(tok, NULL);
            }
            if (column == 6)
            {

                data[row].low_percent = strtod(tok, NULL);
                
            }
            if (column == 7)
            {
                data[row].renew_percent = strtod(tok, NULL);
            }
            
            column++;
            tok = strtok(NULL, ",");
        } 
            
        row++;
    }
        //printf("Row: %d done!\n", row);
        



fclose(fh);
return data;
}
