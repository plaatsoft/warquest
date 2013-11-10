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

CREATE TABLE IF NOT EXISTS `clan` (
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

CREATE TABLE IF NOT EXISTS `sector` (
  `sid` int(11) NOT NULL AUTO_INCREMENT,
  `x` int(11) NOT NULL,
  `y` int(11) NOT NULL,
  `cid` int(11) DEFAULT NULL,
  `strength` int(11) NOT NULL,
  PRIMARY KEY (`sid`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=0;

INSERT INTO sector (`x`,`y`) VALUES ( 0, 0);
INSERT INTO sector (`x`,`y`) VALUES ( 0, 1);
INSERT INTO sector (`x`,`y`) VALUES ( 0, 2);
INSERT INTO sector (`x`,`y`) VALUES ( 0, 3);
INSERT INTO sector (`x`,`y`) VALUES ( 0, 4);
INSERT INTO sector (`x`,`y`) VALUES ( 0, 5);
INSERT INTO sector (`x`,`y`) VALUES ( 0, 6);
INSERT INTO sector (`x`,`y`) VALUES ( 0, 7);
INSERT INTO sector (`x`,`y`) VALUES ( 0, 8);
INSERT INTO sector (`x`,`y`) VALUES ( 0, 9);
INSERT INTO sector (`x`,`y`) VALUES ( 0, 10);
INSERT INTO sector (`x`,`y`) VALUES ( 0, 11);
INSERT INTO sector (`x`,`y`) VALUES ( 0, 12);
INSERT INTO sector (`x`,`y`) VALUES ( 0, 13);
INSERT INTO sector (`x`,`y`) VALUES ( 0, 14);

INSERT INTO sector (`x`,`y`) VALUES ( 1, 0);
INSERT INTO sector (`x`,`y`) VALUES ( 1, 1);
INSERT INTO sector (`x`,`y`) VALUES ( 1, 2);
INSERT INTO sector (`x`,`y`) VALUES ( 1, 3);
INSERT INTO sector (`x`,`y`) VALUES ( 1, 4);
INSERT INTO sector (`x`,`y`) VALUES ( 1, 5);
INSERT INTO sector (`x`,`y`) VALUES ( 1, 6);
INSERT INTO sector (`x`,`y`) VALUES ( 1, 7);
INSERT INTO sector (`x`,`y`) VALUES ( 1, 8);
INSERT INTO sector (`x`,`y`) VALUES ( 1, 9);
INSERT INTO sector (`x`,`y`) VALUES ( 1, 10);
INSERT INTO sector (`x`,`y`) VALUES ( 1, 11);
INSERT INTO sector (`x`,`y`) VALUES ( 1, 12);
INSERT INTO sector (`x`,`y`) VALUES ( 1, 13);
INSERT INTO sector (`x`,`y`) VALUES ( 1, 14);


INSERT INTO sector (`x`,`y`) VALUES ( 2, 0);
INSERT INTO sector (`x`,`y`) VALUES ( 2, 1);
INSERT INTO sector (`x`,`y`) VALUES ( 2, 2);
INSERT INTO sector (`x`,`y`) VALUES ( 2, 3);
INSERT INTO sector (`x`,`y`) VALUES ( 2, 4);
INSERT INTO sector (`x`,`y`) VALUES ( 2, 5);
INSERT INTO sector (`x`,`y`) VALUES ( 2, 6);
INSERT INTO sector (`x`,`y`) VALUES ( 2, 7);
INSERT INTO sector (`x`,`y`) VALUES ( 2, 8);
INSERT INTO sector (`x`,`y`) VALUES ( 2, 9);
INSERT INTO sector (`x`,`y`) VALUES ( 2, 10);
INSERT INTO sector (`x`,`y`) VALUES ( 2, 11);
INSERT INTO sector (`x`,`y`) VALUES ( 2, 12);
INSERT INTO sector (`x`,`y`) VALUES ( 2, 13);
INSERT INTO sector (`x`,`y`) VALUES ( 2, 14);

INSERT INTO sector (`x`,`y`) VALUES ( 3, 0);
INSERT INTO sector (`x`,`y`) VALUES ( 3, 1);
INSERT INTO sector (`x`,`y`) VALUES ( 3, 2);
INSERT INTO sector (`x`,`y`) VALUES ( 3, 3);
INSERT INTO sector (`x`,`y`) VALUES ( 3, 4);
INSERT INTO sector (`x`,`y`) VALUES ( 3, 5);
INSERT INTO sector (`x`,`y`) VALUES ( 3, 6);
INSERT INTO sector (`x`,`y`) VALUES ( 3, 7);
INSERT INTO sector (`x`,`y`) VALUES ( 3, 8);
INSERT INTO sector (`x`,`y`) VALUES ( 3, 9);
INSERT INTO sector (`x`,`y`) VALUES ( 3, 10);
INSERT INTO sector (`x`,`y`) VALUES ( 3, 11);
INSERT INTO sector (`x`,`y`) VALUES ( 3, 12);
INSERT INTO sector (`x`,`y`) VALUES ( 3, 13);
INSERT INTO sector (`x`,`y`) VALUES ( 3, 14);

INSERT INTO sector (`x`,`y`) VALUES ( 4, 0);
INSERT INTO sector (`x`,`y`) VALUES ( 4, 1);
INSERT INTO sector (`x`,`y`) VALUES ( 4, 2);
INSERT INTO sector (`x`,`y`) VALUES ( 4, 3);
INSERT INTO sector (`x`,`y`) VALUES ( 4, 4);
INSERT INTO sector (`x`,`y`) VALUES ( 4, 5);
INSERT INTO sector (`x`,`y`) VALUES ( 4, 6);
INSERT INTO sector (`x`,`y`) VALUES ( 4, 7);
INSERT INTO sector (`x`,`y`) VALUES ( 4, 8);
INSERT INTO sector (`x`,`y`) VALUES ( 4, 9);
INSERT INTO sector (`x`,`y`) VALUES ( 4, 10);
INSERT INTO sector (`x`,`y`) VALUES ( 4, 11);
INSERT INTO sector (`x`,`y`) VALUES ( 4, 12);
INSERT INTO sector (`x`,`y`) VALUES ( 4, 13);
INSERT INTO sector (`x`,`y`) VALUES ( 4, 14);









			