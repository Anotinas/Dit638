#include "test.h"


TEST(CameraCVTest, GetFrame) {
	printf("Test is running");
	ASSERT_TRUE(1 == 1); //Check if the result is a frame.
	
}
TEST(CameraCVTest, GetVideoFrame) {


}

TEST(CameraCVTest, RedDetection) {

}

TEST(CameraCVTest, BlueDetection) {

}

TEST(CameraCVTest, YellowDetection) {

}

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}



