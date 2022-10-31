#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

class cityclass
{
    private:
        struct timestamp;
		struct measurement;
		struct city;
    public:
        void LeerDatos(FILE);
};

struct timestamp 
{
int day; 
int month;
int hh; 
int mm;
};

struct measurement 
{
float temperatura; 
float hum;
struct timestamp fecha; 
};

struct city /*Estructura principal*/
{
struct city* next;
struct measurement temperaturas; 
int cityId;
char cityname [50]; 
};

int main(){
    struct city* head=NULL;
	struct city* temp= NULL;
	struct city* new_node=NULL;
    struct city ciudad;
    struct measurement temps;
    struct timestamp tiempo;
    int provincia=0;
    char data=0;
    char nombreciudad[50];
    string nombreciudadstring;
    FILE *fp;
    fp=fopen("./data_set.txt", "r");
    if (fp==NULL)
    {
        printf("Imposible abrir el archivo");
        exit (1);
    }
    while (!feof(fp))
    {
        fscanf(fp, "%d %d %s %f %f %d %d %d %d", &ciudad.cityId, &provincia, &nombreciudadstring, &temps.temperatura, &temps.hum, &tiempo.hh, &tiempo.mm, &tiempo.day, &tiempo.month);
        new_node = (struct city*)malloc(sizeof(struct city)+sizeof(struct measurement)+sizeof(struct timestamp));
		if(new_node==NULL){
			printf("No hay memoria disponible");
			exit(1);
		}
		new_node->cityId=ciudad.cityId;/*Declaracion de cityID en el nuevo nodo*/
		new_node->temperaturas.temperatura=temps.temperatura;/*Declaracion de temperatura en el nuevo nodo*/
		new_node->temperaturas.hum=temps.hum;/*Declaracion de humedad en el nuevo nodo*/
		new_node->temperaturas.fecha.month=tiempo.month;/*Declaracion del mes en el nuevo nodo*/
		new_node->temperaturas.fecha.day=tiempo.day;/*Declaracion del dia en el nuevo nodo*/
		new_node->temperaturas.fecha.hh=tiempo.hh;/*Declaracion de la hora en el nuevo nodo*/
		new_node->temperaturas.fecha.mm=tiempo.mm;/*Declaracion de minutos en el nuevo nodo*/
		new_node->next=NULL;/*Si la lista esta vacia, el nodo ingresado es el primero de la lista*/
		if(head==NULL){
			head=new_node;
		}else{
			temp=head;
			while(temp->next!=NULL){
				temp=temp->next;
			}
			temp->next=new_node;
		}
    }
    if(head==NULL){
		printf("Lista vacia\n");
		exit(1);
	}
    return 0;
}
