#include "gtest/gtest.h"
using std::string;

class Test1{
  
};

TEST(Test1, launchCase) {
	
   bool result = true;
	EXPECT_EQ(result,true);

}

int main(int argc, char* argv[]){

	::testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
    char exit;
    std::cin >> exit;
	return 0;
}
