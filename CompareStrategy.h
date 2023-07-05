#ifndef COMPARESTRATEGY_H
#define COMPARESTRATEGY_H
#include <functional>
#include <cstring>
#include "Score.h"

template<>
struct std::less<const char*> {
    bool operator()(const char* lhs, const char* rhs) const {
        return std::strcmp(lhs, rhs) < 0;
    }
};

template<>
struct std::greater<const char*> {
    bool operator()(const char* lhs, const char* rhs) const {
        return !std::less<const char*>()(lhs, rhs);
    }
};

template<>
struct std::less<score::Chinese> {
    bool operator()(const StudentScoreInfo& lhs, const StudentScoreInfo& rhs) const {
        return std::get<score::Chinese>(lhs.second).score < std::get<score::Chinese>(rhs.second).score;
    }
};

template<>
struct std::greater<score::Chinese> {
    bool operator()(const StudentScoreInfo& lhs, const StudentScoreInfo& rhs) const {
        return !std::less<score::Chinese>()(lhs, rhs);
    }
};

template<>
struct std::less<score::Math> {
    bool operator()(const StudentScoreInfo& lhs, const StudentScoreInfo& rhs) const {
        return std::get<score::Math>(lhs.second).score < std::get<score::Math>(rhs.second).score;
    }
};

template<>
struct std::greater<score::Math> {
    bool operator()(const StudentScoreInfo& lhs, const StudentScoreInfo& rhs) const {
        return !std::less<score::Math>()(lhs, rhs);
    }
};

template<>
struct std::less<score::Science> {
    bool operator()(const StudentScoreInfo& lhs, const StudentScoreInfo& rhs) const {
        return std::get<score::Science>(lhs.second).score < std::get<score::Science>(rhs.second).score;
    }
};

template<>
struct std::greater<score::Science> {
    bool operator()(const StudentScoreInfo& lhs, const StudentScoreInfo& rhs) const {
        return !std::less<score::Science>()(lhs, rhs);
    }
};

#endif