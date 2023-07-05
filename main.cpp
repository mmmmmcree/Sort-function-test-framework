#include "Sorts.h"
#include "TestObject.h"
#include "ParallelSort.h"
#include "CompareStrategy.h"


int main() {
    TestObject testor;
    std::vector<std::string> str_data{"enter", "number", "size", "begin", "of", "cat", "case", "program", "certain", "a", "cake", "side"};
    std::vector<const char*> c_str_data = {"enter", "number", "size", "begin", "of", "cat", "case", "program", "certain", "a", "cake", "side"};
    // testor.visible_test<std::vector<std::string>, std::greater<std::string>, BubbleSort, QuickSort>(str_data);
    // testor.visible_test<std::vector<const char*>, std::less<const char*>, BubbleSort, CombSort>(c_str_data);
    testor.correctness_test<ParallelSort<IntroSort>, QuickSort, ParallelSort<CombSort>>();
    // testor.suitable_category_test<MergeSort, InterativeMergeSort, QuickSort, IntroSort>();
    // testor.performance_test<ParallelSort<IntroSort>, ParallelIntroSort, IntroSort>();
    // testor.write_to_file();
    // system("pause");
}

