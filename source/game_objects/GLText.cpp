#include "../GLAH/GLAHGraphics.h"
#include "GLText.h"
#include "../spritesheet/UVTranslator.h"
#include <locale> //toupper

using namespace std;

GLText::GLText(){
	alignment = TEXT_ALIGNMENT::ALIGN_LEFT;
	hud = false;
}
GLText::~GLText(void){}

void GLText::SetHUD(bool hud_)
{
	hud = hud_;
}

void GLText::Update(float delta_){}

void GLText::SetPos(Vector2 pos_)
{
	pos = pos_;
}

void GLText::SetAlignment(TEXT_ALIGNMENT alignment_)
{
	alignment = alignment_;
}

std::string GLText::GetText()
{
	return text;
}

void GLText::SetText(string text_)
{
	text = text_;
	uvs.clear();
	UVTranslator trans(1024,1024,64,64);

	for ( int ch : text_ )
	{
		//get the ascii representation of the character
		ch = (int)toupper(ch);

		ch -= 32; //sprite chart starts from ascii 32
		ch -= 5;  //accidentally missed 5 chars when creating sheet
		
		//create an array to pushback into UVS
		std::array<float, 4> tempArray;

		//determine column and row
		int row = ch / 16;
		int col = ch % 16;

		//dump the uv data into the std::array
		trans.GetUV(tempArray.data(), row, col);

		//uvs is a std::vector<std::array<float, 4>> uvs;
		uvs.push_back(tempArray);
	}
}

void GLText::Draw()
{
	//for each std::array in uvs

	if ( alignment == TEXT_ALIGNMENT::ALIGN_LEFT )
	{
		for ( int i = 0; i < uvs.size(); ++i )
		{
			SetSpriteUVCoordinates(SpriteSheet::FontSprite(), uvs[i].data());
			MoveSprite(SpriteSheet::FontSprite(), pos.x + 16 * i, pos.y); //hardcoded 8 as a step for now, variable size can come later
			DrawSprite(SpriteSheet::FontSprite(), false, 1.0f, !hud);
		}
	}
	
	if ( alignment == TEXT_ALIGNMENT::ALIGN_CENTRE )
	{
		//use a float to find the middle character because it can be halfway for even numbers
		float middle_char = (uvs.size() - 1) / 2.f;
		for ( int i = 0; i < uvs.size(); ++i )
		{
			float charOffset = (i - middle_char) * 16;
			SetSpriteUVCoordinates(SpriteSheet::FontSprite(), uvs[i].data());
			MoveSprite(SpriteSheet::FontSprite(), pos.x + charOffset, pos.y);
			DrawSprite(SpriteSheet::FontSprite(), false, 1.0f, !hud);
		}
	}

	if ( alignment == TEXT_ALIGNMENT::ALIGN_RIGHT)
	{
		//use a float to find the middle character because it can be halfway for even numbers		
		for ( int i = 0; i < uvs.size(); ++i )
		{
			SetSpriteUVCoordinates(SpriteSheet::FontSprite(), uvs[uvs.size()-1-i].data());
			MoveSprite(SpriteSheet::FontSprite(), pos.x - 16 * i, pos.y);
			DrawSprite(SpriteSheet::FontSprite(), false, 1.0f, !hud);
		}
	}
}