#include <time.h>
#include <stdio.h>
#include <stdlib.h>


int MAX(int a, int b) {
    return a > b ? a : b;
}

typedef struct noBst {
    int chave;
    struct noBst * esq;
    struct noBst * dir;
} BST;

BST * bstNovoNo(int chaveParaCriacao) {
    BST * no = malloc(sizeof(struct noBst));
    no->chave = chaveParaCriacao;
    no->esq = NULL;
    no->dir = NULL;
    return no;
}

BST * bstInsert(BST * raiz, int chaveParaInsercao) {
    if (raiz == NULL) {
        return bstNovoNo(chaveParaInsercao);
    }

    if (chaveParaInsercao > raiz->chave) {
        raiz->dir = bstInsert(raiz->dir, chaveParaInsercao);
    }
    else {
        raiz->esq = bstInsert(raiz->esq, chaveParaInsercao);
    }

    return raiz;
}

int bstCalculaAltura(BST * raiz) {
  if (raiz == NULL)
    return 0;
  
  int alturaEsq = bstCalculaAltura(raiz->esq);
  int alturaDir = bstCalculaAltura(raiz->dir);
  return MAX(alturaEsq, alturaDir) + 1;
}

void bstFree(BST * raiz) {
  if (raiz == NULL) return;

  if (raiz->esq != NULL)
    bstFree(raiz->esq);
  if (raiz->dir != NULL)
    bstFree(raiz->dir);
  
  free(raiz);
}

typedef struct noAvl {
    int chave;
    int altura;
    struct noAvl * esq;
    struct noAvl * dir;
} AVL;

AVL * avlNovoNo(int chaveParaCriacao) {
    AVL * no = malloc(sizeof(struct noAvl));
    no->chave = chaveParaCriacao;
    no->altura = 1;
    no->esq = NULL;
    no->dir = NULL;
    return no;
}
int avlGetAltura(AVL * raiz) {
  if (raiz == NULL) return 0;
  return raiz->altura;
}
int avlCalculaAltura(AVL * raiz) {
  if (raiz == NULL)
    return 0;

  int alturaEsq = avlCalculaAltura(raiz->esq);
  int alturaDir = avlCalculaAltura(raiz->dir);
  return MAX(alturaEsq, alturaDir) + 1;
}
int avlCalculaFb(AVL * no) {
  return avlGetAltura(no->esq) - avlGetAltura(no->dir);
}
AVL * avlRotL(AVL * raiz) {
  if (raiz == NULL) return raiz;
  
  AVL * novaRaiz = raiz->dir;
  raiz->dir = novaRaiz->esq;
  novaRaiz->esq = raiz;

  raiz->altura = avlCalculaAltura(raiz);
  novaRaiz->altura = avlCalculaAltura(novaRaiz);

  return novaRaiz;
}
AVL * avlRotR(AVL * raiz) {
  if (raiz == NULL) return raiz;
  
  AVL * novaRaiz = raiz->esq;
  raiz->esq = novaRaiz->dir;
  novaRaiz->dir = raiz;

  raiz->altura = avlCalculaAltura(raiz);
  novaRaiz->altura = avlCalculaAltura(novaRaiz);

  return novaRaiz;
}


AVL * avlInsert(AVL * raiz, int chave) {
  if (raiz == NULL)
    return avlNovoNo(chave);
  
  if (chave > raiz->chave)
    raiz->dir = avlInsert(raiz->dir, chave);
  else
    raiz->esq = avlInsert(raiz->esq, chave);

  raiz->altura = avlCalculaAltura(raiz);
  int fb = avlCalculaFb(raiz);
  if (fb == +2) {
    if (avlCalculaFb(raiz->esq) < 0) {
      raiz->esq = avlRotL(raiz->esq);
    }
    raiz = avlRotR(raiz);
  }
  else if (fb == -2) {
    if (avlCalculaFb(raiz->dir) > 0) {
      raiz->dir = avlRotR(raiz->dir);
    }
    raiz = avlRotL(raiz);
  }
  
  return raiz;
}

void avlFree(AVL * raiz) {
  if (raiz == NULL) return;

  if (raiz->esq != NULL)
    avlFree(raiz->esq);
  if (raiz->dir != NULL)
    avlFree(raiz->dir);
  
  free(raiz);
}
int* geraNumerosAleatorios(int N) {
  int* numerosAleatorios = malloc(sizeof(int) * N); 
  srand(time(NULL));
  
  for (int i = 0; i < N; i++) {
    numerosAleatorios[i] = (rand() % (N * 1000)) + 1;
  }
  return numerosAleatorios;
}

void print(char * msg) {
    printf("%s", msg);
    printf("\n");
}

void gerarArvores(int A, int N){    
  int* altBST = malloc(sizeof(int) * A);
  int* altAVL = malloc(sizeof(int) * A);
  
  float mediadaBST = 0;
  float mediadaAVL = 0;
  float totaldaBST = 0;
  float totaldaAVL = 0;
  float mediaGeral = 0;
   
   for (int i = 0; i < A; i++) {
      int * numerosAleatorios = geraNumerosAleatorios(N);
      BST * rBst = malloc(sizeof(BST));
      AVL * rAvl = malloc(sizeof(AVL));
     
        for (int k = 0; k < N; k++) { 
            rBst = bstInsert(rBst, numerosAleatorios[k]);
            rAvl = avlInsert(rAvl, numerosAleatorios[k]);
        }

      altAVL[i] = bstCalculaAltura(rAvl);
      altBST[i] = avlCalculaAltura(rBst);
      }
   
  for(int i = 0; i < A; i++){
        totaldaAVL += altAVL[i];
        totaldaBST += altBST[i];        
    }
   
  mediadaAVL = totaldaAVL/A;
  mediadaBST = totaldaBST/A;
  mediaGeral = (mediadaAVL + mediadaBST)/2*A;

    printf("\n Experimento com A = %d e N = %d\n", A, N);

    printf("----------------------------\n");

    printf("Altura média geral: %f\n", mediaGeral);
  
    printf("----------------------------\n");

    printf("Altura média da BST: %f\n", mediadaBST);
    
    printf("----------------------------\n");

    printf("Altura média da AVL: %f\n", mediadaAVL);
    
    printf("----------------------------\n");

  }

  int main(void) {
  srand(time(NULL));
  int opcao, Amostra, Elemento; 
  do{
      printf("Menu: 1) nova simulação ou 0) sair\n");
      scanf("%d", &opcao);
  
    switch(opcao){
      case 0: 
      printf("\n Tchau");
      break;
      
      case 1: 
        printf(" Digite a quantidade de amostras: ");
        scanf("%d", &Amostra);
        printf(" Digite a quantidade de elementos para cada amostra: ");
        scanf("%d", &Elemento);
        gerarArvores(Amostra, Elemento);
        break; 
      
      default:
        printf(" Opção Inválida!");
    }
  } while(opcao != 0); 
  return 0;
}


