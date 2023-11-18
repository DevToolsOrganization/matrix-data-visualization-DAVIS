#include "davis.h"

int main(int argc, char* argv[]) {
  davis::showSettings settings;
  settings.visualType = davis::visualizationTypes::CHART;
  vector<double>v = {8.0, 8.0, 9, 0, 55};
  vector<vector<double>>hm = {{8.0, 8.0, 9, 0, 55}, {5.0, 18.0, 0.9, 50, 15}};
  dv::show(settings, v);
  settings.visualType = davis::visualizationTypes::HEATMAP;
  dv::show(settings, hm);
  settings.visualType = davis::visualizationTypes::SURFACE;
  dv::show(settings, hm);
  return EXIT_SUCCESS;
}
