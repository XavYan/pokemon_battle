#include <pokemon.hpp>

Pokemon::Pokemon () {
    specie_ = "NOPOKEMON";
    mote_ = specie_;
    stats_ = Stats{};
    level_ = 0;
    type1_ = NOTYPE;
    type2_ = NOTYPE;
    nature_ = Nature{};
    ivs_ = Stats{};
    evs_ = Stats{};

    actualHP_ = 0;
    movesCount_ = 0;
}

Pokemon::Pokemon (std::string specie, std::string mote, Stats stats, unsigned level, int type1, int type2, Nature nature, Stats ivs, Stats evs) {
    specie_ = specie;
    mote_ = mote;
    stats_ = stats;
    level_ = level;
    type1_ = type1;
    type2_ = type2;
    nature_ = nature;
    ivs_ = ivs;
    evs_ = evs;

    actualHP_ = calculateHPStatValue();

    // We always have 4 movements at max
    moves_.resize(4);
    movesCount_ = 0;
}

Pokemon::Pokemon (std::string specie, Stats baseStats, unsigned level, int type1, int type2, Nature nature, Stats ivs, Stats evs) {
    specie_ = specie;
    mote_ = specie_;
    stats_ = baseStats;
    level_ = level;
    type1_ = type1;
    type2_ = type2;
    nature_ = nature;
    ivs_ = ivs;
    evs_ = evs;

    actualHP_ = calculateHPStatValue();

    // We always have 4 movements at max
    moves_.resize(4);
    movesCount_ = 0;
}

Pokemon::Pokemon (const Pokemon& pokemon) {
    specie_ = pokemon.specie_;
    mote_ = pokemon.mote_;
    stats_ = pokemon.stats_;
    level_ = pokemon.level_;
    type1_ = pokemon.type1_;
    type2_ = pokemon.type2_;
    nature_ = pokemon.nature_;
    ivs_ = pokemon.ivs_;
    evs_ = pokemon.evs_;

    actualHP_ = pokemon.actualHP_;

    moves_ = pokemon.moves_;
    movesCount_ = pokemon.movesCount_;
}

Pokemon::~Pokemon () {
    moves_.clear();
}

std::string Pokemon::specie () const {
    return specie_;
}

std::string Pokemon::mote () const {
    return mote_;
}

unsigned Pokemon::level () const {
    return level_;
}

int Pokemon::type1 () const {
    return type1_;
}

int Pokemon::type2 () const {
    return type2_;
}

Nature Pokemon::nature () const {
    return nature_;
}

unsigned Pokemon::actualHP () const {
    return actualHP_;
}

unsigned Pokemon::maxHP () const {
    return calculateHPStatValue();
}

Stats Pokemon::stats() const {
    return stats_;
}

unsigned Pokemon::atk () const {
    if (stagePoints_.atk == 0) {
        return calculateStatValue(ATK);
    } else if (stagePoints_.atk < 0) {
        return calculateStatValue(ATK) * 2.0/(2.0 + (float)(stagePoints_.atk * (-1)));
    } else {
        return calculateStatValue(ATK) * (1.0 + (float)stagePoints_.atk/2.0);
    }
}

unsigned Pokemon::def () const {
    if (stagePoints_.def == 0) {
        return calculateStatValue(DEF);
    } else if (stagePoints_.def < 0) {
        return calculateStatValue(DEF) * 2.0/(2.0 + (float)stagePoints_.def * (-1));
    } else {
        return calculateStatValue(DEF) * (1.0 + (float)stagePoints_.def/2.0);
    }
}

unsigned Pokemon::spatk () const {
    if (stagePoints_.spatk == 0) {
        return calculateStatValue(SPATK);
    } else if (stagePoints_.spatk < 0) {
        return calculateStatValue(SPATK) * 2.0/(2.0 + (float)stagePoints_.spatk * (-1));
    } else {
        return calculateStatValue(SPATK) * (1.0 + (float)stagePoints_.spatk/2.0);
    }
}

unsigned Pokemon::spdef () const {
    if (stagePoints_.spdef == 0) {
        return calculateStatValue(SPDEF);
    } else if (stagePoints_.spdef < 0) {
        return calculateStatValue(SPDEF) * 2.0/(2.0 + (float)stagePoints_.spdef * (-1));
    } else {
        return calculateStatValue(SPDEF) * (1.0 + (float)stagePoints_.spdef/2.0);
    }
}

unsigned Pokemon::speed () const {
    if (stagePoints_.speed == 0) {
        return calculateStatValue(SPEED);
    } else if (stagePoints_.speed < 0) {
        return calculateStatValue(SPEED) * 2.0/(2.0 + (float)stagePoints_.speed * (-1));
    } else {
        return calculateStatValue(SPEED) * (1.0 + (float)stagePoints_.speed/2.0);
    }
}

int Pokemon::receiveDamage (Pokemon*& enemy, const Movement* move) {
    int effectiveAttack = ( move->category() == PHYSICAL ? enemy->atk() : enemy->spatk() );
    int effectiveDefense = ( move->category() == PHYSICAL ? def() : spdef() );

    float STAB = ( move->type() == enemy->type1() || move->type() == enemy->type2() ? 1.5 : 1);
    float type = typeEffectiveness[move->type()][type1()] * (type2() != NOTYPE ? typeEffectiveness[move->type()][type2()] : 1);

    float modifiers = STAB * type;

    int damage = ((2*enemy->level()/5 + 2) * move->power() * effectiveAttack/effectiveDefense) / 50 + 2;
    damage = damage * modifiers;

    // Decrementing hp
    actualHP_ -= damage;

    return damage;
}

unsigned Pokemon::movesCount () const {
    return movesCount_;
}

Movement* Pokemon::getMove (unsigned pos) const {
    if (pos+1 > movesCount_ || pos > 4) {
        // error
    } else {
        return moves_[pos];
    }
}

void Pokemon::setAllMoves (Movement* move1, Movement* move2, Movement* move3, Movement* move4) {
    delete moves_[0];
    delete moves_[1];
    delete moves_[2];
    delete moves_[3];

    moves_[0] = move1;
    moves_[1] = move2;
    moves_[2] = move3;
    moves_[3] = move4;

    movesCount_ = 0;
    for (Movement* move : moves_) {
        if (move != nullptr) {
            movesCount_++;
        }
    }
}

void Pokemon::replaceMove (unsigned oldMovePosition, Movement* newMove) {
    if (oldMovePosition+1 <= movesCount_) {
        delete moves_[oldMovePosition];
        moves_[oldMovePosition] = newMove;
    } else {
        // error
    }
}

void Pokemon::addMove (Movement* newMove) { // Only in case we dont have 4 moves already
    if (movesCount_ < MAX_MOVE_COUNT) {
        moves_[movesCount_++] = newMove;
    }
}

void Pokemon::removeMove (unsigned movePosition) {
    if (movesCount_ > 0) {
        delete moves_[movePosition];
        moves_[movePosition] = nullptr;
        movesCount_--;
    }
}

bool Pokemon::isAlive () const {
    return actualHP_ > 0;
}

unsigned Pokemon::calculateHPStatValue () const {
    return ((2 * stats_.hp + ivs_.hp + evs_.hp/4) * level_)/100 + level_ + 10;
}

unsigned Pokemon::calculateStatValue (int stat) const {
    unsigned base, iv, ev;
    float nature;
    
    switch (stat) {
        case ATK: {
            base = stats_.atk;
            iv = ivs_.atk;
            ev = evs_.atk;
            nature = nature_.atk;
            break;
        }
        case DEF: {
            base = stats_.def;
            iv = ivs_.def;
            ev = evs_.def;
            nature = nature_.def;
            break;
        }
        case SPATK: {
            base = stats_.spatk;
            iv = ivs_.spatk;
            ev = evs_.spatk;
            nature = nature_.spatk;
            break;
        }
        case SPDEF: {
            base = stats_.spdef;
            iv = ivs_.spdef;
            ev = evs_.spdef;
            nature = nature_.spdef;
            break;
        }
        case SPEED: {
            base = stats_.speed;
            iv = ivs_.speed;
            ev = evs_.speed;
            nature = nature_.speed;
            break;
        }
        default: {
            // TODO: Error
        }
    }
    return (((2*base + iv + ev/4) * level_)/100 + 5) * nature;
}

void Pokemon::addStagePoints (int stat, int points) {
    switch (stat) {
        case ATK: {
            if (points > 0) {
                if (stagePoints_.atk < 6) {
                    stagePoints_.atk += points;
                    if (stagePoints_.atk > 6) stagePoints_.atk = 6;
                }
            } else if (points < 0) {
                if (stagePoints_.atk > -6) {
                    stagePoints_.atk += points;
                    if (stagePoints_.atk < -6) stagePoints_.atk = -6;
                }
            }
            break;
        }
        case DEF: {
            if (points > 0) {
                if (stagePoints_.def < 6) {
                    stagePoints_.def += points;
                    if (stagePoints_.def > 6) stagePoints_.def = 6;
                }
            } else if (points < 0) {
                if (stagePoints_.def > -6) {
                    stagePoints_.def += points;
                    if (stagePoints_.def < -6) stagePoints_.def = -6;
                }
            }
            break;
        }
        case SPATK: {
            if (points > 0) {
                if (stagePoints_.spatk < 6) {
                    stagePoints_.spatk += points;
                    if (stagePoints_.spatk > 6) stagePoints_.spatk = 6;
                }
            } else if (points < 0) {
                if (stagePoints_.spatk > -6) {
                    stagePoints_.spatk += points;
                    if (stagePoints_.spatk < -6) stagePoints_.spatk = -6;
                }
            }
            break;
        }
        case SPDEF: {
            if (points > 0) {
                if (stagePoints_.spdef < 6) {
                    stagePoints_.spdef += points;
                    if (stagePoints_.spdef > 6) stagePoints_.spdef = 6;
                }
            } else if (points < 0) {
                if (stagePoints_.spdef > -6) {
                    stagePoints_.spdef += points;
                    if (stagePoints_.spdef < -6) stagePoints_.spdef = -6;
                }
            }
            break;
        }
        case SPEED: {
            if (points > 0) {
                if (stagePoints_.speed < 6) {
                    stagePoints_.speed += points;
                    if (stagePoints_.speed > 6) stagePoints_.speed = 6;
                }
            } else if (points < 0) {
                if (stagePoints_.speed > -6) {
                    stagePoints_.speed += points;
                    if (stagePoints_.speed < -6) stagePoints_.speed = -6;
                }
            }
            break;
        }
        default: {
            // error
        }
    }
}

void Pokemon::resetStagePoints () {
    stagePoints_ = {0,0,0,0,0};
}