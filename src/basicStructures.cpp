#include <basicStructures.hpp>

Stats getRandomIVs () {
    Stats result {};

    result.hp = rand() % MAX_IV;
    result.atk = rand() % MAX_IV;
    result.def = rand() % MAX_IV;
    result.spatk = rand() % MAX_IV;
    result.spdef = rand() % MAX_IV;
    result.speed = rand() % MAX_IV;

    return result;
}

Stats getRandomEVs () {
    Stats result {};

    result.hp = rand() % MAX_EFFORT;
    result.atk = rand() % MAX_EFFORT;
    result.def = rand() % MAX_EFFORT;
    result.spatk = rand() % MAX_EFFORT;
    result.spdef = rand() % MAX_EFFORT;
    result.speed = rand() % MAX_EFFORT;

    return result;
}

std::string statToString (int stat) {
    switch (stat) {
        case ATK: {
            return LanguageManager::instance()->getText("atk");
            break;
        }
        case DEF: {
            return LanguageManager::instance()->getText("def");
            break;
        }
        case SPATK: {
            return LanguageManager::instance()->getText("spdef");
            break;
        }
        case SPDEF: {
            return LanguageManager::instance()->getText("spatk");
            break;
        }
        case SPEED: {
            return LanguageManager::instance()->getText("speed");
            break;
        }
        default: {
            // error
        }
    }
}