#pragma once

#include <pokemon.hpp>

class Pikachu : public Pokemon {
public:
    Pikachu (std::string mote, unsigned level = 1, Nature nature = natureEffectiveness[rand() % 25], Stats ivs = getRandomIVs(), Stats evs = getRandomEVs());
    Pikachu (unsigned level = 1, Nature nature = natureEffectiveness[rand() % 25], Stats ivs = getRandomIVs(), Stats evs = getRandomEVs());
};

class Charmander : public Pokemon {
public:
    Charmander(std::string mote, unsigned level = 1, Nature nature = natureEffectiveness[rand() % 25], Stats ivs = getRandomIVs(), Stats evs = getRandomEVs());
    Charmander(unsigned level = 1, Nature nature = natureEffectiveness[rand() % 25], Stats ivs = getRandomIVs(), Stats evs = getRandomEVs());
};