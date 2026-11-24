#include <iostream>
#include <string>
#include <fstream>
#include <clocale>
#include <unordered_map>

#ifdef _WIN32
#include <windows.h>
#endif

#include "pipe.h"
#include "cs.h"

using namespace std;

// Файл для логирования действий пользователя.
ofstream log_fayl("log.txt");

// Функция защиты от некорректного ввода.
int vvod_celogo(int min_znachenie, int max_znachenie) {
    int chislo;

    while (!(cin >> chislo) || chislo < min_znachenie || chislo > max_znachenie) {
        cout << "Ошибка! Введите число от " << min_znachenie
            << " до " << max_znachenie << ": ";
        cin.clear();
        while (cin.get() != '\n');
    }

    log_fayl << chislo << endl;
    return chislo;
}

// Функция защиты от некорректного ввода.
double vvod_drobnogo(double min_znachenie, double max_znachenie) {
    double chislo;

    while (!(cin >> chislo) || chislo < min_znachenie || chislo > max_znachenie) {
        cout << "Ошибка! Введите число от " << min_znachenie
            << " до " << max_znachenie << ": ";
        cin.clear();
        while (cin.get() != '\n');
    }

    log_fayl << chislo << endl;
    return chislo;
}

// Просмотр всех объектов.
void prosmotr(const unordered_map<int, Truba>& trubi,
    const unordered_map<int, Stanciya>& stancii) {

    cout << "\n=== СПИСОК ТРУБ ===\n";
    cout << "\nСПИСОК ТРУБ\n";

    if (trubi.empty()) {
        cout << "Трубы не созданы.\n";
    }
    else {
        for (const auto& para : trubi) {
            pokazat_trubu(para.first, para.second);
        }
    }

    cout << "\n=== СПИСОК СТАНЦИЙ ===\n";
    cout << "\nСПИСОК СТАНЦИЙ\n";

    if (stancii.empty()) {
        cout << "Станции не созданы.\n";
    }
    else {
        for (const auto& para : stancii) {
            pokazat_stanciyu(para.first, para.second);
        }
    }
}

// Сохранение труб и КС в один файл.
void sohranit(const unordered_map<int, Truba>& trubi,
    const unordered_map<int, Stanciya>& stancii) {

    string imya_fayla;

    cout << "Введите название файла для сохранения: ";
    cin >> ws;
    getline(cin, imya_fayla);
    log_fayl << imya_fayla << endl;

    ofstream fayl(imya_fayla);

    if (fayl.is_open()) {
        fayl << trubi.size() << endl;

        for (const auto& para : trubi) {
            para.second.save(fayl);
        }

        fayl << stancii.size() << endl;

        for (const auto& para : stancii) {
            para.second.save(fayl);
        }

        cout << "Данные сохранены в файл " << imya_fayla << "!\n";
        fayl.close();
    }
    else {
        cout << "Ошибка записи в файл!\n";
    }
}

// Загрузка труб и КС из файла.
void zagruzit(unordered_map<int, Truba>& trubi,
    unordered_map<int, Stanciya>& stancii) {

    string imya_fayla;

    cout << "Введите название файла для загрузки: ";
    cin >> ws;
    getline(cin, imya_fayla);
    log_fayl << imya_fayla << endl;

    ifstream fayl(imya_fayla);

    if (!fayl.is_open()) {
        cout << "Файл не найден!\n";
        return;
    }

    int kolvo_trub;

    if (!(fayl >> kolvo_trub) || kolvo_trub < 0) {
        cout << "Ошибка чтения файла!\n";
        return;
    }

    // Новый файл загружается с начала нумерации.
    trubi.clear();
    stancii.clear();

    Truba::resetId();
    Stanciya::resetId();

    for (int i = 0; i < kolvo_trub; i++) {
        Truba truba;

        if (!truba.load(fayl)) {
            cout << "Ошибка чтения данных о трубе!\n";
            return;
        }

        trubi.emplace(truba.getId(), truba);
    }

    int kolvo_stanciy;

    if (!(fayl >> kolvo_stanciy) || kolvo_stanciy < 0) {
        cout << "Ошибка чтения данных о станциях!\n";
        return;
    }

    for (int i = 0; i < kolvo_stanciy; i++) {
        Stanciya stanciya;

        if (!stanciya.load(fayl)) {
            cout << "Ошибка чтения данных о станции!\n";
            return;
        }

        stancii.emplace(stanciya.getId(), stanciya);
    }

    cout << "Данные загружены из файла " << imya_fayla << "!\n";
    fayl.close();
}

// Главное меню.
int main() {

#ifdef _WIN32
    // Ввод и вывод консоли Windows в кодировке UTF-8.
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    setlocale(LC_ALL, ".UTF8");
#else
    // Использование системной UTF-8-локали в других операционных системах.
    setlocale(LC_ALL, "");
#endif

    unordered_map<int, Truba> trubi;
    unordered_map<int, Stanciya> stancii;

    int vibor_menyu;

    while (true) {
        cout << "\nМеню\n";
        cout << "1. Добавить трубу\n";
        cout << "2. Добавить КС\n";
        cout << "3. Просмотр всех объектов\n";
        cout << "4. Редактировать трубу\n";
        cout << "5. Редактировать КС\n";
        cout << "6. Удалить трубу\n";
        cout << "7. Удалить КС\n";
        cout << "8. Поиск и пакетное редактирование труб\n";
        cout << "9. Поиск КС\n";
        cout << "10. Сохранить\n";
        cout << "11. Загрузить\n";
        cout << "0. Выход\n";

        cout << "Выберите действие: ";

        vibor_menyu = vvod_celogo(0, 11);

        switch (vibor_menyu) {

        case 1:
            dobavit_trubu(trubi);
            break;

        case 2:
            dobavit_stanciyu(stancii);
            break;

        case 3:
            prosmotr(trubi, stancii);
            break;

        case 4:
            redaktirovat_trubu(trubi);
            break;

        case 5:
            redaktirovat_stanciyu(stancii);
            break;

        case 6:
            udalit_trubu(trubi);
            break;

        case 7:
            udalit_stanciyu(stancii);
            break;

        case 8:
            poisk_trub(trubi);
            break;

        case 9:
            poisk_stanciy(stancii);
            break;

        case 10:
            sohranit(trubi, stancii);
            break;

        case 11:
            zagruzit(trubi, stancii);
            break;

        case 0:
            cout << "Выход из программы...\n";
            log_fayl.close();
            return 0;
        }
    }

    return 0;
}