
#include "stdincludes.h"

#include "csvRead.h"
#include "drawGraph.h"
#include "pbPlots/pbPlots.h"
#include "pbPlots/supportLib.h"
#include "graphUtils.h"

struct tm time_input(void)
{
    struct tm time_struct;
    time_struct.tm_isdst = -1;
    time_struct.tm_sec = 0;
    time_struct.tm_min = 0;
    time_struct.tm_hour = 0;

    scanf(" %d-%d-%d", &time_struct.tm_year, &time_struct.tm_mon, &time_struct.tm_mday);

    time_struct.tm_year -= 1900;
    time_struct.tm_mon--;

    return time_struct;
}

// Prints a tm struct to a specified format string, placing the result in the wchar_t string dest.
// Returns the succesful amount of wchar_t's printed to the string.
size_t wcstrftime(wchar_t *dest, size_t max_len, const char *format, const struct tm *timeptr)
{
    // Calloc so string by default will be null-terminated.
    char *temp = calloc(max_len+1, sizeof(char));
    if (temp == NULL) {
        return -1;
    }

    strftime(temp, max_len, format, timeptr);

    size_t ret = mbstowcs(dest, temp, max_len);
    free(temp);

    return ret;
}

// Returns pointer to ScatterPlotSettings struct, containing default values for this programs scatterplots.
// This allocates memory, and needs to be freed with the free_scatter_settings function.
ScatterPlotSettings *default_scatter_settings(ScatterPlotSeries *series)
{
    ScatterPlotSettings *settings = GetDefaultScatterPlotSettings();
    settings->width = 1280;
    settings->height = 720;
    settings->autoBoundaries = true;
    settings->autoPadding = true;
    ScatterPlotSeries **s = (ScatterPlotSeries**)malloc(sizeof(ScatterPlotSeries));
    s[0] = series;
    settings->scatterPlotSeries = s;

    settings->scatterPlotSeriesLength = 1;

    return settings;
}
BarPlotSettings *default_bar_settings(BarPlotSeries *series)
{
    BarPlotSettings* settings = GetDefaultBarPlotSettings();
    settings->width = 1280;
    settings->height = 720;
    settings->autoBoundaries = true;
    settings->autoPadding = true;
    settings->autoSpacing = false;
    settings->barBorder = true;
    BarPlotSeries **s = (BarPlotSeries**)malloc(sizeof(BarPlotSeries));
    s[0] = series;
    settings->barPlotSeries = s;
    settings->barPlotSeriesLength = 1;
}


void free_scatter_settings(ScatterPlotSettings *settings)
{
    free(settings->scatterPlotSeries[0]);
    free(settings->scatterPlotSeries);
    free(settings);
}

void free_bar_settings(BarPlotSettings* settings)
{
    free(settings->barPlotSeries[0]);
    free(settings->barPlotSeries);
    free(settings);
}

void fill_data(DataType type, double *array, size_t array_size, Datapoint *data, struct tm *day)
{

    time_t sel_datetime = mktime(day);
    int i = 0;
    while (data[i].datetime != sel_datetime)
    {
        if(i == 8760) break;
        i++;
    }

    switch (type)
    {
    case LOWPERCENT:
    {
        for (int j = 0; j < array_size; j++)
        {
            array[j] = data[j+i].low_percent;
        }
    } break;

    case RENEWPERCENT:
    {
        for (int j = 0; j < array_size; j++)
        {
            array[j] = data[j+i].renew_percent;
        }
    } break;

    case CIDIRECT:
    {
        for (int j = 0; j < array_size; j++)
        {
            array[j] = data[j+i].ci_direct;
        }
    } break;

    case CILCA:
    {
        for (int j = 0; j < array_size; j++)
        {
            array[j] = data[j+i].ci_lca;
        }
    } break;

    default:
        return;
    }
}
