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

bool tReglasSudoku::finish() const { // comprobar si los valores son correctos??
	return cont == get_dimension() * get_dimension();
}
bool tReglasSudoku::blocked() const {
	return blockedPosition.n > 0;
}
int tReglasSudoku::get_num_celdas_blocked() const {
	return blockedPosition.n;
}
int tReglasSudoku::get_num_celdas_empty() const {
	return get_dimension() * get_dimension() - cont;
}
void tReglasSudoku::get_celdas_blocked(int p, int& f, int& c) const {
	f = blockedPosition.dat[p][0];
	c = blockedPosition.dat[p][1];
}
bool tReglasSudoku::is_posible_value(int f, int c, int v) const {
	if (not get_celda(f, c).is_empty()) {
		cout << "Error, celda ya ocupada\n";
		return false;
	}
	else if (v > get_dimension() || v <= 0) {
		cout << "Error, numero invalido\n";
		return false;
	}
	int i = 0, j = 0, dimsqr, sqrx, sqry; 
	int dim = get_dimension();
	bool posible = true;
	// comprobar fila, columna y cuadrado (recordar que va de 0 a 8)
	dimsqr = sqrt(dim);
	sqrx = c / dimsqr;
	sqry = f / dimsqr;
	while (i < dim && posible) { // revisamos fila, variable 'i' es la columna
		if (not get_celda(f, i).is_empty() && get_celda(f, i).get_value() == v) {
			posible = false;
		}
		i++;
	}
	while (j < dim && posible) { // revisamos columna, variable 'j' es la fila
		if (not get_celda(j, c).is_empty() && get_celda(j, c).get_value() == v) {
			posible = false;
		}
		j++;
	}
	i = 0, j = 0;
	while (i < dimsqr && posible) {
		while (j < dimsqr && posible) {
			if (not get_celda(sqry * dimsqr + i, sqrx * dimsqr + j).is_empty() && get_celda(sqry * dimsqr + i, sqrx * dimsqr + j).get_value() == v) {
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
	for (int i = 1; i <= get_dimension(); i++) {

		if (is_posible_value(f, c, i)) resultado++;
	}
	return resultado;
}

/* modificadoras */
void tReglasSudoku::set_celdas_blocked(int p, int f, int c) {
	blockedPosition.dat[p][0] = f;
	blockedPosition.dat[p][1] = c;
}
bool tReglasSudoku::previously_blocked(int f, int c) const {
	
	int i = 0; int faux, caux;
	bool encontrado = false;
	int n = get_num_celdas_blocked();

	while (i < n && not encontrado) {

		get_celdas_blocked(i, faux, caux);
		if (faux == f && caux == c) {

			encontrado = true;
		}
		i++;
	}
	return encontrado;
}
void tReglasSudoku::search_new_blocked(int f, int c) {

	int resultado = 0;

	int i = 0, j = 0, dimsqr, sqrx, sqry;
	int dim = get_dimension();
	// comprobar fila, columna y cuadrado (recordar que va de 0 a 8)
	dimsqr = sqrt(dim);
	sqrx = c / dimsqr;
	sqry = f / dimsqr;
	while (i < dim) { // revisamos fila, variable 'i' es la columna
		if (get_celda(f, i).is_empty() && posible_values(f, i) == 0 && not previously_blocked(f, i)) { // con encontrar 1 valor posible, ya podríamos salirnos de la busqueda posible_values
			
			set_celdas_blocked(get_num_celdas_blocked(), f, i);
			blockedPosition.n++;
		}
		i++;
	}
	while (j < dim) { // revisamos columna, variable 'j' es la fila
		if (get_celda(j, c).is_empty() && posible_values(j, c) == 0 && not previously_blocked(j, c)) {
			
			set_celdas_blocked(get_num_celdas_blocked(), j, c);
			blockedPosition.n++;
		}
		j++;
	}
	i = 0, j = 0;
	while (i < dimsqr) {
		while (j < dimsqr) {
			if (get_celda(sqry * dimsqr + i, sqrx * dimsqr + j).is_empty() && posible_values(sqry * dimsqr + i, sqrx * dimsqr + j) == 0 && not previously_blocked(sqry * dimsqr + i, sqrx * dimsqr + j)) {

				set_celdas_blocked(get_num_celdas_blocked(), sqry * dimsqr + i, sqrx * dimsqr + j);
				blockedPosition.n++;
			}
			j++;
		}
		i++; j = 0;
	}
}
void tReglasSudoku::search_not_blocked(int f, int c) {

	int faux, caux;
	for (int i = 0; i < get_num_celdas_blocked(); i++) {

		get_celdas_blocked(i, faux, caux);

		if (posible_values(faux, caux) == 0) {

			for (int j = i; j < get_num_celdas_blocked() - 1; j++) {

				get_celdas_blocked(get_num_celdas_blocked() - 1, faux, caux);
				set_celdas_blocked(j, faux, caux);
			}
			blockedPosition.n--;
		}
	}
}
int tReglasSudoku::get_posible_value(int f, int c) const { // presuponemos que se utilizara cuando solo quede una posicion posible

	int num = 1;
	while (num <= get_dimension() && not is_posible_value(f, c, num)) {
		num++;
	}
	return num;
}

bool tReglasSudoku::set_value(int f, int c, tCelda celda) {

	int dim = get_dimension();
	if (f < dim && c < dim && is_posible_value(f, c, celda.get_value())) {

		tablero.set_value(f, c, celda); 
		cont++;
		search_new_blocked(f, c);

		return true;
	}
	else return false;
}
bool tReglasSudoku::clear_value(int f, int c) {

	tCelda celda;
	celda.set_empty();

	int dim = get_dimension();
	if (f < dim && c < dim && not get_celda(f, c).is_empty()) {

		tablero.set_value(f, c, celda);
		cont--;
		search_not_blocked(f, c);

		return true;
	}
	else return false;
}
void tReglasSudoku::reset() {

	tCelda celda;
	celda.set_empty();

	for (int i = 0; i < get_dimension(); i++) {

		for (int j = 0; j < get_dimension(); j++) {

			if (not get_celda(i, j).is_original()) {

				tablero.set_value(i, j, celda);
			}
		}
	}

}
void tReglasSudoku::autofill() {

	tCelda celda;
	celda.set_taken();

	for (int i = 0; i < get_dimension(); i++) {
		for (int j = 0; j < get_dimension(); j++) {
			if (get_celda(i, j).is_empty() && posible_values(i, j) == 1) {

				celda.set_value(get_posible_value(i, j));
				set_value(i, j, celda);	
			}
		}
	}
}

/* inicializadora */
void tReglasSudoku::load_sudoku(ifstream& file) {
	int v;
	int dim;
	file >> dim;

	tCelda celda;

	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			file >> v;
			if (v != 0) {
				celda.set_value(v);
				celda.set_original();
				tablero.set_value(i, j, celda);
				cont++;
			}
			else {
				celda.set_empty();
				tablero.set_value(i, j, celda);
			}
		}
	}
}