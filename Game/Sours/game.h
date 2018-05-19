#pragma once
#include "crusade.h"
struct State;

void help();

struct Game {
    Game(vector<Fraction*>& Fr, Map& W_m, ArmyCreator& A_c, int c);
    State* current_state;
    void set_current_state(State* s);
    void start();
    void global_map();
    void create();
    void move();
    void skip();
    void finish();
};

struct State {
    State(vector<Fraction*>& Fr, Map& W_m, ArmyCreator& A_c, int c):Fractions(Fr), World_map(W_m), A_Creator(A_c), country(c){}
    vector<Fraction*>& Fractions;
    Map World_map;
    ArmyCreator A_Creator;
    int country;
    virtual void set_next_state(Game* g) = 0;
    virtual void start(Game* g);
    virtual void global_map(Game* g);
    virtual void create(Game* g);
    virtual void move(Game* g);
    virtual void skip(Game* g);
    virtual void finish();
};

struct Start: public State {
    Start(vector<Fraction*>& Fr, Map& W_m, ArmyCreator& A_c, int c):State(Fr, W_m, A_c, c){}
    void set_next_state(Game* g);
};

struct Global_map: public State {
    Global_map(vector<Fraction*>& Fr, Map& W_m, ArmyCreator& A_c, int c):State(Fr, W_m, A_c, c){};
    void set_next_state(Game* g);
};

struct Create: public State {
    Create(vector<Fraction*>& Fr, Map& W_m, ArmyCreator& A_c, int c):State(Fr, W_m, A_c, c){};
    void set_next_state(Game* g);
};

struct Move: public State {
    Move(vector<Fraction*>& Fr, Map& W_m, ArmyCreator& A_c, int c):State(Fr, W_m, A_c, c){};
    void set_next_state(Game* g);
};

struct Skip: public State {
    Skip(vector<Fraction*>& Fr, Map& W_m, ArmyCreator& A_c, int c):State(Fr, W_m, A_c, c){};
    void set_next_state(Game* g);
};

struct Finish: public State {
    Finish(vector<Fraction*>& Fr, Map& W_m, ArmyCreator& A_c, int c):State(Fr, W_m, A_c, c){};
    void set_next_state(Game* g);
};
