#include "h/reglasSudoku.h"
#include "h/mostrar.h"

string const PATH = "files/sudoku_1.txt";

void ask(tReglasSudoku& const rTab) {

	if (rTab.blocked()) showBlocked(rTab);
	showTablero(rTab);
	showMenu();
}


int main() {

	tReglasSudoku rTab;
	ifstream arc;

	int option, i, j, aux1, valor;
	char char1;
	bool exit = false;
	tCelda celda;

	arc.open(PATH);
	if (!arc.is_open()) {
		cout << "Fallo al cargar archivo.";
		return 1;
	}
	rTab.load_sudoku(arc);

	showTablero(rTab);
	showMenu();
	do {
		cin >> option;
		switch (option) {
		case 1:
			cout << "Fila y columna entre 1...9: ";
			cin >> i >> j;
			cout << "Valor: ";
			cin >> valor;

			if (rTab.is_posible_value(i - 1, j - 1, valor)) {
				celda.set_value(valor);
				celda.set_taken();
				rTab.set_value(i, j, celda);

			}	

			ask(rTab);
			break;

		case 2:
			cout << "Fila y columna entre 1...9: ";
			cin >> i >> j;

			rTab.clear_value(i - 1, j - 1);

			ask(rTab);
			break;

		case 3:
			rTab.reset();

			ask(rTab);
			break;

		case 4:
			cout << "Fila y columna entre 1...9: ";
			cin >> i >> j;

			cout << "Los posibles valores para la celda son: { ";
			for (int a = 0; a <= 9; a++) {
				if (rTab.is_posible_value(i - 1, j - 1, a)) cout << a << " ";
			}
			cout << "}\n";

			ask(rTab);
			break;

		case 5:
			rTab.autofill();

			ask(rTab);
			break;

		case 6:

			cout << "Ya te rindes?(S/N)"; cin >> char1;
			if (char1 == 'N') {
				cout << "Elige otra opcion entonces: ";
				ask(rTab);
			}
			else if (char1 == 'S') exit = true;	
			else {
				cout << "Subnormal, si quieres salir pon S\n"; // cambiar cuando lo entreguemos
				ask(rTab);
			}
			break;

		default:
			cout << "Elige una opcion correcta: ";
			cin >> option;
			break;
		}
		if (rTab.finish()){
			cout << "\n\nLO HAS LOGRADO!!!\nIntroduce una letra para salir:\n";
			cin >> char1; 
			exit = true;
		}

	} while (!exit);

	return 0;
}

