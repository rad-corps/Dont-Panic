//UVTranslator.cpp
#include "UVTranslator.h"

UVTranslator::UVTranslator(int width_, int height_, int tileWidth_, int tileHeight_)
	: sheetWidth(width_), sheetHeight(height_), tileWidth(tileWidth_), tileHeight(tileHeight_)
{
}

//needs to be initialised still after default ctor
UVTranslator::UVTranslator(void)
{
}


UVTranslator::~UVTranslator(void)
{
}

void UVTranslator::Init(float width_, float height_, float tileWidth_, float tileHeight_)
{
	sheetWidth = width_;
	sheetHeight = height_;
	tileWidth = tileWidth_;
	tileHeight = tileHeight_;
}


void UVTranslator::GetUV(float* out_, int row_, int col_, int blockCols_, int blockRows_)
{
	//{ U_MIN , V_MIN , U_MIN + U_STEP, V_MIN + V_STEP };

	//float u_min, v_min, u_max, v_max, u_step, v_step;

	//u_min = col_ * ((float)tileWidth / sheetWidth); //sheetwidth and sheetheight are floats and passed into UVTranslator on construction
	//v_min = row_ * ((float)tileHeight / sheetHeight);
	//u_step = (blockCols_ * tileWidth) / (float)sheetWidth;
	//v_step = (blockRows_ * tileHeight) / (float)sheetHeight;
	//u_max = u_min + u_step;
	//v_max = v_min + v_step;
	//
	//out_[0] = u_min;
	//out_[1] = v_min;
	//out_[2] = u_max;
	//out_[3] = v_max;	

	out_[0] = col_ * tileWidth;
	out_[1] = row_ * tileHeight;
	out_[2] = tileWidth * blockCols_;
	out_[3] = tileHeight * blockRows_;

}