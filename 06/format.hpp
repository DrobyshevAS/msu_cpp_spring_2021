#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "exceptions.hpp"

template <class T>
void make_list_of_args(std::ostream& res, int count1, int count2, const T& arg);

template <class T, class... ArgsT>
void make_list_of_args(std::ostream& res, int count1, int count2, const T& arg, const ArgsT&... args);

template <class... ArgsT>
std::string format(std::string str, const ArgsT&... args);

#include "format.tpp"