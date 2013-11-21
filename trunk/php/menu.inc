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
** ---------
** MAIN MENU
** ---------
*/

function warquest_ui_mainmenu() {
	
	/* input */
	global $mid;
	global $config;
	global $player;
	global $skill;
	
	/* Count not accepted recruit request */
	$query  = 'select pid1 from player_player where approved=0 and pid2='.$player->pid; 
	$result = warquest_db_query($query);
	$recruit = warquest_db_num_rows($result);	
	
	$query2 = 'select ugid from unit_group where type=2 and planet='.$player->planet;
	$result2 = warquest_db_query($query2);
	$data2 = warquest_db_fetch_object($result2);

	$query3 = 'select bgid from building_group where planet='.$player->planet.' order by bgid limit 1';
	$result3 = warquest_db_query($query3);
	$data3 = warquest_db_fetch_object($result3);
			
	$page  = '<div class="menu">';
	
	$page .= warquest_ui_menu(MENU_HOME, PAGE_OVERVIEW, t('LINK_HOME'), $mid, 
					$player->news + $player->comment + $skill->skill_points + $skill->trade_points);
	
	if ($player->holiday_date <= date("Y-m-d H:i:s", time())) {
		
		$page .= warquest_ui_menu(MENU_MISSIONS, warquest_get_default_mission($player->planet), t('LINK_MISSIONS'), $mid);
	
		$page .= warquest_ui_menu(MENU_BATTLE, PAGE_ENEMIES, t('LINK_BATTLE'), $mid);

		$page .= warquest_ui_menu(MENU_UNITS, $data2->ugid, t('LINK_UNITS'), $mid);
			
		$page .= warquest_ui_menu(MENU_BUILDINGS, $data3->bgid, t('LINK_BUILDINGS'), $mid);

		$page .= warquest_ui_menu(MENU_MONEY, PAGE_BANK, t('LINK_MONEY'), $mid);
			
	}
		
	$page .= warquest_ui_menu(MENU_ALLIANCE, PAGE_PENDING, t('LINK_ALLIANCE'), $mid, $recruit);
		
	$page .= warquest_ui_menu(MENU_FORUMS, PAGE_FORUM, t('LINK_FORUM'), $mid);
	
	$page .= warquest_ui_menu(MENU_HELP, PAGE_INSTRUCTIONS, t('LINK_HELP'), $mid);

	if ($player->pid==$config["adminPid"]) {
		$page .= warquest_ui_menu(MENU_ADMIN, PAGE_PLAYER_LIST, t('LINK_ADMIN'), $mid);	
	}
	
	$page .= '</div>';	
	
	return $page;
}
	
/*
** ---------------
** HOME SUBMENU
** ---------------
*/

function warquest_menu_home() {

	/* input */
	global $mid;
	global $sid;
	global $skill;
	global $player;
				
	$page  = warquest_ui_menu($mid, PAGE_OVERVIEW, t('LINK_OVERVIEW'), $sid);
	$page .= warquest_ui_menu($mid, PAGE_PROFILE, t('LINK_PROFILE'), $sid);
	$page .= warquest_ui_menu($mid, PAGE_BATTLE_NEWS, t('LINK_NEWS'), $sid, $player->news);
	$page .= warquest_ui_menu($mid, PAGE_MESSAGES, t('LINK_COMMENTS'), $sid, $player->comment);
	$page .= warquest_ui_menu($mid, PAGE_SKILLS, t('LINK_SKILLS'), $sid, $skill->skill_points);
	$page .= warquest_ui_menu($mid, PAGE_TRADE, t('LINK_TRADE'), $sid, $skill->trade_points);
	$page .= warquest_ui_menu($mid, PAGE_RESTORE, t('LINK_RESTORE'), $sid);
	$page .= warquest_ui_menu($mid, PAGE_SETTINGS, t('LINK_SETTINGS'), $sid);
	
	$member=warquest_db_member($player->pid);
	if ($member->auto_login==0) {
		$link = warquest_link('mid='.MENU_LOGIN.'&sid='.PAGE_LOGIN.'&eid=4', t('LINK_LOGOUT'), "logout");
		$page .= $link.' ';
	}
	
	return $page;
}

/*
** -----------------
** MISSIONS SUBMENU
** -----------------
*/

function warquest_menu_mission() {

	/* input */
	global $mid;
	global $sid;
	global $player;
	global $config;
	global $player;
		
	/* workarround of existing players */
	if (($player->lid>0) && ($sid==0)) {
		$sid=1;
	}
			
	$query  = 'select mgid from mission_group where planet='.$player->planet;
	$query .= ' and mgid!=0 order by mgid';
	
	$result = warquest_db_query($query);	
	
	$page = "";
	
	if ($player->lid==0) {
	
		/* Training Missions */	
		$page .= warquest_ui_menu($mid, 0, t('MISSION_GROUP_0'), $sid);
	
	} else {
	
		while ($data=warquest_db_fetch_object($result)) {
	
			$page .= warquest_ui_menu($mid, $data->mgid, t('MISSION_GROUP_'.$data->mgid), $sid);

		}
	}
	
	return $page;
}

/*
** -----------------
** BATTLE SUBMENU
** -----------------
*/

function warquest_menu_battle() {

	/* input */
	global $mid;
	global $sid;
	 	
	$page  = warquest_ui_menu($mid, PAGE_ENEMIES, t('BATTLE_ENEMIES'), $sid);
	$page .= warquest_ui_menu($mid, PAGE_BOUNTY, t('BATTLE_BOUNTY'), $sid);
	$page .= warquest_ui_menu($mid, PAGE_CLAN_WAR, t('BATTLE_CLAN_WAR'), $sid);
		
	return $page;
}

/*
** -----------------
** UNITS SUBMENU
** -----------------
*/

function warquest_menu_unit() {

	/* input */
	global $mid;
	global $sid;
	global $player;
	
	$query  = 'select ugid, type from unit_group where planet='.$player->planet.' and type!=0 and type!=6 order by type';
	$result = warquest_db_query($query);	
	
	$page = '';
	while ($data=warquest_db_fetch_object($result)) {
			
		$page .= warquest_ui_menu($mid, $data->ugid, t('UNIT_GROUP_'.$data->ugid), $sid);

	}
	
	return $page;
}

/*
** --------------------
** BUILDINGS SUBMENU
** --------------------
*/

function warquest_menu_building() {

	/* input */
	global $mid;		
	global $sid;
	global $player;
				
	$query  = 'select bgid from building_group where planet='.$player->planet.' order by bgid';
	$result = warquest_db_query($query);	
	
	$page = '';
	
	while ($data=warquest_db_fetch_object($result)) {
	
		$page .= warquest_ui_menu($mid, $data->bgid, t('BUILDING_GROUP_'.$data->bgid), $sid);

	}
	
	return $page;
}

/*
** --------------------
** MONEY SUBMENU
** --------------------
*/

function warquest_menu_money() {

	/* input */
	global $mid;
	global $sid;
	global $cid;
		
	$page  = warquest_ui_menu($mid, PAGE_BANK, t('LINK_BANK'), $sid);
	$page .= warquest_ui_menu($mid, PAGE_STOCK_EXCHANGE, t('LINK_STOCKEXCHANGE'), $sid);
	$page .= warquest_ui_menu($mid, PAGE_CASINO, t('LINK_CASINO'), $sid);
	
	$page .= ' | ';
	
	switch ( $sid ) { 
	
		case PAGE_BANK: 
			$tmp = array(1, 2, 3);
			foreach ($tmp as $id) {
	
				$menu = warquest_link('mid='.$mid.'&sid='.$sid.'&cid='.$id, t('BANK_GROUP_'.$id), t('BANK_GROUP_'.$id));
				if ($id==$cid) {
					$menu = '<b>'.$menu.'</b>';
				} 
				$page .= $menu.' ';
			}
			break;
		
		case PAGE_STOCK_EXCHANGE: 
			$tmp = array(1, 2, 3, 4);
			foreach ($tmp as $id) {
	
				$menu = warquest_link('mid='.$mid.'&sid='.$sid.'&cid='.$id, t('STOCK_GROUP_'.$id), t('STOCK_GROUP_'.$id));
				if ($id==$cid) {
					$menu = '<b>'.$menu.'</b>';
				} 
				$page .= $menu.' ';
			}
			break;
			
		case PAGE_CASINO:
			$menu = warquest_link('mid='.$mid.'&sid='.$sid.'&cid=1', t('CASINO_1'), 'casino1');
			if ($cid==1) {
				$menu = '<b>'.$menu.'</b>';
			} 
			$page .= $menu.' ';
	
			$menu = warquest_link('mid='.$mid.'&sid='.$sid.'&cid=2', t('CASINO_2'), 'casino2');
			if ($cid==2) {
				$menu = '<b>'.$menu.'</b>';
			} 
			$page .= $menu.' ';
			
			$menu = warquest_link('mid='.$mid.'&sid='.$sid.'&cid=3', t('CASINO_3'), 'casino3');
			if ($cid==3) {
				$menu = '<b>'.$menu.'</b>';
			} 
			$page .= $menu.' ';
			break;
	}

	return $page;
}

/*
** --------------------
** ALLIANCE SUBMENU
** --------------------
*/

function warquest_menu_alliance() {

	/* input */
	global $mid;
	global $sid;
	global $player;
	
	/* Count not accepted recruit request */
	$query  = 'select pid1 from player_player where approved=0 and pid2='.$player->pid; 
	$result = warquest_db_query($query);	
	$recruit = warquest_db_num_rows($result);
	
	$page  = warquest_ui_menu($mid, PAGE_PENDING, t('LINK_PENDING'), $sid, $recruit);
	$page .= warquest_ui_menu($mid, PAGE_INVITE, t('LINK_INVITE'), $sid);
	$page .= warquest_ui_menu($mid, PAGE_ACCEPTED, t('LINK_APPROVED'), $sid);
	$page .= warquest_ui_menu($mid, PAGE_BEST_PLAYER, t('LINK_BEST_PLAYER'), $sid);
	$page .= warquest_ui_menu($mid, PAGE_BEST_COUNTRY, t('LINK_BEST_COUNTRY'), $sid);
	$page .= warquest_ui_menu($mid, PAGE_CLAN, t('LINK_CLAN'), $sid);
	
	return $page;
}

/*
** --------------------
** FORUMS SUBMENU
** --------------------
*/

function warquest_menu_forum() {

	/* input */
	global $mid;
	global $sid;

	$page  = warquest_ui_menu($mid, PAGE_FORUM, t('LINK_FORUM'), $sid);
	$page .= warquest_ui_menu($mid, PAGE_POLL, t('LINK_POLLS'), $sid);
	$page .= warquest_ui_menu($mid, PAGE_CHATROOM, t('LINK_CHATROOM'), $sid);
	
	return $page;
}

/*
** --------------------
** HELP SUBMENU
** --------------------
*/

function warquest_menu_help() {

	/* input */
	global $mid;
	global $sid;

	$page  = warquest_ui_menu($mid, PAGE_INSTRUCTIONS, t('LINK_GENERAL'), $sid);
	$page .= warquest_ui_menu($mid, PAGE_RELEASENOTES, t('LINK_NOTES'), $sid);
	$page .= warquest_ui_menu($mid, PAGE_RANKS, t('LINK_RANKS'), $sid);		
	$page .= warquest_ui_menu($mid, PAGE_AWARDS, t('LINK_AWARDS'), $sid);	
	$page .= warquest_ui_menu($mid, PAGE_LEVELS, t('LINK_LEVELS'), $sid);	
	$page .= warquest_ui_menu($mid, PAGE_STATS, t('LINK_STATS'), $sid);	
	$page .= warquest_ui_menu($mid, PAGE_DONATE, t('LINK_DONATE'), $sid);
	$page .= warquest_ui_menu($mid, PAGE_ABOUT, t('LINK_ABOUT'), $sid);
	
	return $page;
}

/*
** --------------------
** ADMIN SUBMENU
** --------------------
*/

function warquest_menu_admin() {

	/* input */
	global $mid;
	global $sid;
		
	$page  = warquest_ui_menu($mid, PAGE_PLAYER_LIST, 'Members', $sid);
	$page .= warquest_ui_menu($mid, PAGE_ADMIN_NEWS, 'News', $sid);
	$page .= warquest_ui_menu($mid, PAGE_ADMIN_MESSAGES, 'Messages', $sid);
	$page .= warquest_ui_menu($mid, PAGE_LEVEL, 'Levels', $sid);
	$page .= warquest_ui_menu($mid, PAGE_BROWSER, 'Browsers', $sid);
	$page .= warquest_ui_menu($mid, PAGE_INFO, 'Info', $sid);
	$page .= warquest_ui_menu($mid, PAGE_ACTIONS, 'Actions', $sid);

	return $page;
}

/*
** ---------
** SUBMENU
** ---------
*/

function warquest_ui_submenu() {

	/* input */
	global $mid;
	global $sid;
		
	$page = '<div class="menu">';
	
	switch ($mid) {
				
		case MENU_HOME:
				$page .= warquest_menu_home();
				break;

		case MENU_MISSIONS:
				$page .= warquest_menu_mission();
				break;

		case MENU_BATTLE:
				$page .= warquest_menu_battle();
				break;

		case MENU_UNITS:
				$page .= warquest_menu_unit();
				break;

		case MENU_BUILDINGS:
				$page .= warquest_menu_building();
				break;

		case MENU_MONEY:
				$page .= warquest_menu_money();
				break;

		case MENU_ALLIANCE:
				$page .= warquest_menu_alliance();
				break;

		case MENU_FORUMS:			
				$page .= warquest_menu_forum();
				break;
			
		case MENU_HELP:
				$page .= warquest_menu_help();
				break;
				
		case MENU_ADMIN:
				$page .= warquest_menu_admin();
				break;	
	}
	
	$page .= '</div>';

	return $page;
}

/*
** ---------
** THE END
** ---------
*/

?>