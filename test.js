var addon = require('./build/Release/addon');

var callback = function(data) {
	console.log('callback');
};

var readData = function(data) {	
	console.log(data);
};

addon.doProgress('', 100, camera113, callback);
addon.doProgress('rtsp://admin:admin@192.168.1.111:554/', 100, camera111, callback);
// addon.doProgress('192.168.1.111', 100, progress, callback);
// addon.doProgress('192.168.1.112', 100, progress, callback);
// addon.doProgress('192.168.1.113', 100, progress, callback);
// // addon.doProgress(10, 100, progress, callback);
// addon.doProgress(10, 100, progress, callback);

console.log('after call doProgress');