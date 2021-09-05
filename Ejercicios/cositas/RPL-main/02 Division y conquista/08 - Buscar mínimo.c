#include "main.h" // No borrar

void min(int vector[],size_t i,size_t j, size_t *minPos)
{
    size_t middle, minPos1=0;

    *minPos=i;
    if(i==j) return;
    else if(i==j-1)
    {
        *minPos = (vector[i]<vector[j])?i:j;
        return;
    }
    else
    {
        // partimos a la mitad el vector
        middle= i + (j-i)/2;
        min(vector,0,middle,minPos);
        min(vector,middle+1,j,&minPos1);
        *minPos = ((vector[*minPos]<=vector[minPos1])?*minPos:minPos1);
    }

}

int buscar_minimo(int arr[], size_t n) {
    size_t minPos=0;

    // casos base
    if(n==0) return -1;
    if(n==1) return 1;

    min(arr,0,n-1,&minPos);
    return arr[minPos];
}
