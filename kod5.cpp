#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Student {
    string surname;
    string name;
    int age;
};

// Функция для поиска студента по фамилии и имени
bool findStudent(const vector<Student>& students, const string& targetSurname, const string& targetName) {
    for (const auto& student : students) {
        if (student.surname == targetSurname && student.name == targetName) {
            return true; // Нашли подходящего студента
        }
    }
    return false; // Студент не найден
}

int main() {
    // Создаем вектор студентов
    vector<Student> students = {
        {"Иванов", "Иван", 20},
        {"Петров", "Пётр", 21},
        {"Сидоров", "Алексей", 19}
    };

    // Параметры поиска
    string targetSurname = "Иванов";
    string targetName = "Иван";

    // Выполняем поиск
    bool found = findStudent(students, targetSurname, targetName);

    if (found) {
        cout << "Студент найден: " << targetSurname << " " << targetName << endl;
    }
    else {
        cout << "Студент не найден." << endl;
    }

    return 0;
}
