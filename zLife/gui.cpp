#include "gui.h"
#include "include\libtcod.hpp"

void initGraphic() {
    TCODConsole::initRoot(windowWidht, windowHeight, "zLife");
    TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::white, TCODColor::black);
    TCODConsole::setColorControl(TCOD_COLCTRL_2, TCODColor::red,   TCODColor::black);
    TCODConsole::setColorControl(TCOD_COLCTRL_3, TCODColor::green, TCODColor::black);
    TCODConsole::setColorControl(TCOD_COLCTRL_4, TCODColor::blue,  TCODColor::black);
}

void drawGameFrame() {
    TCODConsole::root->clear();

    for(int i = 1; i < windowWidht - 1; i++) {
        TCODConsole::root->putChar(i, 0, GORIZONTAL_LINE);
        TCODConsole::root->putChar(i, LifeMap::height+1, GORIZONTAL_LINE);
        TCODConsole::root->putChar(i, windowHeight-1, GORIZONTAL_LINE);
    }

    for(int i = 1; i < windowHeight - 1; i++) {
        TCODConsole::root->putChar(0, i, VERTICAL_LINE);
        TCODConsole::root->putChar(LifeMap::widht+1, i, VERTICAL_LINE);
    }

    TCODConsole::root->putChar(0, 0, LEFT_TOP_LINE);
    TCODConsole::root->putChar(0, windowHeight-1, LEFT_BOTTOM_LINE);
    TCODConsole::root->putChar(windowWidht-1, 0, RIGHT_TOP_LINE);
    TCODConsole::root->putChar(windowWidht-1, windowHeight-1, RIGHT_BOTTOM_LINE);

    TCODConsole::root->putChar(0, LifeMap::height+1, LEFT_T_LINE);
    TCODConsole::root->putChar(windowWidht-1, LifeMap::height+1, RIGHT_T_LINE);

    TCODConsole::root->flush();
}

void drawMap(LifeMap& map) {

    TCODColor cellColor(0,0,0);
    for(int i = 0; i < LifeMap::widht; i++) {
        for(int j = 0; j < LifeMap::height; j++) {
            switch(map.getCell(i, j)) {
                case LifeMap::WHITE_CELL: cellColor.r = 255;
                                          cellColor.g = 255;
                                          cellColor.b = 255;
                                          break;
                case LifeMap::RED_CELL:   cellColor.r = 255;
                                          cellColor.g = 0;
                                          cellColor.b = 0;
                                          break;
                case LifeMap::GREEN_CELL: cellColor.r = 0;
                                          cellColor.g = 255;
                                          cellColor.b = 0;
                                          break;
                case LifeMap::BLUE_CELL:  cellColor.r = 0;
                                          cellColor.g = 0;
                                          cellColor.b = 255;
                                          break;
            }
            if(map.isLive(i, j))
                TCODConsole::root->putCharEx(1+i, 1+j, CELL, cellColor, TCODColor::black);
            else
                TCODConsole::root->putCharEx(1+i, 1+j, FREE_SPACE, cellColor, TCODColor::black);
        }
    }
}

void drawMap(LifeMap& map, int x, int y, char color) {
    drawMap(map);

    TCODColor cursColor(0,0,0);
    switch(color) {
        case LifeMap::WHITE_CELL: cursColor.r = 255;
                                  cursColor.g = 255;
                                  cursColor.b = 255;
            break;
        case LifeMap::RED_CELL:   cursColor.r = 255;
            break;
        case LifeMap::GREEN_CELL: cursColor.g = 255;
            break;
        case LifeMap::BLUE_CELL:  cursColor.b = 255;
            break;
    }

    TCODColor cellColor(0,0,0);
    switch(map.getCell(x, y)) {
        case LifeMap::WHITE_CELL: cellColor.r = 255;
                                  cellColor.g = 255;
                                  cellColor.b = 255;
            break;
        case LifeMap::RED_CELL:   cellColor.r = 255;
            break;
        case LifeMap::GREEN_CELL: cellColor.g = 255;
            break;
        case LifeMap::BLUE_CELL:  cellColor.b = 255;
            break;
    }

    if(x > -1 && y > -1 && x < LifeMap::widht && y < LifeMap::height)
        if(map.isLive(x, y))
            TCODConsole::root->putCharEx(1+x, 1+y, SELECTED_CELL, cursColor, cellColor);
        else
            TCODConsole::root->putCharEx(1+x, 1+y, SELECTED_CELL, cursColor, cellColor);
}

void clearHelp() {
    TCODConsole::root->rect(1, LifeMap::height + 2, windowWidht-2, helpHeight, true);
}
void clearAll() {
    TCODConsole::root->rect(1, 1, LifeMap::widht, LifeMap::height, true);
    clearHelp();
}

int MainMenu::showStandartMainMenu() {
    TCODConsole::root->clear();
    drawTitle();

    TCODConsole::root->setAlignment(TCOD_LEFT);
    TCODConsole::root->print(2, 2, "LIFE: MAIN MENU");

    int xBegin = 2;
    int yBegin = 5;

    TCODConsole::root->print(xBegin, yBegin, "1. NEW GAME");
    yBegin += 2;
    TCODConsole::root->print(xBegin, yBegin, "2. LOAD GAME (BLOCK)");
    yBegin += 2;
    TCODConsole::root->print(xBegin, yBegin, "3. EXIT GAME");
    TCODConsole::root->flush();

    while(true) {
        switch(TCODConsole::waitForKeypress(true).c) {
            case '1': return MainMenu::NEW_GAME_OPTION;
            case '2': return MainMenu::LOAD_OPTION;
            case '3': return MainMenu::EXIT_OPTION;
            default: break;
        }
    }
}
void MainMenu::drawTitle() {
}

void gameMenu::drawGameHelp(char color) {
    int xBegin = 2;
    int yBegin = LifeMap::height + 3;

    TCODConsole::root->setAlignment(TCOD_LEFT);
    TCODConsole::root->print(xBegin, yBegin, "%c%c%c%c%c%s",
                                                                '[',
                                                                TCOD_CHAR_ARROW_W,
                                                                TCOD_CHAR_ARROW_N,
                                                                TCOD_CHAR_ARROW_S,
                                                                TCOD_CHAR_ARROW_E,
                                                                "]  - move");
    TCODConsole::root->print(xBegin, yBegin+2, "[SPACE] - set/remove cell");
    TCODConsole::root->print(xBegin, yBegin+4, "[s]     - save");
    TCODConsole::root->print(xBegin, yBegin+6, "[ENTER] - run game");
    TCODConsole::root->print(xBegin, yBegin+8, "[q]     - quit");

    xBegin = windowWidht - 2;
    yBegin = LifeMap::height + 4;

    TCODConsole::root->setAlignment(TCOD_RIGHT);
    TCODConsole::root->print(xBegin, yBegin,   "[w] -%c white %c   ", TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
    TCODConsole::root->print(xBegin, yBegin+2, "[r] -%c red %c     ", TCOD_COLCTRL_2, TCOD_COLCTRL_STOP);
    TCODConsole::root->print(xBegin, yBegin+4, "[g] -%c green %c   ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
    TCODConsole::root->print(xBegin, yBegin+6, "[b] -%c blue %c    ", TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);

    TCODConsole::root->flush();
}

void gamePlay::showGamePlayInfo(int step, LifeMap& gameMap) {
    clearHelp();

    int xBegin = 2;
    int yBegin = LifeMap::height + 3;

    TCODConsole::root->setAlignment(TCOD_LEFT);
    TCODConsole::root->print(xBegin, yBegin, "Living cells: %i", gameMap.liveCellsNumber());
    TCODConsole::root->print(xBegin, yBegin+2, "          W = %i", gameMap.liveWhiteCellsNumber());
    TCODConsole::root->print(xBegin, yBegin+4, "          %cR%c = %i",
                                                     TCOD_COLCTRL_2, TCOD_COLCTRL_STOP, gameMap.liveRedCellsNumber());
    TCODConsole::root->print(xBegin, yBegin+6, "          %cG%c = %i",
                                                     TCOD_COLCTRL_3, TCOD_COLCTRL_STOP, gameMap.liveGreenCellsNumber());
    TCODConsole::root->print(xBegin, yBegin+8, "          %cB%c = %i",
                                                     TCOD_COLCTRL_4, TCOD_COLCTRL_STOP, gameMap.liveBlueCellsNumber());

    xBegin = windowWidht - 16;
    TCODConsole::root->print(xBegin, yBegin, "Step: %i", step);
    xBegin = windowWidht - 3;

    TCODConsole::root->setAlignment(TCOD_RIGHT);
    TCODConsole::root->print(xBegin, yBegin+6, "Press [p] for pause", step);
    TCODConsole::root->print(xBegin, yBegin+8, "Press ESC for stop ", step);
}

void gamePlay::showFinish() {
    clearHelp();

    int xBegin = 2;
    int yBegin = LifeMap::height + 3;

    TCODConsole::root->setAlignment(TCOD_LEFT);
    TCODConsole::root->print(xBegin, yBegin, "GAME OVER!");
    TCODConsole::root->print(xBegin, yBegin+2, "Press any key for wath score...");
    TCODConsole::root->flush();
}

void gamePlay::showScore(int step, LifeMap& gameMap) {
    clearAll();

    int xBegin = 2;
    int yBegin = 2;
    TCODConsole::root->setAlignment(TCOD_LEFT);
    TCODConsole::root->print(xBegin, yBegin, "Game over on %i step", step);

    TCODConsole::root->print(xBegin, yBegin+2, "Max cells on field together: %i", gameMap.maxCellsNumber());
    TCODConsole::root->print(xBegin, yBegin+4, "                      white: %i", gameMap.maxWhiteCellsNumber());
    TCODConsole::root->print(xBegin, yBegin+6, "                        %cred%c: %i",
                                                    TCOD_COLCTRL_2, TCOD_COLCTRL_STOP, gameMap.maxRedCellsNumber());
    TCODConsole::root->print(xBegin, yBegin+8, "                      %cgreen%c: %i",
                                                    TCOD_COLCTRL_3, TCOD_COLCTRL_STOP, gameMap.maxGreenCellsNumber());
    TCODConsole::root->print(xBegin, yBegin+10, "                       %cblue%c: %i",
                                                    TCOD_COLCTRL_4, TCOD_COLCTRL_STOP, gameMap.maxBlueCellsNumber());

    yBegin = LifeMap::height + helpHeight/2 + 2;
    xBegin = (LifeMap::widht + 1)/2;

    TCODConsole::root->setAlignment(TCOD_CENTER);
    TCODConsole::root->print(xBegin, yBegin, "Press Esc for return to main menu...");
    TCODConsole::root->flush();
}

void gamePlay::showPause() {
    clearHelp();

    int xBegin = (windowWidht - 2)/2;
    int yBegin = LifeMap::height + helpHeight/2 + 2;

    TCODConsole::root->setAlignment(TCOD_CENTER);
    TCODConsole::root->print(xBegin, yBegin, "Press any key for continue...");
    TCODConsole::root->flush();
}
