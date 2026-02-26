#pragma once
#include "celda.h"

const int DIM_TABLERO = 9;

class Tablero {
private:
	int dimension;
	Celda dat[DIM_TABLERO][DIM_TABLERO];

public:
	Tablero();
	void set_up(int v);
	int get_dimension() const;
	Celda get_value(int f, int c) const;
	void set_value(int f, int c, int v);
};