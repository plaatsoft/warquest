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
** ---------------------
** SKILLS 
** ---------------------
*/

function warquest_decrease_skill_do() {
	
	/*  input */ 
	global $uid;
	global $mid;
	global $sid;
	global $config;
	global $amount;
	
	/* output */
	global $skill;
	global $player;
	global $output;
	
	$go=0;
	$max=0;
	switch ($uid) {
	
		case 1: 	$tmp = t('PLAYER_ATTACK');
					if (($skill->attack_max - (2 * $amount)) >= 3) {
						$go=1;
						$skill->attack_max -= (2 * $amount);
						$max = round(($skill->attack_max/2)-3);
					}
					break;
		
		case 2: 	$tmp = t('PLAYER_DEFENSE');
					if (($skill->defense_max - (2 * $amount)) >= 3) {
						$go=1;
						$skill->defense_max -= (2 * $amount);
						$max = round(($skill->defense_max/2)-3);
					}
					break;
					  
		case 3: 	$tmp = t('PLAYER_HEALTH');
					if (($skill->health_max - (20 * $amount)) >= 100) {
						$go=1;
						$skill->health_max -= (20 * $amount);
						$max = round(($skill->health_max-120)/20);
					}
					break;

		case 4:	$tmp = t('PLAYER_ENERGY');
					if (($skill->energy_max - (20 * $amount)) >= 100) {
						$go=1;
						$skill->energy_max -= (20 * $amount);
						$max = round(($skill->energy_max-120)/20);
					}
					break;
		
		case 5: 	$tmp = t('PLAYER_AMMO');
					if (($skill->ammo_max - $amount) >= 3) {
						$go=1;
						$skill->ammo_max -= $amount;
						$max = $skill->ammo_max-3;
					}
					break;	
						
	}
		
	if ($go==1) {
	
		$skill->skill_points += $amount;
	
		warquest_db_skill_update($skill);
	
		$message = t('PLAYER_SKILL_ACCEPTED2', $tmp);
		
		$link = warquest_link('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_HOME_SKILL_DECREASE.'&uid='.$uid,t('LINK_DECREASE'), "decrease");
		if ($max>1) {
			$link .= '<br/><br/>'.t('GENERAL_AMOUNT').'<br/>';		
			$link .= warquest_amount_selected($max);
		}
		
		$output->popup .= warquest_box_icon("info", $message, $link);
		
	} else {
	
		$message = t('PLAYER_SKILL_REJECTED2', $tmp);
		
		$link = warquest_link('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_HOME_SKILL_DECREASE.'&uid='.$uid,t('LINK_DECREASE'), "decrease");
		if ($max>1) {
			$link .= '<br/><br/>'.t('GENERAL_AMOUNT').'<br/>';		
			$link .= warquest_amount_selected($max);
		}
		
		$output->popup .= warquest_box_icon("warning", $message, $link);			
	}	
}

function warquest_increase_skill_do() {
	
	/*  input */ 
	global $uid;
	global $mid;
	global $sid;
	global $amount;
	
	/* output */
	global $skill;
	global $player;
	global $output;
	
	$max=1;

	
	if ($uid==5) {
		$points=2*$amount;
	} else {
		$points=1*$amount;
	}
	
	if ($skill->skill_points >= $points) {
	
		$tmp = "";
	
		$skill->skill_points-=$points;
	
		switch ($uid) {
	
			case 1: 	$tmp = t('PLAYER_ATTACK');
						$skill->attack_max += $amount;
						$player->attack += $amount;
						$max = $skill->skill_points;
						break;
		
			case 2: 	$tmp = t('PLAYER_DEFENSE');
						$skill->defense_max += $amount;
						$player->defense += $amount;
						$max = $skill->skill_points;
						break;
					  
			case 3: 	$tmp = t('PLAYER_HEALTH');
						$skill->health_max += (10*$amount);
						$player->health += (10*$amount);
						$max = $skill->skill_points;
						break;

			case 4:	$tmp = t('PLAYER_ENERGY');
						$skill->energy_max += (10*$amount);
						$player->energy += (10*$amount);
						$max = $skill->skill_points;
						break;
		
			case 5: 	$tmp = t('PLAYER_AMMO');
						$skill->ammo_max += $amount;
						$player->ammo += $amount;
						$max = round(($skill->skill_points-1)/2);
						break;	
		}
		
		warquest_db_skill_update($skill);
		
		$message = t('PLAYER_SKILL_ACCEPTED1', $tmp);
		
		$link = warquest_link('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_HOME_SKILL_INCREASE.'&uid='.$uid,t('LINK_INCREASE'), "increase");
		
		if ($max>0) {
			$link .= '<br/><br/>'.t('GENERAL_AMOUNT').'<br/>';		
			$link .= warquest_amount_selected($max);
		}
		
		$output->popup .= warquest_box_icon("info", $message, $link);
		
	} else {
		
		$message = t('PLAYER_SKILL_REJECTED1', $points);
		
		$link = warquest_link('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_HOME_SKILL_INCREASE.'&uid='.$uid,t('LINK_INCREASE'), "increase");
		
		if ($max>0) {
			$link .= '<br/><br/>'.t('GENERAL_AMOUNT').'<br/>';		
			$link .= warquest_amount_selected($max);
		}
		
		$output->popup .= warquest_box_icon("warning", $message, $link);		
	}	
}

function warquest_skills_form() {

	/* input */
	global $mid;
	global $sid;
	global $skill;
	global $config;
	global $player;

	/* output */ 
	global $page;
	global $output;
	
	$output->title = t('PLAYER_SKILL_SUBTITLE1');
	
	$page .= '<div class="subparagraph">'.t('PLAYER_SKILL_SUBTITLE2', $skill->skill_points).'</div>';
			
	$page .= '<div class="box">';
	
	$page .= '<table>';

	if ($player->lid>0) {
	
		/* -------------------------------------------------------------------- */
	
		$page .= '<tr>';	
		
		$page .= '<td width="50">';
		$page .= warquest_image('other/attack.png',' width="30" height="30" ');
		$page .= '</td>';
		
		$page .= '<td width="150">';
		$page .= '<b>'.t('PLAYER_ATTACK').'</b>';
		$page .= '</td>';
	
		$page .= '<td width="200">'.t('PLAYER_CURRENT').': <b>';
		$page .= strength_format(($skill->attack_max * $config['init_player_skill_step'] * $player->lid),0,",",".").'</b>';
		$page .= '</td>';
	
		$page .= '<td width="100">';
		$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_HOME_SKILL_INCREASE.'&uid=1',t('LINK_INCREASE'), "attack1");
		$page .= '</td>';
	
		$page .= '<td width="65" align="right">';
		$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_HOME_SKILL_DECREASE.'&uid=1',t('LINK_DECREASE'), "attack2");
		$page .= '</td>';
	
		$page .= '</tr>';
	
		$page .= '<tr>';
		$page .= '<td class="clear"></td>';
		$page .= '<td colspan="4" class="clear">';
		$page .= '<div class="remark">';
		$page .= t('PLAYER_ATTACK_TIP',
							number_format2($config['init_player_skill_step'] * $player->lid), 
							number_format2($config['init_player_skill_step'] * 2 * $player->lid));
		$page .= '</div>';
		$page .= '</td>';
		$page .= '</tr>';

		$page .= '<tr>';
		$page .= '<td colspan="5" class="bar"></td>';
		$page .= '</tr>';
	
		/* -------------------------------------------------------------------- */
	
		$page .= '<tr>';
	
		$page .= '<td>';
		$page .= warquest_image('other/defense.png',' width="30" height="30" ');
		$page .= '</td>';
	
		$page .= '<td><b>'.t('PLAYER_DEFENSE').'</b></td>';
		
		$page .= '<td>'.t('PLAYER_CURRENT').': <b>';
		$page .= strength_format(($skill->defense_max * $config['init_player_skill_step'] * $player->lid),0,",",".").'</b>';
		$page .='</td>';
	
		$page .= '<td>';
		$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_HOME_SKILL_INCREASE.'&uid=2', t('LINK_INCREASE'), "defense1");
		$page .= '</td>';
	
		$page .= '<td align="right">';
		$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_HOME_SKILL_DECREASE.'&uid=2', t('LINK_DECREASE'), "defense2");
		$page .= '</td>';
	
		$page .= '</tr>';
	
		$page .= '<tr>';
		$page .= '<td class="clear"> </td>';
		$page .= '<td colspan="4" class="clear">';
		$page .= '<div class="remark">';
		$page .= t('PLAYER_DEFENSE_TIP',
							number_format2($config['init_player_skill_step'] * $player->lid),
							number_format2($config['init_player_skill_step'] * 2 * $player->lid));
		$page .= '</div>';
		$page .= '</td>';
		$page .= '</tr>';
	
		$page .= '<tr>';
		$page .= '<td colspan="5" class="bar"></td>';
		$page .= '</tr>';
	}
	
	/* -------------------------------------------------------------------- */
	
	if ($player->lid>5) {
	
		$page .= '<tr>';
	
		$page .= '<td width="50">';
		$page .= warquest_image('other/health.png',' width="30" height="30" ');
		$page .= '</td>';
	
		$page .= '<td width="150"><b>'.t('PLAYER_HEALTH').'</b></td>';
	
		$page .= '<td width="200">'.t('PLAYER_CURRENT').': <b>';
		$page .= health_format($skill->health_max,0,",",".");
		$page .= '</b></td>';
	
		$page .= '<td width="100">';
		$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_HOME_SKILL_INCREASE.'&uid=3',t('LINK_INCREASE'), "health1");
		$page .= '</td>';
	
		$page .= '<td width="65" align="right">';
		$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_HOME_SKILL_DECREASE.'&uid=3',t('LINK_DECREASE'), "health2");
		$page .= '</td>';
	
		$page .= '</tr>';
	
		$page .= '<tr>';
		$page .= '<td class="clear"></td>';
		$page .= '<td colspan="4" class="clear">';
		$page .= '<div class="remark">';
		$page .= t('PLAYER_HEALTH_TIP');
		$page .= '</div>';
		$page .= '</td>';
		$page .= '</tr>';
	
		$page .= '<tr>';
		$page .= '<td colspan="5" class="bar"></td>';
		$page .= '</tr>';
	}
	
	/* -------------------------------------------------------------------- */
	
	if ($player->lid>8) {
	
		$page .= '<tr>';
	
		$page .= '<td>';
		$page .= warquest_image('other/energy.png',' width="30" height="30" ');
		$page .= '</td>';
	
		$page .= '<td><b>'.t('PLAYER_ENERGY').'</b></td>';
	
		$page .= '<td>'.t('PLAYER_CURRENT').': <b>';
		$page .= energy_format($skill->energy_max,0,",",".");
		$page .= '</b></td>';
	
		$page .= '<td>';
		$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_HOME_SKILL_INCREASE.'&uid=4',t('LINK_INCREASE') ,"energy1");
		$page .= '</td>';

		$page .= '<td align="right">';
		$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_HOME_SKILL_DECREASE.'&uid=4',t('LINK_DECREASE') ,"energy2");
		$page .= '</td>';
		
		$page .= '</tr>';
	
		$page .= '<tr>';
		$page .= '<td class="clear"></td>';
		$page .= '<td colspan="4" class="clear">';
		$page .= '<div class="remark">';
		$page .= t('PLAYER_ENERGY_TIP');
		$page .= '</div>';
		$page .= '</td>';
		$page .= '</tr>';
		
		$page .= '<tr>';
		$page .= '<td colspan="5" class="bar"></td>';
		$page .= '</tr>';
	}
		
	/* -------------------------------------------------------------------- */
	
	$page .= '<tr>';
	
	$page .= '<td>';
	$page .= warquest_image('other/ammo.png',' width="30" height="30" ');
	$page .= '</td>';
	
	$page .= '<td><b>'.t('PLAYER_AMMO').'</b></td>';
	
	$page .= '<td>'.t('PLAYER_CURRENT').': <b>';
	$page .= ammo_format($skill->ammo_max,0,",",".");
	$page .= '</b></td>';
	
	$page .= '<td>';
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_HOME_SKILL_INCREASE.'&uid=5',t('LINK_INCREASE') ,"ammo1");
	$page .= '</td>';

	$page .= '<td align="right">';
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_HOME_SKILL_DECREASE.'&uid=5',t('LINK_DECREASE') ,"ammo2");
	$page .= '</td>';
		
	$page .= '</tr>';
	
	$page .= '<tr>';
	$page .= '<td class="clear"></td>';
	$page .= '<td colspan="4" class="clear">';
	$page .= '<div class="remark">';
	$page .= t('PLAYER_AMMO_TIP');
	$page .= '</div>';
	$page .= '</td>';
	$page .= '</tr>';
	
	/* -------------------------------------------------------------------- */
	
	$page .= '</table>';	
	$page .= '</div>';
	
	$page .= '<p>';
	$page .= '<div class="note">'.t('PLAYER_SKILL_NOTE').'</div>';
	$page .=  '</p>';
}

/*
** ------------------
** HANDLER
** ------------------
*/

/**
 * Skills handler
 */
function warquest_skills_event() {
	
	/* input	*/
	global $eid;
			
	/* Event handler */
	switch ($eid) {
										
		case EVENT_HOME_SKILL_INCREASE:
			warquest_increase_skill_do();
			break;
			
		case EVENT_HOME_SKILL_DECREASE:
			warquest_decrease_skill_do();
			break;
						
	}	
}

/*
** ------------------
** THE END
** ------------------
*/


?>