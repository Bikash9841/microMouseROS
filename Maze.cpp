#include "Maze.h"

uint8_t cells[16][16] = { { 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                          { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                          { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                          { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                          { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                          { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                          { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                          { 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0 },
                          { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                          { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                          { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                          { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                          { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                          { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                          { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                          { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };

uint16_t flood[16][16] = { { 14, 13, 12, 11, 10, 9, 8, 7, 7, 8, 9, 10, 11, 12, 13, 14 },
                           { 13, 12, 11, 10, 9, 8, 7, 6, 6, 7, 8, 9, 10, 11, 12, 13 },
                           { 12, 11, 10, 9, 8, 7, 6, 5, 5, 6, 7, 8, 9, 10, 11, 12 },
                           { 11, 10, 9, 8, 7, 6, 5, 4, 4, 5, 6, 7, 8, 9, 10, 11 },
                           { 10, 9, 8, 7, 6, 5, 4, 3, 3, 4, 5, 6, 7, 8, 9, 10 },
                           { 9, 8, 7, 6, 5, 4, 3, 2, 2, 3, 4, 5, 6, 7, 8, 9 },
                           { 8, 7, 6, 5, 4, 3, 2, 1, 1, 2, 3, 4, 5, 6, 7, 8 },
                           { 7, 6, 5, 4, 3, 2, 1, 0, 0, 1, 2, 3, 4, 5, 6, 7 },
                           { 7, 6, 5, 4, 3, 2, 1, 0, 0, 1, 2, 3, 4, 5, 6, 7 },
                           { 8, 7, 6, 5, 4, 3, 2, 1, 1, 2, 3, 4, 5, 6, 7, 8 },
                           { 9, 8, 7, 6, 5, 4, 3, 2, 2, 3, 4, 5, 6, 7, 8, 9 },
                           { 10, 9, 8, 7, 6, 5, 4, 3, 3, 4, 5, 6, 7, 8, 9, 10 },
                           { 11, 10, 9, 8, 7, 6, 5, 4, 4, 5, 6, 7, 8, 9, 10, 11 },
                           { 12, 11, 10, 9, 8, 7, 6, 5, 5, 6, 7, 8, 9, 10, 11, 12 },
                           { 13, 12, 11, 10, 9, 8, 7, 6, 6, 7, 8, 9, 10, 11, 12, 13 },
                           { 14, 13, 12, 11, 10, 9, 8, 7, 7, 8, 9, 10, 11, 12, 13, 14 } };

//iterator for loop
uint8_t i = 0;


int16_t minVal;
int16_t maxVal;
int8_t minCell, noMovements = 0;

char turning;

//used in isConsistant function
int16_t floodVal;
int16_t minVals[4];
uint8_t minCount;



void getSurrounds(int16_t botx, int16_t boty, int16_t *botx0, int16_t *boty0, int16_t *botx1, int16_t *boty1,
                  int16_t *botx2, int16_t *boty2, int16_t *botx3, int16_t *boty3) {
  *botx3 = botx - 1;
  *boty3 = boty;
  *botx2 = botx;
  *boty2 = boty - 1;
  *botx1 = botx + 1;
  *boty1 = boty;
  *botx0 = botx;
  *boty0 = boty + 1;

  if (*botx1 >= 16) {
    *botx1 = -1;
  }
  if (*boty0 >= 16) {
    *boty0 = -1;
  }
}

void updateWalls(int16_t botx, int16_t boty, int8_t orient,
                 bool L, bool R, bool F) {
  if (L && R && F) {
    if (orient == 0) {
      cells[boty][botx] = 13;
    } else if (orient == 1) {
      cells[boty][botx] = 12;
    } else if (orient == 2) {
      cells[boty][botx] = 11;
    } else if (orient == 3) {
      cells[boty][botx] = 14;
    }
  } else if (L && R && !F) {
    if (orient == 0 || orient == 2) {
      cells[boty][botx] = 9;
    } else if (orient == 1 || orient == 3) {
      cells[boty][botx] = 10;
    }
  } else if (L && F && !R) {
    if (orient == 0) {
      cells[boty][botx] = 8;
    } else if (orient == 1) {
      cells[boty][botx] = 7;
    } else if (orient == 2) {
      cells[boty][botx] = 6;
    } else if (orient == 3) {
      cells[boty][botx] = 5;
    }
  } else if (R && F && !L) {
    if (orient == 0) {
      cells[boty][botx] = 7;
    } else if (orient == 1) {
      cells[boty][botx] = 6;
    } else if (orient == 2) {
      cells[boty][botx] = 5;
    } else if (orient == 3) {
      cells[boty][botx] = 8;
    }
  } else if (F) {
    if (orient == 0) {
      cells[boty][botx] = 2;
    } else if (orient == 1) {
      cells[boty][botx] = 3;
    } else if (orient == 2) {
      cells[boty][botx] = 4;
    } else if (orient == 3) {
      cells[boty][botx] = 1;
    }
  } else if (L) {
    if (orient == 0) {
      cells[boty][botx] = 1;
    } else if (orient == 1) {
      cells[boty][botx] = 2;
    } else if (orient == 2) {
      cells[boty][botx] = 3;
    } else if (orient == 3) {
      cells[boty][botx] = 4;
    }
  } else if (R) {
    if (orient == 0) {
      cells[boty][botx] = 3;
    } else if (orient == 1) {
      cells[boty][botx] = 4;
    } else if (orient == 2) {
      cells[boty][botx] = 1;
    } else if (orient == 3) {
      cells[boty][botx] = 2;
    }
  } else {
    cells[boty][botx] = 15;
  }
}

// to find if the given cell is accesible from the current cell or not

bool isAccessible(int16_t botx, int16_t boty, int16_t givx, int16_t givy)

// returns true(1) if accesible else 0

{
  if (cells[boty][botx] == 15) {
    return true;
  }
  if (botx == givx) {
    if (boty > givy && givy >= 0) {
      if (cells[boty][botx] == 4 or cells[boty][botx] == 5 or cells[boty][botx] == 6 or cells[boty][botx] == 10 or cells[boty][botx] == 11 or cells[boty][botx] == 12 or cells[boty][botx] == 14 or cells[givy][givx] == 2 or cells[givy][givx] == 7 or cells[givy][givx] == 8 or cells[givy][givx] == 10 or cells[givy][givx] == 12 or cells[givy][givx] == 13 or cells[givy][givx] == 14 or cells[givy][givx] == 16) {
        return false;
      } else {
        return true;
      }
    } else if (boty < givy) {
      if (cells[boty][botx] == 2 or cells[boty][botx] == 7 or cells[boty][botx] == 8 or cells[boty][botx] == 10 or cells[boty][botx] == 12 or cells[boty][botx] == 13 or cells[boty][botx] == 14 or cells[givy][givx] == 4 or cells[givy][givx] == 5 or cells[givy][givx] == 6 or cells[givy][givx] == 10 or cells[givy][givx] == 11 or cells[givy][givx] == 12 or cells[givy][givx] == 14 or cells[givy][givx] == 16) {
        return false;
      } else {
        return true;
      }
    } else {
      return false;
    }
  } else if (boty == givy) {
    if (botx > givx && givx >= 0) {
      if (cells[boty][botx] == 1 or cells[boty][botx] == 5 or cells[boty][botx] == 8 or cells[boty][botx] == 9 or cells[boty][botx] == 11 or cells[boty][botx] == 13 or cells[boty][botx] == 14 or cells[givy][givx] == 3 or cells[givy][givx] == 6 or cells[givy][givx] == 7 or cells[givy][givx] == 9 or cells[givy][givx] == 11 or cells[givy][givx] == 12 or cells[givy][givx] == 13 or cells[givy][givx] == 16) {
        return false;
      } else {
        return true;
      }
    } else if (botx < givx) {
      if (cells[boty][botx] == 3 or cells[boty][botx] == 6 or cells[boty][botx] == 7 or cells[boty][botx] == 9 or cells[boty][botx] == 11 or cells[boty][botx] == 12 or cells[boty][botx] == 13 or cells[givy][givx] == 1 or cells[givy][givx] == 5 or cells[givy][givx] == 8 or cells[givy][givx] == 9 or cells[givy][givx] == 11 or cells[givy][givx] == 13 or cells[givy][givx] == 14 or cells[givy][givx] == 16) {
        return false;
      } else {
        return true;
      }
    } else {
      return false;
    }
  } else {
    return false;
  }
}

char toMove(int16_t botx, int16_t boty, int16_t botxP, int16_t botyP, int8_t orient) {
  getSurrounds(botx, boty, &botx0, &boty0, &botx1, &boty1, &botx2, &boty2, &botx3, &boty3);

  floodVal = flood[boty][botx];

  preV = 0;
  minVals[0] = 1000;
  minVals[1] = 1000;
  minVals[2] = 1000;
  minVals[3] = 1000;

  if (isAccessible(botx, boty, botx0, boty0)) {

    if (botx0 == botxP && boty0 == botyP) {
      preV = 0;
    }

    minVals[0] = flood[boty0][botx0];
  }
  if (isAccessible(botx, boty, botx1, boty1)) {

    if (botx1 == botxP && boty1 == botyP) {
      preV = 1;
    }

    minVals[1] = flood[boty1][botx1];
  }
  if (isAccessible(botx, boty, botx2, boty2)) {
    if (botx2 == botxP && boty2 == botyP) {
      preV = 2;
    }
    minVals[2] = flood[boty2][botx2];
  }
  if (isAccessible(botx, boty, botx3, boty3)) {
    if (botx3 == botxP && boty3 == botyP) {
      preV = 3;
    }

    minVals[3] = flood[boty3][botx3];
  }

  minVal = minVals[orient];
  minCell = orient;
  // minCell = 0;
  noMovements = 0;

  for (i = 0; i < 4; i++) {
    if (minVals[i] != 1000) {
      noMovements += 1;
    }
  }
  for (i = 0; i < 4; i++) {
    if (minVals[i] < minVal) {
      if (noMovements == 1) {
        minVal = minVals[i];
        minCell = i;
      } else {
        if (i == preV) {
          continue;
        } else {
          minVal = minVals[i];
          minCell = i;
        }
      }
    }
  }
  if (minCell == orient) {
    return 'F';
  } else if ((minCell == orient - 1) || (minCell == orient + 3)) {
    return 'L';
  } else if ((minCell == orient + 1) || (minCell == orient - 3)) {
    return 'R';
  } else {
    return 'B';
  }
}

char toMoveFast(int16_t botx, int16_t boty, int16_t botxP, int16_t botyP, int8_t orient) {
  getSurrounds(botx, boty, &botx0, &boty0, &botx1, &boty1, &botx2, &boty2, &botx3, &boty3);

  floodVal = flood[boty][botx];
  minCell = orient;
  if (isAccessible(botx, boty, botx0, boty0)) {
    if (flood[boty0][botx0] == floodVal - 1) {
      minCell = 0;
    }
  }
  if (isAccessible(botx, boty, botx1, boty1)) {
    if (flood[boty1][botx1] == floodVal - 1) {
      minCell = 1;
    }
  }
  if (isAccessible(botx, boty, botx2, boty2)) {
    if (flood[boty2][botx2] == floodVal - 1) {
      minCell = 2;
    }
  }
  if (isAccessible(botx, boty, botx3, boty3)) {
    if (flood[boty3][botx3] == floodVal - 1) {
      minCell = 3;
    }
  }
  if (minCell == orient) {
    return 'F';
  } else if ((minCell == orient - 1) || (minCell == orient + 3)) {
    return 'L';
  } else if ((minCell == orient + 1) || (minCell == orient - 3)) {
    return 'R';
  } else {
    return 'B';
  }
}



bool isConsistant(int16_t botx, int16_t boty) {
  getSurrounds(botx, boty, &botx0, &boty0, &botx1, &boty1, &botx2, &boty2, &botx3, &boty3);


  floodVal = flood[boty][botx];

  minVals[0] = -1;
  minVals[1] = -1;
  minVals[2] = -1;
  minVals[3] = -1;

  if (botx0 >= 0 && boty0 >= 0) {
    if (isAccessible(botx, boty, botx0, boty0)) {

      minVals[0] = flood[boty0][botx0];
    }
  }
  if (botx1 >= 0 && boty1 >= 0) {
    if (isAccessible(botx, boty, botx1, boty1)) {

      minVals[1] = flood[boty1][botx1];
    }
  }
  if (botx2 >= 0 && boty2 >= 0) {
    if (isAccessible(botx, boty, botx2, boty2)) {
      minVals[2] = flood[boty2][botx2];
    }
  }
  if (botx3 >= 0 && boty3 >= 0) {
    if (isAccessible(botx, boty, botx3, boty3)) {

      minVals[3] = flood[boty3][botx3];
    }
  }

  minCount = 0;

  for (i = 0; i < 4; i++) {
    if (minVals[i] == -1) {
      continue;
    } else if (minVals[i] == floodVal + 1) {
      continue;
    } else if (minVals[i] == floodVal - 1) {
      minCount += 1;
      continue;
    }
  }
  if (minCount > 0) {
    return true;
  } else {
    return false;
  }
}

void makeConsistant(int16_t botx, int16_t boty) {

  getSurrounds(botx, boty, &botx0, &boty0, &botx1, &boty1, &botx2, &boty2, &botx3, &boty3);
  floodVal = flood[boty][botx];
  minVals[0] = -1;
  minVals[1] = -1;
  minVals[2] = -1;
  minVals[3] = -1;

  if (botx0 >= 0 and boty0 >= 0) {
    if (isAccessible(botx, boty, botx0, boty0)) {

      minVals[0] = flood[boty0][botx0];
    }
  }

  if (botx1 >= 0 and boty1 >= 0) {
    if (isAccessible(botx, boty, botx1, boty1)) {

      minVals[1] = flood[boty1][botx1];
    }
  }

  if (botx2 >= 0 and boty2 >= 0) {
    if (isAccessible(botx, boty, botx2, boty2)) {

      minVals[2] = flood[boty2][botx2];
    }
  }

  if (botx3 >= 0 and boty3 >= 0) {
    if (isAccessible(botx, boty, botx3, boty3)) {

      minVals[3] = flood[boty3][botx3];
    }
  }
  for (i = 0; i < 4; i++) {
    if (minVals[i] == -1) {
      minVals[i] = 1000;
    }
  }
  minVal = minVals[0];

  for (i = 0; i < 4; i++) {
    if (minVals[i] <= minVal) {
      minVal = minVals[i];
    }
  }

  flood[boty][botx] = minVal + 1;
}



void floodfill(int16_t botx, int16_t boty) {
  enqueue(botx);
  enqueue(boty);

  while (q.front != -1) {
    botx = dequeue();
    boty = dequeue();

    // setText(int(botx), int(boty), String(flood[boty][botx]));

    if (isConsistant(botx, boty)) {
      continue;
    } else {
      makeConsistant(botx, boty);
      getSurrounds(botx, boty, &botx0, &boty0, &botx1,
                   &boty1, &botx2, &boty2, &botx3, &boty3);
      if (botx0 >= 0 and boty0 >= 0) {
        if (isAccessible(botx, boty, botx0, boty0)) {
          enqueue(botx0);
          enqueue(boty0);
        }
      }
      if (botx1 >= 0 and boty1 >= 0) {
        if (isAccessible(botx, boty, botx1, boty1)) {
          enqueue(botx1);
          enqueue(boty1);
        }
      }
      if (botx2 >= 0 and boty2 >= 0) {
        if (isAccessible(botx, boty, botx2, boty2)) {
          enqueue(botx2);
          enqueue(boty2);
        }
      }
      if (botx3 >= 0 and boty3 >= 0) {
        if (isAccessible(botx, boty, botx3, boty3)) {
          enqueue(botx3);
          enqueue(boty3);
        }
      }
    }
  }
}

void floodfill2() {
  int16_t yrun, xrun;
  while (q.front != -1) {
    yrun = dequeue();
    xrun = dequeue();
    getSurrounds(xrun, yrun, &botx0, &boty0, &botx1, &boty1, &botx2, &boty2, &botx3, &boty3);

    if (botx0 >= 0 && boty0 >= 0) {
      if (flood[boty0][botx0] == 255) {
        if (isAccessible(xrun, yrun, botx0, boty0)) {
          flood[boty0][botx0] = flood[yrun][xrun] + 1;
          enqueue(boty0);
          enqueue(botx0);
        }
      }
    }
    if (botx1 >= 0 && boty1 >= 0) {
      if (flood[boty1][botx1] == 255) {
        if (isAccessible(xrun, yrun, botx1, boty1)) {
          flood[boty1][botx1] = flood[yrun][xrun] + 1;
          enqueue(boty1);
          enqueue(botx1);
        }
      }
    }
    if (botx2 >= 0 && boty2 >= 0) {
      if (flood[boty2][botx2] == 255) {
        if (isAccessible(xrun, yrun, botx2, boty2)) {
          flood[boty2][botx2] = flood[yrun][xrun] + 1;
          enqueue(boty2);
          enqueue(botx2);
        }
      }
    }
    if (botx3 >= 0 && boty3 >= 0) {
      if (flood[boty3][botx3] == 255) {
        if (isAccessible(xrun, yrun, botx3, boty3)) {
          flood[boty3][botx3] = flood[yrun][xrun] + 1;
          enqueue(boty3);
          enqueue(botx3);
        }
      }
    }
  }
}

void appendDestination(int16_t botx, int16_t boty) {
  for (i = 0; i < 16; i++) {
    for (uint8_t j = 0; j < 16; j++) {
      flood[i][j] = 255;
    }
  }
  flood[boty][botx] = 0;
  enqueue(boty);
  enqueue(botx);
}

void appendZero() {
  for (i = 0; i < 16; i++) {
    for (uint8_t j = 0; j < 16; j++) {
      flood[i][j] = 255;
    }
  }
  flood[7][7] = 0;
  flood[8][7] = 0;
  flood[7][8] = 0;
  flood[8][8] = 0;

  enqueue(7);
  enqueue(7);
  enqueue(8);
  enqueue(7);
  enqueue(7);
  enqueue(8);
  enqueue(8);
  enqueue(8);
}
