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
	cv::Mat frame = cv::imread(sourceDirectory+"/TestProjects/Assets/CarLeft.png");
	std::vector<tracking::Object> cars = tracking::detectObjects(HSV,frame);
	tracking::Object o = detectCarAt9oclock(cars);
	ASSERT_TRUE(o.position.x != -1 && o.position.y !=-1 && o.area != -1);

}

TEST(RecognitionTest, Detect3Car) {
	cv::Mat frame = cv::imread(sourceDirectory+"/TestProjects/Assets/CarCenter.png");
	std::vector<tracking::Object> cars = tracking::detectObjects(HSV,frame);
	tracking::Object o = detectCarAt3oclock(cars);;
	ASSERT_TRUE(o.position.x != -1 && o.position.y !=-1 && o.area != -1);
}

TEST(RecognitionTest, Detect12Car) {
	cv::Mat frame = cv::imread(sourceDirectory+"/TestProjects/Assets/CarRight.png");
	std::vector<tracking::Object> cars = tracking::detectObjects(HSV,frame);
	tracking::Object o = detectCarAt12oclock(cars);;
	ASSERT_TRUE(o.position.x != -1 && o.position.y !=-1 && o.area != -1);
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



