var express = require('express');
app = express();
server = require('http').createServer(app);
io = require('socket.io').listen(server);
var fs = require('fs');

var SerialPort = require('serialport');

var port = new SerialPort('/dev/ttyACM0', {
  parser: SerialPort.parsers.readline('\n')
});

server.listen(8000);
app.use(express.static('client'));		

var hullCode = 0;
var panCode = 0;
var tiltCode = 0;

port.on('data', function (input) {
	var values;
	values = input.split(","); 
	if(values[0].localeCompare("data") == 0){
		io.sockets.emit('compassHeading', {value: values[1] });
		io.sockets.emit('panAngle', {value: values[2] });
		io.sockets.emit('tiltAngle', {value: values[3] });
	}
	
});

io.sockets.on('connection', function (socket) {
	console.log("connected");
	socket.on('hullControl', function (data) {
		hullCode = data.value;
		console.log("Hull code:" + hullCode);
		writeToSerial();

	});
	socket.on('panControl', function (data) {
		panCode = data.value;
		writeToSerial();

	});
	socket.on('tiltControl', function (data) {
		tiltCode = data.value;
		writeToSerial();

	});	
});
console.log("running");

function writeToSerial(){
	var output = hullCode + "," + panCode + "," + tiltCode + "\n" ;
	port.write(output);
}

