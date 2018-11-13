var request = require("request");
var mqtt    = require('mqtt');

var client  = mqtt.connect("mqtt:m15.cloudmqtt.com",{username:"tbtnsrke",password:'M93l7HPVUSiu',port:15704});

console.log("MQTT Connection flag = " + client.connected);

client.on("connect",function(){
        console.log("MQTT Connected flag =  "+ client.connected);
        client.subscribe('sensor/dht11');
})

//handle incoming messages
client.on('message',function(topic, message, packet){
        console.log("topic is "+ topic);
        console.log("message is " + message);

        // Parse message to JSON
        dhtData = JSON.parse(message);
        // send data stream to IOT Platform
        send_stream(dhtData);
});


var send_stream = function(data){
        var device = 'AP_1@zeldi.suryady' //"YOUR_ID_DEVELOPER_DEVICE"
        var apikey = "66c1a5d2c2d8546ef20295bf3d8824467aafec8cb22525432c8d77244aa79447" //"YOUR APIKEY"
    
        var options = { 
          method: 'POST',
          url: 'http://api.altairsmartcore.com/streams/',
          headers: 
           { 
             'cache-control': 'no-cache',
             'carriots.apikey': apikey,
             'Content-Type': 'application/json' },
          body: 
           { protocol: 'v2',
             checksum: '',
             device: device,
             at: 'now',
             data: data //{ temp: '26', hum: '40%' } 
            },
          json: true 
        };
    
        request(options, function (error, response, body) {
          if (error) throw new Error(error);
    
          console.log(body);
        });
    
};

