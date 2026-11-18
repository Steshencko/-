COLORS = ['красный', 'зелёный', 'синий']

EDGES = [
    (0, 1),  # A–B
    (0, 2),  # A–C
    (1, 2),  # B–C
    (1, 3),  # B–D
    (2, 3),  # C–D
    (2, 4),  # C–E
    (3, 4),  # D–E
]

REGION_NAMES = ['A', 'B', 'C', 'D', 'E']

def is_safe(region, color, assignment):
    """Проверка ограничений (constraint check):
    цвет не должен совпадать с цветом уже назначенного соседа."""
    for (u, v) in EDGES:
        if u == region and v < len(assignment):
            if assignment[v] == color:
                return False
        if v == region and u < len(assignment):
            if assignment[u] == color:
                return False
    return True


def solve(assignment, solutions=None):
    """Рекурсивный поиск с возвратом.

    assignment — частичное решение (список цветов по индексам регионов).
    solutions  — если передан список, в него накапливаются ВСЕ решения;
                 если None — возвращается ПЕРВОЕ найденное решение.
    """

    if len(assignment) == len(REGION_NAMES):
        if solutions is not None:
            solutions.append(list(assignment))
            return None
        return list(assignment)

    region = len(assignment)

    for color in COLORS:
        if is_safe(region, color, assignment):
            assignment.append(color)
            result = solve(assignment, solutions)
            if result is not None:
                return result
            assignment.pop()

    return None

def main():
    one = solve([])
    print('Первое решение (A, B, C, D, E):')
    for name, color in zip(REGION_NAMES, one):
        print(f'  {name} = {color}')

    all_sols = []
    solve([], all_sols)
    print(f'\nВсего решений: {len(all_sols)}')
    print('Все решения (A, B, C, D, E):')
    for s in all_sols:
        print(' ', s)


if __name__ == '__main__':
    main()
