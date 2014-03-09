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

$clan = warquest_post('clan', '');
$slogan = warquest_post('slogan', '');
$deposit = warquest_post('deposit', '0');
$amount = warquest_post('amount', 0);

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
	$player_clan = warquest_db_player_clan($other->pid);
	
	if ($clan->pid!=$player->pid) {
	
		$message = t('CLAN_NO_ALLOWED', $clan->name);
		$output->popup .= warquest_box_icon("warning", $message);
		
	} else if ($player_clan->approved==0) {
		
		$player_clan->approved=1;			
		warquest_db_player_clan_update($player_clan);
		
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
	global $other;
	global $cid;
		
	/* output */
	global $output;	

	$clan = warquest_db_clan($cid);
	$player_clan = warquest_db_player_clan($player->pid);
	
	if ( isset($player_clan->cid) ) {
		
		$message = t('CLAN_ALL_PART');
		$output->popup .= warquest_box_icon("warning", $message);
		
	} else {
	
		warquest_db_player_clan_insert($player->pid, $cid, 0);
	
		/* Send mail to commander of clan */
		warquest_clan_join_mail($other->pid, $player->name);
				
		$message = $player->name.' wants to join your clan!';		
		warquest_db_comment_insert(0, 0, $player->pid, $other->pid, $message);
		$other->comment_notification++;
		
		$message = t('CLAN_JOINED', $clan->name, player_format($other->pid, $other->name, $other->country, 1));	
		$output->popup .= warquest_box_icon("info", $message);	
	}
}

/**
 * Commander set of change clan slogan
 */
function warquest_clan_slogan_do() {

	/* input */
	global $player;
	global $cid;
	global $slogan;	
		
	/* output */
	global $output;	
	
	$clan = warquest_db_clan($cid);
	 
	if ($clan->pid!=$player->pid) {
	
		$message = t('CLAN_NO_ALLOWED', $clan->name);
		$output->popup .= warquest_box_icon("warning", $message);
		
	} else if (strlen($slogan) < 5) {
			
		$message = t('CLAN_SLOGAN_TOO_SHORT');
		$output->popup .= warquest_box_icon("warning", $message);

	} else if (strlen($slogan) > 200) {
			
		$message = t('CLAN_SLOGAN_TOO_LONG');
		$output->popup .= warquest_box_icon("warning", $message);
		
	} else {
	
		$clan->slogan = $slogan;
		
		warquest_db_clan_update($clan);
	
		$message = t('CLAN_SLOGAN_SAVED');
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
	global $clan;
		
	/* output */
	global $output;	
	
	$query  = 'select cid from clan where name="'.$clan.'"'; 
	$result = warquest_db_query($query);	
	$count = warquest_db_num_rows($result);
	
	if ($skill->skill_points == 0) {
			
		$message = t('CLAN_NO_SKILL_POINT', $clan);
		$output->popup .= warquest_box_icon("warning", $message);
		
	} else if (strlen($clan) < 2) {
			
		$message = t('CLAN_NAME_TOO_SHORT');
		$output->popup .= warquest_box_icon("warning", $message);

	} else if (strlen($clan) > 5) {
			
		$message = t('CLAN_NAME_TOO_LONG');
		$output->popup .= warquest_box_icon("warning", $message);
		
	} else if ($count > 0) {
			
		$message = t('CLAN_NAME_EXIST', $clan);
		$output->popup .= warquest_box_icon("warning", $message);
		
	} else {
	
		$cid = warquest_db_clan_insert($player->pid, $clan);
		
		warquest_db_player_clan_insert($player->pid, $cid, 1);
		
		$skill->skill_points--;
		warquest_db_skill_update($skill);
	
		$message = t('CLAN_CREATED', $clan);
		$output->popup .= warquest_box_icon("info", $message);			
	}
}

/**
 * Clan member & Commander desposit money on clan bank.
 */
function warquest_clan_deposit_do() {

	/* input */
	global $player;
	global $cid;
	global $deposit;
	global $config;
	
	/* output */
	global $output;	
	
	$old = mktime(date("H"), date("i"), date("s"), date("m"), date("d")-1, date("Y"));

	$query = 'select date from clan_bank where pid='.$player->pid.' and action=2 and date>"'.date("Y-m-d H:i:s", $old).'" order by date desc limit 0,1 ';
	$result = warquest_db_query($query);	
	$data = warquest_db_fetch_object($result);
	
	/* Remove dots */
	$deposit = str_replace(".", "", $deposit);
	
	$clan = warquest_db_clan($cid);
	
	if ($deposit > $player->money) {
			
		$message = t('BANK_DEPOSIT_FAILED', money_format1($deposit));
		$output->popup .= warquest_box_icon("warning", $message);
	
	} else if ($deposit > ($player->money_step*10)) {
	
		$message = t('CLAN_DEPOSIT_TOO_HIGH', money_format1($player->money_step*10));
		$output->popup .= warquest_box_icon("warning", $message);
	
	} else if (isset($data->date)) {
	
		$new = mktime(date("H"), date("i"), date("s"), date("m"), date("d"), date("Y"));
		$value = (24*60*60) - ($new - strtotime($data->date));
	
		$tmp = '<script language="JavaScript" src="'.$config["content_url"].'js/countdown4.js" type="text/javascript"></script>';

		$tmp .= '<div class="countdown"><div id="countdown_time4"></div></div>';
		$tmp .= '<script language="JavaScript" type="text/javascript">';
		$tmp .= "countdown4.init(".$value.", 'countdown_time4', '00:00:00');"; 
		$tmp .= '</script>';
		
		$message = t('CLAN_DEPOSIT_MAX',$tmp );
		$output->popup .= warquest_box_icon("warning", $message);
	
	} else {

		$clan->money += $deposit;
		warquest_db_clan_bank_insert($clan->cid, $player->pid, $deposit, $clan->money, 10);		
		
		$fee = $deposit * ($config["init_clan_bank_deposit"]/100);
		$clan->money -= $fee;
		warquest_db_clan_bank_insert($clan->cid, $player->pid, ($fee*-1), $clan->money, 2);
		
		warquest_db_clan_update($clan);
				
		$player->money -= $deposit;
		
		$message = t('BANK_DEPOSIT', money_format1($deposit), t('BANK_GROUP_4'));
		$output->popup .= warquest_box_icon("info", $message);
		
		$log = 'Deposit '.number_format2($deposit).' to clan bank';		
		warquest_user_log($player, $log);
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
	
	if ($clan->pid!=$player->pid) {
	
		$message = t('CLAN_NO_ALLOWED', $clan->name);
		$output->popup .= warquest_box_icon("warning", $message);
		
	} else {
	
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

	if ($clan->pid!=$player->pid) {
	
		$message = t('CLAN_NO_ALLOWED', $clan->name);
		$output->popup .= warquest_box_icon("warning", $message);
	
	} else if (($id==1) & ($clan->attack < $amount)) {
	
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


/*
** --------------
** CLAN UI
** --------------
*/

/** 
 * Clan profile bank part
 */
function warquest_clan_bank_part($clan, $player_clan) {
   
	/* input	*/
	global $mid;
	global $sid;

	global $player;	
	global $config;
	global $offset;
	
	/* output */
	global $page;

	$page .= '<div class="subparagraph">';
	$page .= t('CLAN_BANK', $clan->name);
	$page .= '</div>';
		
	$page .= '<div class="box">';			
	
	$page .= '<table>';
	$page .= '<tr>';
	$page .= '<td width="160" >';	
	$page .= warquest_bank_image(4, 140, 100);
	$page .= '</td>';
	
	$page .= '<td>';
	
	$page .= '<table>';
	
	$page .= '<tr>';
	$page .= '<td width="340">';		
	$page .= t('LINK_BALANCE').":<br/>";
	$page .= '<input id="text" name="balance" size="22" maxlength="16" disabled="disabled" type="text" ';
	$page .= 'value="'.number_format($clan->money,0,",",".").'">';
	$page .= "</td>";
	
	$page .= "<td>";	
	$page .= "</td>";
	
	$page .= "</tr>";
	
	$page .= "<tr>";
	
	$page .= '<td>';
	if ( isset($player_clan->cid) && ($clan->cid==$player_clan->cid) ) {
		$page .= t('LINK_DEPOSIT').":<br/>";
		$page .= '<input id="text" name="deposit" size="22" maxlength="16" type="text" value="';
		$tmp = $player->money_step * 10;
		if ( $tmp > $player->money ) {
			$tmp = $player->money;
		}
		$page .= number_format($tmp,0,",",".");
		$page .= '"><br/>';
		$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&cid='.$clan->cid.'&eid='.EVENT_CLAN_DEPOSIT, t('LINK_DEPOSIT'));
	}
	$page .= "</td>";
	
	$page .= "</table>";
	
	$page .= '</td>';
	$page .= '</tr>';
	$page .= "</table>";
	
	$page .= '</div>';
	
	$page .= '<div class="note">';
	$page .= t('CLAN_BANK_NOTE', $config["init_clan_bank_deposit"], $config["init_clan_bank_interest"]);
   $page .= '</div>';
		
		
	$page .= '<div class="subparagraph">'.t('CLAN_BANK_TRANSACTION', $clan->name).'</div>' ;
	$limit=20;
	
	$query1  = 'select cid from clan_bank where cid='.$clan->cid;
	$result1 = warquest_db_query($query1);	
	$total = warquest_db_num_rows($result1);
	
	if ($total == 0) {
	
		$message = t('CLAN_BANK_NO_LOG');
		$page .= warquest_box_icon('info', $message);
		
	} else {
		
		/* show bank transactions. */
		$query2  = 'select a.pid, a.amount, a.action, a.balance, ';
		$query2 .= 'date_format(a.date , "%d-%m-%Y %H:%i:%s") as date, ';
		$query2 .= '(select name from player where pid=a.pid) as name, '; 
		$query2 .= '(select country from player where pid=a.pid) as country '; 
		$query2 .= 'from clan_bank a where a.cid='.$clan->cid.' order by a.cbid desc ';
		$query2 .= 'limit '.$offset.','.$limit;
	
		$result2 = warquest_db_query($query2);	
		
		$page .= '<div class="box rows">';
		
		$page .= warquest_page_control($offset, $limit, $total, 1, '&cid='.$clan->cid);
		
		$page .= '<table>';
		
		$page .= '<tr>';
		$page .= '<th width="80">'.t('GENERAL_AGO').'</th>';
		$page .= '<th width="310">'.t('GENERAL_TRANSACTION').'</th>';
		$page .= '<th width="110">'.t('GENERAL_BALANCE').'</th>';
		$page .= '</tr>';
		
		while ($data2=warquest_db_fetch_object($result2)) {
		
			$page .= '<tr>';
			$page .= '<td>'.warquest_ui_ago($data2->date).'</td>';
			$page .= '<td>';
			
			switch ($data2->action) {

				case 10:		
					$page .= player_format($data2->pid, $data2->name, $data2->country).' '.t('BANK_TRANSACTION_TYPE_'.$data2->action);
					$page .= ' '.dollar_format($data2->amount).'.';
					break;
			
				case 11:		
					$page .= t('BANK_TRANSACTION_TYPE_'.$data2->action,t('GENERAL_PLANET_'.$data2->pid)).' ';
					$page .= ' '.dollar_format($data2->amount).'.';
					break;
					
				default:			
					$page .= t('BANK_TRANSACTION_TYPE_'.$data2->action);
					$page .= ' '.dollar_format($data2->amount).'.';
					break;
			}
		
			$page .= '</td>';
			$page .= '<td>'.money_format1($data2->balance).'</td>';
			$page .= '</tr>';
		}
		
		$page .= '</table>';
	
		$page .= warquest_page_control($offset, $limit, $total, 0, '&cid='.$clan->cid);
		
		$page .= '</div>';
	}
}

/** 
 * Clan profile skill part
 */
function warquest_clan_skills_part($clan) {

	/* input	*/
	global $mid;
	global $sid;
	
	global $player;	
	global $config;
	
	/* output */
	global $page;
	
	$strength = warquest_db_clan_strength($clan->cid);
	
	$page .= '<div class="subparagraph">';
	$page .= t('CLAN_SKILLS', $clan->name);
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
	if ($clan->pid==$player->pid) {
		$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&cid='.$clan->cid.'&eid='.EVENT_CLAN_SKILL_INCREASE.'&id=1', t('LINK_INCREASE'), "increase1");
	}
	$page .= '</td>';
		
	$page .= '<td width="65" align="right">';
	if ($clan->pid==$player->pid) {
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
	if ($clan->pid==$player->pid) {
		$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&cid='.$clan->cid.'&eid='.EVENT_CLAN_SKILL_INCREASE.'&id=2', t('LINK_INCREASE'), "increase2");
	}
	$page .= '</td>';
	
	$page .= '<td>';
	if ($clan->pid==$player->pid) {
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
}

/** 
 * Clan profile member part
 */
function warquest_clan_member_part($clan) {

	/* input	*/
	global $mid;
	global $sid;
	
	global $player;	
	global $config;
	
	/* output */
	global $page;
	
	$page .= '<div class="subparagraph">';
	$page .= t('CLAN_MEMBER_LIST', $clan->name);
	$page .= '</div>';
	
	$query  = 'select a.joined, a.approved, b.pid, b.name, b.country, b.lid, b.experience ';
	$query .= 'from player_clan a, player b where a.pid=b.pid and a.cid='.$clan->cid.' ';
	$query .= 'order by b.lid desc';

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
		
		$page .= '<th width="80">';
		$page .= t('GENERAL_APPROVED');
		$page .= '</th>';

		$page .= '<th width="80">';
		$page .= t('GENERAL_JOINED');
		$page .= '</th>';
				
		$page .= '<th width="100">';
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
			if ($clan->pid == $player->pid) {	
			
				if ($data->approved==0) {			
					$page .= warquest_link('mid='.$mid.'&sid='.PAGE_CLAN_PROFILE.'&cid='.$clan->cid.'&oid='.$data->pid.'&eid='.EVENT_CLAN_ACCEPT, t('LINK_ACCEPT'));							
					$page .= '&nbsp;&nbsp';
				}
					
				$page .= warquest_link('mid='.$mid.'&sid='.PAGE_CLAN_PROFILE.'&cid='.$clan->cid.'&oid='.$data->pid.'&eid='.EVENT_CLAN_DROP, t('LINK_DROP'));							
			}
			$page .= '</td>';
	
			$page .= '</tr>';
		}
		
		$page .= '</table>';
		
		$page .= '</div>';
	}
}

/** 
 * Clan profile slogan part
 */
function warquest_clan_slogan_part($clan) {

	/* input	*/
	global $mid;
	global $sid;
	
	global $player;	
	global $comment;
	
	/* output */
	global $page;
	
	$page .= '<div class="subparagraph">';
	$page .= t('CLAN_SLOGAN', $clan->name);
	$page .= '</div>';

	if ($clan->pid==$player->pid) {	
		
		$page .= '<div class="box">';
		
		$page .= "<script language=\"JavaScript\" type=\"text/javascript\">function limitText(limitField, limitNum) { if (limitField.value.length >= limitNum) { limitField.value = limitField.value.substring(0, limitNum); } } </script>";
					
		$page .= '<table>';
		$page .= '<tr>';
		$page .= '<td width="500">';
	
		$page .= '<textarea style="width:100%" id="slogan" name="slogan" rows="3" ';
		$page .= 'onKeyDown="limitText(this,199)">'.$clan->slogan.'</textarea><br/>';
		$page .= warquest_show_smilies('slogan');
		$page .= '<br/><br/>';
	
		$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&cid='.$clan->cid.'&eid='.EVENT_CLAN_SLOGAN, t('LINK_SAVE'), 'save');
		
		$page .= '</td>';
		$page .= '</tr>';
		$page .= '</table>';
		$page .= '</div>';
				
	} else {
	
		$page .= '<div class="box">';
		
		$page .= '<div class="slogan">';
		$page .= warquest_parse_smilies($clan->slogan);
		$page .= '</div>';
		
		$page .= '</div>';
	} 
}

/** 
 * Clan profile statistics part
 */
function warquest_clan_statistics_part($clan) {

	/* input	*/
	global $mid;
	global $sid;
	
	/* output */
	global $page;
	
	$query  = 'select pid from player_clan where cid='.$clan->cid;	
	$result = warquest_db_query($query);	 	
	$size = warquest_db_num_rows($result);
	
	$page .= '<div class="subparagraph">'.t('CLAN_STATISTICS', $clan->name).'</div>';
	  	
	$page .= '<div class="box">';
	
	$page .= '<table>';
	
	$page .= '<tr>';
	$page .= '<td width="170">'.t('CLAN_FIGHTS_WON').':</td>';
	$page .= '<td   width="85">'.number_format($clan->won,0,",",".").'</td>';
	$page .= '<td width="170">'.t('CLAN_FIGHTS_LOST').':</td>';
	$page .= '<td  width="80">'.number_format($clan->lost,0,",",".").'</td>';
	$page .= '</tr>';
		
	$page .= '<tr>';
	$page .= '<td>'.t('CLAN_WON_LOST_RATIO').':</td>';
	$tmp=0;
	if ($clan->lost>0) {
		$tmp = round(($clan->won/$clan->lost),2);
	}
	$page .= '<td >'.$tmp.'</td>';
	$page .= '<td>'.t('CLAN_MISSIONS_COMPLETED').':</td>';
	$page .= '<td >'.number_format($clan->mission,0,",",".").'</td>';	
	$page .= '</tr>';
	
	$page .= '<tr>';
	$page .= '<td>'.t('CLAN_SIZE').':</td>';
	$page .= '<td >'.$size.'</td>';
	$page .= '<td>'.t('CLAN_LAST_ACTIVE').':</td>';
	$page .= '<td >'.warquest_ui_ago($clan->last_activity).'</td>';
	$page .= '</tr>';
	
	$page .= '</table>';
	
	$page .= '</div>';
}

function warquest_clan_profile_form() {

	/* input */	
	global $cid;
	global $player;
		
	/* output */
	global $page;
	global $output;
		
	$clan = warquest_db_clan($cid);
	$player_clan = warquest_db_player_clan($player->pid);
	
	$output->title = t('CLAN_PROFILE', $clan->name);
	
	warquest_clan_statistics_part($clan);
	warquest_clan_bank_part($clan, $player_clan);
	warquest_clan_skills_part($clan);
	warquest_clan_member_part($clan);
	warquest_clan_slogan_part($clan);
	
	$page .= '<div class="note">';
	$page .= t('CLAN_PROFILE_NOTE');
   $page .= '</div>';	
}

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
	$limit = 25;
	
	$output->title = t('CLAN_TITLE');

	$player_clan = warquest_db_player_clan($player->pid);
	
	/* Get pending alliance player */
	$page .= '<div class="subparagraph">';
	$page .= t('CLAN_TITLE');
	$page .= '</div>';
	
	if ($player->lid >= $lid) {
	
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
	
	$query  = 'select a.cid, a.name, a.created, a.won, a.lost, a.pid, ';
	$query .= '(select name from player where pid=a.pid) as name2, ';
	$query .= '(select country from player where pid=a.pid) as country2, ';
	$query .= '(select count(*) from player_clan where approved=1 and cid=a.cid) as size, ';
	$query .= '(select count(*) from player_clan d where d.cid=a.cid and d.pid='.$player->pid.') as joined ';
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
						
		$page .= '<th width="160">';
		$page .= t('GENERAL_NAME');
		$page .= '</th>';
		
		$page .= '<th width="60">';
		$page .= t('GENERAL_SIZE');
		$page .= '</th>';
		
		$page .= '<th width="60">';
		$page .= t('GENERAL_WON');
		$page .= '</th>';

		$page .= '<th width="60">';
		$page .= t('GENERAL_LOST');
		$page .= '</th>';		
				
		$page .= '<th width="180">';
		$page .= t('GENERAL_COMMANDER');
		$page .= '</th>';
		
		$page .= '<th width="80">';
		$page .= '</th>';
		
		$page .= '</tr>';
		
		while ($data = warquest_db_fetch_object($result)) {
		
			$page .= '<tr>';

			$page .= '<td>';
			$page .= warquest_image("other/clan.jpg", 'width="32" height="22"').' ';
			$page .= warquest_link('mid='.$mid.'&sid='.PAGE_CLAN_PROFILE.'&cid='.$data->cid, $data->name);
			$page .= '</td>';
					
			$page .= '<td>';
			$page .= $data->size;
			$page .= '</td>';
			
			$page .= '<td>';
			$page .= number_format($data->won,0,",",".");
			$page .= '</td>';
			
			$page .= '<td>';
			$page .= number_format($data->lost,0,",",".");
			$page .= '</td>';
									
			$page .= '<td>';
			$page .= player_format($data->pid, $data->name2, $data->country2, 1);
			$page .= '</td>';
			
			$page .= '<td>';

			if (isset($player_clan->cid)) {		
				if ($data->cid == $player_clan->cid) {
					$page .= warquest_link('mid='.$mid.'&sid='.PAGE_CLAN.'&cid='.$data->cid.'&eid='.EVENT_CLAN_LEAVE, t('LINK_LEAVE'));			
				}
			} else {
				$page .= warquest_link('mid='.$mid.'&sid='.PAGE_CLAN.'&cid='.$data->cid.'&oid='.$data->pid.'&eid='.EVENT_CLAN_JOIN, t('LINK_JOIN'));				
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
			
		case EVENT_CLAN_SLOGAN:
			warquest_clan_slogan_do();
			break;	
			
		case EVENT_CLAN_DEPOSIT:
			warquest_clan_deposit_do();
			break;
			
		case EVENT_CLAN_SKILL_INCREASE:
			warquest_clan_skill_increase_do();
			break;
			
		case EVENT_CLAN_SKILL_DECREASE:
			warquest_clan_skill_decrease_do();
			break;
	}
	
	switch ($sid) {

		case PAGE_CLAN: 
					warquest_clan_form();
					break; 
					
		case PAGE_CLAN_PROFILE: 
					warquest_clan_profile_form();
					break; 
	}				  	
}

/*
** ---------------------------------------------------------------- 
** THE END
** ----------------------------------------------------------------
*/

?>