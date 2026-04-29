#pragma once
#include "celda.h"

const int DIM_TABLERO = 9; // el tablero es siempre de 9x9, aunque se podrían hacer tableros de otras dimensiones, pero no es el caso
							// suponemos que la dimension maxima que nos puede entrar es 16x16
							// nueva nota, reducimos a 9x9 para reducir el uso de memoria

class tTablero {

private:
	int dimension; 
	tCelda dat[DIM_TABLERO][DIM_TABLERO];

public:
	tTablero();
	void set_up(int v);
	int get_dimension() const;
	tCelda get_value(int f, int c) const;
	void set_value(int f, int c, tCelda celda);
};