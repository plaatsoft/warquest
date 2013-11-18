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
** ---------------------
** POST
** ---------------------
*/

$mycountry = warquest_post('mycountry', '');
$mylanguage = warquest_post('mylanguage', 'EN');
$mybackground = warquest_post('mybackground', 0);
$mytwitter = warquest_post('mytwitter', '');
$myemail = warquest_post('myemail', '');

/*
** ---------------------
** ACTIONS
** ---------------------
*/

/**
 * User email confirm
 */
function warquest_user_email_confirm_do() {

	/* input */
	global $player;
	global $myemail;
	
	/* output */
	global $popup;
		
	$member = warquest_db_member($player->pid);
	
	$query = 'select pid from member where email="'.$myemail.'"';
	$result = warquest_db_query($query);
	$count = warquest_db_num_rows($result);
	
	if (validate_email($myemail)) {
	
		$message = t('PLAYER_EMAIL_INVALID');
		$popup .= warquest_box_icon("warning", $message);
		
	} else if (($myemail!=$member->email) && ($count>0)) {
		
		$message = t('PLAYER_EMAIL_EXIST');
		$popup .= warquest_box_icon("warning", $message);
			
	} else {
				
		/* Store settings */
		$member->email = $myemail;
		$member->email_valid = 0;
		
		warquest_db_member_update($member);	
	
		warquest_confirm_email($myemail, $player->pid);
		
		$popup .= warquest_box_icon('info', t('USER_EMAIL_CONFIRM_SENT', $myemail));
	}
}

function warquest_settings_change_email_do() {

	/* input */
	global $player;
	global $myemail;
	
	/* output */
	global $popup;
	
	$member = warquest_db_member($player->pid);
	
	if (isset($_POST['notification_comment'])) {		
		$member->notification_comment=1;
	} else {
		$member->notification_comment=0;
	}

	if (isset($_POST['notification_alliance'])) {		
		$member->notification_alliance=1;
	} else {
		$member->notification_alliance=0;
	}
		
	$query = 'select pid from member where email="'.$myemail.'"';
	$result = warquest_db_query($query);
	$count = warquest_db_num_rows($result);
	
	if (validate_email($myemail)) {
	
		$message = t('PLAYER_EMAIL_INVALID');
		$popup .= warquest_box_icon("warning", $message);
		
	} else if (($myemail!=$member->email) && ($count>0)) {
		
		$message = t('PLAYER_EMAIL_EXIST');
		$popup .= warquest_box_icon("warning", $message);
			
	} else if ($myemail!=$member->email) {
					
		$member->email = $myemail;
		$member->email_valid = 0;
		
		warquest_confirm_email($myemail, $player->pid);
		
		$popup .= warquest_box_icon('info', t('USER_EMAIL_CONFIRM_SENT', $myemail));
		
		warquest_info("Email is manually changed!");		
	}

	/* Store settings */
	warquest_db_member_update($member);	
}

function warquest_settings_account_reset_do() {

	/* input */
	global $player;
	global $config;

	/* output */
	global $popup;
	
	/* First update alliance partners */
	$query  = 'select pid1 from player_player where approved=1 and pid2='.$player->pid;
	$result = warquest_db_query($query);	  
	
	while ($data=warquest_db_fetch_object($result)) {
		
		$tmp=warquest_db_player($data->pid1);
		
		$tmp->alliance = warquest_db_alliance_size($data->pid1)-1;
	
		warquest_db_player_update($tmp);
	}
	
	$query = "delete from bank where pid1=".$player->pid; 
	warquest_db_query($query);
	
	$query = 'delete from battle where pid1='.$player->pid.' or pid2='.$player->pid; 
	warquest_db_query($query);

	$query = 'delete from bounty where pid1='.$player->pid.' or pid2='.$player->pid; 
	warquest_db_query($query);
		
	$query = "delete from player_building where pid=".$player->pid; 
	warquest_db_query($query);	
		
	$query = "delete from player_mission where pid=".$player->pid; 
	warquest_db_query($query);
	
	$query = "delete from player_player where pid1=".$player->pid.' or pid2='.$player->pid; 
	warquest_db_query($query);

	$query = "delete from player_stock where pid=".$player->pid; 
	warquest_db_query($query);

	$query = "delete from player_unit where pid=".$player->pid; 
	warquest_db_query($query);
	
	/* Update player (pid=1) to save statitics */
	$tmp = warquest_db_player(1);
	$tmp->won += $player->won;
	$tmp->lost += $player->lost;
	$tmp->mission += $player->mission;
	warquest_db_player_update($tmp);
		
	/* Reset player skills */
	$data = warquest_db_skill($player->pid);
	$data->attack_max = $config["init_attack_max"];
	$data->defense_max = $config["init_defense_max"];
	$data->health_max = $config["init_health_max"];
	$data->energy_max = $config["init_energy_max"];
	$data->ammo_max = $config["init_ammo_max"];
	$data->skill_points = 4;
	$data->health_timer = 0;
	$data->energy_timer = 0;
	$data->ammo_timer = 0;	
	$data->trade_points = 0;
	warquest_db_skill_update($data);
	
	/* Reset player data */	
	$player->won=0;
	$player->lost=0;
	$player->experience=0;
	$player->alliance=1;
	$player->invite=0;
	$player->news=0;
	$player->mission=0;
	$player->bounty=0;
	$player->rebel=0;
	$player->won_level=1;	
	$player->rebel_level=1;
	$player->bounty_level=1;
	$player->planet = 0;
	
	$player->lid=$config["init_level"];
	$player->ammo=$config["init_ammo_max"];
	$player->ammo_step=$config["init_ammo_step"];
	$player->health=$config["init_health_max"];
	$player->health_step=$config["init_health_step"];
	$player->energy=$config["init_energy_max"];
	$player->energy_step=$config["init_energy_step"];	
	$player->money=$config["init_money"];
	$player->money_step=$config["init_money_step"];	
	$player->bank1=$config["init_money_bank1"];
	$player->bank2=$config["init_money_bank2"];
	$player->bank3=$config["init_money_bank3"];
		
	$message = t('SETTING_ACCOUNT_RESETTED', $player->name);
	$popup .= warquest_box_icon("info", $message);
	warquest_info($message.' ['.$player->pid.']');
	
}


function warquest_settings_change_general_do() {

	/* input */	
	global $player;
	global $mycountry;
	global $mybackground;
	global $mylanguage;
	global $mytwitter;
	
	/* output */
	global $popup;
	
	$changed=0;
	
	/*  change nickname */
	$myname="";
	if (isset($_POST['myname']) && $_POST['myname'] != "") {
		$myname = trim($_POST['myname']);
	}
	
	$query='select pid from player where name="'.$myname.'"';
	$result = warquest_db_query($query);
	$count=warquest_db_num_rows($result);
	
	if ($player->name==$myname) {
			/* do nothing */
			
	} else if (strlen($myname)<4) {
	
		$message = t('NICKNAME_TO_SHORT');
		$popup .= warquest_box_icon("warning", $message);

	} else if (strrpos($myname, ' ')>0) {
	
		$message = t('NICKNAME_NO_SPACE');
		$popup .= warquest_box_icon("warning", $message);
		
	} else if ($count>0) {

		$message = t('NICKNAME_EXIST');
		$popup .= warquest_box_icon("warning", $message);
		
	} else {
		
		$changed=1;
		
		/* Set new name */
		$player->name=$myname;
	}
		
	/*  Change twitter */
	if ($player->twitter!=$mytwitter) {
		$player->twitter = $mytwitter;
		$changed = 1;
	}	
	
	/*  Change country */
	if (($player->country=="EU") && (strlen($mycountry)>0) && ($player->country!=$mycountry)) {		
		$player->country = strtoupper($mycountry);
		$changed=1;
	}
	
	/*  Change language */
	if ($player->language!=$mylanguage) {		
		$player->language = $mylanguage;
		$changed=1;
	}
		
	/* Change background */	
	if ($player->background!=$mybackground) {	
		$player->background = $mybackground;
		$changed=1;
	}

	/* sound parameter */
	if (isset($_POST['sound'])) {		
		if (warquest_db_query_pattern($player, PATTERN_SOUND)==0) {
			warquest_db_set_pattern($player, PATTERN_SOUND, 1);
			$changed=1;
		}
	} else {
		if (warquest_db_query_pattern($player, PATTERN_SOUND)==1) {
			warquest_db_set_pattern($player, PATTERN_SOUND, 0);
			$changed=1;
		}
	}
	
	/* bounty confirmation popup parameter */
	if (isset($_POST['bounty'])) {		
		if (warquest_db_query_pattern($player, PATTERN_BOUNTY)==0) {
			warquest_db_set_pattern($player, PATTERN_BOUNTY, 1);
			$changed=1;
		}
	} else {
		if (warquest_db_query_pattern($player, PATTERN_BOUNTY)==1) {
			warquest_db_set_pattern($player, PATTERN_BOUNTY, 0);
			$changed=1;
		}
	}
	
	/* restore confirmation popup parameter */
	if (isset($_POST['restore'])) {		
		if (warquest_db_query_pattern($player, PATTERN_RESTORE)==0) {
			warquest_db_set_pattern($player, PATTERN_RESTORE, 1);
			$changed=1;
		}
	} else {
		if (warquest_db_query_pattern($player, PATTERN_RESTORE)==1) {
			warquest_db_set_pattern($player, PATTERN_RESTORE, 0);
			$changed=1;
		}
	}
	
	/* condition in header parameter */
	if (isset($_POST['condition'])) {		
		if (warquest_db_query_pattern($player, PATTERN_CONDITION)==0) {
			warquest_db_set_pattern($player, PATTERN_CONDITION, 1);
			$changed=1;
		}
	} else {
		if (warquest_db_query_pattern($player, PATTERN_CONDITION)==1) {
			warquest_db_set_pattern($player, PATTERN_CONDITION, 0);
			$changed=1;
		}
	}
	
	/* forum parameter */
	if (isset($_POST['forum'])) {		
		if (warquest_db_query_pattern($player, PATTERN_FORUM_POST)==0) {
			warquest_db_set_pattern($player, PATTERN_FORUM_POST, 1);
			$changed=1;
		}
	} else {
		if (warquest_db_query_pattern($player, PATTERN_FORUM_POST)==1) {
			warquest_db_set_pattern($player, PATTERN_FORUM_POST, 0);
			$changed=1;
		}
	}

	/* sort1 parameter */
	if (isset($_POST['sort1'])) {		
		if (warquest_db_query_pattern($player, PATTERN_SORT1)==0) {
			warquest_db_set_pattern($player, PATTERN_SORT1, 1);
			$changed=1;
		}
	} else {
		if (warquest_db_query_pattern($player, PATTERN_SORT1)==1) {
			warquest_db_set_pattern($player, PATTERN_SORT1, 0);
			$changed=1;
		}
	}
	
	/* sort2 parameter */
	if (isset($_POST['sort2'])) {		
		if (warquest_db_query_pattern($player, PATTERN_SORT2)==0) {
			warquest_db_set_pattern($player, PATTERN_SORT2, 1);
			$changed=1;
		}
	} else {
		if (warquest_db_query_pattern($player, PATTERN_SORT2)==1) {
			warquest_db_set_pattern($player, PATTERN_SORT2, 0);
			$changed=1;
		}
	}
	
	/* No bot news parameter */
	if (isset($_POST['nobotnews'])) {		
		if (warquest_db_query_pattern($player, PATTERN_NO_BOT_NEWS)==0) {
			warquest_db_set_pattern($player, PATTERN_NO_BOT_NEWS, 1);
			$changed=1;
		}
	} else {
		if (warquest_db_query_pattern($player, PATTERN_NO_BOT_NEWS)==1) {
			warquest_db_set_pattern($player, PATTERN_NO_BOT_NEWS, 0);
			$changed=1;
		}
	}
	
	/* Allies in battle and bounty list */
	if (isset($_POST['allylist'])) {		
		if (warquest_db_query_pattern($player, PATTERN_ALLY_LIST)==0) {
			warquest_db_set_pattern($player, PATTERN_ALLY_LIST, 1);
			$changed=1;
		}
	} else {
		if (warquest_db_query_pattern($player, PATTERN_ALLY_LIST)==1) {
			warquest_db_set_pattern($player, PATTERN_ALLY_LIST, 0);
			$changed=1;
		}
	}
	
	/* Show message */
	if ($changed==1) {
	
		$message = t('PLAYER_GENERAL_CHANGED');
		$popup .= warquest_box_icon("info", $message);
		warquest_info($message);
	}
}

function warquest_settings_change_login_do() {

	/* input */	
	global $player;

	/* output */
	global $page;
	global $popup;
	
	/* username parameter */
	$username="";
	if (isset($_POST['username']) && $_POST['username'] != "") {
		$username = $_POST['username'];
		$username = stripslashes($username);
		$username = htmlspecialchars($username);
		$username = warquest_db_escape($username);
	}
		
	/*  myoldpassword parameter */
	$myoldpassword="";
	if (isset($_POST['myoldpassword']) && $_POST['myoldpassword'] != "") {
		$myoldpassword = $_POST['myoldpassword'];
		$myoldpassword  = stripslashes($myoldpassword );
		$myoldpassword  = htmlspecialchars($myoldpassword );
		$myoldpassword  = warquest_db_escape($myoldpassword );
	}
	
	/*  mynewpassword parameter */
	$mynewpassword="";
	if (isset($_POST['mynewpassword']) && $_POST['mynewpassword'] != "") {
		$mynewpassword = $_POST['mynewpassword'];
		$mynewpassword  = stripslashes($mynewpassword );
		$mynewpassword  = htmlspecialchars($mynewpassword );
		$mynewpassword  = warquest_db_escape($mynewpassword );
	}
	
	$member = warquest_db_member($player->pid);
		
	$query1 = 'select pid from member where username="'.$username.'"';
	$result1 = warquest_db_query($query1);
	$count1 = warquest_db_num_rows($result1);
	
	/* Change password */

	if ((strlen($username)>0) && ($username!=$member->username)) {
		
		if (strlen($username)<4) {
		
			$message = t('PLAYER_USERNAME_TO_SHORT');
			$popup .= warquest_box_icon("warning", $message);

		} else if ($count1>0) {
	
			$message = t('PLAYER_USERNAME_ALREADY_EXIST');
			$popup .= warquest_box_icon("warning", $message);
		
		} else {

			$message = t('PLAYER_USERNAME_CHANGED');
			$popup .= warquest_box_icon("info", $message);
	
			warquest_db_member_username_update($player->pid, $username);
			warquest_info("Username changed to ".$username);	
		}
	}	
	
	$query2 = 'select pid from member where password="'.md5($myoldpassword).'" and pid='.$player->pid;
	$result2 = warquest_db_query($query2);
	$count2 = warquest_db_num_rows($result2);
	
	/* Change password */

	if ((strlen($mynewpassword)>0) || (strlen($myoldpassword)>0)) {
	
		if ($count2!=1) {
	
			$message = t('PLAYER_PASSWORD_NO_MATCH');
			$popup .= warquest_box_icon("warning", $message);
			
		} else if (strlen($mynewpassword)<6)  {
		
			$message = t('PLAYER_PASSWORD_TO_SHORT');
			$popup .= warquest_box_icon("warning", $message);
			
		} else {

			$message = t('PLAYER_PASSWORD_CHANGED');
			$popup .= warquest_box_icon("info", $message);
	
			warquest_db_member_password_update($player->pid, $mynewpassword);
			warquest_info("Password is changed!");
		}
	}
}

/*
** ---------------------
** UI
** ---------------------
*/

function warquest_settings_form() {

	/* input */
	global $mid;
	global $sid;
	global $player;
	global $config;
	global $browser;
	
	/* output */
	global $page;
	global $title;
	
	$title = t('SETTING_TITLE');
		
	$member = warquest_db_member($player->pid);
	
	if (strlen($member->email)==0) {
		$message = t('HOME_EMAIL_MISSING');
		$page .= warquest_box_icon("warning", $message);
	}
		
	/*
   ** ---------------------------------
	** General Settings (Section 1)
	** ---------------------------------
	*/
	
	$page .= '<div class="subparagraph">'.t('SETTING_GENERAL1').'</div>';
	
	$page .= '<div class="box">';
	
	$page .= '<table cellpadding="2" cellspacing="1">';
	
	$page .= '<tr>';
	$page .= '<td width="200">'.t('SETTING_NICKNAME').':</td>';
	$page .= '<td>';
	$page .= warquest_ui_input('myname', 20, 15, $player->name, false);
	$page .= '</td>';
	$page .= '</tr>';
	
	$page .= '<tr>';
	$page .= '<td>'.t('GENERAL_COUNTRY').':</td>';
	$page .= '<td>';
	$page .= warquest_ui_country("mycountry", $player->country, !($player->country=="EU"));
	$page .= '</td>';
	$page .= '</tr>';
	
	$page .= '<tr>';
	$page .= '<td>'.t('SETTING_LANGUAGE').':</td>';
	$page .= '<td>';
	$page .= warquest_ui_language('mylanguage', $player->language, false);
	$page .= '</td>';
	$page .= '</tr>';
				
	$page .= '<tr>';
	$page .= '<td>'.t('SETTING_BACKGROUND').':</td>';
	$page .= '<td>';
	$page .= warquest_ui_background("mybackground", $player->background, false);
	$page .= '</td>';
	$page .= '</tr>';
		
	$page .= '<tr>';
	$page .= '<td width="200">'.t('SETTING_TWITTER').':</td>';
	$page .= '<td>';
	$page .= warquest_ui_input('mytwitter', 30, 20, $player->twitter, false);
	$page .= '</td>';
	$page .= '</tr>';
	
	$page .= '<tr>';
	$page .= '<td></td>';
	$page .= '<td>';
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&eid=7', t('LINK_CHANGE'), 'change-1');
	$page .= '</td>';
	$page .= '</tr>';
			
	$page .= '</table>';
	$page .= '</div>';
	
	/*
   ** ---------------------------------
	** General Settings (Section 2)
	** ---------------------------------
	*/
	
	$page .= '<div class="subparagraph">'.t('SETTING_GENERAL2').'</div>';
	
	$page .= '<div class="box">';
	
	$page .= '<table cellpadding="2" cellspacing="1">';
	
	$page .= '<tr>';
	
	$page .= '<td>'.warquest_ui_checkbox("sound", "sound", warquest_db_query_pattern($player, PATTERN_SOUND)).'</td>';
	$page .= '<td>'.t('SETTING_SOUND').'</td>';
	$page .= '</tr>';
				
	$page .= '<tr>';
	
	if (!preg_match("/Symbian/", $browser)) {
	
		$page .= '<td>'.warquest_ui_checkbox("bounty", "bounty", warquest_db_query_pattern($player, PATTERN_BOUNTY)).'</td>';
		$page .= '<td>'.t('SETTING_BOUNTY').'</td>';
		$page .= '</tr>';
	
		$page .= '<tr>';	
		$page .= '<td>'.warquest_ui_checkbox("restore", "restore", warquest_db_query_pattern($player, PATTERN_RESTORE)).'</td>';
		$page .= '<td>'.t('SETTING_RESTORE').'</td>';
		$page .= '</tr>';
	}
	
	$page .= '<tr>';
	
	$page .= '<td>'.warquest_ui_checkbox("condition", "condition", warquest_db_query_pattern($player, PATTERN_CONDITION)).'</td>';
	$page .= '<td>'.t('SETTING_CONDITION').'</td>';
	$page .= '</tr>';
	
	$page .= '<tr>';
	$page .= '<td>'.warquest_ui_checkbox("forum", "forum", warquest_db_query_pattern($player, PATTERN_FORUM_POST)).'</td>';
	$page .= '<td>'.t('SETTING_FORUM_POST').'</td>';
	$page .= '</tr>';
	
	$page .= '<tr>';
	$page .= '<td>'.warquest_ui_checkbox("sort1", "sort1", warquest_db_query_pattern($player, PATTERN_SORT1)).'</td>';
	$page .= '<td>'.t('SETTING_SORT1').'</td>';
	$page .= '</tr>';
	
	$page .= '<tr>';
	$page .= '<td>'.warquest_ui_checkbox("sort2", "sort2", warquest_db_query_pattern($player, PATTERN_SORT2)).'</td>';
	$page .= '<td>'.t('SETTING_SORT2').'</td>';
	$page .= '</tr>';
	
	$page .= '<tr>';
	$page .= '<td>'.warquest_ui_checkbox("nobotnews", "nobotnews", warquest_db_query_pattern($player, PATTERN_NO_BOT_NEWS)).'</td>';
	$page .= '<td>'.t('SETTING_NO_BOT_NEWS').'</td>';
	$page .= '</tr>';
	
	$page .= '<tr>';
	$page .= '<td>'.warquest_ui_checkbox("allylist", "allylist", warquest_db_query_pattern($player, PATTERN_ALLY_LIST)).'</td>';
	$page .= '<td>'.t('SETTING_ALLIES_IN_BATTLE_LIST').'</td>';
	$page .= '</tr>';
	
	$page .= '<tr>';
	$page .= '<td></td>';
	$page .= '<td>'.warquest_link('mid='.$mid.'&sid='.$sid.'&eid=7', t('LINK_CHANGE'), 'change-2').'</td>';
	$page .= '</tr>';
	
	$page .= '</table>';
	$page .= '</div>';
		
	/*
	** ---------------------------------
	** Email Settings (Section 3)
	** ---------------------------------
	*/

	$page .= '<div class="subparagraph">'.t('PLAYER_CHANGE_EMAIL').'</div>';
	
	$page .= '<div class="box">';
	$page .= '<table cellpadding="2" cellspacing="1">';

	$page .= '<tr>';
	$page .= '<td width="200">'.t('PLAYER_NEW_EMAIL').':</td>';
	$page .= '<td>';
	$page .= warquest_ui_input('myemail', 30, 100, $member->email, false);
		
	if ($member->email_valid==0) {
		
		$link = warquest_link('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_EMAIL_CONFIRM.'&id='.$player->pid, t('USER_EMAIL_HERE'));
		
		$page .= '<span class="help">';
		$page .= ' '.t('USER_EMAIL_CONFIRM_NEEDED',$link);
		$page .= '</span>';
	}
	
	$page .= '</td>';
	
	$page .= '</tr>';
		
	$page .= '<tr>';
	$page .= '<td>'.t('PLAYER_NOTIFICATION_COMMENT').':</td>';
	$page .= '<td>';
	$page .= warquest_ui_checkbox("notification_comment", "notification_comment", $member->notification_comment);
	$page .= '</td>';
	$page .= '</tr>';
				
	$page .= '<tr>';
	$page .= '<td>'.t('PLAYER_NOTIFICATION_ALLIANCE').':</td>';
	$page .= '<td>';
	$page .= warquest_ui_checkbox("notification_alliance", "notification_alliance", $member->notification_alliance);
	$page .= '</td>';
	$page .= '</tr>';
	
	$page .= '<tr>';
	$page .= '<td>&nbsp;</td>';
	$page .= '<td>';
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_EMAIL_CHANGE, t('LINK_CHANGE'), 'change-3');
	$page .= '</td>';
	$page .= '</tr>';

	$page .= '</table>';
	$page .= '</div>';

	/*
	** ---------------------------------
	** Login settings (Section 4)
	** ---------------------------------
	*/
	
	if (!preg_match("/Symbian/", $browser)) {
	
		$page .= '<div class="subparagraph">'.t('PLAYER_LOGIN_SETTINGS').'</div>';
		
		$page .= '<div class="box">';
	
		$page .= '<table cellpadding="2" cellspacing="1">';
						
		$page .= '<tr>';	
		$page .= '<td width="200">'.t('PLAYER_USERNAME').':</td>';
		$page .= '<td>';
	
		$page .= '<input name="username" type="text" id="username" size="18" ';
		$page .= 'maxlength="'.$config["max_username_length"].'" value="'.$member->username.'"/>';
		$page .= '</td>';
		$page .= '</tr>';
		
		$page .= '<tr>';
		$page .= '<td>'.t('PLAYER_CURRENT_PASSWORD').':</td>';
		$page .= '<td>';
		$page .= '<input name="myoldpassword" type="password" id="myoldpassword" size="18" ';
		$page .= 'maxlength="'.$config["max_password_length"].'" />';
		$page .= '</td>';
		$page .= '</tr>';
		
		$page .= '<tr>';
		$page .= '<td>'.t('PLAYER_NEW_PASSWORD').':</td>';
		$page .= '<td>';
		$page .= '<input name="mynewpassword" type="password" id="mynewpassword" size="18" ';
		$page .= 'maxlength="'.$config["max_password_length"].'" />';
		$page .= '</td>';
		$page .= '</tr>';
	
		$page .= '<tr>';
		$page .= '<td>&nbsp;</td>';
		$page .= '<td>';
		$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&eid=9', t('LINK_CHANGE'), 'change-4');
		$page .= '</td>';
		$page .= '</tr>';
	
		$page .= '</table>';	
		$page .= '</div>';
				
		$page .= '<div class="note">';
		$page .= t('PLAYER_LOGIN_NOTE');
		$page .= '</div>';
	}
		
	$page .= '<div class="subparagraph">';
	$page .= t('SETTING_ACCOUNT_RESET_TITLE');	
	$page .= '</div>';		
	$page .= '<div class="box">';	
	$page .= t('SETTING_ACCOUNT_RESET').' ';
	$page .= warquest_link_confirm('mid='.$mid.'&sid='.$sid.'&eid=10', t('SETTING_YES'), t('SETTING_SURE'));
	$page .= ' '.t('SETTING_NO_REVERSE');	
	$page .= '</div>';
	
	$page .= '<div class="note">';
	$page .= t('SETTING_ACCOUNT_RESET_NOTE');	
	$page .= '</div>';
							
	
	/*
	** ---------------------------------
	** Reset account 
	** ---------------------------------
	*/
	
	$page .= warquest_show_ads();
}

/*
** --------------- 
** Handler
** ---------------
*/

/**
 * Settings handler
 */
function warquest_settings_events() {
	
	/* input	*/
	global $eid;
			
	/* Event handler */
	switch ($eid) {
						
		case 7:
			warquest_settings_change_general_do();
			break;
						
		case 9:
			warquest_settings_change_login_do();
			break;
			
		case 10:
			warquest_settings_account_reset_do();
			break;
			
		case EVENT_EMAIL_CHANGE: 
			warquest_settings_change_email_do();
			break;		
			
		case EVENT_EMAIL_CONFIRM:
			warquest_user_email_confirm_do();
			break;
	}	
}

/*
** ------------------
** THE END
** ------------------
*/

?>