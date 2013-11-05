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
	global $eid;
	global $gid;	
	global $uid;
	global $amount;
	
	/* output */
	global $page; 
	global $player;
	global $popup;
		
	$discount = warquest_discount($player, $player->planet);
		
	/* Get building information */
	$query  = 'select bid, price, income, defense, energy, max from building where bid='.$uid;
	$result = warquest_db_query($query);	 
 	$building=warquest_db_fetch_object($result); 
		
	/* Get amount of buildings */
	$query  = "select amount from player_building where bid=".$uid." and pid=".$player->pid;
	$result = warquest_db_query($query);	 
	$amountOld=0;	
	if ($data=warquest_db_fetch_object($result)) {
		$amountOld=$data->amount;		
	} 
	$totalAmount=$amountOld;
	
	/* Calculate total citizens cost */
	$query3  = 'select sum(a.amount * b.upkeep) as total from building_unit a, unit b where a.uid=b.uid and bid='.$uid;
	$result3 = warquest_db_query($query3);	
	$data3=warquest_db_fetch_object($result3);
		
	/* Calculate total price of buying building transaction */
	$total=0;
	$price =$building->price;
	for ($tmp=$amountOld; $tmp<($amountOld+$amount); $tmp++) {
		$total += warquest_rente($price ,$tmp, $discount);
	}
		
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
	
	} else if ($player->money < $total) {
	
		$message = '<table>';
		$message .= '<tr>';
		$message .= '<td width="100">';
		$message .= warquest_building_image($building,0,0);
		$message .= '</td>';
		$message .= '<td>';
		$message .= t('BUILDING_NO_MONEY', $amount, t('BUILDING_'.$uid), money_format1($total));
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
		$message .= t('BUILDING_LOW_UPKEEP2' ,$amount, t('BUILDING_'.$uid), money_format1($total));
		$message .= '</td>';
		$message .= '</tr>';
		$message .= '</table>';
	
		$type = "warning";
		
   } else {		
	
		$player->energy_step += ($building->energy * $amount);
		$player->money -= $total; 
		$totalAmount = $amountOld+$amount; 
		
		if ($amountOld==0)	{	
			$query  = 'insert into player_building (bid, pid, amount) ';
			$query .= "values (".$uid.",".$player->pid.",".$amount.")";	
		} else {
			$query  = "update player_building set amount=";
			$query .= $totalAmount." where pid=".$player->pid." and bid=".$uid; 
		} 		
		warquest_db_query($query);
			
		/* Update income and defense value */
		warquest_netto_income($player);
		
		/* Update citizens units amount */
		$query  = 'select a.uid, sum(b.amount * c.amount) as amount from unit a ';
		$query .= 'left join building_unit b on b.uid=a.uid, player_building c ';
		$query .= 'where (a.ugid=5 or a.ugid=10 or a.ugid=17 or a.ugid=23) and ';
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
		$message .= t('BUILDING_BUY', $amount, t('BUILDING_'.$uid), money_format1($total), deploy_format($amountOld + $amount));
		$message .= '</td>';
		$message .= '</tr>';
		$message .= '</table>';
		
		$type = "info";
		
		$log = 'Buy '.number_format2($amount).' '.t('BUILDING_'.$uid).' ['.$uid.'] for '.number_format2($total);		
		warquest_user_log($player, $log);
	}
	
	$amountDiff = $building->max - $totalAmount;
	if ($amountDiff<0) $amountDiff=0;
	
	$link  = warquest_link('mid='.$mid.'&sid='.$sid.'&uid='.$uid.'&eid='.$eid.'&gid='.$gid, t('LINK_BUY_AGAIN'), 'buy-0');
	$link .= '<br/><br/>'.t('GENERAL_AMOUNT').'<br/>';
	$link .= warquest_amount_selected($amountDiff);

	$message .= warquest_show_ads();
	$popup .= warquest_box($type, $message, $link);	
}

/** 
 * Sell building(s)
 */
function warquest_building_sell_do() {
   
	/* input */
	global $mid;
	global $sid;
	global $eid;
	global $gid;
	global $player;
	global $uid;
	global $amount;
	global $config;
	
	/* output */
	global $page; 
	global $player;
	global $popup;
	
	$discount = warquest_discount($player, $player->planet);
	
	/* Get building */
	$query  = "select bid, price, income, defense, energy from building where bid=".$uid;
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
	
	/* Calculate total price of selling building transaction */
	$total=0;
	$price = $building->price;
	for ($tmp=$amountOld; $tmp>($amountOld-$amount); $tmp--) {
		$total += warquest_rente($price ,$tmp, $discount);
	}

	/* Decrease money (60% of buy price) */
	$total = round($total * $config["building_sell_ratio"] );
		
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
		$message .= t('BUILDING_LOW_UPKEEP' ,$amount, t('BUILDING_'.$uid), money_format1($total));
		$message .= '</td>';
		$message .= '</tr>';
		$message .= '</table>';
	
		$type = "warning";	
	
	} else {
			
		$player->energy_step -= ($building->energy * $amount);
		$player->money += $total; 

		/* First update */
		$query  = "update player_building set amount=".($amountOld-$amount)." where pid=".$player->pid." and bid=".$uid; 
		warquest_db_query($query);

		/* Update income and defense value */
		warquest_netto_income($player);
	
		/* Update citizens units */
		$query  = 'select a.uid, sum(b.amount * c.amount) as amount from unit a ';
		$query .= 'left join building_unit b on b.uid=a.uid, player_building c ';
		$query .= 'where (a.ugid=5 or a.ugid=10 or a.ugid=17 or a.ugid=23) and b.bid=c.bid and ';
		$query .= 'c.pid='.$player->pid.' group by a.uid';
	 
		$result = warquest_db_query($query);	
		while ($data=warquest_db_fetch_object($result)) {		
			warquest_db_unit_delete($player->pid, $data->uid, $data->amount, 1);
		}
 	
		/* Second remove nul entries */
		if (($amountOld-$amount)==0) {
			$query = "delete from player_building where pid=".$player->pid." and bid=".$uid; 
			warquest_db_query($query);
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
		$message .= t('BUILDING_SELL', $amount, t('BUILDING_'.$uid), money_format1($total), deploy_format($amountOld-$amount));
		$message .= '</td>';
		$message .= '</tr>';
		$message .= '</table>';
		
		$type = "info";		
		
		$log = 'Sell '.number_format2($amount).' '.t('BUILDING_'.$uid).' ['.$uid.'] for '.number_format2($total);		
		warquest_user_log($player, $log);
	}
	
	$link = "";
	if (($amountOld-$amount)>0) {
		$link = warquest_link('mid='.$mid.'&sid='.$sid.'&uid='.$uid.'&eid='.$eid.'&gid='.$gid, t('LINK_SELL_AGAIN'), 'sell-1');
		$link .= '<br/><br/>'.t('GENERAL_AMOUNT').'<br/>';
		$link .= warquest_amount_selected($amountOld-$amount);
	}
		
	$message .= warquest_show_ads();
		
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
	global $sid;
	global $mid;
	global $uid;
	global $amount;
	global $player;
	global $config;
		
	/* output */
	global $page; 
	global $title;
		
	$title = t('BUILDING_GROUP_'.$sid);
	
	$building_group = warquest_db_building_group($sid);
	 
	$discount = warquest_discount($player, $player->planet);
	
	/* Get mission data */
	$query  = 'select count(bid) as total from building ';
	$query .= 'where bgid='.$sid.' and lid<='.$player->lid;
	$result = warquest_db_query($query);
	$total = 0;
	if ($data = warquest_db_fetch_object($result)) {
		$total = $data->total;
	}
		
	/* Get player data */
	$query  = 'select b.ugid, b.bid, b.price, b.income, b.defense, b.energy, b.discount, b.maintenance,  ';
	$query .= 'b.max, IFNULL(a.amount, 0) as amount ';
	$query .= 'from building b left join player_building a ';
	$query .= 'on a.bid=b.bid and a.pid='.$player->pid.' where b.lid<='.$player->lid.' ';  
	$query .= 'and b.bgid='.$sid.' ';
	$query .= 'order by b.lid';
	
	$result = warquest_db_query($query);	
	
	if (($building_group->sell==1) && ($uid==0)) {
		$page .= warquest_amount_radiobox();		
	} else {
		$player->default_amount=1;
	}
	
	$page .= '<div class="box">';
	$page .= '<table>';
	
	$count1 = 0;		
	$count2 = 0;
	while ($data=warquest_db_fetch_object($result)) {
				
		$count1++;
	
		$page .= '<tr>';	
				$page .= '<td valign="top" width="215">';		
		$page .= '<span class="subparagraph">'.t('BUILDING_'.$data->bid).'</span><br/>'; 		 		
		$page .= warquest_building_image($data, 0, 0, 170, 120);			
		$page .= '</td>';
	
		$page .= '<td valign="top" width="180">';
		$page .= '<b>'.t('BUILDING_GAIN').':</b><br/>';
	
		if ($data->income>0) {
			$page .= t('BUILDING_INCOME').': +'.money_format1($data->income).' '.t('GENERAL_DOLLAR');
		}
		if ($data->defense>0) {
			$page .= t('UNIT_GROUP_'.$data->ugid).' '.t('GENERAL_DEFENSE').': +'.$data->defense;
		}			
		if ($data->energy>0)  {
			$page .= t('BUILDING_ENERGY').': +'.energy_format($data->energy);
		}
		if ($data->discount>0) {
			$page .= t('GENERAL_DISCOUNT').': +'.$data->discount.'%';
		}		
		if ($data->maintenance>0) {
			$page .= t('GENERAL_MAINTENANCE').': +'.$data->maintenance.'%';	
		}		
	
		$page .= '<br/><br/><b>'.t('BUILDING_REQUIRED').':</b><br/>';
	
		$query3  = 'select sum(a.amount * b.upkeep) as total from building_unit a, ';
		$query3 .= 'unit b where a.uid=b.uid and bid='.$data->bid;
		$result3 = warquest_db_query($query3);	 
		$data3 = warquest_db_fetch_object($result3);
		$page .= t('BUILDING_UPKEEP').': +'.money_format1($data3->total).'<br/><br/>';
	
		$query  = 'select b.uid, a.amount, b.upkeep, b.attack, b.defense ';
		$query .= 'from building_unit a, unit b where b.uid=a.uid and a.bid='.$data->bid.' order by b.upkeep';  
		$result2 = warquest_db_query($query);	
	
		$page .= '<table>';
		$page .= '<tr>';	
		
		while ($data2=warquest_db_fetch_object($result2)) {
		
			$count2++; 
		
			$page .= '<td width="45" align="left">';
			$page .= warquest_unit_image($data2, $count2, 1, 45, 32);	
			$page .= '<br/><center>'.number_format2($data2->amount).'x</center>';
			$page .= '</td>';
		}
	
		$page .= '</tr>';
		$page .= '</table>';	
	
		$page .= '</td>';
	
		$page .= '<td valign="top" width="100">';
		$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&uid='.$data->bid.'&eid=1', t('LINK_BUY'),"buy-".$count1);
			
		/* Prevent buy with discount, sell without discount */
		if ($building_group->sell==1) {
			$page .= '<span class="right2">';
			$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&uid='.$data->bid.'&eid=2', t('LINK_SELL'), "sell-".$count1);
			$page .= '</span>';
		}		  
	
		/* Calculate price */
		$price = $data->price;
		$price = warquest_rente($price ,$data->amount, $discount);
				
		$page .= '<br/><br/><b>';
		$page .= t('BUILDING_PRICE').':</b><br/>'.money_format2($price);
		$page .= '<br/><br/><b>';
		$page .= t('BUILDING_DEPLOYED').':</b><br/>'.deploy_format($data->amount).'<br/>';
			
		$page .= '</td>';
	
		$page .= '</tr>';
	
		if ($count1!=$total) {
			$page .= '<tr>';
			$page .= '<td colspan="3"><hr></td>';
			$page .= '</tr>';			
		}
	}
	
	/* Unlock next building */
	$query  = 'select bid, lid, income, defense, energy, discount, maintenance, ugid from building where lid>'.$player->lid.' ';
	$query .= 'and bgid='.$sid.' order by income asc, defense asc, energy asc, discount asc, maintenance asc limit 0,1'; 
	$result = warquest_db_query($query);	
		
	if ($data=warquest_db_fetch_object($result)) {
		
		$count1++;
		
		if ($count1>0) {
			$page .= '<tr>';
			$page .= '<td colspan="3"><hr></td>';
			$page .= '</tr>';			
		}
					
		$page .= '<tr>';	
		$page .= '<td width="215">'; 
		$page .= '<span class="subparagraph">'.t('BUILDING_'.$data->bid).'</span><br/>';
		$page .= warquest_image("other/unlock.png", ' width="90" height="67" ');	
		$page .= warquest_image("other/unlock.png", ' width="90" height="67" ');	
		$page .= '</td>'; 
	
		$page .= '<td valign="top" width="180">';
		$page .= '<b>'.t('BUILDING_GAIN').':</b><br/>';
	
		if ($data->income>0) {
			$page .= t('BUILDING_INCOME').': +'.money_format1($data->income).' '.t('GENERAL_DOLLAR');
		}
						
		if ($data->defense>0) {
			$page .= t('UNIT_GROUP_'.$data->ugid).' '.t('GENERAL_DEFENSE').': +'.$data->defense;
		}
		
		if ($data->energy>0)  {
			$page .= t('BUILDING_ENERGY').': +'.energy_format($data->energy);
		}
					
		if ($data->discount>0) {
			$page .= t('GENERAL_DISCOUNT').': +'.$data->discount.'%';
		}		
				
		if ($data->maintenance>0) {
			$page .= t('GENERAL_MAINTENANCE').': +'.$data->maintenance.'%';	
		}		
		$page .= '</td>';
	
		$page .= '<td valign="top" width="100">';
	
		$page .= t('GENERAL_UNLOCK', $data->lid);
		$page .= '</td>';
		$page .= '</tr>';		
	}

	$page .= '</table>';
	$page .= '</div>'; 
		
	if ($count1==0) {
	
		$message = t('BUILDINGS_NO_BUILDINGS');
		$page .= warquest_box_icon('info', $message);
			
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
	global $sequence;
	global $player;
	
		/* output */
	global $popup;
	
	if ($sequence != $player->request) {
	
		$message = t('SYSTEM_HACK_DETECTED');
		$popup .= warquest_box_icon("warning", $message);	
		return;
	}
		
	/* event handler */
	switch ($eid) {
	
		case 1:  	warquest_building_buy_do();
						break;
				
		case 2:   	warquest_building_sell_do();
						break;	

		case 500: 	warquest_switch_planet_do();
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