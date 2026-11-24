#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

// Общий файл логирования и функция проверки целочисленного ввода определены в main.cpp.
extern std::ofstream log_fayl;
int vvod_celogo(int min_znachenie, int max_znachenie);
double vvod_drobnogo(double min_znachenie, double max_znachenie);

// Класс компрессорной станции.
class Stanciya {
private:
    static int nextId;

    int id;
    std::string nazvanie;
    int vsego_cehov;
    int rabochih_cehov;
    int klass;

public:
    Stanciya();
    Stanciya(const std::string& nazvanie, int vsego_cehov,
        int rabochih_cehov, int klass);

    static void resetId() { nextId = 1; }

    int getId() const { return id; }
    const std::string& getNazvanie() const { return nazvanie; }
    int getVsegoCehov() const { return vsego_cehov; }
    int getRabochihCehov() const { return rabochih_cehov; }
    int getKlass() const { return klass; }
    double getProcentNezadeystvovannyhCehov() const;

    bool zapustit_ceh();
    bool ostanovit_ceh();

    void save(std::ostream& fayl) const;
    bool load(std::istream& fayl);
};

// Функции работы с компрессорными станциями.
void pokazat_stanciyu(int id, const Stanciya& stanciya);
void dobavit_stanciyu(std::unordered_map<int, Stanciya>& stancii);
void redaktirovat_stanciyu(std::unordered_map<int, Stanciya>& stancii);
void udalit_stanciyu(std::unordered_map<int, Stanciya>& stancii);
void poisk_stanciy(std::unordered_map<int, Stanciya>& stancii);
