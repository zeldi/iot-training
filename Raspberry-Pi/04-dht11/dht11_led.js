/*
    desc: read temperature data and blink led if temperature reach certain threshold
*/

var sensor = require("node-dht-sensor");
var Gpio = require("onoff").Gpio;

const LED_PIN = 14; 
const DHT_TYPE  = 11;
const GPIO_PIN = 17; 
const THRESHOLD = 30;

var LED = new Gpio(LED_PIN,'out');
var blinkInterval;

readSensor = function() {
    var data = sensor.read(DHT_TYPE,GPIO_PIN);
    console.log('Temperature :  ' + data.temperature.toFixed(1) + ' Celcius');
    console.log('Humidity    :  ' + data.humidity.toFixed(1) + ' %');

    return data;
}

blinkLED = function() {
	if (LED.readSync() === 0)
		LED.writeSync(1);
	else
		LED.writeSync(0);
}

stopBlink = function() {
	clearInterval(blinkInterval);
	LED.writeSync(0);
	LED.unexport();
}


var sensordata = readSensor();

if (sensordata.temperature > THRESHOLD ) {
    // blink the LED
    console.log("temperature = " + sensordata.temperature);
    blinkInterval = setInterval(blinkLED,250);
    setTimeout(stopBlink,5000);    
}
