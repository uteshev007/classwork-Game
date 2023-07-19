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
  char Sym; // ����� ��� ������
  int  clrFon, clrSym; // ���� ����, ���� �������
public:
};

class BasePlayer
{
protected:
  string Name;
  int Row, Col; // ���������� ������
  int oldRow, oldCol; // ����. �����.
  Image Img; // ������� ��� ������
  int HPLife; // ����� (3, %)
  Direct Dir; // ������� ����������� ������

};

class Enemy : virtual public BasePlayer
{

};
