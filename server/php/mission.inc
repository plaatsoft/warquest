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
**  All copyrights reserved (c) PlaatSoft
*/

/*
** ---------------------------------------------------------------- 
** MISSIONS 
** ---------------------------------------------------------------- 
*/

/*
** -----------
** SUPPORT
** -----------
*/

/** 
 *  Detect all clan missions of a planet are complete!
 */
function warquest_mission_clan_planet_complet() {

	/* input */
	global $player;

	/* output */
	global $output;
	global $player;
		 
	/* Get player clan data */
	$player_clan = warquest_db_player_clan($player->pid);
	
	/* Check if all missions are played on active planet */
	$query  = 'select sum(progress) as progress from clan_mission a left join mission b on a.mid=b.mid ';
	$query .= 'left join mission_group c on c.mgid=b.mgid ';
	$query .= 'where a.cid='.$player_clan->cid.' and c.planet='.$player->planet;
		
	$result = warquest_db_query($query);	
	$data = warquest_db_fetch_object($result);
					
	if ($data->progress>=7200) {
	
		/* update clan money */
		$bonus = $player->planet * $player->planet * $player->planet * 2000000000000;		
		
		$clan = warquest_db_clan($player_clan->cid);		
		
		$clan->money += $bonus;
		$clan->last_activity = date('Y-m-d H:i:s');
		
		warquest_db_clan_update($clan);
				
		warquest_db_clan_bank_insert($clan->cid, $player->planet, $bonus, $clan->money, 11);		
	
		/* Log system event */					
		$log = 'Clan receive planet bonus of '.$bonus.' dollar.';		
		warquest_user_log($player, $log);
		
		/* Clear all related clan missions */		
		$query  = 'select a.mid, a.cid from clan_mission a, mission b, mission_group c where ';
		$query .= 'a.mid=b.mid and b.mgid=c.mgid and a.cid='.$player_clan->cid.' and c.planet='.$player->planet;
		$result = warquest_db_query($query);	
		
		while ($data = warquest_db_fetch_object($result)) {
		
			warquest_db_clan_mission_delete($data->cid, $data->mid);
		}

		/* Show message on screen */
		if ($output->format=="html") {
				
			$message = '<table>';
			$message .= '<tr>';
			$message .= '<td width="200">';
			$message .= warquest_image("other/bonus.jpg", ' width="170" height="120" ');
			$message .= '</td>';
			$message .= '<td>';
			$message .= t('MISSION_CLAN_PLANET_COMPLETE',t('GENERAL_PLANET_'.$player->planet), money_format1($bonus));
			$message .= '</td>';
			$message .= '</tr>';
			$message .= '</table>';
			
			/* Play sound */			
			warquest_sound('mission1.mp3');
					
		} else {
				
			$message = t('MISSION_COMPLETE_PLANET_'.$player->planet);
		}
						
		$output->popup .= warquest_box("info", $message);
	}
}

/** 
 *  Detect all player missions of a planet are complete!
 */
function warquest_mission_planet_complet() {

	/* input */
	global $player;

	/* output */
	global $output;
	global $player;
		 
	if ( warquest_db_bonus($player->pid, $player->planet)==0) {

		/* Check if all missions are played on active planet */
		$query  = 'select sum(a.part2) as part2 from player_mission a left join mission b on a.mid=b.mid ';
		$query .= 'left join mission_group c on c.mgid=b.mgid ';
		$query .= 'where a.pid='.$player->pid.' and c.planet='.$player->planet;
		
		$result = warquest_db_query($query);	
		$data = warquest_db_fetch_object($result);
					
		if ($data->part2==216) {
				 
			/* Only if insert is successfull, add bonus to players account */
			if ( warquest_db_bonus($player->pid, $player->planet)==0 ) {
				
				warquest_db_bonus_insert($player->pid, $player->planet);
			
				switch ($player->planet) {
				
					case PLANET_EARTH:	
								$player->money += 100000000;
								break;
							
					case PLANET_MOON:	
								$player->money += 500000000;
								break;
							
					case PLANET_MARS:
								$player->money += 999000000000;
								break;
							
					case PLANET_MERCURY:	
								$player->gold += 2500;
								break;
								
					case PLANET_NEPTUNE:	
								$player->gold += 5000;
								break;
				}

				/* Log system event */					
				$log = 'Player receive all mission complete planet bonus!';		
				warquest_user_log($player, $log);
				
				if ($output->format=="html") {
				
					$message = '<table>';
					$message .= '<tr>';
					$message .= '<td width="200">';
					$message .= warquest_image("other/bonus.jpg", ' width="170" height="120" ');
					$message .= '</td>';
					$message .= '<td>';
					$message .= t('MISSION_COMPLETE_PLANET_'.$player->planet);
					$message .= '</td>';
					$message .= '</tr>';
					$message .= '</table>';
					
					/* Play sound */			
					warquest_sound('mission1.mp3');
					
				} else {
				
					$message = t('MISSION_COMPLETE_PLANET_'.$player->planet);
				}
						
				$output->popup .= warquest_box("info", $message);					
			}
		}		
	}
}

/** 
 *  Detect if all player missions of a continent are complete. 
 */
function warquest_mission_continent_complet() {

	/* input */
	global $id;
	global $config;
	
	/* output */
	global $player;
	global $skill;		
	global $output;
			 
	$player_mission = warquest_db_player_mission($player->pid, $id);
	$part = $player_mission->part2+1;
	
	$mission = warquest_db_mission($id);
	
	$query  = 'select sum(progress) as progress from player_mission a, ';
	$query .= 'mission b where a.mid=b.mid and a.pid='.$player->pid.' and b.mgid='.$mission->mgid;
	$result = warquest_db_query($query);	
	$data = warquest_db_fetch_object($result);
	
	/* Detect if all continent mission parts are 100% complete */
	if (($part*800)==$data->progress) {
		
		/* calculate skill points bonus. */
		$bonus = warquest_format_part($part)+2;
			
		/* Update skill points */
		$skill->skill_points += $bonus;
		warquest_db_skill_update($skill);
				
		/* Restore energy. */
		$player->energy=$skill->energy_max;	

		/* Clear progress state for all eight missions. */
		$query  = 'update player_mission a, mission b set a.part='.$part.', a.part2='.$part.' where '; 
		$query .= 'a.mid=b.mid and a.pid='.$player->pid.' and b.mgid='.$mission->mgid;
		warquest_db_query($query);		
						 
		$message  = t('MISSION_CONTINTENT_READY1', 
							warquest_format_part($part-1), 
							$config["max_mission_part"], 
							t('MISSION_GROUP_'.$mission->mgid));
									
		$message .= t('MISSION_CONTINTENT_READY2', $bonus);
				
		if (warquest_format_part($part) == $config["max_mission_part"]) {
			$message .= t('MISSION_CONTINTENT_READY3');
		} else {				
			$message .= t('MISSION_CONTINTENT_READY4', warquest_format_part($part));
		}				
		$message .= '<br/><br/>';
		
		for ($tmp=0; $tmp<$bonus; $tmp++) {
			$message .= warquest_image('other/star.gif', ' width="60" height="60" ');
		}
		
		$message .= '<br/><br/>';		
		$message .= t('MISSION_COMPLETE_TEXT');
		$message .= warquest_ui_map($player, $player->planet);
		$message .= '<br/>'; 
		
		$link = warquest_link('mid='.MENU_HOME.'&sid='.PAGE_SKILLS, t('LINK_SP') ,'skillpoints');
		$output->popup .= warquest_box("info", $message, $link);
		
		/* Play sound */			
		warquest_sound('mission2.mp3');	
	} 
}

/**
 * Mission unit lost detection
 */
function warquest_mission_unit_lost() {

   /* input */
	global $id;
	global $level;
	
	/* output */
	global $player;
	global $output;

	if ($level->unit_lost==0) {
	
		/* Unit lost disabled for this level. */
	   return;
	}

	/* Update mission damage */
	$maintenance = warquest_db_maintenance($player, $player->planet);	
	$player->damage_units += round(((100-$maintenance)/100) * rand(1,10));
		

	if ($player->damage_units<100) {
		/* Check if units damage is less then 100% then return */	
		return;
	}
	$player->damage_units = 0;
	
	/* get strongest attack unit */
	$query  = 'select a.uid, c.gold, c.defense, c.attack, a.amount, c.upkeep ';
	$query .= 'from mission_unit a LEFT JOIN unit c ' ;
	$query .= 'ON a.uid=c.uid left join player_unit b ';
	$query .= 'ON a.uid=b.uid and b.pid='.$player->pid.' where a.mid='.$id;
		
	$result = warquest_db_query($query);
	
	if ($output->format=="html") {
	 
		$message  = '<br/><span class="warning">'.t('MISSION_UNITS_LOST').':</span><br/>'; 
		$message .= '<table>';
		$message .= '<tr>';
		
	} else {
	
		$message = t('MISSION_UNITS_LOST').': ';
	}
	
	$count=1000;	
	while ($data = warquest_db_fetch_object($result)) {
		
		$amount=rand(1,round($data->amount/10));
			
		/* Update database */
		warquest_db_unit_delete($player->pid, $data->uid, $amount );
			
		if ($output->format=="html") {
			$message .= '<td width="90">';
			$message .= warquest_unit_image($data, $count++);		
			$message .= '<br/><center>'.$amount.'x</center>';
			$message .= '<td>';
				
		} else {
			
			$message .= $amount.' '.t('UNIT_'.$data->uid).' ';
		}
	}
		
	if ($output->format=="html") {
		$message .= '</tr>';
		$message .= '</table>';
		
	} else {
	
		$message .= '. ';
	}
		
	return $message;
}

/*
** -----------
** ACTIONS
** -----------
*/

/** 
 * Buy mission units
 */
function warquest_buy_missing_units_do() {
	
	/* input */
	global $id;
	
	/* output */
	global $player;
	global $output;

	$query  = 'select a.uid, c.gold, c.price, c.upkeep, ifnull(b.amount,0) as amount, ';
	$query .= 'a.amount-ifnull(b.amount,0) as total ';
	$query .= 'from mission_unit a LEFT JOIN unit c ' ;
	$query .= 'ON a.uid = c.uid left join player_unit b ';
	$query .= 'ON a.uid=b.uid and b.pid='.$player->pid.' where a.mid='.$id.' ';
	$query .= 'and a.amount-ifnull(b.amount,0)>0';
	$result = warquest_db_query($query); 
	
	while ($unit=warquest_db_fetch_object($result)) {
	 							
		$money = $unit->price * $unit->total;			
		$upkeep = $unit->upkeep * $unit->total;
		
		if ($money > $player->money) {

			/* No money enough, return message */			
			$message = '<table>';
			$message .= '<tr>';
			$message .= '<td width="100">';
			$message .= warquest_unit_image($unit,0,0);
			$message .= '</td>';
			$message .= '<td>';
			$message .= t('UNIT_NO_FUNDS', $unit->total, t('UNIT_'.$unit->uid), dollar_format($money));
			$message .= '</td>';
			$message .= '</tr>';
			$message .= '</table>';
	
			$output->popup .= warquest_box("warning", $message);
		
		} else if ($upkeep > $player->money_step) {
		
			/* No upkeep enough, return message */
		
			$message = '<table>';
			$message .= '<tr>';
			$message .= '<td width="100">';
			$message .= warquest_unit_image($unit,0,0);
			$message .= '</td>';
			$message .= '<td>';
			$message .= t('UNIT_NO_UPKEEP',$unit->total, t('UNIT_'.$unit->uid));
			$message .= '</td>';
			$message .= '</tr>';
			$message .= '</table>';
	
			$output->popup .= warquest_box("warning", $message);
		
		} else {
		
			/* Buy missing units */
			$player->money -= $money;
			
			/* Update database */
			warquest_db_unit_add($player->pid, $unit->uid, $unit->total);
			
			/* Log system event */
			$log = 'Buy missing units for mission '.number_format2($money);		
			warquest_user_log($player, $log);
				
			/* Update income value */
			warquest_netto_income($player);	
		}
	}
}

/** 
 * Do clan mission 
 */ 
function warquest_mission_clan_do() {

	/* input */
	global $mid;
	global $sid;	
	global $ssid;	
	global $id;
	
	/* output */
	global $player;
	global $output;

	/* Get mission data */
	$mission = warquest_db_mission($id);
	
	/* Get player clan data */
	$player_clan = warquest_db_player_clan($player->pid);
	
	if ( !isset($player_clan->cid) || ($player_clan->approved==0)) { 
	
		$message = t('MISSION_NO_CLAN');
		$output->popup .= warquest_box_icon("warning", $message);
		return;
	}
		
	/* Get progress data */	
	$progress = 0;	
	$data = warquest_db_clan_mission($player_clan->cid, $id);
	if ( isset($data->cid) ) {
		$progress = $data->progress;
	}
	
	/* Check for missing units */
	$query  = 'select a.uid, c.price, c.upkeep, c.attack, c.defense, a.amount-ifnull(b.amount,0) ';
	$query .= 'as total from mission_unit a LEFT JOIN unit c ' ;
	$query .= 'ON a.uid = c.uid left join player_unit b ';
	$query .= 'ON a.uid=b.uid and b.pid='.$player->pid.' where a.mid='.$id.' ';
	$query .= 'and a.amount-ifnull(b.amount,0)>0';
	$result2 = warquest_db_query($query);
	
	$count=0;
	
	if (warquest_db_num_rows($result2)>0) {
		
		$total=0;
		$upkeep=0;
		
		$message  = '<span class="warning">'.t('MISSION_ABORTED').'</span> <br/>';
		$message .= t('MISSION_MISSING_UNITS').'<br/><br/>';
	
		if ($output->format=="html") {
		
			$message .= '<table>';
			$message .= '<tr>';
		}
		
		while ($unit=warquest_db_fetch_object($result2)) {
		
			if ($output->format=="html") {
			
				$message .= '<td>';
				$message .= warquest_unit_image($unit, $count++);		
				$message .= '<br/><center>'.$unit->total.'x</center>';
				$message .= '</td>';					
				
			} else {
			
				$message .= $unit->total.' '.t("UNIT_".$unit->uid).' ';
			}
			
			$total += $unit->price * $unit->total;
			$upkeep += $unit->upkeep * $unit->total;
		}		
		
		if ($output->format=="html") {
			$message .= '</tr>';
			$message .= '</table>';
			
		} else {
		
			$message .= '. ';
		}
		
		$message .= '<br/>';
		$message .= t('MISSION_MISSING_UNITS_PRICE',money_format2($total), money_format2($upkeep));

		$link = warquest_image('bar/bar'.$progress.'.png').'<br/>';		
		$link .= warquest_link('mid='.$mid.'&sid='.$sid.'&ssid='.$ssid.'&id='.$id.'&eid='.EVENT_MISSION_CLAN_BUY_PLAY, t('LINK_BUY_PLAY'), 'buyplay');
	
		$output->popup .= warquest_box(t('GENERAL_CONQUER').' '.t('MISSION_'.$id), $message, $link);
		
	} else if ($player->energy < $mission->energy) {

		$message = '<span class="warning">'.t('MISSION_ABORTED').'</span><br/>';
		$message .= t('MISSION_NO_ENERGY');
				
		$link  = warquest_image('bar/bar'.$progress.'.png').'<br/>';
		$link .= warquest_link('mid='.$mid.'&sid='.$sid.'&ssid='.$ssid.'&id='.$id.'&eid='.EVENT_MISSION_CLAN_PLAY, t('LINK_DO_AGAIN'),'doagain');		
		
		$output->popup .= warquest_box(t('GENERAL_CONQUER').' '.t('MISSION_'.$id), $message, $link);
		
	} else if ($player->alliance < $mission->alliance) {
	
		$message = '<span class="warning">'.t('MISSION_ABORTED').'</span><br/>';
		$message .= t('MISSION_LOW_ALLIANCE');
				
		$output->popup .= warquest_box(t('GENERAL_CONQUER').' '.t('MISSION_'.$id), $message);
		
	} else {
			 
		/* Update player */
		$player->energy -= $mission->energy;
		
		$premium = strtotime($player->premium_date) - time();
		if ($premium>0) {
			$mission->experience *= 2;
		}
	
		$player->experience += $mission->experience;
		$player->mission++;
		
		$money = rand($mission->min_price,$mission->max_price);
		if ($premium>0) {
			$money *= 3;
		}
			
		if ($progress>=100) {
		
			/* If progress is 100% double money */		
			$money *= 2;
			$progress = 100;
			
		} else {		
	
			$progress+=5;
		}
				
		$player->money += $money;
		
		/* Log system event */
		$log = 'Clan mission bonus '.number_format2($money);		
		warquest_user_log($player, $log);
				
		/* Update clan mission progress */
		warquest_db_clan_mission_update($player_clan->cid, $id, $progress);	
		
		/* update clan statistics */
		$clan = warquest_db_clan($player_clan->cid);
		$clan->mission++;
		$clan->last_activity = date('Y-m-d H:i:s');
		warquest_db_clan_update($clan);
		
		/* Check if all clan missions of a planet are complete */
		warquest_mission_clan_planet_complet();
		
		/* Check next level of player */
		warquest_nextlevel($player);
	 
		/* Check if mission award is won */
		warquest_mission_award_won($player);
		
		$message = t('MISSION_YOU_GAIN').': '.money_format1($money).t('MISSION_DOLLAR_AND');
		$message .= experience_format($mission->experience).' '.t('GENERAL_EXPERIENCE_POINTS').'. <br/>';
		$message .= t('MISSION_YOU_USED').': '.energy_format($mission->energy).' '.t('GENERAL_ENERGY').'. <br/>';
		
		if ($output->format=="xml") {
			$message .= 'Mission progress: '.$progress.'% ';
		}
		
		$message .= warquest_mission_unit_lost();
		
		if ($mission->loot==1) {
			$message .= warquest_lootoption($mission->lid);
		}
			
		$link  = warquest_image('bar/bar'.$progress.'.png').'<br/>';	
		$link .= warquest_link('mid='.$mid.'&sid='.$sid.'&ssid='.$ssid.'&eid='.EVENT_MISSION_CLAN_PLAY.'&id='.$id, t('LINK_DO_AGAIN'), "doagain");
		
		$output->result = true;
		$output->popup .= warquest_box(t('GENERAL_CONQUER').' '.t('MISSION_'.$id), $message, $link);		
	}
}

/** 
 * Do Player Mission 
 */ 
function warquest_mission_do() {

	/* input */
	global $mid;
	global $sid;	
	global $ssid;	
	global $id;
	global $config;
	
	/* output */
	global $player;
	global $output;

	/* Get mission data */
	$mission = warquest_db_mission($id);
	
	/* Get progress data */	
	$progress = 0;
	$part = 0;
	$part2 = 0;
	
	$data = warquest_db_player_mission($player->pid, $id);

	if ( isset($data->pid) ) {
		$progress = $data->progress;
		$part = $data->part;
		$part2 = $data->part2;
	}
	
	/* Check for missing units */
	$query  = 'select a.uid, c.price, c.upkeep, c.attack, c.defense, a.amount-ifnull(b.amount,0) ';
	$query .= 'as total from mission_unit a LEFT JOIN unit c ' ;
	$query .= 'ON a.uid = c.uid left join player_unit b ';
	$query .= 'ON a.uid=b.uid and b.pid='.$player->pid.' where a.mid='.$id.' ';
	$query .= 'and a.amount-ifnull(b.amount,0)>0';
	$result2 = warquest_db_query($query);
	
	$count=0;
	
	if (warquest_db_num_rows($result2)>0) {
		
		$total=0;
		$upkeep=0;
		
		$message  = '<span class="warning">'.t('MISSION_ABORTED').'</span> <br/>';
		$message .= t('MISSION_MISSING_UNITS').'<br/><br/>';
	
		if ($output->format=="html") {
		
			$message .= '<table>';
			$message .= '<tr>';
		}
		
		while ($unit=warquest_db_fetch_object($result2)) {
		
			if ($output->format=="html") {
			
				$message .= '<td>';
				$message .= warquest_unit_image($unit, $count++);		
				$message .= '<br/><center>'.$unit->total.'x</center>';
				$message .= '</td>';					
				
			} else {
			
				$message .= $unit->total.' '.t("UNIT_".$unit->uid).' ';
			}
			
			$total += $unit->price * $unit->total;
			$upkeep += $unit->upkeep * $unit->total;
		}		
		
		if ($output->format=="html") {
			$message .= '</tr>';
			$message .= '</table>';
			
		} else {
		
			$message .= '. ';
		}
		
		$message .= '<br/>';
		$message .= t('MISSION_MISSING_UNITS_PRICE',money_format2($total), money_format2($upkeep));

		$link = warquest_image('bar/bar'.warquest_format_progress($progress, $part).'.png').'<br/>';		
		$max = $config['max_mission_part'];
		if ($player->lid==0) {
			$max=1;
		}		
		$link .= t('MISSION_PART').' '.warquest_format_part($part).'/'.$max.'<br/>';
		$link .= warquest_link('mid='.$mid.'&sid='.$sid.'&ssid='.$ssid.'&id='.$id.'&eid='.EVENT_MISSION_BUY_PLAY, t('LINK_BUY_PLAY'), 'buyplay');
	
		$output->popup .= warquest_box(t('GENERAL_CONQUER').' '.t('MISSION_'.$id), $message, $link);
		
	} else if ($player->energy < $mission->energy) {

		$message = '<span class="warning">'.t('MISSION_ABORTED').'</span><br/>';
		$message .= t('MISSION_NO_ENERGY');
				
		$link  = warquest_image('bar/bar'.warquest_format_progress($progress, $part).'.png').'<br/>';		
		$max = $config['max_mission_part'];
		if ($player->lid==0) {
			$max=1;
		}		
		$link .= t('MISSION_PART').' '.warquest_format_part($part).'/'.$max.'<br/>';
		$link .= warquest_link('mid='.$mid.'&sid='.$sid.'&ssid='.$ssid.'&eid='.EVENT_MISSION_PLAY.'&id='.$id, t('LINK_DO_AGAIN'),'doagain');		
		
		$output->popup .= warquest_box(t('GENERAL_CONQUER').' '.t('MISSION_'.$id), $message, $link);
		
	} else if ($player->alliance < $mission->alliance) {
	
		$message = '<span class="warning">'.t('MISSION_ABORTED').'</span><br/>';
		$message .= t('MISSION_LOW_ALLIANCE');
				
		$output->popup .= warquest_box(t('GENERAL_CONQUER').' '.t('MISSION_'.$id), $message);
		
	} else {
			 
		/* Update player */
		$player->energy -= $mission->energy;
		
		$premium = strtotime($player->premium_date) - time();
		if ($premium>0) {
			$mission->experience *= 2;
		}
	
		$player->experience += $mission->experience;
		$player->mission += 1;
		
		$money = rand($mission->min_price,$mission->max_price);
		if ($premium>0) {
			$money *= 3;
		}
			
		/* If progress is 100% double money */				
		if (warquest_format_progress($progress, $part)==100) {
		
			$money *= 2;
			
		} else {
				
			if (warquest_format_progress($progress, $part)==90) { 
			
				$progress+=10;	
				$money *= 2;
					
			} else {
			
				$progress+=15;
			}
		} 
		
		$player->money += $money;
		
		/* Log system event */
		$log = 'Mission play bonus '.number_format2($money);		
		warquest_user_log($player, $log);
				
		/* Rebel restore action */
		if ((warquest_format_progress($progress,$part)==100) && ($part!=$part2)) {
		
			$part++;
		} 
		
		/* Update database */
		warquest_db_player_mission_update($player->pid, $id, $progress, $part, $part2);	
		
		/* Check if all missions of a continent are complete */
		warquest_mission_continent_complet();
		
		/* Check if all missions of a planet are complete */
		warquest_mission_planet_complet();

		/* Check if mission award is won */
		warquest_mission_award_won($player);
		
		/* Update income value */
		warquest_netto_income($player);		
		
		$next = warquest_nextlevel($player);
	 
		if (($next==1) && ($player->lid==1)) {
			
			/* If training mission is complet, skip mission complet message. */
		   $ssid = 1;
			
		} else {
			
			$message = t('MISSION_YOU_GAIN').': '.money_format1($money).t('MISSION_DOLLAR_AND');
			$message .= experience_format($mission->experience).' '.t('GENERAL_EXPERIENCE_POINTS').'. <br/>';
			$message .= t('MISSION_YOU_USED').': '.energy_format($mission->energy).' '.t('GENERAL_ENERGY').'. <br/>';
			
			if ($output->format=="xml") {
				$message .= 'Mission progress: '.warquest_format_progress($progress, $part).'%. ';
			}
		
			$message .= warquest_mission_unit_lost();
			
			if ($mission->loot==1) {
				$message .= warquest_lootoption($mission->lid);
			}
			
			$link  = warquest_image('bar/bar'.warquest_format_progress($progress, $part).'.png').'<br/>';
			
			$max = $config['max_mission_part'];
			if ($player->lid==0) {
				$max=1;
			}		
			$link .= t('MISSION_PART').' '.warquest_format_part($part).'/'.$max.'<br/>';
			$link .= warquest_link('mid='.$mid.'&sid='.$sid.'&ssid='.$ssid.'&eid='.EVENT_MISSION_PLAY.'&id='.$id, t('LINK_DO_AGAIN'), "doagain");

			$output->result = true;
			$output->popup .= warquest_box(t('GENERAL_CONQUER').' '.t('MISSION_'.$id), $message, $link);
		} 
	}
}

/*
** -----------
** FORMS
** -----------
*/

function warquest_mission_clan_form() {

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
		
	$player_clan = warquest_db_player_clan($player->pid);
		
	$output->title = t('MISSION_GROUP_'.$ssid);
	
	/* Show title */	
	$page .= '<div class="subparagraph">';
	$page .= t('MISSION_CLAN_TITLE');		
	$page .= '</div>';
	
	/* Validate */
	if ( !isset($player_clan->cid) || ($player_clan->approved==0)) { 
	
		$message = t('MISSION_NO_CLAN');
		$page .= warquest_box_icon("warning", $message);
				
	} else {
			
		/* Get clan mission data */
		$query  = "select a.mid, a.loot, a.min_price, a.max_price, a.energy, ";
		$query .= "a.experience, a.alliance, ifnull(b.progress, 0) as progress ";
		$query .= "from mission a ";
		$query .= "left join clan_mission b on a.mid=b.mid and b.cid=".$player_clan->cid." ";
		$query .= 'where a.mgid='.$ssid.' and a.lid<='.$player->lid.' ';  
		$query .= 'order by a.lid asc';
	
		$result = warquest_db_query($query);

		$line=0;
		
		/* Show unlocked clan missions */
		while ( $data=warquest_db_fetch_object($result) ) {
	
			$line++;
		
			$page .= '<div class="box" id="'.$data->mid.'">';
			$page .= '<table>';
			$page .= '<tr>';	
			$page .= '<td colspan="3"><span class="paragraph">'.t('GENERAL_CONQUER').' '.t('MISSION_'.$data->mid).'</span>';

			$page .= '<br/>';
			$page .= '<b>'.t('MISSION_GAIN').':</b><br/>';
			$page .= money_format1($data->min_price).' - ';
			$page .= dollar_format($data->max_price).'<br/>';
			$page .= experience_format($data->experience).' '.t('GENERAL_EXPERIENCE').'<br/>';
			if ($data->loot==1) {
				$page .= '<span class="loot">'.t('MISSION_CHANCE_LOOT').'</span><br/>';
			}			
			$page .= '<br/>';
			$page .= '</td>';
			
			$page .= '<td  width="100" align="right" valign="top">';		
			$page .= warquest_image('bar/bar'.$data->progress.'.png').'<br/>';
		
			$max = $config['max_mission_part'];
			if ($player->lid==0) {
				$max=1;
			}
			$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&ssid='.$ssid.'&eid='.EVENT_MISSION_CLAN_PLAY.'&id='.$data->mid,t('LINK_PLAY'),'play'.$line);
			$page .= '</td>';
		
			$page .= '</tr>';

			$page .= '<tr>';
		
			$page .= '<td valign="top" width="240">';
			$page .= '<b>'.t('MISSION_REQUIRED').':</b><br/>';
			$page .= energy_format($data->energy).' '.t('GENERAL_ENERGY').'<br/>';
			$page .= alliance_format($data->alliance).' '.t('GENERAL_ALLIANCE_SIZE');
			$page .= '</td>';
		
			$query2  = 'select b.uid, b.gold, a.amount, b.attack, b.defense, b.upkeep from mission_unit a, ';
			$query2 .= 'unit b where b.uid=a.uid and mid='.$data->mid;  
			$result2 = warquest_db_query($query2); 
		
			$count=0;
			while ($data2 = warquest_db_fetch_object($result2)) {
		
				$count++;
				$page .= '<td align="right" width="100">';   
				$page .= warquest_unit_image($data2, $line);	
				$page .= '<br/><center>'.$data2->amount.'x</center>';
				$page .= '</td>';
			}
			
			/* fill up table */
			for ($tmp=0; $tmp<(3-$count); $tmp++) {
				$page .= '<td align="right" width="100">&nbsp;</td>';
			}
			$page .= '</tr>';
		
			$page .= '</table>';
			$page .= '</div>';
		}

		/* Show next lock clan mission */	
		$query  = 'select mid, lid, loot, min_price, max_price, energy, experience, alliance ';
		$query .= 'from mission where mgid='.$ssid.' and lid>'.$player->lid.' ';
		$query .= 'order by lid asc limit 0,1';
		$result = warquest_db_query($query);
 
		if ($data=warquest_db_fetch_object($result)) {
		
			$line++;
		
			$page .= '<div class="box">';
			$page .= '<table>';
		
			$page .= '<tr>';	
			$page .= '<td colspan="3" >';
			$page .= '<span class="paragraph">'.t('GENERAL_CONQUER').' '.t('MISSION_'.$data->mid).'</span><br/>';
		
			$page .= '<b>'.t('MISSION_GAIN').':</b><br/>';
			$page .= money_format1($data->min_price).' - ';
			$page .= dollar_format($data->max_price).'<br/>';
			$page .= experience_format($data->experience).' '.t('GENERAL_EXPERIENCE').'<br/>';
			if ($data->loot==1) {
				$page .= '<span class="loot">'.t('MISSION_CHANCE_LOOT').'</span><br/>';
			}
			$page .= '<br/></td>';
				
			$page .= '<td  width="100" align="right" valign="top">';
			$page .= t('GENERAL_UNLOCK', $data->lid);
			$page .= '</td>';
		
			$page .= '</tr>';

			$page .= '<tr>';
		
			$page .= '<td valign="top" width="240">';
			$page .= '<b>'.t('MISSION_REQUIRED').':</b><br/>';
			$page .= energy_format($data->energy).' '.t('GENERAL_ENERGY').'<br/>';
			$page .= alliance_format($data->alliance).' '.t('GENERAL_ALLIANCE_SIZE');
			$page .= '</td>';
		
			for ($tmp=0; $tmp<3; $tmp++) {
				$page .= '<td width="100">';
				$page .= warquest_image('other/unlock.png');
				$page .= '</td>';
			}
			
			$page .= '</tr>';	
		
			$page .= '</table>';
			$page .= '</div>';
		}
		
		if ($line==0) {
		
			$message = t('MISSION_NO_MISSIONS');
			$page .= warquest_box_icon('info', $message);	
		}		
	}
	
	if ($player->lid>0) {
	
		$page .= '<div class="note">';
		$bonus = $player->planet * $player->planet * $player->planet * 2000000000000;		
		$page .= t('MISSION_CLAN_NOTE', t('GENERAL_PLANET_'.$player->planet), money_format1($bonus));
		$page .='</div>';
	}
}

function warquest_mission_player_form() {

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
		
	$output->title = t('MISSION_GROUP_'.$ssid);
	
	/* Title */	
	$page .= '<div class="subparagraph">';
	$page .= t('MISSION_PLAYER_TITLE');		
	$page .= '</div>';
				
	/* Show all unlocked player missions */
	$query  = "select a.mid, a.loot, a.min_price, a.max_price, a.energy, ";
	$query .= "a.experience, a.alliance, ifnull(b.progress, 0) as progress, ";
	$query .= "ifnull(b.part, 0) as part, ifnull(b.part2, 0) as part2 from mission a ";
	$query .= "left join player_mission b on a.mid=b.mid and b.pid=".$player->pid." ";
	$query .= 'where a.mgid='.$ssid.' and a.lid<='.$player->lid.' ';  
	$query .= 'order by a.lid asc';

	$result = warquest_db_query($query);

	$line=0;
	while ( $data=warquest_db_fetch_object($result) ) {
	
		$line++;
		
		$page .= '<div class="box" id="'.$data->mid.'">';
		$page .= '<table>';
		$page .= '<tr>';	
		$page .= '<td colspan="3"><span class="paragraph">'.t('GENERAL_CONQUER').' '.t('MISSION_'.$data->mid).'</span>';
		if ($data->part!=$data->part2) {
			$page .= ' <span class="notification">'.t('MISSION_REBEL').'</span>';
		}
		$page .= '<br/>';
		$page .= '<b>'.t('MISSION_GAIN').':</b><br/>';
		$page .= money_format1($data->min_price).' - ';
		$page .= dollar_format($data->max_price).'<br/>';
		$page .= experience_format($data->experience).' '.t('GENERAL_EXPERIENCE').'<br/>';
		if ($data->loot==1) {
			$page .= '<span class="loot">'.t('MISSION_CHANCE_LOOT').'</span><br/>';
		}
		$page .= '<br/></td>';
		$page .= '<td  width="100" align="right" valign="top">';		
		$page .= warquest_image('bar/bar'.warquest_format_progress($data->progress, $data->part).'.png').'<br/>';
	
		$max = $config['max_mission_part'];
		if ($player->lid==0) {
			$max=1;
		}
	
		$page .= t('MISSION_PART').' '.warquest_format_part($data->part).'/'.$max.'<br/>';
		$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&ssid='.$ssid.'&eid='.EVENT_MISSION_PLAY.'&id='.$data->mid,t('LINK_PLAY'),'play'.$line);
		$page .= '</td>';
	
		$page .= '</tr>';
		$page .= '<tr>';
	
		$page .= '<td valign="top" width="240">';
		$page .= '<b>'.t('MISSION_REQUIRED').':</b><br/>';
		$page .= energy_format($data->energy).' '.t('GENERAL_ENERGY').'<br/>';
		$page .= alliance_format($data->alliance).' '.t('GENERAL_ALLIANCE_SIZE');
		$page .= '</td>';
		
		$query2  = 'select b.uid, b.gold, a.amount, b.attack, b.defense, b.upkeep from mission_unit a, ';
		$query2 .= 'unit b where b.uid=a.uid and mid='.$data->mid;  
		$result2 = warquest_db_query($query2); 
	
		$count=0;
		while ($data2 = warquest_db_fetch_object($result2)) {
	
			$count++;
			$page .= '<td align="right" width="100">';   
			$page .= warquest_unit_image($data2, $line);	
			$page .= '<br/><center>'.$data2->amount.'x</center>';
			$page .= '</td>';
		}
			
		/* fill up table */
		for ($tmp=0; $tmp<(3-$count); $tmp++) {
			$page .= '<td align="right" width="100">&nbsp;</td>';
		}
		$page .= '</tr>';
	
		$page .= '</table>';
		$page .= '</div>';
	}

	/* Show next lock player mission */	
	$query  = 'select mid, lid, loot, min_price, max_price, energy, experience, alliance ';
	$query .= 'from mission where mgid='.$ssid.' and lid>'.$player->lid.' ';
	$query .= 'order by lid asc limit 0,1';
	$result = warquest_db_query($query);

	if ($data=warquest_db_fetch_object($result)) {
	
		$line++;
	
		$page .= '<div class="box">';
		$page .= '<table>';
	
		$page .= '<tr>';	
		$page .= '<td colspan="3" >';
		$page .= '<span class="paragraph">'.t('GENERAL_CONQUER').' '.t('MISSION_'.$data->mid).'</span><br/>';
	
		$page .= '<b>'.t('MISSION_GAIN').':</b><br/>';
		$page .= money_format1($data->min_price).' - ';
		$page .= dollar_format($data->max_price).'<br/>';
		$page .= experience_format($data->experience).' '.t('GENERAL_EXPERIENCE').'<br/>';
		if ($data->loot==1) {
			$page .= '<span class="loot">'.t('MISSION_CHANCE_LOOT').'</span><br/>';
		}
		$page .= '<br/></td>';
			
		$page .= '<td  width="100" align="right" valign="top">';
		$page .= t('GENERAL_UNLOCK', $data->lid);
		$page .= '</td>';
	
		$page .= '</tr>';
		$page .= '<tr>';
	
		$page .= '<td valign="top" width="240">';
		$page .= '<b>'.t('MISSION_REQUIRED').':</b><br/>';
		$page .= energy_format($data->energy).' '.t('GENERAL_ENERGY').'<br/>';
		$page .= alliance_format($data->alliance).' '.t('GENERAL_ALLIANCE_SIZE');
		$page .= '</td>';
		
		for ($tmp=0; $tmp<3; $tmp++) {
			$page .= '<td width="100">';
			$page .= warquest_image('other/unlock.png');
			$page .= '</td>';
		}
		
		$page .= '</tr>';	
	
		$page .= '</table>';
		$page .= '</div>';
	}
	
	$page .= '<script type="text/javascript">';
	$page .= "window.scrollTo(0, document.getElementById(".$anchor.").offsetTop);";
	$page .= '</script>';
	
	if ($line==0) {
	
		$message = t('MISSION_NO_MISSIONS');
		$page .= warquest_box_icon('info', $message);	
	}		
	
	$page .= '<div class="note">';
	$page .= t('MISSION_NOTE', $output->title, money_format1($ssid * $config["continent_conquer_bonus"]));
	$page .='</div>';
}

/*
** -----------
** HANDLER
** -----------
*/

/** 
 * Event handler
 */
function warquest_mission() {

	/* input */
	global $eid;
	global $sid;
	  	
	/* Event handler */
	switch ($eid ) {
	
		case EVENT_MISSION_PLAY: 		
						warquest_mission_do();
						break;		

		case EVENT_MISSION_BUY_PLAY: 		
						warquest_buy_missing_units_do();
						warquest_mission_do();
						break;		

		case EVENT_MISSION_CLAN_PLAY: 		
						warquest_mission_clan_do();
						break;	
						
		case EVENT_MISSION_CLAN_BUY_PLAY: 		
						warquest_buy_missing_units_do();
						warquest_mission_clan_do();
						break;	
						
		case EVENT_SWITCH_PLANET:
						warquest_switch_planet_do();
						break;
	}				
	
	switch($sid) {
		
		case PAGE_MISSION_PLAYER: 
			warquest_mission_player_form();
			break;
	
		case PAGE_MISSION_CLAN: 
			warquest_mission_clan_form();
			break;
	}	
}

/*
** ---------------------------------------------------------------- 
** THE END
** ----------------------------------------------------------------
*/

?>