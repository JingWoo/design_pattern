#ifndef __CHART_DASHLINE_H
#define __CHART_DASHLINE_H
#include "IChart.h"

typedef struct ChartDashLine_Fld ChartDashLine_Fld;

typedef struct _ChartDashLine {
    ChartDashLine_Fld *pFld;
} ChartDashLine;

ChartDashLine *ChartDashLineNew();
IChart *ChartDashLine2IChart(ChartDashLine *pInst);
void ChartDashLineDestroy(ChartDashLine **pInst);

#endif
