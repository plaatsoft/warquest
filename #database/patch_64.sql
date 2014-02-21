--
-- WarQuest v6.4 data model patch
--

-- Table and labels needed for soap interface

CREATE TABLE IF NOT EXISTS `planet` (
  `planet_id` int(11) NOT NULL,
  `name` varchar(10) NOT NULL,
  PRIMARY KEY (`planet_id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

INSERT INTO `planet` (`planet_id`, `name`) VALUES
(1, 'earth'),
(2, 'moon'),
(3, 'mars'),
(4, 'mercure'),
(5, 'neptune');

UPDATE unit_group SET ugid=1 WHERE ugid=0;
UPDATE battle SET ugid=1 WHERE ugid=0;

ALTER TABLE `unit_group` ADD `name` VARCHAR( 10 ) NOT NULL AFTER `type` ;

UPDATE unit_group SET name="army" WHERE ugid=1;
UPDATE unit_group SET name="cavalry" WHERE ugid=2;
UPDATE unit_group SET name="navy" WHERE ugid=3;
UPDATE unit_group SET name="airforce" WHERE ugid=4;
UPDATE unit_group SET name="intel" WHERE ugid=6;
UPDATE unit_group SET name="citizens" WHERE ugid=5;

UPDATE unit_group SET name="warriors" WHERE ugid=7;
UPDATE unit_group SET name="drones" WHERE ugid=8;
UPDATE unit_group SET name="spacecrafts" WHERE ugid=9;
UPDATE unit_group SET name="explorers" WHERE ugid=12;
UPDATE unit_group SET name="army" WHERE ugid=11;
UPDATE unit_group SET name="citizens" WHERE ugid=10;

UPDATE unit_group SET name="drones" WHERE ugid=13;
UPDATE unit_group SET name="warriors" WHERE ugid=14;
UPDATE unit_group SET name="spacecrafts" WHERE ugid=15;
UPDATE unit_group SET name="explorers" WHERE ugid=16;
UPDATE unit_group SET name="citizens" WHERE ugid=17;
UPDATE unit_group SET name="army" WHERE ugid=18;

UPDATE unit_group SET name="drones" WHERE ugid=19;
UPDATE unit_group SET name="warriors" WHERE ugid=20;
UPDATE unit_group SET name="spacecrafts" WHERE ugid=21;
UPDATE unit_group SET name="explorers" WHERE ugid=22;
UPDATE unit_group SET name="citizens" WHERE ugid=23;
UPDATE unit_group SET name="army" WHERE ugid=24;

UPDATE unit_group SET name="drones" WHERE ugid=25;
UPDATE unit_group SET name="warriors" WHERE ugid=26;
UPDATE unit_group SET name="spacecrafts" WHERE ugid=27;
UPDATE unit_group SET name="explorers" WHERE ugid=28;
UPDATE unit_group SET name="citizens" WHERE ugid=29;
UPDATE unit_group SET name="army" WHERE ugid=30;

-- Added clan bank

CREATE TABLE IF NOT EXISTS `clan_bank` (
  `cbid` int(11) NOT NULL AUTO_INCREMENT,
  `cid` int(11) NOT NULL,
  `pid` int(11) NOT NULL,
  `amount` bigint(11) NOT NULL,
  `balance` bigint(11) NOT NULL,
  `action` int(11) NOT NULL,
  `date` datetime NOT NULL,
  PRIMARY KEY (`cbid`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=1;


-- Added premium account features

ALTER TABLE player ADD premium_date DATETIME NOT NULL AFTER pattern;

ALTER TABLE `poll_answer` CHANGE `answer_id` `answer_id` INT( 11 ) NOT NULL AUTO_INCREMENT;
