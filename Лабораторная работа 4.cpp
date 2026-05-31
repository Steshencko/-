#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

// Константа для преобразования градусов в радианы
const double PI = 3.14159265358979323846;
double degToRad(double deg) {
    return deg * PI / 180.0;
}

// Абстрактный класс Точка (базовый для всех фигур)
class Point {
protected:
    int x, y;          // Координаты центра или опорной точки
    
public:
    Point(int x = 0, int y = 0) : x(x), y(y) {}
    virtual ~Point() {}
    
    // Чисто виртуальные методы (делают класс абстрактным)
    virtual void draw() const = 0;        // Изобразить
    virtual void erase() = 0;              // Убрать
    virtual void move(int dx, int dy) = 0; // Передвинуть
    virtual void rotate(double angle) = 0; // Повернуть
    
    // Геттеры и сеттеры с разными уровнями доступа
    int getX() const { return x; }
    int getY() const { return y; }
    
protected:
    void setX(int newX) { x = newX; }
    void setY(int newY) { y = newY; }
    
    // Демонстрация различных вариантов регламентации доступа
public:
    void setPosition(int newX, int newY) { x = newX; y = newY; }
    
private:
    // Приватные методы - только для внутреннего использования
    void validateCoordinates() {
        // Логика валидации (упрощённо)
    }
};

// Базовый класс для всех линейных объектов
class Line : virtual public Point {
protected:
    int length;
    double direction; // угол в градусах
    
public:
    Line(int x = 0, int y = 0, int len = 0, double dir = 0) 
        : Point(x, y), length(len), direction(dir) {}
    
    virtual ~Line() {}
    
    void draw() const override {
        cout << "Рисую линию из точки (" << x << "," << y 
             << ") длиной " << length << " под углом " << direction << "°" << endl;
    }
    
    void erase() override {
        cout << "Стираю линию" << endl;
    }
    
    void move(int dx, int dy) override {
        x += dx;
        y += dy;
        cout << "Линия перемещена на (" << dx << "," << dy << ")" << endl;
    }
    
    void rotate(double angle) override {
        direction += angle;
        cout << "Линия повёрнута на " << angle << "°, теперь угол " << direction << "°" << endl;
    }
    
    int getLength() const { return length; }
    double getDirection() const { return direction; }
};

// Класс Параллелограмм
class Parallelogram : virtual public Point {
protected:
    int width, height;
    double skew;      // угол наклона для параллелограмма
    double rotation;  // общий поворот фигуры
    
public:
    Parallelogram(int x = 0, int y = 0, int w = 0, int h = 0, double sk = 0)
        : Point(x, y), width(w), height(h), skew(sk), rotation(0) {}
    
    virtual ~Parallelogram() {}
    
    void draw() const override {
        cout << "Рисую параллелограмм с центром (" << x << "," << y 
             << "), ширина=" << width << ", высота=" << height 
             << ", наклон=" << skew << "°, поворот=" << rotation << "°" << endl;
    }
    
    void erase() override {
        cout << "Стираю параллелограмм" << endl;
    }
    
    void move(int dx, int dy) override {
        x += dx;
        y += dy;
        cout << "Параллелограмм перемещён на (" << dx << "," << dy << ")" << endl;
    }
    
    void rotate(double angle) override {
        rotation += angle;
        cout << "Параллелограмм повёрнут на " << angle << "°, общий поворот " << rotation << "°" << endl;
    }
    
    virtual void setDimensions(int w, int h, double sk) {
        width = w;
        height = h;
        skew = sk;
    }
};

// Класс Прямоугольник (наследует Параллелограмм, но может быть отождествлён)
class Rectangle : virtual public Parallelogram {
public:
    Rectangle(int x = 0, int y = 0, int w = 0, int h = 0)
        : Point(x, y), Parallelogram(x, y, w, h, 0) // наклон 0 для прямоугольника
    {
        skew = 0;
    }
    
    void draw() const override {
        cout << "Рисую прямоугольник с центром (" << x << "," << y 
             << "), ширина=" << width << ", высота=" << height 
             << ", поворот=" << rotation << "°" << endl;
    }
    
    void setDimensions(int w, int h) {
        width = w;
        height = h;
        skew = 0;
    }
};

// Класс Ромб
class Rhombus : virtual public Parallelogram {
public:
    Rhombus(int x = 0, int y = 0, int side = 0, double angle = 60)
        : Point(x, y), Parallelogram(x, y, side, side, angle) {}
    
    void draw() const override {
        cout << "Рисую ромб с центром (" << x << "," << y 
             << "), сторона=" << width << ", острый угол=" << skew 
             << "°, поворот=" << rotation << "°" << endl;
    }
    
    void setSide(int side) {
        width = height = side;
    }
};

// Класс Квадрат (отождествляется с параллелограммом через виртуальное наследование)
// Демонстрация отождествления: Квадрат является частным случаем параллелограмма
class Square : virtual public Parallelogram {
public:
    Square(int x = 0, int y = 0, int side = 0)
        : Point(x, y), Parallelogram(x, y, side, side, 90) // квадрат - параллелограмм с углом 90°
    {
        skew = 90;
    }
    
    void draw() const override {
        cout << "Рисую квадрат с центром (" << x << "," << y 
             << "), сторона=" << width << ", поворот=" << rotation << "°" << endl;
    }
    
    void setSide(int side) {
        width = height = side;
    }
    
    // Отождествление: метод для преобразования квадрата в параллелограмм
    Parallelogram* toParallelogram() {
        return dynamic_cast<Parallelogram*>(this);
    }
};

// Демонстрация множественного наследования и отождествления
// Класс SquareAsParallelogram показывает, что квадрат МОЖЕТ БЫТЬ параллелограммом
class SquareAsParallelogram : public Square, public Parallelogram {
public:
    SquareAsParallelogram(int x = 0, int y = 0, int side = 0)
        : Point(x, y), Square(x, y, side), Parallelogram(x, y, side, side, 90) {}
    
    void draw() const override {
        cout << "Квадрат как параллелограмм: ";
        Parallelogram::draw();
    }
};

// Функция для демонстрации позднего связывания (динамического полиморфизма)
void demonstrateLateBinding(vector<Point*>& shapes) {
    cout << "\n=== Демонстрация позднего связывания ===" << endl;
    cout << "Вызываются виртуальные методы через указатели на базовый класс Point\n" << endl;
    
    for (auto shape : shapes) {
        shape->draw();
        shape->move(5, 5);
        shape->rotate(15);
        shape->erase();
        cout << "------------------------" << endl;
    }
}

// Демонстрация различных уровней доступа
class AccessDemo {
public:
    void demonstrateAccess(Parallelogram& p) {
        cout << "\n=== Демонстрация уровней доступа ===" << endl;
        
        // Публичный доступ
        p.draw();  // public метод
        
        // Доступ через публичные методы-обёртки
        cout << "Координаты через публичный геттер: (" << p.getX() << "," << p.getY() << ")" << endl;
        p.setPosition(100, 100);  // публичный метод установки
        
        // Доступ к защищённым членам через публичные методы производных классов
        // Прямой доступ к protected членам невозможен извне
        // p.x = 10;  // ОШИБКА: protected член недоступен
        
        // Приватные методы полностью скрыты
        // p.validateCoordinates(); // ОШИБКА: приватный метод недоступен
    }
};

int main() {
    cout << "======= ИЕРАРХИЯ ГЕОМЕТРИЧЕСКИХ ОБЪЕКТОВ =======\n" << endl;
    
    // Создание объектов
    Line line(10, 20, 50, 45);
    Rectangle rect(30, 40, 60, 40);
    Rhombus rhomb(50, 60, 40, 60);
    Square square(70, 80, 30);
    Parallelogram para(90, 100, 70, 35, 30);
    
    // Демонстрация работы методов
    cout << "--- Работа с линией ---" << endl;
    line.draw();
    line.move(10, -5);
    line.rotate(30);
    line.erase();
    
    cout << "\n--- Работа с прямоугольником ---" << endl;
    rect.draw();
    rect.move(-10, 20);
    rect.rotate(45);
    rect.erase();
    
    cout << "\n--- Работа с ромбом ---" << endl;
    rhomb.draw();
    rhomb.rotate(20);
    
    cout << "\n--- Работа с квадратом ---" << endl;
    square.draw();
    square.move(15, 15);
    square.rotate(90);
    
    cout << "\n--- Работа с параллелограммом ---" << endl;
    para.draw();
    para.rotate(25);
    
    // Отождествление базовых объектов: Квадрат как Параллелограмм
    cout << "\n=== ОТОЖДЕСТВЛЕНИЕ: Квадрат как Параллелограмм ===" << endl;
    Square mySquare(200, 200, 50);
    cout << "Исходный квадрат: ";
    mySquare.draw();
    
    // Отождествление через указатель на базовый класс
    Parallelogram* paraPtr = &mySquare;
    cout << "Квадрат, рассматриваемый как параллелограмм: ";
    paraPtr->draw();
    
    // Демонстрация виртуального наследования - квадрат может выступать как параллелограмм
    cout << "\nКвадрат может использоваться везде, где ожидается параллелограмм:" << endl;
    vector<Parallelogram*> parallelograms;
    parallelograms.push_back(&para);
    parallelograms.push_back(&rect);
    parallelograms.push_back(&rhomb);
    parallelograms.push_back(&mySquare);  // Квадрат отождествляется с параллелограммом
    
    for (auto p : parallelograms) {
        p->draw();
    }
    
    // Демонстрация позднего связывания (динамический полиморфизм)
    vector<Point*> shapes;
    shapes.push_back(&line);
    shapes.push_back(&rect);
    shapes.push_back(&rhomb);
    shapes.push_back(&square);
    shapes.push_back(&para);
    
    demonstrateLateBinding(shapes);
    
    // Демонстрация различных вариантов регламентации доступа
    AccessDemo accessDemo;
    accessDemo.demonstrateAccess(para);
    
    // Проверка, что Point является абстрактным классом (нельзя создать экземпляр)
    // Point p;  // ОШИБКА: невозможно создать экземпляр абстрактного класса
    
    cout << "\n=== Проверка полиморфизма и dynamic_cast ===" << endl;
    for (auto shape : shapes) {
        // Проверяем, является ли объект квадратом
        Square* sq = dynamic_cast<Square*>(shape);
        if (sq) {
            cout << "Объект является квадратом: ";
            sq->draw();
        }
        
        // Проверяем, является ли объект параллелограммом
        Parallelogram* pgm = dynamic_cast<Parallelogram*>(shape);
        if (pgm) {
            cout << "Объект является параллелограммом (или его наследником)" << endl;
        }
    }
    
    cout << "\n=== Демонстрация виртуального деструктора ===" << endl;
    Point* basePtr = new Square(150, 150, 25);
    basePtr->draw();
    delete basePtr;  // Правильно вызовет деструктор Square через виртуальный деструктор Point
    
    cout << "\nПрограмма завершена успешно!" << endl;
    
    return 0;
}
