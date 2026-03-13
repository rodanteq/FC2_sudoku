#include "../h/celda.h"


tCelda::tCelda(): value(0), status(EMPTY){}

bool tCelda::is_empty() const {
	return status == EMPTY;
}
bool tCelda::is_original() const {
	return status == ORIGINAL;
}
bool tCelda::is_taken() const {

	return status == TAKEN;
}
int tCelda::get_value() const {
	return value;
}

void tCelda::set_value(int a) {
	value = a;
}
void tCelda::set_taken() {
	status = TAKEN;
}
void tCelda::set_original() {
	status = ORIGINAL;
}
void tCelda::set_empty() {
	status = EMPTY;
}