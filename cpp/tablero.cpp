#include "../h/tablero.h"


tTablero::tTablero() : dimension(DIM_TABLERO) {};

void tTablero::set_up(int v) {
	dimension = v;
}

int tTablero::get_dimension() const {
	return dimension;
}
tCelda tTablero::get_value(int f, int c) const {
	return dat[f][c];
}

void tTablero::set_value(int f, int c, int v, int estado) {
	dat[f][c].set_value(v);
	switch (estado) {
	case 0:
		dat[f][c].set_original();
		break;
	case 1:
		dat[f][c].set_taken();
		break;
	case 2:
		dat[f][c].set_empty();
		break;
	}

}
