//*****************************************************************************
//
//	STM32 Game Development Platform V1.0
//
//	(c) Copyright 2012 by Artekit Italy
//	
//	Written by Ruben H. Meleca
//	
//	Release date: Apr-9-2012
//*****************************************************************************

#ifndef	__SPACE_INVADERS_H
#define	__SPACE_INVADERS_H


// Buttons definition

#define	SI_FIRE_BUTTON			GPIO_Pin_0
#define	SI_LEFT_BUTTON			GPIO_Pin_5
#define	SI_RIGHT_BUTTON			GPIO_Pin_4


#define	SI_MAXBADBOYS_COLS		12
#define	SI_MAXBADBOYS_ROWS		4
#define	SI_BADBOYS_START_Y		5
#define	SI_BADBOYSSTARTDELAY	500
#define	SI_BADBOYSSPEEDCOUNT	20
#define	SI_MAXBADBOYSBOMB		10
#define	SI_BADBOYSBOMBDELAY		70
#define	SI_BADBOMBMOVEDELAY		20

#define	SI_MAXGOODBOYS			4
#define	SI_GOODBOYSTART_X		150
#define	SI_GOODBOYSTART_Y		188
#define	SI_GOODBOYSHOTPOINT		11
#define	SI_GOODBOYSKEYDELAY		16
#define	SI_GOODBOMBDELAY		5


#define	SI_MAXDEFENSES_ROWS		3
#define SI_MAXDEFENSES_COLS		12
#define SI_DEFSSTARTX			35
#define SI_DEFSSTARTY			166
#define	SI_DEFXSEPARATOR		72

#define	SI_DEAD					0
#define	SI_ALIVE				1
#define	SI_DESTROYED			2
#define	SI_CANCEL				3

#define	SI_BOMBFREE				0
#define	SI_BOMBACTIVE			1


typedef __packed struct {

	i16			x;			// X position
	i16			y;			// Y position
	u8			mode;		// 0=Dead (not show), 1=Alive, 2=Attack
	u8			flip;		// 0=bitmap 1, 1=bitmap 2

	pu8			b1;			// Bitmap 1
	pu8			b2;			// Bitmap 2
//	pu8			b3;			// Bitmap 3

} SI_BADBOY;

typedef __packed struct {

	i16			x;			// X position
	i16			y;			// Y position
	u8			flip;		// Bitmap select
	u8			mode;		// 0=Free, 1=Active

}	SI_BOMB;

typedef __packed struct {

	i16			x;			// X position
	i16			y;			// Y position
	u8			mode;		// 0=Free, 1=Active

} SI_DEFENSE;

//	Function declarations

void	siInit(void);

#endif // __SPACE_INVADERS_H
