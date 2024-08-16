#include "gtest/gtest.h"
#include "common_utils/common_utils.h"
#include <fstream>
#include <codecvt>
#include <locale>
#include <iostream>
#include <windows.h>


using std::string;
using std::vector;

vector<string> args{"Apple", "Orange", "Banan", "Pineapple", "Kiwi"};

vector<string> args_big{"Yes",//1
  "No", //2
  "Ok", //3
  "Good",//4
  "Bad",//5
  "Nice",//6
  "Ugly",//7
  "Perfect",//8
  "Strong",//9
  "Davis",//10
  "Cat",//11
  "Plotly"//12
};

constexpr char check_test_string_1[] =
    R"(Check args:arg1 = Apple arg2 = Orange arg3 = Banan arg4 = Pineapple arg5 = Kiwi)";

constexpr char check_test_string_2[] =
    R"(I like Apple, Kiwi, Pineapple. And He also likes Kiwi, Pineapple, Apple. But We don't like Banan, Orange...)";

constexpr char check_test_string_3[] =
    R"(Davis is Perfect Soft. Plotly is Good. Test:Yes No Ok 100%)";

constexpr char not_filled_test_string_1[] =
    R"(Check args:arg1 = %1 arg2 = %2 arg3 = %3 arg4 = %4 arg5 = %5)";

constexpr char not_filled_test_string_2[] =
    R"(I like %1, %5, %4. And He also likes %5, %4, %1. But We don't like %3, %2...)";

constexpr char not_filled_test_string_3[] =
    R"(%10 is %8 Soft. %12 is %4. Test:%1 %2 %3 100%)";

// C++ stream interface
class TestCout : public std::stringstream {
 public:
  ~TestCout() {
    std::cout << str() << std::flush;
  }
};

#define TEST_COUT  TestCout()

TEST(CommonUtils, CreateStringFromArgs1) {
  string out;
  dvs::make_string(not_filled_test_string_1, args, out);
  EXPECT_EQ(check_test_string_1, out) << out;
  vector<string> neg_args{"Strawbery", "Orange", "Banan", "Pineapple", "Kiwi"};
  dvs::make_string(not_filled_test_string_1, neg_args, out);
  EXPECT_FALSE(check_test_string_1 == out);
}

TEST(CommonUtils, CreateStringFromDuplicatedArgs2) {
  string out;
  dvs::make_string(not_filled_test_string_2, args, out);
  EXPECT_EQ(check_test_string_2, out) << out;
}

TEST(CommonUtils, CreateStringFromBigArgs) {
  string out;
  dvs::make_string(not_filled_test_string_3, args_big, out);
  EXPECT_EQ(check_test_string_3, out) << out;
}

TEST(CommonUtils, CreateStringFantasyArgs) {
  string out;
  vector<string>sample = {"Ferrari", "Ford", "BMW", "Tatra"};
  dvs::make_string("I like %1 100%! I don't like %4.", sample, out);
  EXPECT_EQ("I like Ferrari 100%! I don't like Tatra.", out) << out;
}


TEST(CommonUtils, SplitString) {
  auto result = dvs::split(not_filled_test_string_1, '%');
  for (size_t i = 0; i < result.size(); ++i) {
    TEST_COUT << result[i] << "\n";
  }
  TEST_COUT << not_filled_test_string_1;
}

TEST(CommonUtils, FindSeparator) {
  char sep;
  dvs::find_separator("5.0;6;7;8", sep);
  EXPECT_EQ(';', sep);
  dvs::find_separator("5.0 6 7 8", sep);
  EXPECT_EQ(' ', sep);
  dvs::find_separator("5.0\t6\t7\t8", sep);
  EXPECT_EQ('\t', sep);
}

/*std::string Utf8ToCp1251(const std::string& utf8Str) {
  int len = MultiByteToWideChar(CP_UTF8, 0, utf8Str.c_str(), -1, NULL, 0);
  wchar_t* wstr = new wchar_t[len];
  MultiByteToWideChar(CP_UTF8, 0, utf8Str.c_str(), -1, wstr, len);
  len = WideCharToMultiByte(1251, 0, wstr, -1, NULL, 0, NULL, NULL);
  char* cp1251 = new char[len];
  WideCharToMultiByte(1251, 0, wstr, -1, cp1251, len, NULL, NULL);
  std::string result(cp1251);
  delete[] wstr;
  delete[] cp1251;
  return result;
}

TEST(CommonUtils, RussianFileC) {

  string russian = "файл.txt";
  auto path = Utf8ToCp1251(russian);
  std::fstream file;
  file.open(path, std::ios::in);
  EXPECT_EQ(bool(file), true);

}*/

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  std::ignore = RUN_ALL_TESTS();
  return 0;
}
