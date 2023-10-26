typedef struct tm tm;

// Data structure for the relevant data of a row from the .csv-file.
typedef struct Datapoint
{
    time_t datetime;
    double ci_direct;
    double ci_lca;
    double low_percent;
    double renew_percent;
    
} Datapoint;

// Read the .csv-file. Returns a pointer to an array of the type Datapoint.
Datapoint* readData(char *filename);

