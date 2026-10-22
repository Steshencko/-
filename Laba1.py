from abc import ABC, abstractmethod

class GameField:
    """Символьная матрица игрового поля."""

    EMPTY = '_'
    WALL = '0'
    COIN = '$'
    TRAP = '*'
    PLAYER = 'P'

    def __init__(self, layout: list[str]):
        self._grid = [list(row) for row in layout]
        self._rows = len(self._grid)
        self._cols = len(self._grid[0]) if self._rows else 0
        self._total_coins = sum(row.count(self.COIN) for row in self._grid)
        self._collected_coins = 0

    @property
    def rows(self) -> int:
        return self._rows

    @property
    def cols(self) -> int:
        return self._cols

    @property
    def total_coins(self) -> int:
        return self._total_coins

    @property
    def collected_coins(self) -> int:
        return self._collected_coins

    # Работа с клетками
    def in_bounds(self, r: int, c: int) -> bool:
        return 0 <= r < self._rows and 0 <= c < self._cols

    def get_cell(self, r: int, c: int) -> str:
        return self._grid[r][c]

    def set_cell(self, r: int, c: int, value: str) -> None:
        self._grid[r][c] = value

    def is_wall(self, r: int, c: int) -> bool:
        return self.get_cell(r, c) == self.WALL

    # Взаимодействие
    def interact_with_cell(self, r: int, c: int) -> str:
        """
        Обрабатывает клетку, на которую встал юнит.
        Возвращает тип события: 'coin', 'trap' или 'empty'.
        """
        cell = self.get_cell(r, c)
        if cell == self.COIN:
            self._collected_coins += 1
            self.set_cell(r, c, self.EMPTY)
            return 'coin'
        if cell == self.TRAP:
            self.set_cell(r, c, self.EMPTY)
            return 'trap'
        return 'empty'

    def all_coins_collected(self) -> bool:
        return self._collected_coins >= self._total_coins

    def render(self, player_pos=None, extra_positions=None) -> str:
        """Возвращает строку для вывода поля в консоль."""
        extra = set(extra_positions or [])
        lines = []
        lines.append('+' + '-' * self._cols + '+')
        for r in range(self._rows):
            row_str = '|'
            for c in range(self._cols):
                if player_pos == (r, c):
                    row_str += self.PLAYER
                elif (r, c) in extra:
                    row_str += 'o'
                else:
                    row_str += self._grid[r][c]
            row_str += '|'
            lines.append(row_str)
        lines.append('+' + '-' * self._cols + '+')
        return '\n'.join(lines)

#  АБСТРАКТНЫЙ ЮНИТ

class Unit(ABC):
    """Базовый абстрактный класс юнита."""

    def __init__(self, name: str, row: int, col: int,
                 max_hp: int, field: GameField):
        self.name = name
        self.row = row
        self.col = col
        self.max_hp = max_hp
        self.hp = max_hp
        self.field = field
        self.alive = True
        self.score = 0
        self.last_message = ''

    # Абстрактные методы
    @abstractmethod
    def move(self, direction: str) -> None:
        """Обработать команду перемещения."""
        ...

    @abstractmethod
    def describe(self) -> str:
        """Описание класса юнита."""
        ...

    # Общие методы
    def _try_step(self, dr: int, dc: int) -> bool:
        """Проверяет возможность шага и делает его. True — успех."""
        nr, nc = self.row + dr, self.col + dc
        if not self.field.in_bounds(nr, nc):
            self.last_message = 'Выход за пределы поля!'
            return False
        if self.field.is_wall(nr, nc):
            self.last_message = 'Там стена!'
            return False
        self.row, self.col = nr, nc
        self._process_cell()
        return True

    def _process_cell(self) -> None:
        event = self.field.interact_with_cell(self.row, self.col)
        if event == 'coin':
            self.score += 10
            self.last_message = 'Монетка! +10 очков'
        elif event == 'trap':
            self.take_damage(1)
            self.last_message = 'Ловушка! -1 жизнь'
        else:
            self.last_message = 'Пустая клетка'

    def take_damage(self, dmg: int) -> None:
        self.hp -= dmg
        if self.hp <= 0:
            self.hp = 0
            self.alive = False

    def status(self) -> str:
        return (f'{self.name}: HP {self.hp}/{self.max_hp} | '
                f'Очки: {self.score} | '
                f'Монеты: {self.field.collected_coins}/{self.field.total_coins}')



#  НАСЛЕДНИК 1 - РАЗВЕДЧИК

class Scout(Unit):
    """Разведчик: ходит на 1 клетку, имеет 5 жизней."""

    def __init__(self, row: int, col: int, field: GameField):
        super().__init__('Разведчик', row, col, max_hp=5, field=field)

    def describe(self) -> str:
        return ('Разведчик — обычный юнит. Ходит на 1 клетку. '
                '5 жизней. Получает урон от каждой ловушки.')

    def move(self, direction: str) -> None:
        deltas = {'w': (-1, 0), 's': (1, 0), 'a': (0, -1), 'd': (0, 1)}
        if direction not in deltas:
            self.last_message = 'Неизвестная команда'
            return
        dr, dc = deltas[direction]
        self._try_step(dr, dc)



#  НАСЛЕДНИК 2 - ПРЫГУН

class Jumper(Unit):
    """
    Прыгун: пытается прыгнуть на 2 клетки.
    Если промежуточная клетка — стена, он НЕ прыгает, а «упирается»:
    делает обычный шаг на 1 клетку вперёд (если там свободно),
    вставая вплотную к стене. Если и там стена/граница — стоит на месте.
    """

    def __init__(self, row: int, col: int, field: GameField):
        super().__init__('Прыгун', row, col, max_hp=3, field=field)

    def describe(self) -> str:
        return ('Прыгун — пытается прыгнуть на 2 клетки. Если на пути '
                'стена — упирается и делает шаг на 1. 3 жизни, '
                'повышенный урон от ловушек (2).')

    def move(self, direction: str) -> None:
        deltas = {'w': (-2, 0), 's': (2, 0), 'a': (0, -2), 'd': (0, 2)}
        mid_deltas = {'w': (-1, 0), 's': (1, 0), 'a': (0, -1), 'd': (0, 1)}

        if direction not in deltas:
            self.last_message = 'Неизвестная команда'
            return

        dr, dc = deltas[direction]
        mr, mc = mid_deltas[direction]

        mid_r, mid_c = self.row + mr, self.col + mc
        target_r, target_c = self.row + dr, self.col + dc

        if self.field.in_bounds(mid_r, mid_c) and self.field.is_wall(mid_r, mid_c):
            self.last_message = 'Упёрся в стену — прыжок невозможен'
            return

        if not self.field.in_bounds(target_r, target_c):
            if self._try_step(mr, mc):
                self.last_message = 'Граница поля — сделан шаг на 1'
            return

        if self.field.is_wall(target_r, target_c):
            if self._try_step(mr, mc):
                self.last_message = 'Упёрся в стену — сделан шаг на 1'
            return

        self.row, self.col = target_r, target_c
        event = self.field.interact_with_cell(self.row, self.col)
        if event == 'coin':
            self.score += 10
            self.last_message = 'Прыжок! Монетка +10 очков'
        elif event == 'trap':
            self.take_damage(2)
            self.last_message = 'Прыжок! Ловушка -2 жизни'
        else:
            self.last_message = 'Прыжок на 2 клетки'

class Game:
    DEFAULT_LAYOUT = [
        "____0____$",
        "_0__*__0__",
        "___$___*__",
        "_*_0___$__",
        "___$__0___",
        "__*____$__",
        "____0____$",
    ]

    def __init__(self, layout=None):
        self.field = GameField(layout or self.DEFAULT_LAYOUT)
        self.unit = None
        self.running = True

    # Выбор юнита
    def choose_unit(self):
        print('\n=== Выбор класса юнита ===')

        sample_scout = Scout(0, 0, self.field)
        sample_jumper = Jumper(0, 0, self.field)

        print('1) ' + sample_scout.describe())
        print('2) ' + sample_jumper.describe())

        while True:
            try:
                choice = input('Ваш выбор (1/2): ').strip()
            except EOFError:
                print('\n[!] Ввод недоступен (EOF). Завершение игры.')
                return None

            if choice == '1':
                return Scout(0, 0, self.field)
            if choice == '2':
                return Jumper(0, 0, self.field)
            print('Некорректный выбор, попробуйте снова.')

    def render(self) -> None:
        print('\n' + self.field.render((self.unit.row, self.unit.col)))
        print(self.unit.status())
        if self.unit.last_message:
            print('>> ' + self.unit.last_message)

    def handle_command(self, cmd: str) -> None:
        cmd = cmd.lower().strip()

        if cmd in ('w', 'a', 's', 'd'):
            self.unit.move(cmd)
        elif cmd == 'help':
            print('\nКоманды: w/a/s/d — движение, help — справка, quit — выход')
        elif cmd == 'quit':
            print('Выход из игры.')
            self.running = False
        else:
            print('Неизвестная команда. Введите help для справки.')

    # Проверка условий победы/поражения
    def check_end(self) -> bool:
        if not self.unit.alive:
            print('\n=== ПОРАЖЕНИЕ ===')
            print(f'{self.unit.name} потерял все жизни.')
            return True
        if self.field.all_coins_collected():
            print('\n=== ПОБЕДА ===')
            print(f'Все монеты собраны! Итоговый счёт: {self.unit.score}')
            return True
        return False

    def run(self) -> None:
        print('=' * 40)
        print('   КОНСОЛЬНАЯ ИГРА "ЮНИТ В ЛАБИРИНТЕ"')
        print('=' * 40)
        print('Символы: "_" — пусто, "0" — стена, "$" — монета, "*" — ловушка')
        print('Управление: w — вверх, s — вниз, a — влево, d — вправо')
        print('Цель: собрать все монеты, не потеряв все жизни.')

        self.unit = self.choose_unit()
        if self.unit is None:
            return

        self.render()

        while self.running:
            if self.check_end():
                break
            try:
                cmd = input('\nКоманда> ')
            except EOFError:
                print('\n[!] Ввод недоступен (EOF). Завершение игры.')
                break
            self.handle_command(cmd)
            if self.running:
                self.render()

if __name__ == '__main__':
    Game().run()
