<?php

/* 
**  ========
**  WARQUEST
**  ========
**
**  @author wplaat
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
** DATABASE
** ---------------------------------------------------------------- 
*/

/* 
** -----------------
** GENERAL
** ----------------- 
*/

/**
 * Connect to database 
 * @unitTest
 * @output:   1 = ok | 0 = failure
 */
function warquest_db_connect($dbhost, $dbuser, $dbpass, $dbname) {

	global $popup;

	if (MYSQL == 1) {
	
		$handle = mysql_connect($dbhost, $dbuser, $dbpass);
		mysql_select_db($dbname);
		
	} else {
	
		$handle = pg_connect('host='.$dbhost.' dbname='.$dbname.' user='.$dbuser.' password='.$dbpass);
	}
	
	if(!$handle) {
		
		$message = warquest_db_error();
		
		$popup .= warquest_box_icon("error", $message);
		warquest_error($message);	
		
		return 0;		
	}
	return 1;
}

/**
 * Disconnect from database 
 * @unitTest   
 */
function warquest_db_close() {

	if (MYSQL == 1) {

		$result = mysql_close();

	} else {
	
		$result = pg_close();
	}
	
	return $result;
}

/**
 * Show SQL error 
 */
function warquest_db_error() {

	if (MYSQL == 1) {
	
		$error = mysql_error();
		
	} else {
	
		$error = pg_last_error();
	}
	
	return $error;
}

/**
 * Count queries 
 * @output:   queries count
 */
$query_count=0;
function warquest_db_count() {

	global $query_count;

	return $query_count;
}

/**
 * Execute database multi query
 * @unitTest
 */
function warquest_db_multi_query($queries) {

	$tokens = @preg_split("/;/", $queries);
	foreach ($tokens as $token) {
	
		$token=trim($token);
		if (strlen($token)>3) {
			warquest_db_query($token);		
		}
	}
}

/**
 * Execute database query
 * @unitTest
 * @output:   Database result
 */
function warquest_db_query($query) {
			
	global $query_count;
	global $popup;
	
	$query_count++;
		
	warquest_debug($query);
	
	if (MYSQL == 1) {
	
		$result = mysql_query($query);
		
	} else {
	
		$query = str_replace('"', '\'', $query); 
		$result = pg_query($query);
	}
		
	if (!$result) {

		$message = warquest_db_error().' - '.$query;
		
		$popup .= warquest_box_icon("error", $message);
		warquest_error($message);
	}
	
	return $result;
}

/**
 * Fetch query result 
 * @unitTest
 */
function warquest_db_fetch_object($result) {
	
	if (MYSQL == 1) {
	
		$data = @mysql_fetch_object($result);	
		
	} else {
	
		$data = @pg_fetch_object($result);
	}
	
	return $data;
}

/**
 * Escape SQL value 
 * @unitTest
 */
function warquest_db_escape($value) {
	
	if (MYSQL == 1) {
	
		$value = mysql_real_escape_string($value);
		
	} else {
	
		$value = pg_escape_string($value);
	}
	
	return $value;
}

/**
 * Return number of rows
 */
function warquest_db_num_rows($value) {
	
	if (MYSQL == 1) {
	
		$value = mysql_num_rows($value);
		
	} else {
	
		$value = pg_num_rows($value);
	}
	
	return $value;
}

/* 
** -----------------
** STATISTICS
** ----------------- 
*/

function warquest_db_statistics_update($data) {

	$query  = 'update statistics set ';
	$query .= 'requests='.$data->requests.', ';
	$query .= 'fights='.$data->fights.', ';
	$query .= 'players='.$data->players.', ';
	$query .= 'logins='.$data->logins.', ';
	$query .= 'missions='.$data->missions.', ';
	$query .= 'gold='.$data->gold.', ';
	$query .= 'casino='.$data->casino.' ';
	$query .= 'where id='.$data->id; 

	return warquest_db_query($query);	
}

function warquest_db_statistics_insert($date, $request, $fights, $players, $logins, $missions, $gold, $casino) {

	$query  = 'insert into statistics (date, requests, fights, players,  logins, missions, gold, casino) ';
	$query .= 'VALUES ("'.date("Y-m-d", $date).'",'.$request.','.$fights.',';
	$query .= $players.', '.$logins.', '.$missions.', '.$gold.', '.$casino.')';
		
	return warquest_db_query($query);	
}

function warquest_db_statistics($date) {

	$query  = 'select id, requests, fights, players, logins, missions, gold, casino from statistics where date = "'.date("Y-m-d", $date).'"';

	$result = warquest_db_query($query);
	$data = warquest_db_fetch_object($result);
				
	return $data;	
}

/* 
** -----------------
** PLAYER_POLL
** ----------------- 
*/

function warquest_db_player_poll_voted($pid, $poll_id) {

	$query  = 'select answer_id from player_poll where pid='.$pid.' and poll_id='.$poll_id;
	
	$result = warquest_db_query($query);
	
	$id=0;
	if ($data = warquest_db_fetch_object($result)) {
		$id = $data->answer_id;
	}
			
	return $id;
}

function warquest_db_player_poll_vote_add($pid, $answer_id, $poll_id) {

	$query  = 'insert into player_poll (pid, answer_id, poll_id) values ('.$pid.','.$answer_id.','.$poll_id.')';		
	
	return warquest_db_query($query);
}

function warquest_db_player_poll_vote_remove($pid, $poll_id) {

	$query  = 'delete from player_poll where pid='.$pid.' and poll_id='.$poll_id;
	
	return warquest_db_query($query);
}

/*
** -----------------
** CHAT
** -----------------
*/

function warquest_db_chat_insert($pid1, $pid2, $message) {

	$query  = 'insert into chat (pid1, pid2, date, message) values (';
	$query .= $pid1.','.$pid2.',"'.date("Y-m-d H:i:s", time()).'","'.warquest_db_escape($message).'")';	
	
	return warquest_db_query($query);
}
		
/*
** -----------------
** COMMENT
** -----------------
*/

function warquest_db_comment_delete($id) {
	
	$returnValue=0;
		
	$query = 'select deleted from comment where id='.$id;	
	$result = warquest_db_query($query);
	
	$data = warquest_db_fetch_object($result);
	
	if ($data->deleted==0) {
	
		$query = 'update comment set deleted=1 where id='.$id;		
		warquest_db_query($query);
		
		$returnValue=1;
	}
	
	return $returnValue;
}

function warquest_db_comment_update($id, $comment) {

	$query  = 'update comment set comment="'.warquest_db_escape($comment).'" where id='.$id;			
	
	return warquest_db_query($query);
}
					
function warquest_db_comment_insert($tid, $pid1, $pid2, $comment) {

	$query  = 'insert into comment (tid, pid1, pid2, date, comment, deleted) values (';
	$query .= $tid.','.$pid1.','.$pid2.',"'.date("Y-m-d H:i:s", time()).'","'.warquest_db_escape($comment).'" ,0)';	
	
	return warquest_db_query($query);
}
				
/*
** -----------------
** TOPIC
** -----------------
*/

function warquest_db_topic_delete($tid) {
	
	$returnValue=0;
		
	$query = 'select deleted from topic where tid='.$tid;	
	$result = warquest_db_query($query);
	
	$data = warquest_db_fetch_object($result);
	
	if ($data->deleted==0) {
	
		$query = 'update topic set deleted=1 where tid='.$tid;		
		warquest_db_query($query);
		
		$query = 'update comment set deleted=1 where tid='.$tid;
		warquest_db_query($query);
		
		$returnValue=1;
	}
	
	return $returnValue;
}

function warquest_db_topic_update($tid, $description) {
	
	/* Create user account */
	$query  = 'update topic set description="'.warquest_db_escape($description).'" where tid='.$tid;
			
	return warquest_db_query($query);
}

function warquest_db_topic_insert($pid, $fid, $description) {
	
	/* Create user account */
	$query  = 'insert into topic (fid, pid, description, date, deleted ) ';
	$query .= 'values ('.$fid.','.$pid.',"'.warquest_db_escape($description).'","'.date("Y-m-d H:i:s").'", 0)';
			
	return warquest_db_query($query);
}
	
/*
** -----------------
** UNIT
** -----------------
*/

function warquest_db_unit_add($pid, $uid, $amount, $direct=0) {

	/* Unit amount of player */
	$query  = "select amount from player_unit where pid=".$pid." and uid=".$uid;	
	$result = warquest_db_query($query);
		
	/* If unit exist */
	if ($data=warquest_db_fetch_object($result)) {
			
		if ($direct==0) {
			$totalAmount = $data->amount + $amount;
		} else {
			$totalAmount = $amount;
		}
		$query  = 'update player_unit set amount='.$totalAmount;
		$query .= ' where pid='.$pid.' and uid='.$uid; 
	} else {		
		$totalAmount = $amount;
		$query  = 'insert into player_unit (pid, uid, amount) values ';
		$query .= '('.$pid.','.$uid.','.$amount.')';	    
	} 
	
	warquest_db_query($query);
	
	return $totalAmount;
}

function warquest_db_unit_delete($pid, $uid, $amount, $direct=0) {

	/* Unit amount of player */
	$query  = "select amount from player_unit where pid=".$pid." and uid=".$uid;	
	$result = warquest_db_query($query);
	
	if ($data=warquest_db_fetch_object($result)) {
		
		if ($direct==0) {
			$totalAmount = $data->amount - $amount;
		} else {
			$totalAmount = $amount;
		}
	
		if ( $totalAmount>0 ) {
			$query = "update player_unit set amount=".$totalAmount." where pid=".$pid." and uid=".$uid;
		} else {
			$query = "delete from player_unit where pid=".$pid." and uid=".$uid; 
		}
		
		$result = warquest_db_query($query);
	}
	return $result;
}

/*
** -----------------
** UNIT_GROUP
** -----------------
*/

function warquest_db_unit_group($ugid) {
			
	$query  = 'select type from unit_group where ugid='.$ugid;
	$result = warquest_db_query($query);
	$data = warquest_db_fetch_object($result);
	
	return $data;
}
		
/*
** -----------------
** BUILDING
** -----------------
*/

function warquest_db_discount($player, $planet) {

	$discount=0;

	$query  = 'select ifnull(sum(a.discount),0) as discount from building a ';
	$query .= 'left join building_group b on a.bgid=b.bgid ';
	$query .= 'left join player_building c on c.bid=a.bid ';
	$query .= 'where b.planet='.$planet.' and a.discount>0 and c.pid='.$player->pid;

	$result = warquest_db_query($query);
	
	if ($data = warquest_db_fetch_object($result)) {
		$discount = $data->discount;
	}
		
	return $discount;
}

function warquest_db_maintenance($player, $planet) {

	$maintenance=0;

	$query  = 'select ifnull(sum(a.maintenance),0) as maintenance from building a ';
	$query .= 'left join building_group b on a.bgid=b.bgid ';
	$query .= 'left join player_building c on c.bid=a.bid ';
	$query .= 'where b.planet='.$planet.' and a.maintenance>0 and c.pid='.$player->pid;
	
	$result = warquest_db_query($query);
	
	if ($data = warquest_db_fetch_object($result)) {
		$maintenance = $data->maintenance;
	}
	
	return $maintenance;
}

function warquest_db_building_add($pid, $bid, $amount, $direct=0) {

	/* Unit amount of player */
	$query  = "select amount from player_building where pid=".$pid." and bid=".$bid;	
	$result = warquest_db_query($query);
		
	/* If unit exist */
	if ($data=warquest_db_fetch_object($result)) {
			
		if ($direct==0) {
			$totalAmount = $data->amount + $amount;
		} else {
			$totalAmount = $amount;
		}
		$query  = 'update player_building set amount='.$totalAmount;
		$query .= ' where pid='.$pid.' and bid='.$bid; 
		
	} else {		
		$totalAmount = $amount;
		$query  = 'insert into player_building (pid, bid, amount) values ';
		$query .= '('.$pid.','.$bid.','.$amount.')';	    
	} 
	
	warquest_db_query($query);
	
	return $totalAmount;
}

function warquest_db_building_delete($pid, $bid, $amount, $direct=0) {

	/* Unit amount of player */
	$query  = "select amount from player_building where pid=".$pid." and bid=".$bid;	
	$result = warquest_db_query($query);
	
	if ($data = warquest_db_fetch_object($result)) {
		
		if ($direct==0) {
			$totalAmount = $data->amount - $amount;
		} else {
			$totalAmount = $amount;
		}
	
		if ( $totalAmount>0 ) {
			$query = "update player_building set amount=".$totalAmount." where pid=".$pid." and bid=".$bid;
		} else {
			$query = "delete from player_building where pid=".$pid." and bid=".$bid; 
		}
	
		$result = warquest_db_query($query);
	}
	
	return $result;
}

/*
** -----------------
** BUILDING_GROUP
** -----------------
*/

function warquest_db_building_group($bgid) {
			
	$query  = 'select planet, sell, type from building_group where bgid='.$bgid; 
	$result = warquest_db_query($query);
	$data = warquest_db_fetch_object($result);
	
	return $data;
}

/* -----------------
** PLAYER_MISSION
** -----------------
*/

function warquest_db_mission_progress_update($pid, $mid, $progress, $part1, $part2=0) {
		
	$query = 'select progress from player_mission where pid='.$pid.' and mid='.$mid; 	
	$result = warquest_db_query($query); 
	
	if (warquest_db_fetch_object($result)) {
	
		/* Update existing record. */
		$query  = "update player_mission set progress=".$progress.", part=".$part1.", part2=".$part2." ";
		$query .= "where pid=".$pid." and mid=".$mid; 
		
	} else {
		
		/* Record does not exist, create it. */
		$query  = "insert into player_mission (pid, mid, progress, part, part2) values ";
		$query .= "(".$pid.",".$mid.",".$progress.",".$part1.",".$part2.")";	
	} 
	
	return warquest_db_query($query);
}
			
/*
** -----------------
** PLAYER_PLAYER
** -----------------
*/
		
function warquest_db_ally($pid1, $pid2) {
		
	$count=0;
	
	$query  = 'select count(pid1) as total from player_player where (pid1='.$pid1.' and pid2='.$pid2.') '; 
	$query .= 'or (pid2='.$pid1.' and pid1='.$pid2.')'; 	
	$result = warquest_db_query($query);
	
	if ($data = warquest_db_fetch_object($result)) {
		$count = $data->total;
	}
	
	return $count;
}
	
function warquest_db_alliance_size($pid) {
	
	$count=0;
	$query = 'select count(pid1) as total from player_player where approved=1 and pid1='.$pid; 	
	$result = warquest_db_query($query);	
	
	if ($data = warquest_db_fetch_object($result)) {
		$count = $data->total;
	}
		
	/* Add your self to the count */
	$count++;
	
	return $count;
}

function warquest_db_invite_size($pid) {
	
	$count=0;
	
	$query = 'select count(pid1) as total from player_player where approved=0 and (pid1='.$pid.' or pid2='.$pid.')'; 	
	$result = warquest_db_query($query);	
	
	if ($data = warquest_db_fetch_object($result)) {
		$count = $data->total;
	}
	
	return $count;
}

function warquest_db_alliance_insert($pid1, $pid2, $approved) { 
	
	/* Create alliance connection $pid1 -> $pid2 */
	$query  = 'insert into player_player (pid1, pid2, approved, invite_date) values ';
	$query .= '('.$pid1.','.$pid2.','.$approved.',"'.date("Y-m-d H:i:s", time()).'")';
	
	return warquest_db_query($query);
}
		

function warquest_db_alliance_update($pid1, $pid2, $approved) { 
	
	/* Update alliance connection $pid1 -> $pid2	 */
	$query  = 'update player_player set approved='.$approved.' where pid1='.$pid1.' ';
	$query .= 'and pid2='.$pid2;
	
	return warquest_db_query($query);
}

function warquest_db_alliance_delete($pid1, $pid2) { 
	
	$query = "delete from player_player where pid1=".$pid1." and pid2=".$pid2;	
	
	return warquest_db_query($query);
}
		
/*
** -----------------
** MEMBER
** -----------------
*/

/**
 * get member by username and password
 * @unitTest
 */
function warquest_db_member_pid($username, $password) {
	
	$pid=0;
	$query = 'select pid from member where username="'.$username.'" and password="'.md5($password).'"';	
	$result = warquest_db_query($query);
	
	$data=warquest_db_fetch_object($result);
	if (isset($data->pid)) {
		$pid = $data->pid;
	}
	return $pid;
}

/**
 * Insert member 
 * @unitTest
 */
function warquest_db_member_insert($username, $password, $email) {
	
	/* Create user account */
	$query  = 'insert into member (username, password, email, created, notification_comment, notification_alliance, ';
	$query .= 'last_login, prev_login, ip, browser, version, platform, auto_login  ) ' ;
	$query .= 'values ("'.warquest_db_escape($username).'","'.md5($password).'","'.warquest_db_escape($email).'",';
	$query .= '"'.date("Y-m-d H:i:s").'", 0, 0, "'.date("Y-m-d H:i:s").'", "'.date("Y-m-d H:i:s").'", "", "", "", "", 0)';
			
	warquest_db_query($query);

	return warquest_db_member_pid($username, $password);
}

/**
 * Insert update
 * @unitTest
 */
function warquest_db_member_update($member) {
		
	/* Update member */
	$query  = 'update member set '; 
	$query .= 'email = "'.warquest_db_escape($member->email).'", ';
	$query .= 'email_valid = '.$member->email_valid.', ';
	$query .= 'notification_comment='.$member->notification_comment.', ';
	$query .= 'notification_alliance='.$member->notification_alliance.', ';
	$query .= 'last_login = "'.$member->last_login.'", ';
	$query .= 'prev_login = "'.$member->prev_login.'", ';
	$query .= 'ip = "'.$member->ip.'", '; 
	$query .= 'browser="'.warquest_db_escape($member->browser).'", ';
	$query .= 'version="'.warquest_db_escape($member->version).'", ';
	$query .= 'platform="'.warquest_db_escape($member->platform).'", ';
	$query .= 'auto_login='.$member->auto_login.' ';
	$query .= 'where pid='.$member->pid; 
	
	return warquest_db_query($query);
}

/**
 * Get member by pid
 * @unitTest
 */
$member_cache;
function warquest_db_member($pid) {
	
	global $member_cache;
	
	/* Cache layer (for faster response) */
	if (isset($member_cache) && ($pid==$member_cache->pid)) {
		warquest_debug("member out cache");
		return $member_cache;
	}
	
	$query  = 'select pid, username, email, email_valid, last_login, prev_login, created, ip, browser, ';
	$query .= 'notification_comment, notification_alliance, ';
	$query .= 'version, platform, auto_login from member where pid='.$pid;
	
	$result = warquest_db_query($query);
	
	$member_cache = warquest_db_fetch_object($result);
	
	return $member_cache;
}

/**
 * Update member username
 */
 function warquest_db_member_username_update($pid, $username) {

	$query  = 'update member set username = "'.warquest_db_escape($username).'" where pid='.$pid; 
	
	return warquest_db_query($query);
}

/**
 * Update member password
 */
function warquest_db_member_password_update($pid, $password) {

	$query  = 'update member set password = "'.md5($password).'" where pid='.$pid; 
	
	return warquest_db_query($query);
}

/**
 * Delete member
 * @unitTest
 */
function warquest_db_member_delete($pid) {

	$query  = 'delete from member where pid='.$pid;

	return warquest_db_query($query);	
}
	
/* 
** -----------------
** PLAYER
** -----------------
*/

/*
 * Insert Player 
 * @unitTest
 */
function warquest_db_player_insert($name, $pid) {

	/* input */
	global $config;
	
	/* Create user account */
	$query  = 'insert into player (';
	$query .= 'pid, name, ';
	$query .= 'ammo, ammo_step, ammo_date,  ';
	$query .= 'health, health_step, health_date, ';
	$query .= 'energy, energy_step, energy_date, ';
	$query .= 'money, money_step, money_date, ';
	$query .= 'bonus_date, ';
	$query .= 'restore_health, restore_energy, restore_ammo, cease_fire_date, holiday_date, ';
	$query .= 'bank1, bank2, bank3, ';	
	$query .= 'lid, alliance, won_level, default_amount, bounty_level, rebel_level, ';
	$query .= 'request, request_date, last_battle, background, pattern, ';
	$query .= 'country, gold) ';
	$query .= 'values (';	
	$query .= $pid.', "'.warquest_db_escape($name).'", ';
	$query .= $config["init_ammo_max"].', '.$config["init_ammo_step"].', "'.date("Y-m-d H:i:s", (time()+$config["init_ammo_timer"])).'", ';
	$query .= $config["init_health_max"].', '.$config["init_health_step"].', "'.date("Y-m-d H:i:s", (time()+$config["init_health_timer"])).'", ';	
	$query .= $config["init_energy_max"].', '.$config["init_energy_step"].', "'.date("Y-m-d H:i:s", (time()+$config["init_energy_timer"])).'", ';
	$query .= $config["init_money"].', '.$config["init_money_step"].', "'.date("Y-m-d H:i:s", (time()+$config["init_money_timer"])).'", ';	
	$query .= '"'.date("Y-m-d H:i:s", time()-10).'", ';
	$query .= '"'.date("Y-m-d H:i:s", time()-10).'", "'.date("Y-m-d H:i:s", time()-10).'", "'.date("Y-m-d H:i:s", time()-10).'", "'.date("Y-m-d H:i:s", time()-10).'", "'.date("Y-m-d H:i:s", time()-10).'", ';
	$query .= $config["init_money_bank1"].','.$config["init_money_bank2"].','.$config["init_money_bank3"].',';
	$query .= $config["init_level"].', 1, 1, 1, 1, 1,';
	$query .= '1,"'.date("Y-m-d H:i:s", time()).'", "'.date("Y-m-d H:i:s", time()).'",1,"0010000000000000", ';
	$query .= '"'.warquest_getlocation($_SERVER["REMOTE_ADDR"]).'", '.$config["gold_dollar_ratio"].')';  
		
	$result = warquest_db_query($query);
	
	/* Initial bank balance */
	if ($config["init_money_bank1"]>0) {
		warquest_db_bank_insert($pid, 0, 1, $config["init_money_bank1"], $config["init_money_bank1"], 4);	
	}
	if ($config["init_money_bank2"]>0) {
		warquest_db_bank_insert($pid, 0, 2, $config["init_money_bank2"], $config["init_money_bank2"], 4);	
	}
	if ($config["init_money_bank3"]>0) {
		warquest_db_bank_insert($pid, 0, 3, $config["init_money_bank3"], $config["init_money_bank3"], 4);	
	}	
	
	return $result;
}

/**
 * Update Player 
 * @unitTest
 */
function warquest_db_player_update($player) {
	
	$query  = 'update player set '; 
	$query .= 'name="'.warquest_db_escape($player->name).'", ';
	$query .= 'twitter="'.warquest_db_escape($player->twitter).'", ';
	$query .= 'health='.$player->health.", ";
	$query .= 'health_step='.$player->health_step.", ";
	$query .= 'health_date="'.$player->health_date.'", ';
	$query .= 'energy='.$player->energy.", ";
	$query .= 'energy_step='.$player->energy_step.", ";
	$query .= 'energy_date="'.$player->energy_date.'", ';
	$query .= 'ammo='.$player->ammo.", ";
	$query .= 'ammo_date="'.$player->ammo_date.'", ';
	$query .= 'ammo_step='.$player->ammo_step.', ';
	$query .= 'money='.$player->money.", ";
	$query .= 'money_step='.$player->money_step.", ";
	$query .= 'money_date="'.$player->money_date.'", ';
	$query .= 'gold='.$player->gold.', ';
	$query .= 'upkeep='.$player->upkeep.", ";
	$query .= 'experience='.$player->experience.", ";
	$query .= 'lid='.$player->lid.", ";
	$query .= 'won_level='.$player->won_level.", ";
	$query .= 'won='.$player->won.", ";
	$query .= 'lost='.$player->lost.", ";
	$query .= 'mission='.$player->mission.", ";
	$query .= 'alliance='.$player->alliance.", ";
	$query .= 'invite='.$player->invite.", ";
	$query .= 'bank1='.$player->bank1.", ";
	$query .= 'bank2='.$player->bank2.", ";
	$query .= 'bank3='.$player->bank3.", ";
	$query .= 'damage_units='.$player->damage_units.", ";
	$query .= 'damage_buildings='.$player->damage_buildings.", ";
	$query .= 'last_battle="'.$player->last_battle.'", ';
	$query .= 'country="'.$player->country.'", ';
	$query .= 'news='.$player->news.', ';
	$query .= 'chat='.$player->chat.', ';
	$query .= 'comment='.$player->comment.', ';
	$query .= 'language="'.$player->language.'", ';
	$query .= 'background='.$player->background.', ';
	$query .= 'default_force="'.warquest_db_escape($player->default_force).'", ';
	$query .= 'default_mission="'.warquest_db_escape($player->default_mission).'", ';
	$query .= 'default_amount='.$player->default_amount.', ';
	$query .= 'request='.$player->request.', ';
	$query .= 'request_date="'.$player->request_date.'", ';
	$query .= 'bonus_date="'.$player->bonus_date.'", ';	
	$query .= 'casino='.$player->casino.', ';
	$query .= 'restore_health="'.$player->restore_health.'", ';
	$query .= 'restore_energy="'.$player->restore_energy.'", ';
	$query .= 'restore_ammo="'.$player->restore_ammo.'", ';
	$query .= 'cease_fire_date="'.$player->cease_fire_date.'", ';
	$query .= 'holiday_date="'.$player->holiday_date.'", ';
	$query .= 'rebel_status='.$player->rebel_status.', ';	
	$query .= 'bounty='.$player->bounty.', ';	
	$query .= 'bounty_level='.$player->bounty_level.', ';	
	$query .= 'planet='.$player->planet.', ';	
	$query .= 'rebel='.$player->rebel.', ';	
	$query .= 'rebel_level='.$player->rebel_level.', ';	
	$query .= 'pattern="'.$player->pattern.'" ';	
	$query .= 'where pid='.$player->pid; 	
		
	return warquest_db_query($query);
}

/**
 * Get player 
 * @unitTest
 */
function warquest_db_player($pid) {

	/* Get player data */
	$query  = 'select pid, name, twitter, country, health, energy, ammo, money, lid, won_level, ';
	$query .= 'experience, mission, won, lost, ';	
	$query .= 'energy_step, health_step, language, background, ';
	$query .= 'money_step, money_date, gold, energy_date, health_date, ammo_date, ammo_step, news, comment, ';
	$query .= 'alliance, invite, bank1, bank2, bank3, upkeep, damage_units, damage_buildings, last_battle, ';
	$query .= 'default_force, default_mission, default_amount, ';
	$query .= 'bonus_date, request, request_date, casino, ';
	$query .= 'restore_health, restore_energy, restore_ammo, cease_fire_date, holiday_date, rebel_status, ';
	$query .= 'bounty, bounty_level, planet, pattern, chat, rebel, rebel_level ';
	$query .= 'from player where pid='.$pid;  
	
	$result = warquest_db_query($query);  

	return warquest_db_fetch_object($result);	
}

/**
 * Delete member
 * @unitTest
 */
function warquest_db_player_delete($pid) {

	$query  = 'delete from player where pid='.$pid;

	return warquest_db_query($query);	
}


function warquest_set_default_force($value) {
	
	global $player;
	global $config;
	
	$tmp1 = array(0,0,0,0,0);
	$tmp2 = json_decode($player->default_force);	

	for ($tmp=0; $tmp<$config["max_planets"]; $tmp++) {
		$tmp1[$tmp] = $tmp2[$tmp];
	}
	
	$tmp1[$player->planet] = $value;
	
	$player->default_force = json_encode($tmp1);
}

function warquest_get_default_force() {
	
	global $player;
	
	$value=0;

	if ($tmp = json_decode($player->default_force)) {
		$value = $tmp[$player->planet]; 
	}
		
	/* Reset default value if not available */
	if ($value==0) {
		
		switch ($player->planet) {
			
			case PLANET_EARTH: 	
						$value = 0;
						break;
					  
			case PLANET_MOON:  
						$value = 11;
						break;
					 
			case PLANET_MARS: 	
						$value = 18;
						break;
						
			case PLANET_ASTEROID: 	
						$value = 24;
						break;
		}
	}
	
	return $value;
}

function warquest_set_default_mission($value) {
	
	global $player;

	global $config;
	
	$tmp1 = array(0,0,0,0,0);
	$tmp2 = json_decode($player->default_mission);	

	for ($tmp=0; $tmp<$config["max_planets"]; $tmp++) {
		$tmp1[$tmp] = $tmp2[$tmp];
	}
	
	$tmp1[$player->planet] = $value;
	
	$player->default_mission = json_encode($tmp1); 
}

function warquest_get_default_mission($planet) {
	
	global $player;
	
	$value = 0;
	if ($tmp = json_decode($player->default_mission)) {
		$value = $tmp[$planet]; 
	}
		
	/* Go to Training mission */
	if ($player->lid==0) {
		return 0;
	}
	
	/* Set default value if not available */
	if ($value==0) {
		
		switch ($planet) {
			
			case PLANET_EARTH: 	
						$value = 1;
						break;
					  
			case PLANET_MOON:  
						$value = 10;
						break;
					 
			case PLANET_MARS: 	
						$value = 20;
						break;
						
			case PLANET_ASTEROID: 	
						$value = 30;
						break;
		}
	}
	
	return $value;
}

/** 
 * Count page requests on login page
 */
function warquest_db_player_login_counter($pid) {

	/* Get player data */
	$query =  "select request from player where pid=".$pid;  
	$result = warquest_db_query($query);
	
	$data = warquest_db_fetch_object($result);
	
	$data->request_date = date("Y-m-d H:i:s", time());
	$data->request+=1;

	/* update player data */
	$query  = 'update player set '; 	
	$query .= 'request='.$data->request.', ';
	$query .= 'request_date="'.$data->request_date.'" ';
	$query .= 'where pid='.$pid; 	
	
	return warquest_db_query($query);
}

/*
** -----------------
** SKILL
** -----------------
*/

/**
 * Insert skill 
 * @unitTest
 */
function warquest_db_skill_insert($pid, $skill_points) {
	
	/* input */
	global $config;
		
	$query  = 'insert into skill (pid, attack_max, defense_max, health_max, energy_max, ammo_max, skill_points, health_timer, energy_timer, ammo_timer ) ';
	$query .= 'values ('.$pid.','.$config["init_attack_max"].','.$config["init_defense_max"].','.$config["init_health_max"].',';
	$query .= $config["init_energy_max"].','.$config["init_ammo_max"].','.$skill_points.',0,0,0)';
	
	return warquest_db_query($query);
}

/**
 * update skill 
 * @unitTest
 */
function warquest_db_skill_update($skill) {
	
	/* update skill data */
	$query  = "update skill set "; 
	$query .= "attack_max=".$skill->attack_max.", ";
	$query .= "defense_max=".$skill->defense_max.", ";
	$query .= "health_max=".$skill->health_max.", ";
	$query .= "energy_max=".$skill->energy_max.", ";
	$query .= "ammo_max=".$skill->ammo_max.", ";
	$query .= "skill_points=".$skill->skill_points.", ";	
	$query .= "health_timer=".$skill->health_timer.", ";
	$query .= "energy_timer=".$skill->energy_timer.", ";
	$query .= "ammo_timer=".$skill->ammo_timer." ";
	$query .= "where pid=".$skill->pid; 
		
	return warquest_db_query($query);	
}

/**
 * Get skill 
 * @unitTest
 */
$skill_cache;
function warquest_db_skill($pid) {
	
	global $skill_cache;
	
	/* Cahce layer for faster response */
	if (isset($skill_cache) && ($pid==$skill_cache->pid)) {
		warquest_debug("Skill out cache");
		return $skill_cache;
	}
	
	/* Get skill data */
	$query  = "select pid, attack_max, defense_max, health_max, energy_max, ammo_max, skill_points, ";
	$query .= "health_timer, energy_timer, ammo_timer ";
	$query .= "from skill where pid=".$pid;  
	
	$result = warquest_db_query($query);	
	$skill_cache = warquest_db_fetch_object($result); 
	
	return $skill_cache;
}

/**
 * Delete skill
 * @unitTest
 */
function warquest_db_skill_delete($pid) {

	$query  = 'delete from skill where pid='.$pid;

	return warquest_db_query($query);	
}

/*
** -----------------
** LEVEL
** -----------------
*/

$level_cache;
function warquest_db_level($lid) {
	
	global $level_cache;
	
	/* Cache layer (for faster response) */
	if (isset($level_cache) && ($lid==$level_cache->lid)) {
		warquest_debug("level out cache");
		return $level_cache;
	}
	
	/* Get level data */
	$query =  'select lid, experience, unit_lost, building_lost, planet ';
	$query .= 'from level where lid='.$lid;  
	
	$result = warquest_db_query($query);	  	
	$level_cache = warquest_db_fetch_object($result);	
	
	return $level_cache;
}

/*
** ---------------------
** BANK
** ---------------------
*/

function warquest_db_bank_insert($pid1, $pid2, $bgid, $amount, $balance, $action) {
	
	$query  = 'insert into bank (pid1, pid2, bgid, amount, date, balance, action) ';
	$query .= 'values ('.$pid1.','.$pid2.','.$bgid.','.$amount.',"'.date("Y-m-d H:i:s").'",'.$balance.','.$action.')';
	
	return warquest_db_query($query);  
}

function warquest_db_bank_delete($id) {

	$query  = 'delete from bank where id='.$id;

	return warquest_db_query($query);	
}

function warquest_db_bank_assest($pid) {

	$query  = 'select sum(a.cost) as cost from player_stock a left join stock b on a.sid=b.sid ';
	$query .= 'where a.pid='.$pid;
	
	$result = warquest_db_query($query);
	
	$total = 0;
	if ($data = warquest_db_fetch_object($result)) {
		$total = $data->cost;
	}
			
	return $total;
}

/*
** ---------------------
** PLAYER_STOCK
** ---------------------
*/

function warquest_db_player_stock_add($pid, $sid, $amount, $cost) {

	/* Get stock amount of player */
	$query  = "select amount from player_stock where pid=".$pid." and sid=".$sid;
	$result = warquest_db_query($query);
		
	/* If stock exist */
	if ($data=warquest_db_fetch_object($result)) {
			
		$totalAmount = $data->amount + $amount;

		$query  = 'update player_stock set amount=';
		$query .= $totalAmount.', cost='.$cost.' where pid='.$pid.' and sid='.$sid; 
		
	} else {		
	
		$totalAmount = $amount;
		
		$query  = 'insert into player_stock (sid, pid, amount, cost) ';
		$query .= 'values ('.$sid.','.$pid.','.$totalAmount.','.$cost.')';	    		
	} 
	
	warquest_db_query($query);
	
	return $totalAmount;
}

function warquest_db_player_stock_delete($pid, $sid, $amount, $cost) {

	/* Unit amount of player */
	$query  = "select amount from player_stock where pid=".$pid." and sid=".$sid;	
	$result = warquest_db_query($query);
	
	/* If stock exist */
	if ($data=warquest_db_fetch_object($result)) {
		
		$totalAmount = $data->amount - $amount;
	
		if ( $totalAmount>0 ) {
			$query = "update player_stock set amount=".$totalAmount.", cost=".$cost." where pid=".$pid." and sid=".$sid;
		} else {
			$query = "delete from player_stock where pid=".$pid." and sid=".$sid; 
		}
		
		$result = warquest_db_query($query);
	}
	
	return $result;
}

/*
** ---------------------
** STOCK
** ---------------------
*/

function warquest_db_stock_insert($symbol, $pid) {
	
	$query  = 'insert into stock (symbol, gsid, pid) ';
	$query .= 'values ("'.warquest_db_escape($symbol).'", 4, '.$pid.')';
	
	return warquest_db_query($query);  
}

function warquest_db_stock_delete($sid) {

	$query  = 'delete from stock where sid='.$sid;
	
	return warquest_db_query($query);	
}

function warquest_db_check($symbol, $pid) {

	$returnValue = 0;
	
	$query = 'select sid from stock where symbol="'.$symbol.'" and pid='.$pid;
	$result = warquest_db_query($query);
	
	if ($data=warquest_db_fetch_object($result)) {
		$returnValue = $data->sid;
	}
	
	return $returnValue;
}


/*
** ---------------------
** BATTLE
** ---------------------
*/

function warquest_db_battle_insert($pid1, $pid2, $money, $health, $exp, $win, $ugid, $bounty=0) {
	
	$query  = 'insert into battle (pid1, pid2, date, money, health, experience, win, ugid, bounty) ';
   $query .= 'values ('.$pid1.','.$pid2.',"'.date("Y-m-d H:i:s").'", ';
	$query .= $money.','.$health.','.$exp.','.$win.','.$ugid.','.$bounty.')';
	
	return warquest_db_query($query);  
}

function warquest_db_battle_delete($id) {

	$query  = 'delete from battle where id='.$id;
	
	return warquest_db_query($query);	
}
	
/*
** ---------------------
** BOUNTY
** ---------------------
*/

function warquest_db_bounty_insert($pid1, $pid2, $amount, $experience ) {
	
	$query  = 'insert into bounty (pid1, pid2, amount, experience, date) ';
	$query .= 'values ('.$pid1.','.$pid2.','.$amount.','.$experience.',"'.date("Y-m-d H:i:s").'")';
	
	return warquest_db_query($query);	  
}

function warquest_db_bounty_delete($id) {
	
	$query  = 'delete from bounty where id='.$id;
	
	return warquest_db_query($query);  
}

function warquest_db_bounty_possible($pid1, $pid2) {
	
	$query  = 'select id from bounty where pid1='.$pid1.' and pid2='.$pid2;
	$result = warquest_db_query($query);
	
	$count=warquest_db_num_rows($result);
	
	return $count;
}

/*
** ---------------------
** CRON
** ---------------------
*/

function warquest_db_cron_update($cid) {
		
	$query  = "update cron set "; 
	$query .= 'last_run = "'.date("Y-m-d H:i:s").'" ';
	$query .= "where cid=".$cid; 
	
	return warquest_db_query($query);
}

/*
** ---------------------
** NEWS
** ---------------------
*/

/**
 * Insert News
 * @unitTest
 */
function warquest_db_news_insert($body, $content, $language ) {
	
	$now = date("Y-m-d H:i:s");
	
	$query  = 'insert into news (date, body, content, language) ';
	$query .= 'values ("'.$now.'","'.warquest_db_escape($body).'","';
	$query .= warquest_db_escape($content).'","'.$language.'")';
	
	warquest_db_query($query);  
	
	$query = 'select id from news where date="'.$now.'"';
	$result = warquest_db_query($query);
	$data = warquest_db_fetch_object($result);
	
	return $data->id;
}

/**
 * Update News
 * @unitTest
 */
function warquest_db_news_update($news) {

	$query  = "update news set "; 
	$query .= 'body = "'.warquest_db_escape($news->body).'", ';
	$query .= 'content = "'.warquest_db_escape($news->content).'", ';
	$query .= 'language = "'.$news->language.'" ';
	$query .= "where id=".$news->id; 
	
	return warquest_db_query($query);  
}

/**
 * Get News
 * @unitTest
 */
function warquest_db_news($id) {
	
	$query  = 'select id, body, content, language from news where id='.$id;
	
	$result = warquest_db_query($query);
	
	return warquest_db_fetch_object($result);
}

/**
 * Delete News
 * @unitTest
 */
function warquest_db_news_delete($id) {
	
	$query  = 'delete from news where id='.$id;
	
	return warquest_db_query($query);
}

/*
** ---------------------
** SESSION
** ---------------------
*/

function warquest_db_session_add($pid) {
		
	/* First delete all old session */
	$query  = 'delete from session where pid='.$pid;	
	warquest_db_query($query);  
		
	/* Create new session */
	$now = date("Y-m-d H:i:s");
	
	$query  = 'insert into session (date, session_id, pid) values ("'.$now.'","",'.$pid.')';	
	warquest_db_query($query);
	
	/* Return new session entry */
	$query  = 'select id from session where pid='.$pid.' and date="'.$now.'"';
	$result = warquest_db_query($query);
	$data = warquest_db_fetch_object($result);
	
	/* created unique session id */
	$tmp = md5($data->id);
	
	/* Update session state */
	$query  = 'update session set session_id = "'.$tmp.'" where id='.$data->id; 
	warquest_db_query($query);
	
	return $tmp;
}

function warquest_db_session_valid( $session_id ) {
	
	/* Session expires after 351 days of inactivity */
	$expired_days = 351;
	
	if (strlen($session_id)==0) {
		return 0;
	}
	
	$query  = 'select pid, date from session where session_id="'.$session_id.'"';
	$result = warquest_db_query($query);
	
	if ($data=warquest_db_fetch_object($result)) {
		
		$expired = mktime(date("H"), date("i"), date("s"), date("m"), date("d")-$expired_days, date("Y"));
		if ($data->date < date("Y-m-d H:i:s",$expired)) {
		
			$member=warquest_db_member($data->pid);	
		
			warquest_error($member->username.' session timeout');		
			warquest_info('logout (session timeout) ['.$data->pid.']');
		
			warquest_db_session_delete($session_id);
			return 0;
		}
	
		/* Update session state */
		$query  = 'update session set date = "'.date("Y-m-d H:i:s").'" where session_id="'.$session_id.'"'; 
		warquest_db_query($query);
		
		return $data->pid;
	}
	return 0;
}

function warquest_db_session_delete($session_id) {
	
	$query  = 'delete from session where session_id="'.$session_id.'"';
	
	return warquest_db_query($query); 
}

/**
 * hack a player session for debug reasons (Admin functionality)
 */
function warquest_db_session_hack($pid) {

	$query  = 'select session_id from session where pid='.$pid;
	$result = warquest_db_query($query);
	
	if ($data = warquest_db_fetch_object($result)) {
		return $data->session_id;
		
	} else {
	
		return warquest_db_session_add($pid);
	}
}

/*
** ---------------------
** BONUS
** ---------------------
*/

function warquest_db_bonus_insert($pid, $bonus_id) {

	$query  = 'insert into bonus (bonus_id, pid, date) values (';
	$query .= $bonus_id.','.$pid.',"'.date("Y-m-d H:i:s", time()).'")';	
	
	return warquest_db_query($query);
}

function warquest_db_bonus($pid, $bonus_id) {
	
	$query  = 'select pid from bonus where pid='.$pid.' and bonus_id='.$bonus_id;
		
	$result = warquest_db_query($query);
	
	$count = warquest_db_num_rows($result);
	
	return $count;
}

/*
** ---------------------
** CLAN
** ---------------------
*/

/**
 * Insert clan
 * @unitTest
 */
function warquest_db_clan_insert($pid, $name) {

	$query  = 'insert into clan (name, pid, date) values ("';
	$query .= warquest_db_escape($name).'",'.$pid.',"'.date("Y-m-d", time()).'")';	
		
	warquest_db_query($query);
	
	$query  = 'select cid from clan where name="'.$name.'"'; 
	$result = warquest_db_query($query);	
	$data = warquest_db_fetch_object($result);
	
	return $data->cid;
}

/**
 * Get clan
 * @unitTest
 */
function warquest_db_clan($cid) {

	$query  = 'select cid, name, slogan, date, won, lost, pid from clan where cid='.$cid;	
	
	$result = warquest_db_query($query);
	
	$data = warquest_db_fetch_object($result);
		
	return $data;
}

/**
 * Update clan
 * @unitTest
 */
function warquest_db_clan_update($data) {

	$query  = "update clan set "; 
	$query .= 'name = "'.warquest_db_escape($data->name).'", ';
	$query .= 'won = '.$data->won.', ';
	$query .= 'lost = '.$data->lost.', ';	
	$query .= 'slogan = "'.warquest_db_escape($data->slogan).'" ';	
	$query .= "where cid=".$data->cid; 
	
	return warquest_db_query($query);  
}

/**
 * Delete clan
 * @unitTest
 */
function warquest_db_clan_delete($cid) {
	
	$query  = 'delete from clan where cid="'.$cid.'"';
	
	return warquest_db_query($query); 
}


/*
** ---------------------
** PLAYER_CLAN
** ---------------------
*/

/**
 * Insert player_clan
 * @unitTest
 */
function warquest_db_player_clan_insert($pid, $cid) {

	$query  = 'insert into player_clan (pid, cid, date) values (';
	$query .= $pid.','.$cid.',"'.date("Y-m-d", time()).'")';	
	
	return warquest_db_query($query);
}

/**
 * Get player_clan
 * @unitTest
 */
function warquest_db_player_clan($pid) {

	$query  = 'select pid, cid from player_clan where pid ='.$pid;

	$result = warquest_db_query($query);
	
	return warquest_db_fetch_object($result);
}

/**
 * Delete player_clan
 * @unitTest
 */
function warquest_db_player_clan_delete($pid, $cid) {
	
	$query  = 'delete from player_clan where pid='.$pid.' and cid="'.$cid.'"';
	
	return warquest_db_query($query); 
}

/*
** ---------------------
** SECTOR
** ---------------------
*/

/**
 * Get Sector
 * @unitTest
 */
function warquest_db_sector($sid) {

	$query = 'select sid, x, y, cid, damage from sector where sid='.$sid;
	$result = warquest_db_query($query);	
	
	return warquest_db_fetch_object($result);	
}

/**
 * Update Sector
 * @unitTest
 */
function warquest_db_sector_update($data) {

	$query  = "update sector set "; 
	$query .= 'damage='.$data->damage.', ';
	$query .= 'cid='.$data->cid.' ';
	$query .= "where sid=".$data->sid; 
	
	return warquest_db_query($query);  
}

/*
** ---------------------
** THE END
** ---------------------
*/

?>