#include "test.h"

std::string sourceDirectory;
int ePmem = 40;
int eVmem = 40;
int pThresholdBrokenAmount = 0;
int vThresholdBrokenAmount = 0;

void memoryCheckCompilation(){
	bool debug = false;
	int vmem = getVMemory();
	std::string vString = std::to_string(vmem);
	int pmem = getPMemory();
	if(eVmem!=-1){
		if(eVmem>vmem){
			vThresholdBrokenAmount++;
		}
		EXPECT_TRUE(eVmem>vmem);
	}
	if(ePmem!=-1){
		if(ePmem>pmem){
			pThresholdBrokenAmount++;
		}
		EXPECT_TRUE(ePmem> pmem);
	}
	if(debug){
		printf("%s, %s, %s"," Virtual memory used: " ,vString.c_str() , "\n");
		printf("%s, %i, %s"," Physical memory used: " , pmem, "\n");
	}
}

TEST(CameraAquisitonTest, GetFrame) {
	cv::Mat frame = cv::imread(sourceDirectory+"/TestProjects/Assets/mask.jpg");
	memoryCheckCompilation();
	ASSERT_FALSE(frame.empty());
}

TEST(CameraAquisitonTest, GetVideoFrame) {
	cv:: VideoCapture cap;
	cap.open(sourceDirectory+"/TestProjects/Assets/pathoTrailer.mp4");
	memoryCheckCompilation();
	ASSERT_TRUE(cap.isOpened());
}

TEST(RecognitionTest, Detect9CarTrue) {
	cv::Mat HSV;
	cv::Mat frame = cv::imread(sourceDirectory+"/TestProjects/Assets/CarLeft.png");
	cv::cvtColor(frame,HSV,cv::COLOR_BGR2HSV);
	std::vector<tracking::Object> cars = tracking::detectObjects(HSV,frame);
	tracking::Object o = detectCarAt9oclock(cars);
	memoryCheckCompilation();
	ASSERT_TRUE(o.position.x != -1 && o.position.y !=-1 && o.area != -1);
}

TEST(RecognitionTest, Detect3CarTrue) {
	cv::Mat HSV;
	cv::Mat frame = cv::imread(sourceDirectory+"/TestProjects/Assets/CarCenter.png");
	cv::cvtColor(frame,HSV,cv::COLOR_BGR2HSV);
	std::vector<tracking::Object> cars = tracking::detectObjects(HSV,frame);
	tracking::Object o = detectCarAt3oclock(cars);
	memoryCheckCompilation();
	ASSERT_TRUE(o.position.x != -1 && o.position.y !=-1 && o.area != -1);
}

TEST(RecognitionTest, Detect12CarTrue) {
	cv::Mat HSV;
	cv::Mat frame = cv::imread(sourceDirectory+"/TestProjects/Assets/CarRight.png");
	cv::cvtColor(frame,HSV,cv::COLOR_BGR2HSV);
	std::vector<tracking::Object> cars = tracking::detectObjects(HSV,frame);
	tracking::Object o = detectCarAt12oclock(cars);
	memoryCheckCompilation();
	ASSERT_TRUE(o.position.x != -1 && o.position.y !=-1 && o.area != -1);
}

TEST(RecognitionTest, Detect312CarTrue) {
	cv::Mat HSV;
	cv::Mat frame = cv::imread(sourceDirectory+"/TestProjects/Assets/CarCenterRight.png");
	cv::cvtColor(frame,HSV,cv::COLOR_BGR2HSV);
	std::vector<tracking::Object> cars = tracking::detectObjects(HSV,frame);
	tracking::Object o = detectCarAt12oclock(cars);
	tracking::Object c = detectCarAt3oclock(cars);
	memoryCheckCompilation();
	ASSERT_TRUE(o.position.x != -1 && o.position.y !=-1 && o.area != -1);
	ASSERT_TRUE(c.position.x != -1 && c.position.y !=-1 && c.area != -1);
}

TEST(RecognitionTest, Detect39CarTrue) {
	cv::Mat HSV;
	cv::Mat frame = cv::imread(sourceDirectory+"/TestProjects/Assets/CarLeftRight.png");
	cv::cvtColor(frame,HSV,cv::COLOR_BGR2HSV);
	std::vector<tracking::Object> cars = tracking::detectObjects(HSV,frame);
	tracking::Object o = detectCarAt9oclock(cars);
	tracking::Object c = detectCarAt3oclock(cars);
	memoryCheckCompilation();
	ASSERT_TRUE(o.position.x != -1 && o.position.y !=-1 && o.area != -1);
	ASSERT_TRUE(c.position.x != -1 && c.position.y !=-1 && c.area != -1);
}
TEST(RecognitionTest, Detect129CarTrue) {
	cv::Mat HSV;
	cv::Mat frame = cv::imread(sourceDirectory+"/TestProjects/Assets/CarLeftCenter.png");
	cv::cvtColor(frame,HSV,cv::COLOR_BGR2HSV);
	std::vector<tracking::Object> cars = tracking::detectObjects(HSV,frame);
	tracking::Object o = detectCarAt9oclock(cars);
	tracking::Object c = detectCarAt12oclock(cars);
	memoryCheckCompilation();
	ASSERT_TRUE(o.position.x != -1 && o.position.y !=-1 && o.area != -1);
	ASSERT_TRUE(c.position.x != -1 && c.position.y !=-1 && c.area != -1);
}
TEST(RecognitionTest, DetectAllCarTrue) {
	cv::Mat HSV;
	cv::Mat frame = cv::imread(sourceDirectory+"/TestProjects/Assets/CarAllPos.png");
	cv::cvtColor(frame,HSV,cv::COLOR_BGR2HSV);
	std::vector<tracking::Object> cars = tracking::detectObjects(HSV,frame);
	tracking::Object v = detectCarAt3oclock(cars);
	tracking::Object o = detectCarAt9oclock(cars);
	tracking::Object c = detectCarAt12oclock(cars);
	memoryCheckCompilation();
	ASSERT_TRUE(v.position.x != -1 && v.position.y !=-1 && v.area != -1);
	ASSERT_TRUE(o.position.x != -1 && o.position.y !=-1 && o.area != -1);
	ASSERT_TRUE(c.position.x != -1 && c.position.y !=-1 && c.area != -1);
}

TEST(RecognitionTest, Detect12CarFalse) {
	cv::Mat HSV;
	cv::Mat frame = cv::imread(sourceDirectory+"/TestProjects/Assets/mask.jpg");
	cv::cvtColor(frame,HSV,cv::COLOR_BGR2HSV);
	std::vector<tracking::Object> cars = tracking::detectObjects(HSV,frame);
	tracking::Object o = detectCarAt12oclock(cars);;
	memoryCheckCompilation();
	ASSERT_FALSE(o.position.x != -1 && o.position.y !=-1 && o.area != -1);
}

TEST(RecognitionTest, Detect9CarFalse) {
	cv::Mat HSV;
	cv::Mat frame = cv::imread(sourceDirectory+"/TestProjects/Assets/mask.jpg");
	cv::cvtColor(frame,HSV,cv::COLOR_BGR2HSV);
	std::vector<tracking::Object> cars = tracking::detectObjects(HSV,frame);
	tracking::Object o = detectCarAt9oclock(cars);;
	memoryCheckCompilation();
	ASSERT_FALSE(o.position.x != -1 && o.position.y !=-1 && o.area != -1);
}

TEST(RecognitionTest, Detect3CarFalse) {
	cv::Mat HSV;
	cv::Mat frame = cv::imread(sourceDirectory+"/TestProjects/Assets/mask.jpg");
	cv::cvtColor(frame,HSV,cv::COLOR_BGR2HSV);
	std::vector<tracking::Object> cars = tracking::detectObjects(HSV,frame);
	tracking::Object o = detectCarAt3oclock(cars);
	memoryCheckCompilation();
	ASSERT_FALSE(o.position.x != -1 && o.position.y !=-1 && o.area != -1);
}


TEST(ClassificationTest, DetectStopsignTrue){

	cv::Mat frame = cv::imread(sourceDirectory+"/TestProjects/Assets/stopSign.png");
    tracking::LoadCascades();
	memoryCheckCompilation();
	ASSERT_TRUE(tracking::detectStopSigns(frame));
}
TEST(ClassificationTest, DetectStopsignFalse){
	cv::Mat frame = cv::imread(sourceDirectory+"/TestProjects/Assets/mask.jpg");
	tracking::LoadCascades();
	memoryCheckCompilation();
	ASSERT_FALSE(tracking::detectStopSigns(frame));
}


TEST(DrivingTest, NoStopSign){



}


TEST(Final, MemoryChecker){
	std::cout << "Times the physical threshold has broken: " << pThresholdBrokenAmount<<"\n";
	std::cout << "Times the virtual threshold has broken: " << vThresholdBrokenAmount<<"\n";

	ASSERT_TRUE(pThresholdBrokenAmount==0);
	ASSERT_TRUE(vThresholdBrokenAmount==0);
}

int main(int argc, char **argv) {
	sourceDirectory = "/~/git/group_09/src";
	tracking::LoadCascades();
	testing::InitGoogleTest(&argc, argv);
	testing::InitGoogleMock(&argc, argv);
	//std::thread memoryChecker (memoryCheckCompilation);
	//memoryChecker.join();
	return RUN_ALL_TESTS();
}



