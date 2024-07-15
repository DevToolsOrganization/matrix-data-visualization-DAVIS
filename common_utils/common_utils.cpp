#include "common_utils.h"
#include "common_constants.h"

//#START_GRAB_TO_INCLUDES_LIST
#include <fstream>
#include <iostream>
#include <sstream>
#include <sys/stat.h>
#include <ctype.h>
#include <limits.h>
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

inline bool is_file_exists(const string& file_name) {
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

void sleepMs(unsigned long milisec) {
#ifdef _WIN32
  Sleep(milisec);
#elif __linux__
  usleep(milisec * 1000);
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

bool getDataFromFile(const string& path, string& result) {

  //TODO different scenarious and sanitizing
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
      result.append(temp).append(";");
    }
  } else {
    return false;
  }
  return true;
}

bool readMatrix(vector<vector<double>>& outMatrix, const std::string& path, char dlmtr) {
  outMatrix.clear();
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
//#STOP_GRAB_TO_DVS_NAMESPACE
}; // namespace dvs
