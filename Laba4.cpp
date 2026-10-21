#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

class Shape {
protected:
    string name;

private:
    string color;

public:
    Shape(string n, string c) : name(n), color(c) {}

    string getColor() const { return color; }

    void setColor(const string& c) {
        if (c.empty()) throw invalid_argument("Цвет не может быть пустым");
        color = c;
    }

    virtual double area() const = 0;
    virtual ~Shape() {}
};

class Circle : public Shape {
private:
    double radius;

public:
    Circle(string c, double r) : Shape("Circle", c), radius(r) {}

    double getRadius() const { return radius; }

    double area() const override { return 3.14159 * radius * radius; }
};

class Rectangle : public Shape {
private:
    double width, height;

public:
    Rectangle(string c, double w, double h)
        : Shape("Rectangle", c), width(w), height(h) {}

    double getWidth()  const { return width; }
    double getHeight() const { return height; }

    double area() const override { return width * height; }
};

int main() {
    Circle c("red", 3);
    Rectangle r("blue", 4, 5);

    cout << c.name << " " << c.getColor() << " " << c.area() << endl;
    cout << r.name << " " << r.getColor() << " " << r.area() << endl;

    return 0;
}
