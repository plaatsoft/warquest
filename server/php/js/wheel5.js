var colors = ["#B8D430", "#3AB745", "#029990", "#3501CB",
             "#2E2C75", "#673A7E", "#CC0071", "#F80120",
             "#F35B20", "#FB9A00", "#FFCC00", "#FEF200"];
var restaraunts = ["200", "150", "100", "90", "80", "70", "60", "50", "40", "30", "20", "10"];

var startAngle = 0;
var arc = Math.PI / 6;
var spinTimeout = null;

var spinArcStart = 10;
var spinTime = 0;
var spinTimeTotal = 0;

var ctx;
var startBet;
var key;
var token;
      
function initWheel( bet, angle, key1, token1 ) {
	startBet = bet;
	startAngle = angle;
	key = key1;
	token = token1;
}
   
function drawWheel() {
  var canvas = document.getElementById("canvas");
  if (canvas.getContext) {
    var outsideRadius = 200;
    var textRadius = 160;
    var insideRadius = 15;
   
    ctx = canvas.getContext("2d");
    ctx.clearRect(0,0,500,500);
      
    ctx.strokeStyle = "black";
    ctx.lineWidth = 2;
   
    ctx.font = 'bold 12px Helvetica, Arial';
   
    for(var i = 0; i < 12; i++) {
      var angle = startAngle + i * arc;
      ctx.fillStyle = colors[i];
     
      ctx.beginPath();
      ctx.arc(250, 250, outsideRadius, angle, angle + arc, false);
      ctx.arc(250, 250, insideRadius, angle + arc, angle, true);
      ctx.stroke();
      ctx.fill();
     
      ctx.save();
      ctx.shadowOffsetX = -1;
      ctx.shadowOffsetY = -1;
      ctx.shadowBlur    = 0;
      ctx.shadowColor   = "rgb(220,220,220)";
      ctx.fillStyle = "black";
      ctx.translate(250 + Math.cos(angle + arc / 2) * textRadius,
                    250 + Math.sin(angle + arc / 2) * textRadius);
      ctx.rotate(angle + arc / 2 + Math.PI / 2);
      var text = restaraunts[i];
      ctx.fillText(text, -ctx.measureText(text).width / 2, 0);
      ctx.restore();
    }
   
    //Arrow
    ctx.fillStyle = "white";
    ctx.beginPath();
    ctx.moveTo(250 - 4, 250 - (outsideRadius + 5));
    ctx.lineTo(250 + 4, 250 - (outsideRadius + 5));
    ctx.lineTo(250 + 4, 250 - (outsideRadius - 5));
    ctx.lineTo(250 + 9, 250 - (outsideRadius - 5));
    ctx.lineTo(250 + 0, 250 - (outsideRadius - 13));
    ctx.lineTo(250 - 9, 250 - (outsideRadius - 5));
    ctx.lineTo(250 - 4, 250 - (outsideRadius - 5));
    ctx.lineTo(250 - 4, 250 - (outsideRadius + 5));
    ctx.fill();
  }
}
   
function spinWheel() {
  spinAngleStart = Math.random() * 10 + 10;
  spinTime = 0;
  spinTimeTotal = Math.random() * 3 + 4 * 1000;
  rotateWheel();
}

function rotateWheel() {
  spinTime += 30;
  if(spinTime >= spinTimeTotal) {
    stopRotateWheel();
    return;
  }
  var spinAngle = spinAngleStart - easeOut(spinTime, 0, spinAngleStart, spinTimeTotal);
  startAngle += (spinAngle * Math.PI / 180);
  drawWheel();
  spinTimeout = setTimeout('rotateWheel()', 30);
}

function easeOut(t, b, c, d) {
  var ts = (t/=d)*t;
  var tc = ts*t;
  return b+c*(tc + -3*ts + 3*t);
}

function stopRotateWheel() {
  clearTimeout(spinTimeout);
  var degrees = startAngle * 180 / Math.PI + 90;
  var arcd = arc * 180 / Math.PI;
  var index = Math.floor((360 - degrees % 360) / arcd);
  ctx.save();
  ctx.font = 'bold 30px Helvetica, Arial';
  ctx.fillStyle = "white";
  var text = restaraunts[index]
  ctx.restore(); 
  
  simpleHttpRequest(text, startAngle, startBet, key);
}

function simpleHttpRequest(wheel, angle, bet, key) {
 
	var form = document.forms['warquest'];

	var newInput1 = document.createElement('input');
	newInput1.setAttribute('type','hidden');
	newInput1.setAttribute('name','wheel');
	newInput1.setAttribute('value', wheel);
	form.appendChild(newInput1);		
		
	var newInput2 = document.createElement('input');
	newInput2.setAttribute('type','hidden');
	newInput2.setAttribute('name','angle');
	newInput2.setAttribute('value', angle);
	form.appendChild(newInput2);	
	
	var newInput3 = document.createElement('input');
	newInput3.setAttribute('type','hidden');
	newInput3.setAttribute('name','bet');
	newInput3.setAttribute('value', bet);
	form.appendChild(newInput3);	
	
	var newInput4 = document.createElement('input');
	newInput4.setAttribute('type','hidden');
	newInput4.setAttribute('name','token');
	newInput4.setAttribute('value', token);
	form.appendChild(newInput4);	
	
	var newInput5 = document.createElement('input');
	newInput5.setAttribute('type','hidden');
	newInput5.setAttribute('name','key');
	newInput5.setAttribute('value', key);
	form.appendChild(newInput5);	
	
	form.submit();	
}
