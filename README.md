# Day 2 – Student Marks Processor (C++)

A C++ program that reads student marks from a CSV file, calculates grades, and generates a summarized report for 75 students.

## Features
- CSV file input
- Grade calculation
- Input validation (invalid records are skipped)
- Clean console output
- Class average calculation
- Pass and fail count
- Class topper identification
- Grade distribution (A, B, C, D, F)

## Tech Stack
- C++
- File Handling
- STL

## Input
The program expects a CSV file with a header and student records in the following format:
Name,Marks

## Output
Student Marks Report
Name Marks Grade
Student1 78.00 B
Student2 85.00 B
Student3 92.00 A
...

Total Students Processed : 25
Class Average Marks : 81.60
Students Passed : 25
Students Failed : 0
Class Topper : Student10 (95.00)

Grade Distribution
A : 5
B : 14
C : 6
D : 0
F : 0

## How to Run
1. Compile:
   g++ student_marks_processor.cpp -o app
2. Run:
   ./app
