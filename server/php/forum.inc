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
** Handle Post Parameters
** ---------------------
*/

$comment = warquest_post('comment', '');
$comment = filterBadWords($comment);

$topic = warquest_post('topic', '');
$topic = filterBadWords($topic);

$search = warquest_post('search', '');

/*
** ---------------------
** COMMENTS 
** ---------------------
*/

/**
 * Remove comment
 */
function warquest_comment_delete_do() {
	
	/* input */
	global $uid;
		
	/* output */
	global $output;
	
	if (warquest_db_comment_delete($uid) == 1) {
		
		$message = t('HOME_MESSAGE_DELETED');
		$output->popup .= warquest_box_icon("info", $message);		
		
		/* Reset comment id */
		$uid=0;
	}
}

/**
 * Send comment notification to all clan members 
 */
function warquest_clan_comment_notification() {

	/* input */
	global $cid;
	global $player;
		
	$clan = warquest_db_clan($cid);
	
	if ( isset($clan->cid) ) {
		
		$query1 = 'select pid from player_clan where cid='.$cid.' and pid<>'.$player->pid;
		$result1 = warquest_db_query($query1);	

		while ($data1=warquest_db_fetch_object($result1)) {
		
			$data2 = warquest_db_player($data1->pid);
			$data2->clan_notification++;
			warquest_db_player_update($data2);
		}
	}
}
	
/**
 * Save comment
 */
function warquest_comment_save_do() {

	/* input */
	global $uid;
	global $cid;
	global $tid;
	global $player;
	global $other;	
	global $comment;

	/* output */
	global $output;
	
	if (!isset($tid)) {
		$tid=0;
	}
	
	if (!isset($cid)) {
		$cid=0;
	}
		
	if (strlen($comment)>0) {
		
		if (isset($other->pid)) {	
			
			/* Private player message */
			warquest_db_comment_insert($tid, $cid, $player->pid, $other->pid, $comment);
				
			if ($uid==0) {
			
				/* Only new comment giv email notification */				
				warquest_comment_mail($other->pid, $comment, $player->name);
				
				/* only new comment give notifacation */
				$other->comment_notification++;				
			}
				
			$message = t('ALLIANCE_COMMENT_PLAYER', $other->name);
					
		} else if ($tid>0) {
			
			/* Forum message for all players */
			if ($uid==0) {
			
				/* new comment */
				warquest_db_comment_insert($tid, 0, $player->pid, 0, $comment);
				
			} else {
			
				/* update comment */
				warquest_db_comment_update($uid, $comment);
			}
		
			$message = t('ALLIANCE_COMMENT_ALL');
			warquest_info("Post message: ".$comment);
			
		} else {
				
			/* Clan comment only for clan players */
			if ($uid==0) {
			
				warquest_db_comment_insert(0, $cid, $player->pid, 0, $comment);
				
				/* only new comment give notification */
				warquest_clan_comment_notification();
				
			} else {
			
				warquest_db_comment_update($uid, $comment);
			}
						
			$clan = warquest_db_clan($cid);
		
			$message = t('CLAN_COMMENT_ALL', clan_format($clan));
			warquest_info("Post message: ".$comment);
		}
						
		/* Clear input parameters */
		$uid = 0;
		
		$output->popup .= warquest_box_icon("info", $message);
	}
}

/**
 * forum comment
 */
function warquest_comment_form() {

	/* input */
	global $mid;
	global $sid;
	global $uid;
	global $fid;
	global $tid;	
	global $other;
	
	global $config;
	global $player;
	global $other;
	
	/* output */
	global $page;
	global $output;
	global $offset;
	
	$output->title = t('ALLIANCE_COMMENT_TITLE');
		
	$comment = "";
	if ($uid!=0) {
		$query  = 'select comment from comment where id='.$uid;
		$result = warquest_db_query($query);	
		
		$data = warquest_db_fetch_object($result);		
		$comment = $data->comment;		
	} 
	
	$page .= "<script language=\"JavaScript\" type=\"text/javascript\">function limitText(limitField, limitNum) { if (limitField.value.length >= limitNum) { limitField.value = limitField.value.substring(0, limitNum); } } </script>";

	$page .= '<div class="subparagraph">';
	if ($fid!=0) {
		$page .= warquest_link('mid='.$mid.'&sid='.PAGE_FORUM, t('FORUM_TITLE2'), 'forum');
		$page .= ' - ';
	}
	if ($tid!=0) {
		$page .= warquest_link('mid='.$mid.'&sid='.PAGE_TOPIC.'&fid='.$fid, t('TOPIC_TITLE'), 'topic');
		$page .= ' - '.t('HOME_MESSAGES_TITLE');
	} else {
		$page .= t('ALLIANCE_COMMENT_TITLE');
	}
	$page .= '</div>';	
	
	$page .= '<div class="box">';	
	
	$page .= '<table>';
	$page .= '<tr>';
	$page .= '<td width="500">';

	if (isset($other->pid)) {
		$page .= t('ALLIANCE_COMMENT_TEXT2', $other->name).'<br/>'; 
	} else {
		$page .= t('ALLIANCE_COMMENT_TEXT1').'<br/>'; 
	} 

	$page .= '<textarea style="width:100%" id="comment" name="comment" rows="5" ';
	$page .= 'onKeyDown="limitText(this,400)">'.$comment.'</textarea><br/>';
	$page .= warquest_show_smilies();
	$page .= '<br/><br/>';
	
	if (isset($other->pid)) {
		$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_FORUM_COMMENT_SAVE.'&fid='.$fid.'&tid='.$tid.'&oid='.$other->pid.'&uid='.$uid, t('LINK_SAVE'), 'save-0');
	} else {
		$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_FORUM_COMMENT_SAVE.'&fid='.$fid.'&tid='.$tid.'&oid=0&uid='.$uid, t('LINK_SAVE'), 'save-0');
	}
	if ($uid!=0) {
		$page .= ' ';
		$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_FORUM_COMMENT_DELETE.'&fid='.$fid.'&tid='.$tid.'&uid='.$uid, t('LINK_DELETE'), 'delete-0');
	}
	
	$page .= '</td>';
	$page .= '</tr>';
	$page .= '</table>';

	$page .= "</div>";	
	
	/* ---------------------------------------------------- */

	if (isset($other->pid)) {
		
		return;
	}
	
	$limit=30;
		
	$query  = 'select pid1 from comment where pid2=0 and deleted=0 and tid='.$tid;
	$result = warquest_db_query($query);	
	$total = warquest_db_num_rows($result);
	
	if (isset($other->pid)) {	
		$query  = 'select a.id, a.pid1, a.date, a.comment, b.name, b.country from comment a, player b ';
		$query .= 'where a.pid1=b.pid and a.pid2='.$other->pid.' and a.deleted=0 and a.tid='.$tid.' ';
	} else {
		$query  = 'select a.id, a.pid1, a.date, a.comment, b.name, b.country from comment a, player b ';
		$query .= 'where a.pid1=b.pid and a.pid2=0 and a.deleted=0 and a.tid='.$tid.' ';
	}

	if (warquest_db_query_pattern($player, PATTERN_SORT1)==1) {
		$query .= 'order by a.date desc ';
	} else {
		$query .= 'order by a.date asc ';
	}
	$query .= 'limit '.$offset.','.$limit;
	
	$result = warquest_db_query($query);	
	
	$page .= '<div id="news">';

	$page .= '<div class="paragraph">'.t('GENERAL_TOPIC').'</div>';
	
	if ($tid!=0) {
		$query2 = 'select a.date, a.description, a.pid, b.name from topic a, player b where a.pid=b.pid and a.tid='.$tid.' ';			
		$result2 = warquest_db_query($query2);
		$data2 = warquest_db_fetch_object($result2);
		
		$page .= '<div class="box"><span class="subparagraph">';
		$page .= warquest_parse_smilies(wordwrap($data2->description, 40, "\n\r", true));
		$page .= '</span></div>';
	}
	
	$page .= '<div class="paragraph">'.t('ALLIANCE_PLAYER_NEWS').'</div>';
	
	$page .= '<div class="box rows">';
	
	$page .= warquest_page_control($offset, $limit, $total, 1, '&tid='.$tid.'&fid='.$fid);
	
	$page .= '<table>';
	
	$page .= '<tr>';
	
	$page .= '<th width="75">'.t('GENERAL_AGO').'</b></th>';
	$page .= '<th width="370">'.t('GENERAL_MESSAGE').'</b></th>';
	$page .= '<th width="55" align="right">'.t('GENERAL_ACTION').'</th>';
			
	$page .= '</tr>';
	
	$count=0;
	while ($data=warquest_db_fetch_object($result)) {
	
		$page .= '<tr valign="top">';
		
		$page .= '<td>';
		$page .= warquest_ui_ago($data->date);
		$page .= '</td>';
				
		$page .= '<td>';
		$page .= player_format($data->pid1,$data->name, $data->country);
		$page .= '<br/>';
		$page .= warquest_parse_smilies(wordwrap($data->comment, 40, "\n\r", true));
		$page .= '</td>';
		
		$page .= '<td align="right">';
		if (($player->pid==$data->pid1) || ($player->pid==$config["adminPid"])) {
			$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&fid='.$fid.'&tid='.$tid.'&uid='.$data->id, t('LINK_EDIT'), 'edit'.$count);
		}
		$page .= '</td>';
		
		$page .= '</tr>';
		
		$count++;
	}
	$page .= '</table>';
	
	$page .= warquest_page_control($offset, $limit, $total, 0, '&tid='.$tid.'&fid='.$fid);
	
	$page .= '</div>';
}

/**
 * Clan comment
 */
function warquest_clan_comment_form() {

	/* input */
	global $mid;
	global $sid;
	global $uid;

	global $config;
	global $player;
	global $other;
	
	/* output */
	global $page;
	global $output;
	global $offset;
	
	$player_clan = warquest_db_player_clan($player->pid);
		
	/* Clear clan notifcation flag is any. */
	$player->clan_notification = 0;
	
	$output->title = t('CLAN_COMMENT_TITLE');
	
	$page .= '<div class="subparagraph">';
	$page .= $output->title;
	$page .= '</div>';	
		
	if ( !isset($player_clan->cid) || ($player_clan->approved==0)) { 
	
		$message = t('CLAN_COMMENT_NO_CLAN');
		$page .= warquest_box_icon("warning", $message);
		
	} else {
		
		$clan = warquest_db_clan($player_clan->cid);
		
		/* ---------------------------------------------------- */
	
		$comment = "";
		if ($uid!=0) {
			$query  = 'select comment from comment where id='.$uid;
			$result = warquest_db_query($query);	
			
			$data = warquest_db_fetch_object($result);		
			$comment = $data->comment;		
		} 
	
		$page .= "<script language=\"JavaScript\" type=\"text/javascript\">function limitText(limitField, limitNum) { if (limitField.value.length >= limitNum) { limitField.value = limitField.value.substring(0, limitNum); } } </script>";
		
		$page .= '<div class="box">';	
	
		$page .= '<table>';
		$page .= '<tr>';
		$page .= '<td width="500">';
		$page .= t('CLAN_COMMENT_TEXT', clan_format($clan)).'<br/>'; 
		
		$page .= '<textarea style="width:100%" id="comment" name="comment" rows="5" ';
		$page .= 'onKeyDown="limitText(this,400)">'.$comment.'</textarea><br/>';
		$page .= warquest_show_smilies();
		$page .= '<br/><br/>';
	
		$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_FORUM_COMMENT_SAVE.'&cid='.$player_clan->cid.'&uid='.$uid, t('LINK_SAVE'), 'save-0');
		if ($uid!=0) {
			$page .= ' ';
			$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_FORUM_COMMENT_DELETE.'&cid='.$player_clan->cid.'&uid='.$uid, t('LINK_DELETE'), 'delete-0');
		}
	
		$page .= '</td>';
		$page .= '</tr>';
		$page .= '</table>';
	
		$page .= "</div>";	
	
		/* ---------------------------------------------------- */
	
		$limit=30;
		
		$query  = 'select pid1 from comment where deleted=0 and cid='.$player_clan->cid;
		$result = warquest_db_query($query);	
		$total = warquest_db_num_rows($result);
		
		$query  = 'select a.id, a.pid1, a.date, a.comment, b.name, b.country from comment a, player b ';
		$query .= 'where a.pid1=b.pid and a.pid2=0 and a.deleted=0 and a.cid='.$player_clan->cid.' ';

		if (warquest_db_query_pattern($player, PATTERN_SORT1)==1) {
			$query .= 'order by a.date desc ';
		} else {
			$query .= 'order by a.date asc ';
		}
		$query .= 'limit '.$offset.','.$limit;
		
		$result = warquest_db_query($query);	
	
		$page .= '<div class="box rows">';
	
		$page .= warquest_page_control($offset, $limit, $total, 1, '&cid='.$player_clan->cid);
	
		$page .= '<table>';
	
		$page .= '<tr>';
	
		$page .= '<th width="75">';
		$page .= t('GENERAL_AGO');
		$page .= '</th>';
		
		$page .= '<th width="370">';
		$page .= t('GENERAL_MESSAGE');
		$page .= '</th>';
		
		$page .= '<th width="55" align="right">';
		$page .= t('GENERAL_ACTION');
		$page .= '</th>';
				
		$page .= '</tr>';
	
		$count=0;
		while ($data=warquest_db_fetch_object($result)) {
		
			$page .= '<tr valign="top">';
		
			$page .= '<td>';
			$page .= warquest_ui_ago($data->date);
			$page .= '</td>';
					
			$page .= '<td>';
			$page .= player_format($data->pid1,$data->name, $data->country);
			$page .= '<br/>';
			$page .= warquest_parse_smilies(wordwrap($data->comment, 40, "\n\r", true));
			$page .= '</td>';
		
			$page .= '<td align="right">';
			if (($player->pid==$data->pid1) || ($player->pid==$config["adminPid"])) {
				$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&cid='.$player_clan->cid.'&uid='.$data->id, t('LINK_EDIT'), 'edit'.$count);
			}
			$page .= '</td>';
			
			$page .= '</tr>';
			
			$count++;
		}
		$page .= '</table>';
		
		$page .= warquest_page_control($offset, $limit, $total, 0, '&cid='.$player_clan->cid);
		
		$page .= '</div>';
	}
}

/*
** ---------------------
** TOPICS
** ---------------------
*/

function warquest_topic_delete_do() {

	/* input */
	global $tid;

	/* output */
	global $output;
	
		
	if (warquest_db_topic_delete($tid)==1) {
						
		$message = t('TOPIC_DELETED');
		$output->popup .= warquest_box_icon("info", $message);
		
		/* Reset tid */
		$tid=0;
	}	
}

function warquest_topic_save_do() {

	/* input */
	global $fid;
	global $tid;
	global $player;
	global $topic;	
	
	/* output */
	global $output;
	
	if (strlen($topic)>0) {
		
		if ($tid==0) {
			warquest_db_topic_insert($player->pid, $fid, $topic);
	
			$message = t('TOPIC_CREATED');
			$output->popup .= warquest_box_icon("info", $message);
			
		} else {
		
			warquest_db_topic_update($tid, $topic);
			
			$message = t('TOPIC_UPDATED');
			$output->popup .= warquest_box_icon("info", $message);
		}
		
		/* clear topic after insert */
		$tid=0;
	}	
}

	
function warquest_topic_form() {

	/* input */
	global $mid;
	global $sid;
	global $tid;
	global $fid;
	global $topic;
	global $search;
	global $config;
	
	global $player;
	global $other;
	
	/* output */
	global $page;
	global $output;
	global $offset;
	
	$output->title = t('TOPIC_TITLE');

	if (($fid==0) && (strlen($search)>=0) && (strlen($search)<3)) {
		
		$message = t('FORUM_SEARCH_TOKEN');
		$page .= warquest_box_icon("info", $message);
	
		return;
	}
	
	$topic="";
	if ($tid!=0) {	
		$query  = 'select description from topic where tid='.$tid;
		$result = warquest_db_query($query);	
		if ($data = warquest_db_fetch_object($result)) {
			$topic = $data->description;
		}
	}

	$page .= '<div class="subparagraph">';
	$page .= warquest_link('mid='.$mid.'&sid='.PAGE_FORUM, t('FORUM_TITLE2'), 'forum');
	$page .= ' - ';
	$page .= t('TOPIC_TITLE');
	$page .= '</div>';	
	
	if (strlen($search)==0) {
		$page .= '<div class="box">';	

		$page .= "<script language=\"JavaScript\" type=\"text/javascript\">function limitText(limitField, limitNum) { if (limitField.value.length >= limitNum) { limitField.value = limitField.value.substring(0, limitNum); } } </script>";
	
		$page .= t('TOPIC_CREATED_INPUT');
		$page .= '<br/>';
		$page .= '<textarea style="width:100%" id="topic" name="topic" rows="1" ';
		$page .= 'onKeyDown="limitText(this,80)">'.$topic.'</textarea><br/>';
		$page .= warquest_show_smilies('topic');
		$page .= '<br/><br/>';
	
		$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&tid='.$tid.'&fid='.$fid.'&eid='.EVENT_FORUM_TOPIC_SAVE, t('LINK_SAVE'), 'save-0').' ';
		if ($tid!=0) {
			$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&tid='.$tid.'&fid='.$fid.'&eid='.EVENT_FORUM_TOPIC_DELETE, t('LINK_DELETE'), 'delete-0');
		}
	}

	$page .= '</div>';
	
	/* ------------------------------------------------- */
		
	$page .= '<div class="subparagraph">';
	if (strlen($search)==0) {
		$page .= t('FORUM_'.$fid).'  ';
	}
	$page .= t('GENERAL_TOPICS');
	$page .= '</div>';	

	$limit=10;

	if (strlen($search)==0) {
		$query  = 'select tid from topic where deleted=0 and fid='.$fid;
		$result = warquest_db_query($query);	
		$total = warquest_db_num_rows($result);
	
		$query  = 'select b.tid, b.fid, b.description, b.date, c.name, c.country, c.pid from ';
		$query .= '(select * from comment where deleted=0 order by date desc) as a '; 
		$query .= 'right join topic as b on a.tid=b.tid left join player as c ';
		$query .= 'on b.pid=c.pid where b.deleted=0 and b.fid='.$fid.' group by b.tid ';
		$query .= 'order by ifnull(a.date, b.date) desc ';
		$query .= 'limit '.$offset.','.$limit;
		
	} else {
	
		$query  = 'select tid from topic where deleted=0 and description like "%'.$search.'%"';
		$result = warquest_db_query($query);	
		$total = warquest_db_num_rows($result);
	
		$query  = 'select b.tid, b.fid, b.description, b.date, c.name, c.country, c.pid from ';
		$query .= '(select * from comment where deleted=0 order by date desc) as a '; 
		$query .= 'right join topic as b on a.tid=b.tid left join player as c ';
		$query .= 'on b.pid=c.pid where b.deleted=0 and b.description like "%'.$search.'%" group by b.tid ';
		$query .= 'order by ifnull(a.date, b.date) desc ';
	}
	
	$result = warquest_db_query($query);	
	$count = warquest_db_num_rows($result);
		
	if ($count == 0 ) {
	
		$message = t('TOPIC_NO_TOPICS');
		$page .= warquest_box_icon("info", $message);
	
	} else {
			
		$page .= '<div class="box rows">';
		
		if (strlen($search)==0) {
			$page .= warquest_page_control($offset, $limit, $total, 1, '&fid='.$fid);
		}
		
		$page .= '<table>';
	
		$page .= '<tr>';
	
		$page .= '<td width="75">';
		$page .= '<b></b>';
		$page .= '</td>';
	
		$page .= '<td width="230">';
		$page .= '</td>';

		$page .= '<td width="195">';
		$page .= '</td>';
		
		$page .= '</tr>';
				
		$count4 = 0;
		while ($data = warquest_db_fetch_object($result)) {
			
			$count4++;
			
			$query2  = 'select id from comment where deleted=0 and tid='.$data->tid;	
			$result2 = warquest_db_query($query2);
			$count2 = warquest_db_num_rows($result2);
			
			$query3  = 'select a.date, a.pid1, c.name, c.country from topic as b, comment as a left join player as c ';
			$query3 .= 'on a.pid1=c.pid where b.fid='.$data->fid.' and a.tid=b.tid and b.tid='.$data->tid.' ';
			$query3 .= 'and a.deleted=0 order by a.date desc';			
		
			if ($result3 = warquest_db_query($query3)) {
				$data3 = warquest_db_fetch_object($result3);	
			}
			
			$page .= '<tr>';
			
			$page .= '<td>';
			$page .= warquest_link('mid='.$mid.'&sid='.PAGE_COMMENT.'&fid='.$data->fid.'&tid='.$data->tid,
				warquest_image('other/forum.png','width="64" height="64"'), $count4);
			$page .= '</td>';
		
			$page .= '<td valign="top">';
			$page .= '<span class="topic">';
			$page .= warquest_link('mid='.$mid.'&sid='.PAGE_COMMENT.'&fid='.$data->fid.'&tid='.$data->tid, 
				warquest_parse_smilies($data->description),'select'.$count4);
			$page .= '</span>';	
			$page .= '<br/>';
			$page .= '<i>';	
			$page .= t('TOPIC_CREATED_BY', player_format($data->pid, $data->name, $data->country));
			$page .= '</i>';		
			$page .= '</td>';
				
			$page .= '<td valign="top">';
			$page .=  health_format($count2).' '.t('GENERAL_MESSAGES').' ';
			
			if (($player->pid==$data->pid) || ($player->pid==$config["adminPid"])) {
				$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&fid='.$data->fid.'&tid='.$data->tid, t('LINK_EDIT'),'edit'.$count4);
			}
			$page .= '<br/>';
			
			if (isset($data3->date)) {
				$page .= '<br/><b>'.t('GENERAL_LAST_MESSAGE').'</b><br/>';
			
				$page .= warquest_ui_ago($data3->date).' '.t('GENERAL_BY').' ';
				$page .= player_format($data3->pid1,$data3->name, $data3->country);
			}
			$page .= '</td>';
			$page .= '</tr>';
			
			if ($count!=$count4) {
				$page .= '<tr>';
				$page .= '<td colspan="3" class="bar">&nbsp;</td>';
				$page .= '</tr>';
			}
		}
		
		$page .= '</table>';
		
		if (strlen($search)==0) {
			$page .= warquest_page_control($offset, $limit, $total, 0, '&fid='.$fid);
		}
	}

	$page .= "</div>";	
	$page .= '<div class="note">'.t('TOPIC_NOTE').'</div>';
}

/*
** ---------------------
** FORUMS
** ---------------------
*/

function warquest_forum_form() {

	/* input */	
	global $mid;
	global $sid;	
	global $config;
	global $player;		
	global $search;	
	
	/* output */
	global $page;
	global $output;
	
	$output->title = t('FORUM_TITLE2');
		
	$page .= '<div class="subparagraph">';
	$page .= $output->title;
	$page .= '</div>';
	
	$page .=	'<div class="box">';	
	$page .=	'<b>'.t('GENERAL_TOPIC').'</b>: ';
	$page .=	'<input name="search" type="text" id="search" size="40" maxlength="30" value="'.$search.'" onkeydown="if (event.keyCode == 13) return false" >';
	$page .=	'<div class="right2">';
	$page .= warquest_link('mid='.$mid.'&sid='.PAGE_TOPIC,t('LINK_SEARCH'),'search-0');
	$page .=	'</div>';
	$page .=	'</div>';
		
	$page .= '<div class="box rows">';
	
	$page .= '<table>';
	
	$page .= '<tr>';
		
	$page .= '<td width="75">';
	$page .= '</td>';
	
	$page .= '<td width="230" valign="top">';
	$page .= '</td>';
	
	$page .= '<td width="195" valign="top">';
	$page .= '</td>';
	
	$page .= '</tr>';
	
	for ($tmp=1; $tmp <= $config["max_forums"]; $tmp++) {
	
		$query  = 'select tid from topic where fid='.$tmp.' and deleted=0';
		$result = warquest_db_query($query);
		$count = warquest_db_num_rows($result);
		
		$query  = 'select a.date, a.pid1, c.name, c.country from topic as b left join comment as a on a.tid=b.tid left join player as c ';
		$query .= 'on a.pid1=c.pid where b.fid='.$tmp.' and a.deleted=0 order by a.date desc';			
		if ($result = warquest_db_query($query)) {
			$data = warquest_db_fetch_object($result);	
		}
		$count2 = warquest_db_num_rows($result);
				
		$page .= '<tr>';
	
		$page .= '<td>';
		$page .= warquest_link('mid='.$mid.'&sid='.PAGE_TOPIC.'&fid='.$tmp, 
						warquest_image('other/forum.png','width="64" height="64"'),'forum'.$tmp);
		$page .= '</td>';
	
		$page .= '<td>';
		$page .= '<span class="paragraph">';
		$page .= warquest_link('mid='.$mid.'&sid='.PAGE_TOPIC.'&fid='.$tmp, t('FORUM_'.$tmp), 'forum'.$tmp);
		$page .= '</span>';
		
		$page .= '<br/>';
		
		$page .= '<div class="remark">';
		$page .= t('FORUM_NOTE_'.$tmp).'<br/>';
			if ($tmp != $config["max_forums"]) {		
			$page .= t('GENERAL_FORUM_MODERATED', player_format($config["adminPid"], 'admin','NL'));
		} else {
			$page .= t('GENERAL_NOT_MODERATED');
		}			
		$page .= '</div>';
		
		$page .= '</td>';
	
		$page .= '<td valign="top">';
		$page .= health_format($count).' '.t('GENERAL_TOPICS').' - ';
		$page .= health_format($count2).' '.t('GENERAL_MESSAGES').'<br/>';
		if (isset($data->date)) {
			$page .= '<br/>';
			$page .= '<b>'.t('GENERAL_LAST_MESSAGE').':</b><br/>';
			$page .= warquest_ui_ago($data->date).' '.t('GENERAL_BY').' ';
			$page .= player_format($data->pid1,$data->name, $data->country);
		}
		$page .= '</td>';
		
		$page .= '</tr>';
	
		if ($tmp != $config["max_forums"]) {
			$page .= '<tr>';
			$page .= '<td colspan="3" class="bar">&nbsp;</td>';
			$page .= '</tr>';
		}
	}
	$page .= '</table>';
	$page .= '</div>';
	
	$page .= '<div class="note">'.t('FORUM_NOTE').'</div>';
}

/*
** ---------------------
** HANDLER
** ---------------------
*/

function warquest_forum() {

	/* input */
	global $sid;
	global $eid;

	/* Event Handler */
	switch ($eid) {
				
		case EVENT_FORUM_COMMENT_SAVE:
			warquest_comment_save_do();
			break;
			
		case EVENT_FORUM_COMMENT_DELETE:
			warquest_comment_delete_do();
			break;
					
		case EVENT_FORUM_TOPIC_SAVE:
			warquest_topic_save_do();
			break;
			
		case EVENT_FORUM_TOPIC_DELETE:
			warquest_topic_delete_do();
			break;
			
		case EVENT_SWITCH_PLANET: 
			warquest_switch_planet_do();
			break;	
	}

	warquest_chat_events();
	warquest_poll_events();
						
	/* Page handler */
	switch ($sid) {
				  
		case PAGE_FORUM:
					warquest_forum_form();
					break;
				 
		case PAGE_TOPIC:
					warquest_topic_form();
					break;		
				  
		case PAGE_COMMENT: 
					warquest_comment_form();
					break;
					
		case PAGE_CLAN_COMMENT:
					warquest_clan_comment_form();
	}	
	
	warquest_poll_forms();
	warquest_chat_forms();
	warquest_player();	
}

?>