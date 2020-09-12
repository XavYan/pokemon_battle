#include <battle.hpp>

Battle* Battle::instance_ = nullptr;
bool Battle::battle_ = false;

Battle::Battle () {}

Battle::~Battle () {}

int Battle::start (Pokemon*& p1, Pokemon*& p2) {

    initializeBattle(p1,p2);

    int option;
    do {
        std::cout << formatString(LanguageManager::instance()->getText("turn"), std::string("turn=") + std::to_string(turn_ + 1)) << '\n';
        showMenu(p1);
        std::cin >> option;
        if (option == 1) {
            showMovementMenu (p1);
            int move;
            std::cin >> move;
            beginTurn (p1->getMove(move-1), getRivalRandomMove(p2));
        }
        fflush(stdin);
    } while (!hasToFinish() && option != 2);

    if (option != 2) declareVictory();
    else {
        std::cout << formatString(LanguageManager::instance()->getText("leftBattle")) << '\n';
    }

    cleanBattle(p1,p2);

    return 0;
}

void Battle::setLanguage (std::string lang) {
    LanguageManager::instance()->changeLanguage(lang);
}

Battle* Battle::instance () {
    if (!instance_) {
        instance_ = new Battle ();
    }
    return instance_;
}

void Battle::initializeBattle (Pokemon*& p1, Pokemon*& p2) {
    srand(time(NULL));

    p1->resetStagePoints();
    p2->resetStagePoints();

    p1_ = p1;
    p2_ = p2;

    turn_ = 0;
}

void Battle::cleanBattle (Pokemon*& p1, Pokemon*& p2) {
    p1->resetStagePoints();
    p2->resetStagePoints();

    p1_ = nullptr;
    p2_ = nullptr;

    battle_ = true;
}

void Battle::beginTurn (Movement* allyMove, Movement* enemyMove) {

    if (allyMove->priority() > enemyMove->priority()) {

        computeTurn(p1_, p2_, allyMove, enemyMove);

    } else if (allyMove->priority() < enemyMove->priority()) {
        
        computeTurn(p2_, p1_, enemyMove, allyMove);

    } else {
        if (p1_->speed() > p2_->speed()) {
            
            computeTurn(p1_, p2_, allyMove, enemyMove);

        } else if (p1_->speed() < p2_->speed()) {
            
            computeTurn(p2_, p1_, enemyMove, allyMove);

        } else {
            // Random selection
            int random = rand() % 2;
            if (random == 0) {
                
                computeTurn(p1_, p2_, allyMove, enemyMove);

            } else {
                
                computeTurn(p2_, p1_, enemyMove, allyMove);
                
            }
        }
    }

    // Next turn
    turn_++;
}

bool Battle::hasToFinish () const {
    return !p1_->isAlive() || !p2_->isAlive();
}

void Battle::showMenu (Pokemon*& p) const {

    std::cout << formatString(LanguageManager::instance()->getText("healthStatus"), "mote=" + p1_->mote(), "actualLife=" + std::to_string(p1_->actualHP()), "totalLife=" + std::to_string(p1_->maxHP())) << '\n';
    std::cout << formatString(LanguageManager::instance()->getText("healthStatus"), "mote=" + p2_->mote(), "actualLife=" + std::to_string(p2_->actualHP()), "totalLife=" + std::to_string(p2_->maxHP())) << '\n';

    std::cout << formatString(LanguageManager::instance()->getText("mainMenu"), "mote=" + p->mote()) << '\n';
    std::cout << formatString(LanguageManager::instance()->getText("fightMenuOption")) << '\n';
    std::cout << formatString(LanguageManager::instance()->getText("leaveMenuOption")) << '\n';
}

void Battle::showMovementMenu (Pokemon*& p) const {
    if (p->movesCount() > 0) {
        std::cout << formatString(LanguageManager::instance()->getText("movesAvailable")) << '\n';
        for (unsigned i = 0; i < p->movesCount(); i++) {
            std::cout << formatString(LanguageManager::instance()->getText("moveOption"), "optionID=" + std::to_string(i+1), "move=" + p->getMove(i)->name()) << ' ';
        }
        std::cout << '\n';
    } else {
        std::cout << formatString(LanguageManager::instance()->getText("noMoves")) << '\n';
    }
}

Movement* Battle::getRivalRandomMove (Pokemon*& p) const {
    return p->getMove(rand() % p->movesCount());
}

void Battle::declareVictory () {
    if (p1_->isAlive()) {
        std::cout << formatString(LanguageManager::instance()->getText("victory"), "mote=" + p1_->mote()) << '\n';
    } else if (p2_->isAlive()) {
        std::cout << formatString(LanguageManager::instance()->getText("victory"), "mote=" + p2_->mote()) << '\n';
    }
}

void Battle::showMoveText (Pokemon*& source, Pokemon*& target, Movement*& move, int damage) {

    std::cout << formatString(LanguageManager::instance()->getText("movementUsed"), "mote=" + source->mote(), "move=" + move->name()) << '\n';
    if (move->category() != STATUS) {
        std::cout << formatString(LanguageManager::instance()->getText("damageDone"), "dmgPoints=" + std::to_string(damage), "mote=" + target->mote()) << '\n';
    } else {
        std::string stat = statToString(move->getAffectedStat());
        std::cout << formatString(LanguageManager::instance()->getText("statFell"), "mote=" + target->mote(), "stat=" + stat) << '\n';
    }
}

void Battle::computeTurn (Pokemon*& priorityPokemon, Pokemon*& anotherPokemon, Movement*& priorityMove, Movement*& anotherMove) {
    int priorityDamage, anotherDamage;
    
    // Executing attacks
    priorityDamage = computeMovement(priorityPokemon, anotherPokemon, priorityMove);
    if (anotherPokemon->isAlive()) {
        anotherDamage = computeMovement(anotherPokemon, priorityPokemon, anotherMove);
    }

    // Showing results    
    showMoveText(priorityPokemon, anotherPokemon, priorityMove, priorityDamage);

    if (anotherPokemon->isAlive()) {
        showMoveText(anotherPokemon, priorityPokemon, anotherMove, anotherDamage);
    }
}

int Battle::computeMovement (Pokemon*& source, Pokemon*& target, Movement*& move) {    
    return move->useMove(source, target);
}