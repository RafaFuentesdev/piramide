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

void Piramide::inicializarNivelesRestantes(){
    int nodos_homogeneos = 0, nodos_no_homogeneos = 0;
    // Inicialización del resto de niveles
    // para los atributos de probabilidad de ocupacion, 
    // homogeneidad ... usamos los cuatro nodos de debajo
    for (int n = 1; n < num_niv; n++) {
        int tam_fila, tam_columna;
        std::tie(tam_fila, tam_columna) = getTam(n);
        for (int i = 0; i < tam_fila; i++) {
            for (int j = 0; j < tam_columna; j++) {
                Nodo& Nodoi = piramide[n][i][j];
                Nodo& Nodo_NO = piramide[n-1][i*2][j*2];
                Nodo& Nodo_NE = piramide[n-1][i*2][j*2+1];
                Nodo& Nodo_SO = piramide[n-1][i*2+1][j*2];
                Nodo& Nodo_SE = piramide[n-1][i*2+1][j*2+1];
                if(nodosSonIguales(Nodo_NO, Nodo_NE, Nodo_SO, Nodo_SE) && nodosSonHomogeneos(Nodo_NO, Nodo_NE, Nodo_SO, Nodo_SE)){
                    Nodoi.homog = 1;
                }
                else{
                    Nodoi.homog = 0;
                }
                
                Nodo_NO.setPadre(Nodoi);
                Nodo_NE.setPadre(Nodoi);
                Nodo_SO.setPadre(Nodoi);
                Nodo_SE.setPadre(Nodoi);
                /*
                if(nodosSonIguales(Nodo_NO, Nodo_NE, Nodo_SO, Nodo_SE) && nodosSonHomogeneos(Nodo_NO, Nodo_NE, Nodo_SO, Nodo_SE)){
                    Nodoi.homog = 1;
                    Nodoi.area = Nodo_NO.area + Nodo_NE.area + Nodo_SO.area + Nodo_SE.area;
                    Nodoi.capacidad_campo_media = Nodo_NO.capacidad_campo_media;
                    Nodoi.estaciones = Nodo_NO.estaciones;
                    Nodoi.pendiente_3clases = Nodo_NO.pendiente_3clases;
                    Nodoi.porosidad_media = Nodo_NO.porosidad_media;
                    Nodoi.umbral_humedo = Nodo_NO.umbral_humedo;
                    Nodoi.umbral_intermedio = Nodo_NO.umbral_intermedio;
                    Nodoi.umbral_seco = Nodo_NO.umbral_seco;
                    Nodo_NO.setPadre(n, i, j);
                    Nodo_NE.setPadre(n, i, j);
                    Nodo_SO.setPadre(n, i, j);
                    Nodo_SE.setPadre(n, i, j);
                }
                */
            }
        }
    }
    std::cout << "Nodos homogeneos: " << nodos_homogeneos << " Nodos no homogeneos: " << nodos_no_homogeneos << std::endl;
}

void Piramide::purga(){

    std::cout << "Purgar nodos no homogeneos..............." << std::endl;

    for (int n = num_niv - 1; n >= 0; n--) {
        int tam_fila, tam_columna;
        std::tie(tam_fila, tam_columna) = getTam(n);
        for (int i = 0; i < tam_fila; i++) {
            for (int j = 0; j < tam_columna; j++) {
                Nodo& Nodoi = piramide[n][i][j];
                if(!Nodoi.esHomogenea()){
                    Nodoi = Nodo();
                }
            }
        }
        std::cout << n << std::endl;
    }
    
    for (int n = num_niv - 1; n >= 0; n--) {
        int tam_fila, tam_columna;
        std::tie(tam_fila, tam_columna) = getTam(n);
        for (int i = 0; i < tam_fila; i++) {
            for (int j = 0; j < tam_columna; j++) {
                Nodo& Nodoi = piramide[n][i][j];
                if (Nodoi.area != -1 && Nodoi.padre != nullptr) {
                    Nodo* padre = piramide[n][i][j].padre;
                    if (padre->padre == nullptr) {
                        Nodoi.parricida();
                    }
                }
            }
        }
        std::cout << n << std::endl;
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

bool Piramide::nodosSonIguales(Nodo& Nodo_NO, Nodo& Nodo_NE, Nodo& Nodo_SO, Nodo& Nodo_SE) {
    std::array<double, 4> parametros[7] = {
        {Nodo_NO.capacidad_campo_media, Nodo_NE.capacidad_campo_media, Nodo_SO.capacidad_campo_media, Nodo_SE.capacidad_campo_media},
        {Nodo_NO.pendiente_3clases, Nodo_NE.pendiente_3clases, Nodo_SO.pendiente_3clases, Nodo_SE.pendiente_3clases},
        {Nodo_NO.porosidad_media, Nodo_NE.porosidad_media, Nodo_SO.porosidad_media, Nodo_SE.porosidad_media},
        {Nodo_NO.punto_marchitez_medio, Nodo_NE.punto_marchitez_medio, Nodo_SO.punto_marchitez_medio, Nodo_SE.punto_marchitez_medio},
        {Nodo_NO.umbral_humedo, Nodo_NE.umbral_humedo, Nodo_SO.umbral_humedo, Nodo_SE.umbral_humedo},
        {Nodo_NO.umbral_intermedio, Nodo_NE.umbral_intermedio, Nodo_SO.umbral_intermedio, Nodo_SE.umbral_intermedio},
        {Nodo_NO.umbral_seco, Nodo_NE.umbral_seco, Nodo_SO.umbral_seco, Nodo_SE.umbral_seco}
    };
    
    for (const auto& parametro : parametros) {
        if (!std::equal(parametro.begin() + 1, parametro.end(), parametro.begin())) {
            return false;
        }
    }
    
    return true;
}

bool Piramide::nodosSonHomogeneos(Nodo& Nodo_NO, Nodo& Nodo_NE, Nodo& Nodo_SO, Nodo& Nodo_SE) {
    if (Nodo_NO.homog == 1 && Nodo_NE.homog == 1 && Nodo_SO.homog == 1 && Nodo_SE.homog == 1) {
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




