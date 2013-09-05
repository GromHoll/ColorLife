#include "gui.h"
#include "include\libtcod.hpp"

#include <stdlib.h>
#include <Windows.h>
#include <time.h>

const int delay = 200;


void startGame(LifeMap& gameMap) {
    int step;
        
    for(step = 0; gameMap.isChange(); step++) {
        gamePlay::showGamePlayInfo(step, gameMap);
        drawMap(gameMap);
        TCODConsole::root->flush();

        gameMap.nextStep();
        Sleep(delay);

        TCOD_key_t key = TCODConsole::checkForKeypress();
        if(key.c == 'p') {
            gamePlay::showPause();
            TCODConsole::waitForKeypress(true);
        }
        else {
            if(key.vk == TCODK_ESCAPE)
                break;
        }
    }
    
    if(!gameMap.isChange()) {
        gamePlay::showFinish();
        TCODConsole::waitForKeypress(true);
    }

    gamePlay::showScore(step-1, gameMap);
    while(TCODConsole::waitForKeypress(true).vk != TCODK_ESCAPE) {}
}

void prepareFild() {
    drawGameFrame();

    char color = LifeMap::WHITE_CELL;
    gameMenu::drawGameHelp(color);

    LifeMap gameMap;

    int xPos = LifeMap::widht/2;
    int yPos = LifeMap::height/2;

    while(true) {
        drawMap(gameMap, xPos, yPos, color);
        TCODConsole::root->flush();
        TCOD_key_t key = TCODConsole::waitForKeypress(true);

        switch(key.c) {
            case ' ': gameMap.set(xPos, yPos, color);
                break;
            case 's': // SAVE
                break;
            case 'q': // QUIT DIALOG
                return;
            case 'w': color = LifeMap::WHITE_CELL;
                      gameMenu::drawGameHelp(color);
                break;
            case 'r': color = LifeMap::RED_CELL;
                      gameMenu::drawGameHelp(color);
                break;
            case 'g': color = LifeMap::GREEN_CELL;
                      gameMenu::drawGameHelp(color);
                break;
            case 'b': color = LifeMap::BLUE_CELL;
                      gameMenu::drawGameHelp(color);
                break;
            default:
                switch(key.vk) {
                    case TCODK_ENTER: startGame(gameMap);
                        return;
                    case TCODK_LEFT: xPos = (xPos+LifeMap::widht-1)%LifeMap::widht;
                        break;
                    case TCODK_UP: yPos = (yPos+LifeMap::height-1)%LifeMap::height;
                        break;
                    case TCODK_DOWN: yPos = (yPos+1)%LifeMap::height;
                        break;
                    case TCODK_RIGHT: xPos = (xPos+1)%LifeMap::widht;
                        break;
                    default:
                        break;
                }
        }
    }
}

void loadGame() {

}

int main() {
    initGraphic();
    while(true) {
        int res = MainMenu::showStandartMainMenu();
        switch(res) {
            case MainMenu::NEW_GAME_OPTION: 
                prepareFild();
                break;
            case MainMenu::LOAD_OPTION: 
                loadGame();
                break;
            case MainMenu::EXIT_OPTION: 
                exit(0);        
        }
    }
    return 1;
}