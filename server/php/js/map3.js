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

var canvas = document.getElementById('myCanvas');
var ctx = canvas.getContext('2d');
var json = "";
var imageObj = new Image();
var clans = new Array();
var mid = 0;
var flag = true;
var url="";
var planet = 1;
var is_touch_device = 'ontouchstart' in document.documentElement;

function getBaseURL() {
	var url = location.href;  
	var baseURL = url.substring(0, url.indexOf('/', 14));


	if (baseURL.indexOf('http://127.0.0.1') != -1) {

		var url = location.href;  
		var pathname = location.pathname;  
		var index1 = url.indexOf(pathname);
		var index2 = url.indexOf("/", index1 + 1);
		var baseLocalUrl = url.substr(0, index2);
	
		return baseLocalUrl + "/";
		
	} else {

		return baseURL + "/";
	}
}

function initMap(planet, mid) {

	this.planet = planet;
	this.url = getBaseURL();
	this.mid = mid;
	drawScreen();
	refresh();
}

function getRandomInt (min, max) {
	return Math.floor(Math.random() * (max - min + 1)) + min;
}

function get_clan_color(cid) {

	for (a=0; a<clans.length; a++) {
		if (clans[cid]) {
			return clans[cid];
		} 
	}
						
	var nr1 = getRandomInt(128, 256);		
	var nr2 = getRandomInt(128, 256);		
	var nr3 = getRandomInt(128, 256);		
			
	clans[cid] = 'rgba('+nr1+','+nr2+','+nr3+', 0.7)';
	return clans[cid];
}

function getSectorData() {

	if (window.XMLHttpRequest) {
		// code for IE7+, Firefox, Chrome, Opera, Safari
		xmlhttp=new XMLHttpRequest();
	} else {
		// code for IE6, IE5
		xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
	}
			
	xmlhttp.onreadystatechange=function() {
		if (xmlhttp.readyState==4 && xmlhttp.status==200) {
		
			json = xmlhttp.responseText;
			drawScreen();
		}
	}
	
	xmlhttp.open("POST", url ,true);
	xmlhttp.setRequestHeader("Content-type","application/x-www-form-urlencoded");
	xmlhttp.send("mid="+mid+"&eid=5001&id="+planet);
}

function getClanInfo(cid) {
	if (window.XMLHttpRequest) {
		// code for IE7+, Firefox, Chrome, Opera, Safari
		xmlhttp=new XMLHttpRequest();
	} else {
		// code for IE6, IE5
		xmlhttp=new ActiveXObject("Microsoft.XMLHTTP");
	}
			
	xmlhttp.onreadystatechange=function() {
		if (xmlhttp.readyState==4 && xmlhttp.status==200) {
					
			var clan = eval('('+xmlhttp.responseText+')');
														
			var text = 'Name = '+clan.name+'\r\n';
				text += 'Slogan = '+clan.slogan+'\r\n';
				text += 'Won = '+clan.won+'\r\n';
				text += 'Lost = '+clan.lost+'\r\n';
				text += 'Created = '+clan.created+'\r\n';
				text += 'Last Active = '+clan.last_activity+'\r\n';
				text += 'Clan Id = '+clan.cid+'\r\n';
				text += 'Player Id = '+clan.pid+'\r\n';
				text += 'Attack strength = '+clan.attack+'\r\n';
				text += 'Defense strength = '+clan.defense+'\r\n';
				text += 'Money = '+clan.money+'\r\n';
				
			alert(text);
		}
	}
	
	xmlhttp.open("POST", url ,true);
	xmlhttp.setRequestHeader("Content-type","application/x-www-form-urlencoded");
	xmlhttp.send("mid="+mid+"&eid=5002&id="+cid);
}
		
function IsInPath(event) {
	var bb, x, y
	bb = canvas.getBoundingClientRect()
	x = (event.clientX-bb.left) * (canvas.width/bb.width)
	y = (event.clientY-bb.top) * (canvas.height/bb.height)
	return ctx.isPointInPath(x,y)
}
	
function createPolygon(x,y) {

	var yoffset=4;
	var xoffset=6;
	if ((y % 2)==0) {
		xoffset+=44;
	}
			
	var poly = [	
		{x:20+(x*88)+xoffset, y:0+ (y*18)+yoffset},
		{x:46+(x*88)+xoffset, y:0+ (y*18)+yoffset},
		{x:64+(x*88)+xoffset, y:18+(y*18)+yoffset},
		{x:46+(x*88)+xoffset, y:36+(y*18)+yoffset},
		{x:20+(x*88)+xoffset, y:36+(y*18)+yoffset},
		{x:2+ (x*88)+xoffset, y:18+(y*18)+yoffset} ];	
				
	return poly;
}
				
function isPointInPolygon(x, y, pt){

	var poly = createPolygon(x,y);
		
	for(var c = false, i = -1, l = poly.length, j = l - 1; ++i < l; j = i)
		((poly[i].y <= pt.y && pt.y < poly[j].y) || (poly[j].y <= pt.y && pt.y < poly[i].y))
		&& (pt.x < (poly[j].x - poly[i].x) * (pt.y - poly[i].y) / (poly[j].y - poly[i].y) + poly[i].x)
		&& (c = !c);
				
	return c;
}	
	
function drawPologon(x, y, name, damage, cid, color) {
	
	var yoffset=4;
	var xoffset=6;
	if ((y % 2)==0) {
		xoffset+=44;
	}
		
	var poly = createPolygon(x,y);
															
	ctx.beginPath();
	ctx.moveTo(poly[0].x, poly[0].y);
	for( j=1; j<poly.length; j++ ){
		ctx.lineTo( poly[j].x , poly[j].y )
	}
	ctx.lineTo( poly[0].x , poly[0].y )
			
	ctx.lineWidth = 1;
	ctx.strokeStyle = '#000000';
	ctx.stroke();
	
	if (name) {
	
		/* Fill backgound of pologon */	
		ctx.fillStyle = color;
		ctx.fill();
	
		/* Enter text to Pologon */			
		ctx.font = '7pt Arial';
		ctx.fillStyle = 'white';
		ctx.fillText(name, 18+(x*88)+xoffset, 18+(y*18)+yoffset);
		if (damage>0) {
			ctx.fillText((damage*10)+'%', 24+(x*88)+xoffset, 28+(y*18)+yoffset);
		}
	}
				
	ctx.closePath();
}	
		
function drawScreen(event) {
	
	/* Clear canvas */
	ctx.clearRect(0, 0, canvas.width, canvas.height);

	/* Draw background */
	imageObj.src = 'images/planet/map'+planet+'a.png';
	ctx.drawImage(imageObj, 0, 0);
			
	/* Draw pologons */
	for(x=0;x<5;x++) {
		for(y=0;y<15;y++) {
			drawPologon(x, y, "", "", 0, "");
		}
	}
					
	/* Draw clan data */
	var obj = eval(json);	
	if (obj) {
		for(i=0;i<obj.length;i++) {				
			color = 'rgba(255,128,128,0.5)';
			drawPologon(obj[i].x,obj[i].y, obj[i].name, obj[i].damage, obj[i].cid, get_clan_color(obj[i].cid));
		}
	}

	/* Draw pointer */
	if (event) {
	
		var pos;
		if (is_touch_device) {
			pos = getTouchPos(canvas, event);	
		} else {
			pos = getMousePos(canvas, event);	
		}
			
		for(x=0;x<5;x++) {
			for(y=0;y<15;y++) {
				if (isPointInPolygon(x, y, pos)) {		
					drawPologon(x, y, " ", "", 0, "rgba(0,255,255,0.5)");
					
					ctx.font = '7pt Arial';
					ctx.fillStyle = 'white';
					ctx.fillText(x+' '+y, 10 , 290);
			
					break;
				}
			}
		}
	}	
}

function getTouchPos(canvas, evt) {
   var coors = {
      x: evt.targetTouches[0].pageX,
      y: evt.targetTouches[0].pageY
   };
	
	// Now we need to get the offset of the canvas location
   var obj = sigCanvas;
 
   if (obj.offsetParent) {
   
		// Every time we find a new object, we add its offsetLeft and offsetTop to curleft and curtop.
		do {
			coors.x -= obj.offsetLeft;
			coors.y -= obj.offsetTop;
		}
		
		// while loop can be "while (obj = obj.offsetParent)" only, which does return null
		// when null is passed back, but that creates a warning in some editors (i.e. VS2010).
      while ((obj = obj.offsetParent) != null);
   }
	
	return coors;				
}
	
function getMousePos(canvas, evt) {
	var rect = canvas.getBoundingClientRect();
	return {
		x: evt.clientX - rect.left,
		y: evt.clientY - rect.top
	};
} 

function doMove(event) {

	event.preventDefault();
 
	/* To improve performance only process each second move event */
	if (flag) { 
		flag = false;
		return;
	} else {
		flag=true;
	}
	
	drawScreen(event);
}

function doPoint(event) {
	
	event.preventDefault();
	 	
	var pos;
	if (is_touch_device) {
		pos = getTouchPos(canvas, event);	
	} else {
		pos = getMousePos(canvas, event);	
	}
			
	var obj = eval(json);
				
	if (obj) {
		for(k=0; k<obj.length; k++) {				
			if (isPointInPolygon(obj[k].x, obj[k].y, pos)) {
				getClanInfo(obj[k].cid);
				break;
			}
		}
	}		 
}
	
	
if (is_touch_device) {

	canvas.addEventListener('touchstart', doPoint, false);
	canvas.addEventListener('touchmove', doMove, false);	
		
	
} else { 
	
	canvas.addEventListener('click', doPoint, false);
	canvas.addEventListener('mousemove', doMove, false);	 
	
}
			
function refresh() {
	getSectorData();
   setTimeout(refresh, 5000);
}