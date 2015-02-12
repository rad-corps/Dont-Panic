//UVTranslator.h
//Author: Adam Hulbert - hulbert.adam@gmail.com
//Use: translates row and column position into a float[4] of UV coordinates

#pragma once

class UVTranslator
{
public:
	//CTOR
	//float width_		: width of the entire spritesheet image
	//float height_		: height of the entire spritesheet image
	//float blockWidth_	: the width of each sprite in the sprite sheet (will only work when sprite sheets have equally spaced sprites), 
	//float blockHeight_	: the height of each sprite in the sprite sheet (will only work when sprite sheets have equally spaced sprites), if 0, defaults to blockWidth_;
	UVTranslator(int width_, int height_, int blockWidth_, int blockHeight_);
	
	

	//calls the matching CTOR
	void Init(float sheetWidth_, float sheetHeight_, float tileWidth_, float tileHeight_);
	
	//float* out_		: must be a float array initialised with 4 elements.
	//float col_		: 0 based column (starting from left)
	//float row_		: 0 based row (starting from the bottom)
	//float blockCols_	: number of columns to retreive in the UV (defaults to 1)
	//float rowWidth_	: number of rows to retreive in the UV (defaults to 1)
	void GetUV(float* out_, int row_, int col_, int tileCols_ = 1, int tileRows_ = 1);

	~UVTranslator();

	//default ctor, object is in an invalid state until Init is called.
	UVTranslator();

private:
	

	int tileWidth;
	int tileHeight;
	int sheetWidth;
	int sheetHeight;
};

