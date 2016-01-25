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
**  All copyrights reserved (c) 2008-2016 PlaatSoft
*/

var timer3;
var value3;
var max3;
var step3;
var timerId3;
var cycle3;

function ammotimer(in1,in2,in3,in4,in5){
  timer3=in1;
  value3=in2;
  max3=in3;
  step3=in4;
  cycle3=in5;
}

function ammocountdown(){

  if(timer3>0) {

     minuten=Math.floor((timer3)/60);
     seconden=Math.floor(timer3-minuten*60);
 
     if (minuten.toString().length < 2) minuten = "0" + minuten;
     if (seconden.toString().length < 2) seconden = "0" + seconden;
 
	  var zichttijd="";
	  if (value3<max3) {
			zichttijd="+"+step3+" in "+minuten+":"+seconden;
	  }
	  
	  document.getElementById("ammocountdown").innerHTML=zichttijd;  
	  document.getElementById("ammovalue").innerHTML=value3.toString(); 
	  
     timer3=timer3-1;
     timerId3=setTimeout("ammocountdown()",1000); 
     
  } else {

		if (timer3==0) {
			value3=value3+step3;
			if (value3>max3) value3=max3;
	  
			timer3=cycle3;
			timerId3=setTimeout("ammocountdown()",0); 
		}
		document.getElementById("ammovalue").innerHTML=value3.toString(); 
  } 
}

function ammoStopTimer() {
	clearTimeout(timerId3);
}
	
