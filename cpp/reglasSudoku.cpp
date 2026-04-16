#include "../h/reglasSudoku.h"
#include "../h/checkML.h"

tReglasSudoku& tReglasSudoku::operator= (const tReglasSudoku& reglas) {

	if (this != &reglas) { // evita autoasignación
		/* se libera la memoria ocupada por this*/
		delete this->blockedPosition.p;
		*this->blockedPosition.p = new tPos(**(reglas.blockedPosition.p));
	}
	this->cont = reglas.cont;
	this->tablero = reglas.tablero;
	this->valores_celda = reglas.valores_celda;
	this->blockedPosition.dim = reglas.blockedPosition.dim;
	this->blockedPosition.n = reglas.blockedPosition.n;

	return *this;
}

/* constructora */
tReglasSudoku::tReglasSudoku() {

	for (int i = 0; i <= this->blockedPosition.n; i++) {
		this->blockedPosition.p[i] = new tPos;
	}
	this->cont = 0;

}
tReglasSudoku::tReglasSudoku(const tReglasSudoku& sudoku) {
	*this = sudoku;
}

/* consultoras */
int tReglasSudoku::get_dimension() const {
	return tablero.get_dimension();
}
tCelda tReglasSudoku::get_celda(int f, int c) const {
	return tablero.get_value(f, c);
}

bool tReglasSudoku::finish() const {
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
void tReglasSudoku::get_celdas_blocked(int pos, int& f, int& c) const {
	f = blockedPosition.p[pos]->f;
	c = blockedPosition.p[pos]->c;
}
bool tReglasSudoku::is_posible_value(int f, int c, int v) const {
	return valores_celda.valores[f][c][v - 1].posible;
}
int tReglasSudoku::posible_values(int f, int c) const { // en este caso los numeros van del 1-9

	int resultado = 0;
	for (int i = 1; i <= get_dimension(); i++) {

		if (is_posible_value(f, c, i)) resultado++;
	}
	return resultado;
}

/* modificadoras */
void tReglasSudoku::set_up_block_values(int dimension) {
	for (int i = 0; i < dimension; i++) {
		for (int j = 0; j < dimension; j++) {
			for (int z = 0; z < dimension; z++) {
				valores_celda.valores[i][j][z].posible = true;
				valores_celda.valores[i][j][z].celdas_que_afectan = 0;
			}
		}
	}
}
void tReglasSudoku::block_values(int f, int c, int v) {
	int dim = get_dimension(), a;
	int hdim = sqrt(dim);
	for (int i = 0; i < dim; i++) {
		valores_celda.valores[f][i][v - 1].posible = false;
		valores_celda.valores[f][i][v - 1].celdas_que_afectan++;
		if (get_celda(f, i).is_empty() && posible_values(f, i) == 0 && not previously_blocked(f, i, a)) {
			set_celdas_blocked(get_num_celdas_blocked(), f, i);
		}
	}
	for (int i = 0; i < dim; i++) {
		valores_celda.valores[i][c][v - 1].posible = false;
		valores_celda.valores[i][c][v - 1].celdas_que_afectan++;
		if (get_celda(i, c).is_empty() && posible_values(i, c) == 0 && not previously_blocked(i, c, a)) {
			set_celdas_blocked(get_num_celdas_blocked(), i, c);
		}
	}
	int fa = f - (f % hdim), ca = c - (c % hdim);
	for (int i = 0; i < hdim; i++) {
		for (int j = 0; j < hdim; j++) {
			valores_celda.valores[fa + i][ca + j][v - 1].posible = false;
			valores_celda.valores[fa + i][ca + j][v - 1].celdas_que_afectan++;
			if (get_celda(fa + i, ca + j).is_empty() && posible_values(fa + i, ca + j) == 0 && not previously_blocked(fa + i, ca + j, a)) {
				set_celdas_blocked(get_num_celdas_blocked(), fa + i, ca + j);
			}
		}
	}
}
void tReglasSudoku::clear_blocked_values(int f, int c, int v) {
	int dim = get_dimension(), res, faux, caux;
	int hdim = sqrt(dim);
	for (int i = 0; i < dim; i++) {
		valores_celda.valores[f][i][v - 1].celdas_que_afectan--;
		if (valores_celda.valores[f][i][v - 1].celdas_que_afectan == 0) {
			valores_celda.valores[f][i][v - 1].posible = true;
			if (previously_blocked(f,i, res) && posible_values(f, i) != 0) {
				for (int d = res; d < get_num_celdas_blocked() - 1; d++) {
					get_celdas_blocked(d + 1, faux, caux);
					set_celdas_blocked(d, faux, caux);
				}
				blockedPosition.n--;
			}
		}

	}
	for (int i = 0; i < dim; i++) {
		valores_celda.valores[i][c][v - 1].celdas_que_afectan--;
		if (valores_celda.valores[i][c][v - 1].celdas_que_afectan == 0) {
			valores_celda.valores[i][c][v - 1].posible = true;
			if (previously_blocked(i, c, res) && posible_values(i, c) != 0) {
				for (int d = res; d < get_num_celdas_blocked() - 1; d++) {
					get_celdas_blocked(d + 1, faux, caux);
					set_celdas_blocked(d, faux, caux);
				}
				blockedPosition.n--;
			}
		}

	}
	int fa = f - (f % hdim), ca = c - (c % hdim);
	for (int i = 0; i < hdim; i++) {
		for (int j = 0; j < hdim; j++) {
			valores_celda.valores[fa + i][ca + j][v - 1].celdas_que_afectan--;
			if (valores_celda.valores[fa + i][ca + j][v - 1].celdas_que_afectan == 0) {
				valores_celda.valores[fa + i][ca + j][v - 1].posible = true;
				if (previously_blocked(fa + i, ca + j, res) && posible_values(fa + i, ca + j) != 0) {
					for (int d = res; d < get_num_celdas_blocked() - 1; d++) {
						get_celdas_blocked(d + 1, faux, caux);
						set_celdas_blocked(d, faux, caux);
					}
					blockedPosition.n--;
				}
			}

		}
	}
}
void tReglasSudoku::set_celdas_blocked(int pos, int fi, int ci) {
	if (blockedPosition.dim <= pos) {
		resize(blockedPosition);
	}
	if (blockedPosition.p[pos] == nullptr) {
		blockedPosition.p[pos] = new tPos;
	}

	blockedPosition.p[pos]->f=fi;
	blockedPosition.p[pos]->c=ci;
	
	blockedPosition.n++;
}
bool tReglasSudoku::previously_blocked(int f, int c, int& res) const { 
	
	int i = 0; int faux, caux;
	res = -1; 
	bool encontrado = false;
	int n = get_num_celdas_blocked();

	while (i < n && not encontrado) {

		get_celdas_blocked(i, faux, caux);
		if (faux == f && caux == c) {

			encontrado = true;
			res = i;
		}
		i++;
	}
	return (encontrado);
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
		block_values(f, c, celda.get_value());

		return true;
	}
	else return false;
}
bool tReglasSudoku::clear_value(int f, int c) {

	tCelda celda, oldCelda = get_celda(f, c);
	celda.set_empty();

	int dim = get_dimension();
	if (get_celda(f, c).is_empty()) {
		cout << "Error, celda ya vacia\n";
		return false;
	}
	else if (get_celda(f, c).is_original()) {
		cout << "Error, celda original\n";
		return false;
	}
	else if (f >= get_dimension() || c >= get_dimension() || f < 0 || c < 0) {
		cout << "Error, posicion fuera de rango\n";
		return false;
	}
	else {

		tablero.set_value(f, c, celda);
		cont--;
		clear_blocked_values(f, c, oldCelda.get_value());
		return true;
	}
}
void tReglasSudoku::reset() {

	tCelda celda;
	celda.set_empty();
	blockedPosition.n = 0;

	for (int i = 0; i < get_dimension(); i++) {

		for (int j = 0; j < get_dimension(); j++) {

			if (get_celda(i, j).is_taken()) {

				clear_value(i, j);
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
void tReglasSudoku::load_sudoku(ifstream& file) { // suponemos que el archivo es correcto
	int v;
	int dim;
	file >> dim;

	tablero.set_up(dim);
	set_up_block_values(dim);

	tCelda celda;

	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++) {
			file >> v;
			if (v != 0) {
				celda.set_value(v);
				celda.set_original();
				set_value(i, j, celda); // tiene en cuenta que haya posibles errores en el sudoku original
			}
			else {
				celda.set_empty();
				tablero.set_value(i, j, celda);
			}
		}
	}
}

void tReglasSudoku::resize(lPositionBlocked& lb) {

	if (lb.dim > lb.n)return;

	int size = lb.dim * 2;
	tPos** paux = new tPos*[size];
	for (int i = 0; i < lb.n; i++) {
		paux[i] = lb.p[i];
	}
	for (int i = lb.n; i < size; i++) {
		paux[i] = nullptr;
	}
	lb.dim = size;
	delete[] lb.p;
	lb.p = paux;
}