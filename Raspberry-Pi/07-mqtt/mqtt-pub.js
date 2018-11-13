var mqtt    = require('mqtt');
var client  = mqtt.connect("mqtt:m15.cloudmqtt.com",{username:"tbtnsrke",password:'M93l7HPVUSiu',port:15704});

console.log("MQTT Connection flag = " + client.connected);

//handle incoming messages
client.on('message',function(topic, message, packet){
});


client.on("connect",function(){
        console.log("MQTT Connected flag =  "+ client.connected);
        var json = {
                    sensor_id : "temperature",
                    value : 100
                    };
            // Convert the JSON object to a string
        var str = JSON.stringify(json);

        client.publish('sensor/testsensor',str);
})
