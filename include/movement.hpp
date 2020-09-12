#pragma once

#include <basicStructures.hpp>
#include <languageManager.hpp>
#include <string>

class Pokemon;
class Battle;

class Movement {
protected:
    std::string baseName_;
    std::string description_;

    int type_;

    unsigned category_;

    unsigned power_;

    unsigned accuracy_;

    unsigned pp_;

    int priority_;

    bool contact_;

public:
    Movement ();

    explicit Movement (std::string baseName, int type, unsigned category, unsigned power, unsigned pp,
             unsigned accuracy = 100, int priority = 0, bool contact = true);

    Movement (const Movement& move);

    virtual ~Movement();

    std::string name () const;
    std::string description () const;

    void setDescription (std::string description);

    int type () const;

    unsigned category () const;
    unsigned power () const;
    unsigned accuracy() const;
    unsigned pp () const;
    int priority () const;
    
    bool hasContact () const;

    virtual int useMove (Pokemon*& source, Pokemon*& target);
    virtual void applyEffect (Pokemon*& source, Pokemon*& target);

    virtual int getAffectedStat () const = 0;
};