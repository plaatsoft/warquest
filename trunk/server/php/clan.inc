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

$name = warquest_post('name', '');
$slogan = warquest_post('slogan', '');
$min_level = warquest_post('min_level', 0);
$amount = warquest_post('amount', 1);
$role = warquest_post('role', CLAN_ROLE_SOLDIER);

/*
** --------------
** CLAN UTILS
** --------------
*/

/**
 * Show radiobox with all possible clan roles 
 */
function warquest_clan_role($role, $readonly=1) {

	/* input */
	global $mid;
	global $sid;
	global $cid;
	global $oid;
	
	$tmp = "";
	
	if ($readonly==1) {
	
		$tmp .= t("CLAN_ROLE_".$role);
		
	} else {
	
		$tmp .= '<select id="role" name="role" onchange="javascript:link(\''.
								warquest_token('mid='.$mid.'&sid='.$sid.'&cid='.$cid.'&oid='.$oid.'&eid='.EVENT_CLAN_MEMBER_SAVE).'\');" />';
										
		$values = array(2, 3);

		$count = 0;
		foreach ($values as $value) {
	
			$tmp .= '<option value="'.$value.'"';
			if ($role==$value) {
				$tmp .= ' selected="selected"';
			}
			$tmp .= '/>'.t("CLAN_ROLE_".$value).' ';	
		}		
		$tmp .= '</select>';
	}
	return $tmp;
}

/*
** --------------
** CLAN ACTIONS
** --------------
*/

/**
 * Commandor of clan can drop a member.
 */
function warquest_clan_drop_do() {

	/* input */
	global $player;
	global $other;
	global $cid;
		
	/* output */
	global $output;	

	$clan = warquest_db_clan($cid);
	$player_clan = warquest_db_player_clan($other->pid);
	
	if (!isset($player_clan->cid) || ($player_clan->cid!=$cid)) {
		
		$message = t('CLAN_NOT_PART');
		
		$output->popup .= warquest_box_icon("warning", $message);
		
	} else {
		
		warquest_db_player_clan_delete($other->pid, $cid);
	
		/* Update player netto income */		
		warquest_netto_income($other);
	
		/* Send internal message */
		$message = $player->name.' removed you from the '.$clan->name.' clan!';		
		warquest_db_comment_insert(0, 0, $player->pid, $other->pid, $message);
		$other->comment_notification++;
				
		/* Show confirm message on screen */
		$message = t('CLAN_DROP', player_format($other->pid, $other->name, $other->country, 1), $clan->name);
		$output->popup .= warquest_box_icon("info", $message);	
	}
}

/**
 * Commander accept clan request
 */
function warquest_clan_accept_do() {

	/* input */
	global $player;
	global $other;
	global $cid;
			
	/* output */
	global $output;	
	
	$clan = warquest_db_clan($cid);
	$player_clan = warquest_db_player_clan($player->pid);
	$other_clan = warquest_db_player_clan($other->pid);
	
	if ($player_clan->role!=CLAN_ROLE_COMMANDER) {
	
		$message = t('CLAN_NO_ALLOWED', $clan->name);
		$output->popup .= warquest_box_icon("warning", $message);
		
	} else if ($other_clan->approved==0) {
		
		$other_clan->approved=1;			
		$other_clan->joined = date('Y-m-d H:i:s');		
		warquest_db_player_clan_update($other_clan);
		
		/* Update player netto income */		
		warquest_netto_income($other);
		
		/* Send internal message */
		$message = $player->name.' accepted your request! You are now part of the '.$clan->name.' clan!';		
		warquest_db_comment_insert(0, 0, $player->pid, $other->pid, $message);
		$other->comment_notification++;
		
		/* Send mail to member of clan */
		warquest_clan_accept_mail($other->pid, $player->name);
		
		/* Show confirm message on screen */
		$message = t('CLAN_ACCEPTED', player_format($other->pid, $other->name, $other->country, 1), $clan->name);
		$output->popup .= warquest_box_icon("info", $message);	
	}
}


/**
 * Member leave clan 
 */
function warquest_clan_leave_do() {

	/* input */
	global $player;
	global $cid;
		
	/* output */
	global $output;	

	$clan = warquest_db_clan($cid);
	$player_clan = warquest_db_player_clan($player->pid);
	
	if (!isset($player_clan->cid) ) {
		
		$message = t('CLAN_NOT_PART');
		$output->popup .= warquest_box_icon("warning", $message);
		
	} else {
		
		warquest_db_player_clan_delete($player->pid, $cid);
		
		/* Update player netto income */		
		warquest_netto_income($player);
	
		$message = t('CLAN_LEAVE', $clan->name);
		$output->popup .= warquest_box_icon("info", $message);	
	}
}

/**
 * Member join clan
 */
function warquest_clan_join_do() {

	/* input */
	global $player;
	global $cid;
		
	/* output */
	global $output;	

	$clan = warquest_db_clan($cid);
	$player_clan = warquest_db_player_clan($player->pid);
	
	if ( isset($player_clan->cid) ) {
		
		$message = t('CLAN_ALL_PART');
		$output->popup .= warquest_box_icon("warning", $message);
		
	} else {
		
		$commander = warquest_db_player_clan_commander($cid);

		if ( !isset($commander->pid) ) {		
		
			/* No commander so make new player direct commander */
			warquest_db_player_clan_insert($player->pid, $cid, 1, CLAN_ROLE_COMMANDER);		

			$message = t('CLAN_JOINED2', $clan->name);
			
		} else {		
		
			warquest_db_player_clan_insert($player->pid, $cid, 0, CLAN_ROLE_SOLDIER);

			/* Send mail to commander of clan */
			warquest_clan_join_mail($commander->pid, $player->name);
					
			$message = $player->name.' wants to join your clan!';		
			warquest_db_comment_insert(0, 0, $player->pid, $commander->pid, $message);
			$commander->comment_notification++;	
			warquest_db_player_update($commander);

			$message = t('CLAN_JOINED', $clan->name, player_format($commander->pid, $commander->name, $commander->country, 1));	
		}
		$output->popup .= warquest_box_icon("info", $message);	
	}
}



/**
 * Commander create clan 
 */
function warquest_clan_create_do() {

	/* input */
	global $player;
	global $skill;
	global $name;
		
	/* output */
	global $output;	
	
	$query  = 'select cid from clan where name="'.name.'"'; 
	$result = warquest_db_query($query);	
	$count = warquest_db_num_rows($result);
	
	if ($skill->skill_points == 0) {
			
		$message = t('CLAN_NO_SKILL_POINT', $name);
		$output->popup .= warquest_box_icon("warning", $message);
		
	} else if (strlen($name) < 2) {
			
		$message = t('CLAN_NAME_TOO_SHORT');
		$output->popup .= warquest_box_icon("warning", $message);

	} else if (strlen($name) > 5) {
			
		$message = t('CLAN_NAME_TOO_LONG');
		$output->popup .= warquest_box_icon("warning", $message);
		
	} else if ($count > 0) {
			
		$message = t('CLAN_NAME_EXIST', $name);
		$output->popup .= warquest_box_icon("warning", $message);
		
	} else {
	
		$cid = warquest_db_clan_insert($player->pid, $name);
		
		warquest_db_player_clan_insert($player->pid, $cid, 1, CLAN_ROLE_COMMANDER);
		
		$skill->skill_points--;
		warquest_db_skill_update($skill);
	
		$message = t('CLAN_CREATED', $name);
		$output->popup .= warquest_box_icon("info", $message);			
	}
}


/**
 * Commander increase clan skill.
 */
function warquest_clan_skill_increase_do() {

	/* input */
	global $player;
	global $config;
	
	global $cid;
	global $mid;
	global $sid;
	global $eid;
	global $id;
	global $amount;

	/* output */
	global $output;	

	$clan = warquest_db_clan($cid);
	
	switch ($id) {
		
		case 1: 	$clan->attack += $amount;
					$max = $clan->attack;
					break;
						
		case 2: 	$clan->defense += $amount;
					$max = $clan->defense;
					break;
	}
		
	warquest_db_clan_update($clan);
		
	$message = t('CLAN_SKILL_INCREASED', number_format(($max * $config['init_clan_skill_step']),0,",","."));
		
	$link = warquest_link('mid='.$mid.'&sid='.$sid.'&cid='.$cid.'&eid='.$eid.'&id='.$id, t('LINK_INCREASE'), "increase");		
	$link .= '<br/><br/>'.t('GENERAL_AMOUNT').'<br/>';		
	$link .= warquest_amount_selected(1000000);
	$link .= '<br/><br/>';
		
	$output->popup .= warquest_box_icon("info", $message, $link);		
}

/**
 * Commander decrease clan skill.
 */
function warquest_clan_skill_decrease_do() {

	/* input */
	global $player;
	global $config;
	
	global $cid;
	global $mid;
	global $sid;
	global $eid;
	global $id;
	global $amount;
	
	/* output */
	global $output;	

	$clan = warquest_db_clan($cid);

	if (($id==1) & ($clan->attack < $amount)) {
	
		$message = t('CLAN_MINIMAL_SKILL');
		$output->popup .= warquest_box_icon("warning", $message);
		
	} else if (($id==2) & ($clan->defense < $amount)) {
	
		$message = t('CLAN_MINIMAL_SKILL');
		$output->popup .= warquest_box_icon("warning", $message);
		
	} else {
	
		switch ($id) {
		
			case 1: 	$clan->attack -= $amount;
						$max = $clan->attack;
						break;
						
			case 2: 	$clan->defense -= $amount;
						$max = $clan->defense;
						break;
		}
		
		warquest_db_clan_update($clan);
		
		$message = t('CLAN_SKILL_DECREASED', number_format(($max * $config['init_clan_skill_step']),0,",","."));
		
		$link = warquest_link('mid='.$mid.'&sid='.$sid.'&cid='.$cid.'&eid='.$eid.'&id='.$id,t('LINK_DECREASE'), "decrease");		
		if ($max>0) {
			$link .= '<br/><br/>'.t('GENERAL_AMOUNT').'<br/>';		
			$link .= warquest_amount_selected($max);
			$link .= '<br/><br/>';
		}
		
		$output->popup .= warquest_box_icon("info", $message, $link);			
	}
}


function warquest_clan_member_edit_do() {

	/* input	*/
	global $mid;
	global $sid;
	global $cid;
	
	global $player;	
	global $other;		
	global $config;
	
	/* input	*/
	global $output;
	
	$clan = warquest_db_clan($cid);
	$player_clan = warquest_db_player_clan($other->pid);
	
	if ($player_clan->approved==0) {	
	
		$message = 'Accept '.player_format($other->pid, $other->name, $other->country, 1).' membership ';
		$message .= warquest_link('mid='.$mid.'&sid='.PAGE_CLAN_PROFILE.'&cid='.$clan->cid.'&oid='.$other->pid.'&eid='.EVENT_CLAN_ACCEPT, t('LINK_YES'));												
		$message .= ' or ';
		$message .= warquest_link('mid='.$mid.'&sid='.PAGE_CLAN_PROFILE.'&cid='.$clan->cid.'&oid='.$other->pid.'&eid='.EVENT_CLAN_DROP, t('LINK_NO'));							
		
	} else {
		
		$message = 'Change '.player_format($other->pid, $other->name, $other->country, 1).' clan membership role ';
		$message .= warquest_clan_role($player_clan->role, false);
		$message .= '<br/>or ';	
		$message .= warquest_link('mid='.$mid.'&sid='.PAGE_CLAN_PROFILE.'&cid='.$clan->cid.'&oid='.$other->pid.'&eid='.EVENT_CLAN_DROP, t('LINK_DROP'));
		$message .= ' membership.';		
	}
		
	$output->popup .= warquest_box_icon("info", $message);
}

function warquest_clan_member_save_do() {

	/* input	*/
	global $cid;	
	global $role;	
	global $other;		
		
	/* input	*/
	global $output;
		
	$player_clan = warquest_db_player_clan($other->pid);
	
	if (!isset($player_clan->cid) || ($player_clan->cid!=$cid)) {
		
		$message = t('CLAN_NOT_PART');		
		$output->popup .= warquest_box_icon("warning", $message);
	
	} else {
	
		$player_clan->role=$role;
		warquest_db_player_clan_update($player_clan);
	
		$message = t('CLAN_ROLE_CHANGED',
						player_format($other->pid, $other->name, $other->country, 1),
						warquest_clan_role($role)
					);
						
		$output->popup .= warquest_box_icon("info", $message);
	}
}

/**
 * Save Clan settings
 */
function warquest_clan_save_do() {

	/* input */
	global $cid;
	global $player;
	global $config;
	
	global $name;	
	global $slogan;	
	global $min_level;	
		
	/* output */
	global $output;	
	global $sid;	
	
	$clan = warquest_db_clan($cid);
	$player_clan = warquest_db_player_clan($player->pid);
	
	$query  = 'select cid from clan where name="'.$name.'"'; 
	$result = warquest_db_query($query);	
	$count = warquest_db_num_rows($result);
	
	if ($player_clan->role!=CLAN_ROLE_COMMANDER) {
	
		$message = t('CLAN_NO_ALLOWED', $clan->name);
		$output->popup .= warquest_box_icon("warning", $message);
		
	} else if (strlen($name) < 2) {
			
		$message = t('CLAN_NAME_TOO_SHORT');
		$output->popup .= warquest_box_icon("warning", $message);

	} else if (strlen($name) > 5) {
			
		$message = t('CLAN_NAME_TOO_LONG');
		$output->popup .= warquest_box_icon("warning", $message);
		
	} else if (($name!=$clan->name) && ($count>0)) {
			
		$message = t('CLAN_NAME_EXIST', $name);
		$output->popup .= warquest_box_icon("warning", $message);
				
	} else if (strlen($slogan) > 200) {
			
		$message = t('CLAN_SLOGAN_TOO_LONG');
		$output->popup .= warquest_box_icon("warning", $message);
	
	} else if (!is_numeric($min_level)) {
			
		$message = t('CLAN_MIN_LEVEL_INVALID');
		$output->popup .= warquest_box_icon("warning", $message);

	} else if ($min_level<0) {
			
		$message = t('CLAN_MIN_LEVEL_TOO_LOW');
		$output->popup .= warquest_box_icon("warning", $message);

	} else if ($min_level>$config["max_level"]) {
			
		$message = t('CLAN_MIN_LEVEL_TOO_HIGH');
		$output->popup .= warquest_box_icon("warning", $message);
		
	} else {
	
		$clan->name = $name;
		$clan->slogan = $slogan;
		$clan->min_level = $min_level;
		
		warquest_db_clan_update($clan);
	
		$message = t('CLAN_SETTINGS_SAVED');
		$output->popup .= warquest_box_icon("info", $message);	

		/* No validation error, redirect! */
		$sid=PAGE_CLAN_PROFILE;
	}
}

/**
 * update clan logo
 */
function warquest_clan_logo_do($step) {
	
	global $cid;
	
	$clan = warquest_db_clan($cid);
	
	if ($step==1) {
		$clan->logo++;
		
		if ($clan->logo>=90) {
			$clan->logo=1;
		}
	
	} else {
	
		$clan->logo--;
		if ($clan->logo==0) {
			$clan->logo=90;
		}
	}
	
	warquest_db_clan_update($clan);
}

/*
** --------------
** CLAN UI
** --------------
*/

/**
 * Clan List form
 */
function warquest_clan_form() {

	/* input */	
	global $mid;
	global $sid;
	global $cid;
	
	global $player;
	global $other;
	global $offset;
		
	/* output */
	global $page;
	global $output;
	
	$lid = 15;
	$limit = 15;
	
	$output->title = t('CLAN_TITLE');

	$player_clan = warquest_db_player_clan($player->pid);
	
	/* Get pending alliance player */
	$page .= '<div class="subparagraph">';
	$page .= t('CLAN_TITLE');
	$page .= '</div>';
		
	if ( ($player->lid>=$lid) && (!isset($player_clan->pid)) ) {
	
		$page .= '<div class="box">';
		$page .= t('CLAN_CREATE').':';	
		$page .= ' ';	
		$page .= '<input name="clan" type="text" id="clan" size="10" maxlength="5" onkeydown="if (event.keyCode == 13) return false"/>';	
		$page .= ' ';
		$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&cid='.$cid.'&eid='.EVENT_CLAN_CREATE, t('CLAN_ADD'), 'add');
		$page .= '</div>';
		
		$page .= '<div class="note">';
		$page .= t('CLAN_CREATE_NOTE');
		$page .= '</div>';
	}
	
	$query  = 'select cid from clan';
	$result = warquest_db_query($query);	
	$total = warquest_db_num_rows($result);
	
	$query  = 'select a.cid, a.name, a.pid, a.last_activity, a.logo, a.min_level, ';
	$query .= '(select count(*) from player_clan where approved=1 and cid=a.cid) as size ';
	$query .= 'from clan a order by a.last_activity desc ';
	$query .= 'limit '.$offset.','.$limit;
	
	$result = warquest_db_query($query);	 	
	$size = warquest_db_num_rows($result);
	
	if ($size == 0) {
	
		$message = t('CLAN_NO_CLANS');
		$page .= warquest_box_icon('info', $message);
		
	} else if ($player->lid < $lid) {
		
		$message = t('CLAN_LOCKED', $lid);
		$page .= warquest_box_icon('locked', $message);
		
	} else {		
	
		$page .= '<div class="box rows">';
	
		$page .= warquest_page_control($offset, $limit, $total, 1);
			
		$page .= '<table>';
		
		$page .= '<tr>';
						
		$page .= '<th width="150">';
		$page .= t('GENERAL_NAME');
		$page .= '</th>';
		
		$page .= '<th width="70">';
		$page .= t('GENERAL_ACTIVE');
		$page .= '</th>';
		
		$page .= '<th width="80">';
		$page .= t('GENERAL_SIZE');
		$page .= '</th>';
				
		$page .= '<th width="150">';
		$page .= t('GENERAL_COMMANDER');
		$page .= '</th>';
		
		$page .= '<th width="50">';
		$page .= '</th>';
		
		$page .= '</tr>';
		
		while ($data = warquest_db_fetch_object($result)) {
		
			$commander = warquest_db_player_clan_commander($data->cid);
	
			$page .= '<tr>';

			$page .= '<td>';
			$page .= warquest_clan_image($data->logo, 32, 32).' ';
			$page .= warquest_link('mid='.$mid.'&sid='.PAGE_CLAN_PROFILE.'&cid='.$data->cid, $data->name);
			$page .= '</td>';
			
			$page .= '<td>';
			$page .= warquest_ui_ago($data->last_activity);
			$page .= '</td>';
			
			$page .= '<td>';
			$page .= $data->size;
			$page .= '</td>';
		
			$page .= '<td>';
			if ( isset($commander->pid) ) {
				$page .= player_format($commander->pid, $commander->name, $commander->country, 1);
			}
			$page .= '</td>';
			
			$page .= '<td>';

			if ( isset($player_clan->cid) ) {
				if ($data->cid == $player_clan->cid) {
					$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&cid='.$data->cid.'&eid='.EVENT_CLAN_LEAVE, t('LINK_LEAVE'));	
				}
			} else {
				if ($player->lid>=$data->min_level) {
					$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&cid='.$data->cid.'&eid='.EVENT_CLAN_JOIN, t('LINK_JOIN'));				
				}
			} 
			$page .= '</td>';
			
			$page .= '</tr>';
		}
		
		$page .= '</table>';		
		
		$page .= warquest_page_control($offset, $limit, $total, 0);
		
		$page .= '</div>';		
	} 
		
	$page .= '<div class="note">';
	$page .= t('CLAN_NOTE');
   $page .= '</div>';	
}

/**
 * Clan Profile (detail) form
 */
function warquest_clan_profile_form() {

	/* input */	
	global $mid;
	global $sid;
	
	global $cid;
	global $player;
	global $config;
		
	/* output */
	global $page;
	global $output;
		
	$clan = warquest_db_clan($cid);
	$player_clan = warquest_db_player_clan($player->pid);
	
	$output->title = t('CLAN_PROFILE', $clan->name);
	
	$page .= '<div class="subparagraph">'.t('CLAN_PROFILE_TITLE').'</div>';
		
	/* ------------------------------------ */
	
	$page .= '<div class="box">';
	
	$query  = 'select pid from player_clan where cid='.$clan->cid;	
	$result = warquest_db_query($query);	 	
	$size = warquest_db_num_rows($result);
		
	$other = warquest_db_player($clan->pid);
	
	$page .= '<table>';
	
	$page .= '<tr>';
	$page .= '<td width="170">'.t('GENERAL_CLAN_NAME').':</td>';
	$page .= '<td width="230">'.$clan->name.'</td>';	
	$page .= '<td width="100"  rowspan="4">';
	$page .= '<div class="right">';	
	$page .= warquest_clan_image($clan->logo, 64, 64);
	$page .= '</div>';	
	$page .= '<td>';
	$page .= '</tr>';
	
	$page .= '<tr>';
	$page .= '<td>'.t('CLAN_SIZE').':</td>';
	$page .= '<td>'.$size.'</td>';	
	$page .= '<td></td>';
	$page .= '</tr>';
	
	$page .= '<tr>';
	$page .= '<td>'.t('GENERAL_MIN_LEVEL').':</td>';
	$page .= '<td>'.$clan->min_level.'</td>';	
	$page .= '<td></td>';	
	$page .= '</tr>';
		
	$page .= '<tr>';
	$page .= '<td>'.t('GENERAL_CREATOR').':</td>';
	$page .= '<td>'.player_format($other->pid, $other->name, $other->country, 0);
	$page .= '</td>';
	$page .= '<td>';
	
	$page .= '<tr>';
	$page .= '<td>'.t('GENERAL_CLAN_CREATED').':</td>';
	$page .= '<td>'.warquest_ui_ago($clan->created);
	$page .= '</td>';
	$page .= '<td>';
	
	
	$page .= '<div class="right2">';
	
	if (isset($player_clan->pid) && ($clan->cid==$player_clan->cid) && ($player_clan->role==CLAN_ROLE_COMMANDER))  {
		$page .= warquest_link('mid='.$mid.'&sid='.PAGE_CLAN_SETTINGS.'&cid='.$cid, t('LINK_EDIT'));
	}	
	$page .= '</td>';
	$page .= '</div>';
	$page .= '</tr>';
	
	$page .= '</table>';
	$page .= '</div>'; 
		
	/* ------------------------------------ */
		
	$page .= '<div class="subparagraph">'.t('CLAN_STATISTICS').'</div>';
	  	
	$page .= '<div class="box">';
	
	$page .= '<table>';
	
	$page .= '<tr>';
	$page .= '<td width="170">'.t('CLAN_FIGHTS_WON').':</td>';
	$page .= '<td width="85">'.number_format($clan->won,0,",",".").'</td>';
	$page .= '<td width="170">'.t('CLAN_FIGHTS_LOST').':</td>';
	$page .= '<td width="80">'.number_format($clan->lost,0,",",".").'</td>';
	$page .= '</tr>';
		
	$page .= '<tr>';
	$page .= '<td>'.t('CLAN_WON_LOST_RATIO').':</td>';
	$tmp=0;
	if ($clan->lost>0) {
		$tmp = round(($clan->won/$clan->lost),2);
	}
	$page .= '<td>'.$tmp.'</td>';
	$page .= '<td>'.t('CLAN_MISSIONS_COMPLETED').':</td>';
	$page .= '<td>'.number_format($clan->mission,0,",",".").'</td>';	
	$page .= '</tr>';
	
	$page .= '<tr>';
	$page .= '<td>'.t('CLAN_LAST_ACTIVE').':</td>';
	$page .= '<td>'.warquest_ui_ago($clan->last_activity).'</td>';
	$page .= '<td></td>';
	$page .= '<td></td>';
	$page .= '</tr>';
	
	$page .= '</table>';
	
	$page .= '</div>';
	
	/* ------------------------------------ */
	
	$page .= '<div class="subparagraph">'.t('CLAN_SLOGAN_TITLE').'</div>';
	
	$page .= '<div class="box">';
		
	$page .= '<div class="slogan">';
	$page .= warquest_parse_smilies($clan->slogan);
	$page .= '</div>';
	
	$page .= '</div>';
	
	/* ------------------------------------ */

	$page .= '<div class="subparagraph">';
	$page .= t('CLAN_MEMBER_LIST');
	$page .= '</div>';
	
	$query  = 'select a.joined, a.approved, a.role, b.pid, b.name, b.country, b.lid, b.experience ';
	$query .= 'from player_clan a, player b where a.pid=b.pid and a.cid='.$clan->cid.' ';
	$query .= 'order by a.role, b.lid desc';

	$result = warquest_db_query($query);	 	
	$size = warquest_db_num_rows($result);
	
	if ($size == 0) {
	
		$message = t('CLAN_NO_MEMBERS');
		$page .= warquest_box_icon('info', $message);
	
	} else {
			
		$page .= '<div class="box rows">';
		
		$page .= '<table>';
		
		$page .= '<tr>';
		
		$page .= '<th width="30">';
		$page .= t('GENERAL_NR');
		$page .= '</th>';
		
		$page .= '<th width="150">';
		$page .= t('GENERAL_NAME');
		$page .= '</th>';
		
		$page .= '<th width="50">';
		$page .= t('GENERAL_LEVEL');
		$page .= '</th>';
		
		$page .= '<th width="100">';
		$page .= t('GENERAL_ROLE');
		$page .= '</th>';
		
		$page .= '<th width="80">';
		$page .= t('GENERAL_APPROVED');
		$page .= '</th>';

		$page .= '<th width="80">';
		$page .= t('GENERAL_JOINED');
		$page .= '</th>';
				
		$page .= '<th width="50">';
		$page .= '</th>';
		
		$page .= '</tr>';
		
		$count = 1;
		while ($data=warquest_db_fetch_object($result)) {
		
			$page .= '<tr>';
			
			$page .= '<td>';
			$page .= $count++;
			$page .= '</td>';
			
			$page .= '<td>';
			$page .= player_format($data->pid, $data->name, $data->country, 1);
			$page .= '</td>';
					
			$page .= '<td>';
			$page .= $data->lid;
			$page .= '</td>';
						
			$page .= '<td>';
			$page .= warquest_clan_role($data->role);
			$page .= '</td>';
			
			$page .= '<td>';
			if ($data->approved==0) {
				$page .= t('GENERAL_NO');
			} else {
				$page .= t('GENERAL_YES');
			}
			$page .= '</td>';
			
			$page .= '<td>';
			$page .= warquest_ui_ago($data->joined);
			$page .= '</td>';
				
			$page .= '<td>';
			if (isset($player_clan->pid) && ($clan->cid==$player_clan->cid) && ($player_clan->role==CLAN_ROLE_COMMANDER) && ($data->pid!=$player->pid)) {					
				$page .= warquest_link('mid='.$mid.'&sid='.PAGE_CLAN_PROFILE.'&cid='.$clan->cid.'&oid='.$data->pid.'&eid='.EVENT_CLAN_MEMBER_EDIT, t('LINK_EDIT'));							
			}
			$page .= '</td>';
	
			$page .= '</tr>';
		}
		
		$page .= '</table>';
		
		$page .= '</div>';
	}
	
	/* ------------------------------------ */
	
	$strength = warquest_db_clan_strength($clan->cid);
	
	$page .= '<div class="subparagraph">';
	$page .= t('CLAN_SKILLS');
	$page .= '</div>';
		
	$page .= '<div class="box rows">';			
	
	$page .= '<table>';
	$page .= '<tr>';
	
	$page .= '<tr>';	
		
	$page .= '<td width="50">';
	$page .= warquest_image('other/attack.png',' width="30" height="30" ');
	$page .= '</td>';
		
	$page .= '<td width="150">';
	$page .= '<span class="subparagraph">'.t('CLAN_ATTACK').'</span>';
	$page .= '</td>';
	
	$page .= '<td width="200">'.t('PLAYER_CURRENT').': ';
	$page .= strength_format(($clan->attack * $config['init_clan_skill_step']),0,",",".");
	$page .= '</td>';
		
	$page .= '<td width="100">';
	if (isset($player_clan->pid) && ($clan->cid==$player_clan->cid) && (($player_clan->role==CLAN_ROLE_COMMANDER) || ($player_clan->role==CLAN_ROLE_DEPUTY))) {
		$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&cid='.$clan->cid.'&eid='.EVENT_CLAN_SKILL_INCREASE.'&id=1', t('LINK_INCREASE'), "increase1");
	}
	$page .= '</td>';
		
	$page .= '<td width="65" align="right">';
	if (isset($player_clan->pid) && ($clan->cid==$player_clan->cid) && (($player_clan->role==CLAN_ROLE_COMMANDER) || ($player_clan->role==CLAN_ROLE_DEPUTY))) {
		$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&cid='.$clan->cid.'&eid='.EVENT_CLAN_SKILL_DECREASE.'&id=1',t('LINK_DECREASE'), "decrease1");
	}
	$page .= '</td>';
	
	$page .= '</tr>';
	
	$page .= '<tr>';
	$page .= '<td class="clear"></td>';
	$page .= '<td colspan="4" class="clear">';
	$page .= '<div class="remark">';
	$page .= t('CLAN_ATTACK_TIP',	dollar_format($clan->attack * $strength * $strength / $config['init_clan_skill_price']));
	$page .= '</div>';
	$page .= '</td>';
	$page .= '</tr>';

	$page .= '<tr>';
	$page .= '<td colspan="5" class="bar">&nbsp;</td>';
	$page .= '</tr>';
	
	/* ------------- */
	
	$page .= '<tr>';
	
	$page .= '<td>';
	$page .= warquest_image('other/defense.png',' width="30" height="30" ');
	$page .= '</td>';
	
	$page .= '<td><span class="subparagraph">'.t('CLAN_DEFENSE').'</span></td>';
		
	$page .= '<td>'.t('PLAYER_CURRENT').': ';
	$page .= strength_format(($clan->defense * $config['init_clan_skill_step']),0,",",".");
	$page .='</td>';
	
	$page .= '<td>';
	if (isset($player_clan->pid) && ($clan->cid==$player_clan->cid) && (($player_clan->role==CLAN_ROLE_COMMANDER) || ($player_clan->role==CLAN_ROLE_DEPUTY))) {
		$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&cid='.$clan->cid.'&eid='.EVENT_CLAN_SKILL_INCREASE.'&id=2', t('LINK_INCREASE'), "increase2");
	}
	$page .= '</td>';
	
	$page .= '<td>';
	if (isset($player_clan->pid) && ($clan->cid==$player_clan->cid) && (($player_clan->role==CLAN_ROLE_COMMANDER) || ($player_clan->role==CLAN_ROLE_DEPUTY))) {
		$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&cid='.$clan->cid.'&eid='.EVENT_CLAN_SKILL_DECREASE.'&id=2',t('LINK_DECREASE'), "decrease2");
	}
	$page .= '</td>';
		
	$page .= '</tr>';
	
	$page .= '<tr>';
	$page .= '<td class="clear"></td>';
	$page .= '<td colspan="4" class="clear">';
	$page .= '<div class="remark">';
	$page .= t('CLAN_DEFENSE_TIP', dollar_format($clan->defense * $strength * $strength / $config['init_clan_skill_price']));
	$page .= '</div>';
	$page .= '</td>';
	$page .= '</tr>';
		
	$page .= '</table>';
	$page .= '</div>';
	
	/* ------------------------------------ */

	$page .= '<div class="note">';
	$page .= t('CLAN_PROFILE_NOTE');
   $page .= '</div>';	
}

/**
 * Clan Setting form
 */
function warquest_clan_settings_form() {

	/* input */	
	global $mid;
	global $sid;
	global $cid;
	
	global $player;
		
	/* output */
	global $page;
	global $output;
	
	$clan = warquest_db_clan($cid);
	$player_clan = warquest_db_player_clan($player->pid);
	
	$output->title = t('CLAN_SETTINGS_TITLE');
		
	/* Get pending alliance player */
	$page .= '<div class="subparagraph">';
	$page .= t('CLAN_SETTINGS_TITLE');	
	$page .= '</div>';	
		
	$page .= '<div class="box">';
	
	$page .= t('GENERAL_CLAN_NAME').':';
	$page .= '<br/>';
	$page .= warquest_ui_input('name', 15, 5, $clan->name, false);
	$page .= '<br/>';
	$page .= '<br/>';
	
	$page .= t('GENERAL_MIN_LEVEL').':';
	$page .= '<br/>';
	$page .= warquest_ui_input('min_level', 15, 3, $clan->min_level, false);
	$page .= '<br/>';
	$page .= '<br/>';
	
	$page .= t('GENERAL_LOGO').':';
	$page .= '<br/>';	
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&cid='.$clan->cid.'&eid='.EVENT_CLAN_LOGO_PREV, t('LINK_PREVIOUS'));	
	$page .= ' ';
	$page .= warquest_clan_image($clan->logo, 64, 64);
	$page .= ' ';	
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&cid='.$clan->cid.'&eid='.EVENT_CLAN_LOGO_NEXT, t('LINK_NEXT'));	
	$page .= '<br/>';
	$page .= '<br/>';
		
	$page .= t('CLAN_SLOGAN_TITLE').':';
	$page .= '<br/>';	
	$page .= "<script language=\"JavaScript\" type=\"text/javascript\">function limitText(limitField, limitNum) { if (limitField.value.length >= limitNum) { limitField.value = limitField.value.substring(0, limitNum); } } </script>";
	$page .= '<textarea style="width:100%" id="slogan" name="slogan" rows="3" ';
	$page .= 'onKeyDown="limitText(this,199)">'.$clan->slogan.'</textarea><br/>';
	$page .= warquest_show_smilies('slogan');
	$page .= '<br/>';
	$page .= '<br/>';

	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&cid='.$clan->cid.'&eid='.EVENT_CLAN_SAVE, t('LINK_SAVE'), 'save');
	$page .= '<br/>';

	$page .= '</div>';
		
	$page .= '<div class="note">';
	$page .= t('CLAN_SETTINGS_NOTE');
   $page .= '</div>';
}

/*
** --------------
** HANDLER
** --------------
*/

function warquest_clan() {

	/* input */
	global $eid;
	global $sid;

	/* Event Handler */
	switch ($eid) {

		case EVENT_CLAN_CREATE:
			warquest_clan_create_do();
			break;	
			
		case EVENT_CLAN_JOIN:
			warquest_clan_join_do();
			break;	
			
		case EVENT_CLAN_LEAVE:
			warquest_clan_leave_do();
			break;	
						
		case EVENT_CLAN_ACCEPT:			
			warquest_clan_accept_do();
			break;
						
		case EVENT_CLAN_DROP:
			warquest_clan_drop_do();
			break;	
			
		case EVENT_CLAN_SAVE:
			warquest_clan_save_do();
			break;	
			
		case EVENT_CLAN_SKILL_INCREASE:
			warquest_clan_skill_increase_do();
			break;
			
		case EVENT_CLAN_SKILL_DECREASE:
			warquest_clan_skill_decrease_do();
			break;

		case EVENT_CLAN_MEMBER_EDIT:
			warquest_clan_member_edit_do();
			break;
			
		case EVENT_CLAN_MEMBER_SAVE:
			warquest_clan_member_save_do();
			break;
		
		case EVENT_CLAN_LOGO_NEXT:
			warquest_clan_logo_do(1);
			break;
			
		case EVENT_CLAN_LOGO_PREV:
			warquest_clan_logo_do(0);
			break;			
	}
		
	switch ($sid) {

		case PAGE_CLAN: 
				warquest_clan_form();
				break; 
					
		case PAGE_CLAN_PROFILE: 
				warquest_clan_profile_form();
				break; 
					
		case PAGE_CLAN_SETTINGS:			
				warquest_clan_settings_form();
				break;
	}				  	
}

/*
** ---------------------------------------------------------------- 
** THE END
** ----------------------------------------------------------------
*/

?>
