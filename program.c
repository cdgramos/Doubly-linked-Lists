#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 100

typedef struct node{
  int number;
  char name[SIZE];
  struct node *nextNode;
  struct node *prevNode;
} Node;

Node* insertIntoList(Node *list, Node *newNode){
  Node *head = list;
  Node *assist;
  //if the list is empty
  if (list == NULL) return newNode;
  //if the first element is bigger than the one we will insert
  if (list->number > newNode->number){
    newNode->nextNode = list;
    list->prevNode = newNode;
    return newNode;
  }
  while (list != NULL){
    assist = list;
    list = list->nextNode;
    //insert node at the end
    if (assist->nextNode == NULL){
      assist->nextNode = newNode;
      newNode->prevNode = assist;
      return head; //return head
    }
    //insert node in the middle
    if (list->number >= newNode->number){
      assist->nextNode = newNode;
      newNode->nextNode = list;
      list->prevNode = newNode;
      newNode->prevNode = assist;
      return head;
    }
  }
  return head;
}

Node* removeFromList(int number, Node *list){
  Node *head = list;
  Node *assist,*auxiliar2;
  //empty list
  if (list == NULL) return list;
  //if the element to remove is the first one
  if (list->number == number){
    head = list->nextNode;
    free (list);
    //single element
    if (head == NULL) return head;
    head->prevNode = NULL;
    return head;
  }
  while (list != NULL){
    assist = list;
    list = list->nextNode;
    //remove last node
    if (assist->nextNode == NULL){
      auxiliar2 = assist->prevNode;
      auxiliar2->nextNode = NULL;
      free (assist);
      return head;
    }
    //remove node in the middle
    if (assist->number == number){
      auxiliar2 = assist->prevNode;
      auxiliar2->nextNode = assist->nextNode;
      list->prevNode = auxiliar2;
      free(assist);
      return head;
    }
  }
  return head;
}

Node* createNode(char *name, int number, Node *list){
  Node *newNode;
  newNode = malloc(sizeof(Node));
  newNode->nextNode = NULL;
  newNode->prevNode = NULL;
  newNode->number = number;
  strncpy(newNode->name,name,SIZE);
  list = insertIntoList(list, newNode);
  return list;
}

void printList(Node *list){
  Node *assist = NULL;
  if (list == NULL) {
    printf("The list is empty!\n");
    return;
  }
  printf("\nAscendant:\n");
  while (list != NULL){
    printf("%6d\t",list->number);
    puts(list->name);
    assist = list;
    list = list->nextNode;
  }
  list = assist;
  printf("\nDescendant:\n");
  while (list != NULL){
    printf("%6d\t%s\n",list->number, list->name);
    list = list->prevNode;
  }
}

int main(void){
  int menu = 1;
  int studentNumber;
  char name[SIZE];
  Node *list = NULL;
  Node *aux = NULL;

  while (menu != 0){
    printf("1 - Insert Student\n");
    printf("2 - Remove Student\n");
    printf("3 - Show student list\n");
    printf("4 - Exit\n");
    scanf("%d",&menu);

    switch(menu){
      case 1:
        printf("Name: ");
        scanf("\n");
        scanf("%99[^\n]",name);
        printf("Number: ");
        scanf("%d",&studentNumber);
        printf("\n");
        list = createNode(name, studentNumber,list);
      break;

      case 2:
        printf("Remove student with number: \n");
        scanf("%d",&studentNumber);
        list = removeFromList(studentNumber, list);
      break;

      case 3:
        printList(list);
      break;

      case 4:
        menu = 0;
      break;

      default:
      break;
    }
  }

  while (list != NULL){
    aux = list;
    list = list->nextNode;
    free(aux);
  }

  return 0;
}
