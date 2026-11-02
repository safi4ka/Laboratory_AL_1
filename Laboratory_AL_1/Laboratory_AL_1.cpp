#include <iostream>
#include <string>
#include <fstream>
#include <clocale>

using namespace std;

// Файл для логирования действий пользователя
ofstream log_fayl("log.txt");

// Базовые структуры
struct Truba {
    string nazvanie = "";
    double dlina = 0.0;
    int diametr = 0;
    bool v_remonte = false;
};

struct Stanciya {
    string nazvanie = "";
    int vsego_cehov = 0;
    int rabochih_cehov = 0;
    int klass = 0;
};

// Функция защиты от некорректного ввода (целые числа)
int vvod_celogo(int min_znachenie, int max_znachenie) {
    int chislo;
    while (!(cin >> chislo) || chislo < min_znachenie || chislo > max_znachenie) {
        cout << "Ошибка! Введите число от " << min_znachenie << " до " << max_znachenie << ": ";
        cin.clear();
        while (cin.get() != '\n');
    }
    log_fayl << chislo << endl; // Логируем введенное целое число
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
    log_fayl << chislo << endl; // Логируем введенное дробное число
    return chislo;
}

// Функции добавления
void dobavit_trubu(Truba& truba) {
    cout << "Введите название трубы: ";
    cin >> ws;
    getline(cin, truba.nazvanie);
    log_fayl << truba.nazvanie << endl; // Логируем название трубы

    cout << "Введите длину (км): ";
    truba.dlina = vvod_drobnogo(0.1, 100000.0);
    cout << "Введите диаметр (мм): ";
    truba.diametr = vvod_celogo(10, 5000);
    cout << "Труба в ремонте? (1 - да, 0 - нет): ";
    truba.v_remonte = vvod_celogo(0, 1);
    cout << "Труба успешно добавлена!\n";
}

void dobavit_stanciyu(Stanciya& stanciya) {
    cout << "Введите название станции: ";
    cin >> ws;
    getline(cin, stanciya.nazvanie);
    log_fayl << stanciya.nazvanie << endl; // Логируем название станции

    cout << "Введите всего цехов: ";
    stanciya.vsego_cehov = vvod_celogo(1, 100);
    cout << "Введите рабочих цехов: ";
    stanciya.rabochih_cehov = vvod_celogo(0, stanciya.vsego_cehov);
    cout << "Введите класс станции (1-5): ";
    stanciya.klass = vvod_celogo(1, 5);
    cout << "Станция успешно добавлена!\n";
}

// Функция просмотра
void prosmotr(Truba& truba, Stanciya& stanciya) {
    if (truba.dlina) {
        cout << "\n--- ТРУБА ---\n";
        cout << "Название: " << truba.nazvanie << "\n";
        cout << "Длина: " << truba.dlina << " км\n";
        cout << "Диаметр: " << truba.diametr << " мм\n";
        cout << "В ремонте: " << (truba.v_remonte ? "Да" : "Нет") << "\n";
    }
    else {
        cout << "\nТруба не создана.\n";
    }

    if (stanciya.vsego_cehov) {
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
    if (!truba.dlina) {
        cout << "Ошибка: Сначала добавьте трубу!\n";
        return;
    }
    cout << "Труба в ремонте? (Сейчас: " << truba.v_remonte << "). Введите 1 (да) или 0 (нет): ";
    truba.v_remonte = vvod_celogo(0, 1);
    cout << "Статус трубы обновлен!\n";
}

void redaktirovat_stanciyu(Stanciya& stanciya) {
    if (!stanciya.vsego_cehov) {
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
    string imya_fayla;
    cout << "Введите название файла для сохранения (например, dannie.txt): ";
    cin >> ws;
    getline(cin, imya_fayla);
    log_fayl << imya_fayla << endl; // Логируем имя файла

    ofstream fayl(imya_fayla);
    if (fayl.is_open()) {
        fayl << truba.dlina << endl;
        if (truba.dlina) {
            fayl << truba.nazvanie << endl;
            fayl << truba.dlina << endl;
            fayl << truba.diametr << endl;
            fayl << truba.v_remonte << endl;
        }
        fayl << stanciya.vsego_cehov << endl;
        if (stanciya.vsego_cehov) {
            fayl << stanciya.nazvanie << endl;
            fayl << stanciya.vsego_cehov << endl;
            fayl << stanciya.rabochih_cehov << endl;
            fayl << stanciya.klass << endl;
        }
        cout << "Данные сохранены в файл " << imya_fayla << "!\n";
        fayl.close();
    }
    else {
        cout << "Ошибка записи в файл!\n";
    }
}

void zagruzit(Truba& truba, Stanciya& stanciya) {
    string imya_fayla;
    cout << "Введите название файла для загрузки (например, dannie.txt): ";
    cin >> ws;
    getline(cin, imya_fayla);
    log_fayl << imya_fayla << endl; // Логируем имя файла

    ifstream fayl(imya_fayla);
    if (fayl.is_open()) {
        fayl >> truba.dlina;
        if (truba.dlina) {
            fayl >> ws;
            getline(fayl, truba.nazvanie);
            fayl >> truba.dlina;
            fayl >> truba.diametr;
            fayl >> truba.v_remonte;
        }
        fayl >> stanciya.vsego_cehov;
        if (stanciya.vsego_cehov) {
            fayl >> ws;
            getline(fayl, stanciya.nazvanie);
            fayl >> stanciya.vsego_cehov;
            fayl >> stanciya.rabochih_cehov;
            fayl >> stanciya.klass;
        }
        cout << "Данные загружены из файла " << imya_fayla << "!\n";
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
        cout << "\nМеню\n";
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

        switch (vibor_menyu) {
        case 1:
            dobavit_trubu(moya_truba);
            break;
        case 2:
            dobavit_stanciyu(moya_stanciya);
            break;
        case 3:
            prosmotr(moya_truba, moya_stanciya);
            break;
        case 4:
            redaktirovat_trubu(moya_truba);
            break;
        case 5:
            redaktirovat_stanciyu(moya_stanciya);
            break;
        case 6:
            sohranit(moya_truba, moya_stanciya);
            break;
        case 7:
            zagruzit(moya_truba, moya_stanciya);
            break;
        case 0:
            cout << "Выход из программы...\n";
            log_fayl.close();
            return 0;
        default:
            break;
        }
    }
    return 0;
}