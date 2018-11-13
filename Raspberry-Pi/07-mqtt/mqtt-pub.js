var mqtt    = require('mqtt');
var sensor = require('node-dht-sensor');

var client  = mqtt.connect("mqtt:m15.cloudmqtt.com",{username:"tbtnsrke",password:'M93l7HPVUSiu',port:15704});

console.log("MQTT Connection flag = " + client.connected);

//handle incoming messages
client.on('message',function(topic, message, packet){
});


client.on("connect",function(){
        console.log("MQTT Connected flag =  "+ client.connected);

        // start reading data from sensor GPIO after connection to MQTT Broker
        var datastream =  readDHT11();

        client.publish('sensor/dht11',datastream);
})


var readDHT11 = function() {
        var result = sensor.read(11,17);
        console.log('temp: ' + result.temperature.toFixed(1) + ' Celcius');
        console.log('humidity: ' + result.humidity.toFixed(1) + ' %');
     
        var sensorData = {
           temp : result.temperature.toFixed(1),
           hum : result.humidity.toFixed(1)
        }
     
        return sensorData;	
}