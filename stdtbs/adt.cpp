// adt.cpp
#include "adt.h"

// Membuat List kosong
void createList(List &L) {
    L.first = nullptr;
    L.last = nullptr;
}

// Mengalokasikan node baru
address allocate(infotype data) {
    address P = new elmlist;
    P->info = data;
    P->next = nullptr;
    P->prev = nullptr;
    return P;
}

// Menyisipkan node setelah cursor
void insertNode(List &L, address &cursor, address P) {
    if (L.first == nullptr) { // List kosong
        L.first = P;
        L.last = P;
    } else if (cursor == nullptr) { // Cursor belum valid, insert di awal
        P->next = L.first;
        L.first->prev = P;
        L.first = P;
    } else { // Insert setelah cursor
        P->next = cursor->next;
        P->prev = cursor;
        if (cursor->next != nullptr) {
            cursor->next->prev = P;
        } else { // Cursor di akhir list
            L.last = P;
        }
        cursor->next = P;
    }
    cursor = P; // Pindahkan cursor ke node yang baru
}

// Menghapus node yang berada di posisi P
void deleteNode(List &L, address &cursor, address P) {
    if (P != nullptr) {
        if (P == L.first && P == L.last) { // List hanya satu elemen
            L.first = nullptr;
            L.last = nullptr;
            cursor = nullptr;
        } else if (P == L.first) { // Hapus node pertama
            L.first = P->next;
            L.first->prev = nullptr;
            cursor = L.first;
        } else if (P == L.last) { // Hapus node terakhir
            L.last = P->prev;
            L.last->next = nullptr;
            cursor = P->prev; // Pindahkan cursor ke node sebelumnya
        } else { // Hapus node di tengah
            P->prev->next = P->next;
            P->next->prev = P->prev;
            cursor = P->prev; // Pindahkan cursor ke node sebelumnya
        }
        delete P;
    }
}

// Mencari node berdasarkan data
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

// Menampilkan isi List dan posisi cursor
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

// Memindahkan cursor ke kiri
void MoveLeft(List L, address &cursor) {
    if (cursor != nullptr && cursor->prev != nullptr) {
        cursor = cursor->prev;
    }
}

// Memindahkan cursor ke kanan
void MoveRight(List L, address &cursor) {
    if (cursor != nullptr && cursor->next != nullptr) {
        cursor = cursor->next;
    }
}

// Membuat Stack kosong
void createStack(Stack &S) {
    S.top = -1;
}

// Memeriksa apakah Stack kosong
bool isStackEmpty(Stack S) {
    return S.top == -1;
}

// Memeriksa apakah Stack penuh
bool isStackFull(Stack S) {
    return S.top == MAX_SIZE - 1;
}

// Push data ke Stack
void push(Stack &S, Action data) {
    if (!isStackFull(S)) {
        S.top++;
        S.elements[S.top] = data;
    }
}

// Pop data dari Stack
bool pop(Stack &S, Action &data) {
    if (!isStackEmpty(S)) {
        data = S.elements[S.top];
        S.top--;
        return true;
    }
    return false;
}

// Menambahkan karakter setelah cursor dan merekam aksi
void insertChar(List &L, address &cursor, infotype word, Stack &undoStack, Stack &redoStack) {
    address P = allocate(word);
    insertNode(L, cursor, P);

    // Mencatat aksi insert
    Action act;
    act.type = "insert";
    act.word = word;
    push(undoStack, act);

    // Bersihkan redoStack setelah aksi baru
    while (!isStackEmpty(redoStack)) {
        Action temp;
        pop(redoStack, temp);
    }
    cout << "Kata \"" << word << "\" berhasil dimasukkan setelah cursor." << endl;
}

// Menghapus karakter di posisi cursor dan merekam aksi
bool deleteChar(List &L, address &cursor, Stack &undoStack, Stack &redoStack) {
    if (cursor != nullptr) {
        infotype word = cursor->info;
        Action act;
        act.type = "delete";
        act.word = word;
        push(undoStack, act);

        deleteNode(L, cursor, cursor);

        // Bersihkan redoStack setelah aksi baru
        while (!isStackEmpty(redoStack)) {
            Action temp;
            pop(redoStack, temp);
        }
        return true;
    }
    return false;
}

// Menambahkan karakter tanpa merekam aksi (untuk undo/redo)
void insertCharWithoutRecord(List &L, address &cursor, infotype word) {
    address P = allocate(word);
    insertNode(L, cursor, P);
}

// Menghapus karakter tanpa merekam aksi (untuk undo/redo)
bool deleteCharWithoutRecord(List &L, address &cursor, infotype word) {
    address P = findNode(L, word);
    if (P != nullptr) {
        deleteNode(L, cursor, P);
        return true;
    }
    return false;
}

// Fungsi Undo
void undo(List &L, address &cursor, Stack &undoStack, Stack &redoStack) {
    if (!isStackEmpty(undoStack)) {
        Action act;
        pop(undoStack, act);

        if (act.type == "insert") {
            // Undo insert dengan menghapus kata
            address P = findNode(L, act.word);
            if (P != nullptr) {
                deleteCharWithoutRecord(L, cursor, act.word);

                // Mencatat aksi untuk redo
                Action redoAct;
                redoAct.type = "insert";
                redoAct.word = act.word;
                push(redoStack, redoAct);
            }
        } else if (act.type == "delete") {
            // Undo delete dengan menyisipkan kata kembali
            insertCharWithoutRecord(L, cursor, act.word);

            // Mencatat aksi untuk redo
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

// Fungsi Redo
void redo(List &L, address &cursor, Stack &undoStack, Stack &redoStack) {
    if (!isStackEmpty(redoStack)) {
        Action act;
        pop(redoStack, act);

        if (act.type == "insert") {
            // Redo insert dengan menyisipkan kata
            insertCharWithoutRecord(L, cursor, act.word);

            // Mencatat aksi untuk undo
            Action undoAct;
            undoAct.type = "insert";
            undoAct.word = act.word;
            push(undoStack, undoAct);
        } else if (act.type == "delete") {
            // Redo delete dengan menghapus kata
            deleteCharWithoutRecord(L, cursor, act.word);

            // Mencatat aksi untuk undo
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
