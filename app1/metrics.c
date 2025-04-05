#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "pizza.h"

/* =========================================================
   1.  utilidades de fecha y tabla de días
   ========================================================= */
static void to_iso_date(const char *src, char *dst)        /* M/D/YYYY → YYYY-MM-DD */
{
    int m,d,y;
    sscanf(src,"%d/%d/%d",&m,&d,&y);
    sprintf(dst,"%04d-%02d-%02d",y,m,d);
}

static void accumulate_date(DateSales days[], int *n,
                            const char *date, int qty, float money)
{
    for(int i=0;i<*n;++i){
        if(strncmp(days[i].date,date,10)==0){
            days[i].total_quantity+=qty;
            days[i].total_money   +=money;
            return;
        }
    }
    strncpy(days[*n].date,date,10); days[*n].date[10]='\0';
    days[*n].total_quantity=qty;
    days[*n].total_money   =money;
    (*n)++;
}

static int build_date_table(Pizza *pizzas,int n,DateSales days[])
{
    int d=0;
    for(int i=0;i<n;++i)
        accumulate_date(days,&d,
                        pizzas[i].order_date,
                        pizzas[i].quantity,
                        pizzas[i].total_price);
    return d;
}

/* =========================================================
   2.  parser CSV
   ========================================================= */
int parse_pizza_line(const char *line, Pizza *p)
{
    float id_tmp, order_tmp; char raw_date[16];

    if(sscanf(line,
        "%f,%f,%[^,],%d,%15[^,],%[^,],%f,%f,%[^,],%[^,],\"%[^\"]\",%[^\n]",
        &id_tmp,&order_tmp,
        p->pizza_name_id,&p->quantity,
        raw_date,p->order_time,
        &p->unit_price,&p->total_price,
        p->pizza_size,p->pizza_category,
        p->pizza_ingredients,p->pizza_name)!=12)
        return 0;

    p->pizza_id=(int)id_tmp;
    p->order_id=(int)order_tmp;
    to_iso_date(raw_date,p->order_date);
    return 1;
}

/* =========================================================
   3.  métricas  (todas devuelven char* malloc‑eado)
   ========================================================= */
typedef struct { char pizza_name[MAX_NAME_LENGTH]; int total_quantity; } PizzaSales;

/* ---------- pms ---------- */
char* pms(int *size, Pizza *pizzas)
{
    PizzaSales sales[MAX_PIZZAS]; int sc=0;
    for(int i=0;i<*size;++i){
        int j; for(j=0;j<sc;++j)
            if(strcmp(sales[j].pizza_name,pizzas[i].pizza_name)==0) break;
        if(j==sc){ strcpy(sales[sc].pizza_name,pizzas[i].pizza_name); sales[sc].total_quantity=0; ++sc; }
        sales[j].total_quantity+=pizzas[i].quantity;
    }
    int idx=0; for(int i=1;i<sc;++i) if(sales[i].total_quantity>sales[idx].total_quantity) idx=i;

    int need=snprintf(NULL,0,"Best Sold Pizza: %s (Total Quantity: %d)",
                      sales[idx].pizza_name,sales[idx].total_quantity)+1;
    char *out=malloc(need);
    snprintf(out,need,"Best Sold Pizza: %s (Total Quantity: %d)",
             sales[idx].pizza_name,sales[idx].total_quantity);
    return out;
}

/* ---------- pls ---------- */
char* pls(int *size, Pizza *pizzas)
{
    PizzaSales sales[MAX_PIZZAS]; int sc=0;
    for(int i=0;i<*size;++i){
        int j; for(j=0;j<sc;++j)
            if(strcmp(sales[j].pizza_name,pizzas[i].pizza_name)==0) break;
        if(j==sc){ strcpy(sales[sc].pizza_name,pizzas[i].pizza_name); sales[sc].total_quantity=0; ++sc; }
        sales[j].total_quantity+=pizzas[i].quantity;
    }
    int idx=0; for(int i=1;i<sc;++i) if(sales[i].total_quantity<sales[idx].total_quantity) idx=i;

    int need=snprintf(NULL,0,"Worst Sold Pizza: %s (Total Quantity: %d)",
                      sales[idx].pizza_name,sales[idx].total_quantity)+1;
    char *out=malloc(need);
    snprintf(out,need,"Worst Sold Pizza: %s (Total Quantity: %d)",
             sales[idx].pizza_name,sales[idx].total_quantity);
    return out;
}

/* ---------- apo ---------- */
char* apo(int *size, Pizza *pizzas)
{
    int orders=0,total=0,last=-1;
    for(int i=0;i<*size;++i){
        total+=pizzas[i].quantity;
        if(pizzas[i].order_id!=last){ ++orders; last=pizzas[i].order_id; }
    }
    float avg=(float)total/orders;
    char *out=malloc(64);
    snprintf(out,64,"Average pizzas per order: %.2f",avg);
    return out;
}

/* ---------- apd ---------- */
char* apd(int *size, Pizza *pizzas)
{
    char dates[MAX_DAYS][11]; int dc=0,total=0;
    for(int i=0;i<*size;++i){
        total+=pizzas[i].quantity;
        int j; for(j=0;j<dc;++j) if(strcmp(dates[j],pizzas[i].order_date)==0) break;
        if(j==dc){ strcpy(dates[dc++],pizzas[i].order_date); }
    }
    float avg=(float)total/dc;
    char *out=malloc(64);
    snprintf(out,64,"Average pizzas per day: %.2f",avg);
    return out;
}

/* ---------- ims ---------- */
char* ims(int *size, Pizza *pizzas)
{
    struct { char name[64]; int cnt; } ing[1000]; int ic=0;
    for(int i=0;i<*size;++i){
        char buf[MAX_INGREDIENTS_LENGTH]; strcpy(buf,pizzas[i].pizza_ingredients);
        for(char *tok=strtok(buf,","); tok; tok=strtok(NULL,",")){
            while(*tok==' ') ++tok;
            int j; for(j=0;j<ic;++j) if(strcmp(ing[j].name,tok)==0) break;
            if(j==ic){ strcpy(ing[ic].name,tok); ing[ic].cnt=0; ++ic; }
            ing[j].cnt+=pizzas[i].quantity;
        }
    }
    int idx=0; for(int i=1;i<ic;++i) if(ing[i].cnt>ing[idx].cnt) idx=i;
    int need=snprintf(NULL,0,"Most used ingredient: %s (%d units)",
                      ing[idx].name,ing[idx].cnt)+1;
    char *out=malloc(need);
    snprintf(out,need,"Most used ingredient: %s (%d units)",
             ing[idx].name,ing[idx].cnt);
    return out;
}

/* ---------- hp ---------- */
char* hp(int *size, Pizza *pizzas)
{
    struct { char cat[MAX_NAME_LENGTH]; int cnt; } cat[100]; int cc=0;
    for(int i=0;i<*size;++i){
        int j; for(j=0;j<cc;++j) if(strcmp(cat[j].cat,pizzas[i].pizza_category)==0) break;
        if(j==cc){ strcpy(cat[cc].cat,pizzas[i].pizza_category); cat[cc].cnt=0; ++cc; }
        cat[j].cnt+=pizzas[i].quantity;
    }

    /* construir string dinámico */
    size_t buf=64; char *out=malloc(buf); out[0]='\0';
    strcat(out,"Pizza count by category:\n");
    for(int i=0;i<cc;++i){
        char line[160];
        snprintf(line,sizeof line,"- %s: %d\n",cat[i].cat,cat[i].cnt);
        size_t need=strlen(out)+strlen(line)+1;
        if(need>buf){ buf*=2; out=realloc(out,buf); }
        strcat(out,line);
    }
    return out;
}

/* ---------- dms ---------- */
char* dms(int *size, Pizza *pizzas)
{
    DateSales days[MAX_DAYS]; int d=build_date_table(pizzas,*size,days);
    if(d==0) return strdup("No data");
    int idx=0; for(int i=1;i<d;++i) if(days[i].total_money>days[idx].total_money) idx=i;
    char *out=malloc(64);
    snprintf(out,64,"%s $%.2f",days[idx].date,days[idx].total_money);
    return out;
}

/* ---------- dls ---------- */
char* dls(int *size, Pizza *pizzas)
{
    DateSales days[MAX_DAYS]; int d=build_date_table(pizzas,*size,days);
    if(d==0) return strdup("No data");
    int idx=0; for(int i=1;i<d;++i) if(days[i].total_money<days[idx].total_money) idx=i;
    char *out=malloc(64);
    snprintf(out,64,"%s $%.2f",days[idx].date,days[idx].total_money);
    return out;
}

/* ---------- dmsp ---------- */
char* dmsp(int *size, Pizza *pizzas)
{
    DateSales days[MAX_DAYS]; int d=build_date_table(pizzas,*size,days);
    if(d==0) return strdup("No data");
    int idx=0; for(int i=1;i<d;++i) if(days[i].total_quantity>days[idx].total_quantity) idx=i;
    char *out=malloc(64);
    snprintf(out,64,"%s %d pizzas",days[idx].date,days[idx].total_quantity);
    return out;
}

/* ---------- dlsp ---------- */
char* dlsp(int *size, Pizza *pizzas)
{
    DateSales days[MAX_DAYS]; int d=build_date_table(pizzas,*size,days);
    if(d==0) return strdup("No data");
    int idx=0; for(int i=1;i<d;++i) if(days[i].total_quantity<days[idx].total_quantity) idx=i;
    char *out=malloc(64);
    snprintf(out,64,"%s %d pizzas",days[idx].date,days[idx].total_quantity);
    return out;
}

/* =========================================================
   4.  lectura de CSV (usada por main.c)
   ========================================================= */
int read_pizzas(const char *file, Pizza pizzas[], int *n)
{
    FILE *fp=fopen(file,"r"); if(!fp){ perror(file); return 0; }
    char line[1024]; *n=0;
    fgets(line,sizeof line,fp);               /* descarta cabecera */
    while(fgets(line,sizeof line,fp) && *n<MAX_PIZZAS){
        if(parse_pizza_line(line,&pizzas[*n])) ++(*n);
    }
    fclose(fp); return 1;
}
