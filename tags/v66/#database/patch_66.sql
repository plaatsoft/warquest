--
-- WarQuest v6.6 data model patch
--

-- Add page view counters
CREATE TABLE IF NOT EXISTS `views` (
  `mid` int(11) NOT NULL,
  `sid` int(11) NOT NULL,
  `ssid` int(11) NOT NULL,
  `eid` int(11) NOT NULL,
  `requests` int(11) NOT NULL,
  PRIMARY KEY (`mid`,`sid`,`ssid`,`eid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

insert into views (mid, sid, ssid, eid, requests) values (0,0,0,0, 44977393);

-- Add clan messages
ALTER TABLE `comment` ADD `cid` INT NOT NULL AFTER `tid` ;

-- Add clan message notification
ALTER TABLE `player` ADD `clan_notification` INT NOT NULL AFTER `comment`;

-- Refactor other message notifcations
ALTER TABLE `player` CHANGE `news` `news_notification` INT( 11 ) NOT NULL;
ALTER TABLE `player` CHANGE `chat` `chat_notification` INT( 11 ) NOT NULL;
ALTER TABLE `player` CHANGE `comment` `comment_notification` INT( 11 ) NOT NULL ;

-- Add mission awards
ALTER TABLE `player` ADD `mission_level` INT NOT NULL AFTER `mission` ;

UPDATE player SET mission_level=1;

CREATE TABLE IF NOT EXISTS `mission_award` (
  `id` int(11) NOT NULL,
  `won` int(11) NOT NULL,
  `ep` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `battle_award`
--

INSERT INTO `mission_award` (`id`, `won`, `ep`) VALUES
(1, 20, 1),
(2, 100, 1),
(3, 200, 1),
(4, 300, 1),
(5, 400, 1),
(6, 500, 1),
(7, 750, 1),
(8, 1000, 1),
(9, 1250, 1),
(10, 1500, 1),
(11, 1750, 1),
(12, 2000, 1),
(13, 2250, 2),
(14, 2500, 2),
(15, 2750, 2),
(16, 3000, 2),
(17, 3500, 2),
(18, 4000, 2),
(19, 4500, 2),
(20, 5000, 2),
(21, 6000, 2),
(22, 7500, 3),
(23, 8000, 3),
(24, 9000, 3),
(25, 10000, 3),
(26, 12000, 3),
(27, 14000, 3),
(28, 16000, 4),
(29, 18000, 4),
(30, 20000, 4),
(31, 22000, 4),
(32, 24000, 4),
(33, 26000, 5),
(34, 28000, 5),
(35, 30000, 5),
(36, 32000, 5),
(37, 34000, 6),
(38, 36000, 6),
(39, 38000, 6),
(40, 40000, 6),
(41, 42000, 6),
(42, 44000, 7),
(43, 46000, 7),
(44, 48000, 7),
(45, 50000, 7);