
#include "h/reglasSudoku.h"
#include "h/mostrar.h"


string const PATH = "files/sudoku_9.txt";
string titulo = R"(
  ____  _   _ ____   ___  _  _  _   _ 
 / ___|| | | |  _ \ / _ \| |/ /| | | |
 \___ \| | | | | | | | | | ' / | | | |
  ___) | |_| | |_| | |_| | . \ | |_| |
 |____/ \___/|____/ \___/|_|\_\ \___/ 

Hecho por: Carlos Martin-Salas y Rodrigo Antequera
Febrero 2026
)";

void ask(tReglasSudoku& const rTab) {

	if (rTab.blocked()) showBlocked(rTab);
	showTablero(rTab);
	showMenu();
}
bool resolver_sudoku(tReglasSudoku& reglas, int fila, int columna) {
	int n = reglas.get_dimension(), nfila = fila, ncolumna = columna;
	bool res = false;
	tCelda celda; celda.set_taken();
	do {
		if (ncolumna < n - 1) ncolumna++;
		else if (nfila < n - 1) {
			nfila++;
			ncolumna = 0;
		}
		else if (nfila == n - 1) nfila++; // para salir del bucle
	} while (!reglas.get_celda(nfila, ncolumna).is_empty() && nfila < n && ncolumna < n );


	if (reglas.finish()) return true;
	if (reglas.blocked() || reglas.posible_values(fila, columna) == 0) return false;

	if (!reglas.get_celda(fila, columna).is_empty()) {

		resolver_sudoku(reglas, nfila, ncolumna);
	}
	else {
		int i = 1;
		while (i <= n && !res) {
			if (reglas.is_posible_value(fila, columna, i)) {
				celda.set_value(i);
				reglas.set_value(fila, columna, celda);
				res = resolver_sudoku(reglas, nfila, ncolumna);
				if (!res) {
					reglas.clear_value(fila, columna);
					// cout << "Mal en " << fila << ' ' << columna << endl;
				}
			}
			i++;
		}
	}

	return res;
	
}


int main() {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	cout << DGREEN << titulo << RESET << endl;

	tReglasSudoku rTab;
	ifstream arc;

	int option, i, j, aux1, valor;
	char char1;
	bool exit = false, resuelto=false;
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
			cout << "Fila (valor entre 1..." << rTab.get_dimension() << ") : ";
			cin >> i;
			cout << "Columna (valor entre 1..." << rTab.get_dimension() << ") : ";
			cin >> j;
			cout << "Valor: ";
			cin >> valor;

			if (rTab.is_posible_value(i - 1, j - 1, valor)) {
				celda.set_value(valor);
				celda.set_taken();
				rTab.set_value(i - 1, j - 1, celda);

			}	

			ask(rTab);
			break;

		case 2:
			cout << "Fila (valor entre 1..." << rTab.get_dimension() << ") : ";
			cin >> i;
			cout << "Columna (valor entre 1..." << rTab.get_dimension() << ") : ";
			cin >> j;

			if(rTab.clear_value(i - 1, j - 1)) cout << "Valor borrado\n";
			
			ask(rTab);
			break;

		case 3:
			rTab.reset();

			ask(rTab);
			break;

		case 4:
			cout << "Fila (valor entre 1..." << rTab.get_dimension() << ") : ";
			cin >> i;
			cout << "Columna (valor entre 1..." << rTab.get_dimension() << ") : ";
			cin >> j;

			if (rTab.get_celda(i-1, j-1).is_original()) {

				cout << "Error, celda original\n";
			}
			else if (rTab.get_celda(i-1, j-1).is_taken()) {

				cout << "Error, celda ocupada\n";
			}
			else {

				cout << "Los posibles valores para la celda son: { ";
				for (int a = 1; a <= rTab.get_dimension(); a++) {
					if (rTab.is_posible_value(i - 1, j - 1, a)) cout << a << " ";
				}
				cout << "}\n";
			}
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
				cout << "Si quieres salir pon S\n";
				ask(rTab);
			}
			break;

		case 7:
			resuelto = resolver_sudoku(rTab, 0, 0);
			ask(rTab);

			break;

		default:
			cout << "Elige una opcion correcta: ";
			break;
		}
		if (rTab.finish()){
			cout << YELLOW << "\n\nLO HAS LOGRADO!!!\nIntroduce una letra para salir:\n" << RESET;
			cin >> char1; 
			exit = true;
		}
		cout << '\n';

	} while (!exit);

	return 0;
}
