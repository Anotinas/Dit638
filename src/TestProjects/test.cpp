#include "test.h"

std::string sourceDirectory;

TEST(CameraAquisitonTest, GetFrame) {
	cv::Mat frame = cv::imread(sourceDirectory+"/TestProjects/Assets/mask.jpg");
	ASSERT_FALSE(frame.empty());
}

TEST(CameraAquisitonTest, GetVideoFrame) {
	cv:: VideoCapture cap;
	cap.open(sourceDirectory+"/TestProjects/Assets/pathoTrailer.mp4");
	ASSERT_TRUE(cap.isOpened());
}


TEST(RecognitionTest, Detect9Car) {
	cv::Mat frame = cv::imread(sourceDirectory+"/TestProjects/Assets/mask.jpg");
	
	
}

TEST(RecognitionTest, Detect3Car) {
	cv::Mat frame = cv::imread(sourceDirectory+"/TestProjects/Assets/mask.jpg");	
}

TEST(RecognitionTest, Detect12Car) {
	cv::Mat frame = cv::imread(sourceDirectory+"/TestProjects/Assets/mask.jpg");

}
TEST(ClassificationTest, DetectStopsignTrue){
	cv::Mat frame = cv::imread(sourceDirectory+"/TestProjects/Assets/stopSign.png");
	ASSERT_TRUE(tracking::detectStopSigns(frame));
}
TEST(ClassificationTest, DetectStopsignFalse){
	cv::Mat frame = cv::imread(sourceDirectory+"/TestProjects/Assets/mask.jpg");
	ASSERT_FALSE(tracking::detectStopSigns(frame));
}



int main(int argc, char **argv) {
	sourceDirectory = "/~/git/group_09/src";
	tracking::LoadCascades();
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}



