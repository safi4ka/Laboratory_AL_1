#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Truba {
    string nazvanie;
    double dlina;
    int diametr;
    bool v_remonte;
    bool sozdana = false;
};

struct Stanciya {
    string nazvanie;
    int vsego_cehov;
    int rabochih_cehov;
    int klass;
    bool sozdana = false;
};

int vvod_celogo(int min_znachenie, int max_znachenie) {
    int chislo;
    while (!(cin >> chislo) || chislo < min_znachenie || chislo > max_znachenie) {
        cout << "Oshibka! Vvedite chislo ot " << min_znachenie << " do " << max_znachenie << ": ";
        cin.clear();
        while (cin.get() != '\n');
    }
    return chislo;
}

double vvod_drobnogo(double min_znachenie, double max_znachenie) {
    double chislo;
    while (!(cin >> chislo) || chislo < min_znachenie || chislo > max_znachenie) {
        cout << "Oshibka! Vvedite chislo ot " << min_znachenie << " do " << max_znachenie << ": ";
        cin.clear();
        while (cin.get() != '\n');
    }
    return chislo;
}

int main() {
    Truba moya_truba;
    Stanciya moya_stanciya;
    int vibor_menyu;

    while (true) {
        cout << "\n=== MENYU ===\n";
        cout << "1. Dobavit trubu\n";
        cout << "2. Dobavit KS\n";
        cout << "3. Prosmotr vseh obyektov\n";
        cout << "4. Redaktirovat trubu\n";
        cout << "5. Redaktirovat KS\n";
        cout << "6. Sohranit\n";
        cout << "7. Zagruzit\n";
        cout << "0. Vihod\n";
        cout << "Viberite deystvie: ";

        vibor_menyu = vvod_celogo(0, 7);

        if (vibor_menyu == 0) {
            cout << "Vihod iz programmi...\n";
            break;
        }
    }
    return 0;
}