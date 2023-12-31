#include "InfoProcessor.h"

void InfoProcessor::print_correctnees(const std::string& name, bool is_correct) {
    std::cout << "Sort function " << name;
    if(is_correct) {
        std::cout << " is correct, capable of moving on to the next step..." << std::endl;
    } else {
        std::cout << " is incorrect , it might not operate the following steps.." << std::endl;
    }
}

std::string get_category_aux(short category) {
    std::string result;
    switch(category) {
        case 0 : result =  "unkown or bad"; break;
        case 1 : result = "forward iterator"; break;
        case 2 : result = "bidirectional iterator"; break;
        case 3 : result = "random access iterator"; break;
    }
    return result;
}

void InfoProcessor::print_category(const std::string& name, short category) {
    std::cout << "Sort function " << name << " is suitable for: ";
    std::cout << get_category_aux(category) << std::endl;
}

void InfoProcessor::print_performance_info(const std::string& name, const PInfoContainer& p_info_container) {
    std::cout << name << " performance test: {" << std::endl;
    for (const auto& item : p_info_container) {
        std::cout << std::endl;
        std::cout << "\tdata distribution type: " << item.distribute_type << std::endl;
        std::cout << "\tvalue type: " << item.value_type << std::endl;
        std::cout << "\tdata scale: " << item.data_scale << std::endl;
        std::cout << "\trunning time(microseconds): " << item.runtime 
                       << "(" << item.compare_assign_times.first << ", "
                       << item.compare_assign_times.second << ")" << std::endl;
    }
    std::cout << "}" << std::endl;
}

std::string current_time_string() {
    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&now_c), "%Y-%m-%d-%H-%M-%S");
    return ss.str();
}

void InfoProcessor::write_info_to_file(std::map<std::string, InfoPointer>& info_map) {
    std::string file_path = "./new release/" + current_time_string() + ".txt";
    std::ofstream file_writer(file_path, std::iostream::out);
    
    file_writer << "The time when the data was written" << std::endl
                      << current_time_string() << std::endl;
    file_writer << std::endl;
    
    for (const auto& item : info_map) {
        auto& sort_function_info_ptr = item.second;
        auto& p_info_container = sort_function_info_ptr->performance_info_container;
        bool is_correct = sort_function_info_ptr->is_correct;
        SortFunctionInfo::IteratorCategory suitable_iterator_category = sort_function_info_ptr->suitable_iterator_category;
        
        file_writer << item.first << " performance test" << std::endl;
        file_writer << "iterator category: " << get_category_aux(static_cast<short>(suitable_iterator_category)) << "\t"
                          << "is correct: " << std::boolalpha << is_correct << std::endl;
        
        if (p_info_container.size() > 0) {
            file_writer << "data scale\t";
            for (int i = 0; i < NUMBER_OF_DISTRIBUTION; ++i) {
                file_writer << p_info_container[i].distribute_type << "<" << p_info_container[i].value_type << ">(microseconds)\t";
            }
        }
        for (auto iter = p_info_container.begin(), end = p_info_container.end(); iter != end; iter += NUMBER_OF_DISTRIBUTION) {
            file_writer << std::endl;
            file_writer << iter->data_scale << "\t";
            for (auto iter_2 = iter, end = iter + NUMBER_OF_DISTRIBUTION; iter_2 != end; ++iter_2) {
                file_writer << iter_2->runtime 
                                   << "(" << iter_2->compare_assign_times.first << ", "
                                   << iter_2->compare_assign_times.second << ")" << "\t";
            }
        }
        file_writer << std::endl << std::endl;
    }
    file_writer.close();
}