--
-- WarQuest v6.1 data model patch
--

UPDATE building_group SET planet=4 WHERE planet=3;
UPDATE building_group SET planet=3 WHERE planet=2;
UPDATE building_group SET planet=2 WHERE planet=1;
UPDATE building_group SET planet=1 WHERE planet=0;

UPDATE level SET planet=4 WHERE planet=3;
UPDATE level SET planet=3 WHERE planet=2;
UPDATE level SET planet=2 WHERE planet=1;
UPDATE level SET planet=1 WHERE planet=0;

UPDATE mission_group SET planet=4 WHERE planet=3;
UPDATE mission_group SET planet=3 WHERE planet=2;
UPDATE mission_group SET planet=2 WHERE planet=1;
UPDATE mission_group SET planet=1 WHERE planet=0;

-- Remove players from sun, if any found
UPDATE player SET planet=0 WHERE planet=4;

UPDATE player SET planet=4 WHERE planet=3;
UPDATE player SET planet=3 WHERE planet=2;
UPDATE player SET planet=2 WHERE planet=1;
UPDATE player SET planet=1 WHERE planet=0;

UPDATE sector SET planet=4 WHERE planet=3;
UPDATE sector SET planet=3 WHERE planet=2;
UPDATE sector SET planet=2 WHERE planet=1;
UPDATE sector SET planet=1 WHERE planet=0;

UPDATE unit_group SET planet=4 WHERE planet=3;
UPDATE unit_group SET planet=3 WHERE planet=2;
UPDATE unit_group SET planet=2 WHERE planet=1;
UPDATE unit_group SET planet=1 WHERE planet=0;

