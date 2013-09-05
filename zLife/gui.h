#ifndef ___GUI___
#define ___GUI___

#include "map.h"

const int helpWidht = LifeMap::widht;
const int helpHeight = 11;

const int windowWidht = 1 + LifeMap::widht + 1;
const int windowHeight = 1 + LifeMap::height + 1 + helpHeight + 1;

#define VERTICAL_LINE       186
#define GORIZONTAL_LINE     205
#define LEFT_TOP_LINE       201
#define LEFT_BOTTOM_LINE    200
#define RIGHT_TOP_LINE      187
#define RIGHT_BOTTOM_LINE   188
#define LEFT_T_LINE         204
#define RIGHT_T_LINE        185

#define CELL 254
#define FREE_SPACE 32

#define SELECTED_CELL 224

void initGraphic();
void drawGameFrame();
void clearHelp();
void clearAll();

void drawMap(LifeMap& map);
void drawMap(LifeMap& map, int x, int y, char color);

namespace MainMenu {
    enum {NEW_GAME_OPTION, LOAD_OPTION, EXIT_OPTION};    
    int showStandartMainMenu();
    void drawTitle();
}

namespace gameMenu {
    enum {SET_CELL, SAVE_MAP, START_GAME, QUIT_GAME};
    void drawGameHelp(char color);
}

namespace gamePlay {
    void showGamePlayInfo(int step, LifeMap& gameMap);
    void showScore(int step, LifeMap& gameMap);
    void showPause();
    void showFinish();
}




#endif /*___GUI___*/