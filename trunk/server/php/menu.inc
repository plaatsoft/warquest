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
** ---------------------------
** MAIN MENU
** ---------------------------
*/

function warquest_mainmenu() {
	
	/* input */
	global $mid;
	global $config;
	global $player;
	global $skill;
	
	/* Count not accepted alliance requests */
	$query  = 'select pid1 from player_player where approved=0 and pid2='.$player->pid; 
	$result = warquest_db_query($query);
	$recruit = warquest_db_num_rows($result);	
	
	/* get default unit */
	$query2 = 'select ugid from unit_group where type=2 and planet='.$player->planet;
	$result2 = warquest_db_query($query2);
	$data2 = warquest_db_fetch_object($result2);

	/* get default building */
	$query3 = 'select bgid from building_group where planet='.$player->planet.' order by bgid limit 1';
	$result3 = warquest_db_query($query3);
	$data3 = warquest_db_fetch_object($result3);
	
	$menu = '<div class="menu">';	
	$menu .= '<ul>';
	
	$menu .= warquest_ui_menu(MENU_HOME, PAGE_OVERVIEW, 0, t('LINK_HOME'), $mid, 
					$player->news + $player->comment + $skill->skill_points);
	
	if ($player->holiday_date <= date("Y-m-d H:i:s", time())) {
		
		$menu .= warquest_ui_menu(MENU_MISSIONS, PAGE_MISSION_PLAYER, warquest_get_default_mission($player->planet), t('LINK_MISSIONS'), $mid);	
		$menu .= warquest_ui_menu(MENU_BATTLE, PAGE_ENEMIES, 0, t('LINK_BATTLE'), $mid);
		$menu .= warquest_ui_menu(MENU_UNITS, $data2->ugid, 0, t('LINK_UNITS'), $mid);			
		$menu .= warquest_ui_menu(MENU_BUILDINGS, $data3->bgid, 0, t('LINK_BUILDINGS'), $mid);
		$menu .= warquest_ui_menu(MENU_MONEY, PAGE_BANK, 1, t('LINK_MONEY'), $mid);
	}
		
	$menu .= warquest_ui_menu(MENU_PLAYERS, PAGE_ALLIANCE, PAGE_INVITE, t('LINK_PLAYERS'), $mid, $recruit);		
	$menu .= warquest_ui_menu(MENU_FORUMS, PAGE_FORUM, 0, t('LINK_FORUM'), $mid);	
	$menu .= warquest_ui_menu(MENU_HELP, PAGE_INSTRUCTIONS, 0, t('LINK_HELP'), $mid);

	if ($player->pid==$config["adminPid"]) {
		$menu .= warquest_ui_menu(MENU_ADMIN, PAGE_PLAYER_LIST, 0, t('LINK_ADMIN'), $mid);	
	}
	
	$menu .= '</ul>';	
	$menu .= '</div>';	
	
	$menu .= '<div class="clear"></div>';
	$menu .= '<div class="spacer"></div>';
			
	return $menu;
}

/*
** ---------------
** LOGIN MENU
** ---------------
*/

function warquest_login_menu() {

	/* input */
	global $mid;
	global $sid;
	global $version;
	
	$menu  = '<table>';
	$menu .= '<tr>';
		
	$menu .= '<td width="20%">';
	$menu .= '</td>';
	
	$menu .= '<td width="60%" aling="center">';
	
	$menu .= '<div class="menu">';
	$menu .= '<ul>';

	$menu .= warquest_ui_menu($mid, PAGE_LOGIN, 0, t('LINK_LOGIN'), $sid);
	$menu .= warquest_ui_menu($mid, PAGE_REGISTER, 0, t('LINK_REGISTER'), $sid);
	$menu .= warquest_ui_menu($mid, PAGE_RECOVER, 0, t('LINK_RECOVER'), $sid);
	$menu .= warquest_ui_menu($mid, PAGE_FACEBOOK, 0,  t('LINK_FACEBOOK'), $sid);
	
	if (strlen($version)==0) {
		$menu .= '<li>';
		$menu .= '<a target="_blank" href="rss.php">'.t('LINK_RSS').'</a>'; 
		$menu .= '</li>';
	}

	$menu .= '</ul>';
	$menu .= '</div>';
	
	$menu .= '</td>';
	
	$menu .= '<td width="20%">';
	$menu .= '</td>';
	
	$menu .= '</table>';
	
	$menu .= '<div class="clear"></div>';
	 
	return $menu;
}
	
/*
** ---------------
** HOME MENU
** ---------------
*/

function warquest_menu_home() {

	/* input */
	global $mid;
	global $sid;
	global $skill;
	global $player;
				
	$menu = '<div class="menu">';
	$menu .= '<ul>';
				
	$menu .= warquest_ui_menu($mid, PAGE_OVERVIEW, 0, t('LINK_OVERVIEW'), $sid);
	$menu .= warquest_ui_menu($mid, PAGE_PROFILE, 0, t('LINK_PROFILE'), $sid);
	$menu .= warquest_ui_menu($mid, PAGE_BATTLE_NEWS, 0, t('LINK_NEWS'), $sid, $player->news);
	$menu .= warquest_ui_menu($mid, PAGE_MESSAGES, 0, t('LINK_COMMENTS'), $sid, $player->comment);
	$menu .= warquest_ui_menu($mid, PAGE_SKILLS, 0, t('LINK_SKILLS'), $sid, $skill->skill_points);
	$menu .= warquest_ui_menu($mid, PAGE_RESTORE, 0, t('LINK_RESTORE'), $sid);
	$menu .= warquest_ui_menu($mid, PAGE_TRADE, 0, t('LINK_TRADE'), $sid );
	$menu .= warquest_ui_menu($mid, PAGE_SETTINGS, 0, t('LINK_SETTINGS'), $sid);
	
	$member=warquest_db_member($player->pid);
	
	if ($member->auto_login==0) {
		$menu .= '<li>';
		$menu .= warquest_link('mid='.MENU_LOGIN.'&sid='.PAGE_LOGIN.'&eid='.EVENT_LOGOUT, t('LINK_LOGOUT'), "logout");
		$menu .= '</li>';
	}
	
	$menu .= '</ul>';
	$menu .= '</div>';
	
	$menu .= '<div class="clear"></div>';
	
	return $menu;
}

/*
** -----------------
** MISSIONS MENU
** -----------------
*/

function warquest_menu_mission() {

	/* input */
	global $mid;
	global $sid;
	global $ssid;
	
	global $player;
	global $config;

	$menu = '<div class="menu">';
	$menu .= '<ul>';
	
	$menu .= warquest_ui_menu($mid, PAGE_MISSION_PLAYER, $ssid, t('LINK_PLAYER'), $sid);
	$menu .= warquest_ui_menu($mid, PAGE_MISSION_CLAN, $ssid, t('LINK_CLAN'), $sid);
	
	$menu .= '</ul>';
	$menu .= '</div>';
	
	$menu .= '<div class="clear"></div>';
	
	return $menu;
}
	
function warquest_submenu_mission() {

	/* input */
	global $mid;
	global $sid;
	global $ssid;
	
	global $player;
	global $config;

	$query  = 'select mgid from mission_group where planet='.$player->planet.' and mgid!=0 order by mgid';
	$result = warquest_db_query($query);	
	
	$menu = '<div class="menu">';
	$menu .= '<ul>';
	
	if ($player->lid==0) {

				
		$menu .= warquest_ui_submenu($mid, 0, 0, t('MISSION_GROUP_0'), PAGE_MISSION_PLAYER, $ssid);
	
	} else {
		
		while ($data=warquest_db_fetch_object($result)) {
	
			$menu .= warquest_ui_submenu($mid, $sid, $data->mgid, t('MISSION_GROUP_'.$data->mgid), $ssid);
		}
	}
		
	$menu .= '</ul>';
	$menu .= '</div>';
	
	$menu .= '<div class="clear"></div>';
	
	return $menu;
}

/*
** -----------------
** BATTLE MENU
** -----------------
*/

function warquest_menu_battle() {

	/* input */
	global $mid;
	global $sid;
	 
	$menu = '<div class="menu">';
	$menu .= '<ul>';
	 
	$menu .= warquest_ui_menu($mid, PAGE_ENEMIES, 0, t('BATTLE_ENEMIES'), $sid);
	$menu .= warquest_ui_menu($mid, PAGE_BOUNTY, 0, t('BATTLE_BOUNTY'), $sid);
	$menu .= warquest_ui_menu($mid, PAGE_CLAN_WAR, 0, t('BATTLE_CLAN_WAR'), $sid);
	
	$menu .= '</ul>';
	$menu .= '</div>';
	
	$menu .= '<div class="clear"></div>';
	
	return $menu;
}

/*
** -----------------
** UNITS MENU
** -----------------
*/

function warquest_menu_unit() {

	/* input */
	global $mid;
	global $sid;
	global $player;
	
	$menu = '<div class="menu">';
	$menu .= '<ul>';
	
	$query  = 'select ugid, type from unit_group where planet='.$player->planet.' and type!=0 and type!=6 order by type';
	$result = warquest_db_query($query);	
	
	while ($data=warquest_db_fetch_object($result)) {
			
		$menu .= warquest_ui_menu($mid, $data->ugid, 0, t('UNIT_GROUP_'.$data->ugid), $sid);	
	}

	$menu .= '</ul>';
	$menu .= '</div>';

	$menu .= '<div class="clear"></div>';

	return $menu;
}

/*
** --------------------
** BUILDINGS MENU
** --------------------
*/

function warquest_menu_building() {

	/* input */
	global $mid;		
	global $sid;
	global $player;
	global $ssid;
	
	/* Get unit types */
	$query2 = 'select ugid from unit_group where type=2 and planet='.$player->planet;
	$result2 = warquest_db_query($query2);
	$data2 = warquest_db_fetch_object($result2);
			
	$query  = 'select bgid, type from building_group where ';
	$query .= 'planet='.$player->planet.' ';	
	$query .= 'order by bgid';
		
	$result = warquest_db_query($query);	
	
	$menu = '<div class="menu">';
	$menu .= '<ul>';
		
	while ($data = warquest_db_fetch_object($result)) {
	
		if ($data->type==2) {
			$ssid = $data2->ugid;
		}
		$menu .= warquest_ui_menu($mid, $data->bgid, $ssid, t('BUILDING_GROUP_'.$data->bgid), $sid);
	}
	
	$menu .= '</ul>';
	$menu .= '</div>';
	
	$menu .= '<div class="clear"></div>';
	
	return $menu;
}

function warquest_submenu_building() {

	/* input */
	global $mid;		
	global $sid;
	global $ssid;
	global $player;

	$menu = '<div class="menu">';
	$menu .= '<ul>';

	/* Get building types */
	$query  = 'select ugid from unit_group where planet='.$player->planet.' and type!=0 and type!=6 order by type';
	$result = warquest_db_query($query);	
	
	while ($data = warquest_db_fetch_object($result)) {
			
		$menu .= warquest_ui_submenu($mid, $sid, $data->ugid, t('UNIT_GROUP_'.$data->ugid), $ssid);
	}
	
	$menu .= '</ul>';
	$menu .= '</div>';
	
	$menu .= '<div class="clear"></div>';
	
	return $menu;
}

/*
** --------------------
** MONEY MENU
** --------------------
*/

function warquest_menu_money() {

	/* input */
	global $mid;
	global $sid;
	global $ssid;
	global $config;
		
	$menu  = '<div class="menu">';
	$menu .= '<ul>';
		
	$menu .= warquest_ui_menu($mid, PAGE_BANK, 1, t('LINK_BANK'), $sid);
	$menu .= warquest_ui_menu($mid, PAGE_STOCK_EXCHANGE, 1, t('LINK_STOCKEXCHANGE'), $sid);
	$menu .= warquest_ui_menu($mid, PAGE_CASINO, 1, t('LINK_CASINO'), $sid);
	
	$menu .= '</ul>';
	$menu .= '</div>';
	
	switch ($sid) {
		
		case PAGE_BANK: 	
					$menu .= warquest_submenu_bank();
					break;
					
		case PAGE_STOCK_EXCHANGE:  
					$menu .= warquest_submenu_stock_exchange();
					break;
					
		case PAGE_CASINO:
					$menu .= warquest_submenu_casino();
					break;
	}
	
	$menu .= '<div class="clear"></div>';
	return $menu;
}

function warquest_submenu_bank() {
	
	/* input */
	global $mid;
	global $sid;
	global $ssid;
	global $config;
	
	/* Get bank group types */
	$query = 'select bgid from bank_group order by bgid';
	$result = warquest_db_query($query);	
	
	$menu  = '<div class="menu right2">';
	$menu .= '<ul>';
	
	while ($data = warquest_db_fetch_object($result)) {
	
		$menu .= warquest_ui_submenu($mid, $sid, $data->bgid, t('BANK_GROUP_'.$data->bgid), $ssid);
	}
	
	$menu .= '</ul>';
	$menu .= '</div>';
	
	return $menu;
}

function warquest_submenu_stock_exchange() {
	
	/* input */
	global $mid;
	global $sid;
	global $ssid;
	global $config;
	
	$menu  = '<div class="menu right2">';
	$menu .= '<ul>';
	
	/* Get stock group types */
	$query = 'select sgid from stock_group order by sgid';
	$result = warquest_db_query($query);			
			
	while ($data = warquest_db_fetch_object($result)) {
		
		$menu .= warquest_ui_submenu($mid, $sid, $data->sgid, t('STOCK_GROUP_'.$data->sgid), $ssid);
	}
	
	$menu .= '</ul>';
	$menu .= '</div>';
	
	return $menu;
}

function warquest_submenu_casino() {
	
	/* input */
	global $mid;
	global $sid;
	global $ssid;
	global $config;
	
	$menu  = '<div class="menu right2">';
	$menu .= '<ul>';
	
	for($cgid=1; $cgid<=$config["max_casio_groups"]; $cgid++) {			
			
		$menu .= warquest_ui_submenu($mid, $sid, $cgid, t('CASINO_'.$cgid), $ssid);				
	}

	$menu .= '</ul>';
	$menu .= '</div>';

	return $menu;
}

/*
** --------------------
** PLAYERS MENU
** --------------------
*/

function warquest_menu_players() {

	/* input */
	global $mid;
	global $sid;
	
	global $player;
	global $config;
	
	/* Count not accepted recruit request */
	$query  = 'select pid1 from player_player where approved=0 and pid2='.$player->pid; 
	$result = warquest_db_query($query);	
	$recruit = warquest_db_num_rows($result);
	
	$menu = '<div class="menu">';
	$menu .= '<ul>';
	
	$menu .= warquest_ui_menu($mid, PAGE_ALLIANCE, PAGE_INVITE, t('LINK_ALLIANCE'), $sid, $recruit);
	$menu .= warquest_ui_menu($mid, PAGE_CLAN, 0, t('LINK_CLAN'), $sid);	
	$menu .= warquest_ui_menu($mid, PAGE_LEADERBOARD, PAGE_BEST_PLAYER, t('LINK_LEADERBOARD'), $sid);
	$menu .= warquest_ui_menu($mid, PAGE_PROMOTION, 0, t('LINK_PROMOTION'), $sid);
	
	$menu .= '</ul>';
	$menu .= '</div>';
	
	switch ($sid) {

		case PAGE_ALLIANCE: 	
					$menu .= warquest_submenu_alliance();
					break;
										
		case PAGE_LEADERBOARD:
					$menu .= warquest_submenu_leaderboards();
					break;
	}
	
	$menu .= '<div class="clear"></div>';
	
	return $menu;
}

function warquest_submenu_alliance() {

	/* input */
	global $mid;
	global $sid;
	global $ssid;
	global $player;
	global $config;
	
	/* Count not accepted recruit request */
	$query  = 'select pid1 from player_player where approved=0 and pid2='.$player->pid; 
	$result = warquest_db_query($query);	
	$recruit = warquest_db_num_rows($result);
	
	$menu = '<div class="menu right2">';
	$menu .= '<ul>';
	
	$menu .= warquest_ui_submenu($mid, $sid, PAGE_INVITE, t('LINK_INVITE'), $ssid);
	$menu .= warquest_ui_submenu($mid, $sid, PAGE_PENDING, t('LINK_PENDING'), $ssid, $recruit);	
	$menu .= warquest_ui_submenu($mid, $sid, PAGE_ACCEPTED, t('LINK_APPROVED'), $ssid);
	
	$menu .= '</ul>';
	$menu .= '</div>';
	
	return $menu;
}

function warquest_submenu_leaderboards() {

	/* input */
	global $mid;
	global $sid;
	global $ssid;
	
	$menu = '<div class="menu right2">';
	$menu .= '<ul>';
	
	$menu .= warquest_ui_submenu($mid, $sid, PAGE_BEST_PLAYER, t('LINK_BEST_PLAYER'), $ssid);
	$menu .= warquest_ui_submenu($mid, $sid, PAGE_BEST_COUNTRY, t('LINK_BEST_COUNTRY'), $ssid);
	$menu .= warquest_ui_submenu($mid, $sid, PAGE_BEST_CLAN, t('LINK_BEST_CLAN'), $ssid);
	
	$menu .= '</ul>';
	$menu .= '</div>';
	
	return $menu;
}

/*
** --------------------
** FORUMS MENU
** --------------------
*/

function warquest_menu_forum() {

	/* input */
	global $mid;
	global $sid;

	$menu = '<div class="menu">';
	$menu .= '<ul>';

	$menu .= warquest_ui_menu($mid, PAGE_FORUM, 0, t('LINK_FORUM'), $sid);
	$menu .= warquest_ui_menu($mid, PAGE_POLL, 0, t('LINK_POLLS'), $sid);
	$menu .= warquest_ui_menu($mid, PAGE_CHATROOM, 0, t('LINK_CHATROOM'), $sid);
	
	$menu .= '</ul>';
	$menu .= '</div>';

	$menu .= '<div class="clear"></div>';

	return $menu;
}

/*
** --------------------
** HELP MENU
** --------------------
*/

function warquest_menu_help() {

	/* input */
	global $mid;
	global $sid;

	$menu = '<div class="menu">';
	$menu .= '<ul>';

	$menu .= warquest_ui_menu($mid, PAGE_INSTRUCTIONS, 0, t('LINK_GENERAL'), $sid);
	$menu .= warquest_ui_menu($mid, PAGE_RELEASENOTES, 0, t('LINK_NOTES'), $sid);
	$menu .= warquest_ui_menu($mid, PAGE_RANKS, 0, t('LINK_RANKS'), $sid);		
	$menu .= warquest_ui_menu($mid, PAGE_AWARDS, 0, t('LINK_AWARDS'), $sid);	
	$menu .= warquest_ui_menu($mid, PAGE_LEVELS, 0, t('LINK_LEVELS'), $sid);	
	$menu .= warquest_ui_menu($mid, PAGE_STATS, 0, t('LINK_STATS'), $sid);	
	$menu .= warquest_ui_menu($mid, PAGE_DONATE, 0, t('LINK_DONATE'), $sid);
	$menu .= warquest_ui_menu($mid, PAGE_ABOUT, 0, t('LINK_ABOUT'), $sid);
	
	$menu .= '</ul>';
	$menu .= '</div>';
	
	$menu .= '<div class="clear"></div>';
	
	return $menu;
}

/*
** --------------------
** ADMIN MENU
** --------------------
*/

function warquest_menu_admin() {

	/* input */
	global $mid;
	global $sid;
		
	$menu = '<div class="menu">';
	$menu .= '<ul>';
		
	$menu .= warquest_ui_menu($mid, PAGE_PLAYER_LIST, 0, 'Members', $sid);
	$menu .= warquest_ui_menu($mid, PAGE_ADMIN_NEWS, 0, 'News', $sid);
	$menu .= warquest_ui_menu($mid, PAGE_ADMIN_MESSAGES, 0, 'Messages', $sid);
	$menu .= warquest_ui_menu($mid, PAGE_LEVEL, 0, 'Levels', $sid);
	$menu .= warquest_ui_menu($mid, PAGE_BROWSER, 0, 'Browsers', $sid);
	$menu .= warquest_ui_menu($mid, PAGE_INFO, 0, 'Info', $sid);
	$menu .= warquest_ui_menu($mid, PAGE_MAPS, 0, 'Maps', $sid);
	$menu .= warquest_ui_menu($mid, PAGE_ACTIONS, 0, 'Actions', $sid);

	$menu .= '</ul>';
	$menu .= '</div>';
	
	$menu .= '<div class="clear"></div>';

	return $menu;
}

/*
** -------------
** STATE MACHINE
** -------------
*/

function warquest_submenu() {

	/* input */
	global $mid;
		
	switch ($mid) {
				
		case MENU_HOME:
				$menu = warquest_menu_home();
				break;

		case MENU_MISSIONS:
				$menu = warquest_menu_mission();
				break;

		case MENU_BATTLE:
				$menu = warquest_menu_battle();
				break;

		case MENU_UNITS:
				$menu = warquest_menu_unit();
				break;

		case MENU_BUILDINGS:
				$menu = warquest_menu_building();
				break;

		case MENU_MONEY:
				$menu = warquest_menu_money();
				break;

		case MENU_PLAYERS:
				$menu = warquest_menu_players();
				break;

		case MENU_FORUMS:			
				$menu = warquest_menu_forum();
				break;
			
		case MENU_HELP:
				$menu = warquest_menu_help();
				break;
				
		case MENU_ADMIN:
				$menu = warquest_menu_admin();
				break;	
	}
	
	return $menu;
}

/*
** ---------
** THE END
** ---------
*/

?>