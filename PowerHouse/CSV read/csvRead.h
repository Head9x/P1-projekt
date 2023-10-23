// Denne struct repræsenterer en række i .csv-filen, og skal justeres for at passe til kolonneformatet.
typedef struct Datapoint 
{
    char* kolonne_1;
    char* kolonne_2;
    float kolonne_3;
    char* kolonne_4;
} Datapoint;

Datapoint* readCSV(char *file_name);
