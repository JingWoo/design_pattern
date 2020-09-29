#include "ChartDashLine.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct ChartDashLine_Fld {
    char *m_context;
    IChart *m_chart;
};

static void display()
{
    printf("line: ----------------\n");
}

static void destroy(IChart **chart)
{
    assert(chart != NULL && *chart != NULL);
    ChartDashLineDestroy((ChartDashLine **)(&(*chart)->instance));
}

ChartDashLine *ChartDashLineNew()
{
    char *context = strdup("chart dash line");
    ChartDashLine *instance = (ChartDashLine *)calloc(1, sizeof(ChartDashLine));
    assert(instance != NULL);
    instance->pFld = (ChartDashLine_Fld *)calloc(1, sizeof(ChartDashLine_Fld));
    assert(instance->pFld != NULL);
    instance->pFld->m_chart = (IChart *)calloc(1, sizeof(IChart));
    assert(instance->pFld->m_chart != NULL);
    instance->pFld->m_context = context;
    instance->pFld->m_chart->instance = (void *)instance;
    instance->pFld->m_chart->display = display;
    instance->pFld->m_chart->destroy = destroy;

    return instance;
}

IChart *ChartDashLine2IChart(ChartDashLine *pInst)
{
    return pInst->pFld->m_chart;
}

void ChartDashLineDestroy(ChartDashLine **pInst)
{
    ChartDashLine *tmp = (*pInst)->pFld->m_chart->instance;
    assert(pInst != NULL && *pInst != NULL);
    printf("destroy %s\n", (*pInst)->pFld->m_context);
    free((*pInst)->pFld->m_context);
    (*pInst)->pFld->m_context = NULL;
    ChartDashLine_Fld *f = (*pInst)->pFld;
    free((*pInst)->pFld->m_chart);
    // (*pInst)->pFld->m_chart = NULL;
    free((*pInst)->pFld);
    (*pInst)->pFld = NULL;
    free(tmp);
    *pInst = NULL;
}
