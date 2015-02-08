#include "GLAH/GLAHGraphics.h"
#include "GLText.h"
#include "../spritesheet/UVTranslator.h"
#include <locale> //toupper

using namespace std;

GLText::GLText(){}
GLText::~GLText(void){}
void GLText::Update(float delta_){}

void GLText::SetPos(Vector2 pos_)
{
	pos = pos_;
}

void GLText::SetText(string text_)
{
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
	for ( int i = 0; i < uvs.size(); ++i )
	{
		SetSpriteUVCoordinates(SpriteSheet::FontSprite(), uvs[i].data());
		MoveSprite(SpriteSheet::FontSprite(), pos.x + 8 * i, pos.y); //hardcoded 8 as a step for now, variable size can come later
		DrawSprite(SpriteSheet::FontSprite());
	}
}