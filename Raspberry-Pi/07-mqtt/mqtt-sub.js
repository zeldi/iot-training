var mqtt    = require('mqtt');
var client  = mqtt.connect("mqtt:m15.cloudmqtt.com",{username:"tbtnsrke",password:'M93l7HPVUSiu',port:15704});

console.log("MQTT Connection flag = " + client.connected);

//handle incoming messages
client.on('message',function(topic, message, packet){
        console.log("message is "+ message);
        console.log("topic is "+ topic);
        console.log("message is " + message);

        jsonMsg = JSON.parse(message);
        console.log(jsonMsg.sensor_id);
        // client.end();
});


client.on("connect",function(){
        console.log("MQTT Connected flag =  "+ client.connected);
        client.subscribe('sensor/testsensor');
})