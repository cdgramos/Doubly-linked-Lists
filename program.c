#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TAM 100

typedef struct no{
  int numero;
  char nome[TAM];
  struct no *nseg;
  struct no *nant;
} No;

No* insereNaLista(No *lista, No *novoNo){
  No *cabeca = lista;
  No *auxiliar;
  //caso a lista esteja vazia ainda
  if (lista == NULL) return novoNo;
  //caso o primeiro elemento seja maior 
  //que o que vamos inserir
  if (lista->numero > novoNo->numero){
    novoNo->nseg = lista;
    lista->nant = novoNo;
    return novoNo;
  }
  while (lista != NULL){
    auxiliar = lista;
    lista = lista->nseg;
    //inserir no fim da lista
    if (auxiliar->nseg == NULL){
      auxiliar->nseg = novoNo;
      novoNo->nant = auxiliar;
      return cabeca; //retorna a cabeça
    }
    //inserir no meio da lista
    if (lista->numero >= novoNo->numero){
      auxiliar->nseg = novoNo;
      novoNo->nseg = lista;
      lista->nant = novoNo;
      novoNo->nant = auxiliar;
      return cabeca;
    }
  }
  return cabeca;
}

No* removeDaLista(int numero, No *lista){
  No *cabeca = lista;
  No *auxiliar,*auxiliar2;
  //lista vazia
  if (lista == NULL) return lista;
  //caso seja o primeiro a remover
  if (lista->numero == numero){
    cabeca = lista->nseg;
    free (lista);
    //unico elemento
    if (cabeca == NULL) return cabeca;
    cabeca->nant = NULL;
    return cabeca;
  }
  while (lista != NULL){
    auxiliar = lista;
    lista = lista->nseg;
    //remove o ultimo elemento
    if (auxiliar->nseg == NULL){
      auxiliar2 = auxiliar->nant;
      auxiliar2->nseg = NULL;
      free (auxiliar);
      return cabeca; 
    }
    //remove no meio da lista
    if (auxiliar->numero == numero){
      auxiliar2 = auxiliar->nant;
      auxiliar2->nseg = auxiliar->nseg;
      lista->nant = auxiliar2;
      free(auxiliar);
      return cabeca;
    }
  }
  return cabeca;
}

No* criaNo(char *nome, int numero, No *lista){
  No *novoNo;
  novoNo = malloc(sizeof(No));
  novoNo->nseg = NULL;
  novoNo->nant = NULL;
  novoNo->numero = numero;
  strncpy(novoNo->nome,nome,TAM);
  lista = insereNaLista(lista, novoNo);
  return lista;
}

void imprimeLista(No *lista){
  No *auxiliar = NULL;
  if (lista == NULL) {
    printf("A lista esta vazia!\n");
    return;
  }
  printf("\nAscendente:\n");
  while (lista != NULL){
    printf("%6d\t",lista->numero);
    puts(lista->nome);
    auxiliar = lista;
    lista = lista->nseg;
  }
  lista = auxiliar;
  printf("\nDescendente:\n");
  while (lista != NULL){
    printf("%6d\t%s\n",lista->numero, lista->nome);
    lista = lista->nant;
  }
}

int main(void){
  int menu = 1;
  int numeroAluno;
  char nome[TAM];
  No *lista = NULL;
  No *aux = NULL;

  while (menu != 0){
    printf("1 - Inserir Aluno\n");
    printf("2 - Remover Aluno\n");
    printf("3 - Mostrar Lista Dos Alunos\n");
    printf("4 - Sair\n");
    scanf("%d",&menu);

    switch(menu){
      case 1:
        printf("Nome: ");
        scanf("\n");
        scanf("%99[^\n]",nome);
        printf("Numero: ");
        scanf("%d",&numeroAluno);
        printf("\n");
        lista = criaNo(nome, numeroAluno,lista);
      break;

      case 2:
        printf("Numero do aluno a remover: \n");
        scanf("%d",&numeroAluno);
        lista = removeDaLista(numeroAluno, lista);
      break;

      case 3:
        imprimeLista(lista);
      break;

      case 4:
        menu = 0;
      break;

      default:
      break;
    }
  }

  while (lista != NULL){
    aux = lista;
    lista = lista->nseg;
    free(aux);
  }

  return 0;
}