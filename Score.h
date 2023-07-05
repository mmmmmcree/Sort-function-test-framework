#ifndef SCORE_H
#define SCORE_H
#include <string>
#include <tuple>
#include <iostream>
#include <fstream>
#include <type_traits>
#include "CompareStrategy.h"

namespace score{
    struct Score {
        Score(float _score) : score(_score) {}
        float score;
    };
    struct Chinese : public Score{
        Chinese(float _score) : Score(_score) {}
    };
    struct Math : public Score{
        Math(float _score) : Score(_score) {}
    };
    struct Science : public Score{
        Science(float _score) : Score(_score) {}
    };
}

using ScoreInfo = std::tuple<score::Chinese, score::Math, score::Science>;
using StudentScoreInfo = std::pair<std::string, std::tuple<score::Chinese, score::Math, score::Science>>;
// using make_info = std::make_pair<std::string, ScoreInfo>;

std::ostream& operator<<(std::ostream& os, const StudentScoreInfo& score_info) {
    os << score_info.first << ": ("
        << "Chinese: " << std::get<0>(score_info.second).score << ", " 
        << "Math: " << std::get<1>(score_info.second).score << ", " 
        << "Science: " << std::get<2>(score_info.second).score << ")";
    return os;
}

std::ofstream& operator<<(std::ofstream& ofs, const StudentScoreInfo& score_info) {
    ofs << score_info.first << ": ("
        << "Chinese: " << std::get<0>(score_info.second).score << ", " 
        << "Math: " << std::get<1>(score_info.second).score << ", " 
        << "Science: " << std::get<2>(score_info.second).score << ")";
    return ofs;    
}

template<typename CurrentFunction, typename... RestFuctions>
void write_student_score_to_file() {
    std::string file_path = "./new release/scores.txt";
    std::ofstream file_writer(file_path, std::iostream::app);
    CurrentFunction sort_function;
    std::vector<StudentScoreInfo> scores_data{
        std::make_pair("1001", ScoreInfo(100, 200, 300)),
        std::make_pair("1002", ScoreInfo(100, 170, 600)),
        std::make_pair("1003", ScoreInfo(300, 300, 600)),
        std::make_pair("1004", ScoreInfo(20, 300, 200)),
        std::make_pair("1005", ScoreInfo(70, 90, 50)),
        std::make_pair("1006", ScoreInfo(140, 30, 800))
    };
    file_writer << CurrentFunction().name << ":\n{" << std::endl;
    sort_function(scores_data.begin(), scores_data.end(), std::less<score::Chinese>());
    file_writer << "        sorted by Chinese score(ascending):\n        {" << std::endl;
    for (auto i : scores_data) {
        file_writer << "\t" << i << std::endl;
    }
    file_writer <<  "        }" << std::endl;
    sort_function(scores_data.begin(), scores_data.end(), std::greater<score::Chinese>());
    file_writer << "        sorted by Chinese score(descending):\n        {" << std::endl;
    for (auto i : scores_data) {
        file_writer << "\t" << i << std::endl;
    }
    file_writer <<  "        }" << std::endl;
    sort_function(scores_data.begin(), scores_data.end(), std::less<score::Math>());
    file_writer << "        sorted by Math score(ascending):\n        {" << std::endl;
    for (auto i : scores_data) {
        file_writer << "\t" << i << std::endl;
    }
    file_writer <<  "        }" << std::endl;
    sort_function(scores_data.begin(), scores_data.end(), std::greater<score::Math>());
    file_writer << "        sorted by Math score(descending):\n        {" << std::endl;
    for (auto i : scores_data) {
        file_writer << "\t" << i << std::endl;
    }
    file_writer <<  "        }" << std::endl;
    sort_function(scores_data.begin(), scores_data.end(), std::less<score::Science>());
    file_writer << "        sorted by Science score(ascending):\n        {" << std::endl;
    for (auto i : scores_data) {
        file_writer << "\t" << i << std::endl;
    }
    file_writer <<  "        }" << std::endl;
    sort_function(scores_data.begin(), scores_data.end(), std::greater<score::Science>());
    file_writer << "        sorted by Science score(descending):\n        {" << std::endl;
    for (auto i : scores_data) {
        file_writer << "\t" << i << std::endl;
    }
    file_writer <<  "        }" << std::endl;
    file_writer <<  "}" << std::endl;
    if constexpr (sizeof...(RestFuctions) > 0) {
        write_student_score_to_file<RestFuctions...>();
    }
}

#endif