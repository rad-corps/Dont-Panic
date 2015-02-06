#include "GLAH/SpriteFont.h"
#include <string>
#include <sstream>

using namespace std;

bool ParseFont( std::istream& Stream, Charset& CharsetDesc )
{
	string Line;
	string Read, Key, Value;
	std::size_t i;
	while( !Stream.eof() )
	{
		std::stringstream LineStream;
		std::getline( Stream, Line );
		LineStream << Line;

		//read the line's type
		LineStream >> Read;
		
		//trim the first char
		Read = Read.substr(1, Read.size()-1);

		if( Read == "common" )
		{
			//this holds common data
			while( !LineStream.eof() )
			{
				std::stringstream Converter;
				LineStream >> Read;
				i = Read.find( '=' );
				Key = Read.substr( 0, i );
				Value = Read.substr( i + 1 );

				//assign the correct value
				Converter << Value;
				if( Key == "lineHeight" )
					Converter >> CharsetDesc.LineHeight;
				else if( Key == "base" )
					Converter >> CharsetDesc.Base;
				else if( Key == "scaleW" )
					Converter >> CharsetDesc.Width;
				else if( Key == "scaleH" )
					Converter >> CharsetDesc.Height;
				else if( Key == "pages" )
					Converter >> CharsetDesc.Pages;
			}
		}
		else if( Read == "char" )
		{
			//this is data for a specific char
			unsigned short CharID = 0;

			while( !LineStream.eof() )
			{
				std::stringstream Converter;
				LineStream >> Read;
				i = Read.find( '=' );
				Key = Read.substr( 0, i );
				Value = Read.substr( i + 1 );

				//assign the correct value
				Converter << Value;
				if( Key == "id" )
					Converter >> CharID;
				else if( Key == "x" )
					Converter >> CharsetDesc.Chars[CharID].x;
				else if( Key == "y" )
					Converter >> CharsetDesc.Chars[CharID].y;
				else if( Key == "width" )
					Converter >> CharsetDesc.Chars[CharID].Width;
				else if( Key == "height" )
					Converter >> CharsetDesc.Chars[CharID].Height;
				else if( Key == "xoffset" )
					Converter >> CharsetDesc.Chars[CharID].XOffset;
				else if( Key == "yoffset" )
					Converter >> CharsetDesc.Chars[CharID].YOffset;
				else if( Key == "xadvance" )
					Converter >> CharsetDesc.Chars[CharID].XAdvance;
				else if( Key == "page" )
					Converter >> CharsetDesc.Chars[CharID].Page;
			}
		}
	}

	return true;
}