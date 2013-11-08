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
** Invite
** ---------------------
*/

function warquest_alliance_invite_mail() {
	
	global $other;
	global $config;
	global $player;
	
	$data = warquest_db_member($other->pid);
			
	$subject = $config["applName"].' alliance request';

	$body = $player->name.' has send you alliance request!'."\r\n\r\n";;
	$body .= 'Visit '.$config["base_url"].', login and accept or reject the request.'."\r\n";
		
	$header = 'From: '.$config["applName"]. '<'.$config['from_email'].">\r\n";

	if (($data->notification_alliance==1) && ($data->email!="")) {
		@mail($data->email, $subject, $body, $header);
		warquest_info("Send email [".$data->email."] alliance request");
	}
}

function warquest_alliance_invite_do() {

	/* output */ 
	global $player;
	global $other;
	global $popup;
	global $config;
	
	$query  = 'select pid1 from player_player where ';
	$query .= '(pid1='.$player->pid.' and pid2='.$other->pid.') or '; 
	$query .= '(pid1='.$other->pid.' and pid2='.$player->pid.')'; 
	$result = warquest_db_query($query);	
	
	$count=warquest_db_num_rows($result);
	
	if (($player->alliance + $player->invite) >= $player->lid*$config["max_ally_factor"]) {
		
		/* Skip action. Max size */
		
	} else if ($count==0) {
	
		warquest_db_alliance_insert($player->pid, $other->pid, 0);	

		$player->invite = warquest_db_invite_size($player->pid);				
		$other->invite = warquest_db_invite_size($other->pid);
	
		warquest_alliance_invite_mail();
		
		$message = t('ALLIANCE_INVITATION', $other->name);
		$popup .= warquest_box_icon("info", $message);
	}
}

/**
 * Invite friend form
 */
function warquest_alliance_invite_form() {

	/* input */
	global $config;
	global $player;
	global $mid;
	global $sid;
	global $myemail;
	global $offset;
	
	/* output */
	global $page;
	global $title;
	global $sort;
	
	$title = t('ALLIANCE_INVITE_TITLE1');
			
	$page .= '<div class="subparagraph">';
	$page .= t('ALLIANCE_INVITE_TITLE2', $player->alliance, $player->invite);
	$page .= '</div>';

	if ($player->lid==0) {
		
		$page .= '<br/>';
	
		$title = "";
		$message = '<table>';
		$message .= '<tr>';
		$message .= '<td>';
		$message .= warquest_image("other/unlock.png");
		$message .= '</td>';
		$message .= '<td>';
		$message .= t('ALLIANCE_LOCKED');
		$message .= '</td>';
		$message .= '</tr>';
		$message .= '</table>';

		$page .= warquest_box($title, $message);
	
	} else if (($player->alliance + $player->invite) >= $player->lid*$config["max_ally_factor"]) {
		
		$message = t('ALLIANCE_MAXIMUM', $player->lid * $config["max_ally_factor"]);
		$page .= warquest_box_icon("info", $message);
	
	} else {
		
		$limit = 50;	
		
		$query  = 'select pid from player where pid not in ';
		$query .= '(select pid2 from player_player where pid1='.$player->pid.') and pid!='.$player->pid.' ';
		$query .= 'and (alliance+invite)<(lid*'.$config["max_ally_factor"].') ';
		$result = warquest_db_query($query);	 
		$total=warquest_db_num_rows($result);
		
		/* Show all not recruited players */
		$query  = 'select pid, name, country, lid, experience, alliance, request_date ';
		$query .= 'from player where pid not in ';
		$query .= '(select pid2 from player_player where pid1='.$player->pid.') and pid!='.$player->pid.' ';
		$query .= 'and (alliance+invite)<(lid*'.$config["max_ally_factor"].') ';
	
		switch ($sort) {
		
			case 1:
				$query .= 'order by country asc ';
				break;
				
			case 2:
				$query .= 'order by name asc ';
				break;
			
			default:	
			case 3:
				$query .= 'order by request_date desc ';
				break;
				
			case 4:
				$query .= 'order by lid desc, experience desc ';
				break;

			case 5:
				$query .= 'order by experience desc ';
				break;
				
			case 6:
				$query .= 'order by alliance desc ';
				break;		
		}
		
		$query .= 'limit '.$offset.','.$limit;
		$result = warquest_db_query($query);	
	
		$page .= '<div class="box">';
		
		$page .= warquest_page_control($offset, $limit, $total, 1, '&sort='.$sort);
	
		$page .= '<table>';
		
		$page .= '<tr>';
		$page .= '<td width="50"><b>';
		$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&sort=1', t('GENERAL_CNTRY'));
		$page .= '</b></td>';
		
		$page .= '<td width="130"><b>';
		$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&sort=2', t('GENERAL_PLAYER'));
		$page .= '<b/></td>';
		
		$page .= '<td width="70"><b>';
		$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&sort=3', t('GENERAL_ACTIVE'));
		$page .= '<b/></td>';
				
		$page .= '<td width="50"><b>';
		$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&sort=4', t('GENERAL_LEVEL'));
		$page .= '<b/></td>';
		
		$page .= '<td width="90"><b>';
		$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&sort=5', t('GENERAL_EXP'));
		$page .= '<b/></td>';
		
		$page .= '<td width="60"><b>';
		$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&sort=6', t('GENERAL_ALLIANCE'));
		$page .= '<b/></td>';
		
		$page .= '<td width="50">';
		$page .= '<b></b>';
		$page .= '</td>';
		$page .= '</tr>';
		
		$count=0;
	
		while ($data=warquest_db_fetch_object($result)) {
		
			$page .= '<tr>';
			$page .= '<td>';
			$page .= warquest_flag_image($data->country);
			$page .= '</td>';
			$page .= '<td>';
			$page .= warquest_link('mid='.$mid.'&sid='.PAGE_PROFILE.'&oid='.$data->pid, $data->name);
			$page .= '</td>';
			$page .= '<td>';
			$page .= warquest_ui_ago($data->request_date);
			$page .= '</td>';					
			$page .= '<td>';
			$page .= $data->lid;
			$page .= '</td>';		
			$page .= '<td>';
			$page .= number_format($data->experience,0,",",".");
			$page .= '</td>';			
			$page .= '<td>';
			$page .= $data->alliance;
			$page .= '</td>';			
			$page .= '<td>';
			$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&oid='.$data->pid.'&eid=1&sort='.$sort.'&offset='.$offset, t('LINK_RECRUIT'), "recuit".$count++);
			$page .= '</td>';
			$page .= '</tr>';
		}
		
		$page .= '</table>';
		$page .= warquest_page_control($offset, $limit, $total, 0, '&sort='.$sort);	
		$page .= '</div>';			
	} 

	$page .= '<div class="note">';
	$page .= t('ALLIANCE_INVITE_NOTE', $player->lid * $config["max_ally_factor"]);
   $page .= '</div>';		
	
	$page .= warquest_show_ads();
}

/*
** ---------------------
** Pending and Approved
** ---------------------
*/

function warquest_alliance_drop_mail() {
	
	global $other;
	global $config;
	global $player;
	global $other;

	$data = warquest_db_member($other->pid);
		
	$subject = $config["applName"].' alliance rejected.';

	$body = $player->name.' has drop your alliance!'."\r\n\r\n";;
	$body .= 'Visit '.$config["base_url"].' to continue the game.'."\r\n";
		
	$header = 'From: '.$config["applName"]. '<'.$config['from_email'].">\r\n";

	if (($data->notification_alliance==1) && ($data->email!="")) {
		@mail($data->email, $subject, $body, $header);
		warquest_info("Send email [".$data->email."] alliance rejected");
	}
}
						
function warquest_alliance_drop_do() {

	/* input */	
	global $player;
	global $other;
	
		/* output */
	global $popup;
	
	warquest_db_alliance_delete($player->pid, $other->pid);
	warquest_db_alliance_delete($other->pid, $player->pid);

	/* Update attack and defense value */
	$player->alliance = warquest_db_alliance_size($player->pid);
	$player->invite = warquest_db_invite_size($player->pid);
	
	$other->alliance = warquest_db_alliance_size($other->pid);
	$other->invite = warquest_db_invite_size($other->pid);
		
	warquest_alliance_reject_mail();
	
	$message = t('ALLIANCE_DROP', $other->name);
	$popup .= warquest_box_icon("info", $message);
}

function warquest_alliance_reject_mail() {
	
	/* input */
	global $other;
	global $config;
	global $player;
	global $other;

	$data = warquest_db_member($other->pid);
		
	$subject = $config["applName"].' alliance rejected.';

	$body = $player->name.' has rejected your alliance request!'."\r\n\r\n";;
	$body .= 'Visit '.$config["base_url"].' to continue the game.'."\r\n";
		
	$header = 'From: '.$config["applName"]. '<'.$config['from_email'].">\r\n";

	if (($data->notification_alliance==1) && ($data->email!="")) {
		@mail($data->email, $subject, $body, $header);
		warquest_info("Send email [".$data->email."] alliance rejected");
	}
}
						
function warquest_alliance_reject_do() {

	/* input */
	global $player;
	global $other;
	
	/* output */
	global $popup;
	
	warquest_db_alliance_delete($player->pid, $other->pid);
	warquest_db_alliance_delete($other->pid, $player->pid);

	/* Update attack and defense value */
	$player->alliance = warquest_db_alliance_size($player->pid);
	$player->invite = warquest_db_invite_size($player->pid);
	
	$other->alliance = warquest_db_alliance_size($other->pid);
	$other->invite = warquest_db_invite_size($other->pid);
		
	warquest_alliance_reject_mail();
	
	$message = t('ALLIANCE_REJECT', $other->name);
	$popup .= warquest_box_icon("info", $message);
}

function warquest_alliance_accept_mail() {
	
	/* input */
	global $other;
	global $config;
	global $player;
	
	$data = warquest_db_member($other->pid);
		
	$subject = $config["applName"].' alliance accepted.';

	$body = $player->name.' has accepted your alliance request!'."\r\n\r\n";
	$body .= 'Visit '.$config["base_url"].' to continue the game.'."\r\n";
		
	$header = 'From: '.$config["applName"]. '<'.$config['from_email'].">\r\n";

	if (($data->notification_alliance==1) && ($data->email!="")) {
		@mail($data->email, $subject, $body, $header);
		warquest_info("Send email [".$data->email."] alliance accepted");
	}
}
			
function warquest_alliance_accept_do() {

	/* output */
	global $player;
	global $other;
	
	/* output */
	global $popup;
	
	$query  = 'select pid1 from player_player where pid1='.$player->pid.' and pid2='.$other->pid;
	$result = warquest_db_query($query);	
	$count=warquest_db_num_rows($result);
	
	if ($count==0) {
		/* Create alliance connection $player -> $other */
		warquest_db_alliance_insert($player->pid, $other->pid, 1);
	}
	warquest_db_alliance_update($other->pid, $player->pid, 1);
		
	/* Update attack and defense value */
	$player->alliance = warquest_db_alliance_size($player->pid);
	$player->invite = warquest_db_invite_size($player->pid);
	
	$other->alliance = warquest_db_alliance_size($other->pid);
	$other->invite = warquest_db_invite_size($other->pid);
		
	warquest_alliance_accept_mail();
	
	$message = t('ALLIANCE_ACCEPT',$other->name); 
	$popup .= warquest_box_icon("info", $message);
}

function warquest_alliance_accepted_form() {

	/* input */	
	global $mid;
	global $sid;
	global $player;
	global $other;
	global $offset;
		
	/* output */
	global $page;
	global $title;
	
	$title = t('ALLIANCE_ACCEPT_TITLE1');

	$count=1;
	
	/* Get approved alliance player */
	$page .= '<div class="subparagraph">';
	$page .= t('ALLIANCE_ACCEPT_TITLE2', $player->alliance, $player->invite);
	$page .= '</div>';

	$page .= '<div class="box">';
	$page .= '<table>';
	
	$page .= '<tr>';
	$page .= '<td width="40">';
	$page .= '<b>'.t('GENERAL_NUMBER').'</b>';
	$page .= '</td>';
	$page .= '<td width="40">';
	$page .= '<b></b>';
	$page .= '</td>';
	$page .= '<td width="150">';
	$page .= '<b>'.t('GENERAL_PLAYER').'</b>';
	$page .= '</td>';
	$page .= '<td width="100">';
	$page .= '<b>'.t('GENERAL_LEVEL').'</b>';
	$page .= '</td>';
	$page .= '<td width="100">';
	$page .= '<b>'.t('GENERAL_APPROVED').'</b>';	
	$page .= '</td>';
	$page .= '<td width="90">';
	$page .= '</td>';
	$page .= '<td width="90">';
	$page .= '</td>';
	$page .= '</tr>';
		
	/* Your Self */
	$page .= '<tr>';
	$page .= '<td>';
	$page .= $count++;
	$page .= '</td>';
	$page .= '<td>';
	$page .= warquest_flag_image($player->country);
	$page .= '</td>';
	$page .= '<td>';
	$page .= warquest_link('mid='.$mid.'&sid='.PAGE_PROFILE.'&oid='.$player->pid, $player->name);
	$page .= '</td>';
	$page .= '<td>';
	$page .= $player->lid;
	$page .= '</td>';
	$page .= '<td>';
	$page .= t('GENERAL_YES');
	$page .= '</td>';		
	$page .= '<td>';
	$page .= '</td>';
	$page .= '<td>';
	$page .= '</td>';
	$page .= '</tr>';
	
	$limit = 50;	
		
	$query = 'select pid1 from player_player where pid1='.$player->pid.' and approved=1';
	$result = warquest_db_query($query);	 
	$total = warquest_db_num_rows($result);
		
	/* Get approved alliance players */
	$query  = 'select b.country, b.name, b.lid, a.pid1, a.pid2, a.approved ';
	$query .= 'from player_player a, player b where b.pid=a.pid2 and a.pid1='.$player->pid.' '; 
	$query .= 'and a.approved=1 order by b.lid desc, b.pid ';
	$query .= 'limit '.$offset.','.$limit;
	$result = warquest_db_query($query);	 
	
	$size=warquest_db_num_rows($result);
	
	$page .= warquest_page_control($offset, $limit, $total, 1);
	
	$count = $offset+2;
	
	if ($size>0) {
	
		$page .= '<tr>';
		$page .= '<td colspan="7">';
		$page .= '<hr>';
		$page .= '</td>';
		$page .= '</tr>';
	
		while ($data=warquest_db_fetch_object($result)) {
	
			$page .= '<tr>';
			$page .= '<td>';
			if ($data->approved==1) {
				$page .= $count++;
			}
			$page .= '</td>';
			$page .= '<td>';
			$page .= warquest_flag_image($data->country);
			$page .= '</td>';
			$page .= '<td>';
			$page .= warquest_link('mid='.$mid.'&sid='.PAGE_PROFILE.'&oid='.$data->pid2, $data->name);
			$page .= '</td>';
			$page .= '<td>';
			$page .= $data->lid;
			$page .= '</td>';
			$page .= '<td>';
			if ($data->approved==0) {
				$page .= t('GENERAL_NO');
			} else {
				$page .= t('GENERAL_YES');
			}
			$page .= '</td>';		
			$page .= '<td>';
			$page .= '</td>';
			$page .= '<td>';
			$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&oid='.$data->pid2.'&eid=4&offset='.$offset, t('LINK_DROP') ,"drop".$count);
			$page .= '</td>';
			$page .= '</tr>';
		}
	}
		
	$page .= '</table>';
	$page .= warquest_page_control($offset, $limit, $total, 0);	
	$page .= '</div>';
	
	$page .= '<div class="note">';
	$page .= t('ALLIANCE_NOTE');
   $page .= '</div>';	
	
	$page .= warquest_show_ads();
}

function warquest_alliance_pending_form() {

	/* input */	
	global $mid;
	global $sid;
	
	global $player;
	global $other;
		
	/* output */
	global $page;
	global $title;
	
	$title = t('ALLIANCE_PENDING_TITLE1');

	$count = 1;
	$flag = 0;
	$tmp1 = "";
	$tmp2 = "";
	
	/* Get pending alliance player */
	$page .= '<div class="subparagraph">';
	$page .= t('ALLIANCE_PENDING_TITLE2', $player->alliance, $player->invite);
	$page .= '</div>';

	/* Show not approved alliance */
	$query  = 'select b.country, b.name, b.lid, a.pid1, a.pid2, a.approved ';
	$query .= 'from player_player a, player b where a.pid1=b.pid and a.pid2='.$player->pid.' '; 
	$query .= 'and a.approved=0';
	$result = warquest_db_query($query);	 
	
	$size=warquest_db_num_rows($result);
	
	if ($size>0) {
	
		$flag = 1;
			
		while ($data=warquest_db_fetch_object($result)) {
		
			$tmp1 .= '<tr>';
			
			$tmp1 .= '<td>';
			$tmp1 .= $count++;		
			$tmp1 .= '</td>';
			
			$tmp1 .= '<td>';
			$tmp1 .= warquest_flag_image($data->country);
			$tmp1 .= '</td>';
			
			$tmp1 .= '<td>';
			$tmp1 .= warquest_link('mid='.$mid.'&sid='.PAGE_PROFILE.'&oid='.$data->pid1, $data->name);
			$tmp1 .= '</td>';
			
			$tmp1 .= '<td>';
			$tmp1 .= $data->lid;
			$tmp1 .= '</td>';
			
			$tmp1 .= '<td>';
			$tmp1 .= t('GENERAL_NO');
			$tmp1 .= '</td>';	
	
			$tmp1 .= '<td>';
			$tmp1 .= warquest_link('mid='.$mid.'&sid='.$sid.'&oid='.$data->pid1.'&eid=3', t('LINK_REJECT'), "reject");
			$tmp1 .= '</td>';
			
			$tmp1 .= '<td>';
			$tmp1 .= warquest_link('mid='.$mid.'&sid='.$sid.'&oid='.$data->pid1.'&eid=2', t('LINK_ACCEPT'), "accept");
			$tmp1 .= '</td>';
			
			$tmp1 .= '</tr>';
		}
		
		$tmp1 .= '<tr>';
		$tmp1 .= '<td colspan="7">';
		$tmp1 .= '<hr>';
		$tmp1 .= '</td>';
		$tmp1 .= '</tr>';
	}
		
	/* Get not approved alliance players */
	$query  = 'select b.country, b.name, b.lid, a.pid1, a.pid2, a.approved ';
	$query .= 'from player_player a, player b where b.pid=a.pid2 and a.pid1='.$player->pid.' '; 
	$query .= 'and a.approved=0 order by b.lid desc';
	$result = warquest_db_query($query);	 
	
		$size=warquest_db_num_rows($result);
	
	if ($size>0) {
	
		$flag = 1;
		
		while ($data=warquest_db_fetch_object($result)) {
	
			$tmp2 .= '<tr>';
			
			$tmp2 .= '<td>';
			$tmp2 .= $count++;
			$tmp2 .= '</td>';
			
			$tmp2 .= '<td>';
			$tmp2 .= warquest_flag_image($data->country);
			$tmp2 .= '</td>';
			
			$tmp2 .= '<td>';
			$tmp2 .= warquest_link('mid='.$mid.'&sid='.PAGE_PROFILE.'&oid='.$data->pid2, $data->name);
			$tmp2 .= '</td>';
			
			$tmp2 .= '<td>';
			$tmp2 .= $data->lid;
			$tmp2 .= '</td>';
			
			$tmp2 .= '<td>';
			if ($data->approved==0) {
				$tmp2 .= t('GENERAL_NO');
			} else {
				$tmp2 .= t('GENERAL_YES');
			}
			$tmp2 .= '</td>';	
	
			$tmp2 .= '<td>';
			$tmp2 .= '</td>';
			
			$tmp2 .= '<td>';
			$tmp2 .= warquest_link('mid='.$mid.'&sid='.$sid.'&oid='.$data->pid2.'&eid=4', t('LINK_DROP') ,"drop".$count);
			$tmp2 .= '</td>';
			
			$tmp2 .= '</tr>';
		}
	}
	
	if ($flag == 0) {
	
		$message = t('ALLIANCE_NO_PENDING');
		$page .= warquest_box_icon("info", $message);
		
	} else {
			
		$page .= '<div class="box">';
		$page .= '<table>';
	
		$page .= '<tr>';
		$page .= '<td width="40">';
		$page .= '<b>'.t('GENERAL_NUMBER').'</b>';
		$page .= '</td>';
		$page .= '<td width="40">';
		$page .= '<b></b>';
		$page .= '</td>';
		$page .= '<td width="150">';
		$page .= '<b>'.t('GENERAL_PLAYER').'</b>';
		$page .= '</td>';
		$page .= '<td width="100">';
		$page .= '<b>'.t('GENERAL_LEVEL').'</b>';
		$page .= '</td>';
		$page .= '<td width="100">';
		$page .= '<b>'.t('GENERAL_APPROVED').'</b>';	
		$page .= '</td>';
		$page .= '<td width="90">';
		$page .= '</td>';
		$page .= '<td width="90">';
		$page .= '</td>';
		$page .= '</tr>';
		
		$page .= $tmp1;
		$page .= $tmp2;
		
		$page .= '</table>';
		
		$page .= '</div>';
	}
	
	$page .= '<div class="note">';
	$page .= t('ALLIANCE_NOTE');
   $page .= '</div>';	
	
	$page .= warquest_show_ads();
}

/*
** --------------
** HANDLER
** --------------
*/

function warquest_clan_form() {

	/* input */	
	global $mid;
	global $sid;
	
	global $player;
	global $other;
		
	/* output */
	global $page;
	global $title;
	
	$title = t('CLAN_TITLE');

	$query  = 'select pid from player_clan where pid='.$player->pid;
	$result = warquest_db_query($query);	
	$data = warquest_db_fetch_object($result);
	$connected = warquest_db_num_rows($result);
	
	/* Get pending alliance player */
	$page .= '<div class="subparagraph">';
	$page .= t('CLAN_TITLE');
	$page .= '</div>';

	$page .= '<div class="box">';

	$query  = 'select a.cid, a.name, a.date, a.pid, ';
	$query .= '(select name from player where pid=a.pid) as name2, ';
	$query .= '(select count(*) from player_clan where cid=a.cid) as size, ';
	$query .= '(select sum(c.lid) from player_clan b, player c where cid=b.cid and c.pid=b.pid) as strength ';
	$query .= 'from clan a';
	$result = warquest_db_query($query);	 
	
	$size = warquest_db_num_rows($result);
	
	if ($size>0) {
	
		$flag = 1;
	
		$page .= '<table>';
		
		$page .= '<tr>';
		
		$page .= '<td width="80">';
		$page .= '</td>';
		
		$page .= '<td width="150"><b>';
		$page .= t('GENERAL_NAME');
		$page .= '<b/></td>';
		
		$page .= '<td width="80"><b>';
		$page .= t('GENERAL_SIZE');
		$page .= '<b/></td>';
		
		$page .= '<td width="80"><b>';
		$page .= t('GENERAL_STRENGTH');
		$page .= '<b/></td>';
		
		$page .= '<td width="100"><b>';
		$page .= t('GENERAL_COMMANDER');
		$page .= '</b></td>';

		$page .= '<td width="80"><b>';
		$page .= '';
		$page .= '</b></td>';
		
		$page .= '<tr>';
		
		while ($data=warquest_db_fetch_object($result)) {
		
			$page .= '<tr>';

			$page .= '<td width="10">';
			$page .= warquest_image("other/clan.jpg", 'width="50" height="30"');
			$page .= '</td>';
			
			$page .= '<td>';
			$page .= warquest_link('mid='.$mid.'&sid='.PAGE_CLAN_LIST.'&id='.$data->cid, $data->name);
			$page .= '</td>';
					
			$page .= '<td>';
			$page .= $data->size;
			$page .= '</td>';
			
			$page .= '<td>';
			$page .= $data->strength;
			$page .= '</td>';
			
			$page .= '<td>';
			$page .= $data->name2;
			$page .= '</td>';
						
			$page .= '<td>';
			if ($connected==0) {
				$page .= warquest_link('mid='.$mid.'&sid='.PAGE_CLAN.'&oid='.$data->cid, t('LINK_JOIN'));
			}
			$page .= '</td>';
			
			$page .= '</tr>';
		}
		
		$page .= '</table>';
		
	}
	
	$page .= '</div>';
	
	$page .= '<div class="note">';
	$page .= t('CLAN_NOTE');
   $page .= '</div>';	
	
	$page .= warquest_show_ads();
}

function warquest_clan_list_form() {

	/* input */	
	global $mid;
	global $sid;
	global $id;
	
	global $player;
	global $other;
		
	/* output */
	global $page;
	global $title;
	
	$count = 1;
	$flag = 0;
	$tmp1 = "";
	$tmp2 = "";

	$query  = 'select name from clan where cid='.$id;
	$result = warquest_db_query($query);	
	$data = warquest_db_fetch_object($result);
	
	/* Get pending alliance player */
	$page .= '<div class="subparagraph">';
	$page .= t('CLAN_LIST_TITLE', $data->name);
	$page .= '</div>';

	$title = t('CLAN_LIST_TITLE', $data->name);
	
	$query  = 'select b.pid, b.name, b.country, b.lid ';
	$query .= 'from player_clan a, player b where a.pid=b.pid and a.cid='.$id.' ';
	$query .= 'order by b.name asc';
	$result = warquest_db_query($query);	 
	
	$size = warquest_db_num_rows($result);
	
	$page .= '<div class="box">';
	
	if ($size>0) {
	
		$flag = 1;
	
		$page .= '<table>';
		
		$page .= '<tr>';
		
		$page .= '<td width="130"><b>';
		$page .= t('GENERAL_NAME');
		$page .= '<b/></td>';
		
		$page .= '<td width="100"><b>';
		$page .= t('GENERAL_STRENGTH');
		$page .= '<b/></td>';
		
		$page .= '<td width="100"><b>';
		$page .= '';
		$page .= '</b></td>';
		
		$page .= '<tr>';
		
		while ($data=warquest_db_fetch_object($result)) {
		
			$page .= '<tr>';
			
			$page .= '<td>';
			$page .= player_format($data->pid, $data->name, $data->country, 1);

			$page .= '</td>';
					
			$page .= '<td>';
			$page .= $data->lid;
			$page .= '</td>';
			
			$page .= '<td>';		
			if ($player->pid==$data->pid) {
				$page .= warquest_link('mid='.$mid.'&sid='.PAGE_CLAN.'&oid='.$data->pid, t('LINK_DROP'));
			}
			$page .= '</td>';
			
			$page .= '</tr>';
		}
		
		$page .= '</table>';
		
	}
	
	$page .= '</div>';
	
	$page .= '<div class="note">';
	$page .= t('CLAN_NOTE');
   $page .= '</div>';	
	
	$page .= warquest_show_ads();
}

/*
** --------------
** HANDLER
** --------------
*/

function warquest_alliance() {

	/* input */
	global $eid;
	global $sid;
	
	global $player;
	global $other;
		
	/* Event Handler */
	switch ($eid) {
			
		case 1:
			warquest_alliance_invite_do();
			break;
			
		case 2:
			warquest_alliance_accept_do();
			break;	
			
		case 3:
			warquest_alliance_reject_do();
			break;	
					
		case 4:
			warquest_alliance_drop_do();
			break;	
			
		case 500: 
			warquest_switch_planet_do();
			break;
			
	}
	
	/* Page handler */
	switch ($sid) {

		case PAGE_PENDING: 
					warquest_alliance_pending_form();
				  break;

		case PAGE_INVITE: 
					warquest_alliance_invite_form();
				  break;
			  
		case PAGE_ACCEPTED: 
					warquest_alliance_accepted_form();
					break;	

		case PAGE_BEST_PLAYER:
					warquest_leaderboard1_form();
					break;
				  
		case PAGE_BEST_COUNTRY: 
					warquest_leaderboard2_form();
					break;
				  		  				  
		case PAGE_BEST_COUNTRY2: 
					warquest_leaderboard3_form();
					break; 
	  				  
		case PAGE_CLAN: 
					warquest_clan_form();
					break; 
					
		case PAGE_CLAN_LIST: 
					warquest_clan_list_form();
					break; 
					
	}				  
	
	warquest_player();	
}

/*
** ---------------------------------------------------------------- 
** THE END
** ----------------------------------------------------------------
*/

?>