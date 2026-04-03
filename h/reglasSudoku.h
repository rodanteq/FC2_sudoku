#pragma once
#include <fstream>
#include "tablero.h"

const int MAX_BLOCKED = 10;	// Ponemos un maximo de celdas bloqueadas de 10 
const int MAX_VALORES = 16; // Suponemos que la matriz maxima de entrada es 16x16 (16 valores)

using namespace std;

struct lPositionBlocked {
	int dat[MAX_BLOCKED][2];
	int n = 0;
};
struct tValor {
	bool posible = false;
	int celdas_que_afectan = 0;
};
struct tValores {
	tValor valores[DIM_TABLERO][DIM_TABLERO][MAX_VALORES];
};

class tReglasSudoku {


private:
	tTablero tablero;
	int cont;
	lPositionBlocked blockedPosition;
	tValores valores_celda;

	/* metodos privados */
	void set_celdas_blocked(int p, int f, int c);
	bool previously_blocked(int f, int c, int& res) const;
	int get_posible_value(int f, int c) const;
	void set_up_block_values(int dimension);
	void block_values(int f, int c, int v);
	void clear_blocked_values(int f, int c, int v);

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
