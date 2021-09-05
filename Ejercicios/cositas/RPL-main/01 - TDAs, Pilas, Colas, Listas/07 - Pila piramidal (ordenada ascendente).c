#include "main.h" // No borrar

bool pila_es_piramidal(pila_t* pila) {
	if (pila_esta_vacia(pila)) return true;
	pila_t *auxiliar = pila_crear();
	int *elemento = pila_desapilar(pila);
	while (!pila_esta_vacia(pila)){
		int *tope = pila_ver_tope(pila);
		if (*elemento >= *tope) return false;
		*elemento = pila_desapilar(pila);
	}
    while (!pila_esta_vacia(auxiliar)){
		pila_apilar(pila, pila_desapilar(auxiliar));
	}
	return true;
}
