#include "tp0.h"

/* *****************************************************************
 *                     FUNCIONES A COMPLETAR                       *
 *         (ver en tp0.h la documentación de cada función)         *
 * *****************************************************************/

void swap(int *x, int *y) {
    
    int aux = *x;
    *x = *y;
    *y = aux;

}


int maximo(int vector[], int n) {

    if (n == 0) return -1;
    int max = 0;
    
    for(int i=1;i<n;i++){
        if (vector[max] < vector[i]) max = i;
    }
    return max;
    
}


int comparar(int vector1[], int n1, int vector2[], int n2) {
    int j=0;
    if (n1<n2){    /*Evaluo en caso de que uno sea mas corto*/
        j = n1;   
    }else{
        j = n2;
    }
    for (int i=0;i<j;i++){    /*evaluo si son iguales e2e hasta el mas corto*/
        if(vector1[i]<vector2[i]){
            return -1;
            break;
        }else if(vector1[i]>vector2[i]){
            return  1;
            break;
        }
    }
    if (n1<n2 ) return -1;
    if (n1>n2) return 1;
  
    return 0;
}


void seleccion(int vector[], int n) {
    if(n==1) return;
    int max=maximo(vector,n--);
    while(max!=-1){
        swap(&vector[max],&vector[n]);
        max=maximo(vector,n--);
    }
}
