#ifndef __SIMPLE_FACTORY_H
#define __SIMPLE_FACTORY_H
#include "IChart.h"

typedef enum _ChartType {
    CHART_DASHLINE = 0,
    CHART_WAVYLINE = 1,
    CHART_MAX
} ChartType;

IChart *simple_factory_generate_chart(ChartType type);

#endif
