## 框架介绍

### 设计思路

C++标准程序库中算法、策略与容器分离的思想是设计模式与泛型编程的结晶。本框架参考C++标准程序库的设计方式架构，采取统一接口。所有排序接口均与std::sort相同，可以对不同的数据类型排序，可以对不同容器中的数据排序，可以使用不同策略来比较元素。同样的，数据生成器**DataGenerator类**也采用类似设计模式，可以生成不同数据类型、不同数据规模、不同数据分布的数据，并且可以指定容纳数据的容器。计时工作由**Timer类**完成；所有测试均由**TestObject类**完成；测试数据由**SortFunctionInfo类**存储；所有信息打印、写入文件等工作都由**InfoProcessor类**完成。其中，**TestObejct类**可以测试排序正确性，排序适用迭代器，以及对不同数据的排序性能(由运行时间、比较次数、赋值次数体现)。由于迭代器测试是在编译期间完成，无法在运行期间捕获，故该功能在测试时暂时不予以考虑。**TestObject类**开放的测试接口均采用模板元编程技巧，可以传入任意数量的函数对象来进行测试，极大增强了测试便捷性。

### 运用的编程技巧

- 面向对象编程
- 设计模式
- C++标准程序库设计
- 泛型编程
- 模板元编程

### 特点

- 便于使用
- 与C++标准程序库兼容
- 关注点分离，便于维护和拓展

### 对象设计与接口设计

- ```C++
  // 用于记录信息的两个类
  /*PerforamanceInfo用于记录性能测试时的信息*/
  struct PerforamanceInfo {
      PerforamanceInfo(const std::string&, const std::string&, long long);
      std::string distribute_type; // 记录用于测试的数据分布类型
      std::string value_type; // 记录用于测试的数据类型
      long long data_scale; // 记录数据规模
      long long runtime; // 记录数据运行时间
      std::pair<long long, long long> compare_assign_times; // 记录比较次数和赋值次数
  };
  /*SortFunctionInfo用于有关排序的所有信息*/
  struct SortFunctionInfo {
      SortFunctionInfo();
      enum class IteratorCategory {
          UnknownOrBad,
          ForwardIterator,
          BidirectionalIterator,
          RandomAccessIterator
      };
      bool is_correct; // 记录排序是否正确
      IteratorCategory suitable_iterator_category; // 记录排序支持的迭代器类型
      std::vector<PerforamanceInfo> performance_info_container; // 收集性能测试信息的容器
  };
  ```

- ```C++
  //  计时器，利用对象的构造与析构计时并记录
  class Timer {
  public:
      Timer(long long&);
      ~Timer();
      Timer() = delete;
      Timer(const Timer&) = delete;
      Timer& operator=(const Timer&) = delete;
  private:
      long long& _runtime_information; // 按引用传递修改PerforamanceInfo中的runtime成员变量
      std::chrono::steady_clock::time_point _start_time; // 构造时记录开始时间
  };
  ```

- ```C++
  //  数据生成器
  template<template<typename> typename Container = std::vector> // 类模板的模板，用于指定任意容器
  class DataGenerator {
  public:
      DataGenerator();
      long long get_data_scale() const; // 输出当前数据的规模
      void set_data_scale(long long); // 用于设置数据规模
      Container<int> get_reversed_data(); // 由于完全逆序数据分布的特殊性，单独设置一个只输出整形逆序数据分布的成员函数
      template<typename DistributionType = std::uniform_int_distribution<int>>
      Container<typename DistributionType::result_type> get_data(); // 模板成员函数，用于生成任意分布、任意类型的数据
  private:
      long long _data_scale; // 记录当前数据规模
  };
  ```

- ```C++
  // 数据处理类
  class InfoProcessor {
      using PInfoContainer = typename std::vector<PerforamanceInfo>;
      using InfoPointer = typename std::shared_ptr<SortFunctionInfo>;
  public:
      template<typename CurrentFunction>
      void print_data_for_visible_test(const std::string& name, const CurrentFunction&, bool); // 排序前后数据展示
      static void print_correctnees(const std::string&, bool); // 排序正确性展示
      static void print_category(const std::string&, short); // 排序适用迭代器展示
      static void print_performance_info(const std::string&, const PInfoContainer&); // 排序性能展示
      static void write_info_to_file(std::map<std::string, InfoPointer>&); // 将排序的各种信息写入文件
  private:
      static const int NUMBER_OF_DISTRIBUTION = 4; // 记录当前使用的数据分布个数，用于写入文件时的排版
  };
  ```

- ```C++
  // 测试类
  class TestObject {
      friend InfoProcessor; // 方便InfoProcessor访问信息
      using InfoPointer = typename std::shared_ptr<SortFunctionInfo>;
  public:
      TestObject() =default;
      template<typename DataType, typename CompareFunctor, typename CurrentFunction, typename... RestFuctions>
      void visible_test(DataType); // 用于排序前后结果可视化，并测试是否可以使用策略
      template<typename CurrentFunction, typename... RestFuctions>
      bool correctness_test(); // 正确性测试
      template<typename CurrentFunction, typename... RestFuctions>
      void suitable_category_test(); // 适用迭代器测试
      template<typename CurrentFunction, typename... RestFuctions>
      void performance_test(); // 性能测试测试
      void write_to_file(); // 委托InfoProcessor工作，用户不必知道InfoProcessor的存在
  private:
      template<typename CurrentFunction> void _prepare(); // 测试排序前的准备工作，如把排序名字插入info_map
      static std::map<std::string, InfoPointer> info_map; // 用info_map存储信息，以排序名字为key
  };
  ```

### 运用实例展示

```c++
int main() {
    TestObject testor;
    std::vector<std::string> data{"enter", "number", "size", "begin", "of", "cat", "case", "program", "certain", "a", "cake", "side"};
    testor.visible_test<std::vector<std::string>, std::greater<std::string>, MergeSort, InterativeMergeSort>(data);
    testor.correctness_test<MergeSort, InterativeMergeSort, QuickSort, IntroSort>();
    // testor.suitable_category_test<IntroSort>();
    testor.performance_test<MergeSort, InterativeMergeSort, QuickSort, IntroSort>();
    testor.write_to_file();
}
```

