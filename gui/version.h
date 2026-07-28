// clang-format off
#ifndef VERSION_H
#define VERSION_H

#define VERSION_MAJOR 1
#define VERSION_MINOR 1
#define VERSION_PATCH 4

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

#define FILE_VERSION_STR                                                       \
  STR(VERSION_MAJOR) "." STR(VERSION_MINOR) "." STR(VERSION_PATCH)
#define PRODUCT_VERSION_STR                                                    \
  STR(VERSION_MAJOR) "." STR(VERSION_MINOR) "." STR(VERSION_PATCH)

#endif // VERSION_H
// clang-format on
