#include "nodo.h"

/**
 * @brief Constructor por defecto para la clase Nodo.
 * 
 * @param id Identificador del Nodo (por defecto es -1).
 */
Nodo::Nodo(int id = -1)
    : id{id}, capacidad_campo_media{-1}, estaciones{-1}, pendiente_3clases{-1},
      porosidad_media{-1}, punto_marchitez_medio{-1}, umbral_humedo{-1},
      umbral_intermedio{-1}, umbral_seco{-1}, homog{-1}, area{-1}, padre{nullptr} {}

/**
 * @brief Verifica si el Nodo es homogéneo.
 * 
 * @return Verdadero si el Nodo es homogéneo, falso en caso contrario.
 */
bool Nodo::esHomogeneo() {
    return homog == 1;
}

/**
 * @brief Establece el Nodo padre del Nodo actual.
 * 
 * @param nodo_padre Referencia al Nodo padre.
 */
void Nodo::setPadre(Nodo& nodo_padre) {
    padre = &nodo_padre;
}

/**
 * @brief Obtiene el Nodo padre del Nodo actual.
 * 
 * @return Referencia al Nodo padre.
 */
Nodo& Nodo::getPadre() {
    return *padre;
}

/**
 * @brief Elimina la referencia al Nodo padre.
 */
void Nodo::parricida(){
    padre = nullptr;
}

/**
 * @brief Verifica si el Nodo es huérfano (no tiene Nodo padre).
 * 
 * @return Verdadero si el Nodo es huérfano, falso en caso contrario.
 */
bool Nodo::esHuerfano(){
    return padre == nullptr;    
}

/**
 * @brief Verifica si el Nodo es enlazable.
 * 
 * @return Verdadero si el Nodo es enlazable, falso en caso contrario.
 */
bool Nodo::esEnlazable(){
    // Falta por implementar
    return true;
}

/**
 * @brief Verifica si el Nodo es fusionable según el área mínima.
 * 
 * @param area_min Área mínima requerida para que el Nodo sea fusionable.
 * @return Verdadero si el Nodo es fusionable, falso en caso contrario.
 */
bool Nodo::esFusionable(int area_min){
    //Falta por implementar
    return true;
}





