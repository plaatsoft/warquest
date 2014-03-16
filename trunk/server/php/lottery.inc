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
** LOTTERY
** ---------------------------------------------------------------- 
*/

function warquest_lottery_bet_do() {

	/* input */
	global $mid;
	global $sid;
	global $player;
	global $id;
	
	/* output */
	global $output;	
	
	$lottery = warquest_db_lottery($id);
 
	if (!isset($lottery->lottery_id)) {
	
		$message = t('LOTTERY_INVALID');
		$output->popup .= warquest_box_icon("warning", $message);
		
	} else if ($player->gold<$lottery->bet) {
	
		$message = t('LOTTERY_NO_GOLD');
		$output->popup .= warquest_box_icon("warning", $message);
	
	} else {
	
		$active = strtotime($lottery->expire_date) - time();			
		
		if ($active<0) {
		
			$message = t('LOTTERY_EXPIRED');
			$output->popup .= warquest_box_icon("warning", $message);
				
		} else { 
	
			$player->gold -= $lottery->bet;
			
			warquest_db_player_lottery($player->pid, $lottery->lottery_id);
						
			$log = 'Buy loot in lottery for '.gold_format($lottery->bet);		
			warquest_user_log($player, $log);
			
			/* Update Statistics */
			warquest_gold_use($lottery->bet);
		
			$link = warquest_link('mid='.$mid.'&sid='.$sid.'&id='.$lottery->lottery_id.'&eid='.EVENT_LOTTERY_BET, t('LINK_BET_AGAIN'));		
			$message = t('LOTTERY_BET_SET', $lottery->lottery_id, gold_format($lottery->bet));
			$output->popup .= warquest_box_icon("info", $message, $link);			
		}
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
	
	global $anchor;
	global $player;
	global $config;
	
	/* output */
	global $page; 
	global $output;

	warquest_set_default_mission($ssid);	
	
	$lid = 30;
	
	$output->title = t('LOTTERY_TITLE');
	
	/* Title */	
	$page .= '<div class="subparagraph">';
	$page .= t('LOTTERY_TITLE');		
	$page .= '</div>';
	
	/* Validate */
	if ($player->lid<=$lid) {
	
		$message = t('LOTTERY_UNLOCKED', $lid);
		$page .= warquest_box_icon('locked', $message);
	
	} else {
		
		$now = date('Y-m-d H:i:s');
		
		/* Show all lotterys */
		$query  = 'select lottery_id, expire_date, bet, uid, uid_amount, bid, bid_amount, money, gold from lottery ';
		$query .= 'where expire_date > "'.$now.'" ';
		$query .= 'order by lottery_id asc';
	
		$result = warquest_db_query($query);

		$line=0;
		while ( $data=warquest_db_fetch_object($result) ) {
	
			$line++;
		
			$query2  = 'select count(pid) as total from player_lottery where lottery_id='.$data->lottery_id;
			$result2 = warquest_db_query($query2);
			$data2 = warquest_db_fetch_object($result2);
		
			$query3  = 'select count(pid) as total from player_lottery where lottery_id='.$data->lottery_id.' ';
			$query3 .= 'and pid='.$player->pid;
			$result3 = warquest_db_query($query3);
			$data3 = warquest_db_fetch_object($result3);
			
			$page .= '<div class="box" >';
		
			$page .= '<div class="right2">';
			$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&id='.$data->lottery_id.'&eid='.EVENT_LOTTERY_BET, t('LINK_BET'));
			$page .= '</div>';
						
			$page .= '<div class="subparagraph">';
			$page .= t('LOTTERY_TITLE').' '.$data->lottery_id;
			$page .= '</div>';			
			
			$page .= '<table>';
			$page .= '<tr>';
		
			$page .= '<td width="145">';			
			$page .= t('LOTTERY_BET_COST').': ';
			$page .= gold_format($data->bet);		
			$page .= '</td>';
			
			$page .= '<td width="200">';
			$page .= t('LOTTERY_BET_EXPIRE').': ';			
			$active = strtotime($data->expire_date) - time();			
			if ($active>0) {
	
				$page .= '<script language="JavaScript" src="'.$config["content_url"].'js/countdown'.$line.'.js" type="text/javascript"></script>';
				$page .= '<div class="countdown strength"><div id="countdown_time'.$line.'"></div></div>';
				$page .= '<script language="JavaScript" type="text/javascript">';
				$page .= 'countdown'.$line.'.init('.$active.', "countdown_time'.$line.'", "00:00:00");'; 
				$page .= '</script>';
			}
			$page .= '</td>';
				
			$page .= '<td width="125">';
			$page .= t('LOTTERY_CHANCE').': ';			
			
			$chance = 0;
			if ($data2->total>0) {
				$chance = ($data3->total/$data2->total)*100;
			}
			
			$page .= '<span class="health">';
			$page .= round($chance,2)."%";
			$page .= '</span>';
			$page .= '</td>';
	
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
				$page .= warquest_unit_image($unit, 1, 1, 160, 130);	
				$page .= '<br/><center>'.$data->uid_amount.'x</center>';
				$page .= '</td>';
			}
			
			if ( $data->bid>0 ) {
				
				$building = warquest_db_building($data->bid);
				
				$page .= '<td>';								
				$page .= warquest_building_image($building, 2, 1, 160, 130);	
				$page .= '<br/><center>'.$data->bid_amount.'x</center>';
				$page .= '</td>';
			}
			
			$page .= '</tr>';		
			$page .= '</table>';
			$page .= '</div>';
		}
	
		if ($line==0) {
		
			$message = t('LOTTERY_NOT_AVAILABLE');
			$page .= warquest_box_icon('info', $message);	
		}		
	}
	
	if ($player->lid>0) {
		$page .= '<div class="note">';
		$page .= t('LOTTERY_NOTE');
		$page .='</div>';
	}
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
	global $sid;
	  	
	/* Event handler */
	switch ($eid ) {
				
		case EVENT_LOTTERY_BET:	
			warquest_lottery_bet_do();
			break;
	}				
	
	switch($sid) {
		
		case PAGE_LOTTERY: 
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