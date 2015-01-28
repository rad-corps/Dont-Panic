#include "SpriteSheetTests.h"
#include <iostream>

using namespace std;

SpriteSheetTests::SpriteSheetTests(void)
{
	
}


SpriteSheetTests::~SpriteSheetTests(void)
{
}

void SpriteSheetTests::RunTest1()
{
	cout << "RunTest1()" << endl;
	sheet.Init(512, 320, 64, 64);
	expected[0] = 0.125f;
	expected[1] = 0.8f;
	expected[2] = 0.250f;
	expected[3] = 1.0f;

	sheet.GetUV(myUV, 4, 1);

	for ( int i = 0; i < 4; ++i ) 
	{
		cout << "myUV[" << i << "]" << myUV[i] << '\t';
		cout << "expected[" << i << "]" << expected[i] << endl;
	}
}

void SpriteSheetTests::RunTest2()
{
	
}