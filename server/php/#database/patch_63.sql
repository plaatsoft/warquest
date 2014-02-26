--
-- WarQuest v6.3 data model patch
--

-- bugfix
UPDATE mission SET lid=279 WHERE mid=451;

-- update levels
UPDATE level SET experience=1025000 WHERE lid=281;
UPDATE level SET experience=1050000 WHERE lid=282;
UPDATE level SET experience=1075000 WHERE lid=283;
UPDATE level SET experience=1100000 WHERE lid=284;
UPDATE level SET experience=1125000 WHERE lid=285;
UPDATE level SET experience=1150000 WHERE lid=286;
UPDATE level SET experience=1175000 WHERE lid=287;
UPDATE level SET experience=1200000 WHERE lid=288;
UPDATE level SET experience=1225000 WHERE lid=289;
UPDATE level SET experience=1250000 WHERE lid=290;
UPDATE level SET experience=1275000 WHERE lid=291;
UPDATE level SET experience=1300000 WHERE lid=292;
UPDATE level SET experience=1325000 WHERE lid=293;
UPDATE level SET experience=1350000 WHERE lid=294;
UPDATE level SET experience=1375000 WHERE lid=295;
UPDATE level SET experience=1400000 WHERE lid=296;
UPDATE level SET experience=1425000 WHERE lid=297;
UPDATE level SET experience=1450000 WHERE lid=298;
UPDATE level SET experience=1475000 WHERE lid=299;

ALTER TABLE sector ADD conquer_date DATETIME NOT NULL AFTER damage;

delete from cron where cid=10;
INSERT INTO cron (cid, note, last_run) VALUES (10, 'Clear inactive sectors', '0000-00-00 00:00:00');

ALTER TABLE player_clan ADD approved INT NOT NULL AFTER joined;

update player_clan set approved=1;

-- Add more earth gold building

UPDATE building SET discount=3 WHERE bid=37;
UPDATE building SET discount=4 WHERE bid=38;
UPDATE building SET discount=5 WHERE bid=30;
UPDATE building SET discount=8 WHERE bid=31;
UPDATE building SET discount=10 WHERE bid=32;
UPDATE building SET discount=12 WHERE bid=33;
UPDATE building SET discount=14 WHERE bid=34;
UPDATE building SET discount=16, lid=95 WHERE bid=36;
UPDATE building SET lid=95 WHERE bid=50;

delete from building where bid=60;
INSERT INTO building (bid, price, gold, lid, income, defense, energy, discount, maintenance, max, bgid, ugid) VALUES
(60, 0,  500, 93, 0, 0, 11, 0, 0, 1, 3, 0);

delete from building where bid=61;
INSERT INTO building (bid, price, gold, lid, income, defense, energy, discount, maintenance, max, bgid, ugid) VALUES
(61, 0,  500, 96, 0, 0, 0, 18, 0, 1, 4, 0);

delete from building where bid=62;
INSERT INTO building (bid, price, gold, lid, income, defense, energy, discount, maintenance, max, bgid, ugid) VALUES
(62, 0,  500, 96, 0, 0, 0, 0, 11, 1, 5, 0);

-- Add more moon gold building

UPDATE building SET discount=7 WHERE bid=906;
UPDATE building SET discount=8 WHERE bid=907;
UPDATE building SET discount=9 WHERE bid=908;
UPDATE building SET discount=10 WHERE bid=909;
UPDATE building SET discount=11 WHERE bid=910;
UPDATE building SET discount=12 WHERE bid=911;
UPDATE building SET lid=141 WHERE bid=911;
UPDATE building SET lid=142 WHERE bid=809;
UPDATE building SET lid=143 WHERE bid=709;

UPDATE building SET lid=146 WHERE bid=811;

delete from building where bid=812;
INSERT INTO building (bid, price, gold, lid, income, defense, energy, discount, maintenance, max, bgid, ugid) VALUES
(812, 0,  500, 149, 0, 0, 13, 0, 0, 1, 8, 0);

delete from building where bid=912;
INSERT INTO building (bid, price, gold, lid, income, defense, energy, discount, maintenance, max, bgid, ugid) VALUES
(912, 0,  500, 144, 0, 0, 0, 15, 0, 1, 9, 0);

delete from building where bid=1010;
INSERT INTO building (bid, price, gold, lid, income, defense, energy, discount, maintenance, max, bgid, ugid) VALUES
(1010, 0,  500, 145, 0, 0, 0, 0, 17, 1, 10, 0);

-- Add more mars gold building

UPDATE building SET discount=7 WHERE bid=1406;
UPDATE building SET discount=8 WHERE bid=1407;
UPDATE building SET discount=9 WHERE bid=1408;

delete from building where bid=1310;
INSERT INTO building (bid, price, gold, lid, income, defense, energy, discount, maintenance, max, bgid, ugid) VALUES
(1310, 0,  500, 199, 0, 0, 11, 0, 0, 1, 13, 0);

delete from building where bid=1409;
INSERT INTO building (bid, price, gold, lid, income, defense, energy, discount, maintenance, max, bgid, ugid) VALUES
(1409, 0,  500, 192, 0, 0, 0, 10, 0, 1, 14, 0);

UPDATE building SET lid=194 WHERE bid=1509;

delete from building where bid=1510;
INSERT INTO building (bid, price, gold, lid, income, defense, energy, discount, maintenance, max, bgid, ugid) VALUES
(1510, 0,  500, 196, 0, 0, 0, 0, 18, 1, 15, 0);


-- Add more mercure gold building

UPDATE building SET discount=8 WHERE bid=1900;
UPDATE building SET discount=10 WHERE bid=1901;
UPDATE building SET discount=14 WHERE bid=1902;
UPDATE building SET discount=16 WHERE bid=1903;
UPDATE building SET discount=18 WHERE bid=1904;

delete from building where bid=1810;
INSERT INTO building (bid, price, gold, lid, income, defense, energy, discount, maintenance, max, bgid, ugid) VALUES
(1810, 0,  500, 246, 0, 0, 11, 0, 0, 1, 18, 0);

delete from building where bid=1905;
INSERT INTO building (bid, price, gold, lid, income, defense, energy, discount, maintenance, max, bgid, ugid) VALUES
(1905, 0,  500, 232, 0, 0, 0, 20, 0, 1, 19, 0);

UPDATE building SET maintenance=8 WHERE bid=2000;
UPDATE building SET maintenance=10 WHERE bid=2001;
UPDATE building SET maintenance=14 WHERE bid=2002;
UPDATE building SET maintenance=16 WHERE bid=2003;
UPDATE building SET maintenance=18 WHERE bid=2004;

delete from building where bid=2005;
INSERT INTO building (bid, price, gold, lid, income, defense, energy, discount, maintenance, max, bgid, ugid) VALUES
(2005, 0,  500, 235, 0, 0, 0, 0, 22, 1, 20, 0);

-- Add more neptune gold building

UPDATE building SET discount=8 WHERE bid=2400;
UPDATE building SET discount=10 WHERE bid=2401;
UPDATE building SET discount=14 WHERE bid=2402;
UPDATE building SET discount=16 WHERE bid=2403;
UPDATE building SET discount=18 WHERE bid=2404;

UPDATE building SET lid=287 WHERE bid=2308;
UPDATE building SET lid=290 WHERE bid=2309;

delete from building where bid=2310;
INSERT INTO building (bid, price, gold, lid, income, defense, energy, discount, maintenance, max, bgid, ugid) VALUES
(2310, 0,  500, 292, 0, 0, 11, 0, 0, 1, 23, 0);

UPDATE building SET lid=274 WHERE bid=2404;

delete from building where bid=2405;
INSERT INTO building (bid, price, gold, lid, income, defense, energy, discount, maintenance, max, bgid, ugid) VALUES
(2405, 0,  500, 280, 0, 0, 0, 20, 0, 1, 24, 0);

UPDATE building SET maintenance=8 WHERE bid=2500;
UPDATE building SET maintenance=10 WHERE bid=2501;
UPDATE building SET maintenance=14 WHERE bid=2502;
UPDATE building SET maintenance=16 WHERE bid=2503;
UPDATE building SET maintenance=18 WHERE bid=2504;

delete from building where bid=2505;
INSERT INTO building (bid, price, gold, lid, income, defense, energy, discount, maintenance, max, bgid, ugid) VALUES
(2505, 0,  500, 275, 0, 0, 0, 0, 22, 1, 25, 0);

UPDATE building SET lid=285 WHERE bid=2308;
UPDATE building SET lid=286 WHERE bid=2309;
UPDATE building SET lid=287 WHERE bid=2310;

-- added gold income buildings

delete from building_unit where bid=1409;

delete from building where bid=63;

INSERT INTO building (bid, price, gold, lid, income, defense, energy, discount, maintenance, max, bgid, ugid) VALUES
(63, 0,  10, 60, 3150000, 0, 0, 0, 0, 645, 1, 0);

UPDATE building SET lid=109 WHERE bid=603;
UPDATE building SET lid=111 WHERE bid=604;
UPDATE building SET lid=115 WHERE bid=605;
UPDATE building SET lid=117 WHERE bid=606;
UPDATE building SET lid=124 WHERE bid=607;
UPDATE building SET lid=127 WHERE bid=608;
UPDATE building SET lid=133 WHERE bid=609;
UPDATE building SET lid=137 WHERE bid=610;
UPDATE building SET lid=142 WHERE bid=611;

delete from building where bid=612;

INSERT INTO building (bid, price, gold, lid, income, defense, energy, discount, maintenance, max, bgid, ugid) VALUES
(612, 0,  10, 146, 4500000, 0, 0, 0, 0, 645, 6, 0);

UPDATE building SET lid=163 WHERE bid=1103;
UPDATE building SET lid=166 WHERE bid=1104;
UPDATE building SET lid=171 WHERE bid=1105;
UPDATE building SET lid=176 WHERE bid=1106;
UPDATE building SET lid=181 WHERE bid=1107;
UPDATE building SET lid=186 WHERE bid=1108;
UPDATE building SET lid=191 WHERE bid=1109;

delete from building where bid=1110;

INSERT INTO building (bid, price, gold, lid, income, defense, energy, discount, maintenance, max, bgid, ugid) VALUES
(1110, 0,  10, 196, 3500000, 0, 0, 0, 0, 645, 11, 0);

delete from building where bid=1610;

INSERT INTO building (bid, price, gold, lid, income, defense, energy, discount, maintenance, max, bgid, ugid) VALUES
(1610, 0,  10, 237, 6500000, 0, 0, 0, 0, 645, 16, 0);

delete from building where bid=2106;

INSERT INTO building (bid, price, gold, lid, income, defense, energy, discount, maintenance, max, bgid, ugid) VALUES
(2106, 0,  10, 276, 6000000, 0, 0, 0, 0, 645, 21, 0);

-- correction
UPDATE building SET discount=10 WHERE bid=1900;
UPDATE building SET discount=12 WHERE bid=1901;
UPDATE building SET discount=14 WHERE bid=1902;
UPDATE building SET discount=16 WHERE bid=1903;
UPDATE building SET discount=18 WHERE bid=1904;
UPDATE building SET discount=20 WHERE bid=1905;

UPDATE building SET discount=10 WHERE bid=2400;
UPDATE building SET discount=12 WHERE bid=2401;
UPDATE building SET discount=14 WHERE bid=2402;
UPDATE building SET discount=16 WHERE bid=2403;
UPDATE building SET discount=18 WHERE bid=2404;
UPDATE building SET discount=20 WHERE bid=2405;

-- Added money, attack and defense strenght to clan
ALTER TABLE clan ADD money BIGINT( 20 ) NOT NULL AFTER lost;
ALTER TABLE clan ADD attack INT NOT NULL AFTER money;
ALTER TABLE clan ADD defense INT NOT NULL AFTER attack;

-- Add promotion invite database table
CREATE TABLE IF NOT EXISTS `invite` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `email` varchar(120) NOT NULL,
  `approved` int(11) NOT NULL,
  `date` datetime NOT NULL,
  `pid` INT NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;
