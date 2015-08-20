var barcodeReader = require('./build/Release/barcode-reader');

var BarcoderReader = function() {

	function readData(address, callback) {
		barcodReader.readData(address, callback);
	}

	return {
		readData : readData
	}
}
module.exports = BarcoderReader();