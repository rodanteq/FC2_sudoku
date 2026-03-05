#pragma once
#include <iostream>
#include <iomanip>
#include "tablero.h"
#include "colors.h"

const short int BARRA_HORIZONTAL = 196,
CRUZ = 197,
BARRA_VERTICAL = 179,
SEPARADOR_IZQUIERDA = 179,
ANCHO_CELDA = 3,
MITAD_ANCHO = ANCHO_CELDA / 2, 
BLANCO = 250;


void mostrarTablero(tTablero& const tab);
