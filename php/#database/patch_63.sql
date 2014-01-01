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
UPDATE level SET experience=1250000 WHERE lid=286;
UPDATE level SET experience=1275000 WHERE lid=287;
UPDATE level SET experience=1300000 WHERE lid=288;
UPDATE level SET experience=1325000 WHERE lid=289;
UPDATE level SET experience=1350000 WHERE lid=290;
UPDATE level SET experience=1375000 WHERE lid=291;
UPDATE level SET experience=1400000 WHERE lid=292;
UPDATE level SET experience=1425000 WHERE lid=293;
UPDATE level SET experience=1450000 WHERE lid=294;
UPDATE level SET experience=1475000 WHERE lid=295;
UPDATE level SET experience=1500000 WHERE lid=296;
UPDATE level SET experience=1525000 WHERE lid=297;
UPDATE level SET experience=1550000 WHERE lid=298;
UPDATE level SET experience=1575000 WHERE lid=299;

ALTER TABLE sector ADD conquer_date DATETIME NOT NULL AFTER damage;

INSERT INTO cron (cid, note, last_run) VALUES (10, 'Clear inactive sectors', '0000-00-00 00:00:00');

ALTER TABLE player_clan ADD approved INT NOT NULL AFTER joined;

update player_clan set approved=1;