var barcodeReader 	= require('./build/Release/barcode-reader');
var _ 				= require('underscore');

var BarcoderReader = function() {

	/**
	 * Reads the barcodes captured in a video file or cam.
	 *
	 * @param 'address' Address to a ipcam or video file or number of a webcam device
	 * @param 'time' Optional value, this is the time interval that the application uses to 
	 * evaluate new barcodes
	 * @param 'callback' Function called when barcode is captured
	 */
	function readData(address, time, callback) {
		if(_.isFunction(time)) {
			callback = time;
			time = 0;
		}

		barcodeReader.readData(address, time, callback);
	}

	return {
		readData : readData
	}
}
module.exports = BarcoderReader();