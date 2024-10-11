#include <iostream> // для ввода-вывода (std::cout, std::cin)
#include <conio.h> // для _kbhit() и _getch() (обработка клавиатуры)
#include <string> // для работы со строками
#include <windows.h> // для функций Sleep() и работы с экраном (cls)
#include <ctime> // для генерации случайных чисел (rand(), srand())
using namespace std; // для упрощения синтаксиса (чтобы не писать std::)

enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir; // переменная для хранения направления движения змейки

// функция для инициализации динамического массива
int** CreateArray(int size) {
    int** arr = new int* [size]; // создаем массив указателей (двумерный массив)
    for (int i = 0; i < size; i++) {
        arr[i] = new int[2]; // две координаты: x и y
    }
    return arr; // возвращаем указатель на массив
}

// функция для удаления динамического массива
void DeleteArray(int** arr, int size) {
    for (int i = 0; i < size; i++) {
        delete[] arr[i]; // удаляем каждый подмассив (строки двумерного массива)
    }
    delete[] arr; // удаляем основной массив указателей
}

// настройки начального состояния игры
void Setup(int& x, int& y, int& fruitX, int& fruitY, int& score, int& nTail, int**& tail, int& obstacleCount, int**& obstacles, int width, int height) {
    x = width / 2; // начальная позиция змейки (центр поля)
    y = height / 2;
    fruitX = rand() % width; // случайная позиция фрукта
    fruitY = rand() % height;
    score = 0; // начальный счет
    nTail = 0; // хвост змейки пустой
    tail = CreateArray(width * height);  // динамический массив для хвоста
    obstacleCount = 10; // количество препятствий
    obstacles = CreateArray(obstacleCount); // динамический массив для препятствий
    dir = RIGHT;  // начальное направление движения

    // генерация препятствий
    for (int i = 0; i < obstacleCount; i++) {
        obstacles[i][0] = rand() % width; // x координата препятствия
        obstacles[i][1] = rand() % height; // y координата препятствия
    }
}

// функция для рисования игрового поля
void Draw(int x, int y, int fruitX, int fruitY, int score, int nTail, int** tail, int obstacleCount, int** obstacles, int width, int height) {
    system("cls"); // очистка экрана для перерисовки

    // верхняя граница
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    // поле игры
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0)
                cout << "#"; // левая граница

            if (i == y && j == x)
                cout << "O"; // голова змейки
            else if (i == fruitY && j == fruitX)
                cout << "F"; // фрукт
            else {
                bool print = false;

                // проверка на хвост змейки
                for (int k = 0; k < nTail; k++) {
                    if (tail[k][0] == j && tail[k][1] == i) {
                        cout << "o"; // часть хвоста
                        print = true;
                    }
                }

                // проверка на препятствия
                for (int k = 0; k < obstacleCount; k++) {
                    if (obstacles[k][0] == j && obstacles[k][1] == i) {
                        cout << "X"; // препятствие
                        print = true;
                    }
                }

                if (!print) // если нет ни хвоста, ни препятствий
                    cout << " "; // пустая клетка
            }

            if (j == width - 1)
                cout << "#"; // правая граница
        }
        cout << "\n";
    }

    // нижняя граница
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << "\n";

    cout << "score: " << score << "\n"; // выводим текущий счет
}

// функция для управления движением змейки
void Input(eDirection& dir) {
    if (_kbhit()) { // проверяем, была ли нажата клавиша
        switch (_getch()) { // читаем клавишу
        case 'a':
            if (dir != RIGHT) dir = LEFT; // меняем направление на ЛЕВО
            break;
        case 'd':
            if (dir != LEFT) dir = RIGHT; // меняем направление на ПРАВО
            break;
        case 'w':
            if (dir != DOWN) dir = UP; // меняем направление на ВВЕРХ
            break;
        case 's':
            if (dir != UP) dir = DOWN; // меняем направление на ВНИЗ
            break;
        case 'x':
            dir = STOP; // прекращение игры
            break;
        }
    }
}

// функция для логики игры
void Logic(int& x, int& y, int& fruitX, int& fruitY, int& score, int& nTail, int** tail, eDirection& dir, int obstacleCount, int** obstacles, int width, int height, int& speed) {
    int prevX = x, prevY = y;  // запоминаем предыдущие координаты
    int prev2X, prev2Y; // переменные для перемещения хвоста

    // изменение координат головы змейки в зависимости от направления
    switch (dir) {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }

    // столкновение с границами поля
    if (x >= width) x = 0; else if (x < 0) x = width - 1;
    if (y >= height) y = 0; else if (y < 0) y = height - 1;

    // столкновение с хвостом
    for (int i = 0; i < nTail; i++)
        if (tail[i][0] == x && tail[i][1] == y)
            dir = STOP; // конец игры

    // перемещение хвоста
    for (int i = 0; i < nTail; i++) {
        prev2X = tail[i][0];
        prev2Y = tail[i][1];
        tail[i][0] = prevX;
        tail[i][1] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    // столкновение с препятствиями
    for (int i = 0; i < obstacleCount; i++) {
        if (obstacles[i][0] == x && obstacles[i][1] == y)
            dir = STOP; // конец игры
    }

    // поедание фрукта
    if (x == fruitX && y == fruitY) {
        score += 10; // увеличение счета
        fruitX = rand() % width; // новая случайная позиция фрукта
        fruitY = rand() % height;
        nTail++; // увеличение длины хвоста
        if (speed > 30) speed -= 5; // увеличение скорости игры
    }
}

// основной цикл игры
int main() {
    int x, y, fruitX, fruitY, score, nTail, obstacleCount, speed = 100;
    int width = 40, height = 20;
    int** tail = nullptr;
    int** obstacles = nullptr;
    dir = STOP; // начальное состояние - змейка стоит

    srand(time(0)); // инициализация генератора случайных чисел

    Setup(x, y, fruitX, fruitY, score, nTail, tail, obstacleCount, obstacles, width, height); // начальная настройка игры

    while (dir != STOP) {  // цикл игры, продолжается пока не нажата клавиша остановки
        Draw(x, y, fruitX, fruitY, score, nTail, tail, obstacleCount, obstacles, width, height); // рисуем игровое поле
        Input(dir); // обрабатываем ввод пользователя
        Logic(x, y, fruitX, fruitY, score, nTail, tail, dir, obstacleCount, obstacles, width, height, speed); // обновляем логику игры
        Sleep(speed); // замедляем цикл игры, чтобы змейка не двигалась слишком быстро
    }

    cout << "Game over! Your score: " << score << "\n"; // выводим финальный счет

    // очищаем динамически выделенную память
    DeleteArray(tail, width * height);
    DeleteArray(obstacles, obstacleCount);
    return 0;
}
