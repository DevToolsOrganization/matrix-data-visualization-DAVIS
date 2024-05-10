#include "gtest/gtest.h"
#include "common_utils/common_utils.h"
#include <fstream>

using std::string;
using std::vector;

constexpr char check_test_string[] =
R"(Check args:
arg1 = Apple
arg2 = Orange
arg3 = Banan
arg4 = Pineapple
arg5 = Kiwi
)";

constexpr char not_filled_test_string[] =
R"(Check args:
arg1 = %1
arg2 = %2
arg3 = %3
arg4 = %4
arg5 = %5
)";

TEST(CommonUtils, CreateStringFromArgs) {

  vector<string> args{"Apple","Orange","Banan","Pineapple","Kiwi"};
  string out;
  dvs::make_string(not_filled_test_string,args,out);
  EXPECT_EQ(check_test_string,out)<<out;
  vector<string> neg_args{"Strawbery","Orange","Banan","Pineapple","Kiwi"};
  dvs::make_string(not_filled_test_string,neg_args,out);
  EXPECT_FALSE(check_test_string == out);
}


int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  std::ignore = RUN_ALL_TESTS();
  return 0;
}
