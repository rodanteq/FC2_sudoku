#pragma once
#include <fstream>
#include "tablero.h"

const int MAX_BLOCKED = 10 ;

using namespace std;

struct lPositionBlocked {
	int dat[MAX_BLOCKED][2];
	int n=0;                                     //Revisar!! (valor MAX_BLOCKED??)
};

class tReglasSudoku {

private:
	tTablero tablero;
	int cont;
	lPositionBlocked blockedPosition;

	/* metodos privados */
	void set_celdas_blocked(int p, int f, int c);
	bool previously_blocked(int f, int c) const;
	void search_new_blocked(int f, int c);
	void search_not_blocked(int f, int c);
	int get_posible_value(int f, int c) const;

public:
	/* constructora */
	tReglasSudoku();

	/* consultoras */
	int get_dimension() const; // devuelve la dimensión del tablero
	tCelda get_celda(int f, int c) const; // devuelve la celda en la posición (f,c)
	bool finish() const ; // true si y sólo si el Sudoku está resuelto
	bool blocked() const ; // true si el Sudoku tiene celdas bloqueadas
	int get_num_celdas_blocked() const ; // devuelve el número de celdas bloqueadas
	int get_num_celdas_empty() const ; // devuelve el número de celdas vacías
	void get_celdas_blocked(int p, int& f, int& c) const; // devuelve en (f,c) la celda bloqueada en la posición p - creamos un metodo privado set_celdas_blocked
	bool is_posible_value(int f, int c, int v) const; // true si y sólo si v se puede colocar en (f,c)
	int posible_values(int f, int c) const; // devuelve el número de posibles valores para (f,c)
	
	/* modificadoras */
	bool set_value(int f, int c, tCelda celda); // pone v en (f,c)
	bool clear_value(int f, int c); // pone la celda (f,c) a VACIA
	void reset(); // recupera el Sudoku original
	void autofill(); // rellena todas las celdas con un único valor posible

	/* inicializadora */
	void load_sudoku(ifstream & file); // carga un Sudoku original de un archivo
};
