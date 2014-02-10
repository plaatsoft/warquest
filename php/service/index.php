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
include '../general.inc';
include "../email.inc";

$player;
$skill;
$level;

$output = new stdClass();
$output->won=0;
$output->faultcode=0;
$output->faultstring="TEST";

/* Connect to database */
warquest_db_connect($config["dbhost"], $config["dbuser"], $config["dbpass"], $config["dbname"]);

function planetIntEnum($planet) {

	switch ($planet) {
	
		case 1: return "earth";
		case 2: return "moon";
		case 3: return "mars";
		case 4: return "mercure";
		case 5: return "neptune";
	}
}

/* Go Battle */
function getBattle($username, $password) {

	/* input */
	global $player;
	global $skill;
	global $level;
	
	global $output;
	
	include "../english.inc";
	include "../login.inc";	
	include "../browser.inc";
	include "../battle.inc";	
	
	$pid = warquest_login_do($username, $password);
	
	/* Load player data from database */
	$player = warquest_db_player($pid);
	$skill = warquest_db_skill($player->pid);
	$level = warquest_db_level($player->lid);

	/* Update player timers (before) */
	warquest_update_timers($player);
		
	/* Do fight */
	warquest_battle_enemy_ws_do();
	
	echo "output.won=[".$output->won.']<br/>';
	echo "output.faultcode=[".$output->faultcode.']</br>';
	echo "output.faultstring=[".$output->faultstring.']<br/>';
}

/**
 * Get Player data
 */ 
function getPlayer($id) {
	
	warquest_info('webservice getPlayer ['.$id.'] start');
	
	$data = warquest_db_player($id);

	if ( isset($data->pid) ) {	

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
		
		$data->planet = planetIntEnum($data->planet);
		
		// Get buildings
		$buildings = new ArrayObject();	
		$query1 = 'select bid, amount from player_building where pid='.$id.' order by bid';	
		$result1 = warquest_db_query($query1);
	
		while ($data1 = warquest_db_fetch_object($result1)) {		
			
			$building = new SoapVar($data1, SOAP_ENC_OBJECT, null, null, 'building');

			$buildings->append($building);
		}	
		$data->buildings = $buildings;
		
		// Get units
		$units = new ArrayObject();	
		$query2 = 'select uid, amount from player_unit where pid='.$id.' order by uid';			
		$result2 = warquest_db_query($query2);
	
		while ($data2 = warquest_db_fetch_object($result2)) {		
			
			$unit = new SoapVar($data2, SOAP_ENC_OBJECT, null, null, 'unit');

			$units->append($unit);
		}	
		$data->units = $units;
		
	} else {
	
		$data = array();	
	} 
		
	warquest_info("webservice getPlayer end");
	
	return $data;
}

/**
 * Get Clan data
 */
function getClan($id) {

	warquest_info('webservice getClan ['.$id.'] start');
	
	$data = warquest_db_clan($id);
	
	if ( isset($data->cid) ) {		
	
		$data->created = warquest_xml_date($data->created);
		$data->last_activity = warquest_xml_date($data->last_activity);
	
	} else {
	
		$data = array();	
	}
	
	warquest_info("webservice getClan end");
	
	return $data;
}

/**
 * Get Sectors data
 */
function getSectors($id) {

	warquest_info('webservice getSectors ['.$id.'] start');
	
	$query  = 'select sid, x, y, cid, damage, planet, conquer_date, cid from sector where planet='.$id.' order by sid';	
	$result = warquest_db_query($query);
		
	$count=0;
	
	$sectors = new ArrayObject();
	 
	while ($data = warquest_db_fetch_object($result)) {		
		
		$data->conquer_date = warquest_xml_date($data->conquer_date);	

		$sector = new SoapVar($data, SOAP_ENC_OBJECT, null, null, 'sector');

		$sectors->append($sector);
	
		$count++;
	}	
		
	warquest_info('webservice getSectors end [count='.$count.']');
			
	return $sectors;
}

ini_set('soap.wsdl_cache_enabled', '0');

$server = new SoapServer('warquest.wsdl');
$server->addFunction(array("getPlayer", "getClan", "getSectors", "goBattle"));
$server->handle();

warquest_db_close();

/*
** ---------------------------------------------------------------- 
** THE END
** ----------------------------------------------------------------
*/

?>