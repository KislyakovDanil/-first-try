#pragma once
#include "game.h"

void help() {
    cout << "To call for help enter 'h'" << endl;
    cout << "One action per step:" << endl;
    cout << "To create an army enter 'c' and proportions of infantrymen, archers and knights in the army. Like 'c 0 1 1'" << endl;
    cout << "To move the army enter 'm', army number and string from one to three route from (U, D, R, L). Like 'm 0 LDD'" << endl;
    cout << "To skip a step enter 's'" << endl;
    cout << "To finish the Game enter 'e'" << endl;
};

void Global_map::set_next_state(Game* g){
    bool flag;
    string command;
    do {
        cin >> command;
        flag = false;
        while (command == "h"){
            help();
            cin >> command;
        }
        if (command == "c") {
            g->set_current_state(new Create(Fractions, World_map, A_Creator, country));
            g->create();
        } else if (command == "m") {
            g->set_current_state(new Move(Fractions, World_map, A_Creator, country));
            g->move();
        } else if (command == "s") {
            g->set_current_state(new Skip(Fractions, World_map, A_Creator, country));
            g->skip();
        } else if (command == "e") {
            country = country ^ 1;
            g->set_current_state(new Finish(Fractions, World_map, A_Creator, country));
            g->finish();
        } else {
            flag = true;
            cout << "Incorrect input, please repeat your command" << endl;
        }
    } while (flag);
}

void Start::set_next_state(Game* g){
    g->set_current_state(new Global_map(Fractions, World_map, A_Creator, country));
    g->global_map();
}

void Create::set_next_state(Game* g){
    g->set_current_state(new Global_map(Fractions, World_map, A_Creator, country));
    g->global_map();
}

void Move::set_next_state(Game* g){
    g->set_current_state(new Global_map(Fractions, World_map, A_Creator, country));
    g->global_map();
}

void Skip::set_next_state(Game* g){
    g->set_current_state(new Global_map(Fractions, World_map, A_Creator, country));
    g->global_map();
}

void Finish::set_next_state(Game* g){
    g->set_current_state(new Finish(Fractions, World_map, A_Creator, country));
    g->finish();
}

void State::start(Game* g) {
    g->current_state->set_next_state(g);
}

void State::global_map(Game* g) {
    country = country^1;
    World_map.Print_Map(Fractions);
    cout << Fractions[country]->name << " step" << endl;
    Fractions[country]->gold += 100 - Fractions[country]->Fraction_Army.size() * 10;
    if (Fractions[country]->gold < 50){
        Fractions[country]->gold = 50;
    }
    g->current_state->set_next_state(g);
    delete this;
}

void State::create(Game* g) {
    vector<int> units(3, -1);
    int v_num = 0;
    for (int i = 0; i < 3; ++i) {
        while (units[i] == -1) {
            units[i] = 0;
            string inp;
            cin >> inp;
            for (char j: inp) {
                if (isdigit(j) && units[i] * 10 + j - '0' >= 0) {
                    units[i] = units[i] * 10 + j - '0';
                } else {
                    units[i] = -1;
                    cout << "Incorrect input, please repeat number of unit " << i+1 <<  " type" << endl;
                    break;
                }
            }
        }
    }
    int inf_proport, arch_proport, knig_proport;
    int sum = units[0] + units[1] + units[2];
    inf_proport = units[0] * Fractions[country]->gold / sum;
    arch_proport = units[1] * Fractions[country]->gold / sum;
    knig_proport = units[2] * Fractions[country]->gold / sum;
    Fractions[country]->gold = 0;
    Fractions[country]->Fraction_Army.push_back(A_Creator.CreateArmy(Fractions[country]->Fraction_unit_creator, inf_proport, arch_proport, knig_proport, Fractions[country]->fraction_id, Fractions[country]->Fraction_Army.size(), make_pair(Fractions[country]->capital_coord.first,Fractions[country]->capital_coord.second)));
    World_map.battlefield[Fractions[country]->capital_coord.first][Fractions[country]->capital_coord.second]->subscribe(Fractions[country]->Fraction_Army.back());
    g->current_state->set_next_state(g);
    delete this;
}

void State::move(Game* g) {
    bool destroyed = false;
    int arm_num = -1, x_coord, y_coord;
    while (arm_num == -1) {
        arm_num = 0;
        string inp;
        cin >> inp;
        for (char i: inp) {
            if (isdigit(i) && arm_num * 10 + i - '0' < Fractions[country]->Fraction_Army.size()) {
                arm_num = arm_num * 10 + i - '0';
            } else {
                arm_num = -1;
                cout << "Incorrect input, please repeat army number" << endl;
                break;
            }
        }
    }
    x_coord = Fractions[country]->Fraction_Army[arm_num]->get_location().first;
    y_coord = Fractions[country]->Fraction_Army[arm_num]->get_location().second;
    Crusade(Fractions, country, destroyed, arm_num, x_coord, y_coord, World_map);
    if (x_coord == Fractions[country^1]->capital_coord.first && y_coord == Fractions[country^1]->capital_coord.second && !destroyed){
        g->set_current_state(new Finish(Fractions, World_map, A_Creator, country));
        g->finish();
    } else {
        g->set_current_state(new Global_map(Fractions, World_map, A_Creator, country));
        g->global_map();
    }// перекинуть в Move::set_next_state
    delete this;
}

void State::skip(Game* g) {
    g->current_state->set_next_state(g);
    delete this;
}

void State::finish() {
    World_map.Print_Map(Fractions);
    cout << Fractions[country]->name << " win" << endl;
    delete this;
}

Game::Game(vector<Fraction*>& Fr, Map& W_m, ArmyCreator& A_c, int c) {
    current_state = new Start(Fr, W_m, A_c, c);
}

void Game::set_current_state(State* s) {
    current_state = s;
}

void Game::start() {
    current_state->start(this);
}

void Game::global_map() {
    current_state->global_map(this);
}

void Game::create() {
    current_state->create(this);
}

void Game::move(){
    current_state->move(this);
}

void Game::skip(){
    current_state->skip(this);
}

void Game::finish(){
    current_state->finish();
}