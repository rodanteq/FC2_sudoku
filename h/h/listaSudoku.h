#pragma once
#include "reglasSudoku.h"
#include "mostrar.h"


class tListaSudoku {
private:
	int num_elems; // número de elementos en la lista (sudokus guardados)
	int dim; // iniciamos a un valor bajo para luego redimensionar
	tReglasSudoku **lista; // puntero a un array dinámico de punteros a tReglasSudoku
public:
	// constructora, destructora
	tListaSudoku();
	~tListaSudoku();

	// consultoras
	int dame_num_elems()const; // devuelve el número de elementos en la lista
	const tReglasSudoku& dame_sudoku(int i)const; // devuelve el sudoku en la posición i (desde 0) - se devuelve por referencia para evitar copias innecesarias
	void mostrar_lista()const; // muestra por pantalla la lista de sudokus guardados

	// modificadoras
	void insertar(const tReglasSudoku& sudoku); // inserta el sudoku al final de la lista, redimensionando si es necesario
	void eliminar(int pos); // elimina el elemento de la posición pos (desde 0)

	// redimensionar
	void resize(tListaSudoku& ls, bool type); // redimensiona

	// auxiliares
	int busquedaBinaria(const tReglasSudoku& sudoku)const; // busqueda binaria
	void mostrar_sudoku(int index) const; // muestra por pantalla el sudoku en la posición index
};