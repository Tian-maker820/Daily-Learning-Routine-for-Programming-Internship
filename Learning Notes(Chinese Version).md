### 课程进度安排：
基础篇：
- 第一讲 类和对象1
- 第二讲 类和对象2
- 第三讲 运算符重载
- 第四讲 派生与继承
- 第五讲 多态与虚函数
进阶篇：
- 第六讲 输入输出流与文件操作
- 第七讲 类模版与函数模版
- 第八讲 标准模版库（I）
- 第九讲 标准模版库（II）
- 第十讲 C++高阶与C++17新特性

QT技术分享，期中考试（4月29 周三）

python程序设计 对比篇
- 第一讲 C++程序员的python修养1
- 第二讲 C++程序员的python修养2
- 第三讲 C++程序员的python修养3
- 第四讲 C++程序员的python修养4

python程序设计 应用实践篇
- 第五讲 python应用实践：网络爬虫
- 第六讲 python应用实践：数据分析
- 第七讲 python应用实践：视觉与可视化

课程大作业的调整：
- QT大作业与python大作业的任选
- 期末路演分赛道安排两次课程汇报
- 元学习赛道+生活应用/游戏


### 类与对象 1

面向对象的程序设计方法：将某类客观事物共同特点（属性）归纳出来，形成一个数据结构，
将这类事物所能进行的行为也归纳出来，形成一个个函数，这些函数可以用来操作数据结构。
面向对象的程序设计方法，设计程序的过程，就是设计类的过程。

```c++
class CRectangle {
public:
    void init (double width, double height) {
        m_width = width;
        m_height = height;
    }
    double getArea() const {
        return m_width * m_height;
    }
    double getPerimeter() const {
        return 2 * (m_width + m_height);
    }
};

int main () {
    int w, h;
    cin >> w >> h;
    CRectangle rect;
    rect.init(w, h);
    cout << "Area: " << rect.getArea() << endl;
    cout << "Perimeter: " << rect.getPerimeter() << endl;
    return 0;
}
```

通过类，可以自定义变量
和结构变量一样，对象所占用的内存空间大小 = 所有成员变量的大小之和
每个对象都有自己独立的存储空间，一个对象的某个成员变量改变了，不会影响其他的
和结构变量一样，对象之间可以使用“=”进行赋值，但是不能用“==”“>“等进行比较。

使用类的成员变量和成员函数：
方法一：对象名.成员名

方法二：指针->成员名

```c++
CRectangle r1, r2;
CRectangle *p = &r1;
p->init(10, 20);
```

方法三：引用名.成员名

```c++
CRectangle r1, r2;
CRectangle &rr = r1;    
rr.init(10, 20);    // 等价于 r1.init(10, 20);
```

引用： 类型名& 变量名 = 某变量名
定义了一个应用，将其初始化为某个变量的值，某个变量的引用，
注意：一定要初始化引用，否则会出现未定义行为。
只能引用变量，不能引用常量和表达式。



### Mar6
### 类与对象 2
课程回顾：
- 类的基本表达
- 对象的内存分配与运算符
- 三种方法使用
- 引用

#### 常引用：
在前面加上const关键字
```c++
    int n;
    const int & r = n; // 常引用
```
好处：引用的值不能被r修改，但是可以被读取。
注意：常引用和普通引用不是一个类型，T&类型的引用或者T类型的变量可以用来初始化const &T类型的引用
但是const &T类型的引用不能用来初始化T&类型的引用。

类的函数的另一种写法：
成员函数和类的定义分开写：
```c++
class CRectangle {
public:
    void init (double width, double height)；
};

void CRectangle::init (double width, double height) { //用“：：”来代表这是CRectangle类的成员函数
    m_width = width;
    m_height = height;
}  
```

#### 类成员的访问权限：封装
类成员的访问范围：
用访问范围关键字：
**public**:公有成员，可以在任何地方访问
**private**:私有成员，只能在成员函数内访问
**protected**:保护成员
默认是private

例：
```c++
class CEmployee {
private:
    char szname[30];
public:
    int salary;
    void setName(char *name);
    void getName(char *name);
    void averageSalary(CEmployee *e1, CEmployee *e2);
};

void CEmployee::setName(char *name) {
    strcpy(szname, name);
}

void CEmployee::getName(char *name) {
    strcpy(name, szname);
}

void CEmployee::averageSalary(CEmployee *e1, CEmployee *e2) {
    int s1 = e1->salary;
    int s2 = e2->salary;
    int avg = (s1 + s2) / 2;
    cout << "The average salary is: " << avg << endl;
}

int main () {
    CEmployee e1, e2;
    e1.salary = 10000;
    e2.salary = 20000;
    e1.setName("Alice");
    e2.setName("Bob");
    char name[30];
    e1.getName(name);
    cout << "Name of e1 is: " << name << endl;
    e1.averageSalary(&e1, &e2);
    return 0;
}

```
将一个比较重要的变量通过一个统一的接口访问，可以提高程序的可读性和可维护性。

#### 用struct定义类：
```c++
struct CRectangle {
    double width, height;
    double getArea() const {
        return width * height;
    }
    double getPerimeter() const {
        return 2 * (width + height);
    }
};
```
默认struct的访问权限是public。

#### 函数重载
一个或者多个函数，名字相同，然而参数个数或者参数类型不同，这叫做**函数的重载**。
```c++
int max(double f1, double f2);
int max(int n1, int n2);
int max(int n1, int n2, int n3);
```
编译器根据函数调用时的参数类型，选择最匹配的函数。
#### 函数的缺省值：
c++中，定义函数时可以让**最右边**的连续若干个参数有缺省值，若相应的位置不写参数，参数就是缺省值
```c++
void func (int x1, int x2 = 10, int x3 = 20);
func (10); // x2 = 10, x3 = 20
```
#### 构造函数(constructor)
在程序没有明确进行初始化的情况下：
- 全局基本类型变量的默认初始化为0
- 局部类型基本变量，初始值随机
  
构造函数是成员函数的一种，它用来初始化对象，构造函数的名字与类名相同，没有返回值（void也不行），没有参数。
作用：为对象进行初始化，如给成员变量赋初值
- 不必专门再写初始化函数，也不必担心忘记调用初始化函数
- 

例：
```c++
class Complex {
    private:
        double real, imag;
    public:
        void set (double r, double i)
}; //编译器自动生成默认构造函数

Complex c1; //默认构造函数被调用
Complex *pc = new Complex; //调用默认构造函数
```
有自定义构造函数：
```c++
class Complex {
    private:
        double real, imag;
    public:
        Complex (double r = 0.0, double i = 0.0) {
            real = r;
            imag = i;
        }
};

Complex c1 //报错，没有参数
Complex *pc = new Complex; //报错，没有参数
Complex c2(2); //OK, Complex c2(2.0, 0.0);
Complex c3(3.0, 4.0); //OK
Complex *pc = new Complex(5.0, 6.0); //OK
```

可以有多个构造函数，参数个数或者类型不同
```c++
class Complex {
    private:
        double real, imag;
    public:
        void set (double r, double i);
        Complex (double r = 0.0, double i = 0.0);
        Complex (double r);
        Complex (Complex c1, Complex c2);
};
```

构造函数最好是public的，private构造函数不能直接用来初始化对象

构造函数在数组中的使用：
```c++
class Complex {
    private:
        double real, imag;
    public:
        Complex (double r, double i) {
            real = r;
            imag = i;
        }
};

int main () {
    Complex c[3] = {Complex(1.0, 2.0), Complex(3.0, 4.0), Complex(5.0, 6.0)};
    return 0;
}
```

#### 复制构造函数(copy constructor)
只有一个参数，即对同类对象的引用
形如X::X或者X::X(const X&)二选一，后者能以const对象作为参数
如果没有自定义，编译器默认生成默认复制构造函数
不允许有形如X::X(X&)的复制构造函数，因为这样会导致对象被复制两次，造成资源浪费。

例：
```c++
class Complex {
    private:
        double real, imag;
    public:
        Complex (double r, double i) { //构造函数
            real = r;
            imag = i;
        }
        Complex (const Complex& c) { //复制构造函数
            real = c.real;
            imag = c.imag;
        }
};

int main () {
    Complex c1(1.0, 2.0);
    Complex c2(c1); //调用复制构造函数
    return 0;
}
```

复制构造函数在以下三种情况被调用：
- 当用一个对象去初始化同类的另一个对象是时
```c++
    Complex c2(c1); //复制构造函数被调用
    Complex c3 = c1; //初始化语句，非赋值语句，完成的是按位拷贝，复制构造函数不会被调用
```
- 如果某函数的一个参数是类A的对象，那么该函数被调用时，类A的复制构造函数被调用
    ```c++
    class A {
        public:
            A(const A& a) { //复制构造函数
                //...
            }
    };
    void func(A a) { //参数是A类型
        //...
    }
    int main () {
        A c1;
        func(c1); //调用复制构造函数
        return 0;
    } 
    ```
- 如果某函数的返回值是类A的对象，那么该函数被调用时，类A的复制构造函数被调用
```c++
class A {
    public:
        A(const A& a) { //复制构造函数
            //...
        } 
};

A func() { //返回值是A类型
    A a;
    return a; //调用复制构造函数
}

int main () {    
    A c1 = func(); //调用复制构造函数
    return 0;
}
```

注意；对象间用等号赋值不会导致复制构造函数被调用，因为按位拷贝，不会调用复制构造函数。

调用时生成形参会引发复制构造函数被调用，开销比较大

#### 类型转换构造函数(conversion constructor)

#### 析构函数(destructor)



### 类与对象 3
课程回顾：
- 面向对象啊的基本概念
- 常引用、类成员的访问权限、函数重载
- 构造函数
- 复制构造函数
- 析构函数
- this指针

下面程序片段哪个没错？
- int n = 4; int &r = n; //错误，只能引用常量，不能引用变量
- int n = 4; const int &r = n; //正确，常引用

#### this指针
非静态成员函数中可以直接使用this来代表指向该函数作用的对象的指针

```c++
class Complex {
public:
    double real, imag;
    void Print() { cout << real << "," << imag; }
    Complex(double r, double i):real(r), imag(i) { }
    Complex AddOne() {
        this->real ++; //等价于 real ++;
        this->Print(); //等价于 Print()
        return * this;
    } 
};
```

注意返回引用和返回对象的区别：
特性	            返回引用	                返回对象
返回的实体	        当前对象本身	        当前对象的副本（临时对象）
是否修改原对象	        是	            否（修改的是原对象，但返回副本）
链式调用的主体	    始终是同一个对象	        不断在临时对象上调用
内存开销	         无额外对象	           每次返回产生临时对象（可能优化）
典型用途	    赋值运算符重载、连续修改同一对象	需要返回新对象的操作（如 + 运算）

基于this指针的这一特性可以实现链式调用：
```c++
#include <iostream>
using namespace std;

class Counter {
public:
    int value;
    Counter(int v = 0) : value(v) {}
    Counter& add_ref(int x) {
        value += x;
        return *this;
    }
    Counter add_val(int x) {
        value += x;
        return *this;
    }
    void show() const { cout << "value = " << value << endl; }
};

int main() {
    cout << "--- 返回引用 ---" << endl;
    Counter a(0);
    a.add_ref(5).add_ref(3);       // 链式调用
    a.show();                       // 输出 value = 8（原对象被修改）

    cout << "--- 返回对象 ---" << endl;
    Counter b(0);
    b.add_val(5).add_val(3);       // 链式调用
    b.show();                       // 输出 value = 5（原对象只加了5）
    // 如果想要看到最终临时对象的值：
    cout << "临时对象的值: " << b.add_val(5).add_val(3).value << endl; // 输出 8
    return 0;
}
```

#### 内联函数
函数调用本身是有时间开销的。如果函数本身只有几条语句, 执行非常快，但是函数被反复执行很多次, 调用函数所产生的，这个开销就会显得比较大。
定义函数时, 在返回值类型前面加 inline 关键字, 可以使得函数成为内联函数
编译器处理内联函数的调用语句时 → 将整个函数的代码插入到调用语句处, 而不会生出调用函数的语句，示例：
```c++
inline int Max(int a, int b)
{
if( a > b ) return a;
return b;
}
```
**内联成员函数：**在成员函数前面加上 inline 关键字后, 成员函数就成为内联成员函数；将整个函数体写在类定义内部, 函数也会成为内联成员函数。例：
```c++
class B{
inline void func1();
void func2() { }
};
void B::func1() { }
//func1和func2都是内联成员函数
```


#### 静态成员
静态成员: 在说明前面加了static关键字的成员
```c++
class CRectangle {
private:
int w, h;
static int nTotalArea; //静态成员变量
static int nTotalNumber;
public:
CRectangle(int w_, int h_);
~CRectangle();
static void PrintTotal(); //静态成员函数
};
CRectangle r;
```
**静态成员变量与普通成员变量的区别：**
- 普通成员变量每个对象有各自的一份，静态成员变量一共就一份, 为所有对象共享
- sizeof 运算符不会计算静态成员变量
- 普通成员函数必须具体作用于某个对象，静态成员函数并不具体作用于某个对象
- 静态成员不需要通过对象就能访问

访问静态成员方式:
(1) 通过：
类名::成员名 的方式：CRectangle::PrintTotal(); 
(2) 也可以和普通成员一样采取
- 对象名.成员名 r.PrintTotal();
- 指针->成员名 CRectangle * p = &r; 
p->PrintTotal();
- 引用.成员名 CRectangle & ref = r; 
int n = ref.nT

静态成员变量本质上是全局变量，哪怕一个对象都不存在, 类的静态成员变量也存在，静态成员函数本质上是全局函数
设置静态成员这种机制的目的
- 将与某些类紧密相关的全局变量和函数写到类里面
- 看上去像一个整体
- 易于维护和理解

注：sizeof()函数
sizeof 是一个编译时运算符，用于计算一个类型或变量所占用的内存字节数。它返回一个 size_t 类型的值。
对于基本类型，比如 sizeof(int) 通常是 4（32位系统）或 8（64位系统），但具体取决于编译器和平台。
- 对于数组，sizeof(数组名) 返回整个数组占用的字节数。
- 对于结构体或类，sizeof(类名) 返回该类型的一个对象所占用的字节数。
注意：sizeof 是在编译时计算的，不会执行括号内的表达式，只关心类型大小。

当你对一个类使用 sizeof 时，它计算的是这个类的对象在内存中占用的总字节数。具体包括：
- 所有非静态成员变量的大小：每个成员变量占据的空间。
- 内存对齐（padding）：为了提高访问效率，编译器可能会在成员之间或末尾插入一些空白字节，使得每个成员的起始地址符合其类型对齐要求。
- 如果类有虚函数：会包含一个指向虚函数表（vtable）的指针（通常是一个指针大小，例如 4 或 8 字节）。
- 如果类有虚继承：可能包含额外的指针或偏移量信息。
不包括的内容：
- 静态成员变量：静态成员不属于某个对象，而是属于类本身，存储在静态存储区，不影响 sizeof。
- 成员函数：函数代码存储在代码段，不占用对象的内存空间（除了虚函数相关的指针）。

#### 常量成员函数
**复习: const 的用法**
对指针定义const, 则不可通过该指针修改其指向地方的内容
```c++
int n, m;
const int * p = & n;
* p = 5; //编译出错
n = 4; //ok
p = &m; //ok
//注意: 不能把常量指针赋值给非常量指针, 反过来可以
const int * p1; int * p2;
p1 = p2; //ok
p2 = p1; //error
p2 = (int * ) p1; //ok
```

**常量对象和常量方法**
常量对象: 如果不希望某个对象的值被改变，则定义该对象的时候可以在前面加 const关键字
```c++
class Sample {
private:
int value;
public:
void GetValue() { }
};
const Sample Obj; // 常量对象
Obj.GetValue(); //错误
```
常量对象只能使用:
构造函数, 析构函数 和 有const说明的函数 (常量方法)
常量对象和常量方法
- 在类的成员函数说明后面加const关键字, 则该成员函数成为常量
成员函数
- 常量成员函数内部不能改非静态属性的值, 也不能调用同类的非
常量成员函数 (静态成员函数除外)
```c++
class Sample {
public: int value; 
void GetValue( ) const;
void func( ) { }
}; 
void Sample::GetValue( ) const {
value = 0; // wrong
func(); //wrong
}
int main(){
const Sample o;
o.GetValue( ); //常量对象上可以执行常量成员函数
return 0;
}
```

#### 成员对象和封闭类

必须使用初始化列表的情况

1. 常量成员（const 成员）

原因：常量必须在定义时初始化，一旦定义就不能再赋值。在构造函数体内赋值相当于先定义（默认初始化）再赋值，而常量不允许这样。
示例：

```cpp
class MyClass {
    const int c;
public:
    MyClass(int x) : c(x) {}  // 正确
    // MyClass(int x) { c = x; }  // 错误！
};
```
2. 引用成员

原因：引用必须在定义时绑定到一个对象，不能重新绑定。在构造函数体内赋值实际上是在试图改变引用的指向，这是不允许的。
示例：

```cpp
class MyClass {
    int &ref;
public:
    MyClass(int &r) : ref(r) {}  // 正确
    // MyClass(int &r) { ref = r; }  // 错误！
};
```
3. 没有默认构造函数的类类型成员

原因：如果成员对象所属的类没有提供默认构造函数（即无参构造函数），那么在创建包含它的对象时，必须显式地调用该成员的有参构造函数来初始化它。这只能在初始化列表中完成。
示例：

```cpp
class Base {
public:
    Base(int x) {}  // 没有默认构造函数
};

class Big {
    Base b;
public:
    Big(int n) : b(n) {}  // 必须显式初始化 b
    // Big(int n) { b = Base(n); }  // 错误！因为 b 先默认构造（但不存在）再赋值
};
```
4. 基类（当基类没有默认构造函数时）

原因：派生类的构造函数在执行其函数体之前，必须先构造基类部分。如果基类没有默认构造函数，派生类必须在初始化列表中调用基类的带参构造函数。
示例：

```cpp
class Base {
public:
    Base(int x) {}
};

class Derived : public Base {
public:
    Derived(int n) : Base(n) {}  // 必须初始化基类
    // Derived(int n) { /* 错误！基类未初始化 */ }
};
```
5. 成员对象是类类型且需要非默认构造（其实与第3点相同，但强调一下）

#### 友元
**什么是友元？**

在 C++ 中，类的主要特点之一是封装：私有成员只能在类的内部访问，外部不能直接操作。但有时候，我们需要让某些特定的外部函数或类能够访问私有成员，以便实现紧密合作的功能。友元就是为此而生的——它打破了封装，授予特定的外部实体访问私有成员的权限。

注意：友元关系是单向的，不能传递，也不能继承。

**友元的种类**

友元可以分为三种：

- 友元函数：一个普通函数（可以是全局函数，也可以是另一个类的成员函数）被声明为某个类的友元，从而可以访问该类的私有成员。
- 友元类：整个类被声明为另一个类的友元，那么这个类的所有成员函数都可以访问另一个类的私有成员。
- 友元成员函数：仅将另一个类的某个特定成员函数声明为友元，而不是整个类。

**友元函数**

3.1 全局函数作为友元

```cpp
#include <iostream>
using namespace std;

class Point {
private:
    int x, y;
public:
    Point(int a, int b) : x(a), y(b) {}
    friend void display(const Point& p);// 声明友元函数
};

// 友元函数定义，可以访问 Point 的私有成员
void display(const Point& p) {
    cout << "(" << p.x << ", " << p.y << ")" << endl;
}

int main() {
    Point pt(3, 4);
    display(pt);   // 输出 (3, 4)
    return 0;
}
```
3.2 另一个类的成员函数作为友元

假设我们有两个类 A 和 B，想让 B 的一个成员函数访问 A 的私有数据。

```cpp
class A;  // 前向声明

class B {
public:
    void showA(const A& a);
};

class A {
private:
    int value;
public:
    A(int v) : value(v) {}
    friend void B::showA(const A& a); // 声明 B 的成员函数 showA 为友元
};

void B::showA(const A& a) {
    cout << "A's value = " << a.value << endl;  // 可以访问私有
}
```
注意：需要先声明类 B，定义其成员函数原型，然后在 A 中将其声明为友元，最后再定义 B::showA 函数体。顺序比较重要。

3.3 友元类

如果想让整个类 B 的所有成员函数都能访问类 A 的私有成员，可以将 B 声明为 A 的友元类。

```cpp
class A {
private:
    int secret;
public:
    A(int s) : secret(s) {}
    friend class B;  // B 是 A 的友元类
};

class B {
public:
    void showSecret(const A& a) {
        cout << "Secret: " << a.secret << endl;  // 可以访问
    }
    void modifySecret(A& a, int val) {
        a.secret = val;  // 也可以修改
    }
};
```
1. 友元的特性

- 友元关系不能传递：如果 B 是 A 的友元，C 是 B 的友元，不能推出 C 是 A 的友元。
- 友元关系是单向的：如果 B 是 A 的友元，不代表 A 是 B 的友元。
- 友元不能继承：基类的友元不自动成为派生类的友元。
- 友元声明不受访问限定符影响：可以放在类的 public、protected 或 private 部分，效果相同。

本讲小结
- 内联函数/内联成员函数
- 成员函数重载与参数缺省
- 静态成员
- 常量成员函数
- 成员对象和封闭类
- 友元


#### 运算符重载
**1. 什么是运算符重载？**

运算符重载就是让已有的运算符（如 +、-、*、/、=、<<、>> 等）能够作用于自定义的类对象，就像它们作用于基本类型一样。例如，你可以定义两个复数对象相加，用 c3 = c1 + c2 这样的表达式，而不必调用类似 c3 = c1.add(c2) 的函数。

**为什么需要运算符重载？**

- 提高代码可读性：使用运算符比调用成员函数更自然、更简洁。
- 使自定义类型更接近内置类型：例如，你定义的复数类、矩阵类等，可以像 int 一样进行算术运算。
2. 运算符重载的基本语法

运算符重载通过定义特殊的函数来实现，函数名由关键字 operator 后跟要重载的运算符组成。

一般形式：
```cpp
返回类型 operator 运算符 (参数列表) {
    // 函数体
}
```
例如，重载 + 运算符的声明：

```cpp
Complex operator+(const Complex& other) const;
```
**3. 哪些运算符可以重载？**

C++ 中大部分运算符都可以重载，**除了以下几个：**
- 成员访问运算符 .
- 成员指针访问运算符 .*
- 作用域解析运算符 ::
- 条件运算符 ?:
- sizeof 运算符
- typeid 运算符
此外，还有一些运算符虽然可以重载，但有特殊限制，比如赋值运算符 =、下标运算符 []、函数调用运算符 ()、成员访问箭头 -> 必须重载为成员函数。

**重载运算符时需要注意：**

- 不能改变运算符的优先级和结合性。
- 不能改变操作数的个数（例如，不能将 + 重载为需要三个操作数）。
- 不能发明新的运算符，只能重载已有的。
- 至少有一个操作数是用户定义类型，这是为了防止重载内置类型的运算符。
**4. 运算符重载的两种方式**

运算符可以重载为成员函数或非成员函数（通常是友元函数）。选择哪种方式取决于具体需求。

4.1 作为成员函数重载

特点：左操作数必须是当前类的对象（或者是对该对象的引用）。因为成员函数通过 this 指针隐式地访问左操作数。
语法：成员函数只有一个参数（对于二元运算符），左操作数是当前对象。
示例（重载 +）：

```cpp
class Complex {
    double real, imag;
public:
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }
};
```
调用时：c1 + c2 被解释为 c1.operator+(c2)。

4.2 作为非成员函数重载

特点：所有操作数都通过参数传递，通常需要声明为友元，以便访问私有成员。
适用场景：当左操作数不是当前类的对象时，比如重载 << 输出运算符，左操作数是 ostream&，必须是非成员函数。
示例（重载 <<）：

```cpp
class Complex {
    // ...
    friend ostream& operator<<(ostream& os, const Complex& c);
};
ostream& operator<<(ostream& os, const Complex& c) {
    os << c.real << "+" << c.imag << "i";
    return os;
}
```
5. 常用运算符重载示例

5.1 算术运算符（+、-、*、/）

通常定义为成员函数或非成员函数，返回新对象（不修改原对象）。一般用 const 修饰，因为不会改变操作数。

```cpp
class Complex {
public:
    Complex operator+(const Complex& other) const;
    Complex operator-(const Complex& other) const;
    // 如果是成员函数，二元运算符有一个参数
};
```
5.2 赋值运算符（=）

必须重载为成员函数。通常需要处理自赋值，并返回 *this 的引用以实现连续赋值。

```cpp
class MyString {
    char* data;
public:
    MyString& operator=(const MyString& other) {
        if (this != &other) {          // 自赋值检查
            delete[] data;
            data = new char[strlen(other.data) + 1];
            strcpy(data, other.data);
        }
        return *this;
    }
};
```
5.3 复合赋值运算符（+=、-= 等）

通常重载为成员函数，返回引用，因为会修改左操作数。

```cpp
Complex& operator+=(const Complex& other) {
    real += other.real;
    imag += other.imag;
    return *this;
}
```
5.4 自增/自减运算符（++、--）

需要区分前置和后置。前置返回引用，后置返回临时对象（并接受一个 int 占位参数）。

```cpp
class Counter {
    int value;
public:
    Counter& operator++() {      // 前置 ++
        ++value;
        return *this;
    }
    Counter operator++(int) {    // 后置 ++，int 参数只是占位
        Counter temp = *this;
        ++value;
        return temp;
    }
};
```
5.5 关系运算符（==、!=、< 等）

通常返回 bool，可以定义为成员或非成员。

```cpp
bool operator==(const Complex& other) const {
    return (real == other.real && imag == other.imag);
}
```
5.6 下标运算符（[]）

必须重载为成员函数，通常返回引用，以便可以修改元素。

```cpp
class MyArray {
    int arr[10];
public:
    int& operator[](int index) {
        return arr[index];
    }
    const int& operator[](int index) const {  // 常量版本
        return arr[index];
    }
};
```
5.7 函数调用运算符（()）

必须重载为成员函数，允许对象像函数一样使用（仿函数）。

```cpp
class Less {
public:
    bool operator()(int a, int b) const {
        return a < b;
    }
};
Less less;
if (less(3, 5)) { ... }
```
5.8 类型转换运算符

允许将类对象隐式或显式转换为其他类型。

```cpp
class Fraction {
    int num, den;
public:
    operator double() const {      // 转换为 double
        return double(num) / den;
    }
};
Fraction f(3, 4);
double d = f;  // 隐式调用 operator double()
```
**6. 注意事项和最佳实践**

- 保持语义一致：重载的运算符应该符合直觉，比如 + 应该做加法，而不是减法。
- 尽量少的破坏封装：优先使用成员函数重载，但必要时（如 <<）使用友元。
- 处理自赋值：重载赋值运算符时必须检查自赋值。

返回类型：

- 赋值运算符和复合赋值运算符返回引用。
- 算术运算符通常返回新对象（值）。
- 比较运算符返回 bool。
- << 和 >> 返回流引用。
常量正确性：如果函数不修改对象，应声明为 const。
考虑对称性：例如 + 如果定义为成员函数，可能无法处理左操作数是其他类型的情况（如 int + Complex），此时可以定义为非成员函数。
1. 完整示例：复数类

```cpp
#include <iostream>
using namespace std;

class Complex {
private:
    double real, imag;
public:
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}

    // 成员函数重载 +
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }

    // 成员函数重载 +=
    Complex& operator+=(const Complex& other) {
        real += other.real;
        imag += other.imag;
        return *this;
    }

    // 前置 ++
    Complex& operator++() {
        ++real;
        return *this;
    }

    // 后置 ++
    Complex operator++(int) {
        Complex temp = *this;
        ++real;
        return temp;
    }

    // 友元函数重载 <<
    friend ostream& operator<<(ostream& os, const Complex& c);
};

ostream& operator<<(ostream& os, const Complex& c) {
    os << c.real << "+" << c.imag << "i";
    return os;
}

int main() {
    Complex c1(1, 2), c2(3, 4);
    Complex c3 = c1 + c2;          // 调用 operator+
    cout << c3 << endl;             // 输出 4+6i

    c1 += c2;                       // 调用 operator+=
    cout << c1 << endl;              // 输出 4+6i

    ++c1;                            // 前置++
    cout << c1 << endl;              // 输出 5+6i

    c2++;                            // 后置++
    cout << c2 << endl;              // 输出 3+4i（原始值），之后 c2 变为 4+4i
    cout << c2 << endl;              // 输出 4+4i
    return 0;
}
```
8. 总结

- 运算符重载让自定义类型使用起来更自然。
- 重载函数名为 operator@。
- 可以重载为成员函数或非成员函数，各有适用场景。
- 必须遵守基本规则（不能改变优先级、操作数个数等）。
- 常用运算符重载包括算术、赋值、关系、下标、函数调用、类型转换等。
- 注意自赋值、常量正确性和返回类型的选择。
