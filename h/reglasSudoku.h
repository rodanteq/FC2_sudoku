#pragma once
#include "tablero.h"


class tReglasSudoku {

private:

	struct tPos { // tipo para almacenar la posición de una celda bloqueada
		int f=0;
		int c=0;
	};
	struct lPositionBlocked { // tipo con una lista dinámica de tPos (dimension y numero de elementos)
		int dim = 1; 
		tPos** p = new tPos * [dim];
		int n = 0; 
	};
	struct tValor { // tipo para almacenar si una celda es bloqueada
		bool posible = false;
		int celdas_que_afectan = 0;
	};
	typedef int arrValores[DIM_TABLERO]; // tipo array

	tTablero tablero; // el tablero del sudoku
	int cont; // número de celdas ocupadas
	lPositionBlocked blockedPosition; // tipo para almacenar las posiciones bloqueadas
	tValor valores_celda[DIM_TABLERO][DIM_TABLERO][DIM_TABLERO]; // matriz tridimensional para controlar los valores bloqueados en cada celda (mejora v1)
	arrValores cuantas_celdas; // array para controlar cuántas celdas pueden tener cada valor (mejora v2)
	string path; // ruta del sudoku original, para poder resetearlo


	/* metodos privados */
	void set_celdas_blocked(int pos, int f, int c); // añade la celda (f,c) a la lista de celdas bloqueadas en la posición pos
	void clear_celdas_blocked(int pos); // elimina la celda bloqueada en la posición pos de la lista de celdas bloqueadas

	void set_up_block_values(int dimension); // inicializa la matriz de valores bloqueados a false y el contador de celdas que afectan a cada valor a 0
	void block_values(int f, int c, int v, bool is_original); // bloquea el valor v en las celdas de la misma fila, columna y bloque que (f,c) y actualiza el contador de celdas que afectan a cada valor
	void clear_blocked_values(int f, int c, int v); // desbloquea el valor v en las celdas de la misma fila, columna y bloque que (f,c) y actualiza el contador de celdas que afectan a cada valor

	int get_posible_value(int f, int c) const; // devuelve el "unico" valor posible en la celda (f,c)
	bool previously_blocked(int f, int c, int& res) const; // true si la celda (f,c) estaba previamente bloqueada
	
public:

	/* constructora */
	tReglasSudoku();
	tReglasSudoku(const tReglasSudoku& sudoku); // por copia

	/* consultoras */
	int get_dimension() const; // devuelve la dimensión del tablero
	tCelda get_celda(int f, int c) const; // devuelve la celda en la posición (f,c)

	string get_path() const; // ...

	bool finish() const ; // true si y sólo si el Sudoku está resuelto
	bool blocked() const ; // true si el Sudoku tiene celdas bloqueadas

	int get_num_celdas_blocked() const ; // devuelve el número de celdas bloqueadas
	int get_num_celdas_empty() const ; // devuelve el número de celdas vacías

	void get_celdas_blocked(int p, int& f, int& c) const; // devuelve en (f,c) la celda bloqueada en la posición p - creamos un metodo privado set_celdas_blocked

	bool is_posible_value(int f, int c, int v) const; // true si y sólo si v se puede colocar en (f,c)
	int posible_values(int f, int c) const; // devuelve el número de posibles valores para (f,c)
	
	int cuantas_celdas_pueden_tener(int n_valores) const; // devuelve el número de celdas que pueden tener exactamente n_valores posibles (v2)

	/* modificadoras */
	void set_path(string path); // ...

	bool set_value(int f, int c, tCelda celda); // pone v en (f,c)
	bool clear_value(int f, int c); // pone la celda (f,c) a VACIA

	void reset(); // recupera el Sudoku original
	void autofill(); // rellena todas las celdas con un único valor posible

	/* inicializadora */
	void load_sudoku(ifstream & file); // carga un Sudoku original de un archivo

	/* metodo auxiliar lista dinamica */
	void resize(lPositionBlocked& lb, bool increase); // redimensiona la lista de celdas bloqueadas, aumentando o disminuyendo su capacidad en x2

	/* sobrecarga de operadores */
	bool operator<(const tReglasSudoku& s2) const;
	bool operator==(const tReglasSudoku& s2) const;
	tReglasSudoku& operator= (const tReglasSudoku& reglas);
};
