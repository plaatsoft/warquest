-- Add commercial options

ALTER TABLE `building` ADD `gold` INT NOT NULL AFTER `price` ;
ALTER TABLE `unit` ADD `gold` INT NOT NULL AFTER `price`;
ALTER TABLE `player` ADD `gold` INT NOT NULL AFTER `money_date`;

-- New earth gold building

UPDATE `building` SET `lid` = '42' WHERE `building`.`bid` =54;

INSERT INTO `building` (`bid`, `price`, `gold`, `lid`, `income`, `defense`, `energy`, `discount`, `maintenance`, `max`, `bgid`, `ugid`) 
		VALUES ('56', 0, '10', '40', '0', '500', '0', '0', '0', '600', '2', '2');
		
INSERT INTO `building` (`bid`, `price`, `gold`, `lid`, `income`, `defense`, `energy`, `discount`, `maintenance`, `max`, `bgid`, `ugid`) 
		VALUES ('57', 0, '10', '41', '0', '500', '0', '0', '0', '600', '2', '3');
		
INSERT INTO `building` (`bid`, `price`, `gold`, `lid`, `income`, `defense`, `energy`, `discount`, `maintenance`, `max`, `bgid`, `ugid`) 
		VALUES ('58', 0, '10', '41', '0', '500', '0', '0', '0', '600', '2', '4');

INSERT INTO `building` (`bid`, `price`, `gold`, `lid`, `income`, `defense`, `energy`, `discount`, `maintenance`, `max`, `bgid`, `ugid`) 
		VALUES ('59', 0, '10', '45', '0', '750', '0', '0', '0', '600', '2', '6');

-- Remove old soldiers calvalry units

delete from unit where (uid>1 and uid<25);
delete from player_unit where (uid>1 and uid<25);
delete from mission_unit where (uid>1 and uid<25);

-- New Moon gold building

INSERT INTO `building` (`bid`, `price`, `gold`, `lid`, `income`, `defense`, `energy`, `discount`, `maintenance`, `max`, `bgid`, `ugid`) 
		VALUES ('716', 0, '10', '147', '0', '1050', '0', '0', '0', '600', '7', '7');
		
INSERT INTO `building` (`bid`, `price`, `gold`, `lid`, `income`, `defense`, `energy`, `discount`, `maintenance`, `max`, `bgid`, `ugid`) 
		VALUES ('717', 0, '10', '147', '0', '1100', '0', '0', '0', '600', '7', '8');
		
INSERT INTO `building` (`bid`, `price`, `gold`, `lid`, `income`, `defense`, `energy`, `discount`, `maintenance`, `max`, `bgid`, `ugid`) 
		VALUES ('718', 0, '10', '147', '0', '1000', '0', '0', '0', '600', '7', '9');
		
INSERT INTO `building` (`bid`, `price`, `gold`, `lid`, `income`, `defense`, `energy`, `discount`, `maintenance`, `max`, `bgid`, `ugid`) 
		VALUES ('719', 0, '10', '147', '0', '1100', '0', '0', '0', '600', '7', '12');
		
UPDATE  building SET  `lid` =  '144' WHERE  bid=710;

-- New Mars gold building

UPDATE  `unit` SET  `lid` =  '194'  WHERE  `unit`.`uid` =1609;

UPDATE  `building` SET  `lid` =  '190' WHERE  `building`.`bid` =1210;

INSERT INTO `building` (`bid`, `price`, `gold`, `lid`, `income`, `defense`, `energy`, `discount`, `maintenance`, `max`, `bgid`, `ugid`) 
		VALUES ('1211', 0, '10', '198', '0', '1050', '0', '0', '0', '600', '12', '13');
		
INSERT INTO `building` (`bid`, `price`, `gold`, `lid`, `income`, `defense`, `energy`, `discount`, `maintenance`, `max`, `bgid`, `ugid`) 
		VALUES ('1212', 0, '10', '198', '0', '950', '0', '0', '0', '600', '12', '14');
		
INSERT INTO `building` (`bid`, `price`, `gold`, `lid`, `income`, `defense`, `energy`, `discount`, `maintenance`, `max`, `bgid`, `ugid`) 
		VALUES ('1213', 0, '10', '198', '0', '1000', '0', '0', '0', '600', '12', '15');
		
INSERT INTO `building` (`bid`, `price`, `gold`, `lid`, `income`, `defense`, `energy`, `discount`, `maintenance`, `max`, `bgid`, `ugid`) 
		VALUES ('1214', 0, '10', '198', '0', '1150', '0', '0', '0', '600', '12', '16');
		
		
-- New Asteroid gold building

UPDATE  `building` SET  `lid` =  '227' WHERE  `building`.`bid` =1707;

INSERT INTO `building` (`bid`, `price`, `gold`, `lid`, `income`, `defense`, `energy`, `discount`, `maintenance`, `max`, `bgid`, `ugid`) 
		VALUES ('1710', 0, '10', '242', '0', '1100', '0', '0', '0', '600', '17', '19');
		
INSERT INTO `building` (`bid`, `price`, `gold`, `lid`, `income`, `defense`, `energy`, `discount`, `maintenance`, `max`, `bgid`, `ugid`) 
		VALUES ('1711', 0, '10', '242', '0', '1300', '0', '0', '0', '600', '17', '20');
		
INSERT INTO `building` (`bid`, `price`, `gold`, `lid`, `income`, `defense`, `energy`, `discount`, `maintenance`, `max`, `bgid`, `ugid`) 
		VALUES ('1712', 0, '10', '242', '0', '900', '0', '0', '0', '600', '17', '21');
		
INSERT INTO `building` (`bid`, `price`, `gold`, `lid`, `income`, `defense`, `energy`, `discount`, `maintenance`, `max`, `bgid`, `ugid`) 
		VALUES ('1713', 0, '10', '242', '0', '1000', '0', '0', '0', '600', '17', '22');