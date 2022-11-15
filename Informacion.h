#ifndef informacion_H
#define informacion_H
#include <string>
using namespace std;

class Informacion
{
private:
	int cant;
    float suma;
    float prom;
    float temp_min;
    float ciudad_fria;
    float ciudad_calida;
    int id_provincia;
    bool data_cargada;
    string nombreprovincia;
public:
	Informacion(string, int);
	void sumCant_tomas();
	int getCant_tomas();
    void sum_suma(float);
    float getSuma_total();
    void setPromedio();
    float getPromedio();
    void setTempMin(float);
    float getTempMin();
    void setCiudadFria(float);
    float getCiudadFria();
    void setCiudadCalida(float);
    float getCiudadCalida();
    int getProvince();
    void cargarData();
    bool getDataCargada();
    string getNombre();
	~Informacion();
};

Informacion::Informacion(string nombre, int id)
{
    nombreprovincia=nombre;
    id_provincia=id;
    cant=0;
    suma=0;
    prom=0;
    temp_min=0;
    data_cargada=0;
}

void Informacion::sumCant_tomas(){
	cant=cant+1;
}

int Informacion::getCant_tomas(){
    return cant;
}

void Informacion::sum_suma(float num){
	suma=suma+num;
}

float Informacion::getSuma_total(){
    return suma;
}

void Informacion::setPromedio(){
    prom=suma/cant;
}

float Informacion::getPromedio(){
    setPromedio();
    return prom;
    printf("%f", prom);
}

void Informacion::setTempMin(float temp){
    temp_min=temp;
}

float Informacion::getTempMin(){
    return temp_min;
}

void Informacion::setCiudadFria(float ciudad_fria_){
    ciudad_fria=ciudad_fria_;
}

float Informacion::getCiudadFria(){
    return ciudad_fria;
}

void Informacion::setCiudadCalida(float ciudad_calida_){
    ciudad_calida=ciudad_calida_;
}

float Informacion::getCiudadCalida(){
    return ciudad_calida;
}

string Informacion::getNombre(){
    return nombreprovincia;
}

int Informacion::getProvince(){
    return id_provincia;
}

void Informacion::cargarData(){
    data_cargada=1;
}

bool Informacion::getDataCargada(){
    return data_cargada;
}

Informacion::~Informacion()
{
}

#endif