/* All copyrights reserved (c) 2008-2014 PlaatSoft */

var suits=['clubs','spades','hearts','diamonds'];
var nums=['2','3','4','5','6','7','8','9','10','J','Q','K','A'];
var deck = new Array();
var cards = new Array();
var gamePhase = 1;
var bet;
var key;
var token;

function swapeCard(i) {
	
	if (gamePhase == 2) {
	
		cards[i][2]=!cards[i][2];
		
		drawCards();
	}
}

function getCard(c) {

	do {
		nr = Math.floor(Math.random()*52);
	} while (deck[nr][3]==true);
		
	deck[nr][3]=true;
	cards[c]=deck[nr];
}

function initCards(bet, key, token) {

	var i=0;
	var nr;		

	for (var s=0; s<suits.length; s++) {
	
		for (var n=0; n<nums.length; n++) {
	
			var part = new Array();
			
			part[0] = suits[s]; /* Card Suit */
			part[1] = nums[n];	/* Card Type */
			part[2] = false;		/* Card backside */
			part[3] = false;		/* Card selected */
			
			deck[i++] = part;
		}	
	}

	for (var c=0; c<5; c++) {			
		getCard(c);
	}	
	
	this.bet = bet;
	this.key = key;
	this.token = token;
	
	drawCards();
}

function statemachineCards(c) {
	
	console.log("game phase = "+gamePhase);
	
	if ((gamePhase==2) && (cards[c][2]==false)) {
		getCard(c);
	}
	
	cards[c][2]=true;
	drawCards();
	
	if (c < (cards.length-1)) {
		setTimeout('statemachineCards('+(c+1)+')',100);		
		
	} else {	
		gamePhase++;
		
		if (gamePhase==3) {
			resultCards();
		}
	}
}

function drawCards() {

	for (var c=0; c<cards.length; c++) {
	
		if (cards[c][2]==true) {
			document.getElementById("card"+c).src=Poker.getCardData(131, cards[c][0],cards[c][1]);			
		} else {
			document.getElementById("card"+c).src=Poker.getBackData(131, '#2E319C', '#7A7BB8');
		}
	}
}

function resultCards() {

	var result = 0;
	var index1;
	var index2;

	var cards2 = cards.slice(0);

	/* Sort cards before compare */
	cards.sort(function (a, b) {
    if (nums.indexOf(a[1]) > nums.indexOf(b[1]))
      return 1;
    if (nums.indexOf(a[1]) < nums.indexOf(b[1]))
      return -1;
    // a must be equal to b
    return 0;});
	 
	/* Pair */
	if( (cards[0][1]==cards[1][1]) ||
		 (cards[1][1]==cards[2][1]) ||
		 (cards[2][1]==cards[3][1]) ||
		 (cards[3][1]==cards[4][1])) {
		
		console.log("Pair");
		result = 1;
	}
	
	/* Two Pairs */	
	if( ((cards[0][1]==cards[1][1]) && (cards[2][1]==cards[3][1])) ||
		 ((cards[0][1]==cards[1][1]) && (cards[3][1]==cards[3][1])) ||
		 ((cards[1][1]==cards[2][1]) && (cards[3][1]==cards[4][1])) ) {
		
		console.log("Two Pair");
		result = 2;
	}
	
	/* Three of a kind */	
	if( ((cards[0][1]==cards[1][1]) && (cards[1][1]==cards[2][1])) ||
		 ((cards[1][1]==cards[2][1]) && (cards[2][1]==cards[3][1])) ||
		 ((cards[2][1]==cards[3][1]) && (cards[3][1]==cards[4][1])) ) {
	
		console.log("Three of a kind");
		result = 3;
	}
	
	/* Straight */	
	index2 = nums.indexOf(cards[0][1]);
	for(var c=1; c<5; c++) {
		if (nums.indexOf(cards[c][1])==(index2+1)) {
			index2 = nums.indexOf(cards[c][1]);
			if (c==4) {		

				console.log("Straight");
				result = 4;
			} 
		} else {		
			break;
		}
	}
	
	/* Flush */	
	index1 = suits.indexOf(cards[0][0]);
	for(var c=1; c<5; c++) {	
		if (suits.indexOf(cards[c][0])==index1) {
			if (c==4) {		
				console.log("Flush");		
				result = 5;
			}
		} else {		
			break;
		}
	}
	
	/* Full house */	
	if( ((cards[0][1]==cards[1][1]) && (cards[1][1]==cards[2][1]) && (cards[3][1]==cards[4][1])) ||
		 ((cards[0][1]==cards[1][1]) && (cards[2][1]==cards[3][1]) && (cards[3][1]==cards[4][1])) ) {
	
		console.log("Full house");		
		result = 6;
	}
		
	/* Four of a kind */	
	if( ((cards[0][1]==cards[1][1]) && (cards[1][1]==cards[2][1]) && (cards[2][1]==cards[3][1])) ||
		 ((cards[1][1]==cards[2][1]) && (cards[2][1]==cards[3][1]) && (cards[3][1]==cards[4][1])) ) {
	
		console.log("Four of a kind");
		result = 7;
	}
	
	/* Straight Flush */	
	index1 = suits.indexOf(cards[0][0]);
	index2 = nums.indexOf(cards[0][1]);	
	for(var c=1; c<5; c++) {
		if ((suits.indexOf(cards[c][0])==index1) && (nums.indexOf(cards[c][1])==(index2+1))) {
			index2 = nums.indexOf(cards[c][1]);
			if (c==4) {		

				console.log("Straight Flush");	
				result = 8;
			}
		}
		else {		
			break;
		}
	}
	
	/* Royal Flush */	
	index1 = suits.indexOf(cards[0][0]);
	index2 = nums.indexOf(cards[0][1]);	
	if (index2==8) {
		for(var c=1; c<5; c++) {
			if ((suits.indexOf(cards[c][0])==index1) && (nums.indexOf(cards[c][1])==(index2+1))) {
				index2 = nums.indexOf(cards[c][1]);
				if (c==4) {			
				
					console.log("Royal Flush");
					result = 9;
				}
			}
			else {		
				break;
			}
		}
	}
	
	console.log("result = " +result);
	
	cardRequest(result, cards2);
	return result;
}

function cardRequest(result, cards2) {
 
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
	newInput5.setAttribute('name','cards');
	newInput5.setAttribute('value', JSON.stringify(cards2));
	form.appendChild(newInput5);	
	
	form.submit();	
}

function showCards(cards) {
	
	this.cards = JSON.parse(cards);
	
	drawCards();	
}