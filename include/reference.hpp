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
#include <boost/chrono.hpp>

#include "Commons.hpp"

using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::unique_ptr;
using boost::iostreams::mapped_file_source;
using boost::iostreams::mapped_file;
using boost::iostreams::stream;
using address_recognition::logging::logError;