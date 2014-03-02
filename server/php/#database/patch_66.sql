--
-- WarQuest v6.6 data model patch
--

CREATE TABLE IF NOT EXISTS `views` (
  `mid` int(11) NOT NULL,
  `sid` int(11) NOT NULL,
  `ssid` int(11) NOT NULL,
  `eid` int(11) NOT NULL,
  `requests` int(11) NOT NULL,
  PRIMARY KEY (`mid`,`sid`,`ssid`,`eid`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;


insert into views (mid, sid, ssid, eid, requests) values (0,0,0,0, 44926454);