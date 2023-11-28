#include <string.h>

typedef struct Appliance
{
    char name[50]; //Appliance name 
    double wh; // watt hours used per run
    double runTime; // time to run appliance rounded to whole hour

} Appliance;
