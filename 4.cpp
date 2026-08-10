#include <iostream>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
using  namespace  std;

void con1 (int a, int b) {
    int c=a ;
    a=b;
    b=c;

}

void con2 (int& a, int& b) {
    int c=a ;
    a=b;
    b=c;
}

void con3 (int*  ptr) {
    if (ptr!= nullptr) {
        *ptr  +=10;
    }
}

void con4 (const string& label , int* b) {

}

int* cont6 ( int value) {
    int* ptr = new int(value);
    return ptr;
}

void con9 (int* arr ,int s) {
    for (int i = 0 ; i < s ; ++i) {
        arr[i]=(i+1)*10;
    }
}

void con10 () {
    int s = 10;
    int* arr = new int[s];
}

class NB {
private:
    int value;

public:
    NB():value(0) {

    }
    NB(int value) :value(value) {

    }

    int getvalue () const {
        return  value;

    }

    void setvalue (int value) {
        this->value=value;
    }
};

class  IntB {

private:
    int s;
    int* z;

public:
    IntB(): s(0),z(nullptr) {

    }

    IntB(int s) : s(s),z(new int(s)) {
        for (int i = 0 ; i < s ; ++i) {
            z[i]=0;
        }
    }


    IntB(const IntB& other) : s(other.s),z(new int[other.s]) {
        for (int i = 0 ; i < s ; ++i) {
            z[i]=other.z[i];
        }
    }

    IntB operator= (const IntB& other) {

        if (this == &other) {
            return *this;
        }

        delete[] z;
        s=other.s;
        z=new int[s];

        for (int i = 0 ; i < s ; ++i) {
            z[i]=other.z[i];
        }
        return *this;
    }

    ~IntB() {
        delete[] z;

    }

    int getvalue () const {
        return s;
    }

    void setnum (int index,int value) {
        if (index>=0 && index<s) {
            z[index]=value;
        }
    }

    int getnum (int index) const {
        if (index>=0 && index<s) {
            return z[index];
        }
        return -1;
    }

    void print (const string& label) const {
        for (int i = 0 ; i < s ; ++i) {
            cout << z[i] << " ";
        }
        cout << endl;
    }
};


void fill(IntB& b,int  sv) {
    for (int i = 0 ; i < b.getvalue() ; ++i) {
        b.setnum(i,sv+1*3);
    }
}


class StudentRecord {
private:
    string name;
    int* scores;
    int scoreCount;

public:
   StudentRecord():name("StudentRecord") ,scoreCount(0) ,scores(nullptr) {

   }

    StudentRecord(const string& name,int scoreCount)
    :name(name),scores( new  int [scoreCount]) ,scoreCount(scoreCount) {
       for (int i = 0 ; i < scoreCount ; ++i) {
           scores[i]=i;
       }
   }

    StudentRecord(const StudentRecord& other)
        :name(other.name),scores(new int[other.scoreCount]),scoreCount(other.scoreCount){
       for (int i = 0 ; i < other.scoreCount ; ++i) {
           scores[i]=other.scores[i];
       }
   }

    StudentRecord& operator=(const StudentRecord& other) {
       if (this == &other) {
           return *this;
       }

       delete[] scores;
       scores=new int[other.scoreCount];
       name=other.name;
       scoreCount=other.scoreCount;
       for (int i = 0 ; i < other.scoreCount ; ++i) {
           scores[i]=other.scores[i];
       }
       return *this;
   }

    ~StudentRecord() {
       delete[] scores;
   }

    void setScore(int index,int score) {
       if (index>=0 && index<scoreCount) {
           scores[index]=score;
       }
   }

    double aver() const {
       int sum=0;
       for (int i = 0 ; i < scoreCount ; ++i) {
           sum+=scores[i];
       }
       return scoreCount==0 ? 0.0 : static_cast<double>(sum)/scoreCount;
   }
    void print () const {
       for (int i = 0 ; i < scoreCount ; ++i) {
           cout << scores[i] << " ";
       }
       cout << endl;
   }


};


void demoStringCreationAndAccess() {


    string title = "Modern C++";
    string copy = title;
    string combined = title + " Learning";

    cout << "title = " << title << endl;
    cout << "copy = " << copy << endl;
    cout << "combined = " << combined << endl;
    cout << "title.size() = " << title.size() << endl;
    cout << "title[0] = " << title[0] << endl;
    cout << "title.at(1) = " << title.at(1) << endl;
    cout << "title.at(2) = " << title.append("1233") << endl;
    cout << "title[0] = " << title.insert(3,"233312") << endl;
    cout << "title[0] = " << title.append("133231") << endl;
    cout << "title[0] = " << title.erase(3,1) << endl;

    string title2 = "51511";
    title2.pop_back();
    title2.push_back('1');

    cout << "title[0] = " << title2 << endl;
    string sentence = "C++ string find and substr example";
    size_t pos = sentence.find("find");
    if (pos != string::npos) {


        }

    string sentence2 =sentence.substr(3,1);
};

string cons0(const  string& s) {
    size_t pos = s.find("find");
    if (pos != string::npos) {
        return s;
    }
    return s.substr(pos+2);
}

void ref1(const vector<int>& nums ,const string& label) {
    for (int value :nums) {
        cout << value << " ";
    }
    cout << endl;
}

void base1() {
    vector<int> i;
    i.push_back(1);
    i.push_back(2);
    i.push_back(3);

    cout << i.size() << endl;
    cout << i[0] << endl;
    cout << i.front() << endl;
    cout << i.back() << endl;

}

void demo1() {
    vector<int> vec = {1,2,3,4,5};
    for (size_t i = 0; i < vec.size(); ++i) {

    }
}

void demo2() {
    vector<int> vec = {1,2,3,4,5};
    vec.insert(vec.begin()+1,6);
    vec.erase(vec.begin());
    vec.clear();

}
void demo3() {
    vector<int> nums = {42, 7, 19, 7, 88, 15};
     sort(nums.begin(), nums.end());
    auto it = find(nums.begin(), nums.end(), 7);
    if (it != nums.end()) {}

    int cout = static_cast<int>(count(nums.begin(), nums.end(),0));
}

struct Book {
    string title;
    string author;
    double price;
};
void pB(const Book& b) {
    cout << b.author <<b.title<<b.price<< endl;
}

void demo4() {
    vector<Book> books={
        {"Clean Code", "Martin", 99.0},
        {"C++ Primer", "Lippman", 128.0},
        {"Effective C++", "Meyers", 108.0}
    };


    for ( Book book : books ) {
        cout << book.author <<book.title <<book.price << endl;
    }
}



class BookMagger {
private:
    vector<Book> books;

public:
    void addBook(const string& name, const string& author, const double price) {
        books.push_back({name,author,price});
    }

    void printbook() const {
        for (Book book : books) {

        }
    }


    bool update(const string& name ,double new_price) {
        for (Book book : books) {
            if (book.price == new_price) {
                return true;
            }
        }
        return false;
    }


    void sort1(const Book& book) {
        sort(books.begin(), books.end(), [](const Book& a, const Book& b) {
            return a.price > b.price;
        });
    };

    vector<Book> keyword(const string& keyword) const{
        vector<Book> v;

        for (const Book book : books) {
            if (book.author.find(keyword) != string::npos||
                book.title.find(keyword) != string::npos) {
                v.push_back(book);
            }
        }
        return v;
    };
};



class Student {
private:
    string name;
    vector<int> scores;

public:
    Student(const string& name):name(name) {

    }

    void addscores(int s) {
        scores.push_back(s);
    }


    double average() const {
        if (scores.empty()) {
            return  0.0;
        }

        int sum = 0;
        for (int s: scores) {
            sum += s;
        }
        return static_cast<double>(sum)/scores.size();
    };

    int hight() const {
        if (scores.empty()) {
            return  0;
        }
        return  *max_element(scores.begin(),scores.end());
    }
 };


vector<string> splitBySpace(const string& s) {
    vector<string> v;
    string c;

    for (char ch : s) {
        if (ch == ' ') {
            if (!c.empty()) {
                v.push_back(c);
                c.clear();
            }
        } else {
            c.push_back(ch);
        }
    }
    if (!c.empty()) {
        v.push_back(c);

    }
    return v;

}




void NestedVec() {
    vector<vector<int>> v ={
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    for ( const vector<int> r : v) {
        for (int u : r) {
            cout << u << " ";
        }
    }
    cout << endl;
}

















































































































































