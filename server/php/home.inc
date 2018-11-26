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
**  All copyrights reserved (c) 1996-2016 PlaatSoft
*/

/*
** ---------------------
** Post Parameters
** ---------------------
*/

$comment = warquest_post('comment', '');
 
/*
** --------------- 
** Actions
** ---------------
*/

/** 
 * Remove comment action
 */
function warquest_home_comment_delete_do() {
	
	/* input */
	global $uid;
	
	/* output */
	global $comment;
	global $output;
	
	if (warquest_db_comment_delete($uid) == 1) {
		
		$message = t('HOME_MESSAGE_DELETED');
		$output->popup .= warquest_box_icon("info", $message);		
		
		$comment="";
		$uid=0;
	}
}

/** 
 * Home message save action
 */
function warquest_home_comment_save_do() {

	/* input */
	global $player;
	global $uid;
	global $other;
	global $comment;

	/* output */
	global $output;

	if (strlen($comment)>0) {
	
		if ($uid==0) {
			warquest_db_comment_insert(0, 0, $player->pid, $other->pid, $comment);
		} else {		
			warquest_db_comment_update($uid, $comment);
		}
		
		if (isset($other->pid)) {
		
			$other->comment_notification++;
			warquest_comment_mail($other->pid, $comment, $player->name);
			$message = t('ALLIANCE_COMMENT_PLAYER', player_format($other->pid, $other->name, $other->country));
			
		} else {
		
			$message = t('ALLIANCE_COMMENT_ALL');
			warquest_info("Post message: ".$comment);		
		}		

		/* Clear input parameters */
		$uid = 0;
		
		$output->popup .= warquest_box_icon("info", $message);
	}
}

/** 
 * Home message edit action
 */
function warquest_home_comment_edit_do() {

	/* input */
	global $mid;
	global $sid;
	global $uid;
	global $other;
		 
	/* output */
	global $page;
			
	if ($uid!=0) {
		$query  = 'select comment from comment where id='.$uid;
		$result = warquest_db_query($query);
		$data = warquest_db_fetch_object($result);
		
		$comment = $data->comment;
		
	} else {
	
		/* Clear input parameters */
		$comment = "";
	}
	
	$page .= "<script language=\"JavaScript\" type=\"text/javascript\">function limitText(limitField, limitNum) { if (limitField.value.length >= limitNum) { limitField.value = limitField.value.substring(0, limitNum); } } </script>";
		
	$page .= '<div class="box">';	
	
	$page .= '<table>';
	$page .= '<tr>';
	$page .= '<td width="500">';

	if (isset($other->pid)) {
		$tmp = player_format($other->pid, $other->name, $other->country);
	} else {
		$tmp = t('GENERAL_ALL');
	}
	$page .= t('ALLIANCE_COMMENT_TEXT2', $tmp).'<br/>'; 
	
	$page .= '<textarea style="width:100%" id="comment" name="comment" rows="5" ';
	$page .= 'onKeyDown="limitText(this,400)">'.$comment.'</textarea><br/>';
	$page .= warquest_show_smilies();
	$page .= '<br/><br/>';
	
	if (isset($other->pid)) {
		$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_HOME_COMMENT_SAVE.'&oid='.$other->pid.'&uid='.$uid, t('LINK_SAVE'), 'save').' ';
	} else {
		$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_HOME_COMMENT_SAVE.'&uid='.$uid, t('LINK_SAVE'), 'save').' ';
	}
	
	if ($uid!=0) {
		$page .= ' ';
		$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_HOME_COMMENT_DELETE.'&uid='.$uid, t('LINK_DELETE'), 'delete');
	}
	
	$page .= '</td>';
	$page .= '</tr>';
	$page .= '</table>';

	$page .= '</div>';	
}

/*
** --------------- 
** UI
** ---------------
*/

/** 
 * Home messages page 
 */
function warquest_home_messages() {
   
	/* input */
	global $mid;
	global $sid;
	global $offset;
	
	/* output */
	global $page;
	global $player;
	global $output;
	
	/* Clear new flag */
	$player->comment_notification=0;
		
	$output->title = t('HOME_MESSAGES_TITLE');
	
	$limit=30;
	
	$query  = 'select pid1 from comment where pid2='.$player->pid.' and deleted=0';
	$result = warquest_db_query($query); 
	$total = warquest_db_num_rows($result);
	
	$query  = 'select a.id, a.pid1, a.pid2, a.date, a.comment, a.cid, b.name, b.country from comment a, player b ';
   $query .= 'where ((a.pid1=b.pid and pid2='.$player->pid.') or (a.pid2=b.pid and pid1='.$player->pid.')) ';
	$query .= 'and deleted=0 order by a.date desc ';
	$query .= 'limit '.$offset.','.$limit;
	$result = warquest_db_query($query);
	$count = warquest_db_num_rows($result);
			
	$page .= '<div class="subparagraph">'.t('HOME_MESSAGES_TITLE').'</div>';
	
	if ($count==0) {
		
		$page .= warquest_box_icon("info",t('HOME_NO_MESSAGES'));
		
	} else {
		
		$page .= '<div class="box rows">';
	
		$count=0;
		
		$page .= warquest_page_control($offset, $limit, $total, 1);
		
		$page .= '<table>';
		
		$page .= '<tr>';
		$page .= '<th width="75" >'.t('GENERAL_AGO').'</th>';
		$page .= '<th width="390">'.t('GENERAL_MESSAGE').'</th>';
		$page .= '<th width="55" align="right">'.t('GENERAL_ACTION').'</th>';
		$page .= '</tr>';
		
		while ($data=warquest_db_fetch_object($result)) {
	
			$count++;
		
			$page .= '<tr valign="top">';
			$page .= '<td>';
			$page .= warquest_ui_ago($data->date);
			$page .= '</td>';
			
			$page .= '<td>';
			
			$page .= '<span class="subparagraph2">';
			if ($player->pid==$data->pid2) {
				$page .= player_format($data->pid1, $data->name, $data->country);
				$page .= ' -> '.player_format($player->pid, $player->name, $player->country);
			} else {
				$page .= player_format($player->pid, $player->name, $player->country);
				$page .= ' -> ';
				
				if ($data->cid > 0) {
					$clan = warquest_db_clan($data->cid);
					$page .= clan_format($clan).' clan';
					
				} else if ($data->pid2==0) {
					$page .= t('GENERAL_ALL');
					
				} else {
					$page .= player_format($data->pid2, $data->name, $data->country);
				}
			}
			$page .= '</span>';
			$page .= '<br/>';
			$page .= warquest_parse_smilies(wordwrap($data->comment, 40, "\n\r", true));
			
			$page .= '</td>';
			
			$page .= '<td align="right">';
			
			if ($player->pid==$data->pid2) {
				$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_HOME_COMMENT_EDIT.'&oid='.$data->pid1, t('LINK_REPLY'), "reply".$count);	
			} else if ($player->pid==$data->pid1) {
				$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_HOME_COMMENT_EDIT.'&oid='.$data->pid2.'&uid='.$data->id, t('LINK_EDIT'), 'edit'.$count);
			}
			
			$page .= '</td>';
			
			$page .= '</tr>';
		}
		
		$page .= '</table>';
		
		$page .= warquest_page_control($offset, $limit, $total, 0);
		$page .= '</div>';
	
	} 
}


/** 
 * Home News page 
 */
function warquest_home_news() {
   
	/* input */
	global $mid;
	global $config;
	global $offset;
	
	/* output */
	global $page;
	global $player;
	global $output;
	
	/* Max records. */
	$limit = 25;
	
	$output->title = t('HOME_BATTLE_TITLE');
		
	/* Clear new flag */
	$player->news_notification=0;
		
	$query  = 'select id from battle where pid2='.$player->pid;
	$result = warquest_db_query($query);	
	$total = warquest_db_num_rows($result);
	
	$query  = 'select a.id, a.ugid, a.pid1, a.money, a.experience, a.bounty, a.health as health1, a.win, ';
	$query .= 'date_format(a.date , "%d-%m-%Y %H:%i:%s") as date, b.cease_fire_date, b.holiday_date, ';
   $query .= 'b.name, b.country, b.health, b.health_date, b.health_step, b.lid, b.alliance, ';
	$query .= '(select c.planet from unit_group c where c.ugid=a.ugid) as planet ';
	$query .= 'from battle a, player b where a.pid1=b.pid and ';
	$query .= 'a.pid2='.$player->pid.' order by id desc ';
	$query .= 'limit '.$offset.','.$limit;
	
	$result = warquest_db_query($query); 
	$count = warquest_db_num_rows($result);
		
	$page .= '<div class="subparagraph">'.t('HOME_BATTLE_TITLE').'</div>';
		
	if ($count>0) {
	
		$page .= '<div class="box rows">';
		
		$page .= warquest_page_control($offset, $limit, $total, 1);
	
		$page .= '<table>';

		$page .= '<tr>';
		$page .= '<th width="75">'.t('GENERAL_AGO').'</th>';
		$page .= '<th width="370">'.t('GENERAL_MESSAGE').'</th>';
		$page .= '<th width="55" align="right">'.t('GENERAL_ACTION').'</th>';
		$page .= '</tr>';
		
		
		while ($data=warquest_db_fetch_object($result)) {
	
			$page .= '<tr valign="top">';
			$page .= '<td>'.warquest_ui_ago($data->date).'</td>';
			
			$page .= '<td>';
			
			$tmp = player_format($data->pid1, $data->name, $data->country);
			if (warquest_battle_surrender($data)==1) {
				$tmp .= warquest_image('other/surrender.png',' width="16" height="16" title="'.t("BATTLE_SURRENDER").'"');
			}
					
					
			if ($data->bounty>0) {
			
				$page .= t('HOME_BOUNTY_NEWS', 
								$tmp, 
								money_format1($data->money), 
								number_format($data->experience,0,",","."));
			} else {
								
				if ($data->win==0) {
			
					$page .= t('HOME_BATTLE_ATTACK_BY',	strtolower(t('GENERAL_PLANET_'.$data->planet)).' '.strtolower(t('UNIT_GROUP_'.$data->ugid)),$tmp);				
					$page .= t('HOME_BATTLE_YOU_WON');
					$page .= t('HOME_BATTLE_YOU_EXP', experience_format($data->experience));
					$page .= t('HOME_BATTLE_TOOK_DAMAGE', health_format($data->health1));
				
				} else {
			
					if ($data->experience>0) {
					
						$page .= t('BATTLE_BOUNTY_LOST', 
											strtolower(t('GENERAL_PLANET_'.$data->planet)).' '.strtolower(t('UNIT_GROUP_'.$data->ugid)),									
											$tmp,
											money_negative($data->money),
											health_format($data->health1),
											experience_format($data->experience));
					} else {
					
						$page .= t('HOME_BATTLE_ATTACK_BY',	strtolower(t('GENERAL_PLANET_'.$data->planet)).' '.strtolower(t('UNIT_GROUP_'.$data->ugid)), $tmp);
						$page .= t('HOME_BATTLE_YOU_LOST');
						$page .= t('HOME_BATTLE_YOU_MONEY', money_negative($data->money));
						$page .= t('HOME_BATTLE_TAKING_DAMAGE', health_format($data->health1));
					
					}
				}
			} 
			$page .= '</td>';
			
			$page .= '<td align="right">';
			 
			 
			if ( ($player->cease_fire_date < date("Y-m-d H:i:s", time())) && 
				  ($data->cease_fire_date < date("Y-m-d H:i:s", time())) && 
				  ($player->holiday_date < date("Y-m-d H:i:s", time())) && 
				  ($data->holiday_date < date("Y-m-d H:i:s", time())) ) {
				$page .= warquest_link('mid='.MENU_BATTLE.'&sid='.PAGE_ENEMIES.'&oid='.$data->pid1.'&eid='.EVENT_BATTLE_NORMAL, t('LINK_ATTACK'), "attack");			
			}
			
			$page .= '</td>';
						
			$page .= '</tr>';
		}
		$page .= '</table>';
		$page .= warquest_page_control($offset, $limit, $total, 0);
				
		$page .= '</div>';
	
	} else {
	
		$page .= warquest_box_icon("info",t('HOME_BATTLE_NO_NEWS'));
	}	
}

/** 
 * Last Forum post item on home page 
 */
function warquest_lastest_forum_post() {
	
	global $mid;
	global $sid;
	global $player;
	global $config;
	
	global $page;
	
	if (warquest_db_query_pattern($player, PATTERN_FORUM_SORT)==0) {
		return;
	}
	
	$query   = 'select b.tid, b.fid, b.description, a.date, c.pid as pid1, c.name as name1, ';
	$query  .= 'c.country as country1, d.pid as pid2, d.name as name2, d.country as country2 ';
	$query  .= 'from comment as a left join topic as b on a.tid=b.tid ';
	$query  .= 'left join player c on a.pid1=c.pid left join player d on b.pid=d.pid ';
	$query  .= 'where a.deleted=0 and b.deleted=0 order by a.id desc limit 1';
			
	$result = warquest_db_query($query);	
	$data = warquest_db_fetch_object($result);
	
	if (isset($data->tid)) {
		$page .= '<div class="subparagraph">'.t('HOME_LASTEST_FORUM_ITEM').'</div>';
		$page .= '<div class="box">';
	
		$page .= '<table>';
	
		$page .= '<tr>';
	
		$page .= '<td width="75">';
		$page .= '<b></b>';
		$page .= '</td>';
		
		$page .= '<td width="215">';
		$page .= '</td>';

		$page .= '<td width="210">';
		$page .= '</td>';
		
		$page .= '</tr>';
						
		$query  = 'select id from comment where deleted=0 and tid='.$data->tid;	
		$result = warquest_db_query($query);
		$count = warquest_db_num_rows($result);
							
		$page .= '<tr>';
			
		$page .= '<td>';
		$page .= warquest_link('mid='.MENU_FORUMS.'&sid='.PAGE_COMMENT.'&fid='.$data->fid.'&tid='.$data->tid,
			warquest_image('other/forum.png','width="64" height="64"'), 'forum1');
		$page .= '</td>';
				
		$page .= '<td valign="top">';
		$page .= '<span class="topic">';
		$page .= warquest_link('mid='.MENU_FORUMS.'&sid='.PAGE_COMMENT.'&fid='.$data->fid.'&tid='.$data->tid, 
			warquest_parse_smilies($data->description),'forum2');
		$page .= '</span>';	
		$page .= '<br/>';
		$page .= '<i>';	
		$page .= t('TOPIC_CREATED_BY', player_format($data->pid2, $data->name2, $data->country2));
		$page .= '</i>';
			
		$page .= '</td>';
				
		$page .= '<td valign="top">';
		$page .=  health_format($count).' '.t('GENERAL_MESSAGES').' ';
			
		$page .= '<br/>';
			
		if (isset($data->date)) {
			$page .= '<br/><b>'.t('GENERAL_LAST_MESSAGE').'</b><br/>';
	
			$page .= warquest_ui_ago($data->date).' '.t('GENERAL_BY').' ';
			$page .= player_format($data->pid1, $data->name1, $data->country1);
		}
		$page .= '</td>';
		$page .= '</tr>';
				
		$page .= '</table>';
			
		$page .= '</div>';
	}
}

/** 
 * Holiday item on home page 
 */
function warquest_holiday_message() {

	/* input */
	global $player;
	global $config;
	
	/* output */
	global $page;
	
	if ($player->holiday_date > date("Y-m-d H:i:s", time())) {
	
		$value = strtotime($player->holiday_date)-time();
	
		$page .= '<script language="JavaScript" src="'.$config["content_url"].'js/countdown5.js" type="text/javascript"></script>';
	
		$tmp = '<div class="countdown"><div id="countdown_time5"></div></div>';		
				
		$message  = '<table>';
		$message .= '<tr>';
		$message .= '<td width="200">';
		$message .= warquest_image("restore/restore8.jpg", ' width="170" height="120" ');
		$message .= '</td>';
		$message .= '<td>';
		$message .= '<div class="subparagraph"><b>'.t('HOME_HOLIDAY').'</b></div>';
		$message .= t('HOME_HOLIDAY_PERIOD_ACTIVE', $tmp);
		$message .= '</td>';
		$message .= '</tr>';
		$message .= '</table>';
						
		$page .= warquest_box("", $message);	
						
		$page .= '<script language="JavaScript" type="text/javascript">';
		$page .= "countdown5.init(".$value.", 'countdown_time5', '00:00:00');"; 
		$page .= '</script>';
	}
}
		
/** 
 * Daily bonus item on home page 
 */
function warquest_daily_bonus() {

	/* input */
	global $config;
	
	/* output */
	global $player;
	global $page;
		
	if ($player->holiday_date > date("Y-m-d H:i:s", time())) {
	
		/* No bonus if holiday is activated! */
		return;
	}
				
	if (date("Y-m-d",strtotime( $player->bonus_date)) != date("Y-m-d")) {
	
		/* Update last_login date for player with long session (>24h) */
		$member = warquest_db_member($player->pid);
		$member->last_login = date("Y-m-d H:i:s");				
		warquest_db_member_update($member);
				
		/* Add bonus */
		$money = $config["init_money"] * $player->lid * rand(20,40);

		$player->bonus_date = date("Y-m-d H:i:s");
		$player->money += $money;
		
		$log = 'Daily bonus '.number_format2($money);		
		warquest_user_log($player, $log);
	
		/* Create message */
 		if ($money>0) {
			$message = t('HOME_DAILY_BONUS', money_format1($money) );		
			$page .= warquest_box_icon("info", $message);			
		}
		
		/* One year WarQuest bonus */
		if ( date("Y-m-d", strtotime("08-02-2012")) == date("Y-m-d") ) {
			
			$skill = warquest_db_skill($player->pid);
			$skill->skill_points+= 10;
			warquest_db_skill_update($skill);
			
			$bonus = 10000000000;
			$player->bank1+=$bonus;		
			warquest_db_bank_insert($player->pid, 0, 1, $bonus, $player->bank1, 6);				
		}	
	}		
}

/** 
 * Mission map item on home page 
 */
function warquest_show_map() {

	/* input */
	global $player;
	global $mid;
	global $sid;
	
	/* output */
	global $page;
	
	$page .= '<div class="subparagraph">'.t('GENERAL_PLANET_'.$player->planet).' '.t('HOME_MAP_TITLE').'</div>';

	$page .= '<div class="box">';
	$page .= warquest_ui_map($player, $player->planet);
	
	$page .= '<div class="note"><center>';
	$page .= t('HOME_MAP_NOTE');
	$page .= '</center></div>';	
		
	$page .= '</div>';
}

/** 
 * Award item on home page 
 */
function warquest_view_awards() {

	/* input */
	global $player;
	global $config;
	global $browser;
	
	$page = '<div class="award">';
	
	/* Get battle award data */
	$query =  "select id, won from battle_award where id<".$player->won_level.' order by id';  
	$result = warquest_db_query($query);
	$count = warquest_db_num_rows($result);
	
	if ($count>0) {
			
		$page .= '<br/>';
		$page .= t('HOME_BATTLE_AWARDS_TEXT');
		$page .= '<br/>';
		
		while ($data = warquest_db_fetch_object($result)) {
 		
			$max=9;		
			$page .= warquest_battle_award_image($data->id, $data->won);
					
			if ((($data->id % $max)==0) && ($data->id!=$count)) { 
				$page .='<br/>';
			}
		}
		
		$page .= '<br/>';
	}
			
	/* Get mission award data */
	$query =  "select id, won from mission_award where id<".$player->mission_level.' order by id';  
	$result = warquest_db_query($query);
	$count = warquest_db_num_rows($result);
	
	if ($count>0) {
	
		$page .= '<br/>';
		$page .= t('HOME_MISSION_AWARDS_TEXT');
		$page .= '<br/>';
		
		while ($data = warquest_db_fetch_object($result)) {
 		
			$max=9;		
			$page .= warquest_mission_award_image($data->id, $data->won);
					
			if ((($data->id % $max)==0) && ($data->id!=$count)) { 
				$page .='<br/>';
			}
		}
		
		$page .= '<br/>';
	}
	
	/* Get bounty award data */
	$query =  "select id, amount from bounty_award where id<".$player->bounty_level.' order by id';  
	$result = warquest_db_query($query);
	$count = warquest_db_num_rows($result);
	
	if ($count>0) {
	
		$page .= '<br/>';
		$page .= t('HOME_BOUNTY_AWARDS_TEXT');
		$page .= '<br/>';
		
		while ($data = warquest_db_fetch_object($result)) {
 		
			$max=9;		
			$page .= warquest_bounty_award_image($data->id, $data->amount);
					
			if ((($data->id % $max)==0) && ($data->id!=$count)) { 
				$page .='<br/>';
			}
		}
		
		$page .= '<br/>';
	}
	
	/* Get rebel award data */
	$query =  "select id, amount from rebel_award where id<".$player->rebel_level.' order by id';  
	$result = warquest_db_query($query);
	$count = warquest_db_num_rows($result);
	
	if ($count>0) {
	
		$page .= '<br/>';
		$page .= t('HOME_REBEL_AWARDS_TEXT');
		$page .= '<br/>';
		
		while ($data = warquest_db_fetch_object($result)) {
 		
			$max=9;		
			$page .= warquest_rebel_award_image($data->id, $data->amount);
					
			if ((($data->id % $max)==0) && ($data->id!=$count)) { 
				$page .='<br/>';
			}
		}
		
		$page .= '<br/>';
	}
	
	$page .= '</div>';
	
	return $page;
}	

/** 
 * Welcome item on home page
 */
function warquest_home_welcome() {

	/* input */
	global $player;
	global $mid;
	global $sid;
	global $config;
	
	/* output */
	global $page;
	global $output;
	
	$output->title = t('HOME_OVERVIEW_TITLE');
		
	$page .= '<div class="subparagraph">'.t('HOME_OVERVIEW_TITLE').'</div>';
	
	$page .= '<div class="box">';

	if ($player->lid <= 5) {
	
		$page .= '<br/>';
	
		$query1 = 'select ugid from unit_group where type=2 and planet='.$player->planet;
		$result1 = warquest_db_query($query1);
		$data1 = warquest_db_fetch_object($result1);

		$query2 = 'select bgid from building_group where planet='.$player->planet.' order by bgid limit 1';
		$result2 = warquest_db_query($query2);
		$data2 = warquest_db_fetch_object($result2);
	
		$page .= warquest_image('other/commander.jpg', ' align="left" width="160" height="120" ');
		
		$page .= t('HOME_WELCOME', warquest_rank($player->lid), player_format($player->pid, $player->name, $player->country));
		$page .= '<br/><br/>';
	
		$page .= t('HOME_INTRO_MISSIONS', warquest_link('mid='.MENU_MISSIONS.'&sid='.PAGE_MISSION_PLAYER.'&ssid='.warquest_get_default_mission($player->planet),t('LINK_MISSIONS'), 'mission1'));
		$page .= t('HOME_INTRO_BATTLES', warquest_link('mid='.MENU_BATTLE.'&sid='.PAGE_ENEMIES,t('LINK_BATTLES'), 'battle1'));
		$page .= t('HOME_INTRO_UNITS', warquest_link('mid='.MENU_UNITS.'&sid='.PAGE_UNIT_PLAYER.'&ssid='.$data1->ugid, t('LINK_UNITS'), 'unit1'));
		$page .= t('HOME_INTRO_BUILDINGS', warquest_link('mid='.MENU_BUILDINGS.'&sid='.$data2->bgid, t('LINK_BUILDINGS'), 'building1'));
		
		$page .= '<br/>';			
		
	} else {
	
		/*$query1 =  'select count(pid) as count, sum(won) as won from player';
		$result1 = warquest_db_query($query1); 
		$data1 = warquest_db_fetch_object($result1);*/
		
		/*$query =  'select distinct(country) from player';
		$result = warquest_db_query($query); 
		$count = warquest_db_num_rows($result);*/
			
		$query2 =  'select pid from player where country="'.$player->country.'" and experience>='.$player->experience;
		$result2 = warquest_db_query($query2);
		$count2 = warquest_db_num_rows($result2);
		
		$query3 =  'select pid from player where experience>='.$player->experience.' and country!="EU"';
		$result3 = warquest_db_query($query3);
		$count3 = warquest_db_num_rows($result3);
	
		/*$yesterday = mktime(date("H"), date("i"), date("s"), date("m"), date("d")-1, date("Y"));
		$query4  = 'select count(pid) as count from member where last_login > "'.date("Y-m-d H:i:s", $yesterday).'" ';		
		$result4 = warquest_db_query($query4);
		$data4 =  warquest_db_fetch_object($result4);*/
	
		/*$query5 =  'select sum(requests) as requests from views';
		$result5 = warquest_db_query($query5); 
		$data5 = warquest_db_fetch_object($result5);*/
	
		$page .= '<div class="right">';
		$page .= warquest_rank_image($player->lid);
		$page .= '</div>';
	
		$page .= t('HOME_WELCOME', warquest_rank($player->lid), player_format($player->pid, $player->name, $player->country));
		
		$page .= '<br/><br/>';
	
		$member = warquest_db_member($player->pid);
		if ($member->prev_login!=0) {
			$page .= t('HOME_LAST_LOGIN', warquest_ui_ago($member->prev_login)).'<br/>';
		}
		$page .= '<br/>';
		
		$page .= t('HOME_INTRO_PLACE1', 
						warquest_link('mid='.MENU_PLAYERS.'&sid='.PAGE_LEADERBOARD.'&ssid='.PAGE_BEST_PLAYER, warquest_place($count3)));
		
		$code = sprintf("%03d%03d",ord($player->country[0]),ord($player->country[1]));
		$page .= t('HOME_INTRO_PLACE2', 
						warquest_link('mid='.MENU_PLAYERS.'&sid='.PAGE_LEADERBOARD.'&ssid='.PAGE_BEST_COUNTRY2.'&uid='.$code, warquest_place($count2)), warquest_landcode($player->country));
		$page .= '<br/>';
		
		/*$page .= '<br/>';		
		$page .= t('HOME_INTRO_PLAYERS', energy_format($data1->count), country_format($count));
		$page .= t('HOME_INTRO_FIGHTS', health_format($data1->won));
		$page .= t('HOME_INTRO_REQUESTS', money_format1($data5->requests));
		$page .= t('HOME_PLAYERS_ONLINE',energy_format($data4->count));			
		$page .= '<br/>';*/
	}
		
	$page .= warquest_view_awards();
	
	if ($player->lid > 4) {
		$page .= warquest_poll_teaser();	
	}

	/* Show tip */
	$page .= warquest_ui_tip();	
	$page .= '<div class="spacer"></div>';	
	
	$page .= '</div>';	
}

/** 
 * Show break news item on home page 
 */
function warquest_show_breaking_news() { 

	/* input */
	global $page;
	global $player;
	global $config;
	global $browser;

	$page .= '<div class="subparagraph">'.t('HOME_FLASH_NEWS_TITLE').'</div>';
	$message = '';
	
	$language="en";
	if (isset($player) && (strlen($player->language)>0)) {
		$language=$player->language;
	} 
		
	$query  = 'select date, body, content from news where language="en" order by id desc ';
	$result = warquest_db_query($query);
		
	while ($data=warquest_db_fetch_object($result)) {
			
		$message .= '<span class="money">';
		$message .= $data->body;
		$message .= '</span> ';
		$message .= $data->content;
		$message .= ' ';
	}
		
	$page .= '<div class="box">';
	
   $page .= '<marquee id="breakingnews" behavior="scroll" direction="left" scrollamount="4">';
	$page .= $message;
	$page .= '</marquee>';
	$page .= '</div>';
	
	$page .= '<script language="JavaScript" src="'.$config["content_url"].'js/news2.js" type="text/javascript"></script>';
	$page .= '<script language="JavaScript">';
	$page .= 'newsInit('.MENU_SERVICE.','.EVENT_GET_HEADLINES.'); newsCall();';
	$page .= '</script>';
}
	
/** 
 * Show ad on home page 
 */
function warquest_home_ad() {

	/* input */
	global $config;
	global $player;

	/* output */
	global $page;
	
	$page .= '<div class="subparagraph">'.t('HOME_ANNOUNCEMENTS').'</div>';
			
	$page .= '<a href="javascript:link(\''.warquest_token('mid='.MENU_HELP.'&sid='.PAGE_DONATE).'\')">';			
	$page .= warquest_image('other/ad1.png', 'width="510" height="75" id="ad" ');
	$page .= '</a>';
		
	$page .= '<script language="JavaScript" type="text/javascript">';
	$page .= 'var AdCount=1; ';
	$page .= 'var filename=""; ';
	$page .= 'function StartAd() { ';
	$page .= '  if (++AdCount>3) { AdCount=1; } ';
	$page .= '  filename = "'.$config["content_url"].'images/other/ad" + AdCount + ".png"; ';
	$page .= '  document.getElementById("ad").src = filename; ';
	$page .= '  setTimeout("StartAd()", 3000); ';
	$page .= '} ';
	$page .= 'StartAd();';
	$page .= '</script>'; 
}

/*
** --------------- 
** Handler
** ---------------
*/

function warquest_home() {
	
	/* input	*/
	global $sid;
	global $eid;
	global $other;
	global $player;
		
	/* Event handler */
	switch ($eid) {
			
		case EVENT_HOME_COMMENT_EDIT:
			warquest_home_comment_edit_do();
			break;
			
		case EVENT_HOME_COMMENT_SAVE:
			warquest_home_comment_save_do();
			break;

		case EVENT_HOME_COMMENT_DELETE:
			warquest_home_comment_delete_do();
			break;
			
		case EVENT_SWITCH_PLANET: 
			warquest_switch_planet_do();
			break;
	}	
	
	warquest_skills_event();
	warquest_restore_event();
	warquest_trade_event();
	warquest_settings_events();
						
	/* Page handler */
	switch ($sid) {
	 
		case PAGE_OVERVIEW: 	
					warquest_rebel_check($player);
					warquest_daily_bonus();
					warquest_nextlevel($player);
					warquest_battle_award_won($player);
					warquest_mission_award_won($player);
					warquest_bounty_award_won($player);
					warquest_rebel_award_won($player);
					warquest_holiday_message();
					warquest_home_welcome();
					warquest_show_breaking_news();
					warquest_lastest_forum_post();						
					warquest_show_map();	
					warquest_home_ad();
					break;
												
		case PAGE_BATTLE_NEWS:	
					warquest_home_news();
					break;
		
		case PAGE_MESSAGES:	
					warquest_home_messages();	
					break;
					
		case PAGE_SKILLS:	
					warquest_skills_form();
					break;
					
		case PAGE_TRADE: 
					warquest_trade_form();
					break;
					
		case PAGE_RESTORE:	
					warquest_restore_form();
					break;
						
		case PAGE_SETTINGS:	
					warquest_settings_form();
					break;	
	}
	
	warquest_player();
}

/*
** ------------------
** THE END
** ------------------
*/

?>