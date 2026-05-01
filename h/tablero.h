#pragma once
#include "celda.h"

const int DIM_TABLERO = 9;	// el tablero es siempre de 9x9, aunque se podrían hacer tableros de otras dimensiones, pero no es el caso
							// nueva nota, reducimos (de 16x16) a 9x9  para reducir el uso de memoria

class tTablero {

private:
	int dimension; // dimension del tablero
	tCelda dat[DIM_TABLERO][DIM_TABLERO]; // array bidimensional de celdas

public:
	/* constructora */
	tTablero();
	/* métodos de consulta */
	int get_dimension() const; // devuelve la dimensión del tablero
	tCelda get_value(int f, int c) const; // devuelve la celda en la posición (f,c)
	/* métodos modificadores */
	void set_up(int v); // pone el valor v como dimension
	void set_value(int f, int c, tCelda celda); // pone el valor de la celda en la posición (f,c) a celda
};