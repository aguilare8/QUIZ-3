# 1. Benchmark de Búsqueda Binaria

## Objetivo

El objetivo de esta parte del proyecto es comprobar de forma empírica que el algoritmo de Binary Search presenta una complejidad de tiempo de O(log n), para esto se realizaron múltiples ejecuciones del algoritmo utilizando arreglos de diferentes tamaños y valores aleatorios, midiendo el tiempo de ejecución y comparándolo con el crecimiento teórico log n.

## Metodología

Se generaron arreglos de enteros random y se ordenaron antes de medir (el ordenamiento no entra en el tiempo).

Tamaños de n: 1.000 hasta 50.000.000.

Para cada n se hicieron 200.000 búsquedas con objetivos random (existentes y no existentes) y se repitió la medición 5 veces; se reporta el promedio.

Se midió el tiempo promedio por búsqueda (ns) y el número promedio de comparaciones.

La curva teórica se escaló con una constante c: teórico(n) = c · log₂(n).

## Cómo ejecutar (Visual Studio Code)

Primero, se abre una terminal integrada en la carpeta binarySearch.

Luego, para compilar escriba en la terminal: g++ -O2 -std=c++17 benchmarkBS.cpp -o benchmarkBS

Por último, para ejecutar escriba: ./benchmarkBS (esto va a generar resultadosBS.csv)

## Resultados

A continuación, se adjuntan los gráficos con las comparaciones y resultados del benchmark.

### Gráfico 1: Tiempo real vs teórico

![Tiempo real vs teorico](/binarySearch/graficosBS/Grafica%201.jpg)

### Gráfico 2: comparaciones vs. log₂(n)

![comparaciones vs. log₂(n)](/binarySearch/graficosBS/Grafica%202.jpg)

### Gráfico 3: tiempo vs. log₂(n)

![tiempo vs. log₂(n)](/binarySearch/graficosBS/Grafica%203.jpg)

## Análisis de resultados y conclusiones

El análisis del número de comparaciones confirma que la búsqueda binaria es O(log n). Entre n = 1.000 y n = 50.000.000 (un factor de 50.000 en el tamaño del arreglo) las comparaciones promedio pasaron de 9,5 a 25,2, es decir, apenas unas 16 comparaciones más. Los datos siguen casi exactamente a log₂(n): la diferencia con log₂(n) es de aproximadamente 0,4 comparaciones en todos los tamaños. Cada vez que n se multiplica por 10, el algoritmo hace en promedio unas 3,3 comparaciones adicionales, que es lo que predice la teoría (log₂(10) ≈ 3,32).

El tiempo de ejecución también crece de forma muy lenta en relación con n: aunque el arreglo es 50.000 veces más grande, el tiempo por búsqueda aumentó cerca de 10 veces (de 77 ns a 766 ns), mientras que un algoritmo lineal habría crecido 50.000 veces. Para tamaños de hasta 1.000.000 el tiempo se ajusta bien a una recta contra log₂(n), consistente con O(log n).

Sin embargo, para los arreglos más grandes (n ≥ 5.000.000) el tiempo real se separa de la curva teórica y crece más rápido de lo que predice c·log₂(n). Esta desviación no se debe a que el algoritmo haga más pasos, ya que las comparaciones siguen exactamente la curva logarítmica, sino al hardware. Un arreglo de decenas de millones de enteros ocupa cientos de MB y deja de caber en la memoria caché del procesador, por lo que cada acceso a memoria se vuelve más lento (más fallos de caché). Esta es la explicación más probable, aunque no la verificamos con un perfilador. En resumen, la complejidad algorítmica de la búsqueda binaria es O(log n), como lo demuestra el conteo de comparaciones, mientras que el tiempo medido refleja además el costo de acceso a memoria de la máquina donde se ejecutó.

# 2. Benchmark de MergeSort

## Objetivo

El objetivo de esta parte del proyecto es comprobar de forma empírica que el algoritmo MergeSort presenta una complejidad de tiempo de O(n log n), para esto se realizaron múltiples ejecuciones del algoritmo utilizando arreglos de diferentes tamaños y valores aleatorios, midiendo el tiempo de ejecución y comparándolo con el crecimiento teórico n log n.

## Metodología

Se utilizaron arreglos con los siguientes tamaños:

- 100 , 500 , 1000 , 5000 , 10000 , 50000

Cada arreglo fue llenado con valores aleatorios entre 0 y 99999, para cada tamaño se realizaron 10 ejecuciones de MergeSort y se calculó el tiempo promedio.

El tiempo se midió en microsegundos utilizando `chrono::high_resolution_clock`.

La generación de números aleatorios se realizó antes de iniciar la medición, de manera que únicamente se midiera el tiempo correspondiente al algoritmo MergeSort.

## Resultados experimentales

Los siguientes resultados corresponden al tiempo promedio obtenido para cada tamaño de arreglo probado:

![Resultados experimentales de MergeSort](mergeSort/graphics/resultados.png)

Los resultados obtenidos muestran que el tiempo de ejecución aumenta conforme aumenta el tamaño del arreglo.

![Benchmark experimental de MergeSort](mergeSort/graphics/grafica-experimental.png)

## Análisis teórico

La complejidad teórica de MergeSort es O(n log n), esto se debe a que el algoritmo divide repetidamente el arreglo en dos mitades.

La siguiente gráfica muestra el crecimiento teórico de n log n para los mismos tamaños utilizados en el benchmark.

![Análisis teórico de MergeSort](mergeSort/graphics/grafica-teorica.png)

## Comparación experimental vs. teórica

Para comparar visualmente los tiempos experimentales con el crecimiento teórico, se escaló la función n log n mediante una constante.

Este escalamiento no cambia la forma de crecimiento de n log n, sino que permite representar ambas curvas en una escala similar.

![Comparación experimental vs. teórica](mergeSort/graphics/grafica-comparativa.png)

Al comparar ambas curvas se observa que presentan una tendencia de crecimiento similar, a medida que aumenta el tamaño del arreglo, el tiempo experimental aumenta de una forma consistente con el comportamiento esperado de n log n.

Por lo tanto, los resultados obtenidos respaldan empíricamente que MergeSort presenta una complejidad de tiempo O(n log n).