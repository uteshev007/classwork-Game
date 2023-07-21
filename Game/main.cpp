//
// main.cpp
//

#include <iostream>
#include <string>       // для строк std::string
#include <time.h>
#include <vector>
#include <conio.h>      // для _getch(), _kbhit()
#include "Win10.h"
#include "BasePlayer.h"

using namespace std;

//
// игровое поле - массив строк типа string
// холст кадра игры (Canvas)
// Символы: & - главный игрок; @ - противники;
//          # - стена; 1,2,3,4 - бонусы;
//          * - жизнь;
//          ? - дверь, переход на следующий уровень;
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


// высота и ширина игрового поля
int PoleHeight;   // = 15
int PoleWidth;    // = 35

// Экранные координаты вывода поля на экран
int PoleRow = 3; // по строке
int PoleCol = 8; // по столбцу

vector < BasePlayer*> lstPlayers;
int cntPlayer   = 1;
int cntEnemy    = 10;
bool isPause = false;
bool isGameOver = false;
bool isGameStart = false;
bool isWin = false;
int cntWin  =   0;
int cntLost =   0;



// прототипы функций
void StartGame();       // ф-ция для запуска новой игры
//GetCoordHero();       // Функция для получения координаты главного игрока
//GetCoordEnemys();     // Функция для получения координат противников
void DrawPole();         // функция вывода игрового поля на экран
void InitNewGame();
int main()
{
  //system("chcp 1251 > nul"); //setlocale(LC_ALL, "RUSSIAN");
  //system("chcp 866 > nul"); //setlocale(LC_ALL, "C");

  // вычисление высоты игрового поля:
  //   размер всего поля / размер одной строки
  PoleHeight = sizeof(Pole) / sizeof(Pole[0]);
  PoleWidth = Pole[0].size(); // ширина строки поля

  // MainMenu(); // Главное меню игры
  InitNewGame();
  StartGame();     // ф-ция для запуска новой игры
  // ContinueGame();  // ф-ция для продолжения игры после паузы
  // Settings();      // настройки
  // About();         // об авторах

  cin.get(); cin.get();
} // main()

void InitNewGame()
{
    for (size_t i = 0; i < lstPlayers.size(); i++)
        delete lstPlayers[i];
    lstPlayers.clear();
    cntEnemy = 0;
    for (int row = 0; row < PoleHeight; row++)
    {
        for (int col = 0; col < PoleWidth; col++)
        {
            if (Pole[row][col] == '@')
            {
                BasePlayer* temp = new Enemy;
                temp->SetRowCol(row, col);
                lstPlayers.push_back(temp);
                //lstPlayers.insert(begin(lstPlayers), temp);
                cntEnemy++;
            }
            if (Pole[row][col] == '&')
            {
                BasePlayer* temp = new Player;
                temp->SetRowCol(row, col);
                lstPlayers.insert(begin(lstPlayers), temp);
                //cntPlayer++

            }
        }
    }
    isGameOver = false;
    isWin = false;


} // InitNewGame

// Функция начала новой игры
void StartGame()
{
    isPause = false;
    isGameStart = true;

  // получить текущую позицию игрока
  while (true) // цикл пока идет игра, завершить цикл по завершению игры
  {
    // 1) проверить нажатие клавиш
    // 2) получить код нажатой клавиши
    // 3) изменить позицию игрока, если он двигается
    // 4) движение противников
      for (size_t i = 0; i < lstPlayers.size(); i++)
      {
          lstPlayers[i]->Move(Pole);
         /*
          if (lstPlayers[i]->IsShoot())
          {
              lstPlayers.append(lstPlayers[i]->Shoot());
              BaseBullet* temp = lstPlayers[i]->Shoot();
              lstPlayers.push_back(temp);
          }
         */
          lstPlayers[i]->Draw(Pole);
          if (lstPlayers[i]->IsPause())
          {
              isPause = true;
          }
      }
    // 5) перепросивока поля на экране
    DrawPole(); // вывод поля на экран
    if (isPause) { return; }


    // 6) проверка на завершение: победа или поражение
    Sleep(200);
  } // while(true)

} // StartGame()

// функция вывода игрового поля на экран
void DrawPole()
{
    int iEn = 1;
  for (int i = 0; i < PoleHeight; i++)
  {
    // поставить курсор консоли для i-ой строки поля
    SetPos(PoleRow + i, PoleCol);

    for (int j = 0; j < PoleWidth; j++)
    {
      if (Pole[i][j] == '#') { // символ стены 
        SetColor(COLOR::black, COLOR::light_green);   cout << char(177);
      }
      else if (Pole[i][j] == '?') { // дверь - переход на новый уровень
        SetColor(COLOR::black, COLOR::light_yellow);  cout << char(178);
      }
      else if (Pole[i][j] == '1') { // бонус №1
        SetColor(COLOR::black, COLOR::light_purple);  cout << '/';
      }
      else if (Pole[i][j] == '2') { // бонус №2
        SetColor(COLOR::black, COLOR::light_purple);  cout << '!';
      }
      else if (Pole[i][j] == '3') { // бонус №3
        SetColor(COLOR::black, COLOR::light_purple);  cout << char(24);
      }
      else if (Pole[i][j] == '4') { // бонус №4
        SetColor(COLOR::black, COLOR::light_purple);  cout << 'l';
      }
      else if (Pole[i][j] == '@') { // противники
       // SetColor(COLOR::black, COLOR::light_aqua);    cout << char(2); // лицо
          cout << *lstPlayers[iEn++];
          //iEn++;
      }
      else if (Pole[i][j] == 'B') {
        SetColor(COLOR::black, COLOR::bright_white);  cout << char(1);
      }
      else if (Pole[i][j] == '*') {
        SetColor(COLOR::black, COLOR::light_red);     cout << char(3);
      }
      else if (Pole[i][j] == '&') { // главный герой игры
        //SetColor(COLOR::black, COLOR::light_yellow);  cout << char(2);
          cout << *lstPlayers[0];
      }
      else { cout << Pole[i][j]; } // все остальные символы поля

    } // for (j : PoleWidth)
  } // for (i : PoleHeight)
} // void DrawPole()
