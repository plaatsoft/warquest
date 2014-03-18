--
-- WarQuest v6.7 data model patch
--

-- Add lottery feature

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
  `done` int(11) NOT NULL,
  PRIMARY KEY (`lottery_id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=3 ;

delete from lottery;
INSERT INTO lottery (lottery_id, expire_date, bet, money, gold, uid, uid_amount, bid, bid_amount, done) VALUES
(1, '2014-03-22 23:59:59', 2, 10000000000, 0, 327, 10, 63, 10,0),
(2, '2014-03-21 23:59:59', 5, 0, 500, 513, 15, 56, 15,0),
(3, '2014-03-20 23:59:59', 3, 20000000000, 0, 1410, 15, 1110, 15, 0),
(4, '2014-03-19 23:59:59', 4, 0, 800,         2709, 20, 2106, 10, 0),
(5, '2014-03-18 23:59:59', 5, 30000000000, 0, 2010, 15, 1610, 5, 0);


CREATE TABLE IF NOT EXISTS `player_lottery` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `pid` int(11) NOT NULL,
  `lottery_id` int(11) NOT NULL,
  `bet_date` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  `winner` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 AUTO_INCREMENT=1;

INSERT INTO  cron (cid, note, last_run) VALUES (13, 'Lottery job', '2014-03-03 00:00:00');

-- Rename action because version is a reserved word in java hibernate framework.
ALTER TABLE `member` CHANGE `version` `versie` VARCHAR( 20 ) CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL ;