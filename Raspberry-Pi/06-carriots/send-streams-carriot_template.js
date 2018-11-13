var https = require("https");

var get_data = function() {
  return "helllo";
}

var send_stream = function(data){
    var device = "YOUR_ID_DEVELOPER_DEVICE"
    var apikey = "YOUR APIKEY"
    var stream = "{'protocol':'v2','device':'"+device+"','at':'now','data':{'key': '"+data+"'}}"

    var options = {
      host: "api.carriots.com",
      path: "/streams",
      method: "POST",
      headers: {"User-Agent": "NodeJS-carriots.com-Client",
                "Content-Type" : "application/vnd.carriots.api.v2+json;q=7",
                "Accept": "application/vnd.carriots.api.v2+json;q=7",
                "Content-Length": stream.length,
                "Carriots.apikey": apikey}
    };

    var req = https.request(options, function(response) {
      console.log("STATUS: " + response.statusCode);
      //console.log("HEADERS: " + JSON.stringify(response.headers));
      response.setEncoding("utf8");
      response.on("data", function (chunk) {
        console.log("BODY: " + chunk);
      });
    });

    req.on("error", function(e) {
      console.log("problem with request: " + e.message);
    });

    req.write(stream);
    req.end();
};

var data = get_data();
console.log(data);


//send_stream("Value");