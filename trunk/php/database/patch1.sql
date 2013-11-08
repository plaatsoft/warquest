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

INSERT INTO `clan` (`cid`, `name`, `date`, `pid`) VALUES
(1, 'WQ', '2013-11-07', 18),
(2, 'NOOBS', '2013-11-01', 23);

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

INSERT INTO `player_clan` (`pid`, `cid`, `date`) VALUES
(18, 1, '2013-11-07'),
(28, 1, '2013-11-01'),
(23, 2, '2013-11-05');

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;

