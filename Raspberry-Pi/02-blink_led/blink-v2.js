// Blink every 250 ms, stop after 5 seconds

var Gpio = require("onoff").Gpio;
var PIN = 17; 

var LED = new Gpio(PIN,'out');

var blinkInterval = setInterval(blinkLED,250);

function blinkLED() {
	if (LED.readSync() === 0)
		LED.writeSync(1);
	else
		LED.writeSync(0);
}


function stopBlink() {
	clearInterval(blinkInterval);
	LED.writeSync(0);
	LED.unexport();
}

setTimeout(stopBlink,5000);
