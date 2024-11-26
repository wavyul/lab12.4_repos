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

    cout << "������ ��'� �����: ";
    cin >> file_name;

    int menu_item;
    while (true) {
        cout << "\n������ ��:\n"
            << "1 - ������ ��� ��� ��������\n"
            << "2 - ������� ���������� ��� ��������\n"
            << "3 - ����� �������� �� �������\n"
            << "4 - ��������� ��������\n"
            << "0 - ��������� ��������\n"
            << "������: ";
        cin >> menu_item;

        switch (menu_item) {
        case 1: Create(file_name); break;
        case 2: Print(file_name); break;
        case 3: Find(file_name); break;
        case 4: SortRoutes(file_name); break;
        case 0: return 0;
        default: cout << "����������� ����. ��������� �� ���.\n";
        }
    }
}

void Create(const string& file_name) {
    ofstream f(file_name, ios::out | ios::binary);
    if (!f.is_open()) {
        cout << "�� ������� ������� ���� ��� ������!" << endl;
        return;
    }

    Route route;
    char choice;
    do {
        cout << "������ ����� ����������� ������ ��������: ";
        cin.ignore();
        cin.getline(route.start_point, 50);
        cout << "������ ����� �������� ������ ��������: ";
        cin.getline(route.end_point, 50);
        cout << "������ ����� ��������: ";
        cin >> route.route_number;

        f.write(reinterpret_cast<char*>(&route), sizeof(Route));

        cout << "������ ������ �� ���� �������? (Y/N): ";
        cin >> choice;
    } while (choice == 'Y' || choice == 'y');

    f.close();
}

void Print(const string& file_name) {
    ifstream f(file_name, ios::in | ios::binary);
    if (!f.is_open()) {
        cout << "�� ������� ������� ���� ��� �������!" << endl;
        return;
    }

    Route route;
    cout << "\n=======================================================\n";
    cout << "| ����� �������� | ���������� �����  | ʳ������ ����� |\n";
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
        cout << "�� ������� ������� ���� ��� �������!" << endl;
        return;
    }

    int route_number;
    cout << "������ ����� �������� ��� ������: ";
    cin >> route_number;

    Route route;
    bool found = false;

    while (f.read(reinterpret_cast<char*>(&route), sizeof(Route))) {
        if (route.route_number == route_number) {
            cout << "\n������� ��������:\n";
            cout << "���������� �����: " << route.start_point << "\n";
            cout << "ʳ������ �����: " << route.end_point << "\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "������� � ������� " << route_number << " �� ��������.\n";
    }

    f.close();
}

void SortRoutes(const string& file_name) {
    ifstream f(file_name, ios::in | ios::binary);
    if (!f.is_open()) {
        cout << "�� ������� ������� ���� ��� �������!" << endl;
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
        cout << "�� ������� ������� ���� ��� ������!" << endl;
        return;
    }

    for (const auto& r : routes) {
        out_file.write(reinterpret_cast<const char*>(&r), sizeof(Route));
    }

    out_file.close();
    cout << "�������� ����������� �� �������.\n";
}
