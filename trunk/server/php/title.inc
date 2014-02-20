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
** ------------
** TITLE
** ------------
*/

function warquest_create_title($title) {

	/* input */
	global $mid;
	global $sid;
	global $ssid;
	global $oid;
	global $uid;
	global $cid;
	global $player;
	global $config;
	
	$page  = '<table>';
	$page .= '<tr>';
	
	$page .= '<td width="250" align="left">';
	$page .= '<span class="paragraph">';
	$page .= warquest_planet_image($player->planet);
	$page .= $title;
	$page .= '</span>';	
	$page .= '</td>';
	
	$page .= '<td width="250" align="right">';
	$page .= t('HOME_TRAVEL_TO');
	
	for ($planet=PLANET_EARTH; $planet<=$config['max_planets']; $planet++) {
		
		$tmp = 'mid='.$mid;
		
		switch ($mid) {
			
				case MENU_MISSIONS:
 					$tmp .= '&sid='.warquest_get_default_mission($planet);					
					break;
					
				case MENU_UNITS:
					if ($sid==PAGE_LIBRARY) {
						$tmp .= '&sid='.$sid;
						
					} else {
					
						$query = 'select type from unit_group where ugid='.$sid;
						$result = warquest_db_query($query);
						$data = warquest_db_fetch_object($result);
						
						$query = 'select ugid from unit_group where type='.$data->type.' and planet='.$planet;
						$result = warquest_db_query($query);
						$data = warquest_db_fetch_object($result);
					
						$tmp .= '&sid='.$data->ugid;
					}
					break;
	
				case MENU_BUILDINGS:
					$query1 = 'select type from building_group where bgid='.$sid;
					$result1 = warquest_db_query($query1);
					$data1 = warquest_db_fetch_object($result1);
					
					$query2 = 'select bgid from building_group where type='.$data1->type.' and planet='.$planet;
					$result2 = warquest_db_query($query2);
					$data2 = warquest_db_fetch_object($result2);
					
					$tmp .= '&sid='.$data2->bgid;
					
					if ($data1->type==2) {
						$query3 = 'select ugid from unit_group where type=2 and planet='.$planet;
						$result3 = warquest_db_query($query3);
						$data3 = warquest_db_fetch_object($result3);
						
						$tmp .= '&ssid='.$data3->ugid;
					}
	
					break;
					
				case MENU_MONEY:				
					$tmp .= '&sid='.$sid.'&ssid='.$ssid;
					break;
					
				default: 
					$tmp .= '&sid='.$sid;
					break;
		}
		
		$tmp .= '&planet='.$planet.'&uid='.$uid.'&eid='.EVENT_SWITCH_PLANET.'&cid='.$cid;
		
		/* opponent is added only when needed */
		if ($oid!=$player->pid) {
			$tmp .= '&oid='.$oid;
		}
		
		$page .= warquest_link_hidden($tmp,  warquest_planet_image($planet), 'planet'.$planet);
	}
	$page .= '</td>';
	
	$page .= '</tr>';
	$page .= '</table>';

	return $page;
}

/*
** ------------
** TITLE
** ------------
*/

function warquest_ui_title() {

	/* input */
	global $mid;
	global $sid;
		
	$page = '<div class="travel">';
	
	switch ($mid) {
				
		case MENU_HOME:
				$page .= warquest_create_title( t('HOME_TITLE') );
				break;

		case MENU_MISSIONS:
				$page .= warquest_create_title( t('MISSION_TITLE') );
				break;

		case MENU_BATTLE:
				$page .= warquest_create_title( t('BATTLE_TITLE') );
				break;

		case MENU_UNITS:
				$page .= warquest_create_title( t('UNIT_TITLE') );
				break;

		case MENU_BUILDINGS:
				$page .= warquest_create_title( t('BUILDING_TITLE') );
				break;

		case MENU_MONEY:
				$page .= warquest_create_title( t('MONEY_TITLE') );
				break;

		case MENU_ALLIANCE:
				$page .= warquest_create_title( t('ALLIANCE_TITLE') );
				break;

		case MENU_FORUMS:			
				$page .= warquest_create_title( t('FORUM_TITLE') );
				break;
			
		case MENU_HELP:
				$page .= warquest_create_title( t('HELP_TITLE'));
				break;
				
		case MENU_ADMIN:
				$page .= warquest_create_title( "ADMIN" );
				break;	
	}
	
	$page .= '</div>';

	return $page;
}

/*
** ------------
** THE END
** ------------
*/

?>