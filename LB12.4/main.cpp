#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <windows.h>
#include <vector>

using namespace std;

struct Route {
    char start_point[50]{};
    char end_point[50]{};
    int route_number = 0;
};

void Create(const string& file_name);
void Print(const string& file_name);
void Find(const string& file_name);
void SortRoutes(const string& file_name);

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    string file_name;

    cout << "Введіть ім'я файлу: ";
    cin >> file_name;

    int menu_item;
    while (true) {
        cout << "\nОберіть дію:\n"
            << "1 - Ввести дані про маршрути\n"
            << "2 - Вивести інформацію про маршрути\n"
            << "3 - Пошук маршруту за номером\n"
            << "4 - Сортувати маршрути\n"
            << "0 - Завершити програму\n"
            << "Введіть: ";
        cin >> menu_item;

        switch (menu_item) {
        case 1: Create(file_name); break;
        case 2: Print(file_name); break;
        case 3: Find(file_name); break;
        case 4: SortRoutes(file_name); break;
        case 0: return 0;
        default: cout << "Некоректний вибір. Спробуйте ще раз.\n";
        }
    }
}

void Create(const string& file_name) {
    ofstream f(file_name, ios::out | ios::binary);
    if (!f.is_open()) {
        cout << "Не вдалося відкрити файл для запису!" << endl;
        return;
    }

    Route route;
    char choice;
    do {
        cout << "Введіть назву початкового пункту маршруту: ";
        cin.ignore();
        cin.getline(route.start_point, 50);
        cout << "Введіть назву кінцевого пункту маршруту: ";
        cin.getline(route.end_point, 50);
        cout << "Введіть номер маршруту: ";
        cin >> route.route_number;

        f.write(reinterpret_cast<char*>(&route), sizeof(Route));

        cout << "Бажаєте ввести ще один маршрут? (Y/N): ";
        cin >> choice;
    } while (choice == 'Y' || choice == 'y');

    f.close();
}

void Print(const string& file_name) {
    ifstream f(file_name, ios::in | ios::binary);
    if (!f.is_open()) {
        cout << "Не вдалося відкрити файл для читання!" << endl;
        return;
    }

    Route route;
    cout << "\n=======================================================\n";
    cout << "| Номер маршруту | Початковий пункт  | Кінцевий пункт |\n";
    cout << "-------------------------------------------------------\n";

    while (f.read(reinterpret_cast<char*>(&route), sizeof(Route))) {
        cout << "| " << setw(15) << route.route_number
            << "| " << setw(18) << route.start_point
            << "| " << setw(14) << route.end_point << " |\n";
    }

    cout << "=======================================================\n";
    f.close();
}

void Find(const string& file_name) {
    ifstream f(file_name, ios::in | ios::binary);
    if (!f.is_open()) {
        cout << "Не вдалося відкрити файл для читання!" << endl;
        return;
    }

    int route_number;
    cout << "Введіть номер маршруту для пошуку: ";
    cin >> route_number;

    Route route;
    bool found = false;

    while (f.read(reinterpret_cast<char*>(&route), sizeof(Route))) {
        if (route.route_number == route_number) {
            cout << "\nМаршрут знайдено:\n";
            cout << "Початковий пункт: " << route.start_point << "\n";
            cout << "Кінцевий пункт: " << route.end_point << "\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Маршрут з номером " << route_number << " не знайдено.\n";
    }

    f.close();
}

void SortRoutes(const string& file_name) {
    ifstream f(file_name, ios::in | ios::binary);
    if (!f.is_open()) {
        cout << "Не вдалося відкрити файл для читання!" << endl;
        return;
    }

    vector<Route> routes;
    Route route;

    while (f.read(reinterpret_cast<char*>(&route), sizeof(Route))) {
        routes.push_back(route);
    }
    f.close();


    sort(routes.begin(), routes.end(), [](const Route& a, const Route& b) {
        return a.route_number < b.route_number;
        });

    ofstream out_file(file_name, ios::out | ios::binary);
    if (!out_file.is_open()) {
        cout << "Не вдалося відкрити файл для запису!" << endl;
        return;
    }

    for (const auto& r : routes) {
        out_file.write(reinterpret_cast<const char*>(&r), sizeof(Route));
    }

    out_file.close();
    cout << "Маршрути відсортовано за номером.\n";
}
