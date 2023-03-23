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
    
    /**
     * @brief Constructor por defecto para la clase Nodo.
     * 
     * @param id Identificador del Nodo (por defecto es -1).
     */
    Nodo(int id = -1);

    /**
     * @brief Verifica si el Nodo es homogéneo.
     * 
     * @return Verdadero si el Nodo es homogéneo, falso en caso contrario.
     */
    bool esHomogeneo();

    /**
     * @brief Establece el Nodo padre del Nodo actual.
     * 
     * @param nodo_padre Referencia al Nodo padre.
     */
    void setPadre(Nodo& nodo_padre);

    /**
     * @brief Obtiene el Nodo padre del Nodo actual.
     * 
     * @return Referencia al Nodo padre.
     */
    Nodo& getPadre();

    /**
     * @brief Elimina la referencia al Nodo padre.
     */
    void parricida();

    /**
     * @brief Verifica si el Nodo es huérfano (no tiene Nodo padre).
     * 
     * @return Verdadero si el Nodo es huérfano, falso en caso contrario.
     */
    bool esHuerfano();

    /**
     * @brief Verifica si el Nodo es enlazable.
     * 
     * @return Verdadero si el Nodo es enlazable, falso en caso contrario.
     */
    bool esEnlazable();

    /**
     * @brief Verifica si el Nodo es fusionable según el área mínima.
     * 
     * @param area_min Área mínima requerida para que el Nodo sea fusionable.
     * @return Verdadero si el Nodo es fusionable, falso en caso contrario.
     */
    bool esFusionable(int area_min);
};

#endif // NODO_H
