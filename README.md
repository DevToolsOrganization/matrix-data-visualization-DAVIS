![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=Plastic&logo=c%2B%2B&logoColor=white)
![Workflow](https://github.com/valvals/devtools/actions/workflows/cmake-multi-platform.yml/badge.svg?branch=main)
[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)](https://opensource.org/licenses/MIT)
[![Quality Gate Status](https://sonarcloud.io/api/project_badges/measure?project=DevToolsOrganization_matrix-data-visualization-DAVIS&metric=alert_status)](https://sonarcloud.io/summary/new_code?id=DevToolsOrganization_matrix-data-visualization-DAVIS)
[![Reliability Rating](https://sonarcloud.io/api/project_badges/measure?project=DevToolsOrganization_matrix-data-visualization-DAVIS&metric=reliability_rating)](https://sonarcloud.io/summary/new_code?id=DevToolsOrganization_matrix-data-visualization-DAVIS)
[![Maintainability Rating](https://sonarcloud.io/api/project_badges/measure?project=DevToolsOrganization_matrix-data-visualization-DAVIS&metric=sqale_rating)](https://sonarcloud.io/summary/new_code?id=DevToolsOrganization_matrix-data-visualization-DAVIS)
[![Code Smells](https://sonarcloud.io/api/project_badges/measure?project=DevToolsOrganization_matrix-data-visualization-DAVIS&metric=code_smells)](https://sonarcloud.io/summary/new_code?id=DevToolsOrganization_matrix-data-visualization-DAVIS)
[![Duplicated Lines (%)](https://sonarcloud.io/api/project_badges/measure?project=DevToolsOrganization_matrix-data-visualization-DAVIS&metric=duplicated_lines_density)](https://sonarcloud.io/summary/new_code?id=DevToolsOrganization_matrix-data-visualization-DAVIS)
[![Bugs](https://sonarcloud.io/api/project_badges/measure?project=DevToolsOrganization_matrix-data-visualization-DAVIS&metric=bugs)](https://sonarcloud.io/summary/new_code?id=DevToolsOrganization_matrix-data-visualization-DAVIS)
[![Technical Debt](https://sonarcloud.io/api/project_badges/measure?project=DevToolsOrganization_matrix-data-visualization-DAVIS&metric=sqale_index)](https://sonarcloud.io/summary/new_code?id=DevToolsOrganization_matrix-data-visualization-DAVIS)

[<img src="https://github.com/user-attachments/assets/7425ddb9-8b6e-4303-8e29-f1144cc79acb" width="220">](https://github.com/DevToolsOrganization)

![Logo](https://github.com/valvals/devtools/assets/104432560/27f28dde-27bc-47f6-8696-f80fb7b4661b)

</br>

# [------------- FULL DOCUMENTATION PAGE -------------](https://devtoolsorganization.github.io/matrix-data-visualization-DAVIS/#/)

</br>

## Table of Contents

* [💡 About](#-about)
* [🔍 Examples](#-examples)
* [💻 Usage](#-usage)
* [⚒️ Setup](#-setup)
* [❓ FAQ](#-faq)
* [🚀 Room for Improvement](#-room-for-improvement)
* [⭐ Used By](#-used-by)
* [🐝 Authors](#-authors)
* [📞 Contacts](#-contacts)
* [📝 Licence](#-license)


# 💡 About
DAVIS (Data Visualisation tool) is utility for data visualization. The visualization is based on [Plotly javascript](https://plotly.com/) So DAVIS generate html page with injected data from code and after that launch browser to show it.

One of the main tasks we solve is to make it easier to debug your application. With Davis you can easy visualize your one- and two-dimensional data variables.

Davis is easy-to-use tool:
* one .h file, one .cpp file, one .js file
* only native c++11 functions, zero external dependences
* simple short syntaxis for minimize code you need to write 

# 🔍 Examples

<details>
<summary>Example 1</summary>

```cpp
#include "davis.h"

// vals - is user's 2d array
int rows = 20;
int cols = 20;
int** vals = new int* [rows];
  for (int i = 0; i < rows; ++i) {
    vals[i] = new int[cols];
    for (int j = 0; j < cols; ++j) {
      vals[i][j] = i * cols + j;
    }
}
dv::show(vals, rows, cols);  // pass varible and dimensions of 2d array  
```
![2d](https://github.com/valvals/devtools/assets/104432560/16832af7-d8c4-4af9-b4b1-60b0d6027478)
</details>

<details>
<summary>Example 2</summary>

```cpp
#include "davis.h"

//it possible and std::list<std::vector<double>> values = ...
//                std::vector<std::list<double>> values = ...
std::vector<std::vector<double>> values = {{30.3, 40, 98, 76} 
                                         , {99, 45, 20, 1}
                                         , {5, 56, 93, 25}
                                         , {45, 23, 90, 2}};
 auto config = dv::Config();
 config.typeVisual = dv::VISUALTYPE_SURFACE;              // select surface visual mode           
 config.surf.colorSc = dv::COLORSCALE_THERMAL;                   // change colorscale
 bool result = dv::show(values, "testSurfacePage", config);      // pass 2d data, html page name, configuration structure
```
![surf](https://github.com/valvals/devtools/assets/104432560/8d1c5488-049f-4471-9e58-1e97b59c03e7)
</details>

<details>
  <summary> Example 3 </summary>
  
  ```cpp
  #include "davis.h"
  
  int vals[] = {2, 6, 4, -34, 56, 33, 2, 15};
  auto config = dv::Config();
  config.heatmap.title = "Custom title";            // change default settings to custom for heatmap
  config.heatmap.xLabel = "Custom xLabel";          // change default settings to custom for heatmap
  config.heatmap.yLabel = "Custom yLabel";          // change default settings to custom for heatmap
  bool result = dv::show(vals, sizeof(vals) / sizeof(vals[0]), "htmlPageName", config);
  ```
  ![chart](https://github.com/valvals/devtools/assets/104432560/43903324-f49c-42f3-9ef1-3cb7e95a786d)
</details>

# 💻 Usage
All user's functions, structs, etc. are placed in `dv::` namespace.

<details>
    <summary>Show(...) function</summary>

## Show(...) function
There is one template overload function for visualization different types of data:

```cpp
template <typename T>
dv::show(...)
```

First arguments of `dv::show(...)` could be either pointer to array:
| Arguments  | Description  |
| ------------ | ------------ |
|  ` T** data, uint64_t arrRows, uint64_t arrCols`      |   2d array with arrRows × arrCols size. Data placed inside array of arrays |
|  ` const T* data, uint64_t arrRows, uint64_t arrCols` |   2d array with arrRows × arrCols size.  Data placed inside pseudo 2d array (element access [i*arrCols + j])  |
|  ` const T* data, uint64_t count`                     |   1d array. Data placed inside array  |

or container:
| Arguments  | Description  |
| ------------ | ------------ |
|  ` C const& container_of_containers `         |   2d array. Data placed inside container of containers. Containers can be `std::vector`, `std::list`, `std::array`, etc. Content of containers must be convertable to `double`                        |
|  ` C const& container`                        |   1d array. Data placed inside container. Сontainer requirements are the same                            |


Two last arguments of `dv::show(...)` are also the same: `const std::string& htmlPageName` and `const dv::Config& configuration`. Theese arguments have default values.
* `htmlPageName` - name of html page will be generated
* `configuration` - configuration structure with custom settings

</br>

```cpp
using std::vector;
using std::string;

//! 2-dimensional array
template <typename T>
bool show(T** data, uint64_t arrRows, uint64_t arrCols,
          const string& htmlPageName = dvs::kAppName, const Config& configuration = Config());

//! 1-dimensional array that simulates a 2-dimensional one (element access [i*cols+j])
template <typename T>
bool show(const T* data, uint64_t arrRows, uint64_t arrCols,
          const string& htmlPageName = dvs::kAppName, const Config& configuration = Config());

//! 1-dimensional array
template <typename T>
bool show(const T* data, uint64_t count, const string& htmlPageName = dvs::kAppName, const Config& configuration = Config());

//! 1-dimensional container
template<typename C,
         typename T = std::decay_t<decltype(*begin(std::declval<C>()))>,
         typename = std::enable_if_t<std::is_convertible_v<T, double>> >
bool show(C const& container, const string& htmlPageName = dvs::kAppName, const Config& configuration = Config());

//! 2-dimensional container
template<typename C,
         typename T = std::decay_t<decltype(*begin(std::declval<C>()))>,
         typename E = std::decay_t<decltype(*begin(std::declval<T>()))>,
         typename = std::enable_if_t<std::is_convertible_v<E, double>> >
bool show(C const& container_of_containers, const string& htmlPageName = dvs::kAppName, const Config& configuration = Config());
```
</details>

<details>
    <summary>Configuration structure</summary>
  
## Configuration structure
Data vizuailisation can be tunned with using custom configuration `dv::Config`. 
Configuration storred 3 structures and 1 enumeration.

1. Create `dv::Config` object;

2. Change it's type (or not, so it will be `VISUALTYPE_AUTO`) 
  ```cpp
enum config_visualizationTypes {
  VISUALTYPE_AUTO, //if user not forces some specific type it will be recognized by context
  VISUALTYPE_CHART,
  VISUALTYPE_HEATMAP,
  VISUALTYPE_SURFACE
};
```

3. Change fields of neaded visualisation type

| Name of structure | Description  |
| ------------ | ------------ |
|chart       |for chart settings|
|heatmap     |for heatmap settings |
|surf        |for surface settings|

Settings fields can be
* `title` - title at top of image
* `xLabel` - title of X axis
* `yLabel` - title of Y axis
* `zLabel` - title of Z axis
* `colorScale` - type of colorscale from enum `config_colorscales`

4. Pass it to `dv::show(...)`;
</details>




# ⚒️ Setup
1. Download **davis.cpp**, **davis.h** and **plotly-2.27.0.min.js** from our last [release](https://github.com/valvals/devtools/releases)
2. Put them in one folder in your project
3. Include **davis.h** to your project
4. Now you can use Davis functionality 

# ❓ FAQ
### Generated html page is empty in browser
Check you building folder, find folder **davis_htmls** and check if **plotly-2.27.0.min.js** exists.
If it not exists copy this file manualy to this place.<br>
And create bug issue :)

### Can I use  newer Plotly .js file?
All our test are made for plotly .js file which is placed at our last [release](https://github.com/valvals/devtools/releases) <br>
But probably newer version will also work. So download newer .js file [at plotly page](https://plotly.com/javascript/), rename it to **plotly-2.27.0.min.js** and test by yorself.

### Which containers can I use in show() function?
Containers must support implementation of `begin()` and `end()` methods. Content of containers must be convertable to `double`


# 🚀 Room for Improvement
Our next steps will involve:
* template functions for saving arrays like text files with separators
* compiling Davis to exe-file which provide command line interface for visualisation text files or copypasted data
* adding some evaluated statistic information abou data to generated html page

# ⭐ Used By
This project is used by the following companies:
- A. N. Sevchenko  Institute  of  Applied  Physical Problems of Belarusian State University
 
# 🐝 Authors
[AntonMrt](https://www.github.com/AntonMrt), [ValeryStk](https://www.github.com/ValeryStk)\
You are welcome to our team! 

# 📞 Contacts
For any questions please contact<br>
devtools.public@gmail.com

# 📝 License
License is [MIT](https://opensource.org/license/mit)

Copyright 2024 Anton Martinov & Valery Stanchyk 

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
