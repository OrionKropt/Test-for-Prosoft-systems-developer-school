/*
* Задача https://www.codingame.com/ide/puzzle/there-is-no-spoon-episode-1
* Сначала создается массив чтобы харнить карту
* Затем пробегая по массиву по строчно для всех нод находятся их правые соседи
* И в конце пробегая по столбцам находятся все нижние соседи
* 
* Для хранения информации о всех соседях каждой ноды создан лист листов,
* где для каждой ноды записаны все ее ближайшие соседи
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;

/**
 * Don't let the machines win. You are humanity's last hope...
 **/


struct Point
{
    Point(const int& X, const int& Y) : x(X), y(Y) {};
    Point() : x(0), y(0) {};
    int x;
    int y;
};

int main()
{
    int width; // the number of cells on the X axis
    cin >> width; cin.ignore();
    int height; // the number of cells on the Y axis
    cin >> height; cin.ignore();
    bool** arr = new bool* [height];
    for (int i = 0; i < height; ++i)
        arr[i] = new bool[width];

    list<list<Point>> ls;
    for (int i = 0; i < height; ++i) {
        string line;
        getline(cin, line); // width characters, each either 0 or .
        cerr << line << endl;

        // Кейс когда у нас всего одна нода
        if (width == 1 && height == 1)
        {
            cout << "0 0 -1 -1 -1 -1" << endl;
            return 0;
        }

        bool isFirst = true;
        for (int j = 0; j < width; ++j)
        {
            arr[i][j] = (line[j] == '0') ? 1 : 0;
            /*
            * Если мы еще никого не добавили то просто добавляем ноду
            * Затем каждая следующая нода будет правм соседом предыдущей
            * поэтому нужно добавлять для предыдущей координаты текущей ноды
            */
            if (arr[i][j])
            {
                if (!isFirst)
                    ls.back().push_back(Point(j, i));
                ls.push_back(list<Point>());
                ls.back().push_back(Point(j, i));
                isFirst = false;
            }
        }
        /*
        * У крайней ноды всегда не будет соседа
        */
        
        auto& last = ls.back();
        if (last.size() != 2)
            last.push_back(Point(-1, -1));

    }


    for (auto iter = ls.begin(); iter != ls.end(); ++iter)
    {
        int i = iter->front().x;
        bool isAdd = false;
        Point temp = iter->front();
        for (int j = 0; j < height; ++j)
        {
            if (arr[j][i])
            {
                // Нода совпадает с текщей ее пропускаем
                if (i == temp.x && j == temp.y)
                    continue;

                // Нода находится ниже текущей
                if (i == temp.x && j > temp.y)
                {
                    iter->push_back(Point(i, j));
                    isAdd = true;
                    break;
                }
            }
        }
        // У последей ноды нету соседа
        if (!isAdd) iter->push_back(Point(-1, -1));
    }
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j)
            cerr << arr[i][j];
        cerr << endl;
    }

    for (auto i = ls.begin(); i != ls.end(); ++i)
    {
        for (auto j = i->begin(); j != i->end(); ++j)
            cout << j->x << ' ' << j->y << ' ';
        cout << endl;
    }
}