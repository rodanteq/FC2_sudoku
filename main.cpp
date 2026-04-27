#include "h/reglasSudoku.h"
#include "h/mostrar.h"
#include <string>

// CONVENIO PARA EL PASO DE DATOS POR REFERENCIA:
// Al llamar a una función, se le pasa el valor del dato en el array.
// Por ejemplo, si queremos pasar la posición (1,2) del sudoku, se le pasará el valor 0 para la fila y el valor 1 para la columna.

const int MAX_PATH = 10;
string titulo = R"(  :)
  ____  _   _ ____   ___  _  _ _   _ 
 / ___|| | | |  _ \ / _ \| |/ / | | |
 \___ \| | | | | | | | | | ' /| | | |
  ___) | |_| | |_| | |_| | . \| |_| |
 |____/ \___/|____/ \___/|_|\_\\___/

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
	tCelda celda; 
	celda.set_taken();

	do {
		if (ncolumna < n - 1) ncolumna++;
		else if (nfila < n - 1) {
			nfila++;
			ncolumna = 0;
		}
		else if (nfila == n - 1) nfila++; // para salir del bucle
	} while (!reglas.get_celda(nfila, ncolumna).is_empty() && nfila < n && ncolumna < n);
	if (reglas.finish()) return true;
	if (reglas.blocked() || not reglas.get_celda(fila, columna).is_empty() || reglas.posible_values(fila, columna) == 0) {
		if (not reglas.get_celda(fila, columna).is_empty()) {

			resolver_sudoku(reglas, nfila, ncolumna);
		}
		else return false;
	}
	if (reglas.get_celda(fila, columna).is_empty()) {

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
	if (fila == 0 && columna == 0) return reglas.finish();
	else return res;
}


int main() {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // memoria dinámica

	cout << GREEN << titulo << RESET << endl;

	tReglasSudoku rTab;
	tCelda celda;
	ifstream arc;

	int option, i, j, valor, num;
	bool exit = false, resuelto = false, pathcheck = false;
	char c;

	while (not pathcheck) {
		cout << ROSE << "Introduce el numero del archivo con el sudoku a resolver (ejemplo: \"1\" para resolver \"sudoku_1.txt\"): " << RESET;
		cin >> num;
		if (num < 0 || num > MAX_PATH) cout << RED << "Error, elige una opcion posible\n" << RESET;
		else pathcheck = true;
	}

	string PATH = "files/sudoku_" + to_string(num) + ".txt";

	arc.open(PATH);
	if (!arc.is_open()) {
		cout << RED << "Fallo al cargar archivo." << RESET;
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

			if (rTab.is_posible_value(i - 1, j - 1, valor)) { // comprobacion en la propia funcion is_posible_value

				celda.set_value(valor);
				celda.set_taken();

				rTab.set_value(i - 1, j - 1, celda);
				
				cout << ROSE << "Valor introducido\n" << RESET;
			}
			ask(rTab);
			break;

		case 2:
			cout << "Fila (valor entre 1..." << rTab.get_dimension() << ") : ";
			cin >> i;
			cout << "Columna (valor entre 1..." << rTab.get_dimension() << ") : ";
			cin >> j;

			if (rTab.clear_value(i - 1, j - 1)) cout << ROSE << "Valor borrado\n" << RESET; // comprobacion en la propia funcion clear_value
			
			ask(rTab);
			break;

		case 3:
			rTab.reset();

			cout << ROSE << "Sudoku reseteado\n" << RESET;

			ask(rTab);
			break;

		case 4:
			cout << "Fila (valor entre 1..." << rTab.get_dimension() << ") : ";
			cin >> i;
			cout << "Columna (valor entre 1..." << rTab.get_dimension() << ") : ";
			cin >> j;

			if (rTab.get_celda(i-1, j-1).is_original()) {

				cout << RED << "Error, celda original\n" << RESET;
			}
			else if (rTab.get_celda(i-1, j-1).is_taken()) {

				cout << RED << "Error, celda ocupada\n" << RESET;
			}
			else {

				cout << ROSE << "Los posibles valores para la celda son: { ";
				for (int a = 1; a <= rTab.get_dimension(); a++) {
					if (rTab.is_posible_value(i - 1, j - 1, a)) cout << a << " ";
				}
				cout << "}\n" << RESET;
			}
				ask(rTab);
				break;

		case 5:
			rTab.autofill();

			cout << ROSE << "Celdas con valor único completadas\n" << RESET;

			ask(rTab);
			break;

		case 6:

			cout << "Ya te rindes?(S/N)"; cin >> c;
			if (c == 'N') {
				cout << "Elige otra opcion entonces: ";
				ask(rTab);
			}
			else if (c == 'S') exit = true;	
			else {
				cout << "Si quieres salir pon S\n";
				ask(rTab);
			}
			break;

		case 7:
			resuelto = resolver_sudoku(rTab, 0, 0);
			if (resuelto) cout << ROSE << "Resolucion automatica del sudoku:\n" << RESET;
			else cout << RED << "No se ha podido resolver el sudoku\n" << RESET;

			ask(rTab);
			break;

		default:
			cout << "Elige una opcion correcta: ";
			break;
		}
		if (rTab.finish()){
			cout << YELLOW << "\n\nLO HAS LOGRADO!!!\nIntroduce una letra para salir:\n" << RESET;
			cin >> c; 
			exit = true;
		}
		cout << '\n';

	} while (!exit);

	return 0;
}
