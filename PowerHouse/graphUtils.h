struct tm time_input(void);

size_t wcstrftime(wchar_t *dest, size_t max_len, const char *format, const struct tm *timeptr);

ScatterPlotSettings *default_scatter_settings(ScatterPlotSeries *series);
BarPlotSettings* default_bar_settings(BarPlotSeries* series);

void free_scatter_settings(ScatterPlotSettings *settings);
void free_bar_settings(BarPlotSettings *settings);

void fill_data(DataType type, double *array, size_t array_size, Datapoint *data, struct tm *day);