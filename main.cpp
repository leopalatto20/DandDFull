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
    } while(buildOption < 1 || buildOption> 3);

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
    if(!player.loadStats()) {
        cerr << "No se pudieron cargar las estadisticas de tu personaje.\n";
        return 1;
    }
    cout << endl << endl;

    cout << "Estas listo para empezar a elegir tus hechizos.\n";
    cout << endl << endl;

    if(!buySpells(player, spellShop)) {
        cerr << "No se pudieron comprar tus hechizos. \n";
        return 1;
    }

    player.showInfo();
    spellShop.deleteShop(); //Borrar tienda de hechizos porque ya no se va a usar
    cout << "Recorrido DFS de la dungeon desde el cuarto 0:\n";
    if(!dungeon.DFS(0)) {
        cerr << "No se pudo completar el recorrido DFS.\n";
        return 1;
    }
    cout << endl;
    cout << "Recordido BFS de la dungeon desde el cuarto 0: \n";
    if(!dungeon.BFS(0)) {
        cerr << "No se pudo completar el recorrido BFS.\n";
        return 1;
    }

    cout << endl << endl;

    unsigned int inicio, final;
    cout << "Elige una ruta.\n";
    do {
        cout << "Dame el cuarto inicial: \n";
        inicio = getNumericInput();
        cout << "Dame el cuarto final: \n";
        final = getNumericInput();
        if(final > dungeon.getSize() || inicio == final || inicio > dungeon.getSize())
            cerr << "Tus numeros son invalidos.\n";
    } while(final > dungeon.getSize() || inicio == final || inicio > dungeon.getSize());

    dungeon.printPath();
    if(!dungeon.createRoute(inicio, final)) {
        cout << "No existe una ruta de " << inicio << " a " << final << endl;
        return 1;
    }
    unsigned int monsterCounter(0);
    do {
        Room *current = dungeon.currentRoomPath();
        if(!current) {
            cerr << "No se pudo obtener el cuarto actual.\n";
            return 1;
        }
        if(monsterCounter > 0 && monsterCounter % 3 == 0) //el jugador se puede levelear cada 3 monstruos
            levelPlayerUp(player);
        cout << "Entrando a " << *current << endl;
        Monster currentMonster = current->monster;
        if(!fightMonster(player, currentMonster)) {
            cout << "Perdiste contra el monstruo " << currentMonster << endl << "Saliendo del programa.\n";
            player.showInfo();
            return 0;
        }
        cout << "Derrotaste al monstruo: " << currentMonster << endl << endl;;
        if(!player.addMonster(currentMonster)) {
            cerr << "No se pudo agregar al monstruo a tu catalogo.\n";
            return 1;
        }
        healPlayer(player);
        monsterCounter++;
    } while(dungeon.goForward());
    cout << "Terminaste tu ruta!!!.\n";
    player.showInfo();

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
    for(unsigned int i = 0; i < str.length(); i++) {
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
    cout << "\nEmpieza la pelea.\n\n";
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
        int dmg = d10Roll();
        cout << "\nAhora el monstruo te ataca y te hace " << dmg << " de danio.\n\n";
        player.setHp(player.getHp() - dmg);
        if(player.getHp() <= 0) {
            player.setHp(0);
            return false;
        }
    }
    return player.getHp() > 0; // no deberia de llegar a este punto pero manda advertencia cuando compilo
}

void healPlayer(Player &player) {
    int addHp = twoD20Roll();
    cout << "\nRecuperas " << addHp << " de vida antes de pelear contra el siguiente monstruo.\n";
    player.setHp(player.getHp() + addHp);
    if(player.getHp() > player.getMaxHp()) //su vida no puede superar la maxima
        player.setHp(player.getMaxHp());
    player.setMp(player.getMp() + 50);
}

void levelPlayerUp(Player &player) {
    int option;
    bool validOption = false;
    string optionStr;
    while(!validOption) {
        do {
            cout << "Llegaste a un punto seguro, puedes subir de nivel.\n"
                    "1. Aumentar tu vida maxima en 50 puntos.\n"
                    "2. Aumentar tu multiplicador de danio en 25%.\n";
            cin >> optionStr;
            if(!isValidNumber(optionStr))
                cout << "No es un número valido.";
        } while(!isValidNumber(optionStr));
        option = stoi(optionStr);
        if(option > 0 && option < 3)
            validOption = true;
    }
    switch(option) {
        case 1: {
            player.setMaxHp(player.getMaxHp() + 50);
            break;
        }
        case 2: {
            player.setDamageMultiplier(player.getDamageMultiplier() + 0.25);
            break;
        }
        default: {
            break;
        }
    }
}

int d10Roll() {
    return 1 + rand() % 10;
}
int twoD20Roll() {
    int num1 = 1 + rand() % 20;
    int num2 = 1 + rand() % 20;
    return num1 + num2;
}