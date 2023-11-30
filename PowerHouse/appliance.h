
typedef struct Appliance
{
    char name[50]; //Appliance name 
    double wh; // watt hours used per run
    double runTime; // time to run appliance rounded to whole hour

} Appliance;

void ApplianceInsert(Appliance a);
int ApplianceFind(char key[]);
bool ApplianceUpdate(Appliance a);
void ApplianceUpsert(Appliance a);
bool ApplianceRemove(char key[]);
