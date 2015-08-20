var barcodeReader = require('./build/Release/barcode-reader');

var BarcoderReader = function() {

	function readData(address, callback) {
		barcodReader.readData(address, callback);
	}
}
module.exports = BarcoderReader();