#include "Sorts.h"
#include "TestObject.h"


int main() {
    TestObject testor;
    // testor.correctness_test<BubbleSort, IntroSort, DoNothingSort>();
    // testor.suitable_category_test<BubbleSort>();
    // testor.performance_test<BubbleSort, IntroSort>(); 
    testor.performance_test<ShellSort_GOONER>();
    testor.write_to_file();
    system("pause");
}

