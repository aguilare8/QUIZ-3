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