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
**  All copyrights reserved (c) 1996-2016 PlaatSoft
*/

/*
** ---------------------------------------------------------------- 
** RSS Feed
** ---------------------------------------------------------------- 
*/

class RSSFeed {

	var $channel_url;
	var $channel_title;
	var $channel_description;
	var $channel_lang;
	var $channel_copyright;
	var $channel_date;
	var $channel_creator;
	var $channel_subject;

	var $image_url;
	var $items = array();
	var $nritems;

	function RSSFeed() {
		$this->nritems=0;
		$this->channel_url='';
		$this->channel_title='';
		$this->channel_description='';
		$this->channel_lang='';
		$this->channel_copyright='';
		$this->channel_date='';
		$this->channel_creator='';
		$this->channel_subject='';
		$this->image_url='';
	}

	function SetChannel($url, $title, $description, $lang, $copyright, $creator, $subject) {
		$this->channel_url=$url;
		$this->channel_title=$title;
		$this->channel_description=$description;
		$this->channel_lang=$lang;
		$this->channel_copyright=$copyright;
		$this->channel_date=date("r", strtotime(date("Y-m-d H:i:s")));
		$this->channel_creator=$creator;
		$this->channel_subject=$subject;
	}

	function SetImage($url) {
		$this->image_url=$url;
		}

	function SetItem($url, $title, $description, $datum) {
		$this->items[$this->nritems]['url']=$url;
		$this->items[$this->nritems]['title']=$title;
		$this->items[$this->nritems]['description']=$description;
		$this->items[$this->nritems]['date']=$datum;
		$this->nritems++;   
	}

	function Output() {
		$output = '<?xml version="1.0" encoding="UTF-8"?>'; 

		$output .= '<rss version="2.0" '; 
		$output .= "\r\n";
		$output .= 'xmlns:content="http://purl.org/rss/1.0/modules/content/" '; 
		$output .= "\r\n";
		$output .= 'xmlns:wfw="http://wellformedweb.org/CommentAPI/" '; 
		$output .= "\r\n";
		$output .= 'xmlns:dc="http://purl.org/dc/elements/1.1/" '; 
		$output .= "\r\n";
		$output .= 'xmlns:atom="http://www.w3.org/2005/Atom" '; 
		$output .= "\r\n";
		$output .= 'xmlns:sy="http://purl.org/rss/1.0/modules/syndication/" '; 
		$output .= "\r\n";
		$output .= 'xmlns:slash="http://purl.org/rss/1.0/modules/slash/" >';
		$output .= "\r\n";
		$output .= "\r\n";
		
		$output .= '<channel>'; 
		$output .= "\r\n";
		$output .= '<title>'.$this->channel_title.'</title>'; 
		$output .= "\r\n";
		$output .= '<atom:link href="'.$this->channel_title.'" rel="self" type="application/rss+xml" />';
		$output .= "\r\n";
		$output .= '<link>'.$this->channel_url.'/rss.php</link>'; 
		$output .= "\r\n";
		$output .= '<description>'.$this->channel_description.'</description>'; 
		$output .= "\r\n";
		$output .= '<language>en-us</language>'; 
		$output .= "\r\n";
		$output .= '<pubDate>'.$this->channel_date.'</pubDate>'; 
		$output .= "\r\n";
		$output .= '<lastBuildDate>'.$this->channel_date.'</lastBuildDate>'; 
		$output .= "\r\n";
		$output .= '<docs>'.$this->channel_url.'</docs>'; 
		$output .= "\r\n";
		$output .= '<sy:updatePeriod>hourly</sy:updatePeriod>';
		$output .= "\r\n";
		$output .= '<sy:updateFrequency>1</sy:updateFrequency>';
		$output .= "\r\n";
		$output .= '<generator>WarQuest</generator>'; 
		$output .= "\r\n";
		$output .= '<managingEditor>info@warquest.nl</managingEditor>'; 
		$output .= "\r\n";
		$output .= '<webMaster>info@warquest.nl</webMaster>'; 
		$output .= "\r\n";
		$output .= "\r\n";
		
		$output .= '<image>';
		$output .= "\r\n";
		$output .= '<url>'.$this->channel_url.'/images/WarQuest.jpg</url>';
		$output .= "\r\n";
		$output .= '<title>'.$this->channel_title.'</title>'; 
		$output .= "\r\n";
		$output .= '<link>'.$this->channel_url.'/rss.php</link>';
		$output .= "\r\n";
		$output .= '</image>';
		$output .= "\r\n";

		for($k=0; $k<$this->nritems; $k++) {
	
			$output .= "\r\n";
			$output .= '<item>';
			$output .= "\r\n";
			$output .= '<title>'.$this->items[$k]['title'].'</title>';
			$output .= "\r\n";
			$output .= '<link>'.$this->items[$k]['url'].'</link>';
			$output .= "\r\n";
			$output .= '<guid isPermaLink="false">'.$this->items[$k]['url'].'</guid>';
			$output .= "\r\n";			
			$output .= '<comments>'.$this->items[$k]['url'].'</comments>';
			$output .= "\r\n";
			$output .= '<pubDate>'.date("r", strtotime($this->items[$k]['date'])).'</pubDate>';
			$output .= "\r\n";
			$output .= '<dc:creator>'.$this->items[$k]['title'].'</dc:creator>';
			$output .= "\r\n";
			$output .= '<category><![CDATA[comment]]></category>';
			$output .= "\r\n";
			$output .= '<description><![CDATA['.$this->items[$k]['description'].']]></description>';
			$output .= "\r\n";
			$output .= '<content:encoded><![CDATA['.$this->items[$k]['description'].']]></content:encoded>';		
			$output .= "\r\n";
			$output .= '<slash:comments>0</slash:comments>';
			$output .= "\r\n";
			$output .= '<wfw:commentRss>'.$this->items[$k]['url'].'</wfw:commentRss>';
			$output .= "\r\n";
			$output .= '</item>';
			$output .= "\r\n";
		}

		$output .= "\r\n";
		$output .= '</channel>';
		$output .= "\r\n";
		$output .= '</rss>';
		$output .= "\r\n";
	
		return $output; 
	}
};
 
include "config.inc";
include "database.inc";
include "general.inc";

warquest_db_connect($config["dbhost"], $config["dbuser"], $config["dbpass"], $config["dbname"]);

$myfeed = new RSSFeed();
$myfeed->SetChannel('http://www.warquest.nl',
	'WarQuest',
	'WarQuest player comments feed',
	'en-us',
	'Copyrights 2008-2014 - PlaatSoft - All Rights Reserved',
	'PlaatSoft',
	'WarQuest comments feed');
$myfeed->SetImage($config["content_url"].'images/WarQuest.jpg');

$query  = 'select a.id, a.date, a.comment, b.name from comment a, player b ';
$query .= 'where a.pid1=b.pid and pid2=0 and deleted=0 order by a.date desc limit 0, 50';
$result = warquest_db_query($query);

while ($data=warquest_db_fetch_object($result)) {
	$myfeed->SetItem('http://www.warquest.nl',
		$data->name,
		warquest_parse_smilies($data->comment),
		$data->date);
}

echo $myfeed->output();

/*
** ---------------------------------------------------------------- 
** THE END
** ----------------------------------------------------------------
*/

?>