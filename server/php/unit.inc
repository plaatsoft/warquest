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
	global $output;
	
	/* Get unit info */
	$query = 'select uid, price, gold, attack, defense, max, upkeep from unit where uid='.$uid;
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
		$message .= warquest_unit_image($unit, 0, 0);
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
		$message .= warquest_unit_image($unit, 0, 0);
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
		$message .= warquest_unit_image($unit, 0, 0);
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
		
		/* Update Statistics */
		warquest_gold_use($totalGold);
						
		/* save data in database */
		$totalAmount = warquest_db_unit_add($player->pid, $uid, $amount);
		
	 	/* Update income, attack and defense value */
		warquest_netto_income($player);
		
		$message = '<table>';
		$message .= '<tr>';
		
		$message .= '<td width="100">';
		$message .= warquest_unit_image($unit, 0, 0);
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
		
	$output->popup .= warquest_box($type, $message, $link);
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
	global $output;
	
	/* Get unit  */
	$query  = "select uid, price, gold, attack, defense, upkeep from unit where uid=".$uid;
	$result = warquest_db_query($query);	
 	$unit = warquest_db_fetch_object($result);
			
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
		$message .= warquest_unit_image($unit, 0, 0);
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
		
		warquest_db_unit_delete($player->pid, $uid, $amount);
			
		/* Update income, attack and defense value */
		warquest_netto_income($player);
	
		$message = '<table>';
		$message .= '<tr>';
		
		$message .= '<td width="100">';
		$message .= warquest_unit_image($unit, 0, 0);
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
				
	$output->popup .= warquest_box($type, $message, $link);
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
	global $output;
	
	$output->title = t('UNIT_GROUP_'.$sid);
		
	/* Get player unit data */
	$query1  = "select a.uid, a.price, a.gold, a.attack, a.defense, a.upkeep, a.max, a.ugid, ";
	$query1 .= "IFNULL(b.amount, 0) as amount from unit a left join player_unit b ";
	$query1 .= "ON a.uid=b.uid and b.pid=".$player->pid." where a.ugid=".$sid." and a.lid<=".$player->lid.' ';  
	$query1 .= 'order by a.lid';
	
	$result1 = warquest_db_query($query1);  
	$count1 = warquest_db_num_rows($result1);
	
	/* Get first locked unit */
	$query2  = 'select uid, lid, attack, defense, upkeep from unit where ugid='.$sid;
	$query2 .= ' and lid>'.$player->lid.' order by lid limit 0,1';
	
	$result2 = warquest_db_query($query2);
	$count2 = warquest_db_num_rows($result2);
	
	if ($uid==0) {
		$page .= warquest_amount_radiobox();
	}
	
	if (($count1==0) && ($count2==0)) {
	
		$message = t('UNITS_NO_UNITS');
		$page .= warquest_box_icon('info', $message);
			
	} else {
	
		$page .= '<div class="box rows">';
		$page .= '<table>';
				
		$count = 0;
	
		/* Show player units */	
		while ($data1=warquest_db_fetch_object($result1)) {
	
			$count++;
		
			$page .= '<tr>';	
	
			$page .= '<td width="100">'; 
			$page .= warquest_unit_image($data1, 0, 0);
			$page .= '</td>';
			
			$page .= '<td width="210">';
			$page .= '<span class="subparagraph">'.t('UNIT_'.$data1->uid).'</span>';			
			if (warquest_library($data1->uid,0)==1) {
				$page .= ' ';
				$page .= warquest_link('mid='.$mid.'&sid='.PAGE_LIBRARY.'&uid='.$data1->uid, warquest_image('other/info.png','width="16" height="16"'),'info'.$count);
			}
			$page .= '<br/>';
			if ($data1->attack > 0) {
				$page .= strength_format($data1->attack).' '.t('GENERAL_ATTACK').' - ';
			}
			if ($data1->defense > 0) {
				$page .= strength_format($data1->defense).' '.t('GENERAL_DEFENSE');
			}		
			if ($data1->upkeep > 0) {
				$page .= '<br/>'.t('GENERAL_UPKEEP').': +'.money_format1($data1->upkeep);
			}		
			$page .= '</td>';
			
			$page .= '<td width="80">';
			if ($data1->price>0) {
				$page .= money_format2($data1->price).'<br/>';
			} else {
				$page .= gold_format($data1->gold).'<br/>';
			}
			$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_UNIT_DEPLOY.'&uid='.$data1->uid, t('LINK_DEPLOY'),'deploy-'.($count+100));
			$page .= '</td>';
			
			$page .= '<td width="110">'.t('GENERAL_DEPLOYED').': '.deploy_format($data1->amount).'<br/>';
			$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_UNIT_DISBAND.'&uid='.$data1->uid, t('LINK_DISBAND'),'disband-'.$count);

			$page .= '</td>';
		
			$page .= '</tr>';
		}
	
		/* show first locked unit */
		if ($data2=warquest_db_fetch_object($result2)) {
	
			$page .= '<tr>';	
		
			$page .= '<td>'; 
			$page .= warquest_image("other/unlock.png");
			$page .= '</td>'; 
		
			$page .= '<td>'; 
			$page .= '<span class="subparagraph bold">'.t('UNIT_'.$data2->uid).'</span><br/>';
			if ($data2->attack > 0) {
				$page .= strength_format($data2->attack).' '.t('GENERAL_ATTACK').' - ';
			}
			if ($data2->defense > 0) {
				$page .= strength_format($data2->defense).' '.t('GENERAL_DEFENSE');
			}
			if ($data2->upkeep > 0) {
				$page .= '<br/>'.t('GENERAL_UPKEEP').': +'.money_format1($data2->upkeep);
			}
			$page .= '</td>'; 
	
			$page .= '<td colspan="2" width="200" align="right">'; 
			$page .= t('GENERAL_UNLOCK', $data2->lid);
			$page .= '</td>';
	
			$page .= '</tr>';
		}	
		
		$page .= '</table>';
		$page .= '</div>'; 
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
	
	/* Event handler */
	switch ($eid) {

		case EVENT_UNIT_DEPLOY: 
					warquest_unit_deploy_do();
				   break;

	   case EVENT_UNIT_DISBAND: 
					warquest_unit_disband_do();
				   break;
				  
		case EVENT_SWITCH_PLANET: 
					warquest_switch_planet_do();
					break;		
	}
		
	/* Page handler */
	switch ($sid) {
	
		default: 
				warquest_unit_form();
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