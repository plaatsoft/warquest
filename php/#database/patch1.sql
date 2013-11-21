-- phpMyAdmin SQL Dump
-- version 3.5.1
-- http://www.phpmyadmin.net
--
-- Machine: localhost
-- Genereertijd: 08 nov 2013 om 06:16
-- Serverversie: 5.5.24-log
-- PHP-versie: 5.4.3

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Databank: `warquest`
--

-- --------------------------------------------------------

--
-- Tabelstructuur voor tabel `clan`
--

CREATE TABLE IF NOT EXISTS `clan` UPDATE mission (`sid`, `mid`) VALUES (
  `cid` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(6) NOT NULL,
  `date` date NOT NULL,
  `pid` int(11) NOT NULL,
  PRIMARY KEY (`cid`),
  UNIQUE KEY `cid` (`cid`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=3 ;

--
-- Gegevens worden uitgevoerd voor tabel `clan`
--

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;




-- phpMyAdmin SQL Dump
-- version 3.5.1
-- http://www.phpmyadmin.net
--
-- Machine: localhost
-- Genereertijd: 08 nov 2013 om 06:17
-- Serverversie: 5.5.24-log
-- PHP-versie: 5.4.3

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Databank: `warquest`
--

-- --------------------------------------------------------

--
-- Tabelstructuur voor tabel `player_clan`
--

CREATE TABLE IF NOT EXISTS `player_clan` (
  `pid` int(11) NOT NULL,
  `cid` int(11) NOT NULL,
  `date` date NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Gegevens worden uitgevoerd voor tabel `player_clan`
--

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;

DELETE FROM mission_group WHERE mgid = 40;
DELETE FROM mission_group WHERE mgid = 41;
DELETE FROM mission_group WHERE mgid = 42;
DELETE FROM mission_group WHERE mgid = 43;
DELETE FROM mission_group WHERE mgid = 44;
DELETE FROM mission_group WHERE mgid = 45;
DELETE FROM mission_group WHERE mgid = 46;
DELETE FROM mission_group WHERE mgid = 47;
DELETE FROM mission_group WHERE mgid = 48;

DELETE FROM mission WHERE mid >= 400;

DELETE FROM player_mission WHERE mid >= 400;

CREATE TABLE IF NOT EXISTS sector (
  `sid` int(11) NOT NULL AUTO_INCREMENT,
  `x` int(11) NOT NULL,
  `y` int(11) NOT NULL,
  `planet` int(11) DEFAULT NULL,
  `cid` int(11) DEFAULT NULL,
  `damage` int(11) NOT NULL,
  PRIMARY KEY (`sid`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=0;


INSERT INTO `sector` (`sid`, `x`, `y`, `cid`, `planet`, `damage`) VALUES
(1, 0, 0, 0, 0, 0),
(2, 0, 1, 0, 0, 0),
(3, 0, 2, 0, 0, 0),
(4, 0, 3, 0, 0, 0),
(5, 0, 4, 0, 0, 0),
(6, 0, 5, 0, 0, 0),
(7, 0, 6, 0, 0, 0),
(8, 0, 7, 0, 0, 0),
(9, 0, 8, 0, 0, 0),
(10, 0, 9, 0, 0, 0),
(11, 0, 10, 0, 0, 0),
(12, 0, 11, 0, 0, 0),
(13, 0, 12, 0, 0, 0),
(14, 0, 13, 0, 0, 0),
(15, 0, 14, 0, 0, 0),
(16, 1, 0, 0, 0, 0),
(17, 1, 1, 0, 0, 0),
(18, 1, 2, 0, 0, 0),
(19, 1, 3, 0, 0, 0),
(20, 1, 4, 0, 0, 0),
(21, 1, 5, 0, 0, 0),
(22, 1, 6, 0, 0, 0),
(23, 1, 7, 0, 0, 0),
(24, 1, 8, 0, 0, 0),
(25, 1, 9, 0, 0, 0),
(26, 1, 10, 0, 0, 0),
(27, 1, 11, 0, 0, 0),
(28, 1, 12, 0, 0, 0),
(29, 1, 13, 0, 0, 0),
(30, 1, 14, 0, 0, 0),
(31, 2, 0, 0, 0, 0),
(32, 2, 1, 0, 0, 0),
(33, 2, 2, 0, 0, 0),
(34, 2, 3, 0, 0, 0),
(35, 2, 4, 0, 0, 0),
(36, 2, 5, 0, 0, 0),
(37, 2, 7, 0, 0, 0),
(38, 2, 6, 0, 0, 0),
(39, 2, 8, 0, 0, 0),
(40, 2, 9, 0, 0, 0),
(41, 2, 10, 0, 0, 0),
(42, 2, 11, 0, 0, 0),
(43, 2, 12, 0, 0, 0),
(44, 2, 13, 0, 0, 0),
(45, 2, 14, 0, 0, 0),
(46, 3, 0, 0, 0, 0),
(47, 3, 1, 0, 0, 0),
(48, 3, 2, 0, 0, 0),
(49, 3, 3, 0, 0, 0),
(50, 3, 4, 0, 0, 0),
(51, 3, 5, 0, 0, 0),
(52, 3, 6, 0, 0, 0),
(53, 3, 7, 0, 0, 0),
(54, 3, 8, 0, 0, 0),
(55, 3, 9, 0, 0, 0),
(56, 3, 10, 0, 0, 0),
(57, 3, 11, 0, 0, 0),
(58, 3, 12, 0, 0, 0),
(59, 3, 13, 0, 0, 0),
(60, 3, 14, 0, 0, 0),
(61, 4, 0, 0, 0, 0),
(62, 4, 1, 0, 0, 0),
(63, 4, 2, 0, 0, 0),
(64, 4, 3, 0, 0, 0),
(65, 4, 4, 0, 0, 0),
(66, 4, 5, 0, 0, 0),
(67, 4, 6, 0, 0, 0),
(68, 4, 7, 0, 0, 0),
(69, 4, 8, 0, 0, 0),
(70, 4, 9, 0, 0, 0),
(71, 4, 10, 0, 0, 0),
(72, 4, 11, 0, 0, 0),
(73, 4, 12, 0, 0, 0),
(74, 4, 13, 0, 0, 0),
(75, 4, 14, 0, 0, 0);


INSERT INTO sector (`sid`, `x`, `y`, `cid`, `planet`, `damage`) VALUES
(101, 0, 0, 0, 1, 0),
(102, 0, 1, 0, 1, 0),
(103, 0, 2, 0, 1, 0),
(104, 0, 3, 0, 1, 0),
(105, 0, 4, 0, 1, 0),
(106, 0, 5, 0, 1, 0),
(107, 0, 6, 0, 1, 0),
(108, 0, 7, 0, 1, 0),
(109, 0, 8, 0, 1, 0),
(110, 0, 9, 0, 1, 0),
(111, 0, 10, 0, 1, 0),
(112, 0, 11, 0, 1, 0),
(113, 0, 12, 0, 1, 0),
(114, 0, 13, 0, 1, 0),
(115, 0, 14, 0, 1, 0),
(116, 1, 0, 0, 1, 0),
(117, 1, 1, 0, 1, 0),
(118, 1, 2, 0, 1, 0),
(119, 1, 3, 0, 1, 0),
(120, 1, 4, 0, 1, 0),
(121, 1, 5, 0, 1, 0),
(122, 1, 6, 0, 1, 0),
(123, 1, 7, 0, 1, 0),
(124, 1, 8, 0, 1, 0),
(125, 1, 9, 0, 1, 0),
(126, 1, 10, 0, 1, 0),
(127, 1, 11, 0, 1, 0),
(128, 1, 12, 0, 1, 0),
(129, 1, 13, 0, 1, 0),
(130, 1, 14, 0, 1, 0),
(131, 2, 0, 0, 1, 0),
(132, 2, 1, 0, 1, 0),
(133, 2, 2, 0, 1, 0),
(134, 2, 3, 0, 1, 0),
(135, 2, 4, 0, 1, 0),
(136, 2, 5, 0, 1, 0),
(137, 2, 7, 0, 1, 0),
(138, 2, 6, 0, 1, 0),
(139, 2, 8, 0, 1, 0),
(140, 2, 9, 0, 1, 0),
(141, 2, 10, 0, 1, 0),
(142, 2, 11, 0, 1, 0),
(143, 2, 12, 0, 1, 0),
(144, 2, 13, 0, 1, 0),
(145, 2, 14, 0, 1, 0),
(146, 3, 0, 0, 1, 0),
(147, 3, 1, 0, 1, 0),
(148, 3, 2, 0, 1, 0),
(149, 3, 3, 0, 1, 0),
(150, 3, 4, 0, 1, 0),
(151, 3, 5, 0, 1, 0),
(152, 3, 6, 0, 1, 0),
(153, 3, 7, 0, 1, 0),
(154, 3, 8, 0, 1, 0),
(155, 3, 9, 0, 1, 0),
(156, 3, 10, 0, 1, 0),
(157, 3, 11, 0, 1, 0),
(158, 3, 12, 0, 1, 0),
(159, 3, 13, 0, 1, 0),
(160, 3, 14, 0, 1, 0),
(161, 4, 0, 0, 1, 0),
(162, 4, 1, 0, 1, 0),
(163, 4, 2, 0, 1, 0),
(164, 4, 3, 0, 1, 0),
(165, 4, 4, 0, 1, 0),
(166, 4, 5, 0, 1, 0),
(167, 4, 6, 0, 1, 0),
(168, 4, 7, 0, 1, 0),
(169, 4, 8, 0, 1, 0),
(170, 4, 9, 0, 1, 0),
(171, 4, 10, 0, 1, 0),
(172, 4, 11, 0, 1, 0),
(173, 4, 12, 0, 1, 0),
(174, 4, 13, 0, 1, 0),
(175, 4, 14, 0, 1, 0);


INSERT INTO sector (`sid`, `x`, `y`, `cid`, `planet`, `damage`) VALUES
(201, 0, 0, 0, 2, 0),
(202, 0, 1, 0, 2, 0),
(203, 0, 2, 0, 2, 0),
(204, 0, 3, 0, 2, 0),
(205, 0, 4, 0, 2, 0),
(206, 0, 5, 0, 2, 0),
(207, 0, 6, 0, 2, 0),
(208, 0, 7, 0, 2, 0),
(209, 0, 8, 0, 2, 0),
(210, 0, 9, 0, 2, 0),
(211, 0, 10, 0, 2, 0),
(212, 0, 11, 0, 2, 0),
(213, 0, 12, 0, 2, 0),
(214, 0, 13, 0, 2, 0),
(215, 0, 14, 0, 2, 0),
(216, 1, 0, 0, 2, 0),
(217, 1, 1, 0, 2, 0),
(218, 1, 2, 0, 2, 0),
(219, 1, 3, 0, 2, 0),
(220, 1, 4, 0, 2, 0),
(221, 1, 5, 0, 2, 0),
(222, 1, 6, 0, 2, 0),
(223, 1, 7, 0, 2, 0),
(224, 1, 8, 0, 2, 0),
(225, 1, 9, 0, 2, 0),
(226, 1, 10, 0, 2, 0),
(227, 1, 11, 0, 2, 0),
(228, 1, 12, 0, 2, 0),
(229, 1, 13, 0, 2, 0),
(230, 1, 14, 0, 2, 0),
(231, 2, 0, 0, 2, 0),
(232, 2, 1, 0, 2, 0),
(233, 2, 2, 0, 2, 0),
(234, 2, 3, 0, 2, 0),
(235, 2, 4, 0, 2, 0),
(236, 2, 5, 0, 2, 0),
(237, 2, 7, 0, 2, 0),
(238, 2, 6, 0, 2, 0),
(239, 2, 8, 0, 2, 0),
(240, 2, 9, 0, 2, 0),
(241, 2, 10, 0, 2, 0),
(242, 2, 11, 0, 2, 0),
(243, 2, 12, 0, 2, 0),
(244, 2, 13, 0, 2, 0),
(245, 2, 14, 0, 2, 0),
(246, 3, 0, 0, 2, 0),
(247, 3, 1, 0, 2, 0),
(248, 3, 2, 0, 2, 0),
(249, 3, 3, 0, 2, 0),
(250, 3, 4, 0, 2, 0),
(251, 3, 5, 0, 2, 0),
(252, 3, 6, 0, 2, 0),
(253, 3, 7, 0, 2, 0),
(254, 3, 8, 0, 2, 0),
(255, 3, 9, 0, 2, 0),
(256, 3, 10, 0, 2, 0),
(257, 3, 11, 0, 2, 0),
(258, 3, 12, 0, 2, 0),
(259, 3, 13, 0, 2, 0),
(260, 3, 14, 0, 2, 0),
(261, 4, 0, 0, 2, 0),
(262, 4, 1, 0, 2, 0),
(263, 4, 2, 0, 2, 0),
(264, 4, 3, 0, 2, 0),
(265, 4, 4, 0, 2, 0),
(266, 4, 5, 0, 2, 0),
(267, 4, 6, 0, 2, 0),
(268, 4, 7, 0, 2, 0),
(269, 4, 8, 0, 2, 0),
(270, 4, 9, 0, 2, 0),
(271, 4, 10, 0, 2, 0),
(272, 4, 11, 0, 2, 0),
(273, 4, 12, 0, 2, 0),
(274, 4, 13, 0, 2, 0),
(275, 4, 14, 0, 2, 0);



INSERT INTO sector (`sid`, `x`, `y`, `cid`, `planet`, `damage`) VALUES
(301, 0, 0, 0, 3, 0),
(302, 0, 1, 0, 3, 0),
(303, 0, 2, 0, 3, 0),
(304, 0, 3, 0, 3, 0),
(305, 0, 4, 0, 3, 0),
(306, 0, 5, 0, 3, 0),
(307, 0, 6, 0, 3, 0),
(308, 0, 7, 0, 3, 0),
(309, 0, 8, 0, 3, 0),
(310, 0, 9, 0, 3, 0),
(311, 0, 10, 0, 3, 0),
(312, 0, 11, 0, 3, 0),
(313, 0, 12, 0, 3, 0),
(314, 0, 13, 0, 3, 0),
(315, 0, 14, 0, 3, 0),
(316, 1, 0, 0, 3, 0),
(317, 1, 1, 0, 3, 0),
(318, 1, 2, 0, 3, 0),
(319, 1, 3, 0, 3, 0),
(320, 1, 4, 0, 3, 0),
(321, 1, 5, 0, 3, 0),
(322, 1, 6, 0, 3, 0),
(323, 1, 7, 0, 3, 0),
(324, 1, 8, 0, 3, 0),
(325, 1, 9, 0, 3, 0),
(326, 1, 10, 0, 3, 0),
(327, 1, 11, 0, 3, 0),
(328, 1, 12, 0, 3, 0),
(329, 1, 13, 0, 3, 0),
(330, 1, 14, 0, 3, 0),
(331, 2, 0, 0, 3, 0),
(332, 2, 1, 0, 3, 0),
(333, 2, 2, 0, 3, 0),
(334, 2, 3, 0, 3, 0),
(335, 2, 4, 0, 3, 0),
(336, 2, 5, 0, 3, 0),
(337, 2, 7, 0, 3, 0),
(338, 2, 6, 0, 3, 0),
(339, 2, 8, 0, 3, 0),
(340, 2, 9, 0, 3, 0),
(341, 2, 10, 0, 3, 0),
(342, 2, 11, 0, 3, 0),
(343, 2, 12, 0, 3, 0),
(344, 2, 13, 0, 3, 0),
(345, 2, 14, 0, 3, 0),
(346, 3, 0, 0, 3, 0),
(347, 3, 1, 0, 3, 0),
(348, 3, 2, 0, 3, 0),
(349, 3, 3, 0, 3, 0),
(350, 3, 4, 0, 3, 0),
(351, 3, 5, 0, 3, 0),
(352, 3, 6, 0, 3, 0),
(353, 3, 7, 0, 3, 0),
(354, 3, 8, 0, 3, 0),
(355, 3, 9, 0, 3, 0),
(356, 3, 10, 0, 3, 0),
(357, 3, 11, 0, 3, 0),
(358, 3, 12, 0, 3, 0),
(359, 3, 13, 0, 3, 0),
(360, 3, 14, 0, 3, 0),
(361, 4, 0, 0, 3, 0),
(362, 4, 1, 0, 3, 0),
(363, 4, 2, 0, 3, 0),
(364, 4, 3, 0, 3, 0),
(365, 4, 4, 0, 3, 0),
(366, 4, 5, 0, 3, 0),
(367, 4, 6, 0, 3, 0),
(368, 4, 7, 0, 3, 0),
(369, 4, 8, 0, 3, 0),
(370, 4, 9, 0, 3, 0),
(371, 4, 10, 0, 3, 0),
(372, 4, 11, 0, 3, 0),
(373, 4, 12, 0, 3, 0),
(374, 4, 13, 0, 3, 0),
(375, 4, 14, 0, 3, 0);


ALTER TABLE clan ADD `won` INT NOT NULL AFTER `pid` ,
ADD `lost` INT NOT NULL AFTER `won`;



INSERT INTO building_unit ( `bid` , `uid` , `amount` ) VALUES ( '1210', '1700', '450' );
INSERT INTO building_unit ( `bid` , `uid` , `amount` ) VALUES ( '1210', '1701', '450' );
INSERT INTO building_unit ( `bid` , `uid` , `amount` ) VALUES ( '1210', '1702', '450' );

UPDATE `unit` SET `upkeep` = '195' WHERE `unit`.`uid` =1700;
UPDATE `unit` SET `upkeep` = '125' WHERE `unit`.`uid` =1701;
UPDATE `unit` SET `upkeep` = '125' WHERE `unit`.`uid` =1702;


ALTER TABLE `sector` ADD `mid` INT NOT NULL AFTER `damage`;

UPDATE sector SET mid=100 WHERE sid=101;
UPDATE sector SET mid=101 WHERE sid=102;
UPDATE sector SET mid=102 WHERE sid=103;
UPDATE sector SET mid=103 WHERE sid=104;
UPDATE sector SET mid=104 WHERE sid=105;
UPDATE sector SET mid=105 WHERE sid=106;
UPDATE sector SET mid=106 WHERE sid=107;
UPDATE sector SET mid=107 WHERE sid=108;
UPDATE sector SET mid=110 WHERE sid=109;
UPDATE sector SET mid=111 WHERE sid=110;
UPDATE sector SET mid=112 WHERE sid=111;
UPDATE sector SET mid=113 WHERE sid=112;
UPDATE sector SET mid=114 WHERE sid=113;
UPDATE sector SET mid=115 WHERE sid=114;
UPDATE sector SET mid=116 WHERE sid=115;
UPDATE sector SET mid=117 WHERE sid=116;
UPDATE sector SET mid=120 WHERE sid=117;
UPDATE sector SET mid=121 WHERE sid=118;
UPDATE sector SET mid=122 WHERE sid=119;
UPDATE sector SET mid=123 WHERE sid=120;
UPDATE sector SET mid=124 WHERE sid=121;
UPDATE sector SET mid=125 WHERE sid=122;
UPDATE sector SET mid=126 WHERE sid=123;
UPDATE sector SET mid=127 WHERE sid=124;
UPDATE sector SET mid=130 WHERE sid=125;
UPDATE sector SET mid=131 WHERE sid=126;
UPDATE sector SET mid=132 WHERE sid=127;
UPDATE sector SET mid=133 WHERE sid=128;
UPDATE sector SET mid=134 WHERE sid=129;
UPDATE sector SET mid=135 WHERE sid=130;
UPDATE sector SET mid=136 WHERE sid=131;
UPDATE sector SET mid=137 WHERE sid=132;
UPDATE sector SET mid=140 WHERE sid=133;
UPDATE sector SET mid=141 WHERE sid=134;
UPDATE sector SET mid=142 WHERE sid=135;
UPDATE sector SET mid=143 WHERE sid=136;
UPDATE sector SET mid=144 WHERE sid=137;
UPDATE sector SET mid=145 WHERE sid=138;
UPDATE sector SET mid=146 WHERE sid=139;
UPDATE sector SET mid=147 WHERE sid=140;
UPDATE sector SET mid=150 WHERE sid=141;
UPDATE sector SET mid=151 WHERE sid=142;
UPDATE sector SET mid=152 WHERE sid=143;
UPDATE sector SET mid=153 WHERE sid=144;
UPDATE sector SET mid=154 WHERE sid=145;
UPDATE sector SET mid=155 WHERE sid=146;
UPDATE sector SET mid=156 WHERE sid=147;
UPDATE sector SET mid=157 WHERE sid=148;
UPDATE sector SET mid=160 WHERE sid=149;
UPDATE sector SET mid=161 WHERE sid=150;
UPDATE sector SET mid=162 WHERE sid=151;
UPDATE sector SET mid=163 WHERE sid=152;
UPDATE sector SET mid=164 WHERE sid=153;
UPDATE sector SET mid=165 WHERE sid=154;
UPDATE sector SET mid=166 WHERE sid=155;
UPDATE sector SET mid=167 WHERE sid=156;
UPDATE sector SET mid=170 WHERE sid=157;
UPDATE sector SET mid=171 WHERE sid=158;
UPDATE sector SET mid=172 WHERE sid=159;
UPDATE sector SET mid=173 WHERE sid=160;
UPDATE sector SET mid=174 WHERE sid=161;
UPDATE sector SET mid=175 WHERE sid=162;
UPDATE sector SET mid=176 WHERE sid=163;
UPDATE sector SET mid=177 WHERE sid=164;
UPDATE sector SET mid=180 WHERE sid=165;
UPDATE sector SET mid=181 WHERE sid=166;
UPDATE sector SET mid=182 WHERE sid=167;
UPDATE sector SET mid=183 WHERE sid=168;
UPDATE sector SET mid=184 WHERE sid=169;
UPDATE sector SET mid=185 WHERE sid=170;
UPDATE sector SET mid=186 WHERE sid=171;
UPDATE sector SET mid=187 WHERE sid=172;
UPDATE sector SET mid=187 WHERE sid=173;
UPDATE sector SET mid=187 WHERE sid=174;
UPDATE sector SET mid=187 WHERE sid=175;


UPDATE sector SET mid=200 WHERE sid=201;
UPDATE sector SET mid=201 WHERE sid=202;
UPDATE sector SET mid=202 WHERE sid=203;
UPDATE sector SET mid=203 WHERE sid=204;
UPDATE sector SET mid=204 WHERE sid=205;
UPDATE sector SET mid=205 WHERE sid=206;
UPDATE sector SET mid=206 WHERE sid=207;
UPDATE sector SET mid=207 WHERE sid=208;
UPDATE sector SET mid=210 WHERE sid=209;
UPDATE sector SET mid=211 WHERE sid=210;
UPDATE sector SET mid=212 WHERE sid=211;
UPDATE sector SET mid=213 WHERE sid=212;
UPDATE sector SET mid=214 WHERE sid=213;
UPDATE sector SET mid=215 WHERE sid=214;
UPDATE sector SET mid=216 WHERE sid=215;
UPDATE sector SET mid=217 WHERE sid=216;
UPDATE sector SET mid=220 WHERE sid=217;
UPDATE sector SET mid=221 WHERE sid=218;
UPDATE sector SET mid=222 WHERE sid=219;
UPDATE sector SET mid=223 WHERE sid=220;
UPDATE sector SET mid=224 WHERE sid=221;
UPDATE sector SET mid=225 WHERE sid=222;
UPDATE sector SET mid=226 WHERE sid=223;
UPDATE sector SET mid=227 WHERE sid=224;
UPDATE sector SET mid=230 WHERE sid=225;
UPDATE sector SET mid=231 WHERE sid=226;
UPDATE sector SET mid=232 WHERE sid=227;
UPDATE sector SET mid=233 WHERE sid=228;
UPDATE sector SET mid=234 WHERE sid=229;
UPDATE sector SET mid=235 WHERE sid=230;
UPDATE sector SET mid=236 WHERE sid=231;
UPDATE sector SET mid=237 WHERE sid=232;
UPDATE sector SET mid=240 WHERE sid=233;
UPDATE sector SET mid=241 WHERE sid=234;
UPDATE sector SET mid=242 WHERE sid=235;
UPDATE sector SET mid=243 WHERE sid=236;
UPDATE sector SET mid=244 WHERE sid=237;
UPDATE sector SET mid=245 WHERE sid=238;
UPDATE sector SET mid=246 WHERE sid=239;
UPDATE sector SET mid=247 WHERE sid=240;
UPDATE sector SET mid=250 WHERE sid=241;
UPDATE sector SET mid=251 WHERE sid=242;
UPDATE sector SET mid=252 WHERE sid=243;
UPDATE sector SET mid=253 WHERE sid=244;
UPDATE sector SET mid=254 WHERE sid=245;
UPDATE sector SET mid=255 WHERE sid=246;
UPDATE sector SET mid=256 WHERE sid=247;
UPDATE sector SET mid=257 WHERE sid=248;
UPDATE sector SET mid=260 WHERE sid=249;
UPDATE sector SET mid=261 WHERE sid=250;
UPDATE sector SET mid=262 WHERE sid=251;
UPDATE sector SET mid=263 WHERE sid=252;
UPDATE sector SET mid=264 WHERE sid=253;
UPDATE sector SET mid=265 WHERE sid=254;
UPDATE sector SET mid=266 WHERE sid=255;
UPDATE sector SET mid=267 WHERE sid=256;
UPDATE sector SET mid=270 WHERE sid=257;
UPDATE sector SET mid=271 WHERE sid=258;
UPDATE sector SET mid=272 WHERE sid=259;
UPDATE sector SET mid=273 WHERE sid=260;
UPDATE sector SET mid=274 WHERE sid=261;
UPDATE sector SET mid=275 WHERE sid=262;
UPDATE sector SET mid=276 WHERE sid=263;
UPDATE sector SET mid=277 WHERE sid=264;
UPDATE sector SET mid=280 WHERE sid=265;
UPDATE sector SET mid=281 WHERE sid=266;
UPDATE sector SET mid=282 WHERE sid=267;
UPDATE sector SET mid=283 WHERE sid=268;
UPDATE sector SET mid=284 WHERE sid=269;
UPDATE sector SET mid=285 WHERE sid=270;
UPDATE sector SET mid=286 WHERE sid=271;
UPDATE sector SET mid=287 WHERE sid=272;
UPDATE sector SET mid=287 WHERE sid=273;
UPDATE sector SET mid=287 WHERE sid=274;
UPDATE sector SET mid=287 WHERE sid=275;



UPDATE sector SET mid=300 WHERE sid=301;
UPDATE sector SET mid=301 WHERE sid=302;
UPDATE sector SET mid=302 WHERE sid=303;
UPDATE sector SET mid=303 WHERE sid=304;
UPDATE sector SET mid=304 WHERE sid=305;
UPDATE sector SET mid=305 WHERE sid=306;
UPDATE sector SET mid=306 WHERE sid=307;
UPDATE sector SET mid=307 WHERE sid=308;
UPDATE sector SET mid=310 WHERE sid=309;
UPDATE sector SET mid=311 WHERE sid=310;
UPDATE sector SET mid=312 WHERE sid=311;
UPDATE sector SET mid=313 WHERE sid=312;
UPDATE sector SET mid=314 WHERE sid=313;
UPDATE sector SET mid=315 WHERE sid=314;
UPDATE sector SET mid=316 WHERE sid=315;
UPDATE sector SET mid=317 WHERE sid=316;
UPDATE sector SET mid=320 WHERE sid=317;
UPDATE sector SET mid=321 WHERE sid=318;
UPDATE sector SET mid=322 WHERE sid=319;
UPDATE sector SET mid=323 WHERE sid=320;
UPDATE sector SET mid=324 WHERE sid=321;
UPDATE sector SET mid=325 WHERE sid=322;
UPDATE sector SET mid=326 WHERE sid=323;
UPDATE sector SET mid=327 WHERE sid=324;
UPDATE sector SET mid=330 WHERE sid=325;
UPDATE sector SET mid=331 WHERE sid=326;
UPDATE sector SET mid=332 WHERE sid=327;
UPDATE sector SET mid=333 WHERE sid=328;
UPDATE sector SET mid=334 WHERE sid=329;
UPDATE sector SET mid=335 WHERE sid=330;
UPDATE sector SET mid=336 WHERE sid=331;
UPDATE sector SET mid=337 WHERE sid=332;
UPDATE sector SET mid=340 WHERE sid=333;
UPDATE sector SET mid=341 WHERE sid=334;
UPDATE sector SET mid=342 WHERE sid=335;
UPDATE sector SET mid=343 WHERE sid=336;
UPDATE sector SET mid=344 WHERE sid=337;
UPDATE sector SET mid=345 WHERE sid=338;
UPDATE sector SET mid=346 WHERE sid=339;
UPDATE sector SET mid=347 WHERE sid=340;
UPDATE sector SET mid=350 WHERE sid=341;
UPDATE sector SET mid=351 WHERE sid=342;
UPDATE sector SET mid=352 WHERE sid=343;
UPDATE sector SET mid=353 WHERE sid=344;
UPDATE sector SET mid=354 WHERE sid=345;
UPDATE sector SET mid=355 WHERE sid=346;
UPDATE sector SET mid=356 WHERE sid=347;
UPDATE sector SET mid=357 WHERE sid=348;
UPDATE sector SET mid=360 WHERE sid=349;
UPDATE sector SET mid=361 WHERE sid=350;
UPDATE sector SET mid=362 WHERE sid=351;
UPDATE sector SET mid=363 WHERE sid=352;
UPDATE sector SET mid=364 WHERE sid=353;
UPDATE sector SET mid=365 WHERE sid=354;
UPDATE sector SET mid=366 WHERE sid=355;
UPDATE sector SET mid=367 WHERE sid=356;
UPDATE sector SET mid=370 WHERE sid=357;
UPDATE sector SET mid=371 WHERE sid=358;
UPDATE sector SET mid=372 WHERE sid=359;
UPDATE sector SET mid=373 WHERE sid=360;
UPDATE sector SET mid=374 WHERE sid=361;
UPDATE sector SET mid=375 WHERE sid=362;
UPDATE sector SET mid=376 WHERE sid=363;
UPDATE sector SET mid=377 WHERE sid=364;
UPDATE sector SET mid=380 WHERE sid=365;
UPDATE sector SET mid=381 WHERE sid=366;
UPDATE sector SET mid=382 WHERE sid=367;
UPDATE sector SET mid=383 WHERE sid=368;
UPDATE sector SET mid=384 WHERE sid=369;
UPDATE sector SET mid=385 WHERE sid=370;
UPDATE sector SET mid=386 WHERE sid=371;
UPDATE sector SET mid=387 WHERE sid=372;
UPDATE sector SET mid=387 WHERE sid=373;
UPDATE sector SET mid=387 WHERE sid=374;
UPDATE sector SET mid=387 WHERE sid=375;

ALTER TABLE `member` ADD `email_valid` INT NOT NULL AFTER `email`;
