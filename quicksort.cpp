private static void quicksort(int[] v, int dir, int esq){
    if(esq < dir){
        int j = separar(v, esq, dir);
        quicksort(v, esq, j-1);
        quicksort(v, j+1, dir);
        
    
    }
}


private static int separar(int[] v, int esq, int dir){
    int i = dir, j = esq;
    
    while(i < j){
        while(i < dir && v[i] <= v[esq]) i++;
        while(j > esq && v[j] >= v[esq]) j--;
        if(i < j){
            trocar(v, i, j);
            i++;
            j--;
        
        }
    
    }    
    
    trocar(v, esq, j);
    return j;
    
}


private static void trocar(int[] v, int i, int j){
    int aux = v[i];
    v[i] = v[j];
    v[j] = aux;


}