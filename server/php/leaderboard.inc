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
** ---------------------------------------------------------------- 
** LEADERBORDS
** ---------------------------------------------------------------- 
*/

/*
** -------------------------------
** Leaderboard best clan
** -------------------------------
*/

function warquest_best_clan_form() {

	/* input */	
	global $mid;
	global $sid;
	global $ssid;
	global $sort;
	global $offset;
			
	/* output */
	global $page;
	global $output;
	
	$limit = 15;
	
	$output->title = t('LEADERBOARD_CLAN');
	
	$page .= '<div class="subparagraph">';
	$page .= $output->title;
	$page .= '</div>';
	
	$query  = 'select cid from clan';
	$result = warquest_db_query($query);	
	$total = warquest_db_num_rows($result);
	
	$query  = 'select a.cid, a.name, a.created, a.won, a.lost, a.mission, a.logo, ';
	$query .= '(select count(*) from player_clan where approved=1 and cid=a.cid) as size ';
	$query .= 'from clan a ';
	
	switch ($sort) {
		
		default:
		case 1:
			$query .= 'order by a.won desc ';
			break;
				
		case 2:
			$query .= 'order by a.lost desc ';
			break;
			
		case 3:
			$query .= 'order by a.mission desc ';
			break;
				
		case 4:
			$query .= 'order by size desc ';
			break;
	}
	$query .= 'limit '.$offset.','.$limit;
	
		
	$result = warquest_db_query($query);	 	
	$size = warquest_db_num_rows($result);
	
	if ($size == 0) {
	
		$message = t('CLAN_NO_CLANS');
		$page .= warquest_box_icon('info', $message);
	
	} else {		
	
		$page .= '<div class="box rows">';
	
		$page .= warquest_page_control($offset, $limit, $total, 1, '&sort='.$sort);
	
		$page .= '<table>';
		
		$page .= '<tr>';
						
		$page .= '<th width="35">';
		$page .= t('GENERAL_TOP');
		$page .= '</th>';
						
		$page .= '<th width="200">';
		$page .= t('GENERAL_NAME');
		$page .= '</th>';
				
		$page .= '<th width="80">';
		$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&ssid='.$ssid.'&sort=1', t('GENERAL_WON'));
		$page .= '</th>';

		$page .= '<th width="80">';
		$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&ssid='.$ssid.'&sort=2', t('GENERAL_LOST'));
		$page .= '</th>';		
				
		$page .= '<th width="80">';
		$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&ssid='.$ssid.'&sort=3', t('GENERAL_MISSIONS'));
		$page .= '</th>';
		
		$page .= '<th width="80">';
		$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&ssid='.$ssid.'&sort=4', t('GENERAL_SIZE'));
		$page .= '</th>';
				
		$page .= '</tr>';
		
		$count=$offset;
		while ($data = warquest_db_fetch_object($result)) {
		
			$count++;
			
			$page .= '<tr>';

			$page .= '<td>';
			$page .= $count;
			$page .= '</td>';
			
			$page .= '<td>';
			$page .= warquest_clan_image($data->logo).' ';
			$page .= warquest_link('mid='.$mid.'&sid='.PAGE_CLAN_PROFILE.'&cid='.$data->cid, $data->name);
			$page .= '</td>';
								
			$page .= '<td>';
			$page .= number_format($data->won,0,",",".");
			$page .= '</td>';
			
			$page .= '<td>';
			$page .= number_format($data->lost,0,",",".");
			$page .= '</td>';
									
			$page .= '<td>';
			$page .= number_format($data->mission,0,",",".");
			$page .= '</td>';
			
			$page .= '<td>';
			$page .= number_format($data->size,0,",",".");
			$page .= '</td>';
			
			$page .= '</tr>';
		}
		
		$page .= '</table>';		
		
		$page .= warquest_page_control($offset, $limit, $total, 0, '&sort='.$sort);
		
		$page .= '</div>';		
	} 
		
	$page .= '<div class="note">';
	$page .= t('LEADERBOARD_CLAN_NOTE');
   $page .= '</div>';	
}

/*
** -------------------------------
** Leaderboard best player country
** -------------------------------
*/

function warquest_best_player_country_form() {

	/* input */
	global $mid;
	global $sid;
	global $ssid;
	
	global $uid;
		
	global $player;
	global $offset;
	global $sort;
		
	/* output */
	global $page;
	global $output;
	
	sscanf($uid, "%03d%03d", $code[0], $code[1]);
	$code = chr($code[0]).chr($code[1]);
	
	$output->title = t('LEADERBORD_PLAYER_COUNTRY',warquest_landcode($code));
	
	$limit = 25;

	$query  = 'select pid from player where country="'.$code.'"';
	$result = warquest_db_query($query);	
	$total=warquest_db_num_rows($result);
	
	/* Get alliance players */
	$query  = 'select pid, country, name, lid, experience, won, lost ';
	$query .= 'from player where country="'.$code.'" ';
	
	switch ($sort) {
		
			case 1:
				$query .= 'order by lid desc, experience desc ';
				break;
			
			default:
			case 2:
				$query .= 'order by experience desc ';
				break;
				
			case 3:
				$query .= 'order by won desc ';
				break;
			
			case 4:
				$query .= 'order by lost desc ';
				break;
	}
	
	$query .= 'limit '.$offset.','.$limit;
	$result = warquest_db_query($query);	
	
	$page .= '<div class="subparagraph">'.t('LEADERBORD_PLAYER_COUNTRY',warquest_landcode($code)).'</div>';
	
	$page .= '<div class="box rows">';
	
	$page .= warquest_page_control($offset, $limit, $total, 1, '&sort='.$sort);
	
	$page .= '<table>';
	
	$page .= '<tr>';
	
	$page .= '<th width="35">';
	$page .= t('GENERAL_TOP');
	$page .= '</th>';
	
	$page .= '<th width="160">';
	$page .= t('GENERAL_PLAYER');
	$page .= '</th>';
	
	$page .= '<th width="50">';
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&ssid='.$ssid.'&sort=1', t('GENERAL_LEVEL'));
	$page .= '</th>';
	
	$page .= '<th width="110">';
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&ssid='.$ssid.'&sort=2', t('GENERAL_EXP'));			
	$page .= '</th>';
	
	$page .= '<th width="70">';
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&ssid='.$ssid.'&sort=3', t('GENERAL_WON'));	
	$page .= '</th>';
	
	$page .= '<th width="70">';
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&ssid='.$ssid.'&sort=4', t('GENERAL_LOST'));
	$page .= '</th>';
	
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
** -------------------------
** Leaderboard best country
** -------------------------
*/

function warquest_best_country_form() {

	/* input */	
	global $mid;
	global $sid;
	global $ssid;

	global $offset;
	
	/* output */
	global $page;
	global $output;
	global $sort;
	
	$output->title = t('LEADERBORD_BEST_COUNTRY');
	
	/* Max records. */
	$limit = 25;
		
	$query  = 'select country from player where country!="EU" group by country ';
	$result = warquest_db_query($query);	 
	$total = warquest_db_num_rows($result);
	
	/* Get alliance players */
	$query  = 'select country, count(*) as total, sum(won) as won , sum(lost) as lost ';
	$query .= 'from player where country!="EU" group by country  ';
	
	switch ($sort) {
					
			case 1:
				$query .= 'order by total desc ';
				break;

			default:
			case 2:
				$query .= 'order by won desc, country asc ';
				break;
				
			case 3:
				$query .= 'order by lost desc ';
				break;
	}
	$query .= 'limit '.$offset.','.$limit;
	$result = warquest_db_query($query);	  
	
	$page .= '<div class="subparagraph">'.t('LEADERBORD_BEST_COUNTRY').'</div>';
	
	$page .= '<div class="box rows">';
	
	$page .= warquest_page_control($offset, $limit, $total, 1, '&sort='.$sort);
	
	$page .= '<table>';
	
	$page .= '<tr>';	
	
	$page .= '<th width="35">';
	$page .= t('GENERAL_TOP');
	$page .= '</th>';
		
	$page .= '<th width="240">';
	$page .= t('GENERAL_COUNTRY');
	$page .= '</th>';
	
	$page .= '<th width="70">';
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&ssid='.$ssid.'&sort=1', t('GENERAL_PLAYERS'));
	$page .= '</th>';
	
	$page .= '<th width="80">';
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&ssid='.$ssid.'&sort=2', t('GENERAL_WONS'));
	$page .= '</th>';
	
	$page .= '<th width="70">';
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&ssid='.$ssid.'&sort=3', t('GENERAL_LOSTS'));
	$page .= '</th>';
	$page .= '</tr>';
	
	$count=$offset + 1;
	while ($data=warquest_db_fetch_object($result)) {
	
		$page .= '<tr>';
		
		$page .= '<td>';
		$page .= $count++;
		$page .= '</td>';
		
		$page .= '<td>';
		$page .= warquest_flag_image($data->country).' ';
		$code = sprintf("%03d%03d",ord($data->country[0]),ord($data->country[1]));
		$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&ssid='.PAGE_BEST_COUNTRY2.'&uid='.$code, warquest_landcode($data->country) ,$data->country);
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
** -----------------------
** Leaderboard best player
** -----------------------
*/

function warquest_best_player_form() {

	/* input */
	global $mid;
	global $sid;
	global $ssid;
	global $uid;
	
	global $player;
	global $offset;
	global $sort;
		
	/* output */
	global $page;
	global $output;
	
	$output->title = t('LEADERBORD_BEST_PLAYER');
		
	/* Max records. */
	$limit = 25;
	
	$query  = 'select pid from player where country!="EU" ';
	$result = warquest_db_query($query);	
	$total=warquest_db_num_rows($result);
	
	/* Get alliance players */
	$query  = 'select pid, country, name, lid, experience, won, lost ';
	$query .= 'from player where country!="EU" ';	
	
	switch ($sort) {
						
			case 1:
				$query .= 'order by lid desc, experience desc ';
				break;
			
			default:
			case 2:
				$query .= 'order by experience desc ';
				break;
			
			case 3:
				$query .= 'order by won desc ';
				break;
			
			case 4:
				$query .= 'order by lost desc ';
				break;
	}
	
	$query .= 'limit '.$offset.','.$limit;
	$result = warquest_db_query($query);	
	
	$page .= '<div class="subparagraph">'.t('LEADERBORD_BEST_PLAYER').'</div>';
	
	$page .= '<div class="box rows">';
	
	$page .= warquest_page_control($offset, $limit, $total, 1, '&sort='.$sort);
	
	$page .= '<table>';
	
	$page .= '<tr>';
	
	$page .= '<th width="35">';
	$page .= t('GENERAL_TOP');
	$page .= '</th>';
	
	$page .= '<th width="160">';
	$page .= t('GENERAL_PLAYER');
	$page .= '</th>';
	
	$page .= '<th width="50">';
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&ssid='.$ssid.'&sort=1', t('GENERAL_LEVEL'));
	$page .= '</th>';
	
	$page .= '<th width="110">';
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&ssid='.$ssid.'&sort=2', t('GENERAL_EXP'));			
	$page .= '</th>';
	
	$page .= '<th width="70">';
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&ssid='.$ssid.'&sort=3', t('GENERAL_WON'));	
	$page .= '</th>';
	
	$page .= '<th width="70">';
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&ssid='.$ssid.'&sort=4', t('GENERAL_LOST'));
	$page .= '</th>';
	
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

		$page .= '</tr>';
	}

	$page .= '</table>';
	
	$page .= warquest_page_control($offset, $limit, $total, 0, '&sort='.$sort);
	
	$page .= '</div>';	
	
	$page .= '<div class="note">';
	$page .= t('LEADERBORD_BEST_PLAYER_NOTE');
   $page .= '</div>';
}

/*
** ---------------------
** Handlers
** ---------------------
*/

function warquest_leaderboard() {

	/* input */
	global $ssid;

	/* output */
	global $page;
			
	/* Page handler */
	switch ($ssid) {

		case PAGE_BEST_PLAYER:
					warquest_best_player_form();
					break;
				  
		case PAGE_BEST_COUNTRY: 
					warquest_best_country_form();
					break;
				  		  				  
		case PAGE_BEST_COUNTRY2: 
					warquest_best_player_country_form();
					break; 
					
		case PAGE_BEST_CLAN: 
					warquest_best_clan_form();
					break; 
	}				  
}

/*
** ---------------------------------------------------------------- 
** THE END
** ----------------------------------------------------------------
*/
