-- Add commercial options

ALTER TABLE `building` ADD `gold` INT NOT NULL AFTER `price` ;
ALTER TABLE `unit` ADD `gold` INT NOT NULL AFTER `price`;
ALTER TABLE `player` ADD `gold` INT NOT NULL AFTER `money_date`;

INSERT INTO `building` (`bid`, `price`, `gold`, `lid`, `income`, `defense`, `energy`, `discount`, `maintenance`, `max`, `bgid`, `ugid`) 
		VALUES ('56', 0, '10', '40', '0', '500', '0', '0', '0', '600', '2', '2');
		
INSERT INTO building_unit (`bid` ,`uid` ,`amount`) VALUES ( '56', '401', '50');
INSERT INTO building_unit (`bid` ,`uid` ,`amount`) VALUES ( '56', '402', '50');
INSERT INTO building_unit (`bid` ,`uid` ,`amount`) VALUES ( '56', '404', '250');

INSERT INTO `building` (`bid`, `price`, `gold`, `lid`, `income`, `defense`, `energy`, `discount`, `maintenance`, `max`, `bgid`, `ugid`) 
		VALUES ('57', 0, '10', '41', '0', '500', '0', '0', '0', '600', '2', '3');
		
INSERT INTO building_unit (`bid` ,`uid` ,`amount`) VALUES ( '57', '401', '50');
INSERT INTO building_unit (`bid` ,`uid` ,`amount`) VALUES ( '57', '402', '50');
INSERT INTO building_unit (`bid` ,`uid` ,`amount`) VALUES ( '57', '404', '250');

INSERT INTO `building` (`bid`, `price`, `gold`, `lid`, `income`, `defense`, `energy`, `discount`, `maintenance`, `max`, `bgid`, `ugid`) 
		VALUES ('58', 0, '10', '41', '0', '500', '0', '0', '0', '600', '2', '4');
		
INSERT INTO building_unit (`bid` ,`uid` ,`amount`) VALUES ( '58', '401', '50');
INSERT INTO building_unit (`bid` ,`uid` ,`amount`) VALUES ( '58', '403', '50');
INSERT INTO building_unit (`bid` ,`uid` ,`amount`) VALUES ( '58', '405', '250');

UPDATE `warquest`.`building` SET `lid` = '42' WHERE `building`.`bid` =54;

INSERT INTO `building` (`bid`, `price`, `gold`, `lid`, `income`, `defense`, `energy`, `discount`, `maintenance`, `max`, `bgid`, `ugid`) 
		VALUES ('59', 0, '10', '45', '0', '750', '0', '0', '0', '600', '2', '6');
		
INSERT INTO building_unit (`bid` ,`uid` ,`amount`) VALUES ( '59', '401', '50');
INSERT INTO building_unit (`bid` ,`uid` ,`amount`) VALUES ( '59', '403', '50');
INSERT INTO building_unit (`bid` ,`uid` ,`amount`) VALUES ( '59', '405', '250');