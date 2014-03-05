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

include '../config.inc';
include '../constants.inc';
include '../database.inc';
include '../english.inc';
include '../general.inc';
include '../login.inc';	
include '../browser.inc';
	
$player;
$other;
$skill;
$level;

$mid=0;
$sid=0;
$id=0;

$output = new stdClass();
$output->format = "xml";	/* Format (html, xml or pdf) */
$output->result = false; 	/* Action result (true / false) */
$output->title = "";			/* Title content */
$output->popup = "";			/* Popup content */

/*
** ---------
** Actions
** ---------
*/

/**
 * Get Player data
 */ 
function getPlayer($name) {
		
	warquest_info('webservice getPlayer ['.$name.'] - start');
		
	$query1  = 'select pid from player where name like "'.$name.'"';	
	$result1 = warquest_db_query($query1);
	$data1 = warquest_db_fetch_object($result1);
	
	$data2 = array();	
	
	if ( isset($data1->pid) ) {	

		$data2 = warquest_db_player($data1->pid);
	
		/* Convert dates / enums */
		$data2->money_date = warquest_xml_date($data2->money_date);
		$data2->energy_date = warquest_xml_date($data2->energy_date);
		$data2->health_date = warquest_xml_date($data2->health_date);
		$data2->ammo_date = warquest_xml_date($data2->ammo_date);			
		$data2->last_battle = warquest_xml_date($data2->last_battle);
		$data2->bonus_date = warquest_xml_date($data2->bonus_date);
		$data2->request_date = warquest_xml_date($data2->request_date);
		$data2->restore_health = warquest_xml_date($data2->restore_health);
		$data2->restore_energy = warquest_xml_date($data2->restore_energy);
		$data2->restore_ammo = warquest_xml_date($data2->restore_ammo);
		$data2->cease_fire_date = warquest_xml_date($data2->cease_fire_date);
		$data2->holiday_date = warquest_xml_date($data2->holiday_date);
		$data2->premium_date = warquest_xml_date($data2->premium_date);
			
		$data2->planet = warquest_db_planet_name($data2->planet);
		
		// Get buildings
		$buildings = new ArrayObject();	
		$query3 = 'select bid, amount from player_building where pid='.$data1->pid.' order by bid';	
		$result3 = warquest_db_query($query3);
		
		while ($data3 = warquest_db_fetch_object($result3)) {		
				
			$building = new SoapVar($data3, SOAP_ENC_OBJECT, null, null, 'building');				
			$buildings->append($building);
		}	
		$data2->buildings = new SoapVar($buildings, SOAP_ENC_OBJECT, null, null, 'buildings');
		
		// Get units
		$units = new ArrayObject();	
		$query4 = 'select uid, amount from player_unit where pid='.$data1->pid.' order by uid';			
		$result4 = warquest_db_query($query4);
	
		while ($data4 = warquest_db_fetch_object($result4)) {		
			
			$unit = new SoapVar($data4, SOAP_ENC_OBJECT, null, null, 'unit');
			$units->append($unit);
		}	
		$data2->units = new SoapVar($units, SOAP_ENC_OBJECT, null, null, 'units');			
	} 
	
	$data2 = new SoapVar($data2, SOAP_ENC_OBJECT, null, null, 'player');
		
	warquest_info("getPlayer - end");
	
	return $data2;
}

/**
 * Get Clan data
 */
function getClan($name) {

	warquest_info('getClan ['.$name.'] - start');
				
	$query1  = 'select cid from clan where name like "'.$name.'"';	
	$result1 = warquest_db_query($query1);
	$data1 = warquest_db_fetch_object($result1);
	
	$data2 = array();
	
	if ( isset($data1->cid) ) {		
	
		$data2 = warquest_db_clan($data1->cid);
		
		/* Convert data */
		$data2->created = warquest_xml_date($data2->created);
		$data2->last_activity = warquest_xml_date($data2->last_activity);	
	}
	
	$data2 = new SoapVar($data2, SOAP_ENC_OBJECT, null, null, 'clan');

	warquest_info("getClan - end");
	
	return $data2;
}

/**
 * Get planet data
 */
function getPlanet($planet) {

	global $ns;
	
	warquest_info('getPlanet ['.$planet.'] - start');
	
	/* Validate input */
	$planet_id = warquest_db_planet_id($planet);
	if ($planet_id==0) {
		return new SoapFault("Server", "Invalid planet enumeration value");
	}
	
	/* Fetch data */
	$query  = 'select sid, x, y, cid, damage, conquer_date, cid from sector where planet='.$planet_id.' order by sid';	
	$result = warquest_db_query($query);
			
	$sectors = new ArrayObject();
	 
	while ($data = warquest_db_fetch_object($result)) {		
		
		/* Convert data */
		$data->conquer_date = warquest_xml_date($data->conquer_date);	

		$sector = new SoapVar($data, SOAP_ENC_OBJECT, null, null, 'sector');
		$sectors->append($sector);
	}	
	
	$sectors = new SoapVar($sectors, SOAP_ENC_OBJECT, null, null, 'sectors');
	
	warquest_info('getPlanet - end');
			
	return $sectors;
}


/* Do Battle */
function doBattle($username, $password, $planet, $force) {

	include '../battle.inc';	

	/* input */
	global $player;
	global $other;
	global $skill;
	global $level;
	
	global $output;
	
	warquest_info('goBattle ['.$username.'|'.$planet.'|'.$force.'] - start');
	
	/* Validate input */
	$planet_id = warquest_db_planet_id($planet);
	if ($planet_id==0) {
		return new SoapFault("Server", "Invalid planet enumeration value");
	}
	
	$ugid = warquest_db_unit_group_id($force, $planet_id);
	if ($ugid==0) {
		return new SoapFault("Server", "Invalid force enumeration value");
	}
	
	/* Authenicate player */
	$pid = warquest_login_do($username, $password);
	if ($pid==0) {
		return new SoapFault("Server", "Authenication failed!");
	} 
	
	/* Load player data from database */
	$player = warquest_db_player($pid);
	$skill = warquest_db_skill($player->pid);
	$level = warquest_db_level($player->lid);

	/* Update player timers (before) */
	warquest_update_timers($player);
	
	/* Select enemy */	
	$query  = 'select a.pid, a.lid, a.won, a.lost, a.name, a.experience, a.alliance, a.country, ';
	$query .= 'a.health, a.health_date, a.health_step, ifnull(b.approved, 0) as approved, ';
	$query .= '(select ifnull(id ,0) from bounty where pid1=a.pid and pid2='.$player->pid.') as bounty ';
	$query .= 'from player a left join player_player b ';
	$query .= 'on b.pid2=a.pid and b.pid1='.$player->pid.' where a.pid!='.$player->pid.' ';	
	$query .= 'and a.lid>='.warquest_get_min_attack_level().' ';
	$query .= 'and a.lid<='.warquest_get_max_attack_level().' ';
	$query .= 'and a.cease_fire_date < "'.date("Y-m-d H:i:s", time()).'" ';
	$query .= 'and a.holiday_date < "'.date("Y-m-d H:i:s", time()).'" ';
	$query .= 'and ifnull(b.approved, 0)=0 '; 
	$query .= 'order by a.last_battle asc limit 0, 1'; 

	$result = warquest_db_query($query);	 
	$data = warquest_db_fetch_object($result);	
		
	if ($data->pid!=0) {

		/* Load other player data from database */
		$other=warquest_db_player($data->pid);
	
		/* Update other player timers (before) */
		warquest_update_timers($other);	
	}

	/* Do fight */
	warquest_battle_do($planet_id, $ugid);
	
	/* Update player timers (after) */
	warquest_update_timers($player);

	/* Update statistics counters */
	$player->request_date=date("Y-m-d H:i:s", time());
	$player->request+=1;
		
	/* Save player data */
	warquest_db_player_update($player);

	/* Convert data */
	$output->popup = strip_tags($output->popup);
		
	warquest_info($output->popup);
	
	/* Remove unwanted parts in the output */
	unset($output->format);
	unset($output->title);
	
	$output = new SoapVar($output, SOAP_ENC_OBJECT, null, null, 'battle');
	
	warquest_info('goBattle - end');
		
	return $output;
}

/* Do Mission */
function doMission($username, $password, $buy, $clan) {

	include '../mission.inc';	

	/* input */
	global $player;
	global $skill;
	global $level;	
	global $output;
	global $id;
	
	warquest_info('goMission ['.$username.'|'.$buy.'|'.$clan.'] - start');
	
	/* Authenicate player */
	$pid = warquest_login_do($username, $password);
	if ($pid==0) {
		return new SoapFault("Server", "Authenication failed!");
	} 
	
	/* Load player data from database */
	$player = warquest_db_player($pid);
	$skill = warquest_db_skill($player->pid);
	$level = warquest_db_level($player->lid);
	$player_clan = warquest_db_player_clan($player->pid);

	/* Update player timers (before) */
	warquest_update_timers($player);
	
	$id = 1;
	
	if ($clan==0) {
		 
		/* Get player mission */
		
		/* Get random mission which is not complete yet */
		$query  = 'select mid from mission where mid NOT in ';
		$query .= '(select mid from player_mission where pid='.$player->pid.' and '; 
		$query .= '((part=0 and progress=100) or (part=1 and progress=200) or ';
		$query .= '(part=2 and progress=300) or progress=(part*100)) ) ';
		$query .= 'and lid<'.$player->lid.' order by mid asc limit 0, 1';
		
		$result = warquest_db_query($query);	 
		$data = warquest_db_fetch_object($result);	
		
		if ( isset($data->mid) ) {
			$id = $data->mid;
			
		} else {	
	
			/* All player missions 100% ready, just select one */
			$query  = 'select mid from mission where lid<'.$player->lid.' order by rand() limit 0, 1';
			
			$result = warquest_db_query($query);	 
			$data = warquest_db_fetch_object($result);	
			
			if ( isset($data->mid) ) {
				$id = $data->mid;
			}
		}
		
	} else {
	
		/* Get first clan mission with is not ready */		
		
		if (isset($player_clan->cid)) {
			
			$query  = 'select mid from mission where mid NOT in ';
			$query .= '(select mid from clan_mission where progress=100 and cid='.$player_clan->cid.') ';
			$query .= 'and lid<'.$player->lid.' and mid!=0 order by mid asc limit 0, 1';
		
			$result = warquest_db_query($query);	 
			$data = warquest_db_fetch_object($result);	
			
			if ( isset($data->mid) ) {
				$id = $data->mid;
			}	
		}
	}
	
	
	/* Buy missing units, if needed */
	if ($buy==1) {
		warquest_buy_missing_units_do();
	}
	
	if ($clan==0) {
	
		/* Do player mission */
		warquest_mission_do();
		
	} else {
		
		/* Do clan mission */
		warquest_mission_clan_do();
	}
	
	/* Update player timers (after) */
	warquest_update_timers($player);

	/* Update statistics counters */
	$player->request_date=date("Y-m-d H:i:s", time());
	$player->request+=1;
		
	/* Save player data */
	warquest_db_player_update($player);

	/* Convert data */
	$output->popup = strip_tags($output->popup);
		
	warquest_info($output->popup);
	
	/* Remove unwanted parts in the output */
	unset($output->format);
	unset($output->title);
	
	$output = new SoapVar($output, SOAP_ENC_OBJECT, null, null, 'mission');
	
	warquest_info('goBattle - end');
		
	return $output;
}

/*
** ---------
** Handler
** ---------
*/

warquest_info("-----------------------");
warquest_info("webservice - start");

/* Create database connection */
warquest_db_connect($config["dbhost"], $config["dbuser"], $config["dbpass"], $config["dbname"]);

/* Added statitics event */
$mid = MENU_WEB_SERVICE;
warquest_db_view_add();

/* Create Soap Server */
ini_set('soap.wsdl_cache_enabled', '0');
$server = new SoapServer('warquest.wsdl');
$server->addFunction(array("getPlayer", "getClan", "getPlanet", "doBattle", "doMission"));

/* Process Soap Call */
$server->handle();

/* Close database connection */
warquest_db_close();

warquest_info("webservice - end");

/*
** ---------------------------------------------------------------- 
** THE END
** ----------------------------------------------------------------
*/

?>