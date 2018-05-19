#pragma once
#include "crusade.h"

void Battle(Army* first, Army* second) {
    //здесь скилы командиров
    Unit* first_army_unit = first->extract_last_unit();
    Unit* second_army_unit = second->extract_last_unit();
    while (first->get_units_size() != 0 && second->get_units_size() != 0){
        //здесь скилы юнитов
        if (first_army_unit->Combat_Distance > 1){
            second_army_unit->Unit_HP -= first_army_unit->Damage *(first_army_unit->Combat_Distance)*2/(second_army_unit->Speed);
        }
        if (second_army_unit->Combat_Distance > 1){
            first_army_unit->Unit_HP -= second_army_unit->Damage *(second_army_unit->Combat_Distance)*2/(first_army_unit->Speed);
        }
        while(first_army_unit->Unit_HP > 0 && second_army_unit->Unit_HP > 0){
            //здесь тоже скилы юнитов
            second_army_unit->Unit_HP = second_army_unit->Unit_HP - first_army_unit->Damage;
            first_army_unit->Unit_HP = first_army_unit->Unit_HP - second_army_unit->Damage;
        }
        if (first_army_unit->Unit_HP <= 0){
            first_army_unit = first->extract_last_unit();
        }
        if(second_army_unit->Unit_HP <= 0){
            second_army_unit = second->extract_last_unit();
        }
    }
}

void Crusade(vector<Fraction*>& Fractions, int country, bool& destroyed, int arm_num, int& x_coord, int& y_coord, Map& World_map){
    string route;
    cin >> route;
    int s = 3;
    if (route.size() < 3){
        s = route.size();
    }
    for (int i = 0; i < s; ++i){
        World_map.battlefield[x_coord][y_coord]->unsubscribe(Fractions[country]->Fraction_Army[arm_num]->get_army_id(), Fractions[country]->Fraction_Army[arm_num]->get_fraction_id());
        if (route[i] == 'L' || route[i] == 'l') {
            if (y_coord > 0) {
                --y_coord;
            }
        } else if (route[i] == 'R' || route[i] == 'r') {
            if (y_coord < World_map.battlefield.size()-1){
                ++y_coord;
            }
        } else if (route[i] == 'U' || route[i] == 'u') {
            if (x_coord > 0){
                --x_coord;
            }
        } else if (route[i] == 'D' || route[i] == 'd') {
            if (x_coord < World_map.battlefield.size()-1){
                ++x_coord;
            }
        } else {
            cout << "Incorrect" << i+1 << "route, the army remains in place" << endl;
            continue;
        }
        World_map.battlefield[x_coord][y_coord]->subscribe(Fractions[country]->Fraction_Army[arm_num]);
        Fractions[country]->Fraction_Army[arm_num]->go_to_square(make_pair(x_coord,y_coord));
        for (int j = 0; j < World_map.battlefield[x_coord][y_coord]->Armies.size(); ++j) {
            if (World_map.battlefield[x_coord][y_coord]->Armies[j]->get_fraction_id() == country^1) {
                Battle(Fractions[country]->Fraction_Army[arm_num], World_map.battlefield[x_coord][y_coord]->Armies[j]);
                if (Fractions[country]->Fraction_Army[arm_num]->get_units_size() == 0) {
                    int del_num = Fractions[country]->Fraction_Army[arm_num]->get_army_id();
                    World_map.battlefield[x_coord][y_coord]->unsubscribe(Fractions[country]->Fraction_Army[arm_num]->get_army_id(), Fractions[country]->Fraction_Army[arm_num]->get_fraction_id());
                    Fractions[country]->Fraction_Army.erase(Fractions[country]->Fraction_Army.begin() + arm_num);
                    for (auto k = 0; k < Fractions[country]->Fraction_Army.size(); ++k){
                        if(Fractions[country]->Fraction_Army[k]->get_army_id() > del_num){
                            Fractions[country]->Fraction_Army[k]->set_army_id(k);
                        }
                    }
                    destroyed = true;
                    return;
                }
                if (World_map.battlefield[x_coord][y_coord]->Armies[j]->get_units_size() == 0) {
                    int del_num = World_map.battlefield[x_coord][y_coord]->Armies[j]->get_army_id();
                    int arm_id = World_map.battlefield[x_coord][y_coord]->Armies[j]->get_army_id();
                    World_map.battlefield[x_coord][y_coord]->unsubscribe(World_map.battlefield[x_coord][y_coord]->Armies[j]->get_army_id(), World_map.battlefield[x_coord][y_coord]->Armies[j]->get_fraction_id());
                    Fractions[country^1]->Fraction_Army.erase(Fractions[country^1]->Fraction_Army.begin() + arm_id);
                    for (auto k = 0; k < Fractions[country^1]->Fraction_Army.size(); ++k){
                        if(Fractions[country^1]->Fraction_Army[k]->get_army_id() > del_num){
                            Fractions[country^1]->Fraction_Army[k]->set_army_id(k);
                        }
                    }
                    --j;
                }
            }
        }
    }
}
