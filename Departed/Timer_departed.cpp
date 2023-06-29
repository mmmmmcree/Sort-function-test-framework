/*

Timer::Timer(func_list sort_functions, str_list sort_function_names):
     _sort_functions(sort_functions),
     _sort_function_names(sort_function_names),
     _runtime_container()
{
    _runtime_container.reserve(30);
}

void Timer::get_runtime() {
    for (const auto& sort_function : _sort_functions) {
        auto start_time = std::chrono::steady_clock::now();
        sort_function();
        auto end_time = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
        _runtime_container.emplace_back(duration.count());
    }
}

void Timer::show_runtime() const {
    auto size = _runtime_container.size();
    for (int i = 0; i < size; ++i) {
        std::cout << "The running time of sort fuction " << _sort_function_names[i] << " is: " 
                       << _runtime_container[i] << " microseconds" << std::endl;
    }
}

*/