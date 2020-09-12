#pragma once

#include <string>
#include <vector>
#include <random>

#include <basicStructures.hpp>
#include <movement.hpp>

class Movement;

class Pokemon {
protected:
    std::string specie_;
    std::string mote_;

    unsigned level_;

    int type1_;
    int type2_;

    Nature nature_;

    // Stats
    Stats stats_;

    int actualHP_;

    // IVs
    Stats ivs_;

    // EVs
    Stats evs_;

    // Moves
    std::vector<Movement*> moves_;
    unsigned movesCount_;

    // Stage points
    StagePoints stagePoints_;

public:

    Pokemon ();

    explicit Pokemon (std::string specie, std::string mote, Stats baseStats, unsigned level, int type1,
             int type2 = NOTYPE, Nature nature = natureEffectiveness[rand() % 25], Stats ivs = getRandomIVs(), Stats evs = getRandomEVs());

    explicit Pokemon (std::string specie, Stats stats, unsigned level, int type1,
             int type2 = NOTYPE, Nature nature = natureEffectiveness[rand() % 25], Stats ivs = getRandomIVs(), Stats evs = getRandomEVs());

    Pokemon (const Pokemon& pokemon);

    virtual ~Pokemon();

    std::string specie () const;
    std::string mote () const;

    unsigned level () const;

    int type1 () const;
    int type2 () const;
 
    Nature nature () const;

    unsigned actualHP () const;
    unsigned maxHP () const;

    Stats stats() const;

    unsigned atk () const;
    unsigned def () const;
    unsigned spatk () const;
    unsigned spdef () const;
    unsigned speed () const;

    int receiveDamage (Pokemon*& enemy, const Movement* move);

    unsigned movesCount () const;
    Movement* getMove (unsigned pos) const; 

    void setAllMoves (Movement* move1, Movement* move2 = nullptr, Movement* move3 = nullptr, Movement* move4 = nullptr);
    void replaceMove (unsigned oldMovePosition, Movement* newMove);
    void addMove (Movement* newMove); // Only in case we dont have 4 moves already
    void removeMove (unsigned movePosition);

    void addStagePoints (int stat, int points);
    void resetStagePoints ();

    bool isAlive() const;

private:

    unsigned calculateHPStatValue () const;
    unsigned calculateStatValue (int stat) const;
};