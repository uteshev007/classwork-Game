//
// BasePlayer.h
//
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Win10.h"
using namespace std;
// 
enum Direct
{
  Stop = -1,
  Left, Right, Up, Down, MAX_Dir
};
class Image
{
  char Sym; // смвол для игрока
  int  clrFon, clrSym; // цвет фона, цвет символа
public:
	Image() : Sym(char(1)), clrFon(COLOR::black), clrSym(COLOR::yellow) {}
	Image(char s, int fon, int color ) : Sym(s), clrFon(fon), clrSym(color) {}
	void SetSym(char s) { Sym = s; }
	char GetSym() const { return Sym; }
	void SetColor(int color, int fon = black) 
	{
		clrSym = color;
		clrFon = fon;
	}
	int GetSymCol() const { return clrSym; }
	int GetSymFon() const { return clrFon; }

	friend ostream& operator << (ostream& os, const Image& obj)
	{
		::SetColor(obj.clrSym, obj.clrFon);
		os << obj.clrSym;
		return os;
	}
};//class Image

class BasePlayer
{
protected:
  string Name;
  int Row, Col; // координаты игрока
  int OldRow, OldCol; // стар. коорд.
  Image Img; // внешний вид игрока
  int HPLife; // жизни (3, %)
  Direct Dir; // текущее направление игрока
  int Damage;
  bool isShoot;
  int Score;
  bool isPause;
public:
	BasePlayer() : Row(), Col(), OldRow(), OldCol(), 
		Img(char(2), COLOR::light_aqua, COLOR::light_aqua), 
		HPLife(1), Dir(Direct::Left), isShoot(false), Score(), isPause(false) {}
	virtual ~BasePlayer() {}

	friend ostream& operator << (ostream & os, const BasePlayer & obj)
	{
		os << obj.Img;
		return os;
	}

	virtual bool IsPause() const { return isPause; }
	virtual bool IsAlive() const { return HPLife > 0; }
	virtual void Move(string Pole[])
	{
		//Dir = Direct(rand() % Direct::MAX_Dir);
		Direct mas[Direct::MAX_Dir];
		int cntDir{};
		if (Pole[Row][Col - 1] != '#')
			mas[cntDir++] == Direct::Left;
		if (Pole[Row][Col + 1] != '#')
			mas[cntDir++] == Direct::Right;
		if (Pole[Row - 1][Col] != '#')
			mas[cntDir++] == Direct::Up;
		if (Pole[Row + 1][Col] != '#')
			mas[cntDir++] == Direct::Down;
		if (cntDir > 0)
		{
			Dir = mas[rand() % cntDir];
			OneStep(Pole);
		}
	}
	virtual void OneStep(string Pole[])
	{
		if (Dir == Direct::Left && Pole[Row][Col - 1] != '#')
			Col--;
		if (Dir == Direct::Right && Pole[Row][Col + 1] != '#')
			Col++;
		if (Dir == Direct::Up && Pole[Row - 1][Col] != '#')
			Row--;
		if (Dir == Direct::Down && Pole[Row + 1][Col] != '#')
			Row++;
	}
	virtual void Draw(string Pole[])
	{
		Pole[Row][Col] = Img.GetSym();
		Pole[OldRow][OldCol] = ' ';
		OldRow = Row;
		OldCol = Col;

	}
	virtual bool IsShoot() const { return isShoot; }

};//class BasePlayer()

class Enemy : virtual public BasePlayer
{
protected:
public:
	Enemy() 
	{
		Img.SetSym(char(2));
		Img.SetColor(COLOR::light_yellow, black);
		HPLife = 1;
		Damage = 1;
		Row = OldRow = RAND(1, 10);
		Col = OldCol = RAND(1, 10);
		Dir = Direct(rand() % Direct::MAX_Dir);
	}
	virtual ~Enemy() override {}
}; //class Enemy

class Player : virtual public BasePlayer
{
protected:
public:
	Player()
	{
		Img.SetSym(char(1));
		Img.SetColor(COLOR::light_green, black);
		HPLife = 3;
		Damage = 1;
		Row = OldRow = RAND(1, 10);
		Col = OldCol = RAND(1, 10);
		Dir = Direct::Stop;
	}
	virtual ~Player() override {}

	virtual void Move(string Pole[]) override 
	{
		if (_kbhit())
		{
			int key = _getch();
			switch (key)
			{
			case 'a': case 'A': case 'ф': case 'Ф': case _KEY::LEFT:
				Dir = Direct::Left;
			case 'd': case 'D': case 'в': case 'В': case _KEY::RIGHT:
				Dir = Direct::Right;
			case 'w': case 'W': case 'ц': case 'Ц': case _KEY::UP:
				Dir = Direct::Up;
			case 's': case 'S': case 'ы': case 'Ы': case _KEY::DOWN:
				Dir = Direct::Down;
			case _KEY ::SPACE:
				isShoot = true;
			case _KEY::ESC:
				isPause = true;
				break;
			}
			OneStep(Pole);
		}
	}
}; //class Player
