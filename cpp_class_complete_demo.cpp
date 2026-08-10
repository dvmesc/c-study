#include <iostream>
#include <string>

using namespace std;

class Printable {
public:
    virtual void printInfo() const = 0;
    virtual ~Printable() {
        cout << "Printable destructor" << endl;
    }
};

class Person : public Printable {
private:
    string name;
    int age;

protected:
    string role;

public:
    static int count;

    Person() : name("Unknown"), age(0), role("Person") {
        ++count;
        cout << "Person default constructor" << endl;
    }

    Person(string name, int age) : name(name), age(age), role("Person") {
        ++count;
        cout << "Person parameter constructor" << endl;
    }

    Person(const Person& other) : name(other.name), age(other.age), role(other.role) {
        ++count;
        cout << "Person copy constructor" << endl;
    }

    virtual ~Person() {
        cout << "Person destructor: " << name << endl;
        --count;
    }

    string getName() const {
        return name;
    }

    int getAge() const {
        return age;
    }

    void setName(string name) {
        this->name = name;
    }

    void setAge(int age) {
        if (age >= 0) {
            this->age = age;
        }
    }

    void introduce() const {
        cout << "Hello, I am " << name << ", age = " << age << endl;
    }

    virtual void work() const {
        cout << name << " is doing general work." << endl;
    }

    void printInfo() const override {
        cout << "[Person] name = " << name
             << ", age = " << age
             << ", role = " << role << endl;
    }

    static void showCount() {
        cout << "Current object count = " << count << endl;
    }

    friend void showPrivateData(const Person& p);
};

int Person::count = 0;

void showPrivateData(const Person& p) {
    cout << "[friend] name = " << p.name << ", age = " << p.age << endl;
}

class Student : public Person {
private:
    string school;
    double score;

public:
    Student() : Person(), school("Unknown School"), score(0.0) {
        role = "Student";
        cout << "Student default constructor" << endl;
    }

    Student(string name, int age, string school, double score)
        : Person(name, age), school(school), score(score) {
        role = "Student";
        cout << "Student parameter constructor" << endl;
    }

    ~Student() override {
        cout << "Student destructor" << endl;
    }

    void setSchool(string school) {
        this->school = school;
    }

    string getSchool() const {
        return school;
    }

    void setScore(double score) {
        this->score = score;
    }

    double getScore() const {
        return score;
    }

    void work() const override {
        cout << getName() << " is studying at " << school << endl;
    }

    void printInfo() const override {
        cout << "[Student] name = " << getName()
             << ", age = " << getAge()
             << ", school = " << school
             << ", score = " << score
             << ", role = " << role << endl;
    }
};

class Teacher : public Person {
private:
    string subject;

public:
    Teacher(string name, int age, string subject)
        : Person(name, age), subject(subject) {
        role = "Teacher";
        cout << "Teacher parameter constructor" << endl;
    }

    ~Teacher() override {
        cout << "Teacher destructor" << endl;
    }

    void work() const override {
        cout << getName() << " is teaching " << subject << endl;
    }

    void printInfo() const override {
        cout << "[Teacher] name = " << getName()
             << ", age = " << getAge()
             << ", subject = " << subject
             << ", role = " << role << endl;
    }
};

void doWork(const Person& p) {
    p.work();
}

void showInfo(const Printable& obj) {
    obj.printInfo();
}

int main() {
    cout << "===== 1. Create Objects =====" << endl;
    Person p1;
    Person p2("Tom", 20);

    cout << endl;
    cout << "===== 2. Getter And Setter =====" << endl;
    p2.setName("Jack");
    p2.setAge(21);
    cout << p2.getName() << " " << p2.getAge() << endl;
    p2.introduce();

    cout << endl;
    cout << "===== 3. Friend Function =====" << endl;
    showPrivateData(p2);

    cout << endl;
    cout << "===== 4. Copy Constructor =====" << endl;
    Person p3 = p2;
    p3.printInfo();

    cout << endl;
    cout << "===== 5. Static Member =====" << endl;
    Person::showCount();

    cout << endl;
    cout << "===== 6. Inheritance =====" << endl;
    Student s1("Alice", 19, "PKU", 95.5);
    Teacher t1("Bob", 40, "Math");
    s1.printInfo();
    t1.printInfo();

    cout << endl;
    cout << "===== 7. Protected Member =====" << endl;
    cout << "role can be used inside child classes, but not directly outside." << endl;

    cout << endl;
    cout << "===== 8. Polymorphism =====" << endl;
    doWork(p2);
    doWork(s1);
    doWork(t1);

    cout << endl;
    cout << "===== 9. Abstract Class Interface =====" << endl;
    showInfo(p2);
    showInfo(s1);
    showInfo(t1);

    cout << endl;
    cout << "===== 10. Base Pointer To Child Object =====" << endl;
    Person* ptr = new Student("Rose", 18, "THU", 99.0);
    ptr->work();
    ptr->printInfo();
    delete ptr;

    cout << endl;
    cout << "===== 11. End =====" << endl;
    Person::showCount();
    return 0;
}
