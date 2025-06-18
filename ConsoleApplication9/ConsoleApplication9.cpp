// ConsoleApplication9.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>
using namespace std;

class Reservoir {
    char* name;
    char* type;
    double width;
    double length;
    double maxDepth;

    void copyString(char*& dest, const char* src) {
        int len = 0;
        while (src[len] != '\0') len++;
        dest = new char[len + 1];
        for (int i = 0; i <= len; i++) dest[i] = src[i];
    }

public:
    Reservoir() : name(nullptr), type(nullptr), width(0), length(0), maxDepth(0) {
        copyString(name, "Unknown");
        copyString(type, "Unknown");
        cout << "Default constructor called\n";
    }

    explicit Reservoir(const char* n, const char* t, double w, double l, double d)
        : name(nullptr), type(nullptr), width(w), length(l), maxDepth(d) {
        copyString(name, n);
        copyString(type, t);
        cout << "Parameterized constructor called\n";
    }
    Reservoir(const Reservoir& other) : name(nullptr), type(nullptr),
        width(other.width), length(other.length), maxDepth(other.maxDepth) {
        copyString(name, other.name);
        copyString(type, other.type);
        cout << "Copy constructor called\n";
    }

    ~Reservoir() {
        delete[] name;
        delete[] type;
        cout << "Destructor called\n";
    }

    double getVolume() const {
        return width * length * maxDepth;
    }

    double getArea() const {
        return width * length;
    }

    bool isSameType(const Reservoir& other) const {
        int i = 0;
        while (type[i] != '\0' && other.type[i] != '\0') {
            if (type[i] != other.type[i]) return false;
            i++;
        }
        return type[i] == other.type[i];
    }

    bool hasLargerAreaThan(const Reservoir& other) const {
        return getArea() > other.getArea();
    }

    const char* getName() const { return name; }
    const char* getType() const { return type; }
    double getWidth() const { return width; }
    double getLength() const { return length; }
    double getDepth() const { return maxDepth; }

    void setName(const char* n) {
        delete[] name;
        copyString(name, n);
    }

    void setType(const char* t) {
        delete[] type;
        copyString(type, t);
    }

    void setWidth(double w) { width = w; }
    void setLength(double l) { length = l; }
    void setDepth(double d) { maxDepth = d; }

    void display() const {
        cout << "Назва: " << name << "\n";
        cout << "Тип: " << type << "\n";
        cout << "Ширина: " << width << "\n";
        cout << "Довжина: " << length << "\n";
        cout << "Глибина: " << maxDepth << "\n";
        cout << "Площа: " << getArea() << "\n";
        cout << "Обсяг: " << getVolume() << "\n";
    }
};

void showMenu() {
    cout << "\n1. Додати водойму\n";
    cout << "2. Видалити водойму\n";
    cout << "3. Показати всі\n";
    cout << "4. Порівняти тип\n";
    cout << "5. Порівняти площу\n";
    cout << "0. Вийти\n";
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    const int MAX = 100;
    Reservoir* list[MAX];
    int count = 0;
    int choice;

    do {
        showMenu();
        cout << "Вибір: ";
        cin >> choice;

        if (choice == 1) {
            char n[100], t[100];
            double w, l, d;
            cout << "Назва: ";
            cin >> n;
            cout << "Тип: ";
            cin >> t;
            cout << "Ширина: ";
            cin >> w;
            cout << "Довжина: ";
            cin >> l;
            cout << "Глибина: ";
            cin >> d;
            list[count++] = new Reservoir(n, t, w, l, d);
        }
        else if (choice == 2) {
            if (count == 0) cout << "Список порожній\n";
            else {
                int idx;
                cout << "Індекс для видалення (0.." << count - 1 << "): ";
                cin >> idx;
                if (idx >= 0 && idx < count) {
                    delete list[idx];
                    for (int i = idx; i < count - 1; i++) {
                        list[i] = list[i + 1];
                    }
                    count--;
                }
            }
        }
        else if (choice == 3) {
            for (int i = 0; i < count; i++) {
                cout << "Водойма #" << i << ":\n";
                list[i]->display();
            }
        }
        else if (choice == 4) {
            int a, b;
            cout << "Номери 2 водойм: ";
            cin >> a >> b;
            if (a >= 0 && b >= 0 && a < count && b < count) {
                if (list[a]->isSameType(*list[b])) cout << "Один тип\n";
                else cout << "Різні типи\n";
            }
        }
        else if (choice == 5) {
            int a, b;
            cout << "Номери 2 водойм: ";
            cin >> a >> b;
            if (a >= 0 && b >= 0 && a < count && b < count) {
                if (list[a]->isSameType(*list[b])) {
                    if (list[a]->hasLargerAreaThan(*list[b]))
                        cout << "Водойма " << a << " має більшу площу\n";
                    else
                        cout << "Водойма " << b << " має більшу площу\n";
                }
                else cout << "Типи різні, не можна порівняти\n";
            }
        }

    } while (choice != 0);

    for (int i = 0; i < count; i++) {
        delete list[i];
    }

    return 0;
}