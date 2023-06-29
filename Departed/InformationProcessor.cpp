#include "InformationProcessor.h"

InformationProcessor::InformationProcessor(std::map<std::string, Information>&& info_map):
     _information_map(info_map)
{

}

void InformationProcessor::print_information() {
    for (auto& item : _information_map) {
        std::cout << "{\n\tsort fuction: " << item.first << std::endl;
        std::cout << "\tdata distribution type: " << item.second.distribute_type << std::endl;
        std::cout << "\tdata container type: " << item.second.container_type << std::endl;
        std::cout << "\tvalue type: " << item.second.value_type << std::endl;
        std::cout << "\tdata scale: " << item.second.data_scale << std::endl;
        std::cout << "\trunning time(microseconds): " << item.second.runtime << "\n}" << std::endl;
    }
}