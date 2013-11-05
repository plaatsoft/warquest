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

echo "<b>Release WarQuest</b><br/>";

/* Enable php source code encryption */
$encrypt=1;

$encrypt_files = array( 
	"admin.inc", 
	"alliance.inc", 
	"bank.inc", 
	"battle.inc", 
	"browser.inc",
	"building.inc", 
	"casino.inc",
	"chat-update.php",
	"chat.inc",
	"config.inc", 
	"cron.inc",
	"database.inc", 
	"english.inc", 
	"forum.inc",
	"general.inc",
	"graph.php", 
	"help.inc", 
	"home.inc", 
	"index.php",	
	"leaderboard.inc",	
	"library.inc",
	"login.inc", 
	"menu.inc",	
	"mission.inc", 
	"money.inc",	
	"nederlands.inc", 
	"player.inc", 	
	"planet.php", 	
	"poll.inc",	
	"readme.inc", 
	"report.inc",
	"restore.inc",
	"rss.php",
	"setting.inc",
	"skill.inc",
	"stock.inc",	
	"unit.inc"	
	);

$copy_files = array( 
	"css/general1.css", 
	"css/ie.css", 
	"css/nokia.css", 
	"css/password.css", 
	
	"js/ammo2.js", 
	"js/energy2.js", 
	"js/health2.js", 
	"js/money2.js", 
	"js/link3.js", 
	"js/wheel4.js",
	"js/slotmachine6.js",
	"js/countdown1.js", 
	"js/countdown2.js", 
	"js/countdown3.js", 
	"js/countdown4.js",	
	"js/slider.js", 
	"js/tooltip.js",
	"js/news.js",
	"js/jquery.js", 
	"js/snow.js", 
	"js/fireworks.js", 
	"js/password.js",
	
	"tmhOAuth.php",
	"cacert.pem"
	);

foreach ($copy_files as $file) {

	echo 'Copy '.$file.'<br/>';
	
	$in = fopen($file, 'r');
	$content = fread($in, filesize($file));
	fclose($in);
	
	$out = fopen('encrypt/'.$file, 'w'); 
	fwrite($out, $content);
	fclose($out);
}

foreach ($encrypt_files as $file) {

	echo 'Encrypt '.$file.'<br/>';
	
	$in = fopen($file, 'r');
	$content = fread($in, filesize($file));
	fclose($in);

	/* Remove php header but not xml header */
	
	$pos = strpos($content, "<?xml");
	$content = str_replace("<?php","", $content);
	if ($pos==0) {
		$content = str_replace("?>","", $content);
	}

	/* Rename variables */
	$content = trim($content);
	//$content = str_replace('$pid', '$a', $content); 
	$content = str_replace('$mid', '$b', $content); 
	$content = str_replace('$sid', '$c', $content); 
	$content = str_replace('$uid', '$d', $content); 
	$content = str_replace('$eid', '$e', $content); 
	//$content = str_replace('$oid', '$f', $content); 
	$content = str_replace('$ugid', '$g', $content); 	
	$content = str_replace('$page', '$h', $content); 
	$content = str_replace('$message', '$i', $content); 
	$content = str_replace('$player', '$j', $content); 
	$content = str_replace('$other', '$k', $content); 
	$content = str_replace('$count', '$l', $content);
	$content = str_replace('$amount', '$m', $content); 

	$content = str_replace('$config', '$n', $content); 
	$content = str_replace('$query', '$o', $content); 
	$content = str_replace('$menu', '$p', $content); 
	$content = str_replace('$link', '$q', $content); 
	/* $content = str_replace('$data', '$r', $content); */
	$content = str_replace('$result', '$s', $content); 
	$content = str_replace('$skill', '$t', $content); 
	$content = str_replace('$tmp', '$u', $content); 
	$content = str_replace('$level', '$v', $content); 
	$content = str_replace('$id', '$w', $content); 
	$content = str_replace('= ', '=', $content); 
	$content = str_replace(' =' , '=', $content); 
	$content = str_replace(' .=' , '.=', $content);
			
	/* Rename all function names */
	$content = str_replace('warquest_', '_', $content); 
		
	/* Remove all enter and line feed characters. */
	$content = str_replace("\r\n", "", $content); 
	$content = str_replace("\n", "", $content); 
		
	/* Remove tabs characters */
	$content = str_replace(array("\t"), '', $content); 
	
	/* Remove source code comment lines */
	$content = preg_replace('!/\*.*?\*/!s', '', $content);
	$content = preg_replace('/\n\s*\n/', '', $content);

	/* Encrypt source code */
	if ($encrypt==1) {
		$content = base64_encode(gzdeflate($content));
		$content = 'eval(gzinflate(base64_decode("'.$content.'")));';
	
		/* Break lines every 165 characters */
		$content = preg_replace('/(.{120})/', "$1\r\n", $content);
	}

	/* Write encrypted file */
	$out = fopen('encrypt/'.$file, 'w'); 	
	$tmp  ="<?php\r\n";
	$tmp .= $content."\r\n";
	$tmp .= '?>';
	
	fwrite($out, $tmp);
	fclose($out);
}

echo '<b>Ready</b><br/>';

/*
** ---------------------------------------------------------------- 
** THE END
** ----------------------------------------------------------------
*/

?>