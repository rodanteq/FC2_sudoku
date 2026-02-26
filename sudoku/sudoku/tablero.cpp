#include "tablero.h"


Tablero::Tablero() : dimension(DIM_TABLERO) {};

void Tablero::set_up(int v) {
	dimension = v;
}

int Tablero::get_dimension() const {
	return dimension;
}
Celda Tablero::get_value(int f, int c) const {
	return dat[f][c];
}

void Tablero::set_value(int f, int c, int v) {
	dat[f][c].set_value(v);
}
