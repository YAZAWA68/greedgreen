#pragma once

//////////////////�������C�u����ver0

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

class CIntData{///�}�C�i�X�ɂ͖��Ή�
public:
	//������2000(�s) *2(���E) =4000����
	//�e�L�X�g�ɕۑ��A�y�ѓǂݍ��ݏo����N���X�ł��B
	//�܂��A�N���X���쐬���ɁA�ǂݍ��ރt�@�C������������
	//ReadData �ŁA�ǂݍ��݁i4000�S�āj
	//WriteData�@�ŁA�������݁i4000�S�āj
	//NewMake�ŁA�V�K�쐬�܂��̓t�@�C���̏����������܂�
	//ReadData �ŁA�t�@�C�����ǂݍ��߂Ȃ������ꍇ�A
	//�����I�ɐV�����t�@�C�����쐬���܂�
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
	//������1000(�s) *128��/�s��
	//�e�L�X�g�ɕۑ��A�y�ѓǂݍ��ݏo����N���X�ł��B
	//�܂��A�N���X���쐬���ɁA�ǂݍ��ރt�@�C������������
	//ReadData �ŁA�ǂݍ��݁i1000�s�S�āj
	//WriteData�@�ŁA�������݁i1000�s�S�āj
	//NewMake�ŁA�V�K�쐬�܂��̓t�@�C���̏����������܂�
	//ReadData �ŁA�t�@�C�����ǂݍ��߂Ȃ������ꍇ�A
	//�����I�ɐV�����t�@�C�����쐬���܂�
	CStrData(char *_DataName);
	char *DataName;
	void NewMake();
	void WriteData();
	void ReadData();
	char Data[1000][128];
};

class CCaesar{
public:
	//�V�[�U�[�Í��i�t�@�C���̕��������炷���ƂňÍ������邱�Ɓj�p�̃N���X�ł��B
	//�ȒP�Ƀt�@�C���f�[�^�O������ǂݍ��܂ꂽ���Ȃ����Ɏg���܂��B
	//�܂��A�N���X�쐬���ɁA���̃t�@�C�����ifiname�j
	//�Í��������t�@�C�����iimname�j
	//���炵�L�[�i�Í�������щ�Ǘp�̐����A�Ȃ�ł�OK�j��ݒ肵�܂��B
	//CaesarCode()�ŁA���̃t�@�C�����Í������ĐV�����t�@�C�������܂�
	//CaesarDecode()�ŁA�Í��������t�@�C������A���̃t�@�C���ɖ߂��܂�
	//�܂��A���̕ύX��̃t�@�C�����A�O���̉�ǎ҂ɉ�ǂ���Ȃ��悤��
	//��H�v�����āAbmp�t�@�C���ɂ��āA���������̃t�@�C����ǂݍ��߂�p�ɂ����܂����B
	//�������������́ACaesarToBMP()�ŁABMP������
	//CaesarFromBMP()�ŁA���ɖ߂��܂��B
	//bmp�ŊJ������A�N�������܂Ȃ��ł��傤�i�΁j
	//�������ABMP���̕��́A0�`255�̂ǂꂩ�P�̃L�[�ŁA
	//��ǂ��������܂���B
	//�Ȃ̂ŁA256����1�̊m���̃L�[�ŁA���s����̂ŁA�Í����Ɖ�ǂƂ̐������m���߂Ă���g����
	//�ӂ��ɃV�[�U�[���Ă��������B
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
//�{�^���A�ŗp�̃N���X�ł��B
//�N���X������āAALLKEYCHECK();���A���񃋁[�v�̎n�߂ɌĂяo���Ă���g���܂��B
//�e�v�f == 1�̎��A�ŘA�ł𔻒�ł��܂��B
//�e�v�f == 0�̎��A�{�^���͉�����Ă��܂���B
//�e�v�f > N(N<255)�̂Ƃ��A�ŁAN�񃋁[�v�o�ߌ�ɔ����Ƃ������ɂȂ�܂��B
public:
	char BACK;//KEY_INPUT_BACK  // �o�b�N�X�y�[�X�L�[ 
	char TAB;//KEY_INPUT_TAB  // �^�u�L�[ 
	char RETURN;//KEY_INPUT_RETURN  // �G���^�[�L�[
	char LSHIFT;//KEY_INPUT_LSHIFT  // ���V�t�g�L�[ 
	char RSHIFT;//KEY_INPUT_RSHIFT  // �E�V�t�g�L�[ 
	char LCONTROL;//KEY_INPUT_LCONTROL  // ���R���g���[���L�[ 
	char RCONTROL;//KEY_INPUT_RCONTROL  // �E�R���g���[���L�[ 
	char ESCAPE;//KEY_INPUT_ESCAPE  // �G�X�P�[�v�L�[ 
	char SPACE;//KEY_INPUT_SPACE  // �X�y�[�X�L�[ 
	char LEFT;//KEY_INPUT_LEFT  // ���L�[ 
	char UP;//KEY_INPUT_UP  // ��L�[ 
	char RIGHT;//KEY_INPUT_RIGHT  // �E�L�[ 
	char DOWN;//KEY_INPUT_DOWN  // ���L�[ 
	char INSERT;//KEY_INPUT_INSERT  // �C���T�[�g�L�[ 
	char Delete;//KEY_INPUT_DELETE  // �f���[�g�L�[
	char LALT;//KEY_INPUT_LALT  // ���`�k�s�L�[ 
	char RALT;//KEY_INPUT_RALT  // �E�`�k�s�L�[ 
	char SCROLL;//KEY_INPUT_SCROLL  // ScrollLock�L�[
	char CAPSLOCK;//KEY_INPUT_CAPSLOCK  // CaspLock�L�[ 
	char PAUSE;//KEY_INPUT_PAUSE  // PauseBreak�L�[
	char MINUS ; // �|�L�[ 
	char YEN ;  // ���L�[ 
	char PREVTRACK ; // �O�L�[ 
	char PERIOD ; // �D�L�[ 
	char SLASH ; // �^�L�[ 
	char SEMICOLON ; // �G�L�[ 
	char COLON ; // �F�L�[ 
	char LBRACKET ; // �m�L�[ 
	char RBRACKET ; // �n�L�[ 
	char AT ; // ���L�[ 
	char BACKSLASH ; // �_�L�[ 
	char COMMA ; // �C�L�[ 
	char F1 ; // �e�P�L�[ 
	char F2 ; // �e�Q�L�[ 
	char F3 ; // �e�R�L�[ 
	char F4 ; // �e�S�L�[ 
	char F5 ; // �e�T�L�[ 
	char F6 ; // �e�U�L�[ 
	char F7 ; // �e�V�L�[ 
	char F8 ; // �e�W�L�[ 
	char F9 ; // �e�X�L�[ 
	char F10 ; // �e�P�O�L�[ 
	char F11 ; // �e�P�P�L�[ 
	char F12 ; // �e�P�Q�L�[
	char A ; // �`�L�[ 
	char B ; // �a�L�[ 
	char C ; // �b�L�[ 
	char D ; // �c�L�[ 
	char E ; // �d�L�[ 
	char F ; // �e�L�[ 
	char G ; // �f�L�[ 
	char H ; // �g�L�[ 
	char I ; // �h�L�[ 
	char J ; // �i�L�[ 
	char K ; // �j�L�[ 
	char L ; // �k�L�[ 
	char M ; // �l�L�[ 
	char N ; // �m�L�[ 
	char O ; // �n�L�[ 
	char P ; // �o�L�[ 
	char Q ; // �p�L�[ 
	char R ; // �q�L�[ 
	char S ; // �r�L�[ 
	char T ; // �s�L�[ 
	char U ; // �t�L�[ 
	char V ; // �u�L�[ 
	char W ; // �v�L�[ 
	char X ; // �w�L�[ 
	char Y ; // �x�L�[ 
	char Z ; // �y�L�[ 
	char Key0 ; // �O�L�[ 
	char Key1 ; // �P�L�[ 
	char Key2 ; // �Q�L�[ 
	char Key3 ; // �R�L�[ 
	char Key4 ; // �S�L�[ 
	char Key5 ; // �T�L�[ 
	char Key6 ; // �U�L�[ 
	char Key7 ; // �V�L�[ 
	char Key8 ; // �W�L�[ 
	char Key9 ; // �X�L�[ 
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