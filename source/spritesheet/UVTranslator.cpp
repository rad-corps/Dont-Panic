//UVTranslator.cpp
#include "UVTranslator.h"

UVTranslator::UVTranslator(float width_, float height_, float tileWidth_, float tileHeight_)
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


void UVTranslator::GetUV(float* out_, float row_, float col_, float blockCols_, float blockRows_)
{
	//{ U_MIN , V_MIN , U_MIN + U_STEP, V_MIN + V_STEP };
	out_[0] = col_ * tileWidth / sheetWidth;
	out_[1] = row_ * tileHeight / sheetHeight;
	out_[2] = out_[0] + ((blockCols_ * tileWidth)/sheetWidth);
	out_[3] = out_[1] + ((blockRows_ * tileHeight)/sheetHeight);	
}