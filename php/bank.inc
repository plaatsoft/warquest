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
** ----------
** ACTIONS
** ----------
*/
	
/**
 * Deposit money on bank.
 */
function warquest_bank_deposit_do() {

   /* input */
	global $player;
	global $sid;
	global $cid;
	global $config;
	
	/* output */
	global $popup;
	
	/* Get posted deposit value */
	$deposit=0;
	if (isset($_POST['deposit']) && $_POST['deposit'] != "") {
		$deposit = $_POST['deposit'];
		$deposit = stripslashes($deposit);
		$deposit = warquest_db_escape($deposit);
		
		/* Remove dots */
		$deposit = str_replace(".", "", $deposit);
	}
	
	$price = $deposit;
		
	if ($price>0) {
	
		if ($player->money >= $price) {
		
			$player->money-=$price;
			$balance=0;
			
			switch ($cid) {
				case 1: 	$player->bank1+=$deposit;
							$balance=$player->bank1;
							$init_bank_deposit = $config["init_bank1_deposit"];
							break;
							
				case 2: 	$player->bank2+=$deposit;
							$balance=$player->bank2;
							$init_bank_deposit = $config["init_bank2_deposit"];
							break;
							
				case 3: 	$player->bank3+=$deposit;
							$balance=$player->bank3;
							$init_bank_deposit = $config["init_bank3_deposit"];
							break;					
			}
			 		
			/* Update transaction log.	*/
			warquest_bank_insert($player->pid, 0, $cid, $deposit, $balance, 1);
			
			$handleFee = (round($deposit * ($init_bank_deposit/100)) * -1);
			$balance=0;
			switch ($cid) {
				case 1: 	$player->bank1 += $handleFee;
							$balance=$player->bank1;
							break;
							
				case 2: 	$player->bank2 += $handleFee;
							$balance=$player->bank2;
							break;
							
				case 3: 	$player->bank3 += $handleFee;
							$balance=$player->bank3;
							break;			
			}
		
			/* Update transaction log. */
			warquest_bank_insert($player->pid, 0, $cid, $handleFee, $balance, 2);
			
			$message = t('BANK_DEPOSIT', money_format1($deposit));
			$popup .= warquest_box_icon("info", $message);
			
			$log = 'Deposit '.number_format2($deposit).' to '.t('BANK_GROUP_'.$cid);		
			warquest_user_log($player, $log);
		
		} else {
	
			$message = t('BANK_DEPOSIT_FAILED', money_format1($price));
			$popup .= warquest_box_icon("warning", $message);
	
		}
	}
}

/**
 * Withdraw money of bank.
 */
function warquest_bank_withdraw_do() {

	/* input */
	global $player;
	global $sid;
	global $cid;
	
	/* output */
	global $popup;
	
	/* Get posted withdraw value */
	$withdraw=0;
	if (isset($_POST['withdraw']) && $_POST['withdraw'] != "") {
		$withdraw = $_POST['withdraw'];
		$withdraw = stripslashes($withdraw);
		$withdraw = warquest_db_escape($withdraw);
		
		/* Remove dots */
		$withdraw = str_replace(".", "", $withdraw);
	}
	
	$balance=0;
	switch ($cid) {
		case 1: $balance=$player->bank1;
				break;
					
		case 2: $balance=$player->bank2;
				break;
					
		case 3: $balance=$player->bank3;
				break;			
	}
	
	if ($withdraw>0) {
	
		if ($balance >= $withdraw) {
	
			/* Calculate new values	*/
			$player->money += $withdraw;
			
			switch ($cid) {
				case 1: 	$player->bank1 -= $withdraw;		
							break;
							
				case 2: 	$player->bank2 -= $withdraw;
							break;
							
				case 3: 	$player->bank3 -= $withdraw;
							break;			
			}
		
			warquest_bank_insert($player->pid, 0, $cid, ($withdraw*-1), ($balance-$withdraw), 0);
				
			$message = t('BANK_WITHDRAW', money_format1($withdraw));
			$popup .= warquest_box_icon("info", $message);
			
			$log = 'Withdraw '.number_format2($withdraw).' for '.t('BANK_GROUP_'.$cid);		
			warquest_user_log($player, $log);
		
		} else {
	
			$message = t('BANK_WITHDRAW_FAILED', money_format1($withdraw));
			$popup .= warquest_box_icon("warning", $message);
		}
	}
}

/*
** ---------------------
** UI
** ---------------------
*/

/**
 * Show bank transaction log
 */
function warquest_bank_log() {
   
	/* input	*/
	global $mid;
	global $sid;
	global $cid;
	global $player;	
	global $config;
	
	/* output */
	global $page;

	/* show bank transactions. */
	$query  = 'select a.id, a.pid1, a.pid2, a.amount, a.action, a.balance, ';
	$query .= 'date_format(a.date , "%d-%m-%Y %H:%i:%s") as date, ';
	$query .= '(select name from player where pid=a.pid2) as name '; 
	$query .= 'from bank a where a.pid1='.$player->pid.' and a.bgid='.$cid.' ';
	$query .= 'order by a.id desc';

	$result = warquest_db_query($query);	
	
	$page .= '<div class="subparagraph">'.t('BANK_TRANSACTION_LOG').'</div>';
	
	$page .= '<div class="box">';
	$page .= '<table>';
	
	$page .= '<tr>';
	$page .= '<td width="100"><b>'.t('GENERAL_AGO').'</b></td>';
	$page .= '<td width="280"><b>'.t('GENERAL_TRANSACTION').'</b></td>';
	$page .= '<td width="90"><b>'.t('GENERAL_BALANCE').'</b></td>';
	$page .= '</tr>';
	
	while ($data=warquest_db_fetch_object($result)) {
	
		$page .= '<tr>';
		$page .= '<td>'.warquest_ui_ago($data->date).'</td>';
		$page .= '<td>';
		
		if ($data->action == 5) {
			$page .= warquest_link('mid='.$mid.'&sid='.PAGE_PROFILE.'&oid='.$data->pid2, $data->name).' ';
			$page .= t('BANK_TRANSACTION_TYPE_'.$data->action);
			$page .= ' '.money_format1($data->amount).' '.t('GENERAL_DOLLAR').'.';
		} else {
			$page .= t('BANK_TRANSACTION_TYPE_'.$data->action);
			$page .= ' '.money_format1($data->amount).' '.t('GENERAL_DOLLAR').'.';
		}
		
		$page .= '</td>';
		$page .= '<td>'.money_format1($data->balance).'</td>';
		$page .= '</tr>';
	}
	
	$page .= '</table>';
	$page .= '</div>';
	
	$page .= warquest_show_ads();
}

/** 
 * Bank form
 */
function warquest_bank_form() {

	/* input */
	global $mid;
	global $sid;
	global $cid;
	global $player;
	global $config;
	
	/* output */
	global $page;
	global $title;
	
	$title = t('BANK_GROUP_'.$cid);
			
	$page .= '<div class="subparagraph">';	
	$page .= t('BANK_GROUP_'.$cid).' '.t('GENERAL_BANK');
	$page .= '</div>';
				
	$balance=0;
	switch ($cid) {
		case 1: $balance=$player->bank1;
				break;
					
		case 2: $balance=$player->bank2;
				break;
					
		case 3: $balance=$player->bank3;
				break;				
	}
			
	$page .= '<div class="box">';			
	
	$page .= '<table>';
	$page .= '<tr>';
	$page .= '<td width="160" >';	
	$page .= warquest_bank_image($cid, 140, 100);
	$page .= '</td>';
	
	$page .= '<td>';
	
	$page .= "<table>";
	
	$page .= "<tr>";
	$page .= "<td>";		
	$page .= t('LINK_BALANCE').":<br/>";
	$page .= '<input id="text" name="balance" size="16" maxlength="16" disabled="disabled" type="text" ';
	$page .= 'value="'.number_format($balance,0,",",".").'">';
	$page .= "</td>";
	
	$page .= "<td>";	
	$page .= "</td>";
	
	$page .= "</tr>";
	
	$page .= "<tr>";
	$page .= "<td>";
	$page .= t('LINK_DEPOSIT').":<br/>";
	$page .= '<input id="text" name="deposit" size="16" maxlength="16" type="text" value="';
	if ($cid<4) {
		$page .= number_format($player->money,0,",",".");
	} else { 
		$page .= '0';
	}
	$page .= '"><br/>';
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&cid='.$cid.'&eid=1', t('LINK_DEPOSIT'), 'deposit-0');
	$page .= "</td>";
	
	$page .= "<td>";
	$page .= t('LINK_WITHDRAW').":<br/>";
	$page .= '<input id="text" name="withdraw" size="16" maxlength="16" type="text" value="'.number_format($balance,0,",",".").'"><br/>';
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&cid='.$cid.'&eid=2', t('LINK_WITHDRAW'), 'withdraw-1');
	$page .= "</td>";
	$page .= "</tr>";
	
	$page .= "</table>";
	
	$page .= '</td>';
	$page .= '</tr>';
	$page .= "</table>";
	
	$page .= '</div>';
	
	switch ($cid) {
		case 1: 	$init_bank_deposit = $config["init_bank1_deposit"];
				   $init_bank_interest = $config["init_bank1_interest"];
					break;
							
		case 2: 	$init_bank_deposit = $config["init_bank2_deposit"];
					$init_bank_interest = $config["init_bank2_interest"];
					break;
							
		case 3: 	$init_bank_deposit = $config["init_bank3_deposit"];
					$init_bank_interest = $config["init_bank3_interest"];
					break;					
	}
					
	$page .= '<div class="note">';
	$page .= t('BANK_NOTE', $init_bank_deposit, $init_bank_interest);
	if (($cid==2) || ($cid==3)) {
		$page .= '<br/>'.t('BANK_WARNING');
	}
	$page .= '</div>';	
}

/*
** -------------
** HANDLER
** -------------
*/

function warquest_bank() {

	/* input */
	global $eid;
	global $cid;	
	
	/* Event handler */
	switch ($eid) {
	
		case 1:	warquest_bank_deposit_do();
					break;
					  
		case 2:	warquest_bank_withdraw_do();
					break;	
	}
		
	/* Page handler */		
	warquest_bank_form();
	warquest_bank_log();
						
	warquest_player();
}

/*
** ---------
** THE END
** ---------
*/

?>