
#include "adt.h"

int main() {
    List L;
    Stack undoStack, redoStack;
    address cursor = nullptr;
    infotype word;

    createList(L);
    createStack(undoStack);
    createStack(redoStack);

    int choice;
    do {
        cout << "\n===== Menu Editor Teks =====" << endl;
        cout << "1. Masukkan Kata" << endl;
        cout << "2. Hapus Kata" << endl;
        cout << "3. Pindah Cursor ke Kiri" << endl;
        cout << "4. Pindah Cursor ke Kanan" << endl;
        cout << "5. Undo" << endl;
        cout << "6. Redo" << endl;
        cout << "7. Tampilkan Teks" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilih opsi: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Masukkan kata yang ingin dimasukkan: ";
                cin >> word;
                insertChar(L, cursor, word, undoStack, redoStack);
                break;

            case 2:
                if (cursor != nullptr) {
                    cout << "Kata \"" << cursor->info << "\" akan dihapus." << endl;
                    if (deleteChar(L, cursor, undoStack, redoStack)) {
                        cout << "Kata berhasil dihapus." << endl;
                    }
                } else {
                    cout << "Cursor tidak berada pada posisi yang valid. Tidak ada kata yang dihapus." << endl;
                }
                break;

            case 3:
                MoveLeft(L, cursor);
                if (cursor != nullptr) {
                    cout << "Cursor dipindahkan ke kiri ke kata: " << cursor->info << endl;
                } else {
                    cout << "Cursor sudah berada di awal teks." << endl;
                }
                break;

            case 4:
                MoveRight(L, cursor);
                if (cursor != nullptr) {
                    cout << "Cursor dipindahkan ke kanan ke kata: " << cursor->info << endl;
                } else {
                    cout << "Cursor sudah berada di akhir teks." << endl;
                }
                break;

            case 5:
                undo(L, cursor, undoStack, redoStack);
                break;

            case 6:
                redo(L, cursor, undoStack, redoStack);
                break;

            case 7:
                show(L, cursor);
                break;

            case 0:
                cout << "Keluar dari program. Sampai jumpa!" << endl;
                break;

            default:
                cout << "Opsi tidak valid. Silakan coba lagi." << endl;
                break;
        }
    } while (choice != 0);

    return 0;
}
