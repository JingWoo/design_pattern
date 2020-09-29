#include "SimpleFactory.h"
#include "ChartDashLine.h"
#include "ChartWavyLine.h"
#include <stdio.h>

IChart *simple_factory_generate_chart(ChartType type)
{
    IChart *chart = NULL;
    switch (type) {
        case CHART_DASHLINE:
            chart = ChartDashLine2IChart(ChartDashLineNew());
            break;
        case CHART_WAVYLINE:
            chart = ChartWavyLine2IChart(ChartWavyLineNew());
            break;
        default:
            fprintf(stderr, "Invalid Chart Type!\n");
            break;
    }

    return chart;
}
