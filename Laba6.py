# ЗАДАНИЕ 1.1 Нечистая версия
total_checks = 0

def total_with_discount_impure(prices, index, discount):
    """НЕЧИСТАЯ: меняет входной список и глобальную переменную."""
    global total_checks
    total_checks += 1                 # глобальное состояние
    prices[index] -= discount         # изменение аргумента
    return sum(prices)

# ЗАДАНИЕ 1.2 Чистая версия
def total_with_discount_pure(prices, index, discount):
    """Вход: список цен, индекс товара, размер скидки.
    Выход: итоговая сумма чека; исходный список не изменяется."""
    updated = [p - discount if i == index else p
               for i, p in enumerate(prices)]
    return sum(updated)

# ЗАДАНИЕ 2
def apply_discount(prices, discount_fn):
    """Применяет discount_fn к каждой цене, возвращает НОВЫЙ список."""
    return [discount_fn(p) for p in prices]

if __name__ == "__main__":
    prices = [120, 300, 250, 90]

    print("=" * 50)
    print("ЗАДАНИЕ 1. Нечистая версия")
    print("=" * 50)
    bad_prices = [120, 300, 250, 90]
    print("До вызова:   ", bad_prices)
    print("Итог:        ", total_with_discount_impure(bad_prices, 1, 50))
    print("После вызова:", bad_prices, " <- список ИЗМЕНЁН")
    print("Глобальный счётчик вызовов:", total_checks)

    print("\n" + "=" * 50)
    print("ЗАДАНИЕ 1. Чистая версия")
    print("=" * 50)
    print("До вызова:   ", prices)
    r1 = total_with_discount_pure(prices, 1, 50)
    print("После вызова:", prices, " <- не изменился")
    r2 = total_with_discount_pure(prices, 1, 50)
    print("Итог 1:      ", r1)
    print("Итог 2:      ", r2)
    print("Детерминированность:", r1 == r2)
    print("Неизменяемость:      ", prices == [120, 300, 250, 90])

    print("\n" + "=" * 50)
    print("ЗАДАНИЕ 2. Функция высшего порядка (тип A) + lambda")
    print("=" * 50)
    print("До вызова:      ", prices)
    discounted = apply_discount(prices, lambda p: round(p * 0.9, 2))
    print("Скидка 10%:     ", discounted)
    fixed = apply_discount(prices, lambda p: max(p - 20, 0))
    print("Скидка 20 руб.: ", fixed)
    print("После вызова:   ", prices, " <- не изменился")
