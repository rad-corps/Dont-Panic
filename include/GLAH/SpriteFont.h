#include <iostream>

struct CharDescriptor
{
	//clean 16 bytes
	unsigned short x, y;
	unsigned short Width, Height;
	float XOffset, YOffset;
	float XAdvance;
	unsigned short Page;

	CharDescriptor() : x( 0 ), y( 0 ), Width( 0 ), Height( 0 ), XOffset( 0 ), YOffset( 0 ),
		XAdvance( 0 ), Page( 0 )
	{ }
};

struct Charset
{
	unsigned short LineHeight;
	unsigned short Base;
	unsigned short Width, Height;
	unsigned short Pages;
	CharDescriptor Chars[256];
};

bool ParseFont( std::istream& Stream, Charset& CharsetDesc );