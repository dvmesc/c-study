#include <array>
#include <iostream>
#include <string>

void printLine() {
    std::cout << "------------------------------------------------------------" << std::endl;
}

void printSection(const std::string& title) {
    std::cout << std::endl;
    printLine();
    std::cout << title << std::endl;
    printLine();
}

void demoOutputBasics() {
    printSection("1. Output Basics");

    std::cout << "Hello, C++!" << std::endl;
    std::cout << "This file is for learning basic syntax." << std::endl;
    std::cout << "You can chain output with << like this: "
              << 10 << ", "
              << 3.14 << ", "
              << 'A' << std::endl;

    std::cout << "Use \\n for newline.\n";
    std::cout << "Use std::endl for newline and flush." << std::endl;
}

void demoVariablesAndTypes() {
    printSection("2. Variables And Types");

    int age = 20;
    double price = 29.99;
    char grade = 'A';
    bool isReady = true;
    std::string name = "Alice";
    const double pi = 3.1415926;

    std::cout << "name = " << name << std::endl;
    std::cout << "age = " << age << std::endl;
    std::cout << "price = " << price << std::endl;
    std::cout << "grade = " << grade << std::endl;
    std::cout << "isReady = " << isReady << std::endl;
    std::cout << "pi = " << pi << std::endl;

    age = 21;
    price = 35.5;
    name = "Bob";

    std::cout << "Updated age = " << age << std::endl;
    std::cout << "Updated price = " << price << std::endl;
    std::cout << "Updated name = " << name << std::endl;
}

void demoArithmeticOperators() {
    printSection("3. Arithmetic Operators");

    int a = 17;
    int b = 5;

    std::cout << "a = " << a << ", b = " << b << std::endl;
    std::cout << "a + b = " << a + b << std::endl;
    std::cout << "a - b = " << a - b << std::endl;
    std::cout << "a * b = " << a * b << std::endl;
    std::cout << "a / b = " << a / b << std::endl;
    std::cout << "a % b = " << a % b << std::endl;

    double x = 17.0;
    double y = 5.0;
    std::cout << "x / y = " << x / y << std::endl;
}

void demoComparisonAndLogicalOperators() {
    printSection("4. Comparison And Logical Operators");

    int score = 86;
    int limit = 90;

    std::cout << "score == limit : " << (score == limit) << std::endl;
    std::cout << "score != limit : " << (score != limit) << std::endl;
    std::cout << "score > limit  : " << (score > limit) << std::endl;
    std::cout << "score < limit  : " << (score < limit) << std::endl;
    std::cout << "score >= 60 && score <= 100 : "
              << (score >= 60 && score <= 100) << std::endl;
    std::cout << "score < 60 || score > 100   : "
              << (score < 60 || score > 100) << std::endl;
    std::cout << "!false : " << (!false) << std::endl;
}

void demoIfElse() {
    printSection("5. If Else");

    int number = -7;

    if (number > 0) {
        std::cout << number << " is positive" << std::endl;
    } else if (number < 0) {
        std::cout << number << " is negative" << std::endl;
    } else {
        std::cout << number << " is zero" << std::endl;
    }

    int score = 92;
    if (score >= 90) {
        std::cout << "grade = A" << std::endl;
    } else if (score >= 80) {
        std::cout << "grade = B" << std::endl;
    } else if (score >= 70) {
        std::cout << "grade = C" << std::endl;
    } else {
        std::cout << "grade = D" << std::endl;
    }
}

void demoSwitch() {
    printSection("6. Switch");

    int day = 3;

    switch (day) {
        case 1:
            std::cout << "Monday" << std::endl;
            break;
        case 2:
            std::cout << "Tuesday" << std::endl;
            break;
        case 3:
            std::cout << "Wednesday" << std::endl;
            break;
        case 4:
            std::cout << "Thursday" << std::endl;
            break;
        case 5:
            std::cout << "Friday" << std::endl;
            break;
        default:
            std::cout << "Weekend or invalid day" << std::endl;
            break;
    }
}

void demoForLoop() {
    printSection("7. For Loop");

    for (int i = 1; i <= 5; ++i) {
        std::cout << "i = " << i << std::endl;
    }

    int sum = 0;
    for (int i = 1; i <= 100; ++i) {
        sum += i;
    }
    std::cout << "sum 1..100 = " << sum << std::endl;
}

void demoWhileLoop() {
    printSection("8. While Loop");

    int count = 3;
    while (count > 0) {
        std::cout << "count = " << count << std::endl;
        --count;
    }

    int value = 1;
    while (value <= 16) {
        std::cout << "value = " << value << std::endl;
        value *= 2;
    }
}

int add(int a, int b) {
    return a + b;
}

double add(double a, double b) {
    return a + b;
}

int square(int value) {
    return value * value;
}

bool isEven(int value) {
    return value % 2 == 0;
}

int maxOfThree(int a, int b, int c) {
    int result = a;
    if (b > result) {
        result = b;
    }
    if (c > result) {
        result = c;
    }
    return result;
}

int factorial(int n) {
    int result = 1;
    for (int i = 1; i <= n; ++i) {
        result *= i;
    }
    return result;
}

void greet(const std::string& name = "World") {
    std::cout << "Hello, " << name << "!" << std::endl;
}

void trySwapByValue(int a, int b) {
    int temp = a;
    a = b;
    b = temp;
    std::cout << "Inside trySwapByValue: a = " << a << ", b = " << b << std::endl;
}

void swapByReference(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

void printValueAndAddress(const std::string& label, int& value) {
    std::cout << label << " value = " << value
              << ", address = " << &value << std::endl;
}

void demoFunctionsAndParameters() {
    printSection("9. Functions And Parameters");

    std::cout << "add(3, 5) = " << add(3, 5) << std::endl;
    std::cout << "add(1.5, 2.25) = " << add(1.5, 2.25) << std::endl;
    std::cout << "square(6) = " << square(6) << std::endl;
    std::cout << "isEven(10) = " << isEven(10) << std::endl;
    std::cout << "maxOfThree(7, 11, 9) = " << maxOfThree(7, 11, 9) << std::endl;
    std::cout << "factorial(5) = " << factorial(5) << std::endl;

    greet();
    greet("Tom");

    int x = 10;
    int y = 20;

    std::cout << "Before trySwapByValue: x = " << x << ", y = " << y << std::endl;
    trySwapByValue(x, y);
    std::cout << "After trySwapByValue : x = " << x << ", y = " << y << std::endl;

    std::cout << "Before swapByReference: x = " << x << ", y = " << y << std::endl;
    swapByReference(x, y);
    std::cout << "After swapByReference : x = " << x << ", y = " << y << std::endl;

    printValueAndAddress("x", x);
    printValueAndAddress("y", y);
}

void demoArrays() {
    printSection("10. Arrays");

    int scores[5] = {90, 85, 88, 92, 79};
    int total = 0;

    for (int i = 0; i < 5; ++i) {
        std::cout << "scores[" << i << "] = " << scores[i] << std::endl;
        total += scores[i];
    }

    std::cout << "total = " << total << std::endl;
    std::cout << "average = " << static_cast<double>(total) / 5 << std::endl;

    std::array<int, 4> ids = {101, 102, 103, 104};
    for (std::size_t i = 0; i < ids.size(); ++i) {
        std::cout << "ids[" << i << "] = " << ids[i] << std::endl;
    }
}

void demoStringBasics() {
    printSection("11. String Basics");

    std::string firstName = "Alice";
    std::string lastName = "Smith";
    std::string fullName = firstName + " " + lastName;

    std::cout << "fullName = " << fullName << std::endl;
    std::cout << "length = " << fullName.size() << std::endl;
    std::cout << "first character = " << fullName[0] << std::endl;

    fullName += " Jr.";
    std::cout << "after += : " << fullName << std::endl;

    if (fullName.find("Smith") != std::string::npos) {
        std::cout << "Found Smith in fullName" << std::endl;
    }

    std::string part = fullName.substr(0, 5);
    std::cout << "substr(0, 5) = " << part << std::endl;
}

struct Student {
    std::string name;
    int age;
    double score;
};

void printStudent(const Student& student) {
    std::cout << "Student { name = " << student.name
              << ", age = " << student.age
              << ", score = " << student.score
              << " }" << std::endl;
}

void demoStructBasics() {
    printSection("12. Struct Basics");

    Student s1 = {"Lily", 19, 95.5};
    Student s2;
    s2.name = "Mark";
    s2.age = 20;
    s2.score = 88.0;

    printStudent(s1);
    printStudent(s2);
}

class Person {
private:
    std::string name;
    int age;

protected:
    std::string tag;

public:
    Person() : name("Unknown"), age(0), tag("person") {}

    Person(const std::string& nameValue, int ageValue)
        : name(nameValue), age(ageValue), tag("person") {}

    std::string getName() const {
        return name;
    }

    int getAge() const {
        return age;
    }

    void setName(const std::string& nameValue) {
        name = nameValue;
    }

    void setAge(int ageValue) {
        if (ageValue >= 0) {
            age = ageValue;
        }
    }

    void celebrateBirthday() {
        ++age;
    }

    virtual void introduce() const {
        std::cout << "I am " << name << ", age " << age << std::endl;
    }

    virtual ~Person() = default;
};

class StudentUser : public Person {
private:
    std::string major;

public:
    StudentUser(const std::string& nameValue, int ageValue, const std::string& majorValue)
        : Person(nameValue, ageValue), major(majorValue) {
        tag = "student";
    }

    std::string getMajor() const {
        return major;
    }

    void setMajor(const std::string& majorValue) {
        major = majorValue;
    }

    void introduce() const override {
        std::cout << "I am " << getName()
                  << ", age " << getAge()
                  << ", major " << major
                  << ", tag " << tag
                  << std::endl;
    }
};

void demoClassBasics() {
    printSection("13. Class Basics");

    Person p1;
    Person p2("Tom", 18);

    p1.introduce();
    p2.introduce();

    p2.setName("Jack");
    p2.setAge(19);
    p2.celebrateBirthday();
    p2.introduce();

    StudentUser s("Rose", 21, "Computer Science");
    s.introduce();
    s.setMajor("Software Engineering");
    s.introduce();
}

class Animal {
public:
    virtual void speak() const {
        std::cout << "Animal makes a sound" << std::endl;
    }

    virtual ~Animal() = default;
};

class Dog : public Animal {
public:
    void speak() const override {
        std::cout << "Dog says: woof" << std::endl;
    }
};

class Cat : public Animal {
public:
    void speak() const override {
        std::cout << "Cat says: meow" << std::endl;
    }
};

void letAnimalSpeak(const Animal& animal) {
    animal.speak();
}

void demoVirtualFunction() {
    printSection("14. Inheritance And Virtual Function");

    Animal animal;
    Dog dog;
    Cat cat;

    animal.speak();
    dog.speak();
    cat.speak();

    letAnimalSpeak(animal);
    letAnimalSpeak(dog);
    letAnimalSpeak(cat);
}

void demoPointerBasics() {
    printSection("15. Pointer Basics");

    int number = 42;
    int* ptr = &number;

    std::cout << "number = " << number << std::endl;
    std::cout << "&number = " << &number << std::endl;
    std::cout << "ptr = " << ptr << std::endl;
    std::cout << "*ptr = " << *ptr << std::endl;

    *ptr = 99;
    std::cout << "After *ptr = 99, number = " << number << std::endl;
}

void demoReferenceBasics() {
    printSection("16. Reference Basics");

    int value = 50;
    int& ref = value;

    std::cout << "value = " << value << std::endl;
    std::cout << "ref = " << ref << std::endl;

    ref = 77;

    std::cout << "After ref = 77, value = " << value << std::endl;
    std::cout << "After ref = 77, ref = " << ref << std::endl;
}

void demoBreakAndContinue() {
    printSection("17. Break And Continue");

    for (int i = 1; i <= 10; ++i) {
        if (i == 3) {
            continue;
        }
        if (i == 8) {
            break;
        }
        std::cout << "i = " << i << std::endl;
    }
}

void demoTypeCasting() {
    printSection("18. Type Casting");

    int total = 7;
    int count = 2;

    double avg1 = total / count;
    double avg2 = static_cast<double>(total) / count;

    std::cout << "avg1 = " << avg1 << std::endl;
    std::cout << "avg2 = " << avg2 << std::endl;
}

void demoNestedLoop() {
    printSection("19. Nested Loop");

    for (int row = 1; row <= 3; ++row) {
        for (int col = 1; col <= 4; ++col) {
            std::cout << "(" << row << "," << col << ") ";
        }
        std::cout << std::endl;
    }
}

void printStudySuggestions() {
    printSection("20. Suggested Study Order");

    std::cout << "1. Read sections 1 to 8 for syntax basics." << std::endl;
    std::cout << "2. Focus on sections 9, 15, 16 for value/reference/pointer." << std::endl;
    std::cout << "3. Focus on sections 12 to 14 for struct, class, inheritance." << std::endl;
    std::cout << "4. Try rewriting each demo by yourself." << std::endl;
    std::cout << "5. Delete one section and implement it again without looking." << std::endl;
}

int main() {
    demoOutputBasics();
    demoVariablesAndTypes();
    demoArithmeticOperators();
    demoComparisonAndLogicalOperators();
    demoIfElse();
    demoSwitch();
    demoForLoop();
    demoWhileLoop();
    demoFunctionsAndParameters();
    demoArrays();
    demoStringBasics();
    demoStructBasics();
    demoClassBasics();
    demoVirtualFunction();
    demoPointerBasics();
    demoReferenceBasics();
    demoBreakAndContinue();
    demoTypeCasting();
    demoNestedLoop();
    printStudySuggestions();

    printSection("21. End");
    std::cout << "Run this file, read output, then comment out sections one by one." << std::endl;
    return 0;
}
