#ifndef __CHART_WAVYLINE_H
#define __CHART_WAVYLINE_H
#include "IChart.h"

typedef struct ChartWavyLine_Fld ChartWavyLine_Fld;
typedef struct _ChartWavyLine ChartWavyLine;

typedef struct _ChartWavyLine {
    ChartWavyLine_Fld *pFld;
} ChartWavyLine;

ChartWavyLine *ChartWavyLineNew();
IChart *ChartWavyLine2IChart(ChartWavyLine *pInst);
void ChartWavyLineDestroy(ChartWavyLine **pInst);

#endif
