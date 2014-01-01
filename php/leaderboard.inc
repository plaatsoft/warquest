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
** ---------------------------------------------------------------- 
** LEADERBORDS
** ---------------------------------------------------------------- 
*/

/*
** ---------------------
** Leaderboard best player per country
** ---------------------
*/

function warquest_leaderboard3_form() {

	/* input */
	global $player;
	global $uid;
	global $sid;
	global $mid;
	global $offset;
	global $sort;
		
	/* output */
	global $page;
	global $title;
	
	sscanf($uid, "%03d%03d", $code[0], $code[1]);
	$code = chr($code[0]).chr($code[1]);
	
	$title = t('LEADERBORD_PLAYER_COUNTRY',warquest_landcode($uid));
	
	$limit = 50;

	$query  = 'select pid from player where country="'.$code.'"';
	$result = warquest_db_query($query);	
	$total=warquest_db_num_rows($result);
	
	/* Get alliance players */
	$query  = 'select pid, country, name, lid, experience, won, lost, ((experience/30)+won-lost) as ranking ';
	$query .= 'from player where country="'.$code.'" ';
	
	switch ($sort) {
		
			case 1:
				$query .= 'order by name asc ';
				break;
				
			case 2:
				$query .= 'order by lid desc, experience desc ';
				break;
					
			case 3:
				$query .= 'order by experience desc ';
				break;
				
			case 4:
				$query .= 'order by won desc ';
				break;
			
			case 5:
				$query .= 'order by lost desc ';
				break;
			
			default:	
			case 6:
				$query .= 'order by ranking desc ';
				break;	
	}
	
	$query .= 'limit '.$offset.','.$limit;
	$result = warquest_db_query($query);	
	
	$page .= '<div class="subparagraph">'.t('LEADERBORD_PLAYER_COUNTRY',warquest_landcode($uid)).'</div>';
	
	$page .= '<div class="box">';
	
	$page .= warquest_page_control($offset, $limit, $total, 1, '&sort='.$sort);
	
	$page .= '<table>';
	
	$page .= '<tr>';
	$page .= '<td width="35">';
	$page .= '<b>'.t('GENERAL_TOP').'</b>';
	$page .= '</td>';
	$page .= '<td width="160"><b>';
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&uid='.$uid.'&sort=1', t('GENERAL_PLAYER'));
	$page .= '</b></td>';
	$page .= '<td width="50"><b>';
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&uid='.$uid.'&sort=2', t('GENERAL_LEVEL'));
	$page .= '</b></td>';
	$page .= '<td width="90"><b>';
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&uid='.$uid.'&sort=3', t('GENERAL_EXP'));		
	$page .= '</b></td>';
	$page .= '<td width="50"><b>';
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&uid='.$uid.'&sort=4', t('GENERAL_WON'));	
	$page .= '</b></td>';
	$page .= '<td width="50"><b>';
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&uid='.$uid.'&sort=5', t('GENERAL_LOST'));
	$page .= '</b></td>';
	$page .= '<td width="60"><b>';
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&uid='.$uid.'&sort=6', t('GENERAL_RANKING'));
	$page .= '</b></td>';
	$page .= '</tr>';
	
	$count=$offset + 1;
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
		$page .= number_format($data->experience,0,",",".");
		
		$query = 'select approved from player_player where pid1='.$player->pid.' and pid2='.$data->pid;
		$result2 = warquest_db_query($query);	 
		$data2=warquest_db_fetch_object($result2);
		if ((isset($data2->approved)) || ($data->pid==$player->pid)) {
			$page .= ' '.warquest_image('other/ally.png',' width="14" height="12" title="'.t('ALLIANCE_ALLY').'"');
		}
	
		$page .= '</td>';
		$page .= '<td>';
		$page .= number_format($data->won,0,",",".");
		$page .= '</td>';
		$page .= '<td>';
		$page .= number_format($data->lost,0,",",".");
		$page .= '</td>';
		$page .= '<td>';
		$page .= number_format($data->ranking,0,",",".");
		$page .= '</td>';
		$page .= '</tr>';
	}

	$page .= '</table>';
	
	$page .= warquest_page_control($offset, $limit, $total, 0, '&sort='.$sort);
	
	$page .= '</div>';	
	
	$page .= '<div class="note">';
	$page .= t('LEADERBORD_PLAYER_COUNTRY_NOTE');
   $page .= '</div>';
}

/*
** ---------------------
** Leaderboard best countries
** ---------------------
*/

function warquest_leaderboard2_form() {

	/* input */
	global $offset;
	global $mid;
	global $sid;
			
	/* output */
	global $page;
	global $title;
	global $sort;
	
	$title = t('LEADERBORD_BEST_COUNTRY');
	
	/* Max records. */
	$limit = 50;
		
	$query  = 'select country from player where country!="EU" group by country ';
	$result = warquest_db_query($query);	 
	$total = warquest_db_num_rows($result);
	
	/* Get alliance players */
	$query  = 'select country, count(*) as total, sum(won) as won , sum(lost) as lost ';
	$query .= 'from player where country!="EU" group by country  ';
	
	switch ($sort) {
		
			case 1:
				$query .= 'order by country asc ';
				break;
				
			case 2:
				$query .= 'order by total desc ';
				break;

			default:
			case 3:
				$query .= 'order by won desc, country asc ';
				break;
				
			case 4:
				$query .= 'order by lost desc ';
				break;
	}
	$query .= 'limit '.$offset.','.$limit;
	$result = warquest_db_query($query);	  
	
	$page .= '<div class="subparagraph">'.t('LEADERBORD_BEST_COUNTRY').'</div>';
	
	$page .= '<div class="box">';
	
	$page .= warquest_page_control($offset, $limit, $total, 1, '&sort='.$sort);
	
	$page .= '<table>';
	
	$page .= '<tr>';	
	$page .= '<td width="35"><b>'.t('GENERAL_TOP').'</b></td>';
	
	$page .= '<td width="40"><b></b></td>';
	
	$page .= '<td width="240"><b>';
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&sort=1', t('GENERAL_COUNTRY'));
	$page .= '</b></td>';
	
	$page .= '<td width="70"><b>';
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&sort=2', t('GENERAL_PLAYERS'));
	$page .= '</b></td>';
	
	$page .= '<td width="80"><b>';
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&sort=3', t('GENERAL_WONS'));
	$page .= '</b></td>';
	
	$page .= '<td width="70"><b>';
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&sort=4', t('GENERAL_LOSTS'));
	$page .= '</b></td>';
	$page .= '</tr>';
	
	$count=$offset + 1;
	while ($data=warquest_db_fetch_object($result)) {
	
		$page .= '<tr>';
		$page .= '<td>';
		$page .= $count++;
		$page .= '</td>';
		$page .= '<td>';
		$page .= warquest_flag_image($data->country);
		$page .= '</td>';
		$page .= '<td>';
		$code = sprintf("%03d%03d",ord($data->country[0]),ord($data->country[1]));
		$page .= warquest_link('mid='.$mid.'&sid='.PAGE_BEST_COUNTRY2.'&uid='.$code, warquest_landcode($data->country) ,$data->country);
		$page .= '</td>';
		$page .= '<td>';
		$page .= number_format($data->total,0,",",".");;
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
	
	$page .= warquest_page_control($offset, $limit, $total, 0, '&sort='.$sort);
	
	$page .= '</div>';	
	
	$page .= '<div class="note">';
	$page .= t('LEADERBORD_BEST_COUNTRY_NOTE');
   $page .= '</div>';
}

/*
** ---------------------
** Leaderboard best player
** ---------------------
*/

function warquest_leaderboard1_form() {

	/* input */
	global $player;
	global $uid;
	global $mid;
	global $sid;
	global $offset;
	global $sort;
		
	/* output */
	global $page;
	global $title;
	
	$title = t('LEADERBORD_BEST_PLAYER');
		
	/* Max records. */
	$limit = 50;
	
	$query  = 'select pid from player where country!="EU" ';
	$result = warquest_db_query($query);	
	$total=warquest_db_num_rows($result);
	
	/* Get alliance players */
	$query  = 'select pid, country, name, lid, experience, won, lost, ((experience/30)+won-lost) as ranking ';
	$query .= 'from player where country!="EU" ';	
	
	switch ($sort) {
		
			case 1:
				$query .= 'order by name asc ';
				break;
				
			case 2:
				$query .= 'order by lid desc, experience desc ';
				break;
				
			case 3:
				$query .= 'order by experience desc ';
				break;
			
			case 4:
				$query .= 'order by won desc ';
				break;
			
			case 5:
				$query .= 'order by lost desc ';
				break;
			
			default:		
			case 6:
				$query .= 'order by ranking desc ';
				break;			
	}
	
	$query .= 'limit '.$offset.','.$limit;
	$result = warquest_db_query($query);	
	
	$page .= '<div class="subparagraph">'.t('LEADERBORD_BEST_PLAYER').'</div>';
	
	$page .= '<div class="box">';
	
	$page .= warquest_page_control($offset, $limit, $total, 1, '&sort='.$sort);
	
	$page .= '<table>';
	
	$page .= '<tr>';
	$page .= '<td width="35">';
	$page .= '<b>'.t('GENERAL_TOP').'</b>';
	$page .= '</td>';
	$page .= '<td width="160"><b>';
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&sort=1', t('GENERAL_PLAYER'));
	$page .= '</b></td>';
	$page .= '<td width="50"><b>';
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&sort=2', t('GENERAL_LEVEL'));
	$page .= '</b></td>';
	$page .= '<td width="90"><b>';
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&sort=3', t('GENERAL_EXP'));			
	$page .= '</b></td>';
	$page .= '<td width="50"><b>';
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&sort=4', t('GENERAL_WON'));	
	$page .= '</b></td>';
	$page .= '<td width="50"><b>';
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&sort=5', t('GENERAL_LOST'));
	$page .= '</b></td>';
	$page .= '<td width="60"><b>';
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&sort=6', t('GENERAL_RANKING'));
	$page .= '</b></td>';
	$page .= '</tr>';
	
	$count=$offset+1;
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
		$page .= number_format($data->experience,0,",",".");
		
		$query = 'select approved from player_player where pid1='.$player->pid.' and pid2='.$data->pid;
		$result2 = warquest_db_query($query);	 
		$data2=warquest_db_fetch_object($result2);
		if ((isset($data2->approved)) || ($data->pid==$player->pid)) {
			$page .= ' '.warquest_image('other/ally.png',' width="14" height="12" title="'.t('ALLIANCE_ALLY').'"');
		}
		
		$page .= '</td>';
		$page .= '<td>';
		$page .= number_format($data->won,0,",",".");
		$page .= '</td>';
		$page .= '<td>';
		$page .= number_format($data->lost,0,",",".");
		$page .= '</td>';
		$page .= '<td>';
		$page .= number_format($data->ranking,0,",",".");
		$page .= '</td>';
		$page .= '</tr>';
	}

	$page .= '</table>';
	
	$page .= warquest_page_control($offset, $limit, $total, 0, '&sort='.$sort);
	
	$page .= '</div>';	
	
	$page .= '<div class="note">';
	$page .= t('LEADERBORD_BEST_PLAYER_NOTE');
   $page .= '</div>';
}

?>