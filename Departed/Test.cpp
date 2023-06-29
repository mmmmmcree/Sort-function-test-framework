#include "Test.h"

Test::Test():
    _sort_function_container(),
    _getable(false)
{
}

void Test::get_runtime() {
    if(!_getable) {
        std::cerr << "You cannot get the running time before you set data." << std::endl;
        std::cerr << "If you have passed data or have had gotten the running time, you should set data again." << std::endl;
        return;
    }
    for (auto& item : _sort_function_container) {
        Timer timer(item.second.runtime);
        item.second.sort_function();
    }
    _getable = false;
}

std::map<std::string, Information> Test::pass_information() {
    if (_sort_function_container.empty()) {
        std::cerr << "No information to pass" << std::endl;
        throw "No information to pass";
    }
    for (auto& item : _sort_function_container) {
        item.second.sort_function = nullptr;
    }
    return _sort_function_container;
}