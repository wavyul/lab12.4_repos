#include "pch.h"
#include "CppUnitTest.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <streambuf>
#include "../LB12.4/main.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(UnitTest1)
    {
    public:

        TEST_METHOD(TestMethodFindRouteFound)
        {
            const string test_file = "test_routes.bin";
            ofstream f(test_file, ios::out | ios::binary);
            Route route1 = { "Point A", "Point B", 101 };
            Route route2 = { "Point C", "Point D", 102 };
            f.write(reinterpret_cast<char*>(&route1), sizeof(Route));
            f.write(reinterpret_cast<char*>(&route2), sizeof(Route));
            f.close();

            streambuf* original_cout = cout.rdbuf();
            ostringstream oss;
            cout.rdbuf(oss.rdbuf());

            istringstream input("101\n");
            streambuf* original_cin = cin.rdbuf(input.rdbuf());

            Find(test_file);

            cin.rdbuf(original_cin);
            cout.rdbuf(original_cout);

            string result = oss.str();
            Assert::AreEqual(string("Введіть номер маршруту для пошуку: \nМаршрут знайдено:\nПочатковий пункт: Point A\nКінцевий пункт: Point B\n"), result);

            remove(test_file.c_str());
        }

        TEST_METHOD(TestMethodFindRouteNotFound)
        {
            const string test_file = "test_routes.bin";
            ofstream f(test_file, ios::out | ios::binary);
            Route route1 = { "Point A", "Point B", 101 };
            Route route2 = { "Point C", "Point D", 102 };
            f.write(reinterpret_cast<char*>(&route1), sizeof(Route));
            f.write(reinterpret_cast<char*>(&route2), sizeof(Route));
            f.close();

            streambuf* original_cout = cout.rdbuf();
            ostringstream oss;
            cout.rdbuf(oss.rdbuf());

            istringstream input("103\n");
            streambuf* original_cin = cin.rdbuf(input.rdbuf());

            Find(test_file);

            cin.rdbuf(original_cin);
            cout.rdbuf(original_cout);

            string result = oss.str();
            Assert::AreEqual(string("Введіть номер маршруту для пошуку: Маршрут з номером 103 не знайдено.\n"), result);

            remove(test_file.c_str());
        }
    };
}
