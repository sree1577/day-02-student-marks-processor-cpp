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
        cout << "❌ Unable to open the file. Please verify the file name.\n";
        return students;
    }

    string line;
    getline(file, line);

    while (getline(file, line) && students.size() < 75) {
        stringstream ss(line);
        string name, marksStr;

        getline(ss, name, ',');
        getline(ss, marksStr, ',');

        try {
            double marks = stod(marksStr);
            students.push_back({name, marks});
        } catch (...) {
            cout << "⚠ Invalid marks entry ignored for student: " << name << endl;
        }
    }

    file.close();
    return students;
}

void generateReport(const vector<Student>& students) {
    cout << "\n📊 Student Marks Report\n";
    cout << "--------------------------------------------------\n";
    cout << left << setw(18) << "Name"
         << setw(10) << "Marks"
         << "Grade\n";
    cout << "--------------------------------------------------\n";

    double totalMarks = 0;
    int passCount = 0, failCount = 0;
    int gradeCount[5] = {0};
    Student topper{"", -1};

    for (const auto& student : students) {
        char grade = calculateGrade(student.marks);
        totalMarks += student.marks;

        if (student.marks >= 40)
            passCount++;
        else
            failCount++;

        if (grade == 'A') gradeCount[0]++;
        else if (grade == 'B') gradeCount[1]++;
        else if (grade == 'C') gradeCount[2]++;
        else if (grade == 'D') gradeCount[3]++;
        else gradeCount[4]++;

        if (student.marks > topper.marks) {
            topper = student;
        }

        cout << left << setw(18) << student.name
             << setw(10) << fixed << setprecision(2)
             << student.marks
             << grade << endl;
    }

    cout << "--------------------------------------------------\n";
    cout << "Total Students Processed : " << students.size() << endl;

    if (!students.empty()) {
        cout << "Class Average Marks      : "
             << fixed << setprecision(2)
             << totalMarks / students.size() << endl;
    }

    cout << "Students Passed          : " << passCount << endl;
    cout << "Students Failed          : " << failCount << endl;

    if (topper.marks >= 0) {
        cout << "Class Topper             : "
             << topper.name << " (" << fixed << setprecision(2)
             << topper.marks << ")\n";
    }

    cout << "\nGrade Distribution\n";
    cout << "A : " << gradeCount[0] << endl;
    cout << "B : " << gradeCount[1] << endl;
    cout << "C : " << gradeCount[2] << endl;
    cout << "D : " << gradeCount[3] << endl;
    cout << "F : " << gradeCount[4] << endl;
}

int main() {
    string filename;

    cout << "Enter the CSV file name: ";
    cin >> filename;

    vector<Student> students = readCSV(filename);

    if (students.size() < 75) {
        cout << "⚠ Note: Fewer than 75 valid student records were found.\n";
    }

    generateReport(students);
    return 0;
}
