#pragma once
#include <fstream>
#include "tablero.h"

using namespace std;

class tReglasSudoku {

private:

	struct tPos {
		int f=0;
		int c=0;
	};

	struct lPositionBlocked {
		int dim = 1;
		tPos** p = new tPos * [dim];
		int n = 0; 
	};
	struct tValor {
		bool posible = false;
		int celdas_que_afectan = 0;
	};
	typedef int arrValores[DIM_TABLERO];

	tTablero tablero;
	int cont;
	lPositionBlocked blockedPosition;
	tValor valores_celda[DIM_TABLERO][DIM_TABLERO][DIM_TABLERO]; // el valor maximo sera igual a la dimension
	string path;
	arrValores cuantas_celdas;

	/* metodos privados */
	void set_celdas_blocked(int pos, int f, int c);
	void clear_celdas_blocked(int pos);
	void set_up_block_values(int dimension);
	void clear_blocked_values(int f, int c, int v);

	void block_values(int f, int c, int v);

	int get_posible_value(int f, int c) const;
	bool previously_blocked(int f, int c, int& res) const;

	/*sobrecarga*/
	

public:

	/* constructora */
	tReglasSudoku();
	tReglasSudoku(const tReglasSudoku& sudoku);

	/* consultoras */
	int get_dimension() const; // devuelve la dimensión del tablero
	tCelda get_celda(int f, int c) const; // devuelve la celda en la posición (f,c)
	string get_path() const;

	bool finish() const ; // true si y sólo si el Sudoku está resuelto
	bool blocked() const ; // true si el Sudoku tiene celdas bloqueadas
	int get_num_celdas_blocked() const ; // devuelve el número de celdas bloqueadas
	int get_num_celdas_empty() const ; // devuelve el número de celdas vacías

	void get_celdas_blocked(int p, int& f, int& c) const; // devuelve en (f,c) la celda bloqueada en la posición p - creamos un metodo privado set_celdas_blocked
	bool is_posible_value(int f, int c, int v) const; // true si y sólo si v se puede colocar en (f,c)
	int posible_values(int f, int c) const; // devuelve el número de posibles valores para (f,c)
	
	/* modificadoras */
	void set_path(string path);
	bool set_value(int f, int c, tCelda celda); // pone v en (f,c)
	bool clear_value(int f, int c); // pone la celda (f,c) a VACIA
	void reset(); // recupera el Sudoku original
	void autofill(); // rellena todas las celdas con un único valor posible

	/* inicializadora */
	void load_sudoku(ifstream & file); // carga un Sudoku original de un archivo

	/* Método auxiliar lista dinamica */
	void resize(lPositionBlocked& lb, bool increase);

	int cuantas_celdas_pueden_tener(int n_valores) const;

	bool operator<(const tReglasSudoku& s2) const;
	bool operator==(const tReglasSudoku& s2) const;
	tReglasSudoku& operator= (const tReglasSudoku& reglas);
};
