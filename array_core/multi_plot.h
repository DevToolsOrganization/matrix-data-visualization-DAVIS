#ifndef MULTI_PLOT_H
#define MULTI_PLOT_H
#include <vector>
#include <string>
#include "configurator.h"

using std::string;
using std::vector;

namespace dvs {
//#START_GRAB_TO_DVS_NAMESPACE

extern bool isHold;
extern vector<string> allChartBlocks;

//#STOP_GRAB_TO_DVS_NAMESPACE
} // end namespace dvs


namespace dv {
//#START_GRAB_TO_DV_NAMESPACE


//! it shows, that we want to start accumulate chart graphs for showing
//! them all at one html in one axes
void holdOn();

//! finish creation of html page with multi pages
void holdOff(const Config& configuration = Config());



//#STOP_GRAB_TO_DV_NAMESPACE
} // end namespace dv

#endif // MULTI_PLOT_H
