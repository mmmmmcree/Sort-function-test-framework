#include "Sorts.h"
#include "TestObject.h"

int main() {
    TestObject testor;
    std::vector<std::string> a{"enter", "number", "size", "begin", "of", "cat", "case", "program", "certain", "a", "cake", "side"};
    testor.visible_test<std::vector<std::string>, std::less<std::string>, BubbleSort, BubbleSort>(a);
    // testor.correctness_test<BubbleSort, IntroSort, DoNothingSort, ShellSort_GOONER>();
    // testor.suitable_category_test<BubbleSort>();
    // testor.performance_test<BubbleSort, IntroSort, ShellSort_GOONER>(); 
    // testor.write_to_file();
    system("pause");
}


