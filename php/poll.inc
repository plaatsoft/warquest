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
** UTILS
** ---------------------
*/

function warquest_poll_text($vote) {
	
	if ($vote==1) {
		return t('POLL_VOTE');
	} else {
		return t('POLL_VOTES');
	}
}

function warquest_poll_teaser() {

	/* input */		
	global $player; 
	
	$page ="";
		
	$query  = 'select poll_id, question from poll where disabled=0 order by poll_id desc limit 0,1 '; 
	$result = warquest_db_query($query);
	
	if ($data=warquest_db_fetch_object($result)) {
	
		if ( warquest_db_player_poll_voted($player->pid, $data->poll_id)==0) {
		
			$page .= '<br/>';
			$page .=' <span class="subparagraph2">';
			$page .= t('POLL_TEASER_TITLE'); 
			$page .=' </span>';
			$page .= '<br>';
			$page .= $data->question.' '.warquest_link('mid='.MENU_FORUMS.'&sid='.PAGE_POLL, t('POLL_VOTE'), 'vote');			
			$page .= '<br/><br/>';
		}
	}

	return $page;
}

/*
** ---------------------
** ACTIONS
** ---------------------
*/

function warquest_poll_vote_remove_do() {

	/* input */			
	global $tid;
	
	/* output */
	global $player;
	global $popup;

	warquest_db_player_poll_vote_remove($player->pid, $tid);
	
	$player->experience-=10;
	
	$message = t('POLL_VOTE_REMOVE');
	$popup .= warquest_box_icon("info", $message);
}

function warquest_poll_vote_add_do() {

	/* input */		
	global $tid;
	
	/* output */
	global $player;
	global $popup;

	/* myusername parameter */
	if (isset($_POST['poll'.$tid])) {
		$answer_id = $_POST['poll'.$tid];

		warquest_db_player_poll_vote_add($player->pid, $answer_id, $tid);
	
		$message = t('POLL_VOTE_ADD');
		$popup .= warquest_box_icon("info", $message);
		
		$player->experience+=10;
		
	} else {
	
		$message = t('POLL_WARNING');
		$popup .= warquest_box_icon("warning", $message);
	}
		
}

/*
** ---------------------
** POLL RESULT FORM
** ---------------------
*/

function warquest_poll_result_form() {

	/* input */		
	global $mid;
	global $sid;
	global $tid;
	global $player;
	
	/* output */
	global $title;
	global $page;
	
	$title = t('POLL_RESULT_TITLE');
		
	$page .= '<div class="subparagraph">';
	$page .= $title;
	$page .= '</div>';
	
	$query1  = 'select question from poll where poll_id='.$tid;
	$result1 = warquest_db_query($query1);
	$data1 = warquest_db_fetch_object($result1);
	
	$query2  = 'select a.pid, (select name from player where pid=a.pid) as name, ';
	$query2 .= '(select country from player where pid=a.pid) as country, ';
	$query2 .= '(select answer from poll_answer where answer_id=a.answer_id) as answer ';
	$query2 .= 'from player_poll a where a.poll_id='.$tid.' order by answer_id asc';
	$result2 = warquest_db_query($query2);
	
	$page .= '<div class="box">';
		
	$page .= '<div class="vote">';
	$page .= $data1->question;
	$page .= '</div>';
		
	$tmp = "";
	while ($data2=warquest_db_fetch_object($result2)) {

		if ($tmp!=$data2->answer) {			
			$page .= '<br/>';
			$page .= $data2->answer;
			$page .= '<br/>';
		}
		
		$page .= player_format($data2->pid,$data2->name, $data2->country);
		$page .= '<br/>';
		
		$tmp = $data2->answer;
	}
	
	$page .= '<br/>';
	$page .= '</div>';
}

/*
** ---------------------
** POLL FORM
** ---------------------
*/

function warquest_poll_form() {

	/* input */	
	global $mid;
	global $sid;
	global $player;
	global $config;

	/* output */
	global $title;
	global $page;
	
	$title = t('POLL_TITLE');
		
	$page .= '<div class="subparagraph">';
	$page .= $title;
	$page .= '</div>';
	
	$query1  = 'select a.poll_id, count(b.pid) as total, ';
	$query1 .= '(select question from poll c where c.poll_id=a.poll_id) as question, ';
	$query1 .= '(select disabled from poll c where c.poll_id=a.poll_id) as disabled ';
	$query1 .= 'from poll_answer a left join player_poll b on a.answer_id=b.answer_id ';
	$query1 .= 'group by a.poll_id order by disabled asc, poll_id desc '; 
	
	$result1 = warquest_db_query($query1);
	$total = warquest_db_num_rows($result1);
	
	$page .= '<div class="box">';
	
	$page .= '<table>';
	
	$count = 0; 
	while ($data1=warquest_db_fetch_object($result1)) {

		$answer = warquest_db_player_poll_voted($player->pid, $data1->poll_id);
	
		$count++;
				
		$query2  = 'select a.answer_id, a.answer, ';
		$query2 .= '(select count(answer_id) from player_poll b where b.answer_id=a.answer_id) as total ';
		$query2 .= 'from poll_answer a where a.poll_id='.$data1->poll_id.' order by a.answer_id';
		$result2 = warquest_db_query($query2);
			
		$page .= '<tr>';
			
		$page .= '<td width="75" valign="top">';
				
		$page .= warquest_image('other/forum.png','width="64" height="64"');
			
		$page .= '</td>';			
		$page .= '<td width="375">';
		$page .= '<span class="vote">'.$data1->question.'</span>';			
		$page .= '<br/>';				
		while ($data2 = warquest_db_fetch_object($result2)) {
			
			$tmp = 0; 
			if (	$data1->total>0) {
				$tmp = ($data2->total/$data1->total)*100;
			}
	
			$page .= warquest_ui_radiobox('poll'.$data1->poll_id, $data2->answer_id, $answer == $data2->answer_id, (($data1->disabled==1) || ($answer!=0)));		
			$page .= ' '.$data2->answer;
			
			if ((($data1->disabled==1) || ($answer!=0)) && ($tmp>0)) {
				$page .= ' <i>(';
				$page .= health_format($tmp).'%, '.health_format($data2->total).' '.warquest_poll_text($data2->total);
				$page .= ')</i>';
			}
			
			$page .= '<br/>';			
		}				
		$page .= '</td>';
						
		$page .= '<td width="50" valign="top" align="right" >';						
			
		if ($data1->disabled==0) {
			if ($answer==0) {
				$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&eid=100&tid='.$data1->poll_id, t('POLL_VOTE'), 'vote-'.$count);	
			} else {
				$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&eid=101&tid='.$data1->poll_id, t('POLL_CANCEL'), 'cancel-'.$count);			
			}
			$page .= "<br/><br/>";
		}
		
		if ($player->pid==$config['adminPid']) {
			$page .= warquest_link('mid='.$mid.'&sid='.PAGE_POLL_RESULT.'&tid='.$data1->poll_id, t('POLL_RESULTS'), 'results'.$count);	
		}
		$page .= '</td>';
				
		$page .= '</tr>';
		
		if (($data1->disabled==1) || ($answer!=0)) {
			$page .= '<tr>';		
			$page .= '<td>';
			$page .= '</td>';
			$page .= '<td colspan="2">';
			$page .= t('POLL_SUMMARY', health_format($data1->total));
			
			if ($data1->disabled==1) {
				$page .= ' '.t('POLL_ClOSED'); 
			}
			
			$page .= '</td>';
			$page .= '</tr>';
		}
			
		if ($count < $total) {
			$page .= '<tr>';
			$page .= '<td colspan="3">';
			$page .= '<hr/>';
			$page .= '</td>';
			$page .= '</tr>';
		}		
	}	

	$page .= '</table>';

	$page .= '</div>';	
}

/*
** ---------------------
** HANDLER
** ---------------------
*/

function warquest_poll_events() {

	global $eid;
	
	/* Event handler */
	switch ($eid) {
	
		case 100: warquest_poll_vote_add_do();
					 break;	

		case 101: warquest_poll_vote_remove_do();
					 break;		
					 
	}
}
	
/*
** ---------------------
** THE END
** ---------------------
*/


?>
