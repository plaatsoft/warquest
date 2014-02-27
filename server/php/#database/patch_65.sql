--
-- WarQuest v6.5 data model patch
--

-- Added auto index number by poll answers
ALTER TABLE `poll_answer` CHANGE `answer_id` `answer_id` INT( 11 ) NOT NULL AUTO_INCREMENT;

-- Added index for better leaderboard performance
ALTER TABLE `player` ADD INDEX ( `experience` ) ;

-- Added two extra discount buildings to mars
UPDATE building SET lid=188, discount=10 WHERE bid=1408;
UPDATE building SET lid=193, discount=16 WHERE bid=1409;

delete from building where bid=1410;
INSERT INTO building (bid, price, gold, lid, income, defense, energy, discount, maintenance, max, bgid, ugid) VALUES
(1410, 128000000000,  0, 190, 0, 0, 0, 12, 0, 1, 14, 0);

delete from building where bid=1411;
INSERT INTO building (bid, price, gold, lid, income, defense, energy, discount, maintenance, max, bgid, ugid) VALUES
(1411, 250000000000,  0, 192, 0, 0, 0, 14, 0, 1, 14, 0);

delete from building_unit where bid=1410;
INSERT INTO `building_unit` (`bid`, `uid`, `amount`) VALUES
(1410, 1700, 350),
(1410, 1701, 280),
(1410, 1702, 300);

delete from building_unit where bid=1411;
INSERT INTO `building_unit` (`bid`, `uid`, `amount`) VALUES
(1411, 1700, 450),
(1411, 1701, 475),
(1411, 1702, 500);

-- Typo correction
UPDATE planet SET name="mercury" WHERE planet_id=4;

-- Added clan missions
ALTER TABLE `clan` ADD `mission` INT NOT NULL AFTER `slogan` ;
ALTER TABLE `clan` CHANGE `last_activity` `last_activity` DATETIME NOT NULL ;
ALTER TABLE `clan` CHANGE `created` `created` DATETIME NOT NULL ;

CREATE TABLE IF NOT EXISTS `clan_mission` (
  `cid` int(11) NOT NULL,
  `mid` int(11) NOT NULL,
  `progress` int(11) NOT NULL,
  PRIMARY KEY (`cid`,`mid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;


