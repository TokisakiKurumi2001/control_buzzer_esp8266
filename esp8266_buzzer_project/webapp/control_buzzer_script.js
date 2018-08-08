$(function(){
	// pass the address of the device
	var device = new Device("192.168.1.32");

	// when the button is pressed, call the built-in function I already made in the .ino file
	$("#on").click(function(){
		device.callFunction('led', 0); // the right parameters is 0 to make the buzzer speak
	});
});