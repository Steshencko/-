#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

// Класс vect - вектор
class vect {
private:
    int dim;           // размерность вектора
    double* v;         // компоненты вектора
    int num;           // номер объекта
    static int count;  // количество созданных объектов

public:
    // Конструктор по умолчанию
    vect(int d = 1) : dim(d), num(++count) {
        v = new double[dim];
        for (int i = 0; i < dim; i++)
            v[i] = 0.0;
        cout << "Создан вектор #" << num << ", размерность=" << dim << endl;
    }

    // Конструктор копирования
    vect(const vect& other) : dim(other.dim), num(++count) {
        v = new double[dim];
        for (int i = 0; i < dim; i++)
            v[i] = other.v[i];
        cout << "Создана копия вектора #" << num << " из вектора #" << other.num << endl;
    }

    // Деструктор
    ~vect() {
        cout << "Удален вектор #" << num << ", размерность=" << dim << endl;
        delete[] v;
    }

    // Оператор присваивания v = v
    vect& operator=(const vect& other) {
        if (this != &other) {
            cout << "Присваивание: вектор #" << num << " = вектор #" << other.num << endl;
            if (dim != other.dim) {
                delete[] v;
                dim = other.dim;
                v = new double[dim];
            }
            for (int i = 0; i < dim; i++)
                v[i] = other.v[i];
        }
        return *this;
    }

    // v + v (компонентная функция)
    vect operator+(const vect& other) const {
        if (dim != other.dim) {
            cerr << "Ошибка: размерности векторов не совпадают!" << endl;
            return vect(1);
        }
        cout << "Операция: вектор #" << num << " + вектор #" << other.num << endl;
        vect result(dim);
        for (int i = 0; i < dim; i++)
            result.v[i] = v[i] + other.v[i];
        return result;
    }

    // v - v (компонентная функция)
    vect operator-(const vect& other) const {
        if (dim != other.dim) {
            cerr << "Ошибка: размерности векторов не совпадают!" << endl;
            return vect(1);
        }
        cout << "Операция: вектор #" << num << " - вектор #" << other.num << endl;
        vect result(dim);
        for (int i = 0; i < dim; i++)
            result.v[i] = v[i] - other.v[i];
        return result;
    }

    // -v (унарный минус)
    vect operator-() const {
        cout << "Операция: -вектор #" << num << endl;
        vect result(dim);
        for (int i = 0; i < dim; i++)
            result.v[i] = -v[i];
        return result;
    }

    // v * v (скалярное произведение)
    double operator*(const vect& other) const {
        if (dim != other.dim) {
            cerr << "Ошибка: размерности векторов не совпадают!" << endl;
            return 0.0;
        }
        cout << "Операция: вектор #" << num << " * вектор #" << other.num << " (скалярное произведение)" << endl;
        double result = 0;
        for (int i = 0; i < dim; i++)
            result += v[i] * other.v[i];
        return result;
    }

    // Внешняя функция k*v (друг)
    friend vect operator*(double k, const vect& vec);

    // Метод для установки компонент
    void setComponent(int index, double value) {
        if (index >= 0 && index < dim)
            v[index] = value;
    }

    // Метод для получения компоненты
    double getComponent(int index) const {
        if (index >= 0 && index < dim)
            return v[index];
        return 0;
    }

    // Метод для вывода вектора
    void print() const {
        cout << "Вектор #" << num << " (dim=" << dim << "): [";
        for (int i = 0; i < dim; i++) {
            cout << v[i];
            if (i < dim - 1) cout << ", ";
        }
        cout << "]" << endl;
    }

    // Получение размерности
    int getDim() const { return dim; }
    
    // Получение номера
    int getNum() const { return num; }
    
    // Получение количества объектов
    static int getCount() { return count; }
};

// Инициализация статической переменной
int vect::count = 0;

// Внешняя функция k * v
vect operator*(double k, const vect& vec) {
    cout << "Операция: " << k << " * вектор #" << vec.num << endl;
    vect result(vec.dim);
    for (int i = 0; i < vec.dim; i++)
        result.v[i] = k * vec.v[i];
    return result;
}

// Класс matr - матрица
class matr {
private:
    int dim;        // размерность матрицы (dim x dim)
    double** a;     // компоненты матрицы
    int num;        // номер объекта
    static int count; // количество созданных объектов

public:
    // Конструктор по умолчанию
    matr(int d = 1) : dim(d), num(++count) {
        a = new double*[dim];
        for (int i = 0; i < dim; i++) {
            a[i] = new double[dim];
            for (int j = 0; j < dim; j++)
                a[i][j] = 0.0;
        }
        cout << "Создана матрица #" << num << ", размерность=" << dim << "x" << dim << endl;
    }

    // Конструктор копирования
    matr(const matr& other) : dim(other.dim), num(++count) {
        a = new double*[dim];
        for (int i = 0; i < dim; i++) {
            a[i] = new double[dim];
            for (int j = 0; j < dim; j++)
                a[i][j] = other.a[i][j];
        }
        cout << "Создана копия матрицы #" << num << " из матрицы #" << other.num << endl;
    }

    // Деструктор
    ~matr() {
        cout << "Удалена матрица #" << num << ", размерность=" << dim << "x" << dim << endl;
        for (int i = 0; i < dim; i++)
            delete[] a[i];
        delete[] a;
    }

    // Оператор присваивания m = m
    matr& operator=(const matr& other) {
        if (this != &other) {
            cout << "Присваивание: матрица #" << num << " = матрица #" << other.num << endl;
            if (dim != other.dim) {
                for (int i = 0; i < dim; i++)
                    delete[] a[i];
                delete[] a;
                dim = other.dim;
                a = new double*[dim];
                for (int i = 0; i < dim; i++)
                    a[i] = new double[dim];
            }
            for (int i = 0; i < dim; i++)
                for (int j = 0; j < dim; j++)
                    a[i][j] = other.a[i][j];
        }
        return *this;
    }

    // m + m
    matr operator+(const matr& other) const {
        if (dim != other.dim) {
            cerr << "Ошибка: размерности матриц не совпадают!" << endl;
            return matr(1);
        }
        cout << "Операция: матрица #" << num << " + матрица #" << other.num << endl;
        matr result(dim);
        for (int i = 0; i < dim; i++)
            for (int j = 0; j < dim; j++)
                result.a[i][j] = a[i][j] + other.a[i][j];
        return result;
    }

    // m - m
    matr operator-(const matr& other) const {
        if (dim != other.dim) {
            cerr << "Ошибка: размерности матриц не совпадают!" << endl;
            return matr(1);
        }
        cout << "Операция: матрица #" << num << " - матрица #" << other.num << endl;
        matr result(dim);
        for (int i = 0; i < dim; i++)
            for (int j = 0; j < dim; j++)
                result.a[i][j] = a[i][j] - other.a[i][j];
        return result;
    }

    // -m (унарный минус)
    matr operator-() const {
        cout << "Операция: -матрица #" << num << endl;
        matr result(dim);
        for (int i = 0; i < dim; i++)
            for (int j = 0; j < dim; j++)
                result.a[i][j] = -a[i][j];
        return result;
    }

    // m * m (умножение матриц)
    matr operator*(const matr& other) const {
        if (dim != other.dim) {
            cerr << "Ошибка: размерности матриц не совпадают!" << endl;
            return matr(1);
        }
        cout << "Операция: матрица #" << num << " * матрица #" << other.num << endl;
        matr result(dim);
        for (int i = 0; i < dim; i++) {
            for (int j = 0; j < dim; j++) {
                result.a[i][j] = 0;
                for (int k = 0; k < dim; k++)
                    result.a[i][j] += a[i][k] * other.a[k][j];
            }
        }
        return result;
    }

    // Внешняя функция k * m (друг)
    friend matr operator*(double k, const matr& mat);

    // m * v (умножение матрицы на вектор)
    vect operator*(const vect& vec) const {
        if (dim != vec.getDim()) {
            cerr << "Ошибка: размерности матрицы и вектора не совпадают!" << endl;
            return vect(1);
        }
        cout << "Операция: матрица #" << num << " * вектор #" << vec.getNum() << endl;
        vect result(dim);
        for (int i = 0; i < dim; i++) {
            double sum = 0;
            for (int j = 0; j < dim; j++)
                sum += a[i][j] * vec.getComponent(j);
            result.setComponent(i, sum);
        }
        return result;
    }

    // Метод для установки элемента
    void setElement(int i, int j, double value) {
        if (i >= 0 && i < dim && j >= 0 && j < dim)
            a[i][j] = value;
    }

    // Метод для получения элемента
    double getElement(int i, int j) const {
        if (i >= 0 && i < dim && j >= 0 && j < dim)
            return a[i][j];
        return 0;
    }

    // Метод для вывода матрицы
    void print() const {
        cout << "Матрица #" << num << " (dim=" << dim << "x" << dim << "):" << endl;
        for (int i = 0; i < dim; i++) {
            cout << "  [";
            for (int j = 0; j < dim; j++) {
                cout << a[i][j];
                if (j < dim - 1) cout << ", ";
            }
            cout << "]" << endl;
        }
    }

    // Получение размерности
    int getDim() const { return dim; }
    
    // Получение номера
    int getNum() const { return num; }
    
    // Получение количества объектов
    static int getCount() { return count; }
};

// Инициализация статической переменной
int matr::count = 0;

// Внешняя функция k * m
matr operator*(double k, const matr& mat) {
    cout << "Операция: " << k << " * матрица #" << mat.num << endl;
    matr result(mat.dim);
    for (int i = 0; i < mat.dim; i++)
        for (int j = 0; j < mat.dim; j++)
            result.a[i][j] = k * mat.a[i][j];
    return result;
}

// Главная функция
int main() {
    cout << "=== СЦЕНАРИЙ РАБОТЫ С ВЕКТОРАМИ И МАТРИЦАМИ ===" << endl << endl;

    cout << "--- Работа с векторами ---" << endl;
    
    // Создание векторов
    vect v1(3);
    vect v2(3);
    vect v3(3);
    
    // Заполнение векторов
    v1.setComponent(0, 1.0);
    v1.setComponent(1, 2.0);
    v1.setComponent(2, 3.0);
    
    v2.setComponent(0, 4.0);
    v2.setComponent(1, 5.0);
    v2.setComponent(2, 6.0);
    
    cout << "\nИсходные векторы:" << endl;
    v1.print();
    v2.print();
    
    // Операции с векторами
    cout << "\n--- Операции с векторами ---" << endl;
    
    vect v_sum = v1 + v2;
    cout << "Результат v1 + v2: ";
    v_sum.print();
    
    vect v_diff = v1 - v2;
    cout << "Результат v1 - v2: ";
    v_diff.print();
    
    vect v_neg = -v1;
    cout << "Результат -v1: ";
    v_neg.print();
    
    double scalar = v1 * v2;
    cout << "Скалярное произведение v1 * v2 = " << scalar << endl;
    
    vect v_k = 2.5 * v1;
    cout << "Результат 2.5 * v1: ";
    v_k.print();
    
    // Оператор присваивания
    cout << "\n--- Оператор присваивания векторов ---" << endl;
    v3 = v1;
    cout << "v3 после присваивания v1: ";
    v3.print();
    
    cout << "\n--- Работа с матрицами ---" << endl;
    
    // Создание матриц
    matr m1(3);
    matr m2(3);
    matr m3(3);
    
    // Заполнение матриц
    cout << "\nЗаполнение матриц:" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            m1.setElement(i, j, i + j + 1);
            m2.setElement(i, j, (i + 1) * (j + 1));
        }
    }
    
    cout << "\nМатрица m1:" << endl;
    m1.print();
    cout << "\nМатрица m2:" << endl;
    m2.print();
    
    // Операции с матрицами
    cout << "\n--- Операции с матрицами ---" << endl;
    
    matr m_sum = m1 + m2;
    cout << "Результат m1 + m2:" << endl;
    m_sum.print();
    
    matr m_diff = m1 - m2;
    cout << "Результат m1 - m2:" << endl;
    m_diff.print();
    
    matr m_neg = -m1;
    cout << "Результат -m1:" << endl;
    m_neg.print();
    
    matr m_prod = m1 * m2;
    cout << "Результат m1 * m2:" << endl;
    m_prod.print();
    
    matr m_k = 1.5 * m1;
    cout << "Результат 1.5 * m1:" << endl;
    m_k.print();
    
    // Оператор присваивания матриц
    cout << "\n--- Оператор присваивания матриц ---" << endl;
    m3 = m1;
    cout << "m3 после присваивания m1:" << endl;
    m3.print();
    
    // Умножение матрицы на вектор
    cout << "\n--- Умножение матрицы на вектор ---" << endl;
    vect v4(3);
    v4.setComponent(0, 1.0);
    v4.setComponent(1, 0.0);
    v4.setComponent(2, 1.0);
    cout << "Вектор v4: ";
    v4.print();
    cout << "\nМатрица m1:" << endl;
    m1.print();
    
    vect mv_result = m1 * v4;
    cout << "Результат m1 * v4: ";
    mv_result.print();
    
    // Дополнительная демонстрация
    cout << "\n--- Дополнительные операции ---" << endl;
    
    vect v5 = v1 + (-v2);
    cout << "Результат v1 + (-v2): ";
    v5.print();
    
    matr m_comb = (m1 + m2) * 0.5;
    cout << "Результат (m1 + m2) * 0.5:" << endl;
    m_comb.print();
    
    // Вывод статистики
    cout << "\n=== СТАТИСТИКА ===" << endl;
    cout << "Всего создано векторов: " << vect::getCount() << endl;
    cout << "Всего создано матриц: " << matr::getCount() << endl;
    
    cout << "\n=== ЗАВЕРШЕНИЕ РАБОТЫ ===" << endl;
    
    return 0;
}