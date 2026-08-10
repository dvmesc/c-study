#include <iostream>
#include <string>

using namespace std;

// 打印一条分隔线。
void printLine() {
    cout << "============================================================" << endl;
}

// 打印带标题的小节头。
void printSection(const string& title) {
    cout << endl;
    printLine();
    cout << title << endl;
    printLine();
}

// 用值传递尝试交换两个数。
void swapByValue(int a, int b) {
    int temp = a;
    a = b;
    b = temp;
    cout << "[swapByValue] a = " << a << ", b = " << b << endl;
}

// 用引用传递交换两个数。
void swapByReference(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// 通过指针给目标值加十。
void addTen(int* ptr) {
    if (ptr != nullptr) {
        *ptr += 10;
    }
}

// 输出指针地址和指向的值。
void printPointerInfo(const string& label, int* ptr) {
    cout << label << " address = " << ptr;
    if (ptr != nullptr) {
        cout << ", value = " << *ptr;
    }
    cout << endl;
}

// 演示引用的基础行为。
void demoReferenceBasics() {
    printSection("1. Reference Basics");

    int value = 25;
    int& ref = value;

    cout << "value = " << value << endl;
    cout << "ref = " << ref << endl;
    cout << "&value = " << &value << endl;
    cout << "&ref = " << &ref << endl;

    ref = 40;

    cout << "After ref = 40" << endl;
    cout << "value = " << value << endl;
    cout << "ref = " << ref << endl;
}

// 对比值传递和引用传递。
void demoValueVsReference() {
    printSection("2. Value And Reference Parameter");

    int x = 10;
    int y = 20;

    cout << "Before swapByValue: x = " << x << ", y = " << y << endl;
    swapByValue(x, y);
    cout << "After swapByValue : x = " << x << ", y = " << y << endl;

    cout << "Before swapByReference: x = " << x << ", y = " << y << endl;
    swapByReference(x, y);
    cout << "After swapByReference : x = " << x << ", y = " << y << endl;
}

// 演示指针定义和解引用。
void demoPointerBasics() {
    printSection("3. Pointer Basics");

    int number = 88;
    int* ptr = &number;

    printPointerInfo("ptr", ptr);
    *ptr = 99;

    cout << "After *ptr = 99, number = " << number << endl;

    int* nullPtr = nullptr;
    printPointerInfo("nullPtr", nullPtr);
}

// 演示把地址传进函数。
void demoPointerParameter() {
    printSection("4. Pointer Parameter");

    int score = 70;
    cout << "Before addTen, score = " << score << endl;
    addTen(&score);
    cout << "After addTen , score = " << score << endl;
}

// 演示 const 引用如何绑定同一个对象。
void demoConstReference() {
    printSection("5. Const Reference");

    string name = "Reference Demo";
    const string& ref = name;

    cout << "name = " << name << endl;
    cout << "ref = " << ref << endl;

    name = "Updated Name";

    cout << "After changing name" << endl;
    cout << "name = " << name << endl;
    cout << "ref = " << ref << endl;
}

// 在堆上申请一个 int 并返回指针。
int* createDynamicInt(int value) {
    int* ptr = new int(value);
    return ptr;
}

// 演示单个对象的 new 和 delete。
void demoDynamicSingleObject() {
    printSection("6. Dynamic Single Object");

    int* ptr = createDynamicInt(123);
    cout << "*ptr = " << *ptr << endl;
    cout << "ptr address = " << ptr << endl;

    delete ptr;
    ptr = nullptr;

    cout << "After delete, ptr = " << ptr << endl;
}

// 给动态数组填充示例数据。
void fillDynamicArray(int* arr, int size) {
    for (int i = 0; i < size; ++i) {
        arr[i] = (i + 1) * 10;
    }
}

// 输出动态数组中的所有元素。
void printDynamicArray(const int* arr, int size, const string& label) {
    cout << label << ": ";
    for (int i = 0; i < size; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// 演示 new[] 和 delete[]。
void demoDynamicArray() {
    printSection("7. Dynamic Array With new[] / delete[]");

    int size = 5;
    int* arr = new int[size];

    fillDynamicArray(arr, size);
    printDynamicArray(arr, size, "dynamic array");

    delete[] arr;
    arr = nullptr;

    cout << "After delete[], arr = " << arr << endl;
}

class NumberBox {
private:
    int value;

public:
    // 创建一个默认值对象。
    NumberBox() : value(0) {
        cout << "NumberBox default constructor" << endl;
    }

    // 创建一个带初始值的对象。
    NumberBox(int value) : value(value) {
        cout << "NumberBox parameter constructor" << endl;
    }

    // 读取当前保存的值。
    int getValue() const {
        return value;
    }

    // 修改当前保存的值。
    void setValue(int value) {
        this->value = value;
    }

    // 输出当前值。
    void print() const {
        cout << "NumberBox value = " << value << endl;
    }
};

// 演示通过对象指针访问成员。
void demoObjectPointer() {
    printSection("8. Object Pointer");

    NumberBox box(55);
    NumberBox* ptr = &box;

    ptr->print();
    ptr->setValue(99);
    ptr->print();
}

class IntBuffer {
private:
    int size;
    int* data;

public:
    // 构造一个空缓冲区。
    IntBuffer() : size(0), data(nullptr) {
        cout << "IntBuffer default constructor" << endl;
    }

    // 按指定大小申请缓冲区。
    IntBuffer(int size) : size(size), data(new int[size]) {
        cout << "IntBuffer parameter constructor" << endl;
        for (int i = 0; i < size; ++i) {
            data[i] = 0;
        }
    }

    // 深拷贝另一个缓冲区。
    IntBuffer(const IntBuffer& other) : size(other.size), data(new int[other.size]) {
        cout << "IntBuffer copy constructor" << endl;
        for (int i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }

    // 通过赋值进行深拷贝。
    IntBuffer& operator=(const IntBuffer& other) {
        cout << "IntBuffer copy assignment" << endl;

        if (this == &other) {
            return *this;
        }

        delete[] data;

        size = other.size;
        data = new int[size];

        for (int i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }

        return *this;
    }

    // 释放自己持有的内存。
    ~IntBuffer() {
        cout << "IntBuffer destructor" << endl;
        delete[] data;
    }

    // 返回缓冲区长度。
    int getSize() const {
        return size;
    }

    // 在合法下标写入数据。
    void setAt(int index, int value) {
        if (index >= 0 && index < size) {
            data[index] = value;
        }
    }

    // 读取合法下标处的数据。
    int getAt(int index) const {
        if (index >= 0 && index < size) {
            return data[index];
        }
        return -1;
    }

    // 输出缓冲区中的所有元素。
    void print(const string& label) const {
        cout << label << ": ";
        for (int i = 0; i < size; ++i) {
            cout << data[i] << " ";
        }
        cout << endl;
    }
};

// 用简单序列填充 IntBuffer。
void fillBuffer(IntBuffer& buffer, int startValue) {
    for (int i = 0; i < buffer.getSize(); ++i) {
        buffer.setAt(i, startValue + i * 3);
    }
}

// 演示为什么深拷贝很重要。
void demoDeepCopy() {
    printSection("9. Deep Copy And Resource Ownership");

    IntBuffer a(5);
    fillBuffer(a, 10);
    a.print("buffer a");

    IntBuffer b = a;
    b.setAt(0, 999);

    a.print("buffer a after copy");
    b.print("buffer b after modify");

    IntBuffer c(3);
    c = a;
    c.setAt(1, 555);

    a.print("buffer a after assignment");
    c.print("buffer c after modify");
}

class StudentRecord {
private:
    string name;
    int* scores;
    int scoreCount;

public:
    // 创建一个带动态成绩数组的记录。
    StudentRecord(const string& name, int scoreCount)
        : name(name), scores(new int[scoreCount]), scoreCount(scoreCount) {
        for (int i = 0; i < scoreCount; ++i) {
            scores[i] = 0;
        }
    }

    // 深拷贝另一个学生记录。
    StudentRecord(const StudentRecord& other)
        : name(other.name), scores(new int[other.scoreCount]), scoreCount(other.scoreCount) {
        for (int i = 0; i < scoreCount; ++i) {
            scores[i] = other.scores[i];
        }
    }

    // 通过赋值进行深拷贝。
    StudentRecord& operator=(const StudentRecord& other) {
        if (this == &other) {
            return *this;
        }

        delete[] scores;

        name = other.name;
        scoreCount = other.scoreCount;
        scores = new int[scoreCount];

        for (int i = 0; i < scoreCount; ++i) {
            scores[i] = other.scores[i];
        }

        return *this;
    }

    // 释放成绩数组。
    ~StudentRecord() {
        delete[] scores;
    }

    // 按下标修改一项成绩。
    void setScore(int index, int score) {
        if (index >= 0 && index < scoreCount) {
            scores[index] = score;
        }
    }

    // 计算平均分。
    double average() const {
        int sum = 0;
        for (int i = 0; i < scoreCount; ++i) {
            sum += scores[i];
        }
        return scoreCount == 0 ? 0.0 : static_cast<double>(sum) / scoreCount;
    }

    // 输出记录和平均分。
    void print() const {
        cout << "StudentRecord { name = " << name << ", scores = ";
        for (int i = 0; i < scoreCount; ++i) {
            cout << scores[i] << " ";
        }
        cout << ", avg = " << average() << " }" << endl;
    }
};

// 演示持有动态内存的类。
void demoClassWithDynamicMemory() {
    printSection("10. Class With Dynamic Memory");

    StudentRecord s1("Alice", 4);
    s1.setScore(0, 90);
    s1.setScore(1, 88);
    s1.setScore(2, 92);
    s1.setScore(3, 95);
    s1.print();

    StudentRecord s2 = s1;
    s2.setScore(0, 60);

    s1.print();
    s2.print();
}

// 运行第二阶段全部示例。
int main() {
    demoReferenceBasics();
    demoValueVsReference();
    demoPointerBasics();
    demoPointerParameter();
    demoConstReference();
    demoDynamicSingleObject();
    demoDynamicArray();
    demoObjectPointer();
    demoDeepCopy();
    demoClassWithDynamicMemory();

    printSection("11. Study Advice");
    cout << "1. Delete one demo and rewrite it by yourself." << endl;
    cout << "2. Change pointer code and observe address/value changes." << endl;
    cout << "3. Focus on why deep copy is needed when a class owns dynamic memory." << endl;
    return 0;
}
