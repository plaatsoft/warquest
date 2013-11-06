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
** HELP
** ---------------------------------------------------------------- 
*/

/*
** ---------------------
** CRON
** ---------------------
*/

function warquest_cron_negative_income($output=0) {

	/* input */
	global $config;
	
		/* output */
	global $popup;
	
	$query1 = 'select pid from player where money_step<0'; 
	$result1 = warquest_db_query($query1);			
	
	$count=0;
	while ($data1 = warquest_db_fetch_object($result1)) {

		$query2 = 'select a.uid, a.price, a.upkeep, b.amount, b.pid from unit a left join player_unit b ';
		$query2 .= 'on b.uid=a.uid where b.pid='.$data1->pid.' order by a.upkeep desc limit 0, 1';
		
		$result2 = warquest_db_query($query2);
		if ($data2 = warquest_db_fetch_object($result2)) {
			$count++;				
			warquest_db_unit_delete($data2->pid, $data2->uid, $data2->amount);
			
			$player = warquest_db_player($data1->pid);
			
			$player->money += round($data2->price * $config["unit_sell_ratio"] * $data2->amount);
			
			warquest_netto_income($player);
			
			warquest_db_player_update($player);
		}		
	}
		
	$message = 'Unit sold by '.$count.' player(s) to get positive hourly income again!<br/>';

	if ($output==1) {
	
		$popup .= warquest_box_icon("info", $message);
		
	} else {
	
		warquest_info($message);
	}
}

function warquest_cron_statistics($output=0) {

	/* input */
	global $config;	
		
	$query1  = 'select count(*) as count, sum(request) as request, sum(won) as won, ';
	$query1 .= 'sum(mission) as missions, sum(ads) as ads, sum(casino) as casino from player';
	$result1 = warquest_db_query($query1);	
	$data1=warquest_db_fetch_object($result1);
					
	$yesterday = mktime(date("H"), date("i"), date("s"), date("m"), date("d")-1, date("Y"));
	
	$query2  = 'select count(*) as count from member where last_login > "'.date("Y-m-d H:i:s", $yesterday).'" ';			
	$result2 = warquest_db_query($query2);	
	$data2=warquest_db_fetch_object($result2);
	
	if ($output==1) {
		$yesterday = mktime(date("H"), date("i"), date("s"), date("m"), date("d"), date("Y"));
	}
	
	$query3 = 'select id from statistics where date = "'.date("Y-m-d", $yesterday).'"';
	$result3 = warquest_db_query($query3);	
 
	if ($data3=warquest_db_fetch_object($result3)) {

		$query  = 'update statistics set ';
		$query .= 'requests='.$data1->request.', ';
		$query .= 'fights='.$data1->won.', ';
		$query .= 'players='.$data1->count.', ';
		$query .= 'logins='.$data2->count.', ';
		$query .= 'missions='.$data1->missions.', ';
		$query .= 'ads='.$data1->ads.', ';
		$query .= 'casino='.$data1->casino.' ';
		$query .= 'where id='.$data3->id; 
		
	} else {
	
		$query  = 'insert into statistics (date, requests, fights, players,  logins, missions, ads, casino) ';
		$query .= 'VALUES ("'.date("Y-m-d", $yesterday).'",'.$data1->request.','.$data1->won.',';
		$query .= $data1->count.', '.$data2->count.', '.$data1->missions.', '.$data1->ads.', '.$data1->casino.')';
	}
	
	warquest_db_query($query);
		
	$message = 'Statistics of '.date("d-m-Y", $yesterday).' updated!'; 
	
	if ($output!=1) {
	
		warquest_info($message);
	}	
}


function warquest_cron_delete_pending_invitations($output=0) {

	/* input */
	global $config;
	
	/* output */
	global $popup;
	
	$count = 0;

	$old = mktime(date("H"), date("i"), date("s"), date("m"), date("d")-$config["max_invite_period"], date("Y"));
	
	$query  = 'select pid1, pid2 from player_player where approved=0 and invite_date<"'.date("Y-m-d H:i:s", $old).'" ';	
	$result = warquest_db_query($query);	
	
	while ($data = warquest_db_fetch_object($result)) {

		$count++;				
	
		warquest_db_alliance_delete($data->pid1, $data->pid2);
			
		$player = warquest_db_player($data->pid1);
		$player->invite = warquest_db_invite_size($player->pid);			
		warquest_db_player_update($player);
		
		$other = warquest_db_player($data->pid2);
		$other->invite = warquest_db_invite_size($other->pid);			
		warquest_db_player_update($other);
	}
		
	$message = $count.' pending ally request cleared! <br/>';

	if ($output==1) {
	
		$popup .= warquest_box_icon("info", $message);
		
	} else {
	
		warquest_info($message);
	}
}

function warquest_cron_clean_battle_log($output=0) {
	
	/* input */
	global $config;
	
	/* output */
	global $popup;
	
	$old = mktime(date("H"), date("i"), date("s"), date("m"), date("d")-$config["max_battle_log_age"], date("Y"));
	
	$count=0;
	$query  = 'select count(id) as total from battle where date < "'.date("Y-m-d H:i:s", $old).'" ';
	$result = warquest_db_query($query);			
	if ($data = warquest_db_fetch_object($result)) {
		$count = $data->total;
	}
		
	$query  = 'delete from battle where date < "'.date("Y-m-d H:i:s", $old).'" ';
	warquest_db_query($query);
			
	$message = $count.' battle records are deleted!';

	if ($output==1) {
	
		$popup .= warquest_box_icon("info", $message);
		
	} else {
	
		warquest_info($message);
	}
}

function warquest_cron_robot_alliancy_update($output=0) {
	
	/* output */
	global $popup;
		
	$query1  = 'select a.pid from player a, player_player b where a.pid=b.pid2 and b.approved=0 and a.country="eu"'; 
	$result1 = warquest_db_query($query1);		
	
	$robots=0;
	$count=0;
	while ($data1 = warquest_db_fetch_object($result1)) {
				
		$flag = 0;
		$query2  = 'select pid1 from player_player where approved=0 and pid2='.$data1->pid;
		$result2 = warquest_db_query($query2);	
				
		while ($data2 = warquest_db_fetch_object($result2)) {
	
			/* Load other player data */			
			$other = warquest_db_player($data2->pid1);
	
			/* Update alliance data */
			warquest_db_alliance_insert($data1->pid, $other->pid, 1);
			warquest_db_alliance_update($other->pid, $data1->pid, 1);
					
			/* Update alliance size data */		
			$other->alliance = warquest_db_alliance_size($other->pid);
			$other->invite = warquest_db_invite_size($other->pid);
						
			/* Store values in database */	
			warquest_db_player_update($other);

			$flag=1;
			$count++;		
		}
		
		if ($flag==1) {		
		
			/* Load player data */	
			$player = warquest_db_player($data1->pid);
		
			/* Update alliance size data */			
			$player->alliance = warquest_db_alliance_size($data1->pid);
			$player->invite = warquest_db_invite_size($data1->pid);
			
			/* Update request date for alliance -> invite page information */
			$player->request_date = date("Y-m-d H:i:s", time());
			
			/* Store values in database */	
			warquest_db_player_update($player);
		}
			
		$robots++;
	}
	
	$message = $count.' alliance requested accepted!<br/>In total '.$robots.' robots checked.';
	
	if ($output==1) {
	
		$popup .= warquest_box_icon("info", $message);
		
	} else {
	
		warquest_info($message);
	}
}

function warquest_cron_player_interest($output=0) {
		
	/* input */
	global $config;
	
	/* output */
	global $popup;
	
	$query  = 'select pid, bank1, bank2, bank3 from player where ';
	$query .= 'holiday_date < "'.date("Y-m-d H:i:s", time()).'" and ';
	$query .= 'bank1>0 or bank2>0 or bank3>0 order by pid'; 
	$result = warquest_db_query($query);			
		
	$count=0;
	
	while ($data=warquest_db_fetch_object($result)) {
		
		$found=0;
					
		if ($data->bank1 > 0) {
			$extra = round(($data->bank1/100) * $config["init_bank1_interest"]);
			$data->bank1 += $extra;
			warquest_bank_insert($data->pid, 0, 1, $extra, $data->bank1, 4);
			$found=1;
		}
		
		if ($data->bank2 > 0) {
			$extra = round(($data->bank2/100) * $config["init_bank2_interest"]);
			$data->bank2 += $extra;
			warquest_bank_insert($data->pid, 0, 2, $extra, $data->bank2, 4);
			$found=1;
		}
		
		if ($data->bank3 > 0) {
			$extra = round(($data->bank3/100) * $config["init_bank3_interest"]);
			$data->bank3 += $extra;
			warquest_bank_insert($data->pid, 0, 3, $extra, $data->bank3, 4);
			$found=1;
		}
		
		if ($found==1) {
		
			$query  = 'update player set '; 
			$query .= 'bank1='.$data->bank1.", ";
			$query .= 'bank2='.$data->bank2.", ";
			$query .= 'bank3='.$data->bank3." ";
			$query .= 'where pid='.$data->pid;
		
			warquest_db_query($query);
		}
		$count++;
	}
	
	$message = number_format2($count).' players interest updated!';
	
	if ($output==1) {
	
		$popup .= warquest_box_icon("info", $message);
		
	} else {
			
		warquest_info($message);
	}
}


function warquest_cron_clean_bank_log($output=0) {

	/* input */
	global $config;
	
	/* output */
	global $popup;
	
	$old = mktime(date("H"), date("i"), date("s"), date("m"), date("d")-$config["max_bank_log_age"], date("Y"));
	
	$count = 0;
	$query  = 'select count(id) as total from bank where date < "'.date("Y-m-d H:i:s", $old).'" ';
	$result = warquest_db_query($query);			
	if ($data = warquest_db_fetch_object($result)) {
		$count = $data->total;
	}
	
	$query  = 'delete from bank where date < "'.date("Y-m-d H:i:s", $old).'" ';
	warquest_db_query($query);
	
	$message = $count.' bank records are deleted!';

	if ($output==1) {
	
		$popup .= warquest_box_icon("info", $message);
		
	} else {
	
		warquest_info($message);
	}
}

/*
** ---------------------
** HANDLER
** ---------------------
*/

/**
 * cron handler
 */
function warquest_cron() {
	
	$query  = 'select cid from cron where DATE(last_run)!="'.date("Y-m-d").'"'; 
	$result = warquest_db_query($query);	
	
	if ($data=warquest_db_fetch_object($result)) {
	
		/* Event handler */
		switch ($data->cid) {
		
			case 1:
				warquest_info("CRON JOB [".$data->cid."] robot allies update - job start.");
				warquest_db_cron_update($data->cid);
				warquest_cron_robot_alliancy_update(0);				
				warquest_info("CRON JOB [".$data->cid."] robot allies update - job end.");
				break;
		
			case 2:
				warquest_info("CRON JOB [".$data->cid."] clean battle log - job start.");				
				warquest_db_cron_update($data->cid);
				warquest_cron_clean_battle_log(0);
				warquest_info("CRON JOB [".$data->cid."] clean battle log - job end.");
				break;
				
			case 3:
				warquest_info("CRON JOB [".$data->cid."] statistics - job start.");
				warquest_db_cron_update($data->cid);
				warquest_cron_statistics(0);								
				warquest_info("CRON JOB [".$data->cid."] statistics - job end.");
				break;
				
			case 4:
				warquest_info("CRON JOB [".$data->cid."] pay bank interest  job start.");
				warquest_db_cron_update($data->cid);
				warquest_cron_player_interest(0);				
				warquest_info("CRON JOB [".$data->cid."] pay bank interest - job end.");
				break;
				
			case 5:
				warquest_info("CRON JOB [".$data->cid."] clean bank log - job start.");
				warquest_db_cron_update($data->cid);
				warquest_cron_clean_bank_log(0);				
				warquest_info("CRON JOB [".$data->cid."] clean bank log - job end.");
				break;

			case 6:
				warquest_info("CRON JOB [".$data->cid."] delete pending alliance invitations - job start.");
				warquest_db_cron_update($data->cid);
				warquest_cron_delete_pending_invitations(0);
				warquest_info("CRON JOB [".$data->cid."] delete pending alliance invitations - job end.");
				break;
	
			case 7:
				warquest_info("CRON JOB [".$data->cid."] delete units of players with negative hourly income - job start.");
				warquest_db_cron_update($data->cid);
				 warquest_cron_negative_income(0);
				warquest_info("CRON JOB [".$data->cid."] delete units of players with negative hourly income - job end.");
				break;
				 
			default:
				warquest_error("CRON JOB [".$data->cid."] unknown job start.");
				warquest_db_cron_update($data->cid);
				warquest_error("CRON JOB [".$data->cid."] unknown job end.");
				break;				
		}		
	}	
}

/*
** ---------------------
** THE END
** ---------------------
*/

?>