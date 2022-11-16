#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Informacion.h"
using namespace std;

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

struct listaciudades /*Estructura principal*/
{
struct listaciudades* next;
int provincia;
char nombreciudad[50]; 
int idciudad;
float suma_temperatura; 
float temp_mascalida;
int dia_mascalido;
int mes_dia_mascalido;
int cont;
};

float CalcularTempPromedio(float,int);
void PromedioCiudades(struct listaciudades*);
void DiasMasCalidosCiudad(struct listaciudades*);
void MejorProvinciaPimientos(Informacion, Informacion, Informacion);
void DiaMasFrioProvincia(struct city*, Informacion);
void CiudadMasFriaProvincia(struct listaciudades*, Informacion, Informacion, Informacion);
void CiudadCalidaProvincia(struct listaciudades*, Informacion, Informacion, Informacion);
void CargaCiudad(struct city*, struct listaciudades*, Informacion*);
void CargaTemps(struct listaciudades*, Informacion*);

int main(){
	struct city* headcordoba=NULL; /*Head para Cordoba*/
	struct city* headmendoza=NULL; /*Head para Mendoza*/
	struct city* headsantafe=NULL; /*Head para Santa Fe*/
	struct city* temp= NULL;
	struct city* new_node=NULL;
    struct city ciudad; /*Estructura auxiliar para cargar datos*/
    struct measurement temps;
    struct timestamp tiempo;
	struct listaciudades* head_ciudades=NULL; /*Estructura de ciudades*/
	struct listaciudades* temp_ciudades= NULL;
	struct listaciudades *new_node_ciudades=NULL;
    int provincia=0;
    char nombrecity[50], opcion=0;
	Informacion mend("Mendoza", 3), cor("Cordoba", 1), stafe("SantaFe",2 ); /*Iniciador de la clase*/
    FILE *fp; 
    fp=fopen("./data_set.txt", "r"); /*Apertura de archivo en modo lectura*/
    if (fp==NULL)
    {
        printf("Imposible abrir el archivo");
        exit (1);
    }
	while (!feof(fp)) /*CREAR ESTRUCTURA PRINCIPAL Y DE CIUDADES*/
    {	
		/*PARTE: PROVINCIAS*/
		fscanf(fp, "%d %d %s %f %f %d %d %d %d", &ciudad.cityId, &provincia, &nombrecity[0], &temps.temperatura, &temps.hum, &tiempo.hh, &tiempo.mm, &tiempo.day, &tiempo.month);
		new_node = (struct city*)malloc(sizeof(struct city));
		if(new_node==NULL){
			printf("No hay memoria disponible");
			exit(1);
		}
		new_node->cityId=ciudad.cityId;/*Declaracion de cityID en el nuevo nodo*/
		strcpy(new_node->cityname, nombrecity);
		new_node->temperaturas.temperatura=temps.temperatura;/*Declaracion de temperatura en el nuevo nodo*/
		new_node->temperaturas.hum=temps.hum;/*Declaracion de humedad en el nuevo nodo*/
		new_node->temperaturas.fecha.month=tiempo.month;/*Declaracion del mes en el nuevo nodo*/
		new_node->temperaturas.fecha.day=tiempo.day;/*Declaracion del dia en el nuevo nodo*/
		new_node->temperaturas.fecha.hh=tiempo.hh;/*Declaracion de la hora en el nuevo nodo*/
		new_node->temperaturas.fecha.mm=tiempo.mm;/*Declaracion de minutos en el nuevo nodo*/
		new_node->next=NULL;/*Si la lista esta vacia, el nodo ingresado es el primero de la lista*/
		if (provincia==3){
			if(headmendoza==NULL){
				headmendoza=new_node;
			}else{
				temp=headmendoza;
				while(temp->next!=NULL){
					temp=temp->next;
				}
				temp->next=new_node;
			}
		}
		else if (provincia==2){
			if(headsantafe==NULL){
				headsantafe=new_node;
			}else{
				temp=headsantafe;
				while(temp->next!=NULL){
					temp=temp->next;
				}
				temp->next=new_node;
			}
		}
		else if (provincia==1){
			if(headcordoba==NULL){
				headcordoba=new_node;
			}else{
				temp=headcordoba;
				while(temp->next!=NULL){
					temp=temp->next;
				}
				temp->next=new_node;
			}	
		}
		else if (provincia>3||provincia<1){
			printf("\nERROR: El codigo %d no pertenece a ninguna provincia\n", provincia);
		}
		/*PARTE: CIUDADES*/	
		bool cargado=0;
		if(head_ciudades==NULL){
			new_node_ciudades = (struct listaciudades*)malloc(sizeof(struct listaciudades));
			if(new_node_ciudades==NULL){
				printf("no hay memoria disponible");
				exit(1);
			}		
			new_node_ciudades->idciudad=ciudad.cityId;
			strcpy(new_node_ciudades->nombreciudad,nombrecity);
			new_node_ciudades->next=NULL;
			if(head_ciudades==NULL){
				head_ciudades=new_node_ciudades;
			}else{
				temp_ciudades=head_ciudades;
				while(temp_ciudades->next!=NULL){
					temp_ciudades=temp_ciudades->next;
				}
				temp_ciudades->next=new_node_ciudades;
			}
		}else{
			temp_ciudades=head_ciudades;
			while(temp_ciudades!=NULL){
				if (temp_ciudades->idciudad==ciudad.cityId)
				{
					cargado=1;
				}
				temp_ciudades = temp_ciudades->next;
			}	
			if (cargado==0)
			{
				new_node_ciudades = (struct listaciudades*)malloc(sizeof(struct listaciudades));
				if(new_node_ciudades==NULL){
					printf("no hay memoria disponible");
					exit(1);
				}		
				new_node_ciudades->idciudad=ciudad.cityId;
				strcpy(new_node_ciudades->nombreciudad,nombrecity);
				new_node_ciudades->next=NULL;
				temp_ciudades=head_ciudades;
				while(temp_ciudades->next!=NULL){
					temp_ciudades=temp_ciudades->next;
				}
				temp_ciudades->next=new_node_ciudades;
			}
								
		}			
    }
	{
	CargaCiudad(headmendoza, head_ciudades, &mend);
	CargaCiudad(headsantafe, head_ciudades, &stafe);
	CargaCiudad(headcordoba, head_ciudades, &cor);
	CargaTemps(head_ciudades, &mend);
	CargaTemps(head_ciudades, &stafe);
	CargaTemps(head_ciudades, &cor);					
	}
	/*MENU DE OPCIONES*/
	do
	{
		printf("\nIngrese la opcion que desee:\n»a- Total de las muestras almacenadas en las listas pertenecientes a cada provincia\n»b- Temperatura promedio de cada provincia\n»c- Temperatura promedio de cada ciudad\n»d- Ciudad mas calida de cada provincia\n»e- Ciudad mas fria de cada provincia\n»f- Dia mas frio de cada provincia\n»g- Dia mas calido de cada ciudad\n»h- Mejor provincia para el cultivo de pimientos\n»s- salir del programa\n");
		scanf(" %c", &opcion);
		switch (opcion)
		{
			case 'a':case 'A':
				printf("\nLa cantidad de muestras tomadas para cada provincia son:\nMendoza: %d\nSanta Fe: %d\nCordoba: %d\n", mend.getCant_tomas(), stafe.getCant_tomas(), cor.getCant_tomas());
			break;
			case 'b':case 'B':
				printf("\nTemperaturas promedio de cada provincia:\nMendoza: %f\nCordoba: %f\nSanta Fe: %f\n", (mend.getPromedio()), (cor.getPromedio()), (stafe.getPromedio()));
			break;
			case 'c':case 'C':
				PromedioCiudades(head_ciudades);
			break;
			case 'd':case 'D':
				CiudadCalidaProvincia(head_ciudades, mend, stafe, cor);
			break;
			case 'e':case 'E':
				CiudadMasFriaProvincia(head_ciudades, mend, stafe, cor);
			break;
			case 'f':case 'F':
				printf("\nDia mas frio de cada provincia:\n");
				DiaMasFrioProvincia(headmendoza, mend);
				DiaMasFrioProvincia(headsantafe, stafe);
				DiaMasFrioProvincia(headcordoba, cor);
			break;
			case 'g':case 'G':
				DiasMasCalidosCiudad(head_ciudades);
			break;
			case 'h':case 'H':
				MejorProvinciaPimientos(mend, stafe, cor);
			break;
			case 's':case 'S':
				printf("\nSaliendo del programa...\n");
			break;
		default:
			printf("\nLa opcion ingresa no existe.\n");
			break;
		}
	} while (opcion!='s'&&opcion!='S');
    return 0;
}

float CalcularTempPromedio(float suma, int cont){
	float promedio=0;
	promedio=suma/cont;
	return promedio;
}

void CargaCiudad(struct city *head_prov, struct listaciudades *head_ciudades, Informacion *prov){
	if(head_prov==NULL){
		printf("Lista vacia\n");
		exit(1);
	}else{
		struct city* temp=head_prov;
		struct listaciudades *temp_ciudades= NULL;
		while(temp!=NULL){
			prov->sumCant_tomas();
			prov->sum_suma(temp->temperaturas.temperatura);
			temp_ciudades=head_ciudades;
			while(temp_ciudades!=NULL){
				if (temp->cityId==temp_ciudades->idciudad)
				{
					temp_ciudades->suma_temperatura=temp_ciudades->suma_temperatura+temp->temperaturas.temperatura;
					if (temp->temperaturas.temperatura>temp_ciudades->temp_mascalida||temp_ciudades->cont==0)
					{
						temp_ciudades->temp_mascalida=temp->temperaturas.temperatura;
						temp_ciudades->dia_mascalido=temp->temperaturas.fecha.day;
						temp_ciudades->mes_dia_mascalido=temp->temperaturas.fecha.month;
						temp_ciudades->provincia=prov->getProvince();
					}
					temp_ciudades->cont++;
				}
				temp_ciudades = temp_ciudades->next;
			}	
			if (temp->temperaturas.temperatura<prov->getTempMin()||prov->getCant_tomas()==0)
			{
				prov->setTempMin(temp->temperaturas.temperatura);
			}
			temp=temp->next;
		}
	}	
}

void CargaTemps(struct listaciudades *head_ciudades, Informacion *prov){
	struct listaciudades *temp_ciudades=head_ciudades;
	while(temp_ciudades!=NULL){
		if (temp_ciudades->provincia==prov->getProvince())
		{
			if (prov->getDataCargada()==0)
			{
				prov->cargarData();
				prov->setCiudadCalida(CalcularTempPromedio(temp_ciudades->suma_temperatura, temp_ciudades->cont));
				prov->setCiudadFria(CalcularTempPromedio(temp_ciudades->suma_temperatura, temp_ciudades->cont));
			}
			if (CalcularTempPromedio(temp_ciudades->suma_temperatura, temp_ciudades->cont)>prov->getCiudadCalida())
			{
				prov->setCiudadCalida(CalcularTempPromedio(temp_ciudades->suma_temperatura, temp_ciudades->cont));
			}
			if (CalcularTempPromedio(temp_ciudades->suma_temperatura, temp_ciudades->cont)<prov->getCiudadFria())
			{
				prov->setCiudadFria(CalcularTempPromedio(temp_ciudades->suma_temperatura, temp_ciudades->cont));
			}
		}	
		temp_ciudades = temp_ciudades->next;
	}						
}

void CiudadCalidaProvincia(struct listaciudades *head_ciudades, Informacion mend, Informacion stafe, Informacion cor){
	struct listaciudades *temp_ciudades= NULL;
	printf("\nCiudad mas calida de cada provincia:\n");
	if(head_ciudades==NULL){
		printf("Lista vacia\n");
		exit(1);
	}else{
		temp_ciudades=head_ciudades;
		while(temp_ciudades!=NULL){
			if (temp_ciudades->provincia==3&&CalcularTempPromedio(temp_ciudades->suma_temperatura, temp_ciudades->cont)==mend.getCiudadCalida())
			{
				printf("En Mendoza la Ciudad: %s\tCon una temperatura promedio de %f\n", temp_ciudades->nombreciudad,	CalcularTempPromedio(temp_ciudades->suma_temperatura, temp_ciudades->cont));
			}
			if (temp_ciudades->provincia==2&&CalcularTempPromedio(temp_ciudades->suma_temperatura, temp_ciudades->cont)==stafe.getCiudadCalida())
			{
				printf("En Santa Fe la Ciudad: %s\tCon una temperatura promedio de %f\n", temp_ciudades->nombreciudad,	CalcularTempPromedio(temp_ciudades->suma_temperatura, temp_ciudades->cont));
			}
			if (temp_ciudades->provincia==1&&CalcularTempPromedio(temp_ciudades->suma_temperatura, temp_ciudades->cont)==cor.getCiudadCalida())
			{
				printf("En Cordoba la Ciudad: %s\tCon una temperatura promedio de %f\n", temp_ciudades->nombreciudad,	CalcularTempPromedio(temp_ciudades->suma_temperatura, temp_ciudades->cont));
			}
			temp_ciudades = temp_ciudades->next;
		}						
	}
}

void PromedioCiudades(struct listaciudades *head_ciudades){
	struct listaciudades *temp_ciudades= NULL;
	if(head_ciudades==NULL){
		printf("Lista vacia\n");
		exit(1);
	}else{
		temp_ciudades=head_ciudades;
		printf("\nTemperatura promedio de cada ciudad:");
		while(temp_ciudades!=NULL){
			printf("\nTemperatura promedio: %f\tCiudad: %s\t", CalcularTempPromedio(temp_ciudades->suma_temperatura, temp_ciudades->cont), temp_ciudades->nombreciudad);
			temp_ciudades = temp_ciudades->next;
		}						
	}
}

void DiaMasFrioProvincia(struct city *head, Informacion info){
	struct city *temp= NULL;
	if(head==NULL){
		printf("Lista vacia\n");
		exit(1);
	}else{
		city*temp=head;
		while(temp!=NULL){
			if (temp->temperaturas.temperatura==info.getTempMin())
			{
				printf("%s: Fecha: %d/%d\tTemperatura: %f\tCiudad:%s\n", info.getNombre().c_str() , temp->temperaturas.fecha.day, temp->temperaturas.fecha.month, info.getTempMin(), temp->cityname);
			}
			temp=temp->next;
		}	
	}
}

void CiudadMasFriaProvincia(struct listaciudades *head_ciudades, Informacion mend, Informacion stafe, Informacion cor){
	struct listaciudades *temp_ciudades= NULL;
	printf("\nCiudad mas fria de cada provincia:\n");
	if(head_ciudades==NULL){
		printf("Lista vacia\n");
		exit(1);
	}else{
		temp_ciudades=head_ciudades;
		while(temp_ciudades!=NULL){
			if (temp_ciudades->provincia==3&&CalcularTempPromedio(temp_ciudades->suma_temperatura, temp_ciudades->cont)==mend.getCiudadFria())
			{
				printf("En Mendoza la Ciudad: %s\tCon una temperatura promedio de %f\n", temp_ciudades->nombreciudad,	CalcularTempPromedio(temp_ciudades->suma_temperatura, temp_ciudades->cont));
			}
			if (temp_ciudades->provincia==2&&CalcularTempPromedio(temp_ciudades->suma_temperatura, temp_ciudades->cont)==stafe.getCiudadFria())
			{
				printf("En Santa Fe la Ciudad: %s\tCon una temperatura promedio de %f\n", temp_ciudades->nombreciudad,	CalcularTempPromedio(temp_ciudades->suma_temperatura, temp_ciudades->cont));
			}
			if (temp_ciudades->provincia==1&&CalcularTempPromedio(temp_ciudades->suma_temperatura, temp_ciudades->cont)==cor.getCiudadFria())
			{
				printf("En Cordoba la Ciudad: %s\tCon una temperatura promedio de %f\n", temp_ciudades->nombreciudad,	CalcularTempPromedio(temp_ciudades->suma_temperatura, temp_ciudades->cont));
			}
			temp_ciudades = temp_ciudades->next;
		}						
	}
}

void DiasMasCalidosCiudad(struct listaciudades *head_ciudades){
	struct listaciudades *temp_ciudades= NULL;
	temp_ciudades=head_ciudades;
	if(head_ciudades==NULL){
		printf("Lista vacia\n");
		exit(1);
	}else{
		printf("\nDia mas calido de cada ciudad:");
		while(temp_ciudades!=NULL){
			printf("\nTemperatura mas calida: %f\tFecha: %d/%d\tCiudad: %s\t", temp_ciudades->temp_mascalida, temp_ciudades->dia_mascalido, temp_ciudades->mes_dia_mascalido, temp_ciudades->nombreciudad);
			temp_ciudades = temp_ciudades->next;
		}						
	}
}

void MejorProvinciaPimientos(Informacion mend, Informacion stafe, Informacion cor){
	int mejor_prov_pimientos=0;
	float comparador_temps=0;
	printf("\nLa mejor provincia para cultivar pimientos ");
	comparador_temps=(mend.getPromedio())-23;
	if (comparador_temps<0) /*Seteo del comparador con la primer provincia para poder comparar*/
	{
		comparador_temps=comparador_temps*(-1);
	}
	mejor_prov_pimientos=3;
	if ((stafe.getPromedio())-23<0) /*Comparacion con Santa Fe*/
	{
		if (((stafe.getPromedio())-23)*(-1)<comparador_temps)
		{
			comparador_temps=((stafe.getPromedio())-23)*(-1);
			mejor_prov_pimientos=2;
		}
	} else if ((stafe.getPromedio())-23<comparador_temps){
		comparador_temps=((stafe.getPromedio())-23)*(-1);
		mejor_prov_pimientos=2;
	}
	if ((cor.getPromedio())-23<0) /*Comparacion con Cordoba*/
	{
		if (((cor.getPromedio())-23)*(-1)<comparador_temps)
		{
			comparador_temps=((cor.getPromedio())-23)*(-1);
			mejor_prov_pimientos=1;
		}
	} else if ((cor.getPromedio())-23<comparador_temps){
		comparador_temps=((cor.getPromedio())-23)*(-1);
		mejor_prov_pimientos=1;
	}
	if (mejor_prov_pimientos==3) /*Imprimir mejor provincia*/
	{
		printf("es Mendoza.\n");
	}
	if (mejor_prov_pimientos==2)
	{
		printf("es Santa Fe.\n");
	}
	if (mejor_prov_pimientos==1)
	{
		printf("es Cordoba.\n");
	}
	if (comparador_temps>3) /*Aviso de diferencia de temperatura alta*/
	{
		printf("Aunque la diferencia de temperatura promedio con la temperatura ideal es de %f grados\n", comparador_temps);
	}
}