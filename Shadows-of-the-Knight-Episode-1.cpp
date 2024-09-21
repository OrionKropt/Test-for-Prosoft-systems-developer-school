/*
* Задача https://www.codingame.com/ide/puzzle/shadows-of-the-knight-episode-1
* Для ее решения использовал бинарный поиск по высоте и ширине
* В игровом цикле идет прарсинг строки bomb_dir с помощью switch case
* И в зависимотси от напрваления меняется текущаяя координата
*
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/


int main()
{
    int w; // width of the building.
    int h; // height of the building.
    cin >> w >> h; cin.ignore();
    int n; // maximum number of turns before game over.
    cin >> n; cin.ignore();
    int x0;
    int y0;
    cin >> x0 >> y0; cin.ignore();


    int left_h = 0;
    int right_h = h - 1;        // Чтобы не выйти за предели поля так как нумерация начинается с нуля
    int left_w = 0;
    int right_w = w - 1;
    int midd_h = y0;
    int midd_w = x0;
    double factor = 0.5;

    // game loop
    while (1) {
        string bomb_dir; // the direction of the bombs from batman's current location (U, UR, R, DR, D, DL, L or UL)
        cin >> bomb_dir; cin.ignore();

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;

        for (auto charr : bomb_dir)
        {
            cerr << "left_h " << left_h << endl;
            cerr << "right_h " << right_h << endl;
            cerr << "left_w " << left_w << endl;
            cerr << "right_w " << right_w << endl;
            cerr << "midd_w " << midd_w << endl;
            cerr << "midd_h " << midd_h << endl;

            switch (charr)
            {
            case 'D':
            {
                left_h = midd_h + 1;
                break;
            }
            case 'R':
            {
                left_w = midd_w + 1;
                break;
            }
            case 'U':
            {
                right_h = midd_h - 1;
                break;
            }
            case 'L':
            {
                right_w = midd_w - 1;
                break;
            }
            }
        }

        // Если мы перескочили нужную координату, меняем left и right местами, чтобы сменить напрваление
        if (right_h < left_h)
        {
            right_h += left_h;
            left_h = right_h - left_h;
            right_h -= left_h;
        }
        if (right_w < left_w)
        {
            right_w += left_w;
            left_w = right_w - left_w;
            right_w -= left_w;
        }

        // Пытаемся угадать нужную координату
        // Каждый раз берем среедину растояния от текущей точки до
        // крайней точки в стороне бомбы

        midd_h = left_h + (right_h - left_h) * factor;
        midd_w = left_w + (right_w - left_w) * factor;

        cout << midd_w << ' ' << midd_h << endl;
    }
}