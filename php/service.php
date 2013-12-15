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

/* Include php classes */
include 'config.inc';
include 'constants.inc';
include 'database.inc';
include 'general.inc';

warquest_db_connect($config["dbhost"], $config["dbuser"], $config["dbpass"], $config["dbname"]);

/*
** ---------
** Post  
** ---------
*/

$planet = warquest_get('planet', 1);
$eid = warquest_get('eid', 0);

/*
** ---------
** ACTIONS
** ---------
*/

function warquest_get_map_data() {

	global $planet;
	
	$query  = 'select a.x, a.y, a.cid, a.damage, ';
	$query .= '(select b.name from clan b where b.cid=a.cid ) as name ';
	$query .= 'from sector a where a.planet='.$planet;	
	$result = warquest_db_query($query);
		
	$cell = array();
		
	/* Calculate cells with can be attack by clan */
	$count=0;
	while ($data = warquest_db_fetch_object($result)) {		
		
		if (isset($data->name)) {
			$cell[$count]['x'] = $data->x;
			$cell[$count]['y'] = $data->y;
			$cell[$count]['damage'] = $data->damage;
			$cell[$count]['name'] = $data->name;
			$count++;
		} 
	}	
	
	echo json_encode($cell);
}

/*
** ---------
** HANDLER
** ---------
*/
	
/* Event handler */
switch ($eid) {
	
	case 1: 	
			warquest_get_map_data();
			break;
			
	default: 
			echo "error";
			break;
}

/*
** ---------
** THE END
** ---------
*/

?>