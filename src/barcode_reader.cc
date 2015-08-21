#include <nan.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <zbar.h>
#include <iomanip>
#include <string>
#include <time.h>

using namespace Nan;
using namespace std;
using namespace cv;
using namespace zbar;

class BarcodeReader : public AsyncProgressWorker {
	public: 

	BarcodeReader(	Callback *callback,
					Callback *progress, 
					char *cam_address,
					int device_number) : 
					AsyncProgressWorker(callback),
					progress(progress),
					cam_address(cam_address),
					device_number(device_number) {}

	~BarcodeReader() {}

	void Execute(const AsyncProgressWorker::ExecutionProgress &progress) {				
		VideoCapture cap;			
		time_t first_decoded;
		time_t last_decoded;
		string last_barcode_decoded("");		
		
		// Check if we need to open a device by address or id
		if(device_number == -1)	
			cap.open(cam_address);
		else 
			cap.open(device_number);

		if (!cap.isOpened()) {
			cout << "Could not open camera." << endl;
			exit(EXIT_FAILURE);
		} 
		cout << "Cam opened" << endl;		

		// Create a zbar reader
		ImageScanner scanner;
    
		// Configure the reader
		scanner.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 1);

		for (;;) {
         
			// Capture an OpenCV frame
			cv::Mat frame, frame_grayscale;
			cap >> frame;

			// Convert to grayscale
			cvtColor(frame, frame_grayscale, CV_BGR2GRAY);

			// Obtain image data
			int width = frame_grayscale.cols;
			int height = frame_grayscale.rows;
			uchar *raw = (uchar *)(frame_grayscale.data);

			// Wrap image data
			Image image(width, height, "Y800", raw, width * height);
			
			// Scan the image for barcodes			
			scanner.scan(image);

			if(image.symbol_begin() != image.symbol_end()) {
				time(&last_decoded);
				double diff = difftime(last_decoded, first_decoded);
				time(&first_decoded);

				// Extract results
				int counter = 0;
				for (Image::SymbolIterator symbol = image.symbol_begin(); symbol != image.symbol_end(); ++symbol) {				
					
					char *data = new char[symbol->get_data().size() + 1];
					copy(symbol->get_data().begin(), symbol->get_data().end(), data);
					string new_barcode(data);					

					if(diff >= 2 || last_barcode_decoded.compare(new_barcode) != 0) {						
						progress.Send(reinterpret_cast<const char*>(data), sizeof(symbol->get_data()));
						last_barcode_decoded = new_barcode;
					}
					
					counter++;
				}
			} 

		}	
	}

	void HandleProgressCallback(const char *data, size_t size) {
		HandleScope scope;		

		v8::Local<v8::Value> argv[] = {
			New<v8::String>(data).ToLocalChecked()
		};

		progress->Call(1, argv);
	}

	private:
		Callback *progress;
		char *cam_address;		
		int device_number;
};

NAN_METHOD(ReadData) {
	Callback *progress = new Callback(info[1].As<v8::Function>());
	Callback *callback = new Callback(info[2].As<v8::Function>());	
	char *address = new char[50];
	int device_number = -1;

	if(!info[0]->IsNumber()) { 
		v8::String::Utf8Value path(info[0]->ToString());		
		strcpy(address, *path);
	} else {
		device_number = To<uint32_t>(info[0]).FromJust();
	}

	AsyncQueueWorker(new BarcodeReader(
		callback,
		progress,
		address,
		device_number));
}

NAN_MODULE_INIT(Init) {	
	Set(target,
		New<v8::String>("readData").ToLocalChecked(),
		New<v8::FunctionTemplate>(ReadData)->GetFunction());
}

NODE_MODULE(asyncprogressworker, Init)