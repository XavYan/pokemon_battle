#include <iostream>

#include <pokemon.hpp>
#include "datasets/pokemonDataset.hpp"
#include "datasets/movementDataset.hpp"
#include <battle.hpp>

int main (void) {

    Pokemon* pikachu = new Pikachu(5);

    pikachu->setAllMoves(new QuickAttack(), new ThunderShock(), new Growl());

    Pokemon* charmander = new Charmander("Dragoncito", 5);

    charmander->setAllMoves(new Scratch());

    std::string lang;
    do {
        std::cout << "Language (es o us ): ";
        std::cin >> lang;

        if (lang == "es") {
            Battle::instance()->setLanguage("es_ES");
        }
    } while (lang != "es" && lang != "us");

    Battle::instance()->start(pikachu, charmander);

    return 0;

}