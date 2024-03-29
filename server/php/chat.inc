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
**  All copyrights reserved (c) PlaatSoft
*/

/*
** ---------
** Post
** ---------
*/

$message = warquest_post('message', '');

/*
** ---------
** ACTIONS
** ---------
*/

/**
 * Save chat message
 */
function warquest_chat_msg_do() {

	/* input */
	global $other;
	global $message;
	global $player;

	if (strlen($message)>0) {

		warquest_db_chat_insert($player->pid, $other->pid, $message);

		/* Set chat flag */
		$other->chat_notification=$player->pid;

		$message="";
	}
}

/*
** ---------
** GUI
** ---------
*/

function warquest_chat_form() {

	/* input */
	global $mid;
	global $sid;

	global $config;
	global $player;
	global $other;

	global $message;

	/* output */
	global $page;
	global $output;

	/* Clear chat flag */
	$player->chat_notification=0;

	$output->title = t('CHAT_TITLE');

	$page .= '<div class="subparagraph">';
	$page .= $output->title;
	$page .= '</div>';

	$page .= "<script language=\"JavaScript\" type=\"text/javascript\">function limitText(limitField, limitNum) { if (limitField.value.length >= limitNum) { limitField.value = limitField.value.substring(0, limitNum); } } </script>";

	$page .= '<div class="box">';
	$page .= '<textarea style="width:100%" id="message" name="message" rows="5" ';
	$page .= 'onKeyDown="limitText(this,400)">'.$message.'</textarea><br>';
	$page .= warquest_show_smilies("message");
	$page .= '<span class="right2">';
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&eid='.EVENT_FORUM_CHAT_UPDATE.'&oid='.$other->pid, t('LINK_SAVE'), 'save-0');
	$page .= '</span>';
	$page .= '</div>';

	$page .= '<div class="box">';
	$page .= '<div id="chatbox">';
	$page .= '</div>';

	$token = warquest_token('pid='.$player->pid.'&oid='.$other->pid);
	$page .= '<script>
		function update() {
			var chatboxElement = document.getElementById("chatbox");
			var xhr = new XMLHttpRequest();
			xhr.onload = function () {
				chatboxElement.innerHTML = xhr.responseText;
			};
			xhr.open("GET", "chat-update.php?token='.$token.'", true);
			xhr.send();
		}
		setInterval(update, 2000);
		update();
	</script>';

	$page .= "</div>";

	$page .= '<div class="note">';
	$page .= t('CHAT_NOTE');
   $page .= '</div>';
}

function warquest_chatroom_form() {

	/* input */
	global $mid;
	global $sid;

	global $player;
	global $other;

	/* output */
	global $page;
	global $output;

	$output->title = t('CHATROOM_TITLE');

	$page .= '<div class="subparagraph">';
	$page .= $output->title;
	$page .= '</div>';

	$prev = mktime(date("H"),date("i")-8,date("s"),date("m"),date("d"),date("Y"));

	$query  = 'select pid, name, country, lid, experience, request_date from player ';
	$query .= 'where pid!='.$player->pid.' and country!="EU" and request_date>="';
	$query .= date("Y-m-d H:i:s",$prev).'" order by request_date desc';

	$result = warquest_db_query($query);

	$page .= '<div class="box rows">';

	$page .= '<table>';

	$page .= '<tr>';

	$page .= '<th width="35">';
	$page .= '</th>';

	$page .= '<th width="160">';
	$page .= t('GENERAL_PLAYER');
	$page .= '</th>';

	$page .= '<th width="50">';
	$page .= t('GENERAL_LEVEL');
	$page .= '</th>';

	$page .= '<th width="90">';
	$page .= t('GENERAL_EXP');
	$page .= '</th>';

	$page .= '<th width="120">';
	$page .= t('CHATROOM_LAST_ACTIVE');
	$page .= '</th>';

	$page .= '<th width="80">';
	$page .= t('GENERAL_ACTION');
	$page .= '</th>';

	$page .= '</tr>';

	$count = 1;
	while ($data=warquest_db_fetch_object($result)) {
		$page .= '<tr>';
		$page .= '<td>';
		$page .= $count++;
		$page .= '</td>';
		$page .= '<td>';
		$page .= player_format($data->pid, $data->name, $data->country,1);
		$page .= '</td>';
		$page .= '<td>';
		$page .= $data->lid;
		$page .= '</td>';
		$page .= '<td>';
		$page .= number_format($data->experience,0,",",".");
		$page .= '</td>';
		$page .= '<td>';
		$page .= warquest_ui_ago($data->request_date);
		$page .= '</td>';
		$page .= '<td>';
		$page .= warquest_link('mid='.$mid.'&sid='.PAGE_CHAT.'&oid='.$data->pid, t('CHATROOM_CHAT'));
		$page .= '</td>';
		$page .= '</tr>';
	}

	$page .= '</table>';

	$page .= '</div>';

	$page .= '<div class="note">';
	$page .= t('CHATROOM_NOTE');
   $page .= '</div>';
}

/*
** ---------
** HANDLER
** ---------
*/

function warquest_chat_events() {

	global $eid;
	global $sid;

	/* Event handler */
	switch ($eid) {

		case EVENT_FORUM_CHAT_UPDATE:
						warquest_chat_msg_do();
						break;
	}
}

function warquest_chat_forms() {

	/* input */
	global $sid;

	/* Page handler */
	switch ($sid) {

		case PAGE_CHATROOM:
					warquest_chatroom_form();
					break;

		case PAGE_CHAT:
					warquest_chat_form();
					break;
	}
}
