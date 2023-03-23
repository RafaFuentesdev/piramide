#ifndef NODO_H
#define NODO_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

class Nodo {
public:
    int id, nivel, fila, columna;
    Nodo* padre;
    int homog;
    int area;
    double capacidad_campo_media;
    int estaciones;
    double pendiente_3clases;
    double porosidad_media;
    double punto_marchitez_medio;
    double umbral_humedo;
    double umbral_intermedio;
    double umbral_seco;
    //constructor por defecto
    Nodo(int id);
    Nodo(int id, double capacidad_campo_media, int estaciones, double pendiente_3clases,
         double porosidad_media, double punto_marchitez_medio, double umbral_humedo,
         double umbral_intermedio, double umbral_seco);
    Nodo();
    bool esHomogenea();
    void setPadre(Nodo& nodo_padre);
    void parricida();
    bool esEnlazable();
    bool esHuerfano();
    bool esFusionable(int area_min);
    Nodo& getPadre();

};

#endif // NODO_H
