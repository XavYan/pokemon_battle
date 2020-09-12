#include <movement.hpp>
#include <pokemon.hpp>

Movement::Movement () {
    baseName_ = "NOMOVE";
    description_ = "";
    type_ = NOTYPE;
    category_ = NONE;
    power_ = 0;
    accuracy_ = 0;
    pp_ = 0;
    priority_ = 0;
    contact_ = true;
}

Movement::Movement (std::string baseName, int type, unsigned category, unsigned power, unsigned pp, unsigned accuracy, int priority, bool contact) {
    baseName_ = baseName;
    description_ = "";
    type_ = type;
    category_ = category;
    power_ = power;
    accuracy_ = accuracy;
    pp_ = pp;
    priority_ = priority;
    contact_ = category_ == SPECIAL ? false : contact;
}

Movement::Movement (const Movement& move) {
    baseName_ = move.baseName_;
    description_ = move.description_;
    type_ = move.type_;
    category_ = move.category_;
    power_ = move.power_;
    accuracy_ = move.accuracy_;
    pp_ = move.pp_;
    priority_ = move.priority_;
    contact_ = move.contact_;
}

Movement::~Movement() = default;

std::string Movement::name () const {
    if (baseName_ != "NOMOVE")
        return LanguageManager::instance()->getText(baseName_);
    else
        return "NOMOVE";
}

std::string Movement::description () const {
    return description_;
}

void Movement::setDescription (std::string description) {
    description_ = description;
}

int Movement::type () const {
    return type_;
}

unsigned Movement::category () const {
    return category_;
}


unsigned Movement::power () const {
    return power_;
}


unsigned Movement::accuracy() const {
    return accuracy_;
}


unsigned Movement::pp () const {
    return pp_;
}

int Movement::priority () const {
    return priority_;
}
    
bool Movement::hasContact () const {
    return contact_;
}

int Movement::useMove (Pokemon*& source, Pokemon*& target) {
    int damage = 0;
    if (category() != STATUS) {
        damage = target->receiveDamage(source, this);
    }
    applyEffect(source, target);
    return damage;
}

void Movement::applyEffect (Pokemon*& source, Pokemon*& target) {
    // it depends on each movement
}