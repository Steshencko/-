#include iostream
#include cmath
#include random
#include iomanip
#include chrono
using namespace std;

 ========== КЛАСС ВЕКТОР ==========
class vect {
private
    int dim;
    double v;
    int num;
    static int count;

public
    vect(int d = 1)  dim(d), num(++count) {
        v = new double[dim];
        for (int i = 0; i  dim; i++)
            v[i] = 0.0;
    }

    vect(const vect& other)  dim(other.dim), num(++count) {
        v = new double[dim];
        for (int i = 0; i  dim; i++)
            v[i] = other.v[i];
    }

    ~vect() {
        delete[] v;
    }

    vect& operator=(const vect& other) {
        if (this != &other) {
            if (dim != other.dim) {
                delete[] v;
                dim = other.dim;
                v = new double[dim];
            }
            for (int i = 0; i  dim; i++)
                v[i] = other.v[i];
        }
        return this;
    }

    vect operator+(const vect& other) const {
        if (dim != other.dim) {
            cerr  Error dimensions do not match!  endl;
            return vect(1);
        }
        vect result(dim);
        for (int i = 0; i  dim; i++)
            result.v[i] = v[i] + other.v[i];
        return result;
    }

    vect operator-(const vect& other) const {
        if (dim != other.dim) {
            cerr  Error dimensions do not match!  endl;
            return vect(1);
        }
        vect result(dim);
        for (int i = 0; i  dim; i++)
            result.v[i] = v[i] - other.v[i];
        return result;
    }

    vect operator-() const {
        vect result(dim);
        for (int i = 0; i  dim; i++)
            result.v[i] = -v[i];
        return result;
    }

    double operator(const vect& other) const {
        if (dim != other.dim) {
            cerr  Error dimensions do not match!  endl;
            return 0.0;
        }
        double result = 0;
        for (int i = 0; i  dim; i++)
            result += v[i]  other.v[i];
        return result;
    }

    friend vect operator(double k, const vect& vec);
    friend vect operator(const vect& vec, double k);

    void setComponent(int index, double value) {
        if (index = 0 && index  dim)
            v[index] = value;
    }

    double getComponent(int index) const {
        if (index = 0 && index  dim)
            return v[index];
        return 0;
    }

    double& operator[](int index) {
        if (index  0  index = dim)
            throw out_of_range(Index out of range!);
        return v[index];
    }

    const double& operator[](int index) const {
        if (index  0  index = dim)
            throw out_of_range(Index out of range!);
        return v[index];
    }

    void print() const {
        cout  [;
        for (int i = 0; i  dim; i++) {
            cout  fixed  setprecision(6)  v[i];
            if (i  dim - 1) cout  , ;
        }
        cout  ];
    }

    int getDim() const { return dim; }
    int getNum() const { return num; }
    static int getCount() { return count; }
    
    double norm() const {
        double sum = 0;
        for (int i = 0; i  dim; i++)
            sum += v[i]  v[i];
        return sqrt(sum);
    }
    
    double maxAbsDiff(const vect& other) const {
        double maxDiff = 0;
        for (int i = 0; i  dim; i++) {
            double diff = fabs(v[i] - other.v[i]);
            if (diff  maxDiff) maxDiff = diff;
        }
        return maxDiff;
    }
};

int vectcount = 0;

vect operator(double k, const vect& vec) {
    vect result(vec.dim);
    for (int i = 0; i  vec.dim; i++)
        result.v[i] = k  vec.v[i];
    return result;
}

vect operator(const vect& vec, double k) {
    return k  vec;
}

 ========== КЛАСС МАТРИЦА ==========
class matr {
private
    int dim;
    double a;
    int num;
    static int count;

public
    matr(int d = 1)  dim(d), num(++count) {
        a = new double[dim];
        for (int i = 0; i  dim; i++) {
            a[i] = new double[dim];
            for (int j = 0; j  dim; j++)
                a[i][j] = 0.0;
        }
    }

    matr(const matr& other)  dim(other.dim), num(++count) {
        a = new double[dim];
        for (int i = 0; i  dim; i++) {
            a[i] = new double[dim];
            for (int j = 0; j  dim; j++)
                a[i][j] = other.a[i][j];
        }
    }

    ~matr() {
        for (int i = 0; i  dim; i++)
            delete[] a[i];
        delete[] a;
    }

    matr& operator=(const matr& other) {
        if (this != &other) {
            if (dim != other.dim) {
                for (int i = 0; i  dim; i++)
                    delete[] a[i];
                delete[] a;
                dim = other.dim;
                a = new double[dim];
                for (int i = 0; i  dim; i++)
                    a[i] = new double[dim];
            }
            for (int i = 0; i  dim; i++)
                for (int j = 0; j  dim; j++)
                    a[i][j] = other.a[i][j];
        }
        return this;
    }

    matr operator+(const matr& other) const {
        if (dim != other.dim) {
            cerr  Error dimensions do not match!  endl;
            return matr(1);
        }
        matr result(dim);
        for (int i = 0; i  dim; i++)
            for (int j = 0; j  dim; j++)
                result.a[i][j] = a[i][j] + other.a[i][j];
        return result;
    }

    matr operator-(const matr& other) const {
        if (dim != other.dim) {
            cerr  Error dimensions do not match!  endl;
            return matr(1);
        }
        matr result(dim);
        for (int i = 0; i  dim; i++)
            for (int j = 0; j  dim; j++)
                result.a[i][j] = a[i][j] - other.a[i][j];
        return result;
    }

    matr operator-() const {
        matr result(dim);
        for (int i = 0; i  dim; i++)
            for (int j = 0; j  dim; j++)
                result.a[i][j] = -a[i][j];
        return result;
    }

    matr operator(const matr& other) const {
        if (dim != other.dim) {
            cerr  Error dimensions do not match!  endl;
            return matr(1);
        }
        matr result(dim);
        for (int i = 0; i  dim; i++) {
            for (int j = 0; j  dim; j++) {
                result.a[i][j] = 0;
                for (int k = 0; k  dim; k++)
                    result.a[i][j] += a[i][k]  other.a[k][j];
            }
        }
        return result;
    }

    friend matr operator(double k, const matr& mat);
    friend matr operator(const matr& mat, double k);

    vect operator(const vect& vec) const {
        if (dim != vec.getDim()) {
            cerr  Error dimensions do not match!  endl;
            return vect(1);
        }
        vect result(dim);
        for (int i = 0; i  dim; i++) {
            double sum = 0;
            for (int j = 0; j  dim; j++)
                sum += a[i][j]  vec.getComponent(j);
            result.setComponent(i, sum);
        }
        return result;
    }

    void setElement(int i, int j, double value) {
        if (i = 0 && i  dim && j = 0 && j  dim)
            a[i][j] = value;
    }

    double getElement(int i, int j) const {
        if (i = 0 && i  dim && j = 0 && j  dim)
            return a[i][j];
        return 0;
    }
    
    double& operator()(int i, int j) {
        if (i  0  i = dim  j  0  j = dim)
            throw out_of_range(Indices out of range!);
        return a[i][j];
    }
    
    const double& operator()(int i, int j) const {
        if (i  0  i = dim  j  0  j = dim)
            throw out_of_range(Indices out of range!);
        return a[i][j];
    }

    void print() const {
        for (int i = 0; i  dim; i++) {
            cout    [;
            for (int j = 0; j  dim; j++) {
                cout  fixed  setprecision(4)  a[i][j];
                if (j  dim - 1) cout  , ;
            }
            cout  ]  endl;
        }
    }

    int getDim() const { return dim; }
    int getNum() const { return num; }
    static int getCount() { return count; }
    
    bool isDiagonallyDominant() const {
        for (int i = 0; i  dim; i++) {
            double diag = fabs(a[i][i]);
            double sum = 0;
            for (int j = 0; j  dim; j++) {
                if (j != i) sum += fabs(a[i][j]);
            }
            if (diag = sum) return false;
        }
        return true;
    }
};

int matrcount = 0;

matr operator(double k, const matr& mat) {
    matr result(mat.dim);
    for (int i = 0; i  mat.dim; i++)
        for (int j = 0; j  mat.dim; j++)
            result.a[i][j] = k  mat.a[i][j];
    return result;
}

matr operator(const matr& mat, double k) {
    return k  mat;
}

 ========== ГЕНЕРАТОР ТЕСТОВЫХ ДАННЫХ ==========
class TestDataGenerator {
private
    mt19937 rng;
    uniform_real_distributiondouble dist;
    
public
    TestDataGenerator()  rng(chronosteady_clocknow().time_since_epoch().count()),
                          dist(-10.0, 10.0) {}
    
    matr generateMatrix(int n) {
        matr A(n);
        
        for (int i = 0; i  n; i++) {
            for (int j = 0; j  n; j++) {
                if (i == j) {
                    A(i, j) = dist(rng)  100.0;
                    if (fabs(A(i, j))  1.0) A(i, j) = 100.0;
                } else {
                    A(i, j) = dist(rng);
                }
            }
        }
        
        return A;
    }
    
    vect generateExpectedSolution(int n) {
        vect x(n);
        for (int i = 0; i  n; i++) {
            x[i] = (i + 1)  1.0;
        }
        return x;
    }
    
    vect computeRightHandSide(const matr& A, const vect& x) {
        return A  x;
    }
    
    vect generateOnesSolution(int n) {
        vect x(n);
        for (int i = 0; i  n; i++) {
            x[i] = 1.0;
        }
        return x;
    }
};

 ========== РЕШЕНИЕ СЛАУ МЕТОДОМ ЯКОБИ ==========
class JacobiSolver {
private
    double tolerance;
    int maxIterations;
    
public
    JacobiSolver(double eps = 1e-10, int maxIter = 10000) 
         tolerance(eps), maxIterations(maxIter) {}
    
    vect solve(const matr& A, const vect& B) {
        int n = A.getDim();
        
        vect x(n);
        vect x_new(n);
        
        cout  n=== JACOBI METHOD ===  endl;
        cout  System size   n  x  n  endl;
        cout  Tolerance   tolerance  endl;
        cout  Max iterations   maxIterations  endl;
        cout  Diagonally dominant  
              (A.isDiagonallyDominant()  YES  NO)  endl;
        
        for (int i = 0; i  n; i++) {
            if (fabs(A(i, i))  1e-15) {
                cerr  ERROR Zero diagonal element A[  i  ][  i  ]  endl;
                return vect(n);
            }
        }
        
        int iter = 0;
        double error = tolerance + 1;
        
        while (iter  maxIterations && error  tolerance) {
            for (int i = 0; i  n; i++) {
                double sum = 0;
                for (int j = 0; j  n; j++) {
                    if (j != i) {
                        sum += A(i, j)  x[j];
                    }
                }
                x_new[i] = (B[i] - sum)  A(i, i);
            }
            
            error = x_new.maxAbsDiff(x);
            x = x_new;
            iter++;
            
            if (iter % 100 == 0  iter == 1) {
                cout    Iteration   iter   error =   scientific 
                      error  endl;
            }
        }
        
        cout  n--- RESULT ---  endl;
        if (iter = maxIterations && error  tolerance) {
            cout  Warning Maximum iterations reached!  endl;
        } else {
            cout  Solution found in   iter   iterations  endl;
        }
        cout  Final error   scientific  error  endl;
        
        return x;
    }
    
    double computeError(const matr& A, const vect& B, const vect& X) {
        vect residual = A  X - B;
        return residual.norm();
    }
};

 ========== ТЕСТИРОВАНИЕ ==========
void testSystem(int n, JacobiSolver& solver, TestDataGenerator& generator) {
    cout  n  string(70, '=')  endl;
    cout  TESTING SYSTEM SIZE   n  x  n  endl;
    cout  string(70, '=')  endl;
    
    matr A = generator.generateMatrix(n);
    vect x_expected = generator.generateExpectedSolution(n);
    vect B = generator.computeRightHandSide(A, x_expected);
    
    cout  nGenerated matrix A (diagonal elements multiplied by 100)  endl;
    A.print();
    
    cout  nRight-hand side B  endl;
    B.print();
    cout  endl;
    
    cout  nExpected solution x_expected  endl;
    x_expected.print();
    cout  endl;
    
    vect x_solution = solver.solve(A, B);
    
    cout  nFound solution x_solution  endl;
    x_solution.print();
    cout  endl;
    
    double error = solver.computeError(A, B, x_solution);
    cout  nResidual Ax - B   scientific  error  endl;
    
    cout  nComparison with expected solution  endl;
    cout    i  Expected  Found  Difference  endl;
    cout      string(50, '-')  endl;
    for (int i = 0; i  n; i++) {
        cout      setw(2)  i+1    
              fixed  setw(10)  setprecision(6)  x_expected[i]    
              setw(10)  setprecision(6)  x_solution[i]    
              scientific  fabs(x_expected[i] - x_solution[i])  endl;
    }
}

void testOnesSystem(int n, JacobiSolver& solver, TestDataGenerator& generator) {
    cout  n  string(70, '=')  endl;
    cout  TEST WITH SOLUTION = 1 (size   n  x  n  )  endl;
    cout  string(70, '=')  endl;
    
    matr A = generator.generateMatrix(n);
    vect x_expected = generator.generateOnesSolution(n);
    vect B = generator.computeRightHandSide(A, x_expected);
    
    cout  nMatrix A  endl;
    A.print();
    
    cout  nJacobi method solution  endl;
    vect x_solution = solver.solve(A, B);
    
    cout  nFound solution  endl;
    x_solution.print();
    cout  endl;
    
    double error = solver.computeError(A, B, x_solution);
    cout  Residual   scientific  error  endl;
}

 ========== ГЛАВНАЯ ФУНКЦИЯ ==========
int main() {
    cout  n============================================================n;
    cout       SOLVING SLAE USING JACOBI METHODn;
    cout  ============================================================n;
    
    TestDataGenerator generator;
    JacobiSolver solver(1e-10, 10000);
    
    int dimensions[] = {3, 5, 8, 10};
    
    for (int n  dimensions) {
        testSystem(n, solver, generator);
    }
    
    cout  nn============================================================n;
    cout  ADDITIONAL TEST (solution = 1)n;
    cout  ============================================================n;
    
    testOnesSystem(4, solver, generator);
    
    cout  n============================================================n;
    cout  OBJECT STATISTICSn;
    cout  ============================================================n;
    cout  Total vectors created   vectgetCount()  endl;
    cout  Total matrices created   matrgetCount()  endl;
    
    cout  n=== PROGRAM FINISHED ===n  endl;
    
    return 0;
}