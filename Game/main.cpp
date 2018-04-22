#pragma once
#include "Sours\army.h"


//fraction_id: Англия-0 Франция-1
//units_id: пех-0 лук-1 конь-2
// в идеале у меня где-то хранятся вектора с этими id

int main() {
    //пример работы
    int fraction_id;
    int inf_num, arch_num, knig_num;
    cin >> fraction_id >> inf_num >> arch_num >> knig_num;//считаем фракцию и предполагаемое число юнитов в армии по типам
    UnitCreator U_Creator;
    ArmyCreator A_Creator;
    CommanderLevelUpper ComLevUpper;
    UnitFactory* unit_creator = U_Creator.CreateUnitFactory(fraction_id);//в начале игры создаём фабрику для этой фракции
    Army* my_army = A_Creator.CreateArmy(unit_creator, inf_num, arch_num, knig_num, make_pair(0,0));//создаём армию
    my_army->attack_commander_skill();//базовые характеристики армии
    cout << endl;
    my_army->defense_commander_skill();
    cout << endl;
    my_army->move_commander_skill();
    cout << endl;
    cout << endl;
    my_army = ComLevUpper.CommanderLevelUp(my_army, 0);//улучшения
    my_army = ComLevUpper.CommanderLevelUp(my_army, 1);
    my_army = ComLevUpper.CommanderLevelUp(my_army, 2);
    my_army = ComLevUpper.CommanderLevelUp(my_army, 5);
    my_army->attack_commander_skill();//характеристики армии после ряда улучшений
    cout << endl;
    my_army->defense_commander_skill();
    cout << endl;
    my_army->move_commander_skill();
    cout << endl;
    cout << endl;
    for (Unit* warrior: my_army->get_units()) {//юниты в этой армии
        warrior->class_skill();
        warrior->special_skill();
        cout << "Damage and Speed:" << warrior->Damage << " " << warrior->Speed << " " << endl;
        cout << endl;
    }
    delete my_army;
    return 0;
}