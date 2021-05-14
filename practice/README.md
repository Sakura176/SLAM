# 视觉SLAM十四讲练习
## C++新特性(问题3)
1. 更方便的列表初始化
   C++11前只有数组能使用初始化列表。而C++11后大部分类型都可以初始化列表，比较方便。如下所示：
   ```C++
   double b = double{ 12.12 };
   int arr[3]{1, 2, 3};
   vecter<int> iv{1, 2, 3};
   map<int, string>{{1, "a"}, {2, "b"}};
   string str{"Hello World"};

   // new
   int* a = new int { 3 };
   int* arr = new int[] {1, 2, 3};
   ```
2. 自动类型推导
   C++11中引入了auto，可以用来进行自动类型推导，不用关心数据类型，编译器会帮助你推导好，而且这种方式也不影响编译速度。
   ```C++
   for (vector<int>::const_iterator itr = vec.cbegin(); itr != vec.cend(); ++itr)

   // 由于 cbegin() 将返回 vector<int>::const_iterator
   // 所以 itr 也应该是 vector<int>::const_iterator 类型
   for (auto itr = vec.cbegin(); itr != vec.cend(); ++itr);
   ```
   `注意:`auto不能代表一个实际的类型声明，auto声明的变量必须马上初始化
   ```C++
   auto x = 5;
   auto pi = new auto(1);      // 正确，pi是int*
   const auto* v = &x, u = 6; // 正确，v是const int*类型，u是const int
   static auto y = 0.0;      // 正确，y是double类型
   auto int r;              // 错误，auto不再表示存储类型的指示符
   auto s;                 // 错误，auto无法推导出s的类型（必须马上初始化）
   ```
3. 简洁舒服的循环体
   for循环是使用频率非常高的循环方式，在新特性里不需要再像以前那样每次都使用自增或者自减的方式来索引了，结合前面介绍的auto，我们可以极大简化循环方式。
   ```C++
   int arr[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
   for (int i = 0; i < 10; i++)
        cout << arr[i];
   
   int arr[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
   for (auto n : arr)
        std::cout << n;

   map<string, int> m{{"a", 1}, {"b", 2}, {"c", 3}};
   for (auto p : m)
   {
       cout << p.first << " : " << p.second << endl;
   }
   ```
4. 简洁的lambda表达式
   lambda表达式可以使得编程非常简洁，尤其适用于简单的函数，一般形式如下：  
   \[函数对象参数\]\(操作符重载函数参数\)->返回值类型{函数体}
   ```C++
   // []中传入的b是全局变量
   for_each(iv.begin(), iv.end(), [b](int &x){cout <<(x + b) << endl;});

   // []中传入=，表示可以取得所有的外部变量
   for_each(iv.begin(), iv.end(), [=](int &x){x *= (a + b);});

   // ->后加上的是lambda表达式返回值的类型，下面返回了int类型变量
   for_each(iv.begin(), iv.end(), [=](int &x)->int{return x * (a + b);});
   ```
5. 随心所欲可变长的参数模板
   在Python和MATLAB中可以非常方便的使用可以变长的参数，C++11以后引入了tuple，可以实现类似功能，并且可以传入多个不同类型的数据，如下：
   ```C++
   // 支持多种不同类型数据
   auto tup1 = std::make_tuple("Hello World!", 'a', 3.14, 0);

   // 方便拆分
   auto tup1 = std::make_tuple(3.14, 1, 'a');
   double a; int b; char c;
   std::tie(a, b, c) = tup1;
   // 结果是a = 3.14, b = 1, c = 'a';

   // 方便链接
   std::tuple<float, string> tup1(3.14, "pi");
   std::tuple<int, char> tup2(10, 'a');
   auto tup3 = tuple_cat(tup1, tup2);
   ```

+ 练习题
请使用C++新特性改写以下函数。该函数功能：将一组无序的坐标按照“z”字形排序，并输出。

+ 本程序学习目标：  
熟悉C++新特性（简化循环、自动类型推导、列表初始化、lambda函数）

+ 题目：
  ```C++
  bool cmp(Point2i pt1, Point2i pt2)
  {
      // --- 开始你的代码 ----//

      // --- 结束你的代码 ----//
  }

  int main()
  {
      vector<Point2i> vec;
      vec.push_back(Point2i(2, 1));
      vec.push_back(Point2i(3, 3));
      vec.push_back(Point2i(2, 3));
      vec.push_back(Point2i(3, 2));
      vec.push_back(Point2i(3, 1));
      vec.push_back(Point2i(1, 3));
      vec.push_back(Point2i(1, 1));
      vec.push_back(Point2i(2, 2));
      vec.push_back(Point2i(1, 2));

      cout << "Before sort: " << endl;
      for (int i = 0; i < vec.size(); i++)
      {
          cout << vec[i] << endl;
      }

      sort(vec.begin(), vec.end(), cmp);

      cout << "Before sort: " << endl;
      for (int i = 0; i < vec.size(); i++)
      {
          cout << vec[i] << endl;
      }

      return 0;
  }
  ```

## 齐次坐标

### 什么是齐次坐标
简单的说：齐次坐标就是在原有坐标上加一个维度：
$$
(x,y) \rightarrow (x, y, 1)\\
(x,y,z) \rightarrow (x,y,z,1)
$$
  1. 能非常方便的表达点在直线或平面上
  2. 方便表达直线与直线，平面与平面的交点
  3. 能够区分一个向量和一个点
  4. 能够表达无穷远
  5. 更简洁的表达欧氏空间变换