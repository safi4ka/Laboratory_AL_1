#include <iostream>
#include <string>
#include <fstream>
#include <clocale>

using namespace std;

// Базовые структуры
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

// Функция защиты от некорректного ввода (целые числа)
int vvod_celogo(int min_znachenie, int max_znachenie) {
    int chislo;
    while (!(cin >> chislo) || chislo < min_znachenie || chislo > max_znachenie) {
        cout << "Ошибка! Введите число от " << min_znachenie << " до " << max_znachenie << ": ";
        cin.clear();
        while (cin.get() != '\n');
    }
    return chislo;
}

// Функция защиты от некорректного ввода (дробные числа)
double vvod_drobnogo(double min_znachenie, double max_znachenie) {
    double chislo;
    while (!(cin >> chislo) || chislo < min_znachenie || chislo > max_znachenie) {
        cout << "Ошибка! Введите число от " << min_znachenie << " до " << max_znachenie << ": ";
        cin.clear();
        while (cin.get() != '\n');
    }
    return chislo;
}

// Функции добавления
void dobavit_trubu(Truba& truba) {
    cout << "Введите название трубы: ";
    cin >> ws;
    getline(cin, truba.nazvanie);
    cout << "Введите длину (км): ";
    truba.dlina = vvod_drobnogo(0.1, 100000.0);
    cout << "Введите диаметр (мм): ";
    truba.diametr = vvod_celogo(10, 5000);
    cout << "Труба в ремонте? (1 - да, 0 - нет): ";
    truba.v_remonte = vvod_celogo(0, 1);
    truba.sozdana = true;
    cout << "Труба успешно добавлена!\n";
}

void dobavit_stanciyu(Stanciya& stanciya) {
    cout << "Введите название станции: ";
    cin >> ws;
    getline(cin, stanciya.nazvanie);
    cout << "Введите всего цехов: ";
    stanciya.vsego_cehov = vvod_celogo(1, 100);
    cout << "Введите рабочих цехов: ";
    stanciya.rabochih_cehov = vvod_celogo(0, stanciya.vsego_cehov);
    cout << "Введите класс станции (1-5): ";
    stanciya.klass = vvod_celogo(1, 5);
    stanciya.sozdana = true;
    cout << "Станция успешно добавлена!\n";
}

// Функция просмотра
void prosmotr(Truba& truba, Stanciya& stanciya) {
    if (truba.sozdana) {
        cout << "\n--- ТРУБА ---\n";
        cout << "Название: " << truba.nazvanie << "\n";
        cout << "Длина: " << truba.dlina << " км\n";
        cout << "Диаметр: " << truba.diametr << " мм\n";
        cout << "В ремонте: " << (truba.v_remonte ? "Да" : "Нет") << "\n";
    }
    else {
        cout << "\nТруба не создана.\n";
    }

    if (stanciya.sozdana) {
        cout << "\n--- СТАНЦИЯ ---\n";
        cout << "Название: " << stanciya.nazvanie << "\n";
        cout << "Всего цехов: " << stanciya.vsego_cehov << "\n";
        cout << "Рабочих цехов: " << stanciya.rabochih_cehov << "\n";
        cout << "Класс станции: " << stanciya.klass << "\n";
    }
    else {
        cout << "\nСтанция не создана.\n";
    }
}

// Функции редактирования
void redaktirovat_trubu(Truba& truba) {
    if (!truba.sozdana) {
        cout << "Ошибка: Сначала добавьте трубу!\n";
        return;
    }
    cout << "Труба в ремонте? (Сейчас: " << truba.v_remonte << "). Введите 1 (да) или 0 (нет): ";
    truba.v_remonte = vvod_celogo(0, 1);
    cout << "Статус трубы обновлен!\n";
}

void redaktirovat_stanciyu(Stanciya& stanciya) {
    if (!stanciya.sozdana) {
        cout << "Ошибка: Сначала добавьте станцию!\n";
        return;
    }
    cout << "1 - Запустить цех, 2 - Остановить цех. Ваш выбор: ";
    int deystvie = vvod_celogo(1, 2);
    if (deystvie == 1) {
        if (stanciya.rabochih_cehov < stanciya.vsego_cehov) {
            stanciya.rabochih_cehov++;
            cout << "Цех запущен!\n";
        }
        else {
            cout << "Все цехи и так работают!\n";
        }
    }
    else {
        if (stanciya.rabochih_cehov > 0) {
            stanciya.rabochih_cehov--;
            cout << "Цех остановлен!\n";
        }
        else {
            cout << "Все цехи и так остановлены!\n";
        }
    }
}

// Работа с файлами
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
        cout << "Данные сохранены в файл dannie.txt!\n";
        fayl.close();
    }
    else {
        cout << "Ошибка записи в файл!\n";
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
        cout << "Данные загружены из файла!\n";
        fayl.close();
    }
    else {
        cout << "Файл не найден!\n";
    }
}

// Главное меню
int main() {
    setlocale(LC_ALL, "Russian"); // Включение кириллицы в консоли

    Truba moya_truba;
    Stanciya moya_stanciya;
    int vibor_menyu;

    while (true) {
        cout << "\Меню\n";
        cout << "1. Добавить трубу\n";
        cout << "2. Добавить КС\n";
        cout << "3. Просмотр всех объектов\n";
        cout << "4. Редактировать трубу\n";
        cout << "5. Редактировать КС\n";
        cout << "6. Сохранить\n";
        cout << "7. Загрузить\n";
        cout << "0. Выход\n";
        cout << "Выберите действие: ";

        vibor_menyu = vvod_celogo(0, 7);

        if (vibor_menyu == 1) dobavit_trubu(moya_truba);
        else if (vibor_menyu == 2) dobavit_stanciyu(moya_stanciya);
        else if (vibor_menyu == 3) prosmotr(moya_truba, moya_stanciya);
        else if (vibor_menyu == 4) redaktirovat_trubu(moya_truba);
        else if (vibor_menyu == 5) redaktirovat_stanciyu(moya_stanciya);
        else if (vibor_menyu == 6) sohranit(moya_truba, moya_stanciya);
        else if (vibor_menyu == 7) zagruzit(moya_truba, moya_stanciya);
        else if (vibor_menyu == 0) {
            cout << "Выход из программы...\n";
            break;
        }
    }
    return 0;
}