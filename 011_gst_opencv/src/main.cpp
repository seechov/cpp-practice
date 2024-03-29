#include <stdio.h>
#include <iostream>
// #include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

int main(int argc, char** argv) {
	printf("Opencv build info: %s.", cv::getBuildInformation().c_str());
	cv::Mat frame;
	cv::VideoCapture cap;
	int deviceID = 1;			// 0 = open default camera
	int apiID = cv::CAP_ANY;	// 0 = autodetect default API
	cap.open(deviceID, apiID);
	// check if we succeeded
	if (!cap.isOpened()) {
		printf("ERROR! Unable to open camera\n");
		return -1;
	}
	int codec = cv::VideoWriter::fourcc('x', '2', '6', '4');  // select desired codec (must be available at runtime)
	cv::VideoWriter writer;
	writer.open("appsrc ! videoconvert ! x264enc noise-reduction=10000 tune=zerolatency byte-stream=true threads=4 ! mpegtsmux ! udpsink host=10.1.2.107 port=5000",
		cv::CAP_GSTREAMER,
		codec,
		16,
		cv::Size(640, 480),
		true);
	if (!writer.isOpened()) {
		printf("=ERR= can't create video writer\n");
		return -1;
	}

	int i = 0;
	printf("Start grabbing\n");
	while (true)
	{

		// wait for a new frame from camera and store it into 'frame'
		cap.read(frame);
		// check if we succeeded
		if (frame.empty()) {
			printf("ERROR! blank frame grabbed\n");
			break;
		}

		time_t mytime = time(NULL);
		char* time_str = ctime(&mytime);
		time_str[strlen(time_str) - 1] = '\0';
		printf("[%s] Frame was captured.\n", time_str);

		cv::Mat frame_resized;
		resize(frame, frame_resized, cv::Size(640, 480), 0, 0, cv::INTER_CUBIC);

		putText(frame_resized, time_str, cv::Point(20, 20),
			cv::FONT_HERSHEY_COMPLEX_SMALL, 0.8, cv::Scalar(200, 200, 250), 1, cv::LINE_AA);

		writer.write(frame_resized);
		cv::String filename = cv::format("frame_%d.jpg", i++);
		// cv::imwrite(filename, frame);
	}
	// the camera will be deinitialized automatically in VideoCapture destructor
	return 0;
}
