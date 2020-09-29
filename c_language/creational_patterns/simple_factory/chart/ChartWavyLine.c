#include "ChartWavyLine.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct ChartWavyLine_Fld {
    char *m_context;
    IChart *m_chart;
};

static void display()
{
    printf("line: ~~~~~~~~~~~~~~~~\n");
}

static void destroy(IChart **chart)
{
    assert(chart != NULL && *chart != NULL);
    ChartWavyLineDestroy((ChartWavyLine **)(&(*chart)->instance));
}

ChartWavyLine *ChartWavyLineNew()
{
    char *context = strdup("chart wavy line");
    ChartWavyLine *instance = (ChartWavyLine *)calloc(1, sizeof(ChartWavyLine));
    assert(instance != NULL);
    instance->pFld = (ChartWavyLine_Fld *)calloc(1, sizeof(ChartWavyLine_Fld));
    assert(instance->pFld != NULL);
    instance->pFld->m_chart = (IChart *)calloc(1, sizeof(IChart));
    instance->pFld->m_context = context;
    instance->pFld->m_chart->instance = (void *)instance;
    instance->pFld->m_chart->display = display;
    instance->pFld->m_chart->destroy = destroy;

    return instance;
}

IChart *ChartWavyLine2IChart(ChartWavyLine *pInst)
{
    return pInst->pFld->m_chart;
}

void ChartWavyLineDestroy(ChartWavyLine **pInst)
{
    ChartWavyLine *tmp = (*pInst)->pFld->m_chart->instance;
    assert(pInst != NULL && *pInst != NULL);
    printf("destroy %s\n", (*pInst)->pFld->m_context);
    free((*pInst)->pFld->m_context);
    (*pInst)->pFld->m_context = NULL;
    free((*pInst)->pFld->m_chart);
    (*pInst)->pFld->m_chart = NULL;
    free((*pInst)->pFld);
    (*pInst)->pFld = NULL;
    free(tmp);
    *pInst = NULL;
}

