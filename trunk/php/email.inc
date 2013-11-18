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
 * Send registrating email
 */
function warquest_register_mail($to, $username, $password) {

	/* input */
	global $config;
	
	$subject = 'Welcome to '.$config["applName"];
	
	$body  = 'Welcome to '.$config["applName"]."\r\n\r\n";
	$body .= 'Thanks you for registrating!'."\r\n\r\n";
	
	$body .= 'Your username = '.$username."\r\n";
	$body .= 'Your password = '.$password."\r\n";
	$body .= "\r\n";
	
	$body .= 'Please confirm your email address by clicking the following link'."\r\n";

	$body .= $config["base_url"].'?action='.EVENT_EMAIL_CONFIRM.'&key='.$id.'-'.md5($to)."\r\n\r\n";
	
	$body .= 'Visit '.$config["base_url"].' and login to continue the game.'."\r\n";

	$header  = 'From: '.$config["applName"]. '<'.$config['from_email'].">\r\n";

	if ($to!="") {
		@mail($to, $subject, $body, $header);
		warquest_info("Send email [".$to."] Welcome message");
	}
}

/** 
 * Send email address confirm mail 
 */
function warquest_confirm_email($to, $pid) {

	/* input */
	global $config;
		
	$subject = 'Confirm email address for '.$config["applName"];
	
	$body  = '<html>';
	$body .= '<body>';	
	$body .= warquest_image("other/WarQuest.png");
	$body .= '<br/>';	
	$body .= '<h1>'.$config["applName"].' Confirm Email</h1>';	
	$body .= '<p>';		
	$body .= 'Please confirm your email address by clicking the following link';
	$body .= '<br/>';	
	$body .= '<br/>';	
	$body .= $config["base_url"].'?action='.EVENT_VALID_EMAIL.'-'.$pid.'-'.md5($to);
	$body .= '</p>';	
	$body .= warquest_image("other/ad.png");	
	$body .= '</body>';		
	$body .= '</html>';
			
	$header = 'From: '.$config["applName"]. '<'.$config['from_email'].">\r\n";
	$header .= "MIME-Version: 1.0\r\n";
	$header .= "Content-Type: text/html; charset=ISO-8859-1\r\n";
	
	@mail($to, $subject, $body, $header);
		
	warquest_info("Send confirmation email to [".$to."]");		
}


/**
 * Send password recover email
 */
function warquest_recover_mail($to, $username, $password) {

	/* input */
	global $config;
	
	$subject = 'Password reset of '.$config["applName"];
	
	$body  = 'Your password is reset!'."\r\n\r\n";
	$body .= 'Your username = '.$username."\r\n";
	$body .= 'Your new password = '.$password."\r\n\r\n";
	$body .= 'Visit '.$config["base_url"].' and login to continue the game.'."\r\n";
		
	$header = 'From: '.$config["applName"]. '<'.$config['from_email'].">\r\n";

	@mail($to, $subject, $body, $header);
	warquest_info("Send email [".$to."] Password reset");
		
	@mail($config["from_email"], $subject, $body, $header);
	warquest_info("Send email [".$config["from_email"]."] Password reset");
				
	warquest_info($myemail.' email reset succesfull');
}

/** 
 * Send comment by mail
 */
function warquest_comment_mail($pid, $comment) {
	
	/* input */
	global $config;
	global $player;
	global $other;
	
	$data = warquest_db_member($pid);
		
	$subject = $config["applName"].' comment!';

	$body  = $player->name.' has send you the following comment:';
	$body .= "\r\n\r\n";
	$body .= $comment;
	$body .= "\r\n\r\n";
	$body .= 'Visit '.$config["base_url"].' to reply!'."\r\n";
		
	$header = 'From: '.$config["applName"]. '<'.$config['from_email'].">\r\n";

	if ( ($data->notification_comment==1) && ($data->email_valid==1) ) {
		@mail($data->email, $subject, $body, $header);
		warquest_info("Send email [".$data->email."] ".$comment);
	}
}

/** 
 * Send allicance invite mail 
 */
function warquest_alliance_invite_mail() {
	
	/* input */
	global $other;
	global $config;
	global $player;
	
	$data = warquest_db_member($other->pid);
			
	$subject = $config["applName"].' alliance request';

	$body  = $player->name.' has send you alliance request!';
	$body .= "\r\n\r\n";
	$body .= 'Visit '.$config["base_url"].', login and accept or reject the request.'."\r\n";
		
	$header = 'From: '.$config["applName"]. '<'.$config['from_email'].">\r\n";

	if ( ($data->notification_alliance==1) && ($data->email_valid==1) ) {
		@mail($data->email, $subject, $body, $header);
		warquest_info("Send email [".$data->email."] alliance request");
	}
}

/** 
 * Send allicance reject mail 
 */
function warquest_alliance_reject_mail() {
	
	/* input */
	global $other;
	global $config;
	global $player;
	global $other;

	$data = warquest_db_member($other->pid);
		
	$subject = $config["applName"].' alliance rejected.';

	$body  = $player->name.' has rejected your alliance request!';
	$body .= "\r\n\r\n";
	$body .= 'Visit '.$config["base_url"].' to continue the game.'."\r\n";
		
	$header = 'From: '.$config["applName"]. '<'.$config['from_email'].">\r\n";

	if ( ($data->notification_alliance==1) && ($data->email_valid==1) ) {
		@mail($data->email, $subject, $body, $header);
		warquest_info("Send email [".$data->email."] alliance rejected");
	}
}

/** 
 * Send allicance drop mail 
 */
function warquest_alliance_drop_mail() {
	
	/* input */
	global $other;
	global $config;
	global $player;
	global $other;

	$data = warquest_db_member($other->pid);
		
	$subject = $config["applName"].' alliance dropped.';

	$body  = $player->name.' has drop your alliance!';
	$body .= "\r\n\r\n";
	$body .= 'Visit '.$config["base_url"].' to continue the game.'."\r\n";
		
	$header = 'From: '.$config["applName"]. '<'.$config['from_email'].">\r\n";

	if ( ($data->notification_alliance==1) && ($data->email_valid==1) ) {
		@mail($data->email, $subject, $body, $header);
		warquest_info("Send email [".$data->email."] alliance rejected");
	}
}

/** 
 * Send allicance accept mail 
 */
function warquest_alliance_accept_mail() {
	
	/* input */
	global $other;
	global $config;
	global $player;
	
	$data = warquest_db_member($other->pid);
		
	$subject = $config["applName"].' alliance accepted.';

	$body  = $player->name.' has accepted your alliance request!';
	$body .= "\r\n\r\n";
	$body .= 'Visit '.$config["base_url"].' to continue the game.'."\r\n";
		
	$header = 'From: '.$config["applName"]. '<'.$config['from_email'].">\r\n";

	if ( ($data->notification_alliance==1) && ($data->email_valid==1) ) {
		@mail($data->email, $subject, $body, $header);
		warquest_info("Send email [".$data->email."] alliance accepted");
	}
}

?>
