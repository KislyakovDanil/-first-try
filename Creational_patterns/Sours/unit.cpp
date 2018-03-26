#pragma once
#include <iostream>
using namespace std;

//подумать о добавлении остальных переменных как неконстантных
struct Unit {
    int Unit_HP; // хп конкретного юнита
    const int Max_HP; // максимальны хп данного вида юнитов
    const int Damage; // атака данного вида юнитов
    const int Combat_Distance; // максимальное расстояние атаки данного вида юнитов
    const int Speed; // скорость данного вида юнитов
    pair<int,int> Location; // местонахождение конкретного юнита
    Unit(int h, int d, int c_d, int s): Unit_HP(h), Max_HP(h), Damage(d), Combat_Distance(c_d), Speed(s), Location(make_pair(-1,-1)){};
    virtual void class_skill() = 0;
    virtual void special_skill() = 0;
    virtual Unit* clone() = 0;
    void set_start_square(pair<int,int> creation_city) { // задаёт квадрат, на котором юнит вступает в игру
        Location.first = creation_city.first;
        Location.second = creation_city.second;
    }
    virtual ~Unit() {}
};

// Базовые классы всех возможных видов юнитов
struct Infantryman: public Unit {
    Infantryman(int h, int d, int s):  Unit(h, d, 1, s){}
    virtual void special_skill() = 0;
    virtual Unit* clone() = 0;
    void class_skill() {
        cout << "InfantrymanSkill" << endl;
    }
    virtual ~Infantryman() {}
};

struct Archer: public Unit {
    Archer(int h, int d, int s):  Unit(h, d, 3, s){}
    virtual void special_skill() = 0;
    virtual Unit* clone() = 0;
    void class_skill() {
        cout << "ArcherSkill" << endl;
    }
    virtual ~Archer() {}
};

struct Knight: public Unit {
    Knight(int h, int d, int s):  Unit(h, d, 1, s){}
    virtual void special_skill() = 0;
    virtual Unit* clone() = 0;
    void class_skill() {
        cout << "KnightSkill" << endl;
    }
    virtual ~Knight() {}
};

// Конкретные классы стандартных юнитов
struct StandartInfantryman: public Infantryman {
    StandartInfantryman(): Infantryman(12, 4, 2){}
    virtual Unit* clone(){
        return new StandartInfantryman(*this);
    }
    void special_skill() {
        cout << "StandartInfantrymanSkill" << endl;
    }
};

struct StandartArcher: public Archer {
    StandartArcher():Archer(8, 2, 3){}
    virtual Unit* clone(){
        return new StandartArcher(*this);
    }
    void special_skill() {
        cout << "StandartArcherSkill" << endl;
    }
};

struct StandartKnight: public Knight {
    StandartKnight(): Knight(15, 6, 6){}
    virtual Unit* clone(){
        return new StandartKnight(*this);
    }
    void special_skill() {
        cout << "StandartKnightSkill" << endl;
    }
};

// Конкретные классы уникальных юнитов
struct EnglandArcher: public Archer {
    EnglandArcher(): Archer(8, 3, 3){}
    virtual Unit* clone(){
        return new EnglandArcher(*this);
    }
    void special_skill() {
        cout << "EnglandArcherSkill" << endl;
    }
};

struct FranceKnight: public Knight {
    FranceKnight(): Knight(18, 6, 5){}
    virtual Unit* clone(){
        return new FranceKnight(*this);
    }
    void special_skill() {
        cout << "FranceKnightSkill" << endl;
    }
};