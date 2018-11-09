var request = require("request");
var sensor = require('node-dht-sensor');

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

var readDHT11 = function() {
   var result = sensor.read(11,4);
   console.log('temp: ' + result.temperature.toFixed(1) + ' Celcius');
   console.log('humidity: ' + result.humidity.toFixed(1) + ' %');

   var datastream = {
      temp : result.temperature.toFixed(1),
      hum : result.humidity.toFixed(1)
   }

   send_stream(datastream);	
}


setInterval(readDHT11,2000);

