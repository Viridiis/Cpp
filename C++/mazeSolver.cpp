#include <iostream>
#include <windows.h>
#include <vector>
#include <queue>
using namespace std;

int firstMaze[15][15] = {
         { -1, -1, -1, -1, -1, -1, -1, -1, 0, -1, -1, -1, -1, -1, -1},
         { -1, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1},
         { -1, -1, -1, -1, 0, -1, -1, -1, -1, -1, 0, -1, -1, 0, -1},
         { -1, 0, -1, 0, 0, 0, -1, 0, 0, 0, 0, -1, 0, 0, -1},
         { -1, 0, -1, 0, -1, 0, -1, -1, -1, -1, -1, -1, 0, -1, -1},
         { -1, 0, -1, 0, -1, 0, 0, 0, 0, 0, 0, -1, 0, -1, -1},
         { -1, 0, -1, 0, -1, 0, -1, -1, -1, -1, 0, -1, 0, 0, -1},
         { -1, 0, -1, 0, -1, 0, 0, 0, -1, 0, 0, -1, -1, 0, -1},
         { -1, 0, 0, 0, -1, -1, -1, -1, -1, -1, 0, -1, -1, 0, -1},
         { -1, 0, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, -1},
         { -1, 0, -1, -1, -1, -1, -1, 0, -1, 0, -1, -1, -1, 0, -1 },
         { -1, 0, 0, 0, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0, -1 },
         { -1, 0, -1, -1, -1, 0, -1, -1, -1, -1, -1, -1, -1, 0, -1 },
         { -1, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
         { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
};

int secondMaze[15][15] = {
         { -1, -1, -1, -1, -1, -1, -1, -1, 0, -1, -1, -1, -1, -1, -1},
         { -1, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1},
         { -1, -1, -1, -1, 0, -1, -1, -1, -1, -1, 0, -1, -1, 0, -1},
         { -1, 0, -1, 0, 0, 0, -1, 0, 0, 0, 0, -1, 0, 0, -1},
         { -1, 0, -1, 0, -1, 0, -1, -1, -1, -1, -1, -1, 0, -1, -1},
         { -1, 0, -1, 0, -1, 0, 0, 0, 0, 0, 0, -1, 0, -1, -1},
         { -1, 0, -1, 0, -1, 0, -1, -1, -1, -1, 0, -1, 0, 0, -1},
         { -1, 0, -1, 0, -1, 0, 0, 0, -1, 0, 0, -1, -1, 0, -1},
         { -1, 0, 0, 0, -1, -1, -1, -1, -1, -1, 0, -1, -1, 0, -1},
         { -1, 0, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, -1},
         { -1, 0, -1, -1, -1, -1, -1, 0, -1, 0, -1, -1, -1, 0, -1 },
         { -1, 0, 0, 0, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0, -1 },
         { -1, 0, -1, -1, -1, 0, -1, -1, -1, -1, -1, -1, -1, 0, -1 },
         { -1, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
         { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0},
};

int thirdMaze[15][15] = {
         { -1, -1, -1, -1, -1, -1, -1, -1, 0, -1, -1, -1, -1, -1, -1},
         { -1, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1},
         { -1, -1, -1, -1, 0, -1, -1, -1, -1, -1, 0, -1, -1, 0, -1},
         { -1, 0, -1, 0, 0, 0, -1, 0, 0, 0, 0, -1, 0, 0, -1},
         { -1, 0, -1, 0, -1, 0, -1, -1, -1, -1, -1, -1, 0, -1, -1},
         { -1, 0, -1, 0, -1, 0, 0, 0, 0, 0, 0, -1, 0, -1, -1},
         { -1, 0, -1, 0, -1, 0, -1, -1, -1, -1, 0, -1, 0, 0, -1},
         { -1, 0, -1, 0, -1, 0, 0, 0, -1, 0, 0, -1, -1, 0, -1},
         { -1, 0, 0, 0, -1, -1, -1, -1, -1, -1, 0, -1, -1, 0, -1},
         { -1, 0, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, -1},
         { -1, 0, -1, -1, -1, -1, -1, 0, -1, 0, -1, -1, -1, 0, -1 },
         { -1, 0, 0, 0, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0, -1 },
         { -1, 0, -1, -1, -1, 0, -1, -1, -1, -1, -1, -1, -1, 0, -1 },
         { -1, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0, -1 },
         { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0, 0},
};



enum colors {
    colorWlal = BACKGROUND_GREEN | FOREGROUND_GREEN,
    colorPath = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED,
    colorStart = BACKGROUND_BLUE | FOREGROUND_BLUE,
    colorFin = BACKGROUND_RED | FOREGROUND_RED,
    colorRoute = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | FOREGROUND_GREEN,
    defaultForeground = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN,
    defaultBackground = 0
};

struct cords {
    int x;
    int y;
    cords(int cordX, int cordY) {
        x = cordX;
        y = cordY;
    }
    cords() {
        x = 0;
        y = 0;
    }
};

// function to show colors
void printData(int a, int x = 0, int y = 0, vector<cords>* path = nullptr)
{
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    if (a == -1) {
        SetConsoleTextAttribute(hConsole, colorWlal);
        cout << "a";
        SetConsoleTextAttribute(hConsole, defaultBackground);
        SetConsoleTextAttribute(hConsole, defaultForeground);
    }
    if (a == -2) {
        SetConsoleTextAttribute(hConsole, colorStart);
        cout << "b";
        SetConsoleTextAttribute(hConsole, defaultBackground);
        SetConsoleTextAttribute(hConsole, defaultForeground);
    }
    if (a == -3) {
        SetConsoleTextAttribute(hConsole, colorFin);
        cout << "c";
        SetConsoleTextAttribute(hConsole, defaultBackground);
        SetConsoleTextAttribute(hConsole, defaultForeground);
    }

    if (a == 0) {
        SetConsoleTextAttribute(hConsole, colorPath);
        cout << "a";
        SetConsoleTextAttribute(hConsole, defaultBackground);
        SetConsoleTextAttribute(hConsole, defaultForeground);
    }

    if (a > 0) {
        if (path) {
            for (int i = 0; i < path->size(); i++) {
                if ((*path)[i].x == x && (*path)[i].y == y) {
                    SetConsoleTextAttribute(hConsole, colorRoute);
                    cout << "o";
                    SetConsoleTextAttribute(hConsole, defaultBackground);
                    SetConsoleTextAttribute(hConsole, defaultForeground);
                    return;
                }
            }
        }
        SetConsoleTextAttribute(hConsole, colorPath);
        cout << "o";
        SetConsoleTextAttribute(hConsole, defaultBackground);
        SetConsoleTextAttribute(hConsole, defaultForeground);
    }
}


int showcaseMaze(int mazeNumber)
{
    int** maze, x, y;

    switch (mazeNumber) {
    case 1:
        x = 15; 
        y = 15;
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
                int** maze = reinterpret_cast<int**>(firstMaze);
            }
        }
    }
   
        cout << "  "; // numbers above maze
        for (int i = 0; i < 15; i++) {
            i > 9 ? cout << i : cout << " " << i;
        }
        cout << endl;

        // numbers on side of maze
        for (int i = 0; i < 15; i++) {
            i > 9 ? cout << i : cout << " " << i;
            for (int j = 0; j < 15; j++) {
                printData(maze[i][j], i, j); 
                printData(maze[i][j], i, j); 
            }
            cout << endl;
        }
        cout << "\n";
    return 0;
}

int pathfinder(int startX, int startY, int finX, int finY, int mazeNumber)
{


    int** maze, x, y;

    switch (mazeNumber) {
    case 1:
        x = 15;
        y = 15;
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
                int** maze = reinterpret_cast<int**>(firstMaze);
            }
        }
    }

    if (maze[startX][startY] != -1)
        maze[startX][startY] = -2;
    else {
        cout << "start can't be wall" << endl;
        return 0;
    }

    if (maze[finX][finY] != -1)
        maze[finX][finY] = -3;
    else {
        cout << "fin can't be wall" << endl;
        return 0;
    }


    vector <cords> openMap;
    vector <cords> nopenMap; // no support wf
    openMap.push_back(cords(startX, startY));
    bool foundPath = false;

    vector<cords> path;

    while (openMap.size() > 0) {
        cords current = openMap[0];
        for (int i = 1; i < openMap.size(); i++) {
            openMap[i - 1] = openMap[i];
        }
        openMap.pop_back();
        nopenMap.push_back(current);

        // this is where u will walk back to start
        if (current.x == finX && current.y == finY) {
            foundPath = true;
            path.push_back(current);

            while (!(current.x == startX && current.y == startY)) {
                int bigRandomNumber = 12415;
                cords lowestValueNeighbour;

                bool istStart = false;

                for (cords direction : {cords(-1, 0), cords(1, 0), cords(0, 1), cords(0, -1)})
                {
                    cords neighbour = cords(current.x + direction.x, current.y + direction.y);

                    if (maze[neighbour.x][neighbour.y] == 0 || maze[neighbour.x][neighbour.y] == -1 || maze[neighbour.x][neighbour.y] == -3) {
                        continue;
                    }

                    if (maze[neighbour.x][neighbour.y] == -2) {
                        istStart = true;
                        break;
                    }

                    if (maze[neighbour.x][neighbour.y] < bigRandomNumber) {
                        bigRandomNumber = maze[neighbour.x][neighbour.y];
                        lowestValueNeighbour = neighbour;
                    }
                }

                if (istStart) {
                    break;
                }
                path.push_back(lowestValueNeighbour);
                current = lowestValueNeighbour;
            }
            break;
        }

        for (cords direction : {cords(-1, 0), cords(1, 0), cords(0, 1), cords(0, -1)})
        {
            cords neighbour = cords(current.x + direction.x, current.y + direction.y);
            if (neighbour.x < 0 || neighbour.x >= 15) { // ist in maze?
                continue;
            }
            if (neighbour.y < 0 || neighbour.y >= 15) { // ist in maze? again
                continue;
            }
            if (maze[neighbour.x][neighbour.y] == -1) { // ist wlal? :ReallyMad:
                continue;
            }

            bool istInNopen = false;
            bool istInOpen = false;

            for (int i = 0; i < nopenMap.size(); i++) {
                if (neighbour.x == nopenMap[i].x && neighbour.y == nopenMap[i].y) { // nopen map, never visit this cord :ReallyMad:
                    istInNopen = true;
                    break;
                }
            }
            if (istInNopen)
                continue;


            bool currentIsStart = current.x == startX && current.y == startY;

            if (maze[neighbour.x][neighbour.y] > maze[current.x][current.y] + (currentIsStart ? 3 : 1) || maze[neighbour.x][neighbour.y] == 0) {
                maze[neighbour.x][neighbour.y] = maze[current.x][current.y] + (currentIsStart ? 3 : 1);
            }

            for (int i = 0; i < openMap.size(); i++) {
                if (neighbour.x == openMap[i].x && neighbour.y == openMap[i].y) { // nopen map, never visit this cord :ReallyMad:
                    istInOpen = true;
                    break;
                }
            }
            if (!istInOpen) {
                openMap.push_back(neighbour);
            }
        }

    }
    if (!foundPath) {
        cout << "path not found";
        return 0;
    }

    

        cout << "  ";
        for (int i = 0; i < 15; i++) {
            i > 9 ? cout << i : cout << " " << i;
        }
        cout << endl;

        for (int i = 0; i < 15; i++) {
            i > 9 ? cout << i : cout << " " << i;
            for (int j = 0; j < 15; j++) {
                printData(maze[i][j], i, j, &path);
                printData(maze[i][j], i, j, &path);
            }
            cout << endl;
        }
    cout << "Shortest path ist " << path.size();
    return 0;
}

int main()
{
    int startX, startY, finX, finY, mazeNumber, maze;
    cout << "Which maze you want to work on? (1-3)" << endl;
    cin >> mazeNumber;

    cout << "\n\n";
    showcaseMaze(mazeNumber);

    cout << "Start cords: " << endl;
    cin >> startX >> startY;
    cout << "Fin cords: " << endl;
    cin >> finX >> finY;
    pathfinder(startY, startX, finY, finX, mazeNumber);
}