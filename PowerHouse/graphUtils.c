
#include "stdincludes.h"

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

size_t wcstrftime(wchar_t *dest, size_t max_len, const char *format, const struct tm *timeptr)
{
    char *temp = calloc(max_len, sizeof(char));
    if (temp == NULL) {
        return -1;
    } 
        
    strftime(temp, max_len, format, timeptr);

    size_t ret = mbstowcs(dest, temp, max_len);
    free(temp);

    return ret;
}

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

void free_scatter_settings(ScatterPlotSettings *settings)
{
    free(settings->scatterPlotSeries[0]);
    free(settings->scatterPlotSeries);
    free(settings);
}
