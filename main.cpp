#include <iostream>
#include <string>
#include <fstream>
#include "catatan.h"
#include "menu.h"
using namespace std;

//kamus
int pilihan;
Catatan catatan;

int main()
{
    do
    {

        tampilMenu();

        cout << "Masukkan pilihan (1-6): ";
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
            system("cls");
            cout << "=======================================" << endl;
            cout << "           Tambah Catatan Baru        " << endl;
            cout << "=======================================" << endl;
            catatan.tambahCatatan();
            break;
        case 2:
            system("cls");
            cout << "=======================================" << endl;
            cout << "           Lihat Daftar Catatan       " << endl;
            cout << "=======================================" << endl;
            catatan.lihatCatatan();
            break;
        case 3:
            system("cls");
            cout << "=======================================" << endl;
            cout << "              Edit Catatan            " << endl;
            cout << "=======================================" << endl;
            catatan.editCatatan();
            break;
        case 4:
            system("cls");
            cout << "=======================================" << endl;
            cout << "              Hapus Catatan            " << endl;
            cout << "=======================================" << endl;
            catatan.hapusCatatan();
            break;
        case 5:
            break;
        default:
            cout << "Pilihan tidak valid. Silakan coba lagi.\n";
        }

        cout << endl;
        cout << "Tekan enter untuk melanjutkan...";
        cin.ignore();
        cin.get();
        system("cls");

    }
    while (pilihan != 5);

    return 0;
}

