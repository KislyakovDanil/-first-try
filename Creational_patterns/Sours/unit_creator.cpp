#pragma once
#include "unit_creator.h"

Unit*  UnitFactory::CreateInfantryman() {
    static StandartInfantryman infantryman;
    return infantryman.clone();
}

Unit*  UnitFactory::CreateArcher() {
    static StandartArcher archer;
    return archer.clone();
}

Unit*  UnitFactory::CreateKnight() {
    static StandartKnight knight;
    return knight.clone();
}

UnitFactory::~UnitFactory() {}


Unit* EnglandUnitFactory::CreateArcher(){
    static EnglandArcher archer;
    return archer.clone();
}


Unit* FranceUnitFactory::CreateKnight(){
    static FranceKnight knight;
    return knight.clone();
}


UnitFactory* UnitCreator::CreateUnitFactory(int fraction_id) {
    switch (fraction_id) {
        case 0:
            return new EnglandUnitFactory;
        case 1:
            return new FranceUnitFactory;
    }
}

Unit* UnitCreator::CreateUnit(int unit_id, UnitFactory *unit_creator) {
    switch (unit_id) {
        case 0:
            return unit_creator->CreateInfantryman();
        case 1:
            return unit_creator->CreateArcher();
        case 2:
            return unit_creator->CreateKnight();
    }
}