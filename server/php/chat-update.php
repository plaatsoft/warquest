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

include "config.inc";
include "database.inc";
include "general.inc";
include "english.inc";

warquest_db_connect($config["dbhost"], $config["dbuser"], $config["dbpass"], $config["dbname"]);

/* Fetch HTML posted token variable */
$token = warquest_get('token' ,'');

if (strlen($token)>0) {
	
	/* Decode token */
	$token=gzinflate(base64_decode($token));
	$tokens = @preg_split("/&/", $token);
	
	foreach ($tokens as $item) {
		$items = preg_split ("/=/", $item);
		$$items[0] = $items[1];	
	}
}

if (!isset($pid)) {
	$pid=0;
}

if (!isset($oid)) {
	$oid=0;
}

$query  = 'select a.pid1, a.pid2, a.date, a.message, ';
$query .= 'b.name as name1, b.country as country1 ';
$query .= 'from chat a ';
$query .= 'left join player b on a.pid1=b.pid ';
$query .= 'where (a.pid1='.$pid.' and a.pid2='.$oid.')';
$query .= 'or (a.pid1='.$oid.' and a.pid2='.$pid.')';
$query .= ' order by date desc limit 0,20';
 
$result = warquest_db_query($query);

/* Needed for player_format function */
$mid = MENU_FORUMS;

$page = "";
while ($data = warquest_db_fetch_object($result)) {

	$page .= player_format($data->pid1, $data->name1, $data->country1);
	$page .= ' (';
	$page .= warquest_ui_ago($data->date);
	$page .= ') ';
	$page .= warquest_parse_smilies(wordwrap($data->message, 40, "\n\r", true));	
	$page .= '<br/>';
}

echo $page;

/* Added statitics event */
warquest_db_view_add();

/*
** ---------
** THE END
** ---------
*/

?>

