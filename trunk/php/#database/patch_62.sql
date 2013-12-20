--
-- WarQuest v6.2 data model patch
--

-- Rebalance earth units
UPDATE unit SET attack=549, defense=450 WHERE uid=126;
UPDATE unit SET attack=607, defense=550 WHERE uid=127;
UPDATE unit SET attack=671, defense=575 WHERE uid=128;

UPDATE unit SET attack=525, defense=600 WHERE uid=227;
UPDATE unit SET attack=742, defense=700 WHERE uid=228;
UPDATE unit SET attack=797, defense=725 WHERE uid=229;

UPDATE unit SET attack=699, defense=500 WHERE uid=324;
UPDATE unit SET attack=735, defense=600 WHERE uid=325;
UPDATE unit SET attack=833, defense=800 WHERE uid=326;
UPDATE unit SET attack=882, defense=825 WHERE uid=327;

UPDATE unit SET attack=1024, defense=1024 WHERE uid=511;
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
UPDATE unit SET attack=789 WHERE uid=710;
UPDATE unit SET attack=903 WHERE uid=711;

UPDATE unit SET attack=200 WHERE uid=807;
UPDATE unit SET attack=250 WHERE uid=808;
UPDATE unit SET attack=300 WHERE uid=809;
UPDATE unit SET attack=361 WHERE uid=810;
UPDATE unit SET attack=489 WHERE uid=811;

UPDATE unit SET attack=5384 WHERE uid=916;
UPDATE unit SET attack=5488 WHERE uid=917;

UPDATE unit SET attack=2736 WHERE uid=1211;
UPDATE unit SET attack=2918 WHERE uid=1212;

-- Rebalance moon buildings
UPDATE building SET defense=250 WHERE bid=701;
UPDATE building SET defense=300 WHERE bid=704;
UPDATE building SET defense=450 WHERE bid=707;
UPDATE building SET defense=550 WHERE bid=710;
UPDATE building SET defense=650 WHERE bid=717;

UPDATE building SET defense=100 WHERE bid=700;
UPDATE building SET defense=250 WHERE bid=703;
UPDATE building SET defense=350 WHERE bid=706;
UPDATE building SET defense=450 WHERE bid=709;
UPDATE building SET defense=550 WHERE bid=716;

UPDATE building SET defense=350 WHERE bid=708;
UPDATE building SET defense=450 WHERE bid=718;

UPDATE building SET defense=1000 WHERE bid=714;

-- Rebalance mars units
UPDATE unit SET attack=888 WHERE uid=1309;
UPDATE unit SET attack=1054, defense=700 WHERE uid=1310;

UPDATE unit SET attack=1928 WHERE uid=1409;
UPDATE unit SET attack=2092 WHERE uid=1410;

UPDATE unit SET attack=3000, defense=3600 WHERE uid=1507;
UPDATE unit SET attack=3858 WHERE uid=1509;
UPDATE unit SET attack=4028, defense=3650 WHERE uid=1510;

UPDATE unit SET attack=2022 WHERE uid=1609;
UPDATE unit SET attack=2210 WHERE uid=1610;

-- Rebalance asteroid buildings
UPDATE building SET defense=450 WHERE bid=1701;

-- Rebalance asteroid units
UPDATE unit SET attack=650 WHERE uid=1907;
UPDATE unit SET attack=790 WHERE uid=1909;
UPDATE unit SET attack=1022, defense=650 WHERE uid=1910;

UPDATE unit SET attack=1200 WHERE uid=2006;
UPDATE unit SET attack=1600 WHERE uid=2007;
UPDATE unit SET attack=1982 WHERE uid=2009;
UPDATE unit SET attack=2188 WHERE uid=2010;

UPDATE unit SET attack=3300 WHERE uid=2106;
UPDATE unit SET attack=2800, defense=3600 WHERE uid=2107;
UPDATE unit SET attack=3400 WHERE uid=2108;
UPDATE unit SET attack=3756 WHERE uid=2109;
UPDATE unit SET attack=3914, defense=3650 WHERE uid=2110;

UPDATE unit SET attack=1000 WHERE uid=2205;
UPDATE unit SET attack=1200 WHERE uid=2206;
UPDATE unit SET attack=1500 WHERE uid=2207;
UPDATE unit SET attack=1700 WHERE uid=2208;
UPDATE unit SET attack=1974 WHERE uid=2209;
UPDATE unit SET attack=2144 WHERE uid=2210;


-- Increase building max to 645
UPDATE building SET max=645 WHERE max=600;

-- Increase unit max to 5382
UPDATE unit SET max=5382 WHERE max=5000;

-- Added Neptune unit groups
INSERT INTO unit_group (ugid , planet , type) VALUES ( 25, 5, 2);
INSERT INTO unit_group (ugid , planet , type) VALUES ( 26, 5, 3);
INSERT INTO unit_group (ugid , planet , type) VALUES ( 27, 5, 4);
INSERT INTO unit_group (ugid , planet , type) VALUES ( 28, 5, 5);
INSERT INTO unit_group (ugid , planet , type) VALUES ( 29, 5, 6);
INSERT INTO unit_group (ugid , planet , type) VALUES ( 30, 5, 0);

-- Added Neptune building groups
INSERT INTO building_group ( bgid, planet, sell, type ) VALUES ( 21, 5, 1, 1);
INSERT INTO building_group ( bgid, planet, sell, type ) VALUES ( 22, 5, 1, 2);
INSERT INTO building_group ( bgid, planet, sell, type ) VALUES ( 23, 5, 0, 3);
INSERT INTO building_group ( bgid, planet, sell, type ) VALUES ( 24, 5, 0, 4);
INSERT INTO building_group ( bgid, planet, sell, type ) VALUES ( 25, 5, 0, 5);

-- Added Neptune mission groups
INSERT INTO mission_group (mgid , planet ) VALUES ( 40, 5 );
INSERT INTO mission_group (mgid , planet ) VALUES ( 41, 5 );
INSERT INTO mission_group (mgid , planet ) VALUES ( 42, 5 );
INSERT INTO mission_group (mgid , planet ) VALUES ( 43, 5 );
INSERT INTO mission_group (mgid , planet ) VALUES ( 44, 5 );
INSERT INTO mission_group (mgid , planet ) VALUES ( 45, 5 );
INSERT INTO mission_group (mgid , planet ) VALUES ( 46, 5 );
INSERT INTO mission_group (mgid , planet ) VALUES ( 47, 5 );
INSERT INTO mission_group (mgid , planet ) VALUES ( 48, 5 );

UPDATE mission_group SET planet=0 WHERE mgid=0;

-- Update level for Neptune planet
UPDATE level set planet=5 where lid>=250; 

-- Added neptune clan war sector data
INSERT INTO `sector` (`sid`, `x`, `y`, `planet`, `cid`, `damage`, `mid`) VALUES
(401, 0, 0, 5, 0, 0, 400),
(402, 0, 1, 5, 0, 0, 401),
(403, 0, 2, 5, 0, 0, 402),
(404, 0, 3, 5, 0, 0, 403),
(405, 0, 4, 5, 0, 0, 404),
(406, 0, 5, 5, 0, 0, 405),
(407, 0, 6, 5, 0, 0, 406),
(408, 0, 7, 5, 0, 0, 407),
(409, 0, 8, 5, 0, 0, 410),
(410, 0, 9, 5, 0, 0, 411),
(411, 0, 10, 5, 0, 0, 412),
(412, 0, 11, 5, 0, 0, 413),
(413, 0, 12, 5, 0, 0, 414),
(414, 0, 13, 5, 0, 0, 415),
(415, 0, 14, 5, 0, 0, 416),
(416, 1, 0, 5, 0, 0, 417),
(417, 1, 1, 5, 0, 0, 420),
(418, 1, 2, 5, 0, 0, 421),
(419, 1, 3, 5, 0, 0, 422),
(420, 1, 4, 5, 0, 0, 423),
(421, 1, 5, 5, 0, 0, 424),
(422, 1, 6, 5, 0, 0, 425),
(423, 1, 7, 5, 0, 0, 426),
(424, 1, 8, 5, 0, 0, 427),
(425, 1, 9, 5, 0, 0, 430),
(426, 1, 10, 5, 0, 0, 431),
(427, 1, 11, 5, 0, 0, 432),
(428, 1, 12, 5, 0, 0, 433),
(429, 1, 13, 5, 0, 0, 434),
(430, 1, 14, 5, 0, 0, 435),
(431, 2, 0, 5, 0, 0, 436),
(432, 2, 1, 5, 0, 0, 437),
(433, 2, 2, 5, 0, 0, 440),
(434, 2, 3, 5, 0, 0, 441),
(435, 2, 4, 5, 0, 0, 442),
(436, 2, 5, 5, 0, 0, 443),
(437, 2, 7, 5, 0, 0, 444),
(438, 2, 6, 5, 0, 0, 445),
(439, 2, 8, 5, 0, 0, 446),
(440, 2, 9, 5, 0, 0, 447),
(441, 2, 10, 5, 0, 0, 450),
(442, 2, 11, 5, 0, 0, 451),
(443, 2, 12, 5, 0, 0, 452),
(444, 2, 13, 5, 0, 0, 453),
(445, 2, 14, 5, 0, 0, 454),
(446, 3, 0, 5, 0, 0, 455),
(447, 3, 1, 5, 0, 0, 456),
(448, 3, 2, 5, 0, 0, 457),
(449, 3, 3, 5, 0, 0, 460),
(450, 3, 4, 5, 0, 0, 461),
(451, 3, 5, 5, 0, 0, 462),
(452, 3, 6, 5, 0, 0, 463),
(453, 3, 7, 5, 0, 0, 464),
(454, 3, 8, 5, 0, 0, 465),
(455, 3, 9, 5, 0, 0, 466),
(456, 3, 10, 5, 0, 0, 467),
(457, 3, 11, 5, 0, 0, 470),
(458, 3, 12, 5, 0, 0, 471),
(459, 3, 13, 5, 0, 0, 472),
(460, 3, 14, 5, 0, 0, 473),
(461, 4, 0, 5, 0, 0, 474),
(462, 4, 1, 5, 0, 0, 475),
(463, 4, 2, 5, 0, 0, 476),
(464, 4, 3, 5, 0, 0, 477),
(465, 4, 4, 5, 0, 0, 480),
(466, 4, 5, 5, 0, 0, 481),
(467, 4, 6, 5, 0, 0, 482),
(468, 4, 7, 5, 0, 0, 483),
(469, 4, 8, 5, 0, 0, 484),
(470, 4, 9, 5, 0, 0, 485),
(471, 4, 10, 5, 0, 0, 486),
(472, 4, 11, 5, 0, 0, 487),
(473, 4, 12, 5, 0, 0, 487),
(474, 4, 13, 5, 0, 0, 487),
(475, 4, 14, 5, 0, 0, 487);

/* Added neptune units */
INSERT INTO unit (uid, lid, price, gold, attack, defense, max, ugid, upkeep) VALUES

(2400, 250, 15000000, 0, 300, 100, 5382, 25, 15000),
(2401, 252, 17500000, 0, 315, 115, 5382, 25, 17000),
(2402, 257, 20200000, 0, 250, 225, 5382, 25, 19000),
(2403, 261, 24000000, 0, 350, 255, 5382, 25, 21000),
(2404, 268, 32600000, 0, 400, 135, 5382, 25, 23000),
(2405, 273, 35500000, 0, 375, 375, 5382, 25, 26000),
(2406, 276, 41000000, 0, 475, 450, 5382, 25, 28000),
(2407, 278, 46000000, 0, 525, 350, 5382, 25, 30000),
(2408, 280, 55000000, 0, 650, 350, 5382, 25, 45000),
(2409, 285, 0, 10, 790, 475, 5382, 25, 50000),

(2500, 251, 5000000, 0, 125, 125, 5382, 26, 10000),
(2501, 260, 8500000, 0, 250, 150, 5382, 26, 50000),
(2502, 262, 10000000, 0, 400, 250, 5382, 26, 55000),
(2503, 267, 14200000, 0, 650, 750, 5382, 260, 65000),
(2504, 272, 18500000, 0, 800, 900, 5382, 26, 70000),
(2505, 277, 20000000, 0, 1000, 750, 5382, 26, 80000),
(2506, 279, 32000000, 0, 1200, 900, 5382, 26, 90000),
(2507, 281, 42000000, 0, 1600, 1750, 5382, 26, 100000),
(2508, 283, 48000000, 0, 1900, 1250, 5382, 26, 110000),
(2509, 287, 0, 10, 2100, 1800, 5382, 26, 120000),

(2600, 253, 100000000, 0, 1000, 900, 5382, 27, 150000),
(2601, 258, 150000000, 0, 1250, 1100, 5382, 27, 180000),
(2602, 261, 220000000, 0, 1600, 1300, 5382, 27, 200000),
(2603, 263, 260000000, 0, 1050, 2000, 5382, 27, 250000),
(2604, 267, 320000000, 0, 2000, 1800, 5382, 27, 500000),
(2605, 275, 350000000, 0, 2500, 2050, 5382, 27, 600000),
(2606, 276, 380000000, 0, 3300, 2400, 5382, 27, 800000),
(2607, 279, 430000000, 0, 2800, 3200, 5382, 27, 150000),
(2608, 281, 480000000, 0, 3400, 2400, 5382, 27, 225000),
(2609, 283, 0, 10, 3700, 3400, 5382, 27, 350000),

(2700, 254, 20000000, 0, 50, 200, 5382, 28, 25000),
(2701, 259, 35000000, 0, 100, 400, 5382, 28, 27000),
(2702, 264, 40000000, 0, 200, 150, 5382, 28, 35000),
(2703, 266, 55000000, 0, 300, 400, 5382, 28, 40000),
(2704, 269, 60000000, 0, 500, 400, 5382, 28, 50000),
(2705, 272, 80000000, 0, 1000, 600, 5382, 28, 75000),
(2706, 276, 100000000, 0, 1200, 1200, 5382, 28, 100000),
(2707, 279, 150000000, 0, 1500, 1800, 5382, 28, 150000),
(2708, 284, 225000000, 0, 1700, 1000, 5382, 28, 200000),
(2709, 286, 0, 10, 2000, 1850, 5382, 28, 250000),

(2800, 0, 0, 0, 0, 0, 0, 29, 120),
(2801, 0, 0, 0, 0, 0, 0, 29, 140),
(2802, 0, 0, 0, 0, 0, 0, 29, 160);