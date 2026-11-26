from functools import reduce

numbers = [3, 8, 12, 5, 20, 7, 11, 4]

total_gen = sum(x for x in numbers if x % 2 != 0)

total_filter = sum(filter(lambda x: x % 2 != 0, numbers))

total_reduce = reduce(lambda acc, x: acc + x, filter(lambda x: x % 2 != 0, numbers), 0)

def sum_odd_recursive(lst):
    if not lst:
        return 0
    head, *tail = lst
    return (head if head % 2 != 0 else 0) + sum_odd_recursive(tail)

total_recursive = sum_odd_recursive(numbers)

print("Входной список:", numbers)
print("Сумма нечётных (sum + генератор):    ", total_gen)
print("Сумма нечётных (filter + sum):      ", total_filter)
print("Сумма нечётных (reduce + filter):   ", total_reduce)
print("Сумма нечётных (рекурсия):          ", total_recursive)

assert total_gen == total_filter == total_reduce == total_recursive == 26
print("Все четыре декларативных реализации дают одинаковый результат: 26")
