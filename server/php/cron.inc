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
** HELP
** ----------------------------------------------------------------
*/

/*
** ---------------------
** CRON
** ---------------------
*/

/**
 * Cron clear inactive clan sectors job
 */
function warquest_cron_clear_inactive_sectors($info=0) {

	/* input */
	global $config;

	/* output */
	global $output;

	$old = mktime(date("H"), date("i"), date("s"), date("m"), date("d")-$config["max_sector_inactive"], date("Y"));

	/* Get inactive sector(s) */
	$query  = 'select sid, cid from sector where conquer_date<"'.date("Y-m-d H:i:s", $old).'" ';
	$result = warquest_db_query($query);

	$count=0;

	while ($data = warquest_db_fetch_object($result)) {

		/* Update sector */

		$data2 = warquest_db_sector($data->sid);

		$data2->damage += rand(0,8);

		if ($data2->damage>=10) {

			$count++;

			/* To much damage, sector is lost */
			$data2->cid = 0;
			$data2->damage = rand(1,7);

			/* Update clan member(s) */
			$query3  = 'select cid, pid from player_clan where cid='.$data->cid;
			$result3 = warquest_db_query($query3);

			while ($data3 = warquest_db_fetch_object($result3)) {

				$player = warquest_db_player($data3->pid);
				warquest_netto_income($player);
				warquest_db_player_update($player);
			}
		}

		warquest_db_sector_update($data2);
	}

	$message = 'Clear '.$count.' inactive sectors!<br>';

	if ($info==1) {
		$output->popup .= warquest_box_icon("info", $message);
	}

	warquest_info($message);
}

/**
 * Cron backup job
 */
function warquest_cron_backup($info=0) {

	/* input */
	global $config;

	/* output */
	global $output;

	/* Remove old database backup file */
	$prev_date = mktime(date("H"), date("i"), date("s"), date("m"), date("d")-$config['backup_period'], date("Y"));
	$filename = 'backup/warquest-'.date('Ymd', $prev_date).'.sql';
	warquest_info('Remove old backup file '.$filename);
	@unlink($filename);

	/* Create new database backup file */
	$filename = 'backup/warquest-'.date("Ymd").'.sql';

   $backupFile = 'database_backup_'.date("YmdHis").'.sql';
	$command = 'mysqldump --user='.$config["dbuser"].' --password='.$config["dbpass"].' --host='.$config["dbhost"].' '.$config["dbname"].' > '.$filename;
	system($command);

	$message = 'Create new backup file '.$filename.'<br>';

	if ($info==1) {
		$output->popup .= warquest_box_icon("info", $message);
	}

	warquest_info($message);
}


/**
 * Cron negative income job
 */
function warquest_cron_negative_income($info=0) {

	/* input */
	global $config;

	/* output */
	global $output;

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

	$message = 'Unit sold by '.$count.' player(s) to get positive hourly income again!<br>';

	if ($info==1) {
		$output->popup .= warquest_box_icon("info", $message);
	}

	warquest_info($message);
}

/**
 * Cron update statistics job
 */
function warquest_cron_statistics($info=0) {

	/* input */
	global $config;

	$query1  = 'select count(*) as count, sum(won) as won, ';
	$query1 .= 'sum(mission) as missions, sum(casino) as casino from player';
	$result1 = warquest_db_query($query1);
	$data1 = warquest_db_fetch_object($result1);

	$date = mktime(date("H"), date("i"), date("s"), date("m"), date("d")-1, date("Y"));

	$query2  = 'select count(*) as count from member where last_login > "'.date("Y-m-d H:i:s", $date).'" ';
	$result2 = warquest_db_query($query2);
	$data2 = warquest_db_fetch_object($result2);

	$query3 =  'select sum(requests) as requests from views';
	$result3 = warquest_db_query($query3);
	$data3 = warquest_db_fetch_object($result3);

	if ($info==1) {
		$date = mktime(date("H"), date("i"), date("s"), date("m"), date("d"), date("Y"));
	}

	$stats = warquest_db_statistics($date);

	if ( isset($stats->id) ) {

		$stats->requests = $data3->requests;
		$stats->fights = $data1->won;
		$stats->players = $data1->count;
		$stats->logins = $data2->count;
		$stats->missions = $data1->missions;
		$stats->casino = $data1->casino;

		warquest_db_statistics_update($stats);

	} else {

		warquest_db_statistics_insert($date, $data3->requests, $data1->won, $data1->count, $data2->count, $data1->missions, 0, $data1->casino);
	}

	$message = 'Statistics of '.date("d-m-Y", $date).' updated!';

	if ($info!=1) {
		warquest_info($message);
	}
}

/**
 * Cron delete long pending invitations job
 */
function warquest_cron_delete_pending_invitations($info=0) {

	/* input */
	global $config;

	/* output */
	global $output;

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

	$message = $count.' pending ally request cleared! <br>';

	if ($info==1) {
		$output->popup .= warquest_box_icon("info", $message);
	}

	warquest_info($message);
}

/**
 * Cron clean battle job
 */
function warquest_cron_clean_battle_log($info=0) {

	/* input */
	global $config;

	/* output */
	global $output;

	$old = mktime(date("H"), date("i"), date("s"), date("m"), date("d")-$config["max_battle_log_age"], date("Y"));

	$count=0;
	$query  = 'select count(id) as total from battle where date < "'.date("Y-m-d H:i:s", $old).'" ';
	$result = warquest_db_query($query);
	if ($data = warquest_db_fetch_object($result)) {
		$count = $data->total;
	}

	$query = 'delete from battle where date < "'.date("Y-m-d H:i:s", $old).'" ';
	warquest_db_query($query);

	$message = $count.' battle records are deleted!';

	if ($info==1) {
		$output->popup .= warquest_box_icon("info", $message);
	}

	warquest_info($message);
}

/**
 * Cron robot alliancy accept job
 */
function warquest_cron_robot_alliancy_update($info=0) {

	/* output */
	global $output;

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

	$message = $count.' alliance requested accepted!<br>In total '.$robots.' robots checked.';

	if ($info==1) {
		$output->popup .= warquest_box_icon("info", $message);
	}

	warquest_info($message);
}

/**
 * Cron Player bank interest job
 */
function warquest_cron_bank_interest($info=0) {

	/* input */
	global $config;

	/* output */
	global $output;

	$query  = 'select pid, bank1, bank2, bank3 from player where ';
	$query .= 'holiday_date < "'.date("Y-m-d H:i:s", time()).'" and ';
	$query .= 'bank1>0 or bank2>0 or bank3>0 order by pid';
	$result = warquest_db_query($query);

	$count=0;

	while ($data=warquest_db_fetch_object($result)) {

		$found=0;

		if ($data->bank1>0) {
			$extra = round(($data->bank1/100) * $config["init_bank1_interest"]);
			$data->bank1 += $extra;
			warquest_db_bank_insert($data->pid, 0, 1, $extra, $data->bank1, 4);
			$found=1;
		}

		if ($data->bank2>0) {
			$extra = round(($data->bank2/100) * $config["init_bank2_interest"]);
			$data->bank2 += $extra;
			warquest_db_bank_insert($data->pid, 0, 2, $extra, $data->bank2, 4);
			$found=1;
		}

		if ($data->bank3>0) {
			$extra = round(($data->bank3/100) * $config["init_bank3_interest"]);
			$data->bank3 += $extra;
			warquest_db_bank_insert($data->pid, 0, 3, $extra, $data->bank3, 4);
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

	$message = number_format2($count).' players bank interest updated!';

	if ($info==1) {
		$output->popup .= warquest_box_icon("info", $message);
	}

	warquest_info($message);
}

/**
 * Cron Clan bank interest job
 */
function warquest_cron_clan_bank_interest($info=0) {

	/* input */
	global $config;

	/* output */
	global $output;

	$query  = 'select cid from clan where money>0';
	$result = warquest_db_query($query);

	$count=0;

	while ($data=warquest_db_fetch_object($result)) {

		$clan = warquest_db_clan($data->cid);

		$amount = round($clan->money * ($config["init_clan_bank_interest"] / 100));
		$clan->money -= $amount;

		warquest_db_clan_update($clan);

		warquest_db_clan_bank_insert($data->cid, 0, ($amount*-1), $clan->money, 7);

		$count++;
	}

	$message = number_format2($count).' clan bank interest updated!';

	if ($info==1) {
		$output->popup .= warquest_box_icon("info", $message);
	}

	warquest_info($message);
}

/**
 * Cron clean bank transaction log job
 */
function warquest_cron_clean_bank_log($info=0) {

	/* input */
	global $config;

	/* output */
	global $output;

	$old = mktime(date("H"), date("i"), date("s"), date("m"), date("d")-$config["max_bank_log_age"], date("Y"));

	$count = 0;
	$query  = 'select count(id) as total from bank where date < "'.date("Y-m-d H:i:s", $old).'" ';
	$result = warquest_db_query($query);
	if ($data = warquest_db_fetch_object($result)) {
		$count = $data->total;
	}

	$query = 'delete from bank where date < "'.date("Y-m-d H:i:s", $old).'" ';
	warquest_db_query($query);

	$message = $count.' player bank records are deleted!';

	if ($info==1) {
		$output->popup .= warquest_box_icon("info", $message);
	}

	warquest_info($message);
}


/**
 * Cron clean clan bank transaction log job
 */
function warquest_cron_clean_clan_bank_log($info=0) {

	/* input */
	global $config;

	/* output */
	global $output;

	$old = mktime(date("H"), date("i"), date("s"), date("m"), date("d")-$config["max_bank_log_age"], date("Y"));

	$count = 0;
	$query  = 'select count(cbid) as total from clan_bank where date < "'.date("Y-m-d H:i:s", $old).'" ';
	$result = warquest_db_query($query);
	if ($data = warquest_db_fetch_object($result)) {
		$count = $data->total;
	}

	$query = 'delete from clan_bank where date < "'.date("Y-m-d H:i:s", $old).'" ';
	warquest_db_query($query);

	$message = $count.' clan bank records are deleted!';

	if ($info==1) {
		$output->popup .= warquest_box_icon("info", $message);
	}

	warquest_info($message);
}

/**
 * Cron create new lottery
 */
function warquest_cron_add_lottery() {

	/* input */
	global $config;

	$query  = 'select lottery_id from lottery where done=0';
	$result = warquest_db_query($query);
	$count = warquest_db_num_rows($result);

	if ($count<3) {

		$expire_date = mktime(23, 59, 59, date("m"), date("d")+2, date("Y"));

		$planet = rand(1,$config["max_planets"]);

		$bet = rand(2,6);

		$value = 0;
		$query1  = 'select count(lottery_id) as total from lottery';
		$result1 = warquest_db_query($query1);
		$data1 = warquest_db_fetch_object($result1);
		if ( isset($data1->total) ) {
			$value = $data1->total;
		}

		$money = 0;
		$gold = 0;
		if (($value % 2)==1) {

			$gold = rand(500,1000);

		} else {

			$money = rand(10,40);
			$money *= 1000000000;
		}

		/* Select random gold unit */
		$query3  = 'select uid from unit where gold>0 and ugid in (select ugid from unit_group where planet='.$planet.') ';
		$query3 .= 'order by rand() limit 0, 1';
		$result3 = warquest_db_query($query3);
		$data3 = warquest_db_fetch_object($result3);

		$uid_amount = rand(10,20);

		/* Select random income or defence gold building */
		$query4  = 'select bid from building where gold>0 and bgid in (select bgid from building_group where type=1 and planet='.$planet.') ';
		$query4 .= 'order by rand() limit 0, 1';
		$result4 = warquest_db_query($query4);
		$data4 = warquest_db_fetch_object($result4);

		$bid_amount = rand(10,20);

		$id = warquest_db_lottery_insert($expire_date, $bet, $money, $gold, $data3->uid, $uid_amount, $data4->bid, $bid_amount);

		$message = 'Lottery '.$id.' added!<br>';

	} else {

		$message = 'More then 3 open lotteries, add lottery skipped!';
	}

	return $message;
}

/**
 * Cron update lottery job
 */
function warquest_cron_update_lottery($info=0) {

	/* input */
	global $config;

	/* output */
	global $output;

	$message = '';

	/* Get all expired lotteries */
	$now = date('Y-m-d H:i:s');

	$query1  = 'select lottery_id from lottery where expire_date <= "'.$now.'" and done=0';
	$result1 = warquest_db_query($query1);

	if ($data1 = warquest_db_fetch_object($result1)) {

		/* Get winning player (random) */
		$query2  = 'select pid from player_lottery where lottery_id='.$data1->lottery_id.' order by rand() limit 0, 1';
		$result2 = warquest_db_query($query2);
		$data2 = warquest_db_fetch_object($result2);

		/* Update lottery as done */
		$lottery = warquest_db_lottery($data1->lottery_id);
		$lottery->done=1;
		warquest_db_lottery_update($lottery);

		/* Winner found */
		if (isset($data2->pid)) {

			/* Set winner in database */
			warquest_db_lottery_winner($data2->pid, $lottery->lottery_id);

			/* Update player Units */
			if ($lottery->uid > 0) {
				warquest_db_unit_add($data2->pid, $lottery->uid, $lottery->uid_amount);
			}

			/* Update player Buildings */
			if ($lottery->bid > 0) {
				warquest_db_building_add($data2->pid, $lottery->bid, $lottery->bid_amount);
			}

			/* Update player profile */
			$player = warquest_db_player($data2->pid);

			$player->money += $lottery->money;
			$player->gold += $lottery->gold;
			$player->comment_notification++;

			warquest_netto_income($player);

			warquest_db_player_update($player);

			/* Send message to player */
			$comment = t('LOTTERY_WON', $lottery->lottery_id);
			warquest_db_comment_insert(0, 0, $config["adminPid"], $player->pid, $comment);
			warquest_user_log($player, $comment);

			$message .= 'Lottery '.$lottery->lottery_id.' finished. The winner is '.$player->name.' ['.$player->pid.']<br>';
		}
	}

	if (strlen($message)==0) {
		$message .= 'No lotteries expired! ';
	}

	/* Create new lottery */
	$message .= warquest_cron_add_lottery();

	if ($info==1) {
		$output->popup .= warquest_box_icon("info", $message);
	}

	warquest_info($message);
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
				warquest_info("CRON JOB [".$data->cid."] bank interest  job start.");
				warquest_db_cron_update($data->cid);
				warquest_cron_bank_interest(0);
				warquest_info("CRON JOB [".$data->cid."] bank interest - job end.");
				break;

			case 5:
				warquest_info("CRON JOB [".$data->cid."] bank clean transaction log - job start.");
				warquest_db_cron_update($data->cid);
				warquest_cron_clean_bank_log(0);
				warquest_info("CRON JOB [".$data->cid."] bank clean transaction log - job end.");
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

   		case 8:
				warquest_info('CRON JOB ['.$data->cid.'] make backup - job start.');
				warquest_db_cron_update($data->cid);
				warquest_cron_backup();
				warquest_info('CRON JOB ['.$data->cid.'] make backup - job end.');
				break;

			case 10:
				warquest_info('CRON JOB ['.$data->cid.'] clear inactive sectors - job start.');
				warquest_db_cron_update($data->cid);
				warquest_cron_clear_inactive_sectors();
				warquest_info('CRON JOB ['.$data->cid.'] clear inactive sectors - job end.');
				break;

			case 11:
				warquest_info('CRON JOB ['.$data->cid.'] clan bank bank interest - job start.');
				warquest_db_cron_update($data->cid);
				warquest_cron_clan_bank_interest();
				warquest_info('CRON JOB ['.$data->cid.'] clan bank bank interest - job end.');
				break;

			case 12:
				warquest_info('CRON JOB ['.$data->cid.'] clan bank clean transaction log - job start.');
				warquest_db_cron_update($data->cid);
				warquest_cron_clean_clan_bank_log();
				warquest_info('CRON JOB ['.$data->cid.'] clan bank clean transaction log - job end.');
				break;

			case 13:
				warquest_info('CRON JOB ['.$data->cid.'] update lottery - job start.');
				warquest_db_cron_update($data->cid);
				warquest_cron_update_lottery();
				warquest_info('CRON JOB ['.$data->cid.'] update lottery - job end.');
				break;

			default:
				warquest_error("CRON JOB [".$data->cid."] unknown job start.");
				warquest_db_cron_update($data->cid);
				warquest_error("CRON JOB [".$data->cid."] unknown job end.");
				break;
		}
	}
}
