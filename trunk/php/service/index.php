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

include '../database.inc';
include '../config.inc';
include '../general.inc';

/* Connect to database */
warquest_db_connect($config["dbhost"], $config["dbuser"], $config["dbpass"], $config["dbname"]);
	
/**
 * Get Player data
 */ 
function getPlayer($id)
{
	global $config;
	
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
		
		$ns = 'http://127.0.0.1/service/warquest.wsdl';
		$sector = new SoapVar($data, SOAP_ENC_OBJECT, null, $ns, 'sector');

		$sectors->append($sector);
	
		$count++;
	}	
		
	warquest_info('webservice getSectors end [count='.$count.']');
			
	return $sectors;
}

ini_set('soap.wsdl_cache_enabled', '0');

$server = new SoapServer('warquest.wsdl');
$server->addFunction(array("getPlayer", "getClan", "getSectors"));
$server->handle();
 
warquest_db_close();

/*
** ---------------------------------------------------------------- 
** THE END
** ----------------------------------------------------------------
*/

?>