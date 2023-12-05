typedef enum GraphTypes {
    SCATTERPLOT,
    HISTOGRAM,
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
    tm day;
} GraphParams;

GraphParams graph_input();
void graph_exec(GraphParams input);
int graph_scatterplot_exec(DataType type, Datapoint *data, tm *day);
