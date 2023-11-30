typedef enum GraphTypes {
    BOXPLOT,
    SCATTERPLOT,
    
} GraphTypes;

typedef enum DataType {
    LOWPERCENT,
    RENEWPERCENT,
    CIDIRECT,
    CILCA
} DataType;

typedef struct GraphParams
{
    GraphTypes type;
    double *x;
    int x_points;
    double *y;
    int y_points;
    time_t time;
} GraphParams;

bool draw_scatterplot(GraphParams data);
bool draw_date_scatterplot(double *time, double *data);
int graph_exec(DataType type, Datapoint *data, time_t day);
