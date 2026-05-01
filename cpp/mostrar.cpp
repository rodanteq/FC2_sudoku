#include "../h/mostrar.h"
using namespace std;

void barHorizontal(int j) { // funcion auxiliar para poner la barra horizontal

	cout << setw(4) << setfill(' ') << ' ';
	for (int i = 0; i < j; i++)
		cout << char(CRUZ) << setw(3 * j) << setfill(char(BARRA_HORIZONTAL)) << char(BARRA_HORIZONTAL);

	cout << char(CRUZ) << '\n';
}

void table(tReglasSudoku& const tab) { // funcion auxiliar que muestra el tablero

	int i = tab.get_dimension();
	int j = sqrt(i);
	tCelda aux;

	for (int a = 0; a < i; a += j) {

		barHorizontal(j);
		for (int b = 0; b < j; b++) {

			cout << MAGENTA << ' ' << left << setw(3) << setfill(' ') << a + b + 1 << RESET;

			for (int c = 0; c < i; c += j) {

				cout << char(BARRA_VERTICAL);
				for (int d = 0; d < j; d++) {

					cout << ' ';
					aux = tab.get_celda(a + b, c + d);
					if (aux.is_empty())
						cout << char(BLANCO) << ' ';
					else if (aux.is_original()) 
						cout << ORANGE << aux.get_value() << RESET << ' ';
					else 
						cout << setw(2) << setfill(' ') << left << aux.get_value();					
				}
			}
			cout << char(BARRA_VERTICAL) << '\n';
		}
	}
	barHorizontal(j);
}

void showTablero(tReglasSudoku& const tab) {

	int i, j;
	i = tab.get_dimension();
	j = sqrt(i);

	cout << "\n" << setw(6) << setfill(' ') << ' ';
	for (int c = 1; c <= i; c += j) {
		for (int d = 0; d < j; d++)
			cout << MAGENTA << left << setw(3) << setfill(' ') << c+d << RESET;

		cout << ' ';
	}
	cout << "\n";

	table(tab);

	cout << '\n';
}

void showMenu() {

	cout << LBLUE <<
		"1.- Poner numero\n" <<
		"2.- Quitar numero\n" <<
		"3.- Reset\n" <<
		"4.- Posibles valores de una celda vacia\n" <<
		"5.- Autocompletar celdas con valor unico\n" <<
		"6.- Salir\n" <<
		"7.- Terminar sudoku\n\n";
	cout << YELLOW <<
		"Elige una opcion: " << RESET;
}

void showBlocked(tReglasSudoku& const regTab) {

	cout << RED << "Sudoku bloqueado...\n" <<
		"Las casillas bloqueadas son: " << RESET;

	int n = regTab.get_num_celdas_blocked(), a,b;
	for (int i = 0; i < n; i++) {
		regTab.get_celdas_blocked(i, a, b);
		cout << '(' << a + 1 << ',' << b + 1 << ")  ";
	}
	cout << '\n' << RED <<
		"Considere la opcion de cambiar los valores o resetear\n" << RESET;
}