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
** MISSIONS 
** ---------------------------------------------------------------- 
*/

/*
** -----------
** ACTIONS
** -----------
*/

/** 
 *  Detect all mission of a planet are finished!
 */
function warquest_mission_planet_complet_bonus() {

	/* input */
	global $player;

	/* output */
	global $popup;
	
	if ( warquest_db_bonus($player->pid, $player->planet)==0) {

		/* Check if all missions are played on active planet */
		$query  = 'select sum(a.part2) as part2 from player_mission a left join mission b on a.mid=b.mid ';
		$query .= 'left join mission_group c on c.mgid=b.mgid ';
		$query .= 'where a.pid='.$player->pid.' and c.planet='.$player->planet;
		
		$result = warquest_db_query($query);	
		$data = warquest_db_fetch_object($result);
					
		if ($data->part2==216) {
			
			/* Only if insert is successfull, add bonus to players account */
			if (warquest_db_bonus_insert($player->pid, $player->planet)) {
			
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
						
				$popup .= warquest_box("info", $message);	

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
							
					case PLANET_ASTEROID:	
								$player->gold += 2500;
								break;
				}
			}
		}		
	}
}

			
/** 
 *  Detect continent missions complete. 
 */
function warquest_mission_complet() {

	/* input */
	global $sid;
	global $uid;
	
	/* output */
	global $player;
	global $skill;	
	global $config;
	global $popup;
	
	$pid = $player->pid;

 	$query1  = 'select progress, part, part2 from player_mission where pid='.$pid.' and mid='.$uid;  
	
	$result1 = warquest_db_query($query1);
	$data1 = warquest_db_fetch_object($result1);

	$part = $data1->part2+1;
	
	$query2  = 'select sum(progress) as progress from player_mission a, ';
	$query2 .= 'mission b where a.mid=b.mid and a.pid='.$pid.' and b.mgid='.$sid;
	$result2 = warquest_db_query($query2);	
	$data2 = warquest_db_fetch_object($result2);
	
	/* Detect if all continent mission parts are 100% complete */
	if (($part*800)==$data2->progress) {
		
		/* calculate skill points bonus. */
		$bonus = warquest_format_part($part)+2;
			
		/* Update skill points */
		$skill->skill_points += $bonus;
		warquest_db_skill_update($skill);
				
		/* Restore energy. */
		$player->energy=$skill->energy_max;	
			
		$message  = t('MISSION_CONTINTENT_READY1', 
							warquest_format_part($part-1), 
							$config["max_mission_part"], 
							t('MISSION_GROUP_'.$sid));
									
		$message .= t('MISSION_CONTINTENT_READY2', $bonus);
				
		if (warquest_format_part($part) == $config["max_mission_part"]) {
			$message .= t('MISSION_CONTINTENT_READY3');
		} else {				
			$message .= t('MISSION_CONTINTENT_READY4', warquest_format_part($part));
		}				
		$message .= '<br/><br/>';
		
		for ($tmp=0; $tmp<$bonus; $tmp++) {
			$message .= warquest_image("other/star.jpg");
		}
		
		$message .= '<br/><br/>';
		
		$message .= t('MISSION_COMPLETE_TEXT');
		$message .= warquest_ui_map($player, $player->planet);
		$message .= '<br/>'; 
		
		$link = warquest_link('mid='.MENU_HOME.'&sid='.PAGE_SKILLS, t('LINK_SP') ,'skillpoints');
		$popup .= warquest_box("info", $message, $link);
							
		/* Clear progress state for all eight missions. */
		$query  = 'update player_mission a, mission b set a.part='.$part.', a.part2='.$part.' where '; 
		$query .= 'a.mid=b.mid and a.pid='.$pid.' and b.mgid='.$sid;
		warquest_db_query($query);		
					
		/* Update income value */
		warquest_netto_income($player);		
	} 
}

/**
 * Mission unit lost detection
 */
function warquest_mission_unit_lost() {

   /* input */
	global $uid;
	global $level;
	
	/* output */
	global $player;
	global $message;
	
	/* Unit lost disabled for this level. */
	if ($level->unit_lost==0) {
	   return;
	}

	/* Update mission damage */
	$maintenance = warquest_maintenance($player, $player->planet);	
	$player->damage_units += round(((100-$maintenance)/100) * rand(1,10));
		
	/* Check if units damage is less then 100% then return */		
	if ($player->damage_units<100) {
		return;
	}
	$player->damage_units = 0;
	
	/* get strongest attack unit */
	$query  = 'select a.uid, c.defense, c.attack, a.amount, c.upkeep ';
	$query .= 'from mission_unit a LEFT JOIN unit c ' ;
	$query .= 'ON a.uid=c.uid left join player_unit b ';
	$query .= 'ON a.uid=b.uid and b.pid='.$player->pid.' where a.mid='.$uid;
		
	$result = warquest_db_query($query);
	
	$message  = '<br/><span class="warning">'.t('MISSION_UNITS_LOST').':</span><br/>'; 
	$message .= '<table>';
	$message .= '<tr>';
	
	$count=1000;	
	while ($data = warquest_db_fetch_object($result)) {
		
		$amount=rand(1,round($data->amount/10));
		
		/* Update database */
		warquest_db_unit_delete($player->pid, $data->uid, $amount );
			
		$message .= '<td width="90">';
		$message .= warquest_unit_image($data, $count++);		
		$message .= '<br/><center>'.$amount.'x</center>';
		$message .= '<td>';
	}
	
	$message .= '</tr>';
	$message .= '</table>';
	
	/* Update income, attack and defense value */
	warquest_netto_income($player);
		
	return $message;
}

/** 
 * Buy mission units
 */
function warquest_buy_missing_units_do() {
	
	/* input */
	global $uid;
	
	/* output */
	global $player;
	global $popup;
	
	$query  = 'select a.uid, c.price, c.upkeep, ifnull(b.amount,0) as amount, ';
	$query .= 'a.amount-ifnull(b.amount,0) as total ';
	$query .= 'from mission_unit a LEFT JOIN unit c ' ;
	$query .= 'ON a.uid = c.uid left join player_unit b ';
	$query .= 'ON a.uid=b.uid and b.pid='.$player->pid.' where a.mid='.$uid.' ';
	$query .= 'and a.amount-ifnull(b.amount,0)>0';
	$result = warquest_db_query($query); 
	
	while ($unit=warquest_db_fetch_object($result)) {
	 							
		/* Process player statistics. */
		$money = $unit->price * $unit->total;			
		$upkeep = $unit->upkeep * $unit->total;
		
		if ($money > $player->money) {

			$message = '<table>';
			$message .= '<tr>';
			$message .= '<td width="100">';
			$message .= warquest_unit_image($unit->uid, 0, 0);
			$message .= '</td>';
			$message .= '<td>';
			$message .= t('UNIT_NO_FUNDS', $unit->total, t('UNIT_'.$unit->uid), dollar_format($money));
			$message .= '</td>';
			$message .= '</tr>';
			$message .= '</table>';
	
			$popup .= warquest_box("warning", $message);
			break;
		
		} else if ($upkeep > $player->money_step) {
		
			$message = '<table>';
			$message .= '<tr>';
			$message .= '<td width="100">';
			$message .= warquest_unit_image($unit->uid, 0, 0);
			$message .= '</td>';
			$message .= '<td>';
			$message .= t('UNIT_NO_UPKEEP',$unit->total, t('UNIT_'.$unit->uid));
			$message .= '</td>';
			$message .= '</tr>';
			$message .= '</table>';
	
			$popup .= warquest_box("warning", $message);
			break;
		
		} else {
		
			/* Buy missing units */
			$player->money -= $money;
			
			$log = 'Buy missing units for mission '.number_format2($money);		
			warquest_user_log($player, $log);
	
			warquest_db_unit_add($player->pid, $unit->uid, $unit->total);
		}
	}
	
	/* Update income, attack and defense value */
	warquest_netto_income($player);
}

/** 
 * Play Mission 
 */ 
function warquest_mission_do() {

	/* input */
	global $mid;
	global $sid;	
	global $uid;
	global $level;
	global $config;
	
	/* output */
	global $page; 
	global $player;
	global $popup;
	
	$pid = $player->pid;

		
	/* Get mission data */
	$query  = 'select min_price, max_price, energy, experience, alliance, ';
	$query .= 'loot, lid from mission where mid='.$uid;  
	$result = warquest_db_query($query); 
	$mission = warquest_db_fetch_object($result);

	/* Get progress data */	
	$progress = 0;
	$part = 0;
	$part2 = 0;
	
	$query  = 'select progress, part, part2 from player_mission where pid='.$pid.' and mid='.$uid;  
	$result = warquest_db_query($query);

	if ($data = warquest_db_fetch_object($result)) {
		$progress = $data->progress;
		$part = $data->part;
		$part2 = $data->part2;
	}
	
	/* Check for missing units */
	$query  = 'select a.uid, c.price, c.upkeep, c.attack, c.defense, a.amount-ifnull(b.amount,0) ';
	$query .= 'as total from mission_unit a LEFT JOIN unit c ' ;
	$query .= 'ON a.uid = c.uid left join player_unit b ';
	$query .= 'ON a.uid=b.uid and b.pid='.$player->pid.' where a.mid='.$uid.' ';
	$query .= 'and a.amount-ifnull(b.amount,0)>0';
	$result2 = warquest_db_query($query);
	
	$count=0;
	if (warquest_db_num_rows($result2)>0) {
		
		$total=0;
		$upkeep=0;
		
		$message  = '<span class="warning">'.t('MISSION_ABORTED').'</span><br/>';
		$message .= t('MISSION_MISSING_UNITS').'<br/><br/>';
	
		$message .= '<table>';
		$message .= '<tr>';
		while ($unit=warquest_db_fetch_object($result2)) {
		
			$message .= '<td>';
			$message .= warquest_unit_image($unit, $count++);		
			$message .= '<br/><center>'.$unit->total.'x</center>';
			$message .= '</td>';					
			
			$total += $unit->price * $unit->total;
			$upkeep += $unit->upkeep * $unit->total;
		}		
		$message .= '</tr>';
		$message .= '</table>';
		
		$message .= '<br/>';
		$message .= t('MISSION_MISSING_UNITS_PRICE',money_format2($total), money_format2($upkeep));
		
		$message .= warquest_show_ads();
		
		$link = warquest_image('bar/bar'.warquest_format_progress($progress, $part).'.png').'<br/>';
		
		$max = $config['max_mission_part'];
		if ($player->lid==0) {
			$max=1;
		}
		
		$link .= t('MISSION_PART').' '.warquest_format_part($part).'/'.$max.'<br/>';
		$link .= warquest_link('mid='.$mid.'&sid='.$sid.'&uid='.$uid.'&eid='.EVENT_MISSION_BUY_PLAY, t('LINK_BUY_PLAY'), 'buyplay');
		
		$popup .= warquest_box(t('GENERAL_CONQUER').' '.t('MISSION_'.$uid), $message, $link);
		
	} else if ($player->energy < $mission->energy) {

		$message = '<span class="warning">'.t('MISSION_ABORTED').'</span><br/>';
		$message .= t('MISSION_NO_ENERGY');
		
		$message .= warquest_show_ads();
		
		$link  = warquest_image('bar/bar'.warquest_format_progress($progress, $part).'.png').'<br/>';
		
		$max = $config['max_mission_part'];
		if ($player->lid==0) {
			$max=1;
		}
		
		$link .= t('MISSION_PART').' '.warquest_format_part($part).'/'.$max.'<br/>';
		$link .= warquest_link('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_MISSION_PLAY.'&uid='.$uid, t('LINK_DO_AGAIN'),'doagain');
		
		$popup .= warquest_box(t('GENERAL_CONQUER').' '.t('MISSION_'.$uid), $message, $link);
		
	} else if ($player->alliance < $mission->alliance) {
	
		$message = '<span class="warning">'.t('MISSION_ABORTED').'</span><br/>';
		$message .= t('MISSION_LOW_ALLIANCE');
		
		$message .= warquest_show_ads();
		
		$popup .= warquest_box(t('GENERAL_CONQUER').' '.t('MISSION_'.$uid), $message);
		
	} else {
		
		/* Update player */
		$player->energy -= $mission->energy;
		$player->experience += $mission->experience;
		$player->mission += 1;
		
		$money = rand($mission->min_price,$mission->max_price);
			
		/* If progress is 100% double money */				
		if (warquest_format_progress($progress, $part)==100) {
		
			$money = $money * 2;
			
		} else {
				
			if (warquest_format_progress($progress, $part)==90) { 
			
				$progress+=10;	
				$money = $money * 2;
					
			} else {
			
				$progress+=15;
			}
		} 
		
		$player->money += $money;
		
		$log = 'Mission play bonus '.number_format2($money);		
		warquest_user_log($player, $log);
			
	
		/* Rebel restore action */
		if ((warquest_format_progress($progress,$part)==100) && ($part!=$part2)) {
		
			$part++;
		} 
		
		warquest_db_mission_progress_update($pid, $uid, $progress, $part, $part2);	
		warquest_mission_complet();
		warquest_mission_planet_complet_bonus();
		
		$next = warquest_nextlevel($player);

		if (($next==1) && ($player->lid==1)) {
			
			/* If training mission is complet, skip mission complet message. */
		   $sid = 1;
			
		} else {
			
			$message = t('MISSION_YOU_GAIN').': '.money_format1($money).t('MISSION_DOLLAR_AND');
			$message .= experience_format($mission->experience).' '.t('GENERAL_EXPERIENCE_POINTS').'<br/>';
			$message .= t('MISSION_YOU_USED').': '.energy_format($mission->energy).' '.t('GENERAL_ENERGY').'<br/>';
			$message .= warquest_mission_unit_lost();
			
			if ($mission->loot==1) {
				$message .= warquest_lootoption($mission->lid);
			}
			
			$message .= warquest_show_ads();
			
			$link  = warquest_image('bar/bar'.warquest_format_progress($progress, $part).'.png').'<br/>';
			
			$max = $config['max_mission_part'];
			if ($player->lid==0) {
				$max=1;
			}
		
			$link .= t('MISSION_PART').' '.warquest_format_part($part).'/'.$max.'<br/>';
			$link .= warquest_link('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_MISSION_PLAY.'&uid='.$uid, t('LINK_DO_AGAIN'), "doagain");
		
			$popup .= warquest_box(t('GENERAL_CONQUER').' '.t('MISSION_'.$uid), $message, $link);
			
			warquest_sound('mission'.rand(1,2).'.mp3');	
		} 
	}
}

/*
** -----------
** GUI
** -----------
*/

/** 
 * Mission form
 */
function warquest_mission_form() {

	/* input */
	global $mid;
	global $sid;
	global $anchor;
	global $player;
	global $config;
	
	/* output */
	global $page; 
	global $title;
		
	warquest_set_default_mission($sid);	
		
	$title = t('MISSION_GROUP_'.$sid);
	
	if ($player->lid==1) {
	
		$message = t('MISSION_UNLOCKED');
	
		$link = warquest_link('mid='.MENU_BATTLE.'&sid='.PAGE_ENEMIES, t('LINK_BATTLE'), "battle1");

		$page .= warquest_box_icon('info', $message, $link);
	
	} else {
					
		$pid = $player->pid;
				
		/* Get mission data */
		$query  = "select a.mid, a.loot, a.min_price, a.max_price, a.energy, ";
		$query .= "a.experience, a.alliance, ifnull(b.progress, 0) as progress, ";
		$query .= "ifnull(b.part, 0) as part, ifnull(b.part2, 0) as part2 from mission a ";
		$query .= "left join player_mission b on a.mid=b.mid and b.pid=".$pid." ";
		$query .= 'where a.mgid='.$sid.' and a.lid<='.$player->lid.' ';  
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
			$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_MISSION_PLAY.'&uid='.$data->mid,t('LINK_PLAY'),'play'.$line);
			$page .= '</td>';
		
			$page .= '</tr>';

			$page .= '<tr>';
		
			$page .= '<td valign="top" width="240">';
			$page .= '<b>'.t('MISSION_REQUIRED').':</b><br/>';
			$page .= energy_format($data->energy).' '.t('GENERAL_ENERGY').'<br/>';
			$page .= alliance_format($data->alliance).' '.t('GENERAL_ALLIANCE_SIZE');
			$page .= '</td>';
		
			$query2  = 'select b.uid, a.amount, b.attack, b.defense, b.upkeep from mission_unit a, ';
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

		/* Unlock mission */	
		$query  = 'select mid, lid, loot, min_price, max_price, energy, experience, alliance ';
		$query .= 'from mission where mgid='.$sid.' and lid>'.$player->lid.' ';
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
	}
	
	if ($player->lid>0) {
		$page .= '<div class="note">';
		$page .= t('MISSION_NOTE', $title, money_format1($sid * $config["continent_conquer_bonus"]));
		$page .='</div>';
	}
}

/*
** -----------
** EVENT HANDLER
** -----------
*/

/** 
 * Mission handler
 */
function warquest_mission() {

	/* input */
	global $eid;
	  	
	/* Event handler */
	switch ($eid ) {
	
		case EVENT_MISSION_PLAY: 		
						warquest_mission_do();
						break;		
				  
		case EVENT_MISSION_BUY_PLAY: 		
						warquest_buy_missing_units_do();
						warquest_mission_do();
						break;		
				  
		case EVENT_SWITCH_PLANET: 	
						warquest_switch_planet_do();
						break;
	}				
		
	/* Page handler */
	warquest_mission_form();	
}

/*
** ---------------------------------------------------------------- 
** THE END
** ----------------------------------------------------------------
*/

?>