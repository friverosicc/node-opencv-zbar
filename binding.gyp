{
	"targets": [
		{
			"target_name": "asyncprogressworker",
			"sources": [ "src/barcode_reader.cc" ],
			"include_dirs" : [
				"<!@(pkg-config --cflags opencv)",
				"<!(node -e \"require('nan')\")"
			],
			"libraries": [
				"<!@(pkg-config --libs opencv)",
				"-lzbar"
            ],		
			"cflags!" : [ "-fno-exceptions"],
			"cflags_cc!": [ "-fno-rtti",  "-fno-exceptions"],
		}
	],
}