#include "main.h" // No borrar

bool dycOrdenado(int arr[], size_t i, size_t j)
{
    bool v1, v2, v3;
    size_t middle;

    if(i==j) return true; // do not compare same element
    if(i==j-1) // getting pair elements of arr
    {
        if(arr[i]>arr[j])
            return false;
        else return true;
    }
    else
    {
        middle = i+(j-i)/2;
        v1 = dycOrdenado(arr,i,middle);
        // when slicing we do not compare the middle and middle+1
        v2 = (arr[middle]>arr[middle+1])? false: true;
        // printf("arr[%zu]>arr[%zu]: %d > %d \n",middle,middle+1,arr[middle],arr[middle+1]);
        v3 = dycOrdenado(arr,middle+1,j);
    }
    
    return ( v1==false || v2==false || v3==false)? false: true;
    
}

bool arreglo_ordenado(int arr[], size_t n)
{

    // check base conditions
    if(arr==NULL) return true;
    if(n<=0) return true;

    return dycOrdenado(arr,0,n-1);
}
