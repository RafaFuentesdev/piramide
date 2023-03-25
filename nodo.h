#ifndef NODO_H
#define NODO_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

/**
 * @brief Clase Nodo que representa un nodo en una estructura de datos tipo Pirámide.
 */
class Nodo {
public:
    // Variables miembro que almacenan información relevante del nodo
    int id, nivel, fila, columna;
    Nodo* padre;
    //añadir la lista de  hijos.
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

    // Constructor de la clase Nodo
    Nodo(int id = -1);

    // Método para verificar si el nodo es homogéneo
    bool esHomogeneo();

    // Métodos para establecer y obtener el nodo padre
    void setPadre(Nodo& nodo_padre);
    Nodo& getPadre();

    // Método para liberar al nodo de su padre
    void parricida();

    // Método para verificar si el nodo no tiene padre (es huérfano)
    bool esHuerfano();

    // Método para verificar si el nodo es enlazable
    bool esEnlazable();

    // Método para verificar si el nodo es fusionable
    bool esFusionable(int area_min);

    // Reinicia los valores de las variables miembro del nodo a sus valores predeterminados
    void reset();
};

#endif // NODO_H
