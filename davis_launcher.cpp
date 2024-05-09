#include "davis.h"

int main(int argc, char* argv[]) {

  vector<double>v = {8.0, 8.0, 9, 0, 55};
  vector<vector<double>>hm = {{8.0, 8.0, 9, 0, 55}, {5.0, 18.0, 0.9, 50, 15}};
  auto settings1 = dvs::createShowSettingsChart();
  auto settings2 = dvs::createShowSettingsHeatMap();
  auto settings3 = dvs::createShowSettingsSurface();
  dv::show(v, settings1.get());

  dv::show(hm, settings2.get());

  dv::show(hm, settings3.get());
  return EXIT_SUCCESS;
}
