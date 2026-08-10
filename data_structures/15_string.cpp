#include <iostream>

using namespace std;

// 计算 C 风格字符串长度。
int stringLength(const char str[]) {
    int length = 0;
    while (str[length] != '\0') {
        ++length;
    }
    return length;
}

// 朴素匹配：逐位尝试，失配后主串回退到下一个起点。
int bruteForceMatch(const char text[], const char pattern[]) {
    int i = 0;
    int j = 0;

    while (text[i] != '\0' && pattern[j] != '\0') {
        if (text[i] == pattern[j]) {
            ++i;
            ++j;
        } else {
            i = i - j + 1;
            j = 0;
        }
    }

    if (pattern[j] == '\0') {
        return i - j;
    }
    return -1;
}

// 构造 next 数组，用于失配时决定模式串跳转位置。
void buildNext(const char pattern[], int next[]) {
    int m = stringLength(pattern);
    next[0] = -1;
    int j = 0;
    int k = -1;

    while (j < m - 1) {
        if (k == -1 || pattern[j] == pattern[k]) {
            ++j;
            ++k;
            next[j] = k;
        } else {
            k = next[k];
        }
    }
}

// 构造 nextVal 数组，进一步减少无效比较。
void buildNextVal(const char pattern[], int nextVal[]) {
    int m = stringLength(pattern);
    nextVal[0] = -1;
    int j = 0;
    int k = -1;

    while (j < m - 1) {
        if (k == -1 || pattern[j] == pattern[k]) {
            ++j;
            ++k;
            if (pattern[j] != pattern[k]) {
                nextVal[j] = k;
            } else {
                nextVal[j] = nextVal[k];
            }
        } else {
            k = nextVal[k];
        }
    }
}

// KMP 匹配：主串不回退，模式串借助 next 数组跳转。
int kmpMatch(const char text[], const char pattern[], const int next[]) {
    int i = 0;
    int j = 0;

    while (text[i] != '\0' && pattern[j] != '\0') {
        if (j == -1 || text[i] == pattern[j]) {
            ++i;
            ++j;
        } else {
            j = next[j];
        }
    }

    if (pattern[j] == '\0') {
        return i - j;
    }
    return -1;
}

// 输出整型数组，便于观察 next 和 nextVal。
void printIntArray(const int arr[], int n, const char label[]) {
    cout << label << ": ";
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << ' ';
    }
    cout << '\n';
}

// 顺序串：用固定数组保存字符，适合学习基本串操作。
class SeqString {
private:
    static const int MAX_SIZE = 100;
    char data[MAX_SIZE];
    int length;

public:
    // 初始化为空串。
    SeqString() : data(), length(0) {}

    // 用字符数组给顺序串赋值。
    void assign(const char str[]) {
        length = 0;
        for (int i = 0; str[i] != '\0' && i < MAX_SIZE - 1; ++i) {
            data[length++] = str[i];
        }
        data[length] = '\0';
    }

    // 返回当前串长。
    int size() const {
        return length;
    }

    // 顺序串上的朴素模式匹配。
    int indexOf(const char pattern[]) const {
        int patternLength = 0;
        while (pattern[patternLength] != '\0') {
            ++patternLength;
        }

        for (int i = 0; i <= length - patternLength; ++i) {
            int j = 0;
            while (j < patternLength && data[i + j] == pattern[j]) {
                ++j;
            }
            if (j == patternLength) {
                return i;
            }
        }
        return -1;
    }

    // 在指定位置插入一个字符串。
    void insert(int pos, const char str[]) {
        if (pos < 0 || pos > length) {
            return;
        }

        int insertLength = 0;
        while (str[insertLength] != '\0' && length + insertLength < MAX_SIZE - 1) {
            ++insertLength;
        }

        for (int i = length - 1; i >= pos; --i) {
            data[i + insertLength] = data[i];
        }
        for (int i = 0; i < insertLength; ++i) {
            data[pos + i] = str[i];
        }

        length += insertLength;
        data[length] = '\0';
    }

    // 删除从 pos 开始的 count 个字符。
    void remove(int pos, int count) {
        if (pos < 0 || pos >= length || count <= 0) {
            return;
        }
        if (pos + count > length) {
            count = length - pos;
        }

        for (int i = pos + count; i <= length; ++i) {
            data[i - count] = data[i];
        }
        length -= count;
    }

    // 输出当前顺序串内容。
    void print() const {
        for (int i = 0; i < length; ++i) {
            cout << data[i];
        }
        cout << '\n';
    }
};

int main() {
    // 演示：顺序串基本操作、朴素匹配和 KMP 匹配。
    SeqString s;
    s.assign("datastructure");
    s.print();

    cout << "index of struct: " << s.indexOf("struct") << '\n';

    s.insert(4, "_");
    s.print();

    s.remove(4, 1);
    s.print();

    // 下面单独演示 KMP 的 next、nextVal 和匹配过程。
    const char text[] = "ababcabcacbab";
    const char pattern[] = "abcac";
    int m = stringLength(pattern);
    int next[100] = {0};
    int nextVal[100] = {0};

    buildNext(pattern, next);
    buildNextVal(pattern, nextVal);

    cout << "seq string indexOf(\"struct\"): " << s.indexOf("struct") << '\n';
    cout << "brute force match position: " << bruteForceMatch(text, pattern) << '\n';
    printIntArray(next, m, "next");
    printIntArray(nextVal, m, "nextVal");
    cout << "kmp match position: " << kmpMatch(text, pattern, next) << '\n';
    cout << "kmp match position with nextVal: " << kmpMatch(text, pattern, nextVal) << '\n';

    return 0;
}
