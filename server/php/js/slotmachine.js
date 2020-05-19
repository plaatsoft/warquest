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

peartop=new Image(80,40);
peartop.src="images/slotmachine/peartop.jpg";

pearbtm=new Image(80,40);
pearbtm.src="images/slotmachine/pearbtm.jpg";

pear=new Image(80,80);
pear.src="images/slotmachine/pear.jpg";

appletop=new Image(80,40);
appletop.src="images/slotmachine/appletop.jpg";

applebtm=new Image(80,40);
applebtm.src="images/slotmachine/applebtm.jpg";

apple=new Image(80,80);
apple.src="images/slotmachine/apple.jpg";

bartop=new Image(80,40);
bartop.src="images/slotmachine/bartop.jpg";

barbtm=new Image(80,40);
barbtm.src="images/slotmachine/barbtm.jpg";

bar=new Image(80,80);
bar.src="images/slotmachine/bar.jpg";

bananatop=new Image(80,40);
bananatop.src="images/slotmachine/bananatop.jpg";

bananabtm=new Image(80,40);
bananabtm.src="images/slotmachine/bananabtm.jpg";

banana=new Image(80,80);
banana.src="images/slotmachine/banana.jpg";

grapetop=new Image(80,40);
grapetop.src="images/slotmachine/grapetop.jpg";

grapebtm=new Image(80,40);
grapebtm.src="images/slotmachine/grapebtm.jpg";

grape=new Image(80,80);
grape.src="images/slotmachine/grape.jpg";

orangetop=new Image(80,40);
orangetop.src="images/slotmachine/orangetop.jpg";

orangebtm=new Image(80,40);
orangebtm.src="images/slotmachine/orangebtm.jpg";

orange=new Image(80,80);
orange.src="images/slotmachine/orange.jpg";

pinetop=new Image(80,40);
pinetop.src="images/slotmachine/pinetop.jpg";

pinebtm=new Image(80,40);
pinebtm.src="images/slotmachine/pinebtm.jpg";

pine=new Image(80,80);
pine.src="images/slotmachine/pine.jpg";

spintop=new Image(80,40);
spintop.src="images/slotmachine/spintop.jpg";

spinbtm=new Image(80,40);
spinbtm.src="images/slotmachine/spinbtm.jpg";

spin=new Image(80,80);
spin.src="images/slotmachine/spin.jpg";

Held=new Array("false","false","false");
Line=new Array(0,0,0);
Reel0=new Array("pine","grape","pear","pine","banana","orange","grape","bar","pear","banana","apple","banana","pear","pine","banana","apple","orange","pine","pear","banana","orange");
Reel1=new Array("pear","bar","orange","pine","pear","banana","orange","apple","grape","pear","banana","pine","orange","apple","pear","grape","banana","orange","pine","apple","orange");
Reel2=new Array("banana","pear","pine","orange","banana","grape","apple","pine","pear","banana","orange","grape","apple","pear","bar","pine","banana","orange","pear","banana","orange");

Result=new Array(3);
Result[0] = new Array("","","");
Result[1] = new Array("","","");
Result[2] = new Array("","","");

var bet=0;
var key=0;
var token;

function Init(a00,a01,a02,a10,a11,a12,a20,a21,a22,bet1, key1, token1) {

	Held[0]="false";
	Held[1]="false";
	Held[2]="false";
	
	document.getElementById("Hold0").style.display = 'none';
	document.getElementById("Hold1").style.display = 'none';
	document.getElementById("Hold2").style.display = 'none';
	
	Result[0][0] = a00;
	Result[0][1] = a01;
	Result[0][2] = a02;

	Result[1][0] = a10;
	Result[1][1] = a11;
	Result[1][2] = a12;
	
	Result[2][0] = a20;
	Result[2][1] = a21;
	Result[2][2] = a22;
	
	HeldCheck=0;
	
	bet=bet1;
	key=key1;
	token=token1;
}

function Show() {
	
	document.r0top.src=eval(Result[0][0]);
	document.r0main.src=eval(Result[0][1]);
	document.r0btm.src=eval(Result[0][2]);

	document.r1top.src=eval(Result[1][0]);
	document.r1main.src=eval(Result[1][1]);
	document.r1btm.src=eval(Result[1][2]);
	
	document.r2top.src=eval(Result[2][0]);
	document.r2main.src=eval(Result[2][1]);
	document.r2btm.src=eval(Result[2][2]);		
}

function Go()
{
	if (Held[0]=="false") {
		Line[0]=0;
		document.r0top.src=spintop.src;
		document.r0main.src=spin.src;
		document.r0btm.src=spinbtm.src;
	}

	if (Held[1]=="false") {
		Line[1]=0;
		document.r1top.src=spintop.src;
		document.r1main.src=spin.src;
		document.r1btm.src=spinbtm.src;
	}
	
	if (Held[2]=="false") {
		Line[2]=0;
		document.r2top.src=spintop.src;
		document.r2main.src=spin.src;
		document.r2btm.src=spinbtm.src;
	}

	x1=0;
	setTimeout('Spin()','150')
}

function Spin() {

	if (x1==3) {			
			
				
		if (HeldCheck==1) {
		
			document.getElementById("Hold0").style.display = 'none';
			document.getElementById("Hold1").style.display = 'none';
			document.getElementById("Hold2").style.display = 'none';
			
			Wincheck();
			
		} else {
		
			document.getElementById("Hold0").style.display = 'inline';
			document.getElementById("Hold1").style.display = 'inline';
			document.getElementById("Hold2").style.display = 'inline';
	
			HeldCheck=1;
		}
	}
	if (Held[x1]=="false")
	{
		rt=eval("document.r"+x1+"top");
		rm=eval("document.r"+x1+"main");
		rb=eval("document.r"+x1+"btm");
		Line[x1]=Math.round(20*Math.random());
		spunreel=eval("Reel"+x1);
		topnum=eval(Line[x1]+1);
		if(topnum>20)
		{
			topnum=topnum-21
		}
		if(topnum<0)
		{
			topnum=topnum+21
		}
		btmnum=eval(Line[x1]-1);
		if(btmnum>20)
		{
			btmnum=btmnum-21
		}
		if(btmnum<0)
		{
			btmnum=btmnum+21
		}
		rt.src=eval(spunreel[topnum]+"top.src");
		rm.src=eval(spunreel[Line[x1]]+".src");
		rb.src=eval(spunreel[btmnum]+"btm.src")
		
		Result[x1][0]=spunreel[topnum]+"top.src";
		Result[x1][1]=spunreel[Line[x1]]+".src";
		Result[x1][2]=spunreel[btmnum]+"btm.src";		
	}
	x1=x1+1;
	setTimeout('Spin()','150')
}

function Wincheck() {

	SmallLeft=Reel0[Line[0]]+Reel1[Line[1]];
	SmallRight=Reel1[Line[1]]+Reel2[Line[2]];
	Large=Reel0[Line[0]]+Reel1[Line[1]]+Reel2[Line[2]];
	if(Large=="barbarbar") {
		simpleHttpRequest(75, bet);
	} else if(Large=="grapegrapegrape") {
		simpleHttpRequest(50, bet);
	} else if(Large=="appleappleapple") {
		simpleHttpRequest(40, bet);
	} else if(Large=="pinepinepine") {
		simpleHttpRequest(30, bet);
	} else if(Large=="pearpearpear") {
		simpleHttpRequest(20, bet);
	} else if(Large=="orangeorangeorange") {
		simpleHttpRequest(15, bet);
	} else if(Large=="bananabananabanana") {
		simpleHttpRequest(10, bet);
	} else if(SmallLeft=="orangeorange") {
		simpleHttpRequest(1, bet);
	} else if(SmallLeft=="pearpear") {
		simpleHttpRequest(2, bet);
	} else if(SmallLeft=="grapegrape") {
		simpleHttpRequest(3, bet);
	} else if(SmallLeft=="appleapple") {
		simpleHttpRequest(4, bet);
	} else if(SmallLeft=="bananabanana") {
		simpleHttpRequest(5, bet);
	} else if(SmallLeft=="pinepine") {
		simpleHttpRequest(6, bet);
	} else if(SmallLeft=="barbar") {
		simpleHttpRequest(12, bet);
	} else if(SmallRight=="orangeorange") {
		simpleHttpRequest(1, bet);
	} else if(SmallRight=="pearpear") {
		simpleHttpRequest(2, bet);
	} else if(SmallRight=="grapegrape") {
		simpleHttpRequest(3, bet);
	} else if(SmallRight=="appleapple") {
		simpleHttpRequest(4, bet);
	} else if(SmallRight=="bananabanana") {
		simpleHttpRequest(5, bet);
	} else if(SmallRight=="pinepine") {
		simpleHttpRequest(6, bet);
	} else if(SmallRight=="barbar") {
		simpleHttpRequest(12, bet);
	} else {
		simpleHttpRequest(0, bet);
	}
}

function Hold(id) {

	if (Held[id]=="false") {
		document.getElementById("Hold"+id).style.display = 'none';	
		Held[id]="true";	
	} else {
		document.getElementById("Hold"+id).style.display = 'inline';	
		Held[id]="false";	
	}
}

function simpleHttpRequest(price, bet) {
 
	var form = document.forms['warquest'];

	var newInput1 = document.createElement('input');
	newInput1.setAttribute('type','hidden');
	newInput1.setAttribute('name','price');
	newInput1.setAttribute('value', price);
	form.appendChild(newInput1);		
	
	var newInput2 = document.createElement('input');
	newInput2.setAttribute('type','hidden');
	newInput2.setAttribute('name','token');
	newInput2.setAttribute('value', token);
	form.appendChild(newInput2);	

	var newInput3 = document.createElement('input');
	newInput3.setAttribute('type','hidden');	
	newInput3.setAttribute('name','a00');
	newInput3.setAttribute('value', Result[0][0]);
	form.appendChild(newInput3);		

	var newInput4 = document.createElement('input');
	newInput4.setAttribute('type','hidden');	
	newInput4.setAttribute('name','a01');
	newInput4.setAttribute('value', Result[0][1]);
	form.appendChild(newInput4);	

	var newInput5 = document.createElement('input');
	newInput5.setAttribute('type','hidden');	
	newInput5.setAttribute('name','a02');
	newInput5.setAttribute('value', Result[0][2]);
	form.appendChild(newInput5);	
			
	var newInput6 = document.createElement('input');
	newInput6.setAttribute('type','hidden');
	newInput6.setAttribute('name','a10');
	newInput6.setAttribute('value', Result[1][0]);
	form.appendChild(newInput6);		
	
	var newInput7 = document.createElement('input');
	newInput7.setAttribute('type','hidden');
	newInput7.setAttribute('name','a11');
	newInput7.setAttribute('value', Result[1][1]);
	form.appendChild(newInput7);	
	
	var newInput8 = document.createElement('input');
	newInput8.setAttribute('type','hidden');	
	newInput8.setAttribute('name','a12');
	newInput8.setAttribute('value', Result[1][2]);
	form.appendChild(newInput8);
	
	var newInput9 = document.createElement('input');
	newInput9.setAttribute('type','hidden');	
	newInput9.setAttribute('name','a20');
	newInput9.setAttribute('value', Result[2][0]);
	form.appendChild(newInput9);		
	
	var newInput10 = document.createElement('input');
	newInput10.setAttribute('type','hidden');
	newInput10.setAttribute('name','a21');
	newInput10.setAttribute('value', Result[2][1]);
	form.appendChild(newInput10);	
	
	var newInput11 = document.createElement('input');
	newInput11.setAttribute('type','hidden');
	newInput11.setAttribute('name','a22');
	newInput11.setAttribute('value', Result[2][2]);
	form.appendChild(newInput11);
	
		var newInput12 = document.createElement('input');
	newInput12.setAttribute('type','hidden');
	newInput12.setAttribute('name','bet');
	newInput12.setAttribute('value', bet);
	form.appendChild(newInput12);
	
	var newInput13 = document.createElement('input');
	newInput13.setAttribute('type','hidden');
	newInput13.setAttribute('name','key');
	newInput13.setAttribute('value', key);
	form.appendChild(newInput13);
	
	form.submit();	
}

