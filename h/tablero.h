#pragma once
#include "celda.h"

const int DIM_TABLERO = 9;

class tTablero {

private:
	int dimension; // numero del 1 al 9 para ser más intuitivo
	tCelda dat[DIM_TABLERO][DIM_TABLERO];

public:
	tTablero();
	void set_up(int v);
	int get_dimension() const;
	tCelda get_value(int f, int c) const;
	void set_value(int f, int c, int v);
};