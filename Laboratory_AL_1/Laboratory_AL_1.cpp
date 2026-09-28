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

void dobavit_trubu(Truba& truba) {
    cout << "Vvedite nazvanie trubi: ";
    cin >> ws;
    getline(cin, truba.nazvanie);
    cout << "Vvedite dlinu (km): ";
    truba.dlina = vvod_drobnogo(0.1, 100000.0);
    cout << "Vvedite diametr (mm): ";
    truba.diametr = vvod_celogo(10, 5000);
    cout << "Truba v remonte? (1 - da, 0 - net): ";
    truba.v_remonte = vvod_celogo(0, 1);
    truba.sozdana = true;
    cout << "Truba uspeshno dobavlena!\n";
}

void dobavit_stanciyu(Stanciya& stanciya) {
    cout << "Vvedite nazvanie stancii: ";
    cin >> ws;
    getline(cin, stanciya.nazvanie);
    cout << "Vvedite vsego cehov: ";
    stanciya.vsego_cehov = vvod_celogo(1, 100);
    cout << "Vvedite rabochih cehov: ";
    stanciya.rabochih_cehov = vvod_celogo(0, stanciya.vsego_cehov);
    cout << "Vvedite klass stancii (1-5): ";
    stanciya.klass = vvod_celogo(1, 5);
    stanciya.sozdana = true;
    cout << "Stanciya uspeshno dobavlena!\n";
}

void prosmotr(Truba& truba, Stanciya& stanciya) {
    if (truba.sozdana) {
        cout << "\n--- TRUBA ---\n";
        cout << "Nazvanie: " << truba.nazvanie << "\n";
        cout << "Dlina: " << truba.dlina << " km\n";
        cout << "Diametr: " << truba.diametr << " mm\n";
        cout << "V remonte: " << (truba.v_remonte ? "Da" : "Net") << "\n";
    }
    else {
        cout << "\nTruba ne sozdana.\n";
    }

    if (stanciya.sozdana) {
        cout << "\n--- STANCIYA ---\n";
        cout << "Nazvanie: " << stanciya.nazvanie << "\n";
        cout << "Vsego cehov: " << stanciya.vsego_cehov << "\n";
        cout << "Rabochih cehov: " << stanciya.rabochih_cehov << "\n";
        cout << "Klass stancii: " << stanciya.klass << "\n";
    }
    else {
        cout << "\nStanciya ne sozdana.\n";
    }
}

void redaktirovat_trubu(Truba& truba) {
    if (!truba.sozdana) {
        cout << "Oshibka: Snachala dobavte trubu!\n";
        return;
    }
    cout << "Truba v remonte? (Seychas: " << truba.v_remonte << "). Vvedite 1 (da) ili 0 (net): ";
    truba.v_remonte = vvod_celogo(0, 1);
    cout << "Status trubi obnovlen!\n";
}

void redaktirovat_stanciyu(Stanciya& stanciya) {
    if (!stanciya.sozdana) {
        cout << "Oshibka: Snachala dobavte stanciyu!\n";
        return;
    }
    cout << "1 - Zapustit ceh, 2 - Ostanovit ceh. Vash vibor: ";
    int deystvie = vvod_celogo(1, 2);
    if (deystvie == 1) {
        if (stanciya.rabochih_cehov < stanciya.vsego_cehov) {
            stanciya.rabochih_cehov++;
            cout << "Ceh zapuschen!\n";
        }
        else {
            cout << "Vse cehi i tak rabotayut!\n";
        }
    }
    else {
        if (stanciya.rabochih_cehov > 0) {
            stanciya.rabochih_cehov--;
            cout << "Ceh ostanovlen!\n";
        }
        else {
            cout << "Vse cehi i tak ostanovleni!\n";
        }
    }
}

void sohranit(Truba& truba, Stanciya& stanciya) {
    ofstream fayl("dannie.txt");
    if (fayl.is_open()) {
        fayl << truba.sozdana << endl;
        if (truba.sozdana) {
            fayl << truba.nazvanie << endl;
            fayl << truba.dlina << endl;
            fayl << truba.diametr << endl;
            fayl << truba.v_remonte << endl;
        }
        fayl << stanciya.sozdana << endl;
        if (stanciya.sozdana) {
            fayl << stanciya.nazvanie << endl;
            fayl << stanciya.vsego_cehov << endl;
            fayl << stanciya.rabochih_cehov << endl;
            fayl << stanciya.klass << endl;
        }
        cout << "Dannie sohraneni v fayl dannie.txt!\n";
        fayl.close();
    }
    else {
        cout << "Oshibka zapisi v fayl!\n";
    }
}

void zagruzit(Truba& truba, Stanciya& stanciya) {
    ifstream fayl("dannie.txt");
    if (fayl.is_open()) {
        fayl >> truba.sozdana;
        if (truba.sozdana) {
            fayl >> ws;
            getline(fayl, truba.nazvanie);
            fayl >> truba.dlina;
            fayl >> truba.diametr;
            fayl >> truba.v_remonte;
        }
        fayl >> stanciya.sozdana;
        if (stanciya.sozdana) {
            fayl >> ws;
            getline(fayl, stanciya.nazvanie);
            fayl >> stanciya.vsego_cehov;
            fayl >> stanciya.rabochih_cehov;
            fayl >> stanciya.klass;
        }
        cout << "Dannie zagruzeni iz fayla!\n";
        fayl.close();
    }
    else {
        cout << "Fayl ne nayden!\n";
    }
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

        if (vibor_menyu == 1) dobavit_trubu(moya_truba);
        else if (vibor_menyu == 2) dobavit_stanciyu(moya_stanciya);
        else if (vibor_menyu == 3) prosmotr(moya_truba, moya_stanciya);
        else if (vibor_menyu == 4) redaktirovat_trubu(moya_truba);
        else if (vibor_menyu == 5) redaktirovat_stanciyu(moya_stanciya);
        else if (vibor_menyu == 6) sohranit(moya_truba, moya_stanciya);
        else if (vibor_menyu == 7) zagruzit(moya_truba, moya_stanciya);
        else if (vibor_menyu == 0) {
            cout << "Vihod iz programmi...\n";
            break;
        }
    }
    return 0;
}