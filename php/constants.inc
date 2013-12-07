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
** ------------------
** PLANETS
** ------------------
*/

define('PLANET_EARTH',        0);
define('PLANET_MOON',         1);
define('PLANET_MARS',         2);
define('PLANET_ASTEROID',     3);
define('PLANET_SUN',     		4);

/*
** ------------------
** MENUS
** ------------------
*/

/* Main menu */
define('MENU_LOGIN',          1000);
define('MENU_HOME',           1001);
define('MENU_MISSIONS',       1002);
define('MENU_BATTLE',         1003);
define('MENU_UNITS',          1004);
define('MENU_BUILDINGS',      1005);
define('MENU_MONEY',          1006);
define('MENU_ALLIANCE',       1007);
define('MENU_FORUMS',         1008);
define('MENU_HELP',           1009);
define('MENU_ADMIN',          1010);

/*
** ------------------
** PAGES
** ------------------
*/

/* Login */
define('PAGE_LOGIN',          1101);
define('PAGE_REGISTER',       1102);
define('PAGE_RECOVER',        1103);
define('PAGE_FACEBOOK',       1104);
define('PAGE_MAINTENANCE',    1105);

/* Home */
define('PAGE_OVERVIEW',       1200);
define('PAGE_BATTLE_NEWS',    1201);
define('PAGE_MESSAGES',       1202);
define('PAGE_SKILLS',         1203);
define('PAGE_TRADE',          1204);
define('PAGE_RESTORE',        1205);
define('PAGE_SETTINGS',       1206);

/* Missions */
define('PAGE_MISSION_TRAINING',  0);

/* Battle */
define('PAGE_ENEMIES',        1301);
define('PAGE_BOUNTY',         1302);
define('PAGE_CLAN_WAR',       1303);

/* Units */
define('PAGE_UNITS',          1401);
define('PAGE_LIBRARY',        1402);

/* Buildings */
define('PAGE_BUILDINGS',      1501);

/* Money */
define('PAGE_BANK',           1601);
define('PAGE_STOCK_EXCHANGE', 1602);
define('PAGE_CASINO',         1603);
define('PAGE_GOLD',           1604);

/* Alliance */
define('PAGE_PENDING',        1701);
define('PAGE_INVITE',         1702);
define('PAGE_ACCEPTED',       1703);
define('PAGE_BEST_PLAYER',    1704);
define('PAGE_BEST_COUNTRY',   1705);
define('PAGE_BEST_COUNTRY2',  1706);
define('PAGE_CLAN',           1707); 
define('PAGE_CLAN_LIST',      1708);

/* Forums */
define('PAGE_FORUM',          1801);
define('PAGE_TOPIC',          1802);
define('PAGE_COMMENT',        1803);
define('PAGE_POLL',           1804);
define('PAGE_POLL_RESULT',    1805);
define('PAGE_CHATROOM',       1806);
define('PAGE_CHAT',           1807);
		
/* Help */
define('PAGE_INSTRUCTIONS',   1901);
define('PAGE_RELEASENOTES',   1902);
define('PAGE_RANKS',          1903);
define('PAGE_AWARDS',         1904);
define('PAGE_LEVELS',         1905);
define('PAGE_STATS',          1906);
define('PAGE_DONATE',         1907);
define('PAGE_ABOUT',          1908);
		
/* Admin */
define('PAGE_PLAYER_LIST',    2000);
define('PAGE_PLAYERS',        2001);
define('PAGE_ADMIN_MESSAGES', 2002);
define('PAGE_LEVEL',          2003); 
define('PAGE_LEVEL_ZOOM',     2004);
define('PAGE_PLAYER_COPY',    2005);
define('PAGE_ACTIONS',        2006);
define('PAGE_ADMIN_NEWS',     2007);
define('PAGE_BROWSER',        2008);
define('PAGE_INFO',           2009);

/* Player */
define('PAGE_PROFILE',        2100);
define('PAGE_ATTACK',         2101);
define('PAGE_DEFENCE',        2102);
define('PAGE_INCOME',         2103);
define('PAGE_UPKEEP',         2104);
define('PAGE_CONTINENT',      2105);
define('PAGE_DISCOUNT',       2106);
define('PAGE_MAITENANCE',     2107);

/*
** ------------------
** EVENTS
** ------------------
*/

/* login (WARNING external used) */
define("EVENT_NONE",   		     			  0);
define("EVENT_LOGIN",    				     1);
define("EVENT_REGISTER",        			  2);
define("EVENT_RECOVER",        			  3);
define("EVENT_LOGOUT",                   4);
define("EVENT_REGISTER_SPECIAL",         5);
 
/* home */
define("EVENT_HOME_COMMENT_EDIT",        3101);
define("EVENT_HOME_COMMENT_SAVE",        3102);
define("EVENT_HOME_COMMENT_DELETE",      3103);
define("EVENT_HOME_SKILL_INCREASE",      3104);
define("EVENT_HOME_SKILL_DECREASE",      3105);
define("EVENT_HOME_TRADE",               3106);
define("EVENT_HOME_RESTORE",             3107);
define("EVENT_HOME_EMAIL_CHANGE", 	     3108);
define("EVENT_HOME_SETTINGS_SAVE",       3109);
define("EVENT_HOME_CHANGE_LOGIN",        3110);
define("EVENT_HOME_ACCOUNT_RESET",       3111);
define("EVENT_HOME_EMAIL_CONFIRM",       3112);

/* mission */
define("EVENT_MISSION_PLAY",             3201);
define("EVENT_MISSION_BUY_PLAY",         3202);

/* battle */
define("EVENT_BATTLE_NORMAL",            3301);
define("EVENT_BATTLE_BOUNTY",            3302);
define("EVENT_BATTLE_CLAN_WAR",          3303);

/* unit */
define("EVENT_UNIT_DEPLOY",              3401);
define("EVENT_UNIT_DISBAND",             3402);

/* building */
define("EVENT_BUILDING_BUY",             3501);
define("EVENT_BUILDING_SELL",            3502);

/* money */
define("EVENT_BANK_DEPOSIT",             3601);
define("EVENT_BANK_WITHDRAW",            3602);

define("EVENT_CASINO_WHEEL_PLAY",        3603);
define("EVENT_CASINO_WHEEL_RESULT",      3604);
define("EVENT_CASINO_SLOT_PLAY",         3605);
define("EVENT_CASINO_SLOT_RESULT",       3606);
define("EVENT_CASINO_TIC_PLAY",          3607);
define("EVENT_CASINO_TIC_RESULT",        3608);

define("EVENT_STOCK_BUY",                3610);
define("EVENT_STOCK_SELL",               3611);
define("EVENT_STOCK_ADD",                3612);
define("EVENT_STOCK_REMOVE",             3613);

/* alliance */
define("EVENT_ALLIANCE_INVITE",          3701);
define("EVENT_ALLIANCE_ACCEPT",          3702);
define("EVENT_ALLIANCE_REJECT",          3703);
define("EVENT_ALLIANCE_DROP",            3704);

define("EVENT_CLAN_CREATE",              3705);
define("EVENT_CLAN_JOIN",                3706);
define("EVENT_CLAN_LEAVE",               3707);
define("EVENT_CLAN_DROP",                3708);
define("EVENT_CLAN_SLOGAN",              3709);

/* forum */
define("EVENT_FORUM_COMMENT_SAVE", 	     3801);
define("EVENT_FORUM_COMMENT_DELETE",     3802);
define("EVENT_FORUM_TOPIC_SAVE", 	     3803);
define("EVENT_FORUM_TOPIC_DELETE", 	     3804);
define("EVENT_FORUM_CHAT_UPDATE", 	     3805);
define("EVENT_FORUM_POLL_VOTE", 	        3806);
define("EVENT_FORUM_POLL_UNVOTE", 	     3807);

/* help */

/* admin */
define("EVENT_ADMIN_EDIT",  	           3900);
define("EVENT_ADMIN_DELETE_MSG",  	     3901);
define("EVENT_ADMIN_COPY",  	           3902);
define("EVENT_ADMIN_DELETE_PLAYER",  	  3903);
define("EVENT_ADMIN_UPDATE_TIMERS",  	  3904);
define("EVENT_ADMIN_UPDATE_MONEY",  	  3905);
define("EVENT_ADMIN_NEWS_SAVE",  	     3906);
define("EVENT_ADMIN_NEWS_DELETE",  	     3907);
define("EVENT_ADMIN_UPDATE_STAFF",  	  3908);
define("EVENT_ADMIN_HACK_ACCOUNT",       3909);
define("EVENT_ADMIN_UPDATE_INTEREST",    3910);
define("EVENT_ADMIN_CLEAN_BANK_LOG",     3911);
define("EVENT_ADMIN_UPDATE_INVITATIONS", 3912);
define("EVENT_ADMIN_UPDATE_AWARDS",  	  3913);
define("EVENT_ADMIN_UPDATE_LEVELS",  	  3914);
define("EVENT_ADMIN_CLEAN_BATTLE_LOG",   3915);
define("EVENT_ADMIN_UPDATE_ROBOTS",  	  3916);
define("EVENT_ADMIN_OPTIMIZE_DATABASE",  3917);
define("EVENT_ADMIN_UPDATE_INCOME",  	  3918);
define("EVENT_ADMIN_SAVE_TWEET",  	     3919);
define("EVENT_ADMIN_BACKUP_DATABASE",    3920);

/* others (internal used) */
define("EVENT_PLAYER_PDF_REPORT", 	     4000);
define("EVENT_SWITCH_PLANET", 	        4001);

/* others (WARNING external used) */
define("EVENT_VALID_EMAIL",              4002);

/*
** ------------------
** PATTERN
** ------------------
*/

define("PATTERN_BOUNTY",      0);
define("PATTERN_SOUND",       1);
define("PATTERN_ADS",         2);
define("PATTERN_CONDITION",   3);
define("PATTERN_FORUM_SORT",  4);
define("PATTERN_RESTORE",     5);
define("PATTERN_SORT1",       6);
define("PATTERN_SORT2",       7);
define("PATTERN_NO_BOT_NEWS", 8);
define("PATTERN_ALLY_LIST",   9);
define("PATTERN_BAN",         10);

/*
** ------------------
** THE END
** ------------------
*/

?>