#include <iostream>
#include <vector>
using namespace std;

// 1. Абстрактный класс Точка (чисто виртуальные методы)
class Point {
protected:
    int x, y;
public:
    Point(int x=0, int y=0) : x(x), y(y) {}
    virtual ~Point() {}
    
    virtual void draw() = 0;      // изобразить
    virtual void erase() = 0;     // убрать
    virtual void move(int dx, int dy) = 0;      // передвинуть
    virtual void rotate(double ang) = 0;        // повернуть
    
    // Публичные методы для демонстрации доступа
    int getX() { return x; }
    int getY() { return y; }
    
protected:
    void setX(int nx) { x = nx; }  // защищённый метод
};

// 2. Линия
class Line : public Point {
    int len;
    double ang;
public:
    Line(int x, int y, int l, double a) : Point(x,y), len(l), ang(a) {}
    
    void draw() { cout << "Line at (" << x << "," << y << ") len=" << len << " ang=" << ang << endl; }
    void erase() { cout << "Erase Line" << endl; }
    void move(int dx, int dy) { x+=dx; y+=dy; cout << "Line moved by " << dx << "," << dy << endl; }
    void rotate(double a) { ang+=a; cout << "Line rotated by " << a << endl; }
};

// 3. Базовый класс Параллелограмм (виртуальное наследование от Point)
class Parallelogram : virtual public Point {
protected:
    int w, h;
    double skew, rot;
public:
    Parallelogram(int x, int y, int w_, int h_, double sk) : Point(x,y), w(w_), h(h_), skew(sk), rot(0) {}
    
    void draw() { cout << "Parallelogram at (" << x << "," << y << ") w=" << w << " h=" << h << " skew=" << skew << endl; }
    void erase() { cout << "Erase Parallelogram" << endl; }
    void move(int dx, int dy) { x+=dx; y+=dy; cout << "Parallelogram moved" << endl; }
    void rotate(double a) { rot+=a; cout << "Parallelogram rotated by " << a << endl; }
    
    int getW() { return w; }
    int getH() { return h; }
};

// 4. Прямоугольник (виртуально наследует Parallelogram)
class Rectangle : virtual public Parallelogram {
public:
    Rectangle(int x, int y, int w_, int h_) : Point(x,y), Parallelogram(x,y,w_,h_,0) {}
    
    void draw() { cout << "Rectangle at (" << x << "," << y << ") w=" << w << " h=" << h << endl; }
};

// 5. Ромб (виртуально наследует Parallelogram)
class Rhombus : virtual public Parallelogram {
public:
    Rhombus(int x, int y, int side, double ang) : Point(x,y), Parallelogram(x,y,side,side,ang) {}
    
    void draw() { cout << "Rhombus at (" << x << "," << y << ") side=" << w << " angle=" << skew << endl; }
};

// 6. Квадрат (виртуально наследует Parallelogram)
class Square : virtual public Parallelogram {
public:
    Square(int x, int y, int side) : Point(x,y), Parallelogram(x,y,side,side,90) {}
    
    void draw() { cout << "Square at (" << x << "," << y << ") side=" << w << endl; }
};

int main() {
    cout << "=== TASK 1: CLASS HIERARCHY ===\n";
    Line line(10,10,50,45);
    Rectangle rect(20,20,60,40);
    Rhombus rhomb(30,30,40,60);
    Square square(40,40,30);
    Parallelogram para(50,50,70,35,30);
    
    // Демонстрация всех методов
    line.draw(); line.move(5,5); line.rotate(30); line.erase(); cout << "\n";
    rect.draw(); rect.move(5,5); rect.rotate(45); rect.erase(); cout << "\n";
    rhomb.draw(); rhomb.move(5,5); rhomb.rotate(20); rhomb.erase(); cout << "\n";
    square.draw(); square.move(5,5); square.rotate(90); square.erase(); cout << "\n";
    
    // === TASK 2: РАЗНЫЕ УРОВНИ ДОСТУПА ===
    cout << "=== TASK 2: ACCESS CONTROL ===\n";
    cout << "Public access: getX() = " << rect.getX() << ", getY() = " << rect.getY() << endl;
    // rect.x = 100;        // ОШИБКА: protected (раскомментировать для проверки)
    // rect.setX(100);      // ОШИБКА: protected метод (раскомментировать для проверки)
    rect.move(10,10);      // public метод - OK
    cout << "Public method move() works, protected members inaccessible\n\n";
    
    // === TASK 3: ОТОЖДЕСТВЛЕНИЕ КВАДРАТА И ПАРАЛЛЕЛОГРАММА (виртуальное наследование) ===
    cout << "=== TASK 3: IDENTIFICATION (Virtual Inheritance) ===\n";
    Square mySquare(100,100,50);
    cout << "As Square: "; mySquare.draw();
    
    Parallelogram* pPtr = &mySquare;  // Отождествление: Square как Parallelogram
    cout << "As Parallelogram: "; pPtr->draw();
    pPtr->move(10,10);
    cout << "After move as Parallelogram: "; pPtr->draw();
    cout << "Square IS-A Parallelogram (virtual inheritance works)\n\n";
    
    // === TASK 4: ТОЧКА - АБСТРАКТНЫЙ КЛАСС ===
    cout << "=== TASK 4: Point is ABSTRACT ===\n";
    // Point p;  // ОШИБКА: нельзя создать объект абстрактного класса (раскомментировать для проверки)
    cout << "Point has pure virtual methods => ABSTRACT CLASS\n";
    cout << "Cannot instantiate Point, only pointers/references\n\n";
    
    // === TASK 5: ПОЗДНЕЕ СВЯЗЫВАНИЕ (динамический полиморфизм) ===
    cout << "=== TASK 5: LATE BINDING (Dynamic Polymorphism) ===\n";
    vector<Point*> shapes;
    shapes.push_back(&line);
    shapes.push_back(&rect);
    shapes.push_back(&rhomb);
    shapes.push_back(&square);
    shapes.push_back(&para);
    shapes.push_back(&mySquare);
    
    for (Point* shape : shapes) {
        cout << "Calling draw() via Point*: ";
        shape->draw();  // Позднее связывание - реальный тип определяется в runtime
        shape->move(1,1);
        cout << "---\n";
    }
    
    // Дополнительная проверка полиморфизма
    cout << "\n=== POLYMORPHISM VERIFICATION ===\n";
    Point* ptr = new Square(200,200,60);
    ptr->draw();      // Вызовется Square::draw() (позднее связывание)
    ptr->rotate(45);
    delete ptr;       // Виртуальный деструктор
    
    cout << "\n=== ALL TASKS COMPLETED SUCCESSFULLY ===\n";
    return 0;
}
