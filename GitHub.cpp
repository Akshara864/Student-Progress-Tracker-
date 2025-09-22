#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class Student {
protected:
    int rollNo;
    string name;
    int age;
public:
    Student() : rollNo(0), name("Unknown"), age(0) {}
    Student(int r, string n, int a) : rollNo(r), name(n), age(a) {}
    Student(const Student &s) { rollNo = s.rollNo; name = s.name; age = s.age; }
    ~Student() {}
    void getData() {
        cout << "Enter Roll Number: "; cin >> rollNo;
        cin.ignore();
        cout << "Enter Name: "; getline(cin, name);
        cout << "Enter Age: "; cin >> age;
    }
    void displayData() const {
        cout << "Roll No: " << rollNo << ", Name: " << name << ", Age: " << age << endl;
    }
};

class Marks : public Student {
protected:
    int marks[6];
public:
    Marks() { for (int i = 0; i < 6; i++) marks[i] = 0; }
    void getMarks() { for (int i = 0; i < 6; i++) { cout << "Enter mark " << i+1 << ": "; cin >> marks[i]; } }
    void displayMarks() const { for (int i = 0; i < 6; i++) cout << marks[i] << " "; cout << endl; }
    float calculateAverage() const { float total = 0; for (int i = 0; i < 6; i++) total += marks[i]; return total/6.0; }
    char grade() const { float avg = calculateAverage(); if (avg >= 90) return 'A'; else if (avg >= 75) return 'B'; else if (avg >= 60) return 'C'; else if (avg >= 40) return 'D'; else return 'F'; }
    Marks& operator++() { for (int i = 0; i < 6; i++) ++marks[i]; return *this; }
    Marks operator++(int) { Marks temp = *this; for (int i = 0; i < 6; i++) marks[i]+=2; return temp; }
    friend void showCombined(const Marks&, const Marks&);
};

void showCombined(const Marks &m1, const Marks &m2) {
    cout << "Student 1: "; m1.displayMarks();
    cout << "Student 2: "; m2.displayMarks();
}

class Attendance {
protected:
    int totalClasses;
    int attendedClasses;
public:
    Attendance() : totalClasses(0), attendedClasses(0) {}
    void getAttendance() { cout << "Enter total classes: "; cin >> totalClasses; cout << "Enter attended classes: "; cin >> attendedClasses; }
    float attendancePercentage() const { if (totalClasses == 0) return 0; return (attendedClasses*100.0)/totalClasses; }
};

class Result : public Marks, public Attendance {
public:
    void displayResult() {
        displayData();
        displayMarks();
        cout << fixed << setprecision(2) << "Average Marks: " << calculateAverage() << ", Grade: " << grade() << endl;
        float perc = attendancePercentage();
        cout << "Attendance: " << perc << "% " << (perc >= 75 ? "(Eligible for Exam)" : "(Not Eligible)") << endl;
        cout << "----------------------------------------\n";
    }
};

class StudentStatic {
    string name;
    int marks;
    static int totalStudents;
    static int totalMarks;
public:
    StudentStatic(string n="", int m=0) : name(n), marks(m) { totalStudents++; totalMarks+=m; }
    void show() const { cout << "Student: " << name << ", Marks: " << marks << ", Grade: " << (marks>=85?"A":(marks>=70?"B":(marks>=50?"C":"F"))) << endl; }
    static void report() { cout << "Total Students: " << totalStudents << ", Total Marks: " << totalMarks << endl; }
};

int StudentStatic::totalStudents = 0;
int StudentStatic::totalMarks = 0;

class NestedDemo {
    int a, b;
    int sum() { return a+b; }
public:
    void input() { cout << "Enter a: "; cin >> a; cout << "Enter b: "; cin >> b; }
    void display() { cout << "Sum = " << sum() << ", Product = " << a*b << endl; }
};

int main() {
    const int MAX = 50;
    Result students[MAX];
    StudentStatic *dynStudents[MAX];
    int n=0, choice;

    do {
        cout << "\n1. Add Student\n2. Display All Students\n3. Operator Overloading Demo\n4. Static Members Demo\n5. Nested Function Demo\n6. Exit\nEnter choice: ";
        cin >> choice;
        switch(choice) {
            case 1:
                if(n<MAX) { students[n].getData(); students[n].getMarks(); students[n].getAttendance(); n++; }
                break;
            case 2:
                for(int i=0;i<n;i++) students[i].displayResult();
                break;
            case 3:
                if(n>=2) { ++students[0]; students[1]++; showCombined(students[0], students[1]); }
                break;
            case 4: {
                int sCount; cout << "Number of static students: "; cin >> sCount;
                for(int i=0;i<sCount;i++) { string nm; int mk; cout << "Name: "; cin >> nm; cout << "Marks: "; cin >> mk; dynStudents[i] = new StudentStatic(nm, mk); }
                StudentStatic::report();
                for(int i=0;i<sCount;i++) delete dynStudents[i];
                break;
            }
            case 5: { NestedDemo nDemo; nDemo.input(); nDemo.display(); break; }
            case 6: break;
        }
    } while(choice !=6);

    return 0;
}

