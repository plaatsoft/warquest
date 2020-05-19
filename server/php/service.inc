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
** ---------
** PARAMETERS
** ---------
*/

$eid = warquest_post('eid', 0);
$id = warquest_post('id', 0);

/*
** ---------
** UTILS
** ---------
*/

function xml_encode($array, $root, $indent=false, $i=0) {

	if(!$i) {
		$data = '<?xml version="1.0" encoding="utf-8"?>'.($indent?"\r\n":'').'<'.$root.'>'.($indent?"\r\n":'');	
	} else {
		$data = '';
	}
	foreach($array as $k=>$v) {
		if(is_numeric($k)) {
          $k = 'item';
      }
      $data .= ($indent?str_repeat("\t", $i):'').'<'.$k.'>';
      if(is_array($v)) {
         $data .= ($indent?"\r\n":'').xml_encode($v, $indent, ($i+1)).($indent?str_repeat("\t", $i):'');
      } else {
         $data .= $v;
      }
      $data .= '</'.$k.'>'.($indent?"\r\n":'');
   }
   if(!$i) {
      $data .= '</'.$root.'>';
   }
   return $data;
}


/*
** ---------
** ACTIONS
** ---------
*/

/**
 * Get sector data (used by map.js)
 */
function warquest_get_sector_event() {

	global $id;
	
	$query  = 'select a.x, a.y, a.cid, a.damage, ';
	$query .= '(select b.name from clan b where b.cid=a.cid ) as name ';
	$query .= 'from sector a where a.planet='.$id;	
	
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
	
	header("Content-type: application/json; charset=utf-8");
	
	echo json_encode($cell);
}

/**
 * Get clan data (used by map.js)
 */
function warquest_get_clan_event() {

	global $id;
	
	$data = warquest_db_clan($id);
	
	if ( !isset($data->cid)) {		
	
		$data = array();	
	}
	
	header("Content-type: application/json; charset=utf-8");
	
	echo json_encode($data);
}

/** 
 * Proces facebook like event 
 */
function warquest_fb_like_event() {

	global $id;
	global $config;
	
	$player = warquest_db_player($id);
	
	if ( isset($player->pid) && (warquest_db_bonus($player->pid, BONUS_FACEBOOK_LIKE)==0) ) {
	
		warquest_db_bonus_insert($player->pid, BONUS_FACEBOOK_LIKE);
	
		$player->gold += $config['gold_bonus_facebook_like'];
		warquest_db_player_update($player);
		
		$log = $player->name.' ['.$player->pid.'] facebook like bonus - '.$config['gold_bonus_facebook_like'].' gold added';
		warquest_info($log);
	}
}

/**
 * Get player data (NOT USED YET)
 */
function warquest_get_player_event() {

	global $id;
		
	$data = warquest_db_player($id);

	if ( isset($data->pid)) {	

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
	
	$xml = xml_encode($data, "player", false);
	
	/* Validate XML against XSD */
	$dom = new DOMDocument();
	$dom->loadXML($xml);
	if (!$dom->schemaValidate('service\warquest.xsd') ){
		echo "XSD Validation Error";		
	} else {
		header("Content-type: text/xml; charset=utf-8");			
		echo $xml;
	}
}

/** 
 * Get news headlines from bbc rss feed
 */
function warquest_get_headlines() { 

	$tmp = "";
	
	$xml = "http://feeds.bbci.co.uk/news/world/rss.xml?edition=uk";

	$xmlDoc = new DOMDocument();
	$xmlDoc->load($xml);

	$x=$xmlDoc->getElementsByTagName('item');
	
	for ($i=0; $i<3; $i++) {
		$item_title=$x->item($i)->getElementsByTagName('title')->item(0)->childNodes->item(0)->nodeValue;
		$item_desc=$x->item($i)->getElementsByTagName('description')->item(0)->childNodes->item(0)->nodeValue;
		
		$tmp .= '<span class="money">';
		$tmp .= $item_title;
		$tmp .= '</span> ';
		$tmp .= $item_desc;
		$tmp .= ' ';
	}
	
	echo $tmp;
}

/* 
 * Get mail notification
 */
function warquest_get_mail_notifcation() {

	/* input */
	global $player;
	global $id;
	
	$player = warquest_db_player($id);
	
	
	if ($player->comment_notification>0) {
	
		$link = warquest_link('mid='.MENU_HOME.'&sid='.PAGE_MESSAGES, warquest_image("other/email.gif").' ','mail');
		echo $link;
	}
}

/*
** ---------
** HANDLER
** ---------
*/

function warquest_service() {

	global $eid;
			
	/* Event handler */
	switch ($eid) {
		
		case EVENT_GET_SECTOR: 	
			warquest_get_sector_event();
			break;
			
		case EVENT_GET_CLAN: 	
			warquest_get_clan_event();
			break;
			
		case EVENT_FB_LIKE: 	
			warquest_fb_like_event();
			break;

		case EVENT_GET_PLAYER:
			warquest_get_player_event();
			break;
			
		case EVENT_GET_HEADLINES:
			warquest_get_headlines();
			break;
			
		case EVENT_GET_MAIL_NOTIFICATION:
			warquest_get_mail_notifcation();
			break;
	}
	
	/* Added statitics event */
	warquest_db_view_add();
}

/*
** ---------
** THE END
** ---------
*/

?>