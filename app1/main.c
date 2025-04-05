#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "pizza.h"

#define MAX_LINE_LENGTH 1024

typedef char* (*MetricFunc)(int*, Pizza*);

/* 10 métricas */
const char *metric_names[] = {
    "apo","apd","ims","hp","pms","pls","dms","dls","dmsp","dlsp"
};
MetricFunc metrics[] = {
    apo, apd, ims, hp, pms, pls, dms, dls, dmsp, dlsp
};
const int num_metrics = 10;

int main(int argc, char *argv[])
{
    if(argc<3){
        printf("Usage: %s <pizzas.csv> <metric1> [metric2 ...]\n",argv[0]);
        return 1;
    }

    Pizza pizzas[MAX_PIZZAS]; int n;
    if(!read_pizzas(argv[1],pizzas,&n)) return 1;

    for(int i=2;i<argc;++i){
        const char *cmd=argv[i]; bool ok=false;
        for(int j=0;j<num_metrics;++j)
            if(strcmp(cmd,metric_names[j])==0){
                char *res=metrics[j](&n,pizzas);
                printf("%s: %s\n",cmd,res);
                free(res); ok=true; break;
            }
        if(!ok) fprintf(stderr,"Unknown metric: %s\n",cmd);
    }
    return 0;
}
