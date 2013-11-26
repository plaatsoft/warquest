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
** UNIT 
** ---------------------------------------------------------------- 
*/

/* 
** -----------
** PARAMETERS
** -----------
*/

if (isset($_POST['amount2']) && $_POST['amount2'] != "") {
	$player->default_amount = $_POST['amount2'];
	$amount = $player->default_amount;
}

/*
** -----------
** ACTIONS
** -----------
*/

/**
 * Deploy unit(s)
 */
function warquest_unit_deploy_do() {

	/* input */
	global $mid;
	global $eid;
	global $sid;
	global $uid;
	global $amount;
	
	/* output */
	global $page; 
	global $player;
	global $popup;
	
	/* Get unit info */
	$query = 'select price, gold, attack, defense, max, upkeep from unit where uid='.$uid;
	$result = warquest_db_query($query);	
 	$unit = warquest_db_fetch_object($result); 

	/* Get amount of units already deployed */
	$query  = "select amount from player_unit where uid=".$uid." and pid=".$player->pid;
	$result = warquest_db_query($query);
	
	$amountOld=0;	
	if ($data=warquest_db_fetch_object($result)) {
		$amountOld=$data->amount;		
	} 
	$totalAmount=$amountOld;
		
	$totalPrice = $unit->price * $amount;
	$totalGold = $unit->gold * $amount;
	
	if (($unit->max!=0) && (($amountOld+$amount) > $unit->max)) {
	
		$message = '<table>';
		$message .= '<tr>';
		$message .= '<td width="100">';
		$message .= warquest_unit_image($uid, 0, 0);
		$message .= '</td>';
		$message .= '<td>';
		$message .= t('UNIT_MAX', number_format2($unit->max), t('UNIT_'.$uid));
		$message .= '</td>';
		$message .= '</tr>';
		$message .= '</table>';
		
		$type = "warning";
				
	} else if ( (($totalPrice>0) && ($player->money < $totalPrice)) || (($totalGold>0) && ($player->gold < $totalGold)) ) {
		
		$message = '<table>';
		$message .= '<tr>';
		$message .= '<td width="100">';
		$message .= warquest_unit_image($uid, 0, 0);
		$message .= '</td>';
		$message .= '<td>';
		if ($totalPrice>0) {
			$message .= t('UNIT_NO_FUNDS', number_format2($amount), t('UNIT_'.$uid), dollar_format($totalPrice));
		} else {
			$message .= t('UNIT_NO_FUNDS', number_format2($amount), t('UNIT_'.$uid), gold_format($totalGold));
		}
		$message .= '</td>';
		$message .= '</tr>';
		$message .= '</table>';
		
		$type = "warning";
	
	} else if ($player->money_step < ($unit->upkeep * $amount)) {
	
		$message = '<table>';
		$message .= '<tr>';
		$message .= '<td width="100">';
		$message .= warquest_unit_image($uid, 0, 0);
		$message .= '</td>';
		$message .= '<td>';
		$message .= t('UNIT_NO_UPKEEP',number_format2($amount), t('UNIT_'.$uid));
		$message .= '</td>';
		$message .= '</tr>';
		$message .= '</table>';
	
		$type = "warning";
		
	} else {
	
		/* Buy unit(s) */
		
		/* Process player statistics. */
		$player->money -= $totalPrice;
		$player->gold -= $totalGold;
				
		/* save data in database */
		$totalAmount = warquest_db_unit_add($player->pid, $uid, $amount);
		
	 	/* Update income, attack and defense value */
		warquest_netto_income($player);
		
		$message = '<table>';
		$message .= '<tr>';
		
		$message .= '<td width="100">';
		$message .= warquest_unit_image($uid, 0, 0);
		$message .= '</td>';
		
		$message .= '<td>';
		if ($totalPrice>0) {
			$message .= t('UNIT_DEPLOY', number_format2($amount), t('UNIT_'.$uid), dollar_format($totalPrice), deploy_format($totalAmount));
		} else {
			$message .= t('UNIT_DEPLOY', number_format2($amount), t('UNIT_'.$uid), gold_format($totalGold), deploy_format($totalAmount));
		}
		$message .= '</td>';
		
		$message .= '</tr>';
		$message .= '</table>';
		
		$type = "info";		
		
		if ($totalPrice>0) {
			$log = 'Deploy '.number_format2($amount).' '.t('UNIT_'.$uid).' ['.$uid.'] for '.dollar_format($totalPrice);		
		} else {
			$log = 'Deploy '.number_format2($amount).' '.t('UNIT_'.$uid).' ['.$uid.'] for '.gold_format($totalGold);		
		}
		warquest_user_log($player, $log);
	}
	
	$link="";
	$amountDiff = $unit->max - $totalAmount;
	if ($amountDiff>0) {
		$link  = warquest_link('mid='.$mid.'&uid='.$uid.'&eid='.$eid.'&sid='.$sid, t('LINK_DEPLOY_AGAIN'), 'deploy-0');
		$link .= '<br/><br/>'.t('GENERAL_AMOUNT').'<br/>';
		$link .= warquest_amount_selected($amountDiff);
	}
		
	$popup .= warquest_box($type, $message, $link);
}

/** 
 * Disband unit(s)
 */
function warquest_unit_disband_do() {

	/* input */
	global $mid;
	global $sid;
	global $eid;
	global $uid;
	global $amount;
	global $config;
	
	/* output */
	global $page;
	global $player;
	global $popup;
	
	/* Get unit  */
	$query  = "select price, gold, attack, defense, upkeep from unit where uid=".$uid;
	$result = warquest_db_query($query);
	
 	$unit=warquest_db_fetch_object($result);
			
	/* Unit amount of player */
	$query  = "select amount from player_unit where pid=".$player->pid." and uid=".$uid;
	$result = warquest_db_query($query);
	
	$totalAmount=0;
	if ($data=warquest_db_fetch_object($result)) {
		$totalAmount=$data->amount;
	}
	
	/* Check amount does not get negative */
	if ($amount > $totalAmount) {
		
		$message = '<table>';
		$message .= '<tr>';
		$message .= '<td width="100">';
		$message .= warquest_unit_image($uid, 0, 0);
		$message .= '</td>';
		$message .= '<td>';
		$message .= t('UNIT_DISBAND_FAILED', number_format2($amount), t('UNIT_'.$uid), $totalAmount);
		$message .= '</td>';
		$message .= '</tr>';
		$message .= '</table>';
		
		$type = "warning";
			
	} else {
		
		/* Increase money (60% of deploy price) of player */
		$totalPrice =  round($unit->price * $amount * $config["unit_sell_ratio"] );
		$totalGold =  round($unit->gold * $amount * $config["unit_sell_ratio"] );
		$player->money += $totalPrice;
		$player->gold += $totalGold;
	
		$totalAmount -= $amount;
		
		/* Delete amount out database */
		warquest_db_unit_delete($player->pid, $uid, $amount);
			
		/* Update income, attack and defense value */
		warquest_netto_income($player);
	
		$message = '<table>';
		$message .= '<tr>';
		
		$message .= '<td width="100">';
		$message .= warquest_unit_image($uid, 0, 0);
		$message .= '</td>';
		
		$message .= '<td>';
		if ($totalPrice  > 0) {
			$message .= t('UNIT_DISBAND',	number_format2($amount), t('UNIT_'.$uid), dollar_format($totalPrice), deploy_format($totalAmount));
		} else {
			$message .= t('UNIT_DISBAND',	number_format2($amount), t('UNIT_'.$uid), gold_format($totalGold), deploy_format($totalAmount));
		}
		$message .= '</td>';
		
		$message .= '</tr>';
		$message .= '</table>';	
		
		$type= "info";		
		
		if ($totalPrice  > 0) {
			$log = 'Disband '.number_format2($amount).' '.t('UNIT_'.$uid).' ['.$uid.'] for '.dollar_format($totalPrice);		
		} else {
			$log = 'Disband '.number_format2($amount).' '.t('UNIT_'.$uid).' ['.$uid.'] for '.gold_format($totalGold);	
		}
		warquest_user_log($player, $log);
	}
	
	$link = "";
	if ($totalAmount>0) {
		$link  = warquest_link('mid='.$mid.'&uid='.$uid.'&eid='.$eid.'&sid='.$sid, t('LINK_DISBAND_AGAIN'), 'disband-0');
		$link .= '<br/><br/>'.t('GENERAL_AMOUNT').'<br/>';
		$link .= warquest_amount_selected($totalAmount);
	}
				
	$popup .= warquest_box($type, $message, $link);
}

/*
** -----------
** UI
** -----------
*/

/** 
 * Unit form
 */
function warquest_unit_form() {

	/* input */
	global $mid;
	global $sid;
	global $uid;
	
	global $player;
	global $amount;
	global $config;
	
	/* output */
	global $page; 
	global $title;
	
	$title = t('UNIT_GROUP_'.$sid);
	
	/* Get player unit data */
	$query  = "select uid from unit where ugid=".$sid." and lid<=".$player->lid;
	$result = warquest_db_query($query); 
	$count = warquest_db_num_rows($result);
	$ads_pos = rand(1,$count);
	
	/* Get player unit data */
	$query  = "select a.uid, a.price, a.gold, a.attack, a.defense, a.upkeep, a.max, a.ugid, ";
	$query .= "IFNULL(b.amount, 0) as amount from unit a left join player_unit b ";
	$query .= "ON a.uid=b.uid and b.pid=".$player->pid." where a.ugid=".$sid." and a.lid<=".$player->lid.' ';  
	$query .= 'order by a.lid';
	$result = warquest_db_query($query);  
	
	if ($uid==0) {
		$page .= warquest_amount_radiobox();
	}
	$page .= '<div class="box">';
	$page .= '<table>';
		
	/* Show unlocked units */
	$count = 0;
	
	while ($data=warquest_db_fetch_object($result)) {
	
		$count++;
		
		$page .= '<tr>';	
	
		$page .= '<td width="100">'; 
		$page .= warquest_unit_image($data->uid, 0, 0);
		$page .= '</td>';
		
		$page .= '<td width="210">';
		$page .= '<b>'.t('UNIT_'.$data->uid).'</b>';
			
		if (warquest_library($data->uid,0)==1) {
			$page .= '&nbsp;'.warquest_link('mid='.$mid.'&sid='.PAGE_LIBRARY.'&uid='.$data->uid, 
				warquest_image('other/info.png','width="16" height="16"'),'info'.$count);
		}
		$page .= '<br/>';
		if ($data->attack > 0) {
			$page .= $data->attack.' '.t('GENERAL_ATTACK').' - ';
		}
		if ($data->defense > 0) {
			$page .= $data->defense.' '.t('GENERAL_DEFENSE');
		}		
		if ($data->upkeep > 0) {
			$page .= '<br/>'.t('GENERAL_UPKEEP').': +'.money_format1($data->upkeep);
		}		
		$page .= '</td>';
		
		$page .= '<td width="80">';
		if ($data->price>0) {
			$page .= money_format2($data->price).'<br/>';
		} else {
			$page .= gold_format($data->gold).'<br/>';
		}
		$page .= warquest_link('eid=1&mid='.$mid.'&uid='.$data->uid.'&sid='.$sid, t('LINK_DEPLOY'),'deploy-'.($count+100));
		$page .= '</td>';
		
		$page .= '<td width="110">'.t('GENERAL_DEPLOYED').': '.deploy_format($data->amount).'<br/>';
		$page .= warquest_link('eid=2&mid='.$mid.'&uid='.$data->uid.'&sid='.$sid, t('LINK_DISBAND'),'disband-'.$count);

		$page .= '</td>';
		
		$page .= '</tr>';
		
		if ($count==$ads_pos) {		
			$begin = '<tr><td colspan="4"><br/>';
			$end = '<br/></td></tr>';	
			$page .= warquest_show_ads($begin, $end);				
		}
	}
	
	/* Show first locked unit  */
	$query  = 'select uid, lid, attack, defense, upkeep from unit where ugid='.$sid;
	$query .= ' and lid>'.$player->lid.' order by lid limit 0,1';
	$result = warquest_db_query($query);
	
	if ($data=warquest_db_fetch_object($result)) {
	
		$count++;
	
		$page .= '<tr>';	
		
		$page .= '<td>'; 
		$page .= warquest_image("other/unlock.png");
		$page .= '</td>'; 
		
		$page .= '<td>'; 
		$page .= '<b>'.t('UNIT_'.$data->uid).'</b><br/>';
		if ($data->attack > 0) {
			$page .= $data->attack.' '.t('GENERAL_ATTACK').' - ';
		}
		if ($data->defense > 0) {
			$page .= $data->defense.' '.t('GENERAL_DEFENSE');
		}
		if ($data->upkeep > 0) {
			$page .= '<br/>'.t('GENERAL_UPKEEP').': +'.money_format1($data->upkeep);
		}
		$page .= '</td>'; 
	
		$page .= '<td colspan="2" width="200" align="right">'; 
		$page .= t('GENERAL_UNLOCK', $data->lid);
		$page .= '</td>';
	
		$page .= '</tr>';
	}
		
	$page .= '</table>';
	$page .= '</div>'; 
	
	if ($count==0) {
	
		$message = t('UNITS_NO_UNITS');
		$page .= warquest_box_icon('info', $message);
			
	}
		
	$page .= '<div class="note">';
	$page .= t('UNIT_NOTE_'.$sid);
	$page .= '</div>';	
}

/*
** --------------
** HANDLER
** --------------
*/

function warquest_unit() {

	/* input */
	global $eid;
	global $sid;
	global $uid;
	global $sequence;
	global $player;
	
		/* output */
	global $page;
	
	/*if ($sequence != $player->request) {
	
		$message = t('SYSTEM_HACK_DETECTED');
		$page .= warquest_box_icon("warning", $message);	
		return;
	}*/
	
	/* Event handler */
	switch ($eid) {

		case 1: warquest_unit_deploy_do();
				  break;

	   case 2: warquest_unit_disband_do();
				  break;
				  
		case 500: warquest_switch_planet_do();
					 break;		
	}
		
	/* Page handler */
	switch ($sid) {
	
		default: warquest_unit_form();
					break;

					
		case PAGE_LIBRARY: 
					warquest_library($uid, 1);
					break;
					
	}
}

/*
** ---------------------------------------------------------------- 
** THE END
** ----------------------------------------------------------------
*/

?>