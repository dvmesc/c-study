#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

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

// 演示 string 的创建和访问。
void demoStringCreationAndAccess() {
    printSection("1. String Creation And Access");

    string title = "Modern C++";
    string copy = title;
    string combined = title + " Learning";

    cout << "title = " << title << endl;
    cout << "copy = " << copy << endl;
    cout << "combined = " << combined << endl;
    // size() 返回字符串长度。
    cout << "title.size() = " << title.size() << endl;
    cout << "title[0] = " << title[0] << endl;
    // at(下标) 按位置取字符，会做越界检查。
    cout << "title.at(1) = " << title.at(1) << endl;
}

// 演示常见的 string 修改操作。
void demoStringModify() {
    printSection("2. String Modify");

    string text = "hello";
    text += " world";
    // append() 在字符串末尾追加内容。
    text.append(" !!!");
    // insert(位置, 内容) 在指定位置插入内容。
    text.insert(0, "[");
    // push_back() 在末尾追加一个字符。
    text.push_back(']');

    cout << "text = " << text << endl;

    // erase(位置, 个数) 从指定位置删除若干字符。
    text.erase(0, 1);
    // pop_back() 删除最后一个字符。
    text.pop_back();

    cout << "after erase/pop_back = " << text << endl;
}

// 演示 string 的查找和截取。
void demoStringFindAndSubstr() {
    printSection("3. String Find And Substr");

    string sentence = "C++ string find and substr example";
    // find() 查找子串第一次出现的位置，找不到时返回 string::npos。
    size_t pos = sentence.find("find");

    if (pos != string::npos) {
        cout << "\"find\" found at index " << pos << endl;
    }

    // substr(起始位置, 长度) 截取子串。
    string part1 = sentence.substr(0, 3);
    string part2 = sentence.substr(4, 6);

    cout << "part1 = " << part1 << endl;
    cout << "part2 = " << part2 << endl;
}

// 去掉 ':' 前面的前缀内容。
string trimSimplePrefix(const string& text) {
    // find() 这里用于定位 ':' 的位置。
    size_t pos = text.find(':');
    if (pos == string::npos) {
        return text;
    }
    // substr() 从 ':' 后面开始截取剩余部分。
    return text.substr(pos + 1);
}

// 演示字符串参数传递和返回值。
void demoStringFunctionParameter() {
    printSection("4. String Function Parameter");

    string raw = "name:Alice";
    string result = trimSimplePrefix(raw);

    cout << "raw = " << raw << endl;
    cout << "result = " << result << endl;
}

// 输出 vector 中的所有数字。
void printVector(const vector<int>& nums, const string& label) {
    cout << label << ": ";
    for (int value : nums) {
        cout << value << " ";
    }
    cout << endl;
}

// 演示 vector 的创建和基础访问。
void demoVectorBasics() {
    printSection("5. Vector Basics");

    vector<int> nums;
    // push_back() 在 vector 末尾追加元素。
    nums.push_back(10);
    nums.push_back(20);
    nums.push_back(30);

    printVector(nums, "nums");

    // size() 返回当前元素个数。
    cout << "size = " << nums.size() << endl;
    // front() 取第一个元素。
    cout << "front = " << nums.front() << endl;
    // back() 取最后一个元素。
    cout << "back = " << nums.back() << endl;

    // pop_back() 删除最后一个元素。
    nums.pop_back();
    printVector(nums, "after pop_back");
}

// 演示多种遍历 vector 的方式。
void demoVectorTraversal() {
    printSection("6. Vector Traversal");

    vector<int> nums = {3, 6, 9, 12, 15};

    cout << "index traversal: ";
    for (size_t i = 0; i < nums.size(); ++i) {
        cout << nums[i] << " ";
    }
    cout << endl;

    cout << "range traversal: ";
    for (int value : nums) {
        cout << value << " ";
    }
    cout << endl;

    for (int& value : nums) {
        value += 1;
    }

    printVector(nums, "after +1");
}

// 演示 vector 的插入、删除和清空。
void demoVectorInsertErase() {
    printSection("7. Vector Insert And Erase");

    vector<int> nums = {1, 2, 4, 5};

    // begin() 返回首元素位置，insert() 在该位置前插入元素。
    nums.insert(nums.begin() + 2, 3);
    printVector(nums, "after insert");

    // erase() 删除指定位置的元素。
    nums.erase(nums.begin() + 1);
    printVector(nums, "after erase index 1");

    // clear() 清空所有元素。
    nums.clear();
    cout << "after clear, size = " << nums.size() << endl;
}

// 演示 algorithm 里的 sort、find 和 count。
void demoAlgorithmSortFind() {
    printSection("8. algorithm sort and find");

    vector<int> nums = {42, 7, 19, 7, 88, 15};
    printVector(nums, "before sort");

    // sort() 对区间内元素进行排序。
    sort(nums.begin(), nums.end());
    printVector(nums, "after sort");

    // find() 在区间里查找指定值，返回对应位置。
    auto it = find(nums.begin(), nums.end(), 19);
    if (it != nums.end()) {
        cout << "19 found at index " << (it - nums.begin()) << endl;
    }

    // count() 统计某个值出现了多少次。
    int count7 = static_cast<int>(count(nums.begin(), nums.end(), 7));
    cout << "count of 7 = " << count7 << endl;
}

struct Book {
    string title;
    string author;
    double price;
};

// 输出一个 Book 对象。
void printBook(const Book& book) {
    cout << "Book { title = " << book.title
         << ", author = " << book.author
         << ", price = " << book.price
         << " }" << endl;
}

// 演示存放结构体的 vector。
void demoVectorOfStruct() {
    printSection("9. Vector Of Struct");

    vector<Book> books = {
        {"Clean Code", "Martin", 99.0},
        {"C++ Primer", "Lippman", 128.0},
        {"Effective C++", "Meyers", 108.0}
    };

    for (const Book& book : books) {
        printBook(book);
    }
}

class BookManager {
private:
    vector<Book> books;

public:
    // 向管理器中添加一本书。
    void addBook(const string& title, const string& author, double price) {
        // push_back() 向 books 末尾追加一条记录。
        books.push_back({title, author, price});
    }

    // 输出当前保存的所有书籍。
    void printAll() const {
        cout << "Book count = " << books.size() << endl;
        for (const Book& book : books) {
            printBook(book);
        }
    }

    // 按书名更新价格。
    bool updatePriceByTitle(const string& title, double newPrice) {
        for (Book& book : books) {
            if (book.title == title) {
                book.price = newPrice;
                return true;
            }
        }
        return false;
    }

    // 按书名删除第一本匹配的书。
    bool removeByTitle(const string& title) {
        for (auto it = books.begin(); it != books.end(); ++it) {
            if (it->title == title) {
                // erase() 删除迭代器指向的元素。
                books.erase(it);
                return true;
            }
        }
        return false;
    }

    // 按价格升序排序。
    void sortByPriceAscending() {
        // sort() 结合比较规则，按价格从小到大排序。
        sort(books.begin(), books.end(), [](const Book& a, const Book& b) {
            return a.price < b.price;
        });
    }

    // 返回所有匹配关键字的书。
    vector<Book> searchByKeyword(const string& keyword) const {
        vector<Book> result;

        for (const Book& book : books) {
            // find() 判断标题或作者中是否包含关键字。
            if (book.title.find(keyword) != string::npos ||
                book.author.find(keyword) != string::npos) {
                // push_back() 把匹配结果加入结果列表。
                result.push_back(book);
            }
        }

        return result;
    }
};

// 输出一组书籍列表。
void printBookList(const vector<Book>& books, const string& label) {
    cout << label << endl;
    for (const Book& book : books) {
        printBook(book);
    }
}

// 演示一个基于 vector 的小型管理类。
void demoBookManager() {
    printSection("10. BookManager Class");

    BookManager manager;
    manager.addBook("C++ Primer", "Lippman", 128.0);
    manager.addBook("Clean Code", "Martin", 99.0);
    manager.addBook("Effective C++", "Meyers", 108.0);
    manager.addBook("The C Programming Language", "Kernighan", 85.0);

    manager.printAll();

    cout << "update price result = "
         << manager.updatePriceByTitle("Clean Code", 88.0)
         << endl;

    manager.sortByPriceAscending();
    manager.printAll();

    vector<Book> result = manager.searchByKeyword("C++");
    printBookList(result, "search result keyword = C++");

    cout << "remove result = "
         << manager.removeByTitle("The C Programming Language")
         << endl;

    manager.printAll();
}

class Student {
private:
    string name;
    vector<int> scores;

public:
    // 创建一个空成绩列表的学生对象。
    Student(const string& name) : name(name) {}

    // 往成绩列表末尾追加一个分数。
    void addScore(int score) {
        // push_back() 追加一个分数到末尾。
        scores.push_back(score);
    }

    // 计算平均分。
    double average() const {
        // empty() 判断容器是否为空。
        if (scores.empty()) {
            return 0.0;
        }

        int sum = 0;
        for (int score : scores) {
            sum += score;
        }
        return static_cast<double>(sum) / scores.size();
    }

    // 返回最高分。
    int highest() const {
        // empty() 判断容器是否为空。
        if (scores.empty()) {
            return 0;
        }
        // max_element() 返回区间内最大元素的位置。
        return *max_element(scores.begin(), scores.end());
    }

    // 输出学生信息摘要。
    void print() const {
        cout << "Student { name = " << name << ", scores = ";
        for (int score : scores) {
            cout << score << " ";
        }
        cout << ", avg = " << average()
             << ", highest = " << highest()
             << " }" << endl;
    }
};

// 演示类里保存 vector 的写法。
void demoVectorInsideClass() {
    printSection("11. Vector Inside Class");

    Student s("Alice");
    s.addScore(90);
    s.addScore(85);
    s.addScore(96);
    s.addScore(91);
    s.print();
}

// 按空格拆分一句话。
vector<string> splitBySpace(const string& text) {
    vector<string> words;
    string current;

    for (char ch : text) {
        if (ch == ' ') {
            // empty() 判断 current 里是否有内容。
            if (!current.empty()) {
                // push_back() 把当前单词加入结果。
                words.push_back(current);
                // clear() 清空当前单词，为下一个单词做准备。
                current.clear();
            }
        } else {
            // push_back() 在字符串末尾追加一个字符。
            current.push_back(ch);
        }
    }

    if (!current.empty()) {
        // push_back() 把最后一个单词加入结果。
        words.push_back(current);
    }

    return words;
}

// 演示一个简单的字符串拆分函数。
void demoStringSplit() {
    printSection("12. String Split");

    string line = "learn cpp with string and vector";
    vector<string> words = splitBySpace(line);

    // size() 返回拆分后的单词个数。
    cout << "word count = " << words.size() << endl;
    for (const string& word : words) {
        cout << word << endl;
    }
}

// 演示二维 vector。
void demoNestedVector() {
    printSection("13. Nested Vector");

    vector<vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    for (const vector<int>& row : matrix) {
        for (int value : row) {
            cout << value << " ";
        }
        cout << endl;
    }
}

// 运行第三阶段全部示例。
int main() {
    demoStringCreationAndAccess();
    demoStringModify();
    demoStringFindAndSubstr();
    demoStringFunctionParameter();
    demoVectorBasics();
    demoVectorTraversal();
    demoVectorInsertErase();
    demoAlgorithmSortFind();
    demoVectorOfStruct();
    demoBookManager();
    demoVectorInsideClass();
    demoStringSplit();
    demoNestedVector();

    printSection("14. Study Advice");
    cout << "1. Rewrite BookManager by yourself." << endl;
    cout << "2. Replace Book with Student or Product and practice again." << endl;
    cout << "3. Add search, remove, sort and statistics functions on your own." << endl;
    return 0;
}
