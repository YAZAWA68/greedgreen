#pragma once

//////////////////数研ライブラリver0

#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 650

#define RED GetColor( 255 , 0 , 0 )
#define GREEN GetColor( 0 , 255 , 0 )
#define BLUE GetColor( 0 , 0 , 255 )
#define BLACK GetColor( 0 , 0 , 0 )
#define WHITE GetColor( 255 , 255 , 255 )
#define GRAY GetColor( 128 , 128 , 128 )
#define DBLUE GetColor( 0 , 183 , 183 )
#define YAZAWA GetColor(255,122,122) 

#include "math.h"

class Vector{
public:
	double x;
	double y;

	void Set( double _x , double _y){
		x = _x;
		y = _y;
	}

	void Add(Vector _vec){
		x += _vec.x;
		y += _vec.y;
	}

	double GetNorm(){
		return sqrt((x*x)+(y*y));
	}
private:
};


class CBox{
public:
	CBox();
	CBox( int _Left , int _Top , int _Width , int _Height , int Color );

	int Left;
	int Top;
	int Width;
	int Height;
	int Color;

	void Draw();
private:
	
};


/*
class CCommandButton{
public:
	CCommandButton();
	CCommandButton( int _left , int _right , int _width , int _height );
	int Left;
	int Top;
	int Width;
	int Height;
	int ForeColor;
	int BGColor; //BackGroundColor
	int FontSize;

	char *Caption;

	void (*Func)();

	void Update();
	void Draw();
	void Judge();
	void Click();
private:
};
*/

class CIntData{///マイナスには未対応
public:
	//数字を2000(行) *2(左右) =4000個分を
	//テキストに保存、及び読み込み出来るクラスです。
	//まず、クラスを作成時に、読み込むファイル名を代入して
	//ReadData で、読み込み（4000個全て）
	//WriteData　で、書き込み（4000個全て）
	//NewMakeで、新規作成またはファイルの初期化をします
	//ReadData で、ファイルが読み込めなかった場合、
	//自動的に新しくファイルを作成します
	CIntData(char *_DataName);
	char *DataName;
	void NewMake();
	void WriteData();
	void ReadData();
	int RightData[2000];
	int LeftData[2000];
};

class CStrData {
public:
	//文字を1000(行) *128字/行を
	//テキストに保存、及び読み込み出来るクラスです。
	//まず、クラスを作成時に、読み込むファイル名を代入して
	//ReadData で、読み込み（1000行全て）
	//WriteData　で、書き込み（1000行全て）
	//NewMakeで、新規作成またはファイルの初期化をします
	//ReadData で、ファイルが読み込めなかった場合、
	//自動的に新しくファイルを作成します
	CStrData(char *_DataName);
	char *DataName;
	void NewMake();
	void WriteData();
	void ReadData();
	char Data[1000][128];
};

class CCaesar{
public:
	//シーザー暗号（ファイルの文字をずらすことで暗号化すること）用のクラスです。
	//簡単にファイルデータ外部から読み込まれたくない時に使えます。
	//まず、クラス作成時に、元のファイル名（finame）
	//暗号化したファイル名（imname）
	//ずらしキー（暗号化および解読用の数字、なんでもOK）を設定します。
	//CaesarCode()で、元のファイルを暗号化して新しいファイルを作ります
	//CaesarDecode()で、暗号化したファイルから、元のファイルに戻します
	//また、その変更後のファイルを、外部の解読者に解読されないように
	//一工夫加えて、bmpファイルにして、しかもそのファイルを読み込める用にもしました。
	//そうしたい時は、CaesarToBMP()で、BMP化して
	//CaesarFromBMP()で、元に戻せます。
	//bmpで開けたら、誰も怪しまないでしょう（笑）
	//ただし、BMP化の方は、0～255のどれか１つのキーで、
	//解読が成功しません。
	//なので、256分の1の確率のキーで、失敗するので、暗号化と解読との成功を確かめてから使うか
	//ふつうにシーザーしてください。
	CCaesar(char finame[],char imname[],int key);
	char *FileName;
	char *ImaginaryName;
	int Key;
	bool CaesarCode();
	bool CaesarDecode();
	bool CaesarToBMP();
	bool CaesarFromBMP();
};

/*
class ObjectManager{
public:
	ObjectManager();
	void Update();
	void Add( void *fucntion() );
private:
	void* *p;
	int Counter;
};

void AddObject( void *fucntion() );
*/

void KEYCHECK(char &CC , int INPUT );

class CKeyPush{
//ボタン連打用のクラスです。
//クラスを作って、ALLKEYCHECK();を、毎回ループの始めに呼び出してから使えます。
//各要素 == 1の時、で連打を判定できます。
//各要素 == 0の時、ボタンは押されていません。
//各要素 > N(N<255)のとき、で、N回ループ経過後に反応という式になります。
public:
	char BACK;//KEY_INPUT_BACK  // バックスペースキー 
	char TAB;//KEY_INPUT_TAB  // タブキー 
	char RETURN;//KEY_INPUT_RETURN  // エンターキー
	char LSHIFT;//KEY_INPUT_LSHIFT  // 左シフトキー 
	char RSHIFT;//KEY_INPUT_RSHIFT  // 右シフトキー 
	char LCONTROL;//KEY_INPUT_LCONTROL  // 左コントロールキー 
	char RCONTROL;//KEY_INPUT_RCONTROL  // 右コントロールキー 
	char ESCAPE;//KEY_INPUT_ESCAPE  // エスケープキー 
	char SPACE;//KEY_INPUT_SPACE  // スペースキー 
	char LEFT;//KEY_INPUT_LEFT  // 左キー 
	char UP;//KEY_INPUT_UP  // 上キー 
	char RIGHT;//KEY_INPUT_RIGHT  // 右キー 
	char DOWN;//KEY_INPUT_DOWN  // 下キー 
	char INSERT;//KEY_INPUT_INSERT  // インサートキー 
	char Delete;//KEY_INPUT_DELETE  // デリートキー
	char LALT;//KEY_INPUT_LALT  // 左ＡＬＴキー 
	char RALT;//KEY_INPUT_RALT  // 右ＡＬＴキー 
	char SCROLL;//KEY_INPUT_SCROLL  // ScrollLockキー
	char CAPSLOCK;//KEY_INPUT_CAPSLOCK  // CaspLockキー 
	char PAUSE;//KEY_INPUT_PAUSE  // PauseBreakキー
	char MINUS ; // －キー 
	char YEN ;  // ￥キー 
	char PREVTRACK ; // ＾キー 
	char PERIOD ; // ．キー 
	char SLASH ; // ／キー 
	char SEMICOLON ; // ；キー 
	char COLON ; // ：キー 
	char LBRACKET ; // ［キー 
	char RBRACKET ; // ］キー 
	char AT ; // ＠キー 
	char BACKSLASH ; // ＼キー 
	char COMMA ; // ，キー 
	char F1 ; // Ｆ１キー 
	char F2 ; // Ｆ２キー 
	char F3 ; // Ｆ３キー 
	char F4 ; // Ｆ４キー 
	char F5 ; // Ｆ５キー 
	char F6 ; // Ｆ６キー 
	char F7 ; // Ｆ７キー 
	char F8 ; // Ｆ８キー 
	char F9 ; // Ｆ９キー 
	char F10 ; // Ｆ１０キー 
	char F11 ; // Ｆ１１キー 
	char F12 ; // Ｆ１２キー
	char A ; // Ａキー 
	char B ; // Ｂキー 
	char C ; // Ｃキー 
	char D ; // Ｄキー 
	char E ; // Ｅキー 
	char F ; // Ｆキー 
	char G ; // Ｇキー 
	char H ; // Ｈキー 
	char I ; // Ｉキー 
	char J ; // Ｊキー 
	char K ; // Ｋキー 
	char L ; // Ｌキー 
	char M ; // Ｍキー 
	char N ; // Ｎキー 
	char O ; // Ｏキー 
	char P ; // Ｐキー 
	char Q ; // Ｑキー 
	char R ; // Ｒキー 
	char S ; // Ｓキー 
	char T ; // Ｔキー 
	char U ; // Ｕキー 
	char V ; // Ｖキー 
	char W ; // Ｗキー 
	char X ; // Ｘキー 
	char Y ; // Ｙキー 
	char Z ; // Ｚキー 
	char Key0 ; // ０キー 
	char Key1 ; // １キー 
	char Key2 ; // ２キー 
	char Key3 ; // ３キー 
	char Key4 ; // ４キー 
	char Key5 ; // ５キー 
	char Key6 ; // ６キー 
	char Key7 ; // ７キー 
	char Key8 ; // ８キー 
	char Key9 ; // ９キー 
	void ALLKEYCHECK();
};

void GetHttpFile(char *&Buf,char *Http,unsigned long ReadSize = 65536);

int Clng( char *Str ,int n = 0) ;
int ClngTo ( char *Str ,char Word );
int ClngFrom ( char *Str ,char Word );
double Scos(int Angle);
double Ssin(int Angle);
double Stan(int Angle);
int AngleFromRad(double Angle);
int Power2(int x, int y);

unsigned long FileGetSize(char *FileName);
bool CheckWord(char *Str ,char Word );
void Awake();
void GameLoop();