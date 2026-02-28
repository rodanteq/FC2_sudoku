#include "../h/reglasSudoku.h"


/* constructora */
tReglasSudoku::tReglasSudoku() : cont(0), tablero(), blockedPosition(){};

/* consultoras */
int tReglasSudoku::get_dimension() const {
	return tablero.get_dimension();
}
tCelda tReglasSudoku::get_celda(int f, int c) const {
	return tablero.get_value(f, c);
}
bool tReglasSudoku::finish() const {
	return cont == tablero.get_dimension() * tablero.get_dimension();
}
bool tReglasSudoku::blocked() const {
	return blockedPosition.n > 0;
}
int tReglasSudoku::get_num_celdas_blocked() const {
	return blockedPosition.n;
}
int tReglasSudoku::get_num_celdas_empty() const {
	return tablero.get_dimension() * tablero.get_dimension() - cont;
}
void tReglasSudoku::get_celdas_blocked(int p, int& f, int& c) const {
	f = blockedPosition.dat[p][0];
	c = blockedPosition.dat[p][1];
}
bool tReglasSudoku::is_posible_value(int f, int c, int v) const {
	if (not tablero.get_value(f, c).is_empty()) {
		cout << "Error, celda ya ocupada\n";
		return false;
	}
	int i = 0, j = 0, dimsqr, sqrx, sqry; 
	int dim = tablero.get_dimension();
	bool posible = true;
	// comprobar fila, columna y cuadrado (recordar que va de 0 a 8)
	dimsqr = sqrt(dim);
	sqrx = c / dimsqr;
	sqry = f / dimsqr;
	while (i < dim && posible) { // revisamos fila, variable 'i' es la columna
		if (not tablero.get_value(f, i).is_empty() && tablero.get_value(f, i).get_value() == v) {
			posible = false;
		}
		i++;
	}
	while (j < dim && posible) { // revisamos columna, variable 'j' es la fila
		if (not tablero.get_value(j, c).is_empty() && tablero.get_value(j, c).get_value() == v) {
			posible = false;
		}
		j++;
	}
	i = 0, j = 0;
	while (i < dimsqr && posible) {
		while (j < dimsqr && posible) {
			if (not tablero.get_value(sqry*dimsqr + i, sqrx*dimsqr + j).is_empty() && tablero.get_value(sqry * dimsqr + i, sqrx * dimsqr + j).get_value() == v) {
				posible = false;
			}
			j++;
		}
		i++; j = 0;
	}
	return posible;
}
int tReglasSudoku::posible_values(int f, int c) const { // en este caso los numeros van del 1-9

	int resultado = 0;
	for (int i = 1; i <= tablero.get_dimension(); i++) {

		if (is_posible_value(f, c, i)) resultado++;
	}
	return resultado;
}

/* modificadoras */
bool previously_blocked(int f, int c, tReglasSudoku& s, const int dat[MAX_BLOCKED][2]) {
	
	int i = 0;
	bool encontrado = false;
	int n = s.get_num_celdas_blocked();
	while (i < n && not encontrado) {
		if (dat[i][0] == f && dat[i][1] == c) {

			encontrado = true;
		}
		i++;
	}
	return encontrado;
}
void search_new_blocked(int f, int c, tReglasSudoku& s, int dat[MAX_BLOCKED][2], int& n) { // pasar s, dat y n por referencia (lo puede modificar??)

	int resultado = 0;

	int i = 0, j = 0, dimsqr, sqrx, sqry;
	int dim = s.get_dimension();
	// comprobar fila, columna y cuadrado (recordar que va de 0 a 8)
	dimsqr = sqrt(dim);
	sqrx = c / dimsqr;
	sqry = f / dimsqr;
	while (i < dim) { // revisamos fila, variable 'i' es la columna
		if (s.get_celda(f, i).is_empty() && s.posible_values(f, i) == 0 && not previously_blocked(f, i, s, dat)) { // con encontrar 1 valor posible, ya podríamos salirnos de la busqueda posible_values
			dat[n][0] = f;
			dat[n][1] = i;
			n++;
		}
		i++;
	}
	while (j < dim) { // revisamos columna, variable 'j' es la fila
		if (s.get_celda(j, c).is_empty() && s.posible_values(j, c) == 0 && not previously_blocked(j, c, s, dat)) {
			dat[n][0] = j;
			dat[n][1] = c;
			n++;
		}
		j++;
	}
	i = 0, j = 0;
	while (i < dimsqr) {
		while (j < dimsqr) {
			if (s.get_celda(sqry * dimsqr + i, sqrx * dimsqr + j).is_empty() && s.posible_values(sqry * dimsqr + i, sqrx * dimsqr + j) == 0 && not previously_blocked(sqry * dimsqr + i, sqrx * dimsqr + j, s, dat)) {
				dat[n][0] = sqry * dimsqr + i;
				dat[n][1] = sqrx * dimsqr + j;
				n++;
			}
			j++;
		}
		i++; j = 0;
	}
}

bool tReglasSudoku::set_value(int f, int c, int v) {

	int dim = tablero.get_dimension();
	if (f < dim && c < dim && v < dim && tablero.get_value(f, c).is_empty() && is_posible_value(f, c, v)) {

		tablero.set_value(f, c, v);
		cont++;
		search_new_blocked(f, c, *this, blockedPosition.dat, blockedPosition.n);

		return true;
	}
	else return false;
}
bool tReglasSudoku::clear_value(int f, int c) {

}
void tReglasSudoku::reset() {

}
void tReglasSudoku::autofill() {

}

/* inicializadora */
void tReglasSudoku::load_sudoku(ifstream& file) {

}