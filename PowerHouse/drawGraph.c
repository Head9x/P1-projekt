#include "stdincludes.h"
#include "pbPlots/pbPlots.h"
#include "pbPlots/supportLib.h"
#include "csvRead.h"
#include "drawGraph.h"



bool draw_scatterplot(GraphParams data)
{
    double *xs = data.x;
    int x_len = data.x_points;
    double *ys = data.y;
    int y_len = data.y_points;
    bool success;
    
    RGBABitmapImageReference *canvasref = CreateRGBABitmapImageReference();
    StringReference *errMsg = CreateStringReference(L"ERR!", 4);
    success = DrawScatterPlot(canvasref, 1280, 720, xs, x_len, ys, y_len, errMsg);

    printf("%d\n", success);

    if (success)
    {
        size_t length;
        double* pngdata = ConvertToPNG(&length, canvasref->image);
        WriteToFile(pngdata, length, "TestGraph.png");
        DeleteImage(canvasref->image);
    }
    else {
        fprintf(stderr, "Error: ");
        for (int i = 0; i < errMsg->stringLength; i++)
        {
            fprintf(stderr, "%c", errMsg->string[i]);
        }
        fprintf(stderr, "\n");
    }
    
    return success;
}

int graph_exec(DataType type, Datapoint *data, time_t day)
{
    double hours[24];
    double datapoints[24];
    bool successfull_print;

    for (int i = 0; i < 24; i++)
    {
        hours[i] = i;
    }

    int i = 0;
    while (data[i].datetime != day) 
    {
        if(i == 8760) break;
        i++;
    }
    if(i == 8760) return 1;
    

    switch (type)
    {
    case LOWPERCENT:
    {
        for (int j = 0; j < 24; j++)
        {
            datapoints[j] = data[j+i].low_percent;
        }
    } break;

    case RENEWPERCENT:
    {
        for (int j = 0; j < 24; j++)
        {
            datapoints[j] = data[j+i].renew_percent;
        }        
    } break;

    case CIDIRECT:
    {
        for (int j = 0; j < 24; j++)
        {
            datapoints[j] = data[j+i].ci_direct;
        }
    } break;

    case CILCA:
    {
        for (int j = 0; j < 24; j++)
        {
            datapoints[j] = data[j+i].ci_lca;
        }
    } break;
    default:
        return 1;
    }

    wchar_t msg[] = L"Error printing graph!\n";
    size_t msglen = wcslen(msg);

    RGBABitmapImageReference *canvasref = CreateRGBABitmapImageReference();
    StringReference *errmsg = CreateStringReference(msg, msglen);
    successfull_print = DrawScatterPlot(canvasref, 1280, 720, hours, 24, datapoints, 24, errmsg);

    if (successfull_print)
    {
        
    }
    

}
