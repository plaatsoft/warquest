-- Add commercial options

ALTER TABLE `building` ADD `gold` INT NOT NULL AFTER `price` ;
ALTER TABLE `unit` ADD `gold` INT NOT NULL AFTER `price`;