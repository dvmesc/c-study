#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <stdexcept>

using namespace std;

// 函数声明
void demoBasicTypes();
void demoConditionAndLoop();
void demoFunction();
void demoArrayAndString();
void demoPointerAndReference();
void demoStruct();
void demoClass();
void demoInheritance();
void demoSTL();
void demoFileIO();
void demoException();

// 普通函数
int add(int a, int b) {
    return a + b;
}

// 带默认参数的函数
void greet(string name = "World") {
    cout << "Hello, " << name << "!" << endl;
}

// 引用传参：交换两个值
void swapValue(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// 结构体
struct Student {
    string name;
    int age;
    double score;
};

// 类
class Person {
private:
    string name;
    int age;

public:
    Person() : name("Unknown"), age(0) {}

    Person(string n, int a) : name(n), age(a) {}

    void setName(string n) {
        name = n;
    }

    void setAge(int a) {
        if (a >= 0) {
            age = a;
        }
    }

    string getName() const {
        return name;
    }

    int getAge() const {
        return age;
    }

    void show() const {
        cout << "Person => name: " << name << ", age: " << age << endl;
    }
};

// 继承
class Animal {
public:
    virtual void speak() const {
        cout << "Animal makes a sound." << endl;
    }

    virtual ~Animal() {}
};

class Dog : public Animal {
public:
    void speak() const override {
        cout << "Dog says: Woof!" << endl;
    }
};

void demoBasicTypes() {
    cout << "\n===== 1. 基本类型与输入输出 =====" << endl;

    int age = 20;
    double height = 175.5;
    char grade = 'A';
    bool isStudent = true;
    string name = "Tom";

    cout << "name = " << name << endl;
    cout << "age = " << age << endl;
    cout << "height = " << height << endl;
    cout << "grade = " << grade << endl;
    cout << "isStudent = " << isStudent << endl;

    const double PI = 3.14159;
    cout << "PI = " << PI << endl;
}

void demoConditionAndLoop() {
    cout << "\n===== 2. 条件与循环 =====" << endl;

    int num = 7;

    if (num % 2 == 0) {
        cout << num << " 是偶数" << endl;
    } else {
        cout << num << " 是奇数" << endl;
    }

    cout << "for 循环: ";
    for (int i = 1; i <= 5; i++) {
        cout << i << " ";
    }
    cout << endl;

    cout << "while 循环: ";
    int j = 1;
    while (j <= 5) {
        cout << j << " ";
        j++;
    }
    cout << endl;

    cout << "do-while 循环: ";
    int k = 1;
    do {
        cout << k << " ";
        k++;
    } while (k <= 5);
    cout << endl;
}

void demoFunction() {
    cout << "\n===== 3. 函数 =====" << endl;

    int x = 10;
    int y = 20;

    cout << "add(" << x << ", " << y << ") = " << add(x, y) << endl;

    greet();
    greet("Alice");
}

void demoArrayAndString() {
    cout << "\n===== 4. 数组与字符串 =====" << endl;

    int arr[5] = {10, 20, 30, 40, 50};
    cout << "数组内容: ";
    for (int i = 0; i < 5; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    string text = "Hello C++";
    cout << "字符串: " << text << endl;
    cout << "长度: " << text.size() << endl;
    cout << "第一个字符: " << text[0] << endl;
}

void demoPointerAndReference() {
    cout << "\n===== 5. 指针与引用 =====" << endl;

    int a = 100;
    int* p = &a;

    cout << "a = " << a << endl;
    cout << "&a = " << &a << endl;
    cout << "p = " << p << endl;
    cout << "*p = " << *p << endl;

    *p = 200;
    cout << "通过指针修改后 a = " << a << endl;

    int x = 3;
    int y = 8;
    cout << "交换前: x = " << x << ", y = " << y << endl;
    swapValue(x, y);
    cout << "交换后: x = " << x << ", y = " << y << endl;
}

void demoStruct() {
    cout << "\n===== 6. 结构体 =====" << endl;

    Student s1;
    s1.name = "Bob";
    s1.age = 18;
    s1.score = 92.5;

    cout << "Student => name: " << s1.name
         << ", age: " << s1.age
         << ", score: " << s1.score << endl;
}

void demoClass() {
    cout << "\n===== 7. 类与对象 =====" << endl;

    Person p1;
    p1.show();

    Person p2("Lucy", 22);
    p2.show();

    p1.setName("Jack");
    p1.setAge(19);
    p1.show();
}

void demoInheritance() {
    cout << "\n===== 8. 继承与多态 =====" << endl;

    Animal* animal = new Animal();
    Animal* dog = new Dog();

    animal->speak();
    dog->speak();

    delete animal;
    delete dog;
}

void demoSTL() {
    cout << "\n===== 9. STL 容器与算法 =====" << endl;

    vector<int> nums = {5, 2, 9, 1, 3};

    cout << "vector 原始数据: ";
    for (int n : nums) {
        cout << n << " ";
    }
    cout << endl;

    sort(nums.begin(), nums.end());

    cout << "排序后: ";
    for (int n : nums) {
        cout << n << " ";
    }
    cout << endl;

    map<string, int> scoreMap;
    scoreMap["Tom"] = 90;
    scoreMap["Alice"] = 95;
    scoreMap["Bob"] = 88;

    cout << "map 内容:" << endl;
    for (const auto& item : scoreMap) {
        cout << item.first << " => " << item.second << endl;
    }
}

void demoFileIO() {
    cout << "\n===== 10. 文件读写 =====" << endl;

    ofstream outFile("data.txt");
    if (outFile.is_open()) {
        outFile << "Hello File" << endl;
        outFile << "C++ File IO Example" << endl;
        outFile.close();
        cout << "已写入 data.txt" << endl;
    } else {
        cout << "文件写入失败" << endl;
    }

    ifstream inFile("data.txt");
    if (inFile.is_open()) {
        string line;
        cout << "读取文件内容:" << endl;
        while (getline(inFile, line)) {
            cout << line << endl;
        }
        inFile.close();
    } else {
        cout << "文件读取失败" << endl;
    }
}

void demoException() {
    cout << "\n===== 11. 异常处理 =====" << endl;

    try {
        int divisor = 0;
        if (divisor == 0) {
            throw runtime_error("除数不能为 0");
        }
        cout << 10 / divisor << endl;
    } catch (const exception& e) {
        cout << "捕获异常: " << e.what() << endl;
    }
}

void showMenu() {
    cout << "\n==============================" << endl;
    cout << " C++ 基础学习代码演示菜单" << endl;
    cout << "==============================" << endl;
    cout << "1. 基本类型与输入输出" << endl;
    cout << "2. 条件与循环" << endl;
    cout << "3. 函数" << endl;
    cout << "4. 数组与字符串" << endl;
    cout << "5. 指针与引用" << endl;
    cout << "6. 结构体" << endl;
    cout << "7. 类与对象" << endl;
    cout << "8. 继承与多态" << endl;
    cout << "9. STL 容器与算法" << endl;
    cout << "10. 文件读写" << endl;
    cout << "11. 异常处理" << endl;
    cout << "12. 全部运行" << endl;
    cout << "0. 退出" << endl;
    cout << "请输入选项: ";
}

int main() {
    int choice;

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                demoBasicTypes();
                break;
            case 2:
                demoConditionAndLoop();
                break;
            case 3:
                demoFunction();
                break;
            case 4:
                demoArrayAndString();
                break;
            case 5:
                demoPointerAndReference();
                break;
            case 6:
                demoStruct();
                break;
            case 7:
                demoClass();
                break;
            case 8:
                demoInheritance();
                break;
            case 9:
                demoSTL();
                break;
            case 10:
                demoFileIO();
                break;
            case 11:
                demoException();
                break;
            case 12:
                demoBasicTypes();
                demoConditionAndLoop();
                demoFunction();
                demoArrayAndString();
                demoPointerAndReference();
                demoStruct();
                demoClass();
                demoInheritance();
                demoSTL();
                demoFileIO();
                demoException();
                break;
            case 0:
                cout << "程序结束。" << endl;
                break;
            default:
                cout << "无效选项，请重新输入。" << endl;
        }
    } while (choice != 0);

    return 0;
}