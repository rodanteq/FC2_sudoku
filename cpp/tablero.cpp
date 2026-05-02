#include "../h/tablero.h"


tTablero::tTablero() : dimension(DIM_TABLERO) {};

int tTablero::get_dimension() const {

	return dimension;
}
tCelda tTablero::get_value(int f, int c) const {

	return dat[f][c];
}

void tTablero::set_up(int v) {

	dimension = v;
}
void tTablero::set_value(int f, int c, tCelda celda) {

	dat[f][c] = celda;
}
