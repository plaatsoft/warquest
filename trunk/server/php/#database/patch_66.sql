--
-- WarQuest v6.6 data model patch
--

CREATE TABLE IF NOT EXISTS `views` (
  `mid` int(11) NOT NULL,
  `sid` int(11) NOT NULL,
  `ssid` int(11) NOT NULL,
  `eid` int(11) NOT NULL,
  `requests` int(11) NOT NULL,
  PRIMARY KEY (`mid`,`sid`,`ssid`,`eid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;


insert into views (mid, sid, ssid, eid, requests) values (0,0,0,0, 44977393);

ALTER TABLE `player` ADD `clan_notification` INT NOT NULL AFTER `comment`;
ALTER TABLE `comment` ADD `cid` INT NOT NULL AFTER `tid` ;
ALTER TABLE `player` CHANGE `news` `news_notification` INT( 11 ) NOT NULL;
ALTER TABLE `player` CHANGE `chat` `chat_notification` INT( 11 ) NOT NULL;
ALTER TABLE `player` CHANGE `comment` `comment_notification` INT( 11 ) NOT NULL ;



