var http = require('http')

http.createServer(function(req,res) {
    res.end("Hello, This is Nodejs webserver on  Raspberry Pi");
}).listen(8080)


 console.log("Webserver running on port 8080");
