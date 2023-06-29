#include "TestObject.h"

std::map<std::string, std::shared_ptr<SortFunctionInfo>>
TestObject::info_map = std::map<std::string, std::shared_ptr<SortFunctionInfo>>();

void TestObject::write_to_file() {
    InfoProcessor::write_info_to_file(info_map);
}