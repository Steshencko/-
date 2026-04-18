#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

const double eps = 0.00001;

int main() {
    setlocale(LC_ALL, "Russian");
    
    int n;
    cin >> n;
    
    // Выделение памяти
    double **a = new double*[n];
    for (int i = 0; i < n; i++) a[i] = new double[n];
    double *b = new double[n];
    double *x = new double[n];
    
    // Ввод матрицы и свободных членов
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) cin >> a[i][j];
    }
    for (int i = 0; i < n; i++) cin >> b[i];
    
    // Метод Гаусса
    int sgn = 1;
    for (int i = 0; i < n; i++) {
        // Поиск ведущего элемента
        int k = i;
        for (int p = i + 1; p < n; p++) {
            if (abs(a[p][i]) > abs(a[k][i])) k = p;
        }
        
        if (abs(a[k][i]) < eps) {
            cout << "Система не имеет однозначного решения (det = 0)." << endl;
            return 0;
        }
        
        // Перестановка строк
        if (i != k) {
            swap(a[i], a[k]);
            swap(b[i], b[k]);
            sgn = -sgn;
        }
        
        // Прямой ход
        for (int j = i + 1; j < n; j++) {
            double factor = a[j][i] / a[i][i];
            for (int col = i; col < n; col++) {
                a[j][col] -= factor * a[i][col];
            }
            b[j] -= factor * b[i];
        }
    }
    
    // Обратный ход
    for (int i = n - 1; i >= 0; i--) {
        x[i] = b[i];
        for (int j = i + 1; j < n; j++) {
            x[i] -= a[i][j] * x[j];
        }
        x[i] /= a[i][i];
    }
    
    // Вывод результатов
    cout << fixed << setprecision(4);
    for (int i = 0; i < n; i++) {
        cout << "x[" << i + 1 << "] = " << x[i] << endl;
    }
    
    // Освобождение памяти
    for (int i = 0; i < n; i++) delete[] a[i];
    delete[] a;
    delete[] b;
    delete[] x;
    
    return 0;
}