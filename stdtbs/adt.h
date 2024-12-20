// adt.h
#ifndef ADT_H_INCLUDED
#define ADT_H_INCLUDED

#include <iostream>
#include <string>
using namespace std;

typedef string infotype;
typedef struct elmlist *address;

// Struktur untuk Doubly Linked List
struct elmlist {
    infotype info;
    address next;
    address prev;
};

struct List {
    address first;
    address last;
};

// Struktur untuk Action (Undo/Redo)
struct Action {
    string type; // "insert" atau "delete"
    string word;
};

// Fungsi List
void createList(List &L);
address allocate(infotype data);
void insertNode(List &L, address &cursor, address P);
void deleteNode(List &L, address &cursor, address P);
address findNode(List L, infotype data);
void show(List L, address cursor);

// Fungsi Cursor
void MoveLeft(List L, address &cursor);
void MoveRight(List L, address &cursor);

// Struktur Stack
const int MAX_SIZE = 100; // Ukuran maksimal stack
struct Stack {
    Action elements[MAX_SIZE]; // Stack menyimpan Action
    int top;
};

// Fungsi Stack
void createStack(Stack &S);
bool isStackEmpty(Stack S);
bool isStackFull(Stack S);
void push(Stack &S, Action data);
bool pop(Stack &S, Action &data);

// Fungsi Insert dan Delete Char
void insertChar(List &L, address &cursor, infotype word, Stack &undoStack, Stack &redoStack);
bool deleteChar(List &L, address &cursor, Stack &undoStack, Stack &redoStack);

// Fungsi Undo dan Redo
void undo(List &L, address &cursor, Stack &undoStack, Stack &redoStack);
void redo(List &L, address &cursor, Stack &undoStack, Stack &redoStack);
void moveToWord(List &L, address &cursor, infotype targetWord);

#endif // ADT_H_INCLUDED
