#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "csvRead.h"

Datapoint* readCSV(char *file_name)
{
    
    char buffer[1024];
    
    // Juster 128*sizeof(Datapoint) for hvor mange forventede rækker du har i din .csv-fil.
    Datapoint *data = malloc(128*sizeof(Datapoint));
    

    FILE* fh = fopen(file_name, "r");
    if (!fh)
    {
        printf("Kunne ikke åbne fil!\n");
        return NULL;
    }
    int row = 0;
    int column;
    while (fgets(buffer, 1024, fh))
    {
        column = 0;
        row++;
        /*if (row == 1)  // Fjern denne multiline comments hvis der er descriptions i række 1.
            continue;
        */
        char *value = strtok(buffer, ","); // buffer tokenizes med "," som delimiter.
        
        // Dette loop allokerer memory til tokensne og, copierer tokensne ind på denne plads.
        while (value)
        {
            char *current_token = malloc(strlen(value));
            // Hvis en token konverteres til en værdi (float, int osv.), skal free(current_token); kaldes. 
            // Ellers opstår der et memory leak.

            strcpy(current_token, value);

            if (column == 0)
            {
                (data+(row-1))->kolonne_1 = current_token;
            }
            if (column == 1)
            {
                (data+(row-1))->kolonne_2 = current_token;
            }
            if (column == 2)
            {
                (data+(row-1))->kolonne_3 = strtof(current_token, NULL);
                free(current_token);
            }
            if (column == 3)
            {
                (data+(row-1))->kolonne_4 = current_token;
            }
            
            // Resten af linjen tokenizes.
            value = strtok(NULL, ",");
            column++;

        }
    }


    /* Fjern denne kommentar for at printe de to første rækker.
    for (int i = 0; i < 2; i++)
    {
        printf("%s\n%s\n%f\n%s\n",  (data+i)->kolonne_1,
                                    (data+i)->kolonne_2,
                                    (data+i)->kolonne_3,
                                    (data+i)->kolonne_4);
    }
    */
    fclose(fh);
    return data;

}