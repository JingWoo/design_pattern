#include <stdio.h>
#include <stdlib.h>
#include "SimpleFactory.h"

int main()
{
    IChart *chart = simple_factory_generate_chart(CHART_DASHLINE);
    chart->display();
    chart->destroy(&chart);

    chart = simple_factory_generate_chart(CHART_WAVYLINE);
    chart->display();
    chart->destroy(&chart);

    exit(EXIT_SUCCESS);
}
