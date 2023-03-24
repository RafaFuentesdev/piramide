#ifndef PIRAMIDE_H
#define PIRAMIDE_H

#include "nodo.h"


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <array>


const int FILAS = 6715;
const int COLUMNAS = 13901;

/**
 * @brief Clase Piramide, representa una estructura de pirámide de nodos.
 */
class Piramide {
public:
    // Dimensiones de la base de la pirámide (es cuadrada)
    int num_niv, num_filas, num_columnas;

    // Constructor de la clase
    Piramide() {
        std::cout << std::endl << "Iniciando init()..." << std::endl;
        init();
        std::cout << std::endl << "Iniciando purga()..." << std::endl;
        purga();
        std::cout << std::endl << "Iniciando enlaza()..." << std::endl;
        enlaza();
        std::cout << std::endl << "Iniciando clasifica()..." << std::endl;
        clasifica();
        std::cout << std::endl << "FIN" << std::endl;
    }

    // Métodos para la construcción de la Pirámide
    void init();
    void purga();
    void enlaza();
    void clasifica();

    // Método para obtener el nivel, fila y columna de un nodo dado su ID
    std::tuple<int, int, int> get_nivel_fila_columna(int id);

    // Método para obtener el tamaño (filas y columnas) de un nivel dado
    std::tuple<int, int> getTam(int nivel) const;

    // Métodos para leer e inicializar la Pirámide
    void leerArchivoCSV();
    void inicializarPiramide();
    void inicializarNivelesRestantes();

    // Métodos para comparar nodos y verificar homogeneidad
    bool nodosSonIguales(Nodo& Base_NO, Nodo& Base_NE, Nodo& Base_SO, Nodo& Base_SE);
    bool nodosSonHomogeneos(Nodo& Base_NO, Nodo& Base_NE, Nodo& Base_SO, Nodo& Base_SE);

    // Métodos para enlazar y fusionar nodos
    bool enlazarConMejorCandidato(Nodo& nodo_enlazable);
    bool fusionarConMejorCandidato(Nodo& nodo);
    
    // Métodos para crear e incluir nodos en clases
    void crearClase(Nodo& nodo);
    void incluirEnClase(Nodo &nodo, Nodo &padre);

    // Contenedor de la Pirámide, que almacena nodos en niveles, filas y columnas
    std::vector<std::vector<std::vector<Nodo>>> piramide;
};

#endif // PIRAMIDE_H
