#include <iostream>
#include <cmath>
#include <random>
#include <iomanip>
#include <chrono>
using namespace std;

// ========== КЛАСС ВЕКТОР (ИЗ ЛАБОРАТОРНОЙ №3) ==========
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
        for (int i = 0; i < dim; i++) v[i] = 0.0;
        cout << "Создан вектор #" << num << ", размерность=" << dim << endl;
    }

    // Конструктор копирования
    vect(const vect& other) : dim(other.dim), num(++count) {
        v = new double[dim];
        for (int i = 0; i < dim; i++) v[i] = other.v[i];
        cout << "Создана копия вектора #" << num << " из вектора #" << other.num << endl;
    }

    // Деструктор
    ~vect() {
        cout << "Удален вектор #" << num << ", размерность=" << dim << endl;
        delete[] v;
    }

    // v = v (оператор присваивания)
    vect& operator=(const vect& other) {
        if (this != &other) {
            cout << "Присваивание: вектор #" << num << " = вектор #" << other.num << endl;
            if (dim != other.dim) {
                delete[] v;
                dim = other.dim;
                v = new double[dim];
            }
            for (int i = 0; i < dim; i++) v[i] = other.v[i];
        }
        return *this;
    }

    // v + v
    vect operator+(const vect& other) const {
        if (dim != other.dim) {
            cerr << "Ошибка: размерности не совпадают!" << endl;
            return vect(1);
        }
        cout << "Операция: вектор #" << num << " + вектор #" << other.num << endl;
        vect result(dim);
        for (int i = 0; i < dim; i++) result.v[i] = v[i] + other.v[i];
        return result;
    }

    // v - v
    vect operator-(const vect& other) const {
        if (dim != other.dim) {
            cerr << "Ошибка: размерности не совпадают!" << endl;
            return vect(1);
        }
        cout << "Операция: вектор #" << num << " - вектор #" << other.num << endl;
        vect result(dim);
        for (int i = 0; i < dim; i++) result.v[i] = v[i] - other.v[i];
        return result;
    }

    // -v
    vect operator-() const {
        cout << "Операция: -вектор #" << num << endl;
        vect result(dim);
        for (int i = 0; i < dim; i++) result.v[i] = -v[i];
        return result;
    }

    // v * v (скалярное произведение)
    double operator*(const vect& other) const {
        if (dim != other.dim) {
            cerr << "Ошибка: размерности не совпадают!" << endl;
            return 0.0;
        }
        cout << "Операция: вектор #" << num << " * вектор #" << other.num << " (скалярное)" << endl;
        double result = 0;
        for (int i = 0; i < dim; i++) result += v[i] * other.v[i];
        return result;
    }

    // k * v (дружественная функция)
    friend vect operator*(double k, const vect& vec);

    // Методы доступа
    void setComponent(int index, double value) {
        if (index >= 0 && index < dim) v[index] = value;
    }
    
    double getComponent(int index) const {
        if (index >= 0 && index < dim) return v[index];
        return 0;
    }

    void print() const {
        cout << "Вектор #" << num << ": [";
        for (int i = 0; i < dim; i++) {
            cout << v[i];
            if (i < dim - 1) cout << ", ";
        }
        cout << "]" << endl;
    }

    int getDim() const { return dim; }
    int getNum() const { return num; }
    static int getCount() { return count; }
    
    // Дополнительный метод для метода Якоби: норма вектора
    double norm() const {
        double sum = 0;
        for (int i = 0; i < dim; i++) sum += v[i] * v[i];
        return sqrt(sum);
    }
    
    // Максимальная разница между компонентами двух векторов
    double maxAbsDiff(const vect& other) const {
        double maxDiff = 0;
        for (int i = 0; i < dim; i++) {
            double diff = fabs(v[i] - other.v[i]);
            if (diff > maxDiff) maxDiff = diff;
        }
        return maxDiff;
    }
};

int vect::count = 0;

// Внешняя функция k * v
vect operator*(double k, const vect& vec) {
    cout << "Операция: " << k << " * вектор #" << vec.num << endl;
    vect result(vec.dim);
    for (int i = 0; i < vec.dim; i++) result.v[i] = k * vec.v[i];
    return result;
}

// ========== КЛАСС МАТРИЦА (ИЗ ЛАБОРАТОРНОЙ №3) ==========
class matr {
private:
    int dim;
    double** a;
    int num;
    static int count;

public:
    // Конструктор по умолчанию
    matr(int d = 1) : dim(d), num(++count) {
        a = new double*[dim];
        for (int i = 0; i < dim; i++) {
            a[i] = new double[dim];
            for (int j = 0; j < dim; j++) a[i][j] = 0.0;
        }
        cout << "Создана матрица #" << num << ", размерность=" << dim << "x" << dim << endl;
    }

    // Конструктор копирования
    matr(const matr& other) : dim(other.dim), num(++count) {
        a = new double*[dim];
        for (int i = 0; i < dim; i++) {
            a[i] = new double[dim];
            for (int j = 0; j < dim; j++) a[i][j] = other.a[i][j];
        }
        cout << "Создана копия матрицы #" << num << " из матрицы #" << other.num << endl;
    }

    // Деструктор
    ~matr() {
        cout << "Удалена матрица #" << num << ", размерность=" << dim << "x" << dim << endl;
        for (int i = 0; i < dim; i++) delete[] a[i];
        delete[] a;
    }

    // m = m
    matr& operator=(const matr& other) {
        if (this != &other) {
            cout << "Присваивание: матрица #" << num << " = матрица #" << other.num << endl;
            if (dim != other.dim) {
                for (int i = 0; i < dim; i++) delete[] a[i];
                delete[] a;
                dim = other.dim;
                a = new double*[dim];
                for (int i = 0; i < dim; i++) a[i] = new double[dim];
            }
            for (int i = 0; i < dim; i++)
                for (int j = 0; j < dim; j++) a[i][j] = other.a[i][j];
        }
        return *this;
    }

    // m + m
    matr operator+(const matr& other) const {
        if (dim != other.dim) {
            cerr << "Ошибка: размерности не совпадают!" << endl;
            return matr(1);
        }
        cout << "Операция: матрица #" << num << " + матрица #" << other.num << endl;
        matr result(dim);
        for (int i = 0; i < dim; i++)
            for (int j = 0; j < dim; j++) result.a[i][j] = a[i][j] + other.a[i][j];
        return result;
    }

    // m - m
    matr operator-(const matr& other) const {
        if (dim != other.dim) {
            cerr << "Ошибка: размерности не совпадают!" << endl;
            return matr(1);
        }
        cout << "Операция: матрица #" << num << " - матрица #" << other.num << endl;
        matr result(dim);
        for (int i = 0; i < dim; i++)
            for (int j = 0; j < dim; j++) result.a[i][j] = a[i][j] - other.a[i][j];
        return result;
    }

    // -m
    matr operator-() const {
        cout << "Операция: -матрица #" << num << endl;
        matr result(dim);
        for (int i = 0; i < dim; i++)
            for (int j = 0; j < dim; j++) result.a[i][j] = -a[i][j];
        return result;
    }

    // m * m
    matr operator*(const matr& other) const {
        if (dim != other.dim) {
            cerr << "Ошибка: размерности не совпадают!" << endl;
            return matr(1);
        }
        cout << "Операция: матрица #" << num << " * матрица #" << other.num << endl;
        matr result(dim);
        for (int i = 0; i < dim; i++)
            for (int j = 0; j < dim; j++) {
                result.a[i][j] = 0;
                for (int k = 0; k < dim; k++) result.a[i][j] += a[i][k] * other.a[k][j];
            }
        return result;
    }

    // m * v
    vect operator*(const vect& vec) const {
        if (dim != vec.getDim()) {
            cerr << "Ошибка: размерности не совпадают!" << endl;
            return vect(1);
        }
        cout << "Операция: матрица #" << num << " * вектор #" << vec.getNum() << endl;
        vect result(dim);
        for (int i = 0; i < dim; i++) {
            double sum = 0;
            for (int j = 0; j < dim; j++) sum += a[i][j] * vec.getComponent(j);
            result.setComponent(i, sum);
        }
        return result;
    }

    // k * m (дружественная функция)
    friend matr operator*(double k, const matr& mat);

    // Методы доступа
    void setElement(int i, int j, double value) {
        if (i >= 0 && i < dim && j >= 0 && j < dim) a[i][j] = value;
    }

    double getElement(int i, int j) const {
        if (i >= 0 && i < dim && j >= 0 && j < dim) return a[i][j];
        return 0;
    }

    void print() const {
        cout << "Матрица #" << num << " (" << dim << "x" << dim << "):" << endl;
        for (int i = 0; i < dim; i++) {
            cout << "  [";
            for (int j = 0; j < dim; j++) {
                cout << a[i][j];
                if (j < dim - 1) cout << ", ";
            }
            cout << "]" << endl;
        }
    }

    int getDim() const { return dim; }
    int getNum() const { return num; }
    static int getCount() { return count; }
    
    // Проверка диагонального преобладания
    bool isDiagonallyDominant() const {
        for (int i = 0; i < dim; i++) {
            double diag = fabs(a[i][i]);
            double sum = 0;
            for (int j = 0; j < dim; j++) {
                if (j != i) sum += fabs(a[i][j]);
            }
            if (diag <= sum) return false;
        }
        return true;
    }
};

int matr::count = 0;

// Внешняя функция k * m
matr operator*(double k, const matr& mat) {
    cout << "Операция: " << k << " * матрица #" << mat.num << endl;
    matr result(mat.dim);
    for (int i = 0; i < mat.dim; i++)
        for (int j = 0; j < mat.dim; j++) result.a[i][j] = k * mat.a[i][j];
    return result;
}

// ========== ГЕНЕРАТОР ТЕСТОВЫХ ДАННЫХ ==========
class TestDataGenerator {
private:
    mt19937 rng;
    uniform_real_distribution<> dist;
    
public:
    TestDataGenerator() : rng(chrono::steady_clock::now().time_since_epoch().count()),
                          dist(-10.0, 10.0) {}
    
    // Генерация матрицы A: случайные элементы, диагональные увеличены в 100 раз
    matr generateMatrix(int n) {
        matr A(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) {
                    // Диагональные элементы увеличены в 100 раз
                    double val = dist(rng) * 100.0;
                    if (fabs(val) < 1.0) val = 100.0; // гарантия ненулевого диагонального
                    A.setElement(i, j, val);
                } else {
                    A.setElement(i, j, dist(rng));
                }
            }
        }
        return A;
    }
    
    // Генерация предполагаемых корней (по выбору разработчика)
    vect generateExpectedSolution(int n) {
        vect x(n);
        // Вариант: корни = 1, 2, 3, ..., n
        for (int i = 0; i < n; i++) {
            x.setComponent(i, (i + 1) * 1.0);
        }
        return x;
    }
    
    // Вычисление правой части B = A * x
    vect computeRightHandSide(const matr& A, const vect& x) {
        return A * x;
    }
};

// ========== РЕШЕНИЕ СЛАУ МЕТОДОМ ЯКОБИ ==========
class JacobiSolver {
private:
    double tolerance;
    int maxIterations;
    
public:
    JacobiSolver(double eps = 1e-10, int maxIter = 10000) 
        : tolerance(eps), maxIterations(maxIter) {}
    
    vect solve(const matr& A, const vect& B) {
        int n = A.getDim();
        
        // Начальное приближение (нулевой вектор)
        vect x(n);
        vect x_new(n);
        
        cout << "\n╔══════════════════════════════════════════════════════════════╗" << endl;
        cout << "║                    МЕТОД ЯКОБИ                               ║" << endl;
        cout << "╚══════════════════════════════════════════════════════════════╝" << endl;
        cout << "  Размер системы: " << n << " x " << n << endl;
        cout << "  Точность: " << scientific << tolerance << endl;
        cout << "  Макс. итераций: " << maxIterations << endl;
        cout << "  Диагональное преобладание: " << (A.isDiagonallyDominant() ? "ДА ✓" : "НЕТ ✗") << endl;
        
        // Проверка, что диагональные элементы не нулевые
        for (int i = 0; i < n; i++) {
            if (fabs(A.getElement(i, i)) < 1e-15) {
                cerr << "\n  ОШИБКА: Нулевой диагональный элемент A[" << i << "][" << i << "]" << endl;
                return vect(n);
            }
        }
        
        int iter = 0;
        double error = tolerance + 1;
        
        cout << "\n  Итерационный процесс:" << endl;
        cout << "  ┌─────────┬─────────────────────┐" << endl;
        cout << "  │ Итерация│     Погрешность     │" << endl;
        cout << "  ├─────────┼─────────────────────┤" << endl;
        
        while (iter < maxIterations && error > tolerance) {
            // Одна итерация метода Якоби
            for (int i = 0; i < n; i++) {
                double sum = 0;
                for (int j = 0; j < n; j++) {
                    if (j != i) {
                        sum += A.getElement(i, j) * x.getComponent(j);
                    }
                }
                double new_val = (B.getComponent(i) - sum) / A.getElement(i, i);
                x_new.setComponent(i, new_val);
            }
            
            // Вычисление ошибки
            error = x_new.maxAbsDiff(x);
            
            // Обновление решения
            x = x_new;
            iter++;
            
            // Вывод прогресса
            if (iter % 100 == 0 || iter == 1 || iter <= 10) {
                cout << "  │ " << setw(7) << iter << " │ " << scientific << setw(19) << error << " │" << endl;
            }
        }
        
        cout << "  └─────────┴─────────────────────┘" << endl;
        
        cout << "\n  ┌─────────────────────────────────────────────────────────┐" << endl;
        if (iter >= maxIterations && error > tolerance) {
            cout << "  │  ПРЕДУПРЕЖДЕНИЕ: Достигнуто максимальное число итераций!  │" << endl;
        } else {
            cout << "  │  ✓ Решение найдено за " << setw(6) << iter << " итераций                     │" << endl;
        }
        cout << "  │  Конечная погрешность: " << scientific << setw(16) << error << "   │" << endl;
        cout << "  └─────────────────────────────────────────────────────────┘" << endl;
        
        return x;
    }
    
    // Вычисление невязки ||Ax - B||
    double computeResidual(const matr& A, const vect& B, const vect& X) {
        vect residual = A * X - B;
        return residual.norm();
    }
};

// ========== ТЕСТИРОВАНИЕ ==========
void runTest(int n, JacobiSolver& solver, TestDataGenerator& generator, const string& testName) {
    cout << "\n\n";
    cout << "╔════════════════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║  " << testName << " (размер " << n << " x " << n << ")" << endl;
    cout << "╚════════════════════════════════════════════════════════════════════════════╝" << endl;
    
    // 1. Генерация матрицы A (диагональные элементы увеличены в 100 раз)
    matr A = generator.generateMatrix(n);
    
    // 2. Генерация предполагаемых корней X_expected
    vect X_expected = generator.generateExpectedSolution(n);
    
    // 3. Вычисление правой части B = A * X_expected
    vect B = generator.computeRightHandSide(A, X_expected);
    
    cout << "\n  Матрица A (диагональные элементы увеличены в 100 раз):" << endl;
    A.print();
    
    cout << "\n  Предполагаемые корни X_expected (по выбору разработчика):" << endl;
    X_expected.print();
    
    cout << "\n  Правая часть B = A * X_expected:" << endl;
    B.print();
    
    // 4. Решение СЛАУ методом Якоби
    vect X_solution = solver.solve(A, B);
    
    cout << "\n  Найденное решение X_solution:" << endl;
    X_solution.print();
    
    // 5. Проверка: невязка
    double residual = solver.computeResidual(A, B, X_solution);
    cout << "\n  Невязка ||Ax - B|| = " << scientific << residual << endl;
    
    // 6. Сравнение с ожидаемыми корнями
    cout << "\n  Сравнение с ожидаемыми корнями:" << endl;
    cout << "  ┌────┬────────────────┬────────────────┬─────────────────────┐" << endl;
    cout << "  │ i  │   Ожидаемый    │    Найденный    │       Разница       │" << endl;
    cout << "  ├────┼────────────────┼────────────────┼─────────────────────┤" << endl;
    for (int i = 0; i < n; i++) {
        double expected = X_expected.getComponent(i);
        double found = X_solution.getComponent(i);
        double diff = fabs(expected - found);
        cout << "  │ " << setw(2) << i+1 << " │ "
             << fixed << setw(14) << setprecision(6) << expected << " │ "
             << setw(14) << setprecision(6) << found << " │ "
             << scientific << setw(19) << diff << " │" << endl;
    }
    cout << "  └────┴────────────────┴────────────────┴─────────────────────┘" << endl;
}

// ========== ГЛАВНАЯ ФУНКЦИЯ ==========
int main() {
    cout << "\n";
    cout << "╔════════════════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║                    РЕШЕНИЕ СЛАУ МЕТОДОМ ЯКОБИ                              ║" << endl;
    cout << "║              Использование классов vect и matr из ЛР №3                    ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════════════════════╝" << endl;
    
    TestDataGenerator generator;
    JacobiSolver solver(1e-10, 10000);
    
    // Тестирование на разных размерностях (согласно требованию)
    int dimensions[] = {3, 5, 8, 10};
    
    for (int n : dimensions) {
        runTest(n, solver, generator, "ТЕСТ " + to_string(n) + "x" + to_string(n));
    }
    
    // Дополнительный тест: система 4x4 для наглядности
    cout << "\n\n";
    cout << "╔════════════════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║                         ДОПОЛНИТЕЛЬНЫЙ ТЕСТ                                ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════════════════════╝" << endl;
    runTest(4, solver, generator, "ДОПОЛНИТЕЛЬНЫЙ ТЕСТ");
    
    // Статистика созданных объектов
    cout << "\n\n";
    cout << "╔════════════════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║                         СТАТИСТИКА ОБЪЕКТОВ                                ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════════════════════╝" << endl;
    cout << "  Всего создано векторов: " << vect::getCount() << endl;
    cout << "  Всего создано матриц: " << matr::getCount() << endl;
    
    cout << "\n";
    cout << "╔════════════════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║                       ПРОГРАММА УСПЕШНО ЗАВЕРШЕНА                          ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════════════════════╝" << endl;
    
    return 0;
}
