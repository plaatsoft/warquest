--
-- WarQuest v6.7 data model patch
--

CREATE TABLE IF NOT EXISTS `player_lottery` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `pid` int(11) NOT NULL,
  `lottery_id` int(11) NOT NULL,
  `bet_date` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 AUTO_INCREMENT=1;

CREATE TABLE IF NOT EXISTS `lottery` (
  `lottery_id` int(11) NOT NULL AUTO_INCREMENT,
  `expire_date` datetime NOT NULL,
  `bet` int(11) NOT NULL,
  `money` bigint(20) NOT NULL,
  `gold` bigint(20) NOT NULL,
  `uid` int(11) NOT NULL,
  `uid_amount` int(11) NOT NULL,
  `bid` int(11) NOT NULL,
  `bid_amount` int(11) NOT NULL,
  PRIMARY KEY (`lottery_id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=3 ;

INSERT INTO `lottery` (`lottery_id`, `expire_date`, `bet`, `money`, `gold`, `uid`, `uid_amount`, `bid`, `bid_amount`) VALUES
(1, '2014-03-23 22:00:00', 2, 2000000000, 0, 327, 10, 63, 10),
(2, '2014-03-23 23:00:00', 5, 0, 500, 513, 15, 56, 15);