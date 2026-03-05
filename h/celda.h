#pragma once
#include <iostream> // así ya lo tenemos

class tCelda {

private:
	enum tEstado { ORIGINAL, TAKEN, EMPTY };
	int value;
	tEstado status;
public:
	tCelda();
	/* métodos de consulta */
	bool is_empty()const; // devuelve true si y sólo si la celda es VACIA
	bool is_original()const; // devuelve true si y sólo si la celda es ORIGINAL
	bool is_taken()const; // devuelve true si y sólo si la celda es OCUPADA
	int get_value()const; // devuelve el valor de la celda
	/* métodos modificadores*/
	void set_value(int a); // pone el valor v en la celda
	void set_taken(); // pone el estado de la celda a OCUPADA
	void set_original(); // pone el estado de la celda a ORIGINAL
	void set_empty(); // pone el estado de la celda a VACIA
};
