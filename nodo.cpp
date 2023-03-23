#include "nodo.h"

// Constructor por defecto
Nodo::Nodo(int id) : id(id) {
    capacidad_campo_media = -1;
    estaciones = -1;
    pendiente_3clases = -1;
    porosidad_media = -1;
    punto_marchitez_medio = -1;
    umbral_humedo = -1;
    umbral_intermedio = -1;
    umbral_seco = -1;
    homog = -1;
    area = -1;
}

// Constructor con parámetros
Nodo::Nodo(int id, double capacidad_campo_media, int estaciones, double pendiente_3clases,
         double porosidad_media, double punto_marchitez_medio, double umbral_humedo,
         double umbral_intermedio, double umbral_seco)
    : id(id), capacidad_campo_media(capacidad_campo_media), estaciones(estaciones),
      pendiente_3clases(pendiente_3clases), porosidad_media(porosidad_media),
      punto_marchitez_medio(punto_marchitez_medio), umbral_humedo(umbral_humedo),
      umbral_intermedio(umbral_intermedio), umbral_seco(umbral_seco) {}

// Constructor vacío
Nodo::Nodo(){
    capacidad_campo_media = -1;
    estaciones = -1;
    pendiente_3clases = -1;
    porosidad_media = -1;
    punto_marchitez_medio = -1;
    umbral_humedo = -1;
    umbral_intermedio = -1;
    umbral_seco = -1;
    homog = -1;
    area = -1;
}

// Indica si el Nodo es homogéneo
bool Nodo::esHomogenea() {
    return homog == 1;
}

void Nodo::setPadre(Nodo& nodo_padre) {
    padre = &nodo_padre;
}

void Nodo::parricida(){
    if (padre != nullptr) {
        padre = nullptr;
    }
}

bool Nodo::esEnlazable(){
    //falta por implementar
    return true;
}

bool Nodo::esHuerfano(){
    return padre == nullptr;    
}

bool Nodo::esFusionable(int area_min){
    return true;
}

Nodo& Nodo::getPadre() {
    return *padre;
}





