#include "h/reglasSudoku.h"
#include "h/listaSudoku.h"
#include "h/mostrar.h"
#include <string>

// CONVENIO PARA EL PASO DE DATOS POR REFERENCIA:
// Al llamar a una función, se le pasa el valor del dato en el array.
// Por ejemplo, si queremos pasar la posición (1,2) del sudoku, se le pasará el valor 0 para la fila y el valor 1 para la columna.

string GAME_PATH = "./files/lista_partidas.txt", ORIGINAL_LIST_PATH = "./files/lista_sudokus.txt";


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


void download_paths(ifstream& arc, tListaSudoku& list) {
	int n; arc >> n; string b;
	ifstream aux; aux.close();
	for (int a = 0; a < n; a++) {
		tReglasSudoku rg;
		arc >> b;
		b = "./files/" + b;
		aux.open(b); 
		if (aux.is_open()) {
			rg.load_sudoku(aux);
			rg.set_path(b);
			list.insertar(rg);
		}
		else cout << "Fallo al cargar archivo\n" << b;
		aux.close();
		aux.clear();
	}
}

void download_sudoku(ifstream& arc, tReglasSudoku& rg) {

	ifstream aux; string p; tCelda celda; celda.set_taken();
	arc >> p;
	aux.open(p);
	if (aux.is_open()) {

		rg.load_sudoku(aux);
		rg.set_path(p);

		int a, b, c;
		arc >> a;
		while (a != -1) {

			arc >> b >> c;

			celda.set_value(c);
			rg.set_value(a, b, celda);

			arc >> a;
		}
	}
	else cout << "Fallo al cargar archivo\n";
	aux.close();
}

void download_lista(ifstream& arc, tListaSudoku& list) {
	int n; arc >> n;
	tReglasSudoku rg;
	for (int i = 0; i < n; i++) {
		download_sudoku(arc,rg);
		list.insertar(rg);
	}
}

void load_list(string PA, tListaSudoku& const ls) {
	ofstream arc; arc.open(PA, ios::trunc);
	int n = ls.dame_num_elems(), h;
	tReglasSudoku rg; tCelda celda;
	arc << n;
	for (int a = 0; a < n; a++) {
		rg = ls.dame_sudoku(a);
		arc << '\n' << rg.get_path() << '\n';
		h = rg.get_dimension();
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < h; j++) {
				celda = rg.get_celda(i, j);
				if (celda.is_taken()) {
					arc << i << ' ' << j << ' ' << celda.get_value() << '\n';
				}
			}
		}
		arc << -1;
	}
	arc.close();
}


void playing(tReglasSudoku& rTab) {
	int option, i, j, valor, num; char c;
	bool exit = false, resuelto = false;
	tCelda celda;

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

			if (rTab.get_celda(i - 1, j - 1).is_original()) {

				cout << RED << "Error, celda original\n" << RESET;
			}
			else if (rTab.get_celda(i - 1, j - 1).is_taken()) {

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

			cout << ROSE << "Celdas con valor unico completadas\n" << RESET;

			ask(rTab);
			break;

		case 6:

			cout << "Ya te rindes?(S/N)"; cin >> c;
			if (c == 'N') {
				cout << "Elige otra opcion entonces: "; cin >> c;
				ask(rTab);
			}
			else if (c == 'S') exit = true;
			else {
				cout << "Si quieres salir pon S\n"; cin >> c;
				ask(rTab);
			}
			break;

		case 7:
			resuelto = resolver_sudoku(rTab, 0, 0);
			if (resuelto) cout << ROSE << "Resolucion automatica del sudoku:\n" << RESET;
			else cout << RED << "No se ha podido resolver el sudoku\n" << RESET;

			ask(rTab);
			break;

		case 8:
			cout <<rTab.cuantas_celdas_pueden_tener(3);
			ask(rTab);
			break;

		default:
			cout << "Elige una opcion correcta: ";
			break;
		}
		if (rTab.finish()) {
			cout << YELLOW << "\n\nLO HAS LOGRADO!!!\nIntroduce una letra para salir:\n" << RESET;
			cin >> c;
			exit = true;
		}
		cout << '\n';

	} while (!exit);

}



int main() {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // memoria dinámica

	cout << GREEN << titulo << RESET << endl;
	
	ifstream arc;
	tListaSudoku games_list, original_list;
	arc.open(ORIGINAL_LIST_PATH);
	if (!arc.is_open()) {
		cout << RED << "Fallo de carga de archivo principal\n" << RESET;
		return -1;
	}
	download_paths(arc, original_list);
	arc.close();
	arc.open(GAME_PATH);
	if (!arc.is_open()) {
		cout << RED << "Fallo de carga de archivo principal\n" << RESET;
		return -1;
	}


	download_lista(arc, games_list);
	arc.close();
	
	int selection;
	tReglasSudoku rTab;

	cout << "Partida nueva (N), continuar partida (C) o abandonar la aplicacion (A)?\n";
	char salir; cin >> salir;

	while (salir != 'A') {

		if (salir == 'N') {
			original_list.mostrar_lista();
			cout << "Elige un sudoku:\n";
			while (!(cin >> selection) || 0 >= selection || selection > original_list.dame_num_elems()) {
				cin.clear();
				cin.ignore();
				cout << RED << "Seleccion incorrecta, elige otro sudoku:\n" << RESET;
			}
			rTab = original_list.dame_sudoku(selection - 1);
			playing(rTab);

			if (!rTab.finish()) {
				games_list.insertar(rTab);
			}
		}
		else if (salir == 'C') {

			if (games_list.dame_num_elems() > 0) {

				games_list.mostrar_lista();
				cout << "Elige un sudoku:\n";
				while (!(cin >> selection) || 0 >= selection || selection > games_list.dame_num_elems()) {
					cin.clear();
					cin.ignore();
					cout << RED << "Seleccion incorrecta, elige otro sudoku:\n" << RESET;
				}
				rTab = games_list.dame_sudoku(selection - 1);
				playing(rTab);

				if (!rTab.finish()) {
					games_list.eliminar(selection - 1);
					games_list.insertar(rTab);
				}
				else if (rTab.finish()) {
					games_list.eliminar(selection - 1);
				}
			}
			else cout << RED << "Lista de Sudokus vacia\n" << RESET;
		}
		else cout << RED << "Elige una opcion correcta\n" << RESET;

		cout << "Partida nueva (N), continuar partida (C) o abandonar la aplicacion (A)?\n";
		cin >> salir;
	}

	load_list(GAME_PATH, games_list);

	return 0;
}