-- Update statistics

ALTER TABLE `statistics` CHANGE `ads` `gold` INT( 11 ) NOT NULL;

UPDATE `statistics` SET gold = 0;


-- Earth Moon
UPDATE `warquest`.`unit` SET `defense` = '410' WHERE `unit`.`uid` =127;
UPDATE `warquest`.`unit` SET `defense` = '460' WHERE `unit`.`uid` =128;
UPDATE `warquest`.`unit` SET `defense` = '625' WHERE `unit`.`uid` =228;
UPDATE `warquest`.`unit` SET `defense` = '675' WHERE `unit`.`uid` =229;
UPDATE `warquest`.`unit` SET `defense` = '545' WHERE `unit`.`uid` =326;
UPDATE `warquest`.`unit` SET `defense` = '595' WHERE `unit`.`uid` =327;
UPDATE `warquest`.`unit` SET `defense` = '440' WHERE `unit`.`uid` =512;
UPDATE `warquest`.`unit` SET `defense` = '490' WHERE `unit`.`uid` =513;

-- Rebalance Moon
UPDATE `warquest`.`unit` SET `defense` = '2400' WHERE `unit`.`uid` =1209;
UPDATE `warquest`.`unit` SET `defense` = '2000' WHERE `unit`.`uid` =1210;
UPDATE `warquest`.`unit` SET `defense` = '2300' WHERE `unit`.`uid` =1211;
UPDATE `warquest`.`unit` SET `defense` = '550' WHERE `unit`.`uid` =710;
UPDATE `warquest`.`unit` SET `defense` = '650' WHERE `unit`.`uid` =708;
UPDATE `warquest`.`unit` SET `defense` = '150' WHERE `unit`.`uid` =810;
UPDATE `warquest`.`unit` SET `defense` = '175' WHERE `unit`.`uid` =808;
UPDATE `warquest`.`unit` SET `upkeep` = '1000000' WHERE `unit`.`uid` =917;

-- Rebalance Mars
UPDATE `warquest`.`unit` SET `defense` = '650' WHERE `unit`.`uid` =1308;
UPDATE `warquest`.`unit` SET `defense` = '1550' WHERE `unit`.`uid` =1409;
UPDATE `warquest`.`unit` SET `defense` = '1600' WHERE `unit`.`uid` =1609;
UPDATE `warquest`.`unit` SET `defense` = '1800' WHERE `unit`.`uid` =1607;

-- Rebalance Asteroid
UPDATE `warquest`.`unit` SET `defense` = '1350' WHERE `unit`.`uid` =2009;
UPDATE `warquest`.`unit` SET `defense` = '1550' WHERE `unit`.`uid` =2209;
UPDATE `warquest`.`unit` SET `defense` = '1800' WHERE `unit`.`uid` =2207;
