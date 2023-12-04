#include "stdincludes.h"
#include "appliance.h"
#include "csvRead.h"
#include "drawGraph.h"

#include "Menu.h"

extern Appliance Appliances[50];
extern int ApplianceCount;

void appliance_print_function(void)
{
    clear_terminal();
    for (int i = 0; i < ApplianceCount; i++) {
        Appliance app = Appliances[i];
        printf("Appliance %d \n", i + 1);
        printf("name: %s \n", app.name);
        printf("wh %lf \n", app.wh);
        printf("runTime %lf \n\n", app.runTime);
    }

    printf("------------------------------------------\n");
    printf("Press any key + ENTER to continue\n\n");
    standardScan(); // wait for user to proceed
}
void appliance_upsert_function(void)
{
    clear_terminal();
    Appliance a;

    printf("Enter appliance name: ");
    scanf(" %s", &a.name);
    printf("Enter appliance wh: ");
    scanf(" %lf", &a.wh);
    printf("Enter appliance runTime: ");
    scanf(" %lf", &a.runTime);
    ApplianceUpsert(a);

    printf("Update succesful \n");
}
void appliance_remove_function(void)
{
    clear_terminal();
    char c[100];

    printf("Enter appliance name: ");
    scanf(" %s", &c);

    printf("appliance removed %s \n", ApplianceRemove(c) ? "Successfully" : "Unsuccessfully");
}

void data_print_function(void)
{
    int total_rows;
    Datapoint* data = readCSV("datafiler/DK-DK2_2022_hourly.csv", &total_rows, true);
    for (int i = 0; i < total_rows; i++)
    {
        Datapoint p = data[i];
        printf("[%d]: %.1lf%%\n", i + 1, p.renew_percent);
    }
}


void graph_draw(void)
{
    GraphParams input = graph_input();

    graph_exec(input);
}
