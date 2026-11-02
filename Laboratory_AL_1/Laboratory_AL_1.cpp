#include <iostream>
#include <string>
#include <fstream>
#include <clocale>
#include <map>
#include <vector>
#include <windows.h>

using namespace std;

// Файл для логирования действий пользователя
ofstream log_fayl("log.txt");

// Базовые классы
class Truba {
public:
    string nazvanie = "";
    double dlina = 0.0;
    int diametr = 0;
    bool v_remonte = false;
};

class Stanciya {
public:
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

// Вспомогательные функции вывода одного объекта
void pokazat_trubu(int id, Truba& truba) {
    cout << "\nТРУБА (ID: " << id << ")\n";
    cout << "Название: " << truba.nazvanie << "\n";
    cout << "Длина: " << truba.dlina << " км\n";
    cout << "Диаметр: " << truba.diametr << " мм\n";
    cout << "В ремонте: " << (truba.v_remonte ? "Да" : "Нет") << "\n";
}

void pokazat_stanciyu(int id, Stanciya& stanciya) {
    double procent = (stanciya.vsego_cehov - stanciya.rabochih_cehov) * 100.0 / stanciya.vsego_cehov;
    cout << "\nСТАНЦИЯ (ID: " << id << ")\n";
    cout << "Название: " << stanciya.nazvanie << "\n";
    cout << "Всего цехов: " << stanciya.vsego_cehov << "\n";
    cout << "Рабочих цехов: " << stanciya.rabochih_cehov << "\n";
    cout << "Незадействовано цехов: " << procent << "%\n";
    cout << "Класс станции: " << stanciya.klass << "\n";
}

// Функции добавления
void dobavit_trubu(map<int, Truba>& trubi, int& id_trubi) {
    Truba truba;
    cout << "Введите название трубы: ";
    cin >> ws;
    getline(cin, truba.nazvanie);
    log_fayl << truba.nazvanie << endl;

    cout << "Введите длину (км): ";
    truba.dlina = vvod_drobnogo(0.1, 100000.0);
    cout << "Введите диаметр (мм): ";
    truba.diametr = vvod_celogo(10, 5000);
    cout << "Труба в ремонте? (1 - да, 0 - нет): ";
    truba.v_remonte = vvod_celogo(0, 1);

    id_trubi++;
    trubi[id_trubi] = truba;
    cout << "Труба успешно добавлена! Её ID: " << id_trubi << "\n";
}

void dobavit_stanciyu(map<int, Stanciya>& stancii, int& id_stancii) {
    Stanciya stanciya;
    cout << "Введите название станции: ";
    cin >> ws;
    getline(cin, stanciya.nazvanie);
    log_fayl << stanciya.nazvanie << endl;

    cout << "Введите всего цехов: ";
    stanciya.vsego_cehov = vvod_celogo(1, 100);
    cout << "Введите рабочих цехов: ";
    stanciya.rabochih_cehov = vvod_celogo(0, stanciya.vsego_cehov);
    cout << "Введите класс станции (1-5): ";
    stanciya.klass = vvod_celogo(1, 5);

    id_stancii++;
    stancii[id_stancii] = stanciya;
    cout << "Станция успешно добавлена! Её ID: " << id_stancii << "\n";
}

// Функция просмотра всех объектов
void prosmotr(map<int, Truba>& trubi, map<int, Stanciya>& stancii) {
    cout << "\nСПИСОК ТРУБ\n";
    if (trubi.empty()) {
        cout << "Трубы не созданы.\n";
    }
    else {
        for (auto& para : trubi) {
            pokazat_trubu(para.first, para.second);
        }
    }

    cout << "\nСПИСОК СТАНЦИЙ\n";
    if (stancii.empty()) {
        cout << "Станции не созданы.\n";
    }
    else {
        for (auto& para : stancii) {
            pokazat_stanciyu(para.first, para.second);
        }
    }
}

// Функции редактирования по ID
void redaktirovat_trubu(map<int, Truba>& trubi) {
    if (trubi.empty()) {
        cout << "Ошибка: Сначала добавьте хотя бы одну трубу!\n";
        return;
    }
    cout << "Введите ID трубы для редактирования: ";
    int id = vvod_celogo(1, 100000);

    if (trubi.find(id) == trubi.end()) {
        cout << "Ошибка: Труба с таким ID не найдена!\n";
        return;
    }

    cout << "Труба в ремонте? (Сейчас: " << trubi[id].v_remonte << "). Введите 1 (да) или 0 (нет): ";
    trubi[id].v_remonte = vvod_celogo(0, 1);
    cout << "Статус трубы обновлен!\n";
}

void redaktirovat_stanciyu(map<int, Stanciya>& stancii) {
    if (stancii.empty()) {
        cout << "Ошибка: Сначала добавьте хотя бы одну станцию!\n";
        return;
    }
    cout << "Введите ID станции для редактирования: ";
    int id = vvod_celogo(1, 100000);

    if (stancii.find(id) == stancii.end()) {
        cout << "Ошибка: Станция с таким ID не найдена!\n";
        return;
    }

    cout << "1 - Запустить цех, 2 - Остановить цех. Ваш выбор: ";
    int deystvie = vvod_celogo(1, 2);
    if (deystvie == 1) {
        if (stancii[id].rabochih_cehov < stancii[id].vsego_cehov) {
            stancii[id].rabochih_cehov++;
            cout << "Цех запущен!\n";
        }
        else {
            cout << "Все цехи и так работают!\n";
        }
    }
    else {
        if (stancii[id].rabochih_cehov > 0) {
            stancii[id].rabochih_cehov--;
            cout << "Цех остановлен!\n";
        }
        else {
            cout << "Все цехи и так остановлены!\n";
        }
    }
}

// Функции удаления по ID
void udalit_trubu(map<int, Truba>& trubi) {
    if (trubi.empty()) {
        cout << "Ошибка: Список труб пуст!\n";
        return;
    }
    cout << "Введите ID трубы для удаления: ";
    int id = vvod_celogo(1, 100000);

    if (trubi.erase(id)) {
        cout << "Труба с ID " << id << " удалена!\n";
    }
    else {
        cout << "Ошибка: Труба с таким ID не найдена!\n";
    }
}

void udalit_stanciyu(map<int, Stanciya>& stancii) {
    if (stancii.empty()) {
        cout << "Ошибка: Список станций пуст!\n";
        return;
    }
    cout << "Введите ID станции для удаления: ";
    int id = vvod_celogo(1, 100000);

    if (stancii.erase(id)) {
        cout << "Станция с ID " << id << " удалена!\n";
    }
    else {
        cout << "Ошибка: Станция с таким ID не найдена!\n";
    }
}

// Пакетное редактирование и удаление найденных труб
void paketnoe_redaktirovanie_trub(map<int, Truba>& trubi, vector<int>& naydennie_id) {
    cout << "\nПакетная обработка найденных труб:\n";
    cout << "1 - Редактировать найденные трубы\n";
    cout << "2 - Удалить найденные трубы\n";
    cout << "0 - Ничего не делать (вернуться в меню)\n";
    cout << "Ваш выбор: ";
    int deystvie = vvod_celogo(0, 2);

    if (deystvie == 0) {
        return;
    }

    cout << "1 - Применить ко ВСЕМ найденным трубам\n";
    cout << "2 - Выбрать конкретные трубы по ID\n";
    cout << "Ваш выбор: ";
    int rezhim = vvod_celogo(1, 2);

    vector<int> vibrannie_id;

    if (rezhim == 1) {
        vibrannie_id = naydennie_id;
    }
    else {
        while (true) {
            cout << "Введите ID трубы из найденных (0 - завершить выбор): ";
            int id = vvod_celogo(0, 100000);
            if (id == 0) {
                break;
            }

            // Проверяем, есть ли этот ID среди найденных
            bool est_v_spiske = false;
            for (int naydenniy : naydennie_id) {
                if (naydenniy == id) {
                    est_v_spiske = true;
                    break;
                }
            }

            if (est_v_spiske) {
                vibrannie_id.push_back(id);
                cout << "Труба с ID " << id << " добавлена в выборку.\n";
            }
            else {
                cout << "Ошибка: Трубы с таким ID нет среди найденных!\n";
            }
        }
    }

    if (vibrannie_id.empty()) {
        cout << "Не выбрано ни одной трубы.\n";
        return;
    }

    if (deystvie == 1) {
        cout << "Установить статус 'в ремонте' для выбранных труб? (1 - да, 0 - нет): ";
        bool noviy_status = vvod_celogo(0, 1);
        for (int id : vibrannie_id) {
            trubi[id].v_remonte = noviy_status;
        }
        cout << "Статус выбранных труб успешно обновлен!\n";
    }
    else if (deystvie == 2) {
        for (int id : vibrannie_id) {
            trubi.erase(id);
        }
        cout << "Выбранные трубы успешно удалены!\n";
    }
}

// Функции поиска объектов по фильтру
void poisk_trub(map<int, Truba>& trubi) {
    if (trubi.empty()) {
        cout << "Список труб пуст!\n";
        return;
    }

    cout << "Фильтр поиска труб:\n";
    cout << "1 - По названию\n";
    cout << "2 - По признаку 'в ремонте'\n";
    cout << "Ваш выбор: ";
    int vibor = vvod_celogo(1, 2);

    vector<int> naydennie_id;

    if (vibor == 1) {
        string poisk_nazvanie;
        cout << "Введите название трубы: ";
        cin >> ws;
        getline(cin, poisk_nazvanie);
        log_fayl << poisk_nazvanie << endl;

        for (auto& para : trubi) {
            if (para.second.nazvanie.find(poisk_nazvanie) != string::npos) {
                naydennie_id.push_back(para.first);
            }
        }
    }
    else {
        cout << "Искать трубы в ремонте? (1 - да, 0 - нет): ";
        bool poisk_remont = vvod_celogo(0, 1);

        for (auto& para : trubi) {
            if (para.second.v_remonte == poisk_remont) {
                naydennie_id.push_back(para.first);
            }
        }
    }

    if (naydennie_id.empty()) {
        cout << "Трубы по заданному фильтру не найдены.\n";
    }
    else {
        cout << "\nНайдено труб: " << naydennie_id.size() << "\n";
        for (int id : naydennie_id) {
            pokazat_trubu(id, trubi[id]);
        }
        // Вызываем пакетное редактирование для найденных труб
        paketnoe_redaktirovanie_trub(trubi, naydennie_id);
    }
}

void poisk_stanciy(map<int, Stanciya>& stancii) {
    if (stancii.empty()) {
        cout << "Список станций пуст!\n";
        return;
    }

    cout << "Фильтр поиска КС:\n";
    cout << "1 - По названию\n";
    cout << "2 - По проценту незадействованных цехов\n";
    cout << "Ваш выбор: ";
    int vibor = vvod_celogo(1, 2);

    vector<int> naydennie_id;

    if (vibor == 1) {
        string poisk_nazvanie;
        cout << "Введите название (или часть названия) станции: ";
        cin >> ws;
        getline(cin, poisk_nazvanie);
        log_fayl << poisk_nazvanie << endl;

        for (auto& para : stancii) {
            if (para.second.nazvanie.find(poisk_nazvanie) != string::npos) {
                naydennie_id.push_back(para.first);
            }
        }
    }
    else {
        cout << "Введите процент незадействованных цехов (0 - 100): ";
        double zadanniy_procent = vvod_drobnogo(0.0, 100.0);
        cout << "Условие (1 - Больше или равно, 2 - Меньше или равно, 3 - Точно равно): ";
        int uslovie = vvod_celogo(1, 3);

        for (auto& para : stancii) {
            double procent = (para.second.vsego_cehov - para.second.rabochih_cehov) * 100.0 / para.second.vsego_cehov;
            if (uslovie == 1 && procent >= zadanniy_procent) {
                naydennie_id.push_back(para.first);
            }
            else if (uslovie == 2 && procent <= zadanniy_procent) {
                naydennie_id.push_back(para.first);
            }
            else if (uslovie == 3 && (int)procent == (int)zadanniy_procent) {
                naydennie_id.push_back(para.first);
            }
        }
    }

    if (naydennie_id.empty()) {
        cout << "Станции по заданному фильтру не найдены.\n";
    }
    else {
        cout << "\nНайдено станций: " << naydennie_id.size() << "\n";
        for (int id : naydennie_id) {
            pokazat_stanciyu(id, stancii[id]);
        }
    }
}

// Работа с файлами
void sohranit(map<int, Truba>& trubi, map<int, Stanciya>& stancii) {
    string imya_fayla;
    cout << "Придумайте название файла для сохранения: ";
    cin >> ws;
    getline(cin, imya_fayla);
    log_fayl << imya_fayla << endl;

    ofstream fayl(imya_fayla);
    if (fayl.is_open()) {
        fayl << trubi.size() << endl;
        for (auto& para : trubi) {
            fayl << para.first << endl;
            fayl << para.second.nazvanie << endl;
            fayl << para.second.dlina << endl;
            fayl << para.second.diametr << endl;
            fayl << para.second.v_remonte << endl;
        }

        fayl << stancii.size() << endl;
        for (auto& para : stancii) {
            fayl << para.first << endl;
            fayl << para.second.nazvanie << endl;
            fayl << para.second.vsego_cehov << endl;
            fayl << para.second.rabochih_cehov << endl;
            fayl << para.second.klass << endl;
        }
        cout << "Данные сохранены в файл " << imya_fayla << "!\n";
        fayl.close();
    }
    else {
        cout << "Ошибка записи в файл!\n";
    }
}

void zagruzit(map<int, Truba>& trubi, map<int, Stanciya>& stancii, int& id_trubi, int& id_stancii) {
    string imya_fayla;
    cout << "Введите название файла для загрузки: ";
    cin >> ws;
    getline(cin, imya_fayla);
    log_fayl << imya_fayla << endl;

    ifstream fayl(imya_fayla);
    if (fayl.is_open()) {
        trubi.clear();
        stancii.clear();
        id_trubi = 0;
        id_stancii = 0;

        int kolvo_trub;
        fayl >> kolvo_trub;
        for (int i = 0; i < kolvo_trub; i++) {
            int id;
            Truba truba;
            fayl >> id;
            fayl >> ws;
            getline(fayl, truba.nazvanie);
            fayl >> truba.dlina;
            fayl >> truba.diametr;
            fayl >> truba.v_remonte;
            trubi[id] = truba;
            if (id > id_trubi) id_trubi = id;
        }

        int kolvo_stanciy;
        fayl >> kolvo_stanciy;
        for (int i = 0; i < kolvo_stanciy; i++) {
            int id;
            Stanciya stanciya;
            fayl >> id;
            fayl >> ws;
            getline(fayl, stanciya.nazvanie);
            fayl >> stanciya.vsego_cehov;
            fayl >> stanciya.rabochih_cehov;
            fayl >> stanciya.klass;
            stancii[id] = stanciya;
            if (id > id_stancii) id_stancii = id;
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
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);       // Включает ввод русских букв
    SetConsoleOutputCP(1251); // Включает вывод русских букв

    map<int, Truba> trubi;
    map<int, Stanciya> stancii;
    int id_trubi = 0;
    int id_stancii = 0;
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
            dobavit_trubu(trubi, id_trubi);
            break;
        case 2:
            dobavit_stanciyu(stancii, id_stancii);
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
            zagruzit(trubi, stancii, id_trubi, id_stancii);
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