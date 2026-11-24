#pragma once
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>

// Общий файл логирования и функции проверки ввода определены в main.cpp.
extern std::ofstream log_fayl;
int vvod_celogo(int min_znachenie, int max_znachenie);
double vvod_drobnogo(double min_znachenie, double max_znachenie);

// Класс трубы.
class Truba {
private:
    static int nextId;

    int id;
    std::string nazvanie;
    double dlina;
    int diametr;
    bool v_remonte;

public:
    Truba();
    Truba(const std::string& nazvanie, double dlina, int diametr);

    static void resetId() { nextId = 1; }

    int getId() const { return id; }
    const std::string& getNazvanie() const { return nazvanie; }
    double getDlina() const { return dlina; }
    int getDiametr() const { return diametr; }
    bool isInRepair() const { return v_remonte; }
    void setRepair(bool value) { v_remonte = value; }

    void save(std::ostream& fayl) const;
    bool load(std::istream& fayl);
};

// Функции работы с трубами. Их названия сохранены из первоначальной программы.
void pokazat_trubu(int id, const Truba& truba);
void dobavit_trubu(std::unordered_map<int, Truba>& trubi);
void redaktirovat_trubu(std::unordered_map<int, Truba>& trubi);
void udalit_trubu(std::unordered_map<int, Truba>& trubi);
void paketnoe_redaktirovanie_trub(
    std::unordered_map<int, Truba>& trubi,
    const std::set<int>& naydennie_id);
void poisk_trub(std::unordered_map<int, Truba>& trubi);