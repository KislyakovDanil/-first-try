#pragma once
#include "unit.cpp"

// Абстрактная фабрика для производства воинов
struct UnitFactory {
    virtual Unit* CreateInfantryman() {
        static StandartInfantryman infantryman;
        return infantryman.clone();
    }
    virtual Unit* CreateArcher() {
        static StandartArcher archer;
        return archer.clone();
    }
    virtual Unit* CreateKnight() {
        static StandartKnight knight;
        return knight.clone();
    }
    virtual ~UnitFactory() {}
};

// Фабрика для создания воинов Английской армии
struct EnglandUnitFactory: public UnitFactory {
    Unit* CreateArcher(){
        return new EnglandArcher;
    }
};

// Фабрика для создания воинов Французской армии
struct FranceUnitFactory: public UnitFactory {
    Unit* CreateKnight(){
        return new FranceKnight;
    }
};

struct UnitCreator {
    UnitFactory* CreateUnitFactory(int fraction_id) {
        switch (fraction_id) {
            case 0:
                return new EnglandUnitFactory;
            case 1:
                return new FranceUnitFactory;
        }
    }
    Unit* CreateUnit(int unit_id, UnitFactory *unit_creator) {
        switch (unit_id) {
            case 0:
                return unit_creator->CreateInfantryman();
            case 1:
                return unit_creator->CreateArcher();
            case 2:
                return unit_creator->CreateKnight();
        }
    }
};