#include "piramide.h"

void Piramide::init(){
    std::cout << "Incializando datos de la piramide..." << std::endl;
    inicializarPiramide();
    std::cout << "Leyendo datos del archivo CSV..." << std::endl;
    leerArchivoCSV();
    std::cout << "Inicializando niveles restantes..." << std::endl;
    inicializarNivelesRestantes();
    std::cout << "Base creada." << std::endl;    
}

/**
 * @brief Inicializa la estructura de datos de la pirámide, estableciendo las dimensiones y configurando los nodos.
 * 
 * Esta función crea una pirámide de niveles basada en las constantes FILAS y COLUMNAS, donde cada nivel es una matriz
 * de nodos. El número de niveles se calcula a partir de las dimensiones de la base de la pirámide.
 * 
 * La función inicializa cada nodo con un identificador único, nivel, fila y columna correspondientes. Luego, se añade
 * cada nivel a la estructura pirámide. 
 *
 */
void Piramide::inicializarPiramide(){
    // Establecer el tamaño de la pirámide utilizando las constantes FILAS y COLUMNAS
    num_filas = FILAS;
    num_columnas = COLUMNAS;

    // Calcular el número de niveles a partir de las dimensiones de la base de la pirámide
    num_niv = static_cast<int>(floor(log2(std::max(num_filas, num_columnas))) + 1);

    // Reservar memoria para el número de niveles en la pirámide
    piramide.reserve(num_niv);
    
    int id_nodo = 0;
    // Recorrer todos los niveles de la pirámide
    for (int n = 0; n < num_niv; n++) {
        int tam_fila, tam_columna;
        // Obtener el tamaño del nivel actual
        std::tie(tam_fila, tam_columna) = getTam(n);

        // Inicializar la matriz del nivel actual
        std::vector<std::vector<Nodo>> level(tam_fila, std::vector<Nodo>(tam_columna));
        
        // Recorrer las filas y columnas del nivel actual
        for (int i = 0; i < tam_fila; i++) {
            for (int j = 0; j < tam_columna; j++) {
                Nodo& Nodoi = level[i][j];
                // Inicializar el nodo con un identificador único
                Nodoi = Nodo(id_nodo);
                // Establecer las propiedades del nodo: nivel, fila y columna
                Nodoi.nivel = n;
                Nodoi.fila = i;
                Nodoi.columna = j;

                id_nodo++;
            }
        }
        // Añadir el nivel inicializado a la estructura de la pirámide
        piramide.push_back(std::move(level));
    }
}


/**
 * @brief Lee los datos de un archivo CSV y asigna los valores a los nodos de la pirámide.
 * 
 * Esta función lee un archivo CSV llamado "completo0.csv" y extrae los datos para cada nodo.
 * A continuación, asigna los valores extraídos a las propiedades de los nodos correspondientes en
 * la estructura de la pirámide.
 * 
 */
void Piramide::leerArchivoCSV() {
    // Abrir el archivo CSV
    std::ifstream file("completo0.csv");
    if (!file) {
        throw std::runtime_error("Error: no se pudo abrir el archivo.");
        return;
    }

    std::string line;

    // Leer encabezado
    std::getline(file, line);

    // Leer y procesar cada línea del archivo CSV
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string id_str, capacidad_campo_media_str, estaciones_str, pendiente_3clases_str,
                    porosidad_media_str, punto_marchitez_medio_str, umbral_humedo_str,
                    umbral_intermedio_str, umbral_seco_str;

        // Extraer los valores de la línea actual
        std::getline(ss, id_str, ',');
        std::getline(ss, capacidad_campo_media_str, ',');
        std::getline(ss, estaciones_str, ',');
        std::getline(ss, pendiente_3clases_str, ',');
        std::getline(ss, porosidad_media_str, ',');
        std::getline(ss, punto_marchitez_medio_str, ',');
        std::getline(ss, umbral_humedo_str, ',');
        std::getline(ss, umbral_intermedio_str, ',');
        std::getline(ss, umbral_seco_str, ',');

        // Convertir los valores extraídos a sus tipos correspondientes
        int id = std::stoi(id_str);
        double capacidad_campo_media = std::stod(capacidad_campo_media_str);
        int estaciones = std::stoi(estaciones_str);
        double pendiente_3clases = std::stod(pendiente_3clases_str);
        double porosidad_media = std::stod(porosidad_media_str);
        double punto_marchitez_medio = std::stod(punto_marchitez_medio_str);
        double umbral_humedo = std::stod(umbral_humedo_str);
        double umbral_intermedio = std::stod(umbral_intermedio_str);
        double umbral_seco = std::stod(umbral_seco_str);

        // Encontrar el nodo correspondiente en la pirámide
        int nivel, fila, columna;
        std::tie(nivel, fila, columna) = get_nivel_fila_columna(id);
        Nodo& Nodoi = piramide[nivel][fila][columna];

        // Asignar los valores extraídos a las propiedades del nodo
        Nodoi.nivel = nivel;
        Nodoi.fila = fila;
        Nodoi.columna = columna;
        Nodoi.capacidad_campo_media = capacidad_campo_media;
        Nodoi.estaciones = estaciones;
        Nodoi.pendiente_3clases = pendiente_3clases;
        Nodoi.porosidad_media = porosidad_media;
        Nodoi.umbral_humedo = umbral_humedo;
        Nodoi.umbral_intermedio = umbral_intermedio;
        Nodoi.umbral_seco = umbral_seco;
        Nodoi.homog = 1;
        Nodoi.area = 1;
    }
    std::cout << "Se han terminado de leer los datos del fichero." << std::endl;
}

/**
 * @brief Inicializa los niveles restantes de la pirámide, estableciendo relaciones entre nodos y calculando sus atributos.
 * 
 * Esta función inicializa los niveles restantes de la pirámide (niveles superiores) a partir de los nodos de nivel inferior.
 * Comprueba si los nodos de la base son iguales y homogéneos, y en caso afirmativo, establece sus atributos y relaciones.
 * También evalúa si los nodos son parecidos y homogéneos, en cuyo caso aún falta implementar la funcionalidad correspondiente.
 * 
 * Base_NO  Base_NE
 * Base_SO  Base_SE
 */
void Piramide::inicializarNivelesRestantes(){
    // Recorrer todos los niveles restantes
    for (int n = 1; n < num_niv; n++) {
        int tam_fila, tam_columna;
        // Obtener el tamaño del nivel actual
        std::tie(tam_fila, tam_columna) = getTam(n);

        // Recorrer todas las filas y columnas del nivel actual
        for (int i = 0; i < tam_fila; i++) {
            for (int j = 0; j < tam_columna; j++) {
                Nodo& Nodoi = piramide[n][i][j];
                Nodo& Base_NO = piramide[n-1][i*2][j*2];
                Nodo& Base_NE = piramide[n-1][i*2][j*2+1];
                Nodo& Base_SO = piramide[n-1][i*2+1][j*2];
                Nodo& Base_SE = piramide[n-1][i*2+1][j*2+1];
                
                if(nodosSonIguales(Base_NO, Base_NE, Base_SO, Base_SE) && nodosSonHomogeneos(Base_NO, Base_NE, Base_SO, Base_SE)){
                    Nodoi.homog = 1;
                    Nodoi.area = Base_NO.area + Base_NE.area + Base_SO.area + Base_SE.area;
                    Nodoi.capacidad_campo_media = Base_NO.capacidad_campo_media;
                    Nodoi.estaciones = Base_NO.estaciones;
                    Nodoi.pendiente_3clases = Base_NO.pendiente_3clases;
                    Nodoi.porosidad_media = Base_NO.porosidad_media;
                    Nodoi.umbral_humedo = Base_NO.umbral_humedo;
                    Nodoi.umbral_intermedio = Base_NO.umbral_intermedio;
                    Nodoi.umbral_seco = Base_NO.umbral_seco;
                    Base_NO.setPadre(Nodoi);
                    Base_NE.setPadre(Nodoi);
                    Base_SO.setPadre(Nodoi);
                    Base_SE.setPadre(Nodoi);
                }
                /*
                else if (nodosSonParecidos(Base_NO, Base_NE, Base_SO, Base_SE, similitud) && nodosSonHomogeneos(Base_NO, Base_NE, Base_SO, Base_SE)){
                    //Falta por implementar.
                }
                */
                else{
                    Nodoi.homog = 0;
                }
            }
        }
    }
}

/**
 * @brief Elimina nodos no homogéneos de la pirámide y actualiza las relaciones entre nodos y sus padres.
 * 
 * Esta función purga la pirámide eliminando nodos no homogéneos y actualizando las relaciones de los nodos restantes con sus padres.
 * Primero, recorre la pirámide desde el nivel más alto hasta el más bajo y elimina los nodos no homogéneos.
 * Luego, recorre la pirámide de nuevo desde el nivel más alto hasta el más bajo, actualizando las relaciones entre nodos y sus padres.
 * 
 */
void Piramide::purga() {
    // Eliminar nodos no homogéneos
    for (int n = num_niv - 1; n >= 0; n--) {
        int tam_fila, tam_columna;
        std::tie(tam_fila, tam_columna) = getTam(n);

        for (int i = 0; i < tam_fila; i++) {
            for (int j = 0; j < tam_columna; j++) {
                Nodo& Nodoi = piramide[n][i][j];

                // Si el nodo no es homogéneo, eliminarlo
                if (!Nodoi.esHomogenea()) {
                    Nodoi = Nodo();
                }
            }
        }
    }

    // Actualizar relaciones entre nodos y sus padres
    for (int n = num_niv - 1; n >= 0; n--) {
        int tam_fila, tam_columna;
        std::tie(tam_fila, tam_columna) = getTam(n);

        for (int i = 0; i < tam_fila; i++) {
            for (int j = 0; j < tam_columna; j++) {
                Nodo& Nodoi = piramide[n][i][j];

                // Si el nodo tiene área y no es huérfano, actualizar la relación con su padre
                if (Nodoi.area != -1 && !Nodoi.esHuerfano()) {
                    Nodo &padre = Nodoi.getPadre();

                    // Si el padre del nodo es huérfano, eliminar la relación entre el nodo y su padre
                    if (padre.esHuerfano()) {
                        Nodoi.parricida();
                    }
                }
            }
        }
    }
}


void Piramide::enlaza() {    	    
    int nivel, fila, col;
    int tam_niv;
    bool hayCambios= false;
    Nodo nodo_enlazable;
    
    std::cout << "Enlazando nodos......................";
    
    do {
        for (int n = num_niv - 1; n >= 0; n--) {
            int tam_fila, tam_columna;
            std::tie(tam_fila, tam_columna) = getTam(n);
            for (int i = 0; i < tam_fila; i++) {
                for (int j = 0; j < tam_columna; j++) {
                    Nodo& Nodoi = piramide[n][i][j];
                    // es huerfana y homogenea?
                    if ((Nodoi.area != -1)) {
                        if (nodo_enlazable.esEnlazable()) {
                            // enlazarConPrimerCandidato(nodo_enlazable);
                            hayCambios=enlazarConMejorCandidato(nodo_enlazable);
                        } // if es enlazable
                    } // if existe
                } // * for (col = 0
            } // * for (fila=0; fila<tam_niv; fila++)
        } // * for (nivel=tamano-1; nivel>=0; nivel--)
    } while (hayCambios);
    
    // showPiramid("Enlaza");
} // fin enlaza.........................

void Piramide::clasifica() {
        int nivel, fila, col;
        int tam_niv;
        bool esFusionado;
        int area_min_paic;
        int m, n;
        std::cout << "Crear regiones.................................................";
                
        for (int n = num_niv; n >= 0; n--) {
            int tam_fila, tam_columna;
            std::tie(tam_fila, tam_columna) = getTam(n);
            for (int i = 0; i < tam_fila; i++) {
                for (int j = 0; j < tam_columna; j++) {
                    Nodo& Nodoi = piramide[n][j][i];
                    if (Nodoi.area != -1) {
                        if (Nodoi.esHuerfano()){
                        	esFusionado = false;
                            if (Nodoi.esFusionable(area_min_paic)) {                                
                            	//esFusionado=fusionarConPrimerCandidato(nodo);
                            	esFusionado=fusionarConMejorCandidato(Nodoi);
                            }//if es fusionable

                            //No ha llegado a fusionarse. ¿Puede generar clase?
                            if ((!esFusionado) && Nodoi.area != -1) {
                            	//excluirDeClase(nodo);
                                crearClase(Nodoi);

                                /*...........................................
                                printf("No se enlaza porque : \n");
                                if (!Piram[nivel][fila][col].esHomogenea()){
                                printf("\t- No es homogeneo\n");
                                }
                                if (Piram[nivel][fila][col].isObstacle()){
                                printf("\t- Es un obstaculo\n");
                                }
                                if (Piram[nivel][fila][col].area <= area_min_paic){
                                printf("\t- Su area (%d) es menor que el minimo (%d)\n",Piram[nivel][fila][col].area ,area_min_paic);
                                }			  			  		                
                                //...........................................
                                 */
                            } //no es fusionado y no es obstaculo                           
                        } else {
                            // Toma la clase del padre  
                        	//excluirDeClase(nodo);
                            incluirEnClase(Nodoi, Nodoi.getPadre());
                        } //nodo con padre
                    } // nodo existe
                } // for (col=0; col<tam_niv; col++) 
            } // for (fila=0; fila<tam_niv; fila++)
        }        
        std::cout << "Clasificación............." << std::endl;
    } // fin clasifica

std::tuple<int, int, int> Piramide::get_nivel_fila_columna(int id) {
    int nivel = 0;
    int tam_nivel = FILAS * COLUMNAS;
    int tam_acumulado = FILAS * COLUMNAS;
    while (id >= tam_acumulado) {
        std::cout << "id: " << id << std::endl;
        std::cout << "tam_nivel: " << tam_nivel << std::endl;
        std::cout << "num_nivel: " << nivel << std::endl;
        nivel++;
        tam_nivel = tam_nivel / 4;
        tam_acumulado += tam_nivel;
    }
    int tam_fila = FILAS / pow(2, nivel);
    int tam_columna = COLUMNAS / pow(2, nivel);
    int resto = id % tam_nivel;
    int fila = resto / tam_columna;
    int columna = resto % tam_columna;
    return std::make_tuple(nivel, fila, columna);
}

std::tuple<int, int> Piramide::getTam(int nivel) const {
    int tam_fila = num_filas / std::pow(2, nivel);
    int tam_columna = num_columnas / std::pow(2, nivel);
    return std::make_tuple(tam_fila, tam_columna);
}

bool Piramide::nodosSonIguales(Nodo& Base_NO, Nodo& Base_NE, Nodo& Base_SO, Nodo& Base_SE) {
    std::array<double, 4> parametros[7] = {
        {Base_NO.capacidad_campo_media, Base_NE.capacidad_campo_media, Base_SO.capacidad_campo_media, Base_SE.capacidad_campo_media},
        {Base_NO.pendiente_3clases, Base_NE.pendiente_3clases, Base_SO.pendiente_3clases, Base_SE.pendiente_3clases},
        {Base_NO.porosidad_media, Base_NE.porosidad_media, Base_SO.porosidad_media, Base_SE.porosidad_media},
        {Base_NO.punto_marchitez_medio, Base_NE.punto_marchitez_medio, Base_SO.punto_marchitez_medio, Base_SE.punto_marchitez_medio},
        {Base_NO.umbral_humedo, Base_NE.umbral_humedo, Base_SO.umbral_humedo, Base_SE.umbral_humedo},
        {Base_NO.umbral_intermedio, Base_NE.umbral_intermedio, Base_SO.umbral_intermedio, Base_SE.umbral_intermedio},
        {Base_NO.umbral_seco, Base_NE.umbral_seco, Base_SO.umbral_seco, Base_SE.umbral_seco}
    };
    
    for (const auto& parametro : parametros) {
        if (!std::equal(parametro.begin() + 1, parametro.end(), parametro.begin())) {
            return false;
        }
    }
    
    return true;
}

bool Piramide::nodosSonHomogeneos(Nodo& Base_NO, Nodo& Base_NE, Nodo& Base_SO, Nodo& Base_SE) {
    if (Base_NO.homog == 1 && Base_NE.homog == 1 && Base_SO.homog == 1 && Base_SE.homog == 1) {
        return true;
    }
    else {
        return false;
    }
}

bool Piramide::enlazarConMejorCandidato(Nodo& nodo_enlazable){
    //falta por implementar
    return true;
}

bool Piramide::fusionarConMejorCandidato(Nodo& nodo){
    //falta por implementar
    return true;
}

void Piramide::crearClase(Nodo& nodo){
    //falta por implementar
    return;
}

void Piramide::incluirEnClase(Nodo &nodo, Nodo &padre){
    //falta por implementar
    return;
}




