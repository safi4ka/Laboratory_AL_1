#include "cs.h"
#include <set>

using namespace std;

int Stanciya::nextId = 1;

Stanciya::Stanciya()
    : id(0), nazvanie(""), vsego_cehov(0), rabochih_cehov(0), klass(0) {
}

Stanciya::Stanciya(const string& nazvanie, int vsego_cehov,
    int rabochih_cehov, int klass)
    : id(nextId++), nazvanie(nazvanie), vsego_cehov(vsego_cehov),
    rabochih_cehov(rabochih_cehov), klass(klass) {
}

double Stanciya::getProcentNezadeystvovannyhCehov() const {
    return (vsego_cehov - rabochih_cehov) * 100.0 / vsego_cehov;
}

bool Stanciya::zapustit_ceh() {
    if (rabochih_cehov >= vsego_cehov) {
        return false;
    }

    ++rabochih_cehov;
    return true;
}

bool Stanciya::ostanovit_ceh() {
    if (rabochih_cehov <= 0) {
        return false;
    }

    --rabochih_cehov;
    return true;
}

// Сохранение станции в прежнем текстовом формате.
void Stanciya::save(ostream& fayl) const {
    fayl << id << endl;
    fayl << nazvanie << endl;
    fayl << vsego_cehov << endl;
    fayl << rabochih_cehov << endl;
    fayl << klass << endl;
}

// Загрузка станции и восстановление следующего свободного ID.
bool Stanciya::load(istream& fayl) {
    if (!(fayl >> id)) {
        return false;
    }

    fayl >> ws;
    if (!getline(fayl, nazvanie)) {
        return false;
    }

    if (!(fayl >> vsego_cehov >> rabochih_cehov >> klass)) {
        return false;
    }

    if (id >= nextId) {
        nextId = id + 1;
    }

    return vsego_cehov > 0 && rabochih_cehov >= 0 &&
        rabochih_cehov <= vsego_cehov && klass >= 1 && klass <= 5;
}

// Вывод информации об одной компрессорной станции.
void pokazat_stanciyu(int id, const Stanciya& stanciya) {
    double procent = stanciya.getProcentNezadeystvovannyhCehov();

    cout << "\n--- СТАНЦИЯ (ID: " << id << ") ---\n";
    cout << "\nСТАНЦИЯ (ID: " << id << ")\n";
    cout << "Название: " << stanciya.getNazvanie() << "\n";
    cout << "Всего цехов: " << stanciya.getVsegoCehov() << "\n";
    cout << "Рабочих цехов: " << stanciya.getRabochihCehov() << "\n";
    cout << "Незадействовано цехов: " << procent << "%\n";
    cout << "Класс станции: " << stanciya.getKlass() << "\n";
}

// Добавление компрессорной станции.
void dobavit_stanciyu(unordered_map<int, Stanciya>& stancii) {
    string nazvanie;

    cout << "Введите название станции: ";
    cin >> ws;
    getline(cin, nazvanie);
    log_fayl << nazvanie << endl;

    cout << "Введите всего цехов: ";
    int vsego_cehov = vvod_celogo(1, 100);

    cout << "Введите рабочих цехов: ";
    int rabochih_cehov = vvod_celogo(0, vsego_cehov);

    cout << "Введите класс станции (1-5): ";
    int klass = vvod_celogo(1, 5);

    Stanciya stanciya(nazvanie, vsego_cehov, rabochih_cehov, klass);
    int id = stanciya.getId();
    stancii.emplace(id, stanciya);

    cout << "Станция успешно добавлена! Её ID: " << id << "\n";
}

// Редактирование количества работающих цехов.
void redaktirovat_stanciyu(unordered_map<int, Stanciya>& stancii) {
    if (stancii.empty()) {
        cout << "Ошибка: Сначала добавьте хотя бы одну станцию!\n";
        return;
    }

    cout << "Введите ID станции для редактирования: ";
    int id = vvod_celogo(1, 100000);

    auto it = stancii.find(id);
    if (it == stancii.end()) {
        cout << "Ошибка: Станция с таким ID не найдена!\n";
        return;
    }

    cout << "1 - Запустить цех, 2 - Остановить цех. Ваш выбор: ";
    int deystvie = vvod_celogo(1, 2);

    if (deystvie == 1) {
        if (it->second.zapustit_ceh()) {
            cout << "Цех запущен!\n";
        }
        else {
            cout << "Все цехи и так работают!\n";
        }
    }
    else {
        if (it->second.ostanovit_ceh()) {
            cout << "Цех остановлен!\n";
        }
        else {
            cout << "Все цехи и так остановлены!\n";
        }
    }
}

// Удаление компрессорной станции по ID.
void udalit_stanciyu(unordered_map<int, Stanciya>& stancii) {
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

// Поиск КС по названию или проценту незадействованных цехов.
void poisk_stanciy(unordered_map<int, Stanciya>& stancii) {
    if (stancii.empty()) {
        cout << "Список станций пуст!\n";
        return;
    }

    cout << "Фильтр поиска КС:\n";
    cout << "1 - По названию\n";
    cout << "2 - По проценту незадействованных цехов\n";
    cout << "Ваш выбор: ";
    int vibor = vvod_celogo(1, 2);

    set<int> naydennie_id;

    if (vibor == 1) {
        string poisk_nazvanie;
        cout << "Введите название (или часть названия) станции: ";
        cin >> ws;
        getline(cin, poisk_nazvanie);
        log_fayl << poisk_nazvanie << endl;

        for (const auto& para : stancii) {
            if (para.second.getNazvanie().find(poisk_nazvanie) != string::npos) {
                naydennie_id.insert(para.first);
            }
        }
    }
    else {
        cout << "Введите процент незадействованных цехов (0 - 100): ";
        double zadanniy_procent = vvod_drobnogo(0.0, 100.0);
        cout << "Условие (1 - Больше или равно, 2 - Меньше или равно, 3 - Точно равно): ";
        int uslovie = vvod_celogo(1, 3);

        for (const auto& para : stancii) {
            double procent = para.second.getProcentNezadeystvovannyhCehov();

            if (uslovie == 1 && procent >= zadanniy_procent) {
                naydennie_id.insert(para.first);
            }
            else if (uslovie == 2 && procent <= zadanniy_procent) {
                naydennie_id.insert(para.first);
            }
            else if (uslovie == 3 && (int)procent == (int)zadanniy_procent) {
                // Сохраняется исходное сравнение целых частей процентов.
                naydennie_id.insert(para.first);
            }
        }
    }

    if (naydennie_id.empty()) {
        cout << "Станции по заданному фильтру не найдены.\n";
    }
    else {
        cout << "\nНайдено станций: " << naydennie_id.size() << "\n";

        for (int id : naydennie_id) {
            pokazat_stanciyu(id, stancii.at(id));
        }
    }
}