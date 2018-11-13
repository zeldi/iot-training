var request = require("request");

var send_stream = function(data){
    var device = "YOUR_ID_DEVELOPER_DEVICE";
    var apikey =  "YOUR APIKEY";

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

var datastream = {
  temp: '26', 
  hum: '40'
}

send_stream(datastream);

