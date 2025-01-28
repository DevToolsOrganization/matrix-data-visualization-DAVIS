#include "common_utils.h"
#include "common_constants.h"
//#START_GRAB_TO_INCLUDES_LIST
#include <fstream>
#include <iostream>
#include <sstream>
#include <sys/stat.h>
#include <ctype.h>
#include <limits.h>
#include <set>
#include <clocale>
#include <cmath>
#include <math.h>
#include <random>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <thread>
//#STOP_GRAB_TO_INCLUDES_LIST

namespace dvs {
//#START_GRAB_TO_DVS_NAMESPACE
using std::string;

#ifdef _WIN32
  #include <direct.h>
  #include <windows.h>
  #define getcwd _getcwd // stupid MSFT "deprecation" warning
#elif __linux__
  #include <unistd.h>
#endif

bool is_file_exists(const string& file_name) {
  std::ifstream file(file_name.c_str());
  if (!file) {
    return false;
  }
  return true;
}

void openFileBySystem(const string& file_name) {
  string command;
#ifdef _WIN32
  command = "start ";
#elif __APPLE__
  command = "open ";
#elif __linux__
  command = "xdg-open ";
#else
#error "Unknown compiler"
#endif
  command.append(file_name);
  std::ignore = system(command.c_str());
}

string getCurrentPath() {
#if defined (_WIN32) || (__linux__)
  char buffer[1024];
  char* answer = getcwd(buffer, sizeof(buffer));
  string s_cwd;
  if (answer) {
    s_cwd = answer;
  }
  return s_cwd;
#elif __APPLE__
  //TODO macos get current path implementation
  return "";
#endif
}

bool isPlotlyScriptExists() {
  return is_file_exists(kPlotlyJsWorkPath);
}

bool saveStringToFile(const string& file_name,
                      const string& data) {
  std::ofstream out(file_name);
  if (out.is_open()) {
    out << data.c_str();
    out.close();
    return true;
  }
  return false;
}


void openPlotlyHtml(const string& file_name) {
  openFileBySystem(file_name);
}

void sleepMicroSec(unsigned long microsec) {
#ifdef _WIN32
  std::this_thread::sleep_for(std::chrono::microseconds(microsec));
#elif __linux__
  usleep(microsec);
#endif
}

void mayBeCreateJsWorkingFolder() {
  struct stat sb;
  if (stat(kOutFolderName, &sb) != 0) {
#ifdef _WIN32
    _mkdir(kOutFolderName);
#elif __linux__
    mode_t mode = 0755;
    mkdir(kOutFolderName, mode);
#endif
  }
}

bool deleteFolder(const char* fname) {
  struct stat sb;
  if (stat(fname, &sb) == 0) {
    //rmdir(fname);
    return true;
  } else {
    return false;
  }
}

bool get_data_from_file(const string& path,
                        vector<string>& result) {

  //TODO different scenarious and sanitizing
  std::setlocale(LC_ALL, "ru_RU.UTF-8");
  if (!is_file_exists(path)) {
    return false;
  }
  if (!result.empty()) {
    result.clear();
  }
  std::fstream file;
  file.open(path, std::ios::in);
  if (file.is_open()) {
    string temp;
    while (std::getline(file, temp)) {
      result.emplace_back(temp);
    }
  } else {
    return false;
  }
  return true;
}

bool readMatrix(vector<vector<double>>& outMatrix, const std::string& path, char dlmtr) {
  outMatrix.clear();
  std::setlocale(LC_ALL, "ru_RU.UTF-8");
  std::ifstream ifs;
  std::string str;
  ifs.open(path, std::ios::in);
  if (ifs) {
    while (!ifs.eof()) {
      std::getline(ifs, str);
      if (str.size() == 0) //if exist empty line
        continue;
      std::vector<std::string> parts = split(str, dlmtr);
      vector<double> doubleLine;
      doubleLine.resize(parts.size());
      for (size_t i = 0; i < parts.size(); ++i) {
        doubleLine[i] = std::stod(parts.at(i));
      }
      outMatrix.push_back(doubleLine);
    }
    ifs.close();
    return true;
  } else {
    std:: cout << "Unable to open file to read: " << path << std::endl;
    return false;
  }
}

vector<string> split(const string& target, char c) {
  std::string temp;
  std::stringstream stringstream { target };
  std::vector<std::string> result;
  while (std::getline(stringstream, temp, c)) {
    result.push_back(temp);
  }

  return result;
}

bool make_string(const string& src,
                 const vector<string>& args,
                 string& out) {
  if (!out.empty()) {
    out.clear();
  }
  if (args.empty()) {
    return false;
  }
  vector<vector<size_t>> road_map;
  size_t reserve_size = 0;
  size_t pos = 0;
  while (pos < src.size()) {
    size_t new_pos = src.find('%', pos);
    if (new_pos == string::npos) {
      //out.append(src.substr(pos, src.size() - pos));
      reserve_size += (src.size() - pos);
      road_map.push_back({pos, src.size() - pos});
      break;
    };
    std::string arg_index;
    size_t temp_pos = 0;
    temp_pos = new_pos;
    while (temp_pos < src.size() && isdigit(src[++temp_pos])) {
      arg_index += src[temp_pos];
    }
    //string part = src.substr(pos, new_pos - pos);
    road_map.push_back({pos, new_pos - pos});
    reserve_size += (new_pos - pos);
    if (!arg_index.empty()) {
      size_t index = std::stol(arg_index);
      if (index > 0 && index <= args.size()) {
        //part.append(args[index - 1]);
        reserve_size += args[index - 1].size();
        road_map.push_back({index - 1});
      } else {
        //TODO return false or continue
      }
    } else {
      //part.append("%");
      road_map.push_back({UINT_MAX});
      ++reserve_size;
    }
    //out.append(part);
    pos = temp_pos;
  }
  // create out according on the road map
  out.reserve(reserve_size);
  for (size_t i = 0; i < road_map.size(); ++i) {
    auto size = road_map[i].size();
    if (size == 2) {
      out.append(src.substr(road_map[i][0], road_map[i][1]));
    } else if (size == 1) {
      if (road_map[i][0] == UINT_MAX) {
        out.append("%");
      } else {
        out.append(args[road_map[i][0]]);
      }
    }
  }
  //std::cout<<"\n\n"<<reserve_size<<"<-->"<<out.size();
  return true;
}

int find_separator(const std::string& src,
                   char& separator) {
  std::vector<char> ignored_chars = {'+', '-', 'e', 'E', '.', '\r', ','};
  std::set<char> unique_chars;
  bool is_service_char = false;
  bool is_dot_present = false;
  bool is_comma_present = false;
  size_t comma_counter = 0;
  size_t dot_counter = 0;

  for (size_t i = 0; i < src.size(); ++i) {

    if (isdigit((unsigned char)src[i]))
      continue;
    is_service_char = false;

    if (src[i] == '.') {
      is_dot_present = true;
      ++dot_counter;
    } else if (src[i] == ',') {
      is_comma_present = true;
      ++comma_counter;
    }

    for (size_t j = 0; j < ignored_chars.size(); ++j) {
      if (src[i] == ignored_chars[j]) {
        is_service_char = true;
        break;
      }
    }
    if (is_service_char)
      continue;
    unique_chars.insert(src[i]);
  }
  if (unique_chars.size() == 1 && is_comma_present == false) {
    separator = *unique_chars.begin();
    return GOOD_SEPARATOR;
  } else if (unique_chars.size() == 1 && is_comma_present == true) {
    if (is_dot_present) {
      separator = ',';
      return MABE_COMMA_MABE_DOT;
    }
    separator = *unique_chars.begin();
    return GOOD_SEPARATOR;
  } else if (unique_chars.size() == 0) {
    return NO_SEPARATOR;
  } else if (unique_chars.size() > 1) {
    return MORE_THAN_ONE_SEPARATOR;
  }
  return UNDEFINED_BEHAVIOR;
}

string removeSpecialCharacters(const string& s) {
  string t;
  for (int i = 0; i < s.length(); i++) {
    if (s[i] == ' ') {
      t += '_';
    } else if ((s[i] >= 'a' && s[i] <= 'z')
               || (s[i] >= 'A' && s[i] <= 'Z')
               || (s[i] >= '0' && s[i] <= '9')
               || (s[i] == '-') || (s[i] == '_')) {
      t += s[i];
    }
  }
  return t;
}


bool is_string_convertable_to_digit(const string& sample) {

  try {
    std::ignore = std::stod(sample);
  } catch (const std::invalid_argument& e) {
    return false;
  } catch (const std::out_of_range& e) {
    return false;
  }
  return true;
}

string nullIfNotFinite(double val) {
  string plotlyVar;
  if (isfinite(val)) {
    plotlyVar = std::to_string(val);
    std::replace(plotlyVar.begin(), plotlyVar.end(), ',', '.');
  } else {
    plotlyVar = "null";
  }
  return plotlyVar;
}

string vectorToString(const vector<double>& vec) {
  std::ostringstream oss;
  for (size_t i = 0; i < vec.size(); ++i) {
    if (i != 0) {
      oss << ",";
    }
    oss << vec[i];
  }
  return oss.str();
}

string makeUniqueDavisHtmlName() {
  sleepMicroSec(1);

  auto now = std::chrono::system_clock::now();
  auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
  auto in_time_t = std::chrono::system_clock::to_time_t(now);
  std::stringstream ss;
  ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d_%H_%M_%S");
  ss << '_' << std::setfill('0')
     << std::setw(3)
     << milliseconds.count();
  return ss.str();
}

std::string makeUniqueDavisHtmlRelativePath() {
  string name = makeUniqueDavisHtmlName();
  return std::string("./").append(kOutFolderName).append(name).append(".html");
}


void transponeMatrix(std::vector<std::vector<double> >& matrix) {

  if (matrix.empty())
    return;

  size_t rows = matrix.size();
  size_t cols = matrix[0].size();
  vector<vector<double>> transposed(cols, vector<double>(rows));

  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 0; j < cols; ++j) {
      transposed[j][i] = matrix[i][j];
    }
  }
  matrix = std::move(transposed);
}

vector<double> calculateAverageVector(const vector<vector<double>>& vectors) {

  if (vectors.empty()) {
    throw std::invalid_argument("Input vector of vectors is empty.");
  }

  size_t vectorSize = vectors[0].size();
  for (const auto& vec : vectors) {
    if (vec.size() != vectorSize) {
      throw std::invalid_argument("All vectors must have the same size.");
    }
  }

  std::vector<double> averageVector(vectorSize, 0.0);
  for (const auto& vec : vectors) {
    for (size_t i = 0; i < vectorSize; ++i) {
      averageVector[i] += vec[i];
    }
  }

  for (double& value : averageVector) {
    value /= vectors.size();
  }

  return averageVector;

}


vector<double> calculateStandardDeviation(const vector<double>& mean,
                                          const vector<vector<double>>& data) {

  std::vector<double> stddev(mean.size(), 0.0);
  int n = data.size();
  for (const auto& vec : data) {
    for (size_t i = 0; i < vec.size(); ++i) {
      double diff = vec[i] - mean[i];
      stddev[i] += diff * diff;
    }
  }
  for (size_t i = 0; i < stddev.size(); ++i) {
    stddev[i] = std::sqrt(stddev[i] / n);
  }
  return stddev;
}

std::string reverseString(const std::string& input) {

  std::stringstream ss(input);
  std::string item;
  std::vector<std::string> elements;

  while (std::getline(ss, item, ',')) {
    elements.push_back(item);
  }

  std::reverse(elements.begin(), elements.end());

  std::string result;
  for (size_t i = 0; i < elements.size(); ++i) {
    result += elements[i];
    if (i < elements.size() - 1) {
      result += ',';
    }
  }

  return result;
}


vector<double> doubleAndReverse(const vector<double>& input,
                                const vector<double>& mean) {

  vector<double> result(input.size(), 0);
  vector<double> minus_result = input;
  for (size_t i = 0; i < result.size(); ++i) {
    result[i] += mean[i] + input[i];
    minus_result[i] = mean[i] - input[i];
  }
  vector<double> reversed(minus_result.rbegin(), minus_result.rend());
  result.insert(result.end(), reversed.begin(), reversed.end());
  return result;
}



//#STOP_GRAB_TO_DVS_NAMESPACE
}; // namespace dvs
