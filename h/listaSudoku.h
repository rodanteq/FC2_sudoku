#pragma once
#include "reglasSudoku.h"

class tListaSudoku {
private:
	int num_elems;
	int dim; // iniciamos a un valor bajo para luego redimensionar
	tReglasSudoku **lista;
public:
	// constructora, destructora
	tListaSudoku();
	~tListaSudoku();

	// consultoras
	int dame_num_elems()const;
	const tReglasSudoku& dame_sudoku(int i) const;
	void mostrar_lista() const;

	// modificadoras
	void insertar(const tReglasSudoku& sudoku);
	void eliminar(int pos); // elimina el elemento de la posición pos (desde 0)

	// redimensionar
	void resize(tListaSudoku& ls, bool type);
};