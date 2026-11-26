NUMBERS = [3, 8, 12, 5, 20, 7]

# ЗАДАНИЕ 1. ПРОЦЕДУРНОЕ
def procedural_odd_sum(numbers):
    """Императивный стиль"""
    total = 0
    for x in numbers:
        if x % 2 != 0:
            total += x
    return total

# ЗАДАНИЕ 1. ОБЪЕКТНО-ОРИЕНТИРОВАННОЕ
class OddSummator:
    """ООП-стиль"""

    def __init__(self, numbers):
        self.numbers = numbers

    def total(self):
        result = 0
        for x in self.numbers:
            if x % 2 != 0:
                result += x
        return result

# ЗАДАНИЕ 1. ДЕКЛАРАТИВНОЕ
def functional_odd_sum(numbers):
    """Функциональный стиль"""
    return sum(x for x in numbers if x % 2 != 0)

# ЗАДАНИЕ 2 — МУЛЬТИПАРАДИГМЕННОЕ РЕШЕНИЕ
class OddSumAnalyzer:

    def __init__(self, numbers):
        self.numbers = numbers

    def odd_sum(self):
        return sum(x for x in self.numbers if x % 2 != 0)

    def report(self):
        lines = []
        for x in self.numbers:
            parity = 'нечётное' if x % 2 != 0 else 'чётное'
            lines.append(f"{x}: {parity}")
        return lines

# ДЕМОНСТРАЦИЯ
def main():
    print("=" * 60)
    print("Тестовые данные:", NUMBERS)
    print("Ожидаемый результат: 15")
    print("=" * 60)

    # --- Задание 1 ---
    print("\nЗАДАНИЕ 1 — три решения одной задачи\n")

    r1 = procedural_odd_sum(NUMBERS)
    print("1) Процедурное (императивное):", r1)

    r2 = OddSummator(NUMBERS).total()
    print("2) Объектно-ориентированное:  ", r2)

    r3 = functional_odd_sum(NUMBERS)
    print("3) Декларативное (функц.):    ", r3)

    assert r1 == r2 == r3 == 15, "Решения дают разный результат!"
    print("\nВсе три решения дают одинаковый результат: 15")

    # --- Задание 2 ---
    print("\n" + "=" * 60)
    print("ЗАДАНИЕ 2 — мультипарадигменное решение\n")

    analyzer = OddSumAnalyzer(NUMBERS)

    print("Функциональный элемент (odd_sum):", analyzer.odd_sum())
    print("\nПроцедурный элемент (report):")
    for line in analyzer.report():
        print("  ", line)


if __name__ == "__main__":
    main()
