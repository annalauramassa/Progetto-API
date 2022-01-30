#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define buffer_dim 10000000

typedef struct{
    unsigned int dist;
    int analizzato;
} Nodo;

typedef struct{
    unsigned int sum;
    int numeroGrafo;
}NodoK;

void showRanking(NodoK *rank);
void addGraph(NodoK *rank);
unsigned int parse();
void maxHeapify(NodoK *rank, int i);
void buildMaxHeap(NodoK *rank);

unsigned int d; //numero dei nodi
unsigned int k; //lunghezza classifica
unsigned int curr=0; //elementi inseriti in classifica
char buffer[buffer_dim]; //buffer di lettura
unsigned int letti=0; //caratteri letti dal buffer

int main(){
    if (fgets(buffer, buffer_dim, stdin)!=NULL){
        d=parse();
        k=parse();
        letti=0; //reimposto la lettura all'inizio del buffer;
    }
    NodoK rank[k];
   
    while (fgets(buffer,buffer_dim, stdin)!=NULL){  //finche ci sono ancora comandi leggi aggiungi grafo o topk e esegui
        switch (buffer[0]){
            case 'A':
            addGraph(rank);
            break;
            case 'T':
            showRanking(rank);
            break;
        } 
    }
}

void showRanking(NodoK *rank){
    unsigned int stop;
    unsigned int i;
    if (curr<k){
        stop=curr;
    }
    else{
        stop=k;
    }
    for (i=0; i<stop; i++){
        if(i!=stop-1){
            printf("%d ", rank[i].numeroGrafo);
        }
        else
        {
            printf("%d\n", rank[i].numeroGrafo);
        }
    }
    if (stop==0){
        printf("\n");    
    }
    return;
}

void addGraph(NodoK *rank){
    //lettura e parsing della matrice
    unsigned int matrix[d][d];
    unsigned int i=0;
    unsigned int j=0;
    for (i=0; i<d; i++){
        if (fgets(buffer, buffer_dim, stdin)!=NULL){ //leggo una riga
            for (j=0; j<d; j++){
                matrix[i][j]=parse();
            }
            letti=0; //resetto la lettura nel buffer
        }
    }

    //dijkstra              i->numero righe, j->numero colonne
    Nodo nodi[d];
    unsigned int sum=0;
    unsigned int vertDistMin=0;
    unsigned int vertTemp=0;
    int aggiornato=1;
    
    for (i=1; i<d; i++){
        nodi[i].dist=UINT_MAX;
        nodi[i].analizzato=0;
    }
  
    nodi[0].dist=0;
    nodi[0].analizzato=0;
   
    for (i=0; i<d; i++){
        vertDistMin=vertTemp;
        nodi[vertDistMin].analizzato=1;
        if (aggiornato==0){
            break;
        }
        sum=sum+nodi[vertDistMin].dist;
        unsigned int distMin=UINT_MAX;
        aggiornato=0;
        for (j=0; j<d; j++){
            unsigned int alt=UINT_MAX;
            if (nodi[j].analizzato!=1){
                if(matrix[vertDistMin][j]!=0){
                    alt=nodi[vertDistMin].dist+matrix[vertDistMin][j];
                    if (alt<nodi[j].dist){
                        nodi[j].dist=alt;
                    }
                }
                if(nodi[j].dist<distMin){
                    distMin=nodi[j].dist;
                    vertTemp=j;
                    aggiornato=1;
                }
            }
        }
    }

    //aggiungo alla classifica
    if (curr<k){
        rank[curr].sum=sum;
        rank[curr].numeroGrafo=curr;
    }
    else if (curr==k){
        buildMaxHeap(rank);
        if (sum<rank[0].sum){
            rank[0].sum=sum;
            rank[0].numeroGrafo=curr;
            maxHeapify(rank, 0);
        }
    }
    else{
        if (sum<rank[0].sum){
            rank[0].sum=sum;
            rank[0].numeroGrafo=curr;
            maxHeapify(rank, 0);
        }
    }
    curr++;
    return;
}

unsigned int parse(){
    unsigned int parsed=0;
    unsigned int i=0;
    for(i=0; (buffer+letti)[i]!=32 && (buffer+letti)[i]!=44 && (buffer+letti)[i]!=0 && (buffer+letti)[i]!=10 && (buffer+letti)[i]!=13; i++){ //diverso da space, comma, null, line feed
        parsed=parsed*10+(buffer+letti)[i]-'0';
    }
    i++;
    letti=letti+i;
    return parsed;
}

void buildMaxHeap(NodoK *rank){
    for(int i=(k-1)/2 ; i>=0; i--){
        maxHeapify(rank, i);
    }
}

void maxHeapify(NodoK *rank, int i){
    int l=(2*i)+1;
    int r=(2*i)+2;
    int max;
    if (l<k && rank[l].sum > rank[i].sum){
        max=l;
    }
    else{
        max=i;
    }
     if (r<k && rank[r].sum > rank[max].sum){
         max=r;
    }
    if (max != i){
        NodoK temp;
        temp=rank[i];
        rank[i]=rank[max];
        rank[max]=temp;
        maxHeapify(rank, max);
    }
}