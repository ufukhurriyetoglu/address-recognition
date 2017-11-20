#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <functional>
#include <regex>
#include <memory>

#include <boost/chrono.hpp>

#include "Commons.hpp"

using std::string;
using std::wstring;
using std::vector;
using std::wifstream;
using std::wofstream;
using std::unique_ptr;
using std::shared_ptr;
using address_recognition::logging::logError;
using address_recognition::logging::logInfo;
using address_recognition::logging::logInfoLn;
