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
** PATTERN
** ------------------
*/

function warquest_db_query_pattern($player, $pos) {
	
	return substr($player->pattern, $pos, 1);
}

function warquest_db_set_pattern($player, $pos, $value) {

	$player->pattern = substr_replace($player->pattern, $value, $pos, 1);
}

/*
** ------------------
** Pologon Functions
** ------------------
*/

/**
 * Add Pologon raster to image 
 */
function addPologonRaster($image) {

	$black = imagecolorallocatealpha($image, 0, 0, 0, 20);
		
	$yoffset=4;
	
	for ($y=0; $y<15; $y++) {

		$xoffset=6;
		if (($y % 2)==0) {
			$xoffset+=44;
		}
			
		for ($x=0; $x<5; $x++) {
		
			$poly = array(	20+($x*88)+$xoffset, 0+ ($y*18)+$yoffset,
								46+($x*88)+$xoffset, 0+ ($y*18)+$yoffset,
								64+($x*88)+$xoffset, 18+($y*18)+$yoffset,
								46+($x*88)+$xoffset, 36+($y*18)+$yoffset,
								20+($x*88)+$xoffset, 36+($y*18)+$yoffset,
								2+ ($x*88)+$xoffset, 18+($y*18)+$yoffset );		  
								
			imagepolygon($image, $poly, 6, $black);	
		}
	}		
}

/**
 * Fill one pologon with a color 
 */
function fillPologon($image, $color, $x, $y) {

	$black = imagecolorallocatealpha($image, 0, 0, 0, 20); 
	
	$yoffset=4;
	$xoffset=6;
	if (($y % 2)==0) {
		$xoffset+=44;
	}
	
	$poly = array(	20+($x*88)+$xoffset, 0+ ($y*18)+$yoffset,
						46+($x*88)+$xoffset, 0+ ($y*18)+$yoffset,
						64+($x*88)+$xoffset, 18+($y*18)+$yoffset,
						46+($x*88)+$xoffset, 36+($y*18)+$yoffset,
						20+($x*88)+$xoffset, 36+($y*18)+$yoffset,
						2+ ($x*88)+$xoffset, 18+($y*18)+$yoffset );		  
		 
	imagefilledpolygon($image, $poly, 6, $color);
	imagepolygon($image, $poly, 6, $black);
}

/**
 * Calc polygon =info used for HTML MAP feature
 */
function calcPologon($x, $y) {

	$xoffset=6;
	$yoffset=4;
		
	if (($y % 2)==0) {
		$xoffset+=44;
	}
	
	$poly  = 20+($x*88)+$xoffset.',';
	$poly .= 0+($y*18)+$yoffset.',';
	$poly .= 46+($x*88)+$xoffset.',';
	$poly .= 0+($y*18)+$yoffset.',';
	$poly .= 64+($x*88)+$xoffset.',';
	$poly .= 18+($y*18)+$yoffset.',';
	$poly .= 46+($x*88)+$xoffset.',';
	$poly .= 36+($y*18)+$yoffset.',';
	$poly .= 20+($x*88)+$xoffset.',';
	$poly .= 36+($y*18)+$yoffset.',';
	$poly .= 2+($x*88)+$xoffset.',';
	$poly .= 18+($y*18)+$yoffset;
		 
	return $poly;
}

/*
** ------------------
** BAD WORDS FILTER
** ------------------
*/

/** 
 * filter out very basic bad language 
 */
function filterBadWords($str){

	/* words to filter */
	$badwords=array( 'fucking', 'fucks', 'fuck', 'pussies', 'pussy', 'penis', 'sucks', 'suck', 'gay', 'homo', 
	     'ashole', 'cock', 'ass', 'bitch' ,'racists' ,'shit', 'dick' ,'crap' );

	for($i=0; $i<sizeof($badwords); $i++){
	
		$str = preg_replace('/^'.$badwords[$i].'/i', ':(', $str);
		$str = preg_replace('/ '.$badwords[$i].'/i', ':(', $str);
	}
	return $str;
}

/*
** -------------------
** Proces Post and Get
** -------------------
*/

function warquest_post($label, $default) {
	
	$value = $default;
	
	if (isset($_POST[$label])) {
		
		$value = $_POST[$label];
		$value = stripslashes($value);
		$value = htmlspecialchars($value);
	}
	return $value;
}


function warquest_get($label, $default) {
	
	$value = $default;
	
	if (isset($_GET[$label])) {
		$value = $_GET[$label];
		$value = stripslashes($value);
		$value = htmlspecialchars($value);	
	}
	
	return $value;
}

/*
** ---------------------------------------------------------------- 
** TRACING
** ----------------------------------------------------------------
*/

function udate($format, $utimestamp = null) {
	if (is_null($utimestamp)) {
		$utimestamp = microtime(true);
	}

	$timestamp = floor($utimestamp);
	$milliseconds = round(($utimestamp - $timestamp) * 1000000);

	return date(preg_replace('`(?<!\\\\)u`', $milliseconds, $format), $timestamp);
}

function warquest_user_log($player, $text) {
	
	$message  = udate('d-m-Y H:i:s:u');		
	$message .= ' [';
	$message .= number_format2($player->money).'|';
	$message .= number_format2($player->bank1).'|';
	$message .= number_format2($player->bank2).'|';
	$message .= number_format2($player->bank3);	
	$message .= '] ';
	$message .= $text;
	$message .= "\r\n";
	
	$myFile = 'user/'.$player->pid.'.log';
	$fp = fopen($myFile, 'a');	
	fwrite($fp, $message);
	fclose($fp);		
}

function warquest_write_file($type, $text) {

	/* input */
	global $player;
	global $other;
	
	$message = udate('d-m-Y H:i:s:u').' ['.$_SERVER["REMOTE_ADDR"];
	
	if (isset($player)) {
		$message .= '|'.$player->pid;
	}
	
	if (isset($other)) {
		$message .= '|'.$other->pid;
	}
	
	$message .= '] '.$type.' '.$text."\r\n";
	$message = str_replace('<br/>', " ", $message); 
	
	$myFile = 'log/WarQuest-'.date('Ymd').'.log';
	$fp = fopen($myFile, 'a');	
	fwrite($fp, $message);
	fclose($fp);		
}

function warquest_info($text) {

	warquest_write_file('INFO', $text);
}

function warquest_error($text) {
	
	warquest_write_file('ERROR', $text);	
}

function warquest_debug($text) {
	
	if (DEBUG == 1 ) {

		warquest_write_file('DEBUG', $text); 
	}
}

/** 
 * Updaet gold use statistics
 */
function warquest_gold_use($gold) {

	if ($gold>0) {
	
		$date = mktime(date("H"), date("i"), date("s"), date("m"), date("d"), date("Y"));
	
		$stats = warquest_db_statistics($date);
	 
		if ( !isset($stats->id) ) {

			warquest_cron_statistics(1);
			$stats = warquest_db_statistics($date);
				
		}
	
		$stats->gold += $gold;

		warquest_db_statistics_update($stats);	
	}
}

	/*
** ---------------------------------------------------------------- 
** CALCULATE FORCE
** ----------------------------------------------------------------
*/

/** 
 * Calculate attack strength of player
 */
function warquest_attack_strength($player, $ugid) {

	/* input */
	global $config;
		
	/* Calculate attack strength of units depending of alliance size */
	$query =  'select a.attack, b.amount from unit a, player_unit b where ';
	$query .= 'a.uid=b.uid and b.pid='.$player->pid;

	switch ($ugid) {
	
		case 0:  /* Army */
					$query .= ' and a.ugid between 1 and 4';
					break;
					
		case 11: /* Moon */
					$query .= ' and a.ugid between 7 and 9';
					break;
					
		case 18: /* Mars */ 
					$query .= ' and a.ugid between 13 and 15';
					break;
						
		case 24:	/* Asteroid */
					$query .= ' and a.ugid between 19 and 21';
					break;
					
		case 30:	/* Sun */
					$query .= ' and a.ugid between 25 and 27';
					break;
										
		default: /* other */
					$query .= ' and a.ugid='.$ugid;
					break;
	}
	$query .= ' order by a.attack desc';

	$result = warquest_db_query($query);

	$attack = 0;
	$size=($player->alliance * 6);
	
	while ($data = warquest_db_fetch_object($result)) {
		
		if ($size >= $data->amount) {
			$size -= $data->amount;
			$attack += ($data->attack * $data->amount);
		} else {
			$attack += ($data->attack * $size);
			$size -= $size;
		}
			
		if ($size==0) {
			break;
		}
	}
	
	/* Get attack strength from skill points */
	$skill = warquest_db_skill($player->pid);
	if (isset($skill->attack_max)) {
		$attack += ($skill->attack_max * $config['init_skill_point_step'] * $player->lid);
	}
	
	return $attack;
}

/** 
 * Calculate defense strength of player
 */ 
function warquest_defense_strength($player, $ugid) {

	/* input */
	global $config;
	
	$defense = 0;
	$size=($player->alliance * 6);
 
	/* Calculate defense strength of units depending of alliance size */
	$query =  'select a.defense, b.amount from unit a, player_unit b where ';
	$query .= 'a.uid=b.uid and b.pid='.$player->pid;

	switch ($ugid) {
	
		case 0:  /* Earth */
					$query .= ' and a.ugid between 1 and 4';
					break;
					
		case 11: /* Moon */
					$query .= ' and a.ugid between 7 and 9';
					break;
					
		case 18: /* Mars */ 
					$query .= ' and a.ugid between 13 and 15';
					break;
					
		case 24:	/* Asteroid */
					$query .= ' and a.ugid between 19 and 21';
					break;

		case 30:	/* Sun */
					$query .= ' and a.ugid between 25 and 27';
					break;

					
		default: /* Other */
					$query .= ' and a.ugid='.$ugid;
					break;
	}
	
	$query .= ' order by a.defense desc';
	$result = warquest_db_query($query);

	while ($data = warquest_db_fetch_object($result)) {
		
		if ($size >= $data->amount) {
			$size -= $data->amount;
			$defense += ($data->defense * $data->amount);
		} else {
			$defense += ($data->defense * $size);
			$size -= $size;
		}
			
		if ($size==0) {
			break;
		}
	}
	
	/* Calculate defense strength of building */
	$query  = 'select a.defense, b.amount from building a, player_building b ';
	$query .= 'where a.bid=b.bid and b.pid='.$player->pid.' and a.defense>0';
	
	switch ($ugid) {
	
		case 0:  /* Army */
					$query .= ' and a.ugid between 1 and 4';
					break;
					
		case 11: /* MoonTroops */
					$query .= ' and a.ugid between 7 and 9';
					break;
					
		case 18: /* MarsTroops */ 
					$query .= ' and a.ugid between 13 and 15';
					break;
		
		case 24:	/* Asteroid */
					$query .= ' and a.ugid between 19 and 21';
					break;
					
		case 30:	/* Sun */
					$query .= ' and a.ugid between 25 and 27';
					break;
					
		default: /* other */
					$query .= ' and a.ugid='.$ugid;
					break;
	}

	$query .= ' order by a.defense desc';
	
	$result = warquest_db_query($query);
	
	while ($data = warquest_db_fetch_object($result)) {
		
		$defense += ($data->defense * $data->amount);
	}
	
	/* Get defense strength from skill points */
	$skill = warquest_db_skill($player->pid);
	if (isset($skill->defense_max)) {
		$defense += ($skill->defense_max * $config['init_skill_point_step'] * $player->lid);
	}
	
	return $defense;
}

function warquest_battle_surrender($player) {

	/* input */
	global $config;
	
	if ($player->health_date>0) {

		$diff = strtotime($player->health_date) - strtotime(date("Y-m-d H:i:s"));
		if ($diff<=0) {
			$diff=abs($diff);
			$amount = floor($diff / $config["init_health_timer"]);
			$player->health += ($player->health_step * ($amount+1));
		}
	}
		
	if ($player->health < $config["init_health_min"]) {	
	   return 1;
	} 
	return 0;
}

/* 
** ----------------------
** INCOME FUNCTIONS
** ----------------------
*/

function warquest_continent_bonus($player, $planet) {

	/* input */
	global $config;
	
	$query  = 'select b.mgid, sum(a.progress) as progress ';
	$query .= 'from player_mission a left join mission b on a.mid=b.mid ';
	$query .= 'left join mission_group c on b.mgid=c.mgid where c.planet='.$planet.' '; 
	$query .= 'and a.pid='.$player->pid.' group by b.mgid';	
	$result = warquest_db_query($query);
			
	$bonus = 0;
	while ($data=warquest_db_fetch_object($result)) {		

		if ($data->progress==2400) {		
			$bonus += $data->mgid * $config["continent_conquer_bonus"];			
		}
	}
	return $bonus;	
}

function warquest_building_income($player, $planet) {

	/* Calculate income */
	$query  = 'select a.income, c.amount from building a left join building_group b on a.bgid=b.bgid, ';
	$query .= 'player_building c where ';
   $query .= 'a.bid=c.bid and c.pid='.$player->pid.' and a.income>0 and b.planet='.$planet;	
	$result = warquest_db_query($query);

	$income = 0;	
	while ($data = warquest_db_fetch_object($result)) {
		$income += ($data->income * $data->amount);	
	}
	
	return $income;
}

function warquest_unit_upkeep($player, $planet) {

	/* Calculate upkeep cost */
	$query =  'select a.upkeep, b.amount from unit a, player_unit b where ';
   $query .= 'a.uid=b.uid and b.pid='.$player->pid;
	
	switch ($planet) {
	
		case PLANET_EARTH: 	
					$query .= ' and a.ugid in (1,2,3,4,5,6)';
					break;
					
		case PLANET_MOON:	
					$query .= ' and a.ugid in (7,8,9,10,12)';
					break;
					
		case PLANET_MARS:	
					$query .= ' and a.ugid in (13,14,15,16,17)';
					break;	

		case PLANET_ASTEROID:	
					$query .= ' and a.ugid in (19,20,21,22,23)';
					break;			
	} 
	
	$result = warquest_db_query($query);

	$upkeep = 0;
	
	while ($data = warquest_db_fetch_object($result)) {
		$upkeep += ($data->upkeep * $data->amount);	
	}
	
	return $upkeep;	
}

/** 
 * Calculate hourly income of player
 */
function warquest_netto_income($player) {
		 
	/* Calculate building income */
	$income  = warquest_building_income($player, PLANET_EARTH);
	$income += warquest_building_income($player, PLANET_MOON);
	$income += warquest_building_income($player, PLANET_MARS);
	$income += warquest_building_income($player, PLANET_ASTEROID);
	
	/* Calculate continent bonus */
	$income += warquest_continent_bonus($player, PLANET_EARTH);
	$income += warquest_continent_bonus($player, PLANET_MOON);
	$income += warquest_continent_bonus($player, PLANET_MARS);
	$income += warquest_continent_bonus($player, PLANET_ASTEROID);

	/* Calculate unit upkeep cost */
	$income -= warquest_unit_upkeep($player, PLANET_EARTH);
	$income -= warquest_unit_upkeep($player, PLANET_MOON);
	$income -= warquest_unit_upkeep($player, PLANET_MARS);
	$income -= warquest_unit_upkeep($player, PLANET_ASTEROID);
	
	$player->money_step = $income;
}

/*
** ---------------------------------------------------------------- 
** SMILIES
** ----------------------------------------------------------------
*/

/* Smilies list */
$smilies = array(
	':arrow:'   =>	'arrow.gif',
	':D' 		   =>	'biggrin.gif',
	':?:' 	   =>	'question.gif',
	':?' 		   =>	'confused.gif',
	'8-)' 	   =>	'cool.gif',
	':(' 	      =>	'cry.gif',
	'8|' 	      =>	'eek.gif',
	':evil:'    =>	'evil.gif',
	':!:' 	   =>	'exclaim.gif',
	':!:' 	   =>	'exclaim.gif',
	':idea:'    =>	'idea.gif',
	':lol:'     =>	'lol.gif',
	':mad:'     =>	'mad.gif',
	':mrgreen:' =>	'mrgreen.gif',
	':|' 		   =>	'neutral.gif',	
	':P' 			=>	'razz.gif',
	':oops:' 	=>	'redface.gif',
	':roll:' 	=>	'rolleyes.gif',
	':sad:' 		=>	'sad.gif',
	':)' 			=>	'smile.gif',
	':o' 			=>	'surprised.gif',
	':twisted:' =>	'twisted.gif',
	';)' 			=>	'wink.gif',
	':sleep:' 	=>	'sleep.gif',
	':like:' 	=>	'thumb_up.gif',
	':bad:' 		=>	'thumb_down.gif'
);

function warquest_parse_smilies($text) {

	/* input */
	global $config;
	global $smilies;
	
	foreach($smilies as $key => $value) {
		$image = '<img src="'.$config["content_url"].'images/smilies/icon_'.$value.'" border="0"/>'; 
		$text = str_replace($key, $image, $text);	
	} 	
	return $text;	
}
	
function warquest_show_smilies($tag="comment") {

	/* input */
	global $config;
	global $smilies;

	/* output */
	global $output;
	
	/* Javascript to insert smily in textarea */
	$images  = '<script type="text/javascript" language="JavaScript">';
	$images .= 'function addtxt(text) {';
	$images .= 'var obj = document.forms[\'warquest\'].elements[\''.$tag.'\']; ';
	$images .= 'obj.focus(); ';	
	$images .= 'obj.value += text + " "; ';
	$images .= '}';
	$images .= '</script>';
	
	$count=0;
	
	foreach($smilies as $key => $value) {
		$images .= '<div id="tip'.$count.'" class="tooltip">'.$key.'</div>';
		$images .= '<img id="smily'.$count.'" src="'.$config["content_url"].'images/smilies/icon_'.$value.'" '; 
		$images .= 'onmouseover="tooltip_show(\'tip'.$count.'\',\'smily'.$count.'\',0,20);" ';
		$images .= 'onmouseout="tooltip_hide(\'tip'.$count.'\',\'smily'.$count.'\',0,20);" ';
		$images .= 'onclick="addtxt(\''.$key.'\');" >';
	
		$count++;
	} 
	return $images;
}

/*
** ---------------------------------------------------------------- 
** GRAVATAR
** ---------------------------------------------------------------- 
*/

/**
 * Get either a Gravatar URL or complete image tag for a specified email address.
 *
 * @param string $email The email address
 * @param string $s Size in pixels, defaults to 80px [ 1 - 512 ]
 * @param string $d Default imageset to use [ 404 | mm | identicon | monsterid | wavatar ]
 * @param string $r Maximum rating (inclusive) [ g | pg | r | x ]
 * @param boole $img True to return a complete IMG tag False for just the URL
 * @param array $atts Optional, additional key/value attributes to include in the IMG tag
 * @return String containing either just a URL or a complete image tag
 * @source www.gravatar.com/site/implement/images/php/
 */
function get_gravatar( $email, $s = 70, $d = 'mm', $r = 'g', $img = false, $atts = array() ) {

	$url = 'http://www.gravatar.com/avatar/';
	$url .= md5( strtolower( trim( $email ) ) );
	$url .= "?s=$s&d=$d&r=$r";
	if ( $img ) {
		$url = '<img src="' . $url . '"';
		foreach ( $atts as $key => $val )
			$url .= ' ' . $key . '="' . $val . '"';
		$url .= ' />';
	}
	return $url;
}

/*
** ---------------------------------------------------------------- 
** TRANSLATE
** ---------------------------------------------------------------- 
*/

/**
 * Translate country label (multi language support)
 */
function warquest_landcode($code) {

	global $landcode;

	$tmp = @$landcode[strtolower($code)];
	if (strlen($tmp)==0) {
		$tmp = $code;
	}
	return $tmp;
}

/**
 * Translate text label (multi language support)
 */
function t() {

	global $lang;
	
   $numArgs = func_num_args();

   $temp = $lang[func_get_arg(0)];

   $pos = 0;
   $i = 1;

   while (($pos = strpos($temp, "%s", $pos)) !== false) {
      if ($i >= $numArgs) {
         throw new InvalidArgumentException("Not enough arguments passed.");
		}

      $temp = substr($temp, 0, $pos) . func_get_arg($i) . substr($temp, $pos + 2);
      $pos += strlen(func_get_arg($i));
      $i++;
   }      
	
	$temp = mb_convert_encoding($temp, "UTF-8", "HTML-ENTITIES" ); 
   return $temp; 
}



function warquest_place($place) {
	
	if ($place==1) {
		return t('GENERAL_ST',$place);	
	} else if ($place==2) {
		return t('GENERAL_ND',$place);	
	} else {
		return t('GENERAL_TH',$place);
	}
}

/*
** ---------------------------------------------------------------- 
** UTILS
** ---------------------------------------------------------------- 
*/

/** 
 * Get Mininum attack level for player.
 */
function warquest_get_min_attack_level() {

	/* input */
	global $player;
	global $config;

	$level=1;
	
	if ($player->lid <= $config["max_linear_attack_level"]) { 
	
		$level = $player->lid;

	} else {	
	
		if ($player->lid >= 259) {
			$level = 250;
		} else {
			$level = floor($player->lid/10)*10;
		}
	}
	return $level;
}

/** 
 * Get Maximum attack level for player.
 */
function warquest_get_max_attack_level() {

	/* input */
	global $player;
	global $config;

	$level=1;
	
	if ($player->lid <= $config["max_linear_attack_level"]) {
	
		$level = $player->lid;
		
	} else {	
	
		if ($player->lid>249) {
			$level = $config["max_level"];
		} else {
			$level = (floor(($player->lid+10)/10)*10)-1;
		}
	}
	return $level;
}

/** 
 *  Give random loot to mission player
 */
function warquest_lootoption($level) {

	/* input */
	global $player;
	
	/* 20 procent chance to win a loot. */
	if (rand(1,5)==1) 
	{		
		$query  = 'select a.uid, a.defense, a.attack, a.upkeep from unit a ';
		$query .= 'left join unit_group b on a.ugid=b.ugid where ';
		$query .= 'b.type in (1,2,3,4,5) and a.gold=0 and b.planet='.$player->planet;
		
		/* Get max level related to active planet */
		$max = $level;
		switch ($player->planet) {
			
			case PLANET_EARTH:  
						$min = 0;
						$max = 100;
					   break;
						
			case PLANET_MOON:  
						$min = 100;
						$max = 150;
						break;
							
			case PLANET_MARS: 
						$min = 150;
						$max = 200;
						break;
						
			case PLANET_ASTEROID:  
						$min = 200;
						$max = 250;
						break;
		}
		
		if ($level<$max) {
			$max=$level;
		}
					
		$tmp = $max - 25;
		if ($tmp < $min) { 
			$tmp = $min;
		}
				
		$query .= ' and lid between '.$tmp.' and '.$max.' order by rand() limit 0,1';
		
		$result = warquest_db_query($query);
		
		/* If a unit loot is found, continue */
		if ($unit = warquest_db_fetch_object($result) ) {
		
			$amount = rand(1, round($player->lid/20));	
						
			/* check if hourly income (upkeep) is not getting negative. */
			if ($player->money_step >= ($unit->upkeep*$amount)) {
		
				warquest_db_unit_add($player->pid, $unit->uid, $amount);
		
				/* Update income, attack and defense value */
				warquest_netto_income($player);
		
				$message  = '<br/>'.loot_format(t('MISSION_LOOT_WON')).'<br/>';		
				$message .= '<table>';
				$message .= '<tr>';
				$message .= '<td width="90">';
				$message .= warquest_unit_image($unit, 1001);		
				$message .= '<br/><center>'.$amount.'x</center>';
				$message .= '<td>';
				$message .= '</tr>';
				$message .= '</table>';
	
				return $message;
			}
		}
	}
}

/** 
 * Table data page control navigation.
 */
function warquest_page_control($offset, $limit, $total, $top=0, $more="") {

	/* input */
	global $mid;
	global $sid;
	global $uid;
			
	$page ="";

	if ($total>$limit) {

		if ($top==0) {
			$page .= '<br/>';
		}
		$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&uid='.$uid.'&offset=0'.$more, t('LINK_FIRST'),'first');
		$page .= '&nbsp;';

		$value = $offset - $limit;
		if ($value<0) {
			$value=0;
		}
		$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&uid='.$uid.'&offset='.$value.$more, t('LINK_PREVIOUS'), 'prev');
		$page .= '&nbsp;';
	
		$value = $offset + $limit;
		if ($value>=$total) {
			$value = $total - $limit;
		}	
		$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&uid='.$uid.'&offset='.$value.$more, t('LINK_NEXT'), 'next');
		$page .= '&nbsp;';
	
		$value = $total - $limit;
		$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&uid='.$uid.'&offset='.$value.$more, t('LINK_LAST'), 'last');	
		
		$page .= '<br/>';
		
		if ($top==1) {
			$page .= '<br/>';
		}
	}
	return $page;
}

/** 
 * Player ranks depending on player current level.
 */
function warquest_rank($lid) {

	$id = ceil($lid / 8);
	if ($id == 0 ) {
		$id = 1;
	}
	if ($id > 23) {
		$id = 23;
	}
   return t('RANK_'.$id);
}

/* 
** ----------------------
** Web Services
** ----------------------
*/

/** 
 * Web services to get country information of remote ip address.
 */
function warquest_getlocation($ip) { 

	ini_set('default_socket_timeout', 5);

	$url = 'http://www.geoplugin.net/php.gp?ip='.$ip;

	if ( function_exists('curl_init') ) {
		
		$ch = curl_init();
		curl_setopt($ch, CURLOPT_URL, $url);
		curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
		curl_setopt($ch, CURLOPT_USERAGENT, 'WarQuest');
		$response = curl_exec($ch);
		curl_close($ch);
			
	} else if ( ini_get('allow_url_fopen') ) {
				
		$response = @file_get_contents($url, 'r');
		
	}
		
   $info = unserialize($response);
	$iso = $info['geoplugin_countryCode'];
	if (strlen($iso)==0) {
		$iso = "EU";
	}
	
	ini_set('default_socket_timeout', 30);
	
   return $iso;		
}

/** 
 * Web services to twitter information.
 */
function warquest_twitter($player) { 
 
	/* input */
	global $config;
	
	ini_set('default_socket_timeout', 2);
 
	$tmp ="";

	if ($config["webservices"]==0) {	
		return $tmp;
	}
	
	$url = 'http://api.twitter.com/1/statuses/user_timeline/'.$player->twitter.'.xml';		

	if ( function_exists('curl_init') ) {
		
		$ch = curl_init();
		curl_setopt($ch, CURLOPT_URL, $url);
		curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
		curl_setopt($ch, CURLOPT_USERAGENT, 'WarQuest');
		$response = curl_exec($ch);
		curl_close($ch);
			
	} else if ( ini_get('allow_url_fopen') ) {
				
		$response = @file_get_contents($url, 'r');
		
	}
	
	$tweet = @simplexml_load_string($response);
	
	$tmp = "";
	if (isset($tweet)) {
	
		$tmp = @$tweet->status[0]->text;
	}
		
	ini_set('default_socket_timeout', 30);
	return $tmp;
	
}
		
/* 
** ----------------------
** UI
** ----------------------
*/

function warquest_switch_planet_do() {

	/* input */
	global $planet;
	
	/* output */
	global $player;
	
	$player->planet=$planet;
}

$link_counter=0;

/**
 * Create link 
 */
function warquest_link($parameters, $label, $id="", $title="") {
   
	global $browser;	
	global $link_counter;
	
	$link_counter++;
	
	if (preg_match("/Symbian/", $browser)) {

		$link  = '<button name="token" value="'.warquest_token($parameters).'" class="link" ';
		$link .= 'id="link-'.$link_counter.'"';
		$link .= '>'.$label.'</button>';
		
	} else {
	
		$link  = '<a href="javascript:link(\''.warquest_token($parameters).'\');" class="link" ';			
		if (strlen($id)!=0) {
			$link .= ' id="'.strtolower($id).'"';
		}
		if (strlen($title)!=0) {
			$link .= ' title="'.strtolower($title).'"';
		}
		$link .= '>'.$label.'</a>';	
	}
	return $link;
}

/**
 * Create hidden link 
 */
function warquest_link_hidden($parameters, $label) {
   
	global $browser;
	global $link_counter;
	
	$link_counter++;
	
	if (preg_match("/Symbian/", $browser)) {

		$link  = '<button name="token" value="'.warquest_token($parameters).'" class="hide_link" ';
		$link .= 'id="link-'.$link_counter.'"';
		$link .= '>'.$label.'</button>';
		
	} else {
	
		$link  = '<a href="javascript:link(\''.warquest_token($parameters).'\');" class="hide_link" ';					
		$link .= 'id="link-'.$link_counter.'">'.$label.'</a>';	
	}
	return $link;
}

/**
 * Create hidden link with popup
 */ 
function warquest_link_confirm($parameters, $label, $question="") {
   			
	global $link_counter;	
	
	$link_counter++;
	
	$link  = '<a href="javascript:show_confirm(\''.$question.'\',\''.warquest_token($parameters).'\');" class="link" ';
	$link .= 'id="link-'.$link_counter.'">'.$label.'</a>';	
		
	return $link;
}

/** 
 * Zip and uuencode token.
 */
function warquest_token($token) {
   
	/* Encode token  */
	$token = base64_encode(gzdeflate($token));
	
	return $token;
}

/** 
 * Show html combobox with amount options
 */
function warquest_amount_selected($max=0) {

	/* input */
	global $amount;
	
	$values = array(1, 2, 5, 10, 20, 50, 100, 200, 500, 1000, 2000);

	$page ='<select id="amount" name="amount">';
	
	foreach ($values as $value) {
	
		if (($max==0) || ($max>$value)) {
			$page.='<option value="'.$value.'"';
		
			if ($amount == $value) {
				$page .= ' selected="selected"';
			}
			$page .= '>'.number_format2($value).'</option>';
		}				
	}
	if ($max!=0) {
		$page.='<option value="'.$max.'">'.number_format2($max).'</option>';
	}
	
	$page.='</select>';
	  
   return $page;
}

function warquest_amount_radiobox() {

	/* input */	
	global $mid;
	global $sid;
	global $ssid;
			
	global $player;
			
	$values = array(1, 2, 5, 10, 20, 50, 100, 200, 500);
		
	$page = '<div class="box"><b>'.t('GENERAL_AMOUNT').':</b> ';

	$count = 0;
	foreach ($values as $value) {

		$count++;
		if ($player->default_amount==$value) {
			$page .= '<input type="radio" name="amount2" value="'.$value.'" checked />'.number_format2($value).' ';	
		} else {
			$page .= '<input type="radio" name="amount2" value="'.$value.
								'" onclick="javascript:link(\''.
								warquest_token('mid='.$mid.'&sid='.$sid.'&ssid='.$ssid).'\');" />'.
								number_format2($value).' ';	
		}	
	}
	
	$page .= '</div>';
	
	return $page;
}

/** 
 * Calculate interest with discount
 */
function warquest_rente($value, $amount, $discount) {

	/* Calculate 1% interest with discount*/
	
	$total = $value * pow( 1.01, $amount);
	$total -= (($total / 100 ) * $discount);
	
	return floor($total);
}

/** 
 * Convert data to dutch format.
 */
function warquest_convert_date($value) { 

  list($date, $time) = preg_split('/ /', $value);
  list($year, $month, $day) = preg_split('/-/', $date); 
  return $day.'-'.$month.'-'.$year.' '.$time;
}

/**
 * Convert data mysql 
 */
function convert_date_mysql($date) {
	$part = preg_split('/-/', $date);
	return $part[2].'-'.$part[1].'-'.$part[0];
}

/**
 * Play mp3 sound file 
 */
function warquest_sound( $filename, $loop=0) {

	/* input */
	global $player;

	/* output */
	global $page;
	
	if (warquest_db_query_pattern($player, PATTERN_SOUND)==1) {
	
		$page .= '<audio autoplay ';
		if ($loop==1) {
			$page .= 'loop';
		}
		$page .= '>'; 
		$page .= '<source src="mp3/'.$filename.'" type="audio/mpeg">';
		$page .= '</audio>';		
	}
}

/* 
** ----------------------
** TIMERS
** ----------------------
*/

/** 
 * Process player timers.
 */
function warquest_update_timers($player) {

	/* input */
	global $config;
	
	$skill = warquest_db_skill($player->pid);
	
	if (!isset($skill->health_max)) {
		/* In case that the player is deleted return direct */
		return;
	}

	/* health */
	if ($player->health < $skill->health_max) {
		if (($player->health_date==0)) {
		    /* start timer */
			$player->health_date = date("Y-m-d H:i:s", time() + $config["init_health_timer"] - ($skill->health_timer * 5)); 
		} else {
			$diff = strtotime($player->health_date) - strtotime(date("Y-m-d H:i:s"));
			if ($diff<=0) {
				$diff=abs($diff);
				$amount = floor($diff / ($config["init_health_timer"] - ($skill->health_timer * 5)));
				$player->health += ($player->health_step * ($amount+1));
				$diff -= ($config["init_health_timer"] - ($skill->health_timer * 5)) * $amount;
				$player->health_date = date("Y-m-d H:i:s", time() + $config["init_health_timer"] - ($skill->health_timer * 5) - $diff);
			} 
		}
	}
	if ($player->health >= $skill->health_max) {
		$player->health=$skill->health_max;
		$player->health_date="0000-00-00 00:00:00"; /* stop timer */
	}
		
	/* energy */
	if ($player->energy < $skill->energy_max) {
	   /* start timer */
		if (($player->energy_date==0)) {
			$player->energy_date = date("Y-m-d H:i:s", time() + $config["init_energy_timer"] - ($skill->energy_timer * 5)); 
		} else {
			$diff = strtotime($player->energy_date) - strtotime(date("Y-m-d H:i:s"));
			if ($diff<=0) {
				$diff=abs($diff);
				$amount = floor($diff / ($config["init_energy_timer"] - ($skill->energy_timer * 5)));
				$player->energy += ($player->energy_step * ($amount+1));
				$diff -= ($config["init_energy_timer"] - ($skill->energy_timer * 5)) * $amount;
				$player->energy_date = date("Y-m-d H:i:s", time() + $config["init_energy_timer"] - ($skill->energy_timer * 5) - $diff);
			} 
		}
	}
	if ($player->energy >= $skill->energy_max) {
		$player->energy=$skill->energy_max;
		$player->energy_date="0000-00-00 00:00:00"; /* stop timer */
	}
			
	/* ammo */
	if ($player->ammo < $skill->ammo_max) {
		if (($player->ammo_date==0)) {
			/* start timer */
			$player->ammo_date = date("Y-m-d H:i:s", time() + $config["init_ammo_timer"] - ($skill->ammo_timer * 5)); 
		} else {
			$diff = strtotime($player->ammo_date) - strtotime(date("Y-m-d H:i:s"));
			if ($diff<=0) {
				$diff=abs($diff);
				$amount = floor($diff / ($config["init_ammo_timer"] - ($skill->ammo_timer * 5)));
				$player->ammo += ($player->ammo_step * ($amount+1));
				$diff -= ($config["init_ammo_timer"] - ($skill->ammo_timer * 5)) * $amount;
				$player->ammo_date = date("Y-m-d H:i:s", time()+$config["init_ammo_timer"] - ($skill->ammo_timer * 5) - $diff);
			} 
		}
	}
	if ($player->ammo >= $skill->ammo_max) {
		$player->ammo=$skill->ammo_max;
		$player->ammo_date="0000-00-00 00:00:00"; /* stop timer */
	}
	
	/* money */
	if ($player->holiday_date <= date("Y-m-d H:i:s", time())) {
	
		if ($player->money_step != 0) {
			if (($player->money_date==0)) {
			
				/* start timer */
				$player->money_date = date("Y-m-d H:i:s", time() + $config["init_money_timer"]); 
			
			} else {
			
				$diff = strtotime($player->money_date) - strtotime(date("Y-m-d H:i:s"));
			
				/* Max. 24 hours can be payed out */
				if ($diff<(-1 * $config["max_income_period"])) {
					$diff = (-1 * $config["max_income_period"]);
				}
						
				if ($diff<=0) {
					$diff=abs($diff);
					$amount = floor($diff / $config["init_money_timer"]);
				
					/* Calculate income of expired hours. */
					$extra = $player->money_step * ($amount + 1);								
					$player->money += $extra;
				
					/*  Calculate new money expire time */
					$diff -= $config["init_money_timer"] * $amount;								
					$player->money_date = date("Y-m-d H:i:s", time()+$config["init_money_timer"] - $diff);
				
					$log = 'Hourly income '.number_format2($extra);		
					warquest_user_log($player, $log);
				} 
			}
		} else {
			/* stop money timer */
			$player->money_date="0000-00-00 00:00:00";
		}
	
		/* stop money timer if user is not login last 24 hours */
		$member = warquest_db_member($player->pid);	
		$diff  = strtotime(date("Y-m-d H:i:s")) -  strtotime($member->last_login);
		if ($diff > $config["max_income_period"]) {		
			/* stop money timer */
			$player->money_date="0000-00-00 00:00:00";
		}
	}	
}

/* 
** ----------------------
** NEXT LEVEL / AWARD DETECTION
** ----------------------
*/

/** 
 * Detect player next level action
 */
function warquest_nextlevel_do($player) {

	global $config;

	$returnValue = 0;

	$level = warquest_db_level($player->lid);
	
	/* Detect next level */
	if (($player->lid<$config["max_level"]) && ($player->experience>=$level->experience)) {		
	
		$returnValue = 1;
	
		$skill = warquest_db_skill($player->pid);
	
		/* Restore health, energy and ammo */
		$player->health = $skill->health_max;
		$player->energy = $skill->energy_max;		
		$player->ammo = $skill->ammo_max;
		
		/* Increase level */
		$player->lid += 1;
					
		/* Update skill points */
		$skill->skill_points += $config["next_level_sp_bonus"];
		warquest_db_skill_update($skill);
	}
	
	return $returnValue;
}

		
/** 
 * Detect player next level 
 */
function warquest_nextlevel($player) {

	/* input */
	global $config;
			
	/* output */
	global $popup;
	
	$returnValue = 0;
	
	/* Detect next level */
	if (warquest_nextlevel_do($player)==1) {
		
		/* Add bonus */
		$money = $config["init_money"] * $player->lid * rand(1,3);
		$player->money += $money;
		
		$log = 'Next Level bonus '.number_format2($money);		
		warquest_user_log($player, $log);
				
		$message  = t('GENERAL_NEXT_LEVEL', $config["next_level_sp_bonus"], money_format1($money)).'<br/><br/>';
		
		for ($tmp=0; $tmp<$config["next_level_sp_bonus"]; $tmp++) {
			$message .= warquest_image("other/star.jpg");
		}
		$message .= '<br/><br/>'; 
		
		/*
		**---------------------
		** NEW FEATURE DETECTION
		** ---------------------
		*/
		$feature = 0;
		
		$tmp = '<table>';
		
		$query = 'select uid, defense, attack, upkeep from unit where lid='.$player->lid;
		$result = warquest_db_query($query);
		
		while ($data=warquest_db_fetch_object($result)) { 
			$tmp .= '<tr>';
			
			$tmp .= '<td width="120">'; 
			$tmp .= warquest_unit_image($data, 0, 1);
			$tmp .= '</td>';
			
			$tmp .= '<td width="130">';	
			$tmp .= t('GENERAL_NEW_UNIT');
			$tmp .= '</td>';
			
			$tmp .= '<td width="250">';
			$tmp .= '<b>'.t('UNIT_'.$data->uid).'</b><br/>';
			if ($data->attack > 0) {
				$tmp .= $data->attack.' '.t('GENERAL_ATTACK').' - ';
			}
			if ($data->defense > 0) {
				$tmp .= $data->defense.' '.t('GENERAL_DEFENSE');
			}
			if ($data->upkeep > 0) {
				$tmp .= '<br/>'.t('GENERAL_UPKEEP').': '.money_format1($data->upkeep);
			}
			$tmp .= '</td>';
			
			$tmp .= '</tr>';
			$feature = 1;
		}
		
		$query = 'select ugid, bid, income, energy, defense, maintenance, discount from building where lid='.$player->lid;
		$result = warquest_db_query($query);
		
		while ($data=warquest_db_fetch_object($result)) { 
			$tmp .= '<tr>';
			$tmp .= '<td width="120">';		
			$tmp .= warquest_building_image($data, 0, 1);			
			$tmp .= '</td>';
		
			$tmp .= '<td width="130">';	
			$tmp .= t('GENERAL_NEW_BUILDING');
			$tmp .= '</td>';
			
			$tmp .= '<td width="250"><b>'.t('BUILDING_'.$data->bid).'</b><br/>' ;
			if ($data->income > 0) {
				$tmp .= t('GENERAL_INCOME').': '.dollar_format($data->income);
			} else if ($data->defense > 0) {
				$tmp .= t('GENERAL_DEFENSE').': +'.$data->defense;
			} else if ($data->energy > 0) {
				$tmp .= t('GENERAL_ENERGY').': +'.$data->energy;
			} else if ($data->maintenance > 0) {
				$tmp .= t('GENERAL_MAINTENANCE').': +'.$data->maintenance;			
			} else if ($data->discount > 0) {
				$tmp .= t('GENERAL_DISCOUNT').': +'.$data->discount;			
			}
			$tmp .= '</td>';	
		
			$tmp .= '</tr>';
			$feature = 1;
		}
	
		$query = 'select mid, min_price, max_price from mission where lid='.$player->lid;
		$result = warquest_db_query($query);
		
		while ($data=warquest_db_fetch_object($result)) { 
			$tmp .= '<tr>';
			
			$tmp .= '<td width="120">';	
			$tmp .= warquest_mission_image($data);
			$tmp .= '</td>';
			
			$tmp .= '<td width="130">';	
			$tmp .= t('GENERAL_NEW_MISSION');
			$tmp .= '</td>';
			
			$tmp .= '<td width="250">';	
			$tmp .= '<b>'.t('GENERAL_CONQUER').' '.t('MISSION_'.$data->mid).'</b><br/>';
			$tmp .=  t('GENERAL_GAIN').': '.money_format1($data->min_price).' - ';
			$tmp .= money_format1($data->max_price);
			$tmp .= '</td>';
			
			$tmp .= '</tr>';
			$feature = 1;
		}
		
		$tmp .= '</table>';

		if ($feature == 1 ) {
		
			$message .= t('GENERAL_NEW_FEATURES');
			$message .= '<br/><br/>';
			$message .= $tmp;
		}
		
		$link = warquest_link('mid='.MENU_HOME.'&sid='.PAGE_SKILLS, t('LINK_SP'));
		
		$popup .= warquest_box("info", $message, $link);
		
		$returnValue = 1;
	}
	
	return $returnValue;
}

/** 
 * Detect player battle award is won
 */
function warquest_battle_award_won_do($player) {

	global $config;
	
	$returnValue = 0;

	$query =  "select won, ep from battle_award where id=".$player->won_level;  	
	$result = warquest_db_query($query);

	$won = 999999;
	if ($data = warquest_db_fetch_object($result)) {
		$won = $data->won;
	}
		
	/* Detect next level */
	if ($player->won>=$won) {		
	
		/* Update player info */
		$player->won_level++;
			
		/* Update skill points */
		$skill = warquest_db_skill($player->pid);
		$skill->skill_points += $data->ep;
		warquest_db_skill_update($skill);
		
		$returnValue = $data->ep;
	}
	
	return $returnValue;
}


/** 
 * Detect when player won a battle award
 */
function warquest_battle_award_won($player) {
		
	/* input */
	global $config;
	
		/* output */
	global $popup;
	
	$ep = warquest_battle_award_won_do($player);
		
	if ($ep>0) {
	
		/* Add bonus */
		$money = $config["init_money"] * $player->lid * rand(1,3);
		$player->money += $money;
		
		$log = 'Battle award bonus '.number_format2($money);		
		warquest_user_log($player, $log);
		
		/* Show message */
		$message  = t('GENERAL_BATTLE_LEVEL', number_format2($player->won), $ep, money_format1($money)).'<br/><br/>';
			
		for ($tmp=0; $tmp<$ep; $tmp++) {
			$message .= warquest_image("other/star.jpg");
		}
		$message .= '<br/><br/>'; 
		 
		$message .= t('GENERAL_RECEIVED_AWARD')."<br/><br/>";			
		$message .= warquest_battle_image($player->won_level-1, $player->won);
		$message .= '<br/><br/>'; 
			
		$link = warquest_link('mid='.MENU_HOME.'&sid='.PAGE_SKILLS, t('LINK_SP'));
		
		$popup .= warquest_box("info", $message, $link);
	}
}

/** 
 * Detect player bounty award is won
 */
function warquest_bounty_award_won_do($player) {

	global $config;
	
	$returnValue = 0;

	$query =  "select amount, ep from bounty_award where id=".$player->bounty_level;  	
	$result = warquest_db_query($query);

	$amount = 999999;
	if ($data = warquest_db_fetch_object($result)) {
		$amount = $data->amount;
	}
		
	/* Detect next level */
	if ($player->bounty>=$amount) {		
	
		/* Update player info */
		$player->bounty_level++;
			
		/* Update skill points */
		$skill = warquest_db_skill($player->pid);
		$skill->skill_points += $data->ep;
		warquest_db_skill_update($skill);
		
		$returnValue = $data->ep;
	}
	
	return $returnValue;
}

/** 
 * Detect when player won a bounty award
 */
function warquest_bounty_award_won($player) {
		
	/* input */
	global $config;
	
	/* output */
	global $popup;
	
	$ep = warquest_bounty_award_won_do($player);
		
	if ($ep>0) {
	
		/* Add bonus */
		$money = $config["init_money"] * $player->lid * rand(1,3);
		$player->money += $money;
		
		$log = 'Bounty award bonus '.number_format2($money);		
		warquest_user_log($player, $log);
		
		/* Show message */
		$message  = t('GENERAL_BOUNTY_LEVEL', number_format2($player->bounty), $ep, money_format1($money)).'<br/><br/>';
			
		for ($tmp=0; $tmp<$ep; $tmp++) {
			$message .= warquest_image("other/star.jpg");
		}
		$message .= '<br/><br/>'; 
		 
		$message .= t('GENERAL_RECEIVED_AWARD')."<br/><br/>";			
		$message .= warquest_bounty_image($player->bounty_level-1, $player->bounty);
		$message .= '<br/><br/>'; 
			
		$link = warquest_link('mid='.MENU_HOME.'&sid='.PAGE_SKILLS, t('LINK_SP'));
		$popup .= warquest_box("info", $message, $link);
	}
}


/** 
 * Detect player rebel award is won
 */
function warquest_rebel_award_won_do($player) {

	global $config;
	
	$returnValue = 0;

	$query =  "select amount, ep from rebel_award where id=".$player->rebel_level;  	
	$result = warquest_db_query($query);

	$amount = 999999;
	if ($data = warquest_db_fetch_object($result)) {
		$amount = $data->amount;
	}
		
	/* Detect next level */
	if ($player->rebel>=$amount) {		
	
		/* Update player info */
		$player->rebel_level++;
			
		/* Update skill points */
		$skill = warquest_db_skill($player->pid);
		$skill->skill_points += $data->ep;
		warquest_db_skill_update($skill);
		
		$returnValue = $data->ep;
	}
	
	return $returnValue;
}

/** 
 * Detect when player won a rebel award
 */
function warquest_rebel_award_won($player) {
		
	/* input */
	global $config;
	
	/* output */
	global $popup;
	
	$ep = warquest_rebel_award_won_do($player);
		
	if ($ep>0) {
	
		/* Add bonus */
		$money = $config["init_money"] * $player->lid * rand(1,3);
		$player->money += $money;
		
		$log = 'Rebel award bonus '.number_format2($money);		
		warquest_user_log($player, $log);
		
		/* Show message */
		$message  = t('GENERAL_REBEL_LEVEL', $player->rebel, $ep, money_format1($money)).'<br/><br/>';
			
		for ($tmp=0; $tmp<$ep; $tmp++) {
			$message .= warquest_image("other/star.jpg");
		}
		$message .= '<br/><br/>'; 
		 
		$message .= t('GENERAL_RECEIVED_AWARD')."<br/><br/>";			
		$message .= warquest_rebel_image($player->bounty_level-1, $player->bounty);
		$message .= '<br/><br/>'; 
			
		$link = warquest_link('mid='.MENU_HOME.'&sid='.PAGE_SKILLS, t('LINK_SP'));
		$popup .= warquest_box("info", $message, $link);
	}
}

/*
** ------------------------
** Map / bonus / rebel
** ------------------------
*/

function warquest_rebel_check($other) {

	/* input */
	global $player;
	global $config;
	
	$tmp="";
   if ($other->rebel_status >= $config["init_rebel_treshhold"])
	{	
		$query  = 'select a.mid, a.part from player_mission a ';
		$query .= 'left join mission b on a.mid=b.mid ';
		$query .= 'left join mission_group c on b.mgid=c.mgid ';
		$query .= 'where progress!=0 and ';
		$query .= 'c.planet='.$player->planet.' and ';
		$query .= 'a.pid='.$other->pid.' ';
		$query .= 'order by rand() limit 0,'.rand(1,2);
		$result = warquest_db_query($query);
		
		while ($data=warquest_db_fetch_object($result)) {		
			
			warquest_db_mission_progress_update($other->pid, $data->mid, 0, 0, $data->part);
			
			if (strlen($tmp)>0) {
				$tmp .= ' '.t('BATTLE_AND').' ';
			}
			$tmp .= t('GENERAL_CONQUER').' '.t('MISSION_'.$data->mid);
		
			/* Clear rebel counter */
			$other->rebel_status=0;
			
			/* Update income value */
			warquest_netto_income($other);
		}		
		
		if (strlen($tmp)==0) {
			
			/* No region found to rebel */			
			$other->rebel_status=101;
		
			
		} else {
		
			$tmp = str_replace('Conquer ', '', $tmp); 
			$tmp = str_replace('Overwin ', '', $tmp); 
			$tmp = str_replace(' Region', '', $tmp); 
			$tmp = str_replace(' regio', '', $tmp); 
		}
	}
		
	return $tmp;
}

function warquest_format_progress($progress, $part) {
  
	/* input */
	global $config;
	
	$tmp=100;
	if ($config['max_mission_part']!=$part) {
		$tmp = ($progress - ($part*100));
	}
	return $tmp;
}

function warquest_format_part($part) {
  
	if ($part == 0) {
		return 1;
	} else if ($part == 1) {
		return 2;
	} 
	return 3;
}

/*
** ---------------------
** UI
** ---------------------
*/

/** 
 * get html ago
 */		
function warquest_ui_ago($date) {

	$value="";
	$diff = strtotime(date("Y-m-d H:i:s")) - strtotime($date);
	if ($diff<0) $diff=0;
	
	$days = floor ($diff / (60*60*24));
	$hours = floor ($diff / (60*60));
	$mins = floor ($diff / 60);
	$secs = $diff;
	
   if ($days>0)  {
		if ($days==1) {
			$value=$days.t('AGO_DAY');
		} else {
			$value=$days.t('AGO_DAYS');
		}
   } else if ($hours>0)  {
		if ($hours==1) {
			$value=$hours.t('AGO_HOUR');
		} else {
			$value=$hours.t('AGO_HOURS');
		}
	} else if ($mins>0)  {
		if ($mins==1) {
			$value=$mins.t('AGO_MIN');
		} else {
			$value=$mins.t('AGO_MINS');
		}
	} else {
		if ($secs==1) {
			$value=$secs.t('AGO_SEC');
		} else {
			$value=$secs.t('AGO_SECS');
		}
	}
	return $value;
}


/** 
 * Get html checkbox 
 */
function warquest_ui_checkbox($name, $value, $checked) {

	$tmp = '<input type="checkbox" name="'.$name.'" value="'.$value.'"';
	if ($checked==1) {
		$tmp .= ' checked="checked"';
	} 
	
	$tmp .= '/>';
	
	return $tmp;	
}

/** 
 * Get html radiobox 
 */
function warquest_ui_radiobox($name, $value, $checked, $disabled) {

	$tmp = '<input type="radio" name="'.$name.'" value="'.$value.'"';
	if ($checked==1) {
		$tmp .= ' checked="checked"';
	} 
	
	if ($disabled==1) {
		$tmp .= ' disabled="true"';
	} 
	
	$tmp .= '/>';
	
	return $tmp;	
}
/**
 * Get HTML map
 */
function warquest_ui_map($player, $planet) {
	
	/* input */
	global $browser;
	global $pid;
		
	$page = "";
		
	$query  = 'select a.mid, a.progress, a.part, a.part2, d.x, d.y ';
	$query .= 'from player_mission a ';
	$query .= 'left join mission b on a.mid=b.mid ';
	$query .= 'left join mission_group c on c.mgid=b.mgid ';
	$query .= 'left join sector d on b.mid=d.mid ';
	$query .= 'where a.pid='.$player->pid.' and c.planet='.$planet;
	
	$result = warquest_db_query($query);
			
	$tmp = "";
	while ($data=warquest_db_fetch_object($result)) {			
		if (strlen($tmp)!=0) {
			$tmp .= ',';
		}
		$progress = $data->progress;
		
		/* rebellion */
		if ($data->part!=$data->part2) {
			$progress = 0;
		}
		
		if ($planet==PLANET_EARTH) {
			$tmp .= $data->mid.'-'.$progress;
		} else {
			$tmp .= $data->x.'-'.$data->y.'-'.$progress;
		}
	}
	
	$width=483;
	$height=300;
	
	$page .= '<center>';			
	switch ($planet) {

		case PLANET_EARTH:
			$page .= '<img src="planet.php?planet='.$planet.'&data='.$tmp.'" width="'.$width.'" height="'.$height.'" title="'.t('GENERAL_PLANET_0').'" usemap="#map">';	
			if (($pid==$player->pid) && ($player->lid>1) && ($player->holiday_date <= date("Y-m-d H:i:s", time()))) {
				$page .= '<map name="map">';		
				$page .= '<area shape="rect" coords="200,0,250,90" title="'.t('MISSION_GROUP_1').'" href="javascript:link(\''.warquest_token('mid='.MENU_MISSIONS.'&sid=1').'\');" />';
				$page .= '<area shape="rect" coords="30,0,190,110" title="'.t('MISSION_GROUP_2').'" href="javascript:link(\''.warquest_token('mid='.MENU_MISSIONS.'&sid=2').'\');" />';
				$page .= '<area shape="rect" coords="80,130,160,250" title="'.t('MISSION_GROUP_3').'" href="javascript:link(\''.warquest_token('mid='.MENU_MISSIONS.'&sid=3').'\');" />';
				$page .= '<area shape="rect" coords="180,90,260,230" title="'.t('MISSION_GROUP_4').'" href="javascript:link(\''.warquest_token('mid='.MENU_MISSIONS.'&sid=4').'\');" />';	
				$page .= '<area shape="rect" coords="250,0,500,70" title="'.t('MISSION_GROUP_5').'" href="javascript:link(\''.warquest_token('mid='.MENU_MISSIONS.'&sid=5').'\');" />';
				$page .= '<area shape="rect" coords="320,70,400,115" title="'.t('MISSION_GROUP_7').'" href="javascript:link(\''.warquest_token('mid='.MENU_MISSIONS.'&sid=7').'\');" />';
				$page .= '<area shape="rect" coords="390,150,500,250" title="'.t('MISSION_GROUP_8').'" href="javascript:link(\''.warquest_token('mid='.MENU_MISSIONS.'&sid=8').'\');" />';	
				$page .= '<area shape="rect" coords="250,70,300,130" title="'.t('MISSION_GROUP_9').'" href="javascript:link(\''.warquest_token('mid='.MENU_MISSIONS.'&sid=9').'\');" />';
				$page .= '</map>';
			}
			break;
		
		default:
			$page .= '<img src="planet.php?planet='.$planet.'&data='.$tmp.'" width="'.$width.'" height="'.$height.'" usemap="#map">';	
			if (($pid==$player->pid) && ($player->lid > 1)) {
			
				$page .= '<map name="map">';
	
				$query  = 'select a.x, a.y, b.mid, b.mgid from sector a, mission b where a.mid=b.mid and a.planet='.$planet;		
				$result = warquest_db_query($query);			
				while ($data=warquest_db_fetch_object($result)) {			
			
					$page .= '<area shape="poly" coords="'.calcPologon($data->x,$data->y).'" title="'.t('MISSION_'.$data->mid).'" ';
					$page .= 'href="javascript:link(\''.warquest_token('mid='.MENU_MISSIONS.'&sid='.$data->mgid.'&anchor='.$data->mid).'\');" />';
				}			
				$page .= '</map>';
			}
			break;
	}
	$page .= '</center>';
	
	return $page;
}

/**
 * Get HTML input
 */
function warquest_ui_input($name, $size, $maxlength, $value, $readonly=false) {
	
	$page  = '<input ';
	$page .= 'type="text" ';
	$page .= 'id="'.$name.'" ';
	$page .= 'name="'.$name.'" ';
	$page .= 'value="'.$value.'" ';
	$page .= 'size='.$size.' ';
	$page .= 'maxlength='.$maxlength.' ';
	
	if ($readonly==true) {
		$page .= 'disabled="true" ';
	}
	
	$page .= '/>';

	return $page;
}

/**
 * Get HTML backgorund selector
 */
function warquest_ui_background($tag, $id, $readonly) {
				
	$array = array( "0" =>  t('BACKGROUND_0'), 
						 "1" =>  t('BACKGROUND_1'), 
						 "2" =>  t('BACKGROUND_2'),
						 "3" =>  t('BACKGROUND_3'),
						 "4" =>  t('BACKGROUND_4'),
						 "5" =>  t('BACKGROUND_5'),
						 "6" =>  t('BACKGROUND_6'),
						 "7" =>  t('BACKGROUND_7'),
						 "8" =>  t('BACKGROUND_8'),
						 "9" =>  t('BACKGROUND_9'),
						 "10" => t('BACKGROUND_10'),
						 "11" => t('BACKGROUND_11'),
						 "12" => t('BACKGROUND_12') );
						 
	$page ='<select id="mybackground" name="mybackground">';
		
	foreach ($array as $key => $value) {
	
		$page.='<option value="'.$key.'" style="background-image: url(images/background/background'.$key.'.jpg);" ';
		
		if ($id == $key) {
			$page .= ' selected="selected"';
		}
		
		$page .= '>'.$value.'</option>';
	}
	$page.='</select>';
	
	return $page;
}

/**
 * Get HTML country selector
 */
function warquest_ui_country($tag, $id, $readonly) {
	
	/* input */
	global $landcode;
	
	$page ='<select id="'.$tag.'" name="'.$tag.'" ';
	if ($readonly) {
		$page .= 'disabled="true" ';
	}
	$page .= '>'; 
	
	$id = strtolower($id);
	
	foreach ($landcode as $key => $value) {
	
		$page.='<option value="'.$key.'"';
		
		if ($id == $key) {
			$page .= ' selected="selected"';
		}
		$page .= '>'.$value.'</option>';
	}
		
	$page.='</select>';
	  
   return $page;
}

/**
 * Get HTML language selector
 */
function warquest_ui_language($tag, $id, $readonly) {

	$array = array( "nl" => t('PLAYER_LANG_DUTCH'),
						 "en" => t('PLAYER_LANG_ENGLISH'), 
						 "de" => t('PLAYER_LANG_GERMAN'),
						 "it" => t('PLAYER_LANG_ITALIAN'),
						 "ro" => t('PLAYER_LANG_ROMANIAN'),
						 "es" => t('PLAYER_LANG_SPANISH') 
						 );

	$page ='<select id="'.$tag.'" name="'.$tag.'">';
	
	foreach ($array as $key => $value) {
	
		$page.='<option value="'.$key.'"';
		
		if ($id == $key) {
			$page .= ' selected="selected"';
		}
		
		$page .= '>'.$value.'</option>';
	}
	$page.='</select>';
	  
   return $page;
}

/**
 * Get HTML menu bar
 */
function warquest_ui_menu($mid, $sid, $ssid, $label, $active_id, $notification=0) {
   
	$menu = warquest_link('mid='.$mid.'&sid='.$sid.'&ssid='.$ssid, $label, strtolower($label));
	if (($mid==$active_id) || ($sid==$active_id)) {
		$menu = '<b>'.$menu.'</b>';
	} 
	if ( $notification > 0 ) {
		$menu .= '<span class="notification">'.$notification.'</span>';	
	}
	$menu .= ' ';
	
	return $menu;
}

/**
 * Get HTML submenu bar
 */
function warquest_ui_subsubmenu($mid, $sid, $ssid, $label, $active_id) {
   
	$menu = warquest_link('mid='.$mid.'&sid='.$sid.'&ssid='.$ssid, $label, strtolower($label));
	if (($ssid==$active_id)) {
		$menu = '<b>'.$menu.'</b>';
	} 

	$menu .= ' ';
	
	return $menu;
}

/**
 * Get HTML tip
 */
function warquest_ui_tip() {

	/* input */
	global $player;
	
	$page = '';
	
	@$help=t('TIP_'.$player->lid);
	
	if (strlen($help)>0) {	
		$page .= '<span class="tip">TIP: '.$help.'</span>';		
	}	
	
	return $page;
}

/**
 * Show HTML box
 */	
function warquest_box($title, $message, $link="") {
	
	$page = '<div class="box">';
	
	if (strlen($link)>0) {
		$page .= '<div class="right">';
		$page .= $link;
		$page .= '</div>'; 
	} 

	if ($title=="info") {
		$page .= '<div class="paragraph"><span class="info">'.t('BOX_INFO').'</span></div>';
	} else if ($title=="warning") {
		$page .= '<div class="paragraph"><span class="warning">'.t('BOX_WARN').'</span></div>';
	} else {
		$page .= '<div class="paragraph">'.$title.'</div>';
	} 
	$page .= $message;
		
	$page .= '</div>';	
	
	return $page;
}
	
/**
 * Show HTML box  with icon
 */	
function warquest_box_icon($title, $message, $link="") {
	
	$page = '<div class="box">';
	
	$page .= '<table>';
	$page .= '<tr>';
	
	if ($title=="info") {
		$page .= '<td width="70" valign="top">'; 
		$page .= warquest_image('other/info.png',' width="64" height="64" ');
		$page .= '</td>';
	
		$page .= '<td width="400">';
		$page .= '<div class="paragraph"><span class="info">'.t('BOX_INFO').'</span></div>';
		
	} else if ($title=="warning") {
		$page .= '<td width="70" valign="top">'; 
		$page .= warquest_image('other/warning.png',' width="64" height="64" ');
		$page .= '</td>';
		
		$page .= '<td width="400">';
		$page .= '<div class="paragraph"><span class="warning">'.t('BOX_WARN').'</span></div>';
	
	} else if ($title=="error") {
		$page .= '<td width="70" valign="top">'; 
		$page .= warquest_image('other/error.png',' width="64" height="64" ');
		$page .= '</td>';
		
		$page .= '<td width="400">';
		$page .= '<div class="paragraph"><span class="error">'.t('BOX_ERROR').'</span></div>';
			
	} else if ($title=="classified") {
		$page .= '<td width="70" valign="top">'; 
		$page .= warquest_image('other/classified.png',' width="64" height="64" ');
		$page .= '</td>';
		
		$page .= '<td width="400">';
		$page .= '<div class="paragraph"><span class="warning">CLASSIFIED</span></div>';
		
	} else { 
	
		$page .= '<td width="400">'; 
		$page .= '<div class="paragraph">'.$title.'</div>';
	} 
	
	$page .= $message;
	$page .= '</td>';
	
	if (strlen($link)>0) {
		$page .= '</td>';
		$page .= '<td width="100" align="right" valign="top">';
		$page .= $link;
		$page .= '</td>';
	}
	$page .= '</tr>';
	$page .= '</table>';
	$page .= '</div>';		
	
	return $page;
}

/**
 * HTML header
 */
function warquest_ui_header( $title = "") {
   
	/* input */
	global $config;
	global $mid;
   global $sid;
	global $browser;
	global $player;
	global $session;
	global $version;
	
	$page  = '<html>';
	$page .= '<head>';

	$page .= '<meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />';
	
	if (preg_match('/iPhone/',$browser)) {
		$page .= '<meta name="viewport" content="width=520" />';
		$page .= '<meta name="format-detection" content="telephone=no" />';	
		/* Added Apple icon  */
		$page .= '<link rel="apple-touch-icon" href="images/WarQuest.png"/>';
	
	} else if (preg_match('/iPod/',$browser)) {
		$page .= '<meta name="viewport" content="width=520" />';
		$page .= '<meta name="format-detection" content="telephone=no" />';
		/* Added Apple icon  */
		$page .= '<link rel="apple-touch-icon" href="images/WarQuest.png"/>';
		
	} else if (preg_match('/iPad/',$browser)) {
		$page .= '<meta name="viewport" content="width=530" />';
		$page .= '<meta name="format-detection" content="telephone=no" />';
		/* Added Apple icon  */
		$page .= '<link rel="apple-touch-icon" href="images/WarQuest.png"/>';
	} 	
 	
	if (preg_match('/Android/',$browser)) {
		$page .= '<meta name="viewport" content="width=535" />';
	}
 
	$page .= '<link href="'.$config["content_url"].'images/favicon.ico" rel="shortcut icon" type="image/x-icon" />'; 
	$page .= '<link href="'.$config["content_url"].'css/general4.css" rel="stylesheet" type="text/css" />';

	if (($mid==MENU_MONEY) && ($sid==PAGE_STOCK_EXCHANGE)) {	
		$page .= '<link href="'.$config["content_url"].'css/jquery.css" rel="stylesheet" type="text/css" />';
	}
	
	if ($mid==MENU_LOGIN) {
		
		$page .= '<link rel="alternate" type="application/rss+xml" title="WarQuest RSS Feed" href="http://www.warquest.nl/rss.php" />';
		$page .= '<meta name="keywords" content="warquest,plaatsoft,rmpg,worldwar,warzone,casino,stock exchange,weapons,buildings,units,alliances" />';
		$page .= '<link rel="canonical" href="http://www.warquest.nl" />';
		
		$page .= '<meta name="application-name" content="WarQuest" />';
		$page .= '<meta name="description" content="WarQuest is a free multiplayer online game (MPOG)" />';
		$page .= '<meta name="application-url" content="http://www.warquest.nl" />';		
		$page .= '<meta name="alexaVerifyID" content="_MX6dKojTtmMFTu5AeOCUc11NP4" />';		
	}
	
	/* Detect Microsoft Internet Explorer */
	if (preg_match("/MSIE/", $browser)) {
		$page .= '<link href="'.$config["content_url"].'css/ie.css" rel="stylesheet" type="text/css" />';
	}
	
	/* Detect Nokia browser devices */
	if (preg_match("/Symbian/", $browser)) {
		$page .= '<link href="'.$config["content_url"].'css/nokia.css" rel="stylesheet" type="text/css" />';
	}
				
	/* Add custom background image */
	if (@$player->background=="") {	
		$background = 1;
	} else {
		$background = $player->background;
	}
	
	$page .= '<style type="text/css">';
	if ($background == 0 ) {
		$page .= 'body { background: black }';			
	} else {	
		$page .= 'body { background: black url("'.$config["content_url"].'images/background/background'.$background.'.jpg") 0 0 repeat fixed; }';		
	}
	$page .= '</style>';
		
	/* Add JavaScripts */
	$page .= '<script language="JavaScript" src="'.$config["content_url"].'js/link3.js" type="text/javascript"></script>';
	
	if ($mid!=0) {
		$page .= '<script language="JavaScript" src="'.$config["content_url"].'js/money3.js" type="text/javascript"></script>';
		$page .= '<script language="JavaScript" src="'.$config["content_url"].'js/health2.js" type="text/javascript"></script>';
		$page .= '<script language="JavaScript" src="'.$config["content_url"].'js/energy2.js" type="text/javascript"></script>';
		$page .= '<script language="JavaScript" src="'.$config["content_url"].'js/ammo2.js" type="text/javascript"></script>';
		$page .= '<script language="JavaScript" src="'.$config["content_url"].'js/tooltip.js" type="text/javascript"></script>';
	}
	
	if (($mid==MENU_MONEY) && ($sid==PAGE_STOCK_EXCHANGE)) {	
		$page .= '<script language="JavaScript" src="'.$config["content_url"].'js/jquery.js" type="text/javascript"></script>';
		$page .= '<script language="JavaScript" src="'.$config["content_url"].'js/jquery-ui.js" type="text/javascript"></script>';	
	}
	
	if (($mid==MENU_MONEY) && ($sid==PAGE_CASINO)) {
		$page .= '<script language="JavaScript" src="'.$config["content_url"].'js/tictactoe.js"></script>';
	}
	
	/* Add HTML Title */
	if ($title=="") {
		$page .= '<title>'.$config["applName"].'</title>';
	} else {
		$page .= '<title>'.$config["applName"].' - '.$title.'</title>';
	}
	$page .= "</head>";

	$page .= "<body>";
	
	$page .= '<form id="warquest" method="POST">';
	
	/* Store session information for next request */	
	$page .= '<input type="hidden" name="session" value="'.$session.'" />';
	
	if ($mid==MENU_LOGIN) {
		$page .= '<input type="hidden" name="version" value="'.$version.'" />';
	}
	
	return $page;
}

/**
 * Player status banner (contain money, exp, level, health, energy and ammo info
 */
function warquest_ui_banner() {

	/* input */
	global $player;
	global $skill;
	global $mid;
	global $config;
		
	$level = warquest_db_level($player->lid);
		
	$page  = '<div class="fixed">'; 
	$page .= '<div class="box">'; 
	$page .= '<div class="banner">'; 
	$page .= '<table>';
	
	$page .= '<tr>';
	
	$page .= '<td valign="top" width="180">';
	$page .= warquest_link_hidden('mid='.MENU_ALLIANCE.'&sid='.PAGE_BEST_PLAYER, t('STATUS_CASH')).': ';
	$page .= '<span class="value" id="moneyvalue"></span>';
	
	$tmp = "";
	if (($player->money_step!=0) && ($player->holiday_date <= date("Y-m-d H:i:s", time()))) {	
		$tmp .= '<br/>';
		$tmp .= '<span class="timer">'.money_format1($player->money_step).' in </span>';
		$tmp .= '<span class="timer" id="moneycountdown"></span> ';
	}
	if (strlen($tmp)>0) {
		$page .= $tmp.' / ';
	} else {
		$page .= '<br/>';
	}
	$page .= '<span class="timer">'.gold_format($player->gold).'</span>';
	$page .= '</td>';
	
	$page .= '<td valign="top" width="180">';
	$page .= warquest_link_hidden('mid='.MENU_ALLIANCE.'&sid='.PAGE_BEST_COUNTRY, t('STATUS_EXP')).': ';
	$page .= '<span class="value experience">'.number_format($player->experience,0,",",".");
	$page .= '</span>';
	if ($player->lid!=$config["max_level"]) {
		$page .= ' / '.number_format($level->experience,0,",",".");
	}
	
	if (warquest_db_query_pattern($player, PATTERN_CONDITION)==1) {
	
		$page .= '<br/><span class="timer">';
		$tmp1 = 100-$player->damage_units;
		if ($tmp1<0) {
			$tmp1=0;
		}
		$tmp2 = 100-$player->damage_buildings;
		if ($tmp2<0) {
			$tmp2=0;
		}
		$page .= 'UC='.indication_format($tmp1,1).' BC='.indication_format($tmp2,1).' RC='.indication_format($player->rebel_status,0);
		$page .= '</span>';
	}
	$page .= '</td>';
	
	$page .= '<td valign="top">';
	$page .= warquest_link_hidden('mid='.MENU_FORUMS.'&sid='.PAGE_FORUM, t('STATUS_LEVEL')).': ';
	$page .= '<span class="value level">'.$player->lid.'</span>';
	if ($player->lid>0) {
		$page .= '<br/><span class="timer">'.t('STATUS_ALLIANCE_SIZE').': ';
		$page .= alliance_format($player->alliance).' / '.($player->lid*$config["max_ally_factor"]).'</span>';
	}
	$page .= '</td>';
	$page .= '</tr>';	
	$page .= '<tr>';
	
	$page .= '<td valign="top" >';
	if ($player->comment>0) {
		$page .= warquest_link('mid='.MENU_HOME.'&sid='.PAGE_MESSAGES, warquest_image("other/email.gif").' ','mail');
	}
	
	if ($player->chat>0) {
		$page .= warquest_link('mid='.MENU_FORUMS.'&sid='.PAGE_CHAT.'&oid='.$player->chat, warquest_image('other/chat.gif').' ','chat');
	}
		
	$page .= warquest_link_hidden('mid='.MENU_HOME.'&sid='.PAGE_RESTORE, t('STATUS_HEALTH')).': ';
	$page .= '<span class="value health" id="healthvalue"></span> / '.number_format($skill->health_max,0,",",".");
	$page .= '<br/>';
	$page .= '<span class="timer" id="healthcountdown"></span>';
	$page .= '</td>';
		
	$page .= '<td valign="top" >';
	$page .= warquest_link_hidden('mid='.MENU_HOME.'&sid='.PAGE_PROFILE, t('STATUS_ENERGY')).': ';
	$page .= '<span class="value energy" id="energyvalue"></span> / '.number_format($skill->energy_max,0,",",".");
	$page .= '<br/>';
	$page .= '<span class="timer" id="energycountdown"></span>';
	$page .= '</td>';
	
	$page .= '<td valign="top">';
	$page .= warquest_link_hidden('mid='.MENU_HOME.'&sid='.PAGE_SKILLS, t('STATUS_AMMO')).': ';
	$page .= '<span class="value ammo" id="ammovalue"></span> / '.$skill->ammo_max;
	$page .= '<br/>';
	$page .= '<span class="timer" id="ammocountdown"></span>';
	$page .= '</td>';
	
	$page .= '</tr>';
	
	$page .= '</table>';
	$page .= '</div>'; 
	$page .= '</div>';
	$page .= '</div>';
	
	$page .= '<script language="JavaScript" type="text/javascript">'; 
	
	$diff=-1;
	if (($player->money_date!=0) && ($player->holiday_date <= date("Y-m-d H:i:s", time()))) {
		$diff=strtotime($player->money_date) - strtotime(date("Y-m-d H:i:s"));
	}
	$page .= 'moneytimer('.$diff.','.$player->money.','.$player->money_step.');';
	$page .= 'moneycountdown();';

	$diff=-1;
	if ($player->health_date!=0) {
		$diff=strtotime($player->health_date) - strtotime(date("Y-m-d H:i:s"));
	}
	$tmp = $config['init_health_timer']- ($skill->health_timer * 5);
   $page .= 'healthtimer('.$diff.','.$player->health.','.$skill->health_max.','.$player->health_step.','.$tmp.');';
   $page .= 'healthcountdown();';
	
	$diff=-1;
	if ($player->energy_date!=0) {
		$diff=strtotime($player->energy_date) - strtotime(date("Y-m-d H:i:s"));
	}
	$tmp = $config['init_energy_timer']- ($skill->energy_timer * 5);
	$page .= 'energytimer('.$diff.','.$player->energy.','.$skill->energy_max.','.$player->energy_step.','.$tmp.');';
	$page .= 'energycountdown();';
			
	$diff=-1;
	if ($player->ammo_date!=0) {
		$diff=strtotime($player->ammo_date) - strtotime(date("Y-m-d H:i:s"));
	}
	$tmp = $config['init_ammo_timer']- ($skill->ammo_timer * 5);
   $page .= 'ammotimer('.$diff.','.$player->ammo.','.$skill->ammo_max.','.$player->ammo_step.','.$tmp.');';
   $page .= 'ammocountdown();';
	
	$page .= '</script>'; 
	
	$page .= '<div class="scroll">';
	
	return $page;
}

/**
 * Get HTML footer
 */
function warquest_ui_footer($renderTime, $queries) {

	global $browser;
	global $config;
	global $player;
	global $mid;
	
	$page = '</div>';
	$page .= '</form>';
	
	if (isset($player->background)) {
		switch ($player->background) {
						
			case 11: $page .= '<script type="text/javascript" src="js/snow.js"></script>';
					   break;

			case 12: $page .= '<script type="text/javascript" src="js/fireworks.js"></script>';
					   break;
		}
	}
		
	$page .= '<div class="copyright">';
	$page .= '<center>';
	$page .= '<i>';
	$page .= t('COPYRIGHT');
	$page .= '<br/>';
	$page .= '['.$renderTime.' ms - '.$queries.' queries]';
	$page .= '</i>';
	$page .= '</center>';
	$page .= '</div>';
		
	/* Google analystic */
	if ($config["webservices"]==1) {	
		$page .= '<script type="text/javascript">var gaJsHost = (("https:" == document.location.protocol) ? "https://ssl." : "http://www."); document.write(unescape("%3Cscript src=\'" + gaJsHost + "google-analytics.com/ga.js\' type=\'text/javascript\'%3E%3C/script%3E"));</script><script type="text/javascript">try{ var pageTracker = _gat._getTracker("UA-26602300-1"); pageTracker._trackPageview(); } catch(err) {} </script>';
	}
	
	$page .= "</body>";
	$page .= "</html>";
	
	return $page;
}

/*
** ---------------------
** UI FORMATING
** ---------------------
*/

/**
 * Get clan html format
 */
function clan_format($clan) {

	$value = "?";
	
	if (isset($clan->cid)) {
	
		$value = warquest_link('mid='.MENU_ALLIANCE.'&sid='.PAGE_CLAN_LIST.'&id='.$clan->cid, $clan->name, "", $clan->slogan);
	}
	
	return $value;
}

/**
 * Get player html format
 */
function player_format($pid, $name, $country, $size=0) {

	global $mid;
		
	if ($size==0) {
		return warquest_link('mid='.$mid.'&sid='.PAGE_PROFILE.'&oid='.$pid, warquest_flag_image($country,16,11).' '.$name);
	} else {
		return warquest_link('mid='.$mid.'&sid='.PAGE_PROFILE.'&oid='.$pid, warquest_flag_image($country).' '.$name);
	}
}
			
/**
 * Get gold html format
 */
function gold_format($value) {

	return '<span class="gold">'.number_format($value,0,",",".").'</span> '.t('GENERAL_GOLD');	
}

/**
 * Get dollar html format
 */
function dollar_format($value) {
   
	if ($value>=0) {
		return '<span class="money">'.number_format($value,0,",",".").'</span> '.t('GENERAL_DOLLAR');	
	} else {
		return '<span class="negative">'.number_format($value,0,",",".").'</span> '.t('GENERAL_DOLLAR');
	}
}
	
/**
 * Get money html format
 */
function money_format1($value) {
   
	if ($value>=0) {
		return '<span class="money">'.number_format($value,0,",",".").'</span>';	
	} else {
		return '<span class="negative">'.number_format($value,0,",",".").'</span>';
	}
}

/**
 * Get money html format
 */
function money_format2($value) {
   
	if ($value>=10000000) {
	   $value=$value/10000;
		$value=floor($value);
		$value=$value/100;
		return '<span class="money">'.number_format($value,0,",",".").' mil</span>';	
	} else {
		return '<span class="money">'.number_format($value,0,",",".").'</span>';	
	}
}

/**
 * Get stock html format
 */
function stock_format($value) {
   
	if ($value>=0) {
		return '<span class="money">'.number_format($value,2,".",".").'</span>';	
	} else {
		return '<span class="negative">'.number_format($value,2,".",".").'</span>';
	}
}

/**
 * Get money negative html format
 */
function money_negative($value) {
   
	return '<span class="negative">'.number_format($value,0,",",".").'</span>';
}

/**
 * Get experience html format
 */
function experience_format($value) {
   
	return '<span class="experience">'.number_format($value,0,",",".").'</span>';
}

/**
 * Get energy html format
 */
function energy_format($value) {
   
	return '<span class="energy">'.number_format($value,0,",",".").'</span>';
}

/**
 * Get country html format
 */
function country_format($value) {
   
	return '<span class="country">'.number_format($value,0,",",".").'</span>';
}

/**
 * Get deploy html format
 */
function deploy_format($value) {
   
	return '<span class="deploy">'.number_format($value,0,",",".").'</span>';
}

/**
 * Get discount html format
 */
function discount_format($value) {
   
	return '<span class="discount">'.$value.'</span>';
}

/**
 * Get maintenance html format
 */
function maintenance_format($value) {
   
	return '<span class="maintenance">'.$value.'</span>';
}

/**
 * Get health html format
 */
function health_format($value) {
   
	return '<span class="health">'.number_format($value,0,",",".").'</span>';
}

/**
 * Get alliance html format
 */
function alliance_format($value) {
   
	return '<span class="alliance">'.number_format($value,0,",",".").'</span>';
}

/**
 * Get level html format
 */
function level_format($value) {
   
	return '<span class="level">'.number_format($value,0,",",".").'</span>';
}

/**
 * Get ammo html format
 */
function ammo_format($value) {
   
	return '<span class="ammo">'.number_format($value,0,",",".").'</span>';
}

/**
 * Get loot html format
 */
function loot_format($value) {
   
	return '<span class="loot">'.$value.'</span>';
}

/**
 * Get number html format
 */
function number_format2($value) {
   
	return number_format($value,0,",",".");
}

/**
 * Get procentage html format
 */
function procent_format($value) {
   
	if ($value>=0) {
		return '<span class="money">'.number_format($value,2,",",".").'%</span>';	
	} else {
		return '<span class="negative">'.number_format($value,2,",",".").'%</span>';
	}
}

/**
 * Get indication html format
 */
function indication_format($value, $pos) {

	if ($pos==1) {
		if ($value>50) {
			return '<span class="green">'.$value.'%</span>';
		} else if ($value>20) {
			return '<span class="yellow">'.$value.'%</span>';
		} else {
			return '<span class="red">'.$value.'%</span>';
		}
	} else {
		if ($value>80) {
			return '<span class="red">'.$value.'%</span>';
		} else if ($value>50) {
			return '<span class="yellow">'.$value.'%</span>';
		} else {
			return '<span class="green">'.$value.'%</span>';
		}
	}
}

/*
** ---------------------
** VALIDATION
** ---------------------
*/

/**
 * Function valid email address
 * @return true or false
 */
function validate_email($address) {

	if (!filter_var($address, FILTER_VALIDATE_EMAIL)) {
		return true;
	} else {
		return false;
	}
}

/*
** ---------------------
** IMAGES
** ---------------------
*/

/**
 * Get general image
 */
function warquest_image($filename, $options="") {

	/*  input */
	global $config;
	
	$image = '<img '.$options.' src="'.$config["content_url"].'images/'.$filename.'" />';
	return $image;
}	

/**
 * Get planet image
 */ 
function warquest_planet_image($id) {

	/* input */
	global $config;
			
	$image  = '<img id="planet'.$id.'" src="'.$config["content_url"].'images/planet/planet'.$id.'.png" title="'.t('GENERAL_PLANET_'.$id).'" width="32" height="32" />';	
	
	return $image;
}

/**
 * Get battle image
 */
function warquest_battle_image($id, $won) {

	/* input */
	global $config;
	
	$image = '<div id="atip'.$id.'" class="tooltip">';
	$image .= number_format($won,0,",",".").' '.t('GENERAL_BATTLE_AWARD_WON');
	$image .= '</div>';
		
	$image  .= '<img id="aaward'.$id.'" src="'.$config["content_url"].'images/battle/insigne'.$id.'.gif" ';
	$image .= 'width="50" height="20" style="padding:1" ';
	$image .= 'onmouseover="tooltip_show(\'atip'.$id.'\', \'aaward'.$id.'\', 5, 5);" ';
	$image .= 'onmouseout="tooltip_hide(\'atip'.$id.'\');" />';
				
	return $image;
}

/**
 * Get bounty image
 */
function warquest_bounty_image($id, $amount) {

	/* input */
	global $config;
	
	$image = '<div id="ztip'.$id.'" class="tooltip">';
	$image .= number_format($amount,0,",",".").' '.t('GENERAL_BOUNTY_AWARD_WON');
	$image .= '</div>';
		
	$image  .= '<img id="zaward'.$id.'" src="'.$config["content_url"].'images/bounty/award'.$id.'.jpg" ';
	$image .= 'width="50" height="20" style="padding:1" ';
	$image .= 'onmouseover="tooltip_show(\'ztip'.$id.'\', \'zaward'.$id.'\', 5, 5);" ';
	$image .= 'onmouseout="tooltip_hide(\'ztip'.$id.'\');" />';
				
	return $image;
}

/**
 * Get rebel image
 */
function warquest_rebel_image($id, $amount) {

	/* input */
	global $config;
	
	$image = '<div id="rtip'.$id.'" class="tooltip">';
	$image .= number_format($amount,0,",",".").' '.t('GENERAL_REBEL_AWARD_WON');
	$image .= '</div>';
		
	$image  .= '<img id="raward'.$id.'" src="'.$config["content_url"].'images/rebel/rebel'.$id.'.jpg" ';
	$image .= 'width="50" height="20" style="padding:1" ';
	$image .= 'onmouseover="tooltip_show(\'rtip'.$id.'\', \'raward'.$id.'\', 5, 5);" ';
	$image .= 'onmouseout="tooltip_hide(\'rtip'.$id.'\');" />';
				
	return $image;
}

/**
 * Get rank image
 */
function warquest_rank_image($lid, $width=0, $height=0) {

	/* input */
	global $player;
	global $config;
	
	$id = ceil($lid / 8);
	if ($id == 0 ) {
		$id = 1;
	}
	if ($id>23) {
		$id=23;
	}
	
	$image  = '<img  title="'.warquest_rank($lid).'" ';
	$image .= 'src="'.$config["content_url"].'images/rank/rank'.$id.'.png" ';
	if ($width!=0) {
		$image .= 'width="'.$width.'" ';
	}
	if ($height!=0) {
		$image .= 'height="'.$height.'"';
	}
	$image .= '/>';
	
	return $image;
}

/**
 * Get flag image
 */
function warquest_flag_image($country, $width=0, $height=0) {	
	
	/*  input */
	global $config;

	if ($width==0) {
		$image =  '<img src="'.$config["content_url"].'images/flags/'.strtolower($country).'.png" title="'.
							warquest_landcode($country).'" />';
	} else {
		$image =  '<img src="'.$config["content_url"].'images/flags/'.strtolower($country).'.png" title="'.
							warquest_landcode($country).'" width="'.$width.'" height="'.$height.'"/>';
	}	
	return $image;	
}

/**
 * Get platform image
 */
function warquest_platform_image($platform) {

	/* input */
	global $config;

	$image = "";
		
	if ($platform=="Windows") {
		
		$image  = '<img src="'.$config["content_url"].'images/other/os-windows.png" title="'.$platform.'" width="22" height="22"/>';
		
	} else if ($platform=="Android") {

		$image  = '<img src="'.$config["content_url"].'images/other/os-android.png" title="'.$platform.'" width="22" height="22"/>';

	} else if ($platform=="BlackBerry") {
	
		$image  = '<img src="'.$config["content_url"].'images/other/os-blackberry.png" title="'.$platform.'" width="22" height="22"/>';
	
	} else if ($platform=="Apple") {
	
		$image  = '<img src="'.$config["content_url"].'images/other/os-apple.png" title="'.$platform.'" width="22" height="22"/>';

	} else if ($platform=="Linux") {
	
		$image  = '<img src="'.$config["content_url"].'images/other/os-linux.png" title="'.$platform.'" width="22" height="22"/>';
		
	} else if ($platform=="Symbian") {
	
		$image  = '<img src="'.$config["content_url"].'images/other/os-symbian.png" title="'.$platform.'" width="22" height="22"/>';

	} 
	
	return $image;
}

/**
 * Get mission image
 */
function warquest_mission_image($mission, $width=90, $height=65) {

	/* input */
	global $config;
	
	$image = '<div id="mtip'.$mission->mid.'" class="tooltip" align="left">';
	$image .= '<b>'.t('GENERAL_CONQUER').' '.t('MISSION_'.$mission->mid).'</b><br/>';
	
	if ($mission->mid<100) {
		$image .= t('GENERAL_PLANET').' '.t('GENERAL_PLANET_0').'<br/>';
		$filename = 'mission0.jpg';
	} else if ($mission->mid<200) {
		$image .=  t('GENERAL_PLANET').' '.t('GENERAL_PLANET_1').'<br/>';
		$filename = 'mission1.jpg';
	} else if ($mission->mid<300) {
		$image .=  t('GENERAL_PLANET').' '.t('GENERAL_PLANET_2').'<br/>';
		$filename = 'mission2.jpg';
	}	else if ($mission->mid<400) {
		$image .=  t('GENERAL_PLANET').' '.t('GENERAL_PLANET_3').'<br/>';
		$filename = 'mission3.jpg';
	}	else if ($mission->mid<500) {
		$image .=  t('GENERAL_PLANET').' '.t('GENERAL_PLANET_4').'<br/>';
		$filename = 'mission4.jpg';
	}
	
	$image .= '</div>';
		
	$image .= '<img id="image'.$mission->mid.'" src="'.$config["content_url"].'images/mission/'.$filename.'" ';
	$image .= 'width="'.$width.'" height="'.$height.'" ';		 
	$image .= 'onmouseover="tooltip_show(\'mtip'.$mission->mid.'\', \'image'.$mission->mid.'\', 5, 5);" ';
	$image .= 'onmouseout="tooltip_hide(\'mtip'.$mission->mid.'\');"';
	$image .= '/>';
			
	return $image;
}	

/**
 * Get casino image
 */
function warquest_casino_image($id, $width=90, $height=65) {

	/* input */
	global $config;
	
	$image = '<div id="ctip'.$id.'" class="tooltip" align="left">';
	$image .= '<b>'.t('CASINO_'.$id).'</b><br/>';
	$image .= '</div>';
		
	$image .= '<img id="cimage'.$id.'" src="'.$config["content_url"].'images/casino/casino'.$id.'.jpg" ';
	$image .= 'width="'.$width.'" height="'.$height.'" ';		 
	$image .= 'onmouseover="tooltip_show(\'ctip'.$id.'\', \'cimage'.$id.'\', 5, 5);" ';
	$image .= 'onmouseout="tooltip_hide(\'ctip'.$id.'\');"';
	$image .= '/>';
			
	return $image;
}

/**
 * Get bank image
 */
function warquest_bank_image($id, $width=90, $height=65) {

	/* input */
	global $config;
			
	$image = '<img src="'.$config["content_url"].'images/bank/bank'.$id.'.jpg" ';
	$image .= 'width="'.$width.'" height="'.$height.'" />';
			
	return $image;
}

/**
 * Get unit image
 */
function warquest_unit_image($unit, $count, $tip=1, $width=90, $height=65, $options="") {

	/* input */
	global $config;
	
	if ($tip == 1) {
		$image = '<div id="utip'.$count.$unit->uid.'" class="tooltip" align="left">';
		$image .= '<b>'.t('UNIT_'.$unit->uid).'</b><br/>';
		
		/* Only show attack / defense information for fighters */
		if ($unit->attack>0) {
			$image .= $unit->attack.' '.t('GENERAL_ATTACK').'<br/>';
		}
		if ($unit->defense>0) {
			$image .= $unit->defense.' '.t('GENERAL_DEFENSE').'<br/>';
		}		
		if ($unit->upkeep>0) {
			$image .= money_format2($unit->upkeep).' '.t('GENERAL_UPKEEP');
		}
		$image .= '</div>';
		
		$image .= '<img id="image'.$count.$unit->uid.'" src="'.$config["content_url"].'images/units/unit'.$unit->uid.'.jpg" ';
		$image .= 'width="'.$width.'" height="'.$height.'" ';		 
		$image .= 'onmouseover="tooltip_show(\'utip'.$count.$unit->uid.'\', \'image'.$count.$unit->uid.'\', 5, 5);" ';
		$image .= 'onmouseout="tooltip_hide(\'utip'.$count.$unit->uid.'\');" '.$options.' ';
		$image .= '/>';
		
	} else {
		
		$image  = '<img src="'.$config["content_url"].'images/units/unit'.$unit.'.jpg" ';
		$image .= 'width="'.$width.'" height="'.$height.'" '.$options.' />';
	}
	
	return $image;
}	

/**
 * Get building image
 */
function warquest_building_image($building, $count=0, $tip=1, $width=90, $height=65) {

	/*  input */
	global $config;
	
	if ($tip==1) {
		$image = '<div id="btip'.$count.$building->bid.'" class="tooltip">';
		$image .= '<b>'.t('BUILDING_'.$building->bid).'</b><br/>';
		if (isset($building->income) && ($building->income > 0)) {
			$image .= '+'.money_format1($building->income).' '.t('GENERAL_INCOME'); 
		}
		
		if (isset($building->defense) && ($building->defense > 0)) {
			$image .= '+'.$building->defense.' '.t('GENERAL_DEFENSE'); 			
			$image .= '<br/>'.loot_format(t('UNIT_GROUP_'.$building->ugid));
		}
		
		if (isset($building->energy) && ($building->energy > 0)) {
			$image .= '+'.$building->energy.' '.t('GENERAL_ENERGY'); 
		}
		
		if (isset($building->discount) && ($building->discount > 0)) {
			$image .= '+'.$building->discount.'% '.t('GENERAL_DISCOUNT');
		}
		
		if (isset($building->maintenance) && ($building->maintenance>0)) {
			$image .= '+'.$building->maintenance.'% '.t('GENERAL_MAINTENANCE');
		}
		$image .= '</div>';
	
		$image .= '<img id="bimage'.$count.$building->bid.'" src="'.$config["content_url"].'images/buildings/building'.$building->bid.'.jpg" ';
		$image .= 'width="'.$width.'" height="'.$height.'" ';	 
		$image .= 'onmouseover="tooltip_show(\'btip'.$count.$building->bid.'\', \'bimage'.$count.$building->bid.'\', 5, 5);" ';
		$image .= 'onmouseout="tooltip_hide(\'btip'.$count.$building->bid.'\');" ';
		$image .= '/>';
		
	} else {
	
		$image = '<img src="'.$config["content_url"].'images/buildings/building'.$building->bid.'.jpg" width="'.$width.'" height="'.$height.'" />';
	}
	return $image;
}

/**
 * Get stock image
 */
function warquest_stock_image($stock, $width=90, $height=65) {

	/*  input */
	global $config;
	
	if ($stock->sid < 300) {
	
		$filename = $config["content_url"].'images/stock/stock'.$stock->sid.'.jpg';
		
	} else {	
	
		$filename = $config["content_url"].'images/stock/stock0.jpg';
	}	
	
	$image = '<img src="'.$filename.'" width="'.$width.'" height="'.$height.'" />';
	return $image;
}

/*
** ---------------------------------------------------------------- 
** THE END
** ----------------------------------------------------------------
*/

?>