# node-opencv-zbar
This nodejs addon uses the opencv library to connect to webcams or video files and the zbar library to scan the images looking for barcodes.

## Requirements
* [Nodejs]
* [Nan]
* [OpenCV]
* [Zbar]

## Installation
To use node-opencv-zbar you have to install OpenCV and Zbar

```bash
npm install node-opencv-zbar
```

## Usage
```
var barcodeReader = require('node-opencv-zbar');

barcodeReader.readData(addres_to_file | address_to_ip_cam | id_device, [time_interval], function(data) {
	console.log(data); // Barcode captured
});

```

