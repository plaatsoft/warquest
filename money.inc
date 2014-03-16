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
** -------------
** HANDLER
** -------------
*/

function warquest_money() {

	/* input */
	global $sid;
	global $eid;
	
	/* Event handler */
	switch ($eid) {
			
		case EVENT_SWITCH_PLANET: 
			warquest_switch_planet_do();
			break;
	}	
	
	switch ($sid) {

		case PAGE_BANK: 	
					warquest_bank();
					break;
					
		case PAGE_STOCK_EXCHANGE:  
					warquest_stock();
					break;
					
		case PAGE_CASINO:
					warquest_casino();
					break;
	}
	warquest_player();	
}

/*
** --------
** THE END
** --------
*/

?>

