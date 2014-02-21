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
** ----------
** PARAMETERS
** ----------
*/

$period1 = warquest_post('period1', '0');
$period2 = warquest_post('period2', '0');

/*
** ---------------------
** ACTIONS
** ---------------------
*/

function warquest_restore_do() {

	/* input */
	global $skill;
	global $uid;
	global $config;
	global $period1;
	global $period2;
	
	/* output */
	global $player;
	global $page;
	global $output;
			
	switch ($uid) {
	
		case 1: 	$tmp = warquest_rente( (($skill->health_max-$player->health) * 400),$player->lid, 0) * $player->lid;
					break;
				  
		case 2: 	$tmp = warquest_rente( (($skill->energy_max-$player->energy) * 200),$player->lid, 0) * $player->lid;
					break;
		
		case 3:	$tmp = warquest_rente( (($skill->ammo_max-$player->ammo) * 12000),$player->lid, 0) * $player->lid;
					break;
					
		case 4:	$tmp = $player->damage_units * $player->lid * $player->lid * 200;
					break;
					
		case 5:	$tmp = $player->damage_buildings * $player->lid * 15000;
					break;
					
		case 6:	$tmp = $player->lid * $player->lid * 20000 * $period1;
					break;
					
		case 7: 	$tmp = $player->rebel_status * $player->lid * 22000;
					break;
					
		case 8:	$tmp = $player->lid * $player->lid * 15000 * $period2;
					break;
					
		default: return;
	}
	
	if ($tmp==0) {
		return;
	}
	
	if ($player->money>=$tmp) {
	
		switch ($uid) {
		
			case 1:  $player->restore_health=date("Y-m-d H:i:s", (time() + $config["max_restore_health"]));
						$player->health = $skill->health_max;
						$message = t('PLAYER_HEALTH_RESTORED', money_format1($tmp));
						break;

			case 2:  $player->energy = $skill->energy_max;
						$player->restore_energy=date("Y-m-d H:i:s", (time() + $config["max_restore_energy"]));
						$message = t('PLAYER_ENERGY_RESTORED', money_format1($tmp));
						break;

			case 3:  $player->ammo = $skill->ammo_max;
						$player->restore_ammo=date("Y-m-d H:i:s", (time() + $config["max_restore_ammo"]));
						$message = t('PLAYER_AMMO_RESTORED', money_format1($tmp));
						break;
						
			case 4:  $player->damage_units = 0;
						$message = t('PLAYER_UNITS_REPAIRED', money_format1($tmp));
						break;
						
			case 5:  $player->damage_buildings = 0;
						$message = t('PLAYER_BUILDINGS_REPAIRED', money_format1($tmp));
						break;
						
			case 6:  $player->cease_fire_date = date("Y-m-d H:i:s", (time() + ($period1 * 60 * 60 * 24)));
						$message = t('PLAYER_CEASE_FIRE_ACTIVATED', money_format1($tmp));
						break;
						
			case 7:  $player->rebel_status = 0;
						$message = t('PLAYER_REBELLION_RESTORED', money_format1($tmp));
						break;
						
			case 8:  $player->holiday_date = date("Y-m-d H:i:s", (time() + ($period2 * 60 * 60 * 24)));
						$message = t('PLAYER_HOLIDAY_ACTIVATED', money_format1($tmp));
						break;
		}
			
		$player->money -= $tmp;		
		
		$log = 'Restore & Repair price '.number_format2($tmp);		
		warquest_user_log($player, $log);
		
		$output->popup .= warquest_box_icon("info", $message);
		
	} else {
	
		$message = t('PLAYER_RESTORED_FAILED' ,money_format1($tmp));					
		$output->popup .= warquest_box_icon("warning", $message);	
	}
}

function warquest_cease_fire_period() {

	$values = array(0.25, 0.5, 0.75, 1);

	$page ='<select id="period1" name="period1">';
	
	foreach ($values as $value) {	
		$page.='<option value="'.$value.'">'.$value.' '.t('AGO_DAY').'</option>';
	}				
		
	$page.='</select>';
	  
   return $page;
}

function warquest_holiday_period() {

	$values = array(1, 2, 3, 4, 5, 6, 7 );

	$page ='<select id="period2" name="period2">';
	
	foreach ($values as $value) {	
		$page.='<option value="'.$value.'">'.$value.' '.t('AGO_DAY').'</option>';
	}				
		
	$page.='</select>';
	  
   return $page;
}

function warquest_restore_form() {

	/* input */
	global $mid;
	global $sid;
	global $player;
	global $skill;
	global $config;
	
	/* output */
	global $page;
	global $output;
	
	$output->title = t('PLAYER_RESTORE_TITLE');
	
	$lid=1;
	if ($player->lid < $lid) {
		
		$message = '<table>';
		$message .= '<tr>';
		$message .= '<td>';
		$message .= warquest_image("other/unlock.png");
		$message .= '</td>';
		$message .= '<td>';
		$message .= t('PLAYER_RESTORE_UNLOCKED', $lid);
		$message .= '</td>';
		$message .= '</tr>';
		$message .= '</table>';
	
		$page .= warquest_box("", $message);
					
	} else {
		
		$page .= '<div class="subparagraph">'.t('PLAYER_RESTORE_SUBTITLE1').' & '.t('PLAYER_RESTORE_SUBTITLE2').'</div>';
	
		$page .= '<div class="box">';	
	
		$page .= '<table>';
	
		/* -------------------------------------------------------------------- */
		
		$tmp = warquest_rente( (($skill->health_max-$player->health) * 400),$player->lid, 0)*$player->lid;
					
		$page .= '<tr>';
		$page .= '<td width="170" >';	
		$page .= warquest_image("restore/restore1.jpg",' width="155" height="120" ');
		$page .= '</td>';
	
		$page .= '<td width="330" valign="top">';
		
		$value = strtotime($player->restore_health) - time();
		if ($value<=0) { 
			$value=0;
		}
	
		$page .= '<div class="right">';
		if ($value==0) {
		
			if (warquest_db_query_pattern($player, PATTERN_RESTORE)==0) {
				$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_HOME_RESTORE.'&uid=1', t('LINK_RESTORE'), "restore1");
			} else {
				$page .= warquest_link_confirm('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_HOME_RESTORE.'&uid=1', t('LINK_RESTORE'), t('PLAYER_HEALTH_CONFIRM'));
			}			
			
		} else {		
		
			$page .= '<script language="JavaScript" src="'.$config["content_url"].'js/countdown1.js" type="text/javascript"></script>';
	
			$page .= '<div class="countdown"><div id="countdown_time1"></div></div>';
			$page .= '<script language="JavaScript" type="text/javascript">';
			$page .= "countdown1.init(".$value.", 'countdown_time1', '00:00:00');"; 
			$page .= '</script>';
		}
		$page .= '</div>';
			
		$page .= '<div class="subparagraph"><b>'.t('PLAYER_HEALTH_TITLE').'</b></div>';
	
		$page .= '<div class="remark">';
		$page .= t('PLAYER_HEALTH_NOTE');		
		$page .= '</div>';
		$page .= '<br/>';	
		
		$page .= t('PLAYER_HEALTH_CONDITION').': '.level_format(round(($player->health / $skill->health_max)*100)).'%';
		$page .= '<br/>';
		$page .= t('PLAYER_RESTORE_PRICE').': ';
		$page .= dollar_format($tmp);			
		$page .= '</td>';
		
		$page .= '</tr>';	

		$page .= '<tr>';
		$page .= '<td colspan="2" class="bar"></td>';
		$page .= '</tr>';	
			
		/* -------------------------------------------------------------------- */

		$tmp = $player->damage_units * $player->lid * $player->lid * 200;
 		
		$page .= '<tr>';
		$page .= '<td width="170">';	
		$page .= warquest_image("restore/restore2.jpg",'  width="155" height="120" ');
		$page .= '</td>';
	
		$page .= '<td width="330" valign="top">';
	
		$page .= '<div class="right" >';	
		if (warquest_db_query_pattern($player, PATTERN_RESTORE)==0) {
			$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_HOME_RESTORE.'&uid=4', t('LINK_REPAIR'), "repair1");
		} else {
			$page .= warquest_link_confirm('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_HOME_RESTORE.'&uid=4', t('LINK_REPAIR'), t('PLAYER_UNITS_CONFIRM'));
		}
		$page .= '</div>';
		
		$page .= '<div class="subparagraph"><b>'.t('PLAYER_UNITS_TITLE').'</b></div>';
		
		$page .= '<div class="remark">';
		$page .= t('PLAYER_UNITS_NOTE');		
		$page .= '</div>';
		$page .= '<br/>';	
	
		$tmp1 = 100-$player->damage_units;
		if ($tmp1<0) {
			$tmp1=0;
		}
		$page .= t('PLAYER_UNITS_CONDITION').': '.indication_format($tmp1,1);
		$page .= '<br/>';
		$page .= t('PLAYER_REPAIR_PRICE').': ';
		$page .= dollar_format($tmp);		
	
		$page .= '</td>';
		$page .= '</tr>';	

		$page .= '<tr>';
		$page .= '<td colspan="2" class="bar"></td>';
		$page .= '</tr>';
	
		/* -------------------------------------------------------------------- */
		
		$tmp = $player->damage_buildings * $player->lid * 15000;
 		
		$page .= '<tr>';
		$page .= '<td>';	
		$page .= warquest_image("restore/restore3.jpg",'  width="155" height="120" ');
		$page .= '</td>';
	
		$page .= '<td valign="top">';
	
		$page .= '<div class="right">';
		if (warquest_db_query_pattern($player, PATTERN_RESTORE)==0) {
			$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_HOME_RESTORE.'&uid=5', t('LINK_REPAIR'), "repair2");
		} else {
			$page .= warquest_link_confirm('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_HOME_RESTORE.'&uid=5', t('LINK_REPAIR'), t('PLAYER_BUILDINGS_CONFIRM'));
		}
		$page .= '</div>';
		
		$page .= '<div class="subparagraph"><b>'.t('PLAYER_BUILDINGS_TITLE').'</b>';
		$page .= '</div>';
		
		$page .= '<div class="remark">';
		$page .= t('PLAYER_BUILDINGS_NOTE');		
		$page .= '</div>';
		$page .= '<br/>';	
		
		$tmp1 = 100-$player->damage_buildings;
		if ($tmp1<0) {
			$tmp1=0;
		}
		
		$page .= t('PLAYER_BUILDINGS_CONDITION').': '.indication_format($tmp1,1);
		$page .= '<br/>';
		$page .= t('PLAYER_REPAIR_PRICE').': ';
		$page .= dollar_format($tmp);			
		
		$page .= '</td>';
		$page .= '</tr>';	
		
		$page .= '<tr>';
		$page .= '<td colspan="2" class="bar"></td>';
		$page .= '</tr>';
		
				/* -------------------------------------------------------------------- */
	
		$tmp = $player->rebel_status * $player->lid * 22000;
 	
		$page .= '<tr>';
		$page .= '<td>';	
		$page .= warquest_image("restore/restore4.jpg",' width="155" height="120" ');
		$page .= '</td>';
	
		$page .= '<td valign="top">';
	
			
		$page .= '<div class="right">';
		if (warquest_db_query_pattern($player, PATTERN_RESTORE)==0) {
			$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_HOME_RESTORE.'&uid=7', t('LINK_RESTORE'), "restore7");
		} else {
			$page .= warquest_link_confirm('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_HOME_RESTORE.'&uid=7', t('LINK_RESTORE'), t('PLAYER_REBELLION_CONFIRM'));
		}
		$page .= '</div>';
	
		$page .= '<div class="subparagraph"><b>'.t('PLAYER_REBELLION_TITLE').'</b>';
		$page .= '</div>';
	
		$page .= '<div class="remark">';
		$page .= t('PLAYER_REBELLION_NOTE');		
		$page .= '</div>';
		$page .= '<br/>';
			
		$page .= t('PLAYER_REBELLION_CONDITION').': '.indication_format($player->rebel_status,0);
		$page .= '<br/>';
		$page .= t('PLAYER_RESTORE_PRICE').': ';
		$page .= dollar_format($tmp);		
	
		$page .= '</td>';
		$page .= '</tr>';
	
		$page .= '<tr>';
		$page .= '<td colspan="2" class="bar"></td>';
		$page .= '</tr>';
		
		/* -------------------------------------------------------------------- */
		
		$tmp = warquest_rente( (($skill->energy_max-$player->energy) * 200),$player->lid, 0)*$player->lid;
			
		$page .= '<tr>';
		$page .= '<td>';	
		$page .= warquest_image("restore/restore5.jpg",' width="155" height="120" ');
		$page .= '</td>';
	
		$page .= '<td valign="top">';
	
		$value = strtotime($player->restore_energy) - time();
		if ($value<=0) { 
			$value=0;
		}
		
		$page .= '<div class="right">';	
		if ($value==0) {
		
			if (warquest_db_query_pattern($player, PATTERN_RESTORE)==0) {
				$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_HOME_RESTORE.'&uid=2', t('LINK_RESTORE'), "restore2");
			} else {
				$page .= warquest_link_confirm('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_HOME_RESTORE.'&uid=2', t('LINK_RESTORE'), t('PLAYER_ENERGY_CONFIRM'));
			}
			
		} else {
			$page .= '<script language="JavaScript" src="'.$config["content_url"].'js/countdown2.js" type="text/javascript"></script>';
	
			$page .= '<div class="countdown"><div id="countdown_time2"></div></div>';
			$page .= '<script language="JavaScript" type="text/javascript">';
			$page .= "countdown2.init(".$value.", 'countdown_time2', '00:00:00');"; 
			$page .= '</script>';
		}
		$page .= '</div>';
		
		$page .= '<div class="subparagraph"><b>'.t('PLAYER_ENERGY_TITLE').'</b></div>';
	
		$page .= '<div class="remark">';
		$page .= t('PLAYER_ENERGY_NOTE');		
		$page .= '</div>';
		$page .= '<br/>';
		
		$page .= t('PLAYER_ENERGY_CONDITION').': '.level_format(round(($player->energy / $skill->energy_max)*100)).'%';
		$page .= '<br/>';
		$page .= t('PLAYER_RESTORE_PRICE').': ';
		$page .= dollar_format($tmp);		
	
		$page .= '</td>';
		$page .= '</tr>';

		$page .= '<tr>';
		$page .= '<td colspan="2" class="bar"></td>';
		$page .= '</tr>';
	
		/* -------------------------------------------------------------------- */
	
		$tmp = warquest_rente( (($skill->ammo_max-$player->ammo) * 12000),$player->lid, 0)*$player->lid;
 	
		$page .= '<tr>';
		$page .= '<td>';	
		$page .= warquest_image("restore/restore6.jpg",'  width="155" height="120" ');
		$page .= '</td>';
	
		$page .= '<td valign="top">';
	
		$value =  strtotime($player->restore_ammo)-time();
		if ($value<=0) { 
			$value=0;
		}
	
		$page .= '<div class="right">';
		if ($value==0) {
		
			if (warquest_db_query_pattern($player, PATTERN_RESTORE)==0) {
				$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_HOME_RESTORE.'&uid=3', t('LINK_RESTORE'), "restore3");
			} else {
				$page .= warquest_link_confirm('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_HOME_RESTORE.'&uid=3', t('LINK_RESTORE'), t('PLAYER_AMMO_CONFIRM'));
			}
			
		} else {
			$page .= '<script language="JavaScript" src="'.$config["content_url"].'js/countdown3.js" type="text/javascript"></script>';
	
			$page .= '<div class="countdown"><div id="countdown_time3"></div></div>';
			$page .= '<script language="JavaScript" type="text/javascript">';
			$page .= "countdown3.init(".$value.", 'countdown_time3', '00:00:00');"; 
			$page .= '</script>';
		}
		$page .= '</div>';
	
		$page .= '<div class="subparagraph"><b>'.t('PLAYER_AMMO_TITLE').'</b></div>';
	
		$page .= '<div class="remark">';
		$page .= t('PLAYER_AMMO_NOTE');		
		$page .= '</div>';
		$page .= '<br/>';
		
		$page .= t('PLAYER_AMMO_CONDITION').': ';
		$page .= level_format(round(($player->ammo / $skill->ammo_max)*100)).'%';
		$page .= '<br/>';
		$page .= t('PLAYER_RESTORE_PRICE').': ';
		$page .= dollar_format($tmp);		
	
		$page .= '</td>';
		$page .= '</tr>';
	
		$page .= '<tr>';
		$page .= '<td colspan="2" class="bar"></td>';
		$page .= '</tr>';
					
		/* -------------------------------------------------------------------- */
	
		$tmp = $player->lid * $player->lid * 20000;
 	
		$page .= '<tr>';
		$page .= '<td>';	
		$page .= warquest_image("restore/restore7.jpg",' width="155" height="120" ');
		$page .= '</td>';
	
		$page .= '<td valign="top">';
	
		$value = strtotime($player->cease_fire_date)-time();
		if ($value<=0) { 
			$value=0;
		}
	
		$page .= '<div class="right">';
		if ($value==0) {
		
			$value = strtotime($player->cease_fire_date) - time() + $config['max_cooldown_period'];
			if ($value>0) { 
					
				$page .= '<script language="JavaScript" src="'.$config["content_url"].'js/countdown4.js" type="text/javascript"></script>';

				$page .= t('GENERAL_INACTIVE').'<br/><div class="countdown"><div id="countdown_time4"></div></div>';
				$page .= '<script language="JavaScript" type="text/javascript">';
				$page .= "countdown4.init(".$value.", 'countdown_time4', '00:00:00');"; 
				$page .= '</script>';
				
			} else {
			
				if (warquest_db_query_pattern($player, PATTERN_RESTORE)==0) {
					$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_HOME_RESTORE.'&uid=6', t('LINK_ACTIVATE'), "restore6");
					$page .= '<br>';
					$page .= warquest_cease_fire_period();
				} else {
					$page .= warquest_link_confirm('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_HOME_RESTORE.'&uid=6', t('LINK_ACTIVATE'), t('PLAYER_CEASE_FIRE_CONFIRM'));
					$page .= '<br>';
					$page .= warquest_cease_fire_period();
				}
			}
			
		} else {
			$page .= '<script language="JavaScript" src="'.$config["content_url"].'js/countdown4.js" type="text/javascript"></script>';

			$page .= t('GENERAL_ACTIVE').'<br/><div class="countdown"><div id="countdown_time4"></div></div>';
			$page .= '<script language="JavaScript" type="text/javascript">';
			$page .= "countdown4.init(".$value.", 'countdown_time4', '00:00:00');"; 
			$page .= '</script>';
		}
		$page .= '</div>';
	
		$page .= '<div class="subparagraph"><b>'.t('PLAYER_CEASE_FIRE_TITLE').'</b></div>';
	
		$page .= '<div class="remark">';
		$page .= t('PLAYER_CEASE_FIRE_NOTE');		
		$page .= '</div>';
		$page .= '<br/>';
			
		$page .= t('PLAYER_RESTORE_PRICE_PER_DAY').': ';
		$page .= dollar_format($tmp);		
	
		$page .= '</td>';
		$page .= '</tr>';
		
		$page .= '<tr>';
		$page .= '<td colspan="2" class="bar"></td>';
		$page .= '</tr>';
	
		/* -------------------------------------------------------------------- */
	
		$tmp = $player->lid * $player->lid * 15000;
 	
		$page .= '<tr>';
		$page .= '<td>';	
		$page .= warquest_image("restore/restore8.jpg",' width="155" height="120" ');
		$page .= '</td>';
	
		$page .= '<td valign="top">';
	
		$value = strtotime($player->holiday_date)-time();
		if ($value<=0) { 
			$value=0;
		}
	
		$page .= '<div class="right">';
		
		if ($value==0) {
		
			$value = strtotime($player->holiday_date) - time() + $config['max_cooldown_period'];
			if ($value>0) { 
					
				$page .= '<script language="JavaScript" src="'.$config["content_url"].'js/countdown5.js" type="text/javascript"></script>';

				$page .= t('GENERAL_INACTIVE').'<br/><div class="countdown"><div id="countdown_time5"></div></div>';
				$page .= '<script language="JavaScript" type="text/javascript">';
				$page .= "countdown5.init(".$value.", 'countdown_time5', '00:00:00');"; 
				$page .= '</script>';
				
			} else {
			
				if (warquest_db_query_pattern($player, PATTERN_RESTORE)==0) {
					$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_HOME_RESTORE.'&uid=8', t('LINK_ACTIVATE'), "restore8");
					$page .= '<br>';
					$page .= warquest_holiday_period();
				} else {
					$page .= warquest_link_confirm('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_HOME_RESTORE.'&uid=8', t('LINK_ACTIVATE'), t('PLAYER_HOLIDAY_CONFIRM'));
					$page .= '<br>';
					$page .= warquest_holiday_period();
				}
			}
			
		} else {
		
			$page .= '<script language="JavaScript" src="'.$config["content_url"].'js/countdown5.js" type="text/javascript"></script>';

			$page .= t('GENERAL_ACTIVE').'<br/><div class="countdown"><div id="countdown_time5"></div></div>';
			$page .= '<script language="JavaScript" type="text/javascript">';
			$page .= "countdown5.init(".$value.", 'countdown_time5', '00:00:00');"; 
			$page .= '</script>';
		}

		$page .= '</div>';
	
		$page .= '<div class="subparagraph"><b>'.t('PLAYER_HOLIDAY_TITLE').'</b></div>';
	
		$page .= '<div class="remark">';
		$page .= t('PLAYER_HOLIDAY_NOTE');		
		$page .= '</div>';
		$page .= '<br/>';
		
		$page .= t('PLAYER_RESTORE_PRICE_PER_DAY').': ';
		$page .= dollar_format($tmp);		
	
		$page .= '</td>';
		$page .= '</tr>';
		
		$page .= '</table>';
		$page .= '</div>'; 
	}
}

/*
** --------------- 
** Handler
** ---------------
*/

/**
 * Restore handler
 */
function warquest_restore_event() {
	
	/* input	*/
	global $eid;
			
	/* Event handler */
	switch ($eid) {
											
		case EVENT_HOME_RESTORE:	
					warquest_restore_do();
					break;
	}	
}

/*
** ------------------
** THE END
** ------------------
*/


?>