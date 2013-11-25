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
** Post Parameters
** ---------------------
*/

$comment = warquest_post('comment', '');
 
/*
** --------------- 
** Messages
** ---------------
*/

function warquest_home_comment_delete_do() {
	
	/* input */
	global $uid;
	
	/* output */
	global $comment;
	global $popup;
	
	if (warquest_db_comment_delete($uid) == 1) {
		
		$message = t('HOME_MESSAGE_DELETED');
		$popup .= warquest_box_icon("info", $message);		
		
		$comment="";
		$uid=0;
	}
}

function warquest_home_comment_save_do() {

	/* input */
	global $player;
	global $uid;
	global $other;
	global $comment;
	
	/* output */
	global $popup;

	if (strlen($comment)>0) {
	
		if ($uid==0) {
	
			warquest_db_comment_insert(0, $player->pid, $other->pid, $comment);
				
			if ($other->pid!=0) {
			
				$other->comment++;
				warquest_comment_mail($other->pid, $comment, $player->name);
				$message = t('ALLIANCE_COMMENT_PLAYER', player_format($other->pid, $other->name, $other->country));
			
			} else {
		
				$message = t('ALLIANCE_COMMENT_ALL');
				warquest_info("Post message: ".$comment);
			}
			
		} else {
		
			$query  = 'update comment set comment="'.$comment.'" where id='.$uid;			
			warquest_db_query($query);
			
			$message = t('ALLIANCE_COMMENT_ALL');
			warquest_info("Post message: ".$comment);	
		}
		
		/* Clear input parameters */
		$uid = 0;
		
		$popup .= warquest_box_icon("info", $message);
	}
}

function warquest_home_comment_edit_do() {

	/* input */
	global $mid;
	global $sid;
	global $uid;
	global $other;
		 
	/* output */
	global $page;
	global $title;
			
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

	$page .= t('ALLIANCE_COMMENT_TEXT2', player_format($other->pid, $other->name, $other->country)).'<br/>'; 
	
	$page .= '<textarea style="width:100%" id="comment" name="comment" rows="5" ';
	$page .= 'onKeyDown="limitText(this,400)">'.$comment.'</textarea><br/>';
	$page .= warquest_show_smilies();
	$page .= '<br/><br/>';
	
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&eid=2&oid='.$other->pid.'&uid='.$uid, t('LINK_SAVE'), 'save').' ';
	if ($uid!=0) {
		$page .= ' '.warquest_link('mid='.$mid.'&sid='.$sid.'&eid=3&uid='.$uid, t('LINK_DELETE'), 'delete');
	}
	
	$page .= '</td>';
	$page .= '</tr>';
	$page .= '</table>';

	$page .= '</div>';	
}

function warquest_home_messages() {
   
	/* input */
	global $mid;
	global $sid;
	global $offset;
	
	/* output */
	global $page;
	global $player;
	global $title;
	
	/* Clear new flag */
	$player->comment=0;
		
	$title = t('HOME_MESSAGES_TITLE');
	
	$limit=30;
	
	$query  = 'select pid1 from comment where pid2='.$player->pid.' and deleted=0';
	$result = warquest_db_query($query); 
	$total = warquest_db_num_rows($result);
	
	$query  = 'select a.id, a.pid1, a.pid2, a.date, a.comment, b.name, b.country from comment a, player b ';
   $query .= 'where ((a.pid1=b.pid and pid2='.$player->pid.') or (a.pid2=b.pid and pid1='.$player->pid.')) and deleted=0 order by a.date desc ';
	$query .= 'limit '.$offset.','.$limit;
	$result = warquest_db_query($query);
	$count = warquest_db_num_rows($result);
			
	$page .= '<div class="subparagraph">'.t('HOME_MESSAGES_TITLE').'</div>';
	
	if ($count>0) {
	
		$page .= '<div class="box">';
	
		$count=0;
		
		$page .= warquest_page_control($offset, $limit, $total, 1);
		
		$page .= '<table>';
		
		$page .= '<tr>';
		$page .= '<td width="75" ><b>'.t('GENERAL_AGO').'</b></td>';
		$page .= '<td width="390"><b>'.t('GENERAL_MESSAGE').'</b></td>';
		$page .= '<td width="55" align="right"><b>'.t('GENERAL_ACTION').'</b></td>';
		$page .= '</tr>';
		
		while ($data=warquest_db_fetch_object($result)) {
	
			$count++;
		
			$page .= '<tr valign="top">';
			$page .= '<td>';
			$page .= warquest_ui_ago($data->date);
			$page .= '</td>';
			
			$page .= '<td>';
			$page .= '<span class="subparagraph2">';
			if ($data->pid2==$player->pid) {
				$page .= player_format($data->pid1, $data->name, $data->country);
				$page .= ' -> '.player_format($player->pid, $player->name, $player->country);
			} else {
				$page .= player_format($player->pid, $player->name, $player->country).'-> ';
				$page .= player_format($data->pid2, $data->name, $data->country);
			}
			$page .= '</span>';
			$page .= '<br/>';

			$page .= warquest_parse_smilies(wordwrap($data->comment, 40, "\n\r", true));
			
			$page .= '</td>';
			
			$page .= '<td align="right">';
			
			if ($data->pid2==$player->pid) {
				$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&eid=1&oid='.$data->pid1, t('LINK_REPLY'), "reply".$count);	
			} else {
				if ($player->pid==$data->pid1) {
					$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&eid=1&uid='.$data->id.'&oid='.$data->pid2, t('LINK_EDIT'), 'edit'.$count);
				}
			}
			$page .= '</td>';
			
			$page .= '</tr>';
		}
		
		$page .= '</table>';
		
		$page .= warquest_page_control($offset, $limit, $total, 0);
		$page .= '</div>';
	
	} else {
	
		$page .= warquest_box_icon("info",t('HOME_NO_MESSAGES'));
	}
	
	$page .= warquest_show_ads();
}

/*
** --------------- 
** NEWS
** ---------------
*/


function warquest_home_news() {
   
	/* input */
	global $mid;
	global $config;
	global $offset;
	
	/* output */
	global $page;
	global $player;
	global $title;
	
	/* Max records. */
	$limit = 25;
	
	$title = t('HOME_BATTLE_TITLE');
		
	/* Clear new flag */
	$player->news=0;
		
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
	$count=warquest_db_num_rows($result);
		
	$page .= '<div class="subparagraph">'.t('HOME_BATTLE_TITLE').'</div>';
		
	if ($count>0) {
	
		$page .= '<div class="box">';
		
		$page .= warquest_page_control($offset, $limit, $total, 1);
	
		$page .= '<table>';

		$page .= '<tr>';
		$page .= '<td width="75"><b>'.t('GENERAL_AGO').'</b></td>';
		$page .= '<td width="370"><b>'.t('GENERAL_MESSAGE').'</b></td>';
		$page .= '<td width="55" align="right"><b>'.t('GENERAL_ACTION').'</b></td>';
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
				$page .= warquest_link('mid='.MENU_BATTLE.'&sid='.PAGE_ENEMIES.'&oid='.$data->pid1.'&eid=1', t('LINK_ATTACK'), "attack");			
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
	
	$page .= warquest_show_ads();
}

/*
** --------------- 
** OVERVIEW
** ---------------
*/

function warquest_ui_breaking_news() {

	/* input */
	global $page;
	global $player;
	global $config;
	global $browser;
		
	$language="en";
	if (isset($player) && (strlen($player->language)>0)) {
		$language=$player->language;
	} 
		
	$query  = 'select date, body, content from news where language="en" order by id desc ';
	$result = warquest_db_query($query);
	
	$message = '&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;';
	
	while ($data=warquest_db_fetch_object($result)) {
			
		$message .= '<span class="money">';
		$message .= $data->body;
		$message .= '</span> ';
		$message .= $data->content;
		$message .= '&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;';
	}
		
	$page .= '<div class="box">';
	
	if (preg_match("/Symbian/", $browser)) {
	   $page .= '<marquee behavior="scroll" direction="left" scrollamount="3">';
	} else if (preg_match("/MSIE/", $browser)) {
		//$page .= '<div id="TICKER" STYLE="overflow:hidden; width:490px">';
	} else {
		$page .= '<div id="TICKER" STYLE="overflow:hidden; width:500px">';
	}
		
	$page .= $message;
			
	if (preg_match("/Symbian/", $browser)) {
		$page .= '</marquee>';
		$page .= '</div>';
	} else {
		$page .= '</div>';
		$page .= '</div>';
		$page .= '<script type="text/javascript" src="'.$config["content_url"].'js/news.js" language="javascript"></script>';
	}
}

function warquest_lastest_forum_post() {
	
	global $mid;
	global $sid;
	global $player;
	global $config;
	
	global $page;
	
	if (warquest_db_query_pattern($player, PATTERN_FORUM_POST)==0) {
		return;
	}
	
	$query   = 'select b.tid, b.fid, b.description, a.date, c.pid as pid1, c.name as name1, ';
	$query  .= 'c.country as country1, d.pid as pid2, d.name as name2, d.country as country2 ';
	$query  .= 'from comment as a left join topic as b on a.tid=b.tid ';
	$query  .= 'left join player c on a.pid1=c.pid left join player d on b.pid=d.pid ';
	$query  .= 'where a.deleted=0 and b.deleted=0 order by a.id desc limit 1';
			
	$result = warquest_db_query($query);	
	$data = warquest_db_fetch_object($result);
	
	$page .= '<div class="subparagraph">'.t('HOME_LASTEST_FORUM_POST').'</div>';
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
	$page .= '<span class="subparagraph">';
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

	
function warquest_new_version_check() {
	
	/* input */
	global $player;
	global $config;
		
	/* output */
	global $page;
	
	$member = warquest_db_member($player->pid);
		
	if ($member->browser=="WarQuest") {
	
		if ($member->platform=="Windows") {
			
			if ($config["windows_client_version"] != $member->version) {
			
				$message  = t('HOME_NEW_WINDOWS_VERSION',$config["windows_client_version"]).'<br/>';	
				$message .= t('HOME_CLICK_TEXT', '<a href="'.$config["windows_client_url"].'">'.t('HOME_CLICK_HERE').'</a>');	
				$page .= warquest_box_icon("info", $message);			
			}
		}
		
		if ($member->platform=="Android") {
			
			if ($config["android_client_version"] != $member->version) {
			
				$message = t('HOME_NEW_ANDROID_VERSION',$config["android_client_version"]);	
				$page .= warquest_box_icon("info", $message);
				
			}
		}
	}
}

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
			warquest_bank_insert($player->pid, 0, 1, $bonus, $player->bank1, 6);				
		}	
	}		
}

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

function warquest_view_awards() {

	/* input */
	global $player;
	global $config;
	global $browser;
	
	$page="";
	
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
			$page .= warquest_battle_image($data->id, $data->won);
					
			if (($data->id % $max) == 0) { 
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
			$page .= warquest_bounty_image($data->id, $data->amount);
					
			if (($data->id % $max) == 0) { 
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
			$page .= warquest_rebel_image($data->id, $data->amount);
					
			if (($data->id % $max) == 0) { 
				$page .='<br/>';
			}
		}
		
		$page .= '<br/>';
	}
	
	return $page;
}	

function warquest_set_background_do() {

	/* output */
	global $player;
	
	$player->background=1;
}


function warquest_home_welcome() {

	/* input */
	global $player;
	global $mid;
	global $sid;
	global $config;
	
	/* output */
	global $page;
	global $title;
	
	$title = t('HOME_OVERVIEW_TITLE');
	
	$query =  'select count(*) as count, sum(request) as request, sum(won) as won from player';
	$result = warquest_db_query($query); 
	$data = warquest_db_fetch_object($result);
		
	$query =  'select distinct(country) from player';
	$result = warquest_db_query($query); 
	$count = warquest_db_num_rows($result);
		
	$ranking = floor($player->experience/30) + $player->won - $player->lost;
	$query =  'select pid from player where country="'.$player->country.'" and ((experience/30)+won-lost)>='.$ranking;
	$result = warquest_db_query($query);
	$count2 = warquest_db_num_rows($result);
		
	$query =  'select pid from player where ((experience/30)+won-lost)>='.$ranking.' and country!="EU"';
	$result = warquest_db_query($query);
	$count3 = warquest_db_num_rows($result);
	
	$yesterday = mktime(date("H"), date("i"), date("s"), date("m"), date("d")-1, date("Y"));
	$query4  = 'select count(*) as count from member where last_login > "'.date("Y-m-d H:i:s", $yesterday).'" ';		
	$result4 = warquest_db_query($query4);
	$data4 =  warquest_db_fetch_object($result4);
		
	$page .= '<div class="subparagraph">'.t('HOME_OVERVIEW_TITLE').'</div>';
	
	$page .= '<div class="box">';

	$page .= '<div class="right">';
	$page .= warquest_rank_image($player->lid);
	$page .= '</div>';
		
	$page .= t('HOME_WELCOME').' '.warquest_rank($player->lid);
	$page .= ' <b>';
	$page .= player_format($player->pid, $player->name, $player->country);
	$page .= '</b><br/>';
	
	$member = warquest_db_member($player->pid);
	if ($member->prev_login!=0) {
		$page .= t('HOME_LAST_LOGIN', warquest_ui_ago($member->prev_login)).'<br/>';
	}
	$page .= '<br/>';
	$page .= t('HOME_INTRO_PLACE1', warquest_place($count3));
	$page .= t('HOME_INTRO_PLACE2', warquest_place($count2), warquest_landcode($player->country)).'<br/>';
	
	if ($player->lid > 5) {
		$page .= '<br/>';
		$page .= t('HOME_INTRO_PLAYERS', energy_format($data->count), country_format($count));
		$page .= t('HOME_INTRO_FIGHTS', health_format($data->won));
		$page .= t('HOME_INTRO_REQUESTS', money_format1($data->request));
		$page .= t('HOME_PLAYERS_ONLINE',energy_format($data4->count));			
		$page .= '<br/>';
	}
		
	$page .= warquest_view_awards();
	
	if ($player->lid <= 5) {
	
		$page .= '<br/>';
	
		$query1 = 'select ugid from unit_group where type=2 and planet='.$player->planet;
		$result1 = warquest_db_query($query1);
		$data1 = warquest_db_fetch_object($result1);

		$query2 = 'select bgid from building_group where planet='.$player->planet.' order by bgid limit 1';
		$result2 = warquest_db_query($query2);
		$data2 = warquest_db_fetch_object($result2);
	
		$page .= '<span class="subparagraph2">'.t('HOME_INTRO_TITLE').'</span><br/>';
		$page .= t('HOME_INTRO_MISSIONS', warquest_link('mid='.MENU_MISSIONS.'&sid='.warquest_get_default_mission($player->planet),t('LINK_MISSIONS'), 'mission1'));
		$page .= t('HOME_INTRO_BATTLES', warquest_link('mid='.MENU_BATTLE.'&sid='.PAGE_ENEMIES,t('LINK_BATTLES'), 'battle1'));
		$page .= t('HOME_INTRO_UNITS', warquest_link('mid='.MENU_UNITS.'&sid='.$data1->ugid, t('LINK_UNITS'), 'unit1'));
		$page .= t('HOME_INTRO_BUILDINGS', warquest_link('mid='.MENU_BUILDINGS.'&sid='.$data2->bgid, t('LINK_BUILDINGS'), 'building1'));
		$page .= t('HOME_INTRO_ENEMY');
		$page .= '<br/>';			
	}
	
	$page .= warquest_show_ads();
		
	if ($player->lid > 4) {
		$page .= warquest_poll_teaser();	
	}

	$page .= '</div>';	

	/* Show tip */
	$page .= warquest_ui_tip();	
}

function warquest_show_breaking_news() { 

	global $page;

	$page .= '<div class="subparagraph">'.t('HOME_FLASH_NEWS_TITLE').'</div>';
	
	warquest_ui_breaking_news();	
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
			
		case 1:
			warquest_home_comment_edit_do();
			break;
			
		case 2:
			warquest_home_comment_save_do();
			break;

		case 3:
			warquest_home_comment_delete_do();
			break;
			
		case 10:
			warquest_set_background_do();
			break;

		case 500: 
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
					warquest_new_version_check();
					warquest_daily_bonus();
					warquest_nextlevel($player);
					warquest_battle_award_won($player);
					warquest_bounty_award_won($player);
					warquest_rebel_award_won($player);
					warquest_holiday_message();
					warquest_home_welcome();
					warquest_show_breaking_news();
					warquest_lastest_forum_post();						
					warquest_show_map();						
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