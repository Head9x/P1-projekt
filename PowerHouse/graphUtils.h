struct tm time_input(void);

size_t wcstrftime(wchar_t *dest, size_t max_len, const char *format, const struct tm *timeptr);

ScatterPlotSettings *default_scatter_settings(ScatterPlotSeries *series);

void free_scatter_settings(ScatterPlotSettings *settings);