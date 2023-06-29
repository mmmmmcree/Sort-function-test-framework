#ifndef INFORMATIONPROCESSOR_H
#define INFORMATIONPROCESSOR_H
#include <map>
#include <string>
#include <iostream>
#include "Information.h"

class InformationProcessor {
public:
    InformationProcessor(std::map<std::string, Information>&&);
    void print_information();
private:
    std::map<std::string, Information> _information_map;
};

#endif