#include <iostream>
#include <vector>
using namespace std;

// Абстрактный класс Точка (содержит чисто виртуальные методы)
class Point {
protected:
    int x, y;
public:
    Point(int x=0, int y=0) : x(x), y(y) {}
    virtual ~Point() {}
    
    // Чисто виртуальные методы (делают класс абстрактным)
    virtual void draw() = 0;
    virtual void erase() = 0;
    virtual void move(int dx, int dy) = 0;
    virtual void rotate(double angle) = 0;
    
    // Публичные методы доступа
    int getX() { return x; }
    int getY() { return y; }
    
protected:
    void setX(int nx) { x = nx; }
    void setY(int ny) { y = ny; }
};

// Линия (наследует Point)
class Line : public Point {
    int length;
    double angle;
public:
    Line(int x, int y, int len, double ang) : Point(x, y), length(len), angle(ang) {}
    
    void draw() { cout << "Line at (" << x << "," << y << ") len=" << length << " ang=" << angle << endl; }
    void erase() { cout << "Erase line" << endl; }
    void move(int dx, int dy) { x += dx; y += dy; cout << "Line moved by " << dx << "," << dy << endl; }
    void rotate(double a) { angle += a; cout << "Line rotated by " << a << endl; }
};

// Параллелограмм
class Parallelogram : virtual public Point {
protected:
    int width, height;
    double skew, rotation;
public:
    Parallelogram(int x, int y, int w, int h, double sk) : Point(x, y), width(w), height(h), skew(sk), rotation(0) {}
    
    void draw() { cout << "Parallelogram at (" << x << "," << y << ") w=" << width << " h=" << height << " skew=" << skew << endl; }
    void erase() { cout << "Erase parallelogram" << endl; }
    void move(int dx, int dy) { x += dx; y += dy; cout << "Parallelogram moved" << endl; }
    void rotate(double a) { rotation += a; cout << "Parallelogram rotated by " << a << endl; }
};

// Прямоугольник (параллелограмм с skew=0)
class Rectangle : virtual public Parallelogram {
public:
    Rectangle(int x, int y, int w, int h) : Point(x, y), Parallelogram(x, y, w, h, 0) {}
    
    void draw() { cout << "Rectangle at (" << x << "," << y << ") w=" << width << " h=" << height << endl; }
};

// Ромб (параллелограмм с равными сторонами)
class Rhombus : virtual public Parallelogram {
public:
    Rhombus(int x, int y, int side, double ang) : Point(x, y), Parallelogram(x, y, side, side, ang) {}
    
    void draw() { cout << "Rhombus at (" << x << "," << y << ") side=" << width << " angle=" << skew << endl; }
};

// Квадрат
class Square : virtual public Parallelogram {
public:
    Square(int x, int y, int side) : Point(x, y), Parallelogram(x, y, side, side, 90) {}
    
    void draw() { cout << "Square at (" << x << "," << y << ") side=" << width << endl; }
};

int main() {
    cout << "=== GEOMETRY HIERARCHY DEMO ===\n\n";
    
    // 1. Создание объектов
    Line line(10, 20, 50, 45);
    Rectangle rect(30, 40, 60, 40);
    Rhombus rhomb(50, 60, 40, 60);
    Square square(70, 80, 30);
    Parallelogram para(90, 100, 70, 35, 30);
    
    // 2. Демонстрация методов
    cout << "--- Line ---\n";
    line.draw();
    line.move(5, 5);
    line.rotate(30);
    line.erase();
    
    cout << "\n--- Rectangle ---\n";
    rect.draw();
    rect.move(-10, 20);
    rect.rotate(45);
    
    cout << "\n--- Rhombus ---\n";
    rhomb.draw();
    rhomb.rotate(20);
    
    cout << "\n--- Square ---\n";
    square.draw();
    square.move(15, 15);
    square.rotate(90);
    
    cout << "\n--- Parallelogram ---\n";
    para.draw();
    para.rotate(25);
    
    // 3. ОТОЖДЕСТВЛЕНИЕ: Квадрат как Параллелограмм (виртуальное наследование)
    cout << "\n=== IDENTIFICATION: Square as Parallelogram ===\n";
    Square mySquare(200, 200, 50);
    cout << "Original: "; mySquare.draw();
    
    Parallelogram* paraPtr = &mySquare;
    cout << "As Parallelogram: "; paraPtr->draw();
    
    // 4. Различные уровни доступа
    cout << "\n=== ACCESS DEMO ===\n";
    cout << "Public getter: x=" << rect.getX() << ", y=" << rect.getY() << endl;
    // rect.x = 10;  // ОШИБКА: protected! (раскомментировать для проверки)
    // rect.validateCoordinates(); // ОШИБКА: private! (если бы был)
    
    // 5. ПОЗДНЕЕ СВЯЗЫВАНИЕ (динамический полиморфизм)
    cout << "\n=== LATE BINDING (Polymorphism) ===\n";
    vector<Point*> shapes;
    shapes.push_back(&line);
    shapes.push_back(&rect);
    shapes.push_back(&rhomb);
    shapes.push_back(&square);
    shapes.push_back(&para);
    shapes.push_back(&mySquare);
    
    for (Point* shape : shapes) {
        shape->draw();  // Позднее связывание - вызывается метод реального типа
        shape->move(2, 2);
        cout << "---\n";
    }
    
    // 6. Проверка dynamic_cast
    cout << "\n=== TYPE CHECK ===\n";
    for (Point* shape : shapes) {
        Square* s = dynamic_cast<Square*>(shape);
        if (s) cout << "Found Square: "; s ? s->draw() : cout << "";
        
        Parallelogram* p = dynamic_cast<Parallelogram*>(shape);
        if (p) cout << " (is Parallelogram)\n";
    }
    
    // 7. Демонстрация виртуального деструктора
    cout << "\n=== VIRTUAL DESTRUCTOR ===\n";
    Point* ptr = new Square(150, 150, 25);
    ptr->draw();
    delete ptr;  // Правильно вызывает деструктор Square
    
    // Point p;  // ОШИБКА: нельзя создать абстрактный класс!
    
    cout << "\n=== PROGRAM COMPLETED ===\n";
    return 0;
}
