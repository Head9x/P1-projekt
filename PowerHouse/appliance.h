
typedef struct Appliance
{
    char name[50]; //Appliance name 
    double wh; // watt hours used per run
    double runTime; // time to run appliance rounded to whole hour

} Appliance;


void _appliance_Insert(Appliance a);
int _appliance_Find(char key[]);
bool _appliance_Update(Appliance a);
void _appliance_Upsert(Appliance a);
bool _appliance_Remove(char key[]);



 
#define APPLIANCEHEADER