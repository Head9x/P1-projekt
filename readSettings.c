
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LINEMAX 100
#define USERVARMAX 100

char line[LINEMAX];
char userVar[USERVARMAX] = {0};
char output[50];

char *readSettings();

int main()
{
    printf("Input variable: ");
    scanf("%100s", &userVar[0]);
    printf("The user has input: %s\n", userVar);

    readSettings();

    return 0;
}

char *readSettings()
{
    int matchFound = 0;

    // Read file
    FILE *settings = fopen("settings.txt", "r+");

    // For each line in file
    while (fgets(line, LINEMAX, settings))
    {
        // printf("Printing line: %s", line);

        // Split line into parts divided by space
        char *strToken = strtok(line, " ");
        while (strToken != NULL) // splits string again until end of string is found
        {
            if (strstr(strToken, userVar) != 0) // strstr returns address of first match, if there is no match returns 0
            {
                printf("\nsplitString \"%s\" is equal to userVar\n", strToken);
                matchFound = 1;
            }
            strToken = strtok(NULL, " "); // goto next strToken

            if (matchFound == 1)
            {
                // printf("\nCHECK\n");
                printf("Printing strToken: %s", strToken);

                char *output = strtok(strToken, ";");
                printf("Printing output: %s\n", output);

                matchFound = 0;
                // Close file
                fclose(settings);
                return output;
            }
        }
    }
    // Close file
    fclose(settings);
    return 0;
}