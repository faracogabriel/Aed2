#include <iostream>
#include <cstdlib>
#define NIL -1

using namespace std;
typedef int Vertice;
enum Cor {branco, cinza, preto};

template<class T>
class No{

private:

    T item;
    No *prox;

public:

    No(){
        //this-prox=null
    }

    T getItem() {
        return this->item;
        //this-prox=null
    }

    void setItem(T item) {
        this->item = item;
    }

    No* getProx() {
        return this->prox;
    }

    void setProx(No* prox) {
        this->prox = prox;
    }

};


template <class T>
class Lista{

private:

    No<T> *prim, *ult;
    int tam;

public:

    Lista(){
        this->prim = new No<T>();
        this->prim->setProx(NULL);
        this->ult = this->prim;
        this->tam = 0;
    }

    //getprim e getult

    void insere(T item){
        No<T> *aux = new No<T>();
        this->ult->setProx(aux);
        this->ult = aux;
        this->ult->setProx(NULL);
        this->ult->setItem(item);
        this->tam++;
    }

    No<T>* pos(int n){
        int i = 0;
        for(No <T> *index = this->prim->getProx(); index != NULL; index = index->getProx()){
            if(i == n){
                return index;
            }i++;
        }
        return NULL;
    }

    int getTam(){
        return this->tam;
    }

    void removeUltimo(){
        No<T> *aux = new No<T>;
        aux=this->ult;
        for(No <T> *index = this->prim->getProx(); index != NULL; index = index->getProx()){
            if (index->getProx()==this->ult){
                this->ult = index;
                index->setProx(NULL);
            }
        }
        delete aux;
        this->tam--;
    }

    void mostraLista(){
        for(No <T> *index = this->prim->getProx(); index != NULL; index = index->getProx()){
            cout << index->getItem() << " ";
        }
    }
};


template <class T>
class Fila{

private:

    No<T> *frente, *tras;
    int tam;

public:

    Fila(){
        this->frente = new No<T>();
        this->frente->setProx(NULL);
        this->tras = this->frente;
        this->tam = 0;
    }

    void enfileira(T item){
        No<T> *aux = new No<T>();
        this->tras->setProx(aux);
        this->tras = aux;
        this->tras->setProx(NULL);
        this->tras->setItem(item);
        this->tam++;
    }

    int getTam(){
        return this->tam;
    }

    bool vazia(){
        if (this->tam==0){
            return true;
        }else{
            return false;
        }
    }

    T desenfileira(){
        No<T> *aux = new No<T>();
        aux = this->frente;
        this->frente = this->frente->getProx();
        delete aux;
        this->tam--;
        return this->frente->getItem();
    }
};


class Grafo{
private:

   
    Lista<Vertice> *adj;
    int  ordem, tamanho;

public:

    Grafo(int ordem){
        this->ordem = ordem;
        this->adj = new Lista<Vertice>[ordem+1];
 
        this->tamanho = 0;                  //VERIFICAR
  
    }

    
    void insereAresta(Vertice vert1, Vertice vert2){
        this->adj[vert1].insere(vert2);
        //this->adj[vert2].insere(vert1);
        this->tamanho++;
    }

    
    int particao(Lista<Vertice> &l, int p, int r){
        int x=l.pos(p)->getItem(), tmp=l.pos(r+1)->getItem();
        l.pos(r+1)->setItem(x);
        int i=p, j=r+1;
        while (true){
            do {
                i=i+1;
            } while (l.pos(i)->getItem()<x);
            
            do {
                j=j-1;
            } while (l.pos(j)->getItem()>x);
            
            if (i<j){
                int aux1=l.pos(i)->getItem();
                l.pos(i)->setItem(l.pos(j)->getItem());
                l.pos(j)->setItem(aux1);
            }
            else{
                int aux1=l.pos(p)->getItem();
                l.pos(p)->setItem(l.pos(j)->getItem());
                l.pos(j)->setItem(aux1);

                l.pos(r+1)->setItem(tmp);
                return j;
            }
        }
    }

    void quicksort(Lista<Vertice> &l, int p, int r){
        if (p<r){
            int q=particao(l,p,r);
            quicksort(l, p, q-1);
            quicksort(l, q+1, r);
        }
    }

    bool estaOrdenado(Lista<Vertice> &l){
        for (int i=1; i<l.getTam()-1;i++){
            if (l.pos(i)->getItem() > l.pos(i+1)->getItem()){
                return false;
            }
        }
        return true;
    }

    void ordenaListaAdj(){
        for(int i=1; i<=this->ordem; i++){
            if (!estaOrdenado(adj[i])){
                this->adj[i].insere(NIL);
                this->quicksort(this->adj[i], 0, this->adj[i].getTam()-2);
                this->adj[i].removeUltimo();
            }
        }
    }

    void colorir(){
        for(int v=1; v<=this->ordem; v++){
            this->cor[v] = branco;
        }
        
    }
    
    Lista<Vertice> runBFS(Vertice vertInicial, Vertice vertFinal){

        Fila<Vertice> fila;
        Vertice *predecessor = new Vertice[this->ordem+1];
        Lista<Vertice> menorCaminho;
        //adicionar distancia
        
        this->ordenaListaAdj();
        this->colorir();
        for(int v=1; v<=this->ordem; v++){
            predecessor[v] = NIL;
            //e setar distncia
        }
        this->cor[vertInicial] = cinza;
        //distancia origem é 0;
        predecessor[vertInicial] = NIL;
        fila.enfileira(vertInicial);

        while(!fila.vazia()){
            Vertice u  = fila.desenfileira();
            for (int i=0; i<this->adj[u].getTam();i++){
                Vertice v = this->adj[u].pos(i)->getItem();
                if (this->cor[v]==branco){
                    this->cor[v] = cinza;
                    //incrementa distancia
                    /// aux do menor caminho
                    predecessor[v] = u;
                    fila.enfileira(v);
                }
            }
            this->cor[u] = preto;
        }

        ///Menor caminho
        //---------melhor separar
        // falta verificar se é igual ao rei
        Vertice aux = vertFinal; /// declaracao subir
        while(aux != vertInicial){
            menorCaminho.insere(aux);
            aux = predecessor[aux];
        }
        menorCaminho.insere(vertInicial);
        return menorCaminho; //RunBFS já retorna o menor caminho
        ///----------
        //fazer um mostra bfs para teste
    }


    int getOrdem(){
        return this->ordem;
    }

    int getTamanho(){
        return this->tamanho;
    }
};
