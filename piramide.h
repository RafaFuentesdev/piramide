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

class Piramide {
public:
    // dimension de la base de la piramide (es cuadrada)
    int num_niv, num_filas, num_columnas;

    // Constructor de la clase
    Piramide() {
        init();
        //purga();
        //enlaza();
        //clasifica();
    }

    void init();
    void purga();
    void enlaza();
    void clasifica();

    std::tuple<int, int, int> get_nivel_fila_columna(int id);
    std::tuple<int, int> getTam(int nivel) const;

    void leerArchivoCSV();
    void inicializarPiramide();
    void inicializarNivelesRestantes();

    bool nodosSonIguales(Nodo& Base_NO, Nodo& Base_NE, Nodo& Base_SO, Nodo& Base_SE);
    bool nodosSonHomogeneos(Nodo& Base_NO, Nodo& Base_NE, Nodo& Base_SO, Nodo& Base_SE);
    bool enlazarConMejorCandidato(Nodo& nodo_enlazable);
    bool fusionarConMejorCandidato(Nodo& nodo);
    void crearClase(Nodo& nodo);
    void incluirEnClase(Nodo &nodo, Nodo &padre);


    //std::pair<int, int> getTam(int i_niv);

    //Nodo& get_Nodo(int nivel, int fila, int columna);

    //Nodo& get_Nodo_id(int id);

    //int get_id(int nivel, int fila, int columna);
    std::vector<std::vector<std::vector<Nodo>>> piramide;

};



#endif // PIRAMIDE_H
