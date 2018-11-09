var sensor = require('node-dht-sensor');

const DHT_TYPE = 11; // DHT11 Sensor
const GPIO_PIN = 4; // GPIO4

var readDHT11 = function() {
   var result = sensor.read(DHT_TYPE,GPIO_PIN);
   console.log('temp: ' + result.temperature.toFixed(1) + ' Celcius');
   console.log('humidity: ' + result.humidity.toFixed(1) + ' %');
 }

var test = function(name) {
  console.log("Hello ",name);
}

setInterval(readDHT11,2000);
