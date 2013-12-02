-- Update clan wars

ALTER TABLE `clan` ADD `slogan` VARCHAR( 200 ) NOT NULL AFTER `lost` 


-- Update statistics

ALTER TABLE `statistics` CHANGE `ads` `gold` INT( 11 ) NOT NULL;

UPDATE `statistics` SET gold = 0;


-- Earth Moon Units
UPDATE `warquest`.`unit` SET `defense` = '410' WHERE `unit`.`uid` =127;
UPDATE `warquest`.`unit` SET `defense` = '460' WHERE `unit`.`uid` =128;
UPDATE `warquest`.`unit` SET `defense` = '625' WHERE `unit`.`uid` =228;
UPDATE `warquest`.`unit` SET `defense` = '675' WHERE `unit`.`uid` =229;
UPDATE `warquest`.`unit` SET `defense` = '545' WHERE `unit`.`uid` =326;
UPDATE `warquest`.`unit` SET `defense` = '595' WHERE `unit`.`uid` =327;
UPDATE `warquest`.`unit` SET `defense` = '440' WHERE `unit`.`uid` =512;
UPDATE `warquest`.`unit` SET `defense` = '490' WHERE `unit`.`uid` =513;

-- Rebalance Moon Units
UPDATE `warquest`.`unit` SET `defense` = '2400' WHERE `unit`.`uid` =1209;
UPDATE `warquest`.`unit` SET `defense` = '2000' WHERE `unit`.`uid` =1210;
UPDATE `warquest`.`unit` SET `defense` = '2300' WHERE `unit`.`uid` =1211;
UPDATE `warquest`.`unit` SET `defense` = '550' WHERE `unit`.`uid` =710;
UPDATE `warquest`.`unit` SET `defense` = '650' WHERE `unit`.`uid` =708;
UPDATE `warquest`.`unit` SET `defense` = '150' WHERE `unit`.`uid` =810;
UPDATE `warquest`.`unit` SET `defense` = '175' WHERE `unit`.`uid` =808;
UPDATE `warquest`.`unit` SET `upkeep` = '1000000' WHERE `unit`.`uid` =917;

-- Rebalance Mars Units
UPDATE `warquest`.`unit` SET `defense` = '650' WHERE `unit`.`uid` =1308;
UPDATE `warquest`.`unit` SET `defense` = '1550' WHERE `unit`.`uid` =1409;
UPDATE `warquest`.`unit` SET `defense` = '1600' WHERE `unit`.`uid` =1609;
UPDATE `warquest`.`unit` SET `defense` = '1800' WHERE `unit`.`uid` =1607;

-- Rebalance Asteroid Units
UPDATE `warquest`.`unit` SET `defense` = '1350' WHERE `unit`.`uid` =2009;
UPDATE `warquest`.`unit` SET `defense` = '1550' WHERE `unit`.`uid` =2209;
UPDATE `warquest`.`unit` SET `defense` = '1800' WHERE `unit`.`uid` =2207;

-- Rebalance Moon Buildings
UPDATE `warquest`.`building` SET `defense` = '250' WHERE `building`.`bid` =701;
UPDATE `warquest`.`building` SET `defense` = '300' WHERE `building`.`bid` =704;
UPDATE `warquest`.`building` SET `defense` = '450' WHERE `building`.`bid` =707;
UPDATE `warquest`.`building` SET `defense` = '550' WHERE `building`.`bid` =710;
UPDATE `warquest`.`building` SET `defense` = '650' WHERE `building`.`bid` =717;

UPDATE `warquest`.`building` SET `defense` = '100' WHERE `building`.`bid` =700;
UPDATE `warquest`.`building` SET `defense` = '250' WHERE `building`.`bid` =707;
UPDATE `warquest`.`building` SET `defense` = '350' WHERE `building`.`bid` =708;
UPDATE `warquest`.`building` SET `defense` = '450' WHERE `building`.`bid` =709;
UPDATE `warquest`.`building` SET `defense` = '550' WHERE `building`.`bid` =716;

UPDATE `warquest`.`building` SET `defense` = '100' WHERE `building`.`bid` =702;
UPDATE `warquest`.`building` SET `defense` = '250' WHERE `building`.`bid` =705;
UPDATE `warquest`.`building` SET `defense` = '355' WHERE `building`.`bid` =708;
UPDATE `warquest`.`building` SET `defense` = '455' WHERE `building`.`bid` =718;

UPDATE `warquest`.`building` SET `defense` = '550' WHERE `building`.`bid` =714;


-- Rebalance Asteroid Buildings
UPDATE `warquest`.`building` SET `defense` = '1000' WHERE `building`.`bid` =1701;

-- Add bank_group
CREATE TABLE IF NOT EXISTS `bank_group` (
  `bgid` int(11) NOT NULL,
  PRIMARY KEY (`bgid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Gegevens worden uitgevoerd voor tabel `bank_group`
--

INSERT INTO `bank_group` (`bgid`) VALUES
(1),
(2),
(3);


-- Add stock_group
CREATE TABLE IF NOT EXISTS `stock_group` (
  `sgid` int(11) NOT NULL,
  PRIMARY KEY (`sgid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Gegevens worden uitgevoerd voor tabel `stock_group`
--

INSERT INTO `stock_group` (`sgid`) VALUES
(1),
(2),
(3),
(4);