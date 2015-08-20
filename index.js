var barcodeReader = require('./build/Release/barcode-reader');

var BarcoderReader = function() {

	function readData(address, callback) {
		barcodeReader.readData(address, callback);
	}

	return {
		readData : readData
	}
}
module.exports = BarcoderReader();