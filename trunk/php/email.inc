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

/** 
 * Format email body
 */
function warquest_email_layout($subject, $content) {

	/* input */
	global $config;
	
	$tmp  = '<html>';
	$tmp .= '<body>';	
	
	$tmp .= '<a href='.$config["base_url"].'>';
	$tmp .= '<img src="'.$config["base_url"].'/images/other/ad.png" />';
	$tmp .= '</a>';
	
	$tmp .= '<h2>'.$subject.'</h2>';	
	
	$tmp .= '<p>';		
	$tmp .= $content;
	$tmp .= '</p>';	

	$tmp .= '<p>';
	$tmp .= 'Best Regards,<br/>';
	$tmp .= 'admin<br/>';
	$tmp .= '</p>';
	
	$tmp .= '<p>';
	for ($i=0; $i<10; $i++) {
		$tmp .= '&nbsp;';
	}
	$tmp .= '<i>'.t('COPYRIGHT').'</i>';
	$tmp .= '</p>';
	
	$tmp .= '<a href='.$config["base_url"].'>';
	$tmp .= '<img src="'.$config["base_url"].'/images/other/ad2.png" />';
	$tmp .= '</a>';
	
	$tmp .= '</body>';		
	$tmp .= '</html>';
	
	return $tmp;
}

/** 
 * Send email address confirm mail 
 */
function warquest_confirm_email($pid) {

	/* input */
	global $config;
	
	$player = warquest_db_player($pid);
	$member = warquest_db_member($pid);
	
	if (isset($player->pid)) {
		
		$subject = 'Confirm '.$config["applName"].' email address';
			
		$content = 'Dear '.$player->name.',';
		$content .= '<br/><br/>';
		$content .= 'Thanks for playing '.$config["applName"].'. ';
		$content .= 'Please confirm your email address by clicking ';
		$content .= '<a href='.$config["base_url"].'?action='.EVENT_VALID_EMAIL.'-'.$player->pid.'-'.md5($member->email).'>here</a>.';

		$body = warquest_email_layout($subject, $content);
				
		$header  = 'From: '.$config["applName"]. '<'.$config['from_email'].">\r\n";
		$header .= "MIME-Version: 1.0\r\n";
		$header .= "Content-Type: text/html; charset=ISO-8859-1\r\n";
	
		@mail($member->email, $subject, $body, $header);
	
		warquest_info('Sent confirmation email to '.$member->email);		
	}
}

/**
 * Send registrating email
 */
function warquest_register_mail($pid, $password) {

	/* input */
	global $config;
	
	$player = warquest_db_player($pid);
	$member = warquest_db_member($pid);
	
	if (isset($player->pid)) {
		
		$subject = 'Welcome to '.$config["applName"];
		
		$content = 'Dear '.$player->name.',';
		$content .= '<br/><br/>';
		$content  = 'Thanks you for registrating!';	
		$content .= '<br/><br/>';	
		$content .= 'Your username = <b>'. $member->username.'</b>';
		$content .= '<br/>';
		$content .= 'Your password = <b>'. $password.'</b>';
		$content .= '<br/><br/>';
		$content .= 'Please confirm your email address by clicking ';
		$content .= '<a href='.$config["base_url"].'?action='.EVENT_VALID_EMAIL.'-'.$player->pid.'-'.md5($member->email).'>here</a>.';
		$content .= '<br/><br/>';
		$content .= 'Visit <a href="'.$config["base_url"].'">'.$config["base_url"].'</a> to continue the game.';
		
		$body = warquest_email_layout($subject, $content);
	
		$header  = 'From: '.$config["applName"]. '<'.$config['from_email'].">\r\n";
		$header .= "MIME-Version: 1.0\r\n";
		$header .= "Content-Type: text/html; charset=UTF-8\r\n";

		@mail($member->email, $subject, $body, $header);
		
		warquest_info('Sent registration email to '.$member->email);
	}
}

/**
 * Send password recover email
 */
function warquest_recover_mail($pid, $password) {

	/* input */
	global $config;

	$player = warquest_db_player($pid);
	$member = warquest_db_member($pid);
	
	if (isset($player->pid)) {
	
		$subject = $config["applName"].' password reset';
	
		$content = 'Dear '.$player->name.',';
		$content .= '<br/><br/>';
		$content  = 'Your password is reset!';
		$content .= "<br/><br/>";
		$content .= 'Your username = <b>'.$member->username.'</b>';
		$content .= "<br/>";
		$content .= 'Your new password = <b>'.$password.'</b>';
		$content .= "<br/><br/>";
		$content .= 'Visit <a href="'.$config["base_url"].'">'.$config["base_url"].'</a> to continue the game.';
		
		$body = warquest_email_layout($subject, $content);
		
		$header  = 'From: '.$config["applName"]. '<'.$config['from_email'].">\r\n";
		$header .= "MIME-Version: 1.0\r\n";
		$header .= "Content-Type: text/html; charset=UTF-8\r\n";

		@mail($member->email, $subject, $body, $header);
		warquest_info('Sent password reset email to '.$member->email);
		
		@mail($config["from_email"], $subject, $body, $header);
		warquest_info('Sent password reset email to '.$config["from_email"]);		
	}
}

/** 
 * Send comment by mail
 */
function warquest_comment_mail($pid, $comment, $name) {
	
	/* input */
	global $config;
	
	$player = warquest_db_player($pid);
	$member = warquest_db_member($pid);
	
	if ( ($member->notification_comment==1) && ($member->email_valid==1) ) {
	
		$subject = $config["applName"].' comment!';

		$content  = 'Dear '.$player->name.',';
		$content .= '<br/><br/>';
		$content .= $name.' has send you the following comment:';
		$content .= "<br/><br/>";
		$content .= '<table border="2">';
		$content .= '<tr>';
		$content .= '<td width="300">';
		$content .= '<pre>';
		$content .= $comment;
		$content .= '</pre>';
		$content .= '</td>';
		$content .= '</tr>';
		$content .= '</table>';
		$content .= "<br/>";
		$content .= 'Visit <a href="'.$config["base_url"].'">'.$config["base_url"].'</a> to reply.';
	
		$body = warquest_email_layout($subject, $content);
	
		$header  = 'From: '.$config["applName"]. '<'.$config['from_email'].">\r\n";
		$header .= "MIME-Version: 1.0\r\n";
		$header .= "Content-Type: text/html; charset=UTF-8\r\n";
	
		@mail($member->email, $subject, $body, $header);
		warquest_info('Sent comment email to '.$member->email);
	}
}

/** 
 * Send allicance invite mail 
 */
function warquest_alliance_invite_mail($pid, $name) {
	
	/* input */
	global $config;

	$player = warquest_db_player($pid);
	$member = warquest_db_member($pid);
	
	if ( ($member->notification_alliance==1) && ($member->email_valid==1) ) {
	
		$subject = $config["applName"].' alliance request';

		$content  = 'Dear '.$player->name.',';
		$content .= '<br/><br/>';
		$content .= $name.' has send you alliance request!';
		$content .= "<br/><br/>";
		$content .= 'Visit <a href="'.$config["base_url"].'">'.$config["base_url"].'</a> to accept or reject this request.';
	
		$body = warquest_email_layout($subject, $content);
	
		$header  = 'From: '.$config["applName"]. '<'.$config['from_email'].">\r\n";
		$header .= "MIME-Version: 1.0\r\n";
		$header .= "Content-Type: text/html; charset=UTF-8\r\n";
	
		@mail($member->email, $subject, $body, $header);
		warquest_info('Sent alliance invite email to '.$member->email);
	}
}

/** 
 * Send allicance reject mail 
 */
function warquest_alliance_reject_mail($pid, $name) {
	
	/* input */
	global $config;

	$player = warquest_db_player($pid);
	$member = warquest_db_member($pid);
	
	if ( ($member->notification_alliance==1) && ($member->email_valid==1) ) {
	
		$subject = $config["applName"].' alliance rejected';

		$content  = 'Dear '.$player->name.',';
		$content .= '<br/><br/>';
		$content .= $name.' has rejected your alliance request!';
		$content .= "<br/><br/>";
	   $content .= 'Visit <a href="'.$config["base_url"].'">'.$config["base_url"].'</a> to continue the game.';
		
		$body = warquest_email_layout($subject, $content);
		
		$header  = 'From: '.$config["applName"]. '<'.$config['from_email'].">\r\n";
		$header .= "MIME-Version: 1.0\r\n";
		$header .= "Content-Type: text/html; charset=UTF-8\r\n";
	
		@mail($member->email, $subject, $body, $header);
		warquest_info('Sent alliance reject email to '.$member->email);
	}
}

/** 
 * Send allicance drop mail 
 */
function warquest_alliance_drop_mail($pid, $name) {
	
	/* input */
	global $config;

	$player = warquest_db_player($pid);
	$member = warquest_db_member($pid);
		
	if ( ($member->notification_alliance==1) && ($member->email_valid==1) ) {
		
		$subject = $config["applName"].' alliance dropped';

		$content  = 'Dear '.$player->name.',';
		$content .= '<br/><br/>';
		$content .= $name.' has drop your alliance!';
		$content .= "<br/><br/>";
		$content .= 'Visit <a href="'.$config["base_url"].'">'.$config["base_url"].'</a> to continue the game.';
	
		$body = warquest_email_layout($subject, $content);
		
		$header  = 'From: '.$config["applName"]. '<'.$config['from_email'].">\r\n";
		$header .= "MIME-Version: 1.0\r\n";
		$header .= "Content-Type: text/html; charset=UTF-8\r\n";
	
		@mail($member->email, $subject, $body, $header);
		warquest_info('Sent alliance drop email to '.$member->email);
	}
}

/** 
 * Send allicance accept mail 
 */
function warquest_alliance_accept_mail($pid, $name) {
	
	/* input */
	global $config;

	$player = warquest_db_player($pid);
	$member = warquest_db_member($pid);
	
	if ( ($member->notification_alliance==1) && ($member->email_valid==1) ) {	
	
		$subject = $config["applName"].' alliance accepted';

		$content  = 'Dear '.$player->name.',';
		$content .= '<br/><br/>';		
		$content .= $name.' has accepted your alliance request!';
		$content .= "<br/><br/>";
		$content .= 'Visit <a href="'.$config["base_url"].'">'.$config["base_url"].'</a> to continue the game.';
		
		$body = warquest_email_layout($subject, $content);
		
		$header  = 'From: '.$config["applName"]. '<'.$config['from_email'].">\r\n";
		$header .= "MIME-Version: 1.0\r\n";
		$header .= "Content-Type: text/html; charset=UTF-8\r\n";
	
		@mail($member->email, $subject, $body, $header);
		warquest_info('Sent alliance accept email to '.$member->email);
	}
}

?>
