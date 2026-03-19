#pragma once
#include <iostream>
#include <iomanip>
#include "reglasSudoku.h"
#include "colors.h"

const short int BARRA_HORIZONTAL = 196,
CRUZ = 197,
BARRA_VERTICAL = 179,
SEPARADOR_IZQUIERDA = 179,
BLANCO = 250;


void showTablero(tReglasSudoku& const tab);
void showMenu();
void table(tReglasSudoku& const tab);
void showBlocked(tReglasSudoku& const regTab);
void setConsts(tReglasSudoku& const regTab);