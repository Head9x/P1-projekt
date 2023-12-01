typedef struct tm tm;

// Data structure for the relevant data of a row from the .csv-file.
struct Datapoint
{
    time_t datetime;
    double ci_direct;
    double ci_lca;
    double low_percent;
    double renew_percent;
    
};

typedef struct Datapoint Datapoint;
// Read the .csv-file. Returns a pointer to an array of the type Datapoint.
Datapoint* readCSV(char *filename, int *rows);
