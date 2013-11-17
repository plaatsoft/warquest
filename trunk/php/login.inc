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
** PARAMS
** ----------------------------------------------------------------
*/

$myusername = warquest_post('myusername', '');
$mypassword = warquest_post('mypassword', '');
$myname = warquest_post('myname', '');
$myemail = warquest_post('myemail', '');

$auto_login = 0;

/* myusername (automatic login with WarQuest client) */
if (isset($_SERVER['HTTP_USERNAME'])) {
	$myusername = $_SERVER['HTTP_USERNAME'];		
	$myusername = stripslashes($myusername);
	$myusername = substr($myusername,0,$config["max_username_length"]);

	/* Set client mode  */
	$auto_login = 1;
}
	
/* mypassword (automatic login with Windows WarQuest client) */
if (isset($_SERVER['HTTP_PASSWORD'])) {
	$mypassword = $_SERVER['HTTP_PASSWORD'];
	$mypassword = stripslashes($mypassword);
	/*$mypassword = warquest_db_escape($mypassword);*/
	$mypassword = substr($mypassword,0,$config["max_password_length"]);
}
	
/* myname (automatic login with Windows WarQuest client) */
if (isset($_SERVER['HTTP_NAME'])) {
	$myname = $_SERVER['HTTP_NAME'];
	$myname = stripslashes($myname);
	$myname = warquest_db_escape($myname);
	$myname = substr($myname,0,15);
}
	
/* eventId (automatic login with Windows WarQuest client) */
if (isset($_SERVER['HTTP_EID'])) {
	$eid = $_SERVER['HTTP_EID'];
	$eid = substr($eid,0,1);
}
	
/* Get WarQuest client version */
if (isset($_SERVER['HTTP_VERSION'])) {
	$version = $_SERVER['HTTP_VERSION'];
}

/*
** ------------------
** GENERAL
** ------------------
*/

/**
 * client overview
 */
function warquest_client_overview() {

	/* input */
	global $page;
	
	$page .= '<br/>';
		
	$page .= '<table>';
	$page .= '<tr>';
	
	$page .= '<td width="100">'; 
	$page .= '</td>';
	
	$page .= '<td width="155" align="center">';
	$page .= '<center><a target="_blank" href="http://market.android.com/details?id=nl.plaatsoft.warquest">';
	$page .= warquest_image("other/android.png");
	$page .= '<br/>WarQuest for Android</a>'; 
	$page .= '</center>';
	$page .= '</td>';
	
	$page .= '<td width="155" align="right">';
	$page .= '<center><a target="_blank" href="http://store.ovi.com/content/253826">';
	$page .= warquest_image("other/symbian.jpg");
	$page .= '<br/>WarQuest for Symbian</a>'; 
	$page .= '</center>';
	$page .= '</td>';
	
	$page .= '<td width="100">'; 
	$page .= '</td>';
	
	$page .= '</tr>';
	$page .= '<tr>';
	
	$page .= '<td width="100">'; 
	$page .= '</td>';
	
	$page .= '<td width="155" align="right">';
	$page .= '<center><a target="_blank" href="http://www.plaatsoft.nl/windows/warquest">';
	$page .= warquest_image("other/windows.jpg");
	$page .= '<br/>WarQuest for Windows</a>'; 
	$page .= '</center>';
	$page .= '</td>';
		
	$page .= '<td width="155" align="right">';
	$page .= '<center><a target="_blank" href="https://myapps.developer.ubuntu.com/dev/apps/859">';
	$page .= warquest_image("other/linux.jpg");
	$page .= '<br/>WarQuest for Linux</a>'; 
	$page .= '</center>';
	$page .= '</td>';
	
	$page .= '<td width="100">'; 
	$page .= '</td>';
	
	$page .= '</tr>';
	$page .= '</table>';
}

function warquest_login_menu() {

	/* input */
	global $mid;
	global $sid;
	global $version;
	
	$page  = '<center>';
		
	$page .= warquest_ui_menu($mid, PAGE_LOGIN, t('LINK_LOGIN'), $sid);
	$page .= warquest_ui_menu($mid, PAGE_REGISTER, t('LINK_REGISTER'), $sid);
	$page .= warquest_ui_menu($mid, PAGE_RECOVER, t('LINK_RECOVER'), $sid);
	$page .= warquest_ui_menu($mid, PAGE_FACEBOOK, t('LINK_FACEBOOK'), $sid);
		
	if (strlen($version)==0) {
		$page .= '<a target="_blank" href="rss.php">'.t('LINK_RSS').'</a>'; 
	}
		
	$page .= '</center>';
	
	return $page;
}

/**
 * Login page header
 */
function warquest_login_header() {

	/* input */
	global $sid;
	global $config;

	/* output */
	global $page;
	
	$page .= '<div class="banner">';
	$page .= '<table>';
	$page .= '<tr>';
	$page .= '<td align="left">';	
	$page .= warquest_unit_image(rand(1,24),0,0,140,100, 'id="i1"');
	$page .= '</td>';
	$page .= '<td align="center" width="100%">';
	$page .= '<div class="title">'.$config["applName"].'</div>'.'';
	$page .= '<span class="subparagraph">'.$config["applVersion"].'</span>';
	$page .= '</td>';	
	$page .= '<td align="right">';	
	$page .= warquest_unit_image(rand(101,127),0,0,140,100, 'id="i2"');
	$page .= '</td>';
	$page .= '</tr>';
	$page .= '</table>';
	$page .= '</div>';
	
	$page .= '<br/>';
	
	$page .= warquest_login_menu();
	
	if ($sid!=5) {
		$page .= '<div class="note">';
		$page .= t('HELP_INTRO');
		$page .= '</div>';
		
		$page .= '<br/>';
	}
		
	warquest_login_refresh(1,24,"i1");
	warquest_login_refresh(101,27,"i2");
}

/** 
 * Auto refresh image 
 */
function warquest_login_refresh($offset, $range, $id) {

	/* input */
	global $config;

	/* output */
	global $page;
	
	$page .= '<script language="JavaScript" type="text/javascript">';
   $page .= 'function Start'.$id.'() { ';
	$page .= 'var nr = "'.$config["content_url"].'images/units/unit" + (Math.floor(Math.random() * '.$range.') + '.$offset.') + ".jpg"; ';
   $page .= 'document.forms[\'warquest\'].elements["'.$id.'"].src = nr; ';
   $page .= 'setTimeout("Start'.$id.'('.$offset.')", 2000); ';
   $page .= '} ';
   $page .= 'Start'.$id.'('.$offset.'); ';
   $page .= '</script>'; 
}
		
/**
 * Login page footer
 */
function warquest_login_footer() {

	/* input */
	global $sid;
	
	/* output */
	global $page;
		
	$page .= '<br/>';	
	
	$page .= '<div class="note">';
	$page .= t('LOGIN_BEST_VIEWED');
	$page .= '</div>';
			
	$page .= '<br/>';	
		
	$page .= '<div class="banner">';
	$page .= '<table>';
	$page .= '<tr>';
	$page .= '<td align="left">';
	$page .= warquest_unit_image(rand(201,228),0,0,140,100, 'id="i3"');
	$page .= '</td>';
	$page .= '<td width="100%">';
	
	/* If no database error show game statistics. */
	if ($sid!=PAGE_MAINTENANCE) {
	
		/* Update login counter */
		warquest_db_player_login_counter(1);
	
		$query =  'select count(*) as count, sum(request) as request from player';
		$result = warquest_db_query($query); 
		$data=warquest_db_fetch_object($result);
				
		$query =  'select distinct(country) from player';
		$result = warquest_db_query($query); 
		$count=warquest_db_num_rows($result);
			
		$yesterday = mktime(date("H"), date("i"), date("s"), date("m"), date("d")-1, date("Y"));
		$query4  = 'select count(*) as count from member where last_login > "'.date("Y-m-d H:i:s", $yesterday).'" ';		
		$result4 = warquest_db_query($query4);
		$data4=warquest_db_fetch_object($result4);
		
		$page .= '<center/>';	
		
		$page .= '<span class="energy">';
		$page .= number_format($data->count,0,",",".");
		$page .= '</span> '.t('LOGIN_PLAYERS').'<br/>';
		$page .= '<span class="country">';
		$page .= number_format($count,0,",",".");
		$page .= '</span> '.t('LOGIN_COUNTRIES').'<br/>';	
		$page .= '<span class="money">';
		$page .= number_format($data->request,0,",",".");
		$page .= '</span> '.t('LOGIN_REQUESTS').'<br/>';	
		$page .= '<span class="energy">';
		$page .= number_format($data4->count,0,",",".");
		$page .= '</span> '.t('LOGIN_ONLINE').'<br/>';	
		
		$page .= '</center>';
	}

	$page .= '</td>';	
	$page .= '<td align="right">';
	$page .= warquest_unit_image(rand(301,326),0,0,140,100, 'id="i4"');
	$page .= '</td>';
	$page .= '</tr>';

	$page .= '</table>';
	$page .= '</div>';
				
	warquest_login_refresh(201,27,"i3");
	warquest_login_refresh(301,26,"i4");	
}


/*
** -----------
** FACEBOOK
** -----------
*/

function warquest_facebook_form() {

	/* output */
	global $page;
	
	$page .= '<style type="text/css">';
	$page .= '.background {';
	$page .= 'background-color:rgb(255,255,255);';
	$page .= '}';
	$page .= '</style>';
	
	$page .= '<div class="background">';
	
	$page .= '<div id="fb-root"></div>
<script>(function(d, s, id) {
  var js, fjs = d.getElementsByTagName(s)[0];
  if (d.getElementById(id)) return;
  js = d.createElement(s); js.id = id;
  js.src = "//connect.facebook.net/nl_NL/all.js#xfbml=1&appId=146129318831064";
  fjs.parentNode.insertBefore(js, fjs);
}(document, \'script\', \'facebook-jssdk\'));</script>';

	$page .= '<div class="fb-like-box" data-href="http://www.facebook.com/WarQuest" data-width="510" data-show-faces="true" data-border-color="#ffffff" data-stream="true" data-header="true"></div>';

	$page .= '</div>';
   $page .= '<br/>'; 
}


/*
** -----------
** MAINTENANCE
** -----------
*/

function warquest_maintenance_form() {

	/* output */
	global $page;
	global $mid;
	
	$page .= '<div class="box2">';
	$page .= '<strong>';
	$page .= '<span class="energy"">'.t('LOGIN_MAINTENANCE_TITLE').'</span>';
	$page .= '</strong>';
	$page .= '<br/><br/>';
	$page .= t('LOGIN_MAINTENANCE');
	$page .= '<br/>';
	$page .= '<br/>';
	$page .= warquest_link('mid='.$mid.'&sid='.PAGE_LOGIN, t('LINK_LOGIN'), 'login'); 
	$page .= '</div>';
}


/*
** -----------
** LOGOUT 
** -----------
*/

function warquest_logout_do() {

	/* input  */	
	global $session;

	/* output  */	
	global $page;
	global $version;
	
	$pid = warquest_db_session_valid($session);
	if ($pid!=0) {
	
		$member = warquest_db_member($pid);	
		$version = $member->version;
		
		warquest_info($member->username.' logout succesfull');
	}
	
	/* destroy session */
	warquest_db_session_delete($session);
	$session="";
		
	$page .= '<div class="box2">';
	$page .= '<span class="info">'.t('BOX_INFO').'</span><br/><br/>';
	$page .= t('LOGIN_LOGOUT');
	$page .= '</div>';	
}

/*
** ------------------
** PASSWORD RECOVERY
** ------------------
*/

/**
 * Create random password
 */
function warquest_randomPassword($length) {
	$possible = '0123456789' .
					'abcdefghjiklmnopqrstuvwxyz'.
					'ABCDEFGHIJKLMNOPQRSTUVWXYZ';
	$str = "";
	while (strlen($str) < $length) {
			$str .= substr($possible, (rand() % strlen($possible)), 1);
	}	

	return($str);
}


/** 
 * Password recovery action handler
 */
function warquest_email_do() {

	/* input */
	global $myemail;
	global $config;
	
	/*  output */
	global $page;

	$query='select pid, username from member where email="'.$myemail.'"';
	$result = warquest_db_query($query);
	$data = warquest_db_fetch_object($result);
	
	if (validate_email($myemail)) {
	
		$page .= '<div class="box2">';
		$page .= '<span class="warning">'.t('BOX_WARN').'</span><br/>';
		$page .= t('LOGIN_EMAIL_INVALID');
		$page .= '</div>';
		
		warquest_info($myemail.' email reset failed. Invalid email!');
		
	} else if (!isset($data->pid)) {
	
		$page .= '<div class="box2">';
		$page .= '<span class="warning">'.t('BOX_WARN').'</span><br/>';
		$page .= t('LOGIN_EMAIL_UNKNOWN');
		$page .= '</div>';
		
		warquest_info($myemail.' email reset failed. Email unknown in db!');
			
	} else {
	
		/* Create random password */
		$password=warquest_randomPassword(10);
	
		warquest_db_member_password_update($data->pid, $password);
		
		$subject = 'Password reset of '.$config["applName"];
	
		$body  = 'Your password is reset!'."\r\n\r\n";
		$body .= 'Your username = '.$data->username."\r\n";
		$body .= 'Your new password = '.$password."\r\n\r\n";
		$body .= 'Visit '.$config["base_url"].' and login to continue the game.'."\r\n";
		
		$header = 'From: '.$config["applName"]. '<'.$config['from_email'].">\r\n";

		@mail($myemail, $subject, $body, $header);
		warquest_info("Send email [".$myemail."] Password reset");
		
		@mail($config["from_email"], $subject, $body, $header);
		warquest_info("Send email [".$config["from_email"]."] Password reset");
		
		$page .= '<div class="box2">';
		$page .= '<span class="info">'.t('BOX_INFO').'</span><br/>';
		$page .= t('LOGIN_NEW_PASSWORD_SEND');
		$page .= '</div>';
		
		warquest_info($myemail.' email reset succesfull');
	}
}

/**
 * Password recover form
 */
function warquest_recover_form() {

	/* input */
	global $myemail;
	global $version;
	global $mid;
	
	/* output  */
	global $page;
	global $title;
	
	$title = t('LOGIN_RECOVER_TITLE');
	
	$page .= '<div class="box2">';
	$page .= '<table cellpadding="2" cellspacing="1">';
	
	$page .= '<tr>';
	$page .= '<td colspan="2">';
	$page .= '<strong>'.t('LOGIN_RECOVER_TITLE').'</strong>';
	$page .= '<br/>';
	$page .= '<div class="note">';
	$page .= t('LOGIN_PASSWORD_RESET_NOTE');
	$page .= '</div>';
	$page .= '</td>';
	$page .= '</tr>';
		
	$page .= '<tr>';
	$page .= '<td width="80">'.t('LOGIN_EMAIL').':</td>';
	$page .= '<td><input name="myemail" type="text" size="35" maxlength="120" value="'.$myemail.'" id="myemail"></td>';
	$page .= '</tr>';
		
	$page .= '<tr>';
	$page .= '<td>&nbsp;</td>';
	$page .= '<td>';
	$page .= '<br/>';
	$page .= '<input type="hidden" name="token" value="'.warquest_token('mid='.$mid.'&sid='.PAGE_RECOVER.'&eid=3&version='.$version).'">';
	$page .= '<input type="submit" name="Submit" value="'.t('LINK_SEND').'">';
	$page .= '</td>';
	$page .= '</tr>';
	$page .= '</table>';
		
	$page .= '</div>';	
	
	/* Set focus on first input element */
	$page .= '<script type="text/javascript" language="JavaScript">';
	$page .= 'document.forms[\'warquest\'].elements[\'myemail\'].focus();';
	$page .= '</script>';
}

/*
** --------
** REGISTER
** --------
*/

/**
 * Send registration welcome email
 */
function warquest_register_mail($to, $username) {

	/* input */
	global $config;
	
	$subject = 'Welcome to '.$config["applName"];
	
	$body  = 'Welcome to '.$config["applName"]."\r\n\r\n";
	$body .= 'Thanks you for registrating!'."\r\n\r\n";
	$body .= 'Your username = '.$username."\r\n\r\n";
	
	$body .= 'Please confirm your email address by clicking the following link'."\r\n";

	$body .= $config["base_url"].'?action='.EVENT_EMAIL_CONFIRM.'&key='.$id.'-'.md5($to)."\r\n\r\n";
	
	$body .= 'Visit '.$config["base_url"].' and login to continue the game.'."\r\n";

	$header = 'From: '.$config["applName"]. '<'.$config['from_email'].">\r\n";

	if ($to!="") {
		@mail($to, $subject, $body, $header);
		warquest_info("Send email [".$to."] Welcome message");
	}
}


/**
 * Registration action handler
 */
function warquest_register_do($amount) {

	/* input */
   global $myname;
	global $myemail;
   global $myusername;
	global $mypassword;
	global $auto_login;
	global $config;
	
	/* output */
	global $page;
	global $sid;
			
	$count1=0;
	$query='select pid from member where username="'.$myusername.'"';
	$result = warquest_db_query($query);	
	if (isset($result)) {
		$count1=warquest_db_num_rows($result);
	}

	$count2=0;
	$query='select pid from player where name="'.$myname.'"';
	$result = warquest_db_query($query);
	if (isset($result)) {
		$count2=warquest_db_num_rows($result);
	}
	
	$count3=0;
	$query='select pid from member where email="'.$myemail.'"';
	$result = warquest_db_query($query);
	if (isset($result)) {
		$count3=warquest_db_num_rows($result);
	}
	
	/* If result matched $myusername and $mypassword, table row must be 1 row */
	if (($auto_login==0) && (strlen($myname)==0)) {
	
		$page .= '<div class="box2">';
		$page .= '<span class="warning">'.t('BOX_WARN').'</span><br/>';
		$page .= t('LOGIN_NICKNAME_NEEDED');
		$page .= '</div>';
		
		warquest_info($myusername.' registration failed. Nickname empty');
		
	} else if (($auto_login==0) && (strrpos($myname, ' ')>0)) {
	
		$page .= '<div class="box2">';
		$page .= '<span class="warning">'.t('BOX_WARN').'</span><br/>';
		$page .= t('NICKNAME_NO_SPACE');
		$page .= '</div>';
		
		warquest_info($myusername.' registration failed. Nickname contain char character');
	
	} else if (($count2>0) && ($auto_login==0)) {
	
		$page .= '<div class="box2">';
		$page .= '<span class="warning">'.t('BOX_WARN').'</span><br/>';
		$page .= T('LOGIN_NICKNAME_EXIST', $myname);
		$page .= '</div>';
		
		warquest_info($myusername.' registration failed. Nickname already exist');
	
	} else if (validate_email($myemail) && ($auto_login==0)) {
	
		$page .= '<div class="box2">';
		$page .= '<span class="warning">'.t('BOX_WARN').'</span><br/>';
		$page .= t('LOGIN_EMAIL_INVALID'); 
		$page .= '</div>';
		
		warquest_info($myusername.' registration failed. Email invalid');
		
	} else if (($count3>0) && ($auto_login==0)) {
	
		$page .= '<div class="box2">';
		$page .= '<span class="warning">'.t('BOX_WARN').'</span><br/>';
		$page .= t('LOGIN_EMAIL_EXIST'); 
		$page .= '</div>';
		
		warquest_info($myusername.' registration failed. Email already exist');
			
	} else if ($count1>0) {
	
		$page .= '<div class="box2">';
		$page .= '<span class="warning">'.t('BOX_WARN').'</span><br/>';
		$page .= t('LOGIN_USERNAME_EXIST', $myusername);
		$page .= '</div>';
		
		warquest_info($myusername.' registration failed. Username already exist');
			
	} else if (strlen($myusername)<4) {
		
		$page .= '<div class="box2">';
		$page .= '<span class="warning">'.t('BOX_WARN').'</span><br/>';
		$page .= t('LOGIN_USERNAME_TO_SHORT');
		$page .= '</div>';
		
		warquest_info($myusername.' registration failed. Username to short');
		
	} else if (strlen($mypassword)<6) {
	
		$page .= '<div class="box2">';
		$page .= '<span class="warning">'.t('BOX_WARN').'</span><br/>';
		$page .= t('LOGIN_PASSWORD_TO_SHORT');
		$page .= '</div>';
		
		warquest_info($myusername.' registration failed. Password to short');
		
	} else {

		$pid = warquest_db_member_insert($myusername,$mypassword,$myemail);
		
		/* If username is unknown (WarQuest Client) created one. */
		if ($myname == "") {
			$myname="player-".$pid;
		}
		warquest_db_player_insert($myname,$pid);
		warquest_db_skill_insert($pid, $amount);
						
		if ($auto_login==0) {		
	
			warquest_register_mail($myemail, $myusername);
		}
		
		$page .= '<div class="box2">';
		$page .= '<span class="info">'.t('BOX_INFO').'</span><br/>';
		$page .= t('LOGIN_REGISTER_OK', $myusername);		
		$page .= '</div>';		
		
		/* redirect to login page. */
		$sid = 1;
		
		warquest_info($myusername.' registration succesfull');
		
		return 1;
	}
	
	return 0;
}

/**
 * Registration form 
 */
function warquest_register_form() {

	/* input */
   global $myname;
	global $myemail;
   global $myusername;
	global $mypassword;
	global $config;
	global $version;
	global $mid;
	
	/* output  */
	global $page;
	global $title;
	
	$title = t('LOGIN_REGISTER_TITLE');
		
	$page .= '<div class="box2">';
		
	$page .= '<table cellpadding="3" cellspacing="1">';
	
	$page .= '<tr>';
	$page .= '<td colspan="2">';
	$page .= '<strong>'.t('LOGIN_REGISTER_TITLE').'</strong>';
	$page .= '<br/><br/>';
	$page .= '</td>';
	$page .= '</tr>';
		
	$page .= '<tr>';
	$page .= '<td width="80">'.t('LOGIN_NICKNAME').':</td>';
	$page .= '<td><input name="myname" type="text" size="20" maxlength="15" value="'.$myname.'" id="myname"></td>';
	$page .= '</tr>';
		
	$page .= '<tr>';
	$page .= '<td>'.t('LOGIN_EMAIL').':</td>';
	$page .= '<td><input name="myemail" type="text" size="35" maxlength="120" value="'.$myemail.'" id="myemail"></td>';
	$page .= '</tr>';
		
	$page .= '<tr>';	
	$page .= '<td>'.t('LOGIN_USERNAME').':</td>';
	$page .= '<td><input name="myusername" type="text" size="18" maxlength="';
	$page .= $config["max_username_length"].'" value="'.$myusername.'" id="myusername"></td>';
	$page .= '</tr>';
		
	$page .= '<tr>';
	$page .= '<td>'.t('LOGIN_PASSWORD').':</td>';
	$page .= '<td><input name="mypassword" type="password" size="18" maxlength="';
	$page .= $config["max_password_length"].'" value="'.$mypassword.'" id="myzpassword"></td>';
	$page .= '</tr>';
		
	$page .= '<tr>';
	$page .= '<td>&nbsp;</td>';
	$page .= '<td>';
	$page .= '<br/>';
	$page .= '<input type="hidden" name="token" value="'.warquest_token('mid='.$mid.'&sid='.PAGE_REGISTER.'&eid=2&version='.$version).'">';
	$page .= '<input type="submit" name="Submit" value="'.t('LINK_REGISTER').'">';
	$page .= '</td>';
	$page .= '</tr>';
	$page .= '</table>';
			
	$page .= '</div>';	
	
	/* Set focus on first input element */
	$page .= '<script type="text/javascript" language="JavaScript">';
	$page .= 'document.forms[\'warquest\'].elements[\'myname\'].focus();';
	$page .= '</script>';
	
	$page .= '<script language="JavaScript" src="'.$config["content_url"].'js/jquery.js"></script>';
	$page .= '<script language="JavaScript" src="'.$config["content_url"].'js/password.js"></script>';
	$page .= '<link href="'.$config["content_url"].'css/password.css" rel="stylesheet" type="text/css" />';
}

/*
** --------
** LOGIN
** --------
*/

/** 
 * Login action
 */
function warquest_login_do() {

	/* input */
   global $myusername;
	global $mypassword;
	global $version;
	global $auto_login;
	
	/* output */
	global $page;
	global $mid;
	global $pid;
	global $sid;
	global $eid;
	global $session;
					
	$pid = warquest_db_member_pid($myusername, $mypassword);
		
	if($pid == 0) {
	
		$page .= '<div class="box2">';
		$page .= '<span class="warning">'.t('BOX_WARN').'</span><br/>';
		$page .= t('LOGIN_FAILED');
		$page .= '</div>';
			
		warquest_info($myusername.' login failed');
	
	} else {
	
	  $player = warquest_db_player($pid);
	  
	  if (warquest_db_query_pattern($player, PATTERN_BAN)==1) {
		
			/* Check if player is ban */		
			$page .= '<div class="box2">';
			$page .= '<span class="warning">'.t('BOX_WARN').'</span><br/>';
			$page .= t('LOGIN_BANN');
			$page .= '</div>';
				
			warquest_info($myusername.' login failed, user is banned!');	
			
			$pid = 0;
		
		} else { 
	
			/* Start session */
			$session = warquest_db_session_add($pid);
	
			/* Update member information. */
			$member = warquest_db_member($pid);
			$member->ip=$_SERVER["REMOTE_ADDR"];
			$member->prev_login = $member->last_login;
			$member->last_login = date("Y-m-d H:i:s");
			$member->auto_login = $auto_login;
		
			$browser = new Browser($version);
			$member->browser=$browser->getBrowser();
			$member->version=$browser->getVersion();
			$member->platform=$browser->getPlatform();
				
			warquest_db_member_update($member);
										
			/* Redirect to home page. */
			$mid = MENU_HOME;			
			$sid = PAGE_OVERVIEW;	
			$eid = 0;
		
			warquest_info($myusername.' login succesfull');
		
			/* Clear login data, if user logins */
			$page = "";	
		}
	} 
}

/**
 * Login Form
 */
function warquest_login_form() {

	/* input */
	global $myusername;
	global $mypassword;
	global $config;
	global $version;
	global $mid;
	global $sid;

	/* output */
	global $page;
	global $title;
	
	$title = t('LOGIN_MEMBER_TITLE');
	
	$page .= '<div class="box2">';
	$page .= '<table cellpadding="3" cellspacing="1">';
	
	$page .= '<tr>';
	$page .= '<td colspan="2">';
	$page .= '<strong>'.t('LOGIN_MEMBER_TITLE').'</strong>';
	$page .= '<br/><br/>';
	$page .= '</td>';	
	$page .= '</tr>';
		
	$page .= '<tr>';
	$page .= '<td width="80">'.t('LOGIN_USERNAME').':</td>';
	$page .= '<td><input name="myusername" type="text" id="myusername" value="'.$myusername;
	$page .= '" size="18" maxlength="'.$config["max_username_length"].'" ></td>';
	$page .= '</tr>';
		
	$page .= '<tr>';
	$page .= '<td>'.t('LOGIN_PASSWORD').':</td>';
	$page .= '<td><input name="mypassword" type="password" id="mypassword" size="18" ';
	$page .= 'maxlength="'.$config["max_password_length"].'">';	
	$page .= '</td>';
	$page .= '</tr>';
		
	$page .= '<tr>';
	$page .= '<td>&nbsp;</td>';
	$page .= '<td>';
	$page .= '<br/>';
	$page .= '<input type="hidden" name="token" value="'.warquest_token('mid='.$mid.'&sid='.$sid.'&eid=1&version='.$version).'" />';
	$page .= '<input type="submit" name="Submit" value="'.t('LINK_LOGIN').'">';
	$page .= '</td>';
	$page .= '</tr>';
	$page .= '</table>';
		
	$page .= '</div>';
	
	/* Set focus on first input element */
	$page .= '<script type="text/javascript" language="JavaScript">';
	$page .= 'document.forms[\'warquest\'].elements[\'myusername\'].focus();';
	$page .= '</script>';
}

function warquest_login_email_confirm() {

	/* input */
	global $action;
	
	/* output */	
	global $page;
	
	/* Validate email address */
	$tmp = preg_split('/-/', $action);

	switch ($tmp[0]) {

		case EVENT_VALID_EMAIL:

			$data = warquest_db_member($tmp[1]);
		
			if (isset($data->email_valid) && ($data->email_valid==0) && (md5($data->email)==$tmp[2]))  {
			
				$data->email_valid=1;
				warquest_db_member_update($data);
				
				/* Check if player is ban */		
				$page .= '<div class="box2">';
				$page .= '<span class="info">'.t('USER_EMAIL_VALID').'</span><br/>';	
				$page .= '</div>';
										
				warquest_info("Receive valid email confirmation for [".$data->email."]");					
			}
			break;
	}
}

/*
** ------------- 
** EVENT HANDLER
** -------------
*/

/** 
 * Handle login events
 */
function warquest_login() {

	/* input */
	global $sid;
	global $eid;
		
	/* Show login header content part */
	warquest_login_header();
	
	warquest_login_email_confirm();
		
	/* Process event */
	switch ($eid) {
	
		case 1: 	warquest_login_do();
					break;
					
		case 2:	/* Default Registration with 4 skill points */
					if (warquest_register_do(4)==1) {
						warquest_login_do();
					}
					break;
					
		case 3: 	warquest_email_do();
					break;
					
		case 4:  warquest_logout_do();
					break;
					
		case 5:	/* Special registration with 10 skill points bonus */
					if (warquest_register_do(10)==1) {
						warquest_login_do();
					}
					break;				
	}
				
	/* Page handler */
	switch ($sid) {
					
		case PAGE_LOGIN: 
					warquest_login_form();		
					warquest_client_overview();
					warquest_login_footer();
					break;
					
		case PAGE_REGISTER: 
					warquest_register_form();	
					warquest_client_overview();
					warquest_login_footer();
					break;
		
		case PAGE_RECOVER:
					warquest_recover_form();
					warquest_client_overview();
					warquest_login_footer();
					break;
													
		case PAGE_FACEBOOK:
					warquest_facebook_form();
					warquest_login_footer();
					break;				
					
		case PAGE_MAINTENANCE:
					warquest_maintenance_form();
					warquest_client_overview();
					warquest_login_footer();
					break;					
	}	
}				

/*
** ---------------------------------------------------------------- 
** THE END
** ----------------------------------------------------------------
*/
	
?>