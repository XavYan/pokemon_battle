#include "pokemonDataset.hpp"

// Pikachu
Pikachu::Pikachu (std::string mote, unsigned level, Nature nature, Stats ivs, Stats evs) :
        Pokemon("Pikachu", mote, {35,55,30,50,40,90}, level, ELECTRIC, NOTYPE, nature, ivs, evs)
{}

Pikachu::Pikachu (unsigned level, Nature nature, Stats ivs, Stats evs) :
        Pokemon("Pikachu", "Pikachu", {35,55,30,50,40,90}, level, ELECTRIC, NOTYPE, nature, ivs, evs)
{}

// Charmander
Charmander::Charmander (std::string mote, unsigned level, Nature nature, Stats ivs, Stats evs) :
        Pokemon("Charmander", mote, {39,52,43,60,50,65}, level, FIRE, NOTYPE, nature, ivs, evs)
{}

Charmander::Charmander (unsigned level, Nature nature, Stats ivs, Stats evs) :
        Pokemon("Charmander", "Charmander", {39,52,43,60,50,65}, level, FIRE, NOTYPE, nature, ivs, evs)
{}