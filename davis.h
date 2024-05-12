#ifndef DAVIS_H
#define DAVIS_H

#include <string>
#include <vector>
#include <cstdlib>
#include "plotly_maker/plotly_maker.h"
#include "array_core/configurator.h"

namespace {

using  std::string;
using  std::vector;

constexpr char davis[] = "davis --";
constexpr char prefix[] = "=\"";
constexpr char postfix[] = "\"";
constexpr char command_heatmap[] = "heatmap";
constexpr char command_surface[] = "surface";
constexpr char command_line_chart[] = "linechart";

void runDavisBySystem(const string& args) {
  system(args.c_str());
}
void makeStringFromValues(const vector<double> in_values,
                          string& out_values) {
  for (size_t i = 0; i < in_values.size(); ++i) {
    std::string value = std::to_string(in_values[i]);
    out_values.append(value);
    if (i != in_values.size() - 1) {
      out_values.append(",");
    }
  }

}
void makeArgs(const vector<vector<double>>& values, string& out) {
  switch (dv::Configurator::getInstance().common.typeVisual) {
    case dv::conf_visualizationTypes::CHART:
      break;
    case dv::conf_visualizationTypes::HEATMAP:
      //duplicated code
      out.append(davis);
      out.append(command_heatmap);
      out.append(prefix);
      for (size_t i = 0; i < values.size(); ++i) {
        makeStringFromValues(values[i], out);
        if (i != values.size() - 1)
          out.append(";");
      }
      out.append(postfix);
      break;
    case dv::conf_visualizationTypes::SURFACE:
      //duplicated code
      out.append(davis);
      out.append(command_surface);
      out.append(prefix);
      for (size_t i = 0; i < values.size(); ++i) {
        makeStringFromValues(values[i], out);
        if (i != values.size() - 1)
          out.append(";");
      }
      out.append(postfix);
      break;
    default:
      break;
  }
}

void makeArgs(vector<double>& values, string& out) {

  switch (dv::Configurator::getInstance().common.typeVisual) {
    case dv::conf_visualizationTypes::CHART:
      out.append(davis);
      out.append(command_line_chart);
      out.append(prefix);
      makeStringFromValues(values, out);
      out.append(postfix);
      break;
    case dv::conf_visualizationTypes::HEATMAP:
      break;
    case dv::conf_visualizationTypes::SURFACE:
      break;
    default:
      break;
  }
}

}

namespace dv {

void show(vector<vector<double>>& values);
void show(vector<double>& values);

void show(vector<vector<double>>& values) {
  string args;
  makeArgs(values, args);
  runDavisBySystem(args);
}

void show(vector<double>& values) {
  string args;
  makeArgs(values, args);
  runDavisBySystem(args);
}
}

#endif // DAVIS_H
