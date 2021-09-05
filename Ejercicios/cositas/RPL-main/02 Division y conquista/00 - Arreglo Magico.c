#include "main.h" // No borrar

bool magic(int arr[],size_t i,size_t j)
{
    // recursive function
    size_t mid;
    bool val1, val2;

    // base case
    if(i==j)
    {
        if(arr[i]==i)
            return true; // we are on the same element
        else 
            return false;

    }
    else
    {
        mid=i+(j-i)/2;
        val1 = magic(arr,0,mid);
        val2 = magic(arr,mid+1,j);
        
        if(val1||val2)
            return true;
    }
    
    return false;
}

bool arreglo_es_magico(int arr[], size_t n) {
    if(n==0) return false;
    if(n==1)
    {
        if(arr[0]==0) 
            return true;
        else 
            return false;
    }
      
    return magic(arr,0,n);
}
