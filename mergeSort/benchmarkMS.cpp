#include <iostream>
#include <cstdlib> Para rand y srand
#include <ctime> //Para clock y time
#include <chrono> //Se utilizo clock pero daba resultados muy pequenos en seg
#include <cmath> //Para usar log
#include <fstream> // Read and write files
using namespace std;


// Esta funcion combina dos partes del arreglo que ya estan ordenadas
void merge(int arreglo[], int izq, int medio, int der) {

    int tamIzquierda = medio - izq + 1;
    int tamDerecha = der - medio;

    // Crear arreglos temporales
    int* arregloIzquierda = new int[tamIzquierda];
    int* arregloDerecha = new int[tamDerecha];

    // Copiar los datos al arreglo temporal izquierdo
    for (int i = 0; i < tamIzquierda; i++) {
        arregloIzquierda[i] = arreglo[izq + i];
    }

    // Copiar los datos al arreglo temporal derecho
    for (int j = 0; j < tamDerecha; j++) {
        arregloDerecha[j] = arreglo[medio + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = izq;


    // Comparar los elementos de ambos arreglos
    // y colocar el menor en el arreglo original
    while (i < tamIzquierda && j < tamDerecha) {

        if (arregloIzquierda[i] <= arregloDerecha[j]) {

            arreglo[k] = arregloIzquierda[i];
            i++;

        } else {

            arreglo[k] = arregloDerecha[j];
            j++;
        }

        k++;
    }


    // Si quedan elementos en el arreglo izquierdo, se copian
    while (i < tamIzquierda) {

        arreglo[k] = arregloIzquierda[i];
        i++;
        k++;
    }


    // Si quedan elementos en el arreglo derecho, se copian
    while (j < tamDerecha) {

        arreglo[k] = arregloDerecha[j];
        j++;
        k++;
    }


    // Liberar la memoria de los arreglos temporales
    delete[] arregloIzquierda;
    delete[] arregloDerecha;
}


// Esta funcion divide el arreglo en partes mas pequenas
void mergeSort(int arreglo[], int izq, int der) {

    // Mientras haya mas de un elemento
    if (izq < der) {

        // Buscar el punto medio
        int medio = izq + (der - izq) / 2;

        // Ordenar la mitad izquierda
        mergeSort(arreglo, izq, medio);

        // Ordenar la mitad derecha
        mergeSort(arreglo, medio + 1, der);

        // Combinar ambas mitades ya ordenadas
        merge(arreglo, izq, medio, der);
    }
}

// Esta funcion llena un arreglo con numeros aleatorios.
void llenarArreglo(int arreglo[], int tamano) {

    for (int i=0; i<tamano; i++) {

        // rand() genera un numero entero aletorio
        // se usa %100000 oara limitar valores entre 0 y 99999
        arreglo[i] = rand() % 100000;
    }
}


int main() {

    //srand() cambia la semilla utilizada por rand()
    //Al usar time(NULL), los numeros generados cmabian cada que se ejecuta el programa
    srand(time(NULL));

    //Tamanos de arreglo que se utilizan para probar
    int tamanos[]={
        100, 500, 1000, 5000, 10000, 50000
    };

    //Calcular automat. cautnos tamanos existen en el arreglo anterior
    int cantidadTamanos= sizeof(tamanos)/sizeof(tamanos[0]);

    //Cada prueba se repite varias veces, tomando en cuenta el cold start
    int reps= 10;

    cout << "Benchmark MergeSort" << endl;
    cout << "-------------------" << endl;

    // Crear archivo donde se guardaran los resultados del benchmark
    // seguir la ruta \cmake-build-debug\resultadosMergeSort
    ofstream archivo("resultadosMergeSort.csv");

    // Encabezados de las columnas
    // se separa con ; para que el excel se vea mejor
    archivo << "Tamano;Tiempo promedio;n log n;Teorico escalado\n";

    //Este ciclo prueba MergeSort con cada tamano definido anteriormente
    for (int t=0; t<cantidadTamanos; t++) {
        int tamano= tamanos[t];

        //Aqui se acumula el tiempo de todas las reps
        double tiempoTotal= 0;

        //Repetiur la prueba varias veces
        for (int r=0; r<reps; r++) {
            //Arreglo dinamico debido al cambio de tamano
            int* arreglo = new int[tamano];

            //Llenar el arreglo
            llenarArreglo(arreglo, tamano);

            /**
            //Guardar el momento en el que empieza el algoritmo
            clock_t inicio= clock();

            //Guardar el instante en que termina
            clock_t fin= clock();

            // Como clock trabaja con otro formato de medicion de tiempo, hay que convertirlo
            double tiempo= (double)(fin-inicio)/CLOCKS_PER_SEC;
            */

            // Guardar el momento exacto antes de ejecutar MergeSort
            auto inicio = chrono::high_resolution_clock::now();

            // Ejecutar el algoritmo que se quiere medir
            mergeSort(arreglo, 0, tamano - 1);

            // Guardar el momento exacto despues de ejecutar MergeSort
            auto fin = chrono::high_resolution_clock::now();

            // Calcular cuanto tiempo paso entre inicio y fin.
            // Se mide en microsegundos
            double tiempo = chrono::duration<double, micro>(fin - inicio).count();

            //Sumar el tiempo de rep
            tiempoTotal+= tiempo;

            // Liberar el arreglo
            delete[] arreglo;
        }

        //Calc prom de reps
        double promedio= tiempoTotal/reps;

        // Calcular el crecimiento teorico de MergeSort: n log n
        double teorico = tamano * log2(tamano);

        // Constante usada para llevar n log n a una escala
        // similar a los tiempos medidos experimentalmente
        double teoricoEscalado = 0.0143 * teorico;

        //Mostrar el tamano probado y el tiempo promedio
        cout << "Tamano: " << tamano
             << " | Tiempo promedio: "
             << promedio
             << " microsegundos"
             << " | n log n: " << teorico
             << " | Teorico escalado: " << teoricoEscalado
             << endl;

        // Guardar los resultados de esta prueba en el archivo CSV
        // se separa con ; para que el excel se vea mejor
        archivo << tamano << ";"
                << promedio << ";"
                << teorico << ";"
                << teoricoEscalado << "\n";
    }

    // Cerrar al archivo cuando no se necesite
    archivo.close();
    return 0;
}