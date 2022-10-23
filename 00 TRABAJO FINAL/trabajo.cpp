#include <stdio.h>
#include <stdlib.h>

using namespace std;

class Lectura
{
    private:
        struct city;
    public:
        void LeerDatos(FILE);
};

struct city /*Estructura principal*/
{
struct city* next;
struct measurement; 
int cityId;
char cityname [50]; 
};

struct measurement 
{
float temp; 
float hum;
struct timestamp; 
};

struct timestamp 
{
int day; 
int month;
int hh; 
int mm;
};

int main(){
    struct city ciudad;
    struct measurement temps;
    struct timestamp tiempo;
    int provincia=0;
    char data=0;
    FILE *fp;
    fp=fopen("./data_set.txt", "r");
    if (fp==NULL)
    {
        printf("Imposible abrir el archivo");
        exit (1);
    }
    while (!feof(fp))
    {
        fscanf(fp, "%d %d %s %f %f %d %d %d %d", &ciudad.cityId, &provincia, &ciudad.cityname, &temps.temp, &temps.hum, &tiempo.hh, &tiempo.mm, &tiempo.day, &tiempo.month);
        printf("%s\n", ciudad.cityname);
    }
    return 0;
}

