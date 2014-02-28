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
** ------------------
** JSON functions
** ------------------
*/

function warquest_set_default_force($value) {
	
	/* input */
	global $player;
	global $config;
	
	$tmp1 = array(0,0,0,0,0,0);
	$tmp2 = json_decode($player->default_force);	

	for ($tmp=PLANET_EARTH; $tmp<=$config["max_planets"]; $tmp++) {
		if (isset($tmp2[$tmp])) {
			$tmp1[$tmp] = $tmp2[$tmp];
		}
	}
	
	$tmp1[$player->planet] = $value;	
	$player->default_force = json_encode($tmp1);
}

function warquest_get_default_force() {
	
	/* input */
	global $player;
	
	$value=0;
	$tmp = json_decode($player->default_force);
	
	if ( isset($tmp[$player->planet]) ) {
		$value = $tmp[$player->planet]; 
	}
		
	/* get default, if no value is found */
	if ($value==0) {
		
		$query = 'select ugid from unit_group where type=0 and planet='.$player->planet;
		$result = warquest_db_query($query);
		$data = warquest_db_fetch_object($result);
		$value = $data->ugid;
	}
	
	return $value;
}

function warquest_set_default_mission($value) {
	
	/* input */
	global $player;
	global $config;
	
	$tmp1 = array(0,0,0,0,0,0);
	$tmp2 = json_decode($player->default_mission);	

	for ($tmp=PLANET_EARTH; $tmp<=$config["max_planets"]; $tmp++) {
		if (isset($tmp2[$tmp])) {
			$tmp1[$tmp] = $tmp2[$tmp];
		}
	}
	
	$tmp1[$player->planet] = $value;	
	$player->default_mission = json_encode($tmp1); 
}

function warquest_get_default_mission($planet) {
	
	/* input */
	global $player;

	/* Go to Training mission */
	if ($player->lid==0) {
		return 0;
	}
	
	$value = 0;
	$tmp = json_decode($player->default_mission);
	
	if ( isset($tmp[$planet]) ) {
		$value = $tmp[$planet]; 
	}
			
	/* Get default, if no value is found */
	if ($value==0) {
		
		$query = 'select mgid from mission_group where planet='.$planet.' order by mgid';
		$result = warquest_db_query($query);
		$data = warquest_db_fetch_object($result);
		$value = $data->mgid;
	}

	return $value;
}

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

function warquest_server($label, $default) {
	
	$value = $default;
	
	if (isset($_SERVER[$label])) {
		$value = $_SERVER[$label];
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
	
	if (isset($player->pid)) {
		$message .= '|'.$player->pid;
	}
	
	if (isset($other->pid)) {
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
function warquest_attack_strength($player, $ugid, $clan) {

	/* input */
	global $config;
	
	$unit_group = warquest_db_unit_group($ugid);
	
	/* Add player unit attack strength (depending of alliance size) */
	$query =  'select a.attack, b.amount from unit a, player_unit b where ';
	$query .= 'a.uid=b.uid and b.pid='.$player->pid.' ';

	if ($unit_group->type==0) {
		$query .= 'and a.ugid in (select ugid from unit_group where type in (2,3,4) and planet='.$unit_group->planet.') ';
	} else {
		$query .= 'and a.ugid='.$ugid.' ';
	}
	
	$query .= 'order by a.attack desc';

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
	
	/* Add player skill strength */
	$skill = warquest_db_skill($player->pid);
	if (isset($skill->attack_max)) {
		$attack += ($skill->attack_max * $config['init_player_skill_step'] * $player->lid);
	}
	
	/* Add clan attack skill strength (optional) */
	if ( isset($clan->attack)) {		
		$attack += ($clan->attack * $config['init_clan_skill_step']);
	}
	
	return $attack;
}

/** 
 * Calculate defense strength of player
 */ 
function warquest_defense_strength($player, $ugid, $clan) {

	/* input */
	global $config;
	
	$defense = 0;
	$size=($player->alliance * 6);
 
	$unit_group = warquest_db_unit_group($ugid);
 
	/* Add player unit defense strength (depending on alliance size) */
	$query =  'select a.defense, b.amount from unit a, player_unit b where ';
	$query .= 'a.uid=b.uid and b.pid='.$player->pid.' ';

	if ($unit_group->type==0) {
		$query .= 'and a.ugid in (select ugid from unit_group where type in (2,3,4) and planet='.$unit_group->planet.') ';
	} else {
		$query .= 'and a.ugid='.$ugid.' ';
	}
	
	$query .= 'order by a.defense desc';
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
	
	/* Add player building defence strength */
	$query  = 'select a.defense, b.amount from building a, player_building b ';
	$query .= 'where a.bid=b.bid and b.pid='.$player->pid.' and a.defense>0 ';
	
	if ($unit_group->type==0) {
		$query .= 'and a.ugid in (select ugid from unit_group where type in (2,3,4) and planet='.$unit_group->planet.') ';
	} else {
		$query .= 'and a.ugid='.$ugid.' ';
	}
	
	$query .= 'order by a.defense desc';
	
	$result = warquest_db_query($query);
	
	while ($data = warquest_db_fetch_object($result)) {
		
		$defense += ($data->defense * $data->amount);
	}
	
	/* Add player defense skill strenght */
	$skill = warquest_db_skill($player->pid);
	if (isset($skill->defense_max)) {
		$defense += ($skill->defense_max * $config['init_player_skill_step'] * $player->lid);
	}
	
	/* Add clan defense skill strength (optional) */
	if ( isset($clan->defense) ) {		
		$defense += ($clan->defense * $config['init_clan_skill_step']);
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

/**
 * Calculate continent income
 */
function warquest_continent_income($player, $planet=0) {

	/* input */
	global $config;
	
	$query  = 'select b.mgid, sum(a.progress) as progress ';
	$query .= 'from player_mission a left join mission b on a.mid=b.mid ';
	$query .= 'left join mission_group c on b.mgid=c.mgid where a.pid='.$player->pid.' ';
	
	if ($planet>0) {
		$query .= 'and c.planet='.$planet.' ';
	}
	$query .= 'group by b.mgid';	
	
	$result = warquest_db_query($query);
			
	$income = 0;
	while ($data=warquest_db_fetch_object($result)) {		

		if ($data->progress==2400) {		
			$income += $data->mgid * $config["continent_conquer_bonus"];			
		}
	}
	return $income;	
}

/**
 * Calculate clan war income
 */
function warquest_clan_war_income($player, $planet=0) {

	/* input */
	global $config;
	
	$clan = warquest_db_player_clan($player->pid);
	
	$income = 0;	
	
	if ( (isset($clan->cid)) && ($clan->approved==1)) { 
		
		$query = 'select count(sid) as amount, planet from sector where cid='.$clan->cid.' ';
		
		if ($planet>0) {
			$query .= 'and planet='.$planet;
		} else {
			$query .= 'group by planet';
		}
		
		$result = warquest_db_query($query);
		while ($data = warquest_db_fetch_object($result)) {
			
			$income += $data->amount * 10000 * $player->lid * $data->planet;
		}
	}

	return $income;	
}

/**
 * Calculate building income
 */

function warquest_building_income($player, $planet=0) {

	/* Calculate income */
	$query  = 'select a.income, c.amount from building a left join building_group b on a.bgid=b.bgid, ';
	$query .= 'player_building c where a.bid=c.bid and c.pid='.$player->pid.' and a.income>0 ';
	
	if ($planet>0) {
		$query .= 'and b.planet='.$planet;	
	}
	
	$result = warquest_db_query($query);

	$income = 0;	
	while ($data = warquest_db_fetch_object($result)) {
		$income += ($data->income * $data->amount);	
	}
	
	return $income;
}

/**
 * Calculate unit cost
 */
function warquest_unit_cost($player, $planet=0) {

	$query =  'select a.upkeep, b.amount from unit a, player_unit b where ';
   $query .= 'a.uid=b.uid and b.pid='.$player->pid.' ';	
	$query .= 'and a.ugid in (select ugid from unit_group where type!=0 and type!=6 ';
	
	if ($planet>0) {
		$query.= 'and planet='.$planet.' ';
	} 
	$query .= ')';
		
	$result = warquest_db_query($query);

	$cost = 0;	
	while ($data = warquest_db_fetch_object($result)) {
	
		$cost += ($data->upkeep * $data->amount);	
	}
	
	return $cost;	
}

/**
 * Calculate citizens cost
 */
function warquest_citizens_cost($player, $planet=0) {

	$query =  'select a.upkeep, b.amount from unit a, player_unit b where ';
   $query .= 'a.uid=b.uid and b.pid='.$player->pid.' ';	
	$query .= 'and a.ugid in (select ugid from unit_group where type=6 ';
	
	if ($planet>0) {
		$query.= 'and planet='.$planet.' ';
	} 
	$query .= ')';
		
	$result = warquest_db_query($query);

	$cost = 0;	
	while ($data = warquest_db_fetch_object($result)) {
	
		$cost += ($data->upkeep * $data->amount);	
	}
	
	return $cost;	
}

/**
 * Calculate hourly income of player
 */
function warquest_netto_income($player) {
		 
	/* Calculate building income */
	$income  = warquest_building_income($player);

	/* Calculate mission continent income */
	$income += warquest_continent_income($player);

	/* Calculate clan war sector income */
	$income += warquest_clan_war_income($player);
	
	/* Calculate unit cost */
	$income -= warquest_unit_cost($player);

	/* Calculate citizens cost */
	$income -= warquest_citizens_cost($player);
	
	/* update player money step */
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
	
		if ($player->lid >= 289) {
			$level = 280;
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
	global $output;
	
	/* 20 procent chance to win a loot. */
	if (rand(1,5)==1) 
	{		
		$query  = 'select a.uid, a.gold, a.defense, a.attack, a.upkeep from unit a ';
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
						
			case PLANET_MERCURY:  
						$min = 200;
						$max = 250;
						break;
						
			case PLANET_NEPTUNE:  
						$min = 250;
						$max = 300;
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
		
				if ($output->format=="html") {
				
					$message  = '<br/>'.loot_format(t('MISSION_LOOT_WON')).'<br/>';		
					$message .= '<table>';
					$message .= '<tr>';
					$message .= '<td width="90">';
					$message .= warquest_unit_image($unit, 1001);		
					$message .= '<br/><center>'.$amount.'x</center>';
					$message .= '<td>';
					$message .= '</tr>';
					$message .= '</table>';
					
				} else {
				
					$message  = t('MISSION_LOOT_WON').': '.$amount.' '.t('UNIT_'.$unit->uid).'.';		
				}
	
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
	global $ssid;
	global $uid;
			
	$page ="";

	if ($total>$limit) {

		if ($top==0) {
			$page .= '<div class="spacer"/></div>';
		}
		$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&ssid='.$ssid.'&uid='.$uid.'&offset=0'.$more, t('LINK_FIRST'),'first');
		$page .= '&nbsp;';

		$value = $offset - $limit;
		if ($value<0) {
			$value=0;
		}
		$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&ssid='.$ssid.'&uid='.$uid.'&offset='.$value.$more, t('LINK_PREVIOUS'), 'prev');
		$page .= '&nbsp;';
	
		$value = $offset + $limit;
		if ($value>=$total) {
			$value = $total - $limit;
		}	
		$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&ssid='.$ssid.'&uid='.$uid.'&offset='.$value.$more, t('LINK_NEXT'), 'next');
		$page .= '&nbsp;';
	
		$value = $total - $limit;
		$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&ssid='.$ssid.'&uid='.$uid.'&offset='.$value.$more, t('LINK_LAST'), 'last');	
		
		$page .= '<br/>';
		
		if ($top==1) {
			$page .= '<div class="spacer"/></div>';
		}
	}
	return $page;
}

/** 
 * Table data page control navigation.
 */
function warquest_page_control_reverse($offset, $limit, $total, $top=0, $more="") {

	/* input */
	global $mid;
	global $sid;
	global $ssid;
	global $uid;
			
	$page ="";

	if ($total>$limit) {

		if ($top==0) {
			$page .= '<div class="spacer"/></div>';
		}
		$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&ssid='.$ssid.'&uid='.$uid.'&offset='.$total.$more, t('LINK_FIRST'),'first');
		$page .= '&nbsp;';

		$value = $offset + $limit;
		if ($value>=$total) {
			$value = $total - $limit;
		}	
			
		$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&ssid='.$ssid.'&uid='.$uid.'&offset='.$value.$more, t('LINK_PREVIOUS'), 'prev');
		$page .= '&nbsp;';
		$value = $offset - $limit;
		if ($value<0) {
			$value=0;
		}
		
		$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&ssid='.$ssid.'&uid='.$uid.'&offset='.$value.$more, t('LINK_NEXT'), 'next');
		$page .= '&nbsp;';
	
		$value = $total - $limit;
		$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&ssid='.$ssid.'&uid='.$uid.'&offset=0'.$more, t('LINK_LAST'), 'last');	
		
		$page .= '<br/>';
		
		if ($top==1) {
			$page .= '<div class="spacer"/></div>';
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
	
	$values = array(1, 2, 5, 10, 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000, 50000, 100000, 500000);

	$page  = '<div class="dropdown dropdown-dark">';	
	$page .='<select id="amount" name="amount" class="dropdown-select">';
	
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
	$page.='</div>';
	  
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
 * Convert mysql datatime to XML format.
 */
function warquest_xml_date($value) { 

	list($date, $time) = preg_split('/ /', $value);
	list($year, $month, $day) = preg_split('/-/', $date); 
	
	/* Prevent XSD validation error conform ISO 8601 */
	if ($year==0) {
		$year="1900";
	}
   if ($day==0) {
		$day="01";
	}
	if ($month==0) {
		$month="01";
	}
	return $year.'-'.$month.'-'.$day.'T'.$time;
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
	global $output;

	/* output */
	global $page;
	
	if (($output->format=="html") && (warquest_db_query_pattern($player, PATTERN_SOUND)==1)) {
	
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
	global $output;
	
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
		
		$query = 'select uid, gold, defense, attack, upkeep from unit where lid='.$player->lid;
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
			$tmp .= '<span class="subparagraph">'.t('UNIT_'.$data->uid).'</span><br/>';
			if ($data->attack > 0) {
				$tmp .= strength_format($data->attack).' '.t('GENERAL_ATTACK').' - ';
			}
			if ($data->defense > 0) {
				$tmp .= strength_format($data->defense).' '.t('GENERAL_DEFENSE');
			}
			if ($data->upkeep > 0) {
				$tmp .= '<br/>'.t('GENERAL_UPKEEP').': '.money_format1($data->upkeep);
			}
			$tmp .= '</td>';
			
			$tmp .= '</tr>';
			$feature = 1;
		}
		
		$query = 'select ugid, bid, income, gold, energy, defense, maintenance, discount from building where lid='.$player->lid;
		$result = warquest_db_query($query);
		
		while ($data=warquest_db_fetch_object($result)) { 
			$tmp .= '<tr>';
			$tmp .= '<td width="120">';		
			$tmp .= warquest_building_image($data, 0, 1);			
			$tmp .= '</td>';
		
			$tmp .= '<td width="130">';	
			$tmp .= t('GENERAL_NEW_BUILDING');
			$tmp .= '</td>';
			
			$tmp .= '<td width="250"><span class="subparagraph">'.t('BUILDING_'.$data->bid).'</span><br/>' ;
			if ($data->income > 0) {
				$tmp .= t('GENERAL_INCOME').': '.dollar_format($data->income);
			} else if ($data->defense > 0) {
				$tmp .= t('GENERAL_DEFENSE').': +'.strength_format($data->defense);
			} else if ($data->energy > 0) {
				$tmp .= t('GENERAL_ENERGY').': +'.energy_format($data->energy);
			} else if ($data->maintenance > 0) {
				$tmp .= t('GENERAL_MAINTENANCE').': +'.maintenance_format($data->maintenance);
			} else if ($data->discount > 0) {
				$tmp .= t('GENERAL_DISCOUNT').': +'.discount_format($data->discount);			
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
			$tmp .= '<span class="subparagraph">'.t('GENERAL_CONQUER').' '.t('MISSION_'.$data->mid).'</span><br/>';
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
		
		$output->popup .= warquest_box("info", $message, $link);
		
		$returnValue = 1;
	}
	
	return $returnValue;
}

/** 
 *  Detect when player wins a battle award
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
 * Detect when player wins a battle award
 */
function warquest_battle_award_won($player) {
		
	/* input */
	global $config;
	
		/* output */
	global $output;
	
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
		
		$output->popup .= warquest_box("info", $message, $link);
	}
}

/** 
 * Detect when player wins a bounty award
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
 * Detect when player wins a bounty award
 */
function warquest_bounty_award_won($player) {
		
	/* input */
	global $config;
	
	/* output */
	global $output;
	
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
		$output->popup .= warquest_box("info", $message, $link);
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
	global $output;
	
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
		$output->popup .= warquest_box("info", $message, $link);
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
			
			warquest_db_player_mission_update($other->pid, $data->mid, 0, 0, $data->part);
			
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
		
			/* Dirty hack to convert ouput string, sorry :( */
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

	$tmp = '<input type="checkbox" name="'.$name.'" value="'.$value.'" ';
	if ($checked==1) {
		$tmp .= ' checked="checked" ';
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
 * Get HTML clan war map
 */
function warquest_ui_clan_war_map($player, $planet, $mode) {
		
	/* input */
	global $mid;
	global $sid;
	global $config;	
	
	$page = "";
	
	$data2 = warquest_db_player_clan($player->pid);
	
	$query  = 'select a.sid, a.x, a.y, a.cid, a.damage, ';
	$query .= '(select b.name from clan b where b.cid=a.cid ) as name ';
	$query .= 'from sector a where a.planet='.$planet;	
	$result = warquest_db_query($query);
		
	$cell = array();
		
	/* Calculate cells with can be attack by clan */
	$count=0;
	while ($data = warquest_db_fetch_object($result)) {		
		
		$owner=0;
		if ( isset($data2->cid) && ($data->cid == $data2->cid)) {
			$owner=2;
		} else if ($data->cid>0) {
			$owner=1;
		} 
		
		$cell[$data->x][$data->y]['owner'] = $owner;
		$cell[$data->x][$data->y]['damage'] = $data->damage;
		$cell[$data->x][$data->y]['name'] = $data->name;
	}
	
	for ($y=0; $y<15; $y++) {
			
		for ($x=0; $x<5; $x++) {
			
			if ($cell[$x][$y]['owner']==2) {
			
				$count++;
		
				if (($y % 2)==1) {
				
					if ( (($x-1)>=0) && (($y-1)>=0) && ($cell[$x-1][$y-1]['owner']<2) ) {
						$cell[$x-1][$y-1]['owner']=3;
					} 
					if ( (($x-1)>=0) && (($y+1)<15) && ($cell[$x-1][$y+1]['owner']<2) ) {	
						$cell[$x-1][$y+1]['owner']=3;
					} 	
					if ( (($y+2)<15) && ($cell[$x][$y+2]['owner']<2) ) {	
						$cell[$x][$y+2]['owner']=3;
					} 
					if ( (($y+1)<15) && ($cell[$x][$y+1]['owner']<2) ) {	
						$cell[$x][$y+1]['owner']=3;
					} 
					if ( (($y-1)>=0) && ($cell[$x][$y-1]['owner']<2) ) {	
						$cell[$x][$y-1]['owner']=3;
					} 
					if ( (($y-2)>=0) && ($cell[$x][$y-2]['owner']<2) ) {	
						$cell[$x][$y-2]['owner']=3;
					}
					
				} else {
					
					if ( (($y-1)>=0) && ($cell[$x][$y-1]['owner']<2)) {
						$cell[$x][$y-1]['owner']=3;
					} 
					if ( (($y+1)<15) && ($cell[$x][$y+1]['owner']<2) ) {	
						$cell[$x][$y+1]['owner']=3;
					} 	
					if ( (($y+2)<15) && ($cell[$x][$y+2]['owner']<2) ) {	
						$cell[$x][$y+2]['owner']=3;
					} 
					if ( (($y-2)>=0) && ($cell[$x][$y-2]['owner']<2) ) {	
						$cell[$x][$y-2]['owner']=3;
					} 
					if ( (($x+1)<5) && (($y-1)>=0) && ($cell[$x+1][$y-1]['owner']<2) ) {	
						$cell[$x+1][$y-1]['owner']=3;
					} 
					if ( (($x+1)<5) && (($y+1)<15) && ($cell[$x+1][$y+1]['owner']<2) ) {	
						$cell[$x+1][$y+1]['owner']=3;
					}
				}
			}
		}
	}

	$tmp = "";
	for ($y=0; $y<15; $y++) {
		
		for ($x=0; $x<5; $x++) {
		
			$tmp .= $x.'-'.$y.'-'.$cell[$x][$y]['name'].'-'.$cell[$x][$y]['owner'].'-';		
			$tmp .= (($cell[$x][$y]['damage']/$config["max_sector_damage"])*100).',';
		}
	}
		
	$width = 483;
	$height = 300;
	
	$page .= '<center>';
	$page .= '<img src="map.php?planet='.$planet.'&data='.$tmp.'" width="'.$width.'" height="'.$height.'" usemap="#map">';	
	$page .= '<map name="map">';
	
	$query  = 'select a.sid, a.x, a.y, a.cid, a.mid from sector a where a.planet='.$planet;		
	$result = warquest_db_query($query);			
	while ($data=warquest_db_fetch_object($result)) {			
		
		$tmp = "";
		if ($data->mid > 0) {
			$tmp = t('MISSION_'.$data->mid);
		}
		if (($count==0) || ($cell[$data->x][$data->y]['owner']==3)) {
			$page .= '<area shape="poly" coords="'.calcPologon($data->x,$data->y).'" title="'.$tmp.'" ';
			if ($mode == true) {
				$page .= 'href="javascript:link(\'';
				$page .= warquest_token('mid='.$mid.'&sid='.$sid.'&uid='.$data->sid.'&eid='.EVENT_BATTLE_CLAN_WAR);
				$page .= '\');"';
			}
			$page .= '/>';
		}		
	}
	$page .= '</map>';	
		
	return $page;
}
		
		
/**
 * Get HTML mission map
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
			$page .= '<img src="planet.php?planet='.$planet.'&data='.$tmp.'" width="'.$width.'" height="'.$height.'" title="'.t('GENERAL_PLANET_1').'" usemap="#map">';	
			if (($pid==$player->pid) && ($player->lid>1) && ($player->holiday_date <= date("Y-m-d H:i:s", time()))) {
				$page .= '<map name="map">';		
				$page .= '<area shape="rect" coords="200,0,250,90" title="'.t('MISSION_GROUP_1').'" href="javascript:link(\''.warquest_token('mid='.MENU_MISSIONS.'&sid='.PAGE_MISSION_PLAYER.'&ssid=1').'\');" />';
				$page .= '<area shape="rect" coords="30,0,190,110" title="'.t('MISSION_GROUP_2').'" href="javascript:link(\''.warquest_token('mid='.MENU_MISSIONS.'&sid='.PAGE_MISSION_PLAYER.'&ssid=2').'\');" />';
				$page .= '<area shape="rect" coords="80,130,160,250" title="'.t('MISSION_GROUP_3').'" href="javascript:link(\''.warquest_token('mid='.MENU_MISSIONS.'&sid='.PAGE_MISSION_PLAYER.'&ssid=3').'\');" />';
				$page .= '<area shape="rect" coords="180,90,260,230" title="'.t('MISSION_GROUP_4').'" href="javascript:link(\''.warquest_token('mid='.MENU_MISSIONS.'&sid='.PAGE_MISSION_PLAYER.'&ssid=4').'\');" />';	
				$page .= '<area shape="rect" coords="250,0,500,70" title="'.t('MISSION_GROUP_5').'" href="javascript:link(\''.warquest_token('mid='.MENU_MISSIONS.'&sid='.PAGE_MISSION_PLAYER.'&ssid=5').'\');" />';
				$page .= '<area shape="rect" coords="320,70,400,115" title="'.t('MISSION_GROUP_7').'" href="javascript:link(\''.warquest_token('mid='.MENU_MISSIONS.'&sid='.PAGE_MISSION_PLAYER.'&ssid=7').'\');" />';
				$page .= '<area shape="rect" coords="390,150,500,250" title="'.t('MISSION_GROUP_8').'" href="javascript:link(\''.warquest_token('mid='.MENU_MISSIONS.'&sid='.PAGE_MISSION_PLAYER.'&ssid=8').'\');" />';	
				$page .= '<area shape="rect" coords="250,70,300,130" title="'.t('MISSION_GROUP_9').'" href="javascript:link(\''.warquest_token('mid='.MENU_MISSIONS.'&sid='.PAGE_MISSION_PLAYER.'&ssid=9').'\');" />';
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
					$page .= 'href="javascript:link(\''.warquest_token('mid='.MENU_MISSIONS.'&sid='.PAGE_MISSION_PLAYER.'&ssid='.$data->mgid.'&anchor='.$data->mid).'\');" />';
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
 * Get HTML background selector
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
						 "8" =>  t('BACKGROUND_8'));
	
	$page  = '<div class="dropdown dropdown-dark">';
	$page .='<select id="mybackground" name="mybackground" class="dropdown-select">';
		
	foreach ($array as $key => $value) {
	
		$page.='<option value="'.$key.'" ';
		
		if ($id == $key) {
			$page .= ' selected="selected"';
		}
		
		$page .= '>'.$value.'</option>';
	}
	$page.='</select>';
	$page.='</div>';
	
	return $page;
}

/**
 * Get HTML country selector
 */
function warquest_ui_country($tag, $id, $readonly) {
	
	/* input */
	global $landcode;
		
	$page  = '<div class="dropdown dropdown-dark">';	
	$page .='<select id="'.$tag.'" name="'.$tag.'" class="dropdown-select" ';
	if ($readonly) {
		$page .= 'disabled="true" ';
	}
	$page .= ' >'; 
	
	$id = strtolower($id);
	
	foreach ($landcode as $key => $value) {
	
		$page.='<option value="'.$key.'"';
		
		if ($id == $key) {
			$page .= ' selected="selected"';
		}
		$page .= '>'.$value.'</option>';
	}
		
	$page.='</select>';
	$page.='</div>';
	  
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

	$page  = '<div class="dropdown dropdown-dark">';
	$page .='<select id="'.$tag.'" name="'.$tag.'" class="dropdown-select">';
	
	foreach ($array as $key => $value) {
	
		$page.='<option value="'.$key.'"';
		
		if ($id == $key) {
			$page .= ' selected="selected"';
		}
		
		$page .= '>'.$value.'</option>';
	}
	
	$page.='</select>';
	$page.='</div>';
	  
   return $page;
}

/**
 * Get HTML menu bar
 */
function warquest_ui_menu($mid, $sid, $ssid, $label, $active_id, $notification=0) {
   
	$menu = '<li>';
		
	if (($mid==$active_id) || ($sid==$active_id)) {
		$menu .= '<div class="active">';
	} 	
	
	$menu .= warquest_link('mid='.$mid.'&sid='.$sid.'&ssid='.$ssid, $label, strtolower($label));
	
	if (($mid==$active_id) || ($sid==$active_id)) {
		$menu .= '</div>';
	} 
	
	$menu .= '</li>';
	
	if ( $notification > 0 ) {
		$menu .= '<div class="notification">'.$notification.'</div>';	
	}

	return $menu;
}

/**
 * Get HTML submenu bar
 */
function warquest_ui_submenu($mid, $sid, $ssid, $label, $active_id) {
   
	$menu = '<li>';
	
	if (($ssid==$active_id)) {
		$menu .= '<div class="active">';
	} 
	
	$menu .= warquest_link('mid='.$mid.'&sid='.$sid.'&ssid='.$ssid, $label, strtolower($label));
	
	if (($ssid==$active_id)) {
		$menu .= '</div>';
	} 
	
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
function warquest_box($title, $content, $link="") {
	
	global $output;
	
	if ($output->format=="html") {
	
		$message = '<div class="box">';
	
		if (strlen($link)>0) {
			$message .= '<div class="right">';
			$message .= $link;
			$message .= '</div>'; 
		} 
	
		if ($title=="info") {
			$message .= '<div class="paragraph"><span class="info">'.t('BOX_INFO').'</span></div>';
		} else if ($title=="warning") {
			$message .= '<div class="paragraph"><span class="warning">'.t('BOX_WARN').'</span></div>';
		} else {
			$message .= '<div class="paragraph">'.$title.'</div>';
		} 
		$message .= $content;
		
		$message .= '</div>';	
		
	} else {
	
		$message = strtoupper($title).': '.$content;
		
	}
	
	return $message;
}
	
/**
 * Show HTML box with icon
 */	
function warquest_box_icon($title, $content, $link="") {
	
	global $output;
	
	if ($output->format=="html") {
	
		$message = '<div class="box">';
		
		$message .= '<table>';
		$message .= '<tr>';
	
		if ($title=="info") {
			$message .= '<td width="70" valign="top">'; 
			$message .= warquest_image('other/info.png',' width="64" height="64" ');
			$message .= '</td>';
		
			$message .= '<td width="430">';
			$message .= '<div class="paragraph"><span class="info">'.t('BOX_INFO').'</span></div>';
			
		} else if ($title=="warning") {
			$message .= '<td width="70" valign="top">'; 
			$message .= warquest_image('other/warning.png',' width="64" height="64" ');
			$message .= '</td>';
		
			$message .= '<td width="430">';
			$message .= '<div class="paragraph"><span class="warning">'.t('BOX_WARN').'</span></div>';
	
		} else if ($title=="error") {
			$message .= '<td width="70" valign="top">'; 
			$message .= warquest_image('other/error.png',' width="64" height="64" ');
			$message .= '</td>';
			
			$message .= '<td width="430">';
			$message .= '<div class="paragraph"><span class="error">'.t('BOX_ERROR').'</span></div>';
				
		} else if ($title=="classified") {
			$message .= '<td width="70" valign="top">'; 
			$message .= warquest_image('other/classified.png',' width="64" height="64" ');
			$message .= '</td>';
			
			$message .= '<td width="430">';
			$message .= '<div class="paragraph"><span class="warning">CLASSIFIED</span></div>';
		
		} else { 
	
			$message .= '<td width="430">'; 
			$message .= '<div class="paragraph">'.$title.'</div>';
		} 
	
		$message .= $content;
		$message .= '</td>';
		
		if (strlen($link)>0) {
			$message .= '</td>';
			$message .= '<td width="100" align="right" valign="top">';
			$message .= $link;
			$message .= '</td>';
		}
		
		$message .= '</tr>';
		$message .= '</table>';
		$message .= '</div>';		
		
	} else {
		
		$message = strtoupper($title).': '.$content;
		
	}
		
	return $message;
}

/**
 * HTML header
 */
function warquest_ui_header() {
   
	/* input */
	global $config;
	global $mid;
   global $sid;
	global $browser;
	global $player;
	global $session;
	global $version;
	global $output;
	
	$page = '';	
	
	//$page  .= '<!DOCTYPE html>';
	$page .= '<html>';
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
	$page .= '<link href="'.$config["content_url"].'css/general9.css" rel="stylesheet" type="text/css" />';
	
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
	
	/* Detect Apple devices */
	if (preg_match("/iPad/", $browser)) {
		$page .= '<link href="'.$config["content_url"].'css/apple.css" rel="stylesheet" type="text/css" />';
	}
	
	/* Detect Apple devices */
	if (preg_match("/iPod/", $browser)) {
		$page .= '<link href="'.$config["content_url"].'css/apple.css" rel="stylesheet" type="text/css" />';
	}
	
	/* Detect Apple devices */
	if (preg_match("/iPhone/", $browser)) {
		$page .= '<link href="'.$config["content_url"].'css/apple.css" rel="stylesheet" type="text/css" />';
	}
	
	/* Add custom background image */
	if (isset($player->background)) {	
		$background = $player->background;
	} else {
		$background = $config["default_background"];		
	}
	
	$page .= '<style type="text/css">';
	if ($background == 0 ) {
		$page .= 'body { background: black }';			
	} else {	
		$page .= 'body { background: black url("'.$config["content_url"].'images/background/background-'.$background.'.jpg") 0 0 repeat fixed; }';				
	}
	$page .= '</style>';
	
	if ($background == 2 ) {
		$page .= '<link href="'.$config["content_url"].'css/style'.$background.'.css" rel="stylesheet" type="text/css" />';
	}
	
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
	$page .= '<title>'.$config["applName"];		
	if ( isset($output->title) ) {
		$page .= ' - '.$output->title;
	}
	$page .= '</title>';

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
		
	$page  = '<div class="header">'; 

	$page .= '<div class="box">'; 
	$page .= '<div class="banner">'; 
	$page .= '<table>';
	
	$page .= '<tr>';
	
	/* First line */
	$page .= '<td valign="top" width="185">';
	$page .= warquest_link_hidden('mid='.MENU_PLAYERS.'&sid='.PAGE_BEST_PLAYER, t('STATUS_CASH')).': ';
	$page .= '<span class="value" id="moneyvalue"></span>';
	
	$tmp = "";
	if (($player->money_step!=0) && ($player->holiday_date <= date("Y-m-d H:i:s", time()))) {	
		$tmp .= '<br/>';
		$tmp .= '<span class="timer">'.money_format1($player->money_step).' in </span>';
		$tmp .= '<span class="timer" id="moneycountdown"></span> ';
	}
	$page .= $tmp;
	
	if (strlen($tmp)>0) {
		$page .= ' ';
	}
	
	if ($player->gold>0) {
		$page .= '<span class="timer"><span class="gold">'.number_format($player->gold,0,",",".").'</span></span>';
	}
	$page .= '<br/>';
	$page .= '</td>';
	
	$page .= '<td valign="top" width="195">';
	$page .= warquest_link_hidden('mid='.MENU_PLAYERS.'&sid='.PAGE_BEST_COUNTRY, t('STATUS_EXP')).': ';
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
	
	$page .= '<td valign="top" width="120">';
	$page .= warquest_link_hidden('mid='.MENU_FORUMS.'&sid='.PAGE_FORUM, t('STATUS_LEVEL')).': ';
	$page .= '<span class="value level">'.$player->lid.'</span>';
	if ($player->lid>0) {
		$page .= '<br/><span class="timer">'.t('STATUS_ALLIANCE_SIZE').': ';
		$page .= alliance_format($player->alliance).' / '.($player->lid*$config["max_ally_factor"]).'</span>';
	}
	$page .= '</td>';
	$page .= '</tr>';	
	
	/* Second line */
	$page .= '<tr>';	
	$page .= '<td colspan="3">';
	$page .= '<div class="spacer"></div>';
	$page .= '</td>';
	$page .= '</tr>';	
	
	/* third line */	
	$page .= '<tr>';	
	$page .= '<td valign="top">';
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
		
	$page .= '<td valign="top">';
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
	
	$page .= '<div class="content">';
	
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
						
			case 7: $page .= '<script type="text/javascript" src="js/snow.js"></script>';
					   break;

			case 8: $page .= '<script type="text/javascript" src="js/fireworks.js"></script>';
					   break;
		}
	}
	
	if ( ($config["default_background"]!=1) && (!isset($player->background)) ) {
		switch ($config["default_background"]) {
						
			case 7: $page .= '<script type="text/javascript" src="js/snow.js"></script>';
					   break;

			case 8: $page .= '<script type="text/javascript" src="js/fireworks.js"></script>';
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
	
		$value = warquest_link('mid='.MENU_PLAYERS.'&sid='.PAGE_CLAN_PROFILE.'&cid='.$clan->cid, $clan->name, "", $clan->slogan);
	}
	
	return $value;
}

/**
 * Get player html format
 */
function player_format($pid, $name, $country, $size=0) {

	global $mid;
	global $output;
	
	if ($output->format=="xml") {
		return $name;
	} else if ($size==0) {
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
 * Get money html negative format
 */
function money_format_negative($value) {
   
	return '<span class="negative">'.number_format($value,0,",",".").'</span>';
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
 * Get strength html format
 */
function strength_format($value) {
   
	return '<span class="strength">'.number_format($value,0,",",".").'</span>';
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

/**
 * Function validate email domein name
 * @return true or false
 */
function validate_dns($email) {

	$part = explode("@",$email);
	
	if(checkdnsrr($part[1],"MX")){
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
			
	$image  = '<img id="planet'.$id.'" src="'.$config["content_url"].'images/planet/planet'.$id.'a.png" title="'.t('GENERAL_PLANET_'.$id).'" width="32" height="32" />';	
	
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
	
	$query  = 'select b.planet from mission a, level b where a.lid=b.lid and a.mid='.$mission->mid;
	$result = warquest_db_query($query);
	$data   = warquest_db_fetch_object($result);	
	
	$image = '<div id="mtip'.$mission->mid.'" class="tooltip" align="left">';
	$image .= '<b>'.t('GENERAL_CONQUER').' '.t('MISSION_'.$mission->mid).'</b><br/>';
	$image .= t('GENERAL_PLANET').' '.t('GENERAL_PLANET_'.$data->planet).'<br/>';		
	$image .= '</div>';
	$image .= '<img id="image'.$mission->mid.'" src="'.$config["content_url"].'images/planet/mission'.$data->planet.'a.jpg" ';
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
		
		if (isset($unit->gold) && ($unit->gold>0)) {
			$image .= ' class="goldimage" ';
			$width -=2;
			$height -=2;
		}
		
		$image .= 'width="'.$width.'" height="'.$height.'" ';		 
		$image .= 'onmouseover="tooltip_show(\'utip'.$count.$unit->uid.'\', \'image'.$count.$unit->uid.'\', 5, 5);" ';
		$image .= 'onmouseout="tooltip_hide(\'utip'.$count.$unit->uid.'\');" '.$options.' ';
		$image .= '/>';
		
	} else {
		
		if ( isset($unit->uid) ) {
			$uid=$unit->uid;
		} else {
			$uid=$unit;
		}
		
		$image  = '<img src="'.$config["content_url"].'images/units/unit'.$uid.'.jpg" ';

		if (isset($unit->gold) && ($unit->gold>0)) {
			$image .= ' class="goldimage" ';
			$width -=2;
			$height -=2;
		}
		
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
		
		if (isset($building->gold) && ($building->gold>0)) {
			$image .= ' class="goldimage" ';
			$width -=2;
			$height -=2;
		}
		
		$image .= 'width="'.$width.'" height="'.$height.'" ';	 
		
		$image .= 'onmouseover="tooltip_show(\'btip'.$count.$building->bid.'\', \'bimage'.$count.$building->bid.'\', 5, 5);" ';
		$image .= 'onmouseout="tooltip_hide(\'btip'.$count.$building->bid.'\');" ';
		$image .= '/>';
		
	} else {
	
		$image = '<img src="'.$config["content_url"].'images/buildings/building'.$building->bid.'.jpg"  ';
		
		if (isset($building->gold) && ($building->gold>0)) {
			$image .= ' class="goldimage" ';
			$width -=2;
			$height -=2;
		}
		$image .= 'width="'.$width.'" height="'.$height.'" />';
		
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