#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "glut.h"

#pragma warning (disable: 4996)

struct tetrimino {
	double color[2];
	double mino[4][4];
};

struct rectangle {
	double pos[2];
	double size[2];
	double color[3];
};

//****************************global*********************************

double field[22][12] = {  // tetris field
						{ -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 },
						{ -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1 },
						{ -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1 },
						{ -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1 },
						{ -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1 },
						{ -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1 },
						{ -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1 },
						{ -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1 },
						{ -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1 },
						{ -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1 },
						{ -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1 },
						{ -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1 },
						{ -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1 },
						{ -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1 },
						{ -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1 },
						{ -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1 },
						{ -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1 },
						{ -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1 },
						{ -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1 },
						{ -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1 },
						{ -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1 },
						{ -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 }
						};

double nextfield[4][4] = {  // next mino
						 { -1,-1,-1,-1 },
						 { -1,-1,-1,-1 },
						 { -1,-1,-1,-1 },
						 { -1,-1,-1,-1 },
						};

// 0‹
double next0[7][4][4] = {
						{  // mino1
						 { 0,1,0,0 },
						 { 0,1,0,0 },
						 { 0,1,0,0 },
						 { 0,1,0,0 },
						},
						{  // mino2
						 { 0,0,0,0 },
						 { 0,2,2,0 },
						 { 0,2,2,0 },
						 { 0,0,0,0 },
						},
						{  // mino3
						 { 0,3,0,0 },
						 { 0,3,3,0 },
						 { 0,0,3,0 },
						 { 0,0,0,0 },
						},
						{  // mino4
						 { 0,0,4,0 },
						 { 0,4,4,0 },
						 { 0,4,0,0 },
						 { 0,0,0,0 },
						},
						{  // mino5
						 { 0,5,0,0 },
						 { 0,5,0,0 },
						 { 0,5,5,0 },
						 { 0,0,0,0 },
						},
						{  // mino6
						 { 0,0,6,0 },
						 { 0,0,6,0 },
						 { 0,6,6,0 },
						 { 0,0,0,0 },
						},
						{  // mino7
						 { 0,7,0,0 },
						 { 0,7,7,0 },
						 { 0,7,0,0 },
						 { 0,0,0,0 },
						}
					   };

// rotate 90
double next90[7][4][4] = {
						 {
						  { 0,0,0,0 },
						  { 1,1,1,1 },
						  { 0,0,0,0 },
						  { 0,0,0,0 },
						 },
						 {
						  { 0,0,0,0 },
						  { 0,2,2,0 },
						  { 0,2,2,0 },
						  { 0,0,0,0 },
						 },
						 {
						  { 0,0,0,0 },
						  { 0,3,3,0 },
						  { 3,3,0,0 },
						  { 0,0,0,0 },
						 },
						 {
						  { 0,0,0,0 },
						  { 4,4,0,0 },
						  { 0,4,4,0 },
						  { 0,0,0,0 },
						 },
						  {
						  { 0,0,0,0 },
						  { 0,5,5,5 },
						  { 0,5,0,0 },
						  { 0,0,0,0 },
	},
	{
		{ 0,0,0,0 },
		{ 0,6,0,0 },
		{ 0,6,6,6 },
		{ 0,0,0,0 },
	},
	{
		{ 0,0,0,0 },
		{ 7,7,7,0 },
		{ 0,7,0,0 },
		{ 0,0,0,0 },
	}
};

// rotate 180
double next180[7][4][4] = {
	{
		{ 0,1,0,0 },
		{ 0,1,0,0 },
		{ 0,1,0,0 },
		{ 0,1,0,0 },
	},
	{
		{ 0,0,0,0 },
		{ 0,2,2,0 },
		{ 0,2,2,0 },
		{ 0,0,0,0 },
	},
	{
		{ 0,3,0,0 },
		{ 0,3,3,0 },
		{ 0,0,3,0 },
		{ 0,0,0,0 },
	},
	{
		{ 0,0,4,0 },
		{ 0,4,4,0 },
		{ 0,4,0,0 },
		{ 0,0,0,0 },
	},
	{
		{ 0,0,0,0 },
		{ 0,5,5,0 },
		{ 0,0,5,0 },
		{ 0,0,5,0 },
	},
	{
		{ 0,0,0,0 },
		{ 0,6,6,0 },
		{ 0,6,0,0 },
		{ 0,6,0,0 },
	},
	{
		{ 0,7,0,0 },
		{ 7,7,0,0 },
		{ 0,7,0,0 },
		{ 0,0,0,0 },
	}
};

// rotate 270
double next270[7][4][4] = {
	{
		{ 0,1,0,0 },
		{ 0,1,0,0 },
		{ 0,1,0,0 },
		{ 0,1,0,0 },
	},
	{
		{ 0,0,0,0 },
		{ 0,2,2,0 },
		{ 0,2,2,0 },
		{ 0,0,0,0 },
	},
	{
		{ 0,0,0,0 },
		{ 0,3,3,0 },
		{ 3,3,0,0 },
		{ 0,0,0,0 },
	},
	{
		{ 0,0,0,0 },
		{ 4,4,0,0 },
		{ 0,4,4,0 },
		{ 0,0,0,0 },
	},
	{
		{ 0,0,0,0 },
		{ 0,0,5,0 },
		{ 5,5,5,0 },
		{ 0,0,0,0 },
	},
	{
		{ 0,0,0,0 },
		{ 0,0,0,0 },
		{ 6,6,6,0 },
		{ 0,0,6,0 },
	},
	{
		{ 0,7,0,0 },
		{ 7,7,7,0 },
		{ 0,0,0,0 },
		{ 0,0,0,0 },
	}
};

struct rectangle *newRect = NULL;
struct tetrimino *tetri;
struct tetrimino *nexttetri;
struct tetrimino *beforetetri;

double posBegin[2];
double posEnd[2];

int downcnt = 0;
int minoIndex = 0;
int nextminoIndex = 10;
int crash = 0;
int rotate_flag[4] = {0};
int right_flag = 0;
int right2_flag = 0;
int left_flag = 0;
int left2_flag = 0;
int side = 0;
int down = 0;
int r_side = 0;
int r_down = 0;
int Index = 0;
int rotation = 0;
int speed = 300;
int score = 0;
int level = 1;
int push_r = 0;
int push_l = 0;
int die;
int clear = 0;
int key_flag = 0;
int tmp = 0;

//***************************************************************************


void init(void) {
    glClearColor(0.0, 0.0, 0.0, 1.0);
}

void drawRect(struct rectangle *r, int flag) {
	glColor3d(r->color[0], r->color[1], r->color[2]);
	if (flag == 0) {
		glBegin(GL_LINE_LOOP);
	}
	else {
		glBegin(GL_POLYGON);
	}
	glVertex2d(r->pos[0], r->pos[1]);
	glVertex2d(r->pos[0] + r->size[0], r->pos[1]);
	glVertex2d(r->pos[0] + r->size[0], r->pos[1] - r->size[1]);
	glVertex2d(r->pos[0], r->pos[1] - r->size[1]);
	glEnd();
}

void randMino() {
	int i, j;
    int ran;
	int randnum = 0;

	randnum = tmp * Index % 5;
	if (randnum == 1) {
		speed = 50;
	}
	else {
		speed = 300;
	}
	tmp++;

	if (nextminoIndex == 10) {
		tetri = (struct tetrimino *)malloc(sizeof(struct tetrimino));
		nexttetri = (struct tetrimino *)malloc(sizeof(struct tetrimino));
		beforetetri = (struct tetrimino *)malloc(sizeof(struct tetrimino));

		minoIndex = rand() % 7;
		for (i = 0; i < 4; i++) {
			for (j = 0; j < 4; j++) {
				tetri->mino[i][j] = next0[minoIndex][i][j];
				beforetetri->mino[i][j] = next0[minoIndex][i][j];
			}
		}
        Index = minoIndex;
	}
	else {
		for (i = 0; i < 4; i++) {
			for (j = 0; j < 4; j++) {
				tetri->mino[i][j] = nexttetri->mino[i][j];
				beforetetri->mino[i][j] = nexttetri->mino[i][j];
			}
		}
        Index = nextminoIndex;
	}
	srand((unsigned int)time(NULL));
	nextminoIndex = rand() % 7;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			nexttetri->mino[i][j] = next0[nextminoIndex][i][j];
		}
	}
}

int gameOver(){
    int i,j;
    int ded_flag = 0;
    char str[20];
    
    for (j = 1; j < 11; j++) {
        if (field[1][j] != 0) {
            ded_flag++;
        }
    }
    if (ded_flag > 0) {
        return 1;
    }else{
        return 0;
    }
}

void display(void) {

	int i, j, k;
	int flag[22][12];
    int n_flag[4][4];
	double pos0 = -0.6;
	double pos1 = 0.8;
    double n_pos0 = 0.1;
    double n_pos1 = 0.7;
	double size0 = 0.05;
	double size1 = 0.05;
    double n_size0 = 0.05;
    double n_size1 = 0.05;
    char str1[20];
    char str2[20];
    char str3[20];
    char str4[20];
    char str5[20];
    char str6[20];
    char str7[20];
    char str8[20];
	struct rectangle *rect[22][12];
    struct rectangle *nextrect[4][4];

	glClear(GL_COLOR_BUFFER_BIT);
	
	for (i = 0; i < 22; i++) {
		for (j = 0; j < 12; j++) {
			rect[i][j] = (struct rectangle *)malloc(sizeof(struct rectangle));
		}
	}
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            nextrect[i][j] = (struct rectangle *)malloc(sizeof(struct rectangle));
        }
    }
    
	for (i = 0; i < 22; i++) {
		for (j = 0; j < 12; j++) {
			rect[i][j]->pos[0] = pos0;
			rect[i][j]->pos[1] = pos1;
			rect[i][j]->size[0] = size0;
			rect[i][j]->size[1] = size1;
			pos0 += 0.05;
		}
		pos1 -= 0.05;
		pos0 = -0.6;
	}
    
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            nextrect[i][j]->pos[0] = n_pos0;
            nextrect[i][j]->pos[1] = n_pos1;
            nextrect[i][j]->size[0] = n_size0;
            nextrect[i][j]->size[1] = n_size1;
            n_pos0 += 0.05;
        }
        n_pos1 -= 0.05;
        n_pos0 = 0.1;
    }
    
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if(nexttetri->mino[i][j] != 0){
                nextfield[i][j] = nexttetri->mino[i][j];
            }else{
                nextfield[i][j] = -1;
            }
        }
    }

	for (i = 0; i < 22; i++) {
		for (j = 0; j < 12; j++) {
			if (field[i][j] == -1) {
				rect[i][j]->color[0] = 0.5;
				rect[i][j]->color[1] = 0.5;
				rect[i][j]->color[2] = 0.5;
				flag[i][j] = 0;
			}
			else if (field[i][j] == 0) {
				rect[i][j]->color[0] = 0.0;
				rect[i][j]->color[1] = 0.0;
				rect[i][j]->color[2] = 0.0;
				flag[i][j] = 1;
			}
			else if (field[i][j] == 1) {
				rect[i][j]->color[0] = 0.0;
				rect[i][j]->color[1] = 1.0;
				rect[i][j]->color[2] = 1.0;
				flag[i][j] = 1;
			}
			else if (field[i][j] == 2) {
				rect[i][j]->color[0] = 1.0;
				rect[i][j]->color[1] = 1.0;
				rect[i][j]->color[2] = 0.0;
				flag[i][j] = 1;
			}
			else if (field[i][j] == 3) {
				rect[i][j]->color[0] = 0.0;
				rect[i][j]->color[1] = 1.0;
				rect[i][j]->color[2] = 0.0;
				flag[i][j] = 1;
			}
			else if (field[i][j] == 4) {
				rect[i][j]->color[0] = 1.0;
				rect[i][j]->color[1] = 0.0;
				rect[i][j]->color[2] = 0.0;
				flag[i][j] = 1;
			}
			else if (field[i][j] == 5) {
				rect[i][j]->color[0] = 1.0;
				rect[i][j]->color[1] = 0.5;
				rect[i][j]->color[2] = 0.0;
				flag[i][j] = 1;
			}
			else if (field[i][j] == 6) {
				rect[i][j]->color[0] = 0.0;
				rect[i][j]->color[1] = 0.0;
				rect[i][j]->color[2] = 1.0;
				flag[i][j] = 1;
			}
			else if (field[i][j] == 7) {
				rect[i][j]->color[0] = 0.5;
				rect[i][j]->color[1] = 0.0;
				rect[i][j]->color[2] = 0.5;
				flag[i][j] = 1;
			}
		}
	}
    
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (nextfield[i][j] == -1) {
                nextrect[i][j]->color[0] = 0.5;
                nextrect[i][j]->color[1] = 0.5;
                nextrect[i][j]->color[2] = 0.5;
                n_flag[i][j] = 0;
            }
            else if (nextfield[i][j] == 0) {
                nextrect[i][j]->color[0] = 0.0;
                nextrect[i][j]->color[1] = 0.0;
                nextrect[i][j]->color[2] = 0.0;
                n_flag[i][j] = 1;
            }
            else if (nextfield[i][j] == 1) {
                nextrect[i][j]->color[0] = 0.0;
                nextrect[i][j]->color[1] = 1.0;
                nextrect[i][j]->color[2] = 1.0;
                n_flag[i][j] = 1;
            }
            else if (nextfield[i][j] == 2) {
                nextrect[i][j]->color[0] = 1.0;
                nextrect[i][j]->color[1] = 1.0;
                nextrect[i][j]->color[2] = 0.0;
                n_flag[i][j] = 1;
            }
            else if (nextfield[i][j] == 3) {
                nextrect[i][j]->color[0] = 0.0;
                nextrect[i][j]->color[1] = 1.0;
                nextrect[i][j]->color[2] = 0.0;
                n_flag[i][j] = 1;
            }
            else if (nextfield[i][j] == 4) {
                nextrect[i][j]->color[0] = 1.0;
                nextrect[i][j]->color[1] = 0.0;
                nextrect[i][j]->color[2] = 0.0;
                n_flag[i][j] = 1;
            }
            else if (nextfield[i][j] == 5) {
                nextrect[i][j]->color[0] = 1.0;
                nextrect[i][j]->color[1] = 0.5;
                nextrect[i][j]->color[2] = 0.0;
                n_flag[i][j] = 1;
            }
            else if (nextfield[i][j] == 6) {
                nextrect[i][j]->color[0] = 0.0;
                nextrect[i][j]->color[1] = 0.0;
                nextrect[i][j]->color[2] = 1.0;
                n_flag[i][j] = 1;
            }
            else if (nextfield[i][j] == 7) {
                nextrect[i][j]->color[0] = 0.5;
                nextrect[i][j]->color[1] = 0.0;
                nextrect[i][j]->color[2] = 0.5;
                n_flag[i][j] = 1;
            }
        }
    }
    
	for (i = 0; i < 22; i++) {
		for (j = 0; j < 12; j++) {
			drawRect(rect[i][j],flag[i][j]);
		}
	}

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            drawRect(nextrect[i][j],n_flag[i][j]);
        }
    }

    sprintf(str1 , " NEXT ");
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(0.1125,0.75);
    for (i = 0; i < strlen(str1); i++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, str1[i]);
    }
    
    sprintf(str2, " Score : %07d ", score);
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(0, 0.4);
    for (i = 0; i < strlen(str2); i++) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, str2[i]);
    }
    
    sprintf(str3, " Level : %d ", level);
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(0, 0.35);
    for (i = 0; i < strlen(str3); i++) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, str3[i]);
    }
    
    sprintf(str4, " -> : Right");
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(0, 0);
    for (i = 0; i < strlen(str4); i++) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, str4[i]);
    }
    
    sprintf(str5, " <- : Left");
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(0, -0.05);
    for (i = 0; i < strlen(str5); i++) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, str5[i]);
    }
    
    sprintf(str6, "    : Down");
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(0, -0.1);
    for (i = 0; i < strlen(str6); i++) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, str6[i]);
    }
    
    sprintf(str7, "  Z : rotation");
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2f(0, -0.15);
    for (i = 0; i < strlen(str7); i++) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, str7[i]);
    }
    
    if (die == 1){
        sprintf(str8 , " GAME OVER ");
        glColor3f(1.0, 1.0, 1.0);
        glRasterPos2f(-0.54,0.3);
        for (i = 0; i < strlen(str8); i++) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str8[i]);
        }
    }

	if (clear == 1) {
		sprintf(str8, " GAME CLEAR ");
		glColor3f(1.0, 1.0, 1.0);
		glRasterPos2f(-0.555, 0.3);
		for (i = 0; i < strlen(str8); i++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str8[i]);
		}
	}
    
    glBegin(GL_LINE_LOOP);
    glVertex2d(0.05,-0.075);
    glVertex2d(0.05,-0.095);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2d(0.035,-0.095);
    glVertex2d(0.05,-0.11);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2d(0.065,-0.095);
    glVertex2d(0.05,-0.11);
    glEnd();
    
    glFlush();

	glutSwapBuffers();

}

void delMino() {
    int i,j,k;
    int del_cnt[22] = {0};
    
    for (i = 1; i < 21; i++) {
        for (j = 1; j < 11; j++) {
            if (field[i][j] == 0) {
                del_cnt[i]++;
            }
        }
    }
    
    for (i = 1; i < 21; i++) {
        if (del_cnt[i] == 0) {
            if (del_cnt[i+1] == 0) {
                if (del_cnt[i+2] == 0) {
                    if (del_cnt[i+3] == 0) {
                        score += 400;
                    }
                    score += 300;
                }
                score += 200;
            }
            score += 100;
            if(score >= 1000) {
                level += 1;
            }
			if (score >= 2000) {
				level += 1;
			}
			if (score >= 3000) {
				level += 1;
			}
			if (score >= 4000) {
				level += 1;
			}
			if (score >= 5000) {
				level += 1;
			}
            for (j = 1; j < 11; j++) {
                field[i][j] = 0;
            }
            for (k = i; k > 1; k--) {
                for (j = 1; j < 11; j++) {
                    field[k][j] = field[k-1][j];
                }
            }
        }
    }
}

void updatePos(int value) {
	int i,j;
	int crash_flag = 0;
    char str8[20];
    push_r = 0;
    push_l = 0;
    
	if (downcnt > 0) {
		for (i = (1 + downcnt); i <= (4 + downcnt); i++) {
			for (j = 4; j <= 7; j++) {
                if (beforetetri->mino[i - downcnt - 1][j - 4] == field[i - 1][j + r_side]) {
                    field[i - 1][j + r_side] = 0;
                }
			}
		}
	}

	// field update check
	for (i = (1 + downcnt); i <= (4 + downcnt); i++) {
		for (j = 4; j <= 7; j++) {
			if (field[i + 1][j + side] != 0 && tetri->mino[i - downcnt - 1][j - 4] > 0) {
				crash_flag = 1;
			}
		}
	}
    
    // right or left check
    right_flag = 0;
    left_flag = 0;
    right2_flag = 0;
    left2_flag = 0;
    for (i = (1 + downcnt); i <= (4 + downcnt); i++) {
        for (j = 4; j <= 7; j++) {
            if (field[i + 1][j + side + 1] != 0 && tetri->mino[i - downcnt - 1][j - 4] > 0) {
                right_flag = 1;
            }
            if (field[i + 1][j + side + 2] != 0 && tetri->mino[i - downcnt - 1][j - 4] > 0) {
                right2_flag = 1;
            }
            if (field[i + 1][j + side - 1] != 0 && tetri->mino[i - downcnt - 1][j - 4] > 0) {
                left_flag = 1;
            }
            if (field[i + 1][j + side - 2] != 0 && tetri->mino[i - downcnt - 1][j - 4] > 0) {
                left2_flag = 1;
            }
        }
    }
    
    // rotate check
    for (i = 0; i < 4; i++) {
        rotate_flag[i] = 0;
    }
    for (i = (1 + downcnt); i <= (4 + downcnt); i++) {
        for (j = 4; j <= 7; j++) {
            if (field[i + 1][j + side] != 0 && next0[Index][i - downcnt - 1][j - 4] > 0) {
                rotate_flag[0] = 1;
            }
            if (field[i + 1][j + side] != 0 && next90[Index][i - downcnt - 1][j - 4] > 0) {
                rotate_flag[1] = 1;
            }
            if (field[i + 1][j + side] != 0 && next180[Index][i - downcnt - 1][j - 4] > 0) {
                rotate_flag[2] = 1;
            }
            if (field[i + 1][j + side] != 0 && next270[Index][i - downcnt - 1][j - 4] > 0) {
                rotate_flag[3] = 1;
            }
        }
    }
    
	// field update
	for (i = (1 + downcnt); i <= (4 + downcnt); i++) {
		for (j = 4; j <= 7; j++) {
			if (field[i][j + side] == 0) {
				field[i][j + side] += tetri->mino[i - downcnt - 1][j - 4];
			}
		}
	}
	if (crash_flag == 0){
		downcnt++;
		r_side = side;
		key_flag = 0;
	}
	else {
		downcnt = 0;
		r_side = 0;
        delMino();
		randMino();
        die = gameOver();
        if (die == 1){
            glutDisplayFunc(display);
            speed += 10000000;
        }
		side = 0;
		rotation = 0;
		// game clear check
		if (level >= 5) {
			clear = 1;
			glutDisplayFunc(display);
			speed += 10000000;
		}
	}
    
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            beforetetri->mino[i][j] = tetri->mino[i][j];
        }
    }
	for (i = 0; i < 22; i++) {
		for (j = 0; j < 12; j++) {
			printf("%.1f ", field[i][j]);
		}
		printf("\n");
	}

	glutPostRedisplay();
	glutTimerFunc(speed, updatePos, 0);
}

void keyboard(int key, int x, int y) {
	int i, j;
	int a;

	if (Index == 0 || Index == 6) {
		a = 5;
	}
	else {
		a = 4;
	}
 
	if (key == GLUT_KEY_LEFT) {
		if (side > -4 && left_flag == 0 && push_l < 1) {
			side--;
		}
        if (push_l == 1){
            if (side > -4 && left2_flag == 0) {
                side--;
            }
        }
        push_l++;
    }
    
	if (key == GLUT_KEY_RIGHT) {
        if (side < a && right_flag == 0 && push_r < 1) {
            side++;
        }
        if (push_r == 1){
            if (side < a && right2_flag == 0) {
                side++;
            }
        }
        push_r++;
	}
    
	if (key == GLUT_KEY_DOWN) {
		speed = 50;
	}

	key_flag = 1;
}

void keyboard2(unsigned char key, int x, int y) {
	int i, j;
	int a;

	if (Index == 6) {
		a = 5;
	}
	else {
		a = 4;
	}

	if (key == 'z') {
		if (side != a && side != -4 && key_flag == 0) {
			rotation++;
			if (rotation > 3) {
				rotation = 0;
			}
			for (i = 0; i < 4; i++) {
				for (j = 0; j < 4; j++) {
					if (rotation == 0) {
						if (rotate_flag[0] == 0) {
							tetri->mino[i][j] = next0[Index][i][j];
						}
						else if (rotate_flag[1] == 0) {
							tetri->mino[i][j] = next90[Index][i][j];
							rotation = 1;
						}
						else {
							rotation = 3;
						}
					}
					if (rotation == 1) {
						if (rotate_flag[1] == 0) {
							tetri->mino[i][j] = next90[Index][i][j];
						}
						else if (rotate_flag[2] == 0) {
							tetri->mino[i][j] = next180[Index][i][j];
							rotation = 2;
						}
						else {
							rotation--;
						}
					}
					if (rotation == 2) {
						if (rotate_flag[2] == 0) {
							tetri->mino[i][j] = next180[Index][i][j];
						}
						else if (rotate_flag[3] == 0) {
							tetri->mino[i][j] = next270[Index][i][j];
							rotation = 3;
						}
						else {
							rotation--;
						}
					}
					if (rotation == 3) {
						if (rotate_flag[3] == 0) {
							tetri->mino[i][j] = next270[Index][i][j];
						}
						else if (rotate_flag[0] == 0) {
							tetri->mino[i][j] = next0[Index][i][j];
							rotation = 0;
						}
						else {
							rotation--;
						}
					}
				}
			}
		}
	}
}

void keyUp(int key, int x, int y) {
	if (key == GLUT_KEY_DOWN) {
            speed = 300 - (5 * level);
	}
}

int main(int argc, char *argv[]) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(640, 640);
	glutCreateWindow(argv[0]);
	randMino();
	glutSpecialFunc(keyboard);
	glutKeyboardFunc(keyboard2);
	glutSpecialUpFunc(keyUp);
	glutDisplayFunc(display);
	glutTimerFunc(speed, updatePos, 0);

	init();
	glutMainLoop();
	return EXIT_SUCCESS;
}
