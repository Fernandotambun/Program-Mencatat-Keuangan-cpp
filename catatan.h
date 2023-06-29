#ifndef TABUNGAN_H
#define TABUNGAN_H
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
const string FILENAME = "catatan.txt";
// Class untuk menyimpan data tabungan
class Catatan
{
public:
    // Atribut utama
    string tanggal;
    string asal_pemasukan;
    int nominal_pemasukan;
    string asal_pengeluaran;
    int nominal_pengeluaran;
    int total;
    //atribut sementara
    int nomor;
    int nomor_awal;
    void hitungTotal()
    {
        total = nominal_pemasukan - nominal_pengeluaran;

    }
    void tambahCatatan()
    {
        // Membuka file catatan.txt
        ifstream fin;
        fin.open(FILENAME);

        int nomor = 1;
        string line;
        // Membaca setiap baris dalam file untuk mendapatkan nomor terakhir
        while (getline(fin, line))
        {
            nomor = nomor + 1;
        }

        fin.close();

        // Meminta pengguna untuk memasukkan data baru
        cout << "Masukkan data baru untuk catatan nomor " << nomor << ":\n";
        cout << "Masukkan tanggal (dd/mm/yyyy): ";
        cin >> tanggal;
        cout << "Masukkan asal pemasukan: ";
        cin.ignore();
        getline(cin, asal_pemasukan);
        cout << "Masukkan nominal pemasukan: ";
        cin >> nominal_pemasukan;
        cout << "Masukkan asal pengeluaran: ";
        cin.ignore();
        getline(cin, asal_pengeluaran);
        cout << "Masukkan nominal pengeluaran: ";
        cin >> nominal_pengeluaran;

        hitungTotal();

        // Menambahkan data baru ke file catatan.txt
        ofstream fout;
        fout.open(FILENAME, ios::app);

        fout << nomor << ". " << tanggal << '|' << asal_pemasukan << '|' << nominal_pemasukan << '|' << asal_pengeluaran << '|' << nominal_pengeluaran << '|' << total << "\n";

        fout.close();
        cout << "Catatan berhasil ditambahkan.\n";
    }
    void lihatCatatan()
    {
        // Membuka file catatan.txt
        ifstream fin;
        fin.open(FILENAME);
        cout << "No Tanggal\tAsal Pemasukan\tNominal\tAsal Pengeluaran\tNominal\t Total \t Uangku Sekarang\n";
        cout << "-------------------------------------------------------------------------------------------------------------\n";
        string line;
        size_t pos;
        int sumtotal = 0; //total dari semua data yang sudah dimasukkan
        int counter = 0; //counter untuk menghitung jumlah data yang sudah dibaca

        while (getline(fin, line))// membaca setiap baris dari file
        {
            counter++;
            pos = line.find('|');// mencari posisi karakter '|'
            tanggal = line.substr(0, pos); // mengambil substring sebelum karakter '|'
            line.erase(0, pos + 1);// menghapus substring sebelum karakter '|'

            pos = line.find('|');
            asal_pemasukan = line.substr(0, pos);
            line.erase(0, pos + 1);

            pos = line.find('|');
            nominal_pemasukan = stoi(line.substr(0, pos));
            line.erase(0, pos + 1);

            pos = line.find('|');
            asal_pengeluaran = line.substr(0, pos);
            line.erase(0, pos + 1);

            pos = line.find('|');
            nominal_pengeluaran = stoi(line.substr(0, pos));
            line.erase(0, pos + 1);

            total = stoi(line);

            cout << left << setw(15) << tanggal << " "
                 << left << setw(12) << asal_pemasukan << " "
                 << right << setw(11) << nominal_pemasukan << " "
                 << left << setw(17) << asal_pengeluaran << " "
                 << right << setw(10) << nominal_pengeluaran << " "
                 << right << setw(10) << total;

            sumtotal = sumtotal + total; //menambahkan total ke sumtotal
            if (counter > 1) //jika counter lebih dari satu
            {
                cout << right << setw(15) << sumtotal;
            }
            cout << "\n"; //pindah baris

        }
        fin.close();
        cout << "-------------------------------------------------------------------------------------------------------------\n";
    }

    void editCatatan()
    {
        lihatCatatan();

        // Meminta pengguna untuk memasukkan nomor catatan yang ingin diedit
        cout << "Masukkan nomor urut catatan yang ingin diedit: ";
        cin >> nomor_awal;
        cout << "Masukkan data baru untuk catatan tersebut:\n";
        cout << "Masukkan tanggal (dd/mm/yyyy): ";
        cin >> tanggal;
        cout << "Masukkan asal pemasukan: ";
        cin.ignore();
        getline(cin, asal_pemasukan);
        cout << "Masukkan nominal pemasukan: ";
        cin >> nominal_pemasukan;
        cout << "Masukkan asal pengeluaran: ";
        cin.ignore();
        getline(cin, asal_pengeluaran);
        cout << "Masukkan nominal pengeluaran: ";
        cin >> nominal_pengeluaran;

        hitungTotal();

        // Membuka file catatan.txt
        ifstream fin;
        fin.open(FILENAME);

        // Membuka file temp.txt sebagai file sementara
        ofstream fout;
        fout.open("temp.txt", ios::app);

        string line;
        size_t pos;
        bool found = false; // variabel untuk menandai apakah catatan ditemukan atau tidak

        // Membaca setiap baris dari file catatan.txt
        while (getline(fin, line))
        {
            pos = line.find(". ");
            nomor = stoi(line.substr(0, pos));
            line.erase(0, pos + 2);

            if (nomor == nomor_awal)
            {
                found = true;
                // tulis data baru ke file sementara
                fout << nomor << ". " << tanggal << '|' << asal_pemasukan << '|' << nominal_pemasukan << '|' << asal_pengeluaran << '|' << nominal_pengeluaran << '|' << total << "\n";
            }
            else
            {
                // menulis data lama yang dibaca dari file catatan.txt ke file temp.txt tanpa mengubahnya
                fout << nomor << ". " << line << "\n";
            }

        }

        fin.close();
        fout.close();

        remove(FILENAME.c_str());
        rename("temp.txt", FILENAME.c_str());

        if (found)
        {
            cout << "Catatan berhasil diedit.\n";
        }
        else
        {
            cout << "Catatan tidak ditemukan.\n";
        }
    }

    void hapusCatatan()
    {
        lihatCatatan();

        cout << "Masukkan nomor urut catatan yang ingin dihapus: ";
        cin >> nomor_awal;

        ifstream fin;
        fin.open(FILENAME);

        ofstream fout;
        fout.open("temp.txt", ios::app);

        string line;
        size_t pos;
        bool found = false;
        int i = 0;

        while (getline(fin, line))
        {
            pos = line.find(". ");
            nomor = stoi(line.substr(0, pos));
            line.erase(0, pos + 2);

            if (nomor == nomor_awal)
            {
                found = true;
                continue;
            }
            else
            {
                // menulis data lama yang dibaca dari file catatan.txt ke file temp.txt dengan mengubah nomor urutnya sesuai dengan variabel i
                fout <<  i + 1  << ". " << line << "\n";
            }
            i++;

        }

        fin.close();
        fout.close();

        remove(FILENAME.c_str());
        rename("temp.txt", FILENAME.c_str());

        if (found) // jika catatan ditemukan
        {
            cout << "Catatan berhasil dihapus.\n";
        }
        else
        {
            cout << "Catatan tidak ditemukan.\n";
        }
    }
};
#endif // TABUNGAN_H
