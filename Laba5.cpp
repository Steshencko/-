#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <iomanip>

using namespace std;

class Vehicle {
public:
    explicit Vehicle(string name) : name_(std::move(name)) {}
    virtual ~Vehicle() = default;

    virtual double move() const {
        return 0.0;
    }

    virtual string describe() const {
        return name_;
    }

protected:
    string name_;
};

class Car : public Vehicle {
public:
    Car(string name, double speedKmh, double fuelPer100)
        : Vehicle(std::move(name)), speedKmh_(speedKmh), fuelPer100_(fuelPer100) {}

    double move() const override {
        return (100.0 / speedKmh_) * (fuelPer100_ / 100.0) * 100.0;
    }

    string describe() const override {
        return name_ + " (автомобиль, " + to_string(speedKmh_) + " км/ч)";
    }

private:
    double speedKmh_;
    double fuelPer100_;
};

class Bicycle : public Vehicle {
public:
    Bicycle(string name, double speedKmh, double riderMassKg)
        : Vehicle(std::move(name)), speedKmh_(speedKmh), riderMassKg_(riderMassKg) {}

    double move() const override {
        double hours = 100.0 / speedKmh_;
        return riderMassKg_ * hours * 4.0;
    }

    string describe() const override {
        return name_ + " (велосипед, " + to_string(speedKmh_) + " км/ч)";
    }

private:
    double speedKmh_;
    double riderMassKg_;
};

class Airplane : public Vehicle {
public:
    Airplane(string name, double cruiseKmh, double fuelPer100)
        : Vehicle(std::move(name)), cruiseKmh_(cruiseKmh), fuelPer100_(fuelPer100) {}

    double move() const override {
        return (100.0 / cruiseKmh_) * fuelPer100_;
    }

    string describe() const override {
        return name_ + " (самолёт, " + to_string(cruiseKmh_) + " км/ч)";
    }

private:
    double cruiseKmh_;
    double fuelPer100_;
};

int main() {
    // Задание 1
    Car car("Лада", 90.0, 7.0);
    Bicycle bike("Стелс", 20.0, 75.0);
    Airplane plane("Боинг", 900.0, 3000.0);

    cout << "=== Задание 1: прямой вызов переопределённого метода ===\n";
    cout << car.describe()   << " -> move() = " << car.move()   << "\n";
    cout << bike.describe()  << " -> move() = " << bike.move()  << "\n";
    cout << plane.describe() << " -> move() = " << plane.move() << "\n\n";

    // Задание 2
    vector<unique_ptr<Vehicle>> fleet;
    fleet.push_back(make_unique<Car>("Лада", 90.0, 7.0));
    fleet.push_back(make_unique<Bicycle>("Стелс", 20.0, 75.0));
    fleet.push_back(make_unique<Airplane>("Боинг", 900.0, 3000.0));
    fleet.push_back(make_unique<Car>("КамАЗ", 60.0, 25.0));
    fleet.push_back(make_unique<Bicycle>("Мерида", 25.0, 65.0));

    cout << "=== Задание 2: единый цикл по коллекции ===\n";
    double total = 0.0;
    int count = 0;
    for (const auto& v : fleet) {
        double cost = v->move();
        total += cost;
        ++count;
        cout << fixed << setprecision(3)
             << v->describe() << " -> move() = " << cost << "\n";
    }
    cout << "Всего объектов: " << count << "\n";
    cout << fixed << setprecision(3)
         << "Суммарный показатель move() по коллекции = " << total << "\n";
    return 0;
}
