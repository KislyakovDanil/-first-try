#include "Sours\unit_creator.cpp"


//fraction_id: Англия-0 Франция-1
//units_id: пех-0 лук-1 конь-2
// в идеале у меня где-то хранятся вектора с этими id

int main() {
    //пример работы
    UnitCreator Creator;
    int fraction_id;
    int unit_id;
    cin >> fraction_id >> unit_id;//на вход подаются фракция и тип юнита
    UnitFactory* unit_creator = Creator.CreateUnitFactory(fraction_id);//в начале игры создаём фабрику для этой фракции
    Unit* warrior = Creator.CreateUnit(unit_id, unit_creator);// которая делает нам конкретных юнитов
    warrior->class_skill();
    warrior->special_skill();
    cout << "Location:" << warrior->Location.first << " " << warrior->Location.second << " ";
    cout << "Damage and Speed:" << warrior->Damage << " " << warrior->Speed << " ";
    warrior->set_start_square(make_pair(5,5));
    cout << "New Location:" << warrior->Location.first << " " << warrior->Location.second << " ";
    return 0;
}