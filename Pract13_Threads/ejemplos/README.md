En este folder puse los archivos de cabecera que use para las pruebas y dos cpp con ejemplos.

### archivos:
- fifo_lock.h: contiene una implementacion de FIFO usando un mutex para proteger las secciones criticas
- fifo_lockless.h: contiene una implementacion lockless thel fifo usando CAS
- fifolifo.h: contiene una copia de ../fifo.h
- mpmc_fifo.h: contiene un fifo de alto desempe;o robado de internet
- pool_compara.cpp: este archivo ejecuta pruebas con los fifos y obtiene datos estadisticos de la ejecucion. la seleccion se hace por medio de una macro
- pool_lock.cpp: este arcihvo muestra una solucion contenida en si misma donde los locks de la cola son parte integra de los threads.
