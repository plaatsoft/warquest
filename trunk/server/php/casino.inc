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
**  All copyrights reserved (c) 2008-2014 PlaatSoft
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

$a00 = warquest_post('a00', 'appletop.src');	
$a01 = warquest_post('a01', 'banana.src');	
$a02 = warquest_post('a02', 'pearbtm.src');	
$a10 = warquest_post('a10', 'peartop.src');
$a11 = warquest_post('a11', 'bar.src');
$a12 = warquest_post('a12', 'orangebtm.src');
$a20 = warquest_post('a20', 'bananatop.src');
$a21 = warquest_post('a21', 'orange.src');
$a22 = warquest_post('a22', 'grapebtm.src');

/*
** ---------------------------------------------------------------- 
** Wheel Of Fortune
** ----------------------------------------------------------------
*/

function warquest_casino_wheel_result_do() {
	
	/* input */
	global $bet;
	global $number;
	global $wheel;
	global $key;

	/* output */
	global $eid;
	global $player;
	global $output;
	
	$message = '';
	
	if ($key != $player->request-1) {
	
		$message= t('SYSTEM_HACK_DETECTED');
		$output->popup .= warquest_box_icon("warning", $message);
			
	} else if ($wheel == $number) {
		
		/* Wheel has rolled */	
		$money = $bet * 10;
		$message  = t('CASINO_WIN', $wheel ,money_format1($money,0,",","."));
		$output->popup .= warquest_box_icon("info", $message);	
		warquest_info($message);
				
		$player->money += $money;
				
		$log = 'Wheel of Fortune won '.number_format2($money);		
		warquest_user_log($player, $log);
		
		warquest_sound("won.mp3");
		
	} else {
					
		$message  = t('CASINO_LOST', $wheel, money_format1($bet,0,",","."));
		$output->popup .= warquest_box_icon('warning', $message);
			
		$log = 'Wheel of Fortune lose '.number_format2($bet);		
		warquest_user_log($player, $log);	
		
		warquest_sound("lost.mp3");
	}		
}


function warquest_casino_wheel_play_do() {
			
	/* input */
	global $bet;
	global $number;

	/* output */
	global $eid;
	global $player;
	global $output;
	
	/* New game, check parameters */
	if ($bet==0) {			
		
		$eid=EVENT_NONE;
		
		$message = t('CASINO_NO_BET');
		$output->popup .= warquest_box_icon("warning", $message);		
		
	} else if ($number==0) {			
	
		$eid=EVENT_NONE;
		
		$message = t('CASINO_NO_LUCKY_NUMBER');	
		$output->popup .= warquest_box_icon("warning", $message);		
	
	} else if ($bet>10000000) {	
		
		$eid=EVENT_NONE;
		
		$message = t('CASINO_BET_TO_LARGE', money_format1(10000000,0,",","."));	
		$output->popup .= warquest_box_icon("warning", $message);		
	
	} else if ($bet > $player->money) {	
		
		$eid=EVENT_NONE;	
		
		$message = t('CASINO_NO_MONEY');
		$output->popup .= warquest_box_icon("warning", $message);		
	
	} else {
		
		$player->money -= $bet;	
		$player->casino++;
		
		warquest_sound("start.mp3");
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
	global $ssid;
	
	global $eid;
	global $player;
	global $config;
	
	global $angle;
	global $number;
	global $bet;
	global $wheel;
	
	/* output */
	global $page; 
	global $output;
	
	$output->title = t('CASINO_1');
	
	$page .= '<div class="subparagraph">';	
	$page .= $output->title;
	$page .= '</div>';
	
	if ($player->lid < $config["casino_unlock_level_1"]) {
	
		$page .= '<br/>';
	
		$message = '<table>';
		$message .= '<tr>';
		$message .= '<td>';
		$message .= warquest_image("other/unlock.png");
		$message .= '</td>';
		$message .= '<td>';
		$message .= t('CASINO_UNLOCK', $output->title, $config["casino_unlock_level_1"]);
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
	$page .= warquest_casino_image($ssid, 140, 100);
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
	$page .= '<input type="text" id="bet" name="bet" size="10" maxlength="7" type="text" value="'.$bet.'" onkeydown="if (event.keyCode == 13) return false" > ';
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&ssid='.$ssid.'&eid='.EVENT_CASINO_WHEEL_PLAY, t('CASINO_PLAY'), 'play');
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

	$page .= 'initWheel('.$bet.','.$angle.','.$player->request.',\''.warquest_token('mid='.$mid.'&sid='.$sid.'&ssid='.$ssid.'&eid='.EVENT_CASINO_WHEEL_RESULT).'\');';
	$page .= 'drawWheel();';
	
	/* Start the wheel */
	if (($wheel==0) && ($eid==EVENT_CASINO_WHEEL_PLAY)) {		
		$page .= 'document.getElementById("number").disabled = true;';
		$page .= 'document.getElementById("bet").disabled = true;';
		$page .= 'spinWheel();';
		$page .= '</script>';
		$page .= '<input type="hidden" name="number" value="'.$number.'" />';
		$page .= '<input type="hidden" name="bet" value="'.$bet.'" />';
	} else {
		$page .= '</script>';
	}
	$page .= '</div>';	
	
	$page .= '<div class="note">';
	$page .= t('CASINO_NOTE'.$ssid);
	$page .= '</div>';
}


/*
** ---------------------------------------------------------------- 
** Slot Machine
** ----------------------------------------------------------------
*/

function warquest_casino_slotmachine_result_do() {

	/* input */
	global $sid;
	global $bet;
	global $key;
	global $price;
	
	/* output */
	global $player;
	global $output;

	if ($key != $player->request-1) {
	
		$message= t('SYSTEM_HACK_DETECTED');
		$output->popup .= warquest_box_icon("warning", $message);	
		
	} else if (($price>0) && ($price<76)) {
	
		$money = $bet * $price;
		$player->money += $money;
		
		$message = t('CASINO_SLOTMACHINE_WIN', health_format($price), money_format1($money)); 
		$output->popup .= warquest_box_icon("info", $message);	
		warquest_info($message);
		
		$log = 'Slot Machine won '.number_format2($money);		
		warquest_user_log($player, $log);
		
		warquest_sound("won.mp3");
	
	} else {
	
		$message = t('CASINO_SLOTMACHINE_LOST', money_format1($bet));
		$output->popup .= warquest_box_icon("warning", $message);	
		
		$log = 'Slot Machine lose '.number_format2($bet);		
		warquest_user_log($player, $log);
		
		warquest_sound("lost.mp3");
	}
}

function warquest_casino_slotmachine_play_do() {
	
	/* input */
	global $sid;
	global $bet;

	/* output */
	global $eid;
	global $player;
	global $output;
		
	/* New game, check parameters */
	if ($bet==0) {			
	
		$eid=EVENT_NONE;
		
		$message = t('CASINO_NO_BET');			
		$output->popup .= warquest_box_icon("warning", $message);		
		
	} else if ($bet>10000000) {	
	
		$eid=EVENT_NONE;
		
		$message = t('CASINO_BET_TO_LARGE', number_format(10000000,0,",","."));	
		$output->popup .= warquest_box_icon("warning", $message);		
		
	} else if ($bet > $player->money) {	
		
		$eid=EVENT_NONE;	
		
		$message = t('CASINO_NO_MONEY').'<br/>';
		$output->popup .= warquest_box_icon("warning", $message);		
		
	} else {
		
		$player->money -= $bet;				
		$player->casino++;
			
		warquest_sound("start.mp3");
	}		
}

function warquest_casino_slotmachine_help() {

	/* output */
	global $page;
	global $output;
	
	$output->title = t('CASINO_2');
	
	$page .= '<div class="subparagraph">';	
	$page .= $output->title;
	$page .= '</div>';
		
	$page .= '<div class="box">';
	
	$page .= t('CASINO_SLOTMACHINE_HELP');
		
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
	global $ssid;
	
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
	global $output; 

	$output->title = t('CASINO_2');
	
	$page .= '<div class="subparagraph">';	
	$page .= $output->title;
	$page .= '</div>';

			
	if ($player->lid < $config["casino_unlock_level_2"]) {
	
		$page .= '<br/>';
	
		$message = '<table>';
		$message .= '<tr>';
		$message .= '<td>';
		$message .= warquest_image("other/unlock.png");
		$message .= '</td>';
		$message .= '<td>';
		$message .= t('CASINO_UNLOCK', $output->title, $config["casino_unlock_level_2"]);
		$message .= '</td>';
		$message .= '</tr>';
		$message .= '</table>';

		$page .= warquest_box("", $message);
	
		return;
	}
		
	$money=0;
		
	$page .= '<script language="JavaScript" src="'.$config["content_url"].'js/slotmachine.js"></script>';
		
	$page .= '<div class="box">';
	$page .= '<table>';
	$page .= '<tr>';
	
	$page .= '<td width="160" >';	
	$page .= warquest_casino_image($ssid, 140, 100);
	$page .= '</td>';
	
	$page .= "<td>";
	
	$page .= "<table>";
			
	$page .= "<tr>";
	$page .= "<td>";
	$page .= t('CASINO_BET').":<br/>";
	$page .= '<input id="bet" name="bet" size="10" maxlength="7" type="text" value="'.$bet.'" onkeydown="if (event.keyCode == 13) return false" /> ';
	if ($eid!=EVENT_CASINO_SLOT_PLAY) {
		$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&ssid='.$ssid.'&eid='.EVENT_CASINO_SLOT_PLAY, t('CASINO_PLAY'), 'play');
	} else {
		$page .= '<a href="javascript:Go()">'.t('CASINO_PLAY').'</a>';
	}
	$page .= "</td>";
	$page .= "</tr>";
	
	$page .= "<tr>";
	$page .= '<td>';	
	$page .= '<br/>';	
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&ssid=4', t('LINK_HELP'), 'help4');
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
		
	if (($price==0) && ($eid==EVENT_CASINO_SLOT_PLAY)) {		

		$page .= 'moneyStopTimer();';		
		$page .= 'healthStopTimer();';		
		$page .= 'energyStopTimer();';
		$page .= 'ammoStopTimer();';
		
		$page .= 'Init("'.$a00.'","'.$a01.'","'.$a02.'","'.$a10.'","'.$a11.'","'.$a12.'","'.$a20.'","'.$a21.'","'.$a22.'","'.$bet.'","'.$player->request.'",\''.warquest_token('mid='.$mid.'&sid='.$sid.'&ssid='.$ssid.'&eid='.EVENT_CASINO_SLOT_RESULT).'\' );';
		$page .= 'Go();';
		
		$page .= 'document.getElementById("bet").disabled = true;';
		
	} else {

		$page .= 'Init("'.$a00.'","'.$a01.'","'.$a02.'","'.$a10.'","'.$a11.'","'.$a12.'","'.$a20.'","'.$a21.'","'.$a22.'","0","'.$player->request.'",\''.warquest_token('mid='.$mid.'&sid='.$sid.'&ssid='.$ssid.'&eid='.EVENT_CASINO_SLOT_RESULT).'\');';
		$page .= 'Show();';		 
	}

	$page .= '</script>'; 

	$page .= '<div class="note">';
	$page .= t('CASINO_NOTE'.$ssid);
	$page .= '</div>';
}

/*
** ---------------------------------------------------------------- 
** Tic Tac Toe
** ----------------------------------------------------------------
*/

function warquest_casino_tictactoe_result_do() {

	/* input */
	global $bet;
	global $key;
	global $result;
	
	/* output */
	global $player;
	global $output;
	
	if ($key != $player->request-1) {
	
		$message = t('SYSTEM_HACK_DETECTED');
		$output->popup .= warquest_box_icon("warning", $message);	
		
	} else if ($result==1 ) {
	
		$money = $bet * 2;
		$player->money += $money;
				
		$message = t('CASINO_TICTACTOE_WIN', health_format(2), money_format1($money)); 
		$output->popup .= warquest_box_icon("info", $message);	
		warquest_info($message);
		
		$log = 'TicTacToe won '.number_format2($money);		
		warquest_user_log($player, $log);
		
		warquest_sound("won.mp3");		
	
	} else if ($result==2 ) {
	
		$money = $bet * 1;
		$player->money += $money;
				
		$message  = t('CASINO_TICTACTOE_DRAW', health_format(1), money_format1($money)); 		
		$output->popup .= warquest_box_icon("info", $message);	
		warquest_info($message);
		
		$log = 'TicTacToe draw '.number_format2($money);		
		warquest_user_log($player, $log);
		
		warquest_sound("won.mp3");
		
	} else {
	
		$message  = t('CASINO_TICTACTOE_LOST', money_format1($bet));
		$output->popup .= warquest_box_icon("warning", $message);	
		
		$log = 'TicTacToe lost '.number_format2($bet);		
		warquest_user_log($player, $log);
		
		warquest_sound("lost.mp3");
	}
}

function warquest_casino_tictactoe_play_do() {

	/* input */
	global $bet;
	global $mid;
	global $sid;
	global $ssid;
	global $player;
	
	/* output */
	global $page;
	global $output;
	global $eid;

	if ($bet==0) {			

		$eid=EVENT_NONE;	
		$message = t('CASINO_NO_BET').'<br/>';			
		$output->popup .= warquest_box_icon("warning", $message);		
		
	} else if ($bet>10000000) {	

		$eid=EVENT_NONE;		
		$message = t('CASINO_BET_TO_LARGE', money_format1(10000000,0,",",".")).'<br/>';	
		$output->popup .= warquest_box_icon("warning", $message);		
		
	} else if ($bet > $player->money) {	
	
		$eid=EVENT_NONE;	
		$message = t('CASINO_NO_MONEY').'<br/>';
		$output->popup .= warquest_box_icon("warning", $message);		
		
	} else {

		$player->money -= $bet;	
		$player->casino++;
		
		warquest_sound("start.mp3");
		
		$page .= '<script language="JavaScript">'; 
		$page .= 'initTicTacToe('.$bet.','.$player->request.',\''.warquest_token('mid='.$mid.'&sid='.$sid.'&ssid='.$ssid.'&eid='.EVENT_CASINO_TIC_RESULT).'\');';					
		$page .= '</script>';
	}
}

/** 
 * Casino TicTacToe form
 */
function warquest_casino_tictactoe() {

	/* input */
	global $mid;
	global $sid;
	global $ssid;
	
	global $eid;
	global $player;
	global $config;
	
	global $bet;
	global $result;
	global $key;
	global $board;
	
	/* output */
	global $page; 
	global $output;
	
	$output->title = t('CASINO_3');
	
	$page .= '<div class="subparagraph">';	
	$page .= $output->title;
	$page .= '</div>';
	
	if ($player->lid < $config["casino_unlock_level_3"]) {
	
		$page .= '<br/>';
	
		$message = '<table>';
		$message .= '<tr>';
		$message .= '<td>';
		$message .= warquest_image("other/unlock.png");
		$message .= '</td>';
		$message .= '<td>';
		$message .= t('CASINO_UNLOCK', $output->title, $config["casino_unlock_level_3"]);
		$message .= '</td>';
		$message .= '</tr>';
		$message .= '</table>';

		$page .= warquest_box("", $message);
	
		return;
	}
	
	$money = 0;
		
	$page .= '<div class="box">';
	$page .= '<table>';
	$page .= '<tr>';
	
	$page .= '<td width="160" >';	
	$page .= warquest_casino_image($ssid, 140, 100);
	$page .= '</td>';
	
	$page .= "<td>";
	
	$page .= "<table>";
	
	$page .= "<tr>";

	$page .= "<td>";
	$page .= t('CASINO_BET').":<br/>";
	$page .= '<input type="text" id="bet" name="bet" size="10" maxlength="7" type="text" onkeydown="if (event.keyCode == 13) return false" value="'.$bet.'"> ';
		
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&ssid='.$ssid.'&eid='.EVENT_CASINO_TIC_PLAY, t('CASINO_PLAY'), 'play');
		
	$page .= "</td>";
	$page .= "</tr>";
					
	$page .= '</table>';
	
	$page .= '</td>';	
	$page .= '</tr>';
	$page .= '</table>';
	
	$page .= '</div>';
		
	$page .= '<div class="box">';
	
	$page .= '<br/>';
	$page .= '<center>';
	$page .= '<input type="button" id="sqr1" class="tictac" onClick="setTicTacToe(1)">';
	$page .= '<input type="button" id="sqr2" class="tictac" onClick="setTicTacToe(2)">';
	$page .= '<input type="button" id="sqr3" class="tictac" onClick="setTicTacToe(3)">';
	$page .= '<br/>';
	$page .= '<input type="button" id="sqr4" class="tictac" onClick="setTicTacToe(4)">';
	$page .= '<input type="button" id="sqr5" class="tictac" onClick="setTicTacToe(5)">';
	$page .= '<input type="button" id="sqr6" class="tictac" onClick="setTicTacToe(6)">';
	$page .= '<br/>';
	$page .= '<input type="button" id="sqr7" class="tictac" onClick="setTicTacToe(7)">';
	$page .= '<input type="button" id="sqr8" class="tictac" onClick="setTicTacToe(8)">';
	$page .= '<input type="button" id="sqr9" class="tictac" onClick="setTicTacToe(9)">';
	$page .= '</center>';
	$page .= '<br/>';

	if ($eid!=EVENT_CASINO_TIC_PLAY) {
		$page .= '<script language="JavaScript">'; 
		$page .= 'disableTicTacToe();';		
		$page .= '</script>';
	}

	if ($eid==EVENT_CASINO_TIC_RESULT) {
		$page .= '<script language="JavaScript">'; 
		$page .= 'showTicTacToe(\''.$board.'\')';
		$page .= '</script>';
	}
				
	$page .= '</div>';	
	
	$page .= '<div class="note">';
	$page .= t('CASINO_NOTE'.$ssid);
	$page .= '</div>';
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
	global $ssid;

	/* Event handler */
	switch ($eid ) {
	
		case EVENT_CASINO_WHEEL_PLAY: 	
					warquest_casino_wheel_play_do();
					break;
					
		case EVENT_CASINO_WHEEL_RESULT: 	
					warquest_casino_wheel_result_do();
					break;					
					
		case EVENT_CASINO_SLOT_PLAY: 	
					warquest_casino_slotmachine_play_do();
					break;	

		case EVENT_CASINO_SLOT_RESULT: 	
					warquest_casino_slotmachine_result_do();
					break;	
	  				  				
		case EVENT_CASINO_TIC_PLAY: 	
					warquest_casino_tictactoe_play_do();
					break;
					
		case EVENT_CASINO_TIC_RESULT: 	
					warquest_casino_tictactoe_result_do();
					break;
	}
	
	/* Page handler */
	switch ($ssid) {
	
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