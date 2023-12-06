typedef enum GraphTypes {
    SCATTERPLOT,
    HISTOGRAM,
    COMPARISON,
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
    struct tm day;
} GraphParams;


GraphParams graph_input(void);
void graph_exec(GraphTypes graph_type, DataType data_type, struct tm day);
int graph_scatterplot_exec(DataType type, Datapoint *data, struct tm *day);
int graph_barplot_exec(DataType type, Datapoint *data, struct tm *day);
int graph_comparison_scatter_exec(DataType type1, DataType type2, Datapoint *data, struct tm *day);
