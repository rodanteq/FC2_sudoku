#pragma once
#include "celda.h"

const int DIM_TABLERO = 9; // el tablero es siempre de 9x9, aunque se podrían hacer tableros de otras dimensiones, pero no es el caso

class tTablero {

private:
	int dimension; 
	// minimo 1, máximo 9 (aunque se podrían hacer tableros de dimensión n^2)
	tCelda dat[DIM_TABLERO][DIM_TABLERO];

public:
	tTablero();
	void set_up(int v);
	int get_dimension() const;
	tCelda get_value(int f, int c) const;
	void set_value(int f, int c, tCelda celda);
};