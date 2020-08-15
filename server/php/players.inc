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
** -------------
** HANDLER
** -------------
*/

function warquest_players() {

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

		case PAGE_ALLIANCE:
					warquest_alliance();
					break;

		case PAGE_CLAN:
		case PAGE_CLAN_PROFILE:
		case PAGE_CLAN_SETTINGS:
					warquest_clan();
					break;

		case PAGE_PROMOTION:
					warquest_promotion();
					break;

		case PAGE_LEADERBOARD:
					warquest_leaderboard();
					break;
	}

	warquest_player();
}
