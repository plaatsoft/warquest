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
$uid=0;

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
function getPlayer($id) {
	
	warquest_info('webservice getPlayer ['.$id.'] - start');
	
	$data = warquest_db_player($id);

	if ( isset($data->pid) ) {	

		/* Convert data */
		$data->money_date = warquest_xml_date($data->money_date);
		$data->energy_date = warquest_xml_date($data->energy_date);
		$data->health_date = warquest_xml_date($data->health_date);
		$data->ammo_date = warquest_xml_date($data->ammo_date);
		
		$data->last_battle = warquest_xml_date($data->last_battle);
		$data->bonus_date = warquest_xml_date($data->bonus_date);
		$data->request_date = warquest_xml_date($data->request_date);
		$data->restore_health = warquest_xml_date($data->restore_health);
		$data->restore_energy = warquest_xml_date($data->restore_energy);
		$data->restore_ammo = warquest_xml_date($data->restore_ammo);
		$data->cease_fire_date = warquest_xml_date($data->cease_fire_date);
		$data->holiday_date = warquest_xml_date($data->holiday_date);
		
		$data->planet = warquest_db_planet_name($data->planet);
		
		// Get buildings
		$buildings = new ArrayObject();	
		$query1 = 'select bid, amount from player_building where pid='.$id.' order by bid';	
		$result1 = warquest_db_query($query1);
	
		while ($data1 = warquest_db_fetch_object($result1)) {		
			
			$building = new SoapVar($data1, SOAP_ENC_OBJECT, null, null, 'building');				
			$buildings->append($building);
		}	
		$data->buildings = new SoapVar($buildings, SOAP_ENC_OBJECT, null, null, 'buildings');
		
		// Get units
		$units = new ArrayObject();	
		$query2 = 'select uid, amount from player_unit where pid='.$id.' order by uid';			
		$result2 = warquest_db_query($query2);
	
		while ($data2 = warquest_db_fetch_object($result2)) {		
			
			$unit = new SoapVar($data2, SOAP_ENC_OBJECT, null, null, 'unit');
			$units->append($unit);
		}	
		$data->units = new SoapVar($units, SOAP_ENC_OBJECT, null, null, 'units');
		
	} else {
	
		/* no data found */
		$data = array();	
	} 
	$data= new SoapVar($data, SOAP_ENC_OBJECT, null, null, 'player');
		
	warquest_info("getPlayer - end");
	
	return $data;
}

/**
 * Get Clan data
 */
function getClan($id) {

	warquest_info('getClan ['.$id.'] - start');
	
	$data = warquest_db_clan($id);
	
	if ( isset($data->cid) ) {		
	
		/* Convert data */
		$data->created = warquest_xml_date($data->created);
		$data->last_activity = warquest_xml_date($data->last_activity);
	
	} else {
	
		/* no data found */
		$data = array();	
	}
	
	$data = new SoapVar($data, SOAP_ENC_OBJECT, null, null, 'clan');

	warquest_info("getClan - end");
	
	return $data;
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
function doMission($username, $password) {

	include '../mission.inc';	

	/* input */
	global $player;
	global $skill;
	global $level;	
	global $output;
	global $uid;
	
	warquest_info('goMission ['.$username.'] - start');
	
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
	
	/* Get first mission which is not complete */
	/*$query  = "select a.mid, a.loot, a.min_price, a.max_price, a.energy, ";
	$query .= "a.experience, a.alliance, ifnull(b.progress, 0) as progress, ";
	$query .= "ifnull(b.part, 0) as part, ifnull(b.part2, 0) as part2 from mission a ";
	$query .= "left join player_mission b on a.mid=b.mid and b.pid=".$player->pid." ";
	$query .= 'where a.mgid='.$sid.' and a.lid<='.$player->lid.' ';  
	$query .= 'order by a.lid asc';
	
	$result = warquest_db_query($query);	 
	$data = warquest_db_fetch_object($result);	
	$uid = $data->mid;*/
	
	$uid=1;
	
	/* Do fight */
	warquest_mission_do();
	
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