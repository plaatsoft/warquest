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
**  All copyrights reserved (c) 2008-2014 PlaatSoft
*/

$notes[66] = '
<div class="subparagraph2">06-03-2014</div>
<i>Game Server v6.6</i>
<ul>
<li>Added 45 mission awards.</li>
<li>Added player search to Player->Alliance->Invite page.</li>
<li>Added Forums->Clan message system.</li>
<li>Added Admin->Views page (Admin Mode only).</li>
<li>Added robot account update (Admin Mode only).</li>
<li>Improve Admin->Levels page (Admin Mode only).</li>
<li>Added doAlliance method to WarQuest WebService interface.</li>
<li>Improve doMission method of WarQuest WebService interface.</li>
<li>Disable account reset functionality.</li>
<li>Disable automatic clan (member) inactive remove.</li>
<li>Added trade, restore features to unlock schema.</li>
</ul></br>

<i>General</i>
<ul>
<li>Please visit www.gravatar.com to upload a player image.</li>
</ul>
';

$notes[65] = '
<div class="subparagraph2">27-02-2014</div>
<i>Game Server v6.5</i>
<ul>
<li>Clan Wars improvements:</li>
<ul>
<li>Added clan missions. See Missions->Clan.</li>
<li>Added clan statistics to Players->Clan->Clan Profile</li>
<li>Added hyperlink from Home->Profile->Clan to Clan Profile.</li>
<li>Added Players->Leaderboard->Best-Clans.</li>
<li>Max. allowed daily deposit to clan bank is 10x hourly income.</li>
</ul>
</ul>
<ul>
<li>GUI improvements:</li>
<ul>
<li>Refactor HTML to support new CCS3 themes.</li>
<li>Added "transparent" theme (Home->Settings->Theme)</li>
<li>Added more color to all themes.</li>
<li>Removed not used themes.</li>
<li>Redesign main menu and login page.</li>
<li>Improve bank transaction log.</li>
<li>Update Help->Instructions text.</li>
<li>Added Home->Profile->Total hourly income page.</li>
<li>Added Home->Profile->Citizens cost page.</li>
<li>Added hyperlinks from Home->Profile->Assest to Bank pages</li>
</ul>
<li>Other improvements:</li>
<ul>
<li>Added two extra mars discount buildings.</li>
<li>Leaderboard position is now only based on expercience.</li>
<li>Limit maximum amount of promotion email invites.</li>
<li>Improve email address validation.</li>
</ul>
</ul>
<br/>

<i>Windows Client v1.6</i>
<ul>
<li>Added text copy parse support.</li>
<li>Added CCS3 support.</li>
<li>Added HTML5 audio support.</li>
<li>Use QT library 5.2.1 as engine.</li>
<li>WarQuest was build with QtCreator v3.0.1</li>
<li>Released app on www.plaatsoft.nl</li>
</ul>';

$notes[64] = '
<div class="subparagraph2">17-02-2014</div>
<i>Game Server v6.4</i>
<ul>
<li>Update premium gold features:</li>
<ul>
<li>Added premium membership feature to Home->Trade page</li>
<li>Premium membership has the following benefits:</li>
<ul>
<li>Double experience during battles and missions.</li>
<li>Triple money during battles and missions.</li>
</ul>
</ul>
<li>Clan Wars improvements:</li>
<ul>
<li>Added clan bank transaction log.</li>
<li>Added clan bank depostit fee.</li>
<li>Added clan bank daily service charge.</li>
</ul>
<li>Added basic SOAP web service interface</li>
<ul>
<li>URL is http://www.warquest.nl/service?wsdl</li>
<li>Added getPlayer method</li>
<li>Added getClan method</li>
<li>Added getPlanet method</li>
<li>Added doBattle method</li>
<li>Added doMission method</li>
</ul>
<li>Enable HTTPS in Apache (based on selfsigned certificate).</li>
<li>Refactor HTML output handeling.</li>
<li>Added extra support text to donate page.</li>
<li>Bug fix: Mission planet image was sometimes incorrect rendered.</li>
</ul>';

$notes[63] = '
<div class="subparagraph2">07-01-2014</div>
<i>Game Server v6.3</i>
<ul>
<li>Clan Wars improvements:</li>
<ul>
<li>Added clan bank.</li>
<li>Added clan attack and defense skills.</li>
<li>Sector rebellion starts when a sector is inactive for '.$config["max_sector_inactive"] .' days.</li>
<li>Increase conquered sector hourly income with factor 10.</li>
<li>Commander must now accept clan member join request.</li>
</ul>
<li>Update premium gold features:</li>
<ul>
<li>Added 5 new gold income building types.</li>
<li>Added 5 new gold energy building types.</li>
<li>Added 5 new gold discount building types.</li>
<li>Added 5 new gold maintenance building types.</li>
<li>Added yellow border to gold unit and building images.</li>
</ul>
<li>Added Alliance-Promotion page:</li>
<ul>
<li>Like WarQuest on Facebook and receive free gold.</li>
<li>Invite friends by email and receive free gold.</li>
</ul>
<li>Improve release notes information navigation.</li>
<li>Improve background option selector (Home-Settings).</li>
<li>Added option to change easy login page background style.</li>
<li>Disable christmas / new year announcement.</li>
<li>Decrease experience value of level 280 till 299.</li>
<li>Updated copyright footer.</li>
<li>Bug fix: Corrected one Neptune mission level!</li>
<li>Bug fix: Neptune army strength calculation is now correct!</li>
</ul>';

$notes[62] = '
<div class="subparagraph2">23-12-2013</div>
<i>Game Server v6.2</i>
<ul>
<li>Added planet Neptune:</li>
<ul>
<li>with new 40 unit types.</li>
<li>with new 36 building types.</li>
<li>with new 72 missions.</li>
<li>features are available from level 250 till 299.</li>
<li>adapted game engine to support new planet.</li>
</ul>
<li>Rename asteroid to mercury planet.</li>
<li>Update most citizens images.</li>
<li>Rebalance earth, moon, mars and mercury units / buildings.</li>
<li>Increase maximum unit amount to 5500.</li>
<li>Increase maximum building amount to 645.</li>
<li>Added admin overview clan war map page.</li>
<li>Enable christmas / new year announcement.</li>
</ul>
<br/>

<i>FireFoxOS Client v1.1</i>
<ul>
<li>Bugfix: Disable full screen mode.</li>
<li>Released app on marketplace.firefox.com</li>
</ul>';

$notes[61] = '
<div class="subparagraph2">11-12-2013</div>
<i>Game Server v6.1</i>
<ul>
<li>Clan Wars improvements:</li>
<ul>
<li>Added hourly income to each conquered sectors.</li>
<li>An inactive clan member is removed from a clan after '.$config["max_clan_member_inactive"].' days.</li>
<li>An inactive clan is removed after '.$config["max_clan_inactive"].' days.</li>
</ul>
<li>Added dynamic screen size css to support Firefox OS.</li>
<li>Added FireFoxOS marketplace button on login page.</li>
<li>Added gift shop to Help-Donate page.</li>
<li>Improve Release-Notes page layout.</li>
<li>Improve Stats page layout.</li>
<li>Added sound effects to mission and help pages.</li>
<li>Remove Ads functionality (not used for long time).</li>
<li>Added database layer unit tests to improve stability.</li>
<li>Rename planet numbers to improve source code quality.</li>
<li>Bug fix: Planet switch on clan list page is now working correct.</li>
<li>Bug fix: Fixed vote exploit!</li>
</ul>
<br/>

<i>FireFoxOS Client v1.0</i>
<ul>
<li>Create FirefoxOS webapp.</li>
<li>Released app on marketplace.firefox.com</li>
</ul>';

$notes[60] = '
<div class="subparagraph2">02-12-2013</div>
<i>Game Server v6.0</i>
<ul>
<li>Clan Wars improvements:</li>
<ul>
<li>Added bonus to each won clan war fight.</li>
<li>Added clan slogan.</li>
<li>Mininal clan size is now set to '.$config["min_clan_size"].' during fights.</li>
<li>Rebalance earth, moon, mars and mercury units and buildings.</li>
<li>Limit map access to neighbor sectors which are already conquered.</li>
<li>Unlock clan wars at level 15.</li>
</ul>
<li>Update javascripts to support IE 6, 7, 8, 9 and 10.</li>
<li>Added gold promotion banner to home page.</li>
<li>Replace all magic event numbers with constants in source code.</li>
<li>Improve security of all POST / GET actions.</li>
</ul>';

$notes[59] = '
<div class="subparagraph2">25-11-2013</div>
<i>Game Server v5.9</i>
<ul>
<li>Added premium gold features:</li>
<ul>
<li>Added 16 gold defence buildings.</li>
<li>Added 16 gold units.</li>
<li>Gold units & buildings are immortal.</li>
<li>Added gold information to game banner.</li>
<li>Updated help and donation page information.</li>
<li>Updated admin page to process manual gold donations.</li>
<li>All existing players receive 500 gold as introduction bonus.</li>
<li>Existing trade points are converted to gold (ratio 1:'.$config["gold_dollar_ratio"].').</li>
<li>Trade features are now payed with gold instead of trade points.</li>
<li>Added gold use to Help -> Stats page.</li>
</ul>
<li>Added building defence submenu for better overview.</li>
<li>Removed weakest cavalry units to make a shorter list.</li>
</ul>';

$notes[58] = '
<div class="subparagraph2">21-11-2013</div>
<i>Game Server v5.8</i>
<ul>
<li>Added clan wars functionality to WarQuest:</li>
<ul>
<li>Added bonus to conquer sector event.</li>
<li>Added Battle -> Clan-Wars battle page.</li>
<li>Added Alliance -> Clan configuration page.</li>
<li>Update Help -> Instruction page.</li>
<li>Update Player -> Profile page.</li>
</ul>
<li>Added third casino game: Tic Tac Toe.</li>
<li>Added sound effects to casino games.</li>
<li>Added email check to activate mail notifications.</li>
<li>Improve WarQuest email layout. Now completly HTML based.</li>
<li>Battle sounds functionality is now based on HTML5 standard.</li>
<li>Mission maps support now direct jump to mission page.</li>
<li>Rebalance earth unit & building defense / attack values.</li>
<li>Bug fix: Create SessionId functionality is now transaction proof.</li>
</ul>
<br/>

<i>Windows Client v1.5</i>
<ul>
<li>Added HTML5 sound support.</li>
<li>Upgraded QT libraries to v5.1.1</li>
<li>The app was build with QtCreator v2.8.1</li>
<li>Released app on www.plaatsoft.nl</li>
</ul>';

$notes[57] = '
<div class="subparagraph2">8-11-2013</div>
<i>Game Server v5.7</i>
<ul>
<li>Pickup WarQuest development again :)</li>
<li>Optimize mission planet images. Reduce filesize to improve load time.</li>
<li>Increase maximum level to 279.</li>
<li>Removed sun features.</li>
<li>Improve database optimize. (Admin mode).</li>
<li>Added backup cron  job.</li>
<li>Update jquery to 10.2.0.</li>
<li>Update jquery-ui to 10.3.0.</li>
<li>update jquery-css smooth to 10.3.0.</li>
<li>Added server php source code to google code.</li>
</ul>';

$notes[56] = '
<div class="subparagraph2">07-02-2013</div>
<i>Game Server v5.6</i>
<ul>
<li>Fixed bug in stock exchange buy functionality.</li>
<li>Increase maximum level to 275.</li>
<li>Updated copyright banner.</li>
<li>Added ban user optional. To lock cheater account (Admin mode).</li>
</ul>';

$notes[55] = '
<div class="subparagraph2">14-07-2012</div>
<i>Game Server v5.5</i>
<ul>
<li>Added spanish translation. Thanks Algarobo!</li>
<li>Added romanian translation. Thanks Prepa!</li>
<li>Added eight extra levels</li>
</ul>';

$notes[54] = '
<div class="subparagraph2">07-06-2012</div>
<i>Game Server v5.4</i>
<ul>
<li>Added country selection box to settings page.</li>
<li>Space character(s) in nickname is not allowed anymore!</li>
<li>Now setting a bounty is rewarded with one expercience point.</li>
<li>Added sun planet (more is coming soon)</li>
<li>Added two extra levels.</li>
<li>Added total hourly income information to player profile page.</li>
<li>Added planet mission bonus information to Help page.</li>
<li>Added option to switch from MySql to PostGreSQL database.</li>
<li>Added query counter information in footer.</li>
<li>Added loosely coupled database layer.</li>
<li>Added WarQuest for Linux hyperlink on login page.</li>
<li>Robots now random sell units / buildings. Make them less strong.</li>
<li>Improve Latest forum query on home page. 10 times faster :)</li>
<li>Improve two cron jobs for better performance.</li>
<li>Bug fix: Citizens are now showed again in player profile.</li>
<li>Bug fix: Bots counter attack cash win is limited to max 1.5 billion.</li>
<li>Bug fix: Mars bonus is now 999 billion.</li>
</ul>
<br/>

<i>Linux Client v1.0</i>
<ul>
<li>First release of WarQuest linux client.</li>
<li>Use QT library 4.8.1 for Linux as engine.</li>
<li>The app was build with QtCreator v2.4.1</li>
<li>Released app on Ubuntu software center.</li>
</ul>';

$notes[53] = '
<div class="subparagraph2">20-05-2012</div>
<i>Game Server v5.3</i>
<ul>
<li>Activated improved holiday mode.</li>
<li>Added following option to setting page:<br/>
<ul>
<li>Enable allies in battle and bounty hunting list.</li>
<li>Disable battle bot news.</li>
</ul>
<li>Improve unit and building menu.</li>
<li>Disable page reload after battle force selected.</li>
<li>Improve forum performance.</li>
<li>Refactor page handler events.</li>
<li>Refactor popup messages.</li>
<li>Refactor menu item.</li>
<li>Refactor post parameter handler.</li>
<li>Planet mission complet bonus is now automatic added!</li>
<li>Add extra database index for better performance.</li>
<li>Improve bad word filter!</li>
<li>Limit maximum battle cash win.</li>
<li>Bug fix: Increase alliance size above max with back button is fixed.</li>
<li>Bug fix: Minor level experience range updated.</li>
<li>Bug fix: Army defense profile overview mismatch resolved.</li>
<li>Bug fix: Exploit with back button on building / unit page fixed.</li>
</ul>';

$notes[52] = '
<div class="subparagraph2">22-04-2012</div>
<i>Game Server v5.2</i>
<ul>
<li>Now manage warquest wishlist on www.plaatsoft.nl/scrumboard.</li> 
<li>Bank transaction log is now cleared after 30 days.</li>
<li>Added basic bad words filter to forum.</li>
<li>Disabled holiday mode because of heavy abuse.</li>
<li>Update bounty award scheme.</li>
<li>Merge earth soldiers units in to earth Cavalry units.</li>
<li>Added surrender flag functionality to Home-News page.</li>
<li>German translation update. Thanks TestBoy.</li>
<li>Added minimal trade timer information to trade page.</li>
<li>Bug fix: Improve bank interest cron job performance with factor 10.</li>
<li>Bug fix: PDF report is now working again.</li>
<li>Bug fix: Home-News contain now correct information for all sitations.</li>
</ul>';

$notes[51] = '
<div class="subparagraph2">04-04-2012</div>
<i>Game Server v5.1</i>
<ul>
<li>Image directory structure updated.</li>
<li>Improve player profile page (Admin mode).</li>
<li>Cache data layer added for better database performance.</li>
<li>Added account reset (Home-Settings) feature.</li>
<li>Added trade points (Home-Trade) functionality.</li>
<ul>
<li>Donations are now rewarded with trade points.</li>
<li>Default health, energy, ammo timer value +/<li>10% increased.</li>
</ul>
<li>Remove Login-Manual page.</li>
<li>Improve restore notifications.</li>
<li>Added ten more battle awards.</li>
<li>Added amount selection to skill point page.</li>
<li>Bug fix: Level 259 battle range corrected.</li>
<li>Bug fix: Level 249 now needs 10.000 expercience points.</li>
<li>Bug fix: Fix some small graphical issues.</li>
<li>Bug fix: Soldier attack force option disabled again in battle area.</li>
</ul>';

$notes[50] = '
<div class="subparagraph2">24-03-2012</div>
<i>Game Server v5.0</i>
<ul>
<li>Resync levels.</li>
<ul>
<li>Earth levels are now 0-99.</li>
<li>Moon levels are now 100-149.</li>
<li>Mars levels are now 150-199.</li>
<li>Mercury levels are now 200-249.</li>
</ul>
<li>Added italian translation. Thanks ZennCore.</li>
<li>Added 0.75 day cease fire option.</li>
<li>Maximun unit amount per type increase to 5.000.</li>
<li>Battle news (Home-News) contains now only last two days.</li>
<li>Added travel option to alliance and help page.</li>
<li>Added player profile building discount and maintenance detail page.</li>
<li>Breaking news content is now always english.</li>
<li>Default sorting alliance invite is change to last active on top.</li>
<li>Bug fix: Cash flow detail pages now support planet switch.</li>
<li>Bug fix: Player profile detail page planet switch is now working correct.</li>
</ul>';

$notes[49] = '
<div class="subparagraph2">15-03-2012</div>
<i>Game Server v4.9</i>
<ul>
<li>Improve planet navigation.</li>
<ul>
<li>Planet icon is now the travel button.</li>
<li>Travel option added to mission, battle and units page.</li>
<li>Travel option added to buildings and player profile page.</li>
<li>Remove travel link on lower part of home page.</li>
</ul>
<li>Added planet mercury:</li>
<ul>
<li>with 72 missions.</li>
<li>with 49 building types.</li>
<li>with 40 unit types.</li>
<li>Added level 275 up to 299.</li>
</ul>
<li>Update Mars unit names.</li>
<li>Building lost configuration moved to database.</li>
<li>Improve english translation. Thanks zenncorE.</li>
<li>Move building configuration complete to database.</li>
<li>Added cease fire period of one day.</li>
<li>Added holiday mode (Home -> Restore).</li>
<li>Bug fix: Help-Level page. First expercience entry now correct.</li>
<li>Bug fix: Cooldown period after cease fire and holiday restored.</li>
</ul>';

$notes[48] = '
<div class="subparagraph2">10-03-2012</div>
<i>Game Server v4.8</i>
<ul>
<li>Added planet Mars:</li>
<ul>
<li>with 72 missions.</li>
<li>with 49 building types.</li>
<li>with 40 unit types.</li>
</ul>
<li>Added level 222 up to 275.</li>
<li>Added german translation. Thanks TestBoy.</li>
<li>Improve dutch translation. Thanks wplaat.</li>
<li>Added battle range information to lower part of battle page.</li>
<li>Updated WarQuest for symbian login banner hyperlink.</li>
<li>Moon features start level moved from 150 to 125.</li>
<li>Player profile page shows now general and planet specific info.</li>
<li>Update moon building and unit images.</li>
<li>Improve audit trail.</li>
<li>Bug fix: Fix several bugs related to new mars features.</li>
</ul>';

$notes[47] = '
<div class="subparagraph2">01-03-2012</div>
<i>Game Server v4.7</i>
<ul>
<li>Added custom cease fire period.</li>
<li>Added level overview page (Help-Levels).</li>
<li>Added personal stocklist (Money-StockExchange-Personal).</li>
<li>Added stock sell transaction fee.</li>
<li>Added more online help for new players.</li>
<li>Improve Player-Message page layout.</li>
<li>Now Player-News contain information up to 15 days old.</li>
<li>Added surrender flag feature to Battle-Bounty hunting page.</li>
<li>Added bounty action to player profile page.</li>
<li>Each vote is rewarded with 10 experience points.</li>
<li>Added WarQuest for Symbian banner to login page.</li>
<li>Now you can fight players also from your own country.</li>
<li>Optimise game engine for Symbian Mobile devices.</li>
<li>Bounty hunting skill points loss reduced with 50%.</li>
<li>Improve Forum-Poll sorting.</li>
<li>Added symbian platform detection.</li>
<li>Improve technical info page (Admin mode).</li>
<li>Bug fix: Bounting Hunting range at level 220 is now working fine.</li>
</ul>
<br/>

<i>Windows Client v1.4</i>
<ul>
<li>Added intro screen.</li>
<li>Use QT library 4.7.4 for Windows as engine.</li>
<li>The app was build with QtCreator v2.4.1.</li>
<li>Released app on freewarefiles.com.</li>
</ul>
<br/>

<i>Symbian Client v1.0</i>
<ul>
<li>Added intro screen.</li>
<li>Added automatic sign on.</li>
<li>Added automatic screen resolution detection.</li>
<li>Added game screen based on QtWebKit.</li>
<li>Use QT library 4.7.3 for Symbian as engine.</li>
<li>The app was build with QtCreator v2.4.1.</li>
<li>Released app on OviStore.</li>
</ul>';

$notes[46] = '
<div class="subparagraph2">15-02-2012</div>
<i>Game Server v4.6</i>
<ul>
<li>Added twitter account setting to settings page.</li>
<li>Show last player tweet on player profile.</li>
<li>Stock amount is now a free input field with suggestion box.</li>
<li>Improve unit loot functionality.</li>
<li>Disable restore / repair notification in main menu.</li>
<li>Increase all spacecrafts defense strength.</li>
<li>Moon energy building price decrease with factor 10.</li>
<li>Warrior hourly cost increase. They were to cheap.</li>
<li>Added 12 moon discount buildings.</li>
<li>Added 10 moon maintenance buildings.</li>
<li>Added "Warrior 11" and "Galaxy Explorer II" moon unit.</li>
<li>Added "No region for rebellion available" detection.</li>
<li>Remove some english typos.</li>
<li>Bounty hunting player list functionality changed:</li>
<ul>
<li>Players under level 150 see only players under level 150.</li>
<li>Players from level 150 see only players from level 150.</li>
</ul>
<li>Added setting "Enable oldest battle player on top at battle list".</li>
<li>Bug fix: Improve header for players in level 220.</li>
<li>Bug fix: Opening chat does not take you back to earth anymore.</li>
</ul>';

$notes[45] = '
<div class="subparagraph2">09-02-2012</div>
<i>Game Server v4.5</i>
<ul>
<li>Battle page contain now random player selection.</li>
<li>Added rebellion rise and bounty set awards.</li>
<li>Updated home award section and help award page.</li>
<li>Added more cyberspace players in higher levels.</li>
<li>Added five more battle awards.</li>
<li>Improve player search (Admin mode).</li>
<li>Integrated Twitter functionality. (Admin mode).</li>
<li>Change battle range algoritme. Now more players are in range.</li>
<li>Added forum topic search.</li>
<li>Cron job functionality:</li>
<ul>
<li>Added "Sell some units of players with negative hourly income".</li>
<li>Optimize some queries for better performance.</li>
</ul>
<li>Health restore timer inactive period decreased to 5 minutes.</li>
<li>Improve cyberspace robots intelligence:</li>
<ul>
<li>Robot get a live when attacked.</li>
<li>Robot buy automatic new units and buildings.</li>
<li>Robot income period is extended with 24 hours after an attack.</li>
<li>Robot trade-in received skill points.</li>
<li>Robot withdraw automatic money for bank accounts.</li>
<li>Robot counter attack smart. So be aware! :)</li>
</ul>
<li>Bug fix: Player battle news contain now always correct army type.</li>
<li>Bug fix: Rebalance some defense values of moon units.</li>
<li>Bug fix: Battle loot is now working correct!</li>
<li>Bug fix: Ranking place on home is now always correct.</li>
<li>Bug fix: Remove typo from home screen.</li>
<li>Bug fix: Remove double player profile on chat page.</li>
<li>Bug fix: Rebellion on moon popup information is now right.</li>
</ul>';

$notes[44] = '
<div class="subparagraph2">03-02-2012</div>
<i>Game Server v4.4</i>
<ul>
<li>Improve english translation. Thanks Mongoose.</li>
<li>Added 4 moon explorers defense buildings.</li>
<li>Improve registration functionality.</li>
<li>Added new leaderboard ranking sort ((experience/30)+won-lost).</li>
<li>Added loot feature to battle.</li>
<li>Added functionality to disabled an old poll.</li>
<li>Bounty rules of engagement changed. Old situation restored.</li>
<li>Added WarQuest One Year Party functionality.</li>
<li>Visit WarQuest on 8 february 2012 to received a present!</li>
<li>Bug fix: Skill points counter in submenu is now working fine again.</li>
<li>Bug fix: Notification in Main Menu is not working correct.</li>
</ul>
<br/>

<i>Android Client v2.6</i>
<ul>
<li>Improve about screen.</li>
<li>Released app on Android Market.</li>
</ul>';

$notes[43] = '
<div class="subparagraph2">25-01-2012</div>
<i>Game Server v4.3</i>
<ul>
<li>Added basic chatroom.</li>
<li>Standardized player name format (name + country flag).</li>
<li>Added 12 explorer moon units (same skills as espionage units).</li>
<li>Bounty hunting is now more restricted. See help instructions.</li>
<li>Refactor menu. Now forum is available in main menu.</li>
<li>After the earth the moon can be now conquered.</li>
<li>Added 37 moon units, 35 moon buildings and 72 moon missions.</li>
<li>Added "Travel to Moon" link on home page.</li>
<li>Player-Profile shows information about your current location.</li>
<li>Force strength is now realtime calculated.</li>
<li>Added one to one relation between units and army battle forces.</li>
<li>Optimize overall performance.</li>
<li>Bank page layout optimized.</li>
<li>Disable set bounty on cyberspace players.</li>
<li>Moon map is now clickable.</li>
<li>Bug fix: Player with only space characters in nickname can now be selected.</li>
<li>Bug fix: Now classified opponent profile is working again.</li>
<li>Bug fix: Resolve some small graphical issues.</li>
</ul>';

$notes[42] = '
<div class="subparagraph2">17-01-2012</div>
<i>Game Server v4.2</i>
<ul>
<li>Redesign Home-Setting page.</li>
<li>Added forum message sort option to setting page.</li>
<li>Added 8 hour cooldown period after using cease fire option.</li>
<li>Added bounty set and receive counter to player profile.</li>
<li>Added Cease Fire information to player profile.</li>
<li>Added basic poll (Alliance-Polls) functionality.</li>
<li>Added database tables optimize action (Admin mode).</li>
<li>Improve member search functionality (Admin mode).</li>
<li>Added five extra battle won awards.</li>
<li>Added country flag to Forum-Topic-Messages.</li>
<li>Increase battle and bounty hunting player list to max. 30 entries.</li>
<li>Bug fix: Optimize some queries for better performance.</li>
<li>Bug fix: Mission loot is now mission level related.</li>
</ul>';

$notes[41] = '
<div class="subparagraph2">12-01-2012</div>
<i>Game Server v4.1</i>
<ul>
<li>Split bounty / restore & repair popup configuration.</li>
<li>Added more cyberspace robots to have more fun!.</li>
<li>Added facebook subpage to login page.</li>
<li>Created www.facebook.com/WarQuest page.</li>
<li>Improve login page.</li>
<li>Added rebellion peace restore (Home-Restore) functionality.</li>
<li>Added optional Rebel Condition (RC) to banner.</li>
<li>Added rebellion chance information to espionage battle page.</li>
<li>Added breaking news information to login page.</li>
<li>Added technical environment settings page. (Admin Mode)</li>
<li>Added worldmap to mission complete message.</li> 
<li>Espionage rob bank selection improved.</li>
<li>Bug fix: Create cyberplayer is now working correct.</li>
<li>Bug fix: Reload casino cheating action.</li>
<li>Bug fix: New client version detection improved.</li>
<li>Bug fix: Remove some typos in unit names.</li>
</ul>';

$notes[40] = '
<div class="subparagraph2">05-01-2012</div>
<i>Game Server v4.0</i>
<ul>
<li>Improve english translation. Thanks Mongoose!</li>
<li>Redesign mission functionality:</li>
<ul>
<li>Worldmap is now split in 64 regions with can be conquered.</li>
<li>Each conquered continent will increase your hourly income.</li>
<li>Added Continent Income Overview page.</li>
<li>Attack opponents with espionage to invoke rebellion by opponent.</li>
<li>Region rebellion result in postpone continent income.</li>
<li>Mission names renamed!</li>
<li>Added worldmap region color indication:</li>
<ul>
<li>Green = Region 0% conquered.</li>
<li>Yellow = Region 33% conquered.</li>
<li>Purple = Region 66% conquered.</li>
<li>Orange = Region 100% conquered.</li>
<li>Red = Rebellion in region. Region must be reconquered.</li>
</ul>
</ul>
<li>Added casino played game statistics.</li>
<li>Added optional lastest forum post on home overview page.</li>
<li>Added more win chance to slotmachine.</li>
<li>Added five extra battle won awards.</li>
<li>Bug fix: Mission loot contain now no citizens anymore.</li>
<li>Bug fix: Remove some typo\'s in Help-Instructions.</li>
<li>Bug fix: Bounty Hunting battle SQL error fixed.</li>
<li>Bug fix: Worldmap is now not clickable anymore for level 0.</li>
</ul>
<br/>

<i>Android Client v2.5</i>
<ul>
<li>Improve about box.</li>
<li>Released app on Android Market.</li>
</ul>';


$notes[39] = '
<div class="subparagraph2">31-12-2011</div>
<i>Game Server v3.9</i>
<ul>
<li>Improve Help-Instructions page content.</li>
<li>Battle-BountyHunting list is not level constrained anymore.</li>
<li>Added Happy New Year banner.</li>
<li>Added star background with firework animation.</li>
<li>Improve change username and/or password functionality.</li>
<li>Added optional units condition (UC) & buildings condition (BC) in banner.</li>
<li>Added slotmachine with help page to casino.</li>
<li>Disabled christmas banner on Home page.</li>
<li>Improve mail notification in banner.</li>
<li>Added unit & building repair notification.</li>
<li>Bug fix: Fix cheating bug in casino games.</li>
<li>Bug fix: Remove typo in home intro text.</li>
<li>Bug fix: Prevent negative units/buildings condition value.</li>
</ul>';

$notes[38] = '
<div class="subparagraph2">24-12-2011</div>
<i>Game Server v3.8</i>
<ul>
<li>Added 9 more battle awards.</li>
<li>Added confirmation popup functionality:</li>
<ul>
<li>Enable popup on the Page-Settings page.</li>	
<li>Added popup to restore & repair actions.</li>
<li>Added popup to set bounty action.</li>
</ul>
<li>Added Help-Statistics page.</li>
<li>Merge Help-About and Credit page.</li>
<li>Added cease fire functionality. See Home-Restore page.</li>
<li>Added unit and building speedbar for fast amount selection.</li>
<li>Attack & defense skillpoints strength depend now on player level.</li>
<li>Added sleeping smiley. Used for feature request on hold.</li>
<li>Adapted losing money color in Player-News page.</li>
<li>Added cash bonus:</li>
<ul>
<li>when battle opponent surrender temporary.</li>
<li>when battle awards is won.</li>
<li>when level is cleared.</li>
</ul>
<li>Added pending alliance request is cleared after 2 days.</li>
<li>Added more the 350 extra cyber robot players.</li>
<li>Added Health, Energy and Ammo countdown timer.</li>
<li>Added contact areas on mission Worldmap.</li>
<li>Added christmas background with falling snowflakes animation.</li>
<li>Bug fix: Army attack & defense strength calculate is now correct.</li>
</ul>
<br/>

<i>Android Client v2.4</i>
<ul>
<li>Maintenance release.</li>
<li>Released app on Android Market.</li>
</ul>';

$notes[37] = '
<div class="subparagraph2">16-12-2011</div>
<i>Game Server v3.7</i>
<ul>
<li>Added Player-Restore page:</li>
<ul>
<li>Energy and Ammo can now be restored directly.</li>
<li>This option can only be used once every 24 hours.</li>
<li>Units and buildings are damaged during battles.</li>
<li>Units and buildings can now be repaired directly.</li>
</ul>
<li>Improve Forum:</li>
<ul>
<li>Topic sorting improved. Newest topic/message is now on top.</li>
<li>Added National Communities Forum.</li>
<li>Added paginating to Topic page.</li>
<li>Added topic description in message section.</li>
<li>Forum image is now clickable.</li>
</ul>
<li>Adbrite Ads disabled, to poor revenue.</li>
<li>Now login username/password can be changed.</li>
<li>Added extra background "Chocolate".</li>
<li>Added four Espionage defense buildings.</li>
<li>Added thumbs up and thumbs down smilies.</li>
<li>Added column sorting to all leaderbord and alliance pages.</li>
<li>Optimize menu structure. Merge Player and Home menu.</li>
<li>Bug fix: Remove some typos in the text across the game.</li>
<li>Bug fix: Last two awards are now working correct.</li>
</ul>
<br/>

<i>Android Client v2.3</i>
<ul>
<li>Improve app text tags.</li>
<li>Released app on Android Market.</li>
</ul>';

$notes[36] = '
<div class="subparagraph2">09-12-2011</div>
<i>Game Server v3.6</i>
<ul>
<li>Added Last Active column to Alliance-Invite page.</li>
<li>Filter out WarQuest robot (cyberspace) players in leaderboards.</li>
<li>Center game page in Ms. Internet Explorer browsers.</li>
<li>Improve PayPal Donate button integration.</li>
<li>Added white surrender flag to players with low health on battle field.</li>
<li>Added lightweight message forum.</li>
<li>Added experimental sound effect setting (default disabled).</li>
<li>Added battle sounds to Battle page. Only works with windows browsers.</li>
<li>Added hide shortcut links in banner for faster navigation:</li>
<ul>
<li>Click "Money" to navigate to player leaderboard page..</li>
<li>Click "Exp." to navigate to country leaderboard page.</li>
<li>Click "Level" to navigate to player messages.</li>
<li>Click "Health" to navigate to hospital page.</li>
<li>Click "Energy" to navigate to player profile page.</li>
<li>Click "Ammo" to navigate to skill points page.</li>
</ul>
<li>Added create and last login date to Player-Profile page.</li>
<li>Bug fix: Alliance invite table offset is maintain during invite action.</li>
<li>Bug fix: Alliance accepted table offset is maintain during drop action.</li>
<li>Bug fix: Corrected some small graphical issues in Ms. Internet Explorer.</li>
</ul>
<br/>

<i>Android Client v2.2</i>
<ul>
<li>Exit app is now working correct when there is no internet connection.</li>
<li>Released app on Android Market.</li>
</ul>';

$notes[35] = '
<div class="subparagraph2">03-12-2011</div>
<i>Game Server v3.5</i>
<ul>
<li>Improve espionage functionality:</li>
<ul>
<li>Split attack and defense strength pre espionage unit type.</li>
<li>Espionage strength depends now on alliance size.</li>
<li>Added Espionage update action (Admin mode)</li>
<li>Espionage unit type amount increase to maximum 4.000.</li>
</ul>
<li>Added best player leaderboard column sorting.</li>
<li>Improve mission unit lost.</li>
<li>Added black background color.</li>
<li>Added Help-Donate page.</li>
<li>Improved background image 4.</li>
<li>Improve alliance pages. Split accepted and pending allies.</li>
<li>Optimise Ads locations.</li>
<li>Added Ad count graph (Admin mode).</li>
<li>Log admin actions in audit trail (Admin mode).</li>
<li>Log database errors in audit trail (Admin mode).</li>
<li>Bug fix: Added word wrap to truncate long comments.</li>
</ul>
<br/>

<i>Android Client v2.1</i>
<ul>
<li>Added back button functionality.</li>
<li>Released app on Android Market.</li>
</ul>
<br/>

<i>Windows Client v1.3</i>
<ul>
<li>Added https support.</li>
<li>Now PayPal donate button is working.</li>
<li>Use QT library 4.7.4 as engine.</li>
<li>The app was build with QtCreator v2.3.0.</li>
<li>Released app on freewarefiles.com.</li>
</ul>';

$notes[34] = '
<div class="subparagraph2">24-11-2011</div>
<i>Game Server v3.4</i>
<ul>
<li>Added bonus deposit to National Bank (Admin mode).</li>
<li>Added WarQuest client upgrade detection.</li>
<li>Added clean battle and bank log cron job.</li>
<li>Improve Player-Settings page:</li>
<ul>
<li>You must enable manually alliance email notifications.</li>
<li>You must enable manually comment email notifications.</li>
</ul>
<li>Added strong password indicator.</li>
<li>Added level 201 until 220.</li>
<li>Added background information for some units.</li>
<li>Bank interest is now paid every day (cron job).</li>
<li>Encrease daily bonus.</li>
<li>Resort units to have a more logical build-up.</li>
<li>Improve link and source code encryption.</li>
<li>Activate AdBrite Ad in footer for non Android players.</li>
<li>Ad income is used to fund the web hosting.</li>
<li>Bug fix: WheelOfFortune cheating not possible anymore.</li>
<li>Bug fix: Player with long session (>24h) receive daily bonus again.</li>
<li>Bug fix: Added TCP/IP web service shorter timeout.</li>
</ul>
<br/>

<i>Android Client v2.0</i>
<ul>
<li>Added workarround to resolve critical freeze problem.</li>
<li>Exit button event cleanups cache and kills app completly.</li>
<li>Released app on Android Market.</li>
</ul>
<br/>

<i>Windows Client v1.2</i>
<ul>
<li>Added support to visit external urls.</li>
<li>Added support for file transfer.</li>
<li>Use QT library 4.7.4 as engine.</li>
<li>The app was build with QtCreator v2.3.0.</li>
<li>Released app on freewarefiles.com.</li>
</ul>';

$notes[33] = '
<div class="subparagraph2">19-11-2011</div>
<ul>
<i>Game Server v3.3</i>
<li>Improve Player-Profile page:</li>
<ul>
<li>Added Stock Exchange asset information.</li>
<li>Split building image type section.</li>
<li>Added alliance invite link.</li>
<li>Improve PDF report.</li>
</ul>
<li>Added new buildings:</li>
<ul>
<li>10 maintenance buildings.</li>
<li>2 energy buildings.</li>
<li>3 discount buildings.</li>
</ul>
<li>Buy maintenance buildings to reduce unit damage during battles.</li>
<li>Added meta html data to login page.</li>
<li>Added alliance size information to banner.</li>
<li>Added Help-Credits page.</li>
<li>Added Cook and Security Guard citizen.</li>
<li>Disable building citizens panel. Less is more</li>
<li>Added Ads to lower part of page. Functionality is still disabled.</li>
<li>Added session take over functionality for better debugging (Admin Mode).</li>
<li>Bug fix: Espionage battle bonus is now always correct.</li>
<li>Bug fix: Battle unit lost contain now only active units.</li>
<li>Bug fix: Army fights do not contain citizens units anymore.</li>
<li>Bug fix: Robot attack message contain now always correct army type.</li>
<li>Bug fix: WarQuest client version detection is now working again.</li>
</ul>
<br/>

<i>Android Client v1.9</i>
<ul>
<li>Maintenance release.</li>
<li>Released app on Android Market.</li>
</ul>';

$notes[32] = '
<div class="subparagraph2">10-11-2011</div>
<i>Game Server v3.2</i>
<ul>
<li>Created new session handler:</li>
<ul>
<li>When IP address change during session you are not logout anymore.</li>
<li>No client cookie needed anymore.</li>
<li>Session inactivity timeout set to 351 days.</li>
<li>Only one active session per player account allowed.</li>
</ul>
<li>Espionage functionality adapted:</li>
<ul>
<li>Opponent information is unlocked when your intelligence is higher.</li>
<li>Protect your own information by buying more espionage units.</li>
<li>Added classified dialog box.</li>
<li>Espionage units can now steal from the Trasquera and SwissCore bank.</li>
</ul>
<li>Added multi units lost during battle.</li>
<li>Added platform & browser information to Player-Profile page.</li>
<li>Replace all html buttons with links. Improve uniform look and feel.</li>
<li>Added maximum amount per unit type.</li>
<li>Improve unit and building buy/sell dialog.</li>
<li>Resolve several small graphical issues.</li>
<li>Improve home page for new players. Less is More :)</li>
<li>Improve debug trace.</li>
<li>Improve browser overview (Admin mode)</li>
<li>Bank interest rate is now different for each bank.</li>
</ul>
<br/>

<i>Android Client v1.8</i>
<ul>
<li>Refactor source code.</li>
<li>Released app on Android Market.</li>
</ul>';

$notes[31] = '
<div class="subparagraph2">06-11-2011</div>
<i>Game Server v3.1</i>
<ul>
<li>Added espionage functionality:</li>
<ul>
<li>Added 12 espionage units.</li>
<li>Added detail espionage strength calculation page.</li>
<li>Player details page info depends now on espionage strength.</li>
<li>More is coming soon :)</li>
</ul>
<li>Redesign Home-Messages page:</li>
<ul>
<li>Now you can reply on received messages.</li>
<li>You can edit / delete send messages.</li>
</ul>
<li>Improve unit, building and stock buy/sell dialog.</li>
<li>Now posted comments can be edit.</li>
<li>Added skill point trade-in functionality to Player-Skills page.</li>
<li>Updated deployed player skill points values.</li>
<li>Added six extra battle awards.</li>
<li>Increase building income.</li>
<li>Update unit defense values to get better attack/defense balance.</li>
<li>Added mission statistics graph (Admin mode).</li>
<li>Improve breaking news input form (Admin mode).</li>
</ul>
<br/>

<i>Android Client v1.7</i>
<ul>
<li>On exit (submenu button) all cached files are deleted.</li> 
<li>This prevents error pages to be reloaded for the cache.</li>
<li>Released app on Android Market.</li>
</ul>';

$notes[30] = '
<div class="subparagraph2">27-10-2011</div>
<i>Game Server v3.0</i>
<ul>
<li>Added to home page amount of online players last 24 hours.</li>
<li>Rank names updated (Thanks scout702 for the information).</li>
<li>Level 1 is now battle training level.</li>
<li>Added WarQuest player comment rss feed on login page.</li>
<li>Added game statistics graphs (Admin mode).</li>
<li>Improve browser overview report (Admin mode).</li>
<li>Bug fix: Cron is now running every day.</li>
<li>Bug fix: WarQuest clients can not change there password anymore.</li>
</ul>
<br/>

<i>Android Client v1.6</i>
<ul>
<li>Improvement stability.</li>
<li>Released app on Android Market.</li>
</ul>';

$notes[29] = '
<div class="subparagraph2">21-10-2011</div>
<i>Game Server v2.9</i>
<ul>
<li>Complete redesign of building functionality:</li>
<ul>
<li>Each building contain now citizens.</li>
<li>Each citizen has hourly cost.</li>
<li>Added calculate initial player citizen size action (Admin mode)</li>
<li>Improve building transaction messages.</li>
</ul>
<li>Refactor some source code for better performance.</li>
<li>Added hourly cost information to unit popup.</li>
<li>Disable Poker, Roulette and BlackJack casino games.</li>
</ul>
<br/>

<i>Android Client v1.4</i>
<ul>
<li>Maintenance release.</li>
<li>Released app on Android Market.</li>
</ul>';

$notes[28] = '
<div class="subparagraph2">16-10-2011</div>
<i>Game Server v2.8</i>
<ul>
<li>Added "Attack" button to player detail page.</li>
<li>Improve About and Release Notes information.</li>
<li>Remove old Windows client detection. Not needed anymore!</li>
<li>Improve breaking news javascript.</li>
<li>Improve home page for MSIE browsers.</li>
<li>Improve part information of mission.</li>
<li>Added member browser / platform overview page. (Admin mode).</li>
<li>Move css and js files to second content location.</li>
<li>Improve php web server response time.</li>
<li>Html requests on login page are now counted.</li>
<li>Bug fix: Robot does not attack player without ammo anymore.</li>
<li>Disabled html redirect on www.warquest.nl domain.</li>
<li>Introduce info@warquest.nl email contact address for questions.</li>
</ul>
<br/>

<i>Android Client v1.3</i>
<ul>
<li>Added support for Android 2.2 and higher.</li>
<li>Added no internet connection warning.</li>
<li>Bug fix: if internet fails during auto sign-on, no account is created anymore.</li>
<li>App is now using the www.warquest.nl url.</li>
<li>Released app on Android Market.</li>
</ul>
<br/>

<i>Windows Client v1.0</i>
<ul>
<li>Added internet and new version check.</li>
<li>Bug fix: if internet fails during auto sign-on, no account is created anymore.</li>
<li>Use QT library 4.7.4 as engine.</li>
<li>The app was build with QtCreator v2.3.0.</li>
<li>Released app on freewarefiles.com.</li>
</ul>';

$notes[27] = '
<div class="subparagraph2">03-10-2011</div>
<i>Game Server v2.7</i>
<ul>
<li>Added breaking news section to home page.</li>
<li>Battle player list does not show allies anymore.</li>
<li>Improve alliance overview 
<li><li>Not approved allies are now on top of the list.</li>
<li>Optimised some pages for Android client.</li>
<li>Improve release notes layout.</li>
</ul>
<br/>

<i>Android Client v1.1</i>
<ul>
<li>WarQuest app released in the Android market place.</li>
<li>Added app icon.</li>
<li>Added exit, setting and about menu.</li>
<li>Added about and setting page.</li>
<li>Added title bar with load progress bar.</li>
<li>Added automatic sign-on.</li>
<li>Added client version information in first http request.</li>
<li>Added background image on setting and about page.</li>
</ul>';

$notes[26] = '
<div class="subparagraph2">25-09-2011</div>
<i>Game Server v2.6</i>
<ul>
<li>Complete redesign of battle functionality:</li>
<ul>
<li>Now you can fight or bounty hunt other players.</li>
<li>You can set a bounty on someone head on the battle page.</li> 
<li>If the player with bounty is defeated, he will lose some experience points.</li>
<li>Bounty hunting feature is enabled at level 5.</li>
</ul>
<li>Battle attack force selection is now stored.</li>
<li>Added "President Office" discount building.</li>
<li>Added update building discount action (Admin Mode).</li>
<li>Added default picture for robot players.</li>
<li>Added leaderboard position on home page.</li>
<li>Added active country count on login page.</li>
<li>Casino games are now unlocked during the game play.</li>
<li>Unit and building attack / defense values updated.</li>
<li>Player attack / defense strength recalculated.</li>
<li>Enlarge maximum amount of buildings from 450 to 600.</li>
<li>Added full automatic cron jobs.</li>
</ul>
<br/>

<i>Android Client v0.1</i>
<ul>
<li>Start building android WarQuest app.</li>
<li>www.warquest.nl site is automatic loaded.</li>
<li>Full control of game possible.</li>
</ul>';

$notes[25] = '
<div class="subparagraph2">07-09-2011</div>
<i>Game Server v2.5</i>
<ul>
<li>Complete redesign of alliance functionality:</li>
<ul>
<li>Player ally size is now limit to maximum 3 times the player level.</li>
<li>For example: A player in level 11 can have maximum 33 allies.</li>
<li>Remove recruit button on Player-Profile page.</li>
<li>Remove invite friend by email functionality. Was not used!</li>
</ul>
<li>Added user audit trail to detect hack attemps.</li>
<li>Added "Satellite Solar Plant" energy building.</li>
<li>Added "Military Headquarters" discount building.</li>
<li>Improve database indexes. Queries average three times faster.</li>
<li>Admin player now visible again in leaderboards.</li>
<li>Enlarge maximum amount of buildings from 350 to 450.
</ul>
<br/>

<i>Windows Client v0.70</i>
<ul>
<li>Added load progress indication in title bar.</li>
<li>Added reload button to popup menu.</li>
<li>Added icons to popup menu.</li>
<li>Added QT version information on about window.</li>
<li>Use QT library 4.7.4 as engine.</li>
<li>The app was build with QtCreator v2.3.0.</li>
<li>Released app on freewarefiles.com.</li>
</ul>';

$notes[24] = '
<div class="subparagraph2">02-09-2011</div>
<i>Game Server v2.4</i>
<ul>
<li>Added Wheel of Fortune casino game.</li>
<li>Added basic casino functionality. More is coming soon!</li>
<li>Move Logout button to home submenu.</li>
<li>Added more awards with more bonus expercience points.</li>
<li>Update all existing player accounts with new award schema.</li>
<li>Improve award help and skill point page.</li>
<li>Improve worldmap. Sea is now transparant.</li>
<li>Corrected total request count. Robots actions are not counted anymore.</li>
<li>Improve some database queries. Now faster page response.</li> 
<li>Added cleanup battle log action. (Admin mode).</li>
</ul>';

$notes[23] = '
<div class="subparagraph2">25-08-2011</div>
<i>Game Server v2.3</i>
<ul>
<li>Added Nasdaq, DowJones, Aex stock exchange with realtime prices.</li>
<li>Enlarge maximum amount of buildings from 300 to 350.</li>
<li>Improve best country leaderboard (Added total server requests).</li>
<li>Replace robots country name from Europe to Cyberspace.</li>
<li>Added discount buildings. Give building price discount.</li>
<li>Refactor existing buildings.</li>
<li>Added "Nuclair power plant" energy building.</li>
<li>Make source code compliant with the PHP 5.3.x standard.</li>
<li>Added some missing country names.</li>
</ul>';

$notes[22] = '
<div class="subparagraph2">14-07-2011</div>
<i>Game Server v2.2</i>
<ul>
<li>Added update player level action. (Admin mode).</li>
<li>Added robot players up to level 61.</li>
<li>Decrease building prices.</li>
<li>Improve login page. New unit images reload every 2 second.</li>
<li>Enlarge maximum amount of buildings from 200 to 300.</li>
<li>Added extra energy building.</li>
<li>Improve user event logging.</li>
<li>Robot players can now fight back. Be aware!</li>
<li>Improve menu notifications.</li>
</ul>';

$notes[21] = '
<div class="subparagraph2">02-07-2011</div>
<i>Game Server v2.1</i>
<ul>
<li>Added ally icon to Best-Player leaderbord and Battle page.</li>
<li>Improve allies overview page.</li>
<li>Allies can not be attack anymore!</li>
<li>Change default background. Hope everybody like it! :lol:.</li>
<li>Increase battle and bank transaction log size to 30 max entries.</li>
<li>Enabled ranks and awards help page again.</li>
<li>Remove wishlist from release notes. Game is almost full feature!.</li>
<li>Improve source code encryption file format.</li>
<li>Improve login page. Added supported hardware and browsers.</li>
<li>Added page navigation above data tables.</li>
<li>Improved Attack and Defense skill points functionality.</li>
<li>Make game compliant with Android browsers.</li>
<li>Added robot players up to level 45.</li>
<li>Bug fix: Mission loot was not always working fine in high levels.</li>
<li>Bug fix: Money values on apple devices are now correctly displayed.</li>
<li>Bug fix: Now all old WarQuest clients are detected correctly.</li>
</ul>';

$notes[20] = '
<div class="subparagraph2">25-06-2011</div>
<i>Game Server v2.0</i>
<ul>
<li>Reassign robot players to europe "country".</li>
<li>Added robot players up to level 35.</li>
<li>Added semi-automatic robot player alliance acceptance. :lol:.</li>
<li>Improve robot player control page. (Admin mode).</li>
<li>Reorder levels above level 110.</li>
<li>Redesign player skills page.</li>
<li>Improve information box layout.</li>
<li>Added Win/Losts ratio information to player statistics.</li>
<li>Added two income and one extra energy building.</li>
<li>Encrypted PHP code on web server. Protect my IPR!.</li>
<li>Added player building income detail page.</li>
<li>Added player unit hourly cost detail page.</li>
</ul>
<br/>

<i>Windows Client v0.60</i>
<ul>
<li>Canvas window height depends now on real video page size.</li>
<li>Use QT library 4.7.2 as engine.</li>
<li>The app was build with QtCreator v2.0.1.</li>
<li>Released app on freewarefiles.com.</li>
</ul>';

$notes[19] = '
<div class="subparagraph2">20-06-2011</div>
<i>Game Server v1.9</i>
<ul>
<li>Improve loot. Now multiple units can be won.</li>
<li>Improve battle opponent list selection.</li>
<li>Added user event logging for better debugging.</li>
<li>Added player PDF report.</li>
<li>Added counter attack action in Home-Battle News view.</li>
<li>Added wishlist to release notes.</li>
<li>Improve menu navigation.</li>
<li>Improve fight bonus message.</li>
<li>Added tooltip to award images.</li>
<li>Enlarge player message size from 200 to max. 400 characters.</li>
<li>Bug fix: Random strength calculation mismatch resolved.</li>
<li>Bug fix: Random battle lost issue resolved.</li>
<li>Bug fix: Protect battle agains negative money bonus.</li>
<li>Bug fix: Protect missions again negative hourly income.</li>
</ul>';

$notes[18] = '
<div class="subparagraph2">14-06-2011</div>
<i>Game Server v1.8</i>
<ul>
<li>Added last visit message on home page.</li>
<li>Added bank interest. Deposit money generate now also income.</li>
<li>Improve daily bonus message.</li>
<li>Improve mission buy missing units message.</li>
<li>Added Antarctica missions.</li>
<li>Split attack / defense strength in army, cavalry, navy and airforce.</li>
<li>Now you can battle opponents on land, water and/or air.</li>
<li>Added three navy defense buildings.</li>
<li>Improve battle page.</li>
<li>Added custom background image setting.</li>
<li>Improve battle news content and layout.</li>
<li>Decrease some building, unit and hourly prices.</li>
<li>Bug fix: Language setting remains when other setting is change.</li>
</ul>';

$notes[17] = '
<div class="subparagraph2">07-06-2011</div>
<i>Game Server v1.7</i>
<ul>
<li>Added attack / defense strength values to battle page.</li>
<li>Added message if no players are available to fight.</li>
<li>Improve menu bar alignment.</li>
<li>Improve game status bar.</li>
<li>Added player-comments page navigation.</li>
<li>Split home page in three parts. Added submenu.</li>
<li>Added bank images.</li>
<li>Added gravatar player image support.</li>
<li>Improve some unit pictures.</li>
<li>Added level 0. Mission training level.</li>
<li>Added multi language support for country names.</li>
<li>Recruit button is only showed when player is not an ally.</li>
<li>Added render time information in footer.</li>
<li>Added message smilies support :D :lol: :roll:.</li>
<li>Improve page title.</li>
<li>Player can now delete message send to all players.</li>
</ul>';

$notes[16] = '
<div class="subparagraph2">19-05-2011</div>
<i>Game Server v1.6</i>
<ul>
<li>Login page language depends on browser language setting now.</li>
<li>Added language selection to Player-Settings page.</li>
<li>Improve english translation. Thanks suave.</li>
<li>Added dutch translation. Thanks SuperT.</li>
<li>Update about page.</li>
<li>Detect very old WarQuest windows client. Force upgrade!</li>
<li>Remove URL get parameter processing.</li>
<li>Remove jquery dependency. Improve performance 5%.</li>
<li>Added picture to hospital page.
<li>Improve award pictures.</li>
<li>Receive extra skill point when award is won.</li>
<li>Adapted first 10 level transistions.</li>
<li>Bug fix: Hourly cost calculation corrected.</li>
</ul>
<br/>

<i>Windows Client v0.50</i>
<ul>
<li>Rename proxy window to settings window.</li>
<li>Added username and password settings.</li>
<li>Added client version information in first request.</li>
<li>Use QT library 4.7.2 as engine.</li>
<li>The app was build with QtCreator v2.0.1.</li>
<li>Released app on freewarefiles.com.</li>
</ul>';

$notes[15] = '
<div class="subparagraph2">14-05-2011</div>
<i>Game Server v1.5</i>
<ul>
<li>Show unlocked features when next level is reached.</li>
<li>Added two extra energy buildings.</li>
<li>Added one extra defense building.</li>
<li>Added multi language support.</li>
<li>Move all database language labels to resource file.</li>
<li>Improve performance (5% less database queries during game play)</li>
<li>Optimize datamodel.</li>
<li>Added English translation (100% ready).</li>
<li>Improve inline source code documentation.</li>
<li>Optimise CSS for Apple Ipad.</li>
</ul>';

$notes[14] = '
<div class="subparagraph2">04-05-2011</div>
<i>Game Server v1.4</i>
<ul>
<li>Improve mission submenu selection.</li>
<li>Improve some game text boxes.</li>
<li>Disable help rank and award page.</li>
<li>Bug fix: Mission bonus money calculated is now working fine.</li>
<li>Bug fix: Transaction with more 2.147.483.647 dollar is now working fine.</li>
<li>Bug fix: Prevent negative hourly income on mission page.</li>
</ul>';

$notes[13] = '
<div class="subparagraph2">27-04-2011</div>
<i>Game Server v1.3</i>
<ul>
<li>Improve worldmap image.</li>
<li>Added worldmap hyperlink to jump directly to mission page.</li>
<li>Improve continent complete bonus energy level is directly restored.</li>
<li>Username and Password length increase to maximum 15 digits.</li>
<li>Initial money increase to 25.000 dollar.</li>
<li>Initial skill points increase to 9.</li>
<li>Move comments functionality to alliance menu.</li>
<li>Comments send to a player are also mailed!</li>
<li>Until level 17 players can only attack other player in the same level.</li>
<li>Bug fix: Alliance player detail page did not work always. Solved.</li>
<li>Bug fix: Notes page is now showed correct on Nokia devices.</li>
</ul>';

$notes[12] = '
<div class="subparagraph2">20-04-2011</div>
<i>Game Server v1.2</i>
<ul>
<li>Added world map with mission conquer progress information.</li>
<li>Decrease chance of losing units during mission with 50%.</li>
<li>Show complete mission submenu bar.</li>
<li>Added data page control to best player leaderbord.</li>
<li>Split every mission continent in three parts.</li>
<li>Created upgrade script to patch database mission tables.</li>
<li>Improve Help-Notes page.</li>
<li>Bug fix: Remove some typos on the mission pages.</li>
<li>Bug fix: Alliance calculation is optimise.</li>
</ul>';

$notes[11] = '
<div class="subparagraph2">14-04-2011</div>
<i>Game Server v1.1</i>
<ul>
<li>Improve bank page.</li>
<li>Payed hospital bill is now recorded in bank transaction log.</li>
<li>Added release notes to help section.</li>
<li>Leaderbords table size enlarge to maximum 100 entries.</li>
<li>Hourly income stops when player is not active last 24 hours.</li>
<li>Added google analystics javascript.</li>
<li>Added direct sign on and login for WarQuest client.</li>
<li>Now only players can be attack with max 3 level difference.</li>
<li>Initial skill point amount decreased from 10 to 7.</li>
<li>Bug fix: Javascript money calculation corrected!</li>
<li>Bug fix: Home page improved for Nokia devices.</li>
</ul>
<br/>

<i>Windows Client v0.40</i>
<ul>
<li>Registration and Login information not needed anymore.</li>
<li>Added direct sign on and login.</li>
<li>Use QT library 4.7.2 as engine.</li>
<li>The app was build with QtCreator v2.0.1.</li>
<li>Released app on freewarefiles.com.</li>
</ul>';

$notes[10] = '
<div class="subparagraph2">08-04-2011</div>
<i>Game Server v1.0</i>
<ul>
<li>Exclude admin account from player reports.</li>
<li>Optimise level ranges.</li>
<li>Added robot players for the first 15 levels. More fun!</li>
<li>Added Players per Level report (Admin page).</li>
<li>Added copy and/or delete member account (Admin page).</li>
<li>Added new member report (Admin page).</li>
<li>Added rang image to home page.</li>
<li>Added logout page.</li>
<li>Adjusted daily bonus.</li>
<li>Added Ranks and About help page.</li>
<li>iPhone Safari login with GPRS connection is now working.</li>
<li>SuperT, thanks for all the usefull comments and bug reports.</li>
<li>First stable release. Beta testing phase closed.</li>
</ul>';

$notes[9] = '
<div class="subparagraph2">01-04-2011</div>
<i>Game Server v0.90</i>
<ul>
<li>Added admin comments maintenance page.</li>
<li>Refactor function names of game.</li>
<li>Added unit amount on battle page.</li>
<li>Improve alliance page.</li>
<li>Performance improvement. Split php and image service.</li>
<li>Added maintenance admin pages.</li>
<li>Improve login page layout.</li>
<li>Added deploy or disband multiple units with one click.</li>
<li>Added buy or sell multiple buildings with one click.</li>
<li>Initial (new account) skill points increase to 10.</li>
<li>Now only players can be attack with max 2 level difference.</li>
<li>Bug fix: Alliance size on leaderboard corrected.</li>
<li>Bug fix: Resolve some small GUI layout issues.</li>
<li>Bug fix: Nokia ccs stylesheet.</li>
<li>Bug fix: Internet Explorer css stylesheet.</li>
<li>Bug fix: Leaderboard player attack is now restricted.</li>
<li>Retested game with Firefox, Safari, IE, Nokia, Opera browser.</li>
</ul>';

$notes[8] = '
<div class="subparagraph2">27-03-2011</div>
<i>Game Server v0.80</i>
<ul>
<li>Redesign intro page. Better look.</li>
<li>Make CSS font size better.</li>
<li>Ordered www.warquest.nl domain.</li> 
<li>Added Nokia css style sheet.</li>
<li>Added admin page, to manage easy users and comments.</li>
<li>Added ids to html links and buttons for selenium tests.</li>
<li>Added send comment to one player.</li>
<li>Added third leaderbord.</li>
<li>Refactor feedback message box.</li>
<li>Improve help text.</li>
<li>Bug fix: 100% continent detect is now working fine.</li>
<li>Bug fix: Attack player for leaderboard is now working again.</li>
<li>Bug fix: Emails contain now correct text.</li>
</ul>
<br/>

<i>Windows Client v0.30</i>
<ul>
<li>Update URL to www.warquest.nl.</li>
<li>Use QT library 4.7.2 as engine.</li>
<li>The app was build with QtCreator v2.0.1.</li>
<li>Released app on freewarefiles.com.</li>
</ul>';

$notes[7] = '
<div class="subparagraph2">20-03-2011</div>
<i>Game Server v0.70</i>
<ul>
<li>Added progress bar to mission.</li>
<li>Added chance of loot during mission.</li>
<li>Added email notification to alliance functionality.</li>
<li>Improve unit lost message during mission.</li>
<li>Improve battle summary page.</li>
<li>Improve email reply address and mail content.</li>
<li>Improve Home-Settings current values are showed.</li>
<li>Added functionality to change email on setting page.</li>
<li>Adjusted unit lost chance.</li>
<li>Improve battle log cleanup.</li>
<li>Added invite friends (email) to game and get bonus.</li>
<li>Now all players can make alliance with each other.</li>
<li>Improve unit and building info box.</li>
<li>Added build number to login page.</li>
<li>Improve player page layout.</li>
<li>Adjust hospital cost.</li>
<li>Bug fix: Solve some small GUI mismatches.</li>
<li>Bug fix: Show correct continent name on mission page.</li>
<li>Bug fix: Battle log is now working correct.</li>
<li>Bug fix: Battle report defense buildings amount now right.</li>
</ul>';

$notes[6] = '
<div class="subparagraph2">13-03-2011</div>
<i>Game Server v0.60</i>
<ul>
<li>Improvement leaderbords.</li>
<li>Improve building images (All same size now)!</li>
<li>Improve help text.</li>
<li>Improve game layout.</li>
<li>Added continent mission complet skill points bonus.</li>
<li>Translate country names to english.</li>
<li>Added apple iphone / ipod css.</li>
<li>Added missing mission and mission unit dependencies.</li>
<li>Bug fix: Mission unit lost is now working correct.</li>
<li>First beta release for the world.</li>
</ul>
<br/>

<i>Windows Client v0.20</i>
<ul>
<li>Added proxy support.</li>
<li>Added about page.</li>
<li>Refactor source code.</li>
<li>Use QT library 4.7.2 as engine.</li>
<li>The app was build with QtCreator v2.0.1.</li>
</ul>';

$notes[5] = '
<div class="subparagraph2">06-03-2011</div>
<i>Game Server v0.50</i>
<ul>
<li>Added submenu to building page. No scrolling anymore. :-}</li>
<li>Added two extra banks with special features.</li>
<li>Added country flags.</li>
<li>Added second leaderbord. Best performing country.</li>
<li>Added bank transaction log.</li>
<li>Added battle and bank table cleanup.</li>
<li>Added basic help page.</li>
<li>Added flavicon image.</li>
<li>Added land names to flags.</li>
<li>Added Credits and Donate page.</li>
<li>Player can now only battle other country players.</li>
<li>Improve Player-Profile page.</li>
<li>Increase daily money bonus.</li>
<li>Improve home page layout.</li>
<li>Show defense buildings during fights.</li>
<li>Create unique game name "War Quest".</li>
<li>Added battle new flag in main menu.</li>
<li>Improve next level message.</li>
<li>Added insigne image to home page.</li>
<li>Update weapon unit names and images.</li>
<li>Update building names and images.</li>
<li>Bug fix: Level 200 is maximum to reach.</li>
</ul>
<br/>

<i>Windows Client v0.10</i>
<ul>
<li>Start building.</li>
<li>Added application icon.</li>
<li>First beta release for the world.</li>
<li>Use QT library 4.7.2 as engine.</li>
<li>The app was build with QtCreator v2.0.1.</li>
</ul>';

$notes[4] = '
<div class="subparagraph2">27-02-2011</div>
<i>Game Server v0.40</i>
<ul>
<li>Added tooltip on battle / mission / player page.</li>
<li>Background image is now fix.</li>
<li>Improve Player-Profile page.</li>
<li>Added Alliance-Leaderbord-Best player.</li>
<li>Added missing units up to level 200.</li>
<li>Added more mission unit connections.</li>
<li>Added buy missing units during mission play.</li>
<li>Added random mission unit lost.</li>
<li>Added unit lost can be enabled/disable per level.</li>
<li>Added battle summary show used weapon units.</li>
<li>Added dot support in money javascript.</li>
<li>Improve battle log text.</li>
<li>Improve number format.</li>
<li>Added settings page (change nickname and/or password).</li>
<li>Performance tuning. Include only php file when needed.</li>
<li>Refactor login functionality.</li>
<li>Html parameters are now hidden. Nice clean url during game.</li>
<li>Added forgot password page.</li>
<li>All hyperlinks are now encrypted to prevent hacking.</li>
<li>Added alliance size to mission.</li>
<li>Improve Health, Energy and Ammo countdown timer.</li>
<li>Added configuration settings in array.</li>
<li>Send welcome email to new register player.</li>
<li>Added Password reset on login page.</li>
<li>Added unit damage functionality during fights.</li>
<li>Bug fix: Prevent income to become negatief because of unit cost.</li>
<li>Bug fix: Java script hourly money did not work.</li>
<li>Bug fix: Defense strength was not correct calculated.</li>
<li>Bug fix: Prevent negatieve income by selling a building.</li>
<li>Bug fix: Several issues solved during battle events.</li>
</ul>';

$notes[3] = '
<div class="subparagraph2">20-02-2011</div>
<i>Game Server v0.30</i>
<ul>
<li>Battle list is order by oldest battle on top.</li>
<li>Player parameters are updated before battle.</li>
<li>Improve skill page.</li>
<li>Increase page width size to 500px.</li>
<li>Added weapon hourly cost feature.</li>
<li>Added menu indication if new ally request is waiting.</li>
<li>Added menu indication if new skill points are available.</li>
<li>Optimise data model.</li>
<li>Calc. attack & defense strength depending on alliance size.</li>
<li>Added hospital page.</li>
<li>Make SQL and PHP code compliant with unix operating system.</li>
<li>Added comments page with ajax partly reload functionality.</li>
<li>Added Alliance functionality.</li>
<li>Protect input for SQL insertion.</li>
<li>Added Daily bonus.</li>
<li>Improve building price structure.</li>
<li>Added private battle zone (Disable member registration).</li>
<li>Add CSS Background.</li>
<li>Added page, mission counter.</li>
<li>Refactor database source code.</li>
<li>Check on dubble nickname during registration.</li>
<li>Building price increase 10% every purchase.</li>
<li>Added progress detection for missions.</li>
<li>Make CSS compliant with Microsoft Internet Explorer.</li>
<li>Added unit dependence to missions.</li>
<li>Improve battle log (ago vs timestamp).</li>
<li>Added more color to energy, health, etc..</li>
<li>Added several hyperlinks to attacker info page.</li>
<li>Added introduction text to login page.</li>
<li>Introduce box layout.</li>
<li>Added maximum amount of building per types.</li>
<li>Bug fix: Player timers now working fine.</li>
</ul>';

$notes[2] = '
<div class="subparagraph2">13-02-2011</div>
<i>Game Server v0.20</i>
<ul>
<li>page width is now base 450px.</li>
<li>Improve player timer calculation.</li>
<li>Added release notes information to source code.</li>
<li>Added div and span html blocks. Remove p html blocks.</li>
<li>Improve mission feedback.</li>
</ul>';

$notes[1] = '
<div class="subparagraph2">08-02-2011</div>
<i>Game Server v0.10</i>
<ul>
<li>Started programming.</li>
<li>Added basic login, registration and logout page.</li>
<li>Added css sheet.</li>
<li>Added unit and building page.</li>
<li>Added player pages.</li>
<li>Added battle page.</li>
<li>Added mission page.</li>
<li>Added bank page.</li>
<li>Added some unit and building images.</li>
<li>Added javascript timers.</li>
<li>Added battle log.</li>
</ul>';

/*
** ---------------------------------------------------------------<li>
** THE END
** ----------------------------------------------------------------
*/

?>