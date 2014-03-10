/* All copyrights reserved (c) 2008-2014 PlaatSoft */

if (document.all||document.getElementById){
	document.write('<style>.tictac{')
	document.write('width:150px;height:145px;font-size:90;}')
	document.write('input[type=button] {background-color: #ffffff;color:#000000;border:3px solid;}');
	document.write('input[type=button]:hover {background-color: #aaaaaa;}');
	document.write('input[type=button]:disabled {background-color: #aaaaaa;}');
	document.write('</style>')
}

var owner = new Array();
var bet;
var key;
var token;
var moveCount = 0;
var turn = 0;
var sqr = new Array( "", "sqr1", "sqr2", "sqr3", "sqr4", "sqr5", "sqr6", "sqr7", "sqr8", "sqr9" );

function setTicTacToe(sqr) {

	if( turn == 0 ) {

		owner[sqr] = 1; 
		turn = 1; 
		moveCount+=2;
	
		if (moveCount==2) {
			randomSet();
			drawboard();	
			
		} else {
		
			check();	
			drawboard();		
		}
	}
}

function randomSet() {

	tmp = ""
	for( var i = 1; i < 10; i++ ) {

		if (owner[i]==0) {
			tmp += i;
		}
	}
	
	var rnum = Math.floor(Math.random() * tmp.length);
	
	owner[tmp[rnum]]=2;		
	turn = 0; 
}


function disableTicTacToe()
{
	for( var i = 1; i < 10; i++ ) {

		document.getElementById(sqr[i]).disabled = true;
	}
}

function enableTicTacToe()
{
  	for( var i = 1; i < 10; i++ ) {

		document.getElementById(sqr[i]).disabled = false;
	}
}

function showTicTacToe(board) {
	
	for( var i = 1; i < 10; i++ ) {

		owner[i]=board.substr((i-1),1);
	}
	
	drawboard();
	disableTicTacToe();
}


function initTicTacToe( bet1, key1, token1 ) {
	bet = bet1;
	key = key1;
	token = token1;
	
  	for( var i = 1; i < 10; i++ ) {
		owner[i]=0;
	}
  
	turn = 0
	moveCount = 0	
	
	enableTicTacToe();
}


function drawboard() {

	for( var i = 1; i < 10; i++ ) {

		if ( navigator.userAgent.indexOf("MSIE")!=-1) {
			value = '';
		} else {
			value = ' ';
		}
			
		disabled = false;

		if (owner[i] == 1) {
			value = 'X';
			disabled = true;
			
		} else if (owner[i] == 2) {
			value = 'O';
			disabled = true;
		} 	
	
		document.getElementById(sqr[i]).value = value;
		document.getElementById(sqr[i]).disabled = disabled;
	}
}
	
function youLose() {
	drawboard();	
	disableTicTacToe();
	simpleHttpRequest(0);
}

function youWin() {	
	drawboard();	
	disableTicTacToe();
	simpleHttpRequest(1);
}

function youDraw() {
	drawboard();
	disableTicTacToe();	
	simpleHttpRequest(2);
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
	
	tmp = ""
	for( var i = 1; i < 10; i++ ) {

		tmp += owner[i];
	}
		
	var newInput5 = document.createElement('input');
	newInput5.setAttribute('type','hidden');
	newInput5.setAttribute('name','board');
	newInput5.setAttribute('value', tmp);
	form.appendChild(newInput5);	
	
	form.submit();	
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
  if(moveCount > 9)
  {
    youDraw();
  }
}

function winCheck()
{
  check2()
  if(owner[1]==2 && owner[2]==2 && owner[3]==0 && turn==1)
  {
    owner[3] = 2; 
    turn = 0;
  }
  else if(owner[2]==2 && owner[3]==2 && owner[1]==0 && turn==1)
  {
    owner[1] = 2; 
    turn = 0;
  }
  else if(owner[4]==2 && owner[5]==2 && owner[6]==0 && turn==1)
  {
    owner[6] = 2; 
    turn = 0;
  }
  else if(owner[5]==2 && owner[6]==2 && owner[4]==0 && turn==1)
  {
    owner[4] = 2; 
    turn = 0;
  }
  else if(owner[7]==2 && owner[8]==2 && owner[9]==0 && turn==1)
  {
    owner[9] = 2; 
    turn = 0;
  }
  else if(owner[8]==2 && owner[9]==2 && owner[7]==0 && turn==1)
  {
    owner[7] = 2; 
    turn = 0;
  }
  else if(owner[1]==2 && owner[5]==2 && owner[9]==0 && turn==1)
  {
    owner[9] = 2; 
    turn = 0;
  }
  else if(owner[5]==2 && owner[9]==2 && owner[1]==0 && turn==1)
  {
    owner[1] = 2; 
    turn = 0;
  }
  else if(owner[3]==2 && owner[5]==2 && owner[7]==0 && turn==1)
  {
    owner[7] = 2; 
    turn = 0;
  }
  else if(owner[7]==2 && owner[5]==2 && owner[3]==0 && turn==1)
  {
    owner[3] = 2; 
    turn = 0;
  }
  else if(owner[1]==2 && owner[3]==2 && owner[2]==0 && turn==1)
  {
    owner[2] = 2; 
    turn = 0;
  }
  else if(owner[4]==2 && owner[6]==2 && owner[5]==0 && turn==1)
  {
    owner[5] = 2; 
    turn = 0;
  }
  else if(owner[7]==2 && owner[9]==2 && owner[8]==0 && turn==1)
  {
    owner[8] = 2; 
    turn = 0;
  }
  else if(owner[1]==2 && owner[7]==2 && owner[4]==0 && turn==1)
  {
    owner[4] = 2; 
    turn = 0;
  }
  else if(owner[2]==2 && owner[8]==2 && owner[5]==0 && turn==1)
  {
    owner[5] = 2; 
    turn = 0;
  }
  else if(owner[3]==2 && owner[9]==2 && owner[6]==0 && turn==1)
  {
    owner[6] = 2; 
    turn = 0;
  }
  else if(owner[1]==2 && owner[5]==2 && owner[9]==0 && turn==1)
  {
    owner[9] = 2; 
    turn = 0;
  }
  else if(owner[4]==2 && owner[7]==2 && owner[1]==0 && turn==1)
  {
    owner[1] = 2; 
    turn = 0;
  }
  else if(owner[5]==2 && owner[8]==2 && owner[2]==0 && turn==1)
  {
    owner[2] = 2; 
    turn = 0;
  }
  else if(owner[6]==2 && owner[9]==2 && owner[3]==0 && turn==1)
  {
    owner[3] = 2; 
    turn = 0;
  }
  else if(owner[1]==2 && owner[4]==2 && owner[7]==0 && turn==1)
  {
    owner[7] = 2; 
    turn = 0;
  }
  else if(owner[2]==2 && owner[5]==2 && owner[8]==0 && turn==1)
  {
    owner[8] = 2; 
    turn = 0;
  }
  else if(owner[3]==2 && owner[6]==2 && owner[9]==0 && turn==1)
  {
    owner[9] = 2; 
    turn = 0;
  }
  else if(owner[1]==2 && owner[9]==2 && owner[5]==0 && turn==1)
  {
    owner[5] = 2; 
    turn = 0;
  }
  else if(owner[3]==2 && owner[7]==2 && owner[5]==0 && turn==1)
  {
    owner[5] = 2; 
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
  if(owner[3]==1 && owner[6]==1 && owner[9]==0 && turn==1)
  {
    owner[9] = 2; 
    turn = 0;
  }  
  else if(owner[1]==1 && owner[2]==1 && owner[3]==0 && turn==1)
  {
    owner[3] = 2; 
    turn = 0;
  }
  else if(owner[2]==1 && owner[3]==1 && owner[1]==0 && turn==1)
  {
    owner[1] = 2; 
    turn = 0;
  }
  else if(owner[4]==1 && owner[5]==1 && owner[6]==0 && turn==1)
  {
    owner[6] = 2; 
    turn = 0;
  }
  else if(owner[5]==1 && owner[6]==1 && owner[4]==0 && turn==1)
  {
    owner[4] = 2; 
    turn = 0;
  }
  else if(owner[7]==1 && owner[8]==1 && owner[9]==0 && turn==1)
  {
    owner[9] = 2; 
    turn = 0;
  }
  else if(owner[8]==1 && owner[9]==1 && owner[7]==0 && turn==1)
  {
    owner[7] = 2; 
    turn = 0;
  }
  else if(owner[1]==1 && owner[5]==1 && owner[9]==0 && turn==1)
  {
    owner[9] = 2; 
    turn = 0;
  }
  else if(owner[5]==1 && owner[9]==1 && owner[1]==0 && turn==1)
  {
    owner[1] = 2; 
    turn = 0;
  }
  else if(owner[3]==1 && owner[5]==1 && owner[7]==0 && turn==1)
  {
    owner[7] = 2; 
    turn = 0;
  }
  else if(owner[7]==1 && owner[5]==1 && owner[3]==0 && turn==1)
  {
    owner[3] = 2; 
    turn = 0;
  }
  else if(owner[1]==1 && owner[3]==1 && owner[2]==0 && turn==1)
  {
    owner[2] = 2; 
    turn = 0;
  }
  else if(owner[4]==1 && owner[6]==1 && owner[5]==0 && turn==1)
  {
    owner[5] = 2; 
    turn = 0;
  }
  else if(owner[7]==1 && owner[9]==1 && owner[8]==0 && turn==1)
  {
    owner[8] = 2; 
    turn = 0;
  }
  else if(owner[1]==1 && owner[7]==1 && owner[4]==0 && turn==1)
  {
    owner[4] = 2; 
    turn = 0;
  }
  else if(owner[2]==1 && owner[8]==1 && owner[5]==0 && turn==1)
  {
    owner[5] = 2; 
    turn = 0;
  }
  else if(owner[3]==1 && owner[9]==1 && owner[6]==0 && turn==1)
  {
    owner[6] = 2; 
    turn = 0;
  }
  else if(owner[1]==1 && owner[5]==1 && owner[9]==0 && turn==1)
  {
    owner[9] = 2; 
    turn = 0;
  }
  else if(owner[4]==1 && owner[7]==1 && owner[1]==0 && turn==1)
  {
    owner[1] = 2; 
    turn = 0;
  }
  else if(owner[5]==1 && owner[8]==1 && owner[2]==0 && turn==1)
  {
    owner[2] = 2; 
    turn = 0;
  }
  else if(owner[6]==1 && owner[9]==1 && owner[3]==0 && turn==1)
  {
    owner[3] = 2; 
    turn = 0;
  }
  else if(owner[1]==1 && owner[4]==1 && owner[7]==0 && turn==1)
  {
    owner[7] = 2; 
    turn = 0;
  }
  else if(owner[2]==1 && owner[5]==1 && owner[8]==0 && turn==1)
  {
    owner[8] = 2; 
    turn = 0;
  }
  else if(owner[1]==1 && owner[9]==1 && owner[5]==0 && turn==1)
  {
    owner[5] = 2; 
    turn = 0;
  }
  else if(owner[3]==1 && owner[7]==1 && owner[5]==0 && turn==1)
  {
    owner[5] = 2; 
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
  if(owner[5]==0 && turn==1)
  {
    owner[5] = 2; 
    turn = 0
  }
  else if(owner[1]==0 && turn==1)
  {
    owner[1] = 2; 
    turn = 0
  }
  else if(owner[9]==0 && turn==1)
  {
    owner[9] = 2; 
    turn = 0
  }
  else if(owner[6]==0 && turn==1)
  {
    owner[6] = 2; 
    turn = 0
  }
  else if(owner[2]==0 && turn==1)
  {
    owner[2] = 2; 
    turn = 0
  }
  else if(owner[8]==0 && turn==1)
  {
    owner[8] = 2; 
    turn = 0
  }
  else if(owner[3]==0 && turn==1)
  {
    owner[3] = 2; 
    turn = 0
  }
  else if(owner[7]==0 && turn==1)
  {
    owner[7] = 2; 
    turn = 0
  }
  else if(owner[4]==0 && turn==1)
  {
    owner[4] = 2; 
    turn = 0
  }
  check2()
}