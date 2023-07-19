//
// main.cpp
//

#include <iostream>
#include <string>       // ��� ����� std::string
#include <time.h>
#include <conio.h>      // ��� _getch(), _kbhit()
#include "Win10.h"
using namespace std;

//
// ������� ���� - ������ ����� ���� string
// ����� ����� ���� (Canvas)
// �������: & - ������� �����; @ - ����������;
//          # - �����; 1,2,3,4 - ������;
//          * - �����;
//          ? - �����, ������� �� ��������� �������;
//
string Pole[]   // <==> char pole[15][35+1];
{
  "###################################",
  "#   #*##      @          @        #",
  "# # @  #@############## ######### #",
  "# ###### #   #*#3  @  # ##@##   # #",
  "#  @       # # ###### # #@4   #@# #",
  "###### # ### #      # # ##@##   # #",
  "##  @# # # # #### # #   ##### # # #",
  "#* #   # # @    # ##*######*#   # #",
  "######## # ####         #   # # #@#",
  "#  2#    #      ####### # # #   # #",
  "# ### #### ######       # #   #   #",
  "# @        #      ####### #########",
  "############ ######   #1# # @ #   #",
  "#   &               #   #   #@  #B#",
  "#################################?#"
};


// ������ � ������ �������� ����
int PoleHeight;   // = 15
int PoleWidth;    // = 35

// �������� ���������� ������ ���� �� �����
int PoleRow = 3; // �� ������
int PoleCol = 8; // �� �������

// ��������� �������
void StartGame();     // �-��� ��� ������� ����� ����
//GetCoordHero();       // ������� ��� ��������� ���������� �������� ������
//GetCoordEnemys();     // ������� ��� ��������� ��������� �����������
void DrawPole();      // ������� ������ �������� ���� �� �����

int main()
{
  //system("chcp 1251 > nul"); //setlocale(LC_ALL, "RUSSIAN");
  //system("chcp 866 > nul"); //setlocale(LC_ALL, "C");

  // ���������� ������ �������� ����:
  //   ������ ����� ���� / ������ ����� ������
  PoleHeight = sizeof(Pole) / sizeof(Pole[0]);
  PoleWidth = Pole[0].size(); // ������ ������ ����

  // MainMenu(); // ������� ���� ����

  StartGame();     // �-��� ��� ������� ����� ����
  // ContinueGame();  // �-��� ��� ����������� ���� ����� �����
  // Settings();      // ���������
  // About();         // �� �������

  cin.get(); cin.get();
} // main()


// ������� ������ ����� ����
void StartGame()
{
  // �������� ������� ������� ������
  while (true) // ���� ���� ���� ����, ��������� ���� �� ���������� ����
  {
    // 1) ��������� ������� ������
    // 2) �������� ��� ������� �������
    // 3) �������� ������� ������, ���� �� ���������
    // 4) �������� �����������
    // 5) ������������� ���� �� ������
    DrawPole(); // ����� ���� �� �����
    // 6) �������� �� ����������: ������ ��� ���������
  } // while(true)

} // StartGame()

// ������� ������ �������� ���� �� �����
void DrawPole()
{
  for (int i = 0; i < PoleHeight; i++)
  {
    // ��������� ������ ������� ��� i-�� ������ ����
    SetPos(PoleRow + i, PoleCol);

    for (int j = 0; j < PoleWidth; j++)
    {
      if (Pole[i][j] == '#') { // ������ ����� 
        SetColor(COLOR::black, COLOR::light_green);   cout << char(177);
      }
      else if (Pole[i][j] == '?') { // ����� - ������� �� ����� �������
        SetColor(COLOR::black, COLOR::light_yellow);  cout << char(178);
      }
      else if (Pole[i][j] == '1') { // ����� �1
        SetColor(COLOR::black, COLOR::light_purple);  cout << '/';
      }
      else if (Pole[i][j] == '2') { // ����� �2
        SetColor(COLOR::black, COLOR::light_purple);  cout << '!';
      }
      else if (Pole[i][j] == '3') { // ����� �3
        SetColor(COLOR::black, COLOR::light_purple);  cout << char(24);
      }
      else if (Pole[i][j] == '4') { // ����� �4
        SetColor(COLOR::black, COLOR::light_purple);  cout << 'l';
      }
      else if (Pole[i][j] == '@') { // ����������
        SetColor(COLOR::black, COLOR::light_aqua);    cout << char(2); // ����
      }
      else if (Pole[i][j] == 'B') {
        SetColor(COLOR::black, COLOR::bright_white);  cout << char(1);
      }
      else if (Pole[i][j] == '*') {
        SetColor(COLOR::black, COLOR::light_red);     cout << char(3);
      }
      else if (Pole[i][j] == '&') { // ������� ����� ����
        SetColor(COLOR::black, COLOR::light_yellow);  cout << char(2);
      }
      else { cout << Pole[i][j]; } // ��� ��������� ������� ����

    } // for (j : PoleWidth)
  } // for (i : PoleHeight)
} // void DrawPole()
