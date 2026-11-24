#include "pipe.h"

using namespace std;

int Truba::nextId = 1;

Truba::Truba()
    : id(0), nazvanie(""), dlina(0.0), diametr(0), v_remonte(false) {
}

Truba::Truba(const string& nazvanie, double dlina, int diametr)
    : id(nextId++), nazvanie(nazvanie), dlina(dlina),
    diametr(diametr), v_remonte(false) {
}

// Сохранение трубы в том же текстовом формате, который использовался раньше.
void Truba::save(ostream& fayl) const {
    fayl << id << endl;
    fayl << nazvanie << endl;
    fayl << dlina << endl;
    fayl << diametr << endl;
    fayl << v_remonte << endl;
}

// Загрузка трубы и восстановление следующего свободного ID.
bool Truba::load(istream& fayl) {
    if (!(fayl >> id)) {
        return false;
    }

    fayl >> ws;
    if (!getline(fayl, nazvanie)) {
        return false;
    }

    if (!(fayl >> dlina >> diametr >> v_remonte)) {
        return false;
    }

    if (id >= nextId) {
        nextId = id + 1;
    }

    return true;
}

// Вывод информации об одной трубе.
void pokazat_trubu(int id, const Truba& truba) {
    cout << "\n--- ТРУБА (ID: " << id << ") ---\n";
    cout << "\nТРУБА (ID: " << id << ")\n";
    cout << "Название: " << truba.getNazvanie() << "\n";
    cout << "Длина: " << truba.getDlina() << " км\n";
    cout << "Диаметр: " << truba.getDiametr() << " мм\n";
    cout << "В ремонте: " << (truba.isInRepair() ? "Да" : "Нет") << "\n";
}

// Добавление трубы.
void dobavit_trubu(unordered_map<int, Truba>& trubi) {
    string nazvanie;

    cout << "Введите название трубы: ";
    cin >> ws;
    getline(cin, nazvanie);
    log_fayl << nazvanie << endl;

    cout << "Введите длину (км): ";
    double dlina = vvod_drobnogo(0.1, 100000.0);

    cout << "Введите диаметр (мм): ";
    int diametr = vvod_celogo(10, 5000);

    cout << "Труба в ремонте? (1 - да, 0 - нет): ";
    bool v_remonte = vvod_celogo(0, 1);

    Truba truba(nazvanie, dlina, diametr);
    truba.setRepair(v_remonte);

    int id = truba.getId();
    trubi.emplace(id, truba);
    cout << "Труба успешно добавлена! Её ID: " << id << "\n";
}

// Редактирование статуса трубы по ID.
void redaktirovat_trubu(unordered_map<int, Truba>& trubi) {
    if (trubi.empty()) {
        cout << "Ошибка: Сначала добавьте хотя бы одну трубу!\n";
        return;
    }

    cout << "Введите ID трубы для редактирования: ";
    int id = vvod_celogo(1, 100000);

    auto it = trubi.find(id);
    if (it == trubi.end()) {
        cout << "Ошибка: Труба с таким ID не найдена!\n";
        return;
    }

    cout << "Труба в ремонте? (Сейчас: "
        << (it->second.isInRepair() ? 1 : 0)
        << "). Введите 1 (да) или 0 (нет): ";
    it->second.setRepair(vvod_celogo(0, 1));
    cout << "Статус трубы обновлен!\n";
}

// Удаление трубы по ID.
void udalit_trubu(unordered_map<int, Truba>& trubi) {
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

// Пакетное редактирование или удаление найденных труб.
// set хранит уникальные ID без повторений.
void paketnoe_redaktirovanie_trub(
    unordered_map<int, Truba>& trubi,
    const set<int>& naydennie_id) {

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

    set<int> vibrannie_id;

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

            if (naydennie_id.find(id) != naydennie_id.end()) {
                vibrannie_id.insert(id);
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
            trubi.at(id).setRepair(noviy_status);
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

// Поиск труб по названию или статусу ремонта.
void poisk_trub(unordered_map<int, Truba>& trubi) {
    if (trubi.empty()) {
        cout << "Список труб пуст!\n";
        return;
    }

    cout << "Фильтр поиска труб:\n";
    cout << "1 - По названию\n";
    cout << "2 - По признаку 'в ремонте'\n";
    cout << "Ваш выбор: ";
    int vibor = vvod_celogo(1, 2);

    set<int> naydennie_id;

    if (vibor == 1) {
        string poisk_nazvanie;
        cout << "Введите название (или часть названия) трубы: ";
        cin >> ws;
        getline(cin, poisk_nazvanie);
        log_fayl << poisk_nazvanie << endl;

        for (const auto& para : trubi) {
            if (para.second.getNazvanie().find(poisk_nazvanie) != string::npos) {
                naydennie_id.insert(para.first);
            }
        }
    }
    else {
        cout << "Искать трубы в ремонте? (1 - да, 0 - нет): ";
        bool poisk_remont = vvod_celogo(0, 1);

        for (const auto& para : trubi) {
            if (para.second.isInRepair() == poisk_remont) {
                naydennie_id.insert(para.first);
            }
        }
    }

    if (naydennie_id.empty()) {
        cout << "Трубы по заданному фильтру не найдены.\n";
    }
    else {
        cout << "\nНайдено труб: " << naydennie_id.size() << "\n";

        for (int id : naydennie_id) {
            pokazat_trubu(id, trubi.at(id));
        }

        // После поиска запускается пакетная обработка, как в первоначальной версии.
        paketnoe_redaktirovanie_trub(trubi, naydennie_id);
    }
}
