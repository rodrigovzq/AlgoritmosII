#include "tp0.h"

/* *****************************************************************
 *                     FUNCIONES A COMPLETAR                       *
 *         (ver en tp0.h la documentación de cada función)         *
 * *****************************************************************/

void swap(int *x, int *y) {
    int aux = *x;
    *x = *y;
    *y = aux;
    
    return ;

}


int maximo(int vector[], int n) {

    if (n == 0) return -1;
	//if (n==1) return vector[0];
    int max = 0;
    
    for(int i=1;i<n;i++){
        if (vector[max] < vector[i]) max = i;
    }
    return max;
    
}


int comparar(int vector1[], int n1, int vector2[], int n2) {
    int *l, *h, j=0;
    int same = 0;
    if (n1<n2){    /*Evaluo en caso de que uno sea mas corto*/
        j = n1;   
    }else{
        j = n2;
    }
    for (int i=0;i<j;i++){    /*evaluo si son iguales eae hasta el mas corto*/
        if(vector1[i]<vector2[i]){
            l = vector1;
            h = vector2;
            same = -1;
            break;
        }else if(vector1[i]>vector2[i]){
            h = vector1;
            l = vector2;
            same = 1;
            break;
        }
    }
    if (same==0 && n1<n2 ) same = -1;
    if (same==0 && n1>n2) same = 1;
  
    return same;
}


void seleccion(int vector[], int n) {
    
    for(int i=0;i<n;i++){
    
        int s = vector[i];
        for (int j=i+1; j<n;j++){
        
            if(vector[j]<s){
            
                swap(&vector[i],&vector[j]);
            }
        }
    
    }
}
