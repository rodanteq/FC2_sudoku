#include "../h/mostrar.h"
using namespace std;

void barHorizontal(int j) {
	cout << "  ";
	for (int i = 0; i < j; i++)
		cout << char(CRUZ) << setw(j * ANCHO_CELDA) << setfill(char(BARRA_HORIZONTAL));
	cout << char(CRUZ) << '\n';
}


void mostrarTablero(tTablero& const tab) {
	int i, j;
	i = tab.get_dimension()+1;
	j = sqrt(i)+1;
	cout << "  ";
	for (int c = 1; c <= i; c++)
		cout << setw(MITAD_ANCHO) << setfill(' ') << ' ' << c << setw(MITAD_ANCHO) << setfill(' ') << ' ';
	cout << '\n';

	for (int a = 1; a <= i; a += j) {
		barHorizontal(j);
		for (int b = 1; b <= i; b += j) {
			cout << a * j + b << ' ';
			for (int c = 0; c < i; c += j){
				cout << char(BARRA_VERTICAL);
				for (int d = 0; d < i; d += j) {
					cout << setw(MITAD_ANCHO) << setfill(' ') << ' ';
					if (tab.get_value(a * j + b, c * j + d).is_empty())
						cout << char(BLANCO);
					else cout << tab.get_value(a * j + b, c * j + d).get_value();
					cout << setw(MITAD_ANCHO) << setfill(' ') << ' ';
				}
				cout << char(BARRA_VERTICAL);
			}
			cout << char(BARRA_VERTICAL) << '\n';
			cout << char(BARRA_VERTICAL);
		}
	}





	cout << "hola";
}