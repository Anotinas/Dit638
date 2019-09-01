#include "test.h"

std::string sourceDirectory;
bool memoryShouldBeChecked = true;
long long ePmem = 1900000000;
long long eVmem = 2835000000;
int pMemThresholdBroke = 0;
int vMemThresholdBroke = 0;
std::ofstream file;


void memoryCheckCompilation(){
	bool debug = true;
	
	while(memoryShouldBeChecked){
	long long vmem = getVMemory();
	long long pmem = getPMemory();
	//printf("here is vmem: %lld \n", vmem);
	//printf("here is pmem: %lld \n", pmem);
	/*if(eVmem!=-1){
		EXPECT_TRUE(eVmem>vmem);
	}
	if(ePmem!=-1){
		EXPECT_TRUE(ePmem> pmem);
	}*/
	if(eVmem <vmem){
		vMemThresholdBroke++;
	}
	if(ePmem <pmem){
		pMemThresholdBroke++;
	}
	if(debug){
		std::string  vmemChar, pmemChar, lineChar;
		vmemChar =  "Virtual memory used: " + std::to_string(vmem);
		pmemChar = " Physical memory used: "+ std::to_string(pmem);

		//pmemChar = " Physical memory used: " , pmem, "\n";
		file << vmemChar;
		file << "\n";
		file << pmemChar;
		file << "\n";
	}
	}
	file.close();
}

void testFileWrite(std::string testName){
	testName = "\n \n" + testName;
	file << testName;
}

TEST(CameraAquisitonTest, GetFrame) {
	testFileWrite("GetFrame");
	cv::Mat frame = cv::imread(sourceDirectory+"/TestProjects/Assets/mask.jpg");
	ASSERT_FALSE(frame.empty());
}

TEST(CameraAquisitonTest, GetVideoFrame) {
	testFileWrite("GetVideoFrame");
	cv:: VideoCapture cap;
	cap.open(sourceDirectory+"/TestProjects/Assets/pathoTrailer.mp4");
	ASSERT_TRUE(cap.isOpened());
}

TEST(RecognitionTest, Detect9CarTrue) {
	testFileWrite("Detect9CarTrue");
	cv::Mat HSV;
	cv::Mat frame = cv::imread(sourceDirectory+"/TestProjects/Assets/CarLeft.png");
	cv::cvtColor(frame,HSV,cv::COLOR_BGR2HSV);
	std::vector<tracking::Object> cars = tracking::detectObjects(HSV,frame);
	tracking::Object o = detectCarAt9oclock(cars);
	ASSERT_TRUE(o.position.x != -1 && o.position.y !=-1 && o.area != -1);
}

TEST(RecognitionTest, Detect3CarTrue) {
	testFileWrite("Detect3CarTrue");
	cv::Mat HSV;
	cv::Mat frame = cv::imread(sourceDirectory+"/TestProjects/Assets/CarCenter.png");
	cv::cvtColor(frame,HSV,cv::COLOR_BGR2HSV);
	std::vector<tracking::Object> cars = tracking::detectObjects(HSV,frame);
	tracking::Object o = detectCarAt3oclock(cars);
	ASSERT_TRUE(o.position.x != -1 && o.position.y !=-1 && o.area != -1);
}

TEST(RecognitionTest, Detect12CarTrue) {
	testFileWrite("Detect12CarTrue");
	cv::Mat HSV;
	cv::Mat frame = cv::imread(sourceDirectory+"/TestProjects/Assets/CarRight.png");
	cv::cvtColor(frame,HSV,cv::COLOR_BGR2HSV);
	std::vector<tracking::Object> cars = tracking::detectObjects(HSV,frame);
	tracking::Object o = detectCarAt12oclock(cars);
	ASSERT_TRUE(o.position.x != -1 && o.position.y !=-1 && o.area != -1);
}

TEST(RecognitionTest, Detect312CarTrue) {
	testFileWrite("Detect312CarTrue");
	cv::Mat HSV;
	cv::Mat frame = cv::imread(sourceDirectory+"/TestProjects/Assets/CarCenterRight.png");
	cv::cvtColor(frame,HSV,cv::COLOR_BGR2HSV);
	std::vector<tracking::Object> cars = tracking::detectObjects(HSV,frame);
	tracking::Object o = detectCarAt12oclock(cars);
	tracking::Object c = detectCarAt3oclock(cars);
	ASSERT_TRUE(o.position.x != -1 && o.position.y !=-1 && o.area != -1);
	ASSERT_TRUE(c.position.x != -1 && c.position.y !=-1 && c.area != -1);
}

TEST(RecognitionTest, Detect39CarTrue) {
	testFileWrite("Detect39CarTrue");
	cv::Mat HSV;
	cv::Mat frame = cv::imread(sourceDirectory+"/TestProjects/Assets/CarLeftRight.png");
	cv::cvtColor(frame,HSV,cv::COLOR_BGR2HSV);
	std::vector<tracking::Object> cars = tracking::detectObjects(HSV,frame);
	tracking::Object o = detectCarAt9oclock(cars);
	tracking::Object c = detectCarAt3oclock(cars);
	ASSERT_TRUE(o.position.x != -1 && o.position.y !=-1 && o.area != -1);
	ASSERT_TRUE(c.position.x != -1 && c.position.y !=-1 && c.area != -1);
}
TEST(RecognitionTest, Detect129CarTrue) {
	testFileWrite("Detect129CarTrue");
	cv::Mat HSV;
	cv::Mat frame = cv::imread(sourceDirectory+"/TestProjects/Assets/CarLeftCenter.png");
	cv::cvtColor(frame,HSV,cv::COLOR_BGR2HSV);
	std::vector<tracking::Object> cars = tracking::detectObjects(HSV,frame);
	tracking::Object o = detectCarAt9oclock(cars);
	tracking::Object c = detectCarAt12oclock(cars);
	ASSERT_TRUE(o.position.x != -1 && o.position.y !=-1 && o.area != -1);
	ASSERT_TRUE(c.position.x != -1 && c.position.y !=-1 && c.area != -1);
}
TEST(RecognitionTest, DetectAllCarTrue) {
	testFileWrite("DetectAllCarTrue");
	cv::Mat HSV;
	cv::Mat frame = cv::imread(sourceDirectory+"/TestProjects/Assets/CarAllPos.png");
	cv::cvtColor(frame,HSV,cv::COLOR_BGR2HSV);
	std::vector<tracking::Object> cars = tracking::detectObjects(HSV,frame);
	tracking::Object v = detectCarAt3oclock(cars);
	tracking::Object o = detectCarAt9oclock(cars);
	tracking::Object c = detectCarAt12oclock(cars);
	ASSERT_TRUE(v.position.x != -1 && v.position.y !=-1 && v.area != -1);
	ASSERT_TRUE(o.position.x != -1 && o.position.y !=-1 && o.area != -1);
	ASSERT_TRUE(c.position.x != -1 && c.position.y !=-1 && c.area != -1);
}

TEST(RecognitionTest, Detect12CarFalse) {
	testFileWrite("Detect12CarFalse");
	cv::Mat HSV;
	cv::Mat frame = cv::imread(sourceDirectory+"/TestProjects/Assets/mask.jpg");
	cv::cvtColor(frame,HSV,cv::COLOR_BGR2HSV);
	std::vector<tracking::Object> cars = tracking::detectObjects(HSV,frame);
	tracking::Object o = detectCarAt12oclock(cars);;
	ASSERT_FALSE(o.position.x != -1 && o.position.y !=-1 && o.area != -1);
}

TEST(RecognitionTest, Detect9CarFalse) {
	testFileWrite("Detect9CarFalse");
	cv::Mat HSV;
	cv::Mat frame = cv::imread(sourceDirectory+"/TestProjects/Assets/mask.jpg");
	cv::cvtColor(frame,HSV,cv::COLOR_BGR2HSV);
	std::vector<tracking::Object> cars = tracking::detectObjects(HSV,frame);
	tracking::Object o = detectCarAt9oclock(cars);;
	ASSERT_FALSE(o.position.x != -1 && o.position.y !=-1 && o.area != -1);
}

TEST(RecognitionTest, Detect3CarFalse) {
	testFileWrite("Detect3CarFalse");
	cv::Mat HSV;
	cv::Mat frame = cv::imread(sourceDirectory+"/TestProjects/Assets/mask.jpg");
	cv::cvtColor(frame,HSV,cv::COLOR_BGR2HSV);
	std::vector<tracking::Object> cars = tracking::detectObjects(HSV,frame);
	tracking::Object o = detectCarAt3oclock(cars);
	ASSERT_FALSE(o.position.x != -1 && o.position.y !=-1 && o.area != -1);
}

TEST(RecognitionTest, DetectMovementFalse){	
	testFileWrite("DetectMovementFalse");
	cv:: VideoCapture cap;
	cap.open(sourceDirectory+"/TestProjects/Assets/bubbs.mp4");

	int carPassed = 0;
	cv::Mat frame, HSV;
	while(carPassed <2  == false){
	
	cap >> frame;
	if(frame.empty() == false){
	cv::cvtColor(frame,HSV,cv::COLOR_BGR2HSV);
	}
	else{
		cap.release();
	}
	if(tracking::scanForMovement(HSV, frame,200)){
		carPassed++;
		}
	}
	ASSERT_TRUE(carPassed==2);
}






TEST(ClassificationTest, DetectStopsignTrue){
	testFileWrite("DetectStopSignTrue");
	cv::Mat frame = cv::imread(sourceDirectory+"/TestProjects/Assets/stopSign.png");
    tracking::LoadCascades();
	ASSERT_TRUE(tracking::detectStopSigns(frame));
}
TEST(ClassificationTest, DetectStopsignFalse){
	testFileWrite("DetectStopsignFalse");
	cv::Mat frame = cv::imread(sourceDirectory+"/TestProjects/Assets/mask.jpg");
	tracking::LoadCascades();
	ASSERT_FALSE(tracking::detectStopSigns(frame));
}


TEST(DrivingTest, NoStopSign){
	testFileWrite("NoStopSign");
	carMock mockeryCar;
	cv::Mat frame = cv::imread(sourceDirectory+"/TestProjects/Assets/mask.jpg");
	tracking::LoadCascades();

	using ::testing::Return;
	EXPECT_CALL(mockeryCar, setPedal(0.0))
	.Times(1)
	.WillOnce(Return (true));

	doFollow(frame, false, &mockeryCar);
}
TEST(DrivingTest, YesStopSign){
	testFileWrite("YesStopSign");
	carMock mockeryCar;
	cv::Mat frame = cv::imread(sourceDirectory+"/TestProjects/Assets/stopsign.jpg");
	tracking::LoadCascades();

	using ::testing::Return;
	using ::testing::AtLeast;

	EXPECT_CALL(mockeryCar, setPedal(0.2))
	.Times(1)
	.WillRepeatedly(Return (true));

	EXPECT_CALL(mockeryCar, setPedal(0.1))
	.Times(1)
	.WillRepeatedly(Return (true));

	EXPECT_CALL(mockeryCar, setPedal(0.0))
	.Times(1)
	.WillRepeatedly(Return (true));

	EXPECT_CALL(mockeryCar, getFrontSensor())
	.Times(3)
	.WillOnce(Return(0.5))
	.WillOnce(Return(0.3))
	.WillOnce(Return(0.1));

	doFollow(frame, true, &mockeryCar);
}

TEST(DrivingTest, intersectionNoCar){
	testFileWrite("intersectionNoCar");
	carMock mockeryCar;
	cv::Mat frame = cv::imread(sourceDirectory+"/TestProjects/Assets/stopsign.jpg");
	cv::Mat HSV;
    cv::cvtColor(frame,HSV,cv::COLOR_BGR2HSV);

	setupIntersection(HSV, frame);

	using ::testing::Return;
	using ::testing::AtLeast;
	//These are for the hardcoded drive. Should be changed when 
	EXPECT_CALL(mockeryCar, setPedal(0.1))
	.Times(1);
	EXPECT_CALL(mockeryCar, setPedal(0.0))
	.Times(1);

	EXPECT_CALL(mockeryCar, setPedal(0.2))
	.Times(1);
	EXPECT_CALL(mockeryCar, getFrontSensor())
	.Times(2)
	.WillOnce(Return (15.0))
	.WillOnce(Return (11.0));
	EXPECT_CALL(mockeryCar, setPedal(0.0))
	.Times(1);

	EXPECT_CALL(mockeryCar, getFrontSensor())
	.Times(1)
	.WillRepeatedly(Return (0.5));

	doIntersection(HSV,frame, &mockeryCar);

}

TEST(DrivingTest, intersection2Car){
	testFileWrite("intersection2Car");
	carMock mockeryCar;
	cv::Mat frame = cv::imread(sourceDirectory+"/TestProjects/Assets/CarLeftRight.png");
	cv::Mat HSV;
    cv::cvtColor(frame,HSV,cv::COLOR_BGR2HSV);

	setupIntersection(HSV, frame);

	using ::testing::Return;
	using ::testing::AtLeast;
	//These are for the hardcoded drive. Should be changed when 
	EXPECT_CALL(mockeryCar, setPedal(0.1))
	.Times(1);
	EXPECT_CALL(mockeryCar, setPedal(0.0))
	.Times(1);

	//For driving through the intersection
	EXPECT_CALL(mockeryCar, setPedal(0.2))
	.Times(1);
	EXPECT_CALL(mockeryCar, getFrontSensor())
	.Times(1)
	.WillRepeatedly(Return (0.5));
	EXPECT_CALL(mockeryCar, setPedal(0.0))
	.Times(1);

	doIntersection(HSV,frame, &mockeryCar);

}

TEST(Final, MemoryBroke){
	printf("Virtual memory: %i : Physichal Memory: %i \n", vMemThresholdBroke, pMemThresholdBroke);
	ASSERT_EQ(vMemThresholdBroke, 0);
	ASSERT_EQ(pMemThresholdBroke, 0);
}
int main(int argc, char **argv) {
	sourceDirectory = "/~/git/group_09/src";
	tracking::LoadCascades();
	testing::InitGoogleTest(&argc, argv);
	testing::InitGoogleMock(&argc, argv);
	file.open((sourceDirectory+"/TestProjects/MemoryInformation/TestMemoryInfo.txt"));

	std::thread memoryChecker (memoryCheckCompilation);

	int result = RUN_ALL_TESTS();
	memoryShouldBeChecked = false;
	memoryChecker.join();
	//return result;
	return 0;
}



