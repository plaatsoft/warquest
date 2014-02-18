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
** PLAYER
** ---------------------------------------------------------------- 
*/

/*
** ---------------------
** PLAYER MAINTENANCE PAGE
** ---------------------
*/

function warquest_maintenance_info_form($other) {

	/* input */
	global $mid;
	global $sid;
	global $player;
		
	/* output */
	global $page;
	global $output;
	
	$total = 0;
	
	$output->title = t('PLAYER_MAINTENANCE_OVERVIEW');
	$page .= '<div class="subparagraph">'.$output->title.'</div>';

	$query  = 'select a.bid, a.maintenance, a.gold, c.amount ';
	$query .= 'from building a left join building_group b on a.bgid=b.bgid, player_building c ';
	$query .= 'where a.bid=c.bid and c.pid='.$other->pid.' and a.maintenance>0 and b.planet='.$player->planet.' ';
	$query .= 'order by a.maintenance desc';
	$result = warquest_db_query($query);

	$page .= '<div class="box">';

	$page .= '<br/>';
	$page .= t('PLAYER_MAINTENANCE_TEXT', 
						warquest_link('mid='.$mid.'&sid='.PAGE_PROFILE.'&oid='.$other->pid, player_format($other->pid, $other->name, $other->country)),
						strtolower(t('GENERAL_PLANET_'.$player->planet)));
	$page .= '<br/><br/>';

	$page .= '<table>';
	$page .= '<tr>';

	$page .= '<td width="110">';
	$page .= '<b>'.t('PLAYER_BUILDING').'</b>';
	$page .= '</td>';
				
	$page .= '<td width="190">';
	$page .= '<b>'.t('PLAYER_NAME').'</b>';
	$page .= '</td>';

	$page .= '<td width="80">';
	$page .= '<b>'.t('PLAYER_AMOUNT').'</b>';
	$page .= '</td>';
	
	$page .= '<td width="160">';
	$page .= '<b>'.t('PLAYER_MAINTENANCE_RATE').'</b>';
	$page .= '</td>';
	
	$page .= '</tr>';
	
	while ($data = warquest_db_fetch_object($result)) {
	
		$page .= '<td>';
		$page .= warquest_building_image($data, 0, 1);
		$page .= '</td>';
		
		$page .= '<td>';
		$page .= '<b>'.t('BUILDING_'.$data->bid).'</b><br/>' ;
		$page .= '</td>';
				
		$page .= '<td>';
		$page .= $data->amount;
		$page .= '</td>';
				
		$page .= '<td>';
		$page .= money_format1($data->maintenance).'%';
		$page .= '</td>';
		
		$page .= '</tr>';
		
		$total += $data->maintenance;		
	}
			
	/* Show horizontal bar */
	$page .= '<tr>';
	$page .= '<td colspan="4">';
	$page .= '<hr>';
	$page .= '</td>';
	$page .= '</tr>';
		
	/* Totals */
	$page .= '<tr>';
	
	$page .= '<td>';
	$page .= '<b></b>';
	$page .= '</td>';
				
	$page .= '<td>';
	$page .= '<b>'.t('PLAYER_TOTAL').'</b>';
	$page .= '</td>';

	$page .= '<td>';
	$page .= '<b></b>';
	$page .= '</td>';
		
	$page .= '<td>';
	$page .= '<b>'.money_format1($total).'% </b>';
	$page .= '</td>';
	
	$page .= '</tr>';
			
	$page .= '</table>';
	
	$page .= '<br/>';
	$page .= '</div>';
}


/*
** ---------------------
** PLAYER DISCOUNT PAGE
** ---------------------
*/

function warquest_discount_info_form($other) {

	/* input */
	global $mid;
	global $sid;
	global $player;
		
	/* output */
	global $page;
	global $output;
	
	$total = 0;
	
	$output->title = t('PLAYER_DISCOUNT_OVERVIEW');
	$page .= '<div class="subparagraph">'.$output->title.'</div>';

	/* Show defense strength of building */
	$query  = 'select a.bid, a.gold, a.discount, c.amount ';
	$query .= 'from building a left join building_group b on a.bgid=b.bgid, player_building c ';
	$query .= 'where a.bid=c.bid and c.pid='.$other->pid.' and a.discount>0 and b.planet='.$player->planet.' ';
	$query .= 'order by a.discount desc';
	$result = warquest_db_query($query);

	$page .= '<div class="box">';

	$page .= '<br/>';
	$page .= t('PLAYER_BUILDING_TEXT', 
						warquest_link('mid='.$mid.'&sid='.PAGE_PROFILE.'&oid='.$other->pid, player_format($other->pid, $other->name, $other->country)),
						strtolower(t('GENERAL_PLANET_'.$player->planet)));
	$page .= '<br/><br/>';

	$page .= '<table>';
	$page .= '<tr>';

	$page .= '<td width="110">';
	$page .= '<b>'.t('PLAYER_BUILDING').'</b>';
	$page .= '</td>';
				
	$page .= '<td width="190">';
	$page .= '<b>'.t('PLAYER_NAME').'</b>';
	$page .= '</td>';

	$page .= '<td width="80">';
	$page .= '<b>'.t('PLAYER_AMOUNT').'</b>';
	$page .= '</td>';
	
	$page .= '<td width="160">';
	$page .= '<b>'.t('PLAYER_DISCOUNT_RATE').'</b>';
	$page .= '</td>';
	
	$page .= '</tr>';
	
	while ($data = warquest_db_fetch_object($result)) {
	
		$page .= '<td>';
		$page .= warquest_building_image($data, 0, 1);
		$page .= '</td>';
		
		$page .= '<td>';
		$page .= '<b>'.t('BUILDING_'.$data->bid).'</b><br/>' ;
		$page .= '</td>';
				
		$page .= '<td>';
		$page .= $data->amount;
		$page .= '</td>';
				
		$page .= '<td>';
		$page .= money_format1($data->discount).'%';
		$page .= '</td>';
		
		$page .= '</tr>';
		
		$total += $data->discount;		
	}
			
	/* Show horizontal bar */
	$page .= '<tr>';
	$page .= '<td colspan="4">';
	$page .= '<hr>';
	$page .= '</td>';
	$page .= '</tr>';
		
	/* Totals */
	$page .= '<tr>';
	
	$page .= '<td>';
	$page .= '<b></b>';
	$page .= '</td>';
				
	$page .= '<td>';
	$page .= '<b>'.t('PLAYER_TOTAL').'</b>';
	$page .= '</td>';

	$page .= '<td>';
	$page .= '<b></b>';
	$page .= '</td>';
		
	$page .= '<td>';
	$page .= '<b>'.money_format1($total).'% </b>';
	$page .= '</td>';
	
	$page .= '</tr>';
			
	$page .= '</table>';
	
	$page .= '<br/>';
	$page .= '</div>';
}

/*
** ---------------------
** CONTINENT INCOME PAGE
** ---------------------
*/

function warquest_continent_income_form($other) {

	/* input */
	global $mid;
	global $sid;
	global $uid;
	global $player;
	global $config;
	
	/* output */
	global $page;
	global $output;
	
	$output->title = t('PLAYER_CONTINENT_OVERVIEW');
	$page .= '<div class="subparagraph">'.$output->title.'</div>';
	
	/* ------------------------------------------------- */
	
	$query  = 'select b.mgid, sum(a.progress) as progress ';
	$query .= 'from player_mission a left join mission b on a.mid=b.mid ';
	$query .= 'left join mission_group c on b.mgid=c.mgid where c.planet='.$player->planet.' ';	
	$query .= 'and a.pid='.$other->pid.' group by mgid';
	$result = warquest_db_query($query);
	
	$page .= '<div class="box">';

	$page .= '<br/>';
	$page .= t('PLAYER_CONTINENT_TEXT', 
						warquest_link('mid='.$mid.'&sid='.PAGE_PROFILE.'&oid='.$other->pid, player_format($other->pid, $other->name, $other->country)),
						strtolower(t('GENERAL_PLANET_'.$player->planet)));
	$page .= '<br/><br/>';

	$page .= warquest_ui_map($other, $player->planet);
	$page .= '<br/>';

	$page .= '<table>';
	$page .= '<tr>';	
	
	$page .= '<td width="200">';
	$page .= '<b>'.t('GENERAL_CONTINENT').'</b>';
	$page .= '</td>';

	$page .= '<td width="150">';
	$page .= '<b>'.t('GENERAL_CONQUERED').'</b>';
	$page .= '</td>';

	$page .= '<td width="150">';
	$page .= '<b>'.t('PLAYER_INCOME').' ['.t('GENERAL_DOLLAR').']</b>';
	$page .= '</td>';

	$page .= '</tr>';
	
	$totalBonus = 0;
	while ($data = warquest_db_fetch_object($result)) {
					
		$page .= '<td>';
		$page .= t('MISSION_GROUP_'.$data->mgid);
		$page .= '</td>';
		
		$page .= '<td>';
		if ($data->mgid==0) {
			$page .= round(($data->progress/100)*100).'%';
		} else {
			$page .= round(($data->progress/2400)*100).'%';
		}
		$page .= '</td>';
		
		$bonus = 0;
		if ($data->progress==2400) {		
			$bonus = $data->mgid * $config["continent_conquer_bonus"];			
			$totalBonus += $bonus;
		}
		
		$page .= '<td>';
		$page .= dollar_format($bonus);
		$page .= '</td>';
								
		$page .= '</tr>';
	}	
	
	/* ------------------------------------------------- */
	
	
	/* Show horizontal bar */
	$page .= '<tr>';
	$page .= '<td colspan="3">';
	$page .= '<hr>';
	$page .= '</td>';
	$page .= '</tr>';
			
	$page .= '<tr>';

	$page .= '<td>';
	$page .= '<b>'.t('PLAYER_TOTAL').'</b>';
	$page .= '</td>';

	$page .= '<td>';
	$page .= '</td>';

	$page .= '<td>';
	$page .= '<b>'.dollar_format($totalBonus).'</b>';
	$page .= '</td>';
			
	$page .= '</tr>';
	$page .= '</table>';
	
	$page .= '<br/>';
	$page .= '</div>';
}

/*
** ---------------------
** CLAN WAR INCOME PAGE
** ---------------------
*/

function warquest_clan_war_income_form($other) {

	/* input */
	global $mid;
	global $sid;
	global $uid;
	global $player;
	global $config;
	
	/* output */
	global $page;
	global $output;
	
	$output->title = t('PLAYER_CLAN_WAR_OVERVIEW');
	
	$clan = warquest_db_player_clan($other->pid);
	
	$count = 0;		
	if ( isset($clan->cid) && ($clan->approved==1) ) { 
	
		$query = 'select sid from sector where cid='.$clan->cid.' and planet='.$player->planet;
		$result = warquest_db_query($query);
		$count = warquest_db_num_rows($result);
	}
		
	$page .= '<div class="subparagraph">'.$output->title.'</div>';
	
	/* ------------------------------------------------- */
		
	$page .= '<div class="box">';

	$page .= '<br/>';
	$page .= t('PLAYER_CLAN_WAR_TEXT', 
						warquest_link('mid='.$mid.'&sid='.PAGE_PROFILE.'&oid='.$other->pid, player_format($other->pid, $other->name, $other->country)),
						strtolower(t('GENERAL_PLANET_'.$player->planet)));
	$page .= '<br/><br/>';

	$page .= warquest_ui_clan_war_map($other, $player->planet, false);
	$page .= '<br/>';
	$page .= '<br/>';

	$page .= '<table>';
	$page .= '<tr>';	
	
	$page .= '<td width="150">';
	$page .= '<b>'.t('GENERAL_SECTORS').'</b>';
	$page .= '</td>';

	$page .= '<td width="200">';
	$page .= '<b>'.t('GENERAL_INCOME_SECTOR').'</b>';
	$page .= '</td>';

	$page .= '<td width="150">';
	$page .= '<b>'.t('GENERAL_TOTAL').'</b>';
	$page .= '</td>';

	$page .= '</tr>';
	
	$page .= '<td>';
	$page .= $count;
	$page .= '</td>';
		
	$page .= '<td>';
	$page .= dollar_format(10000 * $other->lid * $player->planet);
	$page .= '</td>';
							
	$page .= '<td>';
	$page .= dollar_format(warquest_clan_war_income($other, $player->planet));	
	$page .= '</td>';
				
	$page .= '</tr>';
		
	$page .= '</table>';
	
	$page .= '<br/>';
	$page .= '</div>';
}


/*
** ---------------------
** PLAYER UPKEEP PAGE
** ---------------------
*/

function warquest_unit_upkeep_form($other) {

   /* input */
	global $mid;
	global $sid;
	global $player;
	
	/* output */
	global $page;
	global $output;
		
	$output->title = t('PLAYER_UPKEEP_COST');
	$page .= '<div class="subparagraph">'.$output->title.'</div>';
		
	/* Calculate upkeep cost of all player units  */
	$query  = 'select a.uid, a.gold, a.attack, a.defense, a.upkeep, c.amount ';
	$query .= 'from unit a left join unit_group b on a.ugid=b.ugid, ';
	$query .= 'player_unit c where a.uid=c.uid and ';
	$query .= 'c.pid='.$other->pid.' and b.planet='.$player->planet.' and a.upkeep>0 ';	
	$query .= 'order by a.upkeep desc';
	$result = warquest_db_query($query);

	$total = 0;

	$page .= '<div class="box">';

	$page .= '<br/>';
	$page .= t('PLAYER_UPKEEP_TEXT', 
						warquest_link('mid='.$mid.'&sid='.PAGE_PROFILE.'&oid='.$other->pid, player_format($other->pid, $other->name, $other->country)),
						strtolower(t('GENERAL_PLANET_'.$player->planet)));
	$page .= '<br/><br/>';

	$page .= '<table>';
	$page .= '<tr>';	
	
	$page .= '<td width="110">';
	$page .= '<b>'.t('PLAYER_UNIT').'</b>';
	$page .= '</td>';

	$page .= '<td width="220">';
	$page .= '<b>'.t('PLAYER_NAME').'</b>';
	$page .= '</td>';

	$page .= '<td width="80">';
	$page .= '<b>'.t('PLAYER_AMOUNT').'</b>';
	$page .= '</td>';
	
	$page .= '<td width="100">';
	$page .= '<b>'.t('PLAYER_COST').' ['.t('GENERAL_DOLLAR').']</b>';
	$page .= '</td>';

	$page .= '</tr>';

	$totalAmount=0;
	$totalCost=0;
	$count=0;

	while ($data = warquest_db_fetch_object($result)) {
		
		$count++;
		$totalAmount += $data->amount;
				
		$page .= '<td>';
		$page .= warquest_unit_image($data, $count);
		$page .= '</td>';
		
		$page .= '<td>';
		$page .= '<b>'.t('UNIT_'.$data->uid).'</b><br/>' ;
		$page .= t('GENERAL_UPKEEP').': '.dollar_format($data->upkeep);
		$page .= '</td>';
				
		$page .= '<td>';
		$page .= number_format2($data->amount);
		$page .= '</td>';
		
		$cost = $data->amount * $data->upkeep;
		$totalCost += $cost;
		
		$page .= '<td>';
		$page .= money_format1($cost);
		$page .= '</td>';
		
		$page .= '</tr>';
	}
	
	/* Show horizontal bar */
	$page .= '<tr>';
	$page .= '<td colspan="4">';
	$page .= '<hr>';
	$page .= '</td>';
	$page .= '</tr>';
		
	/* Totals */
	$page .= '<tr>';
	
	$page .= '<td>';
	$page .= '<b></b>';
	$page .= '</td>';
				
	$page .= '<td>';
	$page .= '<b>'.t('PLAYER_TOTAL').'</b>';
	$page .= '</td>';

	$page .= '<td>';
	$page .= '<b>'.number_format($totalAmount,0,",",".").'</b>';
	$page .= '</td>';
		
	$page .= '<td>';
	$page .= '<b>'.money_format1($totalCost).'</b>';
	$page .= '</td>';
	
	$page .= '</tr>';
			
	$page .= '</table>';
	
	$page .= '<br/>';
	$page .= '</div>';
}


/*
** ---------------------
** PLAYER INCOME PAGE
** ---------------------
*/

function warquest_building_income_form($other) {

	/* input */
	global $mid;
	global $sid;
	global $player;
		
	/* output */
	global $page;
	global $output;
	
	$totalMoney = 0;
	
	$output->title = t('PLAYER_BUILDING_OVERVIEW');
	$page .= '<div class="subparagraph">'.$output->title.'</div>';

	/* Show defense strength of building */
	$query  = 'select a.bid, a.ugid, a.gold, a.defense, a.income, a.energy, a.discount, c.amount ';
	$query .= 'from building a left join building_group b on a.bgid=b.bgid, player_building c ';
	$query .= 'where a.bid=c.bid and c.pid='.$other->pid.' and a.income>0 and b.planet='.$player->planet.' ';
	$query .= 'order by a.income desc';
	$result = warquest_db_query($query);

	$page .= '<div class="box">';

	$page .= '<br/>';
	$page .= t('PLAYER_BUILDING_TEXT', 
						warquest_link('mid='.$mid.'&sid='.PAGE_PROFILE.'&oid='.$other->pid, player_format($other->pid, $other->name, $other->country)),
						strtolower(t('GENERAL_PLANET_'.$player->planet)));
	$page .= '<br/><br/>';

	$page .= '<table>';
	$page .= '<tr>';

	$page .= '<td width="110">';
	$page .= '<b>'.t('PLAYER_BUILDING').'</b>';
	$page .= '</td>';
				
	$page .= '<td width="190">';
	$page .= '<b>'.t('PLAYER_NAME').'</b>';
	$page .= '</td>';

	$page .= '<td width="80">';
	$page .= '<b>'.t('PLAYER_AMOUNT').'</b>';
	$page .= '</td>';
	
	$page .= '<td width="120">';
	$page .= '<b>'.t('PLAYER_INCOME').' ['.t('GENERAL_DOLLAR').']</b>';
	$page .= '</td>';
	
	$page .= '</tr>';
	
	while ($data = warquest_db_fetch_object($result)) {
	
		$page .= '<td>';
		$page .= warquest_building_image($data, 0, 1);
		$page .= '</td>';
		
		$page .= '<td>';
		$page .= '<b>'.t('BUILDING_'.$data->bid).'</b><br/>' ;
		$page .= dollar_format($data->income);
		$page .= '</td>';
				
		$page .= '<td>';
		$page .= $data->amount;
		$page .= '</td>';
		
		$value = $data->amount * $data->income;
		$totalMoney += $value;
		
		$page .= '<td>';
		$page .= money_format1($value);
		$page .= '</td>';
		
		$page .= '</tr>';
	}
			
	/* Show horizontal bar */
	$page .= '<tr>';
	$page .= '<td colspan="4">';
	$page .= '<hr>';
	$page .= '</td>';
	$page .= '</tr>';
		
	/* Totals */
	$page .= '<tr>';
	
	$page .= '<td>';
	$page .= '<b></b>';
	$page .= '</td>';
				
	$page .= '<td>';
	$page .= '<b>'.t('PLAYER_TOTAL').'</b>';
	$page .= '</td>';

	$page .= '<td>';
	$page .= '<b></b>';
	$page .= '</td>';
		
	$page .= '<td>';
	$page .= '<b>'.money_format1($totalMoney).'</b>';
	$page .= '</td>';
	
	$page .= '</tr>';
			
	$page .= '</table>';
	
	$page .= '<br/>';
	$page .= '</div>';
}

/*
** ---------------------
** PLAYER ATTACK PAGE
** ---------------------
*/

function warquest_attack_info_form($other) {

   /* input */
	global $mid;
	global $sid;
	global $uid;
	global $cid;
	
	global $config;
	global $player;
	
	/* output */
	global $page;
	global $output;
		
	$query1  = 'select ugid from unit_group where planet='.$player->planet.' and type='.$uid;
	$result1 = warquest_db_query($query1);	
	$data1 = warquest_db_fetch_object($result1);
	
	$output->title = t('PLAYER_ATTACK_FORCE', t('GENERAL_PLANET_'.$player->planet), t('UNIT_GROUP_'.$data1->ugid));
	$page .= '<div class="subparagraph">'.$output->title.'</div>';
			
	/* Calculate attack strength of units depending of alliance size */
	$query3  = 'select a.uid, a.gold, a.attack, a.defense, c.amount, a.upkeep ';
	$query3 .= 'from unit a left join unit_group b on a.ugid=b.ugid, ';
	$query3 .= 'player_unit c where a.uid=c.uid and ';
	$query3 .= 'c.pid='.$other->pid.' ';
	if ($uid==0) { 
		$query3 .= ' and b.planet='.$player->planet.' and b.type not in (0,5,6) ';
	} else {
		$query3 .= ' and b.planet='.$player->planet.' and b.type='.$uid.' ';
	}	
	$query3 .= 'order by a.attack desc, a.defense desc ';
	$result3 = warquest_db_query($query3);

	$attack = 0;
	$amount = 0;
   $count = 0;
	$size= $other->alliance * 6;

	$page .= '<div class="box">';
		
	$page .= '<br/>';
	$page .= t('PLAYER_ATTACK_TEXT', 
						warquest_link('mid='.$mid.'&sid='.PAGE_PROFILE.'&oid='.$other->pid, player_format($other->pid, $other->name, $other->country)),
						$other->alliance,
						$size,
						strtolower(t('UNIT_GROUP_'.$data1->ugid)));
	$page .= '<br/><br/>';
	
	$page .= '<table>';
	$page .= '<tr>';	
	
	$page .= '<td width="110">';
	$page .= '<b>'.t('PLAYER_UNIT').'</b>';
	$page .= '</td>';
				
	$page .= '<td width="240">';
	$page .= '<b>'.t('PLAYER_NAME').'</b>';
	$page .= '</td>';

	$page .= '<td width="80">';
	$page .= '<b>'.t('PLAYER_DEPLOYED').'</b>';
	$page .= '</td>';
	
	$page .= '<td width="80">';
	$page .= '<b>'.t('PLAYER_STRENGTH').'</b>';
	$page .= '</td>';
	
	$page .= '</tr>';
	
	$totalAmount=0;
	$totalStrength=0;
	while ($data3 = warquest_db_fetch_object($result3)) {
					
		if ($size >= $data3->amount) {
			
			$size -= $data3->amount;
			$totalAmount += $data3->amount;
			$amount = $data3->amount;
			
		} else {
		
			$amount = $size;
			$totalAmount += $size;
			$size -= $size;
		}

		$page .= '<td>';
		$page .= warquest_unit_image($data3, $count);
		$page .= '</td>';

		$page .= '<td>';
		$page .= '<b>'.t('UNIT_'.$data3->uid).'</b><br/>' ;
		$page .= $data3->attack.' '.t('GENERAL_ATTACK');
		$page .= '</td>';
				
		$page .= '<td>';
		$page .= deploy_format($amount);
		$page .= '</td>';
		
		$strength = $amount * $data3->attack;
		$totalStrength += $strength;
		
		$page .= '<td>';
		$page .= number_format($strength,0,",",".");
		$page .= '</td>';
		
		$page .= '</tr>';
		
		if ($size==0) {
			break;
		}
	}
	
	/* Show horizontal bar */
	$page .= '<tr>';
	$page .= '<td colspan="4">';
	$page .= '<br/>';
	$page .= '</td>';
	$page .= '</tr>';
		
	/* Get player skill attack strength */
	$skill = warquest_db_skill($other->pid);
	$totalStrength += $skill->attack_max * $config['init_player_skill_step'] * $other->lid;
	
	$page .= '<tr>';	
	
	$page .= '<td>';		
	$page .= '<b></b>';
	$page .= '</td>';
				
	$page .= '<td>';	
	$page .= '<b>'.t('PLAYER_ATTACK_SKILLS').'</b><br/>';
	$page .= '</td>';

	$page .= '<td>';		
	$page .= '</td>';
		
	$page .= '<td>';		
	$page .= number_format2($skill->attack_max * $config['init_player_skill_step'] * $other->lid);	
	$page .= '</td>';
	
	$page .= '</tr>';	
	
	/* Get clan attack strength */	
	if ( $cid>0 ) {
		
		$clan = warquest_db_clan($cid);
		
		$totalStrength += ($clan->attack * $config['init_clan_skill_step']);

		$page .= '<tr>';	
	
		$page .= '<td>';		
		$page .= '<b></b>';
		$page .= '</td>';
					
		$page .= '<td>';	
		$page .= '<br/>';
		$page .= '<b>'.t('CLAN_ATTACK_SKILLS').'</b>';
		$page .= '</td>';

		$page .= '<td>';		
		$page .= '</td>';
		
		$page .= '<td>';		
		$page .= number_format2( $clan->attack * $config['init_clan_skill_step']);	
		$page .= '</td>';
	
		$page .= '</tr>';	
	}
	
	
	/* Show horizontal bar */
	$page .= '<tr>';
	$page .= '<td colspan="4">';
	$page .= '<hr>';
	$page .= '</td>';
	$page .= '</tr>';
		
	/* Totals */
	$page .= '<tr>';	
	
	$page .= '<td>';	
	$page .= '<b></b>';
	$page .= '</td>';
				
	$page .= '<td>';	
	$page .= '<b>'.t('PLAYER_TOTAL').'</b>';
	$page .= '</td>';

	$page .= '<td>';	
	$page .= '<b>'.deploy_format($totalAmount,0,",",".").'</b>';
	$page .= '</td>';
		
	$page .= '<td>';		
	$page .= '<b>'.number_format($totalStrength,0,",",".").'</b>';
	$page .= '</td>';
	
	$page .= '</tr>';	
			
	$page .= '</table>';	
	
	$page .= '<br/>';	
	$page .= '</div>'; 
}

/*
** ---------------------
** PLAYER DEFENSE PAGE
** ---------------------
*/

function warquest_defense_info_form($other) {

   /* input */
	global $mid;
	global $sid;
	global $uid;
	global $cid;
	
	global $config;
	global $player;
	
	/* output */
	global $page;
	global $output;
	
	$query1  = 'select ugid from unit_group where planet='.$player->planet.' and type='.$uid;
	$result1 = warquest_db_query($query1);	
	$data1 = warquest_db_fetch_object($result1);
	
	$output->title = t('PLAYER_DEFENSE_FORCE',t('GENERAL_PLANET_'.$player->planet), t('UNIT_GROUP_'.$data1->ugid));
	$page .= '<div class="subparagraph">'.$output->title.'</div>';

	$query3  = 'select a.uid, a.gold, a.attack, a.defense, c.amount, a.upkeep ';
	$query3 .= 'from unit a left join unit_group b on a.ugid=b.ugid, ';
	$query3 .= 'player_unit c where a.uid=c.uid and ';
	$query3 .= 'c.pid='.$other->pid.' ';
	if ($uid==0) { 
		$query3 .= ' and b.planet='.$player->planet.' and b.type not in (0,5,6) ';
	} else {
		$query3 .= ' and b.planet='.$player->planet.' and b.type='.$uid.' ';
	}	
	$query3 .= 'order by a.defense desc, a.attack desc ';
	$result3 = warquest_db_query($query3);
	
	$attack = 0;
	$amount = 0;
   $count = 0;
	$size= $other->alliance * 6;

	$page .= '<div class="box">';
		
	$page .= '<br/>';
	$page .= t('PLAYER_DEFENSE_TEXT', 
						warquest_link('mid='.$mid.'&sid='.PAGE_PROFILE.'&oid='.$other->pid, player_format($other->pid, $other->name, $other->country)),
						$other->alliance, 
						$size,
						strtolower(t('UNIT_GROUP_'.$data1->ugid)) );
	$page .= '<br/><br/>';
	
	$page .= '<table>';
	$page .= '<tr>';	
	
	$page .= '<td width="110" >';		
	$page .= '<b>'.t('PLAYER_UNIT').'</b>';
	$page .= '</td>';
				
	$page .= '<td width="240" >';		
	$page .= '<b>'.t('PLAYER_NAME').'</b>';
	$page .= '</td>';

	$page .= '<td width="80" >';		
	$page .= '<b>'.t('PLAYER_DEPLOYED').'</b>';
	$page .= '</td>';
	
	$page .= '<td width="80" >';		
	$page .= '<b>'.t('PLAYER_STRENGTH').'</b>';
	$page .= '</td>';
	
	$page .= '</tr>';
	
	$totalAmount=0;
	$totalStrength=0;
	while ($data3 = warquest_db_fetch_object($result3)) {
					
		if ($size >= $data3->amount) {
			
			$size -= $data3->amount;
			$totalAmount += $data3->amount;
			$amount = $data3->amount;						
			
		} else {
		
			$amount = $size;
			$totalAmount += $size;
			$size -= $size;		
		}
		
		$page .= '<td>';		
		$page .= warquest_unit_image($data3, $count);
		$page .= '</td>';
		
		$page .= '<td>';		
		$page .= '<b>'.t('UNIT_'.$data3->uid).'</b><br/>' ;
		$page .= $data3->defense.' '.t('GENERAL_DEFENSE');
		$page .= '</td>';
				
		$page .= '<td>';	
		$page .= deploy_format($amount);
		$page .= '</td>';
		
		$strength = $amount * $data3->defense;
		$totalStrength += $strength;
		
		$page .= '<td>';					
		$page .= number_format($strength,0,",",".");
		$page .= '</td>';
		
		$page .= '</tr>';
		
		if ($size==0) {
			break;
		}
	}
		
	/* Show horizontal bar */
	$page .= '<tr>';
	$page .= '<td colspan="4">';
	$page .= '<hr>';
	$page .= '</td>';
	$page .= '</tr>';
	
	/* Totals */
	$page .= '<tr>';	
	
	$page .= '<td>';		
	$page .= '<b></b>';
	$page .= '</td>';
				
	$page .= '<td>';		
	$page .= '<b>'.t('PLAYER_SUB_TOTAL').'</b>';
	$page .= '</td>';

	$page .= '<td>';		
	$page .= '<b>'.deploy_format($totalAmount).'</b>';
	$page .= '</td>';
		
	$page .= '<td>';		
	$page .= '<b>'.number_format($totalStrength,0,",",".").'</b>';
	$page .= '</td>';
	
	$page .= '</tr>';	
	
	$page .= '<tr>';
	$page .= '<td colspan="4">';
	$page .= '<br/>';
	$page .= '</td>';
	$page .= '</tr>';
	
	/* Show defense strength of building */
	$query4  = 'select a.bid, a.ugid, a.gold, a.defense, a.income, a.energy, a.discount, b.amount ';
	$query4 .= 'from building a, player_building b ';
	$query4 .= 'where a.bid=b.bid and b.pid='.$other->pid.' and a.defense>0';
	if ($uid==0) { 
		$query4 .= ' and a.ugid in (select ugid from unit_group where planet='.$player->planet.' and type!=0 and type!=5 and type!=6)';
	} else {
		$query4 .= ' and a.ugid in (select ugid from unit_group where planet='.$player->planet.' and type='.$uid.')';
	}	
	$query4 .= ' order by a.defense desc';
	$result4 = warquest_db_query($query4);
	
	while ($data4 = warquest_db_fetch_object($result4)) {
	
		$page .= '<td >';		
		$page .= warquest_building_image($data4, 0, 1);
		$page .= '</td>';
		
		$page .= '<td>';		
		$page .= '<b>'.t('BUILDING_'.$data4->bid).'</b><br/>' ;
		$page .= $data4->defense.' defense';
		$page .= '</td>';
				
		$page .= '<td>';		
		$page .= deploy_format($data4->amount);
		$page .= '</td>';
		
		$strength = $data4->amount * $data4->defense;
		$totalStrength += $strength;
		
		$page .= '<td>';				
		$page .= number_format($strength,0,",",".");
		$page .= '</td>';
		
		$page .= '</tr>';
	}
		
	/* Show player skill defense */
	$skill = warquest_db_skill($other->pid);
	$totalStrength += $skill->defense_max * $config['init_player_skill_step'] * $other->lid;
	
	$page .= '<tr>';	
	
	$page .= '<td>';		
	$page .= '<b></b>';
	$page .= '</td>';
				
	$page .= '<td>';		
	$page .= '<b>'.t('PLAYER_DEFENSE_SKILLS').'</b><br/>';	
	$page .= '</td>';

	$page .= '<td>';		
	$page .= '</td>';
		
	$page .= '<td>';		
	$page .= number_format2($skill->defense_max * $config['init_player_skill_step'] * $other->lid);
	$page .= '</td>';
	
	$page .= '</tr>';	
	
	/* Get clan defense strength */	
	if ( $cid>0 ) {
		
		$clan = warquest_db_clan($cid);
		
		$totalStrength += ($clan->defense * $config['init_clan_skill_step']);
	
		$page .= '<tr>';	
	
		$page .= '<td>';		
		$page .= '<b></b>';
		$page .= '</td>';
				
		$page .= '<td>';	
		$page .= '<br/>';
		$page .= '<b>'.t('CLAN_DEFENSE_SKILLS').'</b>';
		$page .= '</td>';

		$page .= '<td>';		
		$page .= '</td>';
		
		$page .= '<td>';		
		$page .= number_format2($clan->defense * $config['init_clan_skill_step']);	
		$page .= '</td>';
	
		$page .= '</tr>';	
	}
		
	/* Show horizontal bar */
	$page .= '<tr>';
	$page .= '<td colspan="4">';
	$page .= '<hr>';
	$page .= '</td>';
	$page .= '</tr>';
		
	/* Totals */
	$page .= '<tr>';	
	
	$page .= '<td>';		
	$page .= '<b></b>';
	$page .= '</td>';
				
	$page .= '<td>';		
	$page .= '<b>'.t('PLAYER_TOTAL').'</b>';
	$page .= '</td>';

	$page .= '<td>';		
	$page .= '<b></b>';
	$page .= '</td>';
		
	$page .= '<td>';		
	$page .= '<b>'.number_format($totalStrength,0,",",".").'</b>';
	$page .= '</td>';
	
	$page .= '</tr>';	
			
	$page .= '</table>';	
	
	$page .= '<br/>';	
	$page .= '</div>'; 
}

/*
** ---------------------
** Player Profile
** ---------------------
*/

function warquest_player_data_unlocked($other, $value) {

	/* input */
	global $player;
	global $config;
	
		/* output */
	global $page;
	
	if (($other->pid==$player->pid) || ($player->pid==$config["adminPid"])) {
		return true;
	}
		
	$query = 'select ugid from unit_group where type=5 and planet='.$player->planet;
	$result = warquest_db_query($query);
	$data = warquest_db_fetch_object($result);
	$ugid = $data->ugid;
		
	$spy = t('PLAYER_SPY_'.$player->planet);
				
	$tmp1 = warquest_defense_strength($other, $ugid, 0);
	$tmp1 = round( $tmp1* (($value/100)+1));
		
	$tmp2 = warquest_attack_strength($player, $ugid, 0);
	
	if ($tmp2 >= $tmp1) {
		return true;
	}
	
	if ($value == 0) {
		$message = t('PLAYER_ESPIONAGE_UNLOCK2',t('GENERAL_PLANET_'.$player->planet).' '.$spy);
	} else {
		$message = t('PLAYER_ESPIONAGE_UNLOCK1',t('GENERAL_PLANET_'.$player->planet).' '.$spy, $value);
	}
	$page .= warquest_box_icon("classified", $message);
	
	return false;
}

function warquest_profile($id) {

	/* input */
	global $mid;
	global $sid;
	global $other;
	global $player;
	global $browser;
	global $config;
				
	/* output */ 
	global $output;

	$output->title = t('PLAYER_OVERVIEW');
	 
	$data = warquest_db_player($id);
	$member = warquest_db_member($id);
	
	/* output */
	global $page;

	$page .= '<div class="subparagraph">'.t('PLAYER_OVERVIEW').'</div>';
	
	/* -------------------------------------------------- */
	
	$page .= '<div class="box">';
	
	$page .= '<table>';
	
	$page .= '<tr>';
	$page .= '<td width="170"><b>'.t('PLAYER_RANK').':</b></td>';
	$page .= '<td width="140">'.warquest_rank($data->lid).'</td>';
	
	$page .= '<td width="190" rowspan="4" align="right">';	
	if ($data->country!="EU") {
		$page .= '<img title="www.gravatar.com" src="'.get_gravatar($member->email).'">';
	} else {
		$page .= warquest_image('other/robot.jpg');
	}
	$page .= '</td>';	
	$page .= '</tr>';
	
	$page .= '<tr>';
	$page .= '<td><b>'.t('PLAYER_NAME').':</b></td>';
	$page .= '<td>'.$data->name.'</td>';	
	$page .= '</tr>';
	
	$query2  = 'select a.name from clan a, player_clan b where b.approved=1 and a.cid=b.cid and b.pid='.$data->pid;
	$result2 = warquest_db_query($query2);	
	$data2 = warquest_db_fetch_object($result2);
	
	$page .= '<tr>';
	$page .= '<td><b>'.t('PLAYER_CLAN_NAME').':</b></td>';
	$page .= '<td>';
	if (isset($data2->name)) {
		$page .= $data2->name;
	}
	$page .= '</td>';	
	$page .= '</tr>';
	
	$page .= '<tr>';
	$page .= '<td><b>'.t('GENERAL_COUNTRY').':</b></td>';
	$page .= '<td>'.warquest_flag_image($data->country).'</td>';
	$page .= '</tr>';
	
	$page .= '<tr>';
	$page .= '<td><b>'.t('GENERAL_LEVEL').':</b></td>';
	$page .= '<td>'.$data->lid.'</td>';
	$page .= '</tr>';
	
	$page .= '</tr>';
		
	$page .= '<tr>';
	$page .= '<td><b>'.t('PLAYER_EXP_POINTS').':</b></td>';
	$page .= '<td>'.number_format($data->experience,0,",",".").'</td>';

	$page .= '<td align="right">';
	
	if ($player->pid==$id) {
		$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_PLAYER_PDF_REPORT.'&oid='.$id, t('LINK_REPORT'), "report").' ';
	}
		
	if ($player->pid!=$id) {	
		$page .= warquest_link('mid='.MENU_FORUMS.'&sid='.PAGE_COMMENT.'&oid='.$id, t('LINK_COMMENT'), "comment").' ';		
	
		if ( ($player->lid>0) &&
		     ($other->lid >= warquest_get_min_attack_level()) &&
			  ($other->lid <= warquest_get_max_attack_level()) && 
			  ($other->cease_fire_date < date("Y-m-d H:i:s", time())) && 
			  ($player->cease_fire_date < date("Y-m-d H:i:s", time())) &&
			  ($other->holiday_date < date("Y-m-d H:i:s", time())) && 
			  ($player->holiday_date < date("Y-m-d H:i:s", time())))  {
		
			$page .= warquest_link('mid='.MENU_BATTLE.'&sid='.PAGE_ENEMIES.'&eid='.EVENT_BATTLE_NORMAL.'&oid='.$id, t('LINK_ATTACK'), "attack").' ';
		}
		
		if ( ($player->lid>0) &&
			  (($player->alliance + $player->invite) < $player->lid*$config["max_ally_factor"]) &&
			  (($data->alliance + $data->invite) < ($data->lid * $config["max_ally_factor"])) &&
			  ($player->holiday_date < date("Y-m-d H:i:s", time())) &&
			  (warquest_db_ally($player->pid, $id)==0) ) {
			
			$page .= warquest_link('mid='.MENU_ALLIANCE.'&sid='.PAGE_INVITE.'&eid='.EVENT_ALLIANCE_INVITE.'&oid='.$id, t('LINK_INVITE'), "invite").' ';
		}
	
		if (($player->lid>=9) && 
			 (warquest_db_ally($player->pid,$id)==0) && 		     
			 ($other->lid >= warquest_get_min_attack_level()) &&
			 ($other->lid <= warquest_get_max_attack_level()) && 
		    (warquest_db_bounty_possible($data->pid, $player->pid)==0) && 
			 ($player->holiday_date < date("Y-m-d H:i:s", time())) &&
			 ($data->country!="EU")) {
		
			if (warquest_db_query_pattern($player, PATTERN_BOUNTY)==0) {
				$page .= warquest_link('mid='.MENU_BATTLE.'&sid='.PAGE_BOUNTY.'&eid='.EVENT_BATTLE_BOUNTY.'&oid='.$data->pid, t('LINK_BOUNTY'), "bounty");
				
			} else {
				
				/* Calculate bounty price */
				$money = $data->lid * $data->lid * $data->lid * 100;
				$page .= warquest_link_confirm('mid='.MENU_BATTLE.'&sid='.PAGE_BOUNTY.'&eid=2&oid='.$data->pid, t('LINK_BOUNTY'), 
					t('BATTLE_BOUNTY_CONFIRM',number_format($money,0,",",".")));
			}
		}
	}	
	$page .= '</td>';	
	$page .= '</tr>';
	$page .= '</table>';
			
	$page .= '</div>';
	

	if (strlen($data->twitter)>0) {
		
		$tmp1 = warquest_twitter($data);
		
		if (strlen($tmp1)>0) {
			
			$page .= '<div class="subparagraph">'.t('PLAYER_LAST_TWEET').'</div>';
		
			$page .= '<div class="box">';
	
			if (preg_match("/MSIE/", $browser)) {
				$page .= '<div id="TICKER" STYLE="overflow:hidden; width:490px">';
			} else {
				$page .= '<div id="TICKER" STYLE="overflow:hidden; width:500px">';
			}
		
			for ($tmp=0; $tmp<100; $tmp++) {
				$page .= '&nbsp;';
			}	
		
			$page .= $tmp1;
			
			for ($tmp=0; $tmp<100; $tmp++) {
				$page .= '&nbsp;';
			}	
	
			$page .= '</div>';
			$page .= '</div>';
			$page .= '<script type="text/javascript" src="'.$config["content_url"].'js/news.js" language="javascript"></script>';
		}
	}
			
	
	/* -------------------------------------------------- */
	/* Statistics */
	
	$page .= '<div class="subparagraph">'.t('PLAYER_STATISTICS').'</div>';
	  	
	if (warquest_player_data_unlocked($data, 0)) {
							
		$page .= '<div class="box">';
		$page .= '<table>';
	
		$page .= '<tr>';
		$page .= '<td  width="170"><b>'.t('PLAYER_FIGHTS_WON').':</b></td>';
		$page .= '<td  width="85">'.number_format($data->won,0,",",".").'</td>';
		$page .= '<td  width="160"><b>'.t('PLAYER_FIGHTS_LOST').':</b></td>';
		$page .= '<td>'.number_format($data->lost,0,",",".").'</td>';
		$page .= '</tr>';
		
		$page .= '<tr>';
		$page .= '<td><b>'.t('PLAYER_MISSION_COMPLETED').':</b></td>';
		$page .= '<td>'.number_format($data->mission,0,",",".").'</td>';
		$page .= '<td><b>'.t('PLAYER_ALLIANCE_SIZE').':</b></td>';
		$page .= '<td>'.$data->alliance.'</td>';
		$page .= '</tr>';

		$tmp=0;
		if ($data->lost>0) {
			$tmp = round(($data->won/$data->lost),2);
		}
					
		$page .= '<tr>';
		$page .= '<td><b>'.t('PLAYER_WIN_LOST_RATE').':</b></td>';
		$page .= '<td>'.$tmp.'</td>';
		$page .= '<td><b>'.t('PLAYER_SERVER_REQUEST').':</b></td>';
		$page .= '<td>'.number_format($data->request,0,",",".").'</td>';
		$page .= '</tr>';
	
		$page .= '<tr>';
		$page .= '<td><b>'.t('PLAYER_CASINO_PLAYED').':</b></td>';
		$page .= '<td>'.number_format($data->casino,0,",",".").'</td>';
				
		$premium = strtotime($data->premium_date) - time();

		$page .= '<td><b>'.t('GENERAL_PREMIUM_MEMBERSHIP').':</b></td>';	
		$page .= '<td>';
		
		if ($premium>0) {
	
			$page .= '<script language="JavaScript" src="'.$config["content_url"].'js/countdown1.js" type="text/javascript"></script>';
	
			$page .= '<div class="countdown"><div id="countdown_time1"></div></div>';
			$page .= '<script language="JavaScript" type="text/javascript">';
			$page .= "countdown1.init(".$premium.", 'countdown_time1', '00:00:00');"; 
			$page .= '</script>';
			
		} else {
			$page .= t('GENERAL_IDLE');
		}
		$page .= '</td>';
	
		$page .= '</tr>';
				
		$page .= '<tr>';
		$page .= '<td><b>'.t('PLAYER_BOUNTY_SET').':</b></td>';
		$page .= '<td>'.$data->bounty.'</td>';	
		$page .= '<td><b>'.t('PLAYER_REBELLION_RISE').':</b></td>';
		$page .= '<td>'.$data->rebel.'</td>';	
		$page .= '</tr>';
		
		$page .= '<tr>';
		$page .= '<td><b>'.t('PLAYER_CREATED').':</b></td>';
		$page .= '<td>'.warquest_ui_ago($member->created).'</td>';	
		$page .= '<td><b>'.t('PLAYER_LAST_LOGIN').':</b></td>';
		$page .= '<td>'.warquest_ui_ago($data->request_date).'</td>';	
		$page .= '</tr>';
		
		$page .= '<tr>';
		$page .= '<td><b>'.t('PLAYER_CEASE_FIRE_TITLE').':</b></td>';
		$page .= '<td>';
		$value = strtotime($data->cease_fire_date)-time();
		if ($value<=0) { 
			$value=0;
		}
		if ($value==0) {
			$page .= t('GENERAL_IDLE');		
		} else {
			$page .= '<script language="JavaScript" src="'.$config["content_url"].'js/countdown4.js" type="text/javascript"></script>';

			$page .= '<div class="countdown"><div id="countdown_time4"></div></div>';
			$page .= '<script language="JavaScript" type="text/javascript">';
			$page .= "countdown4.init(".$value.", 'countdown_time4', '00:00:00');"; 
			$page .= '</script>';
		}		
		$page .= '</td>';
		
		$page .= '<td><b>'.t('PLAYER_HOLIDAY_TITLE').':</b></td>';
		$page .= '<td>';
		$value = strtotime($data->holiday_date)-time();
		if ($value<=0) { 
			$value=0;
		}	
		if ($value==0) {
			$page .= t('GENERAL_IDLE');		
		} else {
			$page .= '<script language="JavaScript" src="'.$config["content_url"].'js/countdown5.js" type="text/javascript"></script>';

			$page .= '<div class="countdown"><div id="countdown_time5"></div></div>';
			$page .= '<script language="JavaScript" type="text/javascript">';
			$page .= "countdown5.init(".$value.", 'countdown_time5', '00:00:00');"; 
			$page .= '</script>';
		}
		$page .= '</td>';
		
		$page .= '</tr>';		
	
		$page .= '</table>';
		$page .= '</div>';
	}
	
	/* -------------------------------------------------- */
	/* Browser information */
	
	$page .= '<div class="subparagraph">'.t('PLAYER_PLATFORM_BROWSER').'</div>';
	
	if (warquest_player_data_unlocked($data, 0)) {
	
		$page .= '<div class="box">';
		$page .= '<table>';
		
		$page .= '<tr>';
		$page .= '<td width="170"><b>'.t('PLAYER_BROWSER').':</b></td>';
		$page .= '<td>'.$member->browser.'</td>';
		$page .= '</tr>';

		$page .= '<tr>';
		$page .= '<td><b>'.t('PLAYER_BROWSER_VERSION').':</b></td>';
		$page .= '<td>'.$member->version.'</td>';
		$page .= '</tr>';
	
		$page .= '<tr>';
		$page .= '<td><b>'.t('PLAYER_PLATFORM').':</b></td>';
		$page .= '<td>'.warquest_platform_image($member->platform).'</td>';
		$page .= '</tr>';
		
		$page .= '</table>';
		$page .= '</div>';
	}
	
		
	/* -------------------------------------------------- */
	/* Show current Assets */
	
	$page .= '<div class="subparagraph">'.t('PLAYER_MONEY_STATUS').'</div>';
	
	if (warquest_player_data_unlocked($data, 0)) {
	
		$page .= '<div class="box">';
		$page .= '<table>';
		
		$page .= '<tr>';
		$page .= '<td width="170"><b>'.t('PLAYER_CASH_MONEY').':</b></td>';
		$page .= '<td>'.dollar_format($data->money).'</td>';
		$page .= '</tr>';
	
		$page .= '<tr>';
		$page .= '<td width="170"><b>'.t('PLAYER_GOLD').':</b></td>';
		$page .= '<td>'.gold_format($data->gold).'</td>';
		$page .= '</tr>';
		
		$page .= '<tr>';
		$page .= '<td><b>'.t('BANK_GROUP_1').' '.t('PLAYER_BANK').':</b></td>';
		$page .= '<td>'.dollar_format($data->bank1).'</td>';
		$page .= '</tr>';

		$page .= '<tr>';
		$page .= '<td><b>'.t('BANK_GROUP_2').' '.t('PLAYER_BANK').':</b></td>';
		$page .= '<td>'.dollar_format($data->bank2).'</td>';
		$page .= '</tr>';
	
		$page .= '<tr>';
		$page .= '<td><b>'.t('BANK_GROUP_3').' '.t('PLAYER_BANK').':</b></td>';
		$page .= '<td>'.dollar_format($data->bank3).'</td>';
		$page .= '</tr>';
	
		$page .= '<tr>';
		$page .= '<td><b>'.t('GENERAL_STOCKS').':</b></td>';
		$page .= '<td>'.dollar_format(warquest_db_player_stock_assest($id)).'</td>';
		$page .= '</tr>';
		
		$page .= '<tr>';
		$page .= '<td><b>'.t('PLAYER_TOTAL_HOURLY_INCOME').':</b></td>';
		$page .= '<td>'.dollar_format($data->money_step).'</td>';
		$page .= '</tr>';
		
		$page .= '</table>';
		$page .= '</div>';
	}
	
	/* -------------------------------------------------- */
	/* Strenght */
	
	$page .= '<div class="subparagraph">'.t('PLAYER_FORCE').' ('.t('GENERAL_PLANET_'.$player->planet).')</div>';
	 
	if (warquest_player_data_unlocked($data, 0)) {
		
		$page .= '<div class="box">';
		$page .= '<table>';
	
		$page .= '<tr>';
		$page .= '<td width="170"><b></b></td>';
		$page .= '<td width="150"><b>'.t('PLAYER_ATTACK_STRENGTH').'</b></td>';
		$page .= '<td width="150"><b>'.t('PLAYER_DEFENSE_STRENGTH').'</b></td>';
		$page .= '</tr>';
	
		$query2  = 'select ugid, type from unit_group where planet='.$player->planet.' and type!=1 and type!=6 order by type';
		$result2 = warquest_db_query($query2);	

		while ($data2=warquest_db_fetch_object($result2)) {
								
			$page .= '<tr>';
			$page .= '<td><b>'.t('UNIT_GROUP_'.$data2->ugid).':</b></td>';
			$page .= '<td>';
			$page .= warquest_link('mid='.$mid.'&sid='.PAGE_ATTACK.'&oid='.$id.'&uid='.$data2->type, 
								number_format(warquest_attack_strength($data, $data2->ugid, 0),0,",","."), "attack".$data2->ugid);
			$page .= '</td>';
			$page .= '<td>';
			$page .= warquest_link('mid='.$mid.'&sid='.PAGE_DEFENCE.'&oid='.$id.'&uid='.$data2->type, 
								number_format(warquest_defense_strength($data, $data2->ugid, 0),0,",","."), "defense".$data2->ugid);
			$page .= '</td>';
			$page .= '</tr>';					
		}
				
		$page .= '</table>';
		$page .= '</div>';
	}
	
	/* -------------------------------------------------- */
	/* Show Case Flow */
	
	$page .= '<div class="subparagraph">'.t('PLAYER_CASH_FLOW').' ('.t('GENERAL_PLANET_'.$player->planet).')</div>';
	
	if (warquest_player_data_unlocked($data, 0)) {
	
		$page .= '<div class="box">';
		$page .= '<table>';
		
		$building_income = warquest_building_income($data, $player->planet);
		
		$page .= '<tr>';
		$page .= '<td width="170"><b>'.t('PLAYER_BUILDING_INCOME').':</b></td>';
		
		$page .= '<td>';
		$link = warquest_link('mid='.$mid.'&sid='.PAGE_BUILDING_INCOME.'&oid='.$id, number_format($building_income, 0,",","."), "income");	
		$page .= $link;
		$page .= '</td>';

		$page .= '</tr>';
	
		$continent_income = warquest_continent_income($data, $player->planet);
		
		$page .= '<tr>';
		$page .= '<td><b>'.t('PLAYER_CONTINENT_INCOME').':</b></td>';
		
		$page .= '<td>';
		$link = warquest_link('mid='.$mid.'&sid='.PAGE_CONTINENT_INCOME.'&oid='.$id, number_format($continent_income, 0,",","."), "continent");	
		$page .= $link;
		$page .= '</td>';
		
		$page .= '</tr>';
		
		$clan_war_income = warquest_clan_war_income($data, $player->planet);
		
		$page .= '<tr>';
		$page .= '<td><b>'.t('PLAYER_CLAN_WAR_INCOME').':</b></td>';
		
		$page .= '<td>';
		$link = warquest_link('mid='.$mid.'&sid='.PAGE_CLAN_WAR_INCOME.'&oid='.$id, number_format($clan_war_income, 0,",","."), "earth2");	
		$page .= $link;
		$page .= '</td>';
	
		$page .= '</tr>';
				
		$unit_upkeep = warquest_unit_upkeep($data, $player->planet);
		
		$page .= '<tr>';
		$page .= '<td><b>'.t('PLAYER_UPKEEP').':</b></td>';
		
		$page .= '<td>';
		$link = warquest_link('mid='.$mid.'&sid='.PAGE_UNIT_UPKEEP.'&oid='.$id, number_format(($unit_upkeep*-1), 0,",","."), "earth2");	
		$page .= $link;
		$page .= '</td>';
	
		$page .= '</tr>';
			
		$page .= '<tr>';
		$page .= '<td><b>'.t('PLAYER_NETTO_INCOME').':</b></td>';		
		$page .= '<td>'.money_format1($building_income + $continent_income + $clan_war_income - $unit_upkeep).'</td>';
		$page .= '</tr>';
		
		$page .= '</table>';
		$page .= '</div>';
	}
			
	/* -------------------------------------------------- */
	/* Discount & Maintenance */
	
	$page .= '<div class="subparagraph">'.t('PLAYER_DISCOUNT_MAINTENANCE').' ('.t('GENERAL_PLANET_'.$player->planet).')</div>';
	  	
	if (warquest_player_data_unlocked($data, 0)) {
	
		$page .= '<div class="box">';
		$page .= '<table>';
		
		$page .= '<tr>';
		$page .= '<td width="170"><b>'.t('PLAYER_DISCOUNT_RATE').':</b></td>';
		$link = warquest_link('mid='.$mid.'&sid='.PAGE_DISCOUNT.'&oid='.$id, warquest_db_discount($data, $player->planet), "discount");	
		$page .= '<td>'.$link.'%</td>';
		$page .= '</tr>';
		
		$page .= '<tr>';
		$page .= '<td><b>'.t('PLAYER_MAINTENANCE_RATE').':</b></td>';
		$link = warquest_link('mid='.$mid.'&sid='.PAGE_MAINTENANCE.'&oid='.$id, warquest_db_maintenance($data, $player->planet), "discount");		
		$page .= '<td>'.$link.'%</td>';
		$page .= '</tr>';
		
		$page .= '</table>';
		$page .= '</div>';
	}
		
	/* -------------------------------------------------- */	
	/* Show units */
	
	$max=5;
	
	$query2  = 'select ugid, type from unit_group where planet='.$player->planet.' order by type';
	$result2 = warquest_db_query($query2);	

	while ($data2=warquest_db_fetch_object($result2)) {
	
		$query3  = "select a.uid, a.gold, a.attack, a.defense, a.ugid, b.amount, a.upkeep ";
		$query3 .= "from unit a inner join player_unit b ";
		$query3 .= "ON a.uid=b.uid and b.pid=".$id." where a.ugid=".$data2->ugid." order by a.lid";  
		$result3 = warquest_db_query($query3);

	   if (warquest_db_num_rows($result3)>0) { 

			$page .= '<div class="subparagraph">'.t('UNIT_GROUP_'.$data2->ugid).' ('.t('GENERAL_PLANET_'.$player->planet).')</div>';
			
			if (warquest_player_data_unlocked($data, 0)) {	
				$page .= '<div class="box">';
				$page .= '<table>';
				$page .= '<tr>';
				$count=0;
				while ($data3=warquest_db_fetch_object($result3)) {
	
					$count++;
				
					$page .= '<td width="100">';
					$page .= warquest_unit_image($data3, 0);
					$page .= '<br/><center>'.number_format2($data3->amount).'x</center>';
					$page .= '</td>';
				
					if (($count % $max)==0) {
						$page .= '</tr><tr>';
					}
				}
				$page .= '</tr>';
				$page .= '</table>';
				$page .= '</div>';
			}
		}
	}
	
	/* -------------------------------------------------- */
   /* Get building data */
	
	$query2  = 'select bgid from building_group where planet='.$player->planet.' order by bgid';
	$result2 = warquest_db_query($query2);	
	
	while ($data2=warquest_db_fetch_object($result2)) {
		
		$query  = 'select a.bid, a.ugid, a.gold, a.income, a.defense, a.energy, a.discount, ';
		$query .= 'a.maintenance, b.pid, b.amount ';
		$query .= 'from building a inner join player_building b ';
		$query .= 'on a.bid=b.bid and b.pid='.$id.' ';
		$query .= 'where a.bgid='.$data2->bgid.' ';
		$query .= 'order by a.lid';  
		$result3 = warquest_db_query($query);

		$count=0;
		if (warquest_db_num_rows($result3)>0) { 

			$page .= '<div class="subparagraph">'.t('BUILDING_GROUP_'.$data2->bgid).' '.t('PLAYER_BUILDINGS').' ('.t('GENERAL_PLANET_'.$player->planet).')</div>';
	
			if (warquest_player_data_unlocked($data, 0)) {			
			
				$page .= '<div class="box">';
				$page .= '<table>';
				$page .= '<tr>';
				while ($data3=warquest_db_fetch_object($result3)) {
		
					$count++;
		
					$page .= '<td width="100">';
					$page .= warquest_building_image($data3, 0, 1);
					$page .= '<br/><center>'.$data3->amount.'x</center>';
					
					if (($count % $max)==0) {
						$page .= '</tr><tr>';
					}	
				}
				$page .= '</tr>';
				$page .= '</table>';
				$page .= '</div>';
			}
		}
	}	
}

/*
** ---------------------
** Handler
** ---------------------
*/

/**
 * Player handler
 */
function warquest_player() {

	/* input */
	global $sid;
	global $eid;
	global $player;	
	global $other;	
		
	/* Event handler */
	switch ($eid) {
						
		case EVENT_PLAYER_PDF_REPORT:
			if ($other->pid!=0) {
				warquest_player_report_do($other->pid);
			} else  {
				warquest_player_report_do($player->pid);
			}
			break;	
	}	

	/* page handler */
	switch ($sid) {
		
		case PAGE_PROFILE: 
					if ((isset($other->pid)) && ($other->pid!=0) && ($player->pid!=$other->pid)) {						
						warquest_profile($other->pid);
					} else {
						warquest_profile($player->pid);
					}
					break;
					
		case PAGE_ATTACK:
					if ((isset($other->pid)) && ($other->pid!=0) && ($player->pid!=$other->pid)) {
						warquest_attack_info_form($other);
					} else {
						warquest_attack_info_form($player);
					}
					break;
			
		case PAGE_DEFENCE:	
					if ((isset($other->pid)) && ($other->pid!=0) && ($player->pid!=$other->pid)) {
						warquest_defense_info_form($other);
					} else {
						warquest_defense_info_form($player);
					}
					break;
					
		case PAGE_BUILDING_INCOME:
					if ((isset($other->pid)) && ($other->pid!=0) && ($player->pid!=$other->pid)) {
						warquest_building_income_form($other);
					} else {
						warquest_building_income_form($player);
					}
					break;
					
		case PAGE_UNIT_UPKEEP:
					if ((isset($other->pid)) && ($other->pid!=0) && ($player->pid!=$other->pid)) {
						warquest_unit_upkeep_form($other);
					} else {
						warquest_unit_upkeep_form($player);
					}
					break;
					
		case PAGE_CONTINENT_INCOME: 
					if ((isset($other->pid)) && ($other->pid!=0) && ($player->pid!=$other->pid)) {
						warquest_continent_income_form($other);
					} else {
						warquest_continent_income_form($player);
					}
					break;
					
		case PAGE_CLAN_WAR_INCOME: 
					if ((isset($other->pid)) && ($other->pid!=0) && ($player->pid!=$other->pid)) {
						warquest_clan_War_income_form($other);
					} else {
						warquest_clan_war_income_form($player);
					}
					break;
	
		case PAGE_DISCOUNT: 
					if ((isset($other->pid)) && ($other->pid!=0) && ($player->pid!=$other->pid)) {
						warquest_discount_info_form($other);
					} else {
						warquest_discount_info_form($player);
					}
					break;
					
		case PAGE_MAINTENANCE: if ((isset($other->pid)) && ($other->pid!=0) && ($player->pid!=$other->pid)) {
						warquest_maintenance_info_form($other);
					} else {
						warquest_maintenance_info_form($player);
					}
					break;
	}	
}

/*
** ---------------------
** THE END
** ---------------------
*/

?>