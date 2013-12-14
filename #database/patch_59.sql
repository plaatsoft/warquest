--
-- WarQuest v5.9 data model patch
--

-- Add gold options to WarQuest

ALTER TABLE `building` ADD `gold` INT NOT NULL AFTER `price` ;
ALTER TABLE `unit` ADD `gold` INT NOT NULL AFTER `price`;
ALTER TABLE `player` ADD `gold` INT NOT NULL AFTER `money_date`;

-- Convert tradepoints

UPDATE player a left join skill b on a.pid=b.pid set a.gold=(b.trade_points*500);

/* Add initial gold to player */
UPDATE player a set a.gold=(a.gold+500);

ALTER TABLE skill DROP trade_points;


-- New earth gold buildings

delete from building where (bid>55 and bid<60);

UPDATE `building` SET `lid` = '42' WHERE `building`.`bid` =54;

INSERT INTO `building` (`bid`, `price`, `gold`, `lid`, `income`, `defense`, `energy`, `discount`, `maintenance`, `max`, `bgid`, `ugid`) 
		VALUES ('56', 0, '10', '40', '0', '370', '0', '0', '0', '600', '2', '2');
		
INSERT INTO `building` (`bid`, `price`, `gold`, `lid`, `income`, `defense`, `energy`, `discount`, `maintenance`, `max`, `bgid`, `ugid`) 
		VALUES ('57', 0, '10', '41', '0', '300', '0', '0', '0', '600', '2', '3');
		
INSERT INTO `building` (`bid`, `price`, `gold`, `lid`, `income`, `defense`, `energy`, `discount`, `maintenance`, `max`, `bgid`, `ugid`) 
		VALUES ('58', 0, '10', '41', '0', '250', '0', '0', '0', '600', '2', '4');

INSERT INTO `building` (`bid`, `price`, `gold`, `lid`, `income`, `defense`, `energy`, `discount`, `maintenance`, `max`, `bgid`, `ugid`) 
		VALUES ('59', 0, '10', '45', '0', '375', '0', '0', '0', '600', '2', '6');

-- Remove old soldiers calvalry units

delete from unit where (uid>1 and uid<25);
delete from player_unit where (uid>1 and uid<25);
delete from mission_unit where (uid>1 and uid<25);

-- New Moon gold buildings

INSERT INTO `building` (`bid`, `price`, `gold`, `lid`, `income`, `defense`, `energy`, `discount`, `maintenance`, `max`, `bgid`, `ugid`) 
		VALUES ('716', 0, '10', '147', '0', '1050', '0', '0', '0', '600', '7', '7');
		
INSERT INTO `building` (`bid`, `price`, `gold`, `lid`, `income`, `defense`, `energy`, `discount`, `maintenance`, `max`, `bgid`, `ugid`) 
		VALUES ('717', 0, '10', '147', '0', '1100', '0', '0', '0', '600', '7', '8');
		
INSERT INTO `building` (`bid`, `price`, `gold`, `lid`, `income`, `defense`, `energy`, `discount`, `maintenance`, `max`, `bgid`, `ugid`) 
		VALUES ('718', 0, '10', '149', '0', '1000', '0', '0', '0', '600', '7', '9');
		
INSERT INTO `building` (`bid`, `price`, `gold`, `lid`, `income`, `defense`, `energy`, `discount`, `maintenance`, `max`, `bgid`, `ugid`) 
		VALUES ('719', 0, '10', '148', '0', '1100', '0', '0', '0', '600', '7', '12');
		
UPDATE  building SET  `lid` =  '144' WHERE  bid=710;

-- New Mars gold buildings

UPDATE  `unit` SET  `lid` =  '194'  WHERE  `unit`.`uid` = 1609;

UPDATE  `building` SET  `lid` =  '190' WHERE  `building`.`bid` =1210;

INSERT INTO `building` (`bid`, `price`, `gold`, `lid`, `income`, `defense`, `energy`, `discount`, `maintenance`, `max`, `bgid`, `ugid`) 
		VALUES ('1211', 0, '10', '198', '0', '1050', '0', '0', '0', '600', '12', '13');
		
INSERT INTO `building` (`bid`, `price`, `gold`, `lid`, `income`, `defense`, `energy`, `discount`, `maintenance`, `max`, `bgid`, `ugid`) 
		VALUES ('1212', 0, '10', '198', '0', '950', '0', '0', '0', '600', '12', '14');
		
INSERT INTO `building` (`bid`, `price`, `gold`, `lid`, `income`, `defense`, `energy`, `discount`, `maintenance`, `max`, `bgid`, `ugid`) 
		VALUES ('1213', 0, '10', '198', '0', '1000', '0', '0', '0', '600', '12', '15');
		
INSERT INTO `building` (`bid`, `price`, `gold`, `lid`, `income`, `defense`, `energy`, `discount`, `maintenance`, `max`, `bgid`, `ugid`) 
		VALUES ('1214', 0, '10', '198', '0', '1150', '0', '0', '0', '600', '12', '16');
			
-- New Asteroid gold buildings

UPDATE  `building` SET  `lid` =  '227' WHERE  `building`.`bid` =1707;

INSERT INTO `building` (`bid`, `price`, `gold`, `lid`, `income`, `defense`, `energy`, `discount`, `maintenance`, `max`, `bgid`, `ugid`) 
		VALUES ('1710', 0, '10', '242', '0', '1100', '0', '0', '0', '600', '17', '19');
		
INSERT INTO `building` (`bid`, `price`, `gold`, `lid`, `income`, `defense`, `energy`, `discount`, `maintenance`, `max`, `bgid`, `ugid`) 
		VALUES ('1711', 0, '10', '242', '0', '1300', '0', '0', '0', '600', '17', '20');
		
INSERT INTO `building` (`bid`, `price`, `gold`, `lid`, `income`, `defense`, `energy`, `discount`, `maintenance`, `max`, `bgid`, `ugid`) 
		VALUES ('1712', 0, '10', '242', '0', '900', '0', '0', '0', '600', '17', '21');
		
INSERT INTO `building` (`bid`, `price`, `gold`, `lid`, `income`, `defense`, `energy`, `discount`, `maintenance`, `max`, `bgid`, `ugid`) 
		VALUES ('1713', 0, '10', '243', '0', '1000', '0', '0', '0', '600', '17', '22');
		
-- Add Earth Gold Units

UPDATE `unit` SET `price` = '500' WHERE `unit`.`uid` =1;

UPDATE  `unit` SET  `lid` =  '94' WHERE  `unit`.`uid` =127;
UPDATE  `unit` SET  `lid` =  '91' WHERE  `unit`.`uid` =226;
UPDATE  `unit` SET  `lid` =  '93' WHERE  `unit`.`uid` =227;
UPDATE  `unit` SET  `lid` =  '94' WHERE  `unit`.`uid` =228;
UPDATE  `unit` SET  `lid` =  '95' WHERE  `unit`.`uid` =326;

delete from unit where uid=128;

INSERT INTO `unit` (`uid`, `lid`, `price`, `gold`, `attack`, `defense`, `max`, `ugid`, `upkeep`) 
	VALUES ('128', '95', '0', '10', '675', '450', '5000', '2', '75000');

delete from unit where uid=229;

INSERT INTO `unit` (`uid`, `lid`, `price`, `gold`, `attack`, `defense`, `max`, `ugid`, `upkeep`) 
	VALUES ('229', '99', '0', '10', '900', '665', '5000', '3', '98500');

delete from unit where uid=327;

INSERT INTO `unit` (`uid`, `lid`, `price`, `gold`, `attack`, `defense`, `max`, `ugid`, `upkeep`) 
	VALUES ('327', '97', '0', '10', '800', '585', '5000', '4', '75500');

delete from unit where uid=513;

INSERT INTO `unit` (`uid`, `lid`, `price`, `gold`, `attack`, `defense`, `max`, `ugid`, `upkeep`) 
	VALUES ('513', '92', '0', '10', '765', '480', '5000', '6', '64000');
	
-- Add Moon Gold Units

UPDATE  `unit` SET  `lid` =  '144' WHERE  `unit`.`uid` =710;
UPDATE  `unit` SET  `lid` =  '147' WHERE  `unit`.`uid` =810;
UPDATE `unit` SET `lid` = '147' WHERE `unit`.`uid` = 916;
UPDATE `unit` SET  `lid` =  '148' WHERE  `unit`.`uid` =1211;

delete from unit where uid=711;

INSERT INTO `unit` (`uid`, `lid`, `price`, `gold`, `attack`, `defense`, `max`, `ugid`, `upkeep`) 
	VALUES ('711', '145', '0', '10', '750', '700', '5000', '7', '32500');

delete from unit where uid=811;

INSERT INTO `unit` (`uid`, `lid`, `price`, `gold`, `attack`, `defense`, `max`, `ugid`, `upkeep`) 
	VALUES ('811', '149', '0', '10', '250', '225', '5000', '8', '12500');	

delete from unit where uid=917;

INSERT INTO `unit` (`uid`, `lid`, `price`, `gold`, `attack`, `defense`, `max`, `ugid`, `upkeep`) 
	VALUES ('917', '148', '0', '10', '5550', '5350', '5000', '9', '100000');		
	
delete from unit where uid=1212;
	
INSERT INTO `unit` (`uid`, `lid`, `price`, `gold`, `attack`, `defense`, `max`, `ugid`, `upkeep`) 
	VALUES ('1212', '149', '0', '10', '2800', '2450', '5000', '12', '22500');		
	
-- Add Mars Gold Units

INSERT INTO `unit` (`uid`, `lid`, `price`, `gold`, `attack`, `defense`, `max`, `ugid`, `upkeep`) 
	VALUES ('1310', '199', '0', '10', '700', '600', '5000', '13', '25000');
	
INSERT INTO `unit` (`uid`, `lid`, `price`, `gold`, `attack`, `defense`, `max`, `ugid`, `upkeep`) 
	VALUES ('1410', '197', '0', '10', '1800', '1750', '5000', '14', '60000');

INSERT INTO `unit` (`uid`, `lid`, `price`, `gold`, `attack`, `defense`, `max`, `ugid`, `upkeep`) 
	VALUES ('1510', '197', '0', '10', '3650', '3850', '5000', '15', '175000');	
	

	
INSERT INTO `unit` (`uid`, `lid`, `price`, `gold`, `attack`, `defense`, `max`, `ugid`, `upkeep`) 
	VALUES ('1610', '199', '0', '10', '1850', '1850', '5000', '16', '125000');

-- Add Asteroid Gold Units	

INSERT INTO `unit` (`uid`, `lid`, `price`, `gold`, `attack`, `defense`, `max`, `ugid`, `upkeep`) 
	VALUES ('1910', '236', '0', '10', '700', '600', '5000', '19', '25000');
	
INSERT INTO `unit` (`uid`, `lid`, `price`, `gold`, `attack`, `defense`, `max`, `ugid`, `upkeep`) 
	VALUES ('2010', '238', '0', '10', '1800', '1750', '5000', '20', '60000');
	
INSERT INTO `unit` (`uid`, `lid`, `price`, `gold`, `attack`, `defense`, `max`, `ugid`, `upkeep`) 
	VALUES ('2110', '246', '0', '10', '3650', '3850', '5000', '21', '175000');

INSERT INTO `unit` (`uid`, `lid`, `price`, `gold`, `attack`, `defense`, `max`, `ugid`, `upkeep`) 
	VALUES ('2210', '240', '0', '10', '1850', '1850', '5000', '22', '125000');