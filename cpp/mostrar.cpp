#include "../h/mostrar.h"
using namespace std;

void barHorizontal(int j) {

	cout << setw(4) << setfill(' ') << ' ';
	for (int i = 0; i < j; i++)
		cout << char(CRUZ) << setw(3 * j) << setfill(char(BARRA_HORIZONTAL)) << char(BARRA_HORIZONTAL);

	cout << char(CRUZ) << '\n';
}

void table(tReglasSudoku& const tab) {

	int i = tab.get_dimension();
	int j = sqrt(i);
	// cout << "i es " << i << " y j es " << j << '\n';
	tCelda aux;

	for (int a = 0; a < i; a += j) {

		barHorizontal(j);
		for (int b = 0; b < j; b++) {

			cout << ' ' << left << setw(3) << setfill(' ') << a + b + 1;

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

	cout << "\n\n" << setw(6) << setfill(' ') << ' ';
	for (int c = 1; c <= i; c += j) {
		for (int d = 0; d < j; d++)
			cout << left << setw(3) << setfill(' ') << c+d;

		cout << ' ';
	}
	cout << "\n";

	table(tab);

	cout << '\n';
}

void showMenu() {

	cout << 
		"1.- Poner numero\n" <<
		"2.- Quitar numero\n" <<
		"3.- Reset\n" <<
		"4.- Posibles valores de una celda vacia\n" <<
		"5.- Autocompletar celdas con valor unico\n" <<
		"6.- Salir\n" <<
		"Elige una opcion: ";
}

void showBlocked(tReglasSudoku& const regTab) {

	cout << "Sudoku bloqueado...\n" <<
		"Las casillas bloqueadas son: ";

	int n = regTab.get_num_celdas_blocked(), a,b;
	for (int i = 0; i < n; i++) {
		regTab.get_celdas_blocked(i, a, b);
		cout << '(' << a + 1 << ',' << b + 1 << ")  ";
	}
	cout << '\n' <<
		"Considere la opcion de cambiar los valores o resetear\n";
}