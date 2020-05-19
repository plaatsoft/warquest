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

	global $output;
	global $handle;

	if (MYSQL == 1) {
	
		$handle = mysqli_connect($dbhost, $dbuser, $dbpass, $dbname);	
		
	} else {
	
		$handle = pg_connect('host='.$dbhost.' dbname='.$dbname.' user='.$dbuser.' password='.$dbpass);
	}
	
	if(!$handle) {
		
		$message = warquest_db_error();
		
		$output->popup .= warquest_box_icon('error', $message);
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

	global $handle;

	if (MYSQL == 1) {
	
		mysqli_close($handle);

	} else {
	
		$result = pg_close();
	}
	
	return $result;
}

/**
 * Show SQL error 
 * @unitTest
 */
function warquest_db_error() {

	if (MYSQL == 1) {
	
		$error = mysqli_connect_error();
		
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
	global $output;
	global $handle;
	
	$query_count++;
		
	warquest_debug($query);
	
	if (MYSQL == 1) {
	
		$result = mysqli_query($handle, $query);
		
	} else {
	
		$query = str_replace('"', '\'', $query); 
		$result = pg_query($query);
	}
		
	if (!$result) {

		$message = warquest_db_error().' - '.$query;
		
		$output->popup .= warquest_box_icon('error', $message);
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
	
		$data = $result->fetch_object();
		
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
	
	global $handle;
			
	if (MYSQL == 1) {
	
		$value = mysqli_real_escape_string($handle, $value);
		
	} else {
	
		$value = pg_escape_string($value);
	}
	
	return $value;
}

/**
 * Return number of rows
 * @unitTest
 */
function warquest_db_num_rows($value) {
	
	if (MYSQL == 1) {
	
		$value = mysqli_num_rows($value);
		
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

/**
 * Insert Statistics
 * @unitTest
 */
function warquest_db_statistics_insert($date, $request, $fights, $players, $logins, $missions, $gold, $casino) {

	$current = date('Y-m-d', $date);

	$query  = 'insert into statistics (date, requests, fights, players,  logins, missions, gold, casino) ';
	$query .= 'VALUES ("'.$current.'",'.$request.','.$fights.',';
	$query .= $players.', '.$logins.', '.$missions.', '.$gold.', '.$casino.')';
		
	warquest_db_query($query);	
	
	$query = 'select id from statistics where date="'.$current.'"';
	$result = warquest_db_query($query);
	$data = warquest_db_fetch_object($result);
	
	$value = 0;
	if ( isset($data->id) ) {
		$value = $data->id;
	} 
	return $value;
}

/**
 * update Statistics
 * @unitTest
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

/**
 * Get Statistics
 * @unitTest
 */
function warquest_db_statistics($date) {

	$query  = 'select id, requests, fights, players, logins, missions, gold, casino from statistics ';
	$query .= 'where date = "'.date("Y-m-d", $date).'"';

	$result = warquest_db_query($query);
	$data = warquest_db_fetch_object($result);
				
	return $data;	
}

/**
 * Count Statistics
 * @unitTest
 */
function warquest_db_statistics_count() {

	$query  = 'select count(id) as count from statistics';
	
	$result = warquest_db_query($query);
	$data = warquest_db_fetch_object($result);
	
	return $data->count;
}

/* 
** -----------------
** PLAYER_POLL
** ----------------- 
*/

/**
 * Insert Player Poll
 * @unitTest
 */
function warquest_db_player_poll_vote_add($pid, $poll_id, $answer_id) {

	$query  = 'insert into player_poll (pid, poll_id, answer_id ) values ('.$pid.','.$poll_id.','.$answer_id.')';		
	
	return warquest_db_query($query);
}

/**
 * Voted Player Poll
 * @unitTest
 */
function warquest_db_player_poll_voted($pid, $poll_id) {

	$query  = 'select answer_id from player_poll where pid='.$pid.' and poll_id='.$poll_id;
	
	$result = warquest_db_query($query);
	$data = warquest_db_fetch_object($result);
	
	$answer_id = 0;
	if ( isset($data->answer_id)) {
		$answer_id = $data->answer_id;
	}
			
	return $answer_id;
}

/**
 * Remove Player Poll
 * @unitTest
 */
function warquest_db_player_poll_vote_remove($pid, $poll_id) {

	$query  = 'delete from player_poll where pid='.$pid.' and poll_id='.$poll_id;
	
	return warquest_db_query($query);
}

/*
** -----------------
** CHAT
** -----------------
*/

/**
 * Insert Chat
 * @unitTest
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

/**
 * Insert comment
 * @unitTest
 * @Parameters
 *  pid1 = sender
 *  pid2 = receiver (0 = All)
 */
function warquest_db_comment_insert($tid, $cid, $pid1, $pid2, $comment) {

	$value = 0;
	$now = date('Y-m-d H:i:s');

	$query  = 'insert into comment (tid, cid, pid1, pid2, date, comment, deleted) values (';
	$query .= $tid.','.$cid.','.$pid1.','.$pid2.',"'.$now.'","'.warquest_db_escape($comment).'" ,0)';	
	
	warquest_db_query($query);
	
	$query = 'select id from comment where pid1='.$pid1.' and pid2='.$pid2.' and tid ='.$tid.' and cid='.$cid.' and date="'.$now.'"';
	$result = warquest_db_query($query);
	$data = warquest_db_fetch_object($result);
	
	if ( isset($data->id) ) {
		$value = $data->id;
	} 
	
	return $value;	
}

/**
 * update comment
 * @unitTest
 */
function warquest_db_comment_update($id, $comment) {

	$query  = 'update comment set comment="'.warquest_db_escape($comment).'" where id='.$id;			
	
	return warquest_db_query($query);
}

/**
 * Delete comment
 * @unitTest
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
	
/**
 * Delete all comments of a player.
 * @unitTest
 */
function warquest_db_comment_delete_all($pid) {

	$query = 'delete from comment where pid1='.$pid.' or pid2='.$pid; 
	
	return warquest_db_query($query);
}

/*
** -----------------
** TOPIC
** -----------------
*/

/**
 * Insert topic
 * @unitTest
 */
function warquest_db_topic_insert($pid, $fid, $description) {
	
	$value = 0;
	$now = date('Y-m-d H:i:s');
	
	$query  = 'insert into topic (fid, pid, description, date, deleted ) ';
	$query .= 'values ('.$fid.','.$pid.',"'.warquest_db_escape($description).'","'.$now.'", 0)';
			
	warquest_db_query($query);
		
	$query = 'select tid from topic where pid='.$pid.' and fid ='.$fid.' and date="'.$now.'"';
	$result = warquest_db_query($query);
	$data = warquest_db_fetch_object($result);
	
	if ( isset($data->tid) ) {
		$value = $data->tid;
	} 
	
	return $value;
}

/**
 * update topic
 * @unitTest
 */
function warquest_db_topic_update($tid, $description) {
	
	/* Create user account */
	$query  = 'update topic set description="'.warquest_db_escape($description).'" where tid='.$tid;
			
	return warquest_db_query($query);
}

/**
 * Delete topic
 * @unitTest
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


/*
** -----------------
** UNIT
** -----------------
*/

/**
 * Get unit 
 */
function warquest_db_unit($uid) {
	
	$query = 'select uid, price, gold, attack, defense, max, upkeep from unit where uid='.$uid;
	$result = warquest_db_query($query);	
	
 	return warquest_db_fetch_object($result); 
}

/*
** -----------------
** PLAYER UNIT
** -----------------
*/

/**
 * Add player Unit
 * @unitTest
 */
function warquest_db_unit_add($pid, $uid, $amount, $direct=0) {

	$query  = 'select amount from player_unit where pid='.$pid.' and uid='.$uid;	
	$result = warquest_db_query($query);
		
	/* If player unit exist */
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
		$query .= '('.$pid.','.$uid.','.$totalAmount.')';	    
	} 
	
	warquest_db_query($query);
	
	return $totalAmount;
}

/**
 * Delete player Unit
 * @unitTest
 */
function warquest_db_unit_delete($pid, $uid, $amount, $direct=0) {

	$query  = 'select amount from player_unit where pid='.$pid.' and uid='.$uid;	
	$result = warquest_db_query($query);
	
	if ($data=warquest_db_fetch_object($result)) {
		
		if ($direct==0) {
			$totalAmount = $data->amount - $amount;
		} else {
			$totalAmount = $amount;
		}
	
		if ( $totalAmount>0 ) {
			$query = 'update player_unit set amount='.$totalAmount.' where pid='.$pid.' and uid='.$uid;
		} else {
			$query = 'delete from player_unit where pid='.$pid.' and uid='.$uid; 
		}
		
		$result = warquest_db_query($query);
	}
	return $result;
}

/**
 * Delete all player unit(s)
 * @unitTest
 */
function warquest_db_player_unit_delete_all($pid) {

	$query = 'delete from player_unit where pid='.$pid; 
	
	return warquest_db_query($query);
}

/*
** -----------------
** UNIT_GROUP
** -----------------
*/

/**
 * Get unit group
 * @unitTest
 */
function warquest_db_unit_group($ugid) {
			
	$query  = 'select type, planet from unit_group where ugid='.$ugid;
	$result = warquest_db_query($query);
	$data = warquest_db_fetch_object($result);
	
	return $data;
}

/**
 * Get unit group Id 
 */
function warquest_db_unit_group_id($name, $planet) {

	$query = 'select ugid from unit_group where name="'.$name.'" and planet='.$planet;
	$result = warquest_db_query($query);	
	$data = warquest_db_fetch_object($result);
	
	$value = 0;
	if ( isset($data->ugid) ) {
		$value = $data->ugid;
	}
	
	return $value;	
}

/*
** -----------------
** PLAYER BUILDING
** -----------------
*/

/**
 * Add player building 
 * @unitTest
 */
function warquest_db_building_add($pid, $bid, $amount, $direct=0) {

	/* Unit amount of player */
	$query  = 'select amount from player_building where pid='.$pid.' and bid='.$bid;	
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
		$query .= '('.$pid.','.$bid.','.$totalAmount.')';	    
	} 
	
	warquest_db_query($query);
	
	return $totalAmount;
}

/**
 * Delete player building 
 * @unitTest
 */
function warquest_db_building_delete($pid, $bid, $amount, $direct=0) {

	/* Unit amount of player */
	$query  = 'select amount from player_building where pid='.$pid.' and bid='.$bid;	
	$result = warquest_db_query($query);
	
	if ($data = warquest_db_fetch_object($result)) {
		
		if ($direct==0) {
			$totalAmount = $data->amount - $amount;
		} else {
			$totalAmount = $amount;
		}
	
		if ( $totalAmount>0 ) {
			$query = 'update player_building set amount='.$totalAmount.' where pid='.$pid.' and bid='.$bid;
		} else {
			$query = 'delete from player_building where pid='.$pid.' and bid='.$bid; 
		}
	
		$result = warquest_db_query($query);
	}
	
	return $result;
}

/**
 * Delete all player building(s)
 * @unitTest
 */
function warquest_db_player_building_delete_all($pid) {

	$query = 'delete from player_building where pid='.$pid; 
	
	return warquest_db_query($query);
}

/**
 * Add player building discount
 * @unitTest
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

/**
 * Add player building maintenance
 * @unitTest
 */
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


/*
** -----------------
** BUILDING
** -----------------
*/

/**
 * Get building information 
 */
 
function warquest_db_building($bid) {

	$query  = 'select bid, price, ugid, gold, income, defense, energy, max from building where bid='.$bid;
	$result = warquest_db_query($query);	 
 	
	return warquest_db_fetch_object($result); 
}

	
/*
** -----------------
** BUILDING_GROUP
** -----------------
*/

/**
 * Get building group
 * @unitTest
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

/**
 * Update player mission
 * @unitTest
 */
function warquest_db_player_mission_update($pid, $mid, $progress, $part1, $part2=0) {
	
	$data = warquest_db_player_mission($pid, $mid);
		
	if (isset($data->pid)) {
	
		/* Update existing record. */
		$query  = 'update player_mission set progress='.$progress.', part='.$part1.', part2='.$part2.' ';
		$query .= 'where pid='.$pid.' and mid='.$mid; 
		
	} else {
		
		/* Record does not exist, create it. */
		$query  = 'insert into player_mission (pid, mid, progress, part, part2) values ';
		$query .= '('.$pid.','.$mid.','.$progress.','.$part1.','.$part2.')';	
	} 
	
	return warquest_db_query($query);
}

/**
 * Delete all player mission(s)
 * @unitTest
 */
function warquest_db_player_mission_delete_all($pid) {

	$query = 'delete from player_mission where pid='.$pid; 
	
	return warquest_db_query($query);
}


/**
 * Get player mission
 * @unitTest
 */
function warquest_db_player_mission($pid, $mid) {

	$query = 'select pid, mid, progress, part, part2 from player_mission where pid='.$pid.' and mid='.$mid; 	
	
	$result = warquest_db_query($query);  

	return warquest_db_fetch_object($result);	
}
			
/*
** -----------------
** PLAYER_PLAYER
** -----------------
*/

/**
 * Insert player player
 * @unitTest
 */
function warquest_db_alliance_insert($pid1, $pid2, $approved) { 
	
	/* Create alliance connection $pid1 -> $pid2 */
	$query  = 'insert into player_player (pid1, pid2, approved, invite_date) values ';
	$query .= '('.$pid1.','.$pid2.','.$approved.',"'.date("Y-m-d H:i:s", time()).'")';
	
	return warquest_db_query($query);
}
		
/**
 * Update player player
 * @unitTest
 */
function warquest_db_alliance_update($pid1, $pid2, $approved) { 
	
	/* Update alliance connection $pid1 -> $pid2	 */
	$query  = 'update player_player set approved='.$approved.' where pid1='.$pid1.' ';
	$query .= 'and pid2='.$pid2;
	
	return warquest_db_query($query);
}

/**
 * Delete player player
 * @unitTest
 */
function warquest_db_alliance_delete($pid1, $pid2) { 
	
	$query = 'delete from player_player where pid1='.$pid1.' and pid2='.$pid2;
	
	return warquest_db_query($query);
}

/**
 * Delete all player -> player relations of one player
 * @unitTest
 */
function warquest_db_alliance_delete_all($pid) {

	$query = 'delete from player_player where pid1='.$pid.' or pid2='.$pid;
	
	return warquest_db_query($query);
}

/**
 * Check ally
 * @unitTest
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
	
/**
 * Check alliance size
 * @unitTest
 */
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

/**
 * Check invite size
 * @unitTest
 */
function warquest_db_invite_size($pid) {
	
	$count=0;
	
	$query = 'select count(pid1) as total from player_player where approved=0 and (pid1='.$pid.' or pid2='.$pid.')'; 	
	$result = warquest_db_query($query);	
	
	if ($data = warquest_db_fetch_object($result)) {
		$count = $data->total;
	}
	
	return $count;
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
	$query .= 'last_login, prev_login, ip, browser, versie, platform, auto_login  ) ' ;
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
	$query .= 'versie="'.warquest_db_escape($member->versie).'", ';
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
		warquest_debug('member out cache');
		return $member_cache;
	}
	
	$query  = 'select pid, username, email, email_valid, last_login, prev_login, created, ip, browser, ';
	$query .= 'notification_comment, notification_alliance, ';
	$query .= 'versie, platform, auto_login from member where pid='.$pid;
	
	$result = warquest_db_query($query);
	
	$member_cache = warquest_db_fetch_object($result);
	
	return $member_cache;
}

/**
 * Update member username
 * @unitTest
 */
 function warquest_db_member_username_update($pid, $username) {

	$query  = 'update member set username = "'.warquest_db_escape($username).'" where pid='.$pid; 
	
	return warquest_db_query($query);
}

/**
 * Update member password
 * @unitTest
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
	$query .= 'pid, name, language, ';
	$query .= 'ammo, ammo_step, ammo_date,  ';
	$query .= 'health, health_step, health_date, ';
	$query .= 'energy, energy_step, energy_date, ';
	$query .= 'money, money_step, money_date, ';
	$query .= 'bonus_date, ';
	$query .= 'restore_health, restore_energy, restore_ammo, cease_fire_date, holiday_date, ';
	$query .= 'bank1, bank2, bank3, ';	
	$query .= 'lid, alliance, won_level, default_amount, bounty_level, rebel_level, mission_level,';
	$query .= 'request, request_date, last_battle, background, pattern, ';
	$query .= 'country, gold, planet, premium_date) ';
	$query .= 'values (';	
	$query .= $pid.', "'.warquest_db_escape($name).'", "en", ';
	$query .= $config["init_ammo_max"].', '.$config["init_ammo_step"].', "'.date("Y-m-d H:i:s", (time()+$config["init_ammo_timer"])).'", ';
	$query .= $config["init_health_max"].', '.$config["init_health_step"].', "'.date("Y-m-d H:i:s", (time()+$config["init_health_timer"])).'", ';	
	$query .= $config["init_energy_max"].', '.$config["init_energy_step"].', "'.date("Y-m-d H:i:s", (time()+$config["init_energy_timer"])).'", ';
	$query .= $config["init_money"].', '.$config["init_money_step"].', "'.date("Y-m-d H:i:s", (time()+$config["init_money_timer"])).'", ';	
	$query .= '"'.date("Y-m-d H:i:s", time()-10).'", ';
	$query .= '"'.date("Y-m-d H:i:s", time()-10).'", "'.date("Y-m-d H:i:s", time()-10).'", "'.date("Y-m-d H:i:s", time()-10).'", "'.date("Y-m-d H:i:s", time()-10).'", "'.date("Y-m-d H:i:s", time()-10).'", ';
	$query .= $config["init_money_bank1"].','.$config["init_money_bank2"].','.$config["init_money_bank3"].',';
	$query .= $config["init_level"].', 1, 1, 1, 1, 1, 1, ';
	$query .= '1,"'.date("Y-m-d H:i:s", time()).'", "'.date("Y-m-d H:i:s", time()).'",2,"0010000000000000", ';
	$query .= '"'.warquest_getlocation($_SERVER["REMOTE_ADDR"]).'", 0, '.PLANET_EARTH.',"'.date("Y-m-d H:i:s", time()).'")';  
		
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
	
	if ($player->money > MAX_VALUE) {
		$player->money=MAX_VALUE;
	}
	
	if ($player->bank1 > MAX_VALUE) {
		$player->bank1=MAX_VALUE;
	}
	
	if ($player->bank2 > MAX_VALUE) {
		$player->bank2=MAX_VALUE;
	}
	
	if ($player->bank3 > MAX_VALUE) {
		$player->bank3=MAX_VALUE;
	}

	$query  = 'update player set '; 
	$query .= 'name="'.warquest_db_escape($player->name).'", ';
	$query .= 'twitter="'.warquest_db_escape($player->twitter).'", ';
	$query .= 'health='.$player->health.', ';
	$query .= 'health_step='.$player->health_step.', ';
	$query .= 'health_date="'.$player->health_date.'", ';
	$query .= 'energy='.$player->energy.', ';
	$query .= 'energy_step='.$player->energy_step.', ';
	$query .= 'energy_date="'.$player->energy_date.'", ';
	$query .= 'ammo='.$player->ammo.', ';
	$query .= 'ammo_date="'.$player->ammo_date.'", ';
	$query .= 'ammo_step='.$player->ammo_step.', ';
	$query .= 'money='.number_format($player->money,0,'.', '').', ';
	$query .= 'money_step='.$player->money_step.', ';
	$query .= 'money_date="'.$player->money_date.'", ';
	$query .= 'gold='.$player->gold.', ';
	$query .= 'upkeep='.$player->upkeep.', ';
	$query .= 'experience='.$player->experience.', ';
	$query .= 'lid='.$player->lid.', ';	
	$query .= 'won='.$player->won.', ';
	$query .= 'won_level='.$player->won_level.', ';
	$query .= 'lost='.$player->lost.', ';
	$query .= 'mission='.$player->mission.', ';
	$query .= 'mission_level='.$player->mission_level.', ';
	$query .= 'alliance='.$player->alliance.', ';
	$query .= 'invite='.$player->invite.', ';
	$query .= 'bank1='.number_format($player->bank1,0,'.', '').', ';
	$query .= 'bank2='.number_format($player->bank2,0,'.', '').', ';
	$query .= 'bank3='.number_format($player->bank3,0,'.', '').', ';
	$query .= 'damage_units='.$player->damage_units.', ';
	$query .= 'damage_buildings='.$player->damage_buildings.', ';
	$query .= 'last_battle="'.$player->last_battle.'", ';
	$query .= 'country="'.$player->country.'", ';
	$query .= 'news_notification='.$player->news_notification.', ';
	$query .= 'chat_notification='.$player->chat_notification.', ';
	$query .= 'comment_notification='.$player->comment_notification.', ';
	$query .= 'clan_notification='.$player->clan_notification.', ';
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
	$query .= 'pattern="'.$player->pattern.'", ';	
	$query .= 'premium_date="'.$player->premium_date.'" ';
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
	$query .= 'experience, mission, mission_level, won, lost, ';	
	$query .= 'energy_step, health_step, language, background, ';
	$query .= 'money_step, money_date, gold, energy_date, health_date, ammo_date, ammo_step, ';
	$query .= 'news_notification, comment_notification, chat_notification, clan_notification, ';
	$query .= 'alliance, invite, bank1, bank2, bank3, upkeep, damage_units, damage_buildings, last_battle, ';
	$query .= 'default_force, default_mission, default_amount, ';
	$query .= 'bonus_date, request, request_date, casino, ';
	$query .= 'restore_health, restore_energy, restore_ammo, cease_fire_date, holiday_date, rebel_status, ';
	$query .= 'bounty, bounty_level, planet, pattern, rebel, rebel_level, premium_date ';
	$query .= 'from player where pid='.$pid;  
	
	$result = warquest_db_query($query);  

	return warquest_db_fetch_object($result);	
}

/**
 * Delete Player
 * @unitTest
 */
function warquest_db_player_delete($pid) {

	$query  = 'delete from player where pid='.$pid;

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

/**
 * Get Level
 * @unitTest
 */
$level_cache;
function warquest_db_level($lid) {
	
	global $level_cache;
	
	/* Cache layer (for faster response) */
	if (isset($level_cache) && ($lid==$level_cache->lid)) {
		warquest_debug('level out cache');
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

/**
 * Insert bank
 * @unitTest
 */
function warquest_db_bank_insert($pid1, $pid2, $bgid, $amount, $balance, $action) {
	
	$value = 0;
	$now = date('Y-m-d H:i:s');
	
	$query  = 'insert into bank (pid1, pid2, bgid, amount, date, balance, action) ';
	$query .= 'values ('.$pid1.','.$pid2.','.$bgid.','.$amount.',"'.$now.'",'.number_format($balance,0,'.', '').','.$action.')';
	
	warquest_db_query($query);  
	
	$query  = 'select id from bank where pid1='.$pid1.' and pid2='.$pid2.' and date="'.$now.'"';
	$result = warquest_db_query($query);
	$data   = warquest_db_fetch_object($result);
	
	if (isset($data->id)) {
		$value = $data->id;
	}
	
	return $value;
}

/**
 * Delete bank with pid
 * @unitTest
 */
function warquest_db_bank_delete_pid($pid) {

	$query = 'delete from bank where pid1='.$pid; 
	
	return warquest_db_query($query);	
}

/**
 * Delete bank with id
 * @unitTest
 */
function warquest_db_bank_delete($id) {

	$query  = 'delete from bank where id='.$id;

	return warquest_db_query($query);	
}


/*
** ---------------------
** PLAYER_STOCK
** ---------------------
*/

/**
 * Add Player Stock
 * @unitTest
 */
function warquest_db_player_stock_add($pid, $sid, $amount, $cost) {

	/* Get stock amount of player */
	$query  = 'select cost, amount from player_stock where pid='.$pid.' and sid='.$sid;
	$result = warquest_db_query($query);
		
	/* If stock exist */
	if ($data=warquest_db_fetch_object($result)) {
			
		$totalAmount = $data->amount + $amount;
		$totalCost = $data->cost + $cost;

		$query  = 'update player_stock set amount=';
		$query .= $totalAmount.', cost='.$totalCost.' where pid='.$pid.' and sid='.$sid; 
		
	} else {		
	
		$totalAmount = $amount;
		$totalCost = $cost;
		
		$query  = 'insert into player_stock (sid, pid, amount, cost) ';
		$query .= 'values ('.$sid.','.$pid.','.$totalAmount.','.$totalCost.')';	    		
	} 
	
	warquest_db_query($query);
	
	return $totalAmount;
}

/**
 * Remove Player Stock
 * @unitTest
 */
function warquest_db_player_stock_delete($pid, $sid, $amount) {

	/* Unit amount of player */
	$query  = 'select amount, cost from player_stock where pid='.$pid.' and sid='.$sid;	
	$result = warquest_db_query($query);
	
	/* If stock exist */
	if ($data=warquest_db_fetch_object($result)) {
		
		$totalAmount = $data->amount - $amount;
		$totalCost = $data->cost - (($data->cost / $data->amount) * $amount);
		
		if ( $totalAmount>0 ) {
			$query = 'update player_stock set amount='.$totalAmount.', cost='.$totalCost.' where pid='.$pid.' and sid='.$sid;
		} else {
			$query = 'delete from player_stock where pid='.$pid.' and sid='.$sid; 
		}
		
		$result = warquest_db_query($query);
	}
	
	return $result;
}

/**
 * Get Stock
 * @unitTest
 */
function warquest_db_player_stock_assest($pid) {

	$query  = 'select sum(a.cost) as cost from player_stock a left join stock b on a.sid=b.sid ';
	$query .= 'where a.pid='.$pid;
	
	$result = warquest_db_query($query);
	
	$total = 0;
	if ($data = warquest_db_fetch_object($result)) {
		$total = $data->cost;
	}
			
	return $total;
}

/**
 * Delete all player stock(s)
 * @unitTest
 */
function warquest_db_player_stock_delete_all($pid) {

	$query = 'delete from player_stock where pid='.$pid; 
	
	return warquest_db_query($query);
}

/*
** ---------------------
** STOCK
** ---------------------
*/

/**
 * Insert Stock
 * @unitTest
 */
function warquest_db_stock_insert($symbol, $pid) {
	
	$query  = 'insert into stock (symbol, gsid, pid) ';
	$query .= 'values ("'.warquest_db_escape($symbol).'", 4, '.$pid.')';
	
	warquest_db_query($query);	
	
	return warquest_db_stock_check($symbol, $pid);  
}

/**
 * Delete Stock
 * @unitTest
 */
function warquest_db_stock_delete($sid) {

	$query  = 'delete from stock where sid='.$sid;
	
	return warquest_db_query($query);	
}

/**
 * Check Stock
 * @unitTest
 */
function warquest_db_stock_check($symbol, $pid) {

	$value = 0;
	
	$query = 'select sid from stock where symbol="'.$symbol.'" and pid='.$pid;
	$result = warquest_db_query($query);	
	$data = warquest_db_fetch_object($result);

	if (isset($data->sid)) {
		$value = $data->sid;
	}
	
	return $value;
}

/*
** ---------------------
** BATTLE
** ---------------------
*/

/**
 * Insert Battle
 * @unitTest
 */
function warquest_db_battle_insert($pid1, $pid2, $money, $health, $exp, $win, $ugid, $bounty=0) {
	
	$value = 0;
	$now = date('Y-m-d H:i:s');
	
	$query  = 'insert into battle (pid1, pid2, date, money, health, experience, win, ugid, bounty) ';
   $query .= 'values ('.$pid1.','.$pid2.',"'.$now.'", ';
	$query .= $money.','.$health.','.$exp.','.$win.','.$ugid.','.$bounty.')';
	
	warquest_db_query($query);  
	
	$query  = 'select id from battle where pid1='.$pid1.' and pid2='.$pid2.' and date="'.$now.'"';
	$result = warquest_db_query($query);
	$data   = warquest_db_fetch_object($result);
	
	if (isset($data->id)) {
		$value = $data->id;
	}
	
	return $value;
}

/**
 * Delete Battle with pid
 * @unitTest
 */
function warquest_db_battle_delete_pid($pid) {

	$query  = 'delete from battle where pid1='.$pid.' or pid2='.$pid;
	
	return warquest_db_query($query);	
}

/**
 * Delete Battle
 * @unitTest
 */
function warquest_db_battle_delete($id) {

	$query  = 'delete from battle where id='.$id;
	
	return warquest_db_query($query);	
}
	
/*
** ---------------------
** BOUNTY
** ---------------------
*/

/**
 * Insert Bounty 
 * @unitTest
 */
function warquest_db_bounty_insert($pid1, $pid2, $amount, $experience ) {
	
	$value = 0;
	$now = date('Y-m-d H:i:s');
	
	$query  = 'insert into bounty (pid1, pid2, amount, experience, date) ';
	$query .= 'values ('.$pid1.','.$pid2.','.$amount.','.$experience.',"'.$now.'")';
	
	warquest_db_query($query);
	
	$query  = 'select id from bounty where pid1='.$pid1.' and pid2='.$pid2.' and date="'.$now.'"';
	$result = warquest_db_query($query);
	$data   = warquest_db_fetch_object($result);
	
	if (isset($data->id)) {
		$value = $data->id;
	}
	
	return $value;  
}

/**
 * Delete Bounty
 * @unitTest
 */
function warquest_db_bounty_delete($id) {
	
	$query  = 'delete from bounty where id='.$id;
	
	return warquest_db_query($query);  
}

/**
 * Bounty Possible
 * @unitTest
 */
function warquest_db_bounty_possible($pid1, $pid2) {
	
	$query  = 'select id from bounty where pid1='.$pid1.' and pid2='.$pid2;
	$result = warquest_db_query($query);
	
	$count=warquest_db_num_rows($result);
	
	return $count;
}


/**
 * Delete all bounty from one player
 * @unitTest
 */
function warquest_db_bounty_delete_all($pid) {

	$query = 'delete from bounty where pid1='.$pid.' or pid2='.$pid;
	
	return warquest_db_query($query);
}

/*
** ---------------------
** CRON
** ---------------------
*/

/**
 * Update Cron
 * @unitTest
 */
function warquest_db_cron_update($cid) {
		
	$query  = 'update cron set '; 
	$query .= 'last_run = "'.date("Y-m-d H:i:s").'" ';
	$query .= 'where cid='.$cid; 
	
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
	
	$now = date('Y-m-d H:i:s');
	
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

	$query  = 'update news set '; 
	$query .= 'body = "'.warquest_db_escape($news->body).'", ';
	$query .= 'content = "'.warquest_db_escape($news->content).'", ';
	$query .= 'language = "'.$news->language.'" ';
	$query .= 'where id='.$news->id; 
	
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

/**
 * Add Session 
 * @unitTest
 */
function warquest_db_session_add($pid) {
		
	/* First delete all old session */
	warquest_db_session_delete_pid($pid);
		
	/* Create new session */
	$now = date('Y-m-d H:i:s');
	
	$query  = 'insert into session (date, session_id, pid) values ("'.$now.'","'.$pid.'",'.$pid.')';	
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

/**
 * Validate Session 
 * @unitTest
 */
function warquest_db_session_valid( $session_id ) {
	
	/* Session expires after 351 days of inactivity */
	$expired_days = 351;
	
	if (strlen($session_id)==0) {
		return 0;
	}
	
	$query  = 'select pid, date from session where session_id="'.$session_id.'"';
	$result = warquest_db_query($query);
	
	if ($data=warquest_db_fetch_object($result)) {
		
		$expired = mktime(date('H'), date('i'), date('s'), date('m'), date('d')-$expired_days, date('Y'));
		if ($data->date < date('Y-m-d H:i:s',$expired)) {
		
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

/**
 * Delete Session with pid
 * @unitTest
 */
function warquest_db_session_delete_pid($pid) {
		
	$query  = 'delete from session where pid='.$pid;	
	
	return warquest_db_query($query); 
}

/**
 * Delete Session with session id
 * @unitTest
 */
function warquest_db_session_delete($session_id) {
	
	$query  = 'delete from session where session_id="'.$session_id.'"';
	
	return warquest_db_query($query); 
}

/**
 * hack a player session for debug reasons (Admin functionality)
 * @unitTest
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

/**
 * Insert bonus
 * @unitTest
 */
function warquest_db_bonus_insert($pid, $bonus_id) {

	$query  = 'insert into bonus (bonus_id, pid, date) values (';
	$query .= $bonus_id.','.$pid.',"'.date("Y-m-d H:i:s", time()).'")';	
	
	return warquest_db_query($query);
}

/**
 * Get bonus
 * @unitTest
 */
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

	$now = date('Y-m-d H:i:s');
	
	$query  = 'insert into clan (name, pid, created, last_activity, logo) values ("';
	$query .= warquest_db_escape($name).'",'.$pid.',"'.$now.'","'.$now.'",1)';	
		
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

	$query  = 'select cid, name, created, last_activity, pid, won, lost, money, ';
	$query .= 'attack, defense, slogan, mission, logo, min_level from clan where cid='.$cid;	
	
	$result = warquest_db_query($query);
	
	$data = warquest_db_fetch_object($result);
		
	return $data;
}

/**
 * Update clan
 * @unitTest
 */
function warquest_db_clan_update($data) {
	
	$query  = 'update clan set '; 
	$query .= 'name = "'.warquest_db_escape($data->name).'", ';
	$query .= 'last_activity = "'.$data->last_activity.'", ';	
	$query .= 'won = '.$data->won.', ';
	$query .= 'lost = '.$data->lost.', ';	
	$query .= 'money = '.$data->money.', ';	
	$query .= 'attack = '.$data->attack.', ';	
	$query .= 'defense = '.$data->defense.', ';	
	$query .= 'slogan = "'.warquest_db_escape($data->slogan).'", ';	
	$query .= 'mission = '.$data->mission.', ';			
	$query .= 'logo = '.$data->logo.', ';	
	$query .= 'min_level = '.$data->min_level.' ';		
	$query .= 'where cid='.$data->cid; 
	
	return warquest_db_query($query);  
}

/**
 * Delete clan
 * @unitTest
 */
function warquest_db_clan_delete($cid) {
	
	$query  = 'delete from clan where cid='.$cid;
	
	return warquest_db_query($query); 
}

/**
 * Get strength of clan
 */
function warquest_db_clan_strength($cid) {

	$query  = 'select sum(b.lid) as strength from player_clan a, player b where a.pid=b.pid and a.approved=1 ';
	$query .= 'and a.cid='.$cid;
	
	$result = warquest_db_query($query);	
	$data = warquest_db_fetch_object($result);
	
	return $data->strength;
}

/*
** ---------------------
** CLAN_MISSION
** ---------------------
*/

/**
 * Get clan mission
 * @unitTest
 */
function warquest_db_clan_mission($cid, $mid) {
	
	$query  = 'select cid, mid, progress from clan_mission where cid='.$cid.' and mid='.$mid;	
	$result = warquest_db_query($query);	
	
	return warquest_db_fetch_object($result);
}

/**
 * Update clan_mission
 * @unitTest
 */
function warquest_db_clan_mission_update($cid, $mid, $progress) {
	
	$data = warquest_db_clan_mission($cid, $mid);
		
	if (isset($data->cid)) {
	
		/* Update existing record. */
		$query  = 'update clan_mission set '; 
		$query .= 'progress='.$progress.' ';
		$query .= 'where cid='.$cid.' and mid='.$mid; 
		
	} else {
		
		/* Record does not exist, create it. */
		$query  = 'insert into clan_mission (cid, mid, progress) values (';
		$query .= $cid.','.$mid.','.$progress.')';	
	} 
		
	return warquest_db_query($query);  
}

/**
 * Delete clan
 * @unitTest
 */
function warquest_db_clan_mission_delete($cid, $mid) {
	
	$query  = 'delete from clan_mission where cid='.$cid.' and mid='.$mid;
	
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
function warquest_db_player_clan_insert($pid, $cid, $approved, $role) {

	$now = date('Y-m-d H:i:s');
	
	$query  = 'insert into player_clan (pid, cid, joined, approved, role) values (';
	$query .= $pid.','.$cid.',"'.$now.'",'.$approved.','.$role.')';	
	
	return warquest_db_query($query);
}

/**
 * Update player_clan
 * @unitTest
 */
function warquest_db_player_clan_update($data) {

	$query  = 'update player_clan set '; 
	$query .= 'approved = '.$data->approved.', ';
	$query .= 'joined = "'.$data->joined.'", ';	
	$query .= 'role = "'.$data->role.'" ';	
	$query .= 'where pid='.$data->pid.' and cid='.$data->cid; 
	
	return warquest_db_query($query);
}

/**
 * Get player_clan
 * @unitTest
 */
function warquest_db_player_clan($pid) {

	$query  = 'select pid, cid, joined, approved, role from player_clan where pid ='.$pid;

	$result = warquest_db_query($query);
	
	return warquest_db_fetch_object($result);
}

/**
 * Delete player_clan
 * @unitTest
 */
function warquest_db_player_clan_delete($pid, $cid) {
	
	$query  = 'delete from player_clan where pid='.$pid.' and cid='.$cid;
	
	return warquest_db_query($query); 
}

/**
 * Get commander of selected clan
 */
function warquest_db_player_clan_commander($cid) {

	$player="";
	
	$query  = 'select pid from player_clan where role='.CLAN_ROLE_COMMANDER.' and cid='.$cid;

	$result = warquest_db_query($query);	 
	$data = warquest_db_fetch_object($result);

	if ( isset($data->pid) ) {	
		$player = warquest_db_player($data->pid);
	}
	
	return $player;
}

/*
** ---------------------
** MISSION
** ---------------------
*/

/**
 * Get Mission
 */
function warquest_db_mission($mid) {

	$query  = 'select mid, min_price, max_price, experience, loot, energy, alliance, ';
	$query .= 'lid, mgid from mission where mid='.$mid;  
	
	$result = warquest_db_query($query); 
	
	return warquest_db_fetch_object($result);	
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

	$query = 'select sid, x, y, cid, damage, conquer_date from sector where sid='.$sid;
	$result = warquest_db_query($query);	
	
	return warquest_db_fetch_object($result);	
}

/**
 * Update Sector
 * @unitTest
 */
function warquest_db_sector_update($data) {

	$now = date('Y-m-d H:i:s');

	$query  = 'update sector set '; 
	$query .= 'damage='.$data->damage.', ';
	$query .= 'cid='.$data->cid.', ';
	$query .= 'conquer_date="'.$now.'" ';
	$query .= 'where sid='.$data->sid; 
	
	return warquest_db_query($query);  
}

/*
** ---------------------
** INVITE
** ---------------------
*/

/**
 * Insert Invite
 * @unitTest
 */
function warquest_db_invite_insert($email, $approved, $pid) {

	$now = date('Y-m-d H:i:s');

	$query  = 'insert into invite (email, approved, date, pid) values (';
	$query .= '"'.$email.'",'.$approved.',"'.$now.'",'.$pid.')';	
	
	warquest_db_query($query);
	
	$query  = 'select id from invite where email="'.$email.'"'; 
	$result = warquest_db_query($query);	
	$data = warquest_db_fetch_object($result);
	
	$value = 0;
	if ( isset($data->id) ) {
		$value = $data->id;
	}
	
	return $value;
}

/**
 * Update Invite
 * @unitTest
 */
function warquest_db_invite_update($data) {

	$now = date('Y-m-d H:i:s');

	$query  = 'update invite set '; 
	$query .= 'email="'.$data->email.'", ';
	$query .= 'approved='.$data->approved.', ';
	$query .= 'date="'.$now.'", ';
	$query .= 'pid='.$data->pid.' ';
	$query .= 'where id='.$data->id; 
	
	return warquest_db_query($query);  
}

/**
 * Get Invite
 * @unitTest
 */
function warquest_db_invite($id) {

	$query = 'select id, email, approved, date, pid from invite where id='.$id;
	$result = warquest_db_query($query);	
	
	return warquest_db_fetch_object($result);	
}

/**
 * Check Invite
 * @unitTest
 */
function warquest_db_invite_check($email) {
	
	$query = 'select id from invite where email="'.$email.'"';
	$result = warquest_db_query($query);	
	$data = warquest_db_fetch_object($result);
	
	$value = 0;
	if ( isset($data->id) ) {
		$value = $data->id;
	}
	
	return $value;	
}

/*
** ---------------------
** PLANET
** ---------------------
*/

/**
 * Get Planet Id 
 */
function warquest_db_planet_id($name) {

	$query = 'select planet_id from planet where name="'.$name.'"';
	$result = warquest_db_query($query);	
	$data = warquest_db_fetch_object($result);
	
	$value = 0;
	if ( isset($data->planet_id) ) {
		$value = $data->planet_id;
	}
	
	return $value;	
}

/**
 * Get Planet Name 
 */
function warquest_db_planet_name($id) {

	$query = 'select name from planet where planet_id='.$id;
	$result = warquest_db_query($query);	
	$data = warquest_db_fetch_object($result);
	
	$value = '';
	if ( isset($data->name) ) {
		$value = $data->name;
	}
	
	return $value;	
}

/*
** ---------------------
** CLAN_BANK
** ---------------------
*/

/**
 * Insert clan bank
 */
function warquest_db_clan_bank_insert($cid, $pid, $amount, $balance, $action) {
	
	$value = 0;
	$now = date('Y-m-d H:i:s');
	
	$query  = 'insert into clan_bank (cid, pid, amount, balance, action, date) ';
	$query .= 'values ('.$cid.','.$pid.','.$amount.','.$balance.','.$action.',"'.$now.'")';
	
	warquest_db_query($query);  
	
	$query  = 'select cbid from clan_bank where cid='.$cid.' and pid='.$pid.' and date="'.$now.'"';
	$result = warquest_db_query($query);
	$data   = warquest_db_fetch_object($result);
	
	if (isset($data->id)) {
		$value = $data->id;
	}
	
	return $value;
}

/*
** ---------------------
** VIEWS
** ---------------------
*/

/**
 * Add views event (statistic use only)
 */
function warquest_db_view_add() {

	/* input */
	global $mid;
	global $sid;
	global $ssid;
	global $eid;
	
	if (!isset($mid)) {
		$mid=0;
	}
	
	if (!isset($sid)) {
		$sid=0;
	}
	
	if (!isset($ssid)) {
		$ssid=0;
	}
	
	if (!isset($eid)) {
		$eid=0;
	}
	
	$query  = 'select requests from views where mid='.$mid.' and sid='.$sid.' and ssid='.$ssid.' and eid='.$eid;	
	$result = warquest_db_query($query);
	$data = warquest_db_fetch_object($result);
	
	if (isset($data->requests)) {

		$query  = 'update views set requests='.++$data->requests;
		$query .= ' where mid='.$mid.' and sid='.$sid.' and ssid='.$ssid.' and eid='.$eid;	
		
	} else {		
	
		$query  = 'insert into views (mid, sid, ssid, eid, requests) values ';
		$query .= '('.$mid.','.$sid.','.$ssid.','.$eid.', 1)';	    
	} 
	
	return warquest_db_query($query);
}

/*
** ---------------------
** LOTTERY
** ---------------------
*/

/**
 * Insert lottery
 */
function warquest_db_lottery_insert($expire_date, $bet, $money, $gold, $uid, $uid_amount, $bid, $bid_amount) {

	$value = 0;
	
	$query  = 'insert into lottery (expire_date, bet, money, gold, uid, uid_amount, bid, bid_amount, done) ';
	$query .= 'values ("'.date("Y-m-d H:i:s", $expire_date).'",'.$bet.','.$money.','.$gold.','.$uid.','.$uid_amount.','.$bid.','.$bid_amount.',0)';
	
	warquest_db_query($query); 
	
	$query  = 'select lottery_id from lottery where expire_date="'.date("Y-m-d H:i:s", $expire_date).'" and bet='.$bet.' and gold='.$gold;
	$result = warquest_db_query($query);
	$data   = warquest_db_fetch_object($result);
	
	if (isset($data->lottery_id)) {
		$value = $data->lottery_id;
	}
	
	return $value;
}

/**
 * Update lottery
 */
function warquest_db_lottery_update($lottery) {
	
	$query  = 'update lottery set done='.$lottery->done.' ';
	$query .= 'where lottery_id='.$lottery->lottery_id;	
	
	return warquest_db_query($query);
}
		
/**
 * Get lottery
 */
function warquest_db_lottery($lottery_id) {
		
	$query  = 'select lottery_id, expire_date, bet, uid, uid_amount, bid, bid_amount, money, gold, done ';
	$query .= 'from lottery where lottery_id='.$lottery_id;
	
	$result = warquest_db_query($query);
	return warquest_db_fetch_object($result);
}

/*
** ---------------------
** PLAYER_LOTTERY
** ---------------------
*/

/**
 * Insert player lottery
 */
function warquest_db_player_lottery($pid, $lottery_id) {
	
	$now = date('Y-m-d H:i:s');
	
	$query  = 'insert into player_lottery (pid, lottery_id, bet_date, winner) ';
	$query .= 'values ('.$pid.','.$lottery_id.',"'.$now.'", 0)';
	
	return warquest_db_query($query);  
}

/**
 * Set player lottery winner
 */
function warquest_db_lottery_winner($pid, $lottery_id) {
	
	$query  = 'update player_lottery set winner=1 ';
	$query .= 'where pid='.$pid.' and lottery_id='.$lottery_id;	
	
	return warquest_db_query($query);
}

/*
** ---------------------
** THE END
** ---------------------
*/

?>