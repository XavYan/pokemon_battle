#include <movement.hpp>
#include <pokemon.hpp>

#include <iostream>

class QuickAttack : public Movement {
public:
    QuickAttack() : Movement("quickAttack", NORMAL, PHYSICAL, 40, 30, 100, 1) {}

    int getAffectedStat () const {
        return UNKNOWN;
    }
};

class Scratch : public Movement {
public:
    Scratch() : Movement("scratch", NORMAL, PHYSICAL, 40, 35, 100) {}

    int getAffectedStat () const {
        return UNKNOWN;
    }
};

class ThunderShock : public Movement {
public:
    ThunderShock() : Movement("thunderShock", ELECTRIC, SPECIAL, 40, 30, 100) {}

    int getAffectedStat () const {
        return UNKNOWN;
    }
};

class Ember : public Movement {
public:
    Ember() : Movement("ember", FIRE, SPECIAL, 40, 25, 100) {}

    int getAffectedStat () const {
        return UNKNOWN;
    }
};

class Growl : public Movement {
public:
    Growl() : Movement("growl", NORMAL, STATUS, 0, 40) {}
    
    void applyEffect(Pokemon*& source, Pokemon*& target) {
        target->addStagePoints(ATK, -1);
    }

    int getAffectedStat () const {
        return ATK;
    }
};

class Leer : public Movement {
public:
    Leer() : Movement("leer", NORMAL, STATUS, 0, 30) {}

    void applyEffect (Pokemon*& source, Pokemon*& target) {
        target->addStagePoints(DEF, -1);
    }

    int getAffectedStat () const {
        return DEF;
    }
};