-- Update statistics

ALTER TABLE `statistics` CHANGE `ads` `gold` INT( 11 ) NOT NULL;

UPDATE `statistics` SET gold = 0;