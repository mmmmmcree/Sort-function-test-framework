#include "Sorts.h"
#include "TestObject.h"

int main() {
    TestObject testor;
    testor.visible_test<IntroSort, BubbleSort>();
    testor.correctness_test<BubbleSort, IntroSort, DoNothingSort, ShellSort_GOONER>();
    testor.suitable_category_test<BubbleSort>();
    testor.performance_test<BubbleSort, IntroSort, ShellSort_GOONER>(); 
    testor.write_to_file();
    system("pause");
}


