// Benchmark empírico de búsqueda binaria (O(log n))
// Compilar: g++ -O2 -std=c++17 benchmark.cpp -o benchmark
// Ejecutar: ./benchmark   (genera resultados.csv)

#include <algorithm>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

using namespace std;
using Clock = chrono::steady_clock;

// Devuelve el índice (o -1) y cuenta las comparaciones realizadas
int busquedaBinaria(const vector<int>& arr, int objetivo, long long& comparaciones) {
    int izq = 0, der = (int)arr.size() - 1;
    while (izq <= der) {
        int medio = izq + (der - izq) / 2;
        comparaciones++;
        if (arr[medio] == objetivo) return medio;
        if (arr[medio] < objetivo) izq = medio + 1;
        else der = medio - 1;
    }
    return -1;
}

int main() {
    // Tamaños de n: crecen mucho para que se note la curva logarítmica
    vector<int> tamanos = {1000, 5000, 10000, 50000, 100000, 500000,
                           1000000, 5000000, 10000000, 50000000};
    const int BUSQUEDAS = 200000;  // búsquedas por tamaño (para promediar el ruido)
    const int REPETICIONES = 5;    // veces que se repite cada medición

    mt19937 rng(42);  // semilla fija -> resultados reproducibles
    ofstream csv("resultados.csv");
    csv << "n,tiempo_promedio_ns,comparaciones_promedio,log2_n\n";

    volatile long long sumidero = 0;  // evita que el compilador elimine las búsquedas

    for (int n : tamanos) {
        // 1. Arreglo con valores random y ORDENADO (el sort NO se mide)
        uniform_int_distribution<int> distArr(0, 2 * n);
        vector<int> arr(n);
        for (int& x : arr) x = distArr(rng);
        sort(arr.begin(), arr.end());

        // 2. Objetivos random (algunos existen, otros no)
        uniform_int_distribution<int> distObj(0, 2 * n);
        vector<int> objetivos(BUSQUEDAS);
        for (int& x : objetivos) x = distObj(rng);

        // 3. Calentamiento
        long long tmp = 0;
        for (int i = 0; i < 1000; i++) sumidero += busquedaBinaria(arr, objetivos[i], tmp);

        // 4. Mediciones: nos quedamos con el promedio de varias repeticiones
        double sumaTiempo = 0;
        double sumaComp = 0;
        for (int r = 0; r < REPETICIONES; r++) {
            long long comparaciones = 0;
            auto inicio = Clock::now();
            for (int i = 0; i < BUSQUEDAS; i++)
                sumidero += busquedaBinaria(arr, objetivos[i], comparaciones);
            auto fin = Clock::now();

            double ns = chrono::duration<double, nano>(fin - inicio).count();
            sumaTiempo += ns / BUSQUEDAS;
            sumaComp += (double)comparaciones / BUSQUEDAS;
        }

        double tiempoProm = sumaTiempo / REPETICIONES;
        double compProm = sumaComp / REPETICIONES;

        csv << n << "," << tiempoProm << "," << compProm << "," << log2((double)n) << "\n";
        cout << "n=" << n << "  t=" << tiempoProm << " ns  comparaciones="
             << compProm << "  log2(n)=" << log2((double)n) << endl;
    }

    csv.close();
    cout << "Listo: resultados.csv generado." << endl;
    return 0;
}