#include "stdincludes.h"
#include "csvRead.h"

#define HOURS_PER_YEAR 8760

static int row_count;
static Datapoint* data;

void SetCSVPath(const char* filename, const bool has_header)
{
    FILE* fh = fopen(filename == NULL ? "datafiler/DK-DK2_2022_hourly.csv" : filename, "r");
    if (fh == NULL)
    {
        fprintf(stderr, "Failed to locate or open CSV-file!\n");
        exit(EXIT_FAILURE);
    }
    if (data != NULL) free(data);
    data = readCSV(fh, &row_count, has_header);
    fclose(fh);
}
Datapoint* GetCSVData(int* rows_out) 
{
    if (data == NULL || row_count == 0) {
        SetCSVPath(NULL, true);
    }

    *rows_out = row_count;
    return data;
}

Datapoint* readCSV(FILE* fh, int * rows_out, bool has_header)
{
    // Uninitialized buffer to input the rows to.
    char buffer[1024];
    int row = 0;
    int column;
    // Allocation of the Datapoint-array, with the expected amounts of rows as the number of elements.
    Datapoint *data = malloc(HOURS_PER_YEAR*sizeof(Datapoint));

    if (has_header)
    {
        fgets(buffer, 1024, fh);
        strtok(buffer, ",");
        while (strtok(NULL, ",")) {; } // fast through first line 
    }

    // While-loop that goes through each line of the .csv-file and writes it to buffer[].
    while (fgets(buffer, 1024, fh) && row < HOURS_PER_YEAR)
    {
        column = 0;
        
        // Tokenizes buffer with ',' as the delimiter.
        char *tok = strtok(buffer, ",");      
        
        // Keep going as long as a new token is found.
        while (tok)
        {           
            switch (column) {
                case 0:
                {
                    int year;
                    int month;
                    int day;
                    int hours;
                    int minutes;
                    int seconds;

                    // Struct containing member that represent a date and time.
                    tm datetime;

                    // Parse the first column of the line to the tm struct.
                    sscanf(tok, "%d-%d-%d %d:%d:%d", &year, &month, &day, &hours, &minutes, &seconds);
                    datetime.tm_year = year - 1900;
                    datetime.tm_mon = month - 1;
                    datetime.tm_mday = day;
                    datetime.tm_hour = hours;
                    datetime.tm_min = minutes;
                    datetime.tm_sec = seconds;
                    datetime.tm_isdst = -1;

                    // Convert the tm struct to seconds since epoch.
                    data[row].datetime = mktime(&datetime);
                    break;
                }

                case 4:
                {
                    data[row].ci_direct = strtod(tok, NULL);
                    // If the first row does not contain data use this instead:
                    break;
                }
                case 5:
                {
                    data[row].ci_lca = strtod(tok, NULL);
                    break;
                }
                case 6:
                {
                    data[row].low_percent = strtod(tok, NULL);
                    break;
                }
                case 7:
                {
                    data[row].renew_percent = strtod(tok, NULL);
                    break;
                }
            }
            
            column++;

            // Find the next token on the line.
            tok = strtok(NULL, ",");
        } 
            
        row++;
    }

    *rows_out = row;
    
    return data;
}

