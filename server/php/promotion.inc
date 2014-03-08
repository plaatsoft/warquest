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
** ---------------
** Post Parameters
** ---------------
*/

$email = warquest_post('email', '');

/*
** --------------
** ACTIONS
** --------------
*/

function warquest_promotion_invite_do() {

	/* input */
	global $player;
	global $config;	
	global $email;
	
	/* output */
	global $output;	
	
	$query = 'select id from invite where pid='.$player->pid;
	$result = warquest_db_query($query);	
	$count = warquest_db_num_rows($result);
 
	if (validate_email($email) ) {
	
		/* Invalid email address */
		$message = t('EMAIL_INVALID');
		$output->popup .= warquest_box_icon("warning", $message);
		
	} else if (!validate_dns($email)) {
	
		/* Invalid email domain name */
		$message = t('EMAIL_DOMAIN_INVALID');
		$output->popup .= warquest_box_icon("warning", $message);
		
	} else if (warquest_db_invite_check($email)>0) {
	
		/* Email address is already used in the past */
		$message = t('PROMOTION_INVITE_KNOWN', $email);
		$output->popup .= warquest_box_icon("warning", $message);
	
	} else if ($count>9) {
	
		/* Maxmium amount of invites sent */
		$message = t('PROMOTION_MAX_INVITE', $email);
		$output->popup .= warquest_box_icon("warning", $message);
	
	} else {
	
		/* Add invite request in database */
		warquest_db_invite_insert($email, 0, $player->pid);
		
		/* Send invite email */
		warquest_promotion_invite_mail($player->pid, $email);
		
		$message = t('PROMOTION_INVITE_SENT', $email);
		$output->popup .= warquest_box_icon("info", $message);	
	}
}

/*
** --------------
** GUI
** --------------
*/

function warquest_promotion_form() {

	/* input */	
	global $mid;
	global $sid;
	global $cid;
	global $email;
	global $player;
			
	/* output */
	global $page;
	global $output;
			
	$output->title = t('PROMOTION_TITLE');
			
	/* Invite friends by email */
	$page .= '<div class="subparagraph">';
	$page .= t('PROMOTION_INVITE');
	$page .= '</div>';
	
	$lid = 25;
	
	if ($player->lid < $lid) {
		
		$message = t('PROMOTION_LOCKED', $lid);	
		$page .= warquest_box_icon('locked', $message);
		
	} else {
	
		$page .= '<div class="box">';
	
		$page .= t('LOGIN_EMAIL').' ';
		$page .= '<td><input name="email" type="text" size="50" maxlength="120" value="'.$email.'" id="email"> ';
		$page .= '<input type="hidden" name="token" value="'.warquest_token('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_PROMOTION_INVITE).'">';
		$page .= '<input type="submit" name="Submit" id="do" value="'.t('LINK_INVITE').'">';
		$page .= '</td>';
		$page .= '</tr>';
		
		$page .= '</table>';
	
		$page .= '</div>';
		
		$page .= '<div class="note">';
		$page .= t('PROMOTION_INVITE_NOTE', gold_format(500));
		$page .= '</div>';
		
		/* Facebook */
		$page .= '<div class="subparagraph">';
		$page .= t('PROMOTION_FACEBOOK');
		$page .= '</div>';
			
		$page .= '<div class="box">';			
			
		$page .= '<div id="fb-root"></div>';
		
		$page .= "<script type='text/javascript'>
window.fbAsyncInit = function() {
 FB.init({appId: '146129318831064', status: true, cookie: true, xfbml: true});
 FB.Event.subscribe('edge.create', function(href, widget) {
 
	if (window.XMLHttpRequest) {
		// code for IE7+, Firefox, Chrome, Opera, Safari
		xmlhttp=new XMLHttpRequest();
	} else {
		// code for IE6, IE5
		xmlhttp=new ActiveXObject('Microsoft.XMLHTTP');
	}
	
	xmlhttp.open('POST', href+'/' ,true);
	xmlhttp.setRequestHeader('Content-type','application/x-www-form-urlencoded');
	xmlhttp.send('mid=".MENU_SERVICE."&id=".$player->pid."&eid=3');
	
	});
};

(function(d, s, id){
     var js, fjs = d.getElementsByTagName(s)[0];
     if (d.getElementById(id)) {return;}
     js = d.createElement(s); js.id = id;
     js.src = '//connect.facebook.net/en_US/all.js';
     fjs.parentNode.insertBefore(js, fjs);
   }(document, 'script', 'facebook-jssdk'));
</script>";

		$page .= '<div class="fb-like" data-href="http://www.facebook.com/WarQuest" data-send="true" colorscheme="dark" data-width="450" data-show-faces="true"></div>';
		$page .= '</div>';
	
		$page .= '<div class="note">';
		$page .= t('PROMOTION_FACEBOOK_NOTE', gold_format(500));
		$page .= '</div>';
	}
}

/*
** --------------
** HANDLER
** --------------
*/

function warquest_promotion() {

	/* input */
	global $eid;
	global $sid;
				
	/* Event Handler */
	switch ($eid) {
				
		case EVENT_PROMOTION_INVITE:
			warquest_promotion_invite_do();
			break;	
	}
	
	/* Page handler */
	switch ($sid) {

		case PAGE_PROMOTION:
					warquest_promotion_form();
					break;
	}				  
}

/*
** ---------------------------------------------------------------- 
** THE END
** ----------------------------------------------------------------
*/

?>
