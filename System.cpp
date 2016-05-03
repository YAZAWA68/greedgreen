#include "DxLib.h"
#include "Suken.h"
#include "define.h"

#define BENCHMARK 0//1でベンチマークができる

int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int){

	SetWindowText("Title");
	SetGraphMode(WINDOW_WIDTH , WINDOW_HEIGHT,32 );
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen( DX_SCREEN_BACK );

	int LoadImage = LoadGraph("Natsuiro/BLOCK/load.png");
	DrawExtendGraph(0,0,WINDOW_WIDTH,WINDOW_HEIGHT, LoadImage ,false);
	ScreenFlip();
	
	SetTransColor(255,0,255);
	Awake();

	long long TIME = GetNowHiPerformanceCount();
#	if	BENCHMARK == TRUE
	long long int count = GetNowCount();
#	endif

	while( ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0 && !CheckHitKey(KEY_INPUT_ESCAPE) ){
		GameLoop();
		Sleep( (unsigned long)max( 16 - (int)( GetNowHiPerformanceCount() - TIME ) / 1000 , 0 ) );
		TIME = GetNowHiPerformanceCount();

#		if BENCHMARK == TRUE
		DrawFormatString(WINDOW_WIDTH-200,0,BLACK,"FPS %d (%dms)", (int)( 1000/( GetNowCount() - count ) ) , GetNowCount() - count );
		count = GetNowCount();
#		endif

	}
        
	DxLib_End();
	return 0;
} 