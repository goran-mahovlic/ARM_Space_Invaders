/***************************************************************************
 * STM32 VGA demo
 * Copyright (C) 2012 Artekit Italy
 * http://www.artekit.eu
 * Written by Ruben H. Meleca
 
### space_invaders.c
 
#   This program is free software; you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation; either version 2 of the License, or
#   (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with this program; if not, write to the Free Software
#   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

***************************************************************************/

#include "stm32f10x.h"
#include "sys.h"
#include "video.h"
#include "gdi.h"
#include "space_invaders.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

extern u8				siLogo[VID_VSIZE][VID_HSIZE];
extern volatile u32		sysTicks;

const u8	siBadBoys99[] = {	0x00, 0x00,
								0x00, 0x00,
								0x21, 0x08,
								0x11, 0x10,
								0x09, 0x20,
								0x00, 0x00,
								0x00, 0x00,
								0x09, 0x20,
								0x11, 0x10,
								0x21, 0x08,
								0x00, 0x00,
								0x00, 0x00 };

const u8	siBadBoys00[] = {	0x00, 0x00,
								0x00, 0x00,
								0x00, 0x00,
								0x00, 0x00,
								0x00, 0x00,
								0x00, 0x00,
								0x00, 0x00,
								0x00, 0x00,
								0x00, 0x00,
								0x00, 0x00,
								0x00, 0x00,
								0x00, 0x00 };

const u8	siBadBoys01[] = {	0x00, 0x00,
								0x00, 0x00,
								0x03, 0x80,
								0x07, 0xc0,
								0x0f, 0xe0,
								0x1b, 0xb0,
								0x1f, 0xf0,
								0x04, 0x40,
								0x0b, 0xa0,
								0x14, 0x50,
								0x00, 0x00,
								0x00, 0x00 };

const u8	siBadBoys02[] = {	0x00, 0x00,
								0x00, 0x00,
								0x03, 0x80,
								0x07, 0xc0,
								0x0f, 0xe0,
								0x1b, 0xb0,
								0x1f, 0xf0,
								0x04, 0x40,
								0x0b, 0xa0,
								0x08, 0x20,
								0x00, 0x00,
								0x00, 0x00 };


const u8	siBadBoys11[] = {	0x00, 0x00,
								0x00, 0x00,
								0x08, 0x20,
								0x04, 0x40,
								0x0f, 0xe0,
								0x1b, 0xb0,
								0x3f, 0xf8,
								0x2f, 0xe8,
								0x28, 0x28,
								0x06, 0xc0,
								0x00, 0x00,
								0x00, 0x00 };

const u8	siBadBoys12[] = {	0x00, 0x00,
								0x00, 0x00,
								0x08, 0x20,
								0x24, 0x48,
								0x2f, 0xe8,
								0x3b, 0xb8,
								0x3f, 0xf8,
								0x1f, 0xf0,
								0x08, 0x20,
								0x10, 0x10,
								0x00, 0x00,
								0x00, 0x00 };

const u8	siBadBoys21[] = {	0x00, 0x00,
								0x00, 0x00,
								0x07, 0xc0,
								0x1f, 0xf0,
								0x3f, 0xf8,
								0x33, 0x98,
								0x3f, 0xf8,
								0x0c, 0x60,
								0x1b, 0xb0,
								0x30, 0x18,
								0x00, 0x00,
								0x00, 0x00 };

const u8	siBadBoys22[] = {	0x00, 0x00,
								0x00, 0x00,
								0x07, 0xc0,
								0x1f, 0xf0,
								0x3f, 0xf8,
								0x33, 0x98,
								0x3f, 0xf8,
								0x0c, 0x60,
								0x1b, 0xb0,
								0x0c, 0x60,
								0x00, 0x00,
								0x00, 0x00 };

const u8	siGoodBoys[] = {	0x00, 0x18, 0x00,
								0x00, 0x18, 0x00,
								0x00, 0x3c, 0x00,
								0x00, 0xff, 0x00,
								0x0f, 0xff, 0xf0,
								0x3f, 0xff, 0xfc,
								0x3f, 0xff, 0xfc,
								0x3f, 0xff, 0xfc,
								0x3c, 0x00, 0x3c };

const u8	siGoodBoysBlk[] = {	0x00, 0x00, 0x00,
								0x00, 0x00, 0x00,
								0x00, 0x00, 0x00,
								0x00, 0x00, 0x00,
								0x00, 0x00, 0x00,
								0x00, 0x00, 0x00,
								0x00, 0x00, 0x00,
								0x00, 0x00, 0x00,
								0x00, 0x00, 0x00 };

const u8	siBadBomb00[] = {	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
								0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
const u8	siBadBomb01[] = {	0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x40,
								0x80, 0x40, 0x20, 0x40, 0x80, 0x40, 0x20 };
const u8	siBadBomb02[] = {	0x00, 0x00, 0x00, 0x20, 0x40, 0x80, 0x40,
								0x20, 0x40, 0x80, 0x40, 0x20, 0x40, 0x80 };

const u8	siGoodBomb1[] = {	0xc0, 0xc0, 0xc0, 0x00, 0x00, 0x00 };
const u8	siGoodBomb2[] = {	0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };


const u8	siDefs1[] = {		0xe0, 0xe0, 0xe0, 0xe0, 0xe0 };
const u8	siDefs2[] = {		0x00, 0x00, 0x00, 0x00, 0x00 };

const pu8	siVesselPoints[] = {
				"= 30 POINTS",
				"= 20 POINTS",
				"= 10 POINTS" };

const pu8	siPressKey = "PRESS ANY BUTTON TO START GAME";

static SI_BADBOY	sibb[SI_MAXBADBOYS_ROWS][SI_MAXBADBOYS_COLS];
static SI_BOMB		siBomb[SI_MAXBADBOYSBOMB];
static SI_DEFENSE	sidef1[SI_MAXDEFENSES_ROWS][SI_MAXDEFENSES_COLS];
static SI_DEFENSE	sidef2[SI_MAXDEFENSES_ROWS][SI_MAXDEFENSES_COLS];
static SI_DEFENSE	sidef3[SI_MAXDEFENSES_ROWS][SI_MAXDEFENSES_COLS];
static SI_DEFENSE	sidef4[SI_MAXDEFENSES_ROWS][SI_MAXDEFENSES_COLS];

static	i16			siXGoodBoy = SI_GOODBOYSTART_X;
static	i16			siYGoodBoy = SI_GOODBOYSTART_Y;

static	i16			siGoodBoyCount;
static	i16			siGoodBoyCountOld;

static	i16			siGoodBoysKeyDelay;
static	i16			siGoodBombDelay;
static	i16			siGoodBombActive;
static	i16			siGoodBombX;
static	i16			siGoodBombY;
static	i16			siGoodBombKeyState;

static	i16			siCurrentScore;
static	i16			siBakScore;
static	i16			siBestScore;

static	i16			siBadBoysDelay;
static	i16			siBadBoysShiftX;
static	i16			siBadBoysShiftY;
static	i16			siBadBoysMode;
static	i16			siBadBoysFlip;
static	i16			siBadBoysYCount;
static	i16			siBadBoysBombDelay;
static	i16			siBadBombMoveDelay;
static	i16			siBadBoysCount;				// Count Bad Boys. If 0, you win
static	i16			siBadBoyBombOK = 1;			// 1 = fire bombs, 0 = No

static	u8			siScore[24];

u8	siAnyButtonPressed(void) {

u32		b;

	b = GPIOA->IDR;
	if ((b & 0x00000031) != (SI_FIRE_BUTTON | SI_LEFT_BUTTON | SI_RIGHT_BUTTON)) return(1);
	return(0);
}

void siYouWin(void) {

	vidClearScreen();
	gdiRectangle(0,0,(VID_PIXELS_X - 1),VID_VSIZE - 1,0);

	gdiDrawTextEx(167,80,"* YOU WIN *",GDI_ROP_XOR);
	while(1) {
		if (siAnyButtonPressed()) return;
		gdiDrawTextEx(108,170,siPressKey,GDI_ROP_XOR);
		sysDelayMs(400);
		if (siAnyButtonPressed()) return;
		gdiDrawTextEx(108,170,siPressKey,GDI_ROP_XOR);
		if (siAnyButtonPressed()) return;
		sysDelayMs(200);
	};
}

void siYouLose(void) {

	vidClearScreen();
	gdiRectangle(0,0,(VID_PIXELS_X - 1),VID_VSIZE - 1,0);

	gdiDrawTextEx(164,80,"* YOU LOSE *",GDI_ROP_XOR);
	while(1) {
		if (siAnyButtonPressed()) return;
		gdiDrawTextEx(108,170,siPressKey,GDI_ROP_XOR);
		sysDelayMs(400);
		if (siAnyButtonPressed()) return;
		gdiDrawTextEx(108,170,siPressKey,GDI_ROP_XOR);
		if (siAnyButtonPressed()) return;
		sysDelayMs(200);
	};

}

void siInitialScreen(void) {

u16		i, x, y, l, j;
pu8		ptr = NULL;
u8		buf[] = " ";

	vidClearScreen();

	gdiRectangle(0,0,(VID_PIXELS_X - 1),VID_VSIZE - 1,0);

	gdiDrawTextEx(180, 40, "ARTEKIT", GDI_ROP_COPY);
	gdiDrawTextEx(156, 55, "SPACE INVADERS", GDI_ROP_COPY);
	gdiDrawTextEx(180, 70, "LEVEL I", GDI_ROP_COPY);

	sysDelayMs(1000);

	gdiDrawTextEx(130,110,"* SCORE ADVANCE TABLE *",GDI_ROP_XOR);
	sysDelayMs(400);
	y = 125;
	for (i = 0; i < 3; i++) {
		x = 155;
		switch(i) {
			case 0:		ptr = (pu8) siBadBoys01;
						break;
			case 1:		ptr = (pu8) siBadBoys11;
						break;
			case 2:		ptr = (pu8) siBadBoys21;
						break;
		}
		gdiBitBlt(NULL,x,y,15,12,ptr,GDI_ROP_COPY);
		x += 20;
		l = strlen((const char*)siVesselPoints[i]);
		ptr = siVesselPoints[i];
		for (j = 0; j < l; j++) {
			sysDelayMs(25);
			buf[0] = *ptr++;
			gdiDrawTextEx(x,y + 2,buf,GDI_ROP_COPY);
			x += 6;
		}
		y += 12;
		sysDelayMs(300);
	}
	while(1) {
		if (siAnyButtonPressed()) return;
		gdiDrawTextEx(108,170,siPressKey,GDI_ROP_XOR);
		sysDelayMs(400);
		if (siAnyButtonPressed()) return;
		gdiDrawTextEx(108,170,siPressKey,GDI_ROP_XOR);
		if (siAnyButtonPressed()) return;
		sysDelayMs(200);

	};

}

void siShiftBadboys(void) {

	if (!siBadBoysMode) {
		if (++siBadBoysShiftX >= 50) {
			siBadBoysMode = 1;
			siBadBoysShiftX -= 2;
			siBadBoysShiftY += 2;
			if (siBadBoysYCount < 459) siBadBoysYCount += SI_BADBOYSSPEEDCOUNT;
		} else {
			siBadBoysShiftX += 1;
		}
	} else {
		if (--siBadBoysShiftX < 2) {
			siBadBoysMode = 0;
			siBadBoysShiftX += 2;
			siBadBoysShiftY += 2;
			if (siBadBoysYCount < 459) siBadBoysYCount += SI_BADBOYSSPEEDCOUNT;
		} else {
			siBadBoysShiftX -= 1;
		}
	}

	(siBadBoysFlip == 0) ? (siBadBoysFlip = 1) : (siBadBoysFlip = 0);
}

void siDrawBadboys(void) {

u16		i, n;

	if (--siBadBoysDelay > 0) return;
	siBadBoysDelay = SI_BADBOYSSTARTDELAY - siBadBoysYCount;
	for (i = 0; i < SI_MAXBADBOYS_ROWS; i++) {
		for (n = 0; n < SI_MAXBADBOYS_COLS; n++) {
			if (sibb[i][n].mode == SI_ALIVE) {
				if (!siBadBoysFlip) {
					gdiBitBlt(NULL,sibb[i][n].x + siBadBoysShiftX,sibb[i][n].y + siBadBoysShiftY,15,12,sibb[i][n].b1,GDI_ROP_COPY);
				} else {
					gdiBitBlt(NULL,sibb[i][n].x + siBadBoysShiftX,sibb[i][n].y + siBadBoysShiftY,15,12,sibb[i][n].b2,GDI_ROP_COPY);
				}
			} else {
				if (sibb[i][n].mode == SI_DESTROYED) {
					sibb[i][n].mode = SI_CANCEL;
					gdiBitBlt(NULL,sibb[i][n].x + siBadBoysShiftX,sibb[i][n].y + siBadBoysShiftY,15,12,(pu8) siBadBoys99,GDI_ROP_COPY);
				} else {
					if (sibb[i][n].mode == SI_CANCEL) {
						sibb[i][n].mode = SI_DEAD;
						gdiBitBlt(NULL,sibb[i][n].x + siBadBoysShiftX,sibb[i][n].y + siBadBoysShiftY,15,12,(pu8) siBadBoys00,GDI_ROP_COPY);
					}
				}
			}
		}
	}
	siShiftBadboys();
}

void siShowDefenses(void) {

u16		i, j, n;

	for (i = 0; i < 4; i++) {
		for (j = 0; j < SI_MAXDEFENSES_ROWS; j++) {
			for (n = 0; n < SI_MAXDEFENSES_COLS; n++) {
				switch(i) {
					case 0:		if (sidef1[j][n].mode == SI_ALIVE) {
									gdiBitBlt(NULL,sidef1[j][n].x,sidef1[j][n].y,3,5,(pu8) siDefs1,GDI_ROP_COPY);
								} else {
									gdiBitBlt(NULL,sidef1[j][n].x,sidef1[j][n].y,3,5,(pu8) siDefs2,GDI_ROP_COPY);
								}
								break;
					case 1:		if (sidef2[j][n].mode == SI_ALIVE) {
									gdiBitBlt(NULL,sidef2[j][n].x,sidef2[j][n].y,3,5,(pu8) siDefs1,GDI_ROP_COPY);
								} else {
									gdiBitBlt(NULL,sidef2[j][n].x,sidef2[j][n].y,3,5,(pu8) siDefs2,GDI_ROP_COPY);
								}
								break;
					case 2:		if (sidef3[j][n].mode == SI_ALIVE) {
									gdiBitBlt(NULL,sidef3[j][n].x,sidef3[j][n].y,3,5,(pu8) siDefs1,GDI_ROP_COPY);
								} else {
									gdiBitBlt(NULL,sidef3[j][n].x,sidef3[j][n].y,3,5,(pu8) siDefs2,GDI_ROP_COPY);
								}
								break;
					case 3:		if (sidef4[j][n].mode == SI_ALIVE) {
									gdiBitBlt(NULL,sidef4[j][n].x,sidef4[j][n].y,3,5,(pu8) siDefs1,GDI_ROP_COPY);
								} else {
									gdiBitBlt(NULL,sidef4[j][n].x,sidef4[j][n].y,3,5,(pu8) siDefs2,GDI_ROP_COPY);
								}
								break;


				}
			}
		}
	}
}

void siMoveGoodBoys(void) {

	if (--siGoodBoysKeyDelay > 0) return;
	siGoodBoysKeyDelay = SI_GOODBOYSKEYDELAY;
	if ((GPIOA->IDR & SI_LEFT_BUTTON) == 0) {
		if (siXGoodBoy > 8) {
			siXGoodBoy -= 2;
			gdiBitBlt(NULL,siXGoodBoy,siYGoodBoy,24,9,(pu8) siGoodBoys,GDI_ROP_COPY);
		}
	}
	if ((GPIOA->IDR & SI_RIGHT_BUTTON) == 0) {
		if (siXGoodBoy < 290) {
			siXGoodBoy += 2;
			gdiBitBlt(NULL,siXGoodBoy,siYGoodBoy,24,9,(pu8) siGoodBoys,GDI_ROP_COPY);
		}
	}


}

void siMoveGoodBomb(void) {

i16		d, i, n;

	if (!siGoodBombActive) return;
	if (--siGoodBombDelay > 0) return;
	siGoodBombDelay = SI_GOODBOMBDELAY;

	gdiBitBlt(NULL,siGoodBombX,siGoodBombY,2,6,(pu8) siGoodBomb1,GDI_ROP_COPY);

//	Test if bomb touch defenses

	for (d = 0; d < 4; d++) {
		for (i = 0; i < SI_MAXDEFENSES_ROWS; i++) {
			for (n = 0; n < SI_MAXDEFENSES_COLS; n++) {
				switch(d) {
					case 0:		if (sidef1[i][n].mode == SI_ALIVE) {
									if (siGoodBombX >= sidef1[i][n].x && siGoodBombX <= (sidef1[i][n].x + 3)) {
										if (siGoodBombY <= (sidef1[i][n].y + 5) && siGoodBombY >= sidef1[i][n].y) {
											sidef1[i][n].mode = SI_DEAD;
											gdiBitBlt(NULL,sidef1[i][n].x,sidef1[i][n].y,3,5,(pu8) siDefs2,GDI_ROP_COPY);
											gdiBitBlt(NULL,siGoodBombX,siGoodBombY,2,6,(pu8) siGoodBomb2,GDI_ROP_COPY);
											siGoodBombActive = 0;
//											siShowDefenses();
											return;
										}
									}
								}
								break;
					case 1:		if (sidef2[i][n].mode == SI_ALIVE) {
									if (siGoodBombX >= sidef2[i][n].x && siGoodBombX <= (sidef2[i][n].x + 3)) {
										if (siGoodBombY <= (sidef2[i][n].y + 5) && siGoodBombY >= sidef2[i][n].y) {
											sidef2[i][n].mode = SI_DEAD;
											gdiBitBlt(NULL,sidef2[i][n].x,sidef2[i][n].y,3,5,(pu8) siDefs2,GDI_ROP_COPY);
											gdiBitBlt(NULL,siGoodBombX,siGoodBombY,2,6,(pu8) siGoodBomb2,GDI_ROP_COPY);
											siGoodBombActive = 0;
//											siShowDefenses();
											return;
										}
									}
								}
								break;
					case 2:		if (sidef3[i][n].mode == SI_ALIVE) {
									if (siGoodBombX >= sidef3[i][n].x && siGoodBombX <= (sidef3[i][n].x + 3)) {
										if (siGoodBombY <= (sidef3[i][n].y + 5) && siGoodBombY >= sidef3[i][n].y) {
											sidef3[i][n].mode = SI_DEAD;
											gdiBitBlt(NULL,sidef3[i][n].x,sidef3[i][n].y,3,5,(pu8) siDefs2,GDI_ROP_COPY);
											gdiBitBlt(NULL,siGoodBombX,siGoodBombY,2,6,(pu8) siGoodBomb2,GDI_ROP_COPY);
											siGoodBombActive = 0;
//											siShowDefenses();
											return;
										}
									}
								}
								break;
					case 3:		if (sidef4[i][n].mode == SI_ALIVE) {
									if (siGoodBombX >= sidef4[i][n].x && siGoodBombX <= (sidef4[i][n].x + 3)) {
										if (siGoodBombY <= (sidef4[i][n].y + 5) && siGoodBombY >= sidef4[i][n].y) {
											sidef4[i][n].mode = SI_DEAD;
											gdiBitBlt(NULL,sidef4[i][n].x,sidef4[i][n].y,3,5,(pu8) siDefs2,GDI_ROP_COPY);
											gdiBitBlt(NULL,siGoodBombX,siGoodBombY,2,6,(pu8) siGoodBomb2,GDI_ROP_COPY);
											siGoodBombActive = 0;
//											siShowDefenses();
											return;
										}
									}
								}
								break;

				}
			}
		}
	}

//	Test if bomb touch any Bad Boy

	for (i = 0; i < SI_MAXBADBOYS_ROWS; i++) {
		for (n = 0; n < SI_MAXBADBOYS_COLS; n++) {
			if (sibb[i][n].mode == SI_ALIVE) {
				if (siGoodBombX >= (sibb[i][n].x + siBadBoysShiftX) && siGoodBombX <= (sibb[i][n].x + siBadBoysShiftX + 15)) {
					if (siGoodBombY <= (sibb[i][n].y + siBadBoysShiftY + 12) && siGoodBombY >= (sibb[i][n].y + siBadBoysShiftY)) {
						sibb[i][n].mode = SI_DESTROYED;
//						gdiBitBlt(NULL,sibb[i][n].x + siBadBoysShiftX,sibb[i][n].y + siBadBoysShiftY,15,12,(pu8) siBadBoys99,GDI_ROP_COPY);
						gdiBitBlt(NULL,siGoodBombX,siGoodBombY,2,6,(pu8) siGoodBomb2,GDI_ROP_COPY);
						siGoodBombActive = 0;
						--siBadBoysCount;
						switch(i) {
							case 0:		siCurrentScore += 30;	break;
							case 1:		siCurrentScore += 20;	break;
							case 2:		siCurrentScore += 20;	break;
							case 3:		siCurrentScore += 10;	break;
						}
						return;
					}
				}
			}
		}
	}


	if (siGoodBombY < 5) {
		gdiBitBlt(NULL,siGoodBombX,siGoodBombY,2,6,(pu8) siGoodBomb2,GDI_ROP_COPY);
		siGoodBombActive = 0;
	} else {
		siGoodBombY -= 3;
	}
}

void siGoodBombStart(void) {

	if ((GPIOA->IDR & SI_FIRE_BUTTON) == 0) {
		if (siGoodBombKeyState == 0 && siGoodBombActive == 0) {
			siGoodBombX = siXGoodBoy + SI_GOODBOYSHOTPOINT;
			siGoodBombY = SI_GOODBOYSTART_Y - 6;
			siGoodBombActive = 1;
			siGoodBombKeyState = 1;
		}
	} else {
		siGoodBombKeyState = 0;
	}

}

void siBadBoysFire(void) {

i16		i, r, col = 0, row = 0;

	if (siBadBoyBombOK == 0) return;		// Bomb disabled

	if (--siBadBoysBombDelay != 0) return;
	siBadBoysBombDelay = SI_BADBOYSBOMBDELAY;

	srand(sysTicks);
	r = rand();
	if ((r & 0x03) == 0x01) {			// Fire bomb

//	Select a random Bad Boy to fire bomb

		while(1) {
			col = rand() % SI_MAXBADBOYS_COLS;
			for (row = (SI_MAXBADBOYS_ROWS - 1); row >= 0; row--) {
				if (sibb[row][col].mode == SI_ALIVE) {
					for (i = 0; i < SI_MAXBADBOYSBOMB; i++) {
						if (siBomb[i].mode == SI_DEAD) {
							siBomb[i].x = sibb[row][col].x + 7 + siBadBoysShiftX;
							siBomb[i].y = sibb[row][col].y + 12 + siBadBoysShiftY;
							siBomb[i].mode = SI_ALIVE;
							return;
						}
					}
				}
			}
		}
	}
}

i16 siDrawBadBoyBomb(void) {

i16		i, v, d, n;
i16		ret = 0;

	siBadBoysFire();

	if (--siBadBombMoveDelay != 0) return(ret);;
	siBadBombMoveDelay = SI_BADBOMBMOVEDELAY;

	for (v = 0; v < SI_MAXBADBOYSBOMB; v++) {
		if (siBomb[v].mode == SI_ALIVE) {
			if (siBomb[v].flip == 0) {
				gdiBitBlt(NULL,siBomb[v].x,siBomb[v].y,3,14,(pu8) siBadBomb01,GDI_ROP_COPY);
				siBomb[v].flip = 1;
			} else {
				gdiBitBlt(NULL,siBomb[v].x,siBomb[v].y,3,14,(pu8) siBadBomb02,GDI_ROP_COPY);
				siBomb[v].flip = 0;
			}

//	See if Bad Boys bomb touch defenses

			for (d = 0; d < 4; d++) {
				for (i = 0; i < SI_MAXDEFENSES_ROWS; i++) {
					for (n = 0; n < SI_MAXDEFENSES_COLS; n++) {
						switch(d) {
							case 0:		if (sidef1[i][n].mode == SI_ALIVE) {
											if (siBomb[v].x >= sidef1[i][n].x && siBomb[v].x <= (sidef1[i][n].x + 3)) {
												if ((siBomb[v].y + 12) >= sidef1[i][n].y && (siBomb[v].y + 12) <= (sidef1[i][n].y + 5)) {
													sidef1[i][n].mode = SI_DEAD;
													gdiBitBlt(NULL,sidef1[i][n].x,sidef1[i][n].y,3,5,(pu8) siDefs2,GDI_ROP_COPY);
													gdiBitBlt(NULL,siBomb[v].x,siBomb[v].y,3,14,(pu8) siBadBomb00,GDI_ROP_COPY);
													siBomb[v].mode = SI_DEAD;
												}
											}
										}
										break;
							case 1:		if (sidef2[i][n].mode == SI_ALIVE) {
											if (siBomb[v].x >= sidef2[i][n].x && siBomb[v].x <= (sidef2[i][n].x + 3)) {
												if ((siBomb[v].y + 12) >= sidef2[i][n].y && (siBomb[v].y + 12) <= (sidef2[i][n].y + 5)) {
													sidef2[i][n].mode = SI_DEAD;
													gdiBitBlt(NULL,sidef2[i][n].x,sidef2[i][n].y,3,5,(pu8) siDefs2,GDI_ROP_COPY);
													gdiBitBlt(NULL,siBomb[v].x,siBomb[v].y,3,14,(pu8) siBadBomb00,GDI_ROP_COPY);
													siBomb[v].mode = SI_DEAD;
												}
											}
										}
										break;
							case 2:		if (sidef3[i][n].mode == SI_ALIVE) {
											if (siBomb[v].x >= sidef3[i][n].x && siBomb[v].x <= (sidef3[i][n].x + 3)) {
												if ((siBomb[v].y + 12) >= sidef3[i][n].y && (siBomb[v].y + 12) <= (sidef3[i][n].y + 5)) {
													sidef3[i][n].mode = SI_DEAD;
													gdiBitBlt(NULL,sidef3[i][n].x,sidef3[i][n].y,3,5,(pu8) siDefs2,GDI_ROP_COPY);
													gdiBitBlt(NULL,siBomb[v].x,siBomb[v].y,3,14,(pu8) siBadBomb00,GDI_ROP_COPY);
													siBomb[v].mode = SI_DEAD;
												}
											}
										}
										break;
							case 3:		if (sidef4[i][n].mode == SI_ALIVE) {
											if (siBomb[v].x >= sidef4[i][n].x && siBomb[v].x <= (sidef4[i][n].x + 3)) {
												if ((siBomb[v].y + 12) >= sidef4[i][n].y && (siBomb[v].y + 12) <= (sidef4[i][n].y + 5)) {
													sidef4[i][n].mode = SI_DEAD;
													gdiBitBlt(NULL,sidef4[i][n].x,sidef4[i][n].y,3,5,(pu8) siDefs2,GDI_ROP_COPY);
													gdiBitBlt(NULL,siBomb[v].x,siBomb[v].y,3,14,(pu8) siBadBomb00,GDI_ROP_COPY);
													siBomb[v].mode = SI_DEAD;
												}
											}
										}
										break;
						}
					}
				}
			}

//	See if Bad Boys bomb touch Good Boy

			if (siBomb[v].x >= siXGoodBoy && siBomb[v].x <= (siXGoodBoy + 24)) {
				if ((siBomb[v].y + 12) >= siYGoodBoy && (siBomb[v].y + 12) <= (siYGoodBoy + 9)) {
					gdiBitBlt(NULL,siBomb[v].x,siBomb[v].y,3,14,(pu8) siBadBomb00,GDI_ROP_COPY);
					gdiBitBlt(NULL,siXGoodBoy,SI_GOODBOYSTART_Y,24,9,(pu8) siGoodBoysBlk,GDI_ROP_COPY);
					ret = 1;	// Good Boy was killed
				}
			}

//	Touch nothing, go ahead

			if (siBomb[v].mode != SI_DEAD) {
				siBomb[v].y += 3;
				if (siBomb[v].y >= (VID_PIXELS_Y - 16)) {
					gdiBitBlt(NULL,siBomb[v].x,siBomb[v].y - 3,3,14,(pu8) siBadBomb00,GDI_ROP_COPY);
					siBomb[v].mode = SI_DEAD;
				}
			}
		}
	}
	return(ret);
}

void siCancelAllBadBoms(void) {

i16		i;

	for (i = 0; i < SI_MAXBADBOYSBOMB; i++) {
		if (siBomb[i].mode != SI_DEAD) {
			gdiBitBlt(NULL,siBomb[i].x,siBomb[i].y - 3,3,14,(pu8) siBadBomb00,GDI_ROP_COPY);
			siBomb[i].mode = SI_DEAD;
		}
	}
}

void siDrawGoodBoyLeft(void) {

i16		i, x, t;

	if (siGoodBoyCount != siGoodBoyCountOld) {
		sprintf((char*) siScore,"LEFT: %d",siGoodBoyCount - 1);
		gdiDrawTextEx(340,170,siScore,GDI_ROP_COPY);

		siGoodBoyCountOld = siGoodBoyCount;
		for (t = 0; t < 4; t++) {
			x = 322;
			for (i = 1; i < SI_MAXGOODBOYS; i++) {
				gdiBitBlt(NULL,x,SI_GOODBOYSTART_Y,24,9,(pu8) siGoodBoysBlk,GDI_ROP_COPY);
				x += 24;
			}
			sysDelayMs(200);
			x = 322;
			for (i = 1; i < SI_MAXGOODBOYS; i++) {
				if (i < siGoodBoyCount) {
					gdiBitBlt(NULL,x,SI_GOODBOYSTART_Y,24,9,(pu8) siGoodBoys,GDI_ROP_COPY);
				} else {
					gdiBitBlt(NULL,x,SI_GOODBOYSTART_Y,24,9,(pu8) siGoodBoysBlk,GDI_ROP_COPY);
				}
				x += 24;
			}
			sysDelayMs(300);
		}
		siXGoodBoy = SI_GOODBOYSTART_X;
		gdiBitBlt(NULL,siXGoodBoy,siYGoodBoy,24,9,(pu8) siGoodBoys,GDI_ROP_COPY);
	}
}

//	Test if Bad Boys are closed to defenses. 0 = No, 1 = Game Over

i16 siBadBoysClosed(void) {

int		i, n;

	for (i = (SI_MAXBADBOYS_ROWS - 1); i >= 0; i--) {
		for (n = 0; n < SI_MAXBADBOYS_COLS; n++) {
			if (sibb[i][n].mode == SI_ALIVE) {
				if (sibb[i][n].y + siBadBoysShiftY + 12 >= SI_DEFSSTARTY) {
					return(1);
				} else {
					return(0);
				}
			}
		}
	}
	return(0);
}

//	The game

void siTheGame(void) {

	while(1) {

		sysDelayMs(1);

		siDrawGoodBoyLeft();
		siMoveGoodBoys();
		siGoodBombStart();
		siMoveGoodBomb();
		if (siBadBoysClosed() == 1) {
			siYouLose();
			return;
		}
		if (siBadBoysCount > 0) {
			if (siDrawBadBoyBomb()) {			// Good Boy was killed
				if (--siGoodBoyCount == 0) {	// Game over
					siYouLose();
					return;
				} else {
					siCancelAllBadBoms();
					gdiBitBlt(NULL,siXGoodBoy,siYGoodBoy,24,9,(pu8) siGoodBoysBlk,GDI_ROP_COPY);
				}
			}
		} else {
			siYouWin();
			return;
		}
		siDrawBadboys();
		if (siBakScore != siCurrentScore) {
			siBakScore = siCurrentScore;
			sprintf((char*) siScore,"SCORE: %04d",siCurrentScore);
			gdiDrawTextEx(328,20,siScore,GDI_ROP_COPY);
			sprintf((char*) siScore,"BEST:  %04d",siBestScore);
			gdiDrawTextEx(328,29,siScore,GDI_ROP_COPY);

		}
	}
}

//*****************************************************************************
//	Function siInit
//
//	Init Space Invaders
//
//	return			none
//*****************************************************************************
void siInit(void) {

GPIO_InitTypeDef	GPIO_InitStructure;
u16					i, n, j, x, y;

//	Configure button pins

	GPIO_InitStructure.GPIO_Pin = SI_FIRE_BUTTON | SI_LEFT_BUTTON | SI_RIGHT_BUTTON;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	gdiBitBlt(NULL,0,0,(VID_PIXELS_X - 1),232,(pu8) siLogo,0);
	sysDelayMs(5000);

start:

	siInitialScreen();

	vidClearScreen();
	gdiRectangle(0,0,(VID_PIXELS_X - 1),VID_VSIZE - 1,0);
	gdiLine(NULL,320,0,320,VID_VSIZE,GDI_ROP_COPY);

//	Preload Bad Boys

	for (i = 0; i < SI_MAXBADBOYS_ROWS; i++) {
		x = 15;
		y = SI_BADBOYS_START_Y + ((SI_MAXBADBOYS_ROWS + 12) * i);
		for (n = 0; n < SI_MAXBADBOYS_COLS; n++) {
			sibb[i][n].x = x;
			sibb[i][n].y = y;
			sibb[i][n].mode = SI_ALIVE;
			sibb[i][n].flip = 0;
			if (i == 0) {
				sibb[i][n].b1 = (pu8) siBadBoys01;
				sibb[i][n].b2 = (pu8) siBadBoys02;
			}
			if (i == 1 || i == 2) {
				sibb[i][n].b1 = (pu8) siBadBoys11;
				sibb[i][n].b2 = (pu8) siBadBoys12;
			}
			if (i == 3) {
				sibb[i][n].b1 = (pu8) siBadBoys21;
				sibb[i][n].b2 = (pu8) siBadBoys22;
			}
			x += 20;
		}
	}

//	Preload defenses

	for (i = 0; i < 4; i++) {
		y = SI_DEFSSTARTY;
		for (j = 0; j < SI_MAXDEFENSES_ROWS; j++) {
			x = SI_DEFSSTARTX +  (i * SI_DEFXSEPARATOR);;
			for (n = 0; n < SI_MAXDEFENSES_COLS; n++) {
			switch(i) {
				case 0:		if (j == 0 || j == 1) {
								sidef1[j][n].x = x;
								sidef1[j][n].y = y;
								sidef1[j][n].mode = SI_ALIVE;
							} else {
								if (n == 0 || n == (SI_MAXDEFENSES_COLS - 1)) {
									sidef1[j][n].x = x;
									sidef1[j][n].y = y;
									sidef1[j][n].mode = SI_ALIVE;
								} else {
									sidef1[j][n].x = x;
									sidef1[j][n].y = y;
									sidef1[j][n].mode = SI_DEAD;
								}
							}
							x += 3;
							break;
				case 1:		if (j == 0 || j == 1) {
								sidef2[j][n].x = x;
								sidef2[j][n].y = y;
								sidef2[j][n].mode = SI_ALIVE;
							} else {
								if (n == 0 || n == (SI_MAXDEFENSES_COLS - 1)) {
									sidef2[j][n].x = x;
									sidef2[j][n].y = y;
									sidef2[j][n].mode = SI_ALIVE;
								} else {
									sidef2[j][n].x = x;
									sidef2[j][n].y = y;
									sidef2[j][n].mode = SI_DEAD;
								}
							}
							x += 3;
							break;
				case 2:		if (j == 0 || j == 1) {
								sidef3[j][n].x = x;
								sidef3[j][n].y = y;
								sidef3[j][n].mode = SI_ALIVE;
							} else {
								if (n == 0 || n == (SI_MAXDEFENSES_COLS - 1)) {
									sidef3[j][n].x = x;
									sidef3[j][n].y = y;
									sidef3[j][n].mode = SI_ALIVE;
								} else {
									sidef3[j][n].x = x;
									sidef3[j][n].y = y;
									sidef3[j][n].mode = SI_DEAD;
								}
							}
							x += 3;
							break;
				case 3:		if (j == 0 || j == 1) {
								sidef4[j][n].x = x;
								sidef4[j][n].y = y;
								sidef4[j][n].mode = SI_ALIVE;
							} else {
								if (n == 0 || n == (SI_MAXDEFENSES_COLS - 1)) {
									sidef4[j][n].x = x;
									sidef4[j][n].y = y;
									sidef4[j][n].mode = SI_ALIVE;
								} else {
									sidef4[j][n].x = x;
									sidef4[j][n].y = y;
									sidef4[j][n].mode = SI_DEAD;
								}
							}
							x += 3;
							break;
				}
			}
			y += 5;
		}
	}

//	Init default variables

	siXGoodBoy = SI_GOODBOYSTART_X;
	siYGoodBoy = SI_GOODBOYSTART_Y;

	siBadBoysDelay = SI_BADBOYSSTARTDELAY;
	siBadBoysShiftX = 0;
	siBadBoysShiftX = 0;
	siBadBoysMode = 0;
	siBadBoysFlip = 0;
	siBadBoysYCount = 0;
	siGoodBoysKeyDelay = SI_GOODBOYSKEYDELAY;
	siGoodBombDelay = SI_GOODBOMBDELAY;
	if (siCurrentScore > siBestScore) siBestScore = siCurrentScore;
	siCurrentScore = 0;
	siBadBoysBombDelay = SI_BADBOYSBOMBDELAY;
	siBadBombMoveDelay = SI_BADBOMBMOVEDELAY;
	siBadBoysCount = SI_MAXBADBOYS_COLS * SI_MAXBADBOYS_ROWS;
	siBakScore = -1;
	siGoodBoyCount = SI_MAXGOODBOYS;
	siGoodBoyCountOld = 0;

//	Show Good Boy first time

	gdiBitBlt(NULL,siXGoodBoy,siYGoodBoy,24,9,(pu8) siGoodBoys,GDI_ROP_COPY);

//	Show Bad Boys first time

	siDrawBadboys();

//	Show defenses first time

	siShowDefenses();

//	Start Gane

	siTheGame();
	goto start;
}	

