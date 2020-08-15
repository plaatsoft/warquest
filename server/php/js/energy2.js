/*
**  ========
**  WarQuest
**  ========
**
**  Created by wplaat
**
**  For more information visit the following website.
**  Website : www.plaatsoft.nl
**
**  Or send an email to the following address.
**  Email   : info@plaatsoft.nl
**
**  All copyrights reserved (c) PlaatSoft
*/

var timer2;
var value2;
var max2;
var step2;
var timerId2;
var cycle2;

function energytimer(in1,in2,in3,in4,in5){
  timer2=in1;
  value2=in2;
  max2=in3;
  step2=in4;
  cycle2=in5;
}

function energyaddcommas(nStr)
{
	nStr += '';
	x = nStr.split('.');
	x1 = x[0];
	x2 = x.length > 1 ? '.' + x[1] : '';
	var rgx = /(\d+)(\d{3})/;
	while (rgx.test(x1)) {
		x1 = x1.replace(rgx, '$1' + '.' + '$2');
	}
	return x1 + x2;
}

function energycountdown(){

  if(timer2>0) {

     minuten=Math.floor((timer2)/60);
     seconden=Math.floor(timer2-minuten*60);

     if (minuten.toString().length < 2) minuten = "0" + minuten;
     if (seconden.toString().length < 2) seconden = "0" + seconden;

	  var zichttijd="";
	  if (value2<max2) {
			zichttijd="+"+step2+" in "+minuten+":"+seconden;
	  }

	  document.getElementById("energycountdown").innerHTML=zichttijd;
	  document.getElementById("energyvalue").innerHTML=energyaddcommas(value2).toString();

     timer2=timer2-1;
     timerId2=setTimeout("energycountdown()",1000);

  }

  else {

		if (timer2==0) {

			value2=value2+step2;
			if (value2>max2) value2=max2;

			timer2=cycle2;
			timerId2=setTimeout("energycountdown()",0);
		}
		document.getElementById("energyvalue").innerHTML=energyaddcommas(value2).toString();
  }
}

function energyStopTimer() {
	clearTimeout(timerId2);
}
