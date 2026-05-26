#include iostream
#include string
#include cmath
#include vector

using namespace std;

 ========== АБСТРАКТНЫЙ КЛАСС ТОЧКА ==========
 Абстрактный класс содержит хотя бы одну чистую виртуальную функцию
class Point {
private
    double x, y;   координаты точки (инкапсуляция)
    static int totalShapes;   счётчик всех фигур
    
protected
     Защищённые методы для доступа наследников
    void setX(double xCoord) { x = xCoord; }
    void setY(double yCoord) { y = yCoord; }
    
public
     Конструкторы
    Point(double xCoord = 0, double yCoord = 0)  x(xCoord), y(yCoord) {
        totalShapes++;
        cout  Создана точка (  x  ,   y  )  endl;
    }
    
     Виртуальный деструктор (обязателен для абстрактных классов)
    virtual ~Point() {
        cout  Удалена точка (  x  ,   y  )  endl;
    }
    
     Чистая виртуальная функция (делает класс абстрактным)
    virtual void draw() const = 0;            изобразить
    virtual void erase() = 0;                 убрать
    virtual void move(double dx, double dy) = 0;   передвинуть
    virtual void rotate(double angle) = 0;    повернуть
    
     Обычные методы (не виртуальные)
    double getX() const { return x; }
    double getY() const { return y; }
    
     Виртуальный метод с реализацией по умолчанию
    virtual void info() const {
        cout  Точка в координатах (  x  ,   y  );
    }
    
    static int getTotalShapes() { return totalShapes; }
};

int PointtotalShapes = 0;

 ========== КЛАСС ЛИНИЯ (наследует Point) ==========
class Line  virtual public Point {
private
    double x2, y2;   координаты конца линии
    string color;    цвет линии (дополнительное свойство)
    
public
     Конструктор
    Line(double x1 = 0, double y1 = 0, double x2Coord = 1, double y2Coord = 1, 
         const string& lineColor = черный)
         Point(x1, y1), x2(x2Coord), y2(y2Coord), color(lineColor) {
        cout     - как линия от (  getX()  ,   getY() 
              ) до (  x2  ,   y2  ), цвет   color  endl;
    }
    
     Деструктор
    virtual ~Line() {
        cout  Удалена линия от (  getX()  ,   getY() 
              ) до (  x2  ,   y2  )  endl;
    }
    
     Реализация виртуальных методов
    virtual void draw() const override {
        cout    🖌️  РИСУЮ линию от (  getX()  ,   getY() 
              ) до (  x2  ,   y2  ) цветом   color  endl;
    }
    
    virtual void erase() override {
        cout    🧽 СТИРАЮ линию от (  getX()  ,   getY() 
              ) до (  x2  ,   y2  )  endl;
    }
    
    virtual void move(double dx, double dy) override {
        cout    ➡️  ПЕРЕДВИГАЮ линию на (  dx  ,   dy  )  endl;
         Передвигаем начальную точку (через protected методы)
        setX(getX() + dx);
        setY(getY() + dy);
        x2 += dx;
        y2 += dy;
    }
    
    virtual void rotate(double angle) override {
        cout    🔄 ПОВОРАЧИВАЮ линию на   angle   градусов вокруг центра  endl;
         Поворот линии (упрощённая реализация)
        double centerX = (getX() + x2)  2;
        double centerY = (getY() + y2)  2;
        double rad = angle  M_PI  180.0;
        
        double x1_rel = getX() - centerX;
        double y1_rel = getY() - centerY;
        double x2_rel = x2 - centerX;
        double y2_rel = y2 - centerY;
        
        double newX1 = centerX + x1_rel  cos(rad) - y1_rel  sin(rad);
        double newY1 = centerY + x1_rel  sin(rad) + y1_rel  cos(rad);
        double newX2 = centerX + x2_rel  cos(rad) - y2_rel  sin(rad);
        double newY2 = centerY + x2_rel  sin(rad) + y2_rel  cos(rad);
        
        const_castLine(this)-setX(newX1);
        const_castLine(this)-setY(newY1);
        x2 = newX2;
        y2 = newY2;
    }
    
    virtual void info() const override {
        Pointinfo();
        cout  , линия до (  x2  ,   y2  ), цвет   color;
    }
    
     Специфические методы для линии
    double getLength() const {
        return sqrt(pow(x2 - getX(), 2) + pow(y2 - getY(), 2));
    }
};

 ========== КЛАСС ПАРАЛЛЕЛОГРАММ (виртуальное наследование от Point) ==========
class Parallelogram  virtual public Point {
protected
    double width;    ширина
    double height;   высота
    double skew;     угол наклона (для параллелограмма)
    string fillColor;
    
public
    Parallelogram(double xCoord = 0, double yCoord = 0, 
                  double w = 1, double h = 1, double sk = 0,
                  const string& color = белый)
         Point(xCoord, yCoord), width(w), height(h), skew(sk), fillColor(color) {
        cout     - как параллелограмм   width  x  height 
              , наклон   skew  °, цвет   fillColor  endl;
    }
    
    virtual ~Parallelogram() {
        cout  Удалён параллелограмм  endl;
    }
    
    virtual void draw() const override {
        cout    🖌️  РИСУЮ параллелограмм в точке (  getX()  ,   getY() 
              ), размер   width  x  height 
              , наклон   skew  °, цвет   fillColor  endl;
    }
    
    virtual void erase() override {
        cout    🧽 СТИРАЮ параллелограмм  endl;
    }
    
    virtual void move(double dx, double dy) override {
        cout    ➡️  ПЕРЕДВИГАЮ параллелограмм на (  dx  ,   dy  )  endl;
        setX(getX() + dx);
        setY(getY() + dy);
    }
    
    virtual void rotate(double angle) override {
        cout    🔄 ПОВОРАЧИВАЮ параллелограмм на   angle   градусов  endl;
        skew += angle;
        if (skew = 360) skew -= 360;
    }
    
    virtual void info() const override {
        Pointinfo();
        cout  , параллелограмм   width  x  height 
              , наклон   skew  °;
    }
    
    double getArea() const {
        return width  height  sin(skew  M_PI  180.0);
    }
};

 ========== КЛАСС ПРЯМОУГОЛЬНИК (наследует Параллелограмм) ==========
class Rectangle  public Parallelogram {
public
    Rectangle(double xCoord = 0, double yCoord = 0, 
              double w = 1, double h = 1, const string& color = белый)
         Point(xCoord, yCoord), Parallelogram(xCoord, yCoord, w, h, 90, color) {
        cout        - как прямоугольник (угол 90°)  endl;
    }
    
    virtual ~Rectangle() {
        cout  Удалён прямоугольник  endl;
    }
    
    virtual void draw() const override {
        cout    🖌️  РИСУЮ ПРЯМОУГОЛЬНИК в (  getX()  ,   getY() 
              ), размер   width  x  height 
              , цвет   fillColor  endl;
    }
    
    virtual void rotate(double angle) override {
        cout    🔄 ПОВОРАЧИВАЮ прямоугольник на   angle   градусов  endl;
         Для прямоугольника поворот меняет ширину и высоту местами через 90°
        if (fmod(angle, 90) == 0 && (int(angle  90) % 2 != 0)) {
            swap(width, height);
        }
    }
    
    virtual void info() const override {
        Pointinfo();
        cout  , прямоугольник   width  x  height;
    }
};

 ========== КЛАСС РОМБ (наследует Параллелограмм) ==========
class Rhombus  public Parallelogram {
private
    double diagonal1;
    double diagonal2;
    
public
    Rhombus(double xCoord = 0, double yCoord = 0, 
            double d1 = 1, double d2 = 1, const string& color = белый)
         Point(xCoord, yCoord), Parallelogram(xCoord, yCoord, d12, d22, 60, color),
          diagonal1(d1), diagonal2(d2) {
        cout        - как ромб с диагоналями   d1   и   d2  endl;
    }
    
    virtual ~Rhombus() {
        cout  Удалён ромб  endl;
    }
    
    virtual void draw() const override {
        cout    🖌️  РИСУЮ РОМБ в (  getX()  ,   getY() 
              ), диагонали   diagonal1   и   diagonal2 
              , цвет   fillColor  endl;
    }
    
    virtual void info() const override {
        Pointinfo();
        cout  , ромб с диагоналями   diagonal1   и   diagonal2;
    }
};

 ========== КЛАСС КВАДРАТ (виртуальное наследование от Rectangle и Rhombus) ==========
 Демонстрация отождествления через виртуальное наследование
class Square  public Rectangle, public Rhombus {
private
    double side;
    
public
    Square(double xCoord = 0, double yCoord = 0, double s = 1, const string& color = белый)
         Point(xCoord, yCoord),
          Rectangle(xCoord, yCoord, s, s, color),
          Rhombus(xCoord, yCoord, s  sqrt(2), s  sqrt(2), color),
          side(s) {
        cout           ★ КВАДРАТ со стороной   side   (отождествлён с Rectangle и Rhombus)  endl;
    }
    
    virtual ~Square() {
        cout  Удалён квадрат  endl;
    }
    
     Переопределение методов с демонстрацией позднего связывания
    virtual void draw() const override {
        cout    🖌️  РИСУЮ КВАДРАТ в (  getX()  ,   getY() 
              ), сторона   side  , цвет   fillColor  endl;
        cout       (Отождествлён это и прямоугольник, и ромб)  endl;
    }
    
    virtual void erase() override {
        cout    🧽 СТИРАЮ квадрат  endl;
    }
    
    virtual void move(double dx, double dy) override {
        cout    ➡️  ПЕРЕДВИГАЮ квадрат на (  dx  ,   dy  )  endl;
        setX(getX() + dx);
        setY(getY() + dy);
    }
    
    virtual void rotate(double angle) override {
        cout    🔄 ПОВОРАЧИВАЮ квадрат на   angle   градусов  endl;
         Квадрат совмещает свойства прямоугольника и ромба
        Rectanglerotate(angle);
    }
    
    virtual void info() const override {
        cout  Квадрат со стороной   side;
        cout  , координаты (  getX()  ,   getY()  );
    }
    
    double getSide() const { return side; }
    double getArea() const { return side  side; }
};

 ========== ДЕМОНСТРАЦИЯ РАЗЛИЧНЫХ ВАРИАНТОВ ДОСТУПА ==========

 1. Дружественная функция для демонстрации доступа к private членам
class ShapeDemo {
private
    string demoName;
    
public
    ShapeDemo(const string& name)  demoName(name) {}
    
     Дружественная функция может получить доступ к private членам
    friend void showPointAccess(const Point& p, const string& context);
    
     Дружественный класс
    friend class ShapeTester;
};

void showPointAccess(const Point& p, const string& context) {
     Дружественная функция имеет доступ к private членам Point
    cout  context   точка с координатами ( 
          p.getX()  ,   p.getY()  )  endl;
}

 Дружественный класс
class ShapeTester {
public
    void testAccess(const Point& p) {
         Имеет доступ к protected и public членам
        cout    Тестирование доступа координаты точки ( 
              p.getX()  ,   p.getY()  )  endl;
    }
    
    void demoPublicPrivateProtected() {
        cout  n=== ДЕМОНСТРАЦИЯ УРОВНЕЙ ДОСТУПА ===  endl;
        cout  public   доступны всем  endl;
        cout  private  доступны только внутри класса  endl;
        cout  protected доступны внутри класса и наследникам  endl;
        cout  friend   доступны друзьям класса  endl;
    }
};

 ========== ГЛАВНАЯ ФУНКЦИЯ ==========

int main() {
    cout  n╔══════════════════════════════════════════════════════════════╗n;
    cout  ║     ГЕОМЕТРИЧЕСКАЯ ИЕРАРХИЯ ПОЗДНЕЕ СВЯЗЫВАНИЕ (ПОЛИМОРФИЗМ)  ║n;
    cout  ╚══════════════════════════════════════════════════════════════╝nn;
    
     ===== 1. ДЕМОНСТРАЦИЯ АБСТРАКТНОГО КЛАССА =====
    cout  === ЧАСТЬ 1 АБСТРАКТНЫЙ КЛАСС ===  endl;
     Point p;  ОШИБКА! Нельзя создать объект абстрактного класса
    cout  ✓ Абстрактный класс Point создан (нельзя инстанциировать)n  endl;
    
     ===== 2. СОЗДАНИЕ ОБЪЕКТОВ РАЗНЫХ ТИПОВ =====
    cout  === ЧАСТЬ 2 СОЗДАНИЕ ГЕОМЕТРИЧЕСКИХ ОБЪЕКТОВ ===  endl;
    
    Line line(0, 0, 5, 5, синий);
    Rectangle rect(10, 10, 4, 3, зелёный);
    Rhombus rhomb(20, 20, 6, 4, оранжевый);
    Square square(30, 30, 5, красный);
    Parallelogram para(40, 40, 5, 3, 45, фиолетовый);
    
    cout  n;
    
     ===== 3. ДЕМОНСТРАЦИЯ ПОЗДНЕГО СВЯЗЫВАНИЯ (ПОЛИМОРФИЗМ) =====
    cout  === ЧАСТЬ 3 ПОЗДНЕЕ СВЯЗЫВАНИЕ (массив указателей на базовый класс) ===  endl;
    
     Массив указателей на базовый класс Point
    Point shapes[] = {&line, &rect, &rhomb, &square, &para};
    const char shapeNames[] = {Линия, Прямоугольник, Ромб, Квадрат, Параллелограмм};
    
    cout  n🎨 ДЕМОНСТРАЦИЯ Все объекты через указатель на Point  endl;
    cout  ----------------------------------------------------  endl;
    
    for (int i = 0; i  5; i++) {
        cout  n  shapeNames[i]    endl;
        shapes[i]-draw();
        shapes[i]-move(1, 1);
        shapes[i]-rotate(45);
        shapes[i]-info();
        cout  endl;
    }
    
     ===== 4. ВИРТУАЛЬНОЕ НАСЛЕДОВАНИЕ (КВАДРАТ) =====
    cout  nn=== ЧАСТЬ 4 ОТОЖДЕСТВЛЕНИЕ КВАДРАТА ===  endl;
    cout  Квадрат наследуется от Rectangle и Rhombus с виртуальным наследованием  endl;
    cout  =================================================================  endl;
    
    Rectangle rectPtr = &square;
    Rhombus rhombPtr = &square;
    
    cout  nКвадрат как прямоугольник ;
    rectPtr-draw();
    cout  Квадрат как ромб ;
    rhombPtr-draw();
    
    cout  n✓ Квадрат успешно отождествлён с Rectangle и Rhombus!  endl;
    
     ===== 5. ДОКАЗАТЕЛЬСТВО ПОЗДНЕГО СВЯЗЫВАНИЯ =====
    cout  nn=== ЧАСТЬ 5 ДОКАЗАТЕЛЬСТВО ПОЗДНЕГО СВЯЗЫВАНИЯ ===  endl;
    cout  Вызов методов через указатель на базовый класс  endl;
    cout  -------------------------------------------------  endl;
    
     Обычный вызов (раннее связывание)
    line.draw();
    
     Позднее связывание (через указатель)
    Point p = &square;
    cout  nЧерез указатель на Point вызывается draw() квадрата ;
    p-draw();
    
    cout  n✓ ПОЛИМОРФИЗМ РАБОТАЕТ верная функция определяется во время выполнения!  endl;
    
     ===== 6. ВАРИАНТЫ ДОСТУПА К КОМПОНЕНТАМ =====
    cout  nn=== ЧАСТЬ 6 РАЗЛИЧНЫЕ ВАРИАНТЫ ДОСТУПА ===  endl;
    
    ShapeTester tester;
    tester.demoPublicPrivateProtected();
    
     Публичный доступ
    cout  n✓ public доступ   endl;
    cout    Координаты квадрата x=  square.getX()  , y=  square.getY()  endl;
    cout    Сторона квадрата   square.getSide()  endl;
    
     Защищённый доступ (через дружественную функцию)
    showPointAccess(square, n✓ friend доступ);
    
     Доступ через дружественный класс
    tester.testAccess(square);
    
     ===== 7. ДОПОЛНИТЕЛЬНАЯ ИНФОРМАЦИЯ =====
    cout  nn=== СТАТИСТИКА ===  endl;
    cout  Всего создано геометрических объектов   PointgetTotalShapes()  endl;
    
    cout  n=== ИТОГОВАЯ СВОДКА ПО ИЕРАРХИИ ===  endl;
    cout  Point (абстрактный) ← виртуальное наследование  endl;
    cout    ↑  ↑  endl;
    cout    Line    Parallelogram  endl;
    cout              ↑        ↑  endl;
    cout        Rectangle    Rhombus  endl;
    cout              ↑        ↑  endl;
    cout              └──Square──┘ (отождествление)  endl;
    
    cout  n=== ДЕСТРУКТОРЫ (автоматический вызов) ===  endl;
    cout  При завершении программы объекты удаляются в обратном порядкеn  endl;
    
    return 0;
}