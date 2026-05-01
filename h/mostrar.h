#pragma once
#include "reglasSudoku.h"

const short int BARRA_HORIZONTAL = 196,
CRUZ = 197,
BARRA_VERTICAL = 179,
SEPARADOR_IZQUIERDA = 179,
BLANCO = 250;


void showTablero(tReglasSudoku& const tab); // muestra el tablero del sudoku por pantalla
void showMenu(); // muestra el menú de opciones por pantalla
void showBlocked(tReglasSudoku& const regTab); // muestra por pantalla las celdas bloqueadas, indicando su posición y el valor que bloquean