#include "Dxlib.h"
#include "Suken.h"
#include "stdio.h"
#include "math.h"

#define DEBUG 
#define VER_N
// VER_Nでノーマルデザインに
// VER_Mでメタリックデザインに
// 変更できます


//#define RESET  //cleartimeのリセット
#define WHI '.'
#define GRE '*'
#define WAL '/'
#define WID 10
#define HEI 9
#define QUES 30
#define FONT_SIZE 36



FILE *fq[QUES];
char map[HEI][WID];////10*9////実質8*7
char tmap[QUES][HEI][WID];

////Title関連
int back;
int ghow;
int start[2];
int stx;
int sty;
int how[2];
int howx;
int howy;
int garrowL[2];
int arrLx , arrLy;
int garrowR[2];
int arrRx , arrRy;
int gback[2];
int backx , backy;
int menu = 0;
int menus = 0;
int gques[QUES];
int gquest;//タイマーじゃない。ステージセレクトの「ques」のため
int ques;
bool sts = false;	
bool hows = false;
bool tits = true;

bool clickL_s = false;//クリック（左）
////Select関連
int sx , sy;
int w;
int h;
int mx , my;///Mouse xy
int frame = 0;
////Solve関連
int soltime = 0; 


////////////
int ggre;
int gwhi;
int gwal;
int gsel;
int gcle;
int dx[2][6] = {-1 , -1 , -1 , 0 , 1 , 0 ,//dx[0] 
				 0 , -1 , 0 , 1 , 1 , 1 };//dx[1]

int dy[6] = { -1 , 0 , 1 , -1 , 0 , 1 };

int gtimer;
int timerx;
int timery;

int gcounter;
int countx;
int county;

int gexit[2];
int exitx;
int exity;

CIntData Data("gazoman/ques/cleartime.txt");


int c;
int ht;
int mt;
int st;

bool clear = true;

void Game();
void Draw();
void DMSelect();
void Select();
void Title();
void Solve();

void Awake(){
	
	back = LoadGraph( "gazoman/back.png" );
	ghow = LoadGraph( "gazoman/how.png" );
	start[0] = LoadGraph( "gazoman/stf.png" );
	start[1] = LoadGraph( "gazoman/stt.png" );
	stx = 100;
	sty = 400;
	how[0] = LoadGraph( "gazoman/howf.png" );
	how[1] = LoadGraph( "gazoman/howt.png" );
	howx = 100;
	howy = 530;
	garrowL[0] = LoadGraph( "gazoman/arrL.png" );
	garrowR[0] = LoadGraph( "gazoman/arrR.png" );
	garrowL[1] = LoadGraph( "gazoman/arrL2.png" );
	garrowR[1] = LoadGraph( "gazoman/arrR2.png" );
	arrLx = 150;
	arrLy = 520;
	arrRx = 360;
	arrRy = 520;
	gback[0] = LoadGraph( "gazoman/backf.png" );
	gback[1] = LoadGraph( "gazoman/backt.png" );
	backx = 0;
	backy = WINDOW_HEIGHT - 70;

	menu = 0;
	gques[0] = LoadGraph( "gazoman/ques1.png" ); 
	gques[1] = LoadGraph( "gazoman/ques2.png" ); 
	gques[2] = LoadGraph( "gazoman/ques3.png" ); 
	gquest = LoadGraph( "gazoman/quest.png" );
	ques = 1;
	gcle = LoadGraph( "gazoman/cle.png" );

	gtimer = LoadGraph( "gazoman/timer.png" );
	timerx = 25;
	timery = WINDOW_HEIGHT - 90;
	gcounter = LoadGraph( "gazoman/counter.png" );
	countx = 475;
	county = WINDOW_HEIGHT - 90;
	gexit[0] = LoadGraph( "gazoman/exitf.png" );
	gexit[1] = LoadGraph( "gazoman/exitt.png" );
	exitx = WINDOW_WIDTH - 70;
	exity = WINDOW_HEIGHT - 70;

	sx = 0;
	sy = 0;
	w = 0;
	h = 0;
	c = 0;
	ht = 0;
	mt = 0;
	st = 0;

#	ifdef VER_N

	ggre = LoadGraph("gazoman/gre.png");
	gwhi = LoadGraph("gazoman/whi.png");
	gwal = LoadGraph("gazoman/wal.png");


#	elif VER_M
	
	ggre = LoadGraph("gazoman/Mgre.png");
	gwhi = LoadGraph("gazoman/Mwhi.png");
	gwal = LoadGraph("gazoman/Mwal.png");
#	endif

	gsel = LoadGraph("gazoman/sel.png");

	for (int i=0; i<QUES; i++){	
		char tmp[64];
		sprintf_s(tmp, "gazoman/ques/q%d.txt", i+1);
		fopen_s(&fq[i], tmp , "r" );

		//if (fq[i]==NULL) {	//ファイルが見つからなかった時に代入処理をするとバグるのでスキップ
		//	ErrorDx("FileOpenError:%d", i+1);
		//	continue;
		//}
		for(int j=0;j<HEI;j++){
			fscanf( fq[i] , "%s" , tmap[i][j] );////バグ対策に一時保管
		}
		fclose( fq[i] );/////しまっちゃうおじさん
	}

#ifdef DEBUG

#else
	ChangeFont( "stroke" ) ;
	SetFontSize( FONT_SIZE );
#endif


#ifdef RESET
	Data.NewMake();//リセット用
#endif
	Data.ReadData();


}
void GameLoop(){


	if( !tits ){

#ifdef DEBUG

		if( CheckHitKey(KEY_INPUT_Y) ){
			if( CheckHitKey(KEY_INPUT_N) ){
				Solve();
			}
		}

#endif

		Game();

	}else{
		Title();
	}

	if(frame%4==0){
		GetMousePoint( &mx , &my );
	}
	
	if( ( GetMouseInput() & MOUSE_INPUT_LEFT ) == 0 && clickL_s ){//一回のクリックで一回しか通せなくするアレ
		clickL_s = false;
	}


	
	frame++;

#ifdef DEBUG

	DrawFormatString(WINDOW_WIDTH - 200,0,BLACK,"sx %d sy %d",sx,sy);
	DrawFormatString(WINDOW_WIDTH - 200,30,BLACK,"w %d h %d",w,h);
	DrawFormatString(WINDOW_WIDTH - 200,60,BLACK,"memu %d s %d ques %d",menu,menus,ques);
	DrawFormatString(WINDOW_WIDTH - 200,120,BLACK,"counter %d",c);
	DrawFormatString(WINDOW_WIDTH - 200,210,YAZAWA,"にこタイマー %d秒",soltime);
	DrawFormatString(0,100,BLACK,"%f",sqrt( (float)((my-(51+76*h))*(my-(51+76*h))+(mx-(51+100*w))*(mx-(51+100*w)) ) ) );
	DrawCircle(51,51,40,RED,false);
	DrawFormatString(200,500,BLACK,"%d", clear );
	
#endif
	

}

void Game(){	

	//いつもの
	
	Draw();	
	DMSelect();

	


	//clear

	clear = true;


	for(int i=0;i<HEI;i++){

		for(int j=0;j<WID;j++){
			if(map[i][j]==WHI){
				clear = false;
				break;
			}
		}

		if(!clear){
			break;
		}

	}

	if(clear){

		DrawGraph( WINDOW_WIDTH/2 - 170 , WINDOW_HEIGHT/2 - 100 , gcle , true );
		
		if( ( GetMouseInput() & MOUSE_INPUT_LEFT ) != 0 && !clickL_s ){//メニューに戻る

			if( Data.RightData[ ques-1 ] == 0 ){//未クリア
				Data.LeftData[ ques-1 ] = ht*3600 + mt*60 + st/60;//左にクリアタイムを”秒”で保存
				Data.RightData[ ques-1 ] = c;//右にその時のカウントを保存
				Data.WriteData();
			}else if( ht*3600 + mt*60 + st/60 < Data.LeftData[ ques-1 ] ){
				Data.LeftData[ ques-1 ] = ht*3600 + mt*60 + st/60;//左にクリアタイムを”秒”で保存
				Data.RightData[ ques-1 ] = c;//右にその時のカウントを保存
				Data.WriteData();
			}
		
			Data.WriteData();
			tits = true;
			menus = 1;
			hows = false;
			sts = false;
			menu = 0;
			c = 0;
			ht = 0;
			mt = 0;
			st = 0;
			clickL_s = true;
		}

	}

	//timer

	DrawGraph( timerx , timery , gtimer , true );

	DrawFormatString( 160 , WINDOW_HEIGHT - 75 , DBLUE , "%02d:%02d:%02d" , ht , mt , st/60 );

	if(!clear){
		st++;

		if( st/60>=60 ){
			mt++;
			st = 0;
		
			if( mt>=60 ){
				ht++;
				mt = 0;
			}

		}
	}
	//counter
	DrawGraph( countx , county , gcounter , true );

	DrawFormatString( 650 , WINDOW_HEIGHT - 75 , DBLUE , "%d" , c );

	//exit
	
	if( mx>=exitx && mx<=exitx+70 && my>=exity && my<=exity+70 ){

		DrawGraph( exitx , exity , gexit[1] , true );

		if( ( GetMouseInput() & MOUSE_INPUT_LEFT ) != 0 && !clickL_s ){
			tits = true;
			menus = 1;
			hows = false;
			sts = false;
			menu = 0;
			c = 0;
			ht = 0;
			mt = 0;
			st = 0;
			clickL_s = true;	
		}
	}else{
		DrawGraph( exitx , exity , gexit[0] , true );
	}


	Select();

	
}

void Draw(){

	for(int i=0;i<HEI;i++){
				
		int y = -25 + i*76;
		int x = -75;

		if( i%2==1 ){
			x = -25;
		}

		for(int j=0;j<WID;j++){

			if( map[i][j] == WHI ){
				DrawGraph( x , y , gwhi , true ); 
			}else if( map[i][j] == GRE ){
				DrawGraph( x , y , ggre , true ); 
			}else if( map[i][j] == WAL ){
				DrawGraph( x , y , gwal , true ); 
			}

			x += 100;			
			
		}

	}


}

void DMSelect(){
	

	///////////////////////////////////Mouse//
	

#ifdef DEBUG
	DrawFormatString(WINDOW_WIDTH - 200,180,BLACK,"mx %d , my %d",mx,my);
#endif

	bool flag = false;

	for(int i=1;i<HEI-1;i++){
		
		for(int j=1;j<WID-1;j++){		

			if( map[i][j] == WAL ){
				h = i;
				w = j;
			}else if( i%2==0 ){//奇数段
				if( sqrt( (float)( (my-(26+76*i))*(my-(26+76*i)) + (mx-(100*j-25))*(mx-(100*j-25)) ) ) <= 40 ){///六角形の中心からの距離が40以下
					DrawGraph( j*100-75 , i*76-25 , gsel , true );
					h = i;
					w = j;
					flag = true;
					break;
				}
			}else{//偶数段
				if( sqrt( (float)( (my-(26+76*i))*(my-(26+76*i)) + (mx-(100*j-25+50))*(mx-(100*j-25+50)) ) ) <= 40 ){///六角形の中心からの距離が40以下
					DrawGraph( j*100-25 , i*76-25 , gsel , true );
					h = i;
					w = j;
					flag = true;
					break;
				}
			}
		}

		if(flag){
			break;
		}

	}

}

void Select(){
	
	if( !clickL_s ){
		if( ( GetMouseInput() & MOUSE_INPUT_LEFT ) != 0 ){
			if( map[h][w] == WHI ){
			
				int r = h%2;
				c++;

				map[h][w] = GRE;

				for(int i=0;i<6;i++){	
					switch( map[ h + dy[i] ][ w + dx[r][i] ] ){
					case GRE:
						map[ h + dy[i] ][ w + dx[r][i] ] = WHI;
						break;
					case WHI:
						map[ h + dy[i] ][ w + dx[r][i] ] = GRE;
						break;
					}
				}
			}
		}
			
		clickL_s = true;

	}

}

void Title(){

	DrawExtendGraph( 0 , 0 , WINDOW_WIDTH , WINDOW_HEIGHT , back , false );
	
	switch( menus ){
	case 0://タイトル画面のとき

		if( mx >= stx && mx <= stx + 300 && my >= sty && my <= sty + 80 ){
			menu = 1;
		}else if( mx >= howx && mx <= howx + 300 && my >= howy && my <= howy + 80 ){
			menu = 2;
		}else{
			menu = 0;
		}

		switch( menu ){
		case 0:
			DrawGraph( stx , sty , start[0] , true );
			DrawGraph( howx , howy , how[0] , true );
			break;
		case 1:
			DrawGraph( stx , sty , start[1] , true );
			DrawGraph( howx , howy , how[0] , true );
			break;
		case 2:
			DrawGraph( stx , sty , start[0] , true );
			DrawGraph( howx , howy , how[1] , true );
			break;
		}

		if( ( GetMouseInput() & MOUSE_INPUT_LEFT ) != 0 && !clickL_s ){
			menus = menu;
			clickL_s = true;
		}

		break;

	case 1:///startのとき

		if( mx >= stx && mx <= stx + 300 && my >= sty && my <= sty + 80 ){
			DrawGraph( stx , sty , start[1] , true );

			if( ( GetMouseInput() & MOUSE_INPUT_LEFT ) != 0 && !clickL_s ){//ゲーム開始
				
				tits = false;
				clickL_s = true;

				for(int i=0;i<HEI;i++){
					for(int j=0;j<WID;j++){
						map[i][j] = tmap[ ques-1 ][i][j];
					}
				}
			}

		}else{
			DrawGraph( stx , sty , start[0] , true );
		}

		if( 1 < ques && ques < QUES ){
			DrawGraph( arrLx , arrLy , garrowL[0] , true );
			DrawGraph( arrRx , arrRy , garrowR[0] , true );
		}else if( ques <= 1 ){
			DrawGraph( arrLx , arrLy , garrowL[1] , true );
			DrawGraph( arrRx , arrRy , garrowR[0] , true );			
		}else if( ques >= QUES ){
			DrawGraph( arrLx , arrLy , garrowL[0] , true );
			DrawGraph( arrRx , arrRy , garrowR[1] , true );
		}

		DrawFormatString( 220 , 518 , DBLUE , "Q  %02d" , ques );
		if( Data.RightData[ques-1] != 0 ){
			DrawFormatString( 500 , 500 , DBLUE , "cleartime %02d:%02d:%02d" , Data.LeftData[ ques-1 ] / 3600 , Data.LeftData[ ques-1 ] / 60 , Data.LeftData[ ques-1 ] % 60 );
			DrawFormatString( 500 , 560 , DBLUE , "count %d" , Data.RightData[ ques-1 ] );
		}
		if( ( GetMouseInput() & MOUSE_INPUT_LEFT ) != 0 && !clickL_s ){
			if( mx >= arrLx - 10 && mx <= arrLx + 30 + 10 && my >= arrLy - 10 && my <= arrLy + 30 - 10 ){//判定を10広げている
				if( ques > 1 ){
					ques--;
					clickL_s = true;
				}
			}else if( mx >= arrRx - 10 && mx <= arrRx + 30 + 10 && my >= arrRy - 10 && my <= arrRy + 30 + 10 ){
				if( ques < QUES ){
					ques++;
					clickL_s = true;
				}
			}
		}

		if( mx >= backx && mx <= backx+70 && my >= backy && my <= backy+70 ){
			DrawGraph( backx , backy , gback[1] , true );
			if( ( GetMouseInput() & MOUSE_INPUT_LEFT ) != 0 && !clickL_s ){
				menus = 0;
				clickL_s = true;
			}
		}else{
			DrawGraph( backx , backy , gback[0] , true );
		}

		break;
	case 2://howのとき
		DrawExtendGraph( 0 , 0 , WINDOW_WIDTH , WINDOW_HEIGHT , ghow , false );
		if( ( GetMouseInput() & MOUSE_INPUT_LEFT ) != 0 && !clickL_s ){
			menus  = 0;
			clickL_s = true;
		}
		break;
	}

	
	if( CheckHitKey(KEY_INPUT_BACK) ){
			menus = 0;
			hows = false;
			sts = false;
			menu = 0;
			c = 0;
			ht = 0;
			mt = 0;
			st = 0;
	}

}

void Solve(){

	DrawString( 0 , 30 , "矢澤システム発動" , YAZAWA );

	bool clear = true;
	soltime = GetNowCount();

	do{
		clear = true;
		int stop = 0;

		while( stop < 100 ){
		
			int ry = rand()%(HEI-2) + 1;
			int rx = rand()%(WID-2) + 1;

			if( map[ry][rx] == WHI ){
			
				map[ry][rx] = GRE;
				int r = ry%2;
				c++;
			
				for(int i=0;i<6;i++){	
					switch( map[ ry + dy[i] ][ rx + dx[r][i] ] ){
					case GRE:
						map[ ry + dy[i] ][ rx + dx[r][i] ] = WHI;
						break;
					case WHI:
						map[ ry + dy[i] ][ rx + dx[r][i] ] = GRE;
						break;
					}
				}

				break;
		
			}

			stop++;

		}

		for(int i=1;i<HEI-1;i++){

			for(int j=1;j<WID-1;j++){
				if(map[i][j]==WHI){
					clear = false;
					break;
				}
			}

			if(!clear){
				break;
			}

		}

		if( CheckHitKey(KEY_INPUT_BACK) ){
			break;
		}

	}while(!clear);

	soltime = GetNowCount() - soltime;
	soltime /= 1000;

}