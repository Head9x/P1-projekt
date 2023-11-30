#include "stdincludes.h"
#include "pbPlots/pbPlots.h"
#include "pbPlots/supportLib.h"
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
