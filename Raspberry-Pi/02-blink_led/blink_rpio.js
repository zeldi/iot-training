var rpio = require('rpio');

var PIN = 11; /* PIN11/GPIO17 */

rpio.open(PIN,rpio.OUTPUT,rpio.LOW);

// Loop  to blink 5 times

for (var i=0;i<5;i++) {
	rpio.write(PIN,rpio.HIGH);
	rpio.sleep(1);
	rpio.write(PIN,rpio.LOW);
	rpio.sleep(1);
}
