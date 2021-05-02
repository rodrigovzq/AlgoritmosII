#include "pila.h"
/*******************************************************************
 *               		     TP Pila                               *
 *		 Facultad de Ingenieria de la Universidad de Buenos Aires  *
 *												Vazquez, Rodrigo   *
 ******************************************************************/

#include <stdlib.h>
#define STACK_INIT_SIZE 20
#define STACK_RESIZE_FACTOR 2

/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void **datos;
    size_t cantidad;   // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/
bool pila_redimensionar(pila_t *pila,bool up);

pila_t * pila_crear(void){

    pila_t * pila = malloc(sizeof(pila_t));
    if(!pila) return NULL;
    
    pila->datos = malloc(STACK_INIT_SIZE*sizeof(void*));
    if(!pila->datos){
        free(pila);
        return NULL;
    }
    pila->capacidad=STACK_INIT_SIZE;
    pila->cantidad = 0;
    return pila;

}


void pila_destruir(pila_t *pila){
    free(pila->datos);
    pila->datos=NULL;
    free(pila);
}


bool pila_esta_vacia(const pila_t *pila){
    return !(pila->cantidad);
}


bool pila_apilar(pila_t *pila, void *valor){

    if(pila->cantidad == pila->capacidad){
        if(pila_redimensionar(pila, true)==false) return false;
    }
    pila->datos[pila->cantidad++]=valor;
    return true;
}


void * pila_ver_tope(const pila_t *pila){

    return (!pila_esta_vacia(pila))?pila->datos[pila->cantidad-1]:NULL;
}


void *pila_desapilar(pila_t *pila){
    
    if(pila_esta_vacia(pila)) return NULL;

    size_t lower_bound = pila->capacidad/(STACK_RESIZE_FACTOR*STACK_RESIZE_FACTOR);
    if(pila->cantidad < lower_bound){
        pila_redimensionar(pila, false);
    }

    return pila->datos[-- pila->cantidad]; 
}


bool pila_redimensionar(pila_t *pila,bool up){
    size_t capacidad_nuevo; 
    if (up == true){
        capacidad_nuevo = pila->capacidad*STACK_RESIZE_FACTOR;
    }else{
        capacidad_nuevo = pila->capacidad/STACK_RESIZE_FACTOR;
    }
    void * * datos_nuevo=realloc(pila->datos,sizeof(void*)*capacidad_nuevo);
    if(!datos_nuevo) return false;
    pila->datos=datos_nuevo;
    pila->capacidad=capacidad_nuevo;
    return true;
}
