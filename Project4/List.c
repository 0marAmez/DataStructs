/*********************************************************************************
* Omar Amezquita, ogamezqu
* 2022 Winter CSE101 PA4
* List.c
* List definitions
*********************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "List.h"

// structs --------------------------------------------------------------------

// private Node type
typedef struct NodeObj* Node;

// private NodeObj type
typedef struct NodeObj {
    void* data;
    Node next;
    Node prev;
} NodeObj;

// private ListObj type
typedef struct ListObj {
    Node front;
    Node back;
    Node cursorIndex;
    int length;
    int index;
} ListObj;


// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
Node newNode(void* data) {
    Node N = malloc(sizeof(NodeObj));
    N->data = data;
    N->next = NULL;
    N->prev = NULL;
    return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node* pN) { 
    if (pN != NULL && *pN != NULL) {
        // free((*pN)->data);
        free(*pN);
        *pN = NULL;
    }
}
// newList()
// Returns reference to new empty List object.
List newList() {
    List L;
    L = malloc(sizeof(ListObj));
    L->front = L->back = L->cursorIndex = NULL;
    L->length = 0;
    L->index = -1;
    return(L);
}

// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.
void freeList(List* pL) {
    if (pL != NULL && *pL != NULL) {
        while (!isEmpty(*pL)) {
            deleteFront(*pL);
        }
        free(*pL);
        *pL = NULL;
    }
}

// Access functions -----------------------------------------------------------
// length();
//Returns the number of elements in L
int length(List L) {
    if (L == NULL) {
        printf("List Error: calling length() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    return (L->length);
}

// index();
//Returns index of cursor element if defined, -1 otherwise
int index(List L) {
    if (L == NULL) {
        printf("List Error: calling index() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    return (L->index);
}
// front();
//Returns front element of L. Pre: length()>0
void* front(List L) {
    if (L == NULL) {
        printf("List Error: calling front() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (isEmpty(L)) {
        printf("List Error: calling Front on an empty List\n");
        exit(EXIT_FAILURE);
    }
    return(L->front->data);
}
// back()
// Returns back element of L. Pre: length()>0
void* back(List L) {
    if (L == NULL) {
        printf("List Error: calling back() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (isEmpty(L)) {
        printf("List Error: calling deleteBack() on an empty List\n");
        exit(EXIT_FAILURE);
    }

    return(L->back->data);
}
// get()
// Returns cursor element of L. Pre: length()>0, index()>=0
void* get(List L) {
    if (L == NULL) {
        printf("List Error: calling get() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if (isEmpty(L)) {
        printf("List Error: calling get() on an empty List\n");
        exit(EXIT_FAILURE);
    }
    if (L->index == -1) {
        printf("List Error: calling get() on a not defined cursor List\n");
        exit(EXIT_FAILURE);

    }
    return (L->cursorIndex->data);
}

// isEmpty()
// Returns true (1) if Q is empty, otherwise returns false (0)
bool isEmpty(List L) {
    if (L == NULL) {
        printf("List Error: calling isEmpty() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    return(L->length == 0);
}

//Manipulation procedures ------------------------------------

void clear(List L) {
    if (L == NULL) {
        printf("List Error: calling clear() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    while (length(L) != 0) {
        deleteFront(L);
    }
}


// set();
// Overwrites the cursor element�s data with x.Pre: length()>0, index()>=0
void set(List L, void* x) {
    if (L == NULL) {
        printf("List Error: calling get() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if (length(L) > 0 && index(L) >= 0) {
        L->cursorIndex->data = x;
    }

}
// moveFront()
// If L is non-empty, sets cursor under the front element, otherwise does nothing.
void moveFront(List L) {
    if (L == NULL) {
        printf("List Error: calling moveFront() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    else if(length(L)==0){
    L->cursorIndex = NULL;
    L->index = -1;
    }
    else{
    L->cursorIndex = L->front;
    L->index = 0;
    }

}
// moveBack()
// If L is non-empty, sets cursor under the back element, otherwise does nothing.
void moveBack(List L) {
    if (L == NULL) {
        printf("List Error: calling moveFront() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

      else if(length(L)==0){
        L->cursorIndex = NULL;
        L->index = -1;
    }
    else{
        L->cursorIndex = L->back;
        L->index = L->length - 1;
    }
 
}
// movePrev()
// If cursor is defined and not at front, move cursor one
// step toward the front of L; if cursor is defined and at
// front, cursor becomes undefined; if cursor is undefined
// do nothing
void movePrev(List L) {
    if (L == NULL) {
        printf("List Error: calling moveFront() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    else if (L->cursorIndex->prev == NULL) {
        L->cursorIndex = NULL;
        L->index = -1;
    }
    else {
        L->cursorIndex = L->cursorIndex->prev;
        L->index--;
    }
}

// If cursor is defined and not at back, move cursor one
// step toward the back of L; if cursor is defined and at
// back, cursor becomes undefined; if cursor is undefined
// do nothing
void moveNext(List L) {
    if (L == NULL) {
        printf("List Error: calling moveFront() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    else if (L->cursorIndex->next == NULL) {
        L->cursorIndex = NULL;
        L->index = -1;
    }

    else {
        L->cursorIndex = L->cursorIndex->next;
        L->index++;
    }
}

// prepend()
// Insert new element into L. If L is non-empty,
// insertion takes place before front element.
void prepend(List L, void* x) {
    Node N = newNode(x);
    // If L points to and address and the length is 0 then add node
    if (L == NULL) {
        printf("List Error: calling prepend() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length == 0) {
        L->back = L->front = N;
        L->length++;
    }
    else if (length(L) > 0 && index(L) >= 0) {
        L->front->prev = N;
        N->next = L->front;
        L->front = N;
        L->length++;
        L->index++;
    }
    else {
        //else increment the other node
        L->front->prev = N;
        N->next = L->front;
        L->front = N;
        L->length++;
    }

}

//Append()
// Insert new element into L. If L is non-empty,insertion takes place after back element.
void append(List L, void* x) {
    Node N = newNode(x);
    // If L points to and address and the length is 0 then add node
    if (L == NULL) {
        printf("List Error: calling append() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length == 0) {
        L->back = L->front = N;
        L->length++;
    }
    else {
        //else increment the other node
        L->back->next = N;
        N->prev = L->back;
        L->back = N;
        L->length++;
    }

}

//insertBefore()
// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, void* x) {
    Node N = newNode(x);
    Node temp = NULL;
    if (L == NULL) {
        printf("List Error: calling insertBefore() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    else if (length(L) == 0) {
        printf("List Error: calling insertBefore() on empty List reference\n");
        exit(EXIT_FAILURE);
    }
    else if (length(L) == 1 && index(L) >= 0) {
        // printf("length == 1");
        L->front->prev = N;
        N->next = L->front;
        L->front = N;
        L->length++;
        L->index++;
        // prepend(L,x);
    }
    else if (length(L) >= 1 && index(L) >= 0 && L->cursorIndex == L->front) {
        //  printf("cursor == front");
        L->cursorIndex->prev = N;
        N->next = L->cursorIndex;
        L->front = N;
        L->length++;
        L->index++;
        // prepend(L,x);

    }
    else if (length(L) >= 1 && index(L) >= 0 && L->cursorIndex == L->back) {
        //  printf("cursor == back");
        temp = L->cursorIndex->prev;
        temp->next = N;
        N->prev = temp;
        N->next = L->cursorIndex;
        L->cursorIndex->prev = N;
        L->length++;
        L->index++;
    }
    else {
        // printf("cursor == middle");
        temp = L->cursorIndex->prev;
        temp->next = N;
        N->prev = temp;
        N->next = L->cursorIndex;
        L->cursorIndex->prev = N;
        L->length++;
        L->index++;
    }
}

// insertAfter()
// Insert new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, void* x) {
    Node N = newNode(x);
    Node temp = NULL;
    if (L == NULL) {
        printf("List Error: calling insertAfter() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    else if (length(L) == 0) {
        printf("List Error: calling insertBefore() on empty List reference\n");
        exit(EXIT_FAILURE);
    }
    else if (length(L) == 1 && index(L) >= 0) {
        // printf("length == 1");
        L->back->next = N;
        N->prev = L->back;
        L->back = N;
        L->length++;
        // prepend(L,x);
    }
    else if (length(L) >= 1 && index(L) >= 0 && L->cursorIndex == L->front) {
        temp = L->cursorIndex->next;
        temp->prev = N;
        N->next = temp;
        N->prev = L->cursorIndex;
        L->cursorIndex->next = N;
        L->length++;
        // prepend(L,x);
    }
    else if (length(L) >= 1 && index(L) >= 0 && L->cursorIndex == L->back) {
        //  printf("cursor == back");
        L->cursorIndex->next = N;
        N->prev = L->cursorIndex;
        L->back = N;
        L->length++;
    }

    else {
        // printf("cursor == middle");
        temp = L->cursorIndex->next;
        temp->prev = N;
        N->next = temp;
        N->prev = L->cursorIndex;
        L->cursorIndex->next = N;
        L->length++;
    }



}

// deleteFront()
// Delete the front element. Pre: length()>0
void deleteFront(List L) {
    Node temp = NULL;
    if (L == NULL) {
        printf("List Error: calling deleteFront() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (isEmpty(L)) {
        printf("List Error: calling deleteFront on an empty List\n");
        exit(EXIT_FAILURE);
    }
    temp = L->front;
    if (length(L) > 1 && L->cursorIndex == L->front) {
        L->front = L->front->next;
        L->front->prev = NULL;
        L->cursorIndex = NULL;
        L->index = -1;
    }
    else if (length(L) > 1 && L->cursorIndex != L->front && index(L) == -1) {
        L->front = L->front->next;
        L->front->prev = NULL;
    }
    else if (length(L) > 1 && L->cursorIndex != L->front && index(L) >= 0) {
        L->front = L->front->next;
        L->front->prev = NULL;
        L->index--;
    }
    else {
        L->front = L->back = L->cursorIndex = NULL;
        L->index = -1;
    }
    L->length--;
    freeNode(&temp);
}


// deleteBaCK()
// Delete the back element. Pre: length()>0
void deleteBack(List L) {
    Node temp = NULL;
    if (L == NULL) {
        printf("List Error: calling deleteBack() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if (isEmpty(L)) {
        printf("List Error: calling deleteBack on an empty List\n");
        exit(EXIT_FAILURE);
    }
    temp = L->back;
    if (length(L) > 1 && L->cursorIndex == L->back) {
        L->back = L->back->prev;
        L->back->next = NULL;
        L->cursorIndex = NULL;
        L->index = -1;
    }
    else if (length(L) > 1 && L->cursorIndex != L->back) {
        L->back = L->back->prev;
        L->back->next = NULL;
    }
    else {
        L->front = L->back = L->cursorIndex = NULL;
        L->index = -1;
    }
    L->length--;
    freeNode(&temp);
}
// delete()
// Delete cursor element, making cursor undefined. Pre: length()>0, index()>=0
void delete(List L) {
    Node temp1 = NULL;
    // Node temp2 = NULL;


    if (L == NULL) {
        printf("List Error: calling delete() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if (isEmpty(L)) {
        printf("List Error: calling delete on an empty List\n");
        exit(EXIT_FAILURE);
    }

    if (index(L) == -1) {
        printf("List Error: calling delete on an undefined cursor List\n");
        exit(EXIT_FAILURE);
    }
    temp1 = L->cursorIndex;

    if (length(L) == 1) {
        // printf("FRONT");
        L->front = L->back = L->cursorIndex = NULL;
        freeNode(&temp1);
        L->index = -1;
        L->length--;
    }
    else if (L->cursorIndex == L->front) {
        // printf("FRONT1");
        L->front = L->front->next;
        freeNode(&temp1);
        L->front->prev = NULL;
        L->cursorIndex = NULL;
        L->index = -1;
        L->length--;
    }
    else if (L->cursorIndex == L->back) {
        L->back = L->back->prev;
        freeNode(&temp1);
        L->back->next = NULL;
        L->cursorIndex = NULL;
        L->index = -1;
        L->length--;
    }
    // CASE IF ONLY ONE
    else {
        //  printf("MIDLE");
        L->cursorIndex->prev->next = L->cursorIndex->next;
        L->cursorIndex->next->prev = L->cursorIndex->prev;
        freeNode(&temp1);
        L->cursorIndex = NULL;
        L->index = -1;
        L->length--;
    }
    //  L->length--;
    //  freeNode(&temp1);
}

