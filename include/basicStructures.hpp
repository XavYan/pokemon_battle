#pragma once

#include <vector>
#include <random>
#include <string>
#include <languageManager.hpp>

// MAX values
const unsigned MAX_LEVEL = 100;
const unsigned MAX_EFFORT = 255;
const unsigned MAX_IV = 15;
const unsigned MAX_MOVE_COUNT = 4;

enum STATS {
    HP,
    ATK,
    DEF,
    SPATK,
    SPDEF,
    SPEED,
    UNKNOWN
};

enum TYPES {
    STEEL,
    WATER,
    BUG,
    DRAGON,
    ELECTRIC,
    GHOST,
    FIRE,
    FAIRY,
    ICE,
    FIGHTING,
    NORMAL,
    GRASS,
    PSYCHIC,
    ROCK,
    DARK,
    GROUND,
    POISON,
    FLYING,
    NOTYPE
};

enum NATURES {
    HARDY,
    LONELY,
    BRAVE,
    ADAMANT,
    NAUGHTY,
    BOLD,
    DOCILE,
    RELAXED,
    IMPISH,
    LAX,
    TIMID,
    HASTY,
    SERIOUS,
    JOLLY,
    NAIVE,
    MODEST,
    MILD,
    QUIET,
    BASHFUL,
    RASH,
    CALM,
    GENTLE,
    SASSY,
    CAREFUL,
    QUIRKY
};

struct Stats {
    unsigned hp;
    unsigned atk;
    unsigned def;
    unsigned spatk;
    unsigned spdef;
    unsigned speed;
};

struct StagePoints {
    int atk;
    int def;
    int spatk;
    int spdef;
    int speed; 
};

struct Nature {
    float atk;
    float def;
    float spatk;
    float spdef;
    float speed;
};

enum CATEGORY {
    PHYSICAL,
    SPECIAL,
    STATUS,
    NONE
};

// Types effectivities
const std::vector<std::vector<float>> typeEffectiveness = {
    { 0.5, 0.5, 1, 1, 0.5, 1, 0.5, 2, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1 },
    { 1, 0.5, 1, 0.5, 1, 1, 2, 1, 1, 1, 1, 0.5, 1, 2, 1, 2, 1, 1 },
    { 0.5, 1, 1, 1, 1, 0.5, 0.5, 0.5, 1, 0.5, 1, 2, 2, 1, 2, 1, 0.5, 0.5 },
    { 0.5, 1, 1, 2, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 2, 1, 0.5, 0.5, 1, 1, 1, 1, 1, 1, 0.5, 1, 1, 1, 0, 1, 2 },
    { 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 0, 1, 2, 1, 0.5, 1, 1, 1 },
    { 2, 0.5, 2, 0.5, 1, 1, 0.5, 1, 2, 1, 1, 2, 1, 0.5, 1, 1, 1, 1 },
    { 0.5, 1, 1, 2, 1, 1, 0.5, 1, 1, 2, 1, 1, 1, 1, 2, 1, 0.5, 1 },
    { 0.5, 0.5, 1, 2, 1, 1, 0.5, 1, 0.5, 1, 1, 2, 1, 1, 1, 2, 1, 2 },
    { 2, 1, 0.5, 1, 1, 0, 1, 0.5, 2, 1, 2, 1, 0.5, 2, 2, 1, 0.5, 0.5 },
    { 0.5, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0.5, 1, 1, 1, 1 },
    { 0.5, 2, 0.5, 0.5, 1, 1, 0.5, 1, 1, 1, 1, 0.5, 1, 2, 1, 2, 0.5, 0.5 },
    { 0.5, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 0.5, 1, 0, 1, 2, 1 },
    { 0.5, 1, 2, 1, 1, 1, 2, 1, 2, 0.5, 1, 1, 1, 1, 1, 0.5, 1, 2 },
    { 1, 1, 1, 1, 1, 2, 1, 0.5, 1, 0.5, 1, 1, 2, 1, 0.5, 1, 1, 1 },
    { 2, 1, 0.5, 1, 2, 1, 2, 1, 1, 1, 1, 0.5, 1, 2, 1, 1, 2, 0 },
    { 0, 1, 1, 1, 1, 0.5, 1, 2, 1, 1, 1, 2, 1, 0.5, 1, 0.5, 0.5, 1 },
    { 0.5, 1, 2, 1, 0.5, 1, 1, 1, 1, 2, 1, 2, 1, 0.5, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};

// Nature effectivities
const std::vector<Nature> natureEffectiveness = {
    { 1, 1, 1, 1, 1 },
    { 1.1, 0.9, 1, 1, 1 },
    { 1.1, 1, 1, 1, 0.9 },
    { 1.1, 1, 0.9, 1, 1 },
    { 1.1, 1, 1, 0.9, 1 },
    { 0.9, 1.1, 1, 1, 1 },
    { 1, 1, 1, 1, 1 },
    { 1, 1.1, 1, 1, 0.9 },
    { 1, 1.1, 0.9, 1, 1 },
    { 1, 1.1, 1, 0.9, 1 },
    { 0.9, 1, 1, 1, 1.1 },
    { 1, 0.9, 1, 1, 1.1 },
    { 1, 1, 1, 1, 1 },
    { 1, 1, 0.9, 1, 1.1 },
    { 1, 1, 1, 0.9, 1.1 },
    { 0.9, 1, 1.1, 1, 1 },
    { 1, 0.9, 1.1, 1, 1 },
    { 1, 1, 1.1, 1, 0.9 },
    { 1, 1, 1, 1, 1 },
    { 1, 1, 1.1, 0.9, 1 },
    { 0.9, 1, 1, 1.1, 1 },
    { 1, 0.9, 1, 1.1, 1 },
    { 1, 1, 1, 1.1, 0.9 },
    { 1, 1, 0.9, 1.1, 1 },
    { 1, 1, 1, 1, 1 }
};

Stats getRandomIVs ();

Stats getRandomEVs ();

std::string statToString (int stat);