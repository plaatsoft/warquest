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

var timer4;
var value4;
var step4;
var timerId4;

function moneytimer(in1,in2,in3){
  timer4=in1;
  value4=in2;
  step4=in3;
}

function moneyaddcommas(nStr)
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


function moneycountdown(){

  if(timer4>=0) {

     minuten=Math.floor((timer4)/60);
     seconden=Math.floor(timer4-minuten*60);
 
     if (minuten.toString().length < 2) minuten = "0" + minuten;
     if (seconden.toString().length < 2) seconden = "0" + seconden;
 
     var zichttijd=minuten+":"+seconden;
	  
     document.getElementById("moneycountdown").innerHTML=zichttijd; 
	  document.getElementById("moneyvalue").innerHTML='<span class="money">' + moneyaddcommas(value4).toString() + '</span>'; 

     timer4=timer4-1;
     timerId4=setTimeout("moneycountdown()",1000); 
     
  }
  
  else {
	
		value4=value4+step4;
	  
		timer4=3600;
		timerId4=setTimeout("moneycountdown()",0); 
		
		document.getElementById("moneyvalue").innerHTML='<span class="money">' + moneyaddcommas(value4).toString()  + '</span>'; 
  } 
}

function moneyStopTimer(){
	clearTimeout(timerId4);
}
