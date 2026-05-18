 #include <iostream>
#include <string>
using namespace std;

// ─── Abstract Base Class ───────────────────────────────────────────────
class RekeningBank {
protected:
    string nasabah;
    double saldo;

public:
    RekeningBank(string nama, double saldoAwal)
        : nasabah(nama), saldo(saldoAwal) {}

    virtual void potongAdmin() = 0;  // pure virtual function

    void tampilInfo() const {
        cout << "Nasabah : " << nasabah << endl;
        cout << "Saldo   : Rp " << saldo << endl;
    }

    virtual ~RekeningBank() {}
};

// ─── Rekening Syariah ─────────────────────────────────────────────────
class RekeningSyariah : public RekeningBank {
public:
    RekeningSyariah(string nama, double saldoAwal)
        : RekeningBank(nama, saldoAwal) {}

    void potongAdmin() override {
        // Prinsip syariah: bebas biaya admin, saldo tidak berubah
        cout << "[Syariah] " << nasabah
             << " - Tidak ada potongan biaya admin." << endl;
    }
};

// ─── Rekening Konvensional ────────────────────────────────────────────
class RekeningKonvensional : public RekeningBank {
private:
    const double BIAYA_ADMIN = 15000.0;

public:
    RekeningKonvensional(string nama, double saldoAwal)
        : RekeningBank(nama, saldoAwal) {}

    void potongAdmin() override {
        saldo -= BIAYA_ADMIN;
        cout << "[Konvensional] " << nasabah
             << " - Dipotong Rp 15.000. Saldo sekarang: Rp "
             << saldo << endl;
    }
};

// ─── Rekening Premium (BARU) ──────────────────────────────────────────
class RekeningPremium : public RekeningBank {
private:
    const double BATAS_SALDO = 10000000.0;
    const double BIAYA_ADMIN  =    50000.0;

public:
    RekeningPremium(string nama, double saldoAwal)
        : RekeningBank(nama, saldoAwal) {}

    void potongAdmin() override {
        if (saldo > BATAS_SALDO) {
            // Saldo di atas Rp 10.000.000 → bebas biaya admin
            cout << "[Premium] " << nasabah
                 << " - Saldo > Rp 10.000.000. Bebas biaya admin." << endl;
        } else {
            // Saldo di bawah/sama dengan Rp 10.000.000 → potong Rp 50.000
            saldo -= BIAYA_ADMIN;
            cout << "[Premium] " << nasabah
                 << " - Saldo ≤ Rp 10.000.000. Dipotong Rp 50.000. "
                 << "Saldo sekarang: Rp " << saldo << endl;
        }
    }
};

// ─── Main: Simulasi Proses Akhir Bulan ───────────────────────────────
int main() {
    // Server bank menyimpan semua rekening via pointer base class
    RekeningBank* rekening[] = {
        new RekeningSyariah      ("Ahmad Syarif",   5000000.0),
        new RekeningKonvensional ("Budi Santoso",   2500000.0),
        new RekeningPremium      ("Citra Dewi",    15000000.0),  // bebas admin
        new RekeningPremium      ("Doni Kusuma",    8000000.0),  // kena potong
    };

    cout << "=== Proses Biaya Admin Akhir Bulan ===" << endl;
    cout << "Bank Gibran Jaya" << endl;
    cout << "======================================" << endl;

    int n = sizeof(rekening) / sizeof(rekening[0]);
    for (int i = 0; i < n; i++) {
        rekening[i]->potongAdmin();  // polimorfisme bekerja di sini
    }

    // Bersihkan memori
    for (int i = 0; i < n; i++) {
        delete rekening[i];
    }

    return 0; 
}