#ifndef ___MAP___
#define ___MAP___

class LifeMap {
public:
    static const char FREE_CELL  = ' ';
    static const char WHITE_CELL = 'W';
    static const char RED_CELL   = 'R';
    static const char GREEN_CELL = 'G';
    static const char BLUE_CELL  = 'B';

    static const int height = 50;
    static const int widht = 50;

private:
    char map[2][height][widht];
    int presentLayer;

    int liveNum;
    int liveRedNum;
    int liveGreenNum;
    int liveBlueNum;
 
    int maxNum;
    int maxWhiteNum;
    int maxRedNum;
    int maxGreenNum;
    int maxBlueNum;

    bool change;

    void clear();
    char getNewCell(int x, int y);

    int getNextLayer();
    int getPresentLayer();
public:
    LifeMap();

    char getCell(int x, int y);
    void set(int x, int y, char color = WHITE_CELL);

    void nextStep();

    int liveCellsNumber();
    int liveWhiteCellsNumber();
    int liveRedCellsNumber();
    int liveGreenCellsNumber();
    int liveBlueCellsNumber();

    int maxCellsNumber();
    int maxWhiteCellsNumber();
    int maxRedCellsNumber();
    int maxGreenCellsNumber();
    int maxBlueCellsNumber();

    bool isLive(int x, int y);
    bool isChange();
};

#endif /*___MAP___*/