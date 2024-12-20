#include "adt.h"

void createList(List &L) {
    L.first = nullptr;
    L.last = nullptr;
}


address allocate(infotype data) {
    address P = new elmlist;
    P->info = data;
    P->next = nullptr;
    P->prev = nullptr;
    return P;
}


void insertNode(List &L, address &cursor, address P) {
    if (L.first == nullptr) { 
        L.first = P;
        L.last = P;
    } else if (cursor == nullptr) { 
        P->next = L.first;
        L.first->prev = P;
        L.first = P;
    } else { 
        P->next = cursor->next;
        P->prev = cursor;
        if (cursor->next != nullptr) {
            cursor->next->prev = P;
        } else { 
            L.last = P;
        }
        cursor->next = P;
    }
    cursor = P; 
}

// Menghapus node yang berada di posisi P
void deleteNode(List &L, address &cursor, address P) {
    if (P != nullptr) {
        if (P == L.first && P == L.last) { 
            L.first = nullptr;
            L.last = nullptr;
            cursor = nullptr;
        } else if (P == L.first) { 
            L.first = P->next;
            L.first->prev = nullptr;
            cursor = L.first;
        } else if (P == L.last) { 
            L.last = P->prev;
            L.last->next = nullptr;
            cursor = P->prev; 
        } else { 
            P->prev->next = P->next;
            P->next->prev = P->prev;
            cursor = P->prev; 
        }
        delete P;
    }
}


address findNode(List L, infotype data) {
    address P = L.first;
    while (P != nullptr) {
        if (P->info == data) {
            return P;
        }
        P = P->next;
    }
    return nullptr;
}

void show(List L, address cursor) {
    address P = L.first;
    cout << "Isi teks: ";
    while (P != nullptr) {
        if (P == cursor) {
            cout << "[" << P->info << "] ";
        } else {
            cout << P->info << " ";
        }
        P = P->next;
    }
    cout << endl;
}

void MoveLeft(List L, address &cursor) {
    if (cursor != nullptr && cursor->prev != nullptr) {
        cursor = cursor->prev;
    }
}

void MoveRight(List L, address &cursor) {
    if (cursor != nullptr && cursor->next != nullptr) {
        cursor = cursor->next;
    }
}

void createStack(Stack &S) {
    S.top = -1;
}

bool isStackEmpty(Stack S) {
    return S.top == -1;
}

bool isStackFull(Stack S) {
    return S.top == MAX_SIZE - 1;
}

void push(Stack &S, Action data) {
    if (!isStackFull(S)) {
        S.top++;
        S.elements[S.top] = data;
    }
}

bool pop(Stack &S, Action &data) {
    if (!isStackEmpty(S)) {
        data = S.elements[S.top];
        S.top--;
        return true;
    }
    return false;
}

void insertChar(List &L, address &cursor, infotype word, Stack &undoStack, Stack &redoStack) {
    address P = allocate(word);
    insertNode(L, cursor, P);

    Action act;
    act.type = "insert";
    act.word = word;
    push(undoStack, act);

    while (!isStackEmpty(redoStack)) {
        Action temp;
        pop(redoStack, temp);
    }
    cout << "Kata \"" << word << "\" berhasil dimasukkan setelah cursor." << endl;
}

bool deleteChar(List &L, address &cursor, Stack &undoStack, Stack &redoStack) {
    if (cursor != nullptr) {
        infotype word = cursor->info;
        Action act;
        act.type = "delete";
        act.word = word;
        push(undoStack, act);

        deleteNode(L, cursor, cursor);

        while (!isStackEmpty(redoStack)) {
            Action temp;
            pop(redoStack, temp);
        }
        return true;
    }
    return false;
}

void insertCharWithoutRecord(List &L, address &cursor, infotype word) {
    address P = allocate(word);
    insertNode(L, cursor, P);
}

bool deleteCharWithoutRecord(List &L, address &cursor, infotype word) {
    address P = findNode(L, word);
    if (P != nullptr) {
        deleteNode(L, cursor, P);
        return true;
    }
    return false;
}

void undo(List &L, address &cursor, Stack &undoStack, Stack &redoStack) {
    if (!isStackEmpty(undoStack)) {
        Action act;
        pop(undoStack, act);

        if (act.type == "insert") {
            address P = findNode(L, act.word);
            if (P != nullptr) {
                deleteCharWithoutRecord(L, cursor, act.word);

                Action redoAct;
                redoAct.type = "insert";
                redoAct.word = act.word;
                push(redoStack, redoAct);
            }
        } else if (act.type == "delete") {
            insertCharWithoutRecord(L, cursor, act.word);

            Action redoAct;
            redoAct.type = "delete";
            redoAct.word = act.word;
            push(redoStack, redoAct);
        }
        cout << "Undo berhasil dilakukan." << endl;
    } else {
        cout << "Undo tidak tersedia." << endl;
    }
}

void redo(List &L, address &cursor, Stack &undoStack, Stack &redoStack) {
    if (!isStackEmpty(redoStack)) {
        Action act;
        pop(redoStack, act);

        if (act.type == "insert") {
            insertCharWithoutRecord(L, cursor, act.word);

            Action undoAct;
            undoAct.type = "insert";
            undoAct.word = act.word;
            push(undoStack, undoAct);
        } else if (act.type == "delete") {
            deleteCharWithoutRecord(L, cursor, act.word);

            Action undoAct;
            undoAct.type = "delete";
            undoAct.word = act.word;
            push(undoStack, undoAct);
        }
        cout << "Redo berhasil dilakukan." << endl;
    } else {
        cout << "Redo tidak tersedia." << endl;
    }
}
