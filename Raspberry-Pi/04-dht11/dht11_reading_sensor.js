/*
    desc: read temperature and humidity data from dht11 sensor 
*/

var sensor = require("node-dht-sensor");

const DHT_TYPE  = 11;
const GPIO_PIN = 17; 
readSensor = function() {
    var data = sensor.read(DHT_TYPE,GPIO_PIN);
    console.log('Temperature :  ' + data.temperature.toFixed(1) + ' Celcius');
    console.log('Humidity    :  ' + data.humidity.toFixed(1) + ' %');
}


readSensor();

