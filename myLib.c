#include "myLib.h"

unsigned short *videoBuffer = (unsigned short *)0x6000000;
/**
 * Draw an image with the top left corner at (x, y)
 */
void drawImage3(int r, int c, int width, int height, const u16* image) {

	for(int i = 0; i < height; ++i) {
		drawRow(r, c, width, image, i);
	}
	// TODO Draw the image with the top left corner at (x,y).
	// Recall that the GBA screen is 240 pixels wide, and 160 tall.
	// The videoBuffer is a 1-dimensional array of these pixels.
	// For example, to set pixel (37,21) to white:
	//   videoBuffer[21 * 240 + 37] = 0x7FFF;
	// unsigned short uu = image[1];
	// uu++;
	// for (int r = 0; r < height; r++) {
	// 	int vY = y - r;
	// 	for (int c = 0; c < width; c++) {
	// 		int vX = x + c;
	// 		unsigned short pixelData = image[(height - 1 - r) * width + c];
	// 		videoBuffer[vY * SCREEN_WIDTH + vX] = pixelData;
	// 	}
	// }
}

void drawRow(int r, int c, int width, const unsigned short *image, int row) {

	// TODO re-implement this loop using DMA
	// Hint: There shouldn't even be a loop if you've done it correctly
	// This loop only draws one row of a fullscreen image
	// for(int i = 0; i < 240; ++i) {
	// 	videoBuffer[row * 240 + i] = image[row * 240 + i];
	// }
	DMA[MODE3].src = image + row * width;
	DMA[MODE3].dst = videoBuffer + (r + row) * SCREEN_WIDTH + c;
	DMA[MODE3].cnt = width | DMA_ON;
}


void setPixel(int row, int col, unsigned short color)
{
	videoBuffer[OFFSET(row, col, SCREEN_WIDTH)] = color;
}

void drawRect(int row, int col, int height, int width, unsigned short color)
{
	unsigned short volatile c = color;
	for(int r=0; r<height; r++)
	{
		DMA[MODE3].src = &c;
		for(int h = 0; h < height; h++)
		{ 
			DMA[MODE3].dst = videoBuffer + (row + h) * SCREEN_WIDTH + col;
			DMA[MODE3].cnt = width | DMA_ON | DMA_SOURCE_FIXED;
		}
	}
}

void fillScreen3(unsigned short color)
{
	unsigned short volatile c = color;
	DMA[MODE3].src = &c;
	DMA[MODE3].dst = videoBuffer;
	DMA[MODE3].cnt = SCREEN_WIDTH * SCREEN_HEIGHT | DMA_ON | DMA_SOURCE_FIXED;
}

void delay(int n)
{
	volatile int x=0;
	for(int i=0; i<10000*n; i++)
	{
		x = x + 1;
	}
}


void limitCheck(int *var, int *delta, int limit, int size)
{
	if(*var<0)
	{
		*var = 0;
		*delta = -*delta;
	}
	if(*var>limit-size)
	{
		*var = limit-size;
		*delta = -*delta;
	}
		

}

void waitForVblank()
{
	while(SCANLINECOUNTER > 160);
	while(SCANLINECOUNTER < 160);
}


