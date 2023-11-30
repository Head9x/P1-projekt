typedef enum GraphTypes {
    BOXPLOT,
    SCATTERPLOT,
    
} GraphTypes;

typedef struct GraphParams
{
    GraphTypes type;
    double *x;
    int x_points;
    double *y;
    int y_points;
} GraphParams;

bool draw_scatterplot(GraphParams data);