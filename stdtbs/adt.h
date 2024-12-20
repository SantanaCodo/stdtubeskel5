// adt.h
#ifndef ADT_H_INCLUDED
#define ADT_H_INCLUDED

#include <iostream>
#include <string>
using namespace std;

typedef string infotype;
typedef struct elmlist *address;

struct elmlist {
    infotype info;
    address next;
    address prev;
};

struct List {
    address first;
    address last;
};

struct Action {
    string type; 
    string word;
};


void createList(List &L);
address allocate(infotype data);
void insertNode(List &L, address &cursor, address P);
void deleteNode(List &L, address &cursor, address P);
address findNode(List L, infotype data);
void show(List L, address cursor);


void MoveLeft(List L, address &cursor);
void MoveRight(List L, address &cursor);


const int MAX_SIZE = 100; // Ukuran maksimal stack
struct Stack {
    Action elements[MAX_SIZE]; // Stack menyimpan Action
    int top;
};


void createStack(Stack &S);
bool isStackEmpty(Stack S);
bool isStackFull(Stack S);
void push(Stack &S, Action data);
bool pop(Stack &S, Action &data);


void insertChar(List &L, address &cursor, infotype word, Stack &undoStack, Stack &redoStack);
bool deleteChar(List &L, address &cursor, Stack &undoStack, Stack &redoStack);


void undo(List &L, address &cursor, Stack &undoStack, Stack &redoStack);
void redo(List &L, address &cursor, Stack &undoStack, Stack &redoStack);
void moveToWord(List &L, address &cursor, infotype targetWord);

#endif // ADT_H_INCLUDED
