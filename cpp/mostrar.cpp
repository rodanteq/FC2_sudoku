#include "../h/mostrar.h"
using namespace std;

void barHorizontal(int j) {
	cout << "  ";
	for (int i = 0; i < j; i++)
		cout << char(CRUZ) << setw(j * ANCHO_CELDA) << setfill(char(BARRA_HORIZONTAL)) << char(BARRA_HORIZONTAL);
	cout << char(CRUZ) << '\n';
}

void table(tReglasSudoku& const tab) {
	int i = tab.get_dimension();
	int j = sqrt(i);
	for (int a = 0; a < i; a += j) {
		barHorizontal(j);
		for (int b = 0; b < j; b++) {
			cout << a + b + 1 << ' ';
			for (int c = 0; c < i; c += j) {
				cout << char(BARRA_VERTICAL);
				for (int d = 0; d < j; d++) {
					cout << setw(MITAD_ANCHO) << setfill(' ') << ' ';
					if (tab.get_celda(a + b, c + d).is_empty())
						cout << char(BLANCO);
					else cout << tab.get_celda(a + b, c + d).get_value();
					cout << setw(MITAD_ANCHO) << setfill(' ') << ' ';
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


	cout << "\n\n   ";
	for (int c = 1; c <= i; c += j) {
		for (int d = 0; d < j; d++)
			cout << setw(MITAD_ANCHO) << setfill(' ') << ' ' << c+d << setw(MITAD_ANCHO) << setfill(' ') << ' ';
		cout << ' ';
	}
	cout << "\n";

	table(tab);
	cout << '\n';
}

void showMenu() {
	cout << "1.- poner numero\n" <<
		"2.- quitar numero\n" <<
		"3.- reset\n" <<
		"4.- posibles valores de una celda vacia\n" <<
		"5.- autocompletar celdas con valor unico\n" <<
		"6.- salir\n" <<
		"Elige una opcion: ";
}

void showBlocked(tReglasSudoku& const regTab) {
	cout << "Sudoku bloqueado.....\n" <<
		"Las casillas bloqueadas son: ";

	int n = regTab.get_num_celdas_blocked(), a,b;
	for (int i = 0; i < n; i++) {
		regTab.get_celdas_blocked(n, a, b);
		cout << '(' << a << ',' << b << ")  ";
	}
	cout << '\n' <<
		"Considere la opcion de cambiar los valores o resetear\n";
}