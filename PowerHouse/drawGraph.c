#include "stdincludes.h"
#include "pbPlots/pbPlots.h"
#include "pbPlots/supportLib.h"
#include "csvRead.h"
#include "drawGraph.h"
#include "graphUtils.h"
#include "Menu.h"

static wchar_t type_strings[MAX_DATA_TYPE][50] = {
        {L"Low Carbon Percent"},
        {L"Renewable Percent"},
        {L"Carbon Intensity Direct"},
        {L"Carbon Intensity LCA"},
};

static wchar_t type_units[MAX_DATA_TYPE][50] = {
        {L"%"},
        {L"%"},
        {L"gCO2eq/kWh"},
        {L"gCO2eq/kWh"},
};


int graph_scatterplot_exec(DataType type, Datapoint *data, struct tm *day)
{
    double hours[24];
    double datapoints[24];
    bool successfull_print;
    
    ScatterPlotSeries *series = GetDefaultScatterPlotSeriesSettings();
    series->xs = hours;
    series->xsLength = 24;
    series->ys = datapoints;
    series->ysLength = 24;
    
    ScatterPlotSettings *settings = default_scatter_settings(series);
    
    wchar_t titlestring[256];
    wcstrftime(titlestring, 256, "%Y/%m/%d ", day);
    wcscat(titlestring, type_strings[type]);
    settings->title = titlestring;
    settings->titleLength = wcslen(titlestring);
    settings->xLabel = L"Hour";
    settings->xLabelLength = wcslen(settings->xLabel);
    settings->yLabel = type_units[type];
    settings->yLabelLength = wcslen(settings->yLabel);
    
    for (int i = 0; i < 24; i++)
    {
        hours[i] = i;
    }
    
    fill_data(type, datapoints, 24, data, day);
    
    wchar_t msg[] = L"Error printing graph!\n";
    size_t msglen = wcslen(msg);
    
    RGBABitmapImageReference *canvasref = CreateRGBABitmapImageReference();
    StringReference *errmsg = CreateStringReference(msg, msglen);
    successfull_print = DrawScatterPlotFromSettings(canvasref, settings, errmsg);
    
    if (successfull_print)
    {
        size_t length;
        double *pngdata = ConvertToPNG(&length, canvasref->image);
        WriteToFile(pngdata, length, "graph.png");
        DeleteImage(canvasref->image);
        free_scatter_settings(settings);
        return 0;
    }
    else
    {
        fprintf(stderr, "Error: ");
        for (int i = 0; i < errmsg->stringLength; i++)
        {
            fprintf(stderr, "%c", errmsg->string[i]);
        }
        fprintf(stderr, "\n");
        free_scatter_settings(settings);
        return 1;
    }
}
int graph_barplot_exec(DataType type, Datapoint *data, struct tm *day)
{
    double datapoints[24];
    bool successfull_print;
    
    BarPlotSeries* series = GetDefaultBarPlotSeriesSettings();
    series->ys = datapoints;
    series->ysLength = 24;
    BarPlotSettings* settings = default_bar_settings(series);
    
    wchar_t titlestring[256];
    wcstrftime(titlestring, 256, "%Y/%m/%d ", day);
    wcscat(titlestring, type_strings[type]);
    settings->title = titlestring;
    settings->titleLength = wcslen(titlestring);
    settings->yLabel = type_units[type];
    settings->yLabelLength = wcslen(settings->yLabel);
    
    
    fill_data(type, datapoints, 24, data, day);
    
    wchar_t msg[] = L"Error printing graph!\n";
    size_t msglen = wcslen(msg);
    
    RGBABitmapImageReference* canvasref = CreateRGBABitmapImageReference();
    StringReference *errmsg = CreateStringReference(msg, msglen);
    successfull_print = DrawBarPlotFromSettings(canvasref, settings, errmsg);
    
    if (successfull_print)
    {
        size_t length;
        double* pngdata = ConvertToPNG(&length, canvasref->image);
        WriteToFile(pngdata, length, "graph.png");
        DeleteImage(canvasref->image);
        free_bar_settings(settings);
        return 0;
    }
    else
    {
        fprintf(stderr, "Error: ");
        for (int i = 0; i < errmsg->stringLength; i++)
        {
            fprintf(stderr, "%c", errmsg->string[i]);
        }
        fprintf(stderr, "\n");
        free_bar_settings(settings);
        return 1;
    }


}

int graph_comparison_scatter_exec(DataType type1, DataType type2, Datapoint *data, tm *day)
{
    double common_xs[24];
    double ys_1[24];
    double ys_2[24];
    
    for (int i = 0; i < 24; i++)
    {
        common_xs[i] = i;
    }
    
    fill_data(type1, ys_1, 24, data, day);
    fill_data(type2, ys_2, 24, data, day);
    
    RGBABitmapImageReference *canvasref1 = CreateRGBABitmapImageReference();
    RGBABitmapImageReference *canvasref2 = CreateRGBABitmapImageReference();
    
    ScatterPlotSeries *series1 = GetDefaultScatterPlotSeriesSettings();
    series1->xs = common_xs;
    series1->xsLength = 24;
    series1->ys = ys_1;
    series1->ysLength = 24;
    
    ScatterPlotSeries *series2 = GetDefaultScatterPlotSeriesSettings();
    series2->xs = common_xs;
    series2->xsLength = 24;
    series2->ys = ys_2;
    series2->ysLength = 24;
    
    wchar_t msg[] = L"Error!";
    StringReference *errmsg = CreateStringReference(msg, wcslen(msg));
    
    RGBABitmapImage *combined = CreateImage(640*2, 720, GetWhite());
    RGBABitmapImage *image1, *image2;
    
    ScatterPlotSettings *settings1 = GetDefaultScatterPlotSettings();
    settings1->title = type_strings[type1];
    settings1->titleLength = wcslen(settings1->title);
    settings1->width = 640;
    settings1->height = 720;
    ScatterPlotSeries **s1 = malloc(sizeof(ScatterPlotSeries));
    s1[0] = series1;
    settings1->scatterPlotSeries = s1;
    settings1->scatterPlotSeriesLength = 1;
    
    ScatterPlotSettings *settings2 = GetDefaultScatterPlotSettings();
    settings2->title = type_strings[type2];
    settings2->titleLength = wcslen(settings2->title);
    settings2->width = 640;
    settings2->height = 720;
    ScatterPlotSeries **s2 = malloc(sizeof(ScatterPlotSeries));
    s2[0] = series2;
    settings2->scatterPlotSeries = s2;
    settings2->scatterPlotSeriesLength = 1;
    
    DrawScatterPlotFromSettings(canvasref1, settings1, errmsg);
    DrawScatterPlotFromSettings(canvasref2, settings2, errmsg);
    
    image1 = canvasref1->image;
    image2 = canvasref2->image;
    
    DrawImageOnImage(combined, image1, 0, 0);
    DrawImageOnImage(combined, image2, 640, 0);
    
    size_t length;
    double *pngdata = ConvertToPNG(&length, combined);
    WriteToFile(pngdata, length, "graph.png");
    DeleteImage(combined);
    free_scatter_settings(settings1);
    free_scatter_settings(settings2);
    return 0;
}

GraphParams graph_input(void)
{
    char GraphType_strings[MAX_GRAPH_TYPE][50] = {
        {"Scatterplot"},
        {"Histogram"},
        {"Comparison"},
    };
    
    char DataType_strings[MAX_DATA_TYPE][50] = {
        {"Low Carbon Percent"},
        {"Renewable Percent"},
        {"Carbon Intensity Direct"},
        {"Carbon Intensity LCA"},
    };
    
    GraphParams input = {0};
    
    printf("Choose a which type of graph you wish to be printed:\n\n");
    
    for (int i = 0; i < MAX_GRAPH_TYPE; i++)
    {
        printf("%d. %s\n", i+1, GraphType_strings[i]);
    }
    
    scanf(" %d", &input.graph_type);
    input.graph_type--;
    while (input.graph_type >= MAX_GRAPH_TYPE)
    {
        printf("Please choose a valid graph type.\n");
        scanf(" %d", &input.graph_type);
        input.graph_type--;
    }
    
    printf("You have chosen: ");
    printf("%s\n", GraphType_strings[input.graph_type]);
    
    printf("Which data do you want to graph?\n\n");
    
    for (int i = 0; i < MAX_DATA_TYPE; i++)
    {
        printf("%d. %s\n", i+1, DataType_strings[i]);
    }
    
    scanf(" %d", &input.data_type);
    input.data_type--;
    while (input.data_type >= MAX_DATA_TYPE)
    {
        printf("Please choose a valid data type.\n");
        scanf(" %d", &input.data_type);
        input.data_type--;
    }
    
    printf("You have chosen: ");
    printf("%s\n", DataType_strings[input.data_type]);
    
    printf("Which day do you wish to see the graph for?\n");
    printf("Please input in format yyyy-MM-dd\n");
    input.day = time_input();
    
    return input;
}

void graph_exec(GraphTypes graph_type, DataType data_type, struct tm day)
{
    int total_rows;
    Datapoint* data = GetCSVData(&total_rows);
    
    switch (graph_type)
    {
    case SCATTERPLOT:
        graph_scatterplot_exec(data_type, data, &day);
        system("graph.png");
        break;
        
    case HISTOGRAM:
        graph_barplot_exec(data_type, data, &day);
        system("graph.png");
        break;
        
    case COMPARISON:
        //clear_terminal();
        printf("Which type do you want to compare to?\n");
        for (size_t i = 0; i < MAX_DATA_TYPE; i++)
        {
            wprintf(L"%d. %s\n", i+1, type_strings[i]);
        }
        
        DataType second_type;
        scanf(" %d", &second_type);
        second_type -= 1;
        printf(L"You have chosen: %s\n", type_strings[second_type]);
        
        graph_comparison_scatter_exec(data_type, second_type, data, &day);
        system("graph.png");
        break;
        
    default:
        break;
    }
}
