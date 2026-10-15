class Shape:
    """Базовый класс: фигура с названием и цветом."""

    def __init__(self, name, color):
        self.name = name                 # публичное поле
        self.__color = color             # приватное поле (name mangling)

    def get_color(self):
        """Геттер для приватного поля __color."""
        return self.__color

    def set_color(self, color):
        """Сеттер с простой проверкой."""
        if not isinstance(color, str) or not color:
            raise ValueError("Цвет должен быть непустой строкой")
        self.__color = color

    def area(self):
        """Метод-контракт: переопределяется в наследниках."""
        raise NotImplementedError("Метод area() должен быть переопределён")


class Circle(Shape):
    def __init__(self, color, radius):
        super().__init__("Circle", color)
        self.__radius = radius           # приватное поле наследника

    def get_radius(self):
        return self.__radius

    def area(self):
        return 3.14159 * self.__radius ** 2


class Rectangle(Shape):
    def __init__(self, color, width, height):
        super().__init__("Rectangle", color)
        self.__width = width
        self.__height = height

    def get_width(self):
        return self.__width

    def get_height(self):
        return self.__height

    def area(self):
        return self.__width * self.__height


# --- Демонстрация ---
if __name__ == "__main__":
    c = Circle("red", 3)
    r = Rectangle("blue", 4, 5)

    print(c.name, c.get_color(), round(c.area(), 2))   # Circle red 28.27
    print(r.name, r.get_color(), r.area())             # Rectangle blue 20

    # Проверка инкапсуляции: прямое обращение к __color невозможно
    try:
        print(c.__color)
    except AttributeError as e:
        print("Ошибка доступа:", e)   # 'Circle' object has no attribute '__color'
