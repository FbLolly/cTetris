#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "raylib.h"

#define WIDTH 320
#define HEIGHT 640

#define PIECESIZE 4

#define GRIDWIDTH 10
#define GRIDHEIGHT 20

char templates[7][4][4][4] = {
    {
        {
            {'0', '0', '0', '0'},
            {'1', '1', '1', '1'},
            {'0', '0', '0', '0'},
            {'0', '0', '0', '0'}
        },
        {
            {'0', '0', '1', '0'},
            {'0', '0', '1', '0'},
            {'0', '0', '1', '0'},
            {'0', '0', '1', '0'}
        },
        {
            {'0', '0', '0', '0'},
            {'1', '1', '1', '1'},
            {'0', '0', '0', '0'},
            {'0', '0', '0', '0'}
        },
        {
            {'0', '0', '1', '0'},
            {'0', '0', '1', '0'},
            {'0', '0', '1', '0'},
            {'0', '0', '1', '0'}
        }
    },
    {
        {
            {'0', '0', '0', '0'},
            {'1', '1', '1', '0'},
            {'0', '1', '0', '0'},
            {'0', '0', '0', '0'}
        },
        {
            {'0', '1', '0', '0'},
            {'1', '1', '0', '0'},
            {'0', '1', '0', '0'},
            {'0', '0', '0', '0'}
        },
        {
            {'0', '1', '0', '0'},
            {'1', '1', '1', '0'},
            {'0', '0', '0', '0'},
            {'0', '0', '0', '0'}
        },
        {
            {'0', '1', '0', '0'},
            {'0', '1', '1', '0'},
            {'0', '1', '0', '0'},
            {'0', '0', '0', '0'}
        }
    },
    {
        {
            {'0', '0', '0', '0'},
            {'0', '1', '1', '0'},
            {'0', '1', '1', '0'},
            {'0', '0', '0', '0'}
        },
        {
            {'0', '0', '0', '0'},
            {'0', '1', '1', '0'},
            {'0', '1', '1', '0'},
            {'0', '0', '0', '0'}
        },
        {
            {'0', '0', '0', '0'},
            {'0', '1', '1', '0'},
            {'0', '1', '1', '0'},
            {'0', '0', '0', '0'}
        },
        {
            {'0', '0', '0', '0'},
            {'0', '1', '1', '0'},
            {'0', '1', '1', '0'},
            {'0', '0', '0', '0'}
        }
    },
    {
        {
            {'0', '0', '0', '0'},
            {'0', '0', '1', '1'},
            {'0', '1', '1', '0'},
            {'0', '0', '0', '0'}
        },
        {
            {'0', '0', '1', '0'},
            {'0', '0', '1', '1'},
            {'0', '0', '0', '1'},
            {'0', '0', '0', '0'}
        },
        {
            {'0', '0', '0', '0'},
            {'0', '0', '1', '1'},
            {'0', '1', '1', '0'},
            {'0', '0', '0', '0'}
        },
        {
            {'0', '0', '1', '0'},
            {'0', '0', '1', '1'},
            {'0', '0', '0', '1'},
            {'0', '0', '0', '0'}
        }
    },
    {
        {
            {'0', '0', '0', '0'},
            {'0', '1', '1', '0'},
            {'0', '0', '1', '1'},
            {'0', '0', '0', '0'}
        },
        {
            {'0', '0', '0', '1'},
            {'0', '0', '1', '1'},
            {'0', '0', '1', '0'},
            {'0', '0', '0', '0'}
        },
        {
            {'0', '0', '0', '0'},
            {'0', '1', '1', '0'},
            {'0', '0', '1', '1'},
            {'0', '0', '0', '0'}
        },
        {
            {'0', '0', '0', '1'},
            {'0', '0', '1', '1'},
            {'0', '0', '1', '0'},
            {'0', '0', '0', '0'}
        }
    },
    {
        {
            {'0', '0', '0', '0'},
            {'0', '1', '1', '1'},
            {'0', '1', '0', '0'},
            {'0', '0', '0', '0'}
        },
        {
            {'0', '1', '1', '0'},
            {'0', '0', '1', '0'},
            {'0', '0', '1', '0'},
            {'0', '0', '0', '0'}
        },
        {
            {'0', '0', '0', '1'},
            {'0', '1', '1', '1'},
            {'0', '0', '0', '0'},
            {'0', '0', '0', '0'}
        },
        {
            {'0', '0', '1', '0'},
            {'0', '0', '1', '0'},
            {'0', '0', '1', '1'},
            {'0', '0', '0', '0'}
        }
    },
    {
        {
            {'0', '0', '0', '0'},
            {'0', '1', '1', '1'},
            {'0', '0', '0', '1'},
            {'0', '0', '0', '0'}
        },
        {
            {'0', '0', '1', '0'},
            {'0', '0', '1', '0'},
            {'0', '1', '1', '0'},
            {'0', '0', '0', '0'}
        },
        {
            {'0', '1', '0', '0'},
            {'0', '1', '1', '1'},
            {'0', '0', '0', '0'},
            {'0', '0', '0', '0'}
        },
        {
            {'0', '0', '1', '1'},
            {'0', '0', '1', '0'},
            {'0', '0', '1', '0'},
            {'0', '0', '0', '0'}
        }
    }
};

bool buffer = false;

Color colorArray[7] = {RED, YELLOW, BLUE, GREEN, BROWN, WHITE, PURPLE};

typedef struct{
    Rectangle rect;

    bool air;
    Color color;
}block;

typedef struct{
    block blocks[5][5];

    float speed;
    float defaultSpeed;

    int rotationCount;
    int id;

    bool placed;
}piece;

/* GAME */


void game();



void setGrid(block grid[][GRIDWIDTH]);

void setPiece(piece* piece);
void managePiece(piece* piece, block grid[][GRIDWIDTH], int* frameCounter);
void collidingPiece(piece* piece, block grid[][GRIDWIDTH], int* frameCounter);

void printPieceOnGrid(piece* piece, block grid[][GRIDWIDTH]);
int collidingWithGrid(block* toCheck, block grid[][GRIDWIDTH]);
void collidingWithGridHorizontally(piece* piece, block grid[][GRIDWIDTH]);

void manageInput(piece* piece, int* frameCounter);

void drawAll(piece* piece, block grid[][GRIDWIDTH]);

void rotatePiece(piece* piece);
void manageGrid(block grid[][GRIDWIDTH], int* score, int* score_times);

void move(int toWhere, piece* piece);
void manageGameOver(block grid[][GRIDWIDTH], int* lost);

void getPause(int* frameCounter, int* counter);
void drawPause();

/**/

/*menu*/

int mainMenu();

int manageMenu(Rectangle* buttons, int* pos);
void drawMenu(Rectangle* buttons, int* pos);

/**/

int main(){
    int choice = 0;

    InitWindow(WIDTH, HEIGHT, "tetris");
    SetTargetFPS(60);

    srand(time(NULL));

    while (!WindowShouldClose()){
        choice = mainMenu();

        switch (choice) {
            case 1:
                game();
            break;

            case 2:
                return 0;
            break;
        }
    }

    return 0;
}


void game(){
    block grid[GRIDHEIGHT][GRIDWIDTH];
    piece piece;

    int frameCounter = 0;
    int lost = 0; // 0 for not lost, 1 for lost, -1 for exited but not lost
    int counter = 1;

    int score_times = 0;
    int score = 0;

    piece.speed = 5;

    setGrid(grid);
    setPiece(&piece);

    while (!WindowShouldClose() && lost == 0){
        score_times = 0;
        if (counter != 0){
            manageInput(&piece, &frameCounter);
            collidingPiece(&piece, grid, &frameCounter);
            managePiece(&piece, grid, &frameCounter);
            manageGrid(grid, &score, &score_times);
            collidingWithGridHorizontally(&piece, grid);
            manageGameOver(grid, &lost);
        }
        
        getPause(&frameCounter, &counter);

        if (score_times > 0){
            switch (score_times) {
                case 1:
                    score += 100;
                break;
                case 2:
                    score += 300;
                break;
                case 3:
                    score += 500;
                break;
                case 4:
                    score += 800; //tetris
                break;
            }
        }

        BeginDrawing();
            ClearBackground(BLACK);
            DrawText(TextFormat("%d", score), 5, 5, 30, (Color){245, 245, 245, 100});

            drawAll(&piece, grid);
            
            if (counter == 0){
                drawPause();
            }
        EndDrawing();

        frameCounter++;
    }
}

void drawPause(){
    DrawText("paused", (WIDTH/2.0)-(MeasureText("paused", 30)/2.0), HEIGHT/2.0-15, 30, LIGHTGRAY);
}




void setGrid(block grid[][GRIDWIDTH]){
    int i, ii;

    for (i = 0; i < GRIDHEIGHT; i++){
        for (ii = 0; ii < GRIDWIDTH; ii++){
            grid[i][ii].air = true;
            grid[i][ii].rect = (Rectangle){ii*32, i*32, 32, 32};
        }
    }
}


void setPiece(piece* piece){
    int i, ii;
    int type = rand()%7; //the rand function is used at the end to avoid using heap allocation
    // (0-7)


    for (i = 0; i < PIECESIZE; i++){ //copying a random template
        for (ii = 0; ii < PIECESIZE; ii++){
            piece->blocks[i][ii].rect = (Rectangle){(WIDTH/2.0)-ii*32, i*32, 32, 32};
            
            if (templates[type][0][i][ii] == '0'){
                piece->blocks[i][ii].air = true;
            }else
                piece->blocks[i][ii].air = false;
            
            piece->blocks[i][ii].color = colorArray[type];
        }
    }

    piece->id = type;
    piece->speed -= piece->defaultSpeed; //set to default waiting speed -0.1 every time its reset
    piece->defaultSpeed = piece->speed;
    piece->placed = false;
    piece->rotationCount = 0;
}

void managePiece(piece* piece, block grid[][GRIDWIDTH], int* frameCounter){
    int i, ii;

    if (*frameCounter > piece->speed*10){
        for (i = 0; i < PIECESIZE; i++){
            for (ii = 0; ii < PIECESIZE; ii++){
                piece->blocks[i][ii].rect.y += 32;
            }
        }
        *frameCounter = 0;
    }

    for (i = 0; i < PIECESIZE; i++)
        for (ii = 0; ii < PIECESIZE; ii++){
            if (piece->blocks[i][ii].rect.x < 0 && !piece->blocks[i][ii].air)
                move(1, piece);


            else if (piece->blocks[i][ii].rect.x > WIDTH-32 && !piece->blocks[i][ii].air)
                move(-1, piece);
    }
}

void manageInput(piece* piece, int* frameCounter){
    int i, ii;

    if (IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT)){
        for (i = 0; i < PIECESIZE; i++)
            for (ii = 0; ii < PIECESIZE; ii++)
                piece->blocks[i][ii].rect.x -= 32;
    }else if (IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT)){
        for (i = 0; i < PIECESIZE; i++)
            for (ii = 0; ii < PIECESIZE; ii++)
                piece->blocks[i][ii].rect.x += 32;
    }

    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)){
        piece->speed = 0.5;
    }else{
        piece->speed = 5;
    }

    if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)){
        rotatePiece(piece);
    }

    if (IsKeyDown(KEY_ENTER))
        *frameCounter -= 1;
}

void collidingPiece(piece* piece, block grid[][GRIDWIDTH], int* frameCounter){
    int i, ii;
    int ret;

    for (i = 0; i < PIECESIZE; i++){
        for (ii = 0; ii < PIECESIZE; ii++){
            ret = collidingWithGrid(&piece->blocks[i][ii], grid);

            if (piece->blocks[i][ii].rect.y >= HEIGHT-32 && !piece->blocks[i][ii].air){
                if (!buffer){
                    *frameCounter = 0;
                    buffer = true;
                }

                if (*frameCounter >= piece->speed*10){
                    printPieceOnGrid(piece, grid);
                    *frameCounter = 0;
                    buffer = false;
                }
            }else{
                switch (ret){
                    case 1:
                        if (!buffer){
                            *frameCounter = 0;
                            buffer = true;
                        }
                        
                        if (*frameCounter >= piece->speed*10){
                            printPieceOnGrid(piece, grid);
                            *frameCounter = 0;
                            buffer = false;
                        }
                    break;
                    case 2:
                        move(1, piece);
                    break;
                    case -2:
                        move(-1, piece);
                    break;
                }
            }
        }
    }
}



void printPieceOnGrid(piece* piece, block grid[][GRIDWIDTH]){
    int i, ii, iii, iv;

    for (i = 0; i < GRIDHEIGHT; i++){
        for (ii = 0; ii < GRIDWIDTH; ii++){

            for (iii = 0; iii < PIECESIZE; iii++){
                for (iv = 0; iv < PIECESIZE; iv++){
                    if (grid[i][ii].rect.x == piece->blocks[iii][iv].rect.x && grid[i][ii].rect.y == piece->blocks[iii][iv].rect.y && !piece->blocks[iii][iv].air){
                        grid[i][ii].air = false;
                        grid[i][ii].color = piece->blocks[iii][iv].color;
                    }
                }
            }

        }
    }

    setPiece(piece);
}

int collidingWithGrid(block* toCheck, block grid[][GRIDWIDTH]){
    int i, ii;

    for (i = 0; i < GRIDHEIGHT; i++){
        for (ii = 0; ii < GRIDWIDTH; ii++){
            if ((!grid[i][ii].air) && (!toCheck->air)){
                if (toCheck->rect.y+32 == grid[i][ii].rect.y && toCheck->rect.x == grid[i][ii].rect.x)
                    return 1;

                if (toCheck->rect.x == grid[i][ii].rect.x && toCheck->rect.y == grid[i][ii].rect.y){
                    if (IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT))
                        return 2;
                    else if (IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT))
                        return -2;
                }
            }
        }
    }

    return 0;
}



void drawAll(piece* piece, block grid[][GRIDWIDTH]){
    int i, ii;

    for (i = 0; i < PIECESIZE; i++){
        for (ii = 0; ii < PIECESIZE; ii++){
            if (!piece->blocks[i][ii].air){
                DrawRectangleRounded(piece->blocks[i][ii].rect, 0.2, 2, piece->blocks[i][ii].color);
            }
        }
    }

    for (i = 0; i < GRIDHEIGHT; i++){
        for (ii = 0; ii < GRIDWIDTH; ii++){
            if (!grid[i][ii].air)
                DrawRectangleRounded(grid[i][ii].rect, 0.2, 2, grid[i][ii].color);
        }
    }
}


void rotatePiece(piece* piece){
    int i, ii;

    if (piece->rotationCount >= 3){
        piece->rotationCount = 0;
    }else{
        piece->rotationCount += 1;
    }

    for (i = 0; i < PIECESIZE; i++){
        for (ii = 0; ii < PIECESIZE; ii++){
            if (templates[piece->id][piece->rotationCount][i][ii] == '1'){
                piece->blocks[i][ii].air = false;
            }else{
                piece->blocks[i][ii].air = true;
            }
        }
    }
}

void manageGrid(block grid[][GRIDWIDTH], int* score, int* score_times){
    int i, ii, iii;
    bool full;
    block temp;

    for (i = 0; i < GRIDHEIGHT; i++){
        full = true;

        for (ii = 0; ii < GRIDWIDTH; ii++){
            if (grid[i][ii].air)
                full = false;
        }

        if (full){
            *score_times += 1;

            for (ii = 0; ii < GRIDWIDTH; ii++){
                grid[i][ii].air = true;
            }

            for (ii = i; ii > 0; ii--){
                for (iii = 0; iii < GRIDWIDTH; iii++){
                    grid[ii][iii].air = grid[ii-1][iii].air;
                    grid[ii][iii].color = grid[ii-1][iii].color;
                }
            }
        }
    }
}


void move(int toWhere, piece* piece){
    int i, ii, where;

    if (toWhere == -1)
        where = -32;
    else
        where = 32;

    for (i = 0; i < PIECESIZE; i++){
        for (ii = 0; ii < PIECESIZE; ii++){
            piece->blocks[i][ii].rect.x += where;
        }
    }
}



void collidingWithGridHorizontally(piece* piece, block grid[][GRIDWIDTH]){
    //
}


void manageGameOver(block grid[][GRIDWIDTH], int* lost){
    int i;
    
    for (i = 0; i < GRIDWIDTH; i++){
        if (!grid[1][i].air || !grid[0][i].air){
            *lost = -1;
            return;
        }
    }
}


void getPause(int* frameCounter, int* counter){
    if (IsKeyPressed(KEY_SPACE) ){
        if (*counter == 0){
            *counter += 1;
        }else{
            *counter = 0;
        }
    }

    if (*counter == 0){
        *frameCounter -= 1;
    }
}

/********/


int mainMenu(){
    Rectangle buttons[2];
    int pos[2] = {0};
    int toReturn = -1;
    
    buttons[0] = (Rectangle){(WIDTH/2.0)-125, (HEIGHT/4.0)+30, 250, 50};
    buttons[1] = (Rectangle){(WIDTH/2.0)-125, (HEIGHT/2.0+HEIGHT/4.0)-70, 250, 50}; 

    while (!WindowShouldClose()){
        toReturn = manageMenu(buttons, pos);

        if (toReturn != -1)
            return toReturn;

        BeginDrawing();
            ClearBackground(DARKGRAY);

            drawMenu(buttons, pos);
        EndDrawing();
    }

    return -1;
}

int manageMenu(Rectangle* buttons, int* pos){
    int i;

    for (i = 0; i < 2; i++){
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), buttons[i])){
            if (pos[i] < 5)
                pos[i] = 5;
        }else{
            pos[i] = 0;
        }

        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && CheckCollisionPointRec(GetMousePosition(), buttons[i])){
            return i+1;
        }
    }

    return -1;
}


void drawMenu(Rectangle* buttons, int* pos){
    int i;

    for (i = 0; i < 2; i++){
        DrawRectangleRounded((Rectangle){buttons[i].x+5, buttons[i].y+5, buttons[i].width, buttons[i].height}, 0.2, 10, BLACK);
        
        DrawRectangleRounded((Rectangle){buttons[i].x+pos[i], buttons[i].y+pos[i], buttons[i].width, buttons[i].height}, 0.2, 10, LIGHTGRAY);
    }

    DrawText("cTetris", (WIDTH/2.0)-(MeasureText("cTetris", 40)/2.0), 50, 40, LIGHTGRAY);
    DrawText("Play", (WIDTH/2.0)-(MeasureText("Play", 30)/2.0)+pos[0], buttons[0].y+pos[0]+10, 30, BLACK);
    DrawText("Quit", (WIDTH/2.0)-(MeasureText("Quit", 30)/2.0)+pos[1], buttons[1].y+pos[1]+10, 30, BLACK);
}