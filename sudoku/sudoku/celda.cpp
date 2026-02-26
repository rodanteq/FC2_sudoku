#include "celda.h"



Celda::Celda(): value(0), status(EMPTY){}

bool Celda::is_empty() const {
	return status == EMPTY;
}
bool Celda::is_original() const {
	return status == ORIGINAL;
}
bool Celda::is_taken() const {
	return status == TAKEN;
}
int Celda::get_value() const {
	return value;
}

void Celda::set_value(int a) {
	value = a;
}
void Celda::set_taken() {
	status = TAKEN;
}
void Celda::set_original() {
	status = ORIGINAL;

}
void Celda::set_empty() {
	status = EMPTY;

}









/*
enum tEstado { ORIGINAL, OCUPADA, VACIA };

class Celda {
private:
	int value;
	tEstado status;
public:
	Celda();
	/* métodos de consulta 
	bool is_empty(); // devuelve true si y sólo si la celda es VACIA
	bool is_original(); // devuelve true si y sólo si la celda es ORIGINAL
	bool is_taken(); // devuelve true si y sólo si la celda es OCUPADA
	int get_value(); // devuelve el valor de la celda
	/* métodos modificadores
	void set_value(); // pone el valor v en la celda
	void set_taken(); // pone el estado de la celda a OCUPADA
	void set_original(); // pone el estado de la celda a ORIGINAL
	void set_empty(); // pone el estado de la celda a VACIA
};
*/