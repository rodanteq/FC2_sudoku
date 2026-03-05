#include "h/reglasSudoku.h"
#include "h/mostrar.h"

string const PATH = "files/sudoku_1.txt";

void ask(tReglasSudoku& const rTab, int& option) {
	if (rTab.blocked())
		showBlocked(rTab);
	showTablero(rTab);
	showMenu();
	cin >> option;
}


int main() {
	tReglasSudoku rTab;
	ifstream arc;
	int option, i, j, aux1, valor;
	char char1;
	bool exit = false;

	arc.open(PATH);
	if (!arc.is_open()) {
		cout << "Fallo al cargar archivo.";
		return 1;
	}
	rTab.load_sudoku(arc);

	showTablero(rTab);
	showMenu();
	cin >> option;
	while (!exit) {
		switch (option) {
		case 1:
			cout << "Fila y columna entre 1...9: ";
			cin >> i >> j;
			cout << "Valor: ";
			cin >> valor;

			if (rTab.is_posible_value(i, j, valor)) {
				rTab.set_value(i, j, valor);

			}

			

			ask(rTab, option);
			break;
		case 2:
			cout << "Fila y columna entre 1...9: ";
			cin >> i >> j;

			rTab.clear_value(i, j);

			ask(rTab, option);
			break;
		case 3:
			rTab.reset();

			ask(rTab, option);
			break;
		case 4:
			cout << "Fila y columna entre 1...9: ";
			cin >> i >> j;

			cout << "Los posibles valores para la celda son: { ";
			for (int a = 0; a <= 9; a++) {
				if (rTab.is_posible_value(i, j, a)) cout << a << " ";
			}
			cout << "}\n";

			ask(rTab, option);
			break;
		case 5:
			rTab.autofill();

			ask(rTab, option);
			break;
		case 6:
			cout << "Ya te rindes?(S/N)"; cin >> char1;
			if (char1 == 'N') {
				cout << "Elige otra opcion entonces: ";
				cin >> option;
			}
			else exit = true;
			break;
		default:
			cout << "Elige una opcion correcta: ";
			cin >> option;
			break;
		}
		if (rTab.finish()){
			cout << "\n\n  Lo has logrado!!!\n";
			cin >> char1;
			exit = true;
		}
		cout << rTab.get_celda(1, 1).is_empty();
	}
	return 0;
}

