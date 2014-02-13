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

$lang = array();

$time_start = microtime(true);

/* Include php classes */
include 'config.inc';
include 'constants.inc';
include 'database.inc';
include 'general.inc';
include "email.inc";

include 'menu.inc';
include 'title.inc';
include 'cron.inc';

/*
** ---------------------------------------------------------------- 
** Global variables
** ---------------------------------------------------------------- 
*/

warquest_debug("==============================================");

$mid = MENU_LOGIN;
$sid = PAGE_LOGIN;
$eid = EVENT_NONE;

$id = 1;
$pid = 0;
$uid = 0;
$oid = 0;
$tid = 0;
$fid = 0;
$sort = 0;
$offset = 0;

$page = '';
$version = '';

$output = new stdClass();
$output->format = "html";	/* Format (html, xml or pdf) */
$output->result = false; 	/* Action result (true / false) */
$output->title = "";			/* Title content */
$output->popup = "";			/* Popup content */

 
/*
** ---------------------------------------------------------------- 
** Post variables
** ---------------------------------------------------------------- 
*/

/* Get browser type */
$browser = $_SERVER['HTTP_USER_AGENT'];

$session = warquest_post('session', '');
$token = warquest_post('token', '');
$amount = warquest_post('amount', 1);
$action = warquest_get("action", "");

/* Webservice */
$mid = warquest_post('mid', 0);

if (strlen($token)>0) {
	
	/* Decode token */
	$token=gzinflate(base64_decode($token));
	$tokens = @preg_split("/&/", $token);
	
	foreach ($tokens as $item) {
		$items = preg_split ("/=/", $item);
		if (is_numeric($items[1])) {
			$$items[0] = $items[1];	
		}
	}
}
	
/*
** ---------------------------------------------------------------- 
** Database
** ---------------------------------------------------------------- 
*/

/* Connect to database */
if (@warquest_db_connect($config["dbhost"], $config["dbuser"], $config["dbpass"], $config["dbname"])!=1) {

	/* Database down detected, swith to maintenance mode. */
	include "login.inc";	
	include "english.inc";
	
	/* html banner */
	echo warquest_ui_header();

	/* Set maintenance mode. */
	$sid = PAGE_MAINTENANCE;
	
	/* Show maintenance text */
	warquest_login();
			
	/* show page content */
	echo $page;

	$time_end = microtime(true);
	$time = $time_end - $time_start;

	/* html footer */
	echo warquest_ui_footer( round(($time*1000)), warquest_db_count());
	
	/* End */
	exit;
}

/*
** ---------------------------------------------------------------- 
** Web Service module
** ---------------------------------------------------------------- 
*/

if ($mid==MENU_SERVICE) {

	include 'service.inc';
	
	/* Proces web service call */
	warquest_service();
	
	/* End */
	exit;
}

/*
** ---------------------------------------------------------------- 
** Login check
** ---------------------------------------------------------------- 
*/

/* Check if player is login else go to login page. */
if ($mid!=MENU_LOGIN) {
	
	/* If not login page check login status. */
	$pid = warquest_db_session_valid($session);
	
	if ( $pid==0 ) {
				
		/* No login redirect to login page. */
		$mid = MENU_LOGIN;
		$sid = PAGE_LOGIN;
		$eid = EVENT_NONE;
	} 
}

if ($mid==MENU_LOGIN) {
	
	include "english.inc";
	include "login.inc";	
	include "browser.inc";
	
	warquest_login();
}

/*
** ---------------------------------------------------------------- 
** Load data from database
** ---------------------------------------------------------------- 
*/

if ($pid!=0) {

	/* Load player data from database */
	$player = warquest_db_player($pid);
	$skill = warquest_db_skill($player->pid);
	$level = warquest_db_level($player->lid);

	/* Update player timers (before) */
	warquest_update_timers($player);
	
	/* Load language file (Player setting). */
	include "english.inc";
	
	if ($player->language == 'nl') {
		include "nederlands.inc";
	} else if ($player->language == 'de') {
		include "deutsch.inc";
	} else if ($player->language == 'it') {
		include "italian.inc";
	} else if ($player->language == 'ro') {
		include "romanian.inc";
	} else if ($player->language == 'es') {
		include "spanish.inc";
	} 
}

if ($oid!=0) {

	/* Load other player data from database */
	$other=warquest_db_player($oid);
	
	/* Update other player timers (before) */
	warquest_update_timers($other);	
}

/*
** ---------------------------------------------------------------- 
** State machine
** ---------------------------------------------------------------- 
*/

/* Page Event */
switch ($mid) {

	case MENU_HOME:
			include "home.inc";
			include "player.inc";			
			include "setting.inc";
			include "restore.inc";
			include "skill.inc";
			include 'pdf/fpdf.php';
			include "report.inc";
			include "poll.inc";
			include "trade.inc";
			warquest_home();
			break;

	case MENU_MISSIONS:
			include "mission.inc";
			warquest_mission();
			break;

	case MENU_BATTLE:
			include "battle.inc";
			include "player.inc";
			include 'pdf/fpdf.php';
			include "report.inc";
			warquest_battle();
			break;

	case MENU_UNITS:
			include "library.inc";
			include "unit.inc";
			warquest_unit();
			break;

	case MENU_BUILDINGS:
			include "building.inc";
			warquest_building();
			break;

	case MENU_MONEY:
			include "money.inc";
			include "bank.inc";
			include "stock.inc";
			include "casino.inc";			
			include "player.inc";
			warquest_money();
			break;

	case MENU_ALLIANCE:
			include "alliance.inc";
			include "player.inc";
			include 'pdf/fpdf.php';
			include "report.inc";
			include "leaderboard.inc";
			warquest_alliance();
			break;

	case MENU_FORUMS:
			include "forum.inc";			
			include "poll.inc";
			include "chat.inc";
			include "player.inc";
			include 'pdf/fpdf.php';
			include "report.inc";			
			warquest_forum();
			break;
			
	case MENU_HELP:
			include "notes.inc";
			include "help.inc";
			warquest_help();
			break;
				
	case MENU_ADMIN:
			include "admin.inc";
			include "login.inc";
			include "player.inc";
			include 'pdf/fpdf.php';
			include "report.inc";
			include 'tmhOAuth.php';
			warquest_admin();
			break;
}

/*
** ---------------------------------------------------------------- 
** Save data to database
** ---------------------------------------------------------------- 
*/

if ($pid!=0) {

	/* Update player timers (after) */
	warquest_update_timers($player);

	/* Update statistics counters */
	$player->request_date=date("Y-m-d H:i:s", time());
	$player->request+=1;
		
	/* Save player data */
	warquest_db_player_update($player);
}

if ($oid!=0) {

	/* Update other player timers (after) */
	warquest_update_timers($other);
	
	/* Save other player data; */
	warquest_db_player_update($other);
}

/*
** ---------------------------------------------------------------- 
** Process cron jobs
** ----------------------------------------------------------------
*/

warquest_cron();

/*
** ---------------------------------------------------------------- 
** Create html output
** ----------------------------------------------------------------
*/

if ( $output->format=="html" ) {
		
	/* html banner */
	echo warquest_ui_header();
		
	warquest_debug("Page ".$output->title);
	
	if ($pid!=0) {
	
		/* Show banner */
		echo warquest_ui_banner();

		/* Show main menu */
		echo warquest_ui_mainmenu();
		
		/* Show popup message */	
		if ( isset($output->popup) ) {
			echo $output->popup;
		}
				
		/* Show Page title */
		echo warquest_ui_title();
		
		/* Show submenu */
		echo warquest_ui_submenu();
	}

	/* show page content */
	echo $page;

	$time_end = microtime(true);
	$time = $time_end - $time_start;

	/* html footer */
	echo warquest_ui_footer( round(($time*1000)), warquest_db_count() );
	
	warquest_debug("Page render time = ".round(($time*1000)).'ms');
	warquest_debug("Page queries = ".warquest_db_count());
}

/*
** ---------------------------------------------------------------- 
** THE END
** ----------------------------------------------------------------
*/

?>