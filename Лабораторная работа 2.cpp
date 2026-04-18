#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// Структура, содержащая поля типа string, int, double
struct DataItem {
    string name;
    int id;
    double value;
    DataItem* next;
    
    // Конструктор для удобства создания элементов
    DataItem(const string& n, int i, double v) : name(n), id(i), value(v), next(nullptr) {}
};

// Класс для работы со списком
class LinkedList {
private:
    DataItem* head;
    
public:
    // Конструктор
    LinkedList() : head(nullptr) {}
    
    // Деструктор для освобождения памяти
    ~LinkedList() {
        while (head != nullptr) {
            DataItem* temp = head;
            head = head->next;
            delete temp;
        }
    }
    
    // Добавление элемента в начало списка
    void addToBeginning(const string& name, int id, double value) {
        DataItem* newItem = new DataItem(name, id, value);
        newItem->next = head;
        head = newItem;
        cout << "Элемент \"" << name << "\" добавлен в начало списка." << endl;
    }
    
    // Добавление элемента в конец списка
    void addToEnd(const string& name, int id, double value) {
        DataItem* newItem = new DataItem(name, id, value);
        
        if (head == nullptr) {
            head = newItem;
        } else {
            DataItem* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newItem;
        }
        cout << "Элемент \"" << name << "\" добавлен в конец списка." << endl;
    }
    
    // Добавление элемента после заданного элемента (по имени)
    void addAfter(const string& afterName, const string& name, int id, double value) {
        if (head == nullptr) {
            cout << "Список пуст. Невозможно добавить после элемента \"" << afterName << "\"." << endl;
            return;
        }
        
        DataItem* current = head;
        while (current != nullptr && current->name != afterName) {
            current = current->next;
        }
        
        if (current == nullptr) {
            cout << "Элемент с именем \"" << afterName << "\" не найден." << endl;
            return;
        }
        
        DataItem* newItem = new DataItem(name, id, value);
        newItem->next = current->next;
        current->next = newItem;
        cout << "Элемент \"" << name << "\" добавлен после элемента \"" << afterName << "\"." << endl;
    }
    
    // Добавление элемента перед заданным элементом (по имени)
    void addBefore(const string& beforeName, const string& name, int id, double value) {
        if (head == nullptr) {
            cout << "Список пуст. Невозможно добавить перед элементом \"" << beforeName << "\"." << endl;
            return;
        }
        
        // Если нужно добавить перед первым элементом
        if (head->name == beforeName) {
            addToBeginning(name, id, value);
            return;
        }
        
        DataItem* current = head;
        while (current->next != nullptr && current->next->name != beforeName) {
            current = current->next;
        }
        
        if (current->next == nullptr) {
            cout << "Элемент с именем \"" << beforeName << "\" не найден." << endl;
            return;
        }
        
        DataItem* newItem = new DataItem(name, id, value);
        newItem->next = current->next;
        current->next = newItem;
        cout << "Элемент \"" << name << "\" добавлен перед элементом \"" << beforeName << "\"." << endl;
    }
    
    // Удаление из списка элемента с заданным именем
    void removeByName(const string& name) {
        if (head == nullptr) {
            cout << "Список пуст. Невозможно удалить элемент \"" << name << "\"." << endl;
            return;
        }
        
        // Если удаляем первый элемент
        if (head->name == name) {
            DataItem* temp = head;
            head = head->next;
            delete temp;
            cout << "Элемент \"" << name << "\" удален из списка." << endl;
            return;
        }
        
        DataItem* current = head;
        while (current->next != nullptr && current->next->name != name) {
            current = current->next;
        }
        
        if (current->next == nullptr) {
            cout << "Элемент с именем \"" << name << "\" не найден." << endl;
            return;
        }
        
        DataItem* temp = current->next;
        current->next = temp->next;
        delete temp;
        cout << "Элемент \"" << name << "\" удален из списка." << endl;
    }
    
    // Вывод содержания списка на экран
    void display() const {
        if (head == nullptr) {
            cout << "Список пуст." << endl;
            return;
        }
        
        cout << "\n" << string(70, '=') << endl;
        cout << left << setw(25) << "Имя" 
             << setw(10) << "ID" 
             << setw(15) << "Значение" << endl;
        cout << string(70, '-') << endl;
        
        DataItem* current = head;
        int count = 1;
        while (current != nullptr) {
            cout << left << setw(25) << current->name
                 << setw(10) << current->id
                 << setw(15) << current->value;
            
            // Отмечаем первый элемент
            if (current == head) {
                cout << " <- Голова списка";
            }
            
            cout << endl;
            current = current->next;
            count++;
        }
        cout << string(70, '=') << endl;
        cout << "Всего элементов: " << count - 1 << "\n" << endl;
    }
};

int main() {
    LinkedList list;
    int choice;
    string name, targetName;
    int id;
    double value;
    
    cout << "Программа для работы со списком структур" << endl;
    cout << "Структура содержит поля: имя (string), ID (int), значение (double)" << endl;
    
    // Сценарий работы со списком
    do {
        cout << "\n" << string(50, '-') << endl;
        cout << "МЕНЮ:" << endl;
        cout << "1. Добавить элемент в начало списка" << endl;
        cout << "2. Добавить элемент в конец списка" << endl;
        cout << "3. Добавить элемент после заданного элемента" << endl;
        cout << "4. Добавить элемент перед заданным элементом" << endl;
        cout << "5. Удалить элемент с заданным именем" << endl;
        cout << "6. Вывести содержимое списка" << endl;
        cout << "0. Выход" << endl;
        cout << "Ваш выбор: ";
        cin >> choice;
        cin.ignore(); // Очистка буфера ввода
        
        switch(choice) {
            case 1:
                cout << "Введите имя: ";
                getline(cin, name);
                cout << "Введите ID: ";
                cin >> id;
                cout << "Введите значение: ";
                cin >> value;
                cin.ignore();
                list.addToBeginning(name, id, value);
                break;
                
            case 2:
                cout << "Введите имя: ";
                getline(cin, name);
                cout << "Введите ID: ";
                cin >> id;
                cout << "Введите значение: ";
                cin >> value;
                cin.ignore();
                list.addToEnd(name, id, value);
                break;
                
            case 3:
                cout << "После какого элемента добавить? (введите имя): ";
                getline(cin, targetName);
                cout << "Введите имя нового элемента: ";
                getline(cin, name);
                cout << "Введите ID: ";
                cin >> id;
                cout << "Введите значение: ";
                cin >> value;
                cin.ignore();
                list.addAfter(targetName, name, id, value);
                break;
                
            case 4:
                cout << "Перед каким элементом добавить? (введите имя): ";
                getline(cin, targetName);
                cout << "Введите имя нового элемента: ";
                getline(cin, name);
                cout << "Введите ID: ";
                cin >> id;
                cout << "Введите значение: ";
                cin >> value;
                cin.ignore();
                list.addBefore(targetName, name, id, value);
                break;
                
            case 5:
                cout << "Введите имя элемента для удаления: ";
                getline(cin, name);
                list.removeByName(name);
                break;
                
            case 6:
                list.display();
                break;
                
            case 0:
                cout << "Программа завершена." << endl;
                break;
                
            default:
                cout << "Неверный выбор. Попробуйте снова." << endl;
        }
        
    } while (choice != 0);
    
    return 0;
}