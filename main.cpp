#include <iostream>
#include "main.h"

using namespace std;

int main() {
    MonsterCatalogue catalogue;
    Dungeon dungeon;
    SpellShop spellShop;
    srand(time(0));
    cout << "Crear catalogo...\n";
    if(!catalogue.loadFromCsv()) {
        cerr << "No se pudo crear el catalogo.\n";
        return 1;
    }
    cout << "Crear dungeon...\n";
    if(!dungeon.createDungeon("dungeon.txt")) {
        cerr << "No se pudo crear la dungeon.\n";
        return 1;
    }
    for(unsigned int c = 0; c < dungeon.getSize(); c++) {
        Monster *pMonster = nullptr, copyMonster;

        pMonster = catalogue.getMonster();
        if(!pMonster) {
            cerr << "No se pudo obtener un monstruo\n";
            return 1;
        }
        copyMonster = *pMonster;
        if(!dungeon.createRoom(c, copyMonster))
            return 1;
    }
    if(!spellShop.loadSpells()) {
        cerr << "No se pudo cargar la tienda de hechizos.\n";
        return 1;
    }
    catalogue.print();
    dungeon.printRooms();
    catalogue.deleteCatalogue(); //Borrar catalogo porque ya no lo vamos a usar

    string playerName;
    cout << "\n\nIngresa el nombre de tu personaje: ";
    getline(cin, playerName);

    unsigned int buildOption;
    cout << "Escoge tu clase.\n"
                "1. Fuerza: 75HP|5 Hechizos.\n"
                    "2. Destreza: 60HP|6 hechizos\n"
                    "3. Inteligencia: 45HP|10 hechizos\n";
    do {
        buildOption = getNumericInput();
        if(buildOption < 1 || buildOption> 3)
            cerr << "Tu entrada no esta dentro de los limites.\n";
    }while(buildOption < 1 || buildOption> 3);

    string buildStr;
    switch(buildOption) {
        case 1: {
            buildStr = "strength";
            break;
        }
        case 2: {
            buildStr = "dexterity";
            break;
        }
        case 3: {
            buildStr = "intelligence";
            break;
        }
    }
    Player player(playerName, buildStr);
    cout << "Cargando las estadisticas de tu personaje.\n";
    if(!player.loadStats())
        return 1;
    cout << endl << endl;

    cout << "Estas listo para empezar a elegir tus hechizos.\n";
    cout << endl << endl;

    if(!buySpells(player, spellShop))
        return 1;

    player.showInfo();

    cout << "Recorrido DFS de la dungeon desde el cuarto 0:\n";
    dungeon.DFS(0);

    cout << endl << endl;

    Monster *pMonster = dungeon.getMonster(0), copyMonster;
    if(!pMonster) {
        cerr << "No se pudo obtener un monstruo de la dungeon.\n";
        return 1;
    }
    copyMonster = *pMonster;
    if(!fightMonster(player, copyMonster)) {
        cout << "Perdiste contra el monstruo: " << copyMonster << endl;
    }
    cout << "Derrotaste al monstruo: " << copyMonster << endl << "Saliendo del programa.\n";
    player.addMonster(copyMonster);
    player.showInfo();

    unsigned int inicio, final;
    cout << "Elige una ruta.\n";
    do {
        cout << "Dame el cuarto inicial: ";
        cin >> inicio;
        cout << "Dame el cuarto final: ";
        cin >> final;
    } while(final > dungeon.getSize() || inicio == final);

    dungeon.printPath();
    if(!dungeon.createRoute(inicio, final)) {
        cout << "No existe una ruta de " << inicio << " a " << final << endl;
        return 1;
    }
    return 0;
}

unsigned int getNumericInput() {
    bool validOption = false;
    string optionStr;
    while(!validOption) {
        do {
            cout << "Ingresa un numero: ";
            cin >> optionStr;
            if(!isValidNumber(optionStr))
                cout << "No es un número valido.\n";
        } while(!isValidNumber(optionStr));
        validOption = true;
    }
    return stoi(optionStr);
}

bool isValidNumber(const string &str) {
    for(int i = 0; i < str.length(); i++) {
        if(!isdigit(str[i]))
            return false;
    }
    return true;
}

bool buySpells(Player &player, SpellShop &spellShop) {
    int count = 0;
    while(count < player.getMaxSpells()) {
        cout << "Escoge tus hechizos.\n";
        spellShop.printInOrder();
        unsigned int option = getNumericInput();

        Spell *pSpell = nullptr, copySpell;
        pSpell = spellShop.buyByNumber(option);
        if(!pSpell)
            cerr << "Ese hechizo no existe.\n";
        else {
            copySpell = *pSpell;
            if(!spellShop.deleteSpell(copySpell))
                return false;
            if(player.addSpell(copySpell)) {
                count++;
                cout << "Agregando hechizo " << copySpell << "\n\n";
            }
        }
    }
    return true;
}

bool fightMonster(Player &player, Monster &monster) {
    cout << "Peleando contra: " << monster << " con HP: " << monster.getHp();
    cout << "\nEmpieza la pelea.\n";
    while(player.getHp() > 0 && monster.getHp() > 0) {
        int spellChoice, damage;
        string spellChoiceStr;
        bool validSpell = false;
        cout << "Tienes " << player.getHp() << " puntos de vida.\n";
        cout << "Tienes " << player.getMp() << "MP.\n";
        while(!validSpell) {
            do {
                player.showSpells();
                cout << "0. Usar hechizo default.\n\n";
                cout << "Escoge uno de tus hechizos: ";
                cin >> spellChoiceStr;
                if(!isValidNumber(spellChoiceStr))
                    cout << "No es un numero valido";
            } while(!isValidNumber(spellChoiceStr));
            spellChoice = stoi(spellChoiceStr);
            damage = player.getSpellDamage(spellChoice);
            if(damage <= 0)
                cout << "No puedes usar ese hechizo.\n";
            else
                validSpell = true;
        }
        int newDamage = damage * player.getDamageMultiplier();
        cout << "\nLe haces " << newDamage << " de danio al monstruo.\n";
        monster.setHp(monster.getHp() - newDamage);

        if(monster.getHp() <= 0) {
            monster.setHp(0);
            return true;
        }
        cout << monster << " HP: " << monster.getHp();
        cout << "\nAhora el monstruo te ataca y te hace 20 de danio.\n";
        player.setHp(player.getHp() - 20);
        if(player.getHp() <= 0) {
            player.setHp(0);
            return false;
        }
    }
    return player.getHp() > 0; // no deberia de llegar a este punto pero manda advertencia cuando compilo
}
