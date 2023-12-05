#include "stdincludes.h"
#include "appliance.h"
#include "csvRead.h"
#include "drawGraph.h"
#include <math.h>

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
        printf("[%d]: CI_Direct [%.2lf] CI_LCA[%.2lf] \tlow_percent [%.1lf%%] renew_percent [%.1lf%%] \t%s", // note asctime appends a new line so time has to be last
            i + 1, p.ci_direct, p.ci_lca, p.low_percent, p.renew_percent, asctime(gmtime(&p.datetime)));
    }
    free(data);
}


void graph_draw(void)
{
    GraphParams input = graph_input();
    
    graph_exec(input.graph_type, input.data_type, input.day);
}

void calculate_appliance_run(void) 
{
    clear_terminal();
// specify appliance
    int app_index = -1;
    while (app_index == -1)
    {
        char app_name[50];
        printf("Choose an appliance between among: \t[");
        for (int i = 0; i < ApplianceCount; i++)
            printf("%s%s%s",
                (i % 10) == 5 ? "\n" : "", // add new line for every 10th item
                Appliances[i].name,
                (i + 1) == ApplianceCount ? "] \n" : ", "); //if last, terminate the list and set new line. if not last separate value with comma.

        scanf(" %49s", &app_name);
        app_index = ApplianceFind(app_name);
    }

    Appliance app = Appliances[app_index];

// specify date  
    tm day;
    day.tm_year = 2022;
    day.tm_min = 0;
    day.tm_sec = 0;
    day.tm_isdst = -1;
    printf("Which start time do you wish to calculate for?\n");
    printf("Please input in format MM-dd-hh\n");
    scanf(" %d-%d-%d", &day.tm_mon, &day.tm_mday, &day.tm_hour);

    day.tm_year -= 1900;
    day.tm_mon -= 1;

    time_t start_time = mktime(&day);
    day.tm_mday += (int)floor(app.runTime);
    time_t stop_time = mktime(&day);

//run 
    int total_rows;
    Datapoint* data = readCSV("datafiler/DK-DK2_2022_hourly.csv", &total_rows, true);
    Datapoint* start_point;
    for(start_point = data; start_point < data+total_rows; start_point++)
    {
        if (start_point->datetime >= start_time)
            break;
    }
    // calculate if running now
    int runtime_integer = (int)floor(app.runTime);
    double runtime_decimal = app.runTime - floor(app.runTime);
    bool is_runtime_decimal = 0 > runtime_decimal;
    
    double now = 0;
    for (int i = 0; i < app.runTime; i++)
        now += app.wh * start_point[i].ci_lca;
    //now += is_runtime_decimal ? start_point[runtime_integer + 1].ci_lca * runtime_decimal : 0; TODO deal with non-integer values

// find best sequence
    int best_index = 0;
    double best_value = now, 
        intermediate_value = now;

    for (int i = 1; start_point[i].datetime <= stop_time; i++) // TODO deal with non-integer values
    {
        intermediate_value += start_point[runtime_integer + i].ci_lca - start_point[i - 1].ci_lca;
        if (intermediate_value > best_value) {
            best_index = i;
            best_value = intermediate_value;
        }
    }

// print best vs now
    if (best_index) 
    {
        printf("The best time to turn on %s is in %d hours. \nDoing so will save the environment %.2lf gram of carbon dioxide\n", app.name, best_index, (best_value - now) * app.wh / 1000);
    }
    else 
    {
        printf("The best time on %s is now\n", app.name);
    }

    free(data);
}
