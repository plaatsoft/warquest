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
(1410, 2800, 350),
(1410, 2801, 280),
(1410, 2802, 300);

delete from building_unit where bid=1411;
INSERT INTO `building_unit` (`bid`, `uid`, `amount`) VALUES
(1411, 2800, 450),
(1411, 2801, 475),
(1411, 2802, 500);

-- Typo correction
UPDATE planet SET name="mercury" WHERE planet_id=4;
