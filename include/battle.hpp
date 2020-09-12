#pragma once

#include <iostream>
#include <cstdio>
#include <random>

#include <basicStructures.hpp>
#include <pokemon.hpp>
#include <movement.hpp>
#include <languageManager.hpp>
#include <common.hpp>
#include <sstream>

class Movement;

class Battle {
private:

    static bool battle_;

    Pokemon* p1_;
    Pokemon* p2_;

    unsigned turn_;

    static Battle* instance_;

public:
    static Battle* instance ();

    ~Battle ();

    int start(Pokemon*& p1, Pokemon*& p2);

    void setLanguage (std::string lang);

private:
    Battle ();

    void initializeBattle (Pokemon*& p1, Pokemon*& p2);
    void cleanBattle (Pokemon*& p1, Pokemon*& p2);

    void computeTurn (Pokemon*& priorityPokemon, Pokemon*& anotherPokemon, Movement*& priorityMove, Movement*& anotherMove);
    int computeMovement (Pokemon*& source, Pokemon*& target, Movement*& move);

    void beginTurn (Movement* allyMove, Movement* enemyMove);

    bool hasToFinish () const;

    void showMenu (Pokemon*& p) const;
    void showMovementMenu (Pokemon*& p) const;
    void showMoveText (Pokemon*& source, Pokemon*& target, Movement*& move, int damage);
    void declareVictory ();

    Movement* getRivalRandomMove (Pokemon*& p) const;
};