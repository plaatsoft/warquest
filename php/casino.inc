<?php

/* 
**  ========
**  WARQUEST
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
**  All copyrights reserved (c) 2008-2013 PlaatSoft
*/

/*
** ---------------------------------------------------------------- 
** Post parameters
** ----------------------------------------------------------------
*/

$bet = warquest_post('bet', 0);
$bet = str_replace(".", "", $bet);

$key = warquest_post('key', 0);
$angle = warquest_post('angle', 0);
$wheel = warquest_post('wheel', 0);
$number = warquest_post('number', 0);	
$price = warquest_post('price', 0);	
$result = warquest_post('result', 0);	
$board = warquest_post('board', "");	

if (isset($_POST['a00']) && $_POST['a00'] != "") {
	$a00 = $_POST['a00'];
} else {
	$a00 = 'appletop.src';
}

if (isset($_POST['a01']) && $_POST['a01'] != "") {
	$a01 = $_POST['a01'];
} else {
	$a01 = 'banana.src';
}

if (isset($_POST['a02']) && $_POST['a02'] != "") {
	$a02 = $_POST['a02'];
} else {
	$a02 = 'pearbtm.src';
}

if (isset($_POST['a10']) && $_POST['a10'] != "") {
	$a10 = $_POST['a10'];
} else {
	$a10 = 'peartop.src';
}

if (isset($_POST['a11']) && $_POST['a11'] != "") {
	$a11 = $_POST['a11'];
} else {
	$a11 = 'bar.src';
}

if (isset($_POST['a12']) && $_POST['a12'] != "") {
	$a12 = $_POST['a12'];
} else {
	$a12 = 'orangebtm.src';
}

if (isset($_POST['a20']) && $_POST['a20'] != "") {
	$a20 = $_POST['a20'];
} else {
	$a20 = 'bananatop.src';
}

if (isset($_POST['a21']) && $_POST['a21'] != "") {
	$a21 = $_POST['a21'];
} else {
	$a21 = 'orange.src';
}

if (isset($_POST['a22']) && $_POST['a22'] != "") {
	$a22 = $_POST['a22'];
} else {
	$a22 = 'grapebtm.src';
}

/*
** ---------------------------------------------------------------- 
** Slot Machine
** ----------------------------------------------------------------
*/

function warquest_casino_slotmachine2_do() {

	/* input */
	global $sid;
	global $bet;
	global $key;
	global $price;
	
	/* output */
	global $player;
	global $popup;

	if ($key != $player->request-1) {
	
		$message= t('SYSTEM_HACK_DETECTED');
		$popup .= warquest_box_icon("warning", $message);	
		
	} else if (($price>0) && ($price<76)) {
	
		$money = $bet * $price;
		$player->money += $money;
		
		$message = t('CASINO_SLOTMACHINE_WIN', health_format($price), money_format1($money)); 
		$popup .= warquest_box_icon("info", $message);	
		warquest_info($message);
		
		$log = 'Slot Machine won '.number_format2($money);		
		warquest_user_log($player, $log);
	
	} else if ($price<0) {
	
		$message = t('CASINO_SLOTMACHINE_LOST', money_format1($bet));
		$popup .= warquest_box_icon("warning", $message);	
		
		$log = 'Slot Machine lose '.number_format2($bet);		
		warquest_user_log($player, $log);
	}
}

function warquest_casino_slotmachine1_do() {
	
	/* input */
	global $sid;
	global $bet;
	global $price;

	/* output */
	global $eid;
	global $player;
	global $popup;
		
	/* New game, check parameters */
	if ($bet==0) {			
		$eid=0;		
		$message = t('CASINO_NO_BET').'<br/>';			
	}
		
	if ($bet>10000000) {	
		$eid=0;
		$message = t('CASINO_BET_TO_LARGE', number_format(10000000,0,",",".")).'<br/>';	
	}
	
	if ($bet > $player->money) {	
		$eid=0;	
		$message = t('CASINO_NO_MONEY').'<br/>';
	}
		
	if ($eid==0) {
	
		$popup .= warquest_box_icon("warning", $message);		
		
	} else {
	
		if ($price==0) {
			$player->money -= $bet;				
			$player->casino++;
		}
	}		
}

function warquest_casino_slotmachine_help() {

	/* output */
	global $page;
	
	$page .= t('CASINO_SLOTMACHINE_HELP');
	
	$page .= '<div class="box">';
	
	$page .= '<table>';
	
	$page .= '<tr>';
	$page .= '<td>';
	$page .= '<img src="images/slotmachine/orange.jpg" width="60" height="60" >';
	$page .= '</td>';
	$page .= '<td>';
	$page .= '<img src="images/slotmachine/orange.jpg" width="60" height="60">';
	$page .= '</td>';
	$page .= '<td width="75" >';
	$page .= '<span class="paragraph"> 1x</span>';
	$page .= '</td>';
	
	$page .= '<td>';
	$page .= '<img src="images/slotmachine/orange.jpg" width="60" height="60" >';
	$page .= '</td>';
	$page .= '<td>';
	$page .= '<img src="images/slotmachine/orange.jpg" width="60" height="60">';
	$page .= '</td>';
	$page .= '<td>';
	$page .= '<img src="images/slotmachine/orange.jpg" width="60" height="60">';
	$page .= '</td>';
	$page .= '<td>';
	$page .= '<span class="paragraph"> 15x</span>';
	$page .= '</td>';
	
	$page .= '</tr>';
	
	$page .= '<tr>';
	$page .= '<td>';
	$page .= '<img src="images/slotmachine/pear.jpg" width="60" height="60" >';
	$page .= '</td>';
	$page .= '<td>';
	$page .= '<img src="images/slotmachine/pear.jpg" width="60" height="60">';
	$page .= '</td>';
	$page .= '<td width="75">';
	$page .= '<span class="paragraph"> 2x</span>';
	$page .= '</td>';
	
	$page .= '<td>';
	$page .= '<img src="images/slotmachine/pear.jpg" width="60" height="60" >';
	$page .= '</td>';
	$page .= '<td>';
	$page .= '<img src="images/slotmachine/pear.jpg" width="60" height="60">';
	$page .= '</td>';
	$page .= '<td>';
	$page .= '<img src="images/slotmachine/pear.jpg" width="60" height="60">';
	$page .= '</td>';
	$page .= '<td>';
	$page .= '<span class="paragraph"> 20x</span>';
	$page .= '</td>';
	$page .= '</tr>';
	
	$page .= '<tr>';
	$page .= '<td>';
	$page .= '<img src="images/slotmachine/grape.jpg" width="60" height="60" >';
	$page .= '</td>';
	$page .= '<td>';
	$page .= '<img src="images/slotmachine/grape.jpg" width="60" height="60">';
	$page .= '</td>';
	$page .= '<td width="75">';
	$page .= '<span class="paragraph"> 3x</span>';
	$page .= '</td>';
	
	$page .= '<td>';
	$page .= '<img src="images/slotmachine/grape.jpg" width="60" height="60" >';
	$page .= '</td>';
	$page .= '<td>';
	$page .= '<img src="images/slotmachine/grape.jpg" width="60" height="60">';
	$page .= '</td>';
	$page .= '<td>';
	$page .= '<img src="images/slotmachine/grape.jpg" width="60" height="60">';
	$page .= '</td>';
	$page .= '<td>';
	$page .= '<span class="paragraph"> 50x</span>';
	$page .= '</td>';
	$page .= '</tr>';
	
	$page .= '<tr>';
	$page .= '<td>';
	$page .= '<img src="images/slotmachine/apple.jpg" width="60" height="60" >';
	$page .= '</td>';
	$page .= '<td>';
	$page .= '<img src="images/slotmachine/apple.jpg" width="60" height="60">';
	$page .= '</td>';
	$page .= '<td width="75">';
	$page .= '<span class="paragraph"> 4x</span>';
	$page .= '</td>';
	
	$page .= '<td>';
	$page .= '<img src="images/slotmachine/apple.jpg" width="60" height="60" >';
	$page .= '</td>';
	$page .= '<td>';
	$page .= '<img src="images/slotmachine/apple.jpg" width="60" height="60">';
	$page .= '</td>';
	$page .= '<td>';
	$page .= '<img src="images/slotmachine/apple.jpg" width="60" height="60">';
	$page .= '</td>';
	$page .= '<td>';
	$page .= '<span class="paragraph"> 40x</span>';
	$page .= '</td>';
	
	$page .= '</tr>';
	
	$page .= '<tr>';
	$page .= '<td>';
	$page .= '<img src="images/slotmachine/banana.jpg" width="60" height="60" >';
	$page .= '</td>';
	$page .= '<td>';
	$page .= '<img src="images/slotmachine/banana.jpg" width="60" height="60">';
	$page .= '</td>';
	$page .= '<td width="75">';
	$page .= '<span class="paragraph"> 5x</span>';
	$page .= '</td>';
	
	$page .= '<td>';
	$page .= '<img src="images/slotmachine/banana.jpg" width="60" height="60" >';
	$page .= '</td>';
	$page .= '<td>';
	$page .= '<img src="images/slotmachine/banana.jpg" width="60" height="60">';
	$page .= '</td>';
	$page .= '<td>';
	$page .= '<img src="images/slotmachine/banana.jpg" width="60" height="60">';
	$page .= '</td>';
	$page .= '<td>';
	$page .= '<span class="paragraph"> 10x</span>';
	$page .= '</td>';
	$page .= '</tr>';
	
	$page .= '<tr>';
	$page .= '<td>';
	$page .= '<img src="images/slotmachine/pine.jpg" width="60" height="60" >';
	$page .= '</td>';
	$page .= '<td>';
	$page .= '<img src="images/slotmachine/pine.jpg" width="60" height="60">';
	$page .= '</td>';
	$page .= '<td width="75">';
	$page .= '<span class="paragraph"> 6x</span>';
	$page .= '</td>';
	
	$page .= '<td>';
	$page .= '<img src="images/slotmachine/pine.jpg" width="60" height="60" >';
	$page .= '</td>';
	$page .= '<td>';
	$page .= '<img src="images/slotmachine/pine.jpg" width="60" height="60">';
	$page .= '</td>';
	$page .= '<td>';
	$page .= '<img src="images/slotmachine/pine.jpg" width="60" height="60">';
	$page .= '</td>';
	$page .= '<td>';
	$page .= '<span class="paragraph"> 30x</span>';
	$page .= '</td>';
	$page .= '</tr>';
	
	$page .= '<tr>';
	$page .= '<td>';
	$page .= '<img src="images/slotmachine/bar.jpg" width="60" height="60" >';
	$page .= '</td>';
	$page .= '<td>';
	$page .= '<img src="images/slotmachine/bar.jpg" width="60" height="60">';
	$page .= '</td>';
	$page .= '<td width="75">';
	$page .= '<span class="paragraph"> 12x</span>';
	$page .= '</td>';
	
	$page .= '<td>';
	$page .= '<img src="images/slotmachine/bar.jpg" width="60" height="60" >';
	$page .= '</td>';
	$page .= '<td>';
	$page .= '<img src="images/slotmachine/bar.jpg" width="60" height="60">';
	$page .= '</td>';
	$page .= '<td>';
	$page .= '<img src="images/slotmachine/bar.jpg" width="60" height="60">';
	$page .= '</td>';
	$page .= '<td>';
	$page .= '<span class="paragraph"> 75x</span>';
	$page .= '</td>';
	$page .= '</tr>';
	
	$page .= '</table>';
	
	$page .= '</div>';
}

function warquest_casino_slotmachine() {

	/* input */
	global $mid;
	global $sid;
	global $cid;
	
	global $eid;
	global $player;
	global $config;
	
	global $price;	
	global $bet;
	global $a00;
	global $a01;
	global $a02;
	global $a10;
	global $a11;
	global $a12;
	global $a20;
	global $a21;
	global $a22;
		
	/* output */
	global $page; 

	$title = t('CASINO_2');
	
	$page .= '<div class="subparagraph">';	
	$page .= $title;
	$page .= '</div>';

			
	if ($player->lid < $config["casino_unlock_level_2"]) {
	
		$page .= '<br/>';
	
		$message = '<table>';
		$message .= '<tr>';
		$message .= '<td>';
		$message .= warquest_image("other/unlock.png");
		$message .= '</td>';
		$message .= '<td>';
		$message .= t('CASINO_UNLOCK', $title, $config["casino_unlock_level_2"]);
		$message .= '</td>';
		$message .= '</tr>';
		$message .= '</table>';

		$page .= warquest_box("", $message);
	
		return;
	}
		
	$money=0;
		
	$page .= '<script language="JavaScript" src="'.$config["content_url"].'js/slotmachine7.js"></script>';
		
	$page .= '<div class="box">';
	$page .= '<table>';
	$page .= '<tr>';
	
	$page .= '<td width="160" >';	
	$page .= warquest_casino_image($cid, 140, 100);
	$page .= '</td>';
	
	$page .= "<td>";
	
	$page .= "<table>";
			
	$page .= "<tr>";
	$page .= "<td>";
	$page .= t('CASINO_BET').":<br/>";
	$page .= '<input id="bet" name="bet" size="10" maxlength="7" type="text" value="'.$bet.'" /> ';
	if ($eid!=2) {
		$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&cid='.$cid.'&eid=2', t('CASINO_PLAY'), 'play');
	} else {
		$page .= '<a href="javascript:Go()">'.t('CASINO_PLAY').'</a>';
	}
	$page .= "</td>";
	$page .= "</tr>";
	
	$page .= "<tr>";
	$page .= '<td>';	
	$page .= '<br/>';	
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&cid=4', t('LINK_HELP'), 'help4');
	$page .= '</td>';
	$page .= "</tr>";
	
	$page .= '</table>';
	$page .= '</td>';
	$page .= "</tr>";
	
	$page .= '</table>';
	$page .= '</div>';
	
	$page .= '<div class="box">';
		
	$page .= '<table border=0 cellpadding=0 cellspacing=0>';

	$page .= '<tr>';
	$page .= '<td><a href="javascript:Hold(0)"><img src="" name="r0top"></a></td>';
	$page .= '<td width=9></td>';
	$page .= '<td><a href="javascript:Hold(1)"><img src="" name="r1top"></a></td>';
	$page .= '<td width=9></td>';
	$page .= '<td><a href="javascript:Hold(2)"><img src="" name="r2top"></a></td>';
	$page .= '</tr>';

	$page .= '<tr>';
	$page .= '<td><a href="javascript:Hold(0)"><img src="" name="r0main"></a></td>';
	$page .= '<td width=9></td>';
	$page .= '<td><a href="javascript:Hold(1)"><img src="" name="r1main"></a></td>';
	$page .= '<td width=9></td>';
	$page .= '<td><a href="javascript:Hold(2)"><img src="" name="r2main"></a></td>';
	$page .= '</tr>';

	$page .= '<tr>';
	$page .= '<td><a href="javascript:Hold(0)"><img src="" name="r0btm"></a></td>';
	$page .= '<td width=9></td>';
	$page .= '<td><a href="javascript:Hold(1)"><img src="" name="r1btm"></a></td>';
	$page .= '<td width=9></td>';
	$page .= '<td><a href="javascript:Hold(2)"><img src="" name="r2btm"></a></td>';
	$page .= '</tr>';

	$page .= '<tr>';
	$page .= '<td><center><a href="javascript:Hold(0)"><label id="Hold0">'.t('CASINO_ROLL').'</label></a></center></td>';
	$page .= '<td width=9></td>';
	$page .= '<td><center><a href="javascript:Hold(1)"><label id="Hold1">'.t('CASINO_ROLL').'</label></a></center></td>';
	$page .= '<td width=9></td>';
	$page .= '<td><center><a href="javascript:Hold(2)"><label id="Hold2">'.t('CASINO_ROLL').'</label></a></center></td>';
	$page .= '</tr>';
	
	$page .= '</table>';
	
	$page .= '</div>';

	$page .= '<script language="JavaScript">';
		
	if (($price==0) && ($eid==2)) {		

		$page .= 'moneyStopTimer();';		
		$page .= 'healthStopTimer();';		
		$page .= 'energyStopTimer();';
		$page .= 'ammoStopTimer();';
		
		$page .= 'Init("'.$a00.'","'.$a01.'","'.$a02.'","'.$a10.'","'.$a11.'","'.$a12.'","'.$a20.'","'.$a21.'","'.$a22.'","'.$bet.'","'.$player->request.'",\''.warquest_token('mid='.$mid.'&sid='.$sid.'&cid='.$cid.'&eid=3').'\' );';
		$page .= 'Go();';
		
		$page .= 'document.getElementById("bet").disabled = true;';
		
	} else {

		$page .= 'Init("'.$a00.'","'.$a01.'","'.$a02.'","'.$a10.'","'.$a11.'","'.$a12.'","'.$a20.'","'.$a21.'","'.$a22.'","0","'.$player->request.'",\''.warquest_token('mid='.$mid.'&sid='.$sid.'&cid='.$cid.'&eid=3').'\');';
		$page .= 'Show();';		 
	}

	$page .= '</script>'; 

	$page .= '<div class="note">';
	$page .= t('CASINO_NOTE'.$cid);
	$page .= '</div>';
	
	$page .= warquest_show_ads();
}

/*
** ---------------------------------------------------------------- 
** Wheel Of Fortune
** ----------------------------------------------------------------
*/

function warquest_casino_wheel_do() {
	
	/* input */
	global $bet;
	global $number;
	global $wheel;
	global $key;

	/* output */
	global $eid;
	global $player;
	global $popup;
	
	$message = '';
	
	if ($wheel!=0) {
	
		if ($key != $player->request-1) {
	
			$message= t('SYSTEM_HACK_DETECTED');
			$popup .= warquest_box_icon("warning", $message);
			
		} else {
		
			/* Wheel has rolled */
			if ($wheel == $number) {
	
				$money = $bet * 10;
				$message  = t('CASINO_WIN', $wheel ,money_format1($money,0,",","."));
				$popup .= warquest_box_icon("info", $message);	
				warquest_info($message);
				
				$player->money += $money;
				
				$log = 'Wheel of Fortune won '.number_format2($money);		
				warquest_user_log($player, $log);
		
			} else {
					
				$message  = t('CASINO_LOST', $wheel, money_format1($bet,0,",","."));
				$popup .= warquest_box_icon('warning', $message);
				
				$log = 'Wheel of Fortune lose '.number_format2($bet);		
				warquest_user_log($player, $log);
			}
		}		
		
	} else {
			
		/* New game, check parameters */
		if ($bet==0) {			
			$eid=0;		
			$message .= t('CASINO_NO_BET').'<br/>';			
		}
		
		if ($number==0) {			
			$eid=0;
			$message .= t('CASINO_NO_LUCKY_NUMBER').'<br/>';	
		}
	
		if ($bet>10000000) {	
			$eid=0;
			$message .= t('CASINO_BET_TO_LARGE', money_format1(10000000,0,",",".")).'<br/>';	
		}
	
		if ($bet > $player->money) {	
			$eid=0;	
			$message = t('CASINO_NO_MONEY').'<br/>';
		}
		
		if ($eid==0) {
		
			$popup .= warquest_box_icon("warning", $message);		
			
		} else {
		
			$player->money -= $bet;	
			$player->casino++;
		}	
	}
}

function warquest_lucky_number_selected($default, $option="") {

	$values = array(10, 20, 30, 40, 50, 60, 70, 80, 90 , 100, 150, 200);

	$page ='<select id="number" name="number" '.$option.' >';
	
	foreach ($values as $value) {
	
		$page.='<option value="'.$value.'"';
		
		if ($default == $value) {
			$page .= ' selected="selected" ';
		}
		
		$page .= '>'.$value.'</option>';
	}
	$page.='</select>';
	  
   return $page;
}


/** 
 * Casino general bet form
 */
function warquest_casino_wheel() {

	/* input */
	global $mid;
	global $sid;
	global $cid;
	
	global $eid;
	global $player;
	global $config;
	
	global $angle;
	global $number;
	global $bet;
	global $wheel;
	
	/* output */
	global $page; 
	global $title;
	
	$title = t('CASINO_1');
	
	$page .= '<div class="subparagraph">';	
	$page .= $title;
	$page .= '</div>';
	
	if ($player->lid < $config["casino_unlock_level_1"]) {
	
		$page .= '<br/>';
	
		$message = '<table>';
		$message .= '<tr>';
		$message .= '<td>';
		$message .= warquest_image("other/unlock.png");
		$message .= '</td>';
		$message .= '<td>';
		$message .= t('CASINO_UNLOCK', $title, $config["casino_unlock_level_1"]);
		$message .= '</td>';
		$message .= '</tr>';
		$message .= '</table>';

		$page .= warquest_box("", $message);
	
		return;
	}
	
	$money=0;
		
	$page .= '<div class="box">';
	$page .= '<table>';
	$page .= '<tr>';
	
	$page .= '<td width="160" >';	
	$page .= warquest_casino_image($cid, 140, 100);
	$page .= '</td>';
	
	$page .= "<td>";
	
	$page .= "<table>";	

	$page .= "<tr>";
	$page .= "<td>";
	$page .= t('CASINO_NUMBER').":<br/>";
	
	$page .= warquest_lucky_number_selected($number);
	
	$page .= "</td>";
	$page .= "</tr>";

	$page .= "<tr>";
	$page .= "<td>";
	$page .= t('CASINO_BET').":<br/>";
	$page .= '<input type="text" id="bet" name="bet" size="10" maxlength="7" type="text" value="'.$bet.'"> ';
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&cid='.$cid.'&eid=1', t('CASINO_PLAY'), 'play');
	$page .= "</td>";
	$page .= "</tr>";
	
	$page .= '</table>';
	
	$page .= '</td>';	
	$page .= '</tr>';
	$page .= '</table>';
	
	$page .= '</div>';
	
	$page .= '<div class="box">';
	
	$page .= '<canvas id="canvas" width="500" height="500"></canvas>';
	$page .= '<script language="JavaScript" src="'.$config["content_url"].'js/wheel5.js"></script>';
	
	$page .= '<script language="JavaScript">'; 

	$page .= 'initWheel('.$bet.','.$angle.','.$player->request.',\''.warquest_token('mid='.$mid.'&sid='.$sid.'&cid='.$cid.'&eid=1').'\');';
	$page .= 'drawWheel();';
	
	/* Start the wheel */
	if (($wheel==0) && ($eid==1)) {		
		$page .= 'document.getElementById("number").disabled = true;';
		$page .= 'document.getElementById("bet").disabled = true;';
		$page .= 'spinWheel();';
		$page .= '</script>';
		$page .= '<input type="hidden" name="number" value="'.$number.'" />';
	} else {
		$page .= '</script>';
	}
	$page .= '</div>';	
	
	$page .= '<div class="note">';
	$page .= t('CASINO_NOTE'.$cid);
	$page .= '</div>';
	
	$page .= warquest_show_ads();
}

/*
** ---------------------------------------------------------------- 
** Tic Tac Toe
** ----------------------------------------------------------------
*/

function warquest_casino_tictactoe_result_do() {

	/* input */
	global $sid;
	global $bet;
	global $key;
	global $result;
	global $board;
	
	/* output */
	global $player;
	global $popup;
	global $page;
	
	$page .= '<script language="JavaScript">'; 
	$page .= 'showTicTacToe('.$board.')';
	$page .= '</script>';
			
	if ($key != $player->request-1) {
	
		$message= t('SYSTEM_HACK_DETECTED');
		$popup .= warquest_box_icon("warning", $message);	
		
	} else if ($result==1 ) {
	
		$money = $bet * 2;
		$player->money += $money;
		
		$message = t('CASINO_SLOTMACHINE_WIN', health_format(2), money_format1($money)); 
		$popup .= warquest_box_icon("info", $message);	
		warquest_info($message);
		
		$log = 'TicTacToe won '.number_format2($money);		
		warquest_user_log($player, $log);
	
	} else if ($result==2 ) {
	
		$money = $bet * 1;
		$player->money += $money;
		
		$message = t('CASINO_SLOTMACHINE_WIN', health_format(1), money_format1($money)); 
		$popup .= warquest_box_icon("info", $message);	
		warquest_info($message);
		
		$log = 'TicTacToe won '.number_format2($money);		
		warquest_user_log($player, $log);
		
	} else {
	
		$message = t('CASINO_SLOTMACHINE_LOST', money_format1($bet));
		$popup .= warquest_box_icon("warning", $message);	
		
		$log = 'TicTacToe lost '.number_format2($bet);		
		warquest_user_log($player, $log);
	}
}

function warquest_casino_tictactoe_play_do() {

	/* input */
	global $bet;
	global $player;
	
	/* output */
	global $mid;
	global $sid;
	global $cid;
	global $eid;
	global $page;
	global $popup;
	global $page;
	
	/* New game, check parameters */
	if ($bet==0) {			
		$eid=0;		
		$message = t('CASINO_NO_BET').'<br/>';			
	}
		
	if ($bet>10000000) {	
		$eid=0;
		$message = t('CASINO_BET_TO_LARGE', money_format1(10000000,0,",",".")).'<br/>';	
	}
	
	if ($bet > $player->money) {	
		$eid=0;	
		$message = t('CASINO_NO_MONEY').'<br/>';
	}
		
	if ($eid==0) {
	
		$popup .= warquest_box_icon("warning", $message);		
	
	} else {
		
		$player->money -= $bet;	
		$player->casino++;
		
		$page .= '<script language="JavaScript">'; 
		
		$page .= 'document.getElementById("bet").disabled = true;';	
		$page .= 'document.getElementById("play").disabled = true;';
		
		$page .= 'initTicTacToe('.$bet.','.$player->request.',\''.warquest_token('mid='.$mid.'&sid='.$sid.'&cid='.$cid.'&eid=5').'\');';			
		$page .= '</script>';
	}
}

/** 
 * Casino general bet form
 */
function warquest_casino_tictactoe() {

	/* input */
	global $mid;
	global $sid;
	global $cid;
	
	global $eid;
	global $player;
	global $config;
	
	global $bet;
	global $result;
	global $key;
	
	/* output */
	global $page; 
	global $title;
	
	$title = t('CASINO_3');
	
	$page .= '<div class="subparagraph">';	
	$page .= $title;
	$page .= '</div>';
	
	if ($player->lid < $config["casino_unlock_level_3"]) {
	
		$page .= '<br/>';
	
		$message = '<table>';
		$message .= '<tr>';
		$message .= '<td>';
		$message .= warquest_image("other/unlock.png");
		$message .= '</td>';
		$message .= '<td>';
		$message .= t('CASINO_UNLOCK', $title, $config["casino_unlock_level_3"]);
		$message .= '</td>';
		$message .= '</tr>';
		$message .= '</table>';

		$page .= warquest_box("", $message);
	
		return;
	}
	
	$money=0;
		
	$page .= '<div class="box">';
	$page .= '<table>';
	$page .= '<tr>';
	
	$page .= '<td width="160" >';	
	$page .= warquest_casino_image($cid, 140, 100);
	$page .= '</td>';
	
	$page .= "<td>";
	
	$page .= "<table>";
	
	$page .= "<tr>";

	$page .= "<td>";
	$page .= t('CASINO_BET').":<br/>";
	$page .= '<input type="text" id="bet" name="bet" size="10" maxlength="7" type="text" value="'.$bet.'"> ';
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&cid='.$cid.'&eid=4', t('CASINO_PLAY'), 'play');
	$page .= "</td>";
	$page .= "</tr>";
					
	$page .= '</table>';
	
	$page .= '</td>';	
	$page .= '</tr>';
	$page .= '</table>';
	
	$page .= '</div>';
	
	$page .= '<div class="box">';
	
	$page .= '<script language="JavaScript" src="'.$config["content_url"].'js/tictactoe.js"></script>';
	
	$page .= '<input type="button" id="sqr1" class="tictac" onClick="if( turn == 0 ) { setTicTacToe(1) }">';
	$page .= '<input type="button" id="sqr2" class="tictac" onClick="if( turn == 0 ) { setTicTacToe(2) }">';
	$page .= '<input type="button" id="sqr3" class="tictac" onClick="if( turn == 0 ) { setTicTacToe(3) }">';
	$page .= '<br/>';
	$page .= '<input type="button" id="sqr4" class="tictac" onClick="if( turn == 0 ) { setTicTacToe(4) }">';
	$page .= '<input type="button" id="sqr5" class="tictac" onClick="if( turn == 0 ) { setTicTacToe(5) }">';
	$page .= '<input type="button" id="sqr6" class="tictac" onClick="if( turn == 0 ) { setTicTacToe(6) }">';
	$page .= '<br/>';
	$page .= '<input type="button" id="sqr7" class="tictac" onClick="if( turn == 0 ) { setTicTacToe(7) }">';
	$page .= '<input type="button" id="sqr8" class="tictac" onClick="if( turn == 0 ) { setTicTacToe(8) }">';
	$page .= '<input type="button" id="sqr9" class="tictac" onClick="if( turn == 0 ) { setTicTacToe(9) }">';

	if ($eid!=4) {
		$page .= '<script language="JavaScript">'; 
		$page .= 'disableTicTacToe();';		
		$page .= '</script>';
	}
			
	$page .= '</div>';	
	
	$page .= '<div class="note">';
	$page .= t('CASINO_NOTE'.$cid);
	$page .= '</div>';
	
	$page .= warquest_show_ads();
}

/*
** ----------------------------------------------------------------
** HANDLER
** ----------------------------------------------------------------
*/

/** 
 * Casino handler
 */
function warquest_casino() {

	/* input */
	global $eid;
	global $cid;
		
	/* Event handler */
	switch ($eid ) {
	
		case 1: 	warquest_casino_wheel_do();
					break;
					
		case 2: 	warquest_casino_slotmachine1_do();
					break;	

		case 3: 	warquest_casino_slotmachine2_do();
					break;	
	  				  
		case 4: 	warquest_casino_tictactoe_play_do();
					break;
					
		case 5: 	warquest_casino_tictactoe_result_do();
					break;
					
	}
	
	/* Page handler */
	switch ($cid) {
	
		case 1: 	warquest_casino_wheel();
					break;
					
		case 2:	warquest_casino_slotmachine();	
					break;
							
		case 3:	warquest_casino_tictactoe();	
					break;
					
		case 4:	warquest_casino_slotmachine_help();	
					break;
	}
}

/*
** -------------
** THE END
** -------------
*/

?>