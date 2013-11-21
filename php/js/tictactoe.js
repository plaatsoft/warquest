var bet;
var key;
var token;

if (document.all||document.getElementById){
document.write('<style>.tictac{')
document.write('width:20px;height:20px;font-size:10;')
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

function drawBoard() {

	for( var i = 0; i < 9; i++ ) {

		value = '   ';
		disabled = false;

		if (owner[i] == 1) {
			value = ' X ';
			disabled = true;
			
		} else if (owner[i] == 2) {
			value = ' O ';
			disabled = true;
		} 	
	
		document.getElementById("sqr"+i).value = value;
		document.getElementById("sqr"+i).disabled = disabled;
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
	document.forms['warquest'].sqr1.value = ' X '; 
	document.forms['warquest'].sqr1.disabled = true;
	owner[1] = 1; 
	sqrT[1] = 1; 
	turn = 1; 
	vari(); 
	check();
	drawboard();
}

function set2() {
	document.forms['warquest'].sqr2.value = ' X '; 
	document.forms['warquest'].sqr2.disabled = true;
	owner[2] = 1; 
	sqrT[2] = 1; 
	turn = 1; 
	vari(); 
	check();
}

function set3() {
	document.forms['warquest'].sqr3.value = ' X '; 
	document.forms['warquest'].sqr3.disabled = true;
	owner[3] = 1; 
	sqrT[3] = 1; 
	turn = 1; 
	vari(); 
	check();
}

function set4() {
	document.forms['warquest'].sqr4.value = ' X '; 
	document.forms['warquest'].sqr4.disabled = true;
	owner[4] = 1; 
	sqrT[4] = 1; 
	turn = 1; 
	vari(); 
	check();
}

function set5() {
	document.forms['warquest'].sqr5.value = ' X '; 
	document.forms['warquest'].sqr5.disabled = true;
	owner[5] = 1; 
	sqrT[5] = 1; 
	turn = 1; 
	vari(); 
	check();
}

function set6() {
	document.forms['warquest'].sqr6.value = ' X '; 
	document.forms['warquest'].sqr6.disabled = true;
	owner[6] = 1; 
	sqrT[6] = 1; 
	turn = 1; 
	vari(); 
	check();
}

function set7() {
	document.forms['warquest'].sqr7.value = ' X '; 
	document.forms['warquest'].sqr7.disabled = true;
	owner[7] = 1; 
	sqrT[7] = 1; 
	turn = 1; 
	vari(); 
	check();
}

function set8() {
	document.forms['warquest'].sqr8.value = ' X '; 
	document.forms['warquest'].sqr8.disabled = true;
	owner[8] = 1; 
	sqrT[8] = 1; 
	turn = 1; 
	vari(); 
	check();
}

function set9() {
	document.forms['warquest'].sqr9.value = ' X '; 
	document.forms['warquest'].sqr9.disabled = true;
	owner[9] = 1; 
	sqrT[9] = 1; 
	turn = 1; 
	vari(); 
	check();
}

function check()
{
  if(sqr1 == " X " && sqr2 == " X " && sqr3 == " X ")
  {
    youWin();
    //reset()
  } 
  else if(sqr4 == " X " && sqr5 == " X " && sqr6 == " X ")
  {
    youWin();
    //reset()
  } 
  else if(sqr7 == " X " && sqr8 == " X " && sqr9 == " X ")
  {
    youWin();
    //reset()
  }
  else if(sqr1 == " X " && sqr5 == " X " && sqr9 == " X ")
  {
    youWin();
    //reset()
  }
  else if(sqr1 == " X " && sqr4 == " X " && sqr7 == " X ")
  {
    youWin();
    //reset()
  }
  else if(sqr2 == " X " && sqr5 == " X " && sqr8 == " X ")
  {
    youWin();
    //reset()
  }
  else if(sqr3 == " X " && sqr6 == " X " && sqr9 == " X ")
  {
    youWin();
    //reset()
  }
  else if(sqr1 == " X " && sqr5 == " X " && sqr9 == " X ")
  {
    youWin();
    //reset()
  }
  else if(sqr3 == " X " && sqr5 == " X " && sqr7 == " X ")
  {
    youWin();
    //reset()
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
  vari()
  drawCheck()
  if(sqr1 == " O " && sqr2 == " O " && sqr3 == " O ")
  {
    youLose();
    //reset()
  } 
  else if(sqr4 == " O " && sqr5 == " O " && sqr6 == " O ")
  {
    youLose();
    //reset()
  } 
  else if(sqr7 == " O " && sqr8 == " O " && sqr9 == " O ")
  {
    youLose();
    //reset()
  }
  else if(sqr1 == " O " && sqr5 == " O " && sqr9 == " O ")
  {
    youLose();
    //reset()
  }
  else if(sqr1 == " O " && sqr4 == " O " && sqr7 == " O ")
  {
    youLose();
    //reset()
  }
  else if(sqr2 == " O " && sqr5 == " O " && sqr8 == " O ")
  {
    youLose();
    //reset()
  }
  else if(sqr3 == " O " && sqr6 == " O " && sqr9 == " O ")
  {
    youLose();
    //reset()
  }
  else if(sqr1 == " O " && sqr5 == " O " && sqr9 == " O ")
  {
    youLose();
    //reset()
  }
  else if(sqr3 == " O " && sqr5 == " O " && sqr7 == " O ")
  {
    youLose();
    //reset()
  }
}

function drawCheck()
{
  vari()
  
  moveCount = 0;
  for( var i = 0; i < 9; i++ ) {
   	moveCount += sqrT[i] 
  }
 
  if(moveCount == 9)
  {
    //reset()
    youDraw();
  }
}

function winCheck()
{
  check2()
  if(sqr1 == " O " && sqr2 == " O " && sqrT[3] == 0 && turn == 1)
  {
    document.forms['warquest'].sqr3.value = " O "
	 document.forms['warquest'].sqr3.disabled = true;
    sqrT[3] = 1;
    turn = 0;
  }
  else if(sqr2 == " O " && sqr3 == " O " && sqrT[1] == 0 && turn == 1)
  {
    document.forms['warquest'].sqr1.value = " O "
	 document.forms['warquest'].sqr1.disabled = true;
    sqrT[1] = 1;
    turn = 0;
  }
  else if(sqr4 == " O " && sqr5 == " O " && sqrT[6] == 0 && turn == 1)
  {
    document.forms['warquest'].sqr6.value = " O "
	 document.forms['warquest'].sqr6.disabled = true;
    sqrT[6] = 1;
    turn = 0;
  }
  else if(sqr5 == " O " && sqr6 == " O " && sqrT[4] == 0 && turn == 1)
  {
    document.forms['warquest'].sqr4.value = " O "
	 document.forms['warquest'].sqr4.disabled = true;
    sqrT[4] = 1;
    turn = 0;
  }
  else if(sqr7 == " O " && sqr8 == " O " && sqrT[9] == 0 && turn == 1)
  {
    document.forms['warquest'].sqr9.value = " O "
	 document.forms['warquest'].sqr9.disabled = true;
    sqrT[9] = 1;
    turn = 0;
  }
  else if(sqr8 == " O " && sqr9 == " O " && sqrT[7] == 0 && turn == 1)
  {
    document.forms['warquest'].sqr7.value = " O "
	 document.forms['warquest'].sqr7.disabled = true;
    sqrT[7] = 1;
    turn = 0;
  }
  else if(sqr1 == " O " && sqr5 == " O " && sqrT[9] == 0 && turn == 1)
  {
    document.forms['warquest'].sqr9.value = " O "
	 document.forms['warquest'].sqr9.disabled = true;
    sqrT[9] = 1;
    turn = 0;
  }
  else if(sqr5 == " O " && sqr9 == " O " && sqrT[1] == 0 && turn == 1)
  {
    document.forms['warquest'].sqr1.value = " O "
	 document.forms['warquest'].sqr1.disabled = true;
    sqrT[1] = 1;
    turn = 0;
  }
  else if(sqr3 == " O " && sqr5 == " O " && sqrT[7] == 0 && turn == 1)
  {
    document.forms['warquest'].sqr7.value = " O "
	 document.forms['warquest'].sqr7.disabled = true;
    sqrT[7] = 1;
    turn = 0;
  }
  else if(sqr7 == " O " && sqr5 == " O " && sqrT[3] == 0 && turn == 1)
  {
    document.forms['warquest'].sqr3.value = " O "
	 document.forms['warquest'].sqr3.disabled = true;
    sqrT[3] = 1;
    turn = 0;
  }
  else if(sqr1 == " O " && sqr3 == " O " && sqrT[2] == 0 && turn == 1)
  {
    document.forms['warquest'].sqr2.value = " O "
	 document.forms['warquest'].sqr2.disabled = true;
    sqrT[2] = 1;
    turn = 0;
  }
  else if(sqr4 == " O " && sqr6 == " O " && sqrT[5] == 0 && turn == 1)
  {
    document.forms['warquest'].sqr5.value = " O "
	 document.forms['warquest'].sqr5.disabled = true;
    sqrT[5] = 1;
    turn = 0;
  }
  else if(sqr7 == " O " && sqr9 == " O " && sqrT[8] == 0 && turn == 1)
  {
    document.forms['warquest'].sqr8.value = " O "
	 document.forms['warquest'].sqr8.disabled = true;
    sqrT[8] = 1;
    turn = 0;
  }
  else if(sqr1 == " O " && sqr7 == " O " && sqrT[4] == 0 && turn == 1)
  {
    document.forms['warquest'].sqr4.value = " O "
	 document.forms['warquest'].sqr4.disabled = true;
    sqrT[4] = 1;
    turn = 0;
  }
  else if(sqr2 == " O " && sqr8 == " O " && sqrT[5] == 0 && turn == 1)
  {
    document.forms['warquest'].sqr5.value = " O "
	 document.forms['warquest'].sqr5.disabled = true;
    sqrT[5] = 1;
    turn = 0;
  }
  else if(sqr3 == " O " && sqr9 == " O " && sqrT[6] == 0 && turn == 1)
  {
    document.forms['warquest'].sqr6.value = " O "
	 document.forms['warquest'].sqr6.disabled = true;
    sqrT[6] = 1;
    turn = 0;
  }
  else if(sqr1 == " O " && sqr5 == " O " && sqrT[9] == 0 && turn == 1)
  {
    document.forms['warquest'].sqr9.value = " O "
	 document.forms['warquest'].sqr9.disabled = true;
    sqrT[9] = 1;
    turn = 0;
  }
  else if(sqr4 == " O " && sqr7 == " O " && sqrT[1] == 0 && turn == 1)
  {
    document.forms['warquest'].sqr1.value = " O "
	 document.forms['warquest'].sqr1.disabled = true;
    sqrT[1] = 1;
    turn = 0;
  }
  else if(sqr5 == " O " && sqr8 == " O " && sqrT[2] == 0 && turn == 1)
  {
    document.forms['warquest'].sqr2.value = " O "
	 document.forms['warquest'].sqr2.disabled = true;
    sqrT[2] = 1;
    turn = 0;
  }
  else if(sqr6 == " O " && sqr9 == " O " && sqrT[3] == 0 && turn == 1)
  {
    document.forms['warquest'].sqr3.value = " O "
	 document.forms['warquest'].sqr3.disabled = true;
    sqrT[3] = 1;
    turn = 0;
  }
  else if(sqr1 == " O " && sqr4 == " O " && sqrT[7] == 0 && turn == 1)
  {
    document.forms['warquest'].sqr7.value = " O "
	 document.forms['warquest'].sqr7.disabled = true;
    sqrT[7] = 1;
    turn = 0;
  }
  else if(sqr2 == " O " && sqr5 == " O " && sqrT[8] == 0 && turn == 1)
  {
    document.forms['warquest'].sqr8.value = " O "
	 document.forms['warquest'].sqr8.disabled = true;
    sqrT[8] = 1;
    turn = 0;
  }
  else if(sqr3 == " O " && sqr6 == " O " && sqrT[9] == 0 && turn == 1)
  {
    document.forms['warquest'].sqr9.value = " O "
	 document.forms['warquest'].sqr9.disabled = true;
    sqrT[9] = 1;
    turn = 0;
  }
  else if(sqr1 == " O " && sqr9 == " O " && sqrT[5] == 0 && turn == 1)
  {
    document.forms['warquest'].sqr5.value = " O "
	 document.forms['warquest'].sqr5.disabled = true;
    sqrT[5] = 1;
    turn = 0;
  }
  else if(sqr3 == " O " && sqr7 == " O " && sqrT[5] == 0 && turn == 1)
  {
    document.forms['warquest'].sqr5.value = " O "
	 document.forms['warquest'].sqr5.disabled = true;
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
  if(sqr1 == " X " && sqr2 == " X " && sqrT[3] == 0 && turn == 1)
  {
    document.forms['warquest'].sqr3.value = " O "
	 document.forms['warquest'].sqr3.disabled = true;
    sqrT[3] = 1;
    turn = 0;
  }
  else if(sqr2 == " X " && sqr3 == " X " && sqrT[1] == 0 && turn == 1)
  {
    document.forms['warquest'].sqr1.value = " O "
	 document.forms['warquest'].sqr1.disabled = true;
    sqrT[1] = 1;
    turn = 0;
  }
  else if(sqr4 == " X " && sqr5 == " X " && sqrT[6] == 0 && turn == 1)
  {
    document.forms['warquest'].sqr6.value = " O "
	 document.forms['warquest'].sqr6.disabled = true;
    sqrT[6] = 1;
    turn = 0;
  }
  else if(sqr5 == " X " && sqr6 == " X " && sqrT[4] == 0 && turn == 1)
  {
    document.forms['warquest'].sqr4.value = " O "
	 document.forms['warquest'].sqr4.disabled = true;
    sqrT[4] = 1;
    turn = 0;
  }
  else if(sqr7 == " X " && sqr8 == " X " && sqrT[9] == 0 && turn == 1)
  {
    document.forms['warquest'].sqr9.value = " O "
	 document.forms['warquest'].sqr9.disabled = true;
    sqrT[9] = 1;
    turn = 0;
  }
  else if(sqr8 == " X " && sqr9 == " X " && sqrT[7] == 0 && turn == 1)
  {
    document.forms['warquest'].sqr7.value = " O "
	 document.forms['warquest'].sqr7.disabled = true;
    sqrT[7] = 1;
    turn = 0;
  }
  else if(sqr1 == " X " && sqr5 == " X " && sqrT[9] == 0 && turn == 1)
  {
    document.forms['warquest'].sqr9.value = " O "
	 document.forms['warquest'].sqr9.disabled = true;
    sqrT[9] = 1;
    turn = 0;
  }
  else if(sqr5 == " X " && sqr9 == " X " && sqrT[1] == 0 && turn == 1)
  {
    document.forms['warquest'].sqr1.value = " O "
	 document.forms['warquest'].sqr1.disabled = true;
    sqrT[1] = 1;
    turn = 0;
  }
  else if(sqr3 == " X " && sqr5 == " X " && sqrT[7] == 0 && turn == 1)
  {
    document.forms['warquest'].sqr7.value = " O "
	 document.forms['warquest'].sqr7.disabled = true;
    sqrT[7] = 1;
    turn = 0;
  }
  else if(sqr7 == " X " && sqr5 == " X " && sqrT[3] == 0 && turn == 1)
  {
    document.forms['warquest'].sqr3.value = " O "
	 document.forms['warquest'].sqr3.disabled = true;
    sqrT[3] = 1;
    turn = 0;
  }
  else if(sqr1 == " X " && sqr3 == " X " && sqrT[2] == 0 && turn == 1)
  {
    document.forms['warquest'].sqr2.value = " O "
	 document.forms['warquest'].sqr2.disabled = true;
    sqrT[2] = 1;
    turn = 0;
  }
  else if(sqr4 == " X " && sqr6 == " X " && sqrT[5] == 0 && turn == 1)
  {
    document.forms['warquest'].sqr5.value = " O "
	 document.forms['warquest'].sqr5.disabled = true;
    sqrT[5] = 1;
    turn = 0;
  }
  else if(sqr7 == " X " && sqr9 == " X " && sqrT[8] == 0 && turn == 1)
  {
    document.forms['warquest'].sqr8.value = " O "
	 document.forms['warquest'].sqr8.disabled = true;
    sqrT[8] = 1;
    turn = 0;
  }
  else if(sqr1 == " X " && sqr7 == " X " && sqrT[4] == 0 && turn == 1)
  {
    document.forms['warquest'].sqr4.value = " O "
	 document.forms['warquest'].sqr4.disabled = true;
    sqrT[4] = 1;
    turn = 0;
  }
  else if(sqr2 == " X " && sqr8 == " X " && sqrT[5] == 0 && turn == 1)
  {
    document.forms['warquest'].sqr5.value = " O "
	 document.forms['warquest'].sqr5.disabled = true;
    sqrT[5] = 1;
    turn = 0;
  }
  else if(sqr3 == " X " && sqr9 == " X " && sqrT[6] == 0 && turn == 1)
  {
    document.forms['warquest'].sqr6.value = " O "
	 document.forms['warquest'].sqr6.disabled = true;
    sqrT[6] = 1;
    turn = 0;
  }
  else if(sqr1 == " X " && sqr5 == " X " && sqrT[9] == 0 && turn == 1)
  {
    document.forms['warquest'].sqr9.value = " O "
	 document.forms['warquest'].sqr9.disabled = true;
    sqrT[9] = 1;
    turn = 0;
  }
  else if(sqr4 == " X " && sqr7 == " X " && sqrT[1] == 0 && turn == 1)
  {
    document.forms['warquest'].sqr1.value = " O "
	 document.forms['warquest'].sqr1.disabled = true;
    sqrT[1] = 1;
    turn = 0;
  }
  else if(sqr5 == " X " && sqr8 == " X " && sqrT[2] == 0 && turn == 1)
  {
    document.forms['warquest'].sqr2.value = " O "
	 document.forms['warquest'].sqr2.disabled = true;
    sqrT[2] = 1;
    turn = 0;
  }
  else if(sqr6 == " X " && sqr9 == " X " && sqrT[3] == 0 && turn == 1)
  {
    document.forms['warquest'].sqr3.value = " O "
	 document.forms['warquest'].sqr3.disabled = true;
    sqrT[3] = 1;
    turn = 0;
  }
  else if(sqr1 == " X " && sqr4 == " X " && sqrT[7] == 0 && turn == 1)
  {
    document.forms['warquest'].sqr7.value = " O "
	 document.forms['warquest'].sqr7.disabled = true;
    sqrT[7] = 1;
    turn = 0;
  }
  else if(sqr2 == " X " && sqr5 == " X " && sqrT[8] == 0 && turn == 1)
  {
    document.forms['warquest'].sqr8.value = " O "
	 document.forms['warquest'].sqr8.disabled = true;
    sqrT[8] = 1;
    turn = 0;
  }
  else if(sqr3 == " X " && sqr6 == " X " && sqrT[9] == 0 && turn == 1)
  {
    document.forms['warquest'].sqr9.value = " O "
	 document.forms['warquest'].sqr9.disabled = true;
    sqrT[9] = 1;
    turn = 0;
  }
  else if(sqr1 == " X " && sqr9 == " X " && sqrT[5] == 0 && turn == 1)
  {
    document.forms['warquest'].sqr5.value = " O "
	 document.forms['warquest'].sqr5.disabled = true;
    sqrT[5] = 1;
    turn = 0;
  }
  else if(sqr3 == " X " && sqr7 == " X " && sqrT[5] == 0 && turn == 1)
  {
    document.forms['warquest'].sqr5.value = " O "
	 document.forms['warquest'].sqr5.disabled = true;
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
  vari()
  if(document.forms['warquest'].sqr5.value == "   " && turn == 1)
  {
    document.forms['warquest'].sqr5.value = " O "
	 document.forms['warquest'].sqr5.disabled = true;
    turn = 0
    sqrT[5] = 1
  }
  else if(document.forms['warquest'].sqr1.value == "   " && turn == 1)
  {
    document.forms['warquest'].sqr1.value = " O "
	 document.forms['warquest'].sqr1.disabled = true;
    turn = 0
    sqrT[1] = 1
  }
  else if(document.forms['warquest'].sqr9.value == "   " && turn == 1)
  {
    document.forms['warquest'].sqr9.value = " O "
	 document.forms['warquest'].sqr9.disabled = true;
    turn = 0
    sqrT[9] = 1
  }
  else if(document.forms['warquest'].sqr6.value == "   " && turn == 1)
  {
    document.forms['warquest'].sqr6.value = " O "
	 document.forms['warquest'].sqr6.disabled = true;
    turn = 0
    sqrT[6] = 1
  }
  else if(document.forms['warquest'].sqr2.value == "   " && turn == 1)
  {
    document.forms['warquest'].sqr2.value = " O "
	 document.forms['warquest'].sqr2.disabled = true;
    turn = 0
    sqrT[2] = 1
  }
  else if(document.forms['warquest'].sqr8.value == "   " && turn == 1)
  {
    document.forms['warquest'].sqr8.value = " O "
	 document.forms['warquest'].sqr8.disabled = true;
    turn = 0
    sqrT[8] = 1
  }
  else if(document.forms['warquest'].sqr3.value == "   " && turn == 1)
  {
    document.forms['warquest'].sqr3.value = " O "
	 document.forms['warquest'].sqr3.disabled = true;
    turn = 0
    sqrT[3] = 1
  }
  else if(document.forms['warquest'].sqr7.value == "   " && turn == 1)
  {
    document.forms['warquest'].sqr7.value = " O "
	 document.forms['warquest'].sqr7.disabled = true;
    turn = 0
    sqrT[7] = 1
  }
  else if(document.forms['warquest'].sqr4.value == "   " && turn == 1)
  {
    document.forms['warquest'].sqr4.value = " O "
	 document.forms['warquest'].sqr4.disabled = true;
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
	
  vari()
  turn = 0
  moveCount = 0
}

function resetter()
{
  reset()
}

function youLose() {
	simpleHttpRequest(bet, key, 0);
	disable();
}

function youWin() {	
	simpleHttpRequest(bet, key, 1);
	disable();
}

function youDraw() {
	simpleHttpRequest(bet, key, 2);
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