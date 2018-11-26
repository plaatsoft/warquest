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
**  All copyrights reserved (c) 1996-2016 PlaatSoft
*/

var timer1;
var value1;
var max1;
var step1;
var cycle1;
var timerId1;

function healthtimer(in1, in2, in3, in4, in5){
  timer1=in1;
  value1=in2;
  max1=in3;
  step1=in4;
  cycle1=in5;
}

function healthcountdown(){

  if(timer1>0) {

     minuten=Math.floor((timer1)/60);
     seconden=Math.floor(timer1-minuten*60);
 
     if (minuten.toString().length < 2) minuten = "0" + minuten;
     if (seconden.toString().length < 2) seconden = "0" + seconden;
 
	  var zichttijd="";
	  if (value1<max1) {
			zichttijd="+"+step1+" in "+minuten+":"+seconden;
	  }
	  
	  document.getElementById("healthcountdown").innerHTML=zichttijd;  
	  document.getElementById("healthvalue").innerHTML=value1.toString(); 
	  
     timer1=timer1-1;
     timerId1=setTimeout("healthcountdown()",1000); 
     
  }
  
  else {

		if (timer1==0) {

			value1=value1+step1;
			if (value1>max1) value1=max1;
	  
			timer1=cycle1;
			timerId1=setTimeout("healthcountdown()",0); 
		}
		document.getElementById("healthvalue").innerHTML=value1.toString(); 
  } 
}

function healthStopTimer() {
	clearTimeout(timerId1);
}
