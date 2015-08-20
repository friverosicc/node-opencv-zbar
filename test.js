var barcodeReader = require('./build/Release/barcode-reader');
console.log(barcodeReader);
var callback = function(data) {
	console.log('callback');
};

var readData = function(data) {	
	console.log(data);
};

barcodeReader.readData('rtsp://admin:admin@192.168.1.113:554/', readData, function() {});