typedef enum GraphTypes {
    SCATTERPLOT,
    MAX_GRAPH_TYPE,
    
} GraphTypes;

typedef enum DataType {
    LOWPERCENT,
    RENEWPERCENT,
    CIDIRECT,
    CILCA,
    MAX_DATA_TYPE,
} DataType;

typedef struct GraphParams
{
    GraphTypes graph_type;
    DataType data_type;
    time_t day;
    time_t secondday;
} GraphParams;

GraphParams graph_input();
void graph_exec(GraphParams graph_input);
int graph_scatterplot_exec(DataType type, Datapoint *data, time_t day);
int graph_boxplot_exec(DataType type, Datapoint *data, time_t first_day, time_t last_day);