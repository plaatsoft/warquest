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
** BUILDINGS
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
 * Buy building(s)
 */
function warquest_building_buy_do() {
   
	/* input */
	global $mid;
	global $sid;
	global $ssid;
	
	global $eid;
	global $gid;	
	global $uid;
	global $amount;
	
	/* output */
	global $page; 
	global $player;
	global $popup;
		
	$discount = warquest_db_discount($player, $player->planet);
		
	/* Get building information */
	$query  = 'select bid, price, gold, income, defense, energy, max from building where bid='.$uid;
	$result = warquest_db_query($query);	 
 	$building = warquest_db_fetch_object($result); 
		
	/* Get amount of buildings */
	$query  = "select amount from player_building where bid=".$uid." and pid=".$player->pid;
	$result = warquest_db_query($query);	 
	$amountOld=0;	
	if ($data=warquest_db_fetch_object($result)) {
		$amountOld=$data->amount;		
	} 
	$totalAmount=$amountOld;
	
	/* Calculate total upkeep cost */
	$query3  = 'select sum(a.amount * b.upkeep) as total from building_unit a, unit b where a.uid=b.uid and bid='.$uid;
	$result3 = warquest_db_query($query3);	
	$data3 = warquest_db_fetch_object($result3);
		
	/* Calculate total price of buying building transaction */
	$totalPrice=0;
	$price =$building->price;
	for ($tmp=$amountOld; $tmp<($amountOld+$amount); $tmp++) {
		$totalPrice += warquest_rente($price ,$tmp, $discount);
	}
	
	/* Calculate total gold cost */
	$totalGold = $building->gold * $amount;
		
	if (($amountOld + $amount) > $building->max ) {

		$message = '<table>';
		$message .= '<tr>';
		$message .= '<td width="100">';
		$message .= warquest_building_image($building,0,0);
		$message .= '</td>';
		$message .= '<td>';
		$message .= t('BUILDING_MAX', deploy_format($building->max), t('BUILDING_'.$uid));
		$message .= '</td>';
		$message .= '</tr>';
		$message .= '</table>';
			
		$type = "warning";
	
	} else if ( (($totalPrice>0) && ($player->money < $totalPrice)) || (($totalGold>0) && ($player->gold < $totalGold)) ) {
	
		$message = '<table>';
		$message .= '<tr>';
		$message .= '<td width="100">';
		$message .= warquest_building_image($building,0,0);
		$message .= '</td>';
		$message .= '<td>';
		if ($totalPrice>0) {
			$message .= t('BUILDING_NO_FUNDS', $amount, t('BUILDING_'.$uid), dollar_format($totalPrice));
		} else {
			$message .= t('BUILDING_NO_FUNDS', $amount, t('BUILDING_'.$uid), gold_format($totalGold));
		}
		$message .= '</td>';
		$message .= '</tr>';
		$message .= '</table>';

		$type = "warning";	
			
	} else if ((($player->money_step>0) && ($player->money_step+($building->income*$amount)-($data3->total*$amount))<0)
			|| (($player->money_step<0) && (($building->income*$amount)-($data3->total*$amount)<0)) ) {
	
		$message = '<table>';
		$message .= '<tr>';
		$message .= '<td width="100">';
		$message .= warquest_building_image($building,0,0);
		$message .= '</td>';
		$message .= '<td>';
		if ($totalPrice>0) {
			$message .= t('BUILDING_LOW_UPKEEP2' ,$amount, t('BUILDING_'.$uid), dollar_format($totalPrice));
		} else {
			$message .= t('BUILDING_LOW_UPKEEP2' ,$amount, t('BUILDING_'.$uid), gold_format($totalGold));
		}
		$message .= '</td>';
		$message .= '</tr>';
		$message .= '</table>';
	
		$type = "warning";
		
   } else {		
	
		/* Buy building(s) */
		$player->energy_step += ($building->energy * $amount);
		$player->money -= $totalPrice; 
		$player->gold -= $totalGold;

		/* Update Statistics */
		warquest_gold_use($totalGold);
		
			/* save data in database */
		$totalAmount = warquest_db_building_add($player->pid, $uid, $amount);
		
		/* Update income and defense value */
		warquest_netto_income($player);
		
		/* Update citizens units amount */
		$query  = 'select a.uid, sum(b.amount * c.amount) as amount from unit a ';
		$query .= 'left join building_unit b on b.uid=a.uid, player_building c ';
		$query .= 'where a.ugid in (select ugid from unit_group where type=6) and ';
		$query .= 'b.bid=c.bid and c.pid='.$player->pid.' group by a.uid';
	 
		$result = warquest_db_query($query);	 
		while ($data=warquest_db_fetch_object($result)) {		
			warquest_db_unit_add($player->pid, $data->uid, $data->amount, 1);
		}
		
		/* Update netto income */
		warquest_netto_income($player);
		
		/* Show message on screen */
		$message = '<table>';
		$message .= '<tr>';
		$message .= '<td width="100">';
		$message .= warquest_building_image($building,0,0);
		$message .= '</td>';
		$message .= '<td>';
		if ($totalPrice > 0 ) {
			$message .= t('BUILDING_BUY', $amount, t('BUILDING_'.$uid), dollar_format($totalPrice), deploy_format($amountOld + $amount));
		} else {
			$message .= t('BUILDING_BUY', $amount, t('BUILDING_'.$uid), gold_format($totalGold), deploy_format($amountOld + $amount));
		}
		$message .= '</td>';
		$message .= '</tr>';
		$message .= '</table>';
		
		$type = "info";
		
		if ($totalPrice > 0 ) {
			$log = 'Buy '.number_format2($amount).' '.t('BUILDING_'.$uid).' ['.$uid.'] for '.dollar_format($totalPrice);		
		} else {
			$log = 'Buy '.number_format2($amount).' '.t('BUILDING_'.$uid).' ['.$uid.'] for '.gold_format($totalGold);		
		}
		warquest_user_log($player, $log);
	}
	
	$link = "";
	$amountDiff = $building->max - $totalAmount;
	if ($amountDiff>0) {	
		$link  = warquest_link('mid='.$mid.'&sid='.$sid.'&ssid='.$ssid.'&uid='.$uid.'&eid='.$eid.'&gid='.$gid, t('LINK_BUY_AGAIN'), 'buy-0');
		$link .= '<br/><br/>'.t('GENERAL_AMOUNT').'<br/>';
		$link .= warquest_amount_selected($amountDiff);
	}

	$popup .= warquest_box($type, $message, $link);	
}

/** 
 * Sell building(s)
 */
function warquest_building_sell_do() {
   
	/* input */
	global $mid;
	global $sid;
	global $ssid;
	
	global $eid;
	global $gid;
	global $uid;
	global $amount;
	global $config;
	
	/* output */
	global $page; 
	global $player;
	global $popup;
	
	$discount = warquest_db_discount($player, $player->planet);
	
	/* Get building */
	$query  = "select bid, price, gold, income, defense, energy from building where bid=".$uid;
	$result = warquest_db_query($query);	
 	$building = warquest_db_fetch_object($result); 
		
	/* Unit amount of player */
	$query  = "select amount from player_building where pid=".$player->pid." and bid=".$uid;
	$result = warquest_db_query($query);	  
	$amountOld=0;
	if ($data=warquest_db_fetch_object($result)) {
		$amountOld=$data->amount;
	}

	/* Calculate total citizens cost */
	$query3  = 'select sum(a.amount * b.upkeep) as total from building_unit a, unit b where a.uid=b.uid and bid='.$uid;
	$result3 = warquest_db_query($query3);	
	$data3 = warquest_db_fetch_object($result3);
	
	/* Calculate total price for selling building(s) */
	$totalPrice=0;
	$price = $building->price;
	for ($tmp=$amountOld; $tmp>($amountOld-$amount); $tmp--) {
		$totalPrice += warquest_rente($price ,$tmp, $discount);
	}
	$totalPrice = round($totalPrice * $config["building_sell_ratio"] );
	
	/* Calculate total gold for selling building(s) */
	$totalGold = $building->gold * $amount;
	$totalGold = round($totalGold * $config["building_sell_ratio"] );
		
	if (($amountOld-$amount) < 0) {
	
		$message = '<table>';
		$message .= '<tr>';
		$message .= '<td width="100">';
		$message .= warquest_building_image($building,0,0);
		$message .= '</td>';
		$message .= '<td>';
		$message .= t('BUILDING_NOT_OWNED', $amount , t('BUILDING_'.$uid));
		$message .= '</td>';
		$message .= '</tr>';
		$message .= '</table>';

		$type = "warning";	
				
	} else if (($player->money_step>0) && ($player->money_step<($building->income*$amount))) {
	
		$message = '<table>';
		$message .= '<tr>';
		$message .= '<td width="100">';
		$message .= warquest_building_image($building,0,0);
		$message .= '</td>';
		$message .= '<td>';
		if ($totalPrice>0) {
			$message .= t('BUILDING_LOW_UPKEEP' ,$amount, t('BUILDING_'.$uid), dollar_format($totalPrice));
		} else {
			$message .= t('BUILDING_LOW_UPKEEP' ,$amount, t('BUILDING_'.$uid), gold_format($totalGold));
		}
			
		$message .= '</td>';
		$message .= '</tr>';
		$message .= '</table>';
	
		$type = "warning";	
	
	} else {
			
		/* Sell building(s) */
		$player->energy_step -= ($building->energy * $amount);
		$player->money += $totalPrice; 
		$player->gold += $totalGold; 

		/* Update amount in database */
		warquest_db_building_delete($player->pid, $uid, $amount);
		
		/* Update income and defense value */
		warquest_netto_income($player);
	
		/* Update citizens units */
		$query  = 'select a.uid, sum(b.amount * c.amount) as amount from unit a ';
		$query .= 'left join building_unit b on b.uid=a.uid, player_building c ';
		$query .= 'where a.ugid in (select ugid from unit_group where type=6) and b.bid=c.bid and ';
		$query .= 'c.pid='.$player->pid.' group by a.uid';
	 
		$result = warquest_db_query($query);	
		while ($data=warquest_db_fetch_object($result)) {		
			warquest_db_unit_delete($player->pid, $data->uid, $data->amount, 1);
		}
 	
		/* Update netto incom */
		warquest_netto_income($player);
		
		/* show message on screen */
		$message = '<table>';
		$message .= '<tr>';
		$message .= '<td width="100">';
		$message .= warquest_building_image($building, 0,0);
		$message .= '</td>';
		$message .= '<td>';
		if ($totalPrice>0) {
			$message .= t('BUILDING_SELL', $amount, t('BUILDING_'.$uid), dollar_format($totalPrice), deploy_format($amountOld-$amount));
		} else {
			$message .= t('BUILDING_SELL', $amount, t('BUILDING_'.$uid), gold_format($totalGold), deploy_format($amountOld-$amount));
		}
		$message .= '</td>';
		$message .= '</tr>';
		$message .= '</table>';
		
		$type = "info";		
		
		if ($totalPrice>0) {
			$log = 'Sell '.number_format2($amount).' '.t('BUILDING_'.$uid).' ['.$uid.'] for '.dollar_format($totalPrice);		
		} else {
			$log = 'Sell '.number_format2($amount).' '.t('BUILDING_'.$uid).' ['.$uid.'] for '.gold_format($totalGold);		
		}
		warquest_user_log($player, $log);
	}
	
	$link = "";
	if (($amountOld-$amount)>0) {
		$link = warquest_link('mid='.$mid.'&sid='.$sid.'&ssid='.$ssid.'&uid='.$uid.'&eid='.$eid.'&gid='.$gid, t('LINK_SELL_AGAIN'), 'sell-1');
		$link .= '<br/><br/>'.t('GENERAL_AMOUNT').'<br/>';
		$link .= warquest_amount_selected($amountOld-$amount);
	}
		
	$popup .= warquest_box($type, $message, $link);
}

/*
** -----------
** UI
** -----------
*/

/** 
 * Building form
 */
function warquest_building_form() {
	
	/* input */
	global $uid;
	global $mid;
	global $sid;
	global $ssid;
	
	global $amount;
	global $player;
	global $config;
		
	/* output */
	global $page; 
	global $title;
		
	$title = t('BUILDING_GROUP_'.$sid);
	
	$building_group = warquest_db_building_group($sid);	 
	$discount = warquest_db_discount($player, $player->planet);
		
	/* Get player building data */
	$query2  = 'select b.ugid, b.bid, b.price, b.gold, b.income, b.defense, b.energy, b.discount, b.maintenance,  ';
	$query2 .= 'b.max, IFNULL(a.amount, 0) as amount ';
	$query2 .= 'from building b left join player_building a ';
	$query2 .= 'on a.bid=b.bid and a.pid='.$player->pid.' where b.lid<='.$player->lid.' ';  
	$query2 .= 'and b.bgid='.$sid.' ';	
	if ($building_group->type==2) {
		$query2 .= 'and b.ugid='.$ssid.' ';
	}	
	$query2 .= 'order by b.lid';	
	
	$result2 = warquest_db_query($query2);	
	$count2 = warquest_db_num_rows($result2);
		
	/* Get first locked building */
	$query5  = 'select bid, lid, income, gold, defense, energy, discount, maintenance, ugid from building where lid>'.$player->lid.' ';
	$query5 .= 'and bgid='.$sid.' ';
	if ($building_group->type==2) {
		$query5 .= 'and ugid='.$ssid.' ';
	}
	$query5 .= 'order by income asc, defense asc, energy asc, discount asc, maintenance asc limit 0,1'; 
	
	$result5 = warquest_db_query($query5);	
	$count5 = warquest_db_num_rows($result5);
	
	/* Show Radiobox */
	if ($building_group->sell==1) { 
		
		if ($uid==0) {
	
			$page .= warquest_amount_radiobox();		
			
		} else {
		
			$page .= '<div class="box">';
			$page .= '<br/>';
			$page .= '</div>';		
		}
		
	} else {
	
		$player->default_amount=1;
	}
	
	/* Show submenu */
	if ($building_group->type==2) {
		$page .= warquest_subsubmenu_building();
	}
	
	if (($count2==0) && ($count5==0)) {
	
		$message = t('BUILDINGS_NO_BUILDINGS');
		$page .= warquest_box_icon('info', $message);
			
	} else {
		
		$page .= '<div class="box">';
		$page .= '<table>';
	
		$count3 = 0;		
		$count4 = 0;
		
		/* Show player buildings */
		while ($data2=warquest_db_fetch_object($result2)) {
				
			$count3++;
	
			$page .= '<tr>';	
			$page .= '<td valign="top" width="215">';		
			$page .= '<span class="subparagraph">'.t('BUILDING_'.$data2->bid).'</span><br/>'; 		 		
			$page .= warquest_building_image($data2, 0, 0, 170, 120);			
			$page .= '</td>';
	
			$page .= '<td valign="top" width="180">';
			$page .= '<b>'.t('BUILDING_GAIN').':</b><br/>';
	
			if ($data2->income>0) {
				$page .= t('BUILDING_INCOME').': +'.dollar_format($data2->income);
			}
			if ($data2->defense>0) {
				$page .= t('UNIT_GROUP_'.$data2->ugid).' '.t('GENERAL_DEFENSE').': +'.$data2->defense;
			}			
			if ($data2->energy>0)  {
				$page .= t('BUILDING_ENERGY').': +'.energy_format($data2->energy);
			}
			if ($data2->discount>0) {
				$page .= t('GENERAL_DISCOUNT').': +'.discount_format($data2->discount).'%';
			}		
			if ($data2->maintenance>0) {
				$page .= t('GENERAL_MAINTENANCE').': +'.maintenance_format($data2->maintenance).'%';	
			}		
		
			$page .= '<br/><br/><b>'.t('BUILDING_REQUIRED').':</b><br/>';
		
			$query3  = 'select sum(a.amount * b.upkeep) as total from building_unit a, ';
			$query3 .= 'unit b where a.uid=b.uid and bid='.$data2->bid;
			$result3 = warquest_db_query($query3);	 
			$data3 = warquest_db_fetch_object($result3);
		
			$page .= t('BUILDING_UPKEEP').': +'.money_format1($data3->total).'<br/><br/>';
	
			$query4  = 'select b.uid, b.gold, a.amount, b.upkeep, b.attack, b.defense ';
			$query4 .= 'from building_unit a, unit b where b.uid=a.uid and a.bid='.$data2->bid.' order by b.upkeep';  
			$result4 = warquest_db_query($query4);	
		
			$page .= '<table>';
			$page .= '<tr>';	
		
			while ($data4=warquest_db_fetch_object($result4)) {
		
				$count4++; 
		
				$page .= '<td width="45" align="left">';
				$page .= warquest_unit_image($data4, $count4, 1, 45, 32);	
				$page .= '<br/><center>'.number_format2($data4->amount).'x</center>';
				$page .= '</td>';
			}
	
			$page .= '</tr>';
			$page .= '</table>';	
		
			$page .= '</td>';
		
			$page .= '<td valign="top" width="100">';
			$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&ssid='.$ssid.'&uid='.$data2->bid.'&eid='.EVENT_BUILDING_BUY, t('LINK_BUY'),"buy-".$count3);
			
			/* Prevent buy with discount, sell without discount */
			if ($building_group->sell==1) {
				$page .= '<span class="right2">';
				$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&ssid='.$ssid.'&uid='.$data2->bid.'&eid='.EVENT_BUILDING_SELL, t('LINK_SELL'), "sell-".$count3);
				$page .= '</span>';
			}		  
	
			$page .= '<br/><br/><b>';
			$page .= t('BUILDING_PRICE').':</b><br/>';
				
			/* Calculate price */
			if ($data2->price>0) {
				$price = $data2->price;
				$price = warquest_rente($price ,$data2->amount, $discount);		
				$page .= money_format2($price);
			} else {
				$page .= gold_format($data2->gold);
			}
		
			$page .= '<br/><br/><b>';
			$page .= t('BUILDING_DEPLOYED').':</b><br/>'.deploy_format($data2->amount).'<br/>';
			
			$page .= '</td>';
	
			$page .= '</tr>';
	
			if ($count3!=$count2) {
				$page .= '<tr>';
				$page .= '<td colspan="3"><hr></td>';
				$page .= '</tr>';			
			}
		}
	
		/* Show first lock building */
		if ($data5 = warquest_db_fetch_object($result5)) {
		
			if ($count3>0) {
				$page .= '<tr>';
				$page .= '<td colspan="3"><hr></td>';
				$page .= '</tr>';			
			}	
		
			$count3++;
			
			$page .= '<tr>';	
			$page .= '<td width="215">'; 
			$page .= '<span class="subparagraph">'.t('BUILDING_'.$data5->bid).'</span><br/>';
			$page .= warquest_image("other/unlock.png", ' width="90" height="67" ');	
			$page .= warquest_image("other/unlock.png", ' width="90" height="67" ');	
			$page .= '</td>'; 
	
			$page .= '<td valign="top" width="180">';
			$page .= '<b>'.t('BUILDING_GAIN').':</b><br/>';
	
			if ($data5->income>0) {
				$page .= t('BUILDING_INCOME').': +'.dollar_format($data5->income);
			}
						
			if ($data5->defense>0) {
				$page .= t('UNIT_GROUP_'.$data5->ugid).' '.t('GENERAL_DEFENSE').': +'.$data5->defense;
			}
		
			if ($data5->energy>0)  {
				$page .= t('BUILDING_ENERGY').': +'.energy_format($data5->energy);
			}
					
			if ($data5->discount>0) {
				$page .= t('GENERAL_DISCOUNT').': +'.discount_format($data5->discount).'%';
			}		
				
			if ($data5->maintenance>0) {
				$page .= t('GENERAL_MAINTENANCE').': +'.maintenance_format($data5->maintenance).'%';	
			}		
			$page .= '</td>';
	
			$page .= '<td valign="top" width="100">';
	
			$page .= t('GENERAL_UNLOCK', $data5->lid);
			$page .= '</td>';
			$page .= '</tr>';		
		}

		$page .= '</table>';
		$page .= '</div>'; 
	}
			
	$page .= '<div class="note">';
	$page .= t('BUILDING_NOTE'.$sid);
	$page .= '</div>';	
}

/*
** -------------
** HANDLER
** -------------
*/

/** 
 * Building handler
 */
function warquest_building() {
	
	/* input */
	global $eid;
	
	/* event handler */
	switch ($eid) {
	
		case EVENT_BUILDING_BUY:  	
						warquest_building_buy_do();
						break;
				
		case EVENT_BUILDING_SELL:   	
						warquest_building_sell_do();
						break;	

		case EVENT_SWITCH_PLANET: 	
						warquest_switch_planet_do();
						break;			  
	}

	/* page handler */
	warquest_building_form();			
}

/*
** ---------------------------------------------------------------- 
** THE END
** ----------------------------------------------------------------
*/

?>