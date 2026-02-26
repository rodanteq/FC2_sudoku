#include "reglasSudoku.h"


ReglasSudoku::ReglasSudoku() : cont(0), tablero(), blockedPosition(){};

int ReglasSudoku::get_dimension() const {
	return tablero.get_dimension();
}

Celda ReglasSudoku::get_celda(int f, int c) const {
	return tablero.get_value(f, c);
}

bool ReglasSudoku::finish() const {
	return cont == tablero.get_dimension();
}
bool ReglasSudoku::blocked() const {

}
int ReglasSudoku::get_num_celdas_blocked() const {

}
int ReglasSudoku::get_num_celdas_empty() const {

}
void ReglasSudoku::get_celdas_blocked(int p, int& f, int& c) const {

}
bool ReglasSudoku::is_posible_value(int f, int c, int v) const {

}
int ReglasSudoku::posible_values(int f, int c) const {

}

/* modificadoras */
void ReglasSudoku::set_value(int f, int c, int v) {

}
void ReglasSudoku::clear_value(int f, int c) {

}
void ReglasSudoku::reset() {

}
void ReglasSudoku::autofill() {

}
/* inicializadora */
void ReglasSudoku::load_sudoku(ifstream& file) {

}