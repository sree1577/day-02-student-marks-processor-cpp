#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>

using namespace std;

struct Student {
    string name;
    double marks;
};

char calculateGrade(double marks) {
    if (marks >= 90) return 'A';
    else if (marks >= 75) return 'B';
    else if (marks >= 60) return 'C';
    else if (marks >= 40) return 'D';
    else return 'F';
}

vector<Student> readCSV(const string& filename) {
    vector<Student> students;
    ifstream file(filename);

    if (!file.is_open()) {
        cout << " Error opening file\n";
        return students;
    }

    string line;
    getline(file, line); // Skip header

    while (getline(file, line) && students.size() < 75) {
        stringstream ss(line);
        string name, marksStr;

        getline(ss, name, ',');
        getline(ss, marksStr, ',');

        try {
            double marks = stod(marksStr);
            students.push_back({name, marks});
        } catch (...) {
            cout << "⚠ Ignored invalid marks for " << name << endl;
        }
    }

    file.close();
    return students;
}

void generateReport(const vector<Student>& students) {
    cout << "\n Student Marks Report (75 Students)\n";
    cout << "--------------------------------------------\n";
    cout << left << setw(15) << "Name"
         << setw(10) << "Marks"
         << "Grade\n";
    cout << "--------------------------------------------\n";

    double total = 0;

    for (const auto& s : students) {
        char grade = calculateGrade(s.marks);
        total += s.marks;

        cout << left << setw(15) << s.name
             << setw(10) << fixed << setprecision(2)
             << s.marks << grade << endl;
    }

    cout << "--------------------------------------------\n";
    cout << "Total Students Processed: " << students.size() << endl;
    cout << "Class Average Marks: "
         << fixed << setprecision(2)
         << total / students.size() << endl;
}

int main() {
    string filename;
    cout << "Enter CSV file name: ";
    cin >> filename;

    vector<Student> students = readCSV(filename);

    if (students.size() < 75) {
        cout << " Warning: Less than 75 valid student records found\n";
    }

    generateReport(students);
    return 0;
}
