#include "myLib.h"

#include "res/start.h"

int main()
{
	REG_DISPCTL = MODE3 | BG2_ENABLE;
	//*    ( 19320 =  videoBuffer) = WHITE;
	//videoBuffer[OFFSET(80, 120, 240)] = WHITE;
	//setPixel(80, 120, WHITE);
	int row = 80;
	int col = 120;
	int size = 10;
	int esize = size / 2;
	int ecols[4] = {48, 96, 144, 192};
	int erows[4] = {0, SCREEN_HEIGHT - esize - 1, 0, SCREEN_HEIGHT - esize - 1};
	int rdel = 2;
	/*
	int k=0;
	for(int r=0; r<16; r++)
		for(int c=0; c<16; c++)
			drawChar(r*9, c*9, k++, YELLOW);
	while(1);
	*/
	fillScreen3(WHITE);
	drawRect(row, col, size, size, BLUE);
	for (int i = 0; i < 4; i++) {
			drawRect(erows[i], ecols[i], esize, esize, YELLOW);
	}
	while(1) // Game Loop
	{
		waitForVblank();
		if(KEY_DOWN_NOW(BUTTON_UP)|
				KEY_DOWN_NOW(BUTTON_DOWN)|
				KEY_DOWN_NOW(BUTTON_LEFT)|
				KEY_DOWN_NOW(BUTTON_RIGHT)) {
			drawRect(row, col, size, size, WHITE);
		}
		if(KEY_DOWN_NOW(BUTTON_UP))
		{
			row--;
			if(row<0) row = 0;
		}
		if(KEY_DOWN_NOW(BUTTON_DOWN))
		{
			row++;
			if(row>160 - size) row = 160 - size;
		}
		if(KEY_DOWN_NOW(BUTTON_LEFT))
		{
			col--;
			if(col<0) col = 0;
		}
		if(KEY_DOWN_NOW(BUTTON_RIGHT))
		{
			col++;
			if(col>240 - size) col = 240 - size;
		}
		int multiple = 1;
		for (int i = 0; i < 4; i++) {
			drawRect(erows[i], ecols[i], esize, esize, WHITE);
			erows[i] = erows[i] + rdel * multiple;
			multiple *= -1;
		}
		for (int i = 0; i < 4; i++) {
			drawRect(erows[i], ecols[i], esize, esize, YELLOW);
		}
		limitCheck(erows, &rdel, 159, esize);
		drawRect(row, col, size, size, BLUE);
		// delay(1);
		
		// oldrow = row;
		// oldcol = col;
		// oldsize = size;

	}
	// return 0;
}

