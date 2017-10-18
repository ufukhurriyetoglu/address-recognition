#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <functional>
#include <regex>
#include <memory>

#include <boost/iostreams/device/mapped_file.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/tokenizer.hpp>

using std::string;
using std::vector;
using std::ifstream;
using std::unique_ptr;
using boost::iostreams::mapped_file_source;
using boost::iostreams::stream;

