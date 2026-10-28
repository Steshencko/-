import sys
import time

def factorial(n):
    if n == 0:
        return 1
    return n * factorial(n - 1)

def factorial_tail(n, acc=1):
    if n == 0:
        return acc
    return factorial_tail(n - 1, acc * n)

def check_equal_results():
    print("Проверка совпадения результатов:")
    for n in [0, 1, 2, 3, 5, 7, 10, 20]:
        r1 = factorial(n)
        r2 = factorial_tail(n)
        print(f"n={n}: {r1} == {r2} -> {r1 == r2}")
    print()

def find_max_depth(func, limit):
    sys.setrecursionlimit(limit)
    low, high = 0, limit + 100
    max_ok = 0
    while low <= high:
        mid = (low + high) // 2
        try:
            func(mid)
            max_ok = mid
            low = mid + 1
        except RecursionError:
            high = mid - 1
    return max_ok

def depth_comparison():
    print("Сравнение максимальной глубины:")
    for limit in (1000, 3000):
        plain = find_max_depth(factorial, limit)
        tail = find_max_depth(factorial_tail, limit)
        print(f"limit={limit}: обычная={plain}, хвостовая={tail}, разница={abs(plain-tail)}")
    print()

def time_comparison():
    print("Сравнение времени:")
    sys.setrecursionlimit(5000)
    n, repeats = 900, 5
    factorial(100)
    factorial_tail(100)
    
    t0 = time.perf_counter()
    for _ in range(repeats): factorial(n)
    t1 = time.perf_counter()
    
    t2 = time.perf_counter()
    for _ in range(repeats): factorial_tail(n)
    t3 = time.perf_counter()
    
    print(f"n={n}: обычная={((t1-t0)/repeats):.6f}с, хвостовая={((t3-t2)/repeats):.6f}с\n")

def show_recursion_error():
    print("Демонстрация RecursionError:")
    sys.setrecursionlimit(1000)
    for name, fn in (("factorial", factorial), ("factorial_tail", factorial_tail)):
        try:
            fn(1200)
            print(f"{name}(1200): OK")
        except RecursionError:
            print(f"{name}(1200): RecursionError")

if __name__ == "__main__":
    check_equal_results()
    depth_comparison()
    time_comparison()
    show_recursion_error()
