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
** ---------
** Post  
** ---------
*/

$eid = warquest_post('eid', 0);
$planet = warquest_post('planet', 1);
$cid = warquest_post('cid', 0);

/*
** ---------
** ACTIONS
** ---------
*/

/**
 * Proces get sector data
 */
function warquest_get_sector_data() {

	global $planet;
	
	$query  = 'select a.x, a.y, a.cid, a.damage, ';
	$query .= '(select b.name from clan b where b.cid=a.cid ) as name ';
	$query .= 'from sector a where a.planet='.$planet;	
	
	$result = warquest_db_query($query);
		
	$cell = array();
		
	while ($data = warquest_db_fetch_object($result)) {		
		
		if (isset($data->name)) {
		
			$cell[] = array(
				'x' 		=> $data->x,
				'y' 		=> $data->y,
				'cid' 	=> $data->cid,
				'damage' => $data->damage,
				'name' 	=> $data->name );
		} 
	}	
	
	return json_encode($cell);
}

/**
 * Proces get clan data 
 */
function warquest_get_clan_data() {

	global $cid;
	
	$data = warquest_db_clan($cid);
		
	return json_encode($data);
}

/*
** ---------
** HANDLER
** ---------
*/


function warquest_service() {

	global $eid;
	
	/* Update request counter */
	warquest_db_player_login_counter(1);
	
	/* Event handler */
	switch ($eid) {
		
		case 1: 	
			echo warquest_get_sector_data();
			break;
			
		case 2: 	
			echo warquest_get_clan_data();
			break;
	}
}

/*
** ---------
** THE END
** ---------
*/

?>