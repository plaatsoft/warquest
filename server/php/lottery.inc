<?php

/* 
**  ========
**  WarQuest
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
**  All copyrights reserved (c) 2008-2016 PlaatSoft
*/

/*
** ---------------------------------------------------------------- 
** LOTTERY
** ---------------------------------------------------------------- 
*/

/* 
** -----------
** PARAMETERS
** -----------
*/

$amount = warquest_post('amount', 1);

/* 
** -----------
** ACTIONS
** -----------
*/

function warquest_lottery_bet_do() {

	/* input */
	global $mid;
	global $sid;
	global $ssid;
	global $player;
	global $id;
	global $amount;
	
	/* output */
	global $output;	
	
	$lottery = warquest_db_lottery($id);
 
	if (!isset($lottery->lottery_id)) {
	
		$message = t('LOTTERY_INVALID');
		$output->popup .= warquest_box_icon("warning", $message);
	
	} else if ($lottery->done==1) {
		
		$message = t('LOTTERY_EXPIRED');
		$output->popup .= warquest_box_icon("warning", $message);
	
	} else if ($player->gold<($lottery->bet * $amount)) {
	
		$message = t('LOTTERY_NO_GOLD');
		$output->popup .= warquest_box_icon("warning", $message);
	
	} else {

		/* Withdraw gold from player wallet */
		$player->gold -= ($lottery->bet * $amount);
		
		/* Set bet */
		for ($i=0; $i<$amount; $i++) {
			warquest_db_player_lottery($player->pid, $lottery->lottery_id);
		}
		
		/* Log user event */
		$log = 'Buy '.$amount.' loot(s) in lottery '.$lottery->lottery_id.' for '.gold_format($lottery->bet);		
		warquest_user_log($player, $log);
			
		/* Update gold statistics */
		warquest_gold_use($lottery->bet * $amount);
		
		/* Show popup message */
		$link = warquest_link('mid='.$mid.'&sid='.$sid.'&ssid='.$ssid.'&id='.$lottery->lottery_id.'&eid='.EVENT_LOTTERY_BET, t('LINK_BET_AGAIN'));		
		$link .= '<br/><br/>'.t('GENERAL_AMOUNT').'<br/>';
		
		$max=1;
		if ($lottery->bet>0) {
			$max = round($player->gold/$lottery->bet);
		}
		$link .= warquest_amount_selected($max);
		
		$message = t('LOTTERY_BET_SET', $lottery->lottery_id, gold_format($lottery->bet*$amount));
		$output->popup .= warquest_box_icon("info", $message, $link);
	}
}

/*
** -----------
** FORMS
** -----------
*/

function warquest_lottery_form() {

	/* input */
	global $mid;
	global $sid;
	global $ssid;
	global $ssid;
	
	global $player;
	global $config;
	global $offset;
		
	/* output */
	global $page; 
	global $output;
	
	$limit = 3;
	
	$output->title = t('LOTTERY_TITLE');
	
	$page .= '<div class="subparagraph">';
	$page .= t('LOTTERY_TITLE');		
	$page .= '</div>';
	
	if ($player->lid < $config["casino_unlock_level_5"]) {
	
		$message = t('LOTTERY_UNLOCKED', $config["casino_unlock_level_5"]);
		$page .= warquest_box_icon('locked', $message);
	
	} else {
		
		$query  = 'select count(lottery_id) as total from lottery';
		$result = warquest_db_query($query);
		$data = warquest_db_fetch_object($result);
		$total = $data->total;
		
		$page .= warquest_page_control($offset, $limit, $total, 1);
		
		/* Show running lotteries */
		$query  = 'select lottery_id, expire_date, bet, uid, uid_amount, bid, bid_amount, money, gold, done from lottery ';		
		$query .= 'order by lottery_id desc ';
		$query .= 'limit '.$offset.','.$limit;
	
		$result = warquest_db_query($query);

		$line=0;
		$count=0;
		while ( $data=warquest_db_fetch_object($result) ) {
	
			$active = strtotime($data->expire_date) - time();
	
			$line++;
		
			$query2  = 'select count(pid) as total from player_lottery where lottery_id='.$data->lottery_id;
			$result2 = warquest_db_query($query2);
			$data2 = warquest_db_fetch_object($result2);
		
			$query3  = 'select count(pid) as total from player_lottery where lottery_id='.$data->lottery_id.' ';
			$query3 .= 'and pid='.$player->pid;
			$result3 = warquest_db_query($query3);
			$data3 = warquest_db_fetch_object($result3);
			
			$page .= '<div class="box" >';
		
			if ($active>0) {	
				$page .= '<div class="right2">';
				$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&ssid='.$ssid.'&id='.$data->lottery_id.'&eid='.EVENT_LOTTERY_BET, t('LINK_BET'));
				$page .= '</div>';
			}
						
			$page .= '<div class="subparagraph">';
			$page .= t('LOTTERY_TITLE').' '.$data->lottery_id;
			if ($player->pid==$config["adminPid"]) {
				$page .= ' ['.$data2->total.' bets]';
			}
			
			$page .= '</div>';			
			
			$page .= '<table>';
			$page .= '<tr>';
					
			if ($data->done==0) {
			
				$page .= '<td width="135">';
				$page .= t('LOTTERY_BET_COST').': ';
				$page .= gold_format($data->bet);		
				$page .= '</td>';
				
			} else {
			
				$page .= '<td width="250">';		
				$query4  = 'select pid from player_lottery where lottery_id='.$data->lottery_id.' and winner=1 limit 0,1 ';
				$result4 = warquest_db_query($query4);
				$data4 = warquest_db_fetch_object($result4);
				
				if (isset($data4->pid)) {
				
					$other = warquest_db_player($data4->pid);
					$page .= t('LOTTERY_WINNER_IS').': ';
					$page .= player_format($other->pid, $other->name, $other->country);	
					$page .= '</td>';
					
				} else {
				
					$page .= '';	
					$page .= '</td>';
				}
			}
			
			if ($data->done==0) {		

				$page .= '<td width="175">';
				$page .= t('LOTTERY_EXPIRE').': ';			
				$active = strtotime($data->expire_date) - time();			
				if ($active>0) {		
					$page .= '<script language="JavaScript" src="'.$config["content_url"].'js/countdown'.$line.'.js" type="text/javascript"></script>';
					$page .= '<div class="countdown strength"><div id="countdown_time'.$line.'"></div></div>';
					$page .= '<script language="JavaScript" type="text/javascript">';
					$page .= 'countdown'.$line.'.init('.$active.', "countdown_time'.$line.'", "00:00:00");'; 
					$page .= '</script>';
					
				} else {
				
					$page .= '<span class="strength">00:00:00</span>';
				}
				$page .= '</td>';
				
			} else {
			
				$page .= '<td width="250">';
				$page .= t('LOTTERY_DATE').': ';
				$page .= '<span class="strength">';
				$page .= warquest_ui_ago($data->expire_date).' ';
				$page .= '</span>';
				$page .= t('GENERAL_BY');	
				$page .= '</td>';	
			}
			
			if ($data->done==0) {
				
				$page .= '<td width="150">';
				$page .= t('LOTTERY_CHANCE').': ';			
				
				$chance = 0;
				if ($data2->total>0) {
					$chance = ($data3->total/$data2->total)*100;
				}
			
				$page .= '<span class="health">';
				$page .= round($chance,2)."%";
				$page .= '</span>';
				$page .= '</td>';
			}
			
			$page .= '</tr>';		
			$page .= '</table>';
			
			$page .= '<div class="spacer"></div>';
	
			$page .= '<b>'.t('LOTTERY_PRICE').'</b>:';
			
			$page .= '<table>';
			$page .= '<tr>';		
			
			if ( $data->money>0 ) {
								
				$page .= '<td>';								
				$page .= warquest_image('lottery/dollar.jpg', 'width="160" height="130"');	
				$page .= '<br/><center>'.dollar_format($data->money).'</center>';
				$page .= '</td>';
			}
			
			if ( $data->gold>0 ) {
								
				$page .= '<td>';								
				$page .= warquest_image('lottery/gold.jpg', 'width="160" height="130"');	
				$page .= '<br/><center>'.gold_format($data->gold).'</center>';
				$page .= '</td>';
			}
			
			if ( $data->uid>0 ) {
				
				$unit = warquest_db_unit($data->uid);
				
				$page .= '<td>';								
				$page .= warquest_unit_image($unit, $count++, 1, 160, 130);	
				$page .= '<br/><center>'.$data->uid_amount.'x</center>';
				$page .= '</td>';
			}
			
			if ( $data->bid>0 ) {
				
				$building = warquest_db_building($data->bid);
				
				$page .= '<td>';								
				$page .= warquest_building_image($building, $count++, 1, 160, 130);	
				$page .= '<br/><center>'.$data->bid_amount.'x</center>';
				$page .= '</td>';
			}
			
			$page .= '</tr>';		
			$page .= '</table>';
			
			$page .= '<div class="spacer"></div>';
			
			$page .= '</div>';
		}
	
		$page .= warquest_page_control($offset, $limit, $total, 0);
	
		if ($line==0) {
		
			$message = t('LOTTERY_NOT_AVAILABLE');
			$page .= warquest_box_icon('info', $message);	
		}		
	}
	
	$page .= '<div class="spacer"></div>';
	$page .= '<span class="casino">'.t('CASINO_WARNING').' </span>';
	$page .= '<span class="note">';
	$page .= t('LOTTERY_NOTE');
	$page .='</span>';
	
}

/*
** -----------
** HANDLER
** -----------
*/

/** 
 * Event handler
 */
function warquest_lottery() {

	/* input */
	global $eid;
	global $ssid;
	  	
	/* Event handler */
	switch ($eid ) {
				
		case EVENT_LOTTERY_BET:	
			warquest_lottery_bet_do();
			break;
	}				
	
	switch($ssid) {
		
		case PAGE_CASINO_LOTTERY: 
			warquest_lottery_form();
			break;
	}	
}

/*
** ---------------------------------------------------------------- 
** THE END
** ----------------------------------------------------------------
*/

?>