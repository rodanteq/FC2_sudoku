#include "../h/listaSudoku.h"
#include "../h/colors.h"
#include "../h/mostrar.h"

// constructora, destructora
tListaSudoku::tListaSudoku() : num_elems(0), dim(2) {

	lista = new tReglasSudoku * [dim];
	for (int i = 0; i < dim; i++) {

		lista[i] = nullptr;
	}
}
tListaSudoku::~tListaSudoku() {

	for (int i = 0; i < dim; i++) {

		delete lista[i];
	}
	delete[] lista;
}

// consultoras
int tListaSudoku::dame_num_elems() const{ // a veces salta un warning por la gestion de pila, he reducido MAX_DIM a 9

	return num_elems;
}
const tReglasSudoku& tListaSudoku::dame_sudoku(int i) const { // aquí me tienen que pasar valor entre [0 , num_elems-1]. Si no, se devuelve un sudoku vacío
	if (i < 0 || i >= num_elems) {

		cout << RED << "Error, indice fuera de rango\n" << RESET;
		return *lista[0]; // por devolver algo: CUIDADO si no hay elementos puede dar error
	}
	else {

		return *lista[i];
	}
}

void  tListaSudoku::mostrar_sudoku(int index) const {
	int n = this->lista[index]->get_dimension();
	cout << "Casillas vacias: " << this->lista[index]->get_num_celdas_empty() << '\n';
	for (int i = 1; i <= n; i++) {
		cout << "  Celdas con " << i << " valores posibles: " << this->lista[index]->cuantas_celdas_pueden_tener(i) << '\n';
	}
}

void tListaSudoku::mostrar_lista() const {

	cout << BLUE << "Hola, esta es la lista de sudokus disponibles:\n" << RESET;
	for (int i = 0; i < num_elems; i++) {
		cout << ROSE << "Sudoku " << i + 1 << '\n' << RESET;
		this->mostrar_sudoku(i);
		showTablero(*lista[i]);
	}
}

// modificadoras

//f auxiliar
int tListaSudoku::busquedaBinaria(const tReglasSudoku& sudoku)const {
	int a = 0, b = this->num_elems, c;
	while (b - a > 1) {
		c = (b - a) / 2 + a;
		if ((*this->lista[c] < sudoku) || (*this->lista[c] == sudoku)) a = c;
		else b = c;
	}
	if (this->num_elems!=0 && sudoku < *this->lista[a])b = a;
	return b;
}


void tListaSudoku::insertar(const tReglasSudoku& sudoku) {

	if (num_elems >= dim) { // si el numero de elementos es igual o mayor que la dimension, redimensionamos
		
		resize(*this, true);
	}
	int index = this->busquedaBinaria(sudoku);
	for (int i = num_elems; i > index;i--) lista[i] = lista[i - 1];
	lista[index] = new tReglasSudoku(sudoku);
	num_elems++;
}
void tListaSudoku::eliminar(int pos) { // elimina el elemento de la posición pos

	if (pos < 0 || pos >= num_elems) {

		cout << RED << "Error, indice fuera de rango\n" << RESET;
	}
	else {

		if (num_elems <= dim / 2) { // si el numero de elementos es menor o igual que la dimension / 2, redimensionamos

			resize(*this, false);
		}
		delete lista[pos];
		for (int i = pos; i < num_elems - 1; i++) {

			lista[i] = lista[i + 1];
		}
		lista[num_elems - 1] = nullptr;
		num_elems--;
	}
}

// redimensionar
void tListaSudoku::resize(tListaSudoku& ls, bool type) {

	int size;

	if (type) size=ls.dim * 2;
	else if (dim > 3) size = ls.dim / 2; // no tiene sentido hacerlo mas pequeño que 2
	else size = ls.dim;

	tReglasSudoku** paux = new tReglasSudoku * [size];
	for (int i = 0; i < ls.num_elems; i++) {
		paux[i] = ls.lista[i]; // copiamos los punteros, sabiendo que size es mayor que num_elems, no hay riesgo de overflow
	}
	for (int i = ls.num_elems; i < size; i++) {
		paux[i] = nullptr;
	}
	ls.dim = size;
	delete[] ls.lista;
	ls.lista = paux;
}