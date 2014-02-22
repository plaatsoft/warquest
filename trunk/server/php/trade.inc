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
** ------------------
** ACTIONS
** ------------------
*/

function warquest_trade_do() {
	
	/* input */
	global $uid;
	global $mid;
	global $sid;
	global $config;
	global $skill;
	global $amount;
	
	/* output */
	global $player;
	global $output;
			
	$gold = $config["gold_trade_feature".$uid];	
	$totalGold = $amount * $gold;
							
	if ($totalGold > $player->gold) {
				
		$message = t('HOME_TRADE_NO_GOLD', gold_format($totalGold));
		$output->popup .= warquest_box_icon("warning", $message);
		
	} else if (($uid==1) && ($skill->health_timer>=$config['max_health_reduction'])) {
	
		$message = t('HOME_TRADE_HEALTH_TIMER_TO_LARGE');
		$output->popup .= warquest_box_icon("warning", $message);
		
	} else if (($uid==2) && ($skill->energy_timer>=$config['max_energy_reduction'])) {
		
		$message = t('HOME_TRADE_ENERGY_TIMER_TO_LARGE');
		$output->popup .= warquest_box_icon("warning", $message);
		
	} else if (($uid==3) && ($skill->ammo_timer>=$config['max_ammo_reduction'])) {
		
		$message = t('HOME_TRADE_AMMO_TIMER_TO_LARGE');
		$output->popup .= warquest_box_icon("warning", $message);
		
	} else {
				
		$player->gold -= $totalGold;
		warquest_gold_use($totalGold);
			
		switch ($uid) {
		
			case 1: 	$skill->health_timer += $amount;						
						$max = $config['max_health_reduction'] - $skill->health_timer; 
						break;
						
			case 2: 	$skill->energy_timer += $amount;
						$max = $config['max_energy_reduction'] - $skill->energy_timer; 
						break;
						
			case 3: 	$skill->ammo_timer += $amount;
						$max = $config['max_ammo_reduction'] - $skill->ammo_timer; 
						break;
						
			case 4:  $player->money += (10000000000 * $amount);
						$max = 10000;
						break;
						
			case 5:	$skill->skill_points += $amount;
						$max = 10000;
						break;
						
			case 6:	$time = mktime(date("H"), date("i"), date("s"), date("m"), date("d")+3, date("Y"));
						$player->premium_date =  date("Y-m-d H:i:s", $time);						
						$max = 0;
						break;
		}
		warquest_db_skill_update($skill);	
				
		$message = t('HOME_TRADE_SUCCESFULL');
	
		$link = "";
		if ($player->gold > 0) {

			if (($max*$gold )> $player->gold) {
				$max = round($player->gold / $gold)-1;
				if ($max<0) {
					$max=0;
				}
			}	
		
			$link = "";
			if ($max>0) {
				$link .= warquest_link('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_HOME_TRADE.'&uid='.$uid, t('HOME_TRADE_IN'), "trade");
				$link .= '<br/><br/>'.t('GENERAL_AMOUNT').'<br/>';		
				$link .= warquest_amount_selected($max);
			}
		}
		
		$output->popup .= warquest_box_icon("info", $message, $link);
	}
}

/*
** ------------------
** UI
** ------------------
*/

function warquest_trade_form() {

	/* input */
	global $mid;
	global $sid;
	global $config;
	global $player;
	global $skill;

	/* output */ 
	global $page;
	global $output;
	
	$output->title = t('HOME_TRADE_TITLE1');
	
	$page .= '<div class="subparagraph">'.t('HOME_TRADE_TITLE1').'</div>';
			
	$page .= '<div class="box">';
		
	$page .= '<table>';

	/* -------------------------------------------------------------------- */
	
	$page .= '<tr>';
	$page .= '<td width="170">';	
	$page .= warquest_image("gold/premium.jpg",' width="155" height="120" ');
	$page .= '</td>';
	
	$premium = strtotime($player->premium_date) - time();
	
	$page .= '<td width="330" valign="top" >';
	
	$page .= '<div class="right">';
	
	if ($premium<=0) {
		
		$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_HOME_TRADE.'&uid=6', t('HOME_TRADE_IN'), "trade6");
		
	}
	$page .= '</div>';
		
	$page .= '<div class="subparagraph">';
	$page .= '<b>'.t('HOME_TRADE6').'</b>';
	$page .= '</div>';
	
	$page .= '<div class="remark">';
	$page .= t('HOME_TRADE6_NOTE', gold_format($config["gold_trade_feature6"]));
	$page .= '</div>';
	
	$page .= '<br/>';	
		
	$page .= t('GENERAL_STATUS').': ';
	if ($premium<=0) {
	
		$page .= t('PREMIUM_NOT_ACTIVE');
		
	} else { 
		
		$page .= '<script language="JavaScript" src="'.$config["content_url"].'js/countdown1.js" type="text/javascript"></script>';
	
		$page .= t('PREMIUM_ACTIVE');
		
		$page .= '<div class="countdown"><div id="countdown_time1"></div></div>';
		$page .= '<script language="JavaScript" type="text/javascript">';
		$page .= "countdown1.init(".$premium.", 'countdown_time1', '00:00:00');"; 
		$page .= '</script>';
	}

	$page .= '</td>';
	$page .= '</tr>';	
		
	$page .= '<tr>';
	$page .= '<td colspan="2" class="bar">&nbsp;</td>';
	$page .= '</tr>';


	/* -------------------------------------------------------------------- */
	
	$page .= '<tr>';
	$page .= '<td width="170">';	
	$page .= warquest_image("trade/trade1.jpg",' width="155" height="120" ');
	$page .= '</td>';
	
	$page .= '<td width="330" valign="top" >';
	
	$page .= '<div class="right">';
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_HOME_TRADE.'&uid=1', t('HOME_TRADE_IN'), "trade1");
	$page .= '</div>';
		
	$page .= '<div class="subparagraph">';
	$page .= '<b>'.t('HOME_TRADE1').'</b>';
	$page .= '</div>';
	
	$page .= '<div class="remark">';
	$page .= t('HOME_TRADE1_NOTE', gold_format($config["gold_trade_feature1"]));
	$page .= '</div>';
	
	$page .= '<br/>';	
			
	$tmp = $config["init_health_timer"] - ($skill->health_timer * 5);	
	$page .= t('HOME_TRADE_CONDITION').': '.level_format($tmp);
	$page .= t('AGO_SECS');	
	$page .= '<br/>';

	$tmp = $config['init_health_timer']-($config['max_health_reduction']*5);
	$page .= t('HOME_TRADE_MINIMAL').': '.level_format($tmp);
	$page .= t('AGO_SECS');	
	$page .= '<br/>';
	
	$page .= '</td>';
	$page .= '</tr>';	
		
	$page .= '<tr>';
	$page .= '<td colspan="2" class="bar">&nbsp;</td>';
	$page .= '</tr>';

	/* -------------------------------------------------------------------- */
	
	$page .= '<tr>';
	$page .= '<td width="170">';	
	$page .= warquest_image("trade/trade2.jpg",' width="155" height="120" ');
	$page .= '</td>';
	
	$page .= '<td width="330" valign="top" >';
	
	$page .= '<div class="right">';
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_HOME_TRADE.'&uid=2', t('HOME_TRADE_IN'), "trade2");
	$page .= '</div>';
		
	$page .= '<div class="subparagraph">';
	$page .= '<b>'.t('HOME_TRADE2').'</b>';
	$page .= '</div>';
		
	$page .= '<div class="remark">';
	$page .= t('HOME_TRADE2_NOTE', gold_format($config["gold_trade_feature2"]));
	$page .= '</div>';
	$page .= '<br/>';	
	
	$tmp = $config["init_energy_timer"] - ($skill->energy_timer * 5); 		
	$page .= t('HOME_TRADE_CONDITION').': '.level_format($tmp);
	$page .= t('AGO_SECS');	
	$page .= '<br/>';
	
	$tmp = $config['init_energy_timer']-($config['max_energy_reduction']*5);
	$page .= t('HOME_TRADE_MINIMAL').': '.level_format($tmp);
	$page .= t('AGO_SECS');	
	$page .= '<br/>';
	
	$page .= '</td>';
	$page .= '</tr>';	
		
	$page .= '<tr>';
	$page .= '<td colspan="2" class="bar">&nbsp;</td>';
	$page .= '</tr>';

	/* -------------------------------------------------------------------- */
	
	$page .= '<tr>';
	$page .= '<td width="170">';	
	$page .= warquest_image("trade/trade3.jpg",' width="155" height="120" ');
	$page .= '</td>';
	
	$page .= '<td width="330" valign="top" >';
	
	$page .= '<div class="right">';
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_HOME_TRADE.'&uid=3', t('HOME_TRADE_IN'), "trade3");
	$page .= '</div>';
		
	$page .= '<div class="subparagraph">';
	$page .= '<b>'.t('HOME_TRADE3').'</b>';
	$page .= '</div>';
		
	$page .= '<div class="remark">';
	$page .= t('HOME_TRADE3_NOTE', gold_format($config["gold_trade_feature3"]));
	$page .= '</div>';
	$page .= '<br/>';	
	
	$tmp = $config["init_ammo_timer"] - ($skill->ammo_timer * 5);		
	$page .= t('HOME_TRADE_CONDITION').': '.level_format($tmp);	
	$page .= t('AGO_SECS');	
	$page .= '<br/>';
	
	$tmp = $config['init_ammo_timer']-($config['max_ammo_reduction']*5);
	$page .= t('HOME_TRADE_MINIMAL').': '.level_format($tmp);
	$page .= t('AGO_SECS');	
	$page .= '<br/>';
	
	$page .= '</td>';
	$page .= '</tr>';

	$page .= '<tr>';
	$page .= '<td colspan="2" class="bar">&nbsp;</td>';
	$page .= '</tr>';		
	
	/* -------------------------------------------------------------------- */
	
	$page .= '<tr>';
	$page .= '<td width="170">';	
	$page .= warquest_image("trade/trade4.jpg",' width="155" height="120" ');
	$page .= '</td>';
	
	$page .= '<td width="330" valign="top" >';
	
	$page .= '<div class="right">';
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_HOME_TRADE.'&uid=4', t('HOME_TRADE_IN'), "trade4");
	$page .= '</div>';
		
	$page .= '<div class="subparagraph">';
	$page .= '<b>'.t('HOME_TRADE4').'</b>';
	$page .= '</div>';
	
	$page .= '<div class="remark">';	
	$page .= t('HOME_TRADE4_NOTE', gold_format($config["gold_trade_feature4"]), money_format1(10000000000));
	$page .= '</div>';
	$page .= '<br/>';	
		
	$page .= t('HOME_TRADE_CONDITION').': '.dollar_format($player->money);
			
	$page .= '</td>';
	$page .= '</tr>';	
		
	$page .= '<tr>';
	$page .= '<td colspan="2" class="bar">&nbsp;</td>';
	$page .= '</tr>';
	
		/* -------------------------------------------------------------------- */
	
	$page .= '<tr>';
	$page .= '<td width="170">';	
	$page .= warquest_image("trade/trade5.jpg",' width="155" height="120" ');
	$page .= '</td>';
	
	$page .= '<td width="330" valign="top" >';
	
	$page .= '<div class="right">';
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_HOME_TRADE.'&uid=5', t('HOME_TRADE_IN'), "trade5");
	$page .= '</div>';
		
	$page .= '<div class="subparagraph">';
	$page .= '<b>'.t('HOME_TRADE5').'</b>';
	$page .= '</div>';
	
	$page .= '<div class="remark">';	
	$page .= t('HOME_TRADE5_NOTE', gold_format($config["gold_trade_feature5"]));
	$page .= '</div>';
	$page .= '<br/>';	
	$page .= t('HOME_TRADE_CONDITION').': '.level_format($skill->skill_points).' '.t('HOME_TRADE_SKILL_POINTS');
		
	$page .= '</td>';
	$page .= '</tr>';
					
	/* -------------------------------------------------------------------- */
	
	$page .= '</table>';	
	$page .= '</div>';
	
	$page .= '<p>';
	$page .= '<div class="note">'.t('HOME_TRADE_NOTE').'</div>';
	$page .=  '</p>';
}

/*
** ------------------
** HANDLER
** ------------------
*/

function warquest_trade_event() {
	
	/* input	*/
	global $eid;
				
	switch ($eid) {
										
		case EVENT_HOME_TRADE:
				warquest_trade_do();
				break;					
	}	
}

/*
** ------------
** THE END
** ------------
*/

?>