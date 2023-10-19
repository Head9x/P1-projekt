#include <stdio.h>
#include <stdlib.h>
#include "setSettings.h"

int main(void)
{
 setSettings();
}

void setSettings(){

    int startHour = 0, 
        endHour = 0, 
        carbonPercent = 0;

    // Takes user input
    printf("Input start time: ");
    scanf(" %d", &startHour);

    printf("Input slut time: ");
    scanf(" %d", &endHour);

    // Saves user input to file
    FILE *settings = fopen("settings.txt", "w");
    fprintf(settings, "startHour %d;\nendHour %d;\n", startHour, endHour);

    /*
    SHOW USER MAX MIN CARBON
    */

    printf("Input min acceptable carbon %%: ");
    scanf(" %d", &carbonPercent);
    fprintf(settings, "carbonPercent %d;\n", carbonPercent);

    // Close file
    fclose(settings);

    return 0;

}