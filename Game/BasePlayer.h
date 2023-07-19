//
// BasePlayer.h
//
#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;
// 
enum Direct
{
  Left, Right, Up, Down, MAX_Dir
};
class Image
{
  char Sym; // смвол для игрока
  int  clrFon, clrSym; // цвет фона, цвет символа
public:
};

class BasePlayer
{
protected:
  string Name;
  int Row, Col; // координаты игрока
  int oldRow, oldCol; // стар. коорд.
  Image Img; // внешний вид игрока
  int HPLife; // жизни (3, %)
  Direct Dir; // текущее направление игрока

};

class Enemy : virtual public BasePlayer
{

};
