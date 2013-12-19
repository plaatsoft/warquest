-- Rebalance earth units
UPDATE unit SET attack=607 WHERE uid=127;
UPDATE unit SET attack=671 WHERE uid=128;
UPDATE unit SET attack=742 WHERE uid=228;
UPDATE unit SET attack=797 WHERE uid=229;
UPDATE unit SET attack=833 WHERE uid=326;
UPDATE unit SET attack=882 WHERE uid=327;
UPDATE unit SET attack=2048, defense=1955 WHERE uid=512;
UPDATE unit SET attack=2112, defense=1980 WHERE uid=513;

-- Rebalance earth buildings
UPDATE building SET defense=15 WHERE bid=2;
UPDATE building SET defense=45 WHERE bid=5;
UPDATE building SET defense=155 WHERE bid=11;
UPDATE building SET defense=260 WHERE bid=15;
UPDATE building SET defense=325 WHERE bid=56;

UPDATE building SET defense=15 WHERE bid=21;
UPDATE building SET defense=135 WHERE bid=22;
UPDATE building SET defense=200 WHERE bid=23;
UPDATE building SET defense=250 WHERE bid=57;

UPDATE building SET defense=50 WHERE bid=7;
UPDATE building SET defense=75 WHERE bid=9;
UPDATE building SET defense=150 WHERE bid=20;
UPDATE building SET defense=200 WHERE bid=58;

UPDATE building SET defense=125 WHERE bid=51;
UPDATE building SET defense=150 WHERE bid=52;
UPDATE building SET defense=225 WHERE bid=53;
UPDATE building SET defense=275 WHERE bid=54;
UPDATE building SET defense=325 WHERE bid=59;

-- Add twenty levels
INSERT INTO level (lid, experience, unit_lost, building_lost, planet) VALUES (280,1000000, 1, 1, 4);
INSERT INTO level (lid, experience, unit_lost, building_lost, planet) VALUES (281,1050000, 1, 1, 4);
INSERT INTO level (lid, experience, unit_lost, building_lost, planet) VALUES (282,1100000, 1, 1, 4);
INSERT INTO level (lid, experience, unit_lost, building_lost, planet) VALUES (283,1150000, 1, 1, 4);
INSERT INTO level (lid, experience, unit_lost, building_lost, planet) VALUES (284,1200000, 1, 1, 4);
INSERT INTO level (lid, experience, unit_lost, building_lost, planet) VALUES (285,1250000, 1, 1, 4);
INSERT INTO level (lid, experience, unit_lost, building_lost, planet) VALUES (286,1300000, 1, 1, 4);
INSERT INTO level (lid, experience, unit_lost, building_lost, planet) VALUES (287,1350000, 1, 1, 4);
INSERT INTO level (lid, experience, unit_lost, building_lost, planet) VALUES (288,1400000, 1, 1, 4);
INSERT INTO level (lid, experience, unit_lost, building_lost, planet) VALUES (289,1500000, 1, 1, 4);
INSERT INTO level (lid, experience, unit_lost, building_lost, planet) VALUES (290,1600000, 1, 1, 4);
INSERT INTO level (lid, experience, unit_lost, building_lost, planet) VALUES (291,1700000, 1, 1, 4);
INSERT INTO level (lid, experience, unit_lost, building_lost, planet) VALUES (292,1800000, 1, 1, 4);
INSERT INTO level (lid, experience, unit_lost, building_lost, planet) VALUES (293,1900000, 1, 1, 4);
INSERT INTO level (lid, experience, unit_lost, building_lost, planet) VALUES (294,2000000, 1, 1, 4);
INSERT INTO level (lid, experience, unit_lost, building_lost, planet) VALUES (295,2200000, 1, 1, 4);
INSERT INTO level (lid, experience, unit_lost, building_lost, planet) VALUES (296,2400000, 1, 1, 4);
INSERT INTO level (lid, experience, unit_lost, building_lost, planet) VALUES (297,2600000, 1, 1, 4);
INSERT INTO level (lid, experience, unit_lost, building_lost, planet) VALUES (298,2800000, 1, 1, 4);
INSERT INTO level (lid, experience, unit_lost, building_lost, planet) VALUES (299,3000000, 1, 1, 4);

-- Rebalance moon units
UPDATE unit SET attack=788 WHERE uid=710;
UPDATE unit SET attack=904 WHERE uid=711;
UPDATE unit SET attack=200 WHERE uid=807;
UPDATE unit SET attack=250 WHERE uid=808;
UPDATE unit SET attack=300 WHERE uid=809;
UPDATE unit SET attack=386 WHERE uid=810;
UPDATE unit SET attack=489 WHERE uid=811;
UPDATE unit SET attack=5384 WHERE uid=916;
UPDATE unit SET attack=5488 WHERE uid=917;
UPDATE unit SET attack=2736 WHERE uid=1211;
UPDATE unit SET attack=2918 WHERE uid=1212;

-- Rebalance moon buildings
UPDATE building SET defense=350 WHERE bid=708;
UPDATE building SET defense=450 WHERE bid=718;


-- Rebalance mars units
UPDATE unit SET attack=888 WHERE uid=1309;
UPDATE unit SET attack=1045 WHERE uid=1310;
UPDATE unit SET attack=1928 WHERE uid=1409;
UPDATE unit SET attack=2092 WHERE uid=1410;
UPDATE unit SET attack=3600 WHERE uid=1507;
UPDATE unit SET attack=3858 WHERE uid=1509;
UPDATE unit SET attack=4028 WHERE uid=1510;
UPDATE unit SET attack=2022 WHERE uid=1609;
UPDATE unit SET attack=2210 WHERE uid=1610;

-- Rebalance asteroid buildings
UPDATE building SET defense=450 WHERE bid=1701;

-- Rebalance asteroid units
UPDATE unit SET attack=650 WHERE uid=1907;
UPDATE unit SET attack=790 WHERE uid=1909;
UPDATE unit SET attack=1022 WHERE uid=1910;

UPDATE unit SET attack=1200 WHERE uid=2006;
UPDATE unit SET attack=1600 WHERE uid=2007;
UPDATE unit SET attack=1982 WHERE uid=2009;
UPDATE unit SET attack=2188 WHERE uid=2010;

UPDATE unit SET attack=3300 WHERE uid=2106;
UPDATE unit SET attack=2800 WHERE uid=2107;
UPDATE unit SET attack=3400 WHERE uid=2108;
UPDATE unit SET attack=3756 WHERE uid=2109;
UPDATE unit SET attack=3914 WHERE uid=2110;

UPDATE unit SET attack=1000 WHERE uid=2205;
UPDATE unit SET attack=1200 WHERE uid=2206;
UPDATE unit SET attack=1500 WHERE uid=2207;
UPDATE unit SET attack=1700 WHERE uid=2208;
UPDATE unit SET attack=1974 WHERE uid=2209;
UPDATE unit SET attack=2144 WHERE uid=2210;
