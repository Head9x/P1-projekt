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
Datapoint* readCSV(FILE* fh, int *rows, const bool has_header);

// Sets the file path to the csv data file and reads the file for further processing
void SetCSVPath(const char* filename, const bool has_header);

// Retrieves the data of the csv data file
Datapoint* GetCSVData(int* rows_out);

