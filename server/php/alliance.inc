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
**  All copyrights reserved (c) 2008-2016 PlaatSoft
*/

/*
** --------------
** ALLIANCE 
** --------------
*/

/*
** ---------------------
** Post parameters
** ---------------------
*/

$nickname = warquest_post('nickname', '');

/*
** --------------
** ACTIONS
** --------------
*/

function warquest_alliance_invite_do() {

	/* output */ 
	global $player;
	global $other;
	global $output;
	global $config;
	
	$count = warquest_db_ally($player->pid, $other->pid);
	$output->result = false;
	
	if ($player->lid==0) {
		
		$message = t('ALLIANCE_LOCKED');		
		$output->popup .= warquest_box_icon('locked', $message);

	} else if (($player->alliance + $player->invite) >= ($player->lid*$config["max_ally_factor"])) {
		
		$message = t('ALLIANCE_MAXIMUM', $player->lid * $config["max_ally_factor"]);		
		$output->popup .= warquest_box_icon("warning", $message);
		
	} else if ($count==0) {
	
		warquest_db_alliance_insert($player->pid, $other->pid, 0);	

		$player->invite = warquest_db_invite_size($player->pid);				
		$other->invite = warquest_db_invite_size($other->pid);
	
		warquest_alliance_invite_mail($other->pid, $player->name);
		
		$message = t('ALLIANCE_INVITATION', $other->name);
		$output->popup .= warquest_box_icon("info", $message);
		
		$output->result = true;
	}
}

function warquest_alliance_drop_do() {

	/* input */	
	global $player;
	global $other;
	
		/* output */
	global $output;
	
	$count = warquest_db_ally($player->pid, $other->pid);
	
	if ($player->lid==0) {
		
		$message = t('ALLIANCE_LOCKED');		
		$output->popup .= warquest_box_icon('locked', $message);
	
	} else if ($count>0) {
	
		warquest_db_alliance_delete($player->pid, $other->pid);
		warquest_db_alliance_delete($other->pid, $player->pid);

		/* Update attack and defense value */
		$player->alliance = warquest_db_alliance_size($player->pid);
		$player->invite = warquest_db_invite_size($player->pid);
		
		$other->alliance = warquest_db_alliance_size($other->pid);
		$other->invite = warquest_db_invite_size($other->pid);
		
		warquest_alliance_drop_mail($other->pid, $player->name);
	
		$message = t('ALLIANCE_DROP', $other->name);
		$output->popup .= warquest_box_icon("info", $message);
	}
}
				
function warquest_alliance_reject_do() {

	/* input */
	global $player;
	global $other;
	
	/* output */
	global $output;
	
	$count = warquest_db_ally($player->pid, $other->pid);
	
	if ($player->lid==0) {
		
		$message = t('ALLIANCE_LOCKED');		
		$output->popup .= warquest_box_icon('locked', $message);
		
	} else if ($count>0) {
	
		warquest_db_alliance_delete($player->pid, $other->pid);
		warquest_db_alliance_delete($other->pid, $player->pid);

		/* Update attack and defense value */
		$player->alliance = warquest_db_alliance_size($player->pid);
		$player->invite = warquest_db_invite_size($player->pid);
		
		$other->alliance = warquest_db_alliance_size($other->pid);
		$other->invite = warquest_db_invite_size($other->pid);
			
		warquest_alliance_reject_mail($other->pid, $player->name);
	
		$message = t('ALLIANCE_REJECT', $other->name);
		$output->popup .= warquest_box_icon("info", $message);
	}
}
	
function warquest_alliance_accept_do() {

	/* output */
	global $player;
	global $other;
	
	/* output */
	global $output;
	
	$query  = 'select pid1 from player_player where pid1='.$player->pid.' and pid2='.$other->pid;
	$result = warquest_db_query($query);	
	$count = warquest_db_num_rows($result);
	
	if ($player->lid==0) {
		
		$message = t('ALLIANCE_LOCKED');		
		$output->popup .= warquest_box_icon('locked', $message);

	} else {
	
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
		
		warquest_alliance_accept_mail($other->pid, $player->name);
		
		$message = t('ALLIANCE_ACCEPT',$other->name); 
		$output->popup .= warquest_box_icon("info", $message);
	}
}

/*
** --------------
** GUI
** --------------
*/

/**
 * Alliance Accepted form
 */
function warquest_alliance_accepted_form() {

	/* input */	
	global $mid;
	global $sid;
	global $ssid;
	global $player;
	global $other;
	global $offset;
		
	/* output */
	global $page;
	global $output;
	
	$output->title = t('ALLIANCE_ACCEPT_TITLE1');
	
	$page .= '<div class="subparagraph">';
	$page .= t('ALLIANCE_ACCEPT_TITLE2', $player->alliance);
	$page .= '</div>';

	if ($player->lid==0) {
		
		$message = t('ALLIANCE_LOCKED');		
		$page .= warquest_box_icon('locked', $message);
		
	} else {

		$count=1;
		
		$page .= '<div class="box rows">';
		$page .= '<table>';
	
		$page .= '<tr>';
	
		$page .= '<th width="40">';
		$page .= t('GENERAL_NUMBER');
		$page .= '</th>';
		
		$page .= '<th width="40">';
		$page .= '</th>';
	
		$page .= '<th width="150">';
		$page .= t('GENERAL_PLAYER');
		$page .= '</th>';
		
		$page .= '<th width="100">';
		$page .= t('GENERAL_LEVEL');
		$page .= '</th>';
	
		$page .= '<th width="100">';
		$page .= t('GENERAL_APPROVED');	
		$page .= '</th>';
		
		$page .= '<th width="90">';
		$page .= '</th>';
	
		$page .= '<th width="90">';
		$page .= '</th>';
		
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
		
		$limit = 24;	
		
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
				$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&ssid='.$ssid.'&oid='.$data->pid2.'&eid='.EVENT_ALLIANCE_DROP.'&offset='.$offset, t('LINK_DROP') ,"drop".$count);
				$page .= '</td>';
				
				$page .= '</tr>';
			}
		}
			
		$page .= '</table>';
		$page .= warquest_page_control($offset, $limit, $total, 0);	
		$page .= '</div>';
	}
	
	$page .= '<div class="note">';
	$page .= t('ALLIANCE_NOTE');
   $page .= '</div>';	
}

/**
 * Alliance Pending form
 */
function warquest_alliance_pending_form() {

	/* input */	
	global $mid;
	global $sid;
	global $ssid;
	
	global $player;
	global $other;
		
	/* output */
	global $page;
	global $output;
	
	$output->title = t('ALLIANCE_PENDING_TITLE1');

	$page .= '<div class="subparagraph">';
	$page .= t('ALLIANCE_PENDING_TITLE2', $player->invite);
	$page .= '</div>';
	
	$count = 1;
	$flag = 0;
	
	/* Show not approved alliance */
	$query1  = 'select b.country, b.name, b.lid, a.pid1, a.pid2, a.approved ';
	$query1 .= 'from player_player a, player b where a.pid1=b.pid and a.pid2='.$player->pid.' '; 
	$query1 .= 'and a.approved=0';
	$result1 = warquest_db_query($query1);	 	
	$size1 = warquest_db_num_rows($result1);

	/* Get not approved alliance players */
	$query2  = 'select b.country, b.name, b.lid, a.pid1, a.pid2, a.approved ';
	$query2 .= 'from player_player a, player b where b.pid=a.pid2 and a.pid1='.$player->pid.' '; 
	$query2 .= 'and a.approved=0 order by b.lid desc';
	$result2 = warquest_db_query($query2);	 	
	$size2 = warquest_db_num_rows($result2);
			
	if ($player->lid==0) {
		
		$message = t('ALLIANCE_LOCKED');		
		$page .= warquest_box_icon('locked', $message);
	
	} else if (($size1==0) && ($size2==0))  {
	
		$message = t('ALLIANCE_NO_PENDING');
		$page .= warquest_box_icon("info", $message);

	} else {
		
		$page .= '<div class="box rows">';
		$page .= '<table>';
	
		$page .= '<tr>';
		
		$page .= '<th width="40">';
		$page .= t('GENERAL_NUMBER');
		$page .= '</th>';
			
		$page .= '<th width="40">';
		$page .= '</th>';
			
		$page .= '<th width="150">';
		$page .= t('GENERAL_PLAYER');
		$page .= '</th>';
		
		$page .= '<th width="100">';
		$page .= t('GENERAL_LEVEL');
		$page .= '</th>';
		
		$page .= '<th width="100">';
		$page .= t('GENERAL_APPROVED');	
		$page .= '</th>';
		
		$page .= '<th width="90">';
		$page .= '</th>';
		
		$page .= '<th width="90">';
		$page .= '</th>';
			
		$page .= '</tr>';
				
		while ($data1=warquest_db_fetch_object($result1)) {
		
			$page .= '<tr>';
			
			$page .= '<td>';
			$page .= $count++;		
			$page .= '</td>';
			
			$page .= '<td>';
			$page .= warquest_flag_image($data1->country);
			$page .= '</td>';
			
			$page .= '<td>';
			$page .= warquest_link('mid='.$mid.'&sid='.PAGE_PROFILE.'&oid='.$data1->pid1, $data1->name);
			$page .= '</td>';
			
			$page .= '<td>';
			$page .= $data1->lid;
			$page .= '</td>';
		
			$page .= '<td>';
			$page .= t('GENERAL_NO');
			$page .= '</td>';	
	
			$page .= '<td>';
			$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&ssid='.$ssid.'&oid='.$data1->pid1.'&eid='.EVENT_ALLIANCE_REJECT, t('LINK_REJECT'), "reject");
			$page .= '</td>';
			
			$page .= '<td>';
			$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&ssid='.$ssid.'&oid='.$data1->pid1.'&eid='.EVENT_ALLIANCE_ACCEPT, t('LINK_ACCEPT'), "accept");
			$page .= '</td>';
			
			$page .= '</tr>';
		}
		
		$page .= '<tr>';
		$page .= '<td colspan="7">';
		$page .= '<hr>';
		$page .= '</td>';
		$page .= '</tr>';
						
		while ($data2=warquest_db_fetch_object($result2)) {
	
			$page .= '<tr>';
			
			$page .= '<td>';
			$page .= $count++;
			$page .= '</td>';
			
			$page .= '<td>';
			$page .= warquest_flag_image($data2->country);
			$page .= '</td>';
				
			$page .= '<td>';
			$page .= warquest_link('mid='.$mid.'&sid='.PAGE_PROFILE.'&oid='.$data2->pid2, $data2->name);
			$page .= '</td>';
			
			$page .= '<td>';
			$page .= $data2->lid;
			$page .= '</td>';
			
			$page .= '<td>';
			if ($data2->approved==0) {
				$page .= t('GENERAL_NO');
			} else {
				$page .= t('GENERAL_YES');
			}	
			$page .= '</td>';	
	
			$page .= '<td>';
			$page .= '</td>';
				
			$page .= '<td>';
			$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&ssid='.$ssid.'&oid='.$data2->pid2.'&eid='.EVENT_ALLIANCE_DROP, t('LINK_DROP') ,"drop".$count);
			$page .= '</td>';
				
			$page .= '</tr>';
		}	

		$page .= '</table>';		
		$page .= '</div>';
	}
	
	$page .= '<div class="note">';
	$page .= t('ALLIANCE_NOTE');
   $page .= '</div>';	
}


function warquest_alliance_invite_search_form() {

	/* input */
	global $mid;
	global $sid;
	global $ssid;
	global $nickname;
	
	/* output */
	global $page;
	global $output;
		
	$page .= '<form method="post">';
	$page .=	'<div class="box">';
	
	$page .=	'Nickname: ';
	$page .=	'<input name="nickname" type="text" id="nickname" size="40" maxlength="30" value="'.$nickname.'" >';
	
	$page .=	'<div class="right2">';
	$page .=	'<input type="hidden" name="token" value="'.warquest_token('mid='.$mid.'&sid='.$sid.'&ssid='.$ssid).'" />';
	$page .=	'<input type="submit" name="Submit" value="Search" />';
	$page .=	'</div>';
	
	$page .=	'</div>';
	$page .=	'</form>';	
}

/**
 * Alliance invite form
 */
function warquest_alliance_invite_form() {

	/* input */
	global $config;
	global $player;
	global $mid;
	global $sid;
	global $ssid;
	global $offset;
	global $nickname;
	
	/* output */
	global $page;
	global $output;
	global $sort;
	
	$output->title = t('ALLIANCE_INVITE_TITLE');
	
	$page .= '<div class="subparagraph">';
	$page .= t('ALLIANCE_INVITE_TITLE');
	$page .= '</div>';
	
	if ($player->lid==0) {
		
		$message = t('ALLIANCE_LOCKED');		
		$page .= warquest_box_icon('locked', $message);
	
	} else {
		
		$limit = 25;	
		
		$page .= warquest_alliance_invite_search_form();
		
		if (strlen($nickname)==0) {
		
			$query  = 'select pid from player where pid not in ';
			$query .= '(select pid2 from player_player where pid1='.$player->pid.') and pid!='.$player->pid.' ';
			$query .= 'and (alliance+invite)<(lid*'.$config["max_ally_factor"].') ';
			$result = warquest_db_query($query);	 
			$total = warquest_db_num_rows($result);
		
			/* Show all not recruited players */
			$query  = 'select pid, name, country, lid, experience, alliance, request_date, invite ';
			$query .= 'from player where pid not in ';
			$query .= '(select pid2 from player_player where pid1='.$player->pid.') and pid!='.$player->pid.' ';
			$query .= 'and (alliance+invite)<(lid*'.$config["max_ally_factor"].') ';
			
		} else {
				
			$query  = 'select pid from player '; 
			if (strlen($nickname)>0) {
				$query .= 'where name like "'.$nickname.'%"';
			}
			$result = warquest_db_query($query);	
			$total = warquest_db_num_rows($result);
			
			/* Show all not recruited players */
			$query  = 'select pid, name, country, lid, experience, alliance, request_date, invite ';
			$query .= 'from player where name like "'.$nickname.'%"';			
		}
			
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
	
		$page .= '<div class="box rows">';
		
		$page .= warquest_page_control($offset, $limit, $total, 1, '&sort='.$sort);
	
		$page .= '<table>';
		
		$page .= '<tr>';
		$page .= '<th width="50">';
		$page .= '</th>';
		
		$page .= '<th width="130">';
		$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&ssid='.$ssid.'&sort=2', t('GENERAL_PLAYER'));
		$page .= '</th>';
		
		$page .= '<th width="70">';
		$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&ssid='.$ssid.'&sort=3', t('GENERAL_ACTIVE'));
		$page .= '</th>';
				
		$page .= '<th width="50">';
		$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&ssid='.$ssid.'&sort=4', t('GENERAL_LEVEL'));
		$page .= '</th>';
		
		$page .= '<th width="90">';
		$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&ssid='.$ssid.'&sort=5', t('GENERAL_EXP'));
		$page .= '</th>';
		
		$page .= '<th width="60">';
		$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&ssid='.$ssid.'&sort=6', t('GENERAL_ALLIANCE'));
		$page .= '</th>';
		
		$page .= '<th width="50">';
		$page .= '</th>';
		
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

			if ( (($data->alliance + $data->invite) < ($data->lid * $config["max_ally_factor"])) &&
			     (warquest_db_ally($player->pid, $data->pid)==0) &&
				  ($player->pid!=$data->pid)) {
			  
					$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&ssid='.$ssid.'&oid='.$data->pid.'&eid='.EVENT_ALLIANCE_INVITE.'&sort='.$sort.'&offset='.$offset, t('LINK_RECRUIT'), "recuit".$count++);
			}
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
}

/*
** --------------
** HANDLER
** --------------
*/

function warquest_alliance() {

	/* input */
	global $eid;
	global $ssid;
	
	/* output */
	global $page;
			
	/* Event Handler */
	switch ($eid) {
			
		case EVENT_ALLIANCE_INVITE:
			warquest_alliance_invite_do();
			break;
			
		case EVENT_ALLIANCE_ACCEPT:
			warquest_alliance_accept_do();
			break;	
			
		case EVENT_ALLIANCE_REJECT:
			warquest_alliance_reject_do();
			break;	
					
		case EVENT_ALLIANCE_DROP:
			warquest_alliance_drop_do();
			break;	
	}
	
	/* Page handler */
	switch ($ssid) {

		case PAGE_ALLIANCE_INVITE: 
					warquest_alliance_invite_form();
					break;
					
		case PAGE_ALLIANCE_PENDING: 
					warquest_alliance_pending_form();
					break;

		case PAGE_ALLIANCE_ACCEPTED: 
					warquest_alliance_accepted_form();
					break;	
	}				  
}

/*
** ---------------------------------------------------------------- 
** THE END
** ----------------------------------------------------------------
*/

?>