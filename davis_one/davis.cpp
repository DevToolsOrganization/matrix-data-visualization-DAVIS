#include "davis.h"
#include <iostream>
#include <vector>
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <sstream>
#include <iostream>

namespace {

using std::vector;
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


bool checkThatSizesAreTheSame(const vector<vector<double>>& values) {
  size_t size = 0;
  if (!values.empty()) {
    size = values[0].size();
  };
  for (size_t i = 0; i < values.size(); ++i) {

    if (values[i].size() != size)
      return false;
  }
  return true;
}

bool createStringHeatMapValues(const vector<vector<double>>& values,
                               string& str_values) {
  if (!checkThatSizesAreTheSame(values))
    return false;
  if (!str_values.empty())
    str_values.clear();
  str_values.append(R"(var data = [{z: )");
  str_values.append(R"([)");
  for (size_t i = 0; i < values.size(); ++i) {
    str_values.append("[");
    for (size_t j = 0; j < values[i].size(); ++j) {
      str_values.append(std::to_string(values[i][j]));
      if (j != values[i].size() - 1) {
        str_values.append(",");
      }
    }
    str_values.append("]");
    if (i != values.size() - 1) {
      str_values.append(",");
    }
  }
  str_values.append(R"(],)");
  return true;
}


bool createStringLineChartValues(const vector<double>& values,
                                 string& str_values) {
  if (!str_values.empty()) {
    str_values.clear();
  }
  str_values = R"(var trace = {x: [)";
  for (size_t i = 0; i < values.size(); ++i) {
    str_values.append(std::to_string(i));
    if (i != values.size() - 1) {
      str_values.append(",");
    }
  }
  str_values.append("], y: [");
  for (size_t j = 0; j < values.size(); ++j) {
    str_values.append(std::to_string(values[j]));
    if (j != values.size() - 1) {
      str_values.append(",");
    }
  }
  str_values.append("], mode: 'lines+markers'};var data = [trace];");
  return true;
}

inline bool heatmap_and_surface(const vector<vector<double>>& values,
                                const std::string& title,
                                const davis::visualizationTypes& visualType,
                                const davis::colorscales& colorscale) {
  std::string page;
  if (!createHtmlPageWithPlotlyJS(values, page, visualType, colorscale)) {
    return false;
  }
  string pageName;
  davis::mayBeCreateJsWorkingFolder();
  pageName.append("./").append(davis::kOutFolderName).append(title).append(".html");
  davis::saveStringToFile(pageName, page);
  davis::openPlotlyHtml(pageName);
  return true;// TODO handle different exceptions
};

} // namespace

namespace davis {
const char kAppName[] = "davis";
const char kOutFolderName[] = "davis_htmls/";
const char kPlotlyJsWorkPath[] = "./davis_htmls/plotly-2.27.0.min.js";
const char kPlotlyJsName[] = "plotly-2.27.0.min.js";
const char kPlotlyJsResourcePath[] = "plotly_maker/plotly-2.27.0.min.js";
// *INDENT-OFF*

    const char kDivSizePart[] = R"(<div style = "display: flex;
  align-items:center;height:100%; width:100%;background:#dddfd4;
  justify-content: center;"><div style="height:95%; aspect-ratio: 1/1;"
id="gd"></div></div>
<script>
)";

    const char kCommonHeadPart[] = R"(<head>
<script src="./plotly-2.27.0.min.js" charset="utf-8"></script>
</head>
<body>)";

    const char kColorMapDefaultPart[] = R"(
  colorscale: [
    ['0.0', 'rgb(165,0,38)'],
    ['0.111111111111', 'rgb(215,48,39)'],
    ['0.222222222222', 'rgb(244,109,67)'],
    ['0.333333333333', 'rgb(253,174,97)'],
    ['0.444444444444', 'rgb(254,224,144)'],
    ['0.555555555556', 'rgb(224,243,248)'],
    ['0.666666666667', 'rgb(171,217,233)'],
    ['0.777777777778', 'rgb(116,173,209)'],
    ['0.888888888889', 'rgb(69,117,180)'],
    ['1.0', 'rgb(49,54,149)']
  ],)";


    const char kColorMapSunnyPart[] = R"(
  colorscale: [
    ['0.0', 'rgb(250, 134, 7)'],
    ['0.2', 'rgb(250, 150, 27)'],
    ['0.4', 'rgb(252, 176, 51)'],
    ['0.6', 'rgb(254, 204, 81)'],
    ['0.8', 'rgb(255, 228, 105)'],
    ['1.0', 'rgb(255, 245, 123)']
  ],)";

    const char kColorMapGlamourPart[] = R"(
  colorscale: [
    ['0.0', 'rgb(17,63,93)'],
    ['0.2', 'rgb(88,80,143)'],
    ['0.4', 'rgb(182,79,145)'],
    ['0.6', 'rgb(245,97,94)'],
    ['0.8', 'rgb(248,165,0)'],
    ['1.0', 'rgb(235,248,0)']
  ],)";

    const char kColorMapThermalPart[] = R"(
  colorscale: [
    ['0.0', 'rgb(0,0,5)'],
    ['0.2', 'rgb(12,0,44)'],
    ['0.4', 'rgb(41,0,148)'],
    ['0.6', 'rgb(196,0,123)'],
    ['0.8', 'rgb(230,61,63)'],
    ['1.0', 'rgb(255,213,0)']
  ],)";


    const char kHeatMapTypePart[] = R"(
type: 'heatmap'
}];)";

    const char kSurfaceTypePart[]=R"(
type: 'surface'
}];)";

    const char kCommonLastPart[] = R"(
Plotly.newPlot('gd', data);
</script>
</body>)";

   // *INDENT-ON*
   
using std::string;
using std::vector;
using std::istringstream;

bool getMatrixValuesFromString(const string& in_values,
                               vector<vector<double>>& out_values) {
  istringstream f_lines(in_values);
  string lines;
  while (std::getline(f_lines, lines, ';')) {
    vector<double>vals;
    istringstream f_values(lines);
    string str_value;
    while (std::getline(f_values, str_value, ',')) {
      vals.push_back(std::stod(str_value));
    }
    out_values.push_back(vals);
  }
  return true;
};

bool createHtmlPageWithPlotlyJS(const std::vector<std::vector<double>>& values,
                                std::string& page,
                                const visualizationTypes& visualType,
                                const colorscales& colorscale) {
  page = kCommonHeadPart;
  page.append(kDivSizePart);
  string str_values = "";
  if (!checkThatSizesAreTheSame(values)) {
    return false;
  }
  createStringHeatMapValues(values, str_values);
  page.append(str_values);
  switch (colorscale) {
    case colorscales::DEFAULT:
      page.append(kColorMapDefaultPart);
      break;
    case colorscales::SUNNY:
      page.append(kColorMapSunnyPart);
      break;
    case colorscales::GLAMOUR:
      page.append(kColorMapGlamourPart);
      break;
    case colorscales::THERMAL:
      page.append(kColorMapThermalPart);
      break;
  }
  switch (visualType) {
    case visualizationTypes::CHART:
      break;
    case visualizationTypes::HEATMAP:
      page.append(kHeatMapTypePart);
      break;
    case visualizationTypes::SURFACE:
      page.append(kSurfaceTypePart);
      break;
  }
  page.append(kCommonLastPart);
  return true;
}

bool showHeatMapInBrowser(const vector<vector<double>>& values,
                          const std::string& title,
                          const ShowSettingsHeatMap* settings) {
  return heatmap_and_surface(values, title, settings->getVisualType(), settings->colorScale);
}

bool showHeatMapInBrowser(const std::string& values,
                          const std::string& title,
                          const ShowSettingsHeatMap* settings) {
  vector<vector<double>>heat_map_values;
  getMatrixValuesFromString(values, heat_map_values);
  showHeatMapInBrowser(heat_map_values, title, settings);
  return true;
};

bool showLineChartInBrowser(const vector<double>& values,
                            const string& title,
                            const ShowSettings& settings) {
  string page = kCommonHeadPart;
  page.append(kDivSizePart);
  string str_values = "";
  createStringLineChartValues(values, str_values);
  page.append(str_values);
  page.append(kCommonLastPart);
  string pageName;
  mayBeCreateJsWorkingFolder();
  pageName.append("./").append(kOutFolderName).append(title).append(".html");
  davis::saveStringToFile(pageName, page);
  openPlotlyHtml(pageName);
  return true;
}

bool showLineChartInBrowser(const string& values,
                            const string& title,
                            const ShowSettings& settings) {
  vector<double>vals;
  istringstream f(values);
  string s;
  while (std::getline(f, s, ',')) {
    vals.push_back(std::stod(s));
  }
  showLineChartInBrowser(vals, title, settings);
  return true;
};

bool showSurfaceInBrowser(const vector<vector<double>>& values,
                          const string& title,
                          const ShowSettingsSurface* settings) {
  return heatmap_and_surface(values, title, settings->getVisualType(), settings->colorScale);
}

bool showSurfaceInBrowser(const std::string& values,
                          const string& title,
                          const ShowSettingsSurface* settings) {
  vector<vector<double>>surface_values;
  getMatrixValuesFromString(values, surface_values);
  showSurfaceInBrowser(surface_values, title, settings);
  return true;
}

bool showLineChartInBrowser(const vector<double>& values,
                            const std::string& title,
                            const ShowSettingsChart* settings) {
  std::string page = kCommonHeadPart;
  page.append(kDivSizePart);
  string str_values = "";
  createStringLineChartValues(values, str_values);
  page.append(str_values);
  page.append(kCommonLastPart);
  std::string pageName;
  mayBeCreateJsWorkingFolder();
  pageName.append("./").append(kOutFolderName).append(title).append(".html");
  davis::saveStringToFile(pageName, page);
  openPlotlyHtml(pageName);
  return true;
}

bool showLineChartInBrowser(const std::string& values,
                            const std::string& title,
                            const ShowSettingsChart* settings) {
  std::vector<double>vals;
  std::istringstream f(values);
  std::string s;
  while (std::getline(f, s, ',')) {
    vals.push_back(std::stod(s));
  }
  showLineChartInBrowser(vals, title, settings);
  return true;
};

std::unique_ptr<ShowSettings> testF() {
  return std::make_unique<ShowSettings>();
}


std::unique_ptr<ShowSettingsHeatMap> createShowSettingsHeatMap(colorscales color) {
  return std::make_unique<ShowSettingsHeatMap>(color);
}

std::unique_ptr<ShowSettingsSurface> createShowSettingsSurface(colorscales color) {
  return std::make_unique<ShowSettingsSurface>(color);
}

std::unique_ptr<ShowSettingsChart> createShowSettingsChart() {
  return std::make_unique<ShowSettingsChart>();
}

visualizationTypes ShowSettings::getVisualType() const {
  return visualType;
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

std::vector<std::string> split(const std::string& target, char c) {
  std::string temp;
  std::stringstream stringstream { target };
  std::vector<std::string> result;
  while (std::getline(stringstream, temp, c)) {
    result.push_back(temp);
  }

  return result;
}

}