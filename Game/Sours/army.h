#pragma once
#include "unit_creator.h"
#include <vector>

struct Army {
    virtual void attack_commander_skill() = 0; //бонус к атаке
    virtual void defense_commander_skill() = 0; //бонус к защите
    virtual void move_commander_skill() = 0; //бонус к передвижению
    virtual void go_to_square(pair<int,int> square) = 0;
    virtual void add_unit(Unit* u) = 0;
    virtual int get_units_size() = 0;
    virtual Unit* extract_last_unit() = 0;
    virtual vector<Unit*> get_units() = 0;
    virtual pair<int,int> get_location() = 0;
};

struct RealArmy: public Army {
    string Commander_Name = "Вар, верни мне мою генерацию имён!";//имена должны генерироваться при создании/разделении
    vector<Unit*> Units;
    pair<int,int> Location; // местонахождение армии
    virtual void attack_commander_skill(); //бонус к атаке
    virtual void defense_commander_skill(); //бонус к защите
    virtual void move_commander_skill(); //бонус к передвижению
    virtual void go_to_square(pair<int,int> square);
    virtual void add_unit(Unit* u);
    virtual int get_units_size();
    virtual Unit* extract_last_unit();
    virtual vector<Unit*> get_units();
    virtual pair<int,int> get_location();

    ~RealArmy();
};

struct ArmyCreator {
    Army* CreateArmy(UnitFactory* unit_creator,int inf_num, int arch_num, int knig_num, pair<int, int> location);
    void MergeArmy(Army* first, Army* second);//вливает вторую армию в первую возможно сделать дополнением к add_units хз
};

//различные улучшения различных характеристик армии
struct Commander: public Army {
    Army* army;
    Commander(Army* a);
    virtual void attack_commander_skill();
    virtual void defense_commander_skill();
    virtual void move_commander_skill();
    virtual void go_to_square(pair<int,int> square);
    virtual void add_unit(Unit* u);
    virtual Unit* extract_last_unit();
    virtual int get_units_size();
    virtual vector<Unit*> get_units();
    virtual pair<int,int> get_location();
};

struct CommanderAttackArea: public Commander {
    CommanderAttackArea(Army* a);
    virtual void  attack_commander_skill();
};

struct CommanderAttackStrong: public Commander {
    CommanderAttackStrong(Army* a);
    virtual void  attack_commander_skill();
};

struct CommanderDefenseArea: public Commander {
    CommanderDefenseArea(Army* a);
    virtual void  defense_commander_skill();
};

struct CommanderDefenseStrong: public Commander {
    CommanderDefenseStrong(Army* a);
    virtual void  defense_commander_skill();
};

struct CommanderMoveDistance: public Commander {
    CommanderMoveDistance(Army* a);
    virtual void  move_commander_skill();
};

struct CommanderMoveNavigation: public Commander {
    CommanderMoveNavigation(Army* a);
    virtual void  move_commander_skill();
};

struct CommanderLevelUpper{
    Army *CommanderLevelUp(Army* army, int level_up_id);//улучшение характеристики
};