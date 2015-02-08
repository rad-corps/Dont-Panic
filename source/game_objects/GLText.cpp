#include "GLAH/GLAHGraphics.h"
#include "GLText.h"
#include "../spritesheet/UVTranslator.h"
#include <locale> //toupper

using namespace std;

GLText::GLText()
{
	
}


GLText::~GLText(void)
{
}

void GLText::SetPos(Vector2 pos_)
{
	pos = pos_;
}

void GLText::SetText(string text_)
{
	uvs.clear();
	UVTranslator trans(1024,1024,64,64);

	for ( int i = 0; i < text_.size(); ++i )
	{
		//get the ascii representation of the character
		int ch = (int)toupper(text_[i]);

		ch -= 32; //sprite chart starts from ascii 32
		ch -= 5; //accidentally missed 5 chars when creating sheet
		
		//create an array to pushback into UVS
		std::array<float, 4> tempArray;

		//determine column and row
		int row = ch / 16;
		int col = ch % 16;

		trans.GetUV(tempArray.data(), row,col);
		uvs.push_back(tempArray);
	}
}

void GLText::Update(float delta_)
{}

void GLText::Draw()
{
	for ( int i = 0; i < uvs.size(); ++i )
	{
		SetSpriteUVCoordinates(SpriteSheet::FontSprite(), uvs[i].data());
		MoveSprite(SpriteSheet::FontSprite(), pos.x + 8 * i, pos.y);
		DrawSprite(SpriteSheet::FontSprite());
	}
}