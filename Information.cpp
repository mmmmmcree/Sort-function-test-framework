#include "Information.h"

PerforamanceInfo::PerforamanceInfo( 
    const std::string& distribute_t,
    const std::string& value_t,
    long long scale
) :
    distribute_type(distribute_t),
    value_type(value_t),
    data_scale(scale),
    runtime(-1),
    compare_assign_times(std::make_pair(-1, -1))
{

}

SortFunctionInfo::SortFunctionInfo() :
    is_correct(false),
    suitable_iterator_category(IteratorCategory::UnknownOrBad),
    performance_info_container()
{
    performance_info_container.reserve(30);
}

