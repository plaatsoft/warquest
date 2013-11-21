var bet;
var key;
var token;

if (document.all||document.getElementById){
document.write('<style>.tictac{')
document.write('width:150px;height:150px;font-size:50;')
document.write('}</style>')
}

var sqrT = new Array();
for( var i = 0; i < 9; i++ ) {
	sqrT[i] = 0;
}

var owner = new Array();
for( var i = 0; i < 9; i++ ) {
	owner[i] = 0;
}

var sqr1
var sqr2
var sqr3
var sqr4
var sqr5
var sqr6
var sqr7
var sqr8
var sqr9

var moveCount = 0
var turn = 0

var sqr=new Array( "", "sqr1", "sqr2", "sqr3", "sqr4", "sqr5", "sqr6", "sqr7", "sqr8", "sqr9" );

function drawboard() {

	for( var i = 1; i < 10; i++ ) {

		value = '   ';
		disabled = false;

		if (owner[i] == 1) {
			value = ' X ';
			disabled = true;
			
		} else if (owner[i] == 2) {
			value = ' O ';
			disabled = true;
		} 	
	
		document.getElementById(sqr[i]).value = value
		document.getElementById(sqr[i]).disabled = disabled
	}
}


function vari()
{
sqr1 = document.forms['warquest'].sqr1.value
sqr2 = document.forms['warquest'].sqr2.value
sqr3 = document.forms['warquest'].sqr3.value
sqr4 = document.forms['warquest'].sqr4.value
sqr5 = document.forms['warquest'].sqr5.value
sqr6 = document.forms['warquest'].sqr6.value
sqr7 = document.forms['warquest'].sqr7.value
sqr8 = document.forms['warquest'].sqr8.value
sqr9 = document.forms['warquest'].sqr9.value
}

function set1() {
	owner[1] = 1; 
	sqrT[1] = 1; 
	turn = 1; 
	
	check();	
	drawboard();
}

function set2() {
	owner[2] = 1; 
	sqrT[2] = 1; 
	turn = 1; 
	
	check();	
	drawboard();
}

function set3() {
	owner[3] = 1; 
	sqrT[3] = 1; 
	turn = 1; 
	
	check();	
	drawboard();
}

function set4() {
	owner[4] = 1; 
	sqrT[4] = 1; 
	turn = 1; 
	
	check();	
	drawboard();
}

function set5() {
	owner[5] = 1; 
	sqrT[5] = 1; 
	turn = 1; 
	
	check();	
	drawboard();
}

function set6() {
	owner[6] = 1; 
	sqrT[6] = 1; 
	turn = 1; 
	
	check();	
	drawboard();
}

function set7() {
	owner[7] = 1; 
	sqrT[7] = 1; 
	turn = 1; 
	
	check();	
	drawboard();
}

function set8() {
	owner[8] = 1; 
	sqrT[8] = 1; 
	turn = 1; 
	
	check();	
	drawboard();
}

function set9() {
	owner[9] = 1; 
	sqrT[9] = 1; 
	turn = 1; 
	
	check();	
	drawboard();
}

function check()
{
  if(owner[1]==1 && owner[2]==1 && owner[3]==1)
  {
    youWin();
  } 
  else if(owner[4]==1 && owner[5]==1 && owner[6]==1)
  {
    youWin();
  } 
  else if(owner[7]==1 && owner[8]==1 && owner[9]==1)
  {
    youWin();
  }
  else if(owner[1]==1 && owner[5]==1 && owner[9]==1)
  {
    youWin();
  }
  else if(owner[1]==1 && owner[4]==1 && owner[7]==1)
  {
    youWin();
  }
  else if(owner[2]==1 && owner[5]==1 && owner[8]==1)
  {
    youWin();
  }
  else if(owner[3]==1 && owner[6]==1 && owner[9]==1)
  {
    youWin();
  }
  else if(owner[1]==1 && owner[5]==1 && owner[9]==1)
  {
    youWin();
  }
  else if(owner[3]==1 && owner[5]==1 && owner[7]==1)
  {
    youWin();
  }
  else
  {
    winCheck()
    check2()
    drawCheck()  
  } 
}

function check2()
{
  //vari()
  drawCheck()
  if(owner[1]==2 && owner[2]==2 && owner[3]==2)
  {
    youLose();
  } 
  else if(owner[4]==2 && owner[5]==2 && owner[6]==2)
  {
    youLose();
  } 
  else if(owner[7]==2 && owner[8]==2 && owner[9]==2)
  {
    youLose();
  }
  else if(owner[1]==2 && owner[5]==2 && owner[9]==2)
  {
    youLose();
  }
  else if(owner[1]==2 && owner[4]==2 && owner[7]==2)
  {
    youLose();
  }
  else if(owner[2]==2 && owner[5]==2 && owner[8]==2)
  {
    youLose();
  }
  else if(owner[3]==2 && owner[6]==2 && owner[9]==2)
  {
    youLose();
  }
  else if(owner[1]==2 && owner[5]==2 && owner[9]==2)
  {
    youLose();
   }
  else if(owner[3]==2 && owner[5]==2 && owner[7]==2)
  {
    youLose();
  }
}

function drawCheck()
{
  //vari()
  
  moveCount = 0;
  for( var i = 1; i < 10; i++ ) {
   	moveCount += sqrT[i] 
  }
 
  if(moveCount == 9)
  {
    youDraw();
  }
}

function winCheck()
{
  check2()
  if(owner[1]==2 && owner[2]==2 && sqrT[3] == 0 && turn == 1)
  {
    owner[3] = 2; 
    sqrT[3] = 1;
    turn = 0;
  }
  else if(owner[2]==2 && owner[3]==2 && sqrT[1] == 0 && turn == 1)
  {
    owner[1] = 2; 
    sqrT[1] = 1;
    turn = 0;
  }
  else if(owner[4]==2 && owner[5]==2 && sqrT[6] == 0 && turn == 1)
  {
    owner[6] = 2; 
    sqrT[6] = 1;
    turn = 0;
  }
  else if(owner[5]==2 && owner[6]==2 && sqrT[4] == 0 && turn == 1)
  {
    owner[4] = 2; 
    sqrT[4] = 1;
    turn = 0;
  }
  else if(owner[7]==2 && owner[8]==2 && sqrT[9] == 0 && turn == 1)
  {
    owner[9] = 2; 
    sqrT[9] = 1;
    turn = 0;
  }
  else if(owner[8]==2 && owner[9]==2 && sqrT[7] == 0 && turn == 1)
  {
    owner[7] = 2; 
    sqrT[7] = 1;
    turn = 0;
  }
  else if(owner[1]==2 && owner[5]==2 && sqrT[9] == 0 && turn == 1)
  {
    owner[9] = 2; 
    sqrT[9] = 1;
    turn = 0;
  }
  else if(owner[5]==2 && owner[9]==2 && sqrT[1] == 0 && turn == 1)
  {
    owner[1] = 2; 
    sqrT[1] = 1;
    turn = 0;
  }
  else if(owner[3]==2 && owner[5]==2 && sqrT[7] == 0 && turn == 1)
  {
    owner[7] = 2; 
    sqrT[7] = 1;
    turn = 0;
  }
  else if(owner[7]==2 && owner[5]==2 && sqrT[3] == 0 && turn == 1)
  {
    owner[3] = 2; 
    sqrT[3] = 1;
    turn = 0;
  }
  else if(owner[1]==2 && owner[3]==2 && sqrT[2] == 0 && turn == 1)
  {
    owner[2] = 2; 
    sqrT[2] = 1;
    turn = 0;
  }
  else if(owner[4]==2 && owner[6]==2 && sqrT[5] == 0 && turn == 1)
  {
    owner[5] = 2; 
    sqrT[5] = 1;
    turn = 0;
  }
  else if(owner[7]==2 && owner[9]==2 && sqrT[8] == 0 && turn == 1)
  {
    owner[8] = 2; 
    sqrT[8] = 1;
    turn = 0;
  }
  else if(owner[1]==2 && owner[7]==2 && sqrT[4] == 0 && turn == 1)
  {
    owner[4] = 2; 
    sqrT[4] = 1;
    turn = 0;
  }
  else if(owner[2]==2 && owner[8]==2 && sqrT[5] == 0 && turn == 1)
  {
    owner[5] = 2; 
    sqrT[5] = 1;
    turn = 0;
  }
  else if(owner[3]==2 && owner[9]==2 && sqrT[6] == 0 && turn == 1)
  {
    owner[6] = 2; 
    sqrT[6] = 1;
    turn = 0;
  }
  else if(owner[1]==2 && owner[5]==2 && sqrT[9] == 0 && turn == 1)
  {
    owner[9] = 2; 
    sqrT[9] = 1;
    turn = 0;
  }
  else if(owner[4]==2 && owner[7]==2 && sqrT[1] == 0 && turn == 1)
  {
    owner[1] = 2; 
    sqrT[1] = 1;
    turn = 0;
  }
  else if(owner[5]==2 && owner[8]==2 && sqrT[2] == 0 && turn == 1)
  {
    owner[2] = 2; 
    sqrT[2] = 1;
    turn = 0;
  }
  else if(owner[6]==2 && owner[9]==2 && sqrT[3] == 0 && turn == 1)
  {
    owner[3] = 2; 
    sqrT[3] = 1;
    turn = 0;
  }
  else if(owner[1]==2 && owner[4]==2 && sqrT[7] == 0 && turn == 1)
  {
    owner[7] = 2; 
    sqrT[7] = 1;
    turn = 0;
  }
  else if(owner[2]==2 && owner[5]==2 && sqrT[8] == 0 && turn == 1)
  {
    owner[8] = 2; 
    sqrT[8] = 1;
    turn = 0;
  }
  else if(owner[3]==2 && owner[6]==2 && sqrT[9] == 0 && turn == 1)
  {
    owner[9] = 2; 
    sqrT[9] = 1;
    turn = 0;
  }
  else if(owner[1]==2 && owner[9]==2 && sqrT[5] == 0 && turn == 1)
  {
    owner[5] = 2; 
    sqrT[5] = 1;
    turn = 0;
  }
  else if(owner[3]==2 && owner[7]==2 && sqrT[5] == 0 && turn == 1)
  {
    owner[5] = 2; 
    sqrT[5] = 1;
    turn = 0;
  }
  else
  {
    computer()
  }
  check2()
}

function computer()
{
  check2()
  if(owner[1]==1 && owner[2]==1 && sqrT[3] == 0 && turn == 1)
  {
    owner[3] = 2; 
    sqrT[3] = 1;
    turn = 0;
  }
  else if(owner[2]==1 && owner[3]==1 && sqrT[1] == 0 && turn == 1)
  {
    owner[1] = 2; 
    sqrT[1] = 1;
    turn = 0;
  }
  else if(owner[4]==1 && owner[5]==1 && sqrT[6] == 0 && turn == 1)
  {
    owner[6] = 2; 
    sqrT[6] = 1;
    turn = 0;
  }
  else if(owner[5]==1 && owner[6]==1 && sqrT[4] == 0 && turn == 1)
  {
    owner[4] = 2; 
    sqrT[4] = 1;
    turn = 0;
  }
  else if(owner[7]==1 && owner[8]==1 && sqrT[9] == 0 && turn == 1)
  {
    owner[9] = 2; 
    sqrT[9] = 1;
    turn = 0;
  }
  else if(owner[8]==1 && owner[9]==1 && sqrT[7] == 0 && turn == 1)
  {
    owner[7] = 2; 
    sqrT[7] = 1;
    turn = 0;
  }
  else if(owner[1]==1 && owner[5]==1 && sqrT[9] == 0 && turn == 1)
  {
    owner[9] = 2; 
    sqrT[9] = 1;
    turn = 0;
  }
  else if(owner[5]==1 && owner[9]==1 && sqrT[1] == 0 && turn == 1)
  {
    owner[1] = 2; 
    sqrT[1] = 1;
    turn = 0;
  }
  else if(owner[3]==1 && owner[5]==1 && sqrT[7] == 0 && turn == 1)
  {
    owner[7] = 2; 
    sqrT[7] = 1;
    turn = 0;
  }
  else if(owner[7]==1 && owner[5]==1 && sqrT[3] == 0 && turn == 1)
  {
    owner[3] = 2; 
    sqrT[3] = 1;
    turn = 0;
  }
  else if(owner[1]==1 && owner[3]==1 && sqrT[2] == 0 && turn == 1)
  {
    owner[2] = 2; 
    sqrT[2] = 1;
    turn = 0;
  }
  else if(owner[4]==1 && owner[6]==1 && sqrT[5] == 0 && turn == 1)
  {
    owner[5] = 2; 
    sqrT[5] = 1;
    turn = 0;
  }
  else if(owner[7]==1 && owner[9]==1 && sqrT[8] == 0 && turn == 1)
  {
    owner[8] = 2; 
    sqrT[8] = 1;
    turn = 0;
  }
  else if(owner[1]==1 && owner[7]==1 && sqrT[4] == 0 && turn == 1)
  {
    owner[4] = 2; 
    sqrT[4] = 1;
    turn = 0;
  }
  else if(owner[2]==1 && owner[8]==1 && sqrT[5] == 0 && turn == 1)
  {
    owner[5] = 2; 
    sqrT[5] = 1;
    turn = 0;
  }
  else if(owner[3]==1 && owner[9]==1 && sqrT[6] == 0 && turn == 1)
  {
    owner[6] = 2; 
    sqrT[6] = 1;
    turn = 0;
  }
  else if(owner[1]==1 && owner[5]==1 && sqrT[9] == 0 && turn == 1)
  {
    owner[9] = 2; 
    sqrT[9] = 1;
    turn = 0;
  }
  else if(owner[4]==1 && owner[7]==1 && sqrT[1] == 0 && turn == 1)
  {
    owner[1] = 2; 
    sqrT[1] = 1;
    turn = 0;
  }
  else if(owner[5]==1 && owner[8]==1 && sqrT[2] == 0 && turn == 1)
  {
    owner[2] = 2; 
    sqrT[2] = 1;
    turn = 0;
  }
  else if(owner[6]==1 && owner[9]==1 && sqrT[3] == 0 && turn == 1)
  {
    owner[3] = 2; 
    sqrT[3] = 1;
    turn = 0;
  }
  else if(owner[1]==1 && owner[4]==1 && sqrT[7] == 0 && turn == 1)
  {
    owner[7] = 2; 
    sqrT[7] = 1;
    turn = 0;
  }
  else if(owner[2]==1 && owner[5]==1 && sqrT[8] == 0 && turn == 1)
  {
    owner[8] = 2; 
    sqrT[8] = 1;
    turn = 0;
  }
  else if(owner[3]==1 && owner[6]==1 && sqrT[9] == 0 && turn == 1)
  {
    owner[9] = 2; 
    sqrT[9] = 1;
    turn = 0;
  }
  else if(owner[1]==1 && owner[9]==1 && sqrT[5] == 0 && turn == 1)
  {
    owner[5] = 2; 
    sqrT[5] = 1;
    turn = 0;
  }
  else if(owner[3]==1 && owner[7]==1 && sqrT[5] == 0 && turn == 1)
  {
    owner[5] = 2; 
    sqrT[5] = 1;
    turn = 0;
  }
  else
  {
    AI()
  }
  check2()
}

function AI()
{
  //vari()
  if(owner[5]==0 && turn == 1)
  {
    owner[5] = 2; 
    turn = 0
    sqrT[5] = 1
  }
  else if(owner[1]==0 && turn == 1)
  {
    owner[1] = 2; 
    turn = 0
    sqrT[1] = 1
  }
  else if(owner[9]==0 && turn == 1)
  {
    owner[9] = 2; 
    turn = 0
    sqrT[9] = 1
  }
  else if(owner[6]==0 && turn == 1)
  {
    owner[6] = 2; 
    turn = 0
    sqrT[6] = 1
  }
  else if(owner[2]==0 && turn == 1)
  {
    owner[2] = 2; 
    turn = 0
    sqrT[2] = 1
  }
  else if(owner[8]==0 && turn == 1)
  {
    owner[8] = 2; 
    turn = 0
    sqrT[8] = 1
  }
  else if(owner[3]==0 && turn == 1)
  {
    owner[3] = 2; 
    turn = 0
    sqrT[3] = 1
  }
  else if(owner[7]==0 && turn == 1)
  {
    owner[7] = 2; 
    turn = 0
    sqrT[7] = 1
  }
  else if(owner[4]==0 && turn == 1)
  {
    owner[4] = 2; 
    turn = 0
    sqrT[4] = 1
  }
  check2()
}

function disable()
{
  document.forms['warquest'].sqr1.disabled = true;
  document.forms['warquest'].sqr2.disabled = true;
  document.forms['warquest'].sqr3.disabled = true;
  document.forms['warquest'].sqr4.disabled = true;
  document.forms['warquest'].sqr5.disabled = true;
  document.forms['warquest'].sqr6.disabled = true;
  document.forms['warquest'].sqr7.disabled = true;
  document.forms['warquest'].sqr8.disabled = true;
  document.forms['warquest'].sqr9.disabled = true;
}

function enable()
{
  document.forms['warquest'].sqr1.disabled = false;
  document.forms['warquest'].sqr2.disabled = false;
  document.forms['warquest'].sqr3.disabled = false;
  document.forms['warquest'].sqr4.disabled = false;
  document.forms['warquest'].sqr5.disabled = false;
  document.forms['warquest'].sqr6.disabled = false;
  document.forms['warquest'].sqr7.disabled = false;
  document.forms['warquest'].sqr8.disabled = false;
  document.forms['warquest'].sqr9.disabled = false;
}

function reset()
{
  document.forms['warquest'].sqr1.value = "   "
  document.forms['warquest'].sqr2.value = "   "
  document.forms['warquest'].sqr3.value = "   "
  document.forms['warquest'].sqr4.value = "   "
  document.forms['warquest'].sqr5.value = "   "
  document.forms['warquest'].sqr6.value = "   "
  document.forms['warquest'].sqr7.value = "   "
  document.forms['warquest'].sqr8.value = "   "
  document.forms['warquest'].sqr9.value = "   "
  
	for( var i = 0; i < 9; i++ ) {
		sqrT[i] = 0;
	}
	
  //vari()
  turn = 0
  moveCount = 0
}

function resetter()
{
  reset()
}

function youLose() {
	simpleHttpRequest(0);
	disable();
}

function youWin() {	
	simpleHttpRequest(1);
	disable();
}

function youDraw() {
	simpleHttpRequest(2);
	disable();
}

function simpleHttpRequest(result) {
 
	var form = document.forms['warquest'];

	var newInput1 = document.createElement('input');
	newInput1.setAttribute('type','hidden');
	newInput1.setAttribute('name','bet');
	newInput1.setAttribute('value', bet);
	form.appendChild(newInput1);		
		
	var newInput2 = document.createElement('input');
	newInput2.setAttribute('type','hidden');
	newInput2.setAttribute('name','key');
	newInput2.setAttribute('value', key);
	form.appendChild(newInput2);	
			
	var newInput3 = document.createElement('input');
	newInput3.setAttribute('type','hidden');
	newInput3.setAttribute('name','token');
	newInput3.setAttribute('value', token);
	form.appendChild(newInput3);
	
	var newInput4 = document.createElement('input');
	newInput4.setAttribute('type','hidden');
	newInput4.setAttribute('name','result');
	newInput4.setAttribute('value', result);
	form.appendChild(newInput4);	
	
	form.submit();	
}

function initTicTacToe( bet1, key1, token1 ) {
	bet = bet1;
	key = key1;
	token = token1;
}