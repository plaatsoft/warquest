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
** ADMIN
** ---------------------------------------------------------------- 
*/

/*
** ---------------------
** Post parameters
** ---------------------
*/

$body = warquest_post('body', '');
$content = warquest_post('content', '');
$nickname = warquest_post('nickname', '');
$language = warquest_post('language', $player->language);

/*
** ---------------------
** technical info page
** ---------------------
*/

function warquest_admin_info() {

	/* intput */
	global $mid;
	global $sid;
	
	/* output */
	global $page;
	global $title;
	
	$title = 'Info';
					
	$page .= '<div class="subparagraph">Technical Info</div>';
	
	$page .= '<div class="box">';
		
	$page .= 'PHP version = '.phpversion();
	$page .= '<br/>';
	
	$page .= 'display_errors = '.ini_get('display_errors');
	$page .= '<br/>';
			
	$page .= 'post_max_size = '.ini_get('post_max_size');
	$page .= '<br/>';
	
	$page .= 'Server IP = '.gethostbyname($_SERVER['SERVER_NAME']);
	$page .= '<br/>';

	$page .= 'Server URL = '.$_SERVER['HTTP_HOST'];
	$page .= '<br/>';
	
	$page .= 'Server Software = '.$_SERVER['SERVER_SOFTWARE'];
	$page .= '<br/>';
	
	$page .= 'Client IP addres = '.$_SERVER['REMOTE_ADDR'];
	$page .= '<br/>';
	
	$page .= '</div>';
}

/*
** --------------- 
** FORM ACTIONS
** ---------------
*/

function warquest_admin_optimize_tables_do() {
	
	/* output */
	global $popup;
	
	$message = 'Tables optimized!<br/>';
	
	$query  = 'optimize table bank'; 
	$result = warquest_db_query($query);
	if ($data=warquest_db_fetch_object($result)) {
		$message .= $data->Table.' '.$data->Msg_type.' '.$data->Msg_text.'<br/>';
	}

	$query  = 'optimize table battle'; 
	$result = warquest_db_query($query);
	if ($data=warquest_db_fetch_object($result)) {
		$message .= $data->Table.' '.$data->Msg_type.' '.$data->Msg_text.'<br/>';
	}
	
	$query  = 'optimize table bounty'; 
	$result = warquest_db_query($query);
	if ($data=warquest_db_fetch_object($result)) {
		$message .= $data->Table.' '.$data->Msg_type.' '.$data->Msg_text.'<br/>';
	}
	
	$query  = 'optimize table news'; 
	$result = warquest_db_query($query);
	if ($data=warquest_db_fetch_object($result)) {
		$message .= $data->Table.' '.$data->Msg_type.' '.$data->Msg_text.'<br/>';
	}
	
	$query  = 'optimize table player_building'; 
	$result = warquest_db_query($query);
	if ($data=warquest_db_fetch_object($result)) {
		$message .= $data->Table.' '.$data->Msg_type.' '.$data->Msg_text.'<br/>';
	}
	
	$query  = 'optimize table player_player'; 
	$result = warquest_db_query($query);
	if ($data=warquest_db_fetch_object($result)) {
		$message .= $data->Table.' '.$data->Msg_type.' '.$data->Msg_text.'<br/>';
	}

	$query  = 'optimize table player_unit'; 
	$result = warquest_db_query($query);
	if ($data=warquest_db_fetch_object($result)) {
		$message .= $data->Table.' '.$data->Msg_type.' '.$data->Msg_text.'<br/>';
	}
		
	$query  = 'optimize table session'; 
	$result = warquest_db_query($query);
	if ($data=warquest_db_fetch_object($result)) {
		$message .= $data->Table.' '.$data->Msg_type.' '.$data->Msg_text.'<br/>';
	}
	
	$query  = 'optimize table player_stock'; 
	$result = warquest_db_query($query);
	if ($data=warquest_db_fetch_object($result)) {
		$message .= $data->Table.' '.$data->Msg_type.' '.$data->Msg_text.'<br/>';
	}
	
	$query  = 'optimize table player_poll'; 
	$result = warquest_db_query($query);
	if ($data=warquest_db_fetch_object($result)) {
		$message .= $data->Table.' '.$data->Msg_type.' '.$data->Msg_text.'<br/>';
	}
	
	$popup .= warquest_box_icon("info", $message);	
	warquest_info($message);
}

function warquest_admin_update_building_staff_do() {
	
	/* output */
	global $popup;
	
	$query  = 'select pid from player'; 
	$result = warquest_db_query($query);
	
	$count=0;
	$update=0;
	while ($data=warquest_db_fetch_object($result)) {
				
		$query2  = 'select a.uid, sum(b.amount * c.amount) as amount from unit a ';
		$query2 .= 'left join building_unit b on b.uid=a.uid, player_building c ';
		$query2 .= 'where a.ugid=5 and b.bid=c.bid and c.pid='.$data->pid.' group by a.uid';
	 
		$result2 = warquest_db_query($query2);	
  
		while ($data2=warquest_db_fetch_object($result2)) {		
			warquest_db_unit_add($data->pid, $data2->uid, $data2->amount, 1);
			$update++;
		}
	
		$count++;
	}
	
	$message = $update.' citizens updated!<br>'.$count.' players checked';
	$popup .= warquest_box_icon("info", $message);	
	warquest_info($message);
}
		
function warquest_admin_player_award_update_do() {
			
	/* output */
	global $popup;
	
	$query  = 'select pid from player'; 
	$result = warquest_db_query($query);		
	
	$count=0;
	$update=0;
	while ($data=warquest_db_fetch_object($result)) {
		
		$found = 0;

		/* Load player data */
		$player = warquest_db_player($data->pid);
			
		if (warquest_battle_award_won_do($player)>0) {
			$update++;
			$found = 1;
		}
		
		if (warquest_bounty_award_won_do($player)>0) {
			$update++;
			$found = 1;	
		}
		
		if (warquest_rebel_award_won_do($player)>0) {
			$update++;
			$found = 1;	
		}
		
		if ($found == 1 ) { 
		
			/* Save player data */
			warquest_db_player_update($player);
		}
		
		$count++;
	}
		
	$message = $update.' player awards updated!<br/>'.$count.' players checked.';
	$popup .= warquest_box_icon("info", $message);
	warquest_info($message);
}

function warquest_admin_update_player_level_do() {
		
	/* output */
	global $popup;
	
	$query  = 'select pid from player'; 
	$result = warquest_db_query($query);			
	
	$count=0;
	$update=0;
	while ($data=warquest_db_fetch_object($result)) {
		
		/* Load player data */
		$player = warquest_db_player($data->pid);
				
		if (warquest_nextlevel_do($player)==1) {
			$update++;
			
			/* Save player data */
			warquest_db_player_update($player);
		}
		
		$count++;
	}
	
	$message = $update.' player levels updated!<br/>'.$count.' players checked.';
	$popup .= warquest_box_icon("info", $message);
	warquest_info($message);
}


function warquest_admin_update_all_money_do() {
	
	/* output */
	global $popup;
	
	$query  = 'select pid from player'; 
	$result = warquest_db_query($query);			
	
	$count=0;
	while ($data=warquest_db_fetch_object($result)) {
		
		/* Load player data */
		$player = warquest_db_player($data->pid);
	
		warquest_netto_income($player);
		
		/* Save player data */
		warquest_db_player_update($player);
		
		$count++;
	}
	
	$message = 'Money parameters updated!<br>'.$count.' players checked';
	$popup .= warquest_box_icon("info", $message);
	warquest_info($message);
}


function warquest_admin_update_all_timers_do() {
		
	/* output */
	global $popup;
	
	$query  = 'select pid from player where country="eu"'; 
	$result = warquest_db_query($query);			
	
	$count=0;
	while ($data1=warquest_db_fetch_object($result)) {
	
		/* Update login member information. */
		$member = warquest_db_member($data1->pid);
		$member->prev_login = $member->last_login;
		$member->last_login = date("Y-m-d H:i:s");
		warquest_db_member_update($member);
	
		/* Load player data */
		$player1 = warquest_db_player($data1->pid);
	
		/* Update player timers */
		warquest_update_timers($player1);
		
		/* Save player data */
		warquest_db_player_update($player1);
		
		$count++;
	}
	
	$message = 'Robot timers updated!<br>'.$count.' robots checked.';
	$popup .= warquest_box_icon("info", $message);
	warquest_info($message);
}

function warquest_admin_action_form() {

	/* intput */
	global $mid;
	global $sid;
	
	/* output */
	global $page;
	global $title;
	
	$title = 'Actions';
					
	$page .= '<div class="subparagraph">Actions</div>';
	
	$page .= '<div class="box action">';
		
	$page .= '<b>GENERAL ACTIONS</b>'; 
	
	$page .= '<ul>'; 
	
	$page .= '<li>';
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_ADMIN_UPDATE_LEVELS, 'Players level update. (HIGH DATABASE LOAD)');
	$page .= '</li>';
	
	$page .= '<li>'; 
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_ADMIN_UPDATE_AWARDS, 'Players awards update. (HIGH DATABASE LOAD)');
	$page .= '</li>';
		
	$page .= '<li>'; 
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_ADMIN_UPDATE_ROBOTS, 'Accept all robot ally requested (cron job)');
	$page .= '</li>';

	$page .= '<li>'; 
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_ADMIN_CLEAN_BATTLE_LOG, 'Players clean battle log (cron job)');
	$page .= '</li>';
	
	$page .= '<li>'; 
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_ADMIN_CLEAN_BANK_LOG, 'Players clean bank log (cron job)');
	$page .= '</li>';
	
	$page .= '<li>'; 
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_ADMIN_UPDATE_INVITATIONS, 'Delete long pending alliance requests (cron job)');
	$page .= '</li>';
	
	$page .= '<li>'; 
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_ADMIN_UPDATE_INCOME, 'Update players with negative hourly income (cron job)');
	$page .= '</li>';
	
	$page .= '<li>'; 
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_ADMIN_BACKUP_DATABASE, 'Make database backup (cron job)');
	$page .= '</li>';

	$page .= '<li>'; 
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_ADMIN_OPTIMIZE_DATABASE, 'Optimize database tables');
	$page .= '</li>';
	
	$page .= '</ul>';
	
	$page .= '<br/>';
	$page .= '<b>SPECIAL ACTIONS</b>'; 
	
	$page .= '<ul>';
	
	$page .= '<li>'; 
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_ADMIN_UPDATE_TIMERS, 'Generate 24h extra robot income.');
	$page .= '</li>';
		
	$page .= '<li>'; 
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_ADMIN_UPDATE_MONEY, 'Players money update. (HIGH DATABASE LOAD)');
	$page .= '</li>';
					
	$page .= '<li>'; 
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_ADMIN_UPDATE_STAFF, 'Players citizens update. (HIGH DATABASE LOAD)');
	$page .= '</li>';
	
	$page .= '<li>'; 
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_ADMIN_UPDATE_INTEREST, 'Pay bank interest (cron job)');
	$page .= '</li>';

	$page .= '</ul>';
	
	$page .= '</div>';	
}

/*
** ---------------------
** FORM BROWSER
** ---------------------
*/

function warquest_admin_browser_report() {
	
	/* output */
	global $page;
	global $title;
	
	$title = 'Browsers';
		
	$query  = 'select COUNT(*) as count, browser, platform, version ';
	$query .= 'from member group by browser, platform, version ';
	$query .= 'order by browser asc, version asc ';

	$result = warquest_db_query($query);		

	$page .= '<div class="subparagraph">Browsers</div>';
	
	$page .= '<div class="box">';
	
	$page .= '<table>';
	
	$page .= '<tr>';	
	$page .= '<th width="150">Browser</th>';
	$page .= '<th width="150">Version</th>';
	$page .= '<th width="100">Count</th>';	
	$page .= '<th width="50">Platform</th>';
	$page .= '</tr>';	
	
	$total = 0;
	while ($data=warquest_db_fetch_object($result)) {
	
		$page .= '<tr>';
		
		$page .= '<td>';
		if ($data->browser=="") {
			$page .= "Unknown";
		} else {
			$page .= $data->browser;
		}
		$page .= '</td>';
		
		$page .= '<td>';
		$page .= $data->version;
		$page .= '</td>';
		
		$page .= '<td>';
		$page .= $data->count;
		$total += $data->count;
		$page .= '</td>';
		
		$page .= '<td>';
		if ($data->platform!="") {
			$page .= warquest_platform_image($data->platform);
		}
		$page .= '</td>';
		
		$page .= '</tr>';
	}
	
	$page .= '<tr>';	
	$page .= '<td width="150"><b>Total</b></td>';
	$page .= '<td width="150"></td>';
	$page .= '<td width="50"><b>'.$total.'</b></td>';	
	$page .= '</tr>';	
	
	$page .= '</table>';
	$page .= '</div>';	
	
	/* ------------------------------ */
	
	$query  = 'select platform, COUNT(*) as count ';
	$query .= 'from member group by platform ';
	$query .= 'order by platform asc ';
	
	$result = warquest_db_query($query);	

	$page .= '<div class="subparagraph">Platforms</div>';
	
	$page .= '<div class="box">';
	
	$page .= '<table>';
	
	$page .= '<tr>';	
	$page .= '<th width="150">Platform</th>';	
	$page .= '<th width="150">Logo</th>';	
	$page .= '<th width="50">Count</th>';	
	$page .= '</tr>';	
		
	$total = 0;
	while ($data=warquest_db_fetch_object($result)) {
	
		$page .= '<tr>';
		
		$page .= '<td>';
		if ($data->platform=="") {
			$page .= "Unknown";
		} else {
			$page .= $data->platform;
		}
		$page .= '</td>';

		$page .= '<td>';
		if ($data->platform!="") {
			$page .= warquest_platform_image($data->platform);
		}
		$page .= '</td>';
		
		$page .= '<td>';
		$page .= $data->count;
		$total += $data->count;
		$page .= '</td>';
		
		$page .= '</tr>';
	}
	
	$page .= '<tr>';	
	$page .= '<td><b>Total</b></td>';
	$page .= '<td><b></b></td>';	
	$page .= '<td><b>'.$total.'</b></td>';	
	$page .= '</tr>';	
	
	$page .= '</table>';
	$page .= '</div>';			
}

/*
** ---------------------
** FORM LEVELS
** ---------------------
*/

function warquest_admin_level_form() {

	/* input */
	global $mid;
	global $config;
			
	/* output */
	global $page;
	global $title;
			
	$title = 'Levels'; 
	
	/* Get alliance players */
	$query  = 'select lid, count(*) as total, count(distinct country) as country ';
	$query .= 'from player group by lid order by lid asc'; 
	$result = warquest_db_query($query);	
	
	$page .= '<div class="subparagraph">'.$title.'</div>';
	
	$page .= '<div class="box">';
	$page .= '<table>';
	
	$page .= '<tr>';	
	$page .= '<th width="100">Level</th>';
	$page .= '<th width="125">Players</th>';
	$page .= '<th width="125">Countries</th>';
	$page .= '</tr>';
	
	$total = 0;
	while ($data=warquest_db_fetch_object($result)) {
	
		$page .= '<tr>';
		$page .= '<td>';
		$page .= warquest_link('mid='.$mid.'&uid='.$data->lid.'&sid='.PAGE_LEVEL_ZOOM, $data->lid);
		$page .= '</td>';
		$page .= '<td>';
		$page .= number_format($data->total,0,",",".");
		$total += $data->total;
		$page .= '</td>';
		$page .= '<td>';
		$page .= number_format($data->country,0,",",".");
		$page .= '</td>';
		$page .= '</tr>';
	}

	$page .= '<tr>';
	$page .= '<td>';
	$page .= 'Total';
	$page .= '</td>';
	$page .= '<td>';
	$page .= number_format($total,0,",",".");
	$page .= '</td>';
	$page .= '</tr>';
		
	$page .= '</table>';
	$page .= '</div>';	
	
	$page .= '<div class="note">';
	$page .= 'Note: Report show amount of players per level.';
   $page .= '</div>';
}

/*
** ---------------------
** FORM MESSAGES
** ---------------------
*/

function warquest_admin_message_delete_do() {
	
	/* input */
	global $uid;
	
	/* output */
	global $popup;
	
	if (warquest_db_comment_delete($uid) == 1) {
		
		$message = t('HOME_NO_MESSAGES');
		$popup .= warquest_box_icon("info", $message);		
	}
}

function warquest_admin_messages_form() {
   
	/* input */
	global $other;
	global $mid;
	global $sid;
	global $offset;
	
	/* output */
	global $page;
	global $title;

	$title = 'Messages';
	
	$limit=30;
	
	$query  = 'select pid1 from comment where deleted=0';
	$result = warquest_db_query($query);	
	$total = warquest_db_num_rows($result);
	
	$query  = 'select a.id, a.date, a.comment, ';
	$query .= 'a.pid1, b.name as name1, b.country as country1, ';
	$query .= 'a.pid2, c.name as name2, c.country as country2 ';
	$query .= 'from comment a left join player b ';
	$query .= 'on b.pid=a.pid1 left join player c on c.pid=a.pid2 ';
	$query .= 'where a.deleted=0 order by a.date desc ';
	$query .= 'limit '.$offset.','.$limit;
	$result = warquest_db_query($query);	
	$count = warquest_db_num_rows($result);
	
	if ($count>0) {
	
		$page .= '<div class="subparagraph">'.$title.'</div>';
	
		$page .= '<div class="box">';
		
		$page .= warquest_page_control($offset, $limit, $total, 1);
		
		$page .= '<table>';
		while ($data=warquest_db_fetch_object($result)) {
	
			$page .= '<tr>';
			$page .= '<td width="100" valign="top" >';
			$page .= warquest_ui_ago($data->date).' ago';
			$page .= '</td>';
			
			$page .= '<td width="340" valign="top">';
			$page .= '<span class="subparagraph2">';
			$page .= player_format($data->pid1, $data->name1, $data->country1).' -> ';
			
			if ($data->pid2==0) {
				$page .= t("GENERAL_ALL");
			} else {
				$page .= player_format($data->pid2, $data->name2, $data->country2);
			}
			$page .= '</span><br/>';
			
			$page .= warquest_parse_smilies(wordwrap($data->comment, 40, "\n\r", true));
			
			$page .= '</td>';
		
			$page .= '<td align="right" valign="top">';
			$page .= warquest_link_confirm('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_ADMIN_DELETE_MSG.'&uid='.$data->id, 'Delete', 'Delete message. Are your sure?');
			$page .= '</td>';
		
			$page .= '</tr>';
		}
		$page .= '</table>';
		
		$page .= warquest_page_control($offset, $limit, $total, 0);
		
		$page .= '</div>';
	}
	$page .= '<div class="note">';
	$page .= 'Note: Show last 50 messages of players.';
	$page .= '</div>';
}

/*
** ---------------------
** FORM NEWS
** ---------------------
*/

/**
 * Send tweet to twitter and process response.
 */
function warquest_admin_post_tweet_do() {

	/* input */
	global $body;
	global $content;
	global $config;
	   
	/* output */
	global $popup;
	
	$tmhOAuth = new tmhOAuth(array(
		'consumer_key'    => $config['consumer_key'],
		'consumer_secret' => $config['consumer_secret'],
		'user_token'      => $config['user_token'],
		'user_secret'     => $config['user_secret'],
	));
	
	$tweet_text = substr($body.' '.$content,0,130).' #WarQuest';
	$code = $tmhOAuth->request('POST', $tmhOAuth->url('1/statuses/update'), array('status' => $tweet_text));
		
	$message = 'Posted following tweet: '.$tweet_text;
	
	if ($code == 200) {
	
		$popup .= warquest_box_icon("info", $message);	
		
	} else {
	
		$popup .= warquest_box_icon("error", $message);
	}
	
	warquest_info($message);	
}

/**
 * Delete news 
 */
function warquest_admin_news_delete_do() {
	
	/* input/output */
	global $uid;

	/* output */
	global $popup;
	
	warquest_db_news_delete($uid);
	
	/* Clear input parameters */	
	$uid = 0;
		
	$message = 'News item '.$uid.' deleted!';
	$popup .= warquest_box_icon("info", $message);	
	warquest_info($message);	
}

/**
 * Save news
 */
function warquest_admin_news_save_do() {

	/* input */
	global $body;
	global $content;
	global $language;
	
	/* output */
	global $uid;
	global $popup;
	
	if (strlen($content)>0) {
		if ($uid==0) {
	
			warquest_db_news_insert($body, $content, $language);
				
			$message = 'News item added!';
			$popup .= warquest_box_icon("info", $message);
			warquest_info($message);
		
		} else {
	
			warquest_db_news_update($body, $content, $language, $uid);
				
			$message = 'News item '.$uid.' updated!';
			$popup .= warquest_box_icon("info", $message);
			warquest_info($message);
		}
		
		/* Clear input parameters */
		$uid = 0;
	}
}

/**
 * Show all news items
 */
function warquest_admin_news_log() {
   	
	/* input */
	global $mid;
	global $sid;
	
	/* output */
	global $page;
	
	$query  = 'select id, date, body, content, language from news order by id desc';
	$result = warquest_db_query($query);	
	
	$page .= '<div id="news">';

	$page .= '<div class="subparagraph">News items</div>';
	
	$page .= '<div class="box">';
	
	$page .= '<table>';
	
	$page .= '<tr>';
	
	$page .= '<th width="75">'.t('GENERAL_AGO').'</th>';
	$page .= '<th width="360">'.t('GENERAL_MESSAGE').'</th>';
	$page .= '<th width="20"></th>';
	$page .= '<th width="55" align="right">'.t('GENERAL_ACTION').'</th>';
	
	$page .= '</tr>';
	
	$count = 0;
	while ($data=warquest_db_fetch_object($result)) {
	
		$page .= '<tr valign="top">';
		
		$page .= '<td>';
		$page .= warquest_ui_ago($data->date);
		$page .= '</td>';
				
		$page .= '<td>';
		$page .= '<span class="money">'.$data->body.'</span> ';
		$page .= $data->content;
		$page .= '</td>';
	
		$page .= '<td>';
		if ($data->language=="nl") {
			$language='nl';
		} else if ($data->language=="de") {
		   $language='de';
		} else {
			$language='gb';
		}
		$page .= warquest_flag_image($language);
		$page .= '</td>';
		
		$page .= '<td align="right">';
		$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&uid='.$data->id, t('LINK_EDIT')).' ';
		$page .= '</td>';
		
		$page .= '</tr>';
		
		$count++;
	}
	$page .= '</table>';
	$page .= '</div>';
}

/**
 * Add news item
 */
function warquest_admin_news() {

	/* input */
	global $mid;
	global $sid;
	global $uid;
	
	global $body;
	global $content;
	global $language;
		
	/* output */
	global $page;
	global $title;
	
	if ($uid!=0) {
		$query  = 'select body, content, language from news where id='.$uid;
		$result = warquest_db_query($query);	
		
		$data = warquest_db_fetch_object($result);
		
		$body = $data->body;
		$content = $data->content;
		$language = $data->language;
		
	} else {
	
		/* Clear input parameters */
		$body = "";
		$content = "";
		$language = "";
	}

	$title = 'News';
		
	$page .= "<script>
		function limitText(limitField, limitNum) {
			if (limitField.value.length >= limitNum) {
				limitField.value = limitField.value.substring(0, limitNum);
			} 
		}
		</script>\n";

	$page .= '<div class="subparagraph">'.$title.'</div>';	
	
	$page .= '<div class="box">';	
	
	$page .= '<table>';
	
	$page .= '<tr>';
	$page .= '<td width="500">';
	$page .= 'Body:';
	$page .= '</td>';
	$page .= '</tr>';
	
	$page .= '<tr>';
	$page .= '<td>';
	$page .= '<input style="width:100%" id="body" name="body" type="text" maxlength="100" value="'.$body.'"/>';
	$page .= '</td>';
	$page .= '</tr>';
	
	$page .= '<tr>';
	$page .= '<td>';
	$page .= 'Content:';
	$page .= '</td>';
	$page .= '</tr>';
	
	$page .= '<tr>';
	$page .= '<td>';
	$page .= '<textarea style="width:100%" id="content" name="content" rows="5" ';
	$page .= 'onKeyDown="limitText(this,1000)">'.$content.'</textarea>';
	$page .= '</td>';
	$page .= '</tr>';
		
	$page .= '<tr>';
	$page .= '<td>';
	$page .= 'Language:';
	$page .= '</td>';
	$page .= '</tr>';
	
	$page .= '<tr>';
	$page .= '<td>';
	$page .= warquest_ui_language("language", $language, false);
	$page .= '</td>';
	$page .= '</tr>';
	
	$page .= '<tr>';
	$page .= '<td>';
	$page .= '<br/>';
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_ADMIN_NEWS_SAVE.'&uid='.$uid, t('LINK_SAVE'));
	if ($uid!=0) {
		$page .= ' ';
		$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_ADMIN_NEWS_DELETE.'&uid='.$uid, t('LINK_DELETE'));
	}
	$page .= ' ';
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_ADMIN_SAVE_TWEET.'&uid='.$uid, 'Tweet');
	$page .= '</td>';
	$page .= '</tr>';
		
	$page .= '</table>';
		
	$page .= "</div>";
}

/*
** ---------------------
** FORM COPY MEMBER
** ---------------------
*/

function warquest_admin_copy_do() {

	/* input */
	global $other;
	
   global $myname;
	global $myemail;
   global $myusername;
	global $mypassword;
	
		/* output */
	global $popup;
	
	if (strlen($myusername)==0) {
		$myusername = $myname;
	}
		
	if (strlen($myemail)==0) {
		$myemail = $myname."@plaatsoft.nl";
	}
	
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
	$message="";
	if ($count1==1) {
	
		$message = 'Username '.$myusername.' already exist!';
		$popup .= warquest_box_icon("warning", $message);
	
	} else if (strlen($myname)==0) {
	
		$message = 'Nickname must be entered!';
		$popup .= warquest_box_icon("warning", $message);
		
	} else if ($count2==1) {
	
		$message = 'Nickname '.$myname.' already exist!';
		$popup .= warquest_box_icon("warning", $message);
	
	} else if (validate_email($myemail)) {
	
		$message = 'Email is not valid!';
		$popup .= warquest_box_icon("warning", $message);
		
	} else if ($count3==1) {
	
		$message = 'Email is already register!';
		$popup .= warquest_box_icon("warning", $message);
		
	} else if (strlen($myusername)<4) {
		
		$message = 'User name must be at least 4 characters long!';
		$popup .= warquest_box_icon("warning", $message);
		
	} else if (strlen($mypassword)<4) {
	
		$message = 'Password must be atleast 4 characters long!';
		$popup .= warquest_box_icon("warning", $message);
		
	} else {
 
		$pid2=warquest_db_member_insert($myusername,$mypassword,$myemail);
	
		/* Copy player data */
		warquest_db_player_insert($myname,$pid2);
		$other2=warquest_db_player($other->pid);
		$other2->pid=$pid2;
		$other2->name=$myname;
		warquest_db_player_update($other2);
				
		/* copy skill data */
		warquest_db_skill_insert($pid2, 0);
		$skill2=warquest_db_skill($other->pid);
		$skill2->pid=$pid2;
		warquest_db_skill_update($skill2);
				
		/* Copy buildings */
		$query = 'select bid, amount from player_building where pid='.$other->pid;
		$result = warquest_db_query($query);	  
		
		$buildings=0;
		while ($data=warquest_db_fetch_object($result)) {
			$buildings++;
			$query  = 'insert into player_building (pid, bid, amount) ';
			$query .= 'values ('.$pid2.','.$data->bid.','.$data->amount.')';	
			warquest_db_query($query);
		}
		
		/* Copy missions */
		$query = 'select mid, progress, part, part2 from player_mission where pid='.$other->pid;
		$result = warquest_db_query($query);	
  
		$missions=0;
		while ($data=warquest_db_fetch_object($result)) {
			$missions++;
			warquest_db_mission_progress_update($pid2, $data->mid, $data->progress, $data->part, $data->part2);
		}
		
		/* Copy units */
		$query = 'select uid, amount from player_unit where pid='.$other->pid;
		$result = warquest_db_query($query);	
 
		$units=0;
		while ($data=warquest_db_fetch_object($result)) {
			$units++;
			$query  = 'insert into player_unit (pid, uid, amount) ' ;
			$query .= 'values ('.$pid2.','.$data->uid.','.$data->amount.')';	
			warquest_db_query($query);
		}
		
		/* Reinitiase some player parameters */
		$other2->request = 0;
		$other2->alliance = 1; 
		$other2->invite = 0; 
		$other2->experience += rand(1,5);
		$other2->won = 0;
		$other2->lost = 0;
		$other2->ads = 0;
		$other2->mission = 0;
		$other2->casino = 0;
		$other2->country = "EU";

		warquest_db_player_update($other2);
				
		$message  = 'User '.$other->name.' -> '.$myname.' copied!<br/>';
		$message .= 'Copy '.$buildings.' buildings<br/>';
		$message .= 'Copy '.$missions.' missions<br/>';
		$message .= 'Copy '.$units.' units<br/>';
		$popup .= warquest_box_icon("info", $message);
		warquest_info($message);
	}
}

function warquest_admin_copy_form() {

	/* input */
	global $mid;
	global $sid;
	global $config;
	global $other;
	
   global $myname;
	global $mypassword;
	
	/* output */
	global $page;

	$page .= '<div class="subparagraph">Copy Player</div>';
	
	$page .= '<div class="box">';
	$page .= '<table>';		
	$page .= '<tr>';
	$page .= '<td width="120">Nickname:</td>';
	$page .= '<td><input name="myname" type="text" size="20" maxlength="15" value="'.$myname.'" id="myname"></td>';
	$page .= '</tr>';
		
	$page .= '<tr>';
	$page .= '<td>Password:</td>';
	$page .= '<td><input name="mypassword" type="password" maxlength="';
	$page .= $config["max_password_length"].'" size="18" value="';
	$page .= $mypassword.'" id="mypassword"></td>';
	$page .= '</tr>';
		
	$page .= '<tr>';
	$page .= '<td>&nbsp;</td>';
	$page .= '<td>';
	$page .= '<input type="hidden" name="token" value="'.warquest_token('mid='.$mid.'&sid='.$sid.'&oid='.$other->pid.'&eid='.EVENT_ADMIN_COPY).'">';
	$page .= '<input type="submit" name="Submit" value="Copy">';
	$page .= '</td>';
	$page .= '</tr>';
		
	$page .= '</table>';
	$page .= '</div>';	
}

/* 
** -----------------------------
** ADMIN EDIT/DELETE/HACK MEMBER
** -----------------------------
*/

function warquest_admin_hack() {

	/* input */
	global $other;
	
	/* output */
	global $session;
	global $popup;
	
	$session = warquest_db_session_hack($other->pid);	
	
	$message = 'Hack session of '.$other->name;
	$popup .= warquest_box_icon("info", $message);
	warquest_info($message);
}

function warquest_admin_delete_do() {

	/* input */
	global $other;
	
	/* output */
	global $page;
	global $popup;
	
	/* First update alliance partners */
	$query  = 'select pid1 from player_player where approved=1 and pid2='.$other->pid;
	$result = warquest_db_query($query);	  
	
	while ($data=warquest_db_fetch_object($result)) {
		
		$tmp=warquest_db_player($data->pid1);
		
		$tmp->alliance = warquest_db_alliance_size($data->pid1)-1;
	
		warquest_db_player_update($tmp);
	}
	
	$query = "delete from bank where pid1=".$other->pid; 
	warquest_db_query($query);
	
	$query = 'delete from battle where pid1='.$other->pid.' or pid2='.$other->pid; 
	warquest_db_query($query);

	$query = 'delete from bounty where pid1='.$other->pid.' or pid2='.$other->pid; 
	warquest_db_query($query);
	
	$query = 'delete from comment where pid1='.$other->pid.' or pid2='.$other->pid; 
	warquest_db_query($query);
	
	$query = "delete from member where pid=".$other->pid; 
	warquest_db_query($query);

	$query = "delete from player where pid=".$other->pid; 
	warquest_db_query($query);
	
	$query = "delete from player_building where pid=".$other->pid; 
	warquest_db_query($query);	
		
	$query = "delete from player_mission where pid=".$other->pid; 
	warquest_db_query($query);
	
	$query = "delete from player_player where pid1=".$other->pid.' or pid2='.$other->pid; 
	warquest_db_query($query);

	$query = "delete from player_stock where pid=".$other->pid; 
	warquest_db_query($query);

	$query = "delete from player_unit where pid=".$other->pid; 
	warquest_db_query($query);
	
	$query = "delete from skill where pid=".$other->pid; 
	warquest_db_query($query);
	
	$query = "delete from session where pid=".$other->pid; 
	warquest_db_query($query);

	$message = 'Player '.$other->name.' ['.$other->pid.'] is deleted!';
	$popup .= warquest_box_icon("info", $message);
	warquest_info($message);
}

function warquest_admin_edit_do() {

	/* input */
	global $other;
	
	/* output */
	global $page;
	global $popup;

	/* name parameter */
	$name=$other->name;
	if (isset($_POST['name']) && $_POST['name'] != "") {
		$name = $_POST['name'];
	} 
	$other->name=$name;	
	
	/* country parameter */
	$country=$other->country;
	if (isset($_POST['country']) && $_POST['country'] != "") {
		$country = $_POST['country'];
	} 
	$other->country=$country;	
	
	/* money parameter */
	$money=$other->money;
	if (isset($_POST['money']) && $_POST['money'] != "") {
		$money = $_POST['money'];
		
		/* Remove dots */
		$money = str_replace(".", "", $money);
	} 
	$other->money=$money;
	$log = 'Admin change money to '.number_format2($money);		
	warquest_user_log($other, $log);
		
	/* level parameter */
	$lid=$other->lid;
	if (isset($_POST['lid']) && $_POST['lid'] != "") {
		$lid = $_POST['lid'];
	} 
	$other->lid=$lid;	
	
	/* level parameter */
	$experience=$other->experience;
	if (isset($_POST['experience']) && $_POST['experience'] != "") {
		$experience= $_POST['experience'];
		
		/* Remove dots */
		$experience = str_replace(".", "", $experience);
	} 
	$other->experience=$experience;
	
	/* ads parameter */
	$ads = warquest_db_query_pattern($other, PATTERN_ADS);
	if (isset($_POST['ads'])) {
		$ads = 1;
	} else {
		$ads = 0;
	}
	warquest_db_set_pattern($other, PATTERN_ADS, $ads);	
	
	/* ban parameter */
	$ban = warquest_db_query_pattern($other, PATTERN_BAN);
	if (isset($_POST['ban'])) {
		$ban = 1;
	} else {
		$ban = 0;
	}
	warquest_db_set_pattern($other, PATTERN_BAN, $ban);
	
	/* bank parameter */
	$bank=0;
	if (isset($_POST['bank']) && $_POST['bank'] != "") {
		$bank = $_POST['bank'];
		
		/* Remove dots */
		$bank = str_replace(".", "", $bank);
	} 
	
	/* gold parameter */
	$gold=0;
	if (isset($_POST['gold']) && $_POST['gold'] != "") {
		$gold = $_POST['gold'];
		
		if ($gold>0) {
			$log = 'Admin add '.$gold.' gold';		
			warquest_user_log($other, $log);
			$other->gold += $gold;
		}
	} 
	
	$message ="";
	if ($bank>0) {	
		$other->bank1+=$bank;	

		$log = 'Admin add '.number_format2($bank).' dollars as bonus to the national bank';		
		warquest_user_log($other, $log);
	
		warquest_bank_insert($other->pid, 0, 1, $bank, $other->bank1, 6);		
		$message = 'Added '.$bank.' dollar as bonus to National Bank.<br/>';
	}
	
	warquest_db_player_update($other);
	
	$message .= 'Players settings from '.$other->name.' saved!';
	$popup .= warquest_box_icon("info", $message);
	warquest_info($message);	
}

function warquest_admin_personal_messages() {
   
	/* input */
	global $mid;
	global $sid;
	global $other;
	
	/* output */
	global $page;
			
	$query  = 'select a.id, a.date, a.comment, ';
	$query .= 'a.pid1, b.name as name1, b.country as country1, ';
	$query .= 'a.pid2, c.name as name2, c.country as country2 ';
	$query .= 'from comment a, player b, player c ';
   $query .= 'where a.pid1=b.pid and a.pid2=c.pid and ((pid1='.$other->pid.') or (pid2='.$other->pid.')) ';
	$query .= 'and a.deleted=0 order by a.date desc limit 0,50';
	$result = warquest_db_query($query);
	$count = warquest_db_num_rows($result);
			
	$page .= '<div class="subparagraph">'.t('HOME_MESSAGES_TITLE').'</div>';
	
	if ($count>0) {
	
		$page .= '<div class="box">';
	
		$count=0;
		
		$page .= '<table>';
		
		$page .= '<tr>';
		$page .= '<th width="75" >'.t('GENERAL_AGO').'</th>';
		$page .= '<th width="425">'.t('GENERAL_MESSAGE').'</th>';
		$page .= '</tr>';
		
		while ($data=warquest_db_fetch_object($result)) {
	
			$count++;
		
			$page .= '<tr valign="top">';
			$page .= '<td>';
			$page .= warquest_ui_ago($data->date);
			$page .= '</td>';
			
			$page .= '<td>';
			$page .= '<span class="subparagraph2">';
			
			$page .= player_format($data->pid1, $data->name1, $data->country1);
			$page .= ' -> ';
			
			if ($data->pid2==0) {
				$page .= t('GENERAL_ALL');
			} else {
				$page .= player_format($data->pid2, $data->name2, $data->country2);
			}
			
			$page .= '</span>';
			$page .= '<br/>';

			$page .= warquest_parse_smilies(wordwrap($data->comment, 40, "\n\r", true));
			
			$page .= '</td>';
					
			$page .= '</tr>';
		}
		
		$page .= '</table>';

		$page .= '</div>';
	
	} else {
	
		$page .= warquest_box_icon("info",t('HOME_NO_MESSAGES'));
	}
}

function warquest_admin_player_form() {
	
	/* input */
	global $other;
	global $mid;
	
	/* output */
	global $page;
	global $title;

	$title = 'Profile';
	$member=warquest_db_member($other->pid);
	
	$page .= '<form method="post">';
	$page .= '<div class="subparagraph">Editable data</div>';
	$page .= '<div class="box">';

	$page .= '<table>';		
	$page .= '<tr>';
	$page .= '<td width="120">Nickname:</td>';
	$page .= '<td><input name="name" type="text" size="20" maxlength="15" value="'.$other->name.'" /></td>';
	$page .= '</tr>';
			
	$page .= '<tr>';
	$page .= '<td>Country:</td>';
	$page .= '<td><input name="country" type="text" size="3" maxlength="2" value="'.$other->country.'" /></td>';
	$page .= '</tr>';
		
	$page .= '<tr>';
	$page .= '<td>Money:</td>';
	$page .= '<td><input name="money" type="text" size="20" maxlength="15" value="'.number_format($other->money,0,",",".").'" /></td>';
	$page .= '</tr>';
	
	$page .= '<tr>';
	$page .= '<td>Bonus Deposit:</td>';
	$page .= '<td><input name="bank" type="text" size="20" maxlength="15" value="0"/></td>';
	$page .= '</tr>';
	
	$page .= '<tr>';
	$page .= '<td>Gold:</td>';
	$page .= '<td><input name="gold" type="text" size="6" maxlength="6" value="0"/></td>';
	$page .= '</tr>';
		
	$page .= '<tr>';
	$page .= '<td>Level:</td>';
	$page .= '<td><input name="lid" type="text" size="5" maxlength="5" value="'.$other->lid.'" /></td>';
	$page .= '</tr>';
		
	$page .= '<tr>';
	$page .= '<td>Experience:</td>';
	$page .= '<td><input name="experience" type="text" size="10" maxlength="10" value="'.number_format($other->experience,0,",",".").'" /></td>';
	$page .= '</tr>';
		
	$page .= '<tr>';
	$page .= '<td>Show Ads:</td>';
	$page .= '<td>'.warquest_ui_checkbox("ads", "ads", warquest_db_query_pattern($other, PATTERN_ADS)).'</td>';
	$page .= '</tr>';
		
	$page .= '<tr>';
	$page .= '<td>Ban this user:</td>';
	$page .= '<td>'.warquest_ui_checkbox("ban", "ban", warquest_db_query_pattern($other, PATTERN_BAN)).'</td>';
	$page .= '</tr>';
	
	$page .= '<tr>';
	$page .= '<td>&nbsp;</td>';
	$page .= '<td>';
	$page .= '<input type="hidden" name="token" value="'.warquest_token('mid='.$mid.'&sid='.PAGE_PLAYERS.'&eid='.EVENT_ADMIN_EDIT.'&oid='.$other->pid).'" />';
	$page .= '<input type="submit" name="Submit" value="Change" />';
	$page .= '</td>';
	$page .= '</tr>';		
	
	$page .= '</table>';
	$page .= '</div>';
	$page .= '</form>';
		
	$page .= '<div class="subparagraph">Technical Data</div>';
	$page .= '<div class="box">';
	
	$page .= '<table>';
		
	$page .= '<tr>';
	$page .= '<td width="120">ID:</td>';
	$page .= '<td><input name="id" type="text" size="10" maxlength="10" value="'.$other->pid.'" disabled="yes" /></td>';
	$page .= '</tr>';
		
	$page .= '</tr>';		
	$page .= '<td>Username:</td>';
	$page .= '<td><input name="username" type="text" size="20" maxlength="80" value="'.$member->username.'" /></td>';
	$page .= '</tr>';
	
	$page .= '<td>Email:</td>';
	$page .= '<td><input name="email" type="text" size="40" maxlength="120" value="'.$member->email.'" /></td>';
	$page .= '</tr>';
		
	$page .= '</tr>';	
	$page .= '<td>Created:</td>';
	$page .= '<td><input name="created" type="text" size="20" maxlength="20" value="'.warquest_convert_date($member->created).'" disabled="yes" /></td>';
	$page .= '</tr>';
		
	$page .= '</tr>';	
	$page .= '<td>Last Login:</td>';
	$page .= '<td><input name="lastlogin" type="text" size="20" maxlength="20" value="'.warquest_convert_date($member->last_login).'" disabled="yes" /></td>';
	$page .= '</tr>';
		
	$page .= '</tr>';	
	$page .= '<td>Previous Login:</td>';
	$page .= '<td><input name="prevlogin" type="text" size="20" maxlength="20" value="'.warquest_convert_date($member->prev_login).'" disabled="yes" /></td>';
	$page .= '</tr>';
		
	$page .= '</tr>';
	$page .= '<td>IP address:</td>';
	$page .= '<td><input name="ip" type="text" size="15" maxlength="15" value="'.$member->ip.'" disabled="yes" /></td>';
	$page .= '</tr>';
		
	$page .= '</table>';
	
	$page .= '<br/>';
	
	$page .= '<table>';
	$page .= '<tr>';
	$page .= '<td width="165" align="left">';
	$page .= warquest_link_confirm('mid='.$mid.'&oid='.$other->pid.'&sid='.PAGE_PLAYER_LIST.'&eid='.EVENT_ADMIN_DELETE_PLAYER, 
						'Delete account' ,'Delete '.$other->name.'. Are you sure?');
	$page .= '</td>';
		
	$page .= '<td width="165" align="center">';
	$page .= warquest_link('mid='.$mid.'&oid='.$other->pid.'&sid='.PAGE_PLAYER_LIST.'&eid='.EVENT_ADMIN_HACK_ACCOUNT, 'Hack Session');
	$page .= '</td>';
	$page .= '<td width="165" align="right">';
	$page .= warquest_link('mid='.$mid.'&oid='.$other->pid.'&sid='.PAGE_PLAYER_COPY, 'Copy account');
	$page .= '</td>';
	$page .= '</tr>';
	$page .= '</table>';
		
	$page .= '</div>';
			
	$page .= warquest_profile($other->pid);	
	
	warquest_admin_personal_messages();
}

/*
** ---------------------
** FORM SEARCH MEMBER
** ---------------------
*/

function warquest_admin_level_zoom_form() {

	/* input */
	global $player;
	global $uid;
	global $mid;
	global $config;
			
	/* output */
	global $page;
			
	/* Get alliance players */
	$query  = 'select pid, country, name, lid, experience, alliance, won, lost ';
	$query .= 'from player where pid!='.$config["adminPid"].' and lid="'.$uid.'" ';
	$query .= 'order by lid desc, experience desc';
	$result = warquest_db_query($query);	
	
	$page .= '<div class="subparagraph">Players in level '.$uid.'</div>';
	
	$page .= '<div class="box">';
	$page .= '<table>';
	
	$page .= '<tr>';
	
	$page .= '<th width="35">';
	$page .= 'Top';
	$page .= '</th>';
	
	$page .= '<th width="160">';
	$page .= 'Name';
	$page .= '</th>';
	
	$page .= '<th width="50">';
	$page .= 'Level';
	$page .= '</th>';
	
	$page .= '<th width="90">';
	$page .= 'Experience';	
	$page .= '</th>';
	
	$page .= '<th width="60">';
	$page .= 'Alliance';	
	$page .= '</th>';
	
	$page .= '<th width="50">';
	$page .= 'Won';	
	$page .= '</th>';
	
	$page .= '<th width="50">';
	$page .= 'Lost';	
	$page .= '</th>';
	
	$page .= '</tr>';
	
	$count=1;
	while ($data=warquest_db_fetch_object($result)) {
	
		$page .= '<tr>';
		$page .= '<td>';
		$page .= $count++;
		$page .= '</td>';
		$page .= '<td>';
		$page .= warquest_link('mid='.$mid.'&oid='.$data->pid.'&sid='.PAGE_PLAYERS, warquest_flag_image($data->country));
		$page .= ' ';
		$page .= warquest_link('mid='.$mid.'&oid='.$data->pid.'&sid='.PAGE_PLAYERS, $data->name);
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
		$page .= number_format($data->won,0,",",".");
		$page .= '</td>';
		$page .= '<td>';
		$page .= number_format($data->lost,0,",",".");
		$page .= '</td>';
		$page .= '</tr>';
	}

	$page .= '</table>';
	$page .= '</div>';	
	
	$page .= '<div class="note">';
	$page .= 'Note: Show all players of selected level.';
   $page .= '</div>';
}

function warquest_admin_member_do() {

	/* input */
	global $mid;
	global $sid;
	global $offset;
	global $sort;
	global $config;
	global $player;
	global $nickname;

	/* output */
	global $page;
	
	/* Max records. */
	$limit = 50;
	
	$query  = 'select pid from player '; 
	if (strlen($nickname)>0) {
		$query .= 'where pid like "'.$nickname.'"';
	}
	$result = warquest_db_query($query);	
	$total = warquest_db_num_rows($result);
	
	
		
	if ($total != 0 ) {
					
		$query  = 'select a.pid, a.created, b.request_date, b.name, b.country, b.experience, a.platform, ';
		$query .= 'b.request from player b left join member a on a.pid=b.pid ';
		if (strlen($nickname)>0) {
			$query .= 'where b.pid like "'.$nickname.'" ';
		}
		
	} else {
	
		$query  = 'select a.pid from player a left join member b on a.pid=b.pid ';
		if (strlen($nickname)>0) {
			$query .='where a.name like "%'.$nickname.'%" or b.username like "%'.$nickname.'%"';	
		}	
		$result = warquest_db_query($query);	
		$total = warquest_db_num_rows($result);
		
		$query  = 'select a.pid, a.created, b.request_date, b.name, b.country, b.experience, a.platform, ';
		$query .= 'b.request from player b left join member a on a.pid=b.pid ';
		if (strlen($nickname)>0) {
			$query .= 'where b.name like "%'.$nickname.'%" or a.username like "%'.$nickname.'%" ';
		}
	}
				
	switch ($sort) {
		
			default:
				$query .= 'order by request_date desc ';
				break;
				
			case 1:
				$query .= 'order by country asc ';
				break;
				
			case 2:
				$query .= 'order by name asc ';
				break;
			
			case 3:
				$query .= 'order by request desc ';
				break;
				
			case 4:
				$query .= 'order by platform desc ';
				break;
				
			case 5:
				$query .= 'order by created desc ';
				break;
	}
				
	$query .= 'limit '.$offset.','.$limit;
	
	$result = warquest_db_query($query);	
	
	$page .= '<div class="box">';
	
	$page .= warquest_page_control($offset, $limit, $total, 1, '&sort='.$sort);
	
	$page .= '<table>';
	
	$page .= '<tr>';	
	
	$page .= '<th width="60">';
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&sort=1', "Country");
	$page .= '</th>';
	
	$page .= '<th width="105">';
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&sort=2', "Name");
	$page .= '</th>';

	$page .= '<th width="75">';
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&sort=3', "Requests");
	$page .= '</th>';
	
	$page .= '<th width="80">';
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&sort=4', "Platform");
	$page .= '</th>';
	
	$page .= '<th width="80">';
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&sort=5', "Created");
	$page .= '</th>';
	
	$page .= '<th width="80">';
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&sort=0', "Last Active");
	$page .= '</th>';

	$page .= '</tr>';
	
	while ($data=warquest_db_fetch_object($result)) {
	
		$page .= '<tr>';
		$page .= '<td>';
		$page .= warquest_link('mid='.$mid.'&oid='.$data->pid.'&sid='.PAGE_PLAYERS,warquest_flag_image($data->country));
		$page .= '</td>';
		$page .= '<td>';
		$page .= warquest_link('mid='.$mid.'&oid='.$data->pid.'&sid='.PAGE_PLAYERS, $data->name);		
		$page .= '</td>';
		$page .= '<td>';
		$page .= number_format($data->request,0,",",".");
		$page .= '</td>';
		$page .= '<td>';
		$page .= warquest_platform_image($data->platform);
		$page .= '</td>';
		$page .= '<td>';
		$page .= warquest_ui_ago($data->created);
		$page .= '</td>';
		$page .= '<td>';
		$page .= warquest_ui_ago($data->request_date);
		$page .= '</td>';		
		$page .= '</tr>';
	}

	$page .= '</table>';
	
	$page .= warquest_page_control($offset, $limit, $total, 0, '&sort='.$sort);
	
	$page .= '</div>';	
	
	$page .= '<div class="note">';
	$page .= 'Note: Report show all or filter members.';
   $page .= '</div>';
}

	
function warquest_admin_member_form() {

	/* input */
	global $mid;
	global $nickname;
	
	/* output */
	global $page;
	global $title;
	
	$title = 'Members'; 
		
	$page .= '<div class="subparagraph">'.$title.'</div>';
	
	$page .= '<form method="post">';
	$page .=	'<div class="box">';
	$page .=	'<table>';
		
	$page .=	'<tr>';
	
	$page .=	'<td width="100">Nickname:</td>';
	$page .=	'<td>';
	$page .=	'<input name="nickname" type="text" id="nickname" size="40" maxlength="30" value="'.$nickname.'" >';
	$page .=	'</td>';
	
	$page .=	'<td width="130" align="right">';
	$page .=	'<input type="hidden" name="token" value="'.warquest_token('mid='.$mid.'&sid='.PAGE_PLAYER_LIST).'" />';
	$page .=	'<input type="submit" name="Submit" value="Search" />';
	$page .=	'</td>';
	
	$page .=	'</tr>';
		
	$page .=	'</table>';
	$page .=	'</div>';
	$page .=	'</form>';	
}

/*
** ---------------------
** MACHINE
** ---------------------
*/

/**
 * Admin handler
 */
function warquest_admin() {

	/* input */
	global $config;
	global $sid;
	global $eid;		
	global $other;
	global $player;
	
	/* output */
	global $popup;
	
	if ($player->pid!=$config["adminPid"]) {
	
		$message = 'Access denied!'; 
		$popup .= warquest_box_icon("warning", $message);
		
		return;
	}
	
	/* Event handler */
	switch ($eid) {
						
		case EVENT_ADMIN_EDIT:
			warquest_admin_edit_do();
			break;
			
	   case EVENT_ADMIN_DELETE_MSG:
			warquest_admin_message_delete_do();
			break;
			
		case EVENT_ADMIN_COPY:
			warquest_admin_copy_do();
			break;
			
		case EVENT_ADMIN_DELETE_PLAYER:
			warquest_admin_delete_do();
			break;
			
		case EVENT_ADMIN_UPDATE_TIMERS:
			warquest_admin_update_all_timers_do();
			break;
					
		case EVENT_ADMIN_UPDATE_MONEY:
			warquest_admin_update_all_money_do();
			break;
		
		case EVENT_ADMIN_NEWS_SAVE:	
			warquest_admin_news_save_do();
			break;
			
		case EVENT_ADMIN_NEWS_DELETE:	
			warquest_admin_news_delete_do();
			break;
			
		case EVENT_ADMIN_UPDATE_STAFF:	
			warquest_admin_update_building_staff_do();
			break;
			
		case EVENT_ADMIN_HACK_ACCOUNT:
			warquest_admin_hack();
			break;
			
		case EVENT_ADMIN_UPDATE_INTEREST:
			warquest_cron_player_interest(1);
			break;

		case EVENT_ADMIN_CLEAN_BANK_LOG:
			warquest_cron_clean_bank_log(1);
			break;			
			
		case EVENT_ADMIN_UPDATE_INVITATIONS: 
			warquest_cron_delete_pending_invitations(1);		
			break;
			
		case EVENT_ADMIN_UPDATE_AWARDS:
			warquest_admin_player_award_update_do();
			break;

		case EVENT_ADMIN_UPDATE_LEVELS:
			warquest_admin_update_player_level_do();
			break;
			
		case EVENT_ADMIN_CLEAN_BATTLE_LOG:
			warquest_cron_clean_battle_log(1);	
			break;
			
		case EVENT_ADMIN_UPDATE_ROBOTS:
			warquest_cron_robot_alliancy_update(1);
			break;
			
		case EVENT_ADMIN_OPTIMIZE_DATABASE:
			warquest_admin_optimize_tables_do();
			break;
			
		case EVENT_ADMIN_UPDATE_INCOME:
			warquest_cron_negative_income(1);
			break;
			
		case EVENT_ADMIN_SAVE_TWEET:
			warquest_admin_post_tweet_do();
			break;
			
		case EVENT_ADMIN_BACKUP_DATABASE:
			warquest_cron_backup(1);
			break;
			
		case EVENT_SWITCH_PLANET: 
			warquest_switch_planet_do();
			break;	
	}	
		
	/* Page handler */
	switch ($sid) {
		
		case PAGE_PLAYER_LIST:
			warquest_admin_member_form();
			warquest_admin_member_do();
			break;
			
		case PAGE_PLAYERS:
			warquest_admin_player_form();
			break;
			
		case PAGE_ADMIN_MESSAGES:
			warquest_admin_messages_form();
			break;
			
		case PAGE_LEVEL:
			warquest_admin_level_form();
			break;
			
		case PAGE_LEVEL_ZOOM:
			warquest_admin_level_zoom_form();
			break;
			
		case PAGE_PLAYER_COPY:
			warquest_admin_copy_form();
			break;	
			
		case PAGE_ACTIONS:
			warquest_admin_action_form();
			break;				
			
		case PAGE_ADMIN_NEWS:
			warquest_admin_news();
			warquest_admin_news_log();
			break;
			
		case PAGE_BROWSER:
			warquest_admin_browser_report();
			break;	
			
		case PAGE_INFO:
			warquest_admin_info();
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