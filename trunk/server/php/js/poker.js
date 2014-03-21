/* All copyrights reserved (c) 2008-2014 PlaatSoft */

var cardWidth=90;   // CARD WIDTH IN PIXELS, THE CARD HEIGHT WILL BE 2X THIS VALUE.
var cardBGC="#0066AE";  // BACKGROUND COLOR OF CARD WHEN "FLIPPED" TO HIDE THE CARD.

// USE THE ARRAY BELOW TO CHANGE THE BET MULTIPIERS IF DESIRED.
var multipliers=[1,2,3,7,10,15,20,30,60];

// THE POSITIONS OF THE NUMBERS ABOVE CORRESPOND TO THE POSITIONS OF THE WIN TYPE IN THE LIST BELOW.
// [ ONE PAIR , TWO PAIR , THREE PAIR , STRAIGHT , FLUSH , FULL HOUSE , FOUR OF A KIND , STRAIGHT FLUSH , ROYAL STRIGHT FLUSH ]

var suits=[0,'&clubs;','&spades;','&hearts;','&diams;'];
var nums=['A','2','3','4','5','6','7','8','9','10','J','Q','K','A'];
var cNum=[0,0,0,0,0,0];
var cSuit=[0,0,0,0,0,0];
var deck=new Array();
var replaceBusy=true;
var buttonBusy=false;
var isBegin=true;
var toRepl=[0,1,1,1,1,1];
var cards;
var tmpn;
var cards=new Array();
var arrows=new Array();
var textStyle="font-family:verdana; font-size:8pt; color:black";
var wamount;
var start=false;

var bet;
var key;
var token;

function simpleHttpRequest(result, multiply) {
 
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
	
	var newInput5 = document.createElement('input');
	newInput5.setAttribute('type','hidden');
	newInput5.setAttribute('name','multiply');
	newInput5.setAttribute('value', multiply);
	form.appendChild(newInput5);	
	
	/*tmp = ""
	for( var i= 1; i<6; i++ ) {

		tmp += cSuite[i];
	}
		
	var newInput5 = document.createElement('input');
	newInput5.setAttribute('type','hidden');
	newInput5.setAttribute('name','cards');
	newInput5.setAttribute('value', tmp);
	form.appendChild(newInput5);*/
	
	form.submit();	
}

// BUILD AND SHUFFLE THE DECK.
function buildShuffle() {

	for(i=1;i<6;i++) {
		cards[i].innerHTML="";
		cards[i].style.backgroundColor=cardBGC;
		arrows[i].on=false;
	}

	isBegin=true;
	var x,y,xd,yd;
	var A=new Array();
	
	for(s=1;s<=4;s++) {
		for(c=1;c<=13;c++) {
			A[s*13-13+c]=[s,c];
		}
	}
	
	for(i=0;i<=300;i++) {
		x=Math.floor(Math.random()*52+1);
		xd=A[x];
		y=Math.floor(Math.random()*52+1);
		yd=A[y];
		A[y]=xd;
		A[x]=yd;
	}
	deck=A;
	replaceBusy=true;
	buttonBusy=true;
	replaceCards();
}

// TOGGLES THE CHECKBOX UNDER THE CARD WHEN CLICKED.
function changeCard(n) {
	if(!replaceBusy){
		arrows[n].on=!arrows[n].on;
		arrows[n].innerHTML=(arrows[n].on)?"&Delta;":"&nbsp;";
	}
}

// REPLACES THE CARDS CHECKED.
function replaceCards() {
	for(i=1;i<6;i++){
		if(arrows[i].on || isBegin) toRepl[i]=1;
	}
	revert(1);
}

// REVERTS THE CARDS TO "FACE DOWN" BEFORE PUTTING NEW ONES UP.
function revert(i) {
	if(i<6) {
		if(toRepl[i]==1) {
			cards[i].innerHTML="";
			cards[i].style.backgroundColor=cardBGC;
			setTimeout('revert('+(i+1)+')',100);
		} else revert(i+1);
	} else {
		if(isBegin) {
			setTimeout('subReplace(1)',200);
		}
		else setTimeout('subReplace(1)',200);
	}
}

//SUB-FUNCTION TO REPLACE THE CARDS TO ACHIEVE THE "FLIPPING" DELAY.
function subReplace(i) {
	if(i>5) {
		if(isBegin) {
			isBegin=false;
			buttonBusy=false;
			replaceBusy=false;
		} else {
			testCards();
		}
	} else {
	
		if(toRepl[i]==1) {
			cSuit[i]=deck[deck.length-1][0];
			cNum[i]=deck[deck.length-1][1];
			cards[i].style.backgroundColor="white";
			var sts=deck[deck.length-1][0];
			cards[i].innerHTML='<span style="font-family:arial; font-size:'+(cardWidth-10)+'px; font-weight:bold; color:'+((sts==1||sts==2)?'black':'red')+'">'+nums[deck[deck.length-1][1]]+'</span><br><span style="font-family:arial; font-size:'+(cardWidth-2)+'px; color:'+((sts==1||sts==2)?'black':'red')+'">'+suits[sts]+'</span>';
			deck.length=deck.length-1;
		
			arrows[i].on=false;
			toRepl[i]=0;
			setTimeout('subReplace('+(i+1)+')',200);
		} else {
			subReplace(i+1);
		}
	}
}

// CHANGES THE BUTTON LOOK AND ACTION WHEN CLICKED.
function testStatus() {
	
	if(!buttonBusy) {
		buttonBusy=true;
		if(isBegin) {
		
			replaceBusy=true;
			buildShuffle();
			
		} else {
		
			replaceBusy=true;
			replaceCards();
		}
	}
}

// CALLS THE FUNCTION TO TEST THE CARDS AND UPDATES MONEY, STATUS, ETC.
function testCards() {
	isBegin=true;
	buttonBusy=true;
	replaceBusy=true;
	var txt = testCombos();
	
	simpleHttpRequest(txt, wamount);
	
	buttonBusy=false;
}

// GET ELEMENT REFERENCES
function getEl(s){
	return document.getElementById(s);
}

// SUB-FUNCTION FOR THE "SORT()" METHOD
function sortnumbs(a,b){
	return a-b;
}

// TESTS THE FOR "FLUSH" CONDITION ON A SORTED DECK.
function testflush(){
	return ( (cSuit[1]==cSuit[2])&&(cSuit[1]==cSuit[3])&&(cSuit[1]==cSuit[4])&&(cSuit[1]==cSuit[5]) );
}

// TESTS FOR "ROYAL STRAIGHT" CONDITION ON A SORTED DECK (USED WITH THE testflush() FUNCTION).
function testface(){
	return ( ((cNum[1]>=10)||(cNum[1]==1))&&((cNum[2]>=10)||(cNum[2]==1))&&((cNum[3]>=10)||(cNum[3]==1))&&((cNum[4]>=10)||(cNum[4]==1))&&((cNum[5]>=10)||(cNum[5]==1)) )
}

// TESTS FOR "STRAIGHT" CONDITION ON A SORTED DECK.
function teststraight(){
	var x=( (tmpn[1]+4==tmpn[5]) && (tmpn[2]+3==tmpn[5]) && (tmpn[3]+2==tmpn[5]) && (tmpn[4]+1==tmpn[5]) );
	for(i=1;i<=5;i++){
		if(tmpn[i]==1)tmpn[i]=14;
	}
	tmpn=new Array();
	tmpn[0]=0;
	for(i=1;i<=5;i++)tmpn[i]=cNum[i];
	tmpn.sort(sortnumbs);
	var y=( (tmpn[1]+4==tmpn[5]) && (tmpn[2]+3==tmpn[5]) && (tmpn[3]+2==tmpn[5]) && (tmpn[4]+1==tmpn[5]) );
	return x||y;
}

// FUNCTION TO TEST ALL CARD POSSIBILITIES
function testCombos(){
	tmpn=new Array();
	tmpn[0]=0;
	for(i=1;i<=5;i++)tmpn[i]=cNum[i];
	tmpn.sort(sortnumbs);
	var wtype='Nothing';
	
	wamount=0;
	if( ((tmpn[1]==tmpn[2])&&(tmpn[1]>=10))||((tmpn[2]==tmpn[3])&&(tmpn[2]>=10))||((tmpn[3]==tmpn[4])&&(tmpn[3]>=10))||((tmpn[4]==tmpn[5])&&(tmpn[4]>=10)) ){
		wtype='a Pair';
		wamount=multipliers[0];
	}
	if( ((tmpn[1]==tmpn[2])&&(tmpn[3]==tmpn[4]))||((tmpn[1]==tmpn[2])&&(tmpn[4]==tmpn[5]))||((tmpn[2]==tmpn[3])&&(tmpn[4]==tmpn[5])) ){
		wtype='Two Pair';
		wamount=multipliers[1];
	}
	if( ((tmpn[1]==tmpn[2])&&(tmpn[1]==tmpn[3]))||((tmpn[2]==tmpn[3])&&(tmpn[2]==tmpn[4]))||((tmpn[3]==tmpn[4])&&(tmpn[3]==tmpn[5])) ){
		wtype='3 of a Kind';
		wamount=multipliers[2];
	}
	if( teststraight() ){
		wtype='a Straight';
		wamount=multipliers[3];
	}
	if( testflush() ){
		wtype='a Flush';
		wamount=multipliers[4];
	}
	if( ((tmpn[1]==tmpn[2])&&(tmpn[3]==tmpn[4])&&(tmpn[3]==tmpn[5])&&(tmpn[1]!=tmpn[3]))||((tmpn[4]==tmpn[5])&&(tmpn[1]==tmpn[2])&&(tmpn[1]==tmpn[3])&&(tmpn[4]!=tmpn[1])) ){
		wtype='a Full House';
		wamount=multipliers[5];
	}
	if( ((tmpn[1]==tmpn[2])&&(tmpn[1]==tmpn[3])&&(tmpn[1]==tmpn[4]))||((tmpn[2]==tmpn[3])&&(tmpn[2]==tmpn[4])&&(tmpn[2]==tmpn[5])) ){
		wtype='4 of a Kind';
		wamount=multipliers[6];
	}	
	// STRAIGHT FLUSH
	if(testflush() && teststraight()){
		wtype='a Straight Flush';
		wamount=multipliers[7];
	}
	// ROYAL STRAIGHT FLUSH
	if(teststraight() && testface() && testflush()){
		wtype='a Royal Straight Flush';
		wamount=multipliers[8];
	}
	return wtype;
}

function initPoker( bet, key, token ) {

	this.bet = bet;
	this.key = key;
	this.token = token;
	
	for(i=1;i<6;i++) {
		cards[i]=getEl('c'+i);
		cards[i].innerHTML='';
	}
	
	for(i=1;i<6;i++) {
		arrows[i]=getEl('b'+i);
		arrows[i].innerHTML='';
		arrows[i].on=false;
	}
	
	if (start) {
		testStatus();	
	}
}

function showRresultPoker($type) {

	for(i=1;i<6;i++) {
		cards[i]=getEl('c'+i);
		cards[i].innerHTML='<span style="font-family:arial; font-size:'+(cardWidth-10)+'px; font-weight:bold; color:'+((sts==1||sts==2)?'black':'red')+'">'+nums[deck[deck.length-1][1]]+'</span><br><span style="font-family:arial; font-size:'+(cardWidth-2)+'px; color:'+((sts==1||sts==2)?'black':'red')+'">'+suits[type[i]]+'</span>';
	}
	
	for(i=1;i<6;i++) {
		arrows[i].innerHTML='';
		arrows[i].on=false;
	} 
}

function startPoker() {
	start=true;
}