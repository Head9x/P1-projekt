#include "stdincludes.h"
#include "appliance.h"

int ApplianceCount = 3;
Appliance Appliances[50] = {
    {"vaskemaskine", 100, 1},
    {"toerretumbler", 50, 1.2},
    {"kedel", 20, 3.2},
};

void _appliance_Insert(Appliance a)
{
     Appliances[ApplianceCount++] = a;
}

// returns the index of the element or -1 if not found
int _appliance_Find(char key[])
{
    for (int i = 0; i < ApplianceCount; i++)
    {
        if (strcmp(key, Appliances[i].name) == 0)
        {
            return i;
        }
    }
    return -1;
}

bool _appliance_Update(Appliance a)
{
    int id = _appliance_Find(a.name);
    if (id == -1) return false;

    Appliances[id] = a;

    return true;
}

void _appliance_Upsert(Appliance a)
{
    if (!_appliance_Update(a))
        _appliance_Insert(a);
}

bool _appliance_Remove(char key[])
{
    int id = _appliance_Find(key);
    if (id == -1) return false;

    for (int i = id; i < ApplianceCount - 1; i++)
    {
        Appliances[i] = Appliances[i + 1];
        //for (int j = 0; j < 50; j++) Appliances[i].name[j] = Appliances[i + 1].name[j];
        //Appliances[i].wh = Appliances[i + 1].wh;
        //Appliances[i].runTime = Appliances[i + 1].runTime;
    }

    ApplianceCount--;

    return true;
}
