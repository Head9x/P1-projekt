typedef struct tm tm;

typedef struct Datapoint
{
    time_t datetime;
    double ci_direct;
    double ci_lca;
    double low_percent;
    double renew_percent;
    
} Datapoint;

Datapoint* readData(char *filename);

