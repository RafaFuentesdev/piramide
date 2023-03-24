#include "piramide.h"

void Piramide::init(){
    std::cout << "\tIncializando datos de la piramide..." << std::endl;
    inicializarPiramide();
    std::cout << "\tLeyendo datos del archivo CSV..." << std::endl;
    leerArchivoCSV();
    std::cout << "\tInicializando niveles restantes..." << std::endl;
    inicializarNivelesRestantes();
    std::cout << "\tBase creada." << std::endl;    
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
    std::cout << "\t\tCalculando numero de niveles de la piramide..." << std::endl;
    num_niv = static_cast<int>(floor(log2(std::max(num_filas, num_columnas))) + 1);

    // Reservar memoria para el número de niveles en la pirámide
    std::cout << "\t\tReservando memoria para la piramide..." << std::endl;
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
    std::cout << "\t\tPiramide inicializada..." << std::endl;
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
    std::cout << "\t\tLeyendo encabezado del archivo..." << std::endl;
    std::getline(file, line);
    std::cout << "\t\tLeyendo cada linea del archivo..." << std::endl;
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
    std::cout << "\t\tArchivo CSV leido y asignado a la base..." << std::endl;
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
    std::cout << "\t\tInicializando el resto de niveles..." << std::endl;
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
                
                //Caso 1: Nodos de la base son iguales y homogéneos.
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
                //Caso 2: Nodos de la base son suficientemente parecidos (umbral de similitud) y homogéneos.
                /*
                else if (nodosSonParecidos(Base_NO, Base_NE, Base_SO, Base_SE, similitud) && nodosSonHomogeneos(Base_NO, Base_NE, Base_SO, Base_SE)){

                }
                */

                //Caso 3: Los nodos de la base son diferentes o no homogéneos.   
                else{
                    Nodoi.homog = 0;
                }
            }
        }
    }
    std::cout << "\t\tTerminado de inicializar los demás niveles..." << std::endl;
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
    std::cout << "\t\tEliminando nodos no homogéneos..." << std::endl;
    for (int n = num_niv - 1; n >= 0; n--) {
        int tam_fila, tam_columna;
        std::tie(tam_fila, tam_columna) = getTam(n);

        for (int i = 0; i < tam_fila; i++) {
            for (int j = 0; j < tam_columna; j++) {
                Nodo& Nodoi = piramide[n][i][j];

                // Si el nodo no es homogéneo, inicializarlo vacío.
                if (!Nodoi.esHomogeneo()) {
                    Nodoi.reset();
                }
            }
        }
    }

    // Actualizar relaciones entre nodos y sus padres
    std::cout << "\t\tActualizando relaciones entre nodos y sus padres..." << std::endl;
    for (int n = num_niv - 1; n >= 0; n--) {
        int tam_fila, tam_columna;
        std::tie(tam_fila, tam_columna) = getTam(n);

        for (int i = 0; i < tam_fila; i++) {
            for (int j = 0; j < tam_columna; j++) {
                Nodo& Nodoi = piramide[n][i][j];

                // Si el nodo es válido y no es huérfano, actualizar la relación con su padre
                if (Nodoi.id != -1 && !Nodoi.esHuerfano()) {
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


/**
 * @brief Enlaza nodos en la pirámide según criterios específicos.
 * 
 * Esta función enlaza nodos en la pirámide siguiendo criterios específicos y de acuerdo con la función enlazarConMejorCandidato.
 * Recorre la pirámide desde el nivel más alto hasta el más bajo en busca de nodos enlazables.
 * Si se encuentra un nodo enlazable, se intenta enlazar con el mejor candidato.
 * Este proceso se repite hasta que no haya cambios.
 * 
 */
void Piramide::enlaza() {
    int nivel, fila, col;
    int tam_niv;
    bool hayCambios = false;
    Nodo nodo_enlazable;

    do {
        hayCambios = false;

        // Recorrer la pirámide desde el nivel más alto hasta el más bajo
        for (int n = num_niv - 1; n >= 0; n--) {
            int tam_fila, tam_columna;
            std::tie(tam_fila, tam_columna) = getTam(n);

            // Recorrer filas y columnas del nivel actual
            for (int i = 0; i < tam_fila; i++) {
                for (int j = 0; j < tam_columna; j++) {

                    Nodo& Nodoi = piramide[n][i][j];
                    // Si el nodo es válido, verificar si es enlazable
                    if (Nodoi.id != -1) {
                        if (nodo_enlazable.esEnlazable()) {
                            // Intentar enlazar con el mejor candidato y actualizar hayCambios
                            hayCambios = enlazarConMejorCandidato(nodo_enlazable);
                        }
                    }
                }
            }
        }
        hayCambios = false;
    } while (hayCambios);
}

/**
 * @brief Clasifica los nodos de la Pirámide para generar regiones.
 */
void Piramide::clasifica() {
    int nivel, fila, col;
    int tam_niv;
    bool esFusionado;
    int area_min_paic;
    int m, n;
            
    // Recorre los niveles de la Pirámide de forma descendente
    for (int n = num_niv; n >= 0; n--) {
        int tam_fila, tam_columna;
        std::tie(tam_fila, tam_columna) = getTam(n);
        
        // Recorre las filas y columnas de cada nivel
        for (int i = 0; i < tam_fila; i++) {
            for (int j = 0; j < tam_columna; j++) {
                Nodo& Nodoi = piramide[n][j][i];
                
                // Si el Nodo es válido
                if (Nodoi.id != -1) {
                    // Si el Nodo es huérfano (no tiene padre)
                    if (Nodoi.esHuerfano()){
                        esFusionado = false;
                        
                        // Verifica si el Nodo es fusionable
                        if (Nodoi.esFusionable(area_min_paic)) {
                            // Intenta fusionar el Nodo con el mejor candidato
                            esFusionado = fusionarConMejorCandidato(Nodoi);
                        }

                        // Si el Nodo no pudo ser fusionado y sigue siendo válido
                        if ((!esFusionado) && Nodoi.id != -1) {
                            // Crea una nueva clase para el Nodo
                            crearClase(Nodoi);
                        }                         
                    } else {  
                        // Si el Nodo no es huérfano, lo incluye en la clase de su Nodo padre
                        incluirEnClase(Nodoi, Nodoi.getPadre());
                    }
                }
            }
        }
    }        
}

/**
 * @brief Obtiene el nivel, fila y columna de un nodo en la pirámide dado su ID.
 * 
 * @param id El ID del nodo.
 * @return Un tuple con el nivel, fila y columna del nodo.
 * 
 * Esta función calcula el nivel, fila y columna de un nodo en la pirámide
 * a partir de su ID. La pirámide se compone de varios niveles, donde cada
 * nivel tiene un número específico de filas y columnas.
 * La función calcula la posición del nodo en la pirámide iterativamente,
 * sumando el tamaño de los niveles hasta que se alcanza el nivel correcto.
 * Luego, calcula las coordenadas de fila y columna del nodo en dicho nivel.
 */
std::tuple<int, int, int> Piramide::get_nivel_fila_columna(int id) {
    int nivel = 0;
    int tam_nivel = FILAS * COLUMNAS;
    int tam_acumulado = FILAS * COLUMNAS;

    // Buscar el nivel correspondiente al ID
    while (id >= tam_acumulado) {
        nivel++;
        tam_nivel = tam_nivel / 4;
        tam_acumulado += tam_nivel;
    }

    // Calcular el tamaño de fila y columna en el nivel encontrado
    int tam_fila, tam_columna;
    std::tie(tam_fila, tam_columna) = getTam(nivel);

    // Calcular las coordenadas de fila y columna dentro del nivel
    int resto = id % tam_nivel;
    int fila = resto / tam_columna;
    int columna = resto % tam_columna;

    return std::make_tuple(nivel, fila, columna);
}


/**
 * @brief Obtiene el tamaño de un nivel específico de la pirámide en términos de filas y columnas.
 * 
 * @param nivel El nivel de la pirámide.
 * @return Un tuple con el tamaño de filas y columnas del nivel.
 * 
 * Esta función calcula el tamaño de un nivel específico de la pirámide en términos de filas y columnas.
 * El tamaño se reduce a la mitad en cada nivel sucesivo de la pirámide.
 */
std::tuple<int, int> Piramide::getTam(int nivel) const {
    int tam_fila = num_filas / std::pow(2, nivel);
    int tam_columna = num_columnas / std::pow(2, nivel);
    return std::make_tuple(tam_fila, tam_columna);
}

/**
 * @brief Verifica si los cuatro nodos base son iguales en base a sus atributos.
 * 
 * @param Base_NO Nodo base noroeste.
 * @param Base_NE Nodo base noreste.
 * @param Base_SO Nodo base suroeste.
 * @param Base_SE Nodo base sureste.
 * @return Verdadero si los nodos base son iguales, falso en caso contrario.
 * 
 * Esta función compara los atributos de los cuatro nodos base para determinar si son iguales.
 * Los nodos se consideran iguales si todos sus atributos correspondientes son iguales.
 */
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
    
    // Verificar si todos los atributos correspondientes son iguales entre los nodos
    for (const auto& parametro : parametros) {
        if (!std::equal(parametro.begin() + 1, parametro.end(), parametro.begin())) {
            return false;
        }
    }
    
    return true;
}

/**
 * @brief Verifica si los cuatro nodos base son homogéneos.
 * 
 * @param Base_NO Nodo base noroeste.
 * @param Base_NE Nodo base noreste.
 * @param Base_SO Nodo base suroeste.
 * @param Base_SE Nodo base sureste.
 * @return Verdadero si los nodos base son homogéneos, falso en caso contrario.
 * 
 * Esta función verifica si los cuatro nodos base son homogéneos, es decir, si todos tienen
 * un atributo 'homog' igual a 1. Si todos los nodos tienen un atributo 'homog' igual a 1,
 * la función devuelve verdadero. En caso contrario, devuelve falso.
 */
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
    return false;
}

bool Piramide::fusionarConMejorCandidato(Nodo& nodo){
    //falta por implementar
    return false;
}

void Piramide::crearClase(Nodo& nodo){
    //falta por implementar
    return;
}

void Piramide::incluirEnClase(Nodo &nodo, Nodo &padre){
    //falta por implementar
    return;
}




