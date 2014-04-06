--
-- WarQuest v6.8 data model patch
--

ALTER TABLE clan ADD logo INT NOT NULL AFTER mission;
ALTER TABLE clan ADD min_level INT NOT NULL AFTER logo;

UPDATE clan SET logo=1;