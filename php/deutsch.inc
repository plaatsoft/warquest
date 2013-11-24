<?php

/* 
**  ========
**  WARQUEST
**  ========
**
**  Created by wplaat
**
**  For more information visit the following website.
**  Website : www.plaatsoft.nl 
**
**  Or send an email to the following address.
**  Email   : info@plaatsoft.nl
**
**  All copyrights reserved (c) 2008-2013 PlaatSoft
*/

/*
** Some translation remarks:
** (1) Every line has the following syntax $lang['<KEY>'] = '<DESCRIPTION>';
**     Only change the <DESCRIPTION> part. Leave the rest unchanged.
** (2) The <DESCRIPTION> part contain %s tags. DO NOT REMOVE THEN.
**     The %s are realtime replace with game parameters. 
**     For example: 'Restore for %s dollar' will be on screen 'Restore for 100 dollar'
** (3) The LINK keys contain the menu items of the game. Choose as short as possible words.
** (4) Leave HTML tags unchanged, for example <b>, </b>, etc....
**
** Good luck and have fun!
*/

/*
** ------------------
** Language: DEUTSCH
** ------------------
*/
 
/*
** ------------------
** LINKS
** ------------------
*/

/* Login */
$lang['LINK_LOGIN']  = 'Login'; 
$lang['LINK_REGISTER'] = 'Registration'; 
$lang['LINK_RECOVER'] = 'Erholung'; 
$lang['LINK_MANUAL'] = 'Handbuch'; 
$lang['LINK_RSS']  = 'RSS'; 

/* General */
$lang['LINK_HOME'] = 'Home';
$lang['LINK_MISSIONS'] = 'Mission';
$lang['LINK_BATTLE'] = 'Kampf';
$lang['LINK_UNITS']  = 'Einheiten';
$lang['LINK_BUILDINGS']  = 'Gebäude';
$lang['LINK_BANKS'] = 'Bank';
$lang['LINK_ALLIANCE'] = 'Bündnis';
$lang['LINK_PLAYER'] = 'Spieler';
$lang['LINK_MONEY'] = 'Geld';
$lang['LINK_HELP'] = 'Hilfe';
$lang['LINK_ADMIN'] = 'Admin';

$lang['LINK_FIRST']  = 'Anfang';
$lang['LINK_PREVIOUS'] = 'Zurück';
$lang['LINK_NEXT'] = 'Weiter';
$lang['LINK_LAST'] = 'Ende';

/* Home */
$lang['LINK_RESTORE'] = 'Restore';
$lang['LINK_REPAIR'] = 'Reparatur';
$lang['LINK_TRADE'] = 'Trade';
$lang['LINK_ACTIVATE'] = 'Activate';

/* Player */
$lang['LINK_OVERVIEW'] = 'Übersicht';
$lang['LINK_DELETE'] = 'Löschen';
$lang['LINK_SETTINGS'] = 'Einstellung';
$lang['LINK_NEWS'] = 'News';
$lang['LINK_COMMENTS'] = 'Nachrichten';
$lang['LINK_STATISTICS'] = 'Statistik';
$lang['LINK_LOGOUT'] = 'Logout';
$lang['LINK_EDIT'] = 'Edit';
$lang['LINK_SAVE'] = 'Speichern';
$lang['LINK_REPLY'] = 'Reply';
$lang['LINK_PROFILE'] = 'Profil';
$lang['LINK_SKILLS'] = 'Skills';
$lang['LINK_RECRUIT']  = 'Einladen';
$lang['LINK_INCREASE'] = 'Erhöhen';
$lang['LINK_DECREASE'] = 'Erniedrigen';
$lang['LINK_RESTORE_NOW']  = 'Restore for %s dollar';
$lang['LINK_CHANGE'] = 'Ändern';
$lang['LINK_REPORT'] = 'Melden';
$lang['LINK_BOUNTY'] = 'Belohnung';

/* Mission */
$lang['LINK_PLAY'] = 'Angriff';
$lang['LINK_BUY_PLAY'] = 'Kaufen und Angriff';
$lang['LINK_DO_AGAIN'] = 'wieder Angriff';

/* Battle */
$lang['LINK_ATTACK'] = 'Angriff';
$lang['LINK_BATTLES']  = 'Kampf';
$lang['LINK_SP'] = 'Skill Punkte';

/* Unit */
$lang['LINK_DEPLOY'] = 'Entlassen';
$lang['LINK_DEPLOY_AGAIN'] = 'weiter Entlassen';
$lang['LINK_DISBAND']  = 'Disband';
$lang['LINK_DISBAND_AGAIN']= 'Disband Again';

/* Building */
$lang['LINK_INCOME'] = 'Einkommen';
$lang['LINK_DEFENSE'] = 'Verteidigung';
$lang['LINK_ENERGY'] = 'Energie';
$lang['LINK_BUY'] = 'Erwerben';
$lang['LINK_BUY_AGAIN'] = 'Mehr Erwerben';
$lang['LINK_SELL'] = 'Verkaufen';
$lang['LINK_SELL_AGAIN'] = 'Mehr Verkaufen';

/* Bank / Exchange / Casino */
$lang['LINK_BANK'] = 'Bank';
$lang['LINK_STOCKEXCHANGE'] = 'Börse';
$lang['LINK_CASINO'] = 'Kasino';

$lang['LINK_DEPOSIT']  = 'Einzahlen';
$lang['LINK_WITHDRAW'] = 'Abheben';
$lang['LINK_BALANCE']  = 'Kontostand';

/* Alliance */
$lang['LINK_INVITE'] = 'Einladen';
$lang['LINK_PENDING'] = 'Pending';
$lang['LINK_APPROVED'] = 'Akzeptieren';
$lang['LINK_COMMENT']  = 'Nachricht';
$lang['LINK_BEST_PLAYER']  = 'Bester Spieler';
$lang['LINK_BEST_COUNTRY'] = 'Bestes Land';
$lang['LINK_DROP'] = 'Ablehnen';
$lang['LINK_ACCEPT'] = 'Akzeptieren';
$lang['LINK_REJECT'] = 'Reject';
$lang['LINK_SEND'] = 'Senden';
$lang['LINK_RESET']  = 'Reset';

/* Forum */
$lang['LINK_FORUM']  = 'Forum';
$lang['LINK_POLLS'] = 'Wahlen';
$lang['LINK_CHATROOM'] = 'Chatroom';
$lang['LINK_SEARCH']  = 'Suchen';

/* Help */
$lang['LINK_GENERAL']  = 'Anleitung';
$lang['LINK_RANKS']  = 'Rank';
$lang['LINK_AWARDS'] = 'Auszeichnung';
$lang['LINK_NOTES']  = 'Release-Notes';
$lang['LINK_STATS']  = 'Statistik';
$lang['LINK_ABOUT']  = 'Über';
$lang['LINK_DONATE']  = 'Spende';

/*
** ------------------
** GENERAL 
** ------------------
*/

$lang['SYSTEM_HACK_DETECTED'] = 'Please do not use the reload, prev or next button!';

$lang['AGO_DAY']   = ' Tag';	
$lang['AGO_DAYS']  = ' Tage';
$lang['AGO_HOUR']  = ' Stunde';
$lang['AGO_HOURS'] = ' Stunden';
$lang['AGO_MIN']   = ' Min';
$lang['AGO_MINS']  = ' Min';
$lang['AGO_SEC']   = ' Sek';
$lang['AGO_SECS']  = ' Sek';
	
$lang['COPYRIGHT'] = 'Copyright © 2008-2013 - All Rights Reserved - <a target="new" href="http://www.plaatsoft.nl">PlaatSoft</a>';

$lang['STATUS_MONEY']  = 'Geld';
$lang['STATUS_EXP']  = 'Exp.';
$lang['STATUS_LEVEL']  = 'Rang';
$lang['STATUS_HEALTH'] = 'Gesundheit';
$lang['STATUS_ENERGY'] = 'Energie';
$lang['STATUS_AMMO'] = 'Muni';
$lang['STATUS_ALLIANCE_SIZE'] = 'Bundnis Größe';

$lang['BOX_INFO'] = 'INFO';
$lang['BOX_WARN'] = 'ACHTUNG';
$lang['BOX_ERROR'] = 'ERROR';

$lang['GENERAL_NEXT_LEVEL'] = 'Brilliant! Du erhälst einen neuen Rang! Du erhälst %s skill Punkte und %s Dollar. Deine Gesundheit, Energie und Muni ist vollständig. ';
$lang['GENERAL_BATTLE_LEVEL'] = 'Brilliant! Du warst %s siegreich im Kampf und erhälst dafür %s Extra skill Punkt(e) und %s Dollar.';
$lang['GENERAL_BOUNTY_LEVEL'] = 'Großartig! Du hast %s Belohnung(en) ausgesetzt and erhälst dafür %s Extra Skill Punkte(e) und %s Dollar.';
$lang['GENERAL_REBEL_LEVEL'] = 'Großartig! Du hast die Chance einen Aufstand auszulösen um %s erhöht und erhälst %s Extra Skill Punkte(e) und %s Dollar.';
$lang['GENERAL_BATTLE_AWARD_WON'] = 'gewonnene Kriege';
$lang['GENERAL_BOUNTY_AWARD_WON'] = 'Belohnungen ausgesetzt';
$lang['GENERAL_REBEL_AWARD_WON'] = 'Aufstände ausgelöst';
$lang['GENERAL_UNLOCK'] = 'Freigeschaltet bei Rang %s';
$lang['GENERAL_NEW_FEATURES'] = 'Die folgenden Features sind nun verfügbar:';
$lang['GENERAL_RECEIVED_AWARD'] = 'Auszeichnung erhalten:';

$lang['GENERAL_ATTACK'] = 'Angriff';
$lang['GENERAL_DEFENSE'] = 'Verteidigung';
$lang['GENERAL_INCOME']  = 'Einkommen';
$lang['GENERAL_ENERGY']  = 'Energie';
$lang['GENERAL_EXPERIENCE']  = 'Erfahrung';
$lang['GENERAL_DOLLAR']  = 'Dollar';
$lang['GENERAL_ALLIANCE_SIZE'] = 'Bündnis Größe';
$lang['GENERAL_EXPERIENCE_POINTS'] = 'Erfahrungspunkte';
$lang['GENERAL_UPKEEP'] = 'Stündliche Kosten';
$lang['GENERAL_BANK']  = 'Bank';
$lang['GENERAL_STOCKEXCHANGE']  = 'Stock Exchange';
$lang['GENERAL_DEPLOYED']  = 'Angestellt';

$lang['GENERAL_PLAYER']  = 'Spieler';
$lang['GENERAL_LEVEL'] = 'Rang';
$lang['GENERAL_ALLIANCE']  = 'Bündnis';
$lang['GENERAL_WON'] = 'Sieg';
$lang['GENERAL_LOST']  = 'Niederlage';
$lang['GENERAL_AMOUNT'] = 'Stück';
$lang['GENERAL_DATE'] = 'Datum';
$lang['GENERAL_TRANSACTION'] = 'Transaktion';
$lang['GENERAL_BALANCE'] = 'Kontostand';
$lang['GENERAL_APPROVED'] = 'Approved';
$lang['GENERAL_EMAIL'] = 'Email';
$lang['GENERAL_TOP']	= 'Top';
$lang['GENERAL_EXP'] = 'Erfahrung';
$lang['GENERAL_COUNTRY'] = 'Land';
$lang['GENERAL_PLAYERS'] = 'Spieler';
$lang['GENERAL_WONS']  = 'Siege';
$lang['GENERAL_LOSTS'] = 'Niederlage';
$lang['GENERAL_NO'] = 'Nein';
$lang['GENERAL_YES'] = 'Ja';
$lang['GENERAL_AGO'] = 'Ago';
$lang['GENERAL_MESSAGE'] = 'Nachricht';
$lang['GENERAL_ACTION'] = 'Aktion';
$lang['GENERAL_NUMBER'] = 'Nr.';
$lang['GENERAL_DISCOUNT'] = 'Building discount';
$lang['GENERAL_REQUESTS'] = 'Anfrage';
$lang['GENERAL_EP'] = 'Erfahrungspunkte';
$lang['GENERAL_AWARD'] = 'Belohnung';
$lang['GENERAL_LANGUAGE'] = 'Sprache';
$lang['GENERAL_RANKING'] = 'Ranking';

$lang['GENERAL_NEW_UNIT'] = 'NEUE EINHEIT';
$lang['GENERAL_NEW_BUILDING'] = 'NEUES GEBÄUDE';
$lang['GENERAL_NEW_MISSION'] = 'NEUE MISSION';
$lang['GENERAL_GAIN'] = 'verdienen';

$lang['GENERAL_BOUNTY'] = 'Belohnung';
$lang['GENERAL_INTELLIGENCE'] = 'Intelligenz';
$lang['GENERAL_SPIES'] = 'spionieren';
$lang['GENERAL_MAINTENANCE'] = 'Einheiten Zustand';

$lang['GENERAL_CNTRY'] = 'Land';
$lang['GENERAL_TOPICS'] = 'Übersicht'; 
$lang['GENERAL_FORUM'] = 'Forum';
$lang['GENERAL_MESSAGES'] = 'Nachrichten';
$lang['GENERAL_LAST_MESSAGE'] = 'Letzte Nachricht';
$lang['GENERAL_FORUM_MODERATED'] = '(Moderated by %s)';
$lang['GENERAL_NOT_MODERATED'] = '(Not Moderated)';
$lang['GENERAL_BY'] = 'VOR';
$lang['GENERAL_TOPIC'] = 'Übersicht';
$lang['GENERAL_LOCKED'] = 'Verschlossen';
$lang['GENERAL_WORLDMAP'] = 'Welt-Karte';
$lang['GENERAL_PLAATSOFT'] = 'PlaatSoft';
$lang['GENERAL_CONQUER'] = 'Erobere';

$lang['GENERAL_ST'] = '%sst';
$lang['GENERAL_ND'] = '%snd';
$lang['GENERAL_TH'] = '%sth';

$lang['GENERAL_CONTINENT'] = 'Kontinent';
$lang['GENERAL_CONQUERED'] = 'Erobert';

$lang['GENERAL_IDLE'] = 'Idle';
$lang['GENERAL_ACTIVE'] = 'Aktiv';
$lang['GENERAL_INACTIVE'] = 'Inaktiv';

$lang['GENERAL_PLANET_0'] = 'Erde';
$lang['GENERAL_PLANET_1'] = 'Mond';

/*
** ------------------
** TIP
** ------------------
*/

$lang['TIP_GENERAL']  = 'TIP';
$lang['TIP_0'] = 'Play the training mission to collect experience points and reach the next level.';
$lang['TIP_1'] = 'Buy some units and start battle training to collect experience points.';
$lang['TIP_2'] = 'Trade in received skill points (Home -> Skills) to improve your soldier skills.';
$lang['TIP_3'] = 'Enter your email address to receive message and alliance notifications!';
$lang['TIP_4'] = 'Buy some income buildings to generate hourly income.';
$lang['TIP_5'] = 'Buy some defense buildings to improve your defense strength.';
$lang['TIP_6'] = 'Make alliance with ohter players to improve your attack/defense strenght.';
$lang['TIP_7'] = 'Store cash money on the National bank to keep it safe for other players.';
$lang['TIP_8'] = 'Collect extra experience points by voting on the available polls!';
$lang['TIP_9'] = 'Set bounty on other players to collect bounty awards.';
$lang['TIP_10'] = 'Visit the casino to try out the Wheel of Fortune and win more cash.';
$lang['TIP_11'] = 'Buy energy buildings for faster energy restore.';
$lang['TIP_12'] = 'Buy exspionage units to spy other players and start rebellion on there side.';
$lang['TIP_13'] = 'Store cash money on the Trasquera bank to receive daily interest.';
$lang['TIP_14'] = 'Visit the forum. New game ideas are welcome!';
$lang['TIP_15'] = 'Check out the Help section for more information.';
$lang['TIP_16'] = 'Buy/Sell stocks to make more profit (Money -> StockExchange)';
$lang['TIP_17'] = 'Store cash money on the SwissCore bank to receive daily interest.';
$lang['TIP_18'] = 'Complete all continent missions to receive extra bonus skill points.';
$lang['TIP_19'] = 'Repair units (Home -> Restore) to prevent unit loss';
$lang['TIP_20'] = 'Visit the casino to try out the Slot Machine and win more cash.';
$lang['TIP_21'] = 'Repair buildings (Home -> Restore) to prevent building loss';
$lang['TIP_22'] = 'Continue with the game and become the best player of your country!';

$lang['TIP_115'] = 'Only 10 levels away from starting your own moon colony.';
$lang['TIP_116'] = 'Only 9 levels away from starting your own moon colony.';
$lang['TIP_117'] = 'Only 8 levels away from starting your own moon colony.';
$lang['TIP_118'] = 'Only 7 levels away from starting your own moon colony.';
$lang['TIP_119'] = 'Only 6 levels away from starting your own moon colony.';
$lang['TIP_120'] = 'Only 5 levels away from starting your own moon colony.';
$lang['TIP_121'] = 'Only 4 levels away from starting your own moon colony.';
$lang['TIP_122'] = 'Only 3 levels away from starting your own moon colony.';
$lang['TIP_123'] = 'Only 2 levels away from starting your own moon colony.';
$lang['TIP_124'] = 'Only 1 level away from starting your own moon colony.';
$lang['TIP_125'] = 'Start your own moon colony!';

$lang['TIP_190'] = 'Only 10 levels away from starting your own mars colony.';
$lang['TIP_191'] = 'Only 9 levels away from starting your own mars colony.';
$lang['TIP_192'] = 'Only 8 levels away from starting your own mars colony.';
$lang['TIP_193'] = 'Only 7 levels away from starting your own mars colony.';
$lang['TIP_194'] = 'Only 6 levels away from starting your own mars colony.';
$lang['TIP_195'] = 'Only 5 levels away from starting your own mars colony.';
$lang['TIP_196'] = 'Only 4 levels away from starting your own mars colony.';
$lang['TIP_197'] = 'Only 3 levels away from starting your own mars colony.';
$lang['TIP_198'] = 'Only 2 levels away from starting your own mars colony.';
$lang['TIP_199'] = 'Only 1 level away from starting your own mars colony.';
$lang['TIP_200'] = 'Start your own mars colony!';

/*
** ------------------
** LOGIN PAGE
** ------------------
*/

$lang['LOGIN_MEMBER_TITLE'] = 'Member Login';
$lang['LOGIN_REGISTER_TITLE'] = 'Kostenlose Registrierung';
$lang['LOGIN_RECOVER_TITLE'] = 'Passwort vergessen?';
$lang['LOGIN_MANUAL_TITLE'] = 'Handbuch';

$lang['LOGIN_PLAYERS'] = 'Spieler';
$lang['LOGIN_REQUESTS'] = 'Anfragen';
$lang['LOGIN_COUNTRIES'] = 'Länder';
$lang['LOGIN_ONLINE'] = 'Spieler online';

$lang['LOGIN_PASSWORD'] = 'Passwort';
$lang['LOGIN_USERNAME'] = 'Username';
$lang['LOGIN_EMAIL'] = 'Email';
$lang['LOGIN_NICKNAME']  = 'Nickname';

$lang['LOGIN_MAINTENANCE_TITLE'] = 'Server Maintenance';
$lang['LOGIN_MAINTENANCE'] = 'Im Moment ist der Server abgeschaltet. Bitte versuchen Sie es in 5 Minuten nocheinmal.';

$lang['LOGIN_LOGOUT'] = 'Du bist ausgeloggt!'; 
$lang['LOGIN_FAILED'] = 'Falscher Username und/oder Passwort!';
$lang['LOGIN_REGISTER_OK'] = 'User Account %s ist erstellt!';
$lang['LOGIN_PASSWORD_TO_SHORT'] = 'Passwort muss mindestens 6 Zeichen lang sein!';
$lang['LOGIN_USERNAME_TO_SHORT'] = 'Username muss mindestens 4 Zeichen lang sein!';
$lang['LOGIN_USERNAME_EXIST'] = 'Username %s existiert bereits!';
$lang['LOGIN_EMAIL_EXIST'] = 'Email ist schon registriert!';
$lang['LOGIN_EMAIL_INVALID'] = 'Email ist nicht korrekt! (Falsche Schreibweise)';
$lang['LOGIN_NICKNAME_EXIST'] = 'Nickname %s wird schon benutzt!';
$lang['LOGIN_NICKNAME_NEEDED'] = 'Nickname muss eingegeben werden!';
$lang['LOGIN_NEW_PASSWORD_SEND'] = 'Das neue Passwort wurde dir per Mail geschickt!';
$lang['LOGIN_EMAIL_UNKNOWN'] = 'Email ist unbekannt!';
$lang['LOGIN_BEST_VIEWED'] = 'WarQuest ist optimiert für folgende Handys: "Apple iPhone / iPad / iPod, Nokia Smartphones, BlackBerry Smartphones, Android Smartphones" und Internet Browsers: "Microsoft Internet Explorer, Mozilla Firefox, Apple Safari, Opera, Google Chrome". This game is best viewed with browser width set to 500px. ';

$lang['LOGIN_NEW_CLIENT_TITLE'] = 'New WarQuest Client ist verfügbar!';
$lang['LOGIN_NEW_CLIENT'] = 'Sie verwenden einen alten WarQuest Windows client. Bitte besuchen Sie www.plaatsoft.nl um die neueste Version zu erhalten.';

/*
** ------------------
** HOME - OVERVIEW
** ------------------
*/

$lang['HOME_TITLE'] = 'HOME';

$lang['HOME_FLASH_NEWS_TITLE'] = 'Breaking News';

$lang['HOME_LASTEST_FORUM_POST'] = 'Letzter Forum Post';

$lang['HOME_INTRO_PLAYERS'] = 'Im Moment sind %s Spieler aus %s Ländern aktiv, ';
$lang['HOME_INTRO_FIGHTS'] = '%s Kämpfe wurden ausgetragen und ';
$lang['HOME_INTRO_REQUESTS'] = '%s Serveranfragen wurden beantwortet. ';
		
$lang['HOME_INTRO_TITLE'] = 'Anleitung';
$lang['HOME_INTRO_MISSIONS'] = 'Beginne das Spiel indem du %s ';
$lang['HOME_INTRO_BATTLES'] = 'und kämpfe %s. ';
$lang['HOME_INTRO_UNITS'] = 'Wenn du ausreichend Erfahrung und Geld gesammelt, hast kannst du bessere %s ';
$lang['HOME_INTRO_BUILDINGS'] = ' und %s um mächtiger zu werden. ';
$lang['HOME_INTRO_ENEMY'] = 'Zu jeder Zeit können andere Spiele dich angreifen. Desshalb ist es ratsam die Verteidigung nicht ausser Acht zu lassen.';

$lang['HOME_NEW_ANDROID_VERSION'] = 'Neue App Version v%s ist im Android Market verfügbar.<br/>Bitte Upgraden!';
$lang['HOME_NEW_WINDOWS_VERSION'] = 'Neuer WarQuest client v%s ist verfügbar!';
$lang['HOME_CLICK_HERE'] = 'hier';
$lang['HOME_CLICK_TEXT'] = 'Klick %s um den Download zu starten.';
$lang['HOME_EMAIL_MISSING'] = 'Please provide your email address to receive player messages by mail and be able to recover your password.';
$lang['HOME_DAILY_BONUS'] = 'Du hast %s Dollar bei einem feindlichen Stützpunkt gefunden!';

$lang['HOME_WELCOME'] = 'Willkommen';
$lang['HOME_LAST_LOGIN'] = 'Letzter Besuch  ist <b>%s</b> her.';
$lang['HOME_AWARDS'] = 'Auszeichnungen';
$lang['HOME_BATTLE_AWARDS_TEXT'] = 'Folgende Auszeichnungen hast du im Kampf verdient:';
$lang['HOME_BOUNTY_AWARDS_TEXT'] = 'Folgende Auszeichnungen hast du für Kopfgelder verdient:';
$lang['HOME_REBEL_AWARDS_TEXT'] = 'Folgende Auszeichnungen hast du für Aufstände verdient:';
$lang['HOME_OVERVIEW_TITLE']= 'Übersicht';
$lang['HOME_MAP_TITLE'] = 'eroberte Kontinente';
$lang['HOME_MAP_NOTE'] = 'Jede Mission muss dreimal absolviert, werden um den Kontinent erfolgreich einzunehmen.';

$lang['HOME_TRAVEL_TO'] = 'Reise zu';

$lang['HOME_INTRO_PLACE1'] = 'Du bist auf dem <b>%s</b> Platz in der allgemeinen Rangliste '; 
$lang['HOME_INTRO_PLACE2'] = 'und auf dem <b>%s</b> Platz auf der <b>%s</b> Rangliste. '; 
$lang['HOME_PLAYERS_ONLINE'] = 'In den letzten 24 Stunden waren %s Spieler online.';


/*
** ------------------
** HOME - PROFILE
** ------------------
*/

$lang['PLAYER_TITLE'] = 'Spieler';
$lang['PLAYER_WIN_LOST_RATE'] = 'Sieg/Niederlage Ratio';
$lang['PLAYER_BUILDINGS'] = 'Gebäude';
$lang['PLAYER_CASH_FLOW'] = 'Cash Flow';
$lang['PLAYER_ALLIANCE_SIZE'] = 'Bündnis Größe';
$lang['PLAYER_EXP_POINTS']  = 'Erfahrungspunkte';
$lang['PLAYER_SERVER_REQUEST']  = 'Server Anfragen';
$lang['PLAYER_MISSION_COMPLETED'] = 'Missionen abgeschlossen';
$lang['PLAYER_DEFENSE_STRENGTH']  = 'Verteidigungswert';
$lang['PLAYER_ATTACK_STRENGTH'] = 'Angriffswert';
$lang['PLAYER_FIGHTS_LOST'] = 'Niederlagen';
$lang['PLAYER_FIGHTS_WON']  = 'Siege';
$lang['PLAYER_BUILDING_INCOME'] = 'Gebäude Einkommen';
$lang['PLAYER_CONTINENT_INCOME'] = 'Kontinent Einkommen';
$lang['PLAYER_BOUNTY_SET'] = 'Belohnungen ausgesetzt';
$lang['PLAYER_REBELLION_RISE'] = 'Aufstände ausgelöst';
$lang['PLAYER_UPKEEP']  = 'Kosten pro Stunde';
$lang['PLAYER_NETTO_INCOME']  = 'Netto Einkommen';
$lang['PLAYER_STATISTICS']  = 'Statistik'; 
$lang['PLAYER_DISCOUNT_MAINTENANCE']  = 'Rabatt & Zustand';
$lang['PLAYER_NAME']  = 'Name'; 
$lang['PLAYER_ID']  = 'Id';
$lang['PLAYER_RANK']  = 'Rang'; 
$lang['PLAYER_OVERVIEW']  = 'Profil'; 
$lang['PLAYER_DISCOUNT_RATE'] = 'Gebäude Rabatt';
$lang['PLAYER_MAINTENANCE_RATE'] = 'Einheiten Zustand';
$lang['PLAYER_LAST_LOGIN'] = 'Zuletzt aktiv (Vor)';
$lang['PLAYER_CREATED'] = 'Erstellt (Vor)';
$lang['PLAYER_CASINO_PLAYED']  = 'Kasino besucht';
$lang['PLAYER_ADS_SHOWED']  = 'Werbung erhalten';


$lang['PLAYER_ATTACK_FORCE'] = 'Übersicht (Angriff %s)';
$lang['PLAYER_DEFENSE_FORCE'] = 'Übersicht (Verteidigung %s)';
$lang['PLAYER_ATTACK_TEXT'] = '%s hat momentan <b>%s</b> Verbündete und kann eine maximale Armeegröße von <b>%s</b> Einheiten befehligen. Der Angriffswert von %s errechnet sich aus folgenden Einheiten:';
$lang['PLAYER_DEFENSE_TEXT'] = '%s hat mometan <b>%s</b> Verbündete und kann eine maximale Armeegröße von <b>%s</b> Einheiten befehligen. Der Verteidigungswert von %s errechnet sich aus folgenden Einheiten:';
$lang['PLAYER_UNIT'] = 'Einheit';
$lang['PLAYER_AMOUNT'] = 'Anzahl';
$lang['PLAYER_STRENGTH'] = 'Stärke';
$lang['PLAYER_ATTACK_SKILLS'] = 'Angriffswert';
$lang['PLAYER_DEFENSE_SKILLS'] = 'Verteidigungswert';
$lang['PLAYER_SUB_TOTAL'] = 'Sub total';
$lang['PLAYER_TOTAL'] = 'Total';
$lang['PLAYER_FORCE'] = 'Angriffs & Verteidigungsstärke'; 
$lang['PLAYER_DEPLOYED'] = 'Beschäftigt';

$lang['PLAYER_BUILDING'] = 'Gebäude';
$lang['PLAYER_INCOME'] = 'Einkommen';
$lang['PLAYER_COST'] = 'Kosten';
$lang['PLAYER_BUILDING_OVERVIEW'] = 'Gebäude Einkommen Übersicht';
$lang['PLAYER_BUILDING_TEXT'] = 'SPieler %s hat ein momentaniges Einkommen durch Gebäude in Höhe von %s:';
$lang['PLAYER_UPKEEP_COST'] = 'Stündliche Kosten Übersicht';
$lang['PLAYER_UPKEEP_TEXT'] = 'Spieler %s besitzt im Moment folgende %s Einheit(en):';
$lang['PLAYER_CONTINENT_OVERVIEW'] = 'Kontinent Einkommen Übersicht';
$lang['PLAYER_CONTINENT_TEXT'] = 'Spieler %s eroberte folgende %s Kontinent(e):';

$lang['PLAYER_SPY_1'] = 'Spionage';
$lang['PLAYER_SPY_2'] = 'Kundschafter';
$lang['PLAYER_SPY_3'] = 'Kundschafter';
$lang['PLAYER_ESPIONAGE_UNLOCK1'] = 'Freigeschaltet wenn deine %s Stärke um %s% höher ist als beim Gegner.';
$lang['PLAYER_ESPIONAGE_UNLOCK2'] = 'Freigeschaltet wenn deine %s Stärke gleich oder höher als beim Gegner.';

$lang['PLAYER_MONEY_STATUS'] = 'Current Assets';
$lang['PLAYER_CASH_MONEY'] = 'Geld';
$lang['PLAYER_BANK'] = 'Bank';

$lang['PLAYER_PLATFORM_BROWSER'] = 'Platform & Browser';
$lang['PLAYER_BROWSER'] = 'Browser';
$lang['PLAYER_BROWSER_VERSION'] = 'Version';
$lang['PLAYER_PLATFORM'] = 'Platform';

$lang['PLAYER_LAST_TWEET'] = 'Letzte Meldung';

/*
** ------------------
** HOME - NEWS
** ------------------
*/

$lang['HOME_BATTLE_TITLE'] = 'Neuigkeiten';
$lang['HOME_BATTLE_ATTACK_BY'] = 'You were attacked by the %s of %s.';
$lang['HOME_BATTLE_YOU_WON'] = 'Du hast <b>GEWONNEN</b>. ';
$lang['HOME_BATTLE_YOU_LOST'] = 'Du hast <b>VERLOREN</b>. ';
$lang['HOME_BATTLE_YOU_EXP'] = 'Du erhälst %s Erfahrung ';
$lang['HOME_BATTLE_TOOK_DAMAGE'] = 'und teilst %s Schaden aus.';
$lang['HOME_BATTLE_TAKING_DAMAGE'] = 'und erleidest %s Punkte Schaden.';
$lang['HOME_BATTLE_YOU_MONEY'] = 'Verlierst %s dollar ';
$lang['HOME_BATTLE_NO_NEWS'] = 'No battle news available on this moment!'; 

$lang['HOME_BOUNTY_NEWS'] = '%s hat ein Kopfgeld von %s Dollar auf dich gesetzt . Wenn du besiegt wirst, verlierst du %s Erfahrungspunkte.';

/*
** ------------------
** HOME - MESSAGE
** ------------------
*/

$lang['HOME_COMMENTS_TITLE']= 'Nachricht';
$lang['HOME_COMMENT_DELETED'] = 'Nachricht gelöscht!';
$lang['HOME_NO_COMMENTS'] = 'Keine Nachrichten von Spielern verfügbar!'; 

/*
** ------------------
** HOME - SKILLS
** ------------------
*/

$lang['PLAYER_SKILL_SUBTITLE1']  = 'Skill Punkte';
$lang['PLAYER_SKILL_SUBTITLE2']  = 'Skill Punkte [%s verfügbar]';
$lang['PLAYER_SKILL_NOTE']  = 'Tipp : Verteile Skillpunkte um deinen Angriffs-, verteidigungs-, Gesunheits- und Energiewert zusteigern oder dein Munitionsdepot zu erhöhen.';
$lang['PLAYER_SKILLS']  = 'Skills'; 
$lang['PLAYER_MAX'] = 'Current'; 
$lang['PLAYER_ATTACK']  = 'ANGRIFF';
$lang['PLAYER_DEFENSE'] = 'VERTEIDIGUNG';
$lang['PLAYER_HEALTH']  = 'GESUNDHEIT'; 
$lang['PLAYER_ENERGY']  = 'ENERGIE'; 
$lang['PLAYER_AMMO']  = 'MUNITION'; 
$lang['PLAYER_ATTACK_TIP']  = 'Erhöhe deinen Angriffswert um mehr Schaden und mehr Kriege zu gewinnen. Es koste 1 Skillpunkt um deinen Angriffswert um  %s zu erhöhen. Deinen Angriffswert wird auf %s reduziert um einen 1 Skillpunkt wiederzuerlangen.';
$lang['PLAYER_DEFENSE_TIP'] = 'Erhöhe deinen Verteidigungswert um größeren Angriffen standzuhalten. Es kostet 1 Skillpunkt um deinen Verteidigungswert um %s zu erhöhen. Deinen Verteidigungswert wird auf %s reduziert um einen 1 Skillpunkt wiederzuerlangen.';
$lang['PLAYER_HEALTH_TIP']  = 'Erhöhe deine Gesundheit um länger bei intensive Gefechten am Leben zu bleiben. Es kostet 1 Skillpunkt um deine maximale Gesundheit um 10 zu erhöhen. Dein Gesundheitswert wird um 20 reduziert um 1 Skillpunkt wiederzuerlangen.';
$lang['PLAYER_ENERGY_TIP']  = 'Erhöhe deinen maximale Energie um mehr Missionen zu auszuführen. Es kostet 1 Skillpunkt um deine maximale Energie um 10 zu erhöhen. Reduziere dein Energie-Niveau um 20 um 1 Skillpunkt wiederzuerlangen.';
$lang['PLAYER_AMMO_TIP']  = 'Erhöhe dein Munitionsdepot um mehr Angriffe gegen Spieler auszüben. Es kostet 2 Skillpunkte um dein Munitionsdepot um 1 zu erhöhen. Reduziere dein Munitionsdepot um 1 um 1 Skillpunkt wiederzuerlangen.';
$lang['PLAYER_SKILL_ACCEPTED1']  = '%s s Wert erhöht.';
$lang['PLAYER_SKILL_REJECTED1']  = 'Du benötigst %s Skillpunkt(e) um den Wert zu ändern.';
$lang['PLAYER_SKILL_ACCEPTED2']  = '%s s Wert reduziert.';
$lang['PLAYER_SKILL_REJECTED2']  = '%s s Wert ist auf der kleinsten Stufe.';

/*
** ------------------
** HOME - TRADE
** ------------------
*/

$lang['HOME_TRADE_CONDITION'] = 'Current';
$lang['HOME_TRADE_MINIMAL'] = 'Minimal';

$lang['HOME_TRADE1'] = 'Health Timer';
$lang['HOME_TRADE1_NOTE'] = 'Decrease health timer so your health restores faster. It takes 1 trade point to decrease your health timer with 5 seconds.';

$lang['HOME_TRADE2'] = 'Energy Timer';
$lang['HOME_TRADE2_NOTE'] = 'Decrease energy timer so your energy restores faster. It takes 1 trade point to decrease your energy timer with 5 seconds.';

$lang['HOME_TRADE3'] = 'Ammo Timer';
$lang['HOME_TRADE3_NOTE'] = 'Decrease ammo timer so your ammo restores faster. It takes 1 trade point to decrease your ammo timer with 5 seconds.';

$lang['HOME_TRADE4'] = 'Cash';
$lang['HOME_TRADE4_NOTE'] = 'Get cash to buy new units, buildings, etc.. It takes 1 trade point to increase your cash with %s dollar.';

$lang['HOME_TRADE5'] = 'Skill Point';
$lang['HOME_TRADE5_NOTE'] = 'Get skill points to improve your attack, defence, health, energy or ammo skill. It takes 1 trade point to get 2 skill points.';

$lang['HOME_TRADE_SKILL_POINTS'] = 'skill point(s)';
$lang['HOME_TRADE_IN'] = 'Trade-In';
$lang['HOME_MAX_REACHED'] = 'Max Reached';
$lang['HOME_TRADE_NO_POINTS'] = 'You do not own %s trade point(s).';
$lang['HOME_TRADE_HEALTH_TIMER_TO_LARGE'] = 'Health timer has reached minimum value.';
$lang['HOME_TRADE_ENERGY_TIMER_TO_LARGE'] = 'Energy timer has reached minimum value.';
$lang['HOME_TRADE_AMMO_TIMER_TO_LARGE'] = 'Ammo timer has reached minimum value.';
$lang['HOME_TRADE_SUCCESFULL'] = 'The trade point is succesfully processed!';

/*
** ------------------
** HOME - RESTORE
** ------------------
*/

$lang['PLAYER_RESTORE_TITLE'] = 'Wiederherstellen & Reparieren';
$lang['PLAYER_RESTORE_SUBTITLE1'] = 'Wiederherstellen';
$lang['PLAYER_RESTORE_SUBTITLE2'] = 'Reparieren';
$lang['PLAYER_RESTORE_UNLOCKED'] = 'Wiederherstellen & Reparieren ist freigeschaltet ab Level %s.';
$lang['PLAYER_RESTORE_PRICE'] = 'Wiederherstellungspreis';
$lang['PLAYER_REPAIR_PRICE'] = 'Reperaturkosten';
$lang['PLAYER_RESTORED_FAILED'] = 'Nicht genug Geld!';

$lang['PLAYER_HEALTH_TITLE'] = 'Gesundheit wiederherstellen';
$lang['PLAYER_HEALTH_NOTE'] = 'Bezahle den Krankenhausaufenthalt für deine Soldaten damit ihre Gesundheit zurückkehrt. Eine Behandlung kann nur jede 5 Minuten erfolgen. Der Heilungsprozess findet auch unabhängig vom Krankenhaus statt.';	
$lang['PLAYER_HEALTH_CONDITION'] = 'Gesundheitszustand';
$lang['PLAYER_HEALTH_RESTORED'] = 'Gesundheit wiederherstellen für %s Dollar.';
$lang['PLAYER_HEALTH_CONFIRM'] = 'Möchtest du wirklich das Krankenhaus aufsuchen?';

$lang['PLAYER_ENERGY_TITLE'] = 'Restore Energy';
$lang['PLAYER_ENERGY_NOTE'] = 'Kaufe Benzin um die Energievorräte deiner Amee aufzufüllen. Die Wiederherstellung kann nur alle 24-Stunden erfolgen. Die Energieleiste füllt sich auch selbstständig mit der Zeit. ';	
$lang['PLAYER_ENERGY_CONDITION'] = 'Energiezustand';
$lang['PLAYER_ENERGY_RESTORED'] = 'Energie wieder herstellen f+r %s Dollar.';
$lang['PLAYER_ENERGY_CONFIRM'] = 'Möchtest du wirklich Benzin kaufen?';

$lang['PLAYER_AMMO_TITLE'] = 'Munitions auffüllen';
$lang['PLAYER_AMMO_NOTE'] = 'Bezahle einen großen Waffenhändler um sofort Munition zu erhalten. Der Waffenhändler kann nur alle 24 Stunden ausliefern. Deine Fabriken fertigen auch unabhängig vom Händler.';	
$lang['PLAYER_AMMO_CONDITION'] = 'Munition';
$lang['PLAYER_AMMO_RESTORED'] = 'Munition auffüllen für %s Dollar.';
$lang['PLAYER_AMMO_CONFIRM'] = 'Möchtest du wirklich dein Depot auffüllen lassen?';

$lang['PLAYER_CEASE_FIRE_TITLE'] = 'Waffenruhe';
$lang['PLAYER_CEASE_FIRE_NOTE'] = 'Bezahle Schutzgeld für 8 Stündige Feuerpause. Während dieser Zeit ist es anderen Spielern nicht möglich dich anzugreifen, jedoch gilt dieses Abkommen auch für dich.';	
$lang['PLAYER_CEASE_FIRE_ACTIVATED'] = 'Abkommen für Waffenruhe kaufen für %s Dollar.';
$lang['PLAYER_CEASE_FIRE_CONFIRM'] = 'Möchtest du wirklich das Abkommen abzeichnen?';

$lang['PLAYER_UNITS_TITLE'] = 'Werkstatt';
$lang['PLAYER_UNITS_NOTE'] = 'Lass deine Einheiten reparieren. Wenn der Zustand bei 0% ist werden manche Einheiten zerstört and the remaining units are automaticly repaired.';	
$lang['PLAYER_UNITS_CONDITION'] = 'Einheiten Zustand(UC)';
$lang['PLAYER_UNITS_REPAIRED'] = 'Einheiten reparieren für %s Dollar.';
$lang['PLAYER_UNITS_CONFIRM'] = 'Möchtest du wirklich deine Einheiten reparieren lassen?';

$lang['PLAYER_BUILDINGS_TITLE'] = 'Gebäude Restauration';
$lang['PLAYER_BUILDINGS_NOTE'] = 'Restauriere deine Gebäude um sie vor dem Verfall zu retten. Wenn der Wert auf 0% sinkt werden einige Gebäude zerstört und die übrigen Gebäude renoviert.';	
$lang['PLAYER_BUILDINGS_CONDITION'] = 'Gebäude Zustand (BC)';
$lang['PLAYER_BUILDINGS_REPAIRED'] = 'Gebäude restaurieren für %s Dollar.';
$lang['PLAYER_BUILDINGS_CONFIRM'] = 'Möchtest du wirklich deine Gebäude restaurieren?';

$lang['PLAYER_REBELLION_TITLE'] = 'Aufstand vermeiden';
$lang['PLAYER_REBELLION_NOTE'] = 'Besteche die Anführer der Rebellen um sie zu besänftigen. Sollte der Wert bei 100% liegen ist ein Aufstand unausweichlich und einige Regionen müssen erneut erobert werden.';	
$lang['PLAYER_REBELLION_CONDITION'] = 'Rebellen im Volk (RC)';
$lang['PLAYER_REBELLION_RESTORED'] = 'Rebellen bestechen für %s Dollar.';
$lang['PLAYER_REBELLION_CONFIRM'] = 'Möchtest du wirklich die Rebellen bestechen?';

/*
** ------------------
** HOME - SETTINGS
** ------------------
*/

$lang['SETTING_TITLE'] = 'Einstellung';
$lang['SETTING_GENERAL1'] = 'Grundeinstellungen 1';
$lang['SETTING_GENERAL2'] = 'Grundeinstelungen 2';

$lang['SETTING_NICKNAME'] = 'WarQuest Nickname';
$lang['SETTING_TWITTER'] = 'Twitter Account';
$lang['SETTING_LANGUAGE'] = 'Sprache';
$lang['SETTING_BACKGROUND'] = "Hintergrund";
$lang['SETTING_SOUND'] = 'Sound aktivieren (Experimental)';
$lang['SETTING_BOUNTY'] = 'Kopfgeld Bestätigung aktivieren.';
$lang['SETTING_RESTORE'] = 'Wiederherstellen & Reparatur Bestätigung aktivieren.';
$lang['SETTING_CONDITION'] = 'Zustand von Einheiten/Gebäuden/Aufstand in einem Banner aktivieren.';
$lang['SETTING_FORUM_POST'] = 'Letzten Eintrag vom Forum auf der Start-Seite aktivieren.';
$lang['SETTING_SORT1'] = 'Die neuesten Nachrichten oben im Forum.';
$lang['SETTING_SORT2'] = 'Älteste Spieler nach oben in der Kampf-Liste.';

$lang['PLAYER_LANG_ENGLISH'] = 'Englisch';
$lang['PLAYER_LANG_DUTCH'] = 'Holländisch';
$lang['PLAYER_LANG_GERMAN'] = 'German';
$lang['PLAYER_LANG_ITALIAN'] = 'Italian';

$lang['BACKGROUND_0'] = 'schwarz';
$lang['BACKGROUND_1'] = 'Armee Grün';
$lang['BACKGROUND_2'] = 'Rote Aura';
$lang['BACKGROUND_3'] = 'Steingrau';
$lang['BACKGROUND_4'] = 'Pinke Kreise';
$lang['BACKGROUND_5'] = 'Blaue Seide';
$lang['BACKGROUND_6'] = 'Braun';
$lang['BACKGROUND_7'] = 'Pirat';
$lang['BACKGROUND_8'] = 'Modern';
$lang['BACKGROUND_9'] = 'Klassich';
$lang['BACKGROUND_10'] = 'Schokolade';
$lang['BACKGROUND_11'] = 'Weihnachten';
$lang['BACKGROUND_12'] = 'Feuerwerk';

$lang['PLAYER_GENERAL_CHANGED'] = 'Grundeinstellungen geändert!';
$lang['NICKNAME_EXIST'] = 'Nickname ist schon gewählt!';
$lang['NICKNAME_TO_SHORT'] = 'Nickname muss mindestens 4 Zeichen lang sein!';
$lang['NICKNAME_NO_SPACE'] = 'Space character(s) in nickname is not allowed!';

$lang['PLAYER_CHANGE_EMAIL'] = 'Email Einstellungen';
$lang['PLAYER_NEW_EMAIL'] = 'Email Addresse';
$lang['PLAYER_NOTIFICATION_ALLIANCE'] = 'Bündnisanfragen per mail';
$lang['PLAYER_NOTIFICATION_COMMENT'] = 'Nachrichteneingang per mail';
$lang['PLAYER_EMAIL_CHANGED'] = 'Email Einstellung geändert';
$lang['PLAYER_EMAIL_EXIST'] = 'Email Adresse ist bereits registriert!';
$lang['PLAYER_EMAIL_INVALID'] = 'Email Adresse ist nicht gültig (Falsche Schreibweise)!';

$lang['PLAYER_LOGIN_SETTINGS'] = 'Login Einstellungen';
$lang['PLAYER_USERNAME'] = 'Username';
$lang['PLAYER_USERNAME_TO_SHORT'] = 'Username muss mindestens 4 Zeichen lang sein!';
$lang['PLAYER_USERNAME_ALREADY_EXIST'] = 'Username existiert bereits!';
$lang['PLAYER_USERNAME_CHANGED'] = 'Username ist geändert. Vergiß nicht deinen Username in der WarQuest Android und/oder Windows app zu ändern, ansonsten funktioniert der automatische LogIn nicht mehr!';
$lang['PLAYER_CURRENT_PASSWORD'] = 'Bisheriges Passwort';		
$lang['PLAYER_NEW_PASSWORD'] = 'Neues Passwort';
$lang['PLAYER_PASSWORD_CHANGED'] = 'Passwort geändert. Vergiß nicht dein Passwort in der WarQuest Android und/oder Windows app zu ändern, ansonsten funktioniert der automatische LogIn nicht mehr!';
$lang['PLAYER_PASSWORD_NO_MATCH'] = 'Das jetztige Passwort stimmt nicht überein!';
$lang['PLAYER_PASSWORD_TO_SHORT'] = 'Das neue Passwort muss mindestens 6 Zeichen lang sein!';
$lang['PLAYER_LOGIN_NOTE'] = 'ACHTUNG: Der automatische Login während des Starts funktioniert nur wenn der Username und das Passwort eingestellt ist in der WarQuest Android und/oder Windows app!'; 

$lang['SETTING_ACCOUNT_RESET_TITLE'] = 'Account reset';
$lang['SETTING_YES'] = 'Yes';
$lang['SETTING_SURE'] = 'Account reset! Are your really sure?';
$lang['SETTING_ACCOUNT_RESET'] = 'Activate an account reset? ';
$lang['SETTING_NO_REVERSE'] = '(This reset action can not be reversed!)';
$lang['SETTING_ACCOUNT_RESET_NOTE'] = 'WARNING: When your account is resetted all data of your account is put back to the begin state. This means that everything is removed (units, buildings, alliances, missions, etc..)'; 
$lang['SETTING_ACCOUNT_RESETTED'] = 'Player %s account is resetted!';

/*
** ------------------
** MISSION DATA
** ------------------
*/

/* Earth Missions */
$lang['MISSION_GROUP_0'] = 'Training';
$lang['MISSION_GROUP_1'] = 'Europa';
$lang['MISSION_GROUP_2'] = 'N-Amerika';
$lang['MISSION_GROUP_3'] = 'S-Amerika';
$lang['MISSION_GROUP_4'] = 'Afrika';
$lang['MISSION_GROUP_5'] = 'N-Asien';
$lang['MISSION_GROUP_6'] = 'S-Asien';
$lang['MISSION_GROUP_7'] = 'E-Asien';
$lang['MISSION_GROUP_8'] = 'Australien';
$lang['MISSION_GROUP_9'] = 'Nahost';

$lang['MISSION_0'] = 'Trainings Mission';
$lang['MISSION_1'] = 'Groß-Britannien';
$lang['MISSION_2'] = 'Luxemburg';
$lang['MISSION_3'] = 'Frankreich';
$lang['MISSION_4'] = 'Zentral Europa';
$lang['MISSION_5'] = 'Skandinavien';
$lang['MISSION_6'] = 'Ost Europa';
$lang['MISSION_7'] = 'Spanien';
$lang['MISSION_8'] = 'Süd Europa';

$lang['MISSION_10'] = 'Grönland';
$lang['MISSION_11'] = 'Kanada';
$lang['MISSION_12'] = 'USA';
$lang['MISSION_13'] = 'Mexiko';
$lang['MISSION_14'] = 'Guatemala Region';
$lang['MISSION_15'] = 'Nicaragua Region';
$lang['MISSION_16'] = 'Kuba Region';
$lang['MISSION_17'] = 'Karibik Region';

$lang['MISSION_20'] = 'Mittel Amerika';
$lang['MISSION_21'] = 'Equador';
$lang['MISSION_22'] = 'Bolivien';
$lang['MISSION_23'] = 'Paraguay';
$lang['MISSION_24'] = 'Chile Region';
$lang['MISSION_25'] = 'Argentinien';
$lang['MISSION_26'] = 'Uruguay';
$lang['MISSION_27'] = 'Brasilien';

$lang['MISSION_30'] = 'Algerien';
$lang['MISSION_31'] = 'Ägypten';
$lang['MISSION_32'] = 'West Afrika';
$lang['MISSION_33'] = 'Zentral Africa';
$lang['MISSION_34'] = 'Ost Afrika';
$lang['MISSION_35'] = 'Mozambique Region';
$lang['MISSION_36'] = 'Zimbabwe Region';
$lang['MISSION_37'] = 'Süd Afrika';

$lang['MISSION_40'] = 'Russland';
$lang['MISSION_41'] = 'Mongolei';
$lang['MISSION_42'] = 'Kasachstan';
$lang['MISSION_43'] = 'Uzbekistan';
$lang['MISSION_44'] = 'Tajikistan';
$lang['MISSION_45'] = 'Turkmenistan';
$lang['MISSION_46'] = 'Georgien';
$lang['MISSION_47'] = 'Armenien';

$lang['MISSION_50'] = 'Iran';
$lang['MISSION_51'] = 'Afghanistan';
$lang['MISSION_52'] = 'Pakistan';
$lang['MISSION_53'] = 'Indien';
$lang['MISSION_54'] = 'Nepal';
$lang['MISSION_55'] = 'Bangladesh';
$lang['MISSION_56'] = 'Thailand';
$lang['MISSION_57'] = 'Laos';

$lang['MISSION_60'] = 'China';
$lang['MISSION_61'] = 'Nord Korea';
$lang['MISSION_62'] = 'Süd Korea';
$lang['MISSION_63'] = 'Japan';
$lang['MISSION_64'] = 'Taiwan';
$lang['MISSION_65'] = 'Kambotscha';
$lang['MISSION_66'] = 'Vietnam';
$lang['MISSION_67'] = 'Malaysia';

$lang['MISSION_70'] = 'West Indonesien';
$lang['MISSION_71'] = 'Ost Indonesien';
$lang['MISSION_72'] = 'Philippin';
$lang['MISSION_73'] = 'Papua New Guinea';
$lang['MISSION_74'] = 'Timor';
$lang['MISSION_75'] = 'Nord Australien';
$lang['MISSION_76'] = 'Süd Australien';
$lang['MISSION_77'] = 'Neuseeland';

$lang['MISSION_80'] = 'Syria';
$lang['MISSION_81'] = 'Irak';
$lang['MISSION_82'] = 'Saudi Arabien';
$lang['MISSION_83'] = 'Kuwait';
$lang['MISSION_84'] = 'Yemen';
$lang['MISSION_85'] = 'Oman';
$lang['MISSION_86'] = 'Jordan';
$lang['MISSION_87'] = 'Israel';

/* Moon Missions */
$lang['MISSION_GROUP_10'] = 'Alpha ';
$lang['MISSION_GROUP_11'] = 'Bravo';
$lang['MISSION_GROUP_12'] = 'Charlie';
$lang['MISSION_GROUP_13'] = 'Delta';
$lang['MISSION_GROUP_14'] = 'Echo';
$lang['MISSION_GROUP_15'] = 'Foxtrot';
$lang['MISSION_GROUP_16'] = 'Golf';
$lang['MISSION_GROUP_17'] = 'Hotel';
$lang['MISSION_GROUP_18'] = 'Lima';

$lang['MISSION_100'] = 'Krater Endymion';
$lang['MISSION_101'] = 'Krater Franklin';
$lang['MISSION_102'] = 'Tal Honoris';
$lang['MISSION_103'] = 'Berg Fidei';
$lang['MISSION_104'] = 'Krater Blanc';
$lang['MISSION_105'] = 'Krater Fesenkov';
$lang['MISSION_106'] = 'Gipfel Temporis';
$lang['MISSION_107'] = 'Krater Darwin';

$lang['MISSION_110'] = 'Krater Agnes';
$lang['MISSION_111'] = 'Berg Andre';
$lang['MISSION_112'] = 'Hügel Ardeshir';
$lang['MISSION_113'] = 'Krater Aristoteles';
$lang['MISSION_114'] = 'Mare Blanc';
$lang['MISSION_115'] = 'Berg Bradley';
$lang['MISSION_116'] = 'Hügel Delisle';
$lang['MISSION_117'] = 'Tal Dieter';

$lang['MISSION_120'] = 'Berg Dilip';
$lang['MISSION_121'] = 'Berg Esam';
$lang['MISSION_122'] = 'Krater Albategnius';
$lang['MISSION_123'] = 'Berg Gruithuisen Delta';
$lang['MISSION_124'] = 'Mare Gruithuisen Gamma';
$lang['MISSION_125'] = 'Krater Hansteen';
$lang['MISSION_126'] = 'Hügel Herodotus';
$lang['MISSION_127'] = 'Berg Huygens';

$lang['MISSION_130'] = 'Tal La Hire';
$lang['MISSION_131'] = 'Berg Maraldi';
$lang['MISSION_132'] = 'Berg Moro';
$lang['MISSION_133'] = 'Krater Aristarchus';
$lang['MISSION_134'] = 'Berg Pico';
$lang['MISSION_135'] = 'Hügel Piton';
$lang['MISSION_136'] = 'Tal Rumker';
$lang['MISSION_137'] = 'Berg Usov';

$lang['MISSION_140'] = 'Berg Vinogradov';
$lang['MISSION_141'] = 'Berg Vitruvius';
$lang['MISSION_142'] = 'Berg Wolff';
$lang['MISSION_143'] = 'Gipfel Agricola';
$lang['MISSION_144'] = 'Gipfel Alpes';
$lang['MISSION_145'] = 'Krater Apenninus';
$lang['MISSION_146'] = 'Gipfel Archimedes';
$lang['MISSION_147'] = 'Gipfel Carpatus';

$lang['MISSION_150'] = 'Gipfel Caucasus';
$lang['MISSION_151'] = 'Mare Cordillera';
$lang['MISSION_152'] = 'Gipfel Haemus';
$lang['MISSION_153'] = 'Krater Harbinger';
$lang['MISSION_154'] = 'Tal Pyrenaeus';
$lang['MISSION_155'] = 'Gipfel Riphaeus';
$lang['MISSION_156'] = 'Gipfel Rook';
$lang['MISSION_157'] = 'Mare Secchi';

$lang['MISSION_160'] = 'Gipfel Spitzbergen';
$lang['MISSION_161'] = 'Mare Taurus';
$lang['MISSION_162'] = 'Tal Teneriffe';
$lang['MISSION_163'] = 'Gipfel Harbinger';
$lang['MISSION_164'] = 'Hügel Rheita';
$lang['MISSION_165'] = 'Hügel Baade';
$lang['MISSION_166'] = 'Krater Bohr';
$lang['MISSION_167'] = 'Hügel Palitzsch';

$lang['MISSION_170'] = 'Krater Fecunditatis';
$lang['MISSION_171'] = 'Mare Australe';
$lang['MISSION_172'] = 'Gipfel Orientale';
$lang['MISSION_173'] = 'Tal Cognitum';
$lang['MISSION_174'] = 'Mare Crisium';
$lang['MISSION_175'] = 'Berg Spumans';
$lang['MISSION_176'] = 'Gipfel Tranquillitatis';
$lang['MISSION_177'] = 'Mare Vaporum';

$lang['MISSION_180'] = 'Krater Aestatis';
$lang['MISSION_181'] = 'Lacus Bonitatis';
$lang['MISSION_182'] = 'Gipfel Felicitatis';
$lang['MISSION_183'] = 'Tal Luxuriae';
$lang['MISSION_184'] = 'Lacus Oblivionis';
$lang['MISSION_185'] = 'Berg Solitudinis';
$lang['MISSION_186'] = 'Gipfel Temporis';
$lang['MISSION_187'] = 'Krater Timoris';

/* Mars Missions */
$lang['MISSION_GROUP_20'] = 'Alpaca';
$lang['MISSION_GROUP_21'] = 'Bison';
$lang['MISSION_GROUP_22'] = 'Coyote';
$lang['MISSION_GROUP_23'] = 'Dinosaur';
$lang['MISSION_GROUP_24'] = 'Emu';
$lang['MISSION_GROUP_25'] = 'Fox';
$lang['MISSION_GROUP_26'] = 'Gnu';
$lang['MISSION_GROUP_27'] = 'Heron';
$lang['MISSION_GROUP_28'] = 'Lion';

$lang['MISSION_200'] = 'Krater Al-Qahira';
$lang['MISSION_201'] = 'Tal Ares';
$lang['MISSION_202'] = 'Hügel Auqakuh';
$lang['MISSION_203'] = 'Krater Bahram';
$lang['MISSION_204'] = 'Mare Harmakhis';
$lang['MISSION_205'] = 'Berg Her Desher';
$lang['MISSION_206'] = 'Tal Hrad';
$lang['MISSION_207'] = 'Hügel Huo Hsing';

$lang['MISSION_210'] = 'Berg Kasei';
$lang['MISSION_211'] = 'Mare Labou';
$lang['MISSION_212'] = 'Hügel Maadim';
$lang['MISSION_213'] = 'Krater Maja';
$lang['MISSION_214'] = 'Tal Mamers';
$lang['MISSION_215'] = 'Hügel Mangala';
$lang['MISSION_216'] = 'Krater Marte';
$lang['MISSION_217'] = 'Mare Mawrth';

$lang['MISSION_220'] = 'Krater Nirgal';
$lang['MISSION_221'] = 'Hügel Shalbatana';
$lang['MISSION_222'] = 'Krater Simud';
$lang['MISSION_223'] = 'Tal Tiu';
$lang['MISSION_224'] = 'Hügel Aloysius';
$lang['MISSION_225'] = 'Krater Ambrosius';
$lang['MISSION_226'] = 'Mare Barnabas';
$lang['MISSION_227'] = 'Mare Constantia';

$lang['MISSION_230'] = 'Hügel Edmondus';
$lang['MISSION_231'] = 'Mare Eustachius';
$lang['MISSION_232'] = 'Krater Georgius';
$lang['MISSION_233'] = 'Tal Griselda';
$lang['MISSION_234'] = 'Hügel Gualterius';
$lang['MISSION_235'] = 'Krater Homfridus';
$lang['MISSION_236'] = 'Mare Henricus';
$lang['MISSION_237'] = 'Guglielmus';

$lang['MISSION_240'] = 'Mare Janetta';
$lang['MISSION_241'] = 'Hügel Jerominus';
$lang['MISSION_242'] = 'Krater Josephus';
$lang['MISSION_243'] = 'Mare Leonardus';
$lang['MISSION_244'] = 'Tal Mauritius';
$lang['MISSION_245'] = 'Krater Nicholaus';
$lang['MISSION_246'] = 'Hügel Laurentius';
$lang['MISSION_247'] = 'Berg Octavius';

$lang['MISSION_250'] = 'Krater Misericordia';
$lang['MISSION_251'] = 'Hügel Petronella';
$lang['MISSION_252'] = 'Tal Sylvanus';
$lang['MISSION_253'] = 'Krater Reginaldus';
$lang['MISSION_254'] = 'Hügel Adeipho';
$lang['MISSION_255'] = 'Tal Randulphus';
$lang['MISSION_256'] = 'Krater Xpofer';
$lang['MISSION_257'] = 'Mare Aegidius';

$lang['MISSION_260'] = 'Tal Aeneas';
$lang['MISSION_261'] = 'Krater Philipus';
$lang['MISSION_262'] = 'Tal Beniaminus';
$lang['MISSION_263'] = 'Hügel Rosamundi';
$lang['MISSION_264'] = 'Berg Peregrinus';
$lang['MISSION_265'] = 'Mare Xtianus';
$lang['MISSION_266'] = 'Hügel Crispianus';
$lang['MISSION_267'] = 'Krater Clementia';

$lang['MISSION_270'] = 'Hügel Elizabeta';
$lang['MISSION_271'] = 'Krater Xtopher';
$lang['MISSION_272'] = 'Mare Placentia';
$lang['MISSION_273'] = 'Tal Gaufridus';
$lang['MISSION_274'] = 'Krater Stephanus';
$lang['MISSION_275'] = 'Hügel Xpianus	';
$lang['MISSION_276'] = 'Mare Girardus';
$lang['MISSION_277'] = 'Krater Radulphus';

$lang['MISSION_280'] = 'Krater Xtopherus';
$lang['MISSION_281'] = 'Hügel Terentius';
$lang['MISSION_282'] = 'Berg Eamnonn';
$lang['MISSION_283'] = 'Krater Kadisha';
$lang['MISSION_284'] = 'Mare Kachine';
$lang['MISSION_285'] = 'Hügel Oddvar';
$lang['MISSION_286'] = 'Tal Radborne';
$lang['MISSION_287'] = 'Krater Ebenezer';

/* Asteroid */
$lang['MISSION_300'] = 'Crater Albococcinea';
$lang['MISSION_301'] = 'Sinus argentea';
$lang['MISSION_302'] = 'Vallis Atrococcinea';
$lang['MISSION_303'] = 'Crater Colorans';
$lang['MISSION_304'] = 'Mare Cardinalis';
$lang['MISSION_305'] = 'Mons Brunnea';
$lang['MISSION_306'] = 'Sinus Chlorantha';
$lang['MISSION_307'] = 'Vallis Erythrocarpa';

$lang['MISSION_310'] = 'Mons Ferruginea';
$lang['MISSION_311'] = 'Mare Colorans';
$lang['MISSION_312'] = 'Vallis Aurea';
$lang['MISSION_313'] = 'Crater Atrovirens';
$lang['MISSION_314'] = 'Sinus lutescens';
$lang['MISSION_315'] = 'Vallis Maculata';
$lang['MISSION_316'] = 'Crater Nigrescens';
$lang['MISSION_317'] = 'Mare Punicea';

$lang['MISSION_320'] = 'Crater Rosea';
$lang['MISSION_321'] = 'Vallis Rubiginosa';
$lang['MISSION_322'] = 'Crater Tinctoria';
$lang['MISSION_323'] = 'Sinus Sulphurea';
$lang['MISSION_324'] = 'Vallis Sempervirens';
$lang['MISSION_325'] = 'Crater Rubicunda';
$lang['MISSION_326'] = 'Mare Variegata';
$lang['MISSION_327'] = 'Mare Versicolor';

$lang['MISSION_330'] = 'Vallis Vinosa';
$lang['MISSION_331'] = 'Mare Viridescens';
$lang['MISSION_332'] = 'Crater Citrodora';
$lang['MISSION_333'] = 'Sinus Foetidissima';
$lang['MISSION_334'] = 'Vallis Gravaeolens';
$lang['MISSION_335'] = 'Crater Odorata';
$lang['MISSION_336'] = 'Mare Suaveolens';
$lang['MISSION_337'] = 'Crater Ursina';

$lang['MISSION_340'] = 'Mare Amabile';
$lang['MISSION_341'] = 'Vallis Praecox ';
$lang['MISSION_342'] = 'Crater Bella';
$lang['MISSION_343'] = 'Mare Amoena';
$lang['MISSION_344'] = 'Sinus Gracilis';
$lang['MISSION_345'] = 'Crater Formosa';
$lang['MISSION_346'] = 'Vallis Fragilis';
$lang['MISSION_347'] = 'Mons Foeniculaceus';

$lang['MISSION_350'] = 'Crater Blanda';
$lang['MISSION_351'] = 'Vallis Elegantissima';
$lang['MISSION_352'] = 'Sinus Imperialis';
$lang['MISSION_353'] = 'Crater Splendens';
$lang['MISSION_354'] = 'Vallis Superba';
$lang['MISSION_355'] = 'Sinus Magnifica';
$lang['MISSION_356'] = 'Crater Campestris';
$lang['MISSION_357'] = 'Mare Collina';

$lang['MISSION_360'] = 'Sinus Insignis';
$lang['MISSION_361'] = 'Crater Peregrina';
$lang['MISSION_362'] = 'Sinus Mutabilis';
$lang['MISSION_363'] = 'Vallis Spectabilis';
$lang['MISSION_364'] = 'Mons Thermalis';
$lang['MISSION_365'] = 'Mare Gracilis';
$lang['MISSION_366'] = 'Vallis Sinensis';
$lang['MISSION_367'] = 'Crater Pratensis';

$lang['MISSION_370'] = 'Vallis Mirabilis';
$lang['MISSION_371'] = 'Crater Umbrosa ';
$lang['MISSION_372'] = 'Mare Paradoxas';
$lang['MISSION_373'] = 'Sinus Pulchella';
$lang['MISSION_374'] = 'Crater Floribunda';
$lang['MISSION_375'] = 'Vallis Microphylla';
$lang['MISSION_376'] = 'Mare Parviflora';
$lang['MISSION_377'] = 'Crater Venusta';

$lang['MISSION_380'] = 'Crater Monstrosus';
$lang['MISSION_381'] = 'Vallis Septentrionalis';
$lang['MISSION_382'] = 'Mons Occidentalis';
$lang['MISSION_383'] = 'Crater Pulcherrima';
$lang['MISSION_384'] = 'Mare Spectabilis';
$lang['MISSION_385'] = 'Vallis Regia';
$lang['MISSION_386'] = 'Sinus Macrantha';
$lang['MISSION_387'] = 'Crater Caespitosa';

/*
** ------------------
** MISSION PAGE
** ------------------
*/

$lang['MISSION_TITLE'] = 'MISSIONS';
$lang['MISSION_NOTE'] = 'Tipp: Spiele Missionen um Erfahrungspunkte und Geld zu erhalten. Bei Abschluß einer Mission mit 100% bekommst du doppelt soviel Geld. Wenn du alles zu 100% erobert hast gehört dir der Kontinent %s und dein stündliches Einkommen wird um %s Dollar gesteigert.';

$lang['MISSION_ALLIANCE_SIZE'] = 'Verbündete';
$lang['MISSION_GAIN'] = 'Verdien';
$lang['MISSION_PART'] = 'Part';
$lang['MISSION_REQUIRED'] = 'Benötigt';
$lang['MISSION_UNLOCK'] = 'Freigeschaltet ab dem Level %s';
$lang['MISSION_CHANCE_LOOT'] = 'Chance Gegenstand zu erhalten';

$lang['MISSION_YOU_USED'] = 'Du benutztest';
$lang['MISSION_YOU_GAIN'] = 'Du verdientest';
$lang['MISSION_DOLLAR_AND'] = ' Dollar und ';
$lang['MISSION_ABORTED'] = 'Mission abgebrochen!';
$lang['MISSION_NO_ENERGY'] = 'Du hast nicht ausreichend Energie um die Mission abzuschließen. Warte einige Minuten damit sich deine Energie sich wieder füllt.';
$lang['MISSION_LOW_ALLIANCE'] = 'Deine Bündnis Größe ist nicht ausreichend um diese Mission zu beginnen.';
$lang['MISSION_MISSING_UNITS'] = 'Du besitzt nicht die nötige Anzahl an Einheiten um diese Mission zu schaffen. Fehlende Einheit(en): ';
$lang['MISSION_MISSING_UNITS_PRICE'] = 'Gesamtsumme um die EInheit(en) zu kaufen liegt bei %s Dollar. Die stündlichen Kosten betragen %s Dollars.';
$lang['MISSION_UNITS_LOST'] = 'Während der Mission sind folgende Einheit(en) gefallen';
$lang['MISSION_LOOT_WON'] = 'Du hast folgenden Einheit gewonnen';
$lang['MISSION_UNLOCKED'] = 'Nun setze dein Kampf-Training weiter fort.';

$lang['MISSION_CONTINTENT_READY1'] = 'Brilliant! Du hast erfolgreich den Teil %s von %s in dem Kontinent %s! ';
$lang['MISSION_CONTINTENT_READY2'] = 'Du erhälst %s Extra Skillpunkte. ';
$lang['MISSION_CONTINTENT_READY3'] = 'Du hast alle Teile absolviert und erfolgreich erobert. Bereite dich auf den nächsten Kontinent vor!';
$lang['MISSION_CONTINTENT_READY4'] = 'Mache weiter mit dem Teil %s auf dem Kontinent!';
$lang['MISSION_COMPLETE_TEXT'] = 'Du hast folgende Kontinente bis jetzt erobert!';

$lang['MISSION_REBEL'] = 'Rebellion';

/*
** ------------------
** BATTLE PAGE
** ------------------
*/

$lang['BATTLE_TITLE'] = 'Kampf';
$lang['BATTLE_GENERAL_TITLE'] = 'Kampf';
$lang['BATTLE_BOUNTY_TITLE'] = 'Kopfgeld';

$lang['BATTLE_LOST'] =  'Your %s attacked %s. You lost the Battle, taking %s damage, while dealing %s to %s.';
$lang['BATTLE_WON'] = 'Your %s attacked %s. You won the battle, taking %s damage while dealing %s to %s. You took %s dollar and gain %s experience point.';
$lang['BATTLE_DEFENDER_HEALTH_LOW'] = '%s ist vorrübergehend außer Gefecht gesetzt weil seine Lebenspunkte zu niedrig sind für einen weiteren Kampf!';
$lang['BATTLE_ATTACKER_HEALTH_LOW'] = 'Deine Gesundheit ist zu niedrig für den Kampf!. Besuche ein Krankenhaus um deine Reserven wieder aufzufüllen oder warte einen Augenblick.';
$lang['BATTLE_AMMO_LOW'] = 'You are out of ammo! Wait a few minutes for your ammo to recharge or deploy skill points to improve ammo skill.';
$lang['BATTLE_UNITS_LOST'] = 'Während des Kampfes ist/sind folgende Einheit/en gefallen:';
$lang['BATTLE_BUILDINGS_LOST'] = 'Während des Kampfes wurde folgende(s) Gebäude zerstört:';
$lang['BATTLE_DEFENSE_FORCE'] = '%s defense %s (%s Verteidigungswert):'; 
$lang['BATTLE_DEFENSE_BASE'] = '%s defense base:'; 
$lang['BATTLE_ATTACK_FORCE'] = 'Your attack %s (%s attack strenght)';
$lang['BATTLE_MORE'] = 'more';
$lang['BATTLE_NO_PLAYER_AVAILABLE'] = 'On this moment no player(s) are available to fight.';
$lang['BATTLE_UNLOCKED'] = 'Battle is unlocked at level 1.<br/>First complete the training mission.';
$lang['BATTLE_BOUNTY_UNLOCKED'] = 'Bounty hunting is unlocked at level %s.';
$lang['BATTLE_ALLY_NO_ATTACK'] = '<b>%s</b> is an ally. You cannot attack allies.';
$lang['BATTLE_SURRENDER'] = 'Temporary Surrender';

$lang['BATTLE_NOTE1'] = 'Tipp: Kämpfe gegen andere Spieler, um Erfahrungspunkte und Geld zu verdienen. Du kannst nur gegen Spieler aus anderen Ländern kämpfen.';
$lang['BATTLE_NOTE2'] = 'Tipp: Jage andere Spieler um ein Kopfgeld zu kassieren und um Erfahrungspunkte zu sammeln für einen Stufenaufstieg. Du kannst nur gegen Spieler aus anderen Ländern kämpfen.';

$lang['BATTLE_FORCE_TYPE'] = 'Einheiten:';
$lang['BATTLE_ENEMIES'] = 'Feinde';
$lang['BATTLE_BOUNTY'] = 'Kopfgeld';
$lang['BATTLE_NO_BOUNTY_PLAYERS'] = 'Im Moment ist kein Kopfgeld auf einen Spieler ausgesetzt worden.';
$lang['BATTLE_BOUNTY_BONUS'] = 'Extra: Kopfgeld-Bonus von %s Dollar erhalten.'; 
$lang['BATTLE_HOSPITAL_BONUS'] = '%s ist vorübergehend ausser Gefecht. Du erhälst einen Bonus von %s Dollar!'; 
$lang['BATTLE_BOUNTY_LOST'] = 'You were attacked by the %s of %s.You LOST. Losing %s dollar, taking %s damage and losing %s experience points.';
$lang['BATTLE_BOUNTY_CONFIRM'] = 'Möchtest du eine Belohnung in Höhe von %s Dollar setzen?';

$lang['BATTLE_CEASE_FIRE_PERIOD'] = 'Waffenruhe ist aktiv! %s';
$lang['BATTLE_AND'] = 'und';
$lang['BATTLE_REBEL_UPDATE1'] = 'Well done, you initialed rebellion for %s in the %s region(s). Below you see his current situation.';
$lang['BATTLE_REBEL_UPDATE2'] = 'Well done, you increased their rebellion chance for %s to %s%.';
$lang['BATTLE_REBEL_UPDATE3'] = 'Pech gehabt, Es gibt keine Region um eine Rebellion auszulösen!';

$lang['BATTLE_NO_BOUNTY_MONEY'] = 'You do not own %s dollar to set a bounty on %s head.';
$lang['BATTLE_BOUNTY_SET'] = 'You set %s dollar on %s head. When %s is defeated he will lose %s expercience points.'; 

$lang['BATTLE_MOON_UNLOCKED'] = 'Moon battles are unlocked at level 100.';
$lang['BATTLE_MARS_UNLOCKED'] = 'Mars battles are unlocked at level 150.';
$lang['BATTLE_ASTERIOD_UNLOCKED'] = 'Asteriod battles are unlocked at level 200.';

/*
** ------------------
** UNIT DATA
** ------------------
*/

/* Earth */
$lang['UNIT_GROUP_0']  = 'Armee';
$lang['UNIT_GROUP_2']  = 'Kavalarie';
$lang['UNIT_GROUP_3']  = 'Marine';
$lang['UNIT_GROUP_4']  = 'Luftwaffe';
$lang['UNIT_GROUP_5']  = 'Zivilisten';
$lang['UNIT_GROUP_6']  = 'Nachrichtendienst';

/* Moon */
$lang['UNIT_GROUP_7']  = 'Warriors';
$lang['UNIT_GROUP_8']  = 'Drohnen';
$lang['UNIT_GROUP_9']  = 'Spacecrafts';
$lang['UNIT_GROUP_10'] = 'Zivilisten';
$lang['UNIT_GROUP_11'] = 'Armee';
$lang['UNIT_GROUP_12'] = 'Kundschafter';

/* Mars */
$lang['UNIT_GROUP_13']  = 'Drohnen';
$lang['UNIT_GROUP_14']  = 'Warriors';
$lang['UNIT_GROUP_15']  = 'Spacecrafts';
$lang['UNIT_GROUP_16']  = 'Explorers';
$lang['UNIT_GROUP_17'] 	= 'Zivilisten';
$lang['UNIT_GROUP_18'] 	= 'Armee';

/* Asteroid */
$lang['UNIT_GROUP_19']  = 'Drones';
$lang['UNIT_GROUP_20']  = 'Warriors';
$lang['UNIT_GROUP_21']  = 'Spacecrafts';
$lang['UNIT_GROUP_22']  = 'Explorers';
$lang['UNIT_GROUP_23'] 	= 'Citizens';
$lang['UNIT_GROUP_24'] 	= 'Army';


/* Calvary (Earth) - Group 2 */
$lang['UNIT_1'] = 'Schützen';
$lang['UNIT_2'] = 'Rekruten';
$lang['UNIT_3'] = 'Marine Soldaten';
$lang['UNIT_4'] = 'Fallschirmjäger';
$lang['UNIT_5'] = 'Sanitäter';
$lang['UNIT_6'] = 'Grenadiere';
$lang['UNIT_7'] = 'Militär Polizei';
$lang['UNIT_8'] = 'Navy Seal';
$lang['UNIT_9'] = 'Machine Gunner';
$lang['UNIT_10'] = 'Raktenwerfer';
$lang['UNIT_11'] = 'Kommandant';
$lang['UNIT_12'] = 'Sonder Kommando';
$lang['UNIT_13'] = 'Aerial Vehicle Squad';
$lang['UNIT_14'] = 'XM-25 Gunner';
$lang['UNIT_15'] = 'Panzerfaust';
$lang['UNIT_16'] = 'Navy Seal';
$lang['UNIT_17'] = 'FELIN Combat Infantry';
$lang['UNIT_18'] = 'Heavy Assault Squad';
$lang['UNIT_19'] = 'Force Warrior Squad';
$lang['UNIT_20'] = 'Machine Gun Squad';
$lang['UNIT_21'] = 'Scharfschützen Team';
$lang['UNIT_22'] = 'Grenade Squad';
$lang['UNIT_23'] = 'Rail Gun Troopers';
$lang['UNIT_24'] = 'Mobile Marines';
$lang['UNIT_101'] = 'Military Car';
$lang['UNIT_102'] = 'Hum-Vee';
$lang['UNIT_103'] = 'Truck';
$lang['UNIT_104'] = 'Light Artillery';
$lang['UNIT_105'] = 'Personnel Carrier';
$lang['UNIT_106'] = 'MGM-51 Shillelagh';
$lang['UNIT_107'] = 'Personal Transporter';
$lang['UNIT_108'] = 'Assault Vehicle';
$lang['UNIT_109'] = 'SSM Launcher';
$lang['UNIT_110'] = 'Light Hovercraft';
$lang['UNIT_111'] = 'M1 Abrams Tank';
$lang['UNIT_112'] = 'Armored Vehicle';
$lang['UNIT_113'] = 'Ambush Protected Vehicle';
$lang['UNIT_114'] = 'Heavy Tank';
$lang['UNIT_115'] = 'Leopard 1A1';
$lang['UNIT_116'] = 'HG-544 Vehicle';
$lang['UNIT_117'] = 'Tracked Carrier';
$lang['UNIT_118'] = 'Combat Vehicle';
$lang['UNIT_119'] = 'Hellfire Tank';
$lang['UNIT_120'] = 'Battle Tank';
$lang['UNIT_121'] = 'Mounted Combat System';
$lang['UNIT_122'] = 'Self Propelled Artillery';
$lang['UNIT_123'] = 'Chaparral Tank';
$lang['UNIT_124'] = 'M198 Howitzer';
$lang['UNIT_125'] = 'Heavy Artillery';
$lang['UNIT_126'] = 'Missile Launcher';
$lang['UNIT_127'] = 'Mobile Anti Aircraft';

/* Navy (Earth) - Group 3 */
$lang['UNIT_201'] = 'Rubber inflating boat';
$lang['UNIT_202'] = 'Transport';
$lang['UNIT_203'] = 'Frigate';
$lang['UNIT_204'] = 'Naval Tanker';
$lang['UNIT_205'] = 'Naval Destroyer';
$lang['UNIT_206'] = 'M80 Stiletto';
$lang['UNIT_207'] = 'Submarine';
$lang['UNIT_208'] = 'Helicopter Carrier';
$lang['UNIT_209'] = 'Battleship';
$lang['UNIT_210'] = 'Houbei Missile ship';
$lang['UNIT_211'] = 'Horizon Frigate';
$lang['UNIT_212'] = 'Type 13 Frigate';
$lang['UNIT_213'] = 'Destroyer';
$lang['UNIT_214'] = 'Scorpene Submarine';
$lang['UNIT_215'] = 'DDG 1000 Destroyer';
$lang['UNIT_216'] = 'Elite Dreadnought';
$lang['UNIT_217'] = 'SPY-1D Destroyer';
$lang['UNIT_218'] = 'Sea Fighter';
$lang['UNIT_219'] = 'HSV-2 Swift';
$lang['UNIT_220'] = 'Missile Cruiser';
$lang['UNIT_221'] = 'UXV Combatant';
$lang['UNIT_222'] = 'Anti Submarine Ship';
$lang['UNIT_223'] = 'Kanimbla AT ship';
$lang['UNIT_224'] = 'Aircraft Carrier';
$lang['UNIT_225'] = 'Landing Platform Dock';
$lang['UNIT_226'] = 'Type 23 Frigate';
$lang['UNIT_227'] = 'Ohio Submarine';
$lang['UNIT_228'] = 'Nuclear Cruiser';

/* Airforce (Earth) - Group 4 */
$lang['UNIT_301'] = 'Cessna 172';
$lang['UNIT_302'] = 'C-17 Cargo plane';
$lang['UNIT_303'] = 'V-22A Osprey Gunship';
$lang['UNIT_304'] = 'AV-8B Harrier Jet';
$lang['UNIT_305'] = 'Comanche Helicopter';
$lang['UNIT_306'] = 'Havoc Helicopter';
$lang['UNIT_307'] = 'Saab JA37 Viggen';
$lang['UNIT_308'] = 'SR-71 Blackbird';
$lang['UNIT_309'] = 'Apache Helicopter';
$lang['UNIT_310'] = 'B-2 Spirit Bomber';
$lang['UNIT_311'] = 'F-18 Super Hornet';
$lang['UNIT_313'] = 'F-15 Silent Eagle';
$lang['UNIT_314'] = 'B-1 Lancer';
$lang['UNIT_316'] = 'F3 Interceptor';
$lang['UNIT_318'] = 'F-16 Falcon';
$lang['UNIT_319'] = 'PAK-FA Fighter';
$lang['UNIT_320'] = 'F-117 Nighthawk';
$lang['UNIT_321'] = 'Boeing NGB Bomber';
$lang['UNIT_322'] = 'F-14 Tomcat';
$lang['UNIT_323'] = 'F-35 Lightning II';
$lang['UNIT_324'] = 'B-52 Stratofortress';
$lang['UNIT_325'] = 'F-22 Raptor';
$lang['UNIT_326'] = 'Trident II Missile';

/* Citizens (Earth) - Group 5 */
$lang['UNIT_401'] = 'Construction Engineer';
$lang['UNIT_402'] = 'Mechanic Engineer';
$lang['UNIT_403'] = 'Lab Engineer';
$lang['UNIT_404'] = 'Manager';
$lang['UNIT_405'] = 'Doctor';
$lang['UNIT_406'] = 'Cook';
$lang['UNIT_407'] = 'Security Guard';

/* Espionage (Earth) - Group 6 */
$lang['UNIT_501'] = 'Surveillance Camera';
$lang['UNIT_502'] = 'Marine Intelligence';
$lang['UNIT_503'] = 'Mini Air Drone';
$lang['UNIT_504'] = 'G343 Spy Robot';
$lang['UNIT_505'] = 'Intelligence A3 Crusader';
$lang['UNIT_506'] = 'Spy Fishing Ship';
$lang['UNIT_507'] = 'Hawk Eye';
$lang['UNIT_508'] = 'UK-80 AWACS';
$lang['UNIT_509'] = 'AS-102 Stealth Ship';
$lang['UNIT_510'] = 'US-101 Predator';
$lang['UNIT_511'] = 'Heron Drone';
$lang['UNIT_512'] = 'HG101 Satellite';


/* Warriors (Moon) - Group 7 */
$lang['UNIT_700'] = 'Ahiga I';
$lang['UNIT_701'] = 'Aindrias II';
$lang['UNIT_702'] = 'Aloisius III';
$lang['UNIT_703'] = 'Aloysius IV';
$lang['UNIT_704'] = 'Alvar V';
$lang['UNIT_705'] = 'Aindrias VI';
$lang['UNIT_706'] = 'Cadomedo VII';
$lang['UNIT_707'] = 'Catigernus VIII';
$lang['UNIT_708'] = 'Catutigernos IX';
$lang['UNIT_709'] = 'Cedric X';
$lang['UNIT_710'] = 'Cheveyo XI';

/* Drones (Moon) - Group 8 */
$lang['UNIT_800'] = 'Basic Rover I';
$lang['UNIT_801'] = 'Lunar Transporter II';
$lang['UNIT_802'] = 'Moon Explorer III';
$lang['UNIT_803'] = 'Moon Havostar IV';
$lang['UNIT_804'] = 'Mobile Lab V';
$lang['UNIT_805'] = 'Transporter VI';
$lang['UNIT_805'] = 'Space Crane VII';
$lang['UNIT_806'] = 'Moon Buggy VIII';
$lang['UNIT_807'] = 'Fuel Transporter IX';
$lang['UNIT_808'] = 'Fuel Explorer X';
$lang['UNIT_809'] = 'Moon Explorer XI';
$lang['UNIT_810'] = 'Transporter XII';

/* Spacecrafts (Moon) - Group 9 */
$lang['UNIT_900'] = 'Moon Cruiser';
$lang['UNIT_901'] = 'Millennium Falcon';
$lang['UNIT_902'] = 'Ebon Hawk';
$lang['UNIT_903'] = 'Transport Robot';
$lang['UNIT_904'] = 'Slave I';
$lang['UNIT_905'] = 'Assault ship';
$lang['UNIT_906'] = 'Corellian corvette';
$lang['UNIT_907'] = 'War Hawk Shadow';
$lang['UNIT_908'] = 'Solar Spacecraft';
$lang['UNIT_909'] = 'Royal starship';
$lang['UNIT_910'] = 'Theta-Class Shuttle';
$lang['UNIT_911'] = 'Trade Cruiser';
$lang['UNIT_912'] = 'Sith Infiltrator';
$lang['UNIT_913'] = 'Imperial landing craft';
$lang['UNIT_914'] = 'Star Skiff II';
$lang['UNIT_915'] = 'Star Destroyer';
$lang['UNIT_916'] = 'Flag Ship';

/* Citizens (Moon) - Group 10 */
$lang['UNIT_1000'] = 'Astronaut';
$lang['UNIT_1001'] = 'Female';
$lang['UNIT_1002'] = 'Male';

/* Explorers (Moon) - Group 12 */
$lang['UNIT_1200'] = 'Explorer Satellite';
$lang['UNIT_1201'] = 'Explorer Ship';
$lang['UNIT_1202'] = 'Short Range Radar';
$lang['UNIT_1203'] = 'Deepspace Explorer';
$lang['UNIT_1204'] = 'Planet Explorer';
$lang['UNIT_1205'] = 'Space Elevator';
$lang['UNIT_1206'] = 'Astronaut Explorer';
$lang['UNIT_1207'] = 'Long Range Rader';
$lang['UNIT_1208'] = 'Deepspace Relay Station';
$lang['UNIT_1209'] = 'Lightspeed Explorer';
$lang['UNIT_1210'] = 'Planet Destroyer';
$lang['UNIT_1211'] = 'Galaxy Explorer';


/* Drones (Mars) - Group 13 */
$lang['UNIT_1300'] = 'Loyce I';
$lang['UNIT_1301'] = 'Labhaoise II';
$lang['UNIT_1302'] = 'Kondo III';
$lang['UNIT_1303'] = 'Kiaskari VI';
$lang['UNIT_1304'] = 'Khalon V';
$lang['UNIT_1305'] = 'Hida VI';
$lang['UNIT_1306'] = 'Irapeke VII';
$lang['UNIT_1307'] = 'Heriberto VIII';
$lang['UNIT_1308'] = 'Kerbasi IX';
$lang['UNIT_1309'] = 'Karna X';

/* Warriors (Mars) - Group 14 */
$lang['UNIT_1400'] = 'Gervaso I';
$lang['UNIT_1401'] = 'Galtero II';
$lang['UNIT_1402'] = 'Gunther III';
$lang['UNIT_1403'] = 'Donnachadh VI';
$lang['UNIT_1404'] = 'Duncan V';
$lang['UNIT_1405'] = 'Eskiminzin VI';
$lang['UNIT_1406'] = 'Fenyang VII';
$lang['UNIT_1407'] = 'Finnegan VIII';
$lang['UNIT_1408'] = 'Clodovea IX';
$lang['UNIT_1409'] = 'Eferhilda X';

/* Spacecrafts (Mars) - Group 15 */
$lang['UNIT_1500'] = 'Mars Cruiser I';
$lang['UNIT_1501'] = 'Cocon II';
$lang['UNIT_1502'] = 'Hawk Eye III';
$lang['UNIT_1503'] = 'Ariane IV';
$lang['UNIT_1504'] = 'Gyro V';
$lang['UNIT_1505'] = 'Miner VI';
$lang['UNIT_1506'] = 'Jannus VII';
$lang['UNIT_1507'] = 'Tango VIII';
$lang['UNIT_1508'] = 'Rader IX';
$lang['UNIT_1509'] = 'Eloy  X';

/* Explorers (Mars) - Group 16 */
$lang['UNIT_1600'] = 'Cadabyr I';
$lang['UNIT_1601'] = 'Chadwick II';
$lang['UNIT_1602'] = 'Calhoun III';
$lang['UNIT_1603'] = 'Cheveyo IV';
$lang['UNIT_1604'] = 'Clancy V';
$lang['UNIT_1605'] = 'Clodovea VI';
$lang['UNIT_1606'] = 'Cochise VII';
$lang['UNIT_1607'] = 'Czarine VIII';
$lang['UNIT_1608'] = 'Caddawyc IX';
$lang['UNIT_1609'] = 'Chlodwig X';

/* Citizens (Mars) - Group 17 */
$lang['UNIT_1700'] = 'Astronaut';
$lang['UNIT_1701'] = 'Female';
$lang['UNIT_1702'] = 'Male';

/* Explorers (Mars) - Group 16 */
$lang['UNIT_1600'] = 'Explorer M0';
$lang['UNIT_1601'] = 'Explorer M1';
$lang['UNIT_1602'] = 'Explorer M2';
$lang['UNIT_1603'] = 'Explorer M3';
$lang['UNIT_1604'] = 'Explorer M4';
$lang['UNIT_1605'] = 'Explorer M5';
$lang['UNIT_1606'] = 'Explorer M6';
$lang['UNIT_1607'] = 'Explorer M7';
$lang['UNIT_1608'] = 'Explorer M8';
$lang['UNIT_1609'] = 'Explorer M9';

/* Citizens (Mars) - Group 17 */
$lang['UNIT_1700'] = 'Astronaut';
$lang['UNIT_1701'] = 'Female Citizen';
$lang['UNIT_1702'] = 'Male Citizen';

/* Warriors (Asteroid) - Group 19 */
$lang['UNIT_1900'] = 'Swify I';
$lang['UNIT_1901'] = 'Euhm II';
$lang['UNIT_1902'] = 'Mirageman III';
$lang['UNIT_1903'] = 'Vereldor IV';
$lang['UNIT_1904'] = 'Maelsius V';
$lang['UNIT_1905'] = 'Suldan VI';
$lang['UNIT_1906'] = 'Jonesy VII';
$lang['UNIT_1907'] = 'Pendejo VIII';
$lang['UNIT_1908'] = 'Vorpal IX';
$lang['UNIT_1909'] = 'Iyona X';

/* Warriors (Asteroid) - Group 20 */
$lang['UNIT_2000'] = 'Grandmaster I';
$lang['UNIT_2001'] = 'Courage II';
$lang['UNIT_2002'] = 'Hero III';
$lang['UNIT_2003'] = 'Pious IV';
$lang['UNIT_2004'] = 'Stalwart V';
$lang['UNIT_2005'] = 'Bombadil VI';
$lang['UNIT_2006'] = 'Happyelf VII';
$lang['UNIT_2007'] = 'Rainbow VIII';
$lang['UNIT_2008'] = 'MerryLad IX';
$lang['UNIT_2009'] = 'Drenar X';

/* Spacecrafts (Asteroid) - Group 21 */
$lang['UNIT_2100'] = 'Halvilion I';
$lang['UNIT_2101'] = 'Menelaus II';
$lang['UNIT_2102'] = 'Ultimatum III';
$lang['UNIT_2103'] = 'Erudur IV';
$lang['UNIT_2104'] = 'Banbelion V';
$lang['UNIT_2105'] = 'Nimtharadon VI';
$lang['UNIT_2106'] = 'Voronthil VII';
$lang['UNIT_2107'] = 'Anion VIII';
$lang['UNIT_2108'] = 'Partharaon IX';
$lang['UNIT_2109'] = 'Erudil X';

/* Explorers (Asteroid) - Group 22 */
$lang['UNIT_2200'] = 'Girlyman I';
$lang['UNIT_2201'] = 'Wuss II';
$lang['UNIT_2202'] = 'Sissy III';
$lang['UNIT_2203'] = 'Tauren IV';
$lang['UNIT_2204'] = 'Hykon V';
$lang['UNIT_2205'] = 'Talenx VI';
$lang['UNIT_2206'] = 'DDazra VII';
$lang['UNIT_2207'] = 'Hexa VIII';
$lang['UNIT_2208'] = 'Marest IX';
$lang['UNIT_2209'] = 'Rawrgrable X';

/* Citizens (Asteroid) - Group 23 */
$lang['UNIT_2300'] = 'Astronaut';
$lang['UNIT_2301'] = 'Female';
$lang['UNIT_2302'] = 'Male';

/*
** ------------------
** UNIT PAGE
** ------------------
*/

$lang['UNIT_TITLE'] = 'UNITS';

$lang['UNIT_NOTE_1'] = 'Note: Buy soldier units to enable missions.';
$lang['UNIT_NOTE_2'] = 'Note: Buy Calvary units to improve your calvary strength. Battle, win and steal money from your opponent\'s cash account.';
$lang['UNIT_NOTE_3'] = 'Note: Buy Navy units to improve your naval strength. Battle, win and steal money from your opponent\'s cash account.';
$lang['UNIT_NOTE_4'] = 'Note: Buy Airfoce units to improve your airforce strength. Battle, win and steal money from your opponent\'s cash account.';
$lang['UNIT_NOTE_6'] = 'Note: Buy Intel units to improve  your intel strength. Batlle, win to start rebellions on Earth regions and steal money from your opponent\'s Trasquera or SwissCore bank account.';

$lang['UNIT_NOTE_8'] = 'Note: Buy Moon Drone units to improve your drone strength. Battle, win and steal money from your opponent\'s cash account.';
$lang['UNIT_NOTE_7'] = 'Note: Buy Moon Warrior units to improve your warrior strength. Battle, win and steal money from your opponent\'s cash account.';
$lang['UNIT_NOTE_9'] = 'Note: Buy Moon Spacecraft units to improve your spacecraft strength. Battle, win and steal money from your opponent\'s cash account.';
$lang['UNIT_NOTE_12'] = 'Note: Buy Moon Explore units to improve your explorer strength. Batlle, win to start rebellions on the Moon and steal money from your opponent\'s Trasquera or SwissCore bank account.';

$lang['UNIT_NOTE_13'] = 'Note: Buy Mars Drone units to improve your drone strength. Battle, win and steal money from your opponent\'s cash account.';
$lang['UNIT_NOTE_14'] = 'Note: Buy Mars Warrior units to improve your warrior strenght. Battle, win and steal money from your opponent\'s cash account.';
$lang['UNIT_NOTE_15'] = 'Note: Buy Mars Spacecraft units to improve your spacecraft strength. Battle, win and steal money from your opponent\'s cash account.';
$lang['UNIT_NOTE_16'] = 'Note: Buy Mars Explore units to improve your explorers strength. Batlle, win to start rebellions on Mars and steal some money from your opponent\'s Trasquera or SwissCore bank account.';

$lang['UNIT_NOTE_19'] = 'Note: Buy asteroid drone units to improve your drone strength. Battle, win and steal money from your opponent\'s cash account.';
$lang['UNIT_NOTE_20'] = 'Note: Buy asteroid warrior units to improve your warrior strenght. Battle, win and steal money from your opponent\'s cash account.';
$lang['UNIT_NOTE_21'] = 'Note: Buy asteroid spacecraft units to improve your spacecraft strength. Battle, win and steal money from your opponent\'s cash account.';
$lang['UNIT_NOTE_22'] = 'Note: Buy asteroid explore units to improve your explorers strength. Batlle, win to start rebellions on Mars and steal some money from your opponent\'s Trasquera or SwissCore bank account.';


$lang['UNIT_DISBAND'] = 'You disband %s %s for %s dollar. Still %s deployed.';
$lang['UNIT_DISBAND_FAILED'] = 'You do not own %s %s. Still %s deployed.';

$lang['UNIT_DEPLOY'] = 'You deploy %s %s for %s dollar. Now %s deployed.';
$lang['UNIT_NO_UPKEEP'] = 'Not enough hourly income to fund %s %s.';
$lang['UNIT_NO_MONEY'] = 'Not enough money to buy %s %s for %s dollar.';
$lang['UNIT_MAX'] = 'No more then %s %s(s) allowed!';;

/*
** ------------------
** BUILDING DATA
** ------------------
*/

/* Earth Buildings */
$lang['BUILDING_GROUP_1'] = 'Einkommen';
$lang['BUILDING_GROUP_2'] = 'Verteidigung';
$lang['BUILDING_GROUP_3'] = 'Energie';
$lang['BUILDING_GROUP_4'] = 'Discount';
$lang['BUILDING_GROUP_5'] = 'Maintenance';

/* Moon Buildings */
$lang['BUILDING_GROUP_6'] = 'Einkommen';
$lang['BUILDING_GROUP_7'] = 'Verteidigung';
$lang['BUILDING_GROUP_8'] = 'Energie';
$lang['BUILDING_GROUP_9'] = 'Discount';
$lang['BUILDING_GROUP_10'] = 'Maintenance';

/* Mars Buildings */
$lang['BUILDING_GROUP_11'] = 'Einkommen';
$lang['BUILDING_GROUP_12'] = 'Verteidigung';
$lang['BUILDING_GROUP_13'] = 'Energie';
$lang['BUILDING_GROUP_14'] = 'Discount';
$lang['BUILDING_GROUP_15'] = 'Maintenance';

/* Asteroid Buildings */
$lang['BUILDING_GROUP_16'] = 'Income';
$lang['BUILDING_GROUP_17'] = 'Defence';
$lang['BUILDING_GROUP_18'] = 'Energy';
$lang['BUILDING_GROUP_19'] = 'Discount';
$lang['BUILDING_GROUP_20'] = 'Maintenance';


/* Income (Earth) - Group 1 */
$lang['BUILDING_1']  = 'Supply Depot';
$lang['BUILDING_3']  = 'Raffinerie';
$lang['BUILDING_6']  = 'Waffenfabrik';
$lang['BUILDING_8']  = 'Kommunkationszentrum';
$lang['BUILDING_24'] = 'Bio-Forschungs-Labor';
$lang['BUILDING_12'] = 'Ölbohrinsel';
$lang['BUILDING_14'] = 'Militär Forschungs-Institut';
$lang['BUILDING_16'] = 'Nuclear Testing Facility';
$lang['BUILDING_25'] = 'Water Treatment Facility';
$lang['BUILDING_17'] = 'Solar Satellite Network';

/* Defense (Earth) - Group 2 */
$lang['BUILDING_2']  = 'Bunker';
$lang['BUILDING_21'] = 'See Mine';
$lang['BUILDING_5']  = 'Wachturm';
$lang['BUILDING_51'] = 'Embassy';
$lang['BUILDING_7']  = 'Kurzstrecken Rakeketenstellung';
$lang['BUILDING_22'] = 'Torpedo Werfer';
$lang['BUILDING_9']  = 'Langstrecken Raketenstellung';
$lang['BUILDING_11'] = 'Minenfeld';
$lang['BUILDING_52'] = 'Spy Command Centre';
$lang['BUILDING_20'] = 'Airfield';
$lang['BUILDING_23'] = 'U-Boot Werft';
$lang['BUILDING_15'] = 'Magnetfeld Kanone';
$lang['BUILDING_53'] = 'Dron Control Centre';
$lang['BUILDING_54'] = 'Cyberspace Warfare';

/* Energy (Earth) - Group 3 */
$lang['BUILDING_4']  = 'Solar Power Unit';
$lang['BUILDING_10'] = 'Mobile Generator';
$lang['BUILDING_13'] = 'Coal Power Plant';
$lang['BUILDING_18'] = 'Wind Farm';
$lang['BUILDING_19'] = 'Oil Well';
$lang['BUILDING_26'] = 'Solar Power Plant';
$lang['BUILDING_27'] = 'Offshore Wind Farm';
$lang['BUILDING_28'] = 'Geothermal Energy Plant';
$lang['BUILDING_35'] = 'Hydro Power Plant';
$lang['BUILDING_39'] = 'Nuclear Power Plant';

/* Discount (Earth) - Group 4 */
$lang['BUILDING_29'] = 'Army Field Mess';
$lang['BUILDING_40'] = 'Military Shopping Mall';
$lang['BUILDING_37'] = 'Mobile Hospital';
$lang['BUILDING_38'] = 'Command Centre';
$lang['BUILDING_30'] = 'Military Training camp';
$lang['BUILDING_31'] = 'Military Academy';
$lang['BUILDING_32'] = 'Recreation Facility';
$lang['BUILDING_33'] = 'Military Statue';
$lang['BUILDING_34'] = 'Military Headquarters';
$lang['BUILDING_36'] = 'President Office';

/* Maintenance (Earth) - Group 5 */
$lang['BUILDING_41'] = 'Road Maintenance';
$lang['BUILDING_42'] = 'Bridge Maintenance';
$lang['BUILDING_43'] = 'Transport Garage';
$lang['BUILDING_44'] = 'Helikopter Hangar';
$lang['BUILDING_45'] = 'Vehicle Garage';
$lang['BUILDING_46'] = 'Navy Ship Dock';
$lang['BUILDING_47'] = 'Building Maintenance';
$lang['BUILDING_48'] = 'Submarine Dock';
$lang['BUILDING_49'] = 'Power Plant Maintenance';
$lang['BUILDING_50'] = 'Flugzeug Hangar';

/* Income (Moon) - Group 6 */
$lang['BUILDING_600'] = 'General base';
$lang['BUILDING_601'] = 'Explore & Research center';
$lang['BUILDING_602'] = 'Personel quarters';
$lang['BUILDING_603'] = 'Oxygen factory';
$lang['BUILDING_604'] = 'Water factory';
$lang['BUILDING_605'] = 'Communication center';
$lang['BUILDING_606'] = 'Greenhouse';
$lang['BUILDING_607'] = 'Construction factory';
$lang['BUILDING_608'] = 'Metal extraction center';
$lang['BUILDING_609'] = 'Spacecraft launch center';
$lang['BUILDING_610'] = 'Lunar hospital';
$lang['BUILDING_611'] = 'Terraforming centre';

/* Defence (Moon) - Group 7 */
$lang['BUILDING_700'] = 'Defence research center';
$lang['BUILDING_701'] = 'Drone factory';
$lang['BUILDING_702'] = 'Short range missile';
$lang['BUILDING_703'] = 'Warrior factory';
$lang['BUILDING_704'] = 'Allarm system';
$lang['BUILDING_705'] = 'Long range laser';
$lang['BUILDING_706'] = 'Spacecraft factory';
$lang['BUILDING_707'] = 'Energy shield';
$lang['BUILDING_708'] = 'Nuclear missile launcher';
$lang['BUILDING_709'] = 'Tasers weapon factory';
$lang['BUILDING_710'] = 'Photonic weapon factory';
$lang['BUILDING_711'] = 'Mobile android defender';
$lang['BUILDING_712'] = 'Colony defence shield';
$lang['BUILDING_713'] = 'Underground factory';
$lang['BUILDING_714'] = 'Spacecraft launcher';

/* Energy (Moon) - Group 8 */
$lang['BUILDING_800'] = 'Gas research center';
$lang['BUILDING_801'] = 'Petroleum research center';
$lang['BUILDING_802'] = 'Gas extractors';
$lang['BUILDING_803'] = 'Petroleum extractors';
$lang['BUILDING_804'] = 'Solar power facility';
$lang['BUILDING_805'] = 'Gas power facility';
$lang['BUILDING_806'] = 'Mini orbit solar facility';
$lang['BUILDING_807'] = 'Nuclear power facility';
$lang['BUILDING_808'] = 'Large orbit solar facility';
$lang['BUILDING_809'] = 'Mini space colony';
$lang['BUILDING_810'] = 'Solar grid system';
$lang['BUILDING_811'] = 'Large space colony';

/* Discount (Moon) - Group 9 */
$lang['BUILDING_900'] = 'Skyscraper';
$lang['BUILDING_901'] = 'Bridge';
$lang['BUILDING_902'] = 'Village';
$lang['BUILDING_903'] = 'Headquarters';
$lang['BUILDING_904'] = 'Volcano base';
$lang['BUILDING_905'] = 'City';
$lang['BUILDING_906'] = 'Bootcamp';
$lang['BUILDING_907'] = 'Missile launchers';
$lang['BUILDING_908'] = 'President\'s Office';
$lang['BUILDING_909'] = 'Military academy';
$lang['BUILDING_910'] = 'Recreation facility';
$lang['BUILDING_911'] = 'Command center';

/* Maintenance (Moon) - Group 10 */
$lang['BUILDING_1000'] = 'Architect design center';
$lang['BUILDING_1001'] = 'Drone repair center';
$lang['BUILDING_1002'] = 'Missile repair center';
$lang['BUILDING_1003'] = 'Explore repair center';
$lang['BUILDING_1004'] = 'Vehicle repair center';
$lang['BUILDING_1005'] = 'Warrior repair center';
$lang['BUILDING_1006'] = 'Infra repair center';
$lang['BUILDING_1007'] = 'Unit repair center';
$lang['BUILDING_1008'] = 'Power repair center';
$lang['BUILDING_1009'] = 'Robot repair center';

/* Income (Mars) - Group 11 */
$lang['BUILDING_1100'] = 'General base';
$lang['BUILDING_1101'] = 'Research center';
$lang['BUILDING_1102'] = 'Oxygen factory';
$lang['BUILDING_1103'] = 'Personel quarters';
$lang['BUILDING_1104'] = 'Water factory';
$lang['BUILDING_1105'] = 'Metal extration center';
$lang['BUILDING_1106'] = 'Communication center';
$lang['BUILDING_1107'] = 'Converance center';
$lang['BUILDING_1108'] = 'Greenhouse';
$lang['BUILDING_1109'] = 'Hotel';

/* Defense (Mars) - Group 12 */
$lang['BUILDING_1200'] = 'Research center';
$lang['BUILDING_1201'] = 'Weapon factory';
$lang['BUILDING_1202'] = 'Short range missile';
$lang['BUILDING_1203'] = 'Warrior factory';
$lang['BUILDING_1204'] = 'Allarm system';
$lang['BUILDING_1205'] = 'Spacecraft factory';
$lang['BUILDING_1206'] = 'Long range launcher';
$lang['BUILDING_1207'] = 'Explorer factory';
$lang['BUILDING_1208'] = 'Drone factory';
$lang['BUILDING_1209'] = 'Warrior factory';
$lang['BUILDING_1210'] = 'Alien Detect unit';

/* Energy (Mars) - Group 13 */
$lang['BUILDING_1300'] = 'Energy research center';
$lang['BUILDING_1301'] = 'Gas power facility';
$lang['BUILDING_1302'] = 'Petroleum research center';
$lang['BUILDING_1303'] = 'Petroleum extractors';
$lang['BUILDING_1304'] = 'Solar power facility';
$lang['BUILDING_1305'] = 'Gas extractors';
$lang['BUILDING_1306'] = 'Mining center';
$lang['BUILDING_1307'] = 'Nuclear power facility';
$lang['BUILDING_1308'] = 'Large orbit solar facility';
$lang['BUILDING_1309'] = 'Large mars colony';

/* Discount (Mars) - Group 14 */
$lang['BUILDING_1400'] = 'Training center';
$lang['BUILDING_1401'] = 'Terraforming center';
$lang['BUILDING_1402'] = 'Village';
$lang['BUILDING_1403'] = 'Headquarters';
$lang['BUILDING_1404'] = 'Supply depot';
$lang['BUILDING_1405'] = 'Construction unit';
$lang['BUILDING_1406'] = 'Bootcamp';
$lang['BUILDING_1407'] = 'President\'s office';
$lang['BUILDING_1408'] = 'Command center';

/* Maintenance (Mars) - Group 15 */
$lang['BUILDING_1500'] = 'Architect design center';
$lang['BUILDING_1501'] = 'Drone repair center';
$lang['BUILDING_1502'] = 'Missile repair center';
$lang['BUILDING_1503'] = 'Explore repair center';
$lang['BUILDING_1504'] = 'Vehicle repair center';
$lang['BUILDING_1505'] = 'Warrior repair center';
$lang['BUILDING_1506'] = 'Infra repair center';
$lang['BUILDING_1507'] = 'Unit repair center';
$lang['BUILDING_1508'] = 'Power repair center';
$lang['BUILDING_1509'] = 'Robot repair center';

/* Income (Asteroid) - Group 16 */
$lang['BUILDING_1600'] = 'General base';
$lang['BUILDING_1601'] = 'Research center';
$lang['BUILDING_1602'] = 'Oxygen factory';
$lang['BUILDING_1603'] = 'Personel quarters';
$lang['BUILDING_1604'] = 'Water factory';
$lang['BUILDING_1605'] = 'Metal extration center';
$lang['BUILDING_1606'] = 'Communication center';
$lang['BUILDING_1607'] = 'Converance center';
$lang['BUILDING_1608'] = 'Greenhouse';
$lang['BUILDING_1609'] = 'Hotel';

/* Defense (Asteroid) - Group 17 */
$lang['BUILDING_1700'] = 'Research center';
$lang['BUILDING_1701'] = 'Weapon factory';
$lang['BUILDING_1702'] = 'Short range missile';
$lang['BUILDING_1703'] = 'Warrior factory';
$lang['BUILDING_1704'] = 'Allarm system';
$lang['BUILDING_1705'] = 'Spacecraft factory';
$lang['BUILDING_1706'] = 'Long range launcher';
$lang['BUILDING_1707'] = 'Explorer factory';
$lang['BUILDING_1708'] = 'Drone factory';
$lang['BUILDING_1709'] = 'Warrior factory';

/* Energy (Asteroid) - Group 18 */
$lang['BUILDING_1800'] = 'Energy research center';
$lang['BUILDING_1801'] = 'Gas power facility';
$lang['BUILDING_1802'] = 'Petroleum research center';
$lang['BUILDING_1803'] = 'Petroleum extractors';
$lang['BUILDING_1804'] = 'Solar power facility';
$lang['BUILDING_1805'] = 'Gas extractors';
$lang['BUILDING_1806'] = 'Mining center';
$lang['BUILDING_1807'] = 'Nuclear power facility';
$lang['BUILDING_1808'] = 'Large orbit solar facility';
$lang['BUILDING_1809'] = 'Large mars colony';

/* Discount (Asteroid) - Group 19 */
$lang['BUILDING_1900'] = 'Training center';
$lang['BUILDING_1901'] = 'Terraforming center';
$lang['BUILDING_1902'] = 'Military personel quarters';
$lang['BUILDING_1903'] = 'Military headquarters';
$lang['BUILDING_1904'] = 'Supply depot';
$lang['BUILDING_1905'] = 'Construction company';
$lang['BUILDING_1906'] = 'Bootcamp';
$lang['BUILDING_1907'] = 'President\'s office';
$lang['BUILDING_1908'] = 'Village';
$lang['BUILDING_1909'] = 'Recreation facility';

/* Maintenance (Asteroid) - Group 20 */
$lang['BUILDING_2000'] = 'Architect design center';
$lang['BUILDING_2001'] = 'Drone repair center';
$lang['BUILDING_2002'] = 'Missile repair center';
$lang['BUILDING_2003'] = 'Explore repair center';
$lang['BUILDING_2004'] = 'Vehicle repair center';
$lang['BUILDING_2005'] = 'Warrior repair center';
$lang['BUILDING_2006'] = 'Infra repair center';
$lang['BUILDING_2007'] = 'Unit repair center';
$lang['BUILDING_2008'] = 'Power repair center';
$lang['BUILDING_2009'] = 'Robot repair center';

/*
** ------------------
** BUILDING PAGE
** ------------------
*/

$lang['BUILDING_TITLE'] = 'BUILDINGS';

$lang['BUILDING_NOTE1'] = 'Note: Income buildings provide higher hourly income. Each building contains citizens which increase hourly cost.';
$lang['BUILDING_NOTE2'] = 'Note: Defence buildings provide higher defence against attacks. Each building contains citizens which increase hourly cost.';
$lang['BUILDING_NOTE3'] = 'Note: Energy buildings provide faster energy recovery. Each building contains citizens which increase hourly cost.';
$lang['BUILDING_NOTE4'] = 'Note: Discount buildings provide price discount on building purchase. Each building contains citizens which increase hourly cost.';
$lang['BUILDING_NOTE5'] = 'Note: Maintenance buildings provide faster unit repair wich results in less unit loss during battles. Each building contains citizens which increase hourly cost.';

$lang['BUILDING_NOTE6'] = 'Note: Income buildings provide higher income for your moon base.';
$lang['BUILDING_NOTE7'] = 'Note: Defence buildings provide higher defence against attacks on your moon base.';
$lang['BUILDING_NOTE8'] = 'Note: Energy buildings provide faster energy recovery for your moon base.';
$lang['BUILDING_NOTE9'] = 'Note: Discount buildings provide price discount on moon building purchase.';
$lang['BUILDING_NOTE10'] = 'Note: Maintenance buildings provide faster moon unit repair wich results in less unit loss during battles.';

$lang['BUILDING_NOTE11'] = 'Note: Income buildings provide higher income for your mars base.';
$lang['BUILDING_NOTE12'] = 'Note: Defence buildings provide higher defence against attacks on your mars base.';
$lang['BUILDING_NOTE13'] = 'Note: Energy buildings provide faster energy recovery for your mars base.';
$lang['BUILDING_NOTE14'] = 'Note: Discount buildings provide price discount on mars building purchase.';
$lang['BUILDING_NOTE15'] = 'Note: Maintenance buildings provide faster mars unit repair wich results in less unit loss during battles.';

$lang['BUILDING_NOTE16'] = 'Note: Income buildings provide higher income for your asteroid base.';
$lang['BUILDING_NOTE17'] = 'Note: Defence buildings provide higher defence against attacks on your asteroid base.';
$lang['BUILDING_NOTE18'] = 'Note: Energy buildings provide faster energy recovery for your asteroid base.';
$lang['BUILDING_NOTE19'] = 'Note: Discount buildings provide price discount on your asteroid building purchase.';
$lang['BUILDING_NOTE20'] = 'Note: Maintenance buildings provide faster asteroid unit repair wich results in less unit loss during battles.';

$lang['BUILDING_SELL'] = 'You sell %s %s for %s dollar. Still %s deployed.';
$lang['BUILDING_LOW_UPKEEP'] = 'Not enough hourly income to sell %s %s for %s dollar.';
$lang['BUILDING_NOT_OWNED'] = 'You do not own %s %s.';

$lang['BUILDING_BUY'] = 'You buy %s %s for %s dollar. Now %s deployed.';
$lang['BUILDING_MAX'] = 'No more then %s %s(s) allowed!';
$lang['BUILDING_NO_MONEY'] = 'Not enough money to buy %s %s for %s dollar.'; 
$lang['BUILDING_LOW_UPKEEP2'] = 'Not enough hourly income to buy %s %s for %s dollar.';

$lang['BUILDING_UPKEEP'] = 'Stündliche Kosten';
$lang['BUILDING_PRICE'] = 'Preis';
$lang['BUILDING_DEPLOYED'] = 'Beschäftigt';
$lang['BUILDING_GAIN'] = 'Verdienst';
$lang['BUILDING_ENERGY'] = 'Energie';
$lang['BUILDING_INCOME'] = 'Einkommen';
$lang['BUILDING_REQUIRED'] = 'Benötigt';

/*
** ------------------
** MONEY 
** ------------------
*/

$lang['MONEY_TITLE'] = 'MONEY';

/*
** ------------------
** BANKS 
** ------------------
*/

$lang['BANK_GROUP_1'] = 'National';
$lang['BANK_GROUP_2'] = 'Trasquera';
$lang['BANK_GROUP_3'] = 'SwissCore';

$lang['BANK_TITLE'] = 'BANKS';
$lang['BANK_NOTE'] = 'Tipp: There is a %s% Gebühr für jede Einzahlung. Die Bank zahlt dir %s% tägliche Zinsen. ';
$lang['BANK_WARNING'] = 'Achtung: Nachrichtendienst und Kundschafter von anderen Spielern können Geld stehlen von dieser Bank.';

$lang['BANK_TRANSACTION_TYPE_0'] = 'Abgehoben:';
$lang['BANK_TRANSACTION_TYPE_1'] = 'Eingezahlt:';
$lang['BANK_TRANSACTION_TYPE_2'] = 'Bankgebühr';
$lang['BANK_TRANSACTION_TYPE_3'] = 'Restore bill';		
$lang['BANK_TRANSACTION_TYPE_4'] = 'Zinsen:';	
$lang['BANK_TRANSACTION_TYPE_5'] = 'Gestohlen:';
$lang['BANK_TRANSACTION_TYPE_6'] = 'Bonus ';

$lang['BANK_TRANSACTION_LOG'] = 'Kontoauszug';

$lang['BANK_WITHDRAW']= 'Withdrawn %s dollar from bank';
$lang['BANK_WITHDRAW_FAILED'] = 'No %s dollar on bank!';

$lang['BANK_DEPOSIT'] = 'Deposited %s dollar in the bank.';
$lang['BANK_DEPOSIT_FAILED'] = 'You do not have %s dollar.';

/*
** ------------------
** STOCK EXCHANGES
** ------------------
*/

$lang['STOCK_GROUP_1'] = 'Nasdaq';
$lang['STOCK_GROUP_2'] = 'DowJones';
$lang['STOCK_GROUP_3'] = 'AEX';
$lang['STOCK_GROUP_4'] = 'Personal';

$lang['STOCK_TITLE'] = 'STOCK EXCHANGES';
$lang['STOCK_BROKER_ERROR'] = 'Broker connection failed. No trading possible at this moment. Try again later.';
$lang['STOCK_BUY'] = 'You buy %s %s stocks for %s dollar. Now %s owned.';
$lang['STOCK_NO_MONEY'] = 'Not enough money to buy %s %s stocks for %s dollar.';
$lang['STOCK_PRICE'] = 'Stock price %s [%s]';
$lang['STOCK_PROFIT'] = 'Stock profit %s [%s]';
$lang['STOCK_NOT_OWNED'] = 'You do not own %s %s stocks.';
$lang['STOCK_SELL'] = 'You sell %s %s stocks for %s dollar. You paid %s dollar transaction fee. Still %s owned.';
$lang['STOCK_NOTE'] = 'Note: You can buy or sell stocks to make profit. Stock prices are based on realtime information from yahoo finance service. There is %s% handle fee on each sell transaction.';
$lang['STOCK_PRICE_TO_LOW'] = 'Stock price to low. Trading blocked!';

$lang['STOCK_SYMBOL'] = 'Stock Symbol'; 
$lang['STOCK_SYMBOL_INFO'] = 'Note: Enter yahoo financial stock symbol to customize this list.'; 

$lang['STOCK_ADD'] = 'Add Stock';
$lang['STOCK_SYMBOL_ADDED'] = 'You added (%s) to your personal stock list.';
$lang['STOCK_NO_SYMBOLS' ] = 'You did not add any personal stocks yet!';
$lang['STOCK_SYMBOL_NOT_FOUND'] = 'Stock symbol (%s) does not exist!';
$lang['STOCK_SYMBOL_AVAILABLE'] = 'Stock symbol (%s) all ready available in personal list.';

$lang['STOCK_REMOVE'] = 'Remove Stock';
$lang['STOCK_SYMBOL_REMOVED'] = 'Stock symbol removed!';

$lang['GENERAL_STOCKS'] = 'Stocks';

/*
** ------------------
** CASINO
** ------------------
*/

$lang['CASINO_TITLE'] = 'KASINO' ;

$lang['CASINO_WHEEL'] = 'Glücksrad';
$lang['CASINO_SLOTMACHINE'] = 'Einarmiger Bandit';

$lang['CASINO_COMING_SOON'] = 'ist noch in der Versuchsphase!';

$lang['CASINO_MONEY'] = 'Geld';
$lang['CASINO_NUMBER'] = 'Glücksnummer';
$lang['CASINO_BET'] = 'wetten';
$lang['CASINO_PLAY'] = 'Spielen';
$lang['CASINO_ROLL'] = 'Drehen';

$lang['CASINO_NO_BET'] = 'Gib deinen Wetteinsatz!';
$lang['CASINO_NO_LUCKY_NUMBER'] = 'Wähle deine Glücksnummer!';
$lang['CASINO_BET_TO_LARGE'] = 'Wetteinsatz zu hoch! Das Limit liegt bei %s Dollar.'; 
$lang['CASINO_NO_MONEY'] = 'Nicht genug Geld!'; 

$lang['CASINO_WIN'] = 'Glücksnummer war %s. Du gewinnst %s  Dollar.';
$lang['CASINO_LOST'] = 'Glücksnummer war %s. Du verlierst %s Dollar.';

$lang['CASINO_NOTE1'] = 'Note: Enter your bet and lucky number and press the play button. If you are lucky you win 10 times your bet.';
$lang['CASINO_NOTE2'] = 'Note: Enter your bet and press the play button. Maybe your bet will pay out.';

$lang['CASINO_UNLOCK'] = '%s is unlocked at level %s';

$lang['CASINO_SLOTMACHINE_WIN'] = 'Du gewinnst das %sfache deines Wetteinsatzes. Du erhälst %s Dollar.';
$lang['CASINO_SLOTMACHINE_LOST'] = 'Du verlierst %s Dollar.';
$lang['CASINO_SLOTMACHINE_HELP'] = 'The following slot machine combinations will pay out';

/*
** ------------------
** ALLIANCE
** ------------------
*/

$lang['ALLIANCE_TITLE'] = 'Verbündete';

$lang['ALLIANCE_PENDING_TITLE1'] = 'Pending';
$lang['ALLIANCE_PENDING_TITLE2'] = 'Pending [%s accepted - %s invited allies]';

$lang['ALLIANCE_ACCEPT_TITLE1'] = 'Akzeptieren';
$lang['ALLIANCE_ACCEPT_TITLE2'] = 'Akzeptiert [%s akzeptiert - %s eingeladen]';

$lang['ALLIANCE_INVITE_TITLE1'] = 'Einladen';
$lang['ALLIANCE_INVITE_TITLE2'] = 'Eingeladen [%s akzeptiert - %s eingeladene Verbündete]';

$lang['ALLIANCE_NO_PENDING'] = 'No pending invitations waiting!'; 
$lang['ALLIANCE_INVITATION'] = 'Bündnisanfrage gesendet an %s!'; 
$lang['ALLIANCE_REJECT'] = 'Reject %s as ally!';
$lang['ALLIANCE_DROP'] = 'Drop %s as ally!';
$lang['ALLIANCE_ACCEPT'] = '%s als Verbündeten akzeptiert!';
$lang['ALLIANCE_ALLY'] = 'Ally';
$lang['ALLIANCE_MAXIMUM'] = 'Maximume Anzahl von %s Verbündeten ist für das Level erreicht.'; 
$lang['ALLIANCE_LOCKED'] = 'Bündnisanfragen sind ab level 1 verfügbar';
$lang['ALLIANCE_NOTE'] = 'Tipp: Mit jedem bestätigtem Verbündeten, kannst du sechs weitere Einheiten in den Kampf schicken. Denke immer daran, Verbündete können nicht angegriffen werden.';

$lang['ALLIANCE_INVITE_FRIENDS'] = 'Invite friend by email';
$lang['ALLIANCE_INVITE_NOTE'] = 'Note: Invite a player for an alliance. If the other player accepts or rejects the alliance you will receive a notification by email (option in settings). Maximum amount of accepted + invited allies for this level is %s.';
$lang['ALLIANCE_EMAIL_INVALID']= 'Email address is not valid!';
$lang['ALLIANCE_ALREADY_INVITED'] = 'Email address is already invited!';
$lang['ALLIANCE_INVITE_SENT'] = 'Invite email is sent.';

$lang['ALLIANCE_COMMENT_TITLE'] = 'Message';
$lang['ALLIANCE_COMMENT_TEXT1'] = 'Create message (max. 400 characters) for all players';
$lang['ALLIANCE_COMMENT_TEXT2'] = 'Create message (max. 400 characters) for %s';
$lang['ALLIANCE_PLAYER_NEWS'] = 'Messages';
$lang['ALLIANCE_COMMENT_ALL'] = 'Message is stored and available for all players.';
$lang['ALLIANCE_COMMENT_PLAYER'] = 'Message is sent to %s';

$lang['LEADERBORD_BEST_PLAYER'] = 'Leaderboard (Best Players)';
$lang['LEADERBORD_BEST_PLAYER_NOTE'] = 'Note: Leaderboard shows the best human players. WarQuest robot (cyberspace) players are not shown!';

$lang['LEADERBORD_BEST_COUNTRY'] = 'Leaderboard (Best Countries)';
$lang['LEADERBORD_BEST_COUNTRY_NOTE'] = 'Note: Leaderboard shows the best real countries.';

$lang['LEADERBORD_PLAYER_COUNTRY'] = 'Leaderboard (Best Players of %s)';
$lang['LEADERBORD_PLAYER_COUNTRY_NOTE'] = 'Note: Leaderboard shows the best players of the selected country.';

/*
** ------------------
** FORUM 
** ------------------
*/

$lang['FORUM_TITLE'] = 'FORUMS'; 
$lang['FORUM_TITLE2'] = 'Forums';
$lang['FORUM_NOTE'] = 'Note: Select a forum to see all posted topics.';

$lang['FORUM_1'] = 'Announcements'; 
$lang['FORUM_NOTE_1'] = 'General announcements';
$lang['FORUM_2'] = 'Bug Reports'; 
$lang['FORUM_NOTE_2'] = 'What goes wrong in this release?';
$lang['FORUM_3'] = 'Feature Requests'; 
$lang['FORUM_NOTE_3'] = 'What do you want in the next release?';
$lang['FORUM_4'] = 'Help'; 
$lang['FORUM_NOTE_4'] = 'What is not clear in WarQuest?';
$lang['FORUM_5'] = 'Other'; 
$lang['FORUM_NOTE_5'] = 'Any other discussion?';
$lang['FORUM_6'] = 'Country Communities'; 
$lang['FORUM_NOTE_6'] = 'Local language discussions?';

$lang['FORUM_SEARCH_TOKEN'] = 'Search token must be atleast 3 character long.';

$lang['TOPIC_TITLE'] = 'Topics'; 
$lang['TOPIC_CREATED_INPUT'] = 'Create new topic (max. 80 characters)';
$lang['TOPIC_CREATED'] = 'Topic ist erstellt';
$lang['TOPIC_UPDATED'] = 'Topic ist upgedatet';
$lang['TOPIC_DELETED'] = 'Topic ist gelöscht';
$lang['TOPIC_NO_TOPICS'] = 'Im Moment sind keine Topic(s) gegründet.';
$lang['TOPIC_NOTE'] = 'Tipp: Select a topic to read/write posted messages or create a new topic.'; 
$lang['TOPIC_CREATED_BY'] = '(Erstellt von %s)';

/*
** ------------------
** FORUM - POLL
** ------------------
*/

$lang['POLL_TITLE'] = 'Wahlen';
$lang['POLL_RESULT_TITLE'] = 'Wahl Resultate';
$lang['POLL_TEASER_TITLE'] = 'Neue Wahl';
$lang['POLL_RESULTS'] = 'Resultat';
$lang['POLL_ClOSED'] = '(Wahl geschlossen)';
$lang['POLL_VOTE_ADD'] = 'Danke für die Unterstützung!';
$lang['POLL_VOTE_REMOVE'] = 'Deine Wahl wurde abgebrochen!';
$lang['POLL_VOTE'] = 'Wahl';
$lang['POLL_VOTES'] = 'Abstimmen';
$lang['POLL_CANCEL'] = 'Abbrechen';
$lang['POLL_SUMMARY'] = 'Total Voters: %s';
$lang['POLL_WARNING'] = 'Select one of the possible vote options!';

/*
** ------------------
** FORUM - CHAT
** ------------------
*/

$lang['CHATROOM_TITLE'] = 'Chatroom';
$lang['CHATROOM_NOTE'] = 'Tipp: Klicke einen Online Spieler an um den Chat zu starten!';
$lang['CHATROOM_LAST_ACTIVE'] = 'Zuletzt aktiv';
$lang['CHATROOM_CHAT'] = 'Chat';
$lang['CHAT_NOTE'] = 'Tipp: Schreibe eine Nachricht um den Chat zu beginnen!';

$lang['CHAT_TITLE'] = 'Chat';

/*
** ------------------
** HELP - INSTRUCTIONS
** ------------------
*/

$lang['HELP_TITLE'] = 'Hilfe';

$lang['HELP_GENERAL_SUBTITLE'] = 'Einführung';

$lang['HELP_INTRO_TITLE'] = 'Einführung';
$lang['HELP_INTRO'] =	'WarQuest ist ein kostenloses Multiplayer Online Game featuring a war zone mit tausenden von realen Spielern. WarQuest nimmt dich mit ins 
Jahr 2020. Der Weltkrieg ist ausgebrochen. Das Ziel des Spiels ist es dein Land zu verteidigen und andere Länder zu erobern. Rüste dich mit schwerem Kriegsgerät,
 produziere Einheiten, spiele Missionen, kämpfe, schließe Bündisse und werde der beste Spieler aller Zeiten.';

$lang['HELP_EXP_TITLE'] = 'Erfahrungspunkte / Level';
$lang['HELP_EXP'] = 'Spiele Missionen und trage Kämpfe gegen Spieler aus um Erfahrungspunkte zu sammeln. Wenn du genügend Punkte für einen Levelaufstieg gesammelt hast, 
kannst du wertvolle Skillpunkte verteilen. Wenn du eine Stufe aufsteigst, füllt sich deine Energie-, Lebens- und Munitionsbar automatisch vollständig auf.';

$lang['HELP_HEALTH_TITLE'] = 'Gesundheit';
$lang['HELP_HEALTH'] = 'Deine Gesundheit nimmt mit jedem Kampf drastisch ab, wird jedoch automatisch mit der Zeit wieder aufgefüllt. Du kannst auch das Krankenhaus aufsuchen (Home -> Restore) um sofortige Heilung zu erhalten.';

$lang['HELP_ENERGY_TITLE'] = 'Energie'; 
$lang['HELP_ENERGY'] = 'Deine Energie nimmt mit jeder Mission ab, füllt sich jedoch automatisch mit der Zeit wieder. Kaufe Energie Gebäude um eine größere Menge wieder zu erlangen und somit schneller Mission zu spielen.
 Auf dem gleiche Weg wie du deine Gesundheit sofort auffrischen kannst, gibt es eine Möglichkeit für dein Energie.';

$lang['HELP_AMMO_TITLE'] = 'Munition'; 
$lang['HELP_AMMO'] =	'In jedem Kampf gegen einen Spieler benötigst du Eine Munitionspunkt. Die Munition füllt sich ebenfalls mit der Zeit vollkommen automatisch. Ein Waffenhändler füllt dein Depot vollständig
 wieder auf, auf dem gleichen weg zu finde wie das Krankenhaus.';

$lang['HELP_MISSION_TITLE'] = 'Missionen';
$lang['HELP_MISSION'] = 'Spiele Missionen um Geld und Erfahrungspunkte zu erhalten für einen Stufenaufstieg. 
Wenn eine Mission zu 100% abgeschlossen ist, erhälst du beim wiederholten Angriff die doppelte Menge Geld. Wenn der Kontinent vollständig 
erobert wurde, erhälst du einen Bonus auf dein Stündliches Einkommen.';

$lang['HELP_BATTLE_TITLE'] = 'Kampf';
$lang['HELP_BATTLE'] =	'Kämpfe gegen andere Spieler, um Erfahrungspunkte und Geld zu verdienen, für einen Stufenaufstieg.
 Während des Kampfes werden deine Gebäude und Truppen beschädigt und können sogar fallen. Du kannst nur gegen Spieler aus anderen Ländern kämpfen.';

$lang['HELP_UNITS_TITLE'] = 'Einheiten';
$lang['HELP_UNITS'] =  'Während eines Angriffs werden deine besten Truppen automatisch gewählt. Die Größe der Truppe (Anzahl) deiner Armee bezieht sich auf die Anzahl deiner Verbündeten. Zu Anfang 
 besitzt du nur einen Verbündeten (Dich selbst) und kannst daher nur sechs Einheiten befehligen. Jeder Verbündeter hilft dir sechs weitere Einheiten zu führen. Denke daran es werden immer nur die besten in den Kampf geschickt und die Anzahl der Truppen entspricht dem 6fachen deiner Verbündeten.';

$lang['HELP_BUILDINGS_TITLE'] = 'Gebäude';
$lang['HELP_BUILDINGS'] = 'Während des Spielens ermöglichen dir deine Gebäude eine bestimmtes Einkommen, eine Verteidigung, mehr Energie, 
Rabatte und/oder besseren Schutz gegen Verlust von Einheiten während eines Kampfes. Jedes gekaufte Gebäude steigert den Preis beim Neuerwerb. Jedes Gebäude hat natürlich auch Zivilisten, die Kosten verursachen.';

$lang['HELP_BANKS_TITLE'] = 'Bank';
$lang['HELP_BANKS'] = 'Jede Bank hat eine Einzahlungsgebühr, dafür erhälst du aber auch Zinsen. Die National Bank ist die sicherste aller Banken, jedoch ist der Zinssatz auch dementsprechend der niedrigste. 
.Andere Banken haben einen höheren Zinssatz, jedoch ist es anderen Spielern möglich, mithilfe vom Nachrichtendienst (Erde) bzw. Kundschaftern (Mond) diese auszurauben.';

$lang['HELP_ALLIANCE_TITLE'] = 'Bündnis'; 
$lang['HELP_ALLIANCE'] = 'Jeder bestätigte Verbündetet erlaubt dir sechs weitere Einheiten zu kommandieren(welche du natürlich besitzen musst) 
während eines Angriffs auf einen Spieler. Gehe Bündnise ein um stärker zu werden! Selbstverständliche ist es nicht möglich Verbündete anzugreifen.';

$lang['HELP_SKILL_POINTS_TITLE'] = 'Skill Punkte';
$lang['HELP_SKILL_POINTS'] = 'During the game skill points can be collected. Deploy skill points to 
increase attack, defense, health, energy and/or ammo skills. Ammo skill upgrade costs two skill points, 
others will cost you only one skill points. You can also trade-in 2:1 skillpoints to reallocate your skills.';

$lang['HELP_TACTICS_TITLE'] = 'Tactics';
$lang['HELP_TACTICS'] = 'One thing to keep in mind is that units used in missions are also subject to 
loss as casualties. This is important to consider as the cost of replacing some of the higher priced 
units used in a mission may exceed the money earned from the mission itself. In general, if your goal 
is to maximize money from missions, then focus on the Money / Energy value of the mission. 
If your goal is to maximize experience points, then focus on the Exp / Energy value of the 
missions.<br/><br/>

Once you hit the higher levels, the game automatically increases the range of opponents that can 
attack you. When this occurs, you should increase alliance size or max out the number of members 
in your alliance.<br/><br/>

Defense buildings are an ideal purchase because they added to your defense score whenever you are
 attacked. I recommend purchasing as many as you can afford as it will allow you to allocate more 
 of your money toward attack units without having to worry about their defense points.<br/><br/>
 
In WarQuest, defense buildings makes some opponents extremely difficult to successfully attack. 
Although it is still recommended to allocate points to defense, I recommend putting as many points 
as possible toward Attack. You can compensate for lower defense skill points with defense 
buildings.<br/><br/>

When deciding what units to buy, you need to carefully consider the units hour costs, Attack and 
Defense strenght. Assuming you can afford to buy the unit, cost should not be a factor in your 
decision since it is only a one time expenditure. Because of the reduction in income dure to hourly
unit cost, it does not always make sense to buy the best available units. If you are winning most of 
your fights with your current units, then it may make more strategic sense to not increase your 
hourly cost and allow your income to build at a faster rate.';

$lang['HELP_GRAVATAR_TITLE'] = 'Gravatar';
$lang['HELP_GRAVATAR'] = 'WarQuest support gravatar (www.gravatar.com) image service. Gravatar is an 
image that follows you from site to site appearing beside your (nick)name.';

$lang['HELP_BOUNTY_TITLE'] = 'Bounty Hunting';
$lang['HELP_BOUNTY'] = 'You can set bounty on your opponents head. The bounty price is related to the 
opponent level. After you set the bounty other players <b>(from an other country)</b> can attack the 
opponent (Battle -> BountyHunting). If the opponent is defended he will lose some experience points 
and the bounty money is transferred to the winner.';

$lang['HELP_UNITS_CONDITION_TITLE'] = 'Einheiten Zustand (EZ)';
$lang['HELP_UNITS_CONDITION'] = 'Dieser Wert gibt dir aufschlussreiche Inforamtion über den momentanigen Zustand deiner Streitkraft. 
Sollte der Wert auf 0% sinken, wirst du einige Einheiten verlieren. Um dies zu verhinderen solltest du regelmäßig die Werkstatt aufsuchen und deine Truppen pflegen, gehe dazu (Home -> Restore).'; 

$lang['HELP_BUILDINGS_CONDITION_TITLE'] = 'Gebäude Zustand (GZ)';
$lang['HELP_BUILDINGS_CONDITION'] = 'This value gives information about your current base buildings 
condition. If the condition goes below 0% you will lose some buildings. To prevent building loss 
you can visit (Home -> Restore) to repair your base.'; 

$lang['HELP_FORUM_TITLE'] = 'Forum';
$lang['HELP_FORUM'] = 'To get more information and chat with other players please visit the Warquest 
Forum under (Alliance -> Forum).';

$lang['HELP_WORLDMAP_TITLE'] = 'Map';
$lang['HELP_WORLDMAP'] = 'The map (earth and moon) contain 72 regions which can be conquered with playing 
missions. The regions can have one of the following colors: <br/>
- "Green" Region 0% conquered<br/>
- "Yellow" Region 33% conquered.<br/>
- "Purple" Region 66% conquered.<br/>
- "Orange" Region 100% conquered.<br/>
- "Red" Rebellion in region. Region must be reconquered.';

$lang['HELP_SHORTCUTS_TITLE'] = 'Menu Shortcuts';
$lang['HELP_SHORTCUTS'] = 'The following hidden menu shortcuts are available in the banner for 
faster navigation:<br/>
- Click "Cash" to navigate to player leaderboard page.<br/>
- Click "Exp." to navigate to country leaderboard page.<br/>
- Click "Level" to navigate to the poll page.<br/>
- Click "Health" to navigate to restore page.<br/>
- Click "Energy" to navigate to player profile page.<br/>
- Click "Ammo" to navigate to skill points page.';

$lang['HELP_ATTACK_FORCE_TITLE'] = 'Attack Force';
$lang['HELP_ATTACK_FORCE'] = 'Before battle you can select one of the following attack forces:<br/><br/>
EARTH<br/>
- "Army" Best of Cavalry, Navy and Aircrafs units.<br/>
- "Cavalry" Only Cavalry units.<br/>
- "Navy" Only Navy units.<br/>
- "Airforce" Only Aircraft units.<br/>
- "Espionage" Only Espionage units.<br/><br/>
MOON<br/>
- "SpaceTroops" Best of Drone, Warrior and Spacecraft units.<br/>
- "Drones" Only Drone units.<br/>
- "Warriors" Only Warrior units.<br/>
- "Spacecrafts " Only SpaceCraft units.<br/>
- "Explorers " Only Explorer units.';

$lang['HELP_REBELLION_CONDITION_TITLE'] = 'Rebellion Condition (RC)';
$lang['HELP_REBELLION_CONDITION'] = 'This value gives information about your current rebellion condition. Region 
rebellion is trigger by espionage (earth) or explorers (moon) attacks by your opponents. If the 
condition reaches 100%, some of your conquered regions will be in rebellion. To prevent rebellion, 
visit (Home -> Restore) to quell the rebellion. Each rebellion region results in postponed continent 
hourly income. Restore control in the rebel region by playing the related mission.';

/*
** ------------------
** HELP - RELEASE NOTES
** ------------------
*/

$lang['HELP_NOTES_SUBTITLE1'] = 'Release Notes';
$lang['HELP_NOTES_SUBTITLE2'] = 'Release Notes (English only)';

/*
** ------------------
** HELP - RANKS
** ------------------
*/

$lang['HELP_RANKS_SUBTITLE'] = 'Ranks';
$lang['HELP_RANKS'] = 'The following ranks are available:';

/*
** ------------------
** HELP - AWARDS
** ------------------
*/

$lang['HELP_AWARDS_SUBTITLE'] = 'Auszeichnungen';
$lang['HELP_BATTLE_AWARDS'] = 'The following battle won awards can be earned:';
$lang['HELP_BOUNTY_AWARDS'] = 'The following bounty set awards can be earned:';
$lang['HELP_REBEL_AWARDS'] = 'The following rebellion rise awards can be earned:';

/*
** ------------------
** HELP - DONATE
** ------------------
*/

$lang['HELP_DONATE_TITLE1'] = 'Donate';
$lang['HELP_DONATE_TITLE2'] = 'Donate (English only)';

$lang['HELP_SUBTITLE_DONATE1'] = 'General';
$lang['HELP_DONATE1'] = 'WarQuest software may be used free of charge, but if you wish to express 
your appreciation for the time and resources the author spent developing and supporting it 
over the years, and also help reduce the costs of running the web server, we do accept and appreciate 
donations.';

$lang['HELP_SUBTITLE_DONATE2'] = 'Reward';
$lang['HELP_DONATE2'] = 'Each dollar donated will be rewarded with 1 trade point. Purchased trade points 
can be exchanged in to skill points, cash money or can be used to improve your health, energy or ammo 
restore timer. The reward is manually processed so keep in mind that it takes a few hours before it is available.';

$lang['HELP_SUBTITLE_DONATE3'] = 'PayPal';
$lang['HELP_DONATE3'] = 'To make a donation online using your credit card, or PayPal account, click 
below and enter the amount you would like to contribute. Your credit card will be processed by PayPal, 
a trusted name in secure online transactions. Many thanks for your support.';
/*
** ------------------
** HELP - STATS
** ------------------
*/

$lang['HELP_STATS_TITLE'] = 'Statistics';
$lang['HELP_STATS_NOTE'] = 'Note: On this page realtime WarQuest statistics are showed.';
$lang['HELP_STATS_PLAYERS'] = 'New players (last 14 days)';
$lang['HELP_STATS_ONLINE'] = 'Players online (last 14 days)';
$lang['HELP_STATS_FIGHTS'] = 'Player fights (last 14 days)';
$lang['HELP_STATS_MISSIONS'] = 'Missions played (last 14 days)';
$lang['HELP_STATS_CASINO'] = 'Casino games played (last 14 days)';
$lang['HELP_STATS_ADS'] = 'Ads showed (last 14 days)';
$lang['HELP_STATS_REQUESTS'] = 'Server requests (last 14 days)';

/*
** ------------------
** HELP - ABOUT
** ------------------
*/

$lang['HELP_ABOUT_SUBTITLE'] = 'About';
$lang['HELP_BACKGROUND_TITLE'] = 'Background';
$lang['HELP_BACKGROUND'] = 'WarQuest is created by <a target="new" href="http://www.plaatsoft.nl">PlaatSoft</a>. Original game idea is based on some other games available in the Apple appstore. The main reason to recreate this kind of game is to create a better game play and user interface which can be controlled on the following device types: Smart phones (Apple, Android, Nokia and BlackBerry), Tables (Samsung and Apple), Game consoles (Nintendo) and all kinds of notebooks (Intel / AMD base).';
$lang['HELP_CREDITS_TITLE'] = 'Credits';
$lang['HELP_BROWSERS_TITLE'] = 'Supported Browsers'; 
$lang['HELP_HARDWARE_TITLE'] = 'Supported Hardware'; 
$lang['HELP_DISCLAIMER_TITLE'] = 'Disclaimer'; 
$lang['HELP_DISCLAIMER'] = 'The program is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.<br/>';

$lang['HELP_CREDITS_TITLE'] = 'Credits';
$lang['HELP_CREDITS'] = 'Many thanks to the following people and organisations who helped creating this game.';
$lang['HELP_CREDITS_ARCHITECT'] = 'Architect';
$lang['HELP_CREDITS_DEVELOPERS'] = 'Developer';
$lang['HELP_CREDITS_GRAPHICS'] = 'Graphics & Information';
$lang['HELP_CREDITS_TRANSLATORS'] = 'Translators';
$lang['HELP_CREDITS_TESTERS'] = 'Testers';
$lang['HELP_CREDITS_OTHER'] = 'Other';
$lang['HELP_CREDITS_OTHER_NOTE'] = 'And of course all WarQuest players who sent great feedback to improve the game. Enjoy then game and lets have fun!';

/*
** ------------------
** RANK DATA
** ------------------
*/

$lang['RANK_1'] = "Private";
$lang['RANK_2'] = "Private first class";
$lang['RANK_3'] = "Specialist";
$lang['RANK_4'] = "Corporal";
$lang['RANK_5'] = "Sergeant";
$lang['RANK_6'] = "Staff Sergeant";
$lang['RANK_7'] = "Sergeant First Class";
$lang['RANK_8'] = "Master Sergeant";
$lang['RANK_9'] = "First Sergeant";
$lang['RANK_10'] = "Sergeant Major";
$lang['RANK_11'] = "Command Sergeant Major";
$lang['RANK_12'] = "Sergeant Major of the Army";
$lang['RANK_13'] = "Second Lieutenant";
$lang['RANK_14'] = "First Lieutenant";
$lang['RANK_15'] = "Captain";
$lang['RANK_16'] = "Major";
$lang['RANK_17'] = "Lieutenant Colonel";
$lang['RANK_18'] = "Colonel";
$lang['RANK_19'] = "Brigadier General";
$lang['RANK_20'] = "Major General";
$lang['RANK_21'] = "Lieutenant General";
$lang['RANK_22'] = "General";
$lang['RANK_23'] = "General of the Army";

/*
** ------------------
** COUNTRY NAMES
** ------------------
*/

$landcode = array();

$landcode['ad'] = "Andorra";
$landcode['ae'] = "Arab Emirates";
$landcode['af'] = "Afghanistan";
$landcode['ag'] = "Antigua and Barbuda";
$landcode['ai'] = "Anguilla";
$landcode['al'] = "Albania";
$landcode['am'] = "Armenia";
$landcode['an'] = "Netherlands Antilles";
$landcode['ao'] = "Angola";
$landcode['aq'] = "Antarctica";
$landcode['ar'] = "Argentina";
$landcode['as'] = "American Samoa";
$landcode['at'] = "Österreich";
$landcode['au'] = "Australien";
$landcode['aw'] = "Aruba";
$landcode['ax'] = "Aland Islands";
$landcode['az'] = "Azerbaijan";
		
$landcode['ba'] = "Bosnia and Herzegovina";
$landcode['bb'] = "Barbados";
$landcode['bd'] = "Bangladesch";
$landcode['be'] = "Belgien";
$landcode['bf'] = "Burkina Faso";
$landcode['bg'] = "Bulgaria";
$landcode['bh'] = "Bahrain";
$landcode['bi'] = "Burundi";
$landcode['bj'] = "Benin";
$landcode['bm'] = "Bermuda";
$landcode['bn'] = "Brunei Darussalam";	
$landcode['bl'] = "Saint Barthelemy";
$landcode['bn'] = "Brunei";
$landcode['bo'] = "Bolivia";
$landcode['br'] = "Brazil";
$landcode['bs'] = "Bahamas";
$landcode['bt'] = "Bhutan";
$landcode['bv'] = "Bouvet island";
$landcode['bw'] = "Botswana";
$landcode['by'] = "Belarus";
$landcode['bz'] = "Belize";
	
$landcode['ca'] = "Canada";
$landcode['cc'] = "Cocos Islands";
$landcode['cf'] = "Central African Republic";
$landcode['cg'] = "Kongo";
$landcode['ch'] = "Schweiz";
$landcode['ci'] = "Cote d lvoire";
$landcode['ck'] = "Cook Islands";
$landcode['cl'] = "Chili";
$landcode['cm'] = "Kameroon";
$landcode['cn'] = "China";
$landcode['co'] = "Columbien";
$landcode['cr'] = "Costa Rica";
$landcode['cs'] = "Serbia en Montenegro";
$landcode['cu'] = "Kuba";
$landcode['cv'] = "Cape Verde";
$landcode['cx'] = "Christmas Island";
$landcode['cy'] = "Cyprus";
$landcode['cz'] = "Czech Republic";
	
$landcode['de'] = "Deutschland";
$landcode['dj'] = "Djibouti";
$landcode['dk'] = "Denmark";
$landcode['dm'] = "Dominica";
$landcode['do'] = "Dominican Republic";
$landcode['dz'] = "Algeria";
	
$landcode['ec'] = "Equador";
$landcode['ee'] = "Estonia";
$landcode['eg'] = "Ägypten";
$landcode['eh'] = "Western Sahara";
$landcode['er'] = "Eritrea";
$landcode['es'] = "Spain";
$landcode['et'] = "Ethiopia";
$landcode['eu'] = "Cyberspace";
	
$landcode['fi'] = "Finnland";
$landcode['fj'] = "Fiji";
$landcode['fk'] = "Falkland Islands";
$landcode['fm'] = "Micronesia";
$landcode['fo'] = "Faroe Islands";
$landcode['fr'] = "France";
	
$landcode['ga'] = "Gabon";
$landcode['gb'] = "United Kingdom";
$landcode['gd'] = "Grenada";
$landcode['ge'] = "Georgia";
$landcode['gf'] = "French Guiana";
$landcode['gh'] = "Ghana";
$landcode['gi'] = "Gibraltar";
$landcode['gl'] = "Grönland";
$landcode['gm'] = "Gambia";
$landcode['gn'] = "Guinea";
$landcode['gp'] = "Guadeloupe";
$landcode['gq'] = "Equatorial Guinea";
$landcode['gr'] = "Greece";
$landcode['gs'] = "Zuid-Georgia";
$landcode['gt'] = "Guatemala";
$landcode['gu'] = "Guam";
$landcode['gw'] = "Guinee-Bissau";
$landcode['gy'] = "Guyana";
	
$landcode['hk'] = "Hong Kong";
$landcode['hm'] = "Heard- en McDonald Islands";
$landcode['hn'] = "Honduras";
$landcode['hr'] = "Kroatien";
$landcode['ht'] = "Haiti";
$landcode['hu'] = "Hungary";
	
$landcode['id'] = "Indonesien";
$landcode['ie'] = "Irland";
$landcode['il'] = "Israel";
$landcode['in'] = "India";
$landcode['im'] = "Isle of Man";
$landcode['io'] = "BI Ocean Territory";
$landcode['iq'] = "Irak";
$landcode['ir'] = "Iran";
$landcode['is'] = "Iceland";
$landcode['it'] = "Italien";
	
$landcode['jm'] = "Jamaika";
$landcode['jo'] = "Jordan";
$landcode['jp'] = "Japan";
	
$landcode['ke'] = "Kenia";
$landcode['kg'] = "Kyrgyzstan";
$landcode['kh'] = "Cambodia";
$landcode['ki'] = "Kiribati";
$landcode['km'] = "Comores";
$landcode['kn'] = "Saint Kitts en Nevis";
$landcode['kp'] = "North Korea";
$landcode['kr'] = "South Korea";
$landcode['kw'] = "Kuwait";
$landcode['ky'] = "Cayman Islands";
$landcode['kz'] = "Kazachstan";
	
$landcode['la'] = "Laos";
$landcode['lb'] = "Libanon";
$landcode['lc'] = "Saint Lucia";
$landcode['li'] = "Liechtenstein";
$landcode['lk'] = "Sri Lanka";
$landcode['lr'] = "Liberia";
$landcode['ls'] = "Lesotho";
$landcode['lt'] = "Lithuania";
$landcode['lu'] = "Luxemburg";
$landcode['lv'] = "Latvia";
$landcode['ly'] = "Libyen";
	
$landcode['ma'] = "Marokko";
$landcode['mc'] = "Monako";
$landcode['md'] = "Moldova";
$landcode['mg'] = "Madagascar";
$landcode['mh'] = "Marshall Islands";
$landcode['mk'] = "Macedonia";
$landcode['ml'] = "Mali";
$landcode['mm'] = "Myanmar";
$landcode['mn'] = "Mongolia";
$landcode['mo'] = "Macao";
$landcode['mp'] = "Northern Mariana Islands";
$landcode['mq'] = "Martinique";
$landcode['mr'] = "Mauritania";
$landcode['ms'] = "Montserrat";
$landcode['mt'] = "Malta";
$landcode['mu'] = "Mauritius";
$landcode['mv'] = "Maldives";
$landcode['mw'] = "Malawi";
$landcode['mx'] = "Mexico";
$landcode['my'] = "Malaysia";
$landcode['mz'] = "Mozambique";
	
$landcode['na'] = "Namibia";
$landcode['nc'] = "New Caledonia";
$landcode['ne'] = "Niger";
$landcode['nf'] = "Norfolk Islands";
$landcode['ng'] = "Niger";
$landcode['ni'] = "Nicaragua";
$landcode['nl'] = "Netherlands";
$landcode['no'] = "Norway";
$landcode['np'] = "Nepal";
$landcode['nr'] = "Nauru";
$landcode['nu'] = "Niue";
$landcode['nz'] = "New Zealand";
	
$landcode['om'] = "Oman";
	
$landcode['pa'] = "Panama";
$landcode['pe'] = "Peru";
$landcode['pf'] = "French Polynesia";
$landcode['pg'] = "Papua New Guinea";
$landcode['ph'] = "Philippines";
$landcode['pk'] = "Pakistan";
$landcode['pl'] = "Poland";
$landcode['pm'] = "Saint Pierre and Miquelon";
$landcode['pn'] = "Pitcairn";
$landcode['pr'] = "Puerto Rico";
$landcode['ps'] = "Palestinian";
$landcode['pt'] = "Portugal";
$landcode['pw'] = "Palau";
$landcode['py'] = "Paraguay";
	
$landcode['qa'] = "Qatar";
	
$landcode['re'] = "Reunion";
$landcode['ro'] = "Romania";
$landcode['ru'] = "Russian Federation";
$landcode['rs'] = "Serbia";
$landcode['rw'] = "Rwanda";
	
$landcode['sa'] = "Saudi Arabia";
$landcode['sb'] = "Solomon Islands";
$landcode['sc'] = "Seychelles";
$landcode['sd'] = "Sudan";
$landcode['se'] = "Sweden";
$landcode['sg'] = "Singapore";
$landcode['sh'] = "Saint-Helena";
$landcode['si'] = "Slovenia";
$landcode['sj'] = "Svalbard and Jan Mayen";
$landcode['sk'] = "Slovakia";
$landcode['sl'] = "Sierra Leone";
$landcode['sm'] = "San Marino";
$landcode['sn'] = "Senegal";
$landcode['so'] = "Somalia";
$landcode['sr'] = "Suriname";
$landcode['st'] = "Sao Tome en Principe";
$landcode['sv'] = "El Salvador";
$landcode['sy'] = "Syrien";
$landcode['sz'] = "Swaziland";
	
$landcode['tc'] = "Turks and Caicos Islands";
$landcode['td'] = "Chad";
$landcode['tg'] = "Togo";
$landcode['th'] = "Thailand";
$landcode['tj'] = "Tajikistan";
$landcode['tk'] = "Tokelau";
$landcode['tl'] = "Timor";
$landcode['tm'] = "Turkmenistan";
$landcode['tn'] = "Tunisien";
$landcode['to'] = "Tonga";
$landcode['tr'] = "Turkei";
$landcode['tt'] = "Trinidad and Tobago";
$landcode['tv'] = "Tuvalu";
$landcode['tw'] = "Taiwan";
$landcode['tz'] = "Tanzania";
	
$landcode['ua'] = "Ukraine";
$landcode['ug'] = "Uganda";
$landcode['um'] = "United States Minor Outlying Islands";
$landcode['us'] = "USA";
$landcode['uy'] = "Uruguay";	
$landcode['uz'] = "Uzbekistan";
	
$landcode['va'] = "Vatikan";
$landcode['vc'] = "Saint Vincent and the Grenadines";
$landcode['ve'] = "Venezuela";
$landcode['vg'] = "Virgin Islands; British";
$landcode['vi'] = "Virgin islands; US";
$landcode['vn'] = "Vietnam";
$landcode['vu'] = "Vanuatu";
	
$landcode['wf'] = "Wallis and Futuna";
$landcode['ws'] = "Samoa";
	
$landcode['ye'] = "Yemen";
$landcode['yt'] = "Mayotte";
	
$landcode['za'] = "Süd Afrika";
$landcode['zm'] = "Zambia";
$landcode['zw'] = "Zimbabwe";
	
/*
** ------------------
** THE END
** ------------------
*/

?>