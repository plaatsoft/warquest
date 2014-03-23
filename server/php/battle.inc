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
** BATTLE
** ---------------------------------------------------------------- 
*/

/* 
** -----------
** PARAMETERS
** -----------
*/

if (isset($_POST['force']) && $_POST['force'] != "") {
	warquest_set_default_force($_POST['force']);
}

/* 
** -----------
** UTILS
** -----------
*/

/*
** Robot trade 
*/
function warquest_robot_trade($other, $planet) {

	if ($other->country!="EU") {
		return;
	}
		 		
	/* Update login timers */
	$member = warquest_db_member($other->pid);
	$member->prev_login = $member->last_login;
	$member->last_login = date("Y-m-d H:i:s");
	warquest_db_member_update($member);
	
	/* Withdraw all money of the bank, if any */
	if ($other->bank1 > 0) {
		warquest_db_bank_insert($other->pid, 0, 1, ($other->bank1*-1), 0, 0);	
		$other->money += $other->bank1;
		$other->bank1 = 0;
	}
		
	if ($other->bank2 > 0) {
		warquest_db_bank_insert($other->pid, 0, 2, ($other->bank2*-1), 0, 0);	
		$other->money += $other->bank2;
		$other->bank2 = 0;
	}

	if ($other->bank3 > 0) {
		warquest_db_bank_insert($other->pid, 0, 3, ($other->bank3*-1), 0, 0);	
		$other->money += $other->bank3;
		$other->bank3 = 0;
	}
		
	/* Robot improve skills strenght */
	$skill = warquest_db_skill($other->pid);	
	if ($skill->skill_points>0) {			
		
		switch (rand(1,5)) {
	
			case 1: 	$skill->attack_max += 1;
						break;
		
			case 2: 	$skill->defense_max += 1;
						break;
					  
			case 3: 	$skill->health_max += 10;
						$other->health += 10;
						break;

			case 4:	$skill->energy_max += 10;
						$other->energy += 10;
						break;
		
			case 5: 	$skill->ammo_max++;
						$other->ammo++;
						break;	
		}		
		$skill->skill_points--;
		warquest_db_skill_update($skill);
	}
	
	switch (rand(1,4)) {
		
		case 1:  /* Robot buy some units */
				   $tmp=$other->lid - 20;
					if ($tmp<0) {
						$tmp=0;
					}
					$query  = 'select uid, price, max from unit where lid between '.$tmp.' and '.$other->lid.' ';
					$query .= 'order by rand() limit 0, 1';
										
					$result = warquest_db_query($query);	
					while ($data = warquest_db_fetch_object($result)) {
						
						$query2  = 'select amount from player_unit where pid='.$other->pid.' and uid='.$data->uid;
						$result2 = warquest_db_query($query2);	
						$amount = 0;
						if ($data2 = warquest_db_fetch_object($result2)) {
							$amount = $data2->amount;
						}
					
						$total = @floor($other->money / $data->price);
						$total = rand(0, $total);
						if ($total > ($data->max - $amount)) {
							$total = $data->max - $amount;
						}
						if ($total > ($other->lid *6)) {
							$total = $other->lid *6;
						}
						
						if ($total>0) {
							$other->money -= $total * $data->price;								
							warquest_db_unit_add($other->pid, $data->uid, $total);				
						}						
					}
					break;
		
		case 2:  /* Robot sell some units */		
					$query  = 'select a.uid, a.price, b.amount from unit a left join player_unit b on a.uid=b.uid ';
					$query .= 'left join unit_group c on a.ugid=c.ugid ';
					$query .= 'where b.pid='.$other->pid.' and c.planet='.$planet.' and c.type!=6 and b.amount>2 and a.gold=0 ';
					$query .= 'order by rand() limit 0, 1';
								
					$result = warquest_db_query($query);	
					while ($data = warquest_db_fetch_object($result)) {
											
						$total = rand(1, ($data->amount/20));							
						$other->money += $total * $data->price;								
							
						warquest_db_unit_delete($other->pid, $data->uid, $total);			
					}
					break;
										
		case 3:  /* Robot buy some buildings */
				   $tmp=$other->lid - 20;
					if ($tmp<0) {
						$tmp=0;
					}
					$query  = 'select bid, price, max from building where lid between '.$tmp.' and '.$other->lid.' ';
					$query .= 'and gold=0 order by rand() limit 0, 1';
					
					$result = warquest_db_query($query);	
					while ($data = warquest_db_fetch_object($result)) {
					
						$query2  = 'select amount from player_building where pid='.$other->pid.' and bid='.$data->bid;
						$result2 = warquest_db_query($query2);	
						$amount = 0;
						if ($data2 = warquest_db_fetch_object($result2)) {
							$amount = $data2->amount;
						}
							
						$total = floor($other->money / $data->price);
						$total = rand(0, $total);
						if ($total > ($other->lid - $amount)) {
							$total = $other->lid - $amount;
						}
							
						if ($total>0) {
							$other->money -= $total * $data->price;								
							warquest_db_building_add($other->pid, $data->bid, $total);
						}
					}
					break;
					
		case 4:  /* Robot sell some buildings */		
					$query  = 'select a.bid, a.price, b.amount from building a left join player_building b on a.bid=b.bid ';
					$query .= 'left join building_group c on a.bgid=c.bgid ';
					$query .= 'where b.pid='.$other->pid.' and c.planet='.$planet.' and c.type=2 and b.amount>2 order by rand() limit 0, 1';
								
					$result = warquest_db_query($query);	
					while ($data = warquest_db_fetch_object($result)) {
											
						$total = rand(1, ($data->amount/20));							
						$other->money += $total * $data->price;								
							
						warquest_db_building_delete($other->pid, $data->bid, $total);
					}
					break;
	}
	
	warquest_netto_income($other);		
}

/**
 * Battle robot player
 */
function warquest_robot_battle($player, $other) {
	  
	/* input */
	global $config;
	global $level;
		
	/* 50% chance on robot counter attack */
	if ((rand(1,2)==1) &&
		 ($other->country=="EU") &&
		 ($other->ammo>0) &&
		 ($player->health>=$config["init_health_min"]) &&
		 ($other->health>=$config["init_health_min"])) 
	{
		$money = round((1/rand(10,15)) * $player->money);
		if ($money < 0) {
			$money = 0;
		}
		
		/* Prevent to big money wins */
		if ($money > $config["max_money_win"] ) {
			$money = $config["max_money_win"]  + rand(10000, 600000);
		}
							
		$health_winner = rand(1,10);
		$health_losser = rand(8,20);
		$exp = rand(1, (round($other->lid/10)+5));
	
		/* select random attack force */		
		$query  = 'select ugid from unit_group where type in (0,2,3,4,5) and planet='.$player->planet.' ';
		$query .= 'order by rand() limit 1';
		
		$result = warquest_db_query($query);	
		$data = warquest_db_fetch_object($result);
		$force = $data->ugid;
		
		if (warquest_battle_check($other, $player, $force)==1) {
		
			/* Robot won */
			$other->ammo -= 1;
			$other->money += $money;
			$other->experience += $exp;
			$other->health -= $health_winner;
			$other->won += 1;	
			
			$maintenance = warquest_db_maintenance($other, $other->planet);
	
			if ($level->unit_lost==1) {
				$other->damage_units += round(((100-$maintenance)/100) * ($health_winner/2));
			}
			
			if ($level->building_lost==1) {				
				$other->damage_buildings += round(((100-$maintenance)/100) * rand(1,2));
			}
			
			/* update defender */
			$player->money -= $money;
			$player->health -= $health_losser;
			$player->lost += 1;
			$player->last_battle = date("Y-m-d H:i:s");
			
			if (warquest_db_query_pattern($player, PATTERN_NO_BOT_NEWS)==0) {
			
				$player->news_notification++;
			
				/* Update battle log. */
				warquest_db_battle_insert($other->pid, $player->pid, $money, $health_losser, 0, 1, $force);
			}
			
			$maintenance = warquest_db_maintenance($player, $player->planet);		
			
			if ($level->unit_lost==1) {
				$player->damage_units += round(((100-$maintenance)/100) * ($health_losser/2));
			}
				
			if ($level->building_lost==1) {
				$player->damage_buildings += round(((100-$maintenance)/100) * rand(1,4));
			}
				 			
			$log = 'Battle lost losing '.number_format2($money).' ['.$other->pid.']';		
			warquest_user_log($player, $log);
			
		} else {
		
			/* Robot lost */
			$other->ammo -= 1;
			$other->health -= $health_losser;
			$other->lost += 1;
			
			$maintenance = warquest_db_maintenance($other, $other->planet);		
			
			if ($level->unit_lost==1) {
				$other->damage_units += round(((100-$maintenance)/100)*($health_losser/2));
			}
			
			if ($level->building_lost==1) {
				$other->damage_buildings += round(((100-$maintenance)/100) * rand(1,4));
			}
	
			/* Update defender */
			$player->experience += $exp;
			$player->health -= $health_winner;
			$player->won += 1;
			$player->last_battle = date("Y-m-d H:i:s");
			
			if (warquest_db_query_pattern($player, PATTERN_NO_BOT_NEWS)==0) {
			
				$player->news_notification++;
				
				/* Update battle log. */
				warquest_db_battle_insert($other->pid, $player->pid, 0, $health_winner, $exp, 0, $force);
			}
						
			$maintenance = warquest_db_maintenance($player, $player->planet);
		
			if ($level->unit_lost==1) {
				$player->damage_units += round(((100-$maintenance)/100) * ($health_winner/2));
			}
		
			if ($level->building_lost==1) {
				$player->damage_buildings += round(((100-$maintenance)/100) * rand(1,2));
			}			
		}
	}
}

/** 
 * Battle show attack army 
 */
function warquest_show_attack_army($data2, $ugid) {

   /* input */
	global $mid;
	global $player;
	global $output;
	
	$message = "";
	
	if ( $output->format=="html" ) {
			
		$unit_group = warquest_db_unit_group($ugid);
			
		$message .= '<br/><br/>';
		$message .= t('BATTLE_ATTACK_FORCE', 
			strtolower(t('GENERAL_PLANET_'.$player->planet)),
			strtolower(t('UNIT_GROUP_'.$ugid)),
			warquest_link('mid='.$mid.'&sid='.PAGE_ATTACK.'&oid='.$data2->pid.'&uid='.$unit_group->type,
						    number_format(warquest_attack_strength($data2, $ugid, 0),0,",","."), "attack_strenght"));
		$message .= '<br/>';
		$message .= '<table>';
		$message .= '<tr>';	
		
		/* Calculate attack strength of units depending of alliance size */
		$query  = 'select a.uid, a.gold, a.attack, a.defense, a.upkeep, b.amount ';
		$query .= 'from unit a, player_unit b where ';
		$query .= 'a.uid=b.uid and b.pid='.$data2->pid.' ';
	
		if ($unit_group->type==0) {
			$query .= 'and a.ugid in (select ugid from unit_group where type in (2,3,4) and planet='.$unit_group->planet.') ';
		} else {
			$query .= 'and a.ugid='.$ugid.' ';
		}
	
		$query .= 'order by a.attack desc, a.defense desc';
		$result = warquest_db_query($query);	

		$amount = 0;
		$count = 0;
		$size= $data2->alliance * 6;
			
		$max = 10;
		while ($data = warquest_db_fetch_object($result)) {
					
			if ($size >= $data->amount) {
			
				$size -= $data->amount;
				$amount = $data->amount;
			
			} else {
		
				$amount = $size;
				$size -= $size;			
			}

			$message .= '<td width="45" >';		
			$message .= warquest_unit_image($data, $count, 1, 45, 32);
			$message .= '<br/><center>'.$amount.'x</center>';
			$message .= '</td>';
				
			if ($size==0) {
				break;
			}
			
			if ((++$count%$max)==0) {
						
				$message .= '</tr>';
				$message .= '<tr>';			
			}
		}
	
		$message .= '</tr>';
		$message .= '</table>';	
	}
	return $message;
}

/** 
 * Battle show defend army 
 */
 function warquest_show_defense_army($data2, $ugid) {

   /* input */
	global $mid;
	global $player;
	global $output;
	
	$message = "";
	
	if ( $output->format=="html" ) {
	
		$unit_group = warquest_db_unit_group($ugid);
			
		/* show defense units */
		$query =  'select a.uid, a.gold, a.attack, a.defense, a.upkeep, b.amount ';
		$query .= 'from unit a, player_unit b where ';
		$query .= 'a.uid=b.uid and b.pid='.$data2->pid.' ';
	
		if ($unit_group->type==0) {
			$query .= 'and a.ugid in (select ugid from unit_group where type in (2,3,4) and planet='.$unit_group->planet.') ';
		} else {
			$query .= 'and a.ugid='.$ugid.' ';
		}
		
		$query .= 'order by a.defense desc, a.attack desc';
		$result = warquest_db_query($query);	

		$amount = 0;
		$count = 0;
		$size = $data2->alliance * 6;
		
		$message .= '<br/>';
		$message .= t('BATTLE_DEFENSE_FORCE', 
			player_format($data2->pid, $data2->name, $data2->country), 
			strtolower(t('GENERAL_PLANET_'.$player->planet)),
			strtolower(t('UNIT_GROUP_'.$ugid)),
			warquest_link('mid='.$mid.'&sid='.PAGE_DEFENCE.'&oid='.$data2->pid.'&uid='.$unit_group->type, 
								number_format(warquest_defense_strength($data2, $ugid, 0),0,",","."), "defense_strength"));
		$message .= '<br/>';
		$message .= '<table>';
		$message .= '<tr>';	
		
		$max=10;	
		while ($data = warquest_db_fetch_object($result)) {
						
			if ($size >= $data->amount) {
				
				$size -= $data->amount;
				$amount = $data->amount;
				
			} else {
			
				$amount = $size;
				$size -= $size;			
			}
		
			$message .= '<td width="45" align="left">';
			$message .= warquest_unit_image($data, $count, 1, 45, 32);	
			$message .= '<br/><center>'.$amount.'x</center>';
			$message .= '</td>';
		
			if ($size==0) {
				break;
			}
		
			if ((++$count%$max)==0) {
					
				$message .= '</tr>';
				$message .= '<tr>';			
			}
		}
		$message .= '</tr>';
		$message .= '</table>';	
	
		/* show defense base (buildings) */
		$query  = 'select a.bid, a.ugid, a.gold, a.energy, a.income, a.defense, a.discount, b.amount ';
		$query .= 'from building a, player_building b where ';
		$query .= 'a.bid=b.bid and b.pid='.$data2->pid.' and a.defense>0 ';
		
		if ($unit_group->type==0) {
			$query .= 'and a.ugid in (select  ugid from unit_group where type in (2,3,4) and planet='.$player->planet.') ';
		} else {
			$query .= 'and a.ugid='.$ugid.' ';
		}	
		$query .= 'order by a.defense desc';
	
		$result = warquest_db_query($query);	
		$count = warquest_db_num_rows($result);
	
		if ($count>0) {
			$message .= '<br/>';
			$message .= t('BATTLE_DEFENSE_BASE', player_format($data2->pid, $data2->name, $data2->country).' '.strtolower(t('GENERAL_PLANET_'.$player->planet)));
			$message .= '<br/>';
			$message .= '<table>';
			$message .= '<tr>';	
	
			$count=0;
			while ($data = warquest_db_fetch_object($result)) {
								
				$message .= '<td width="45" align="left">';
				$message .= warquest_building_image($data, 0, 1, 45, 32);	
				$message .= '<br/><center>'.$data->amount.'x</center>';
				$message .= '</td>';
					
				if ((++$count%$max)==0) {
					
					$message .= '</tr>';
					$message .= '<tr>';			
				}
			}
			$message .= '</tr>';
			$message .= '</table>';		
		}
	}
	return $message;
}

/** 
 * Battle building lost (Premium gold building are excluded)
 */
function warquest_battle_building_lost($ugid) {

   /* input */
	global $level;
	global $output;
	
	/* output */
	global $player;
	 
	/* Check if building damage is less then 100% then return */
	if ($player->damage_buildings<100) {
		return;
	}
	$player->damage_buildings = 0;
	
	/* get random some building */
	$query  = 'select a.bid, a.energy, a.gold, a.income, a.defense, a.discount, a.ugid, c.amount ';
	$query .= 'from building a left join building_group b on a.bgid=b.bgid, player_building c ';
	$query .= 'where b.planet='.$player->planet.' and b.sell=1 and a.bid=c.bid and c.pid='.$player->pid.' ';	
	$query .= 'and a.gold=0 ';
	$query .= 'order by rand() limit '.rand(1,2);
		
	$result = warquest_db_query($query);	
	
	if ( $output->format=="html" ) {

		$message  = '<br/><span class="warning">';
		$message .= t('BATTLE_BUILDINGS_LOST');
		$message .= '</span><br/>'; 
		$message .= '<table>';
		$message .= '<tr>';
		
	} else {
	
		$message = t('BATTLE_BUILDINGS_LOST').' ';	
	}
	
	$count=2000;	
	while ($data = warquest_db_fetch_object($result)) {
				
		$amount=rand(1,round($data->amount/50));
	
		/* Update database */
		warquest_db_building_delete($player->pid, $data->bid, $amount );
		
		if ( $output->format=="html" ) {
		
			$message .= '<td width="90">';
			$message .= warquest_building_image($data, $count++, 1);		
			$message .= '<br/><center>'.$amount.'x</center>';
			$message .= '<td>';

		} else {
		
			$message .= $amout.' '.t('BUILDING_'.$data->bid).' ';
		}	
	}
	
	if ( $output->format=="html" ) {
		$message .= '</tr>';
		$message .= '</table>';
		
	} else {
		
		$message .= '. ';
	}
	
	/* Update income, attack and defense value */
	warquest_netto_income($player);
		
	return $message; 
}

/** 
 * Battle unit lost (Premium gold units are excluded)
 */
function warquest_battle_unit_lost($ugid) {

   /* input */
	global $level;
	global $output;
	
	/* output */
	global $player;
		 
	/* Check if units damage is less then 100% then return */
	if ($player->damage_units<100) {
		return;
	}
	$player->damage_units = 0;
	
	$unit_group = warquest_db_unit_group($ugid);
	
	/* First determinate which units are involved in battle */
	$query  = 'select a.uid, b.amount from unit a, player_unit b where ';
   $query .= 'a.uid=b.uid and b.pid='.$player->pid.' and a.gold=0 ';
	
	if ($unit_group->type==0) {
		$query .= 'and a.ugid in (select ugid from unit_group where type in (2,3,4) and planet='.$unit_group->planet.') ';
	} else {
		$query .= 'and a.ugid='.$ugid.' ';
	}

	$query .= 'order by a.attack desc, a.defense desc';
	$result = warquest_db_query($query);	
	
	$size=($player->alliance * 6);
	
	$tmp="";
	while ($data = warquest_db_fetch_object($result)) {
					
		if ($size >= $data->amount) {			
			$size -= $data->amount;			
		} else {		
			$size -= $size;	
		}
		
		$tmp = $data->uid;
	
		if ($size==0) {
			break;
		}
	}

	if (strlen($tmp)==0) {
		/* No units available */
		return;
	}

	/* get random some units */
	$query  = 'select a.uid, a.gold, a.defense, a.attack, b.amount, a.upkeep from ';
	$query .= 'unit a, player_unit b where ';
	$query .= 'a.uid=b.uid and b.pid='.$player->pid.' and a.uid>='.$tmp.' and a.gold=0 ';
	
	if ($unit_group->type==0) {
		$query .= 'and a.ugid in (select ugid from unit_group where type in (2,3,4) and planet='.$unit_group->planet.') ';
	} else {
		$query .= 'and a.ugid='.$ugid.' ';
	}
	
	$query .= 'order by rand() limit '.rand(1,4);
	
	$result = warquest_db_query($query);	
	
	if ( $output->format=="html" ) {
		
		$message  = '<br/><span class="warning">';
		$message .= t('BATTLE_UNITS_LOST');
		$message .= '</span><br/>'; 
		$message .= '<table>';
		$message .= '<tr>';
		
	} else {
	
		$message = t('BATTLE_UNITS_LOST').' ';	
	}
		
	$count=1000;	
	while ($data = warquest_db_fetch_object($result)) {
			
		$amount=rand(1,round($data->amount/50));
			
		/* Update database */
		warquest_db_unit_delete($player->pid, $data->uid, $amount );
				
		if ( $output->format=="html" ) {
		
			$message .= '<td width="90">';
			$message .= warquest_unit_image($data, $count++);		
			$message .= '<br/><center>'.$amount.'x</center>';
			$message .= '<td>';
		
		} else {
		
			$message .= $amount.' '.t('UNIT_'.$data->uid).' ';
		}
	}
	
	if ( $output->format=="html" ) {
	
		$message .= '</tr>';
		$message .= '</table>';
		
	} else {
		
		$message .= '. ';
	}

	/* Update income, attack and defense value */
	warquest_netto_income($player);
		
	return $message; 
}

/**
 * Calculate who wins by player-player war
 */
function warquest_battle_check($player, $other, $force) {

	$value = 0;

	$attack = warquest_attack_strength($player, $force, 0);
	$defense = warquest_defense_strength($other, $force, 0);
	
	if ($attack > $defense) {
		$value = 1;
	}
	
	return $value;
}

/** 
 * Calculate minimal attack vs defense clan size. Size is minimal 6 to prevent small clans.
 */
function warquest_clan_size($player_clan, $other_clan) {

	/*input */
	global $config;
	
	$count1 = 0; 
	if ( isset($player_clan->cid) ) {
		$query1 =  'select pid from player_clan where approved=1 and cid='.$player_clan->cid;
		$result1 = warquest_db_query($query1);	 
		$count1 = warquest_db_num_rows($result1);
	}

	$count2 = 0;
	if ( isset($other_clan->cid) ) {
		$query2 =  'select pid from player_clan where approved=1 and cid='.$other_clan->cid;
		$result2 = warquest_db_query($query2);	 
		$count2 = warquest_db_num_rows($result2);
	}
	
	/* Get smallest clan size */	
	if ($count1>$count2) {
		$size = $count2;
	} else {
		$size = $count1;
	}

	/* Set Minimal size if needed */
	if ($size<$config["min_clan_size"]) {
		$size=$config["min_clan_size"];
	}

	return $size;
}

/* 
** Show attack and defense clan player information 
*/
function warquest_clan_war_battle($player_clan, $other_clan, $ugid) {

	/* input */
	global $config;
	global $mid;
	global $sid;
	
	$won = 0;
	$lost = 0;
	
	/* Get minimal attack vs defense clan size */
	$size = warquest_clan_size($player_clan, $other_clan);

	$message = (object) array();
		
	if (isset($player_clan->cid) && ($size>0)) {
	
		/* First check clan skills */
		$player_clan_skill_enabled = false;
		$strength = warquest_db_clan_strength($player_clan->cid);
		$cost = $player_clan->attack * $strength * $strength / $config['init_clan_skill_price'];
	 
		if (($player_clan->attack>0) && ($player_clan->money >= $cost)) {
			$player_clan_skill_enabled = true;			
			$player_clan->money -= $cost;
			
			warquest_db_clan_bank_insert($player_clan->cid, 0, ($cost*-1), $player_clan->money, 8);
		}
		
		$other_clan_skill_enabled = false;
		if ( isset($other_clan->cid) ) {
			$strength = warquest_db_clan_strength($other_clan->cid);
			$cost = $other_clan->defense * $strength * $strength / $config['init_clan_skill_price'];
			
			if (($other_clan->defense>0) && ($other_clan->money >= $cost)) {
				$other_clan_skill_enabled = true;			
				$other_clan->money -= $cost;
				
				warquest_db_clan_bank_insert($other_clan->cid, 0, ($cost*-1), $other_clan->money, 9);
			}
		}
		
		/* Second fetch clan members */
		$unit_group = warquest_db_unit_group($ugid);
	
		/* Fetch all attack clan war members */
		$query1  = 'select b.name, b.pid, b.country, b.alliance, b.lid from player_clan a, player b where ';
		$query1 .= 'a.approved=1 and a.pid=b.pid and a.cid='.$player_clan->cid.' order by rand() desc limit 0,'.$size;
		$result1 = warquest_db_query($query1);	 
		
		/* Fetch all defense clan war members */
		if ( isset($other_clan->cid) ) {
			$query2  = 'select b.name, b.pid, b.country, b.alliance, b.lid from player_clan a, player b where ';
			$query2 .= 'a.approved=1 and a.pid=b.pid and a.cid='.$other_clan->cid.' order by rand() desc limit 0,'.$size;
			$result2 = warquest_db_query($query2);	 
		}
			
		$message->body  = '<br/><br/>';
		$message->body .= '<table>';
		
		$message->body .= '<tr>';
		
		$message->body .= '<th width="140" valign="top">';
		$message->body .= $player_clan->name.' '.t('GENERAL_CLAN');
		$message->body .= '</th>';
		
		$message->body .= '<th width="100" valign="top">';
		$message->body .= t('PLAYER_ATTACK_STRENGTH');
		if ($player_clan_skill_enabled) {
			$message->body .= " *";
		}
		$message->body .= '</th>';
		
		$message->body .= '<th width="140" valign="top">';
		if ( isset($other_clan->cid) ) {
			$message->body .= $other_clan->name;
		} else {
			$message->body .= '?'; 
		}
		$message->body .= ' '.t('GENERAL_CLAN');
		$message->body .= '</th>';
		
		$message->body .= '<th width="100" valign="top">';
		$message->body .= t('PLAYER_DEFENSE_STRENGTH');
		if ($other_clan_skill_enabled) {
			$message->body .= " *";
		}
		$message->body .= '</th>';
		
		$message->body .= '<th width="60" valign="top">';
		$message->body .= t('GENERAL_RESULT');
		$message->body .= '</th>';
				
		$message->body .= '</tr>';
		
		/* third compare each clan member */
		for ($i=0; $i<$size; $i++) {
		
			$attack=0;
			$data1 = warquest_db_fetch_object($result1);
			if ( isset($data1->pid) ) {		

				if ($player_clan_skill_enabled) {
					$attack = warquest_attack_strength($data1, $ugid, $player_clan);
				} else {
					$attack = warquest_attack_strength($data1, $ugid, 0);
				}				
			}
		
			$defense = 0;
			if ( isset($other_clan->cid) ) {
				$data2 = warquest_db_fetch_object($result2);
				if ( isset($data2->pid)) {
				
					if ($other_clan_skill_enabled) {
						$defense = warquest_defense_strength($data2, $ugid, $other_clan);
					} else {
						$defense = warquest_defense_strength($data2, $ugid, 0);
					}
				}
			}
			
			$message->body .= '<tr>';
		
			$message->body .= '<td style="border-top:1px solid;border-color:gray;">';
			if ( isset($data1->pid) ) {
				$message->body .= player_format($data1->pid, $data1->name, $data1->country);
			} else {
				$message->body .= '&nbsp;';
			}	
			$message->body .= '</td>';
						
			$message->body .= '<td style="border-top:1px solid;border-color:gray;">';
			if ( isset($data1->pid) ) {
			
				if ($player_clan_skill_enabled) {
					$message->body .= warquest_link('mid='.$mid.'&sid='.PAGE_ATTACK.'&oid='.$data1->pid.'&uid='.$unit_group->type.'&cid='.$player_clan->cid,
						number_format($attack,0,",","."), "attack_strenght");			
				} else {
					$message->body .= warquest_link('mid='.$mid.'&sid='.PAGE_ATTACK.'&oid='.$data1->pid.'&uid='.$unit_group->type,
						number_format($attack,0,",","."), "attack_strenght");		
				}
			} else {
				$message->body .= '0';
			}
			$message->body .= '</td>';
			
			$message->body .= '<td style="border-top:1px solid;border-color:gray;">';
			if ( isset($other_clan->cid) && isset($data2->pid) ) {
				$message->body .= player_format($data2->pid, $data2->name, $data2->country);
			} else {
				$message->body .= '&nbsp;';
			}
			$message->body .= '</td>';
			
			$message->body .= '<td style="border-top:1px solid;border-color:gray;">';			
			if (isset($other_clan->cid) && isset($data2->pid)) {
			
				if ($other_clan_skill_enabled) {
					$message->body .= warquest_link('mid='.$mid.'&sid='.PAGE_DEFENCE.'&oid='.$data2->pid.'&uid='.$unit_group->type.'&cid='.$other_clan->cid,
						number_format($defense,0,",","."), "defense_strenght");
				} else {
					$message->body .= warquest_link('mid='.$mid.'&sid='.PAGE_DEFENCE.'&oid='.$data2->pid.'&uid='.$unit_group->type,
						number_format($defense,0,",","."), "defense_strenght");
				}
			} else {
				$message->body .= '0';
			}
			$message->body .= '</td>';
			
			$message->body .= '<td style="border-top:1px solid;border-color:gray;">';
			
			if ($attack > $defense) {
			
				$message->body .= t('GENERAL_WON');
				$won++;
				
			} else {
			
				$message->body .= t('GENERAL_LOST');
				$lost++;
			}
			$message->body .= '</td>';
			
			$message->body .= '</tr>';				
		}		
		
		$message->body .= '<tr>';
		
		$message->body .= '<td colspan="5" style="border-top:1px solid;border-color:gray;">';
		$message->body .= '<div class="small">';
		if ($other_clan_skill_enabled || $player_clan_skill_enabled) {
			$message->body .= t('CLAN_SKILL_ENABLED');
		}
		$message->body .= '</div>';
		$message->body .= '</td>';
	
		$message->body .= '</tr>';
		
		$message->body .= '</table>';	
	}
	
	$message->outcome=1;
	
	if ($lost>$won) {
		$message->outcome=0;
	}
	return $message;
}

function warquest_clan_income_update($player_clan,$other_clan) {

	/* input */
	global $player;
	
	warquest_netto_income($player);
	
	if ( isset($player_clan->cid) ) {
		
		$query1 = 'select pid from player_clan where cid='.$player_clan->cid.' and pid<>'.$player->pid;
		$result1 = warquest_db_query($query1);	

		while ($data1=warquest_db_fetch_object($result1)) {
		
			$data2 = warquest_db_player($data1->pid);
			warquest_netto_income($data2);
			warquest_db_player_update($data2);
		}
	}
			
	if ( isset($other_clan->cid) ) {
		
		$query1 = 'select pid from player_clan where cid='.$other_clan->cid;
		$result1 = warquest_db_query($query1);	

		while ($data1=warquest_db_fetch_object($result1)) {
		
			$data2 = warquest_db_player($data1->pid);
			warquest_netto_income($data2);
			warquest_db_player_update($data2);
		}
	}
}

/*
** -----------
** ACTIONS
** -----------
*/

function warquest_battle_do($planet, $ugid) {
	  
	/* input */
	global $mid;
	global $sid;
	global $uid;
	global $config;
	global $level;
		
	/* output */
	global $other;
	global $player;
	global $output;
	
	if (!isset($other->pid)) {
		
		/* No enemy selected */
		$message = t('BATTLE_NO_PLAYER_AVAILABLE');
				
		$output->popup .= warquest_box_icon("warning", $message);
		
		return;		
	}	
	
	$premium = strtotime($player->premium_date) - time();

	$max = $config["max_money_win"];
	if ($premium>0) {
		$max *= 3;
	}
	
	/* First increase robot strength, if possible */
	warquest_robot_trade($other, $planet);

	$health_winner = rand(1,10);	
	$health_losser = rand(8,20);
	
	$exp = rand(1, (round($player->lid/10)+5));
	if ($premium>0) {
		$exp *= 2;
	}
	
	/* Check information about select force */
	$query1 = 'select type from unit_group where ugid='.$ugid;
	$result1 = warquest_db_query($query1);	
	$data1 = warquest_db_fetch_object($result1);	
		
	
	/* Check if defender is ally */
	$query = 'select approved from player_player where pid1='.$player->pid.' and pid2='.$other->pid;		
	$result2 = warquest_db_query($query);	
	$data2 = warquest_db_fetch_object($result2);			
					
	if ($sid==PAGE_BOUNTY) {
	
		/* Fetch bounty money amount */
		$query = 'select amount, experience from bounty where id='.$uid;
		$result3 = warquest_db_query($query);	 
		$data3 = warquest_db_fetch_object($result3);	
		
		if (!isset($data3->experience)) {
			return;
		}
	}
	
	$query4 = 'select uid from unit a, unit_group b where a.ugid=b.ugid and b.planet='.$planet;
	$result4 = warquest_db_query($query4);	
	$data4 = warquest_db_fetch_object($result4);
	$count4 = warquest_db_num_rows($result4);
	
	if ($count4==0) {
		
		$message = t('BATTLE_NO_UNITS_AVAILABLE');
		$output->popup .= warquest_box_icon("warning", $message);
		
	} else if ($player->lid==0) {
			
		$message = t('BATTLE_UNLOCKED', t('GENERAL_PLANET_1'), 1).' '.t('BATTLE_FIRST_MISSION');
		$output->popup .= warquest_box_icon("locked", $message);
		
	} else if ($player->ammo<=0) {
	
		$message = t('BATTLE_AMMO_LOW');
		$link = warquest_link('mid='.MENU_HOME.'&sid='.PAGE_RESTORE, t('LINK_RESTORE'), 'restore');		
		$output->popup .= warquest_box_icon("warning", $message, $link);
		
	} else if ($player->health<$config["init_health_min"]) {
	
		$message = t('BATTLE_ATTACKER_HEALTH_LOW');		
		$link = warquest_link('mid='.MENU_HOME.'&sid='.PAGE_RESTORE, t('LINK_RESTORE'), 'restore');
		$output->popup .= warquest_box_icon("warning", $message, $link);
	
	} else if ($other->health<$config["init_health_min"]) {
	
		$message = t('BATTLE_DEFENDER_HEALTH_LOW', player_format($other->pid, $other->name, $other->country));		
		$link = warquest_link('mid='.$mid.'&sid='.$sid.'&oid='.$other->pid.'&uid='.$uid.'&eid='.EVENT_BATTLE_NORMAL, t('LINK_ATTACK') ,'attack');
		$output->popup .= warquest_box_icon("warning", $message, $link);
		
		/* Update battle timestamp */
		$other->last_battle = date("Y-m-d H:i:s");
		
	} else if (isset($data2->approved) && ($data2->approved==1)) {
	
		$message = t('BATTLE_ALLY_NO_ATTACK', player_format($other->pid, $other->name, $other->country));
		$output->popup .= warquest_box_icon("warning", $message);
		
		/* Update last battle timestamp */
		$other->last_battle = date("Y-m-d H:i:s");
	
	} else if (($planet==PLANET_MOON) && ($player->lid<100)) {
	
		$message = t('BATTLE_UNLOCKED', t('GENERAL_PLANET_'.$planet), 100);
		$output->popup .= warquest_box_icon("locked", $message);
	
	} else if (($planet==PLANET_MARS) && ($player->lid<150)) {
	
		$message = t('BATTLE_UNLOCKED', t('GENERAL_PLANET_'.$planet), 150);
		$output->popup .= warquest_box_icon("locked", $message);
		
	} else if (($planet==PLANET_MERCURY) && ($player->lid<200)) {
	
		$message = t('BATTLE_UNLOCKED', t('GENERAL_PLANET_'.$planet), 200);
		$output->popup .= warquest_box_icon("locked", $message);

	} else if (($planet==PLANET_NEPTUNE) && ($player->lid<250)) {
	
		$message = t('BATTLE_UNLOCKED', t('GENERAL_PLANET_'.$planet), 250);		
		$output->popup .= warquest_box_icon("locked", $message);
		
	} else if (warquest_battle_check($player, $other, $ugid)==1) {
		
		/* Player won */
		$output->result = true;
		
		/* Update money */
		$tmp = "";		
		if ($data1->type==5) {
						
			if ($other->bank2 > $other->bank3) {
				$id = 2;
			} else {
				$id = 3;
			}
			
			/* Espionage steals from bank account */	
			switch ( $id ) {
			
				case 2: 	$money = round((1/rand(10,15)) * $other->bank2);
				
							/* Prevent to big money wons */
							if ($money > $max ) {
								$money = $max + rand(10000, 600000);
							}
			
							if ($money>0) {
								$other->bank2 -= $money;
								warquest_db_bank_insert($other->pid, $player->pid, 2, ($money*-1), $other->bank2, 5);
							}
							break;

				case 3: 	$money = round((1/rand(10,15)) * $other->bank3);
							
							/* Prevent to big money wons */
							if ($money > $max ) {
								$money = $max + rand(10000, 600000);
							}
							
							if ($money>0) {
								$other->bank3 -= $money;
								warquest_db_bank_insert($other->pid, $player->pid, 3, ($money*-1), $other->bank3, 5);
							}
							break;				
			}
			
			$log = 'Battle espionage lost, lost '.number_format2($money).' ['.$player->pid.']';
			warquest_user_log($other, $log);
			
			/* Espionage attack won increase rebel counter of opponent */
			$other->rebel_status += rand(2,10);
			$tmp = warquest_rebel_check($other);
			
			/* Add stolen money to cash account */
			$player->money += $money;
			
			$log = 'Battle espionage won, won '.number_format2($money).' ['.$other->pid.']';		
			warquest_user_log($player, $log);

		} else {
		
			/* Steal from cash account */	
			$money = round( (1/rand(10,15)) * $other->money);
			if ($money < 0) $money = 0;
			
			/* Prevent to big money wons */
			if ($money > $max ) {
				$money = $max  + rand(10000, 600000);
			}
			
			$player->money += $money;
			
			$log = 'Battle won, won '.number_format2($money).' ['.$other->pid.']';		
			warquest_user_log($player, $log);
			
			$other->money -= $money;
			
			$log = 'Battle lost, lost '.number_format2($money).' ['.$player->pid.']';		
			warquest_user_log($other, $log);
		} 
				
		$player->ammo -= 1;
		$player->won += 1;
		$player->experience += $exp;
		$player->health -= $health_winner;
		
		$maintenance = warquest_db_maintenance($player, $planet);
			
		if ($level->unit_lost==1) {			
			$player->damage_units += round(((100-$maintenance)/100)* ($health_winner/2) );
		}
		
		if ($level->building_lost==1) {			
			$player->damage_buildings += round(((100-$maintenance)/100) * rand(1,2));
		}
	
		/* update defender */
		$other->health -= $health_losser;
		$other->lost += 1;
		$other->last_battle = date("Y-m-d H:i:s");
		$other->news_notification++;
		
		$maintenance = warquest_db_maintenance($other, $planet);
	
		if ($level->unit_lost==1) {			
			$other->damage_units += round(((100-$maintenance)/100)* ($health_losser/2) );
		}
		
		if ($level->building_lost==1) {	
			$other->damage_buildings += round(((100-$maintenance)/100) * rand(1,4));
		}
							
		/* Update battle log. */
		if ($sid==PAGE_BOUNTY) {	
			warquest_db_battle_insert($player->pid, $other->pid, $money, $health_losser, $data3->experience, 1, $ugid);
		} else {
			warquest_db_battle_insert($player->pid, $other->pid, $money, $health_losser, 0, 1, $ugid);
		}
				
		if ($player->ammo > 0) {
			warquest_robot_battle($player, $other);
		}
	
		/* Check if next level is reached */
		warquest_nextlevel($player);

		/* Check if battle award is won */
		warquest_battle_award_won($player);
		
		$message = t('BATTLE_WON', 
					strtolower(t('GENERAL_PLANET_'.$planet)).' '.strtolower(t('UNIT_GROUP_'.$ugid)),
					player_format($other->pid, $other->name, $other->country),
					health_format($health_winner),
					health_format($health_losser), 
					$other->name,
					money_format1($money),
					experience_format($exp));
		
		if ($other->health < $config["init_health_min"]) {
		
			/* Add bonus */
			$money = 5000 * $player->lid * rand(1,3);
			$player->money += $money;
			
			$log = 'Battle surrender bonus '.number_format2($money);		
			warquest_user_log($player, $log);
						
			$message .= '<br/><br/>'.t('BATTLE_HOSPITAL_BONUS', 
					$other->name, 
					money_format1($money));
		}
		
		if ($sid==PAGE_BOUNTY) {		
			/* Bounty attack succesfull */
			$player->money += $data3->amount;			
				
			$other->experience -= $data3->experience;
			if ($other->experience<0) {
				$other->experience=0;
			}
					
			warquest_db_bounty_delete($uid);	
			$message .= '<br/><br/>'.t('BATTLE_BOUNTY_BONUS', money_format1($data3->amount)); 						
			
			$log = 'Battle bounty bonus '.number_format2($data3->amount);		
			warquest_user_log($player, $log);
		}
	
		if ($data1->type==5) {
		
			if (strlen($tmp)>0) {	
			
				$message .= '<br/><br/>';
				$message .= t('BATTLE_REBEL_UPDATE1', $other->name, $tmp); 														
				$message .= '<br/><br/>';
				$message .= warquest_ui_map($other, $planet);
				
				$player->rebel++;
				
				/* Check if battle award is won */
				warquest_rebel_award_won($player);
				
			} else {
			
				if ($other->rebel_status==101) {
			
					$message .= '<br/><br/>';
					$message .= t('BATTLE_REBEL_UPDATE3'); 
					$message .= '<br/><br/>';
					$message .= warquest_ui_map($other, $planet);
					
					$other->rebel_status=99;
					
				} else {
				
					$message .= '<br/><br/>';
					$message .= t('BATTLE_REBEL_UPDATE2', $other->name, health_format($other->rebel_status)); 
				}
			}
		}
			
		$message .= warquest_show_attack_army($player, $ugid);
		$message .= warquest_show_defense_army($other, $ugid);
		$message .= warquest_battle_unit_lost($ugid);
		$message .= warquest_battle_building_lost($ugid);
		
		$message .= warquest_lootoption($player->lid);
				
		if ($sid!=PAGE_BOUNTY) {
			$link = warquest_link('mid='.$mid.'&sid='.$sid.'&oid='.$other->pid.'&uid='.$uid.'&eid='.EVENT_BATTLE_NORMAL,t('LINK_ATTACK'), 'attack-0');
		} else {
			/* If player wins during bounty hunting, no repeat attack needed */
			$link = "";
		}

		$output->popup .= warquest_box("info", $message, $link);
		
		warquest_sound('battle'.rand(1,8).'.mp3');
				
	} else {
		
		/* Player Lost */
		$output->result = false;
		
		$player->ammo -= 1;
		$player->health -= $health_losser;
		$player->lost += 1;
		
		$maintenance = warquest_db_maintenance($player, $planet);
	
		if ($level->unit_lost==1) {
			$player->damage_units += round(((100-$maintenance)/100)* ($health_losser/2));
		}

		if ($level->building_lost==1) {
			$player->damage_buildings += round(((100-$maintenance)/100) * rand(1,4));
		}
					
		/* Update defender */
		$other->experience += $exp;
		$other->health -= $health_winner;
		$other->won += 1;
		$other->last_battle = date("Y-m-d H:i:s");
		$other->news_notification++;
		
		$maintenance = warquest_db_maintenance($other, $other->planet);
		
		if ($level->unit_lost==1) {
			$other->damage_units += round(((100-$maintenance)/100)* ($health_winner/2));
		}
		
		if ($level->building_lost==1) {
			$other->damage_buildings += round(((100-$maintenance)/100) * rand(1,2));
		}
		
		/* Update battle log. */
		warquest_db_battle_insert($player->pid, $other->pid, 0, $health_winner, $exp, 0, $ugid);
		
		if ($player->ammo > 0) {
			warquest_robot_battle($player, $other);
		}
	
		/* Check if next level is reached */
		warquest_nextlevel($player);

		/* Check if next won level is reached */
		warquest_battle_award_won($player);
			
		$message =  t('BATTLE_LOST', 
			strtolower(t('GENERAL_PLANET_'.$planet)).' '.strtolower(t('UNIT_GROUP_'.$ugid)),
			player_format($other->pid, $other->name, $other->country),
			health_format($health_losser),
		   health_format($health_winner),
		   $other->name);

		$message .= warquest_show_attack_army($player, $ugid);
		$message .= warquest_show_defense_army($other, $ugid);
		$message .= warquest_battle_unit_lost($ugid);
		$message .= warquest_battle_building_lost($ugid);
		
		$link =  warquest_link('mid='.$mid.'&sid='.$sid.'&oid='.$other->pid.'&uid='.$uid.'&eid='.EVENT_BATTLE_NORMAL,t('LINK_ATTACK'), 'attack-0');
		$output->popup .= warquest_box("warning", $message, $link);
		
		warquest_sound('battle'.rand(1,8).'.mp3');
	}
	
	/* Save other player direcly else battle view is now updated! */
	if ($other->pid!=0) {

		/* Update other player timers (after) */
		warquest_update_timers($other);
		
		/* Save other player data; */
		warquest_db_player_update($other);
	}
}

function warquest_player_bounty_do() {

	/* input */
	global $other;
	
	/* output */
	global $player;
	global $output;
	
	/* Calculate bounty price */
	$money = $other->lid * $other->lid * $other->lid * 100;
	
	/* Calculate target experience lose */
	$level_max = warquest_db_level($other->lid);
	$level_min = warquest_db_level($other->lid-1);	
	$experience = $level_max->experience - $level_min->experience;	
	
	$exp = round((1/rand(20,30)) * $experience); 
	if ($exp > $other->experience) {
		$exp = $other->experience-1;
	}
	if ($exp<0) {
	  $exp=0;
	}
		
	if ( $player->money < $money) {
		
		$message = t('BATTLE_NO_BOUNTY_MONEY', 
							money_format2($money), 
							player_format($other->pid, $other->name, $other->country));		
							
		$output->popup .= warquest_box_icon("warning", $message);
				
	} else {
	
		if (warquest_db_bounty_possible($other->pid, $player->pid)==0) {		
	
			/* Pay the bounty price */
			$player->money -= $money;
			$player->bounty++;
			$player->experience++;
		
			$log = 'Set bounty for '.number_format2($money);		
			warquest_user_log($player, $log);
					
			/* Insert bounty event */
			warquest_db_bounty_insert($other->pid, $player->pid, $money, $exp);
		
			/* Inform other player with message */
			warquest_db_battle_insert($player->pid, $other->pid, $money, 0, $exp, 0, 0, 1);
			
			/* Set news flag */
			$other->news_notification++;
			
			/* Update battle timestamp */
			$other->last_battle = date("Y-m-d H:i:s");
						
			warquest_bounty_award_won($player);
			
			/* Update other player timers (after) */
			warquest_update_timers($other);
		
			/* Save other player direcly else battle view is now updated! */
			warquest_db_player_update($other);
			
			/* Check if next level is reached */
			warquest_nextlevel($player);
		
			$message = t('BATTLE_BOUNTY_SET', 
					money_format2($money), 
					player_format($other->pid, $other->name, $other->country), 
					$other->name, 
					number_format($exp,0,",","."));
							
			$output->popup .= warquest_box_icon("info", $message);
		}
	}
}

function warquest_clan_war_battle_do() {
	
	/* input */
	global $mid;
	global $sid;
	global $uid;
	global $config;
	
	/* output */
	global $player;
	global $level;
	global $output;
	
	$health_winner = rand(8,15);
	$health_losser = rand(10,20);
	$exp = rand(1, (round($player->lid/10)+5));
			
	/* Fetch player clan data */	
	$data = warquest_db_player_clan($player->pid);
	
	$money = 0;
	$player_clan = 0;
	if ( isset($data->cid) ) {
	
		$player_clan = warquest_db_clan($data->cid);
		
		$query1 = 'select sid from sector where cid='.$data->cid.' and planet='.$player->planet;
		$result1 = warquest_db_query($query1);	
		$count1 = warquest_db_num_rows($result1);
	
		$money = (($count1+1) * 2000 * ($player->lid*9))+ rand(10000, 60000);	
	}
			
	/* Fetch sector data */	
	$sector = warquest_db_sector($uid);

	/* Fetch other clan data */	
	$other_clan = warquest_db_clan($sector->cid);
			
	/* Get battle result */
	$result = warquest_clan_war_battle($player_clan, $other_clan, warquest_get_default_force());
		
	if ( !isset($player_clan->cid) || ($data->approved==0)) { 
	
		$message = t('BATTLE_NO_CLAN');
		$output->popup .= warquest_box_icon("warning", $message);
		
	} else if ($player_clan->cid == $sector->cid) {
	
		$message = t('BATTLE_SECTOR_ALL_CONQUERED');
		$output->popup .= warquest_box_icon("warning", $message);
	
	} else if ($player->ammo<=0) {
	
		$message = t('BATTLE_AMMO_LOW');
		$link = warquest_link('mid='.MENU_HOME.'&sid='.PAGE_RESTORE, t('LINK_RESTORE'), 'restore');
		
		$output->popup .= warquest_box_icon("warning", $message, $link);
		
	} else if ($player->health<$config["init_health_min"]) {
	
		$message = t('BATTLE_ATTACKER_HEALTH_LOW');
		$link = warquest_link('mid='.MENU_HOME.'&sid='.PAGE_RESTORE, t('LINK_RESTORE'), 'restore');
		$output->popup .= warquest_box_icon("warning", $message, $link);
		
	} else if ($result->outcome==1) {
			
		/* PLAYER WON */
		
		/* Update attack clan stats */				
		$player_clan->won++;
		warquest_db_clan_update($player_clan);
	
		/* Update defend clan stats, if possible */
		if (isset($other_clan->cid)) {
			$other_clan->lost++;
			warquest_db_clan_update($other_clan);
		}
		
		/* update player stats */
		$player->ammo -= 1;
		$player->won++;		
		$player->experience += $exp;
		$player->health -= $health_winner;
		$player->last_battle = date("Y-m-d H:i:s");
		
		$maintenance = warquest_db_maintenance($player, $player->planet);
			
		if ($level->unit_lost==1) {			
			$player->damage_units += round(((100-$maintenance)/100)* ($health_winner/2) );
		}
		
		if ($level->building_lost==1) {			
			$player->damage_buildings += round(((100-$maintenance)/100) * rand(1,2));
		}
		
		$message = t('BATTLE_CLAN_WON', 
					clan_format($player_clan),
					strtolower(t('GENERAL_PLANET_'.$player->planet)).' '.strtolower(t('UNIT_GROUP_'.warquest_get_default_force())),
					clan_format($other_clan),
					health_format($health_winner),
					experience_format($exp),
					money_format1($money));
		
		$player->money += $money;
		
		if ($sector->damage >= ($config["max_sector_damage"]-1) ) {
			
			/* Sector conquered (because of max damage)*/
			$sector->damage = 0;
			$sector->cid = $player_clan->cid;
			
			
			warquest_db_sector_update($sector);
			
			$message .= t('BATTLE_CLAN_SECTOR_CONQUER');
			
			/* Update clan players hourly income */
			warquest_clan_income_update($player_clan, $other_clan);
					
		} else {
		
			/* Sector damage increase with 1 */
			$sector->damage++;
			
			warquest_db_sector_update($sector);
		
			$message .= t('BATTLE_CLAN_SECTOR_DAMAGE', 
									alliance_format(($sector->damage/$config["max_sector_damage"])*100) );			
		}
						
		$message .= $result->body;		
		$message .= warquest_battle_unit_lost(warquest_get_default_force());
		$message .= warquest_battle_building_lost(warquest_get_default_force());
		$message .= warquest_lootoption($player->lid);
		
		$link = warquest_link('mid='.$mid.'&sid='.$sid.'&uid='.$uid.'&eid='.EVENT_BATTLE_CLAN_WAR,t('LINK_ATTACK'), 'attack-0');
	
		$output->popup .= warquest_box("info", $message, $link);
		
		/* Check if next level is reached */
		warquest_nextlevel($player);
		
		/* Check if battle award is won */
		warquest_battle_award_won($player);
				
		$log = 'Clan war won, won '.number_format2($money).' ['.$player->pid.']';		
		warquest_user_log($player, $log);
		
		warquest_sound('battle'.rand(1,8).'.mp3');
			
	} else {
		
		/* PLAYER LOST */

		/* Update attack clan stats */
		$player_clan->lost++;
		warquest_db_clan_update($player_clan);
		
		/* Update defend clan stats */
		if (isset($other_clan->won)) {
			$other_clan->won++;
			warquest_db_clan_update($other_clan);
		}
		
		/* Update player stats */
		$player->ammo -= 1;
		$player->lost++;
		$player->health -= $health_losser;
		$player->last_battle = date("Y-m-d H:i:s");
		
		$maintenance = warquest_db_maintenance($player, $player->planet);
			
		if ($level->unit_lost==1) {			
			$player->damage_units += round(((100-$maintenance)/100)* ($health_losser/2) );
		}
		
		if ($level->building_lost==1) {			
			$player->damage_buildings += round(((100-$maintenance)/100) * rand(1,4));
		}
		
		$message = t('BATTLE_CLAN_LOST',
					clan_format($player_clan),
					strtolower(t('GENERAL_PLANET_'.$player->planet)).' '.strtolower(t('UNIT_GROUP_'.warquest_get_default_force())),
					clan_format($other_clan),
					health_format($health_losser));
		
		$message .= $result->body;			
		$message .= warquest_battle_unit_lost(warquest_get_default_force());
		$message .= warquest_battle_building_lost(warquest_get_default_force());
			
		$link = warquest_link('mid='.$mid.'&sid='.$sid.'&uid='.$uid.'&eid='.EVENT_BATTLE_CLAN_WAR,t('LINK_ATTACK'), 'attack-0');
		
		$output->popup .= warquest_box("warning", $message, $link);
		
		warquest_sound('battle'.rand(1,8).'.mp3');
	}
}

/*
** -----------
** UI
** -----------
*/

/**
 * Enemy Battle form
 */
function warquest_battle_enemies_form() {

	/* input */
	global $mid;
	global $sid;
	global $player;	
	global $config;	
		
	/* output */
	global $page; 
	global $output;
	
	$output->title = t('BATTLE_GENERAL_TITLE');
		
	$query = 'select uid from unit a, unit_group b where a.ugid=b.ugid and b.planet='.$player->planet;
	$result = warquest_db_query($query);	
	$data = warquest_db_fetch_object($result);
	$count = warquest_db_num_rows($result);
	
	if ($count==0) {
		
		$page .= warquest_box_icon('info', t('BATTLE_NO_UNITS_AVAILABLE'));
		
	} else if ($player->lid==0) {
		
		$message = t('BATTLE_FIRST_MISSION');		
		
		$link = warquest_link('mid='.MENU_MISSIONS.'&sid='.PAGE_MISSION_PLAYER.'&ssid='.PAGE_MISSION_TRAINING, t('LINK_MISSIONS'), "mission-0");
		
		$page .= warquest_box_icon('locked', $message, $link);
			
	} else if (($player->planet==PLANET_MOON) && ($player->lid<100)) {
			
		$message = t('BATTLE_UNLOCKED', t('GENERAL_PLANET_'.$player->planet), 100);
		$page .= warquest_box_icon('locked', $message);
		
	} else if (($player->planet==PLANET_MARS) && ($player->lid<150)) {
		
		$message = t('BATTLE_UNLOCKED', t('GENERAL_PLANET_'.$player->planet), 150);
		$page .= warquest_box_icon('locked', $message);
	
	} else if (($player->planet==PLANET_MERCURY) && ($player->lid<200)) {
			
		$message = t('BATTLE_UNLOCKED', t('GENERAL_PLANET_'.$player->planet), 200);
		$page .= warquest_box_icon('locked', $message);
		
	} else if (($player->planet==PLANET_NEPTUNE) && ($player->lid<250)) {
			
		$message = t('BATTLE_UNLOCKED', t('GENERAL_PLANET_'.$player->planet), 250);
		$page .= warquest_box_icon('locked', $message);
		
	} else if ($player->cease_fire_date > date("Y-m-d H:i:s", time())) {
	
		$value = strtotime($player->cease_fire_date)-time();
	
		$page .= '<script language="JavaScript" src="'.$config["content_url"].'js/countdown4.js" type="text/javascript"></script>';
	
		$tmp = '<div class="countdown"><div id="countdown_time4"></div></div>';		
		$page .= warquest_box_icon('info', t('BATTLE_CEASE_FIRE_PERIOD', $tmp));
		
		$page .= '<script language="JavaScript" type="text/javascript">';
		$page .= "countdown4.init(".$value.", 'countdown_time4', '00:00:00');"; 
		$page .= '</script>';
		
	} else {
				
		/* Get player data */	
		$query  = 'select a.pid, a.lid, a.won, a.lost, a.name, a.experience, a.alliance, a.country, ';
		$query .= 'a.health, a.health_date, a.health_step, ifnull(b.approved, 0) as approved, ';
		$query .= '(select ifnull(id ,0) from bounty where pid1=a.pid and pid2='.$player->pid.') as bounty ';
		$query .= 'from player a left join player_player b ';
		$query .= 'on b.pid2=a.pid and b.pid1='.$player->pid.' where a.pid!='.$player->pid.' ';	
		$query .= 'and a.lid>='.warquest_get_min_attack_level().' ';
		$query .= 'and a.lid<='.warquest_get_max_attack_level().' ';
		$query .= 'and a.cease_fire_date < "'.date("Y-m-d H:i:s", time()).'" ';
		$query .= 'and a.holiday_date < "'.date("Y-m-d H:i:s", time()).'" ';
		
		/* filter out approved alliance */
		if (warquest_db_query_pattern($player, PATTERN_ALLY_LIST)==0) {
			$query .= 'and ifnull(b.approved, 0)=0 '; 
		}
		
		if (warquest_db_query_pattern($player, PATTERN_SORT2)==1) {
			$query .= 'order by a.last_battle asc limit 0, 20'; 
		} else { 		
			$query .= 'order by rand() limit 0, 20';	
		}
		
		$result = warquest_db_query($query);	 
		$count = warquest_db_num_rows($result);

		if ($count==0) {
		
			/* No fighters available */
			$page .= warquest_box_icon("info",t('BATTLE_NO_PLAYER_AVAILABLE'));
				
		} else {
		
			$page .= '<div class="box rows">';
		
			$page .= '<table>';
	
			$page .= '<tr>';
			$page .= '<th width="170">'.t('GENERAL_PLAYER').'</th>';
			$page .= '<th width="45">'.t('GENERAL_LEVEL').'</th>';
			$page .= '<th width="65">'.t('GENERAL_ALLIANCE').'</th>';
			$page .= '<th width="65">'.t('GENERAL_WON').'</th>';
			$page .= '<th width="65">'.t('GENERAL_LOST').'</th>';
			$page .= '<th width="65"></th>';
			$page .= '<th width="65"></th>';
			$page .= "</tr>";

			$count=0;
			while ($data=warquest_db_fetch_object($result)) {
			
				$count++;
				$page .= '<tr>';
	
				$page .= '<td>';
				$page .= player_format($data->pid, $data->name, $data->country, 1);
				
				if (warquest_battle_surrender($data)==1) {
					$page .= warquest_image('other/surrender.png',' width="16" height="16" title="'.t("BATTLE_SURRENDER").'"');
				}
				$page .= '</td>';
				$page .= '<td>'.$data->lid.'</td>';
				$page .= '<td>'.$data->alliance;
				if ($data->approved==1) {
					$page .= ' '.warquest_image('other/ally.png',' width="14" height="12" title="'.t('ALLIANCE_ALLY').'"');
				}
				$page .= '</td>';
				$page .= '<td>'.number_format($data->won,0,",",".").'</td>';
				$page .= '<td>'.number_format($data->lost,0,",",".").'</td>';
		
				$page .= '<td>';
		
				/* Only one active bounty can be set */
				if (($player->lid>=10) && ($data->bounty==0) && ($data->country!="EU") && ($data->approved==0)) {
		
					if (warquest_db_query_pattern($player, PATTERN_BOUNTY)==0) {
						$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_BATTLE_BOUNTY.'&oid='.$data->pid, t('LINK_BOUNTY'), "bounty-".($count+100)).' ';
					} else {
					
						/* Calculate bounty price */
						$money = $data->lid * $data->lid * $data->lid * 100;
						$page .= warquest_link_confirm('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_BATTLE_BOUNTY.'&oid='.$data->pid, t('LINK_BOUNTY'), 
							t('BATTLE_BOUNTY_CONFIRM',number_format($money,0,",",".")));
					}			
				}
				$page .= '</td>';
					
				$page .= '<td align="right">';
				if ( $data->approved==0 ) {
					$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&oid='.$data->pid.'&eid='.EVENT_BATTLE_NORMAL, t('LINK_ATTACK'), "attack-".$count);
				}
				$page .= '</td>';
				$page .= '</tr>';
			}
	
			$page .= '</table>';
			$page .= '</div>';
		}
	}
			
	$page .= '<div class="note">';
	$page .= t('BATTLE_NOTE1').' ';
	$page .= t('BATTLE_RANGE',warquest_get_min_attack_level(), warquest_get_max_attack_level());
	$page .= '</div>';
}

/**
 * Bounty form
 */
function warquest_battle_bounty_form() {

	/* input */
	global $mid;
	global $sid;
	global $player;	
	global $config;	
	
	/* output */
	global $page; 
	global $output;
	
	$output->title = t('BATTLE_BOUNTY_TITLE');
	$lid=10;
	
	$query = 'select uid from unit a, unit_group b where a.ugid=b.ugid and b.planet='.$player->planet;
	$result = warquest_db_query($query);	
	$data = warquest_db_fetch_object($result);
	$count = warquest_db_num_rows($result);
			
	if ($count==0) {
		
		$page .= warquest_box_icon('info', t('BATTLE_NO_UNITS_AVAILABLE'));
		
	} else if (($player->planet==PLANET_MOON) && ($player->lid<100)) {
	
		$message = t('BATTLE_BOUNTY_UNLOCKED', t('GENERAL_PLANET_'.$player->planet), 100);
		$page .= warquest_box_icon('locked', $message);
		
	} else if (($player->planet==PLANET_MARS) && ($player->lid<150)) {
			
		$message = t('BATTLE_BOUNTY_UNLOCKED', t('GENERAL_PLANET_'.$player->planet), 150);
		$page .= warquest_box_icon('locked', $message);
	
	} else if (($player->planet==PLANET_MERCURY) && ($player->lid<200)) {
			
		$message = t('BATTLE_BOUNTY_UNLOCKED', t('GENERAL_PLANET_'.$player->planet), 200);
		$page .= warquest_box_icon('locked', $message);
	
	} else if (($player->planet==PLANET_NEPTUNE) && ($player->lid<250)) {
			
		$message = t('BATTLE_BOUNTY_UNLOCKED', t('GENERAL_PLANET_'.$player->planet), 250);
		$page .= warquest_box_icon('locked', $message);
	
	} else if ($player->lid < $lid) {
	
		$message = t('BATTLE_BOUNTY_UNLOCKED', t('GENERAL_PLANET_1'), $lid);
		$page .= warquest_box_icon('locked', $message);
	
	} else if ($player->cease_fire_date > date("Y-m-d H:i:s", time())) {
	
		$value = strtotime($player->cease_fire_date)-time();
	
		$page .= '<script language="JavaScript" src="'.$config["content_url"].'js/countdown4.js" type="text/javascript"></script>';
	
		$tmp = '<div class="countdown"><div id="countdown_time4"></div></div>';		
		$page .= warquest_box_icon('info', t('BATTLE_CEASE_FIRE_PERIOD', $tmp));
		
		$page .= '<script language="JavaScript" type="text/javascript">';
		$page .= "countdown4.init(".$value.", 'countdown_time4', '00:00:00');"; 
		$page .= '</script>';
	
	} else {
			
		/* Get player data */
		$query  = 'select a.id, a.pid1, a.pid2, a.amount, b.health, b.health_date, b.health_step, b.name, b.country, ';
		$query .= 'e.country as country2, b.lid, b.won, b.lost, b.alliance, ';
		$query .= 'ifnull(c.approved, 0) as approved ';
		$query .= 'from bounty a left join player b on a.pid1=b.pid ';
		$query .= 'left join player e on a.pid2=e.pid ';
		$query .= 'left join player_player c on c.pid2=b.pid and c.pid1='.$player->pid.' ';
		$query .= 'where a.pid1!='.$player->pid.' ';		
		$query .= 'and b.cease_fire_date < "'.date("Y-m-d H:i:s", time()).'" ';
		$query .= 'and b.holiday_date < "'.date("Y-m-d H:i:s", time()).'" ';
		
		/* filter out approved alliance */
		if (warquest_db_query_pattern($player, PATTERN_ALLY_LIST)==0) {
			$query .= 'and ifnull(c.approved, 0)=0 '; 
		}
		
		if ($player->lid < 100) {
			$query .= 'and b.lid between 0 and 99 ';
		} else if ($player->lid < 149) {
			$query .= 'and b.lid between 100 and 149 ';
		}  else if ($player->lid < 199) {
			$query .= 'and b.lid between 150 and 199 ';
		}	else if ($player->lid < 249) {
			$query .= 'and b.lid between 200 and 249 ';
		} else {
			$query .= 'and b.lid > 249 ';
		}
		
		if (warquest_db_query_pattern($player, PATTERN_SORT2)==1) {
			$query .= 'order by b.last_battle asc limit 0, 20'; 
		} else { 		
			$query .= 'order by rand() limit 0, 20';	
		}
	
		$result = warquest_db_query($query);	  
		$count=warquest_db_num_rows($result);

		if ($count==0) {
		
			/* No fighters available */
			$page .= warquest_box_icon("info",t('BATTLE_NO_BOUNTY_PLAYERS'));
				
		} else {
		
			$page .= '<div class="box rows">';
	
			$page .= '<table>';
	
			$page .= '<tr>';
			$page .= '<th width="170">'.t('GENERAL_PLAYER').'</th>';
			$page .= '<th width="45">'.t('GENERAL_LEVEL').'</th>';
			$page .= '<th width="60">'.t('GENERAL_ALLIANCE').'</th>';
			$page .= '<th width="60">'.t('GENERAL_WON').'</th>';
			$page .= '<th width="60">'.t('GENERAL_LOST').'</th>';
			$page .= '<th width="65">'.t('GENERAL_BOUNTY').'</th>';
			$page .= '<th width="80"></th>';
			$page .= "</tr>";

			$count=0;
			while ($data=warquest_db_fetch_object($result)) {
		
				$count++;
				$page .= '<tr>';
				
				$page .= '<td>';
				$page .= player_format($data->pid1, $data->name, $data->country, 1);		
				if (warquest_battle_surrender($data)==1) {
					$page .= warquest_image('other/surrender.png',' width="16" height="16" title="'.t("BATTLE_SURRENDER").'"');
				}	
				$page .= '</td>';
				$page .= '<td>'.$data->lid.'</td>';
				$page .= '<td>'.$data->alliance;
				if ($data->approved==1) {
					$page .= ' '.warquest_image('other/ally.png',' width="14" height="12" title="'.t('ALLIANCE_ALLY').'"');
				}
				$page .= '</td>';
				$page .= '<td>'.number_format($data->won,0,",",".").'</td>';
				$page .= '<td>'.number_format($data->lost,0,",",".").'</td>';
				$page .= '<td>'.money_format2($data->amount).'</td>';
				
				$page .= '<td align="right">';
				if (($player->pid!=$data->pid2) && ($data->approved==0)) {
					$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&oid='.$data->pid1.'&uid='.$data->id.'&eid='.EVENT_BATTLE_NORMAL, t('LINK_ATTACK'), "attack-".$count);
				}
				$page .= '</td>';
				
				$page .= '</tr>';
			}
		
			$page .= '</table>';
			$page .= '</div>';	
		}
	}
	
	$page .= '<div class="note">';
	$page .= t('BATTLE_NOTE2');
	$page .= '</div>';	
}

/**
 * Clan War Form
 */
function warquest_battle_clan_war_form() {

	/* input */
	global $mid;
	global $sid;
	global $player;	
	global $config;	
	
	/* output */
	global $page; 
	global $output;
		
	$output->title = t('BATTLE_CLAN_WAR_TITLE');
	
	$lid=15;
		
	$query = 'select uid from unit a, unit_group b where a.ugid=b.ugid and b.planet='.$player->planet;
	$result = warquest_db_query($query);	
	$data = warquest_db_fetch_object($result);
	$count = warquest_db_num_rows($result);
		
	if ($count==0) {
		
		$page .= warquest_box_icon('info', t('BATTLE_NO_UNITS_AVAILABLE'));
		
	} else if (($player->planet==PLANET_MOON) && ($player->lid<100)) {
	
		$message = t('BATTLE_CLAN_WAR_UNLOCKED', t('GENERAL_PLANET_'.$player->planet), 100);
		$page .= warquest_box_icon('locked', $message);

		$page .= warquest_box("", $message);
		
	} else if (($player->planet==PLANET_MARS) && ($player->lid<150)) {
			
		$message = t('BATTLE_CLAN_WAR_UNLOCKED', t('GENERAL_PLANET_'.$player->planet), 150);
		$page .= warquest_box_icon('locked', $message);
	
	} else if (($player->planet==PLANET_MERCURY) && ($player->lid<200)) {
			
		$message = t('BATTLE_CLAN_WAR_UNLOCKED', t('GENERAL_PLANET_'.$player->planet), 200);
		$page .= warquest_box_icon('locked', $message);
		
	} else if (($player->planet==PLANET_NEPTUNE) && ($player->lid<250)) {
			
		$message = t('BATTLE_CLAN_WAR_UNLOCKED', t('GENERAL_PLANET_'.$player->planet), 250);
		$page .= warquest_box_icon('locked', $message);
			
	} else if ($player->lid < $lid) {
			
		$message = t('BATTLE_CLAN_WAR_UNLOCKED', t('GENERAL_PLANET_'.$player->planet), $lid);
		$page .= warquest_box_icon('locked', $message);

	} else if ($player->cease_fire_date > date("Y-m-d H:i:s", time())) {
	
		$value = strtotime($player->cease_fire_date)-time();
	
		$page .= '<script language="JavaScript" src="'.$config["content_url"].'js/countdown4.js" type="text/javascript"></script>';
	
		$tmp = '<div class="countdown"><div id="countdown_time4"></div></div>';		
		$page .= warquest_box_icon('info', t('BATTLE_CEASE_FIRE_PERIOD', $tmp));
		
		$page .= '<script language="JavaScript" type="text/javascript">';
		$page .= "countdown4.init(".$value.", 'countdown_time4', '00:00:00');"; 
		$page .= '</script>';
	
	} else {	
	
		$page .= '<div class="box">';	
		$page .= warquest_ui_clan_war_map($player, $player->planet, true);
		$page .= '</div>';
	}
	
	$page .= '<div class="note">';
	$page .= t('BATTLE_NOTE_CLAN_WAR');
	$page .= '</div>';
}


function warquest_battle_force_option() {

	/* input */
	global $player;
	global $mid;
	global $sid;
	
	/* output */
	global $page; 
		
	$page .= '<div class="box"><b>';
	$page .= t('BATTLE_FORCE_TYPE');
	$page .= '</b>&nbsp;';

	$query  = 'select ugid, type from unit_group where planet='.$player->planet.' and type!=6 order by type';
	$result = warquest_db_query($query);	
	
	while ($data=warquest_db_fetch_object($result)) {
		
		if (warquest_get_default_force()==$data->ugid) {
			$page .= '<INPUT TYPE="radio" name="force" VALUE="'.$data->ugid.'" checked />'.t('UNIT_GROUP_'.$data->ugid).' ';	
		} else {		
			$page .= '<input type="radio" name="force" value="'.$data->ugid.'"/>'.
								t('UNIT_GROUP_'.$data->ugid).' ';	
								
		}	
	}

	$page .= '</div>';
}

/*
** -------------
** HANDLER
** -------------
*/

/**
 * Battle handler
 */
function warquest_battle() {

	/* input */
	global $eid;
	global $sid;
	global $player;
	global $other;
		
	/* Event handler */
	switch ($eid ) {
	
		case EVENT_BATTLE_NORMAL:  
					warquest_battle_do($player->planet, warquest_get_default_force());
					break;
							  				  
		case EVENT_BATTLE_BOUNTY:	
					warquest_player_bounty_do();
					break;	

		case EVENT_BATTLE_CLAN_WAR:	
					warquest_clan_war_battle_do();
					break;	
					
		case EVENT_SWITCH_PLANET:
					warquest_switch_planet_do();
					break;					  
	}
		
	/* Page handler */
	switch ($sid) {
	
		case PAGE_ENEMIES: 	
					warquest_battle_force_option();
					warquest_battle_enemies_form();	
					break;
			
		case PAGE_BOUNTY:  
					warquest_battle_force_option();
					warquest_battle_bounty_form();	
					break;
					
		case PAGE_CLAN_WAR:  
					warquest_battle_force_option();
					warquest_battle_clan_War_form();	
					break;
	}
	
	warquest_player();
}

/*
** -------------
** THE END
** -------------
*/

?>
