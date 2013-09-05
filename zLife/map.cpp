#include "map.h"

#include <iostream>
using namespace std;


LifeMap::LifeMap() {
    presentLayer = 0;
    liveNum = 0;
    liveRedNum = 0;
    liveGreenNum = 0;
    liveBlueNum = 0;

    maxNum = 0;
    maxWhiteNum = 0;
    maxRedNum = 0;
    maxGreenNum = 0;
    maxBlueNum = 0;

    change = true;

    clear();
}

void LifeMap::clear() {
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < widht; j++) {
            map[0][i][j] = FREE_CELL;
            map[1][i][j] = FREE_CELL;
        }
    }
}

int LifeMap::getNextLayer() {
    return (presentLayer + 1)%2;
}
int LifeMap::getPresentLayer() {
    return presentLayer;
}

char LifeMap::getCell(int x, int y) {
    if(x > -1 && y > -1 && x < widht && y < height) {
        return map[getPresentLayer()][y][x];
    }
    return 'X';
}
void LifeMap::set(int x, int y, char color) {
    if(color != WHITE_CELL &&
       color != RED_CELL   &&
       color != GREEN_CELL &&
       color != BLUE_CELL)
    {
        return;
    }

    if(x > -1 && y > -1 && x < widht && y < height) {
        if(map[getPresentLayer()][y][x] != color)
            map[getPresentLayer()][y][x] = color;
        else
            map[getPresentLayer()][y][x] = FREE_CELL;
    }
}

void LifeMap::nextStep() {
    change = false;
    liveNum = 0;
    liveRedNum = 0;
    liveGreenNum = 0;
    liveBlueNum = 0;

    for(int i = 0; i < widht; i++) {
        for(int j = 0; j < height; j++) {
            map[getNextLayer()][j][i] = getNewCell(i, j);

            switch(getCell(i, j)) {
                case RED_CELL:   liveNum++; liveRedNum++;   break;
                case GREEN_CELL: liveNum++; liveGreenNum++; break;
                case BLUE_CELL:  liveNum++; liveBlueNum++;  break;
                case WHITE_CELL: liveNum++; break;
                case FREE_CELL: break;
            }
            if(map[getPresentLayer()][j][i] != map[getNextLayer()][j][i])
                change = true;
        }
    }

    maxNum = max(maxNum, liveNum);
    maxWhiteNum = max(maxWhiteNum, (liveNum - liveRedNum - liveGreenNum - liveBlueNum));
    maxRedNum = max(maxRedNum, liveRedNum);
    maxGreenNum = max(maxGreenNum, liveGreenNum);
    maxBlueNum = max(maxBlueNum, liveBlueNum);

    presentLayer = getNextLayer();
}

char LifeMap::getNewCell(int x, int y) {
    int neighbors = 0;
    int red = 0;
    int green = 0;
    int blue = 0;
    
    switch(getCell(x, (y+1)%height)) {
        case RED_CELL:   neighbors++; red++;   break;
        case GREEN_CELL: neighbors++; green++; break;       
        case BLUE_CELL:  neighbors++; blue++;  break; 
        case WHITE_CELL: neighbors++; break;
        case FREE_CELL:  break;
    }
    switch(getCell((x+1)%widht, (y+1)%height)) {
        case RED_CELL:   neighbors++; red++;   break;
        case GREEN_CELL: neighbors++; green++; break;       
        case BLUE_CELL:  neighbors++; blue++;  break; 
        case WHITE_CELL: neighbors++; break;
        case FREE_CELL:  break;
    }
    switch(getCell((x-1+widht)%widht, (y+1)%height)) {
        case RED_CELL:   neighbors++; red++;   break;
        case GREEN_CELL: neighbors++; green++; break;       
        case BLUE_CELL:  neighbors++; blue++;  break; 
        case WHITE_CELL: neighbors++; break;
        case FREE_CELL:  break;
    }
    switch(getCell((x-1+widht)%widht, y)) {
        case RED_CELL:   neighbors++; red++;   break;
        case GREEN_CELL: neighbors++; green++; break;       
        case BLUE_CELL:  neighbors++; blue++;  break; 
        case WHITE_CELL: neighbors++; break;
        case FREE_CELL:  break;
    }
    switch(getCell((x-1+widht)%widht, (y-1+height)%height)) {
        case RED_CELL:   neighbors++; red++;   break;
        case GREEN_CELL: neighbors++; green++; break;       
        case BLUE_CELL:  neighbors++; blue++;  break; 
        case WHITE_CELL: neighbors++; break;
        case FREE_CELL:  break;
    }
    switch(getCell(x, (y-1+height)%height)) {
        case RED_CELL:   neighbors++; red++;   break;
        case GREEN_CELL: neighbors++; green++; break;       
        case BLUE_CELL:  neighbors++; blue++;  break; 
        case WHITE_CELL: neighbors++; break;
        case FREE_CELL:  break;
    }
    switch(getCell((x+1)%widht, (y-1+height)%height)) {
        case RED_CELL:   neighbors++; red++;   break;
        case GREEN_CELL: neighbors++; green++; break;       
        case BLUE_CELL:  neighbors++; blue++;  break; 
        case WHITE_CELL: neighbors++; break;
        case FREE_CELL:  break;
    }
    switch(getCell((x+1)%widht, y)) {
        case RED_CELL:   neighbors++; red++;   break;
        case GREEN_CELL: neighbors++; green++; break;       
        case BLUE_CELL:  neighbors++; blue++;  break; 
        case WHITE_CELL: neighbors++; break;
        case FREE_CELL:  break;
    } 

    if(isLive(x, y))
        if(neighbors == 2 || neighbors == 3)
            return getCell(x, y);
        else
            return FREE_CELL;

    if(neighbors == 3) {
        if(red == green && green == blue)
            return WHITE_CELL;
        if(red != 0 && green != 0)
            return BLUE_CELL;
        if(red != 0 && blue != 0)
            return GREEN_CELL;
        if(green != 0 && blue != 0)
            return RED_CELL; 
        if(red != 0)
            return RED_CELL; 
        if(green != 0)
            return GREEN_CELL; 
        if(blue != 0)
            return BLUE_CELL; 
        cout << red << ' ' << green << ' ' << blue << endl;
    }

    return FREE_CELL;
}

int LifeMap::liveCellsNumber() {
    return liveNum;
}
int LifeMap::liveWhiteCellsNumber() {
    return liveNum - liveRedNum - liveGreenNum - liveBlueNum;
}
int LifeMap::liveRedCellsNumber() {
    return liveRedNum;
}
int LifeMap::liveGreenCellsNumber() {
    return liveGreenNum;
}
int LifeMap::liveBlueCellsNumber() {
    return liveBlueNum;
}

int LifeMap::maxCellsNumber() {
    return maxNum;
}
int LifeMap::maxWhiteCellsNumber() {
    return maxWhiteNum;
}
int LifeMap::maxRedCellsNumber() {
    return maxRedNum;
}
int LifeMap::maxGreenCellsNumber() {
    return maxGreenNum;
}
int LifeMap::maxBlueCellsNumber() {
    return maxBlueNum;
}

bool LifeMap::isLive(int x, int y) {
    if(map[getPresentLayer()][y][x] != FREE_CELL)
        return true;
    else 
        return false;
}

bool LifeMap::isChange() {
    return change;
}