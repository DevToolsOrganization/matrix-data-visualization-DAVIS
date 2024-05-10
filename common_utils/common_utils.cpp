#include "common_utils.h"
#include "common_constants.h"

//#START_GRAB_TO_INCLUDES_LIST
#include <fstream>
#include <iostream>
#include <sstream>
#include <sys/stat.h>
//#STOP_GRAB_TO_INCLUDES_LIST

namespace {
//#START_GRAB_TO_NAMESPACE
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
  system(command.c_str());
}
//#STOP_GRAB_TO_NAMESPACE
} // namespace

namespace dvs {
//#START_GRAB_TO_NAMESPACE
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
                 vector<string>& args,
                 string& out) {
  if(!out.empty())out.clear();
  string sep_string;
  int args_size = 0;
  int reserve_size = 0;
  std::map<size_t, string> positions;
  for (size_t i = 0; i < args.size(); ++i) {
    string check = "%" + std::to_string(i + 1);
    auto position = src.find(check);
    if (position == string::npos) {
      std::cout << "arg" << i + 1 << "doesn't exists...";
      return false;
    }
    positions.insert({position, check});
    //std::cout << check << position << "...ok";
    sep_string.append(check);
    args_size += args[i].size();
  }
  reserve_size = (src.size() - sep_string.size()) + args_size;
  //std::cout << "All args exist------------------ OK -------------------";
  //std::cout << reserve_size;
  out.reserve(reserve_size);
  //std::cout << "Resize out string: " << out.size();
  size_t prev_pos = 0;
  for (auto &&it : positions) {
    auto pos = it.first;
    auto arg = it.second;
    auto substr = src.substr(prev_pos, pos - prev_pos);
    prev_pos = pos + arg.size();
    //std::cout << substr;
    //std::cout << pos << arg;
    out.append(substr);
    arg.erase(std::remove(arg.begin(), arg.end(), '%'), arg.end());
    int index = std::stoi(arg);
    out.append(args[index - 1]);
  }
  if (prev_pos != src.size()) {
    auto end = src.substr(prev_pos, src.size() - prev_pos);
    //std::cout << end;
    out.append(end);
  }
  //std::cout << "**************************************\n\n";
  //std::cout << out;
  return true;
}
//#STOP_GRAB_TO_NAMESPACE
}; // namespace dvs
