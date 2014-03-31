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

require_once "../database.inc";
require_once "../constants.inc";
require_once "../general.inc";
require_once "../config.inc";
require_once "config.inc";

class TestDatabase extends PHPUnit_Framework_TestCase {

	/**
	* @test create database tables
	*/ 	
   function testCreateDatabaseTables() {
	
		echo "testCreateDatabaseTables()\r\n";
		
		global $config;
		global $popup;
		
		/* test data */
		$_SERVER["REMOTE_ADDR"] = "127.0.0.1";
		
		$result = warquest_db_connect($config["dbhost"], $config["dbuser"], $config["dbpass"], $config["dbname"]);
		$this->assertEquals($result, 1);
		
		warquest_db_multi_query( file_get_contents('../#database/base_57.sql', true) );
		warquest_db_multi_query( file_get_contents('../#database/patch_58.sql', true) );
		warquest_db_multi_query( file_get_contents('../#database/patch_59.sql', true) );
		warquest_db_multi_query( file_get_contents('../#database/patch_60.sql', true) );
		warquest_db_multi_query( file_get_contents('../#database/patch_61.sql', true) );
		warquest_db_multi_query( file_get_contents('../#database/patch_62.sql', true) );
		warquest_db_multi_query( file_get_contents('../#database/patch_63.sql', true) );
		warquest_db_multi_query( file_get_contents('../#database/patch_64.sql', true) );
		warquest_db_multi_query( file_get_contents('../#database/patch_65.sql', true) );
		warquest_db_multi_query( file_get_contents('../#database/patch_66.sql', true) );
		warquest_db_multi_query( file_get_contents('../#database/patch_67.sql', true) );
		warquest_db_multi_query( file_get_contents('../#database/patch_68.sql', true) );
		
		$result = warquest_db_close();
		$this->assertEquals($result, 1);	
	}
	
	/**
	* @test member database api
	*/ 
   public function testMemberAPI() {
		
		echo "testMemberAPI()\r\n";
			
		global $config;
		global $popup;

		/* test data */
		$username1 = "test1";
		$username2 = "test2";
		$username3 = "test2";
		$password1  = "12345678";
		$password2 = "87654321";
		$email     = "test@plaatsoft.nl";
		$_SERVER["REMOTE_ADDR"] = "127.0.0.1";
				
		$result = warquest_db_connect($config["dbhost"], $config["dbuser"], $config["dbpass"], $config["dbname"]);
		$this->assertEquals($result, 1);
		
		$pid = warquest_db_member_insert($username1, $password1, $email);
		$this->assertNotEquals($pid, 0);
					
		$member1 = warquest_db_member($pid);
		$this->assertEquals($member1->username, $username1);
		$this->assertEquals($member1->pid, $pid);
		$this->assertEquals($member1->email_valid,0);
		
		$member1->username = $username2;
		$result = warquest_db_member_update($member1);
		$this->assertEquals($result, 1);		
		
		$member2 = warquest_db_member($pid);
		$this->assertEquals($member2->username, $username2);
		
		$result = warquest_db_member_username_update($pid, $username3);
		$this->assertEquals($result, 1);	
		
		$member3 = warquest_db_member($pid);
		$this->assertEquals($member3->username, $username3);
		
		$result = warquest_db_member_password_update($pid, $password2);
		$this->assertEquals($result, 1);	
		
		$result = warquest_db_member_delete($pid);		
		$this->assertEquals($result, 1);
		
		$result = warquest_db_close();
		$this->assertEquals($result, 1);	
	}
	
	/**
	* @test player database api
	*/ 
   public function testPlayerAPI() {
		
		echo "testPlayerAPI()\r\n";
		
		global $config;
		global $popup;

		/* test data */
		$name1 = "test1";
		$name2 = "test2";
		$pid = 1;
		$_SERVER["REMOTE_ADDR"] = "127.0.0.1";
						
		$result = warquest_db_connect($config["dbhost"], $config["dbuser"], $config["dbpass"], $config["dbname"]);
		$this->assertEquals($result, 1);
		
		/* Clear old data, if any */
		$result = warquest_db_player_delete($pid);	
		$this->assertEquals($result, 1);
						
		$result = warquest_db_player_insert($name1, $pid);
		$this->assertEquals($result, 1);

		$player1 = warquest_db_player($pid);
		$this->assertEquals($player1->name, $name1);
		$this->assertEquals($player1->pid, $pid);
		
		$player1->name = $name2;
		$result = warquest_db_player_update($player1);
		$this->assertEquals($result, 1);
		
		$player2 = warquest_db_player($pid);
		$this->assertEquals($player2->name, $name2);
					
		$result = warquest_db_player_login_counter($pid);
		$this->assertEquals($result, 1);		
					
		$result = warquest_db_player_delete($pid);		
		$this->assertEquals($result, 1);
		
		$result = warquest_db_close();
		$this->assertEquals($result, 1);	
   }
	
	/**
	* @test skill database api
	*/ 
   public function testSkillAPI() {

		echo "testSkillAPI()\r\n";
		
		global $config;
		global $popup;

		/* test data */
		$pid = 1;
		$skill_points1 = 10;
		$skill_points2 = 15;
		$_SERVER["REMOTE_ADDR"] = "127.0.0.1";
						
		$result = warquest_db_connect($config["dbhost"], $config["dbuser"], $config["dbpass"], $config["dbname"]);
		$this->assertEquals($result, 1);
	
		/* Clear old data, if any */
		$result = warquest_db_skill_delete($pid);		
		$this->assertEquals($result, 1);
	
		$result = warquest_db_skill_insert($pid, $skill_points1);
		$this->assertEquals($result, 1);
		
		$skill1 = warquest_db_skill($pid);
		$this->assertEquals($skill1->skill_points, $skill_points1);
		
		$skill1->skill_points = $skill_points2;
		$result = warquest_db_skill_update($skill1);
		$this->assertEquals($result, 1);
		
		$skill2 = warquest_db_skill($pid);
		$this->assertEquals($skill2->skill_points, $skill_points2);
					
		$result = warquest_db_skill_delete($pid);		
		$this->assertEquals($result, 1);
		
		$result = warquest_db_close();
		$this->assertEquals($result, 1);	
   }
	
	/**
	* @test news database api
	*/ 
   public function testNewsAPI() {
		
		echo "testNewsAPI()\r\n";
		
		global $config;
		global $popup;
		
		/* test data */
		$body1 = "Body test1";
		$body2 = "Body test2";
		$content1 = "Content of test 1";
		$content2 = "Content of test 2";
		$language1 = "EN";
		$language2 = "NL";
		$_SERVER["REMOTE_ADDR"] = "127.0.0.1";
						
		$result = warquest_db_connect($config["dbhost"], $config["dbuser"], $config["dbpass"], $config["dbname"]);
		$this->assertEquals($result, 1);
	
		$id = warquest_db_news_insert($body1, $content1, $language1);
		$this->assertNotEquals($id, 0);
		
		$news1 = warquest_db_news($id);
		$this->assertEquals($news1->body, $body1);
		$this->assertEquals($news1->content, $content1);
		$this->assertEquals($news1->language, $language1);
		
		$news1->body = $body2;
		$news1->content = $content2;
		$news1->language = $language2;
		$result = warquest_db_news_update($news1);
		$this->assertEquals($result, 1);
		
		$news2 = warquest_db_news($id);
		$this->assertEquals($news2->body, $body2);
		$this->assertEquals($news2->content, $content2);
		$this->assertEquals($news2->language, $language2);	

		$result = warquest_db_news_delete($id);
		$this->assertEquals($result, 1);
				
		$result = warquest_db_close();
		$this->assertEquals($result, 1);	
   }
	
	/**
	* @test sector database api
	*/ 
   public function testSectorAPI() {
		
		echo "testSectorAPI()\r\n";
		
		global $config;
		global $popup;
		
		/* test data */
		$cid = 1;
		$damage = 100;
		$_SERVER["REMOTE_ADDR"] = "127.0.0.1";
						
		$result = warquest_db_connect($config["dbhost"], $config["dbuser"], $config["dbpass"], $config["dbname"]);
		$this->assertEquals($result, 1);
	
		$sector1 = warquest_db_sector($cid);
			
		$sector2 = warquest_db_sector($cid);
		$sector2->cid = $cid;
		$sector2->damage = $damage;
		
		$result = warquest_db_sector_update($sector2);
		$this->assertEquals($result, 1);
		
		$sector3 = warquest_db_sector($cid);	
		$this->assertEquals($sector3->cid,$cid);
		$this->assertEquals($sector3->damage,$damage);
		
		$result = warquest_db_sector_update($sector1);
		$this->assertEquals($result, 1);
		
		$result = warquest_db_close();
		$this->assertEquals($result, 1);	
   }
	
	
	/**
	* @test clan database api
	*/ 
   public function testClanAPI() {
		
		echo "testClanAPI()\r\n";
		
		global $config;
		global $popup;
		
		/* test data */
		$pid = 1;
		$name1 = "TEST";
		$name2 = "TEST";
		$_SERVER["REMOTE_ADDR"] = "127.0.0.1";
						
		$result = warquest_db_connect($config["dbhost"], $config["dbuser"], $config["dbpass"], $config["dbname"]);
		$this->assertEquals($result, 1);
		
		$cid = warquest_db_clan_insert($pid, $name1);
		$this->assertNotEquals($cid, 0);
		
		$clan = warquest_db_clan($cid);
		$this->assertEquals($clan->name, $name1);
		
		$clan->name = $name2;
		$result = warquest_db_clan_update($clan);
		$this->assertEquals($result, 1);
		
		$clan = warquest_db_clan($cid);
		$this->assertEquals($clan->name, $name2);
					
		$result = warquest_db_clan_delete($cid);		
		$this->assertEquals($result, 1);
		
		$result = warquest_db_close();
		$this->assertEquals($result, 1);	
   }
	
	/**
	* @test player_clan database api
	*/ 
   public function testPlayerClanAPI() {

		echo "testPlayerClanAPI()\r\n";
		
		global $config;
		global $popup;

		/* test data */
		$pid = 1;
		$cid = 1;
		$approved1 = 0;
		$approved2 = 0;
		$_SERVER["REMOTE_ADDR"] = "127.0.0.1";
						
		$result = warquest_db_connect($config["dbhost"], $config["dbuser"], $config["dbpass"], $config["dbname"]);
		$this->assertEquals($result, 1);
		
		$result = warquest_db_player_clan_insert($pid, $cid, $approved1);
		$this->assertEquals($result, 1);
		
		$player_clan = warquest_db_player_clan($pid);
		$this->assertEquals($player_clan->cid, $cid);
		$this->assertEquals($player_clan->approved, $approved1);
		
		$player_clan->approved=$approved2;		
		$result = warquest_db_player_clan_update($player_clan);
		$this->assertEquals($result, 1);
		
		$player_clan = warquest_db_player_clan($pid);
		$this->assertEquals($player_clan->cid, $cid);
		$this->assertEquals($player_clan->approved, $approved2);
		
		$result = warquest_db_player_clan_delete($pid, $cid);
		$this->assertEquals($result, 1);
		
		$result = warquest_db_close();
		$this->assertEquals($result, 1);	
   }
		
	/**
	* @test bonus database api
	*/ 
   public function testBonusAPI() {

		echo "testBonusAPI()\r\n";
		
		global $config;
		global $popup;

		/* test data */
		$pid = 1;
		$bonus = 1;
		$_SERVER["REMOTE_ADDR"] = "127.0.0.1";
						
		$result = warquest_db_connect($config["dbhost"], $config["dbuser"], $config["dbpass"], $config["dbname"]);
		$this->assertEquals($result, 1);
		
		$result = warquest_db_bonus_insert($pid, $bonus);
		$this->assertEquals($result, 1);
		
		$value = warquest_db_bonus($pid, $bonus);
		$this->assertEquals($value, 1);
		
		$result = warquest_db_close();
		$this->assertEquals($result, 1);	
   }
	
	/**
	* @test session database api
	*/ 
   public function testSessionAPI() {

		echo "testSessionAPI()\r\n";
		
		global $config;
		global $popup;

		/* test data */
		$pid = 1;
		$_SERVER["REMOTE_ADDR"] = "127.0.0.1";
						
		$result = warquest_db_connect($config["dbhost"], $config["dbuser"], $config["dbpass"], $config["dbname"]);
		$this->assertEquals($result, 1);
		
		$session_id = warquest_db_session_add($pid);
		$this->assertNotEquals($session_id, 0);	
		
		$value = warquest_db_session_valid( $session_id );
		$this->assertEquals($value, 1);	
				
		$value = warquest_db_session_hack($pid);
		$this->assertEquals($value, $session_id);	
		
		$result = warquest_db_session_delete($session_id);
		$this->assertEquals($result, 1);	
		
		$session_id = warquest_db_session_add($pid);
		$this->assertNotEquals($session_id, 0);	
		
		$result = warquest_db_session_delete_pid($pid);
		$this->assertEquals($result, 1);	
			
		$result = warquest_db_close();
		$this->assertEquals($result, 1);	
   }
	
	/**
	* @test cron database api
	*/ 
   public function testCronAPI() {

		echo "testCronAPI()\r\n";
		
		global $config;
		global $popup;

		/* test data */
		$cid = 1;
		$_SERVER["REMOTE_ADDR"] = "127.0.0.1";
						
		$result = warquest_db_connect($config["dbhost"], $config["dbuser"], $config["dbpass"], $config["dbname"]);
		$this->assertEquals($result, 1);

		$result = warquest_db_cron_update($cid);
		$this->assertEquals($result, 1);	
		
		$result = warquest_db_close();
		$this->assertEquals($result, 1);	
   }
	
	/**
	* @test bounty database api
	*/ 
   public function testBountyAPI() {

		echo "testBountyAPI()\r\n";
		
		global $config;
		global $popup;

		/* test data */
		$pid1 = 1;
		$pid2 = 1;
		$amount = 10;
		$experience = 20;
		
		$_SERVER["REMOTE_ADDR"] = "127.0.0.1";
						
		$result = warquest_db_connect($config["dbhost"], $config["dbuser"], $config["dbpass"], $config["dbname"]);
		$this->assertEquals($result, 1);

		$id = warquest_db_bounty_insert($pid1, $pid2, $amount, $experience );
		$this->assertNotEquals($id, 0);	

		$value = warquest_db_bounty_possible($pid1, $pid2);
		$this->assertEquals($value, 1);	
		
		$result = warquest_db_bounty_delete($id);
		$this->assertEquals($result, 1);
		
		$id = warquest_db_bounty_insert($pid1, $pid2, $amount, $experience );
		$this->assertNotEquals($id, 0);	
		
		$result = warquest_db_bounty_delete_all($pid1);
		$this->assertEquals($result, 1);
				
		$result = warquest_db_close();
		$this->assertEquals($result, 1);	
   }
	
	/**
	* @test battle database api
	*/ 
   public function testBattleAPI() {

		echo "testBattleAPI()\r\n";
		
		global $config;
		global $popup;

		/* test data */
		$pid1 = 1;
		$pid2 = 1;
		$money = 10;
		$health = 20;
		$exp = 30;
		$win = 1;
		$ugid = 40;
		$bounty = 0;
		
		$_SERVER["REMOTE_ADDR"] = "127.0.0.1";
						
		$result = warquest_db_connect($config["dbhost"], $config["dbuser"], $config["dbpass"], $config["dbname"]);
		$this->assertEquals($result, 1);

		$id = warquest_db_battle_insert($pid1, $pid2, $money, $health, $exp, $win, $ugid, $bounty);
		$this->assertNotEquals($id, 0);	

		$result = warquest_db_battle_delete_pid($pid1);
		$this->assertEquals($result, 1);	
		
		$id = warquest_db_battle_insert($pid1, $pid2, $money, $health, $exp, $win, $ugid, $bounty);
		$this->assertNotEquals($id, 0);	
		
		$result = warquest_db_battle_delete($id);
		$this->assertEquals($result, 1);
		
		$result = warquest_db_close();
		$this->assertEquals($result, 1);	
   }
	
	
	/**
	* @test stock database api
	*/ 
   public function testStockAPI() {

		echo "testStockAPI()\r\n";
		
		global $config;
		global $popup;

		/* test data */
		$pid = 1;
		$symbol = "IBM";
				
		$_SERVER["REMOTE_ADDR"] = "127.0.0.1";
						
		$result = warquest_db_connect($config["dbhost"], $config["dbuser"], $config["dbpass"], $config["dbname"]);
		$this->assertEquals($result, 1);

		$id = warquest_db_stock_insert($symbol, $pid);
		$this->assertNotEquals($id, 0);	

		$result = warquest_db_stock_check($symbol, $pid);
		$this->assertNotEquals($result, 0);	
		
		$result = warquest_db_stock_delete($id);
		$this->assertEquals($result, 1);
		
		$result = warquest_db_close();
		$this->assertEquals($result, 1);	
   }
	
	/**
	* @test player_stock database api
	*/ 
   public function testPlayerStockAPI() {

		echo "testPlayerStockAPI()\r\n";
		
		global $config;
		global $popup;

		/* test data */
		$pid = 1;
		$amount1 = 100;
		$amount2 = 50;	
		$amount3 = 150;		
		$cost1 = 200;
		$symbol = "IBM";
				
		$_SERVER["REMOTE_ADDR"] = "127.0.0.1";
						
		$result = warquest_db_connect($config["dbhost"], $config["dbuser"], $config["dbpass"], $config["dbname"]);
		$this->assertEquals($result, 1);

		$sid = warquest_db_stock_insert($symbol, $pid);
		$this->assertNotEquals($sid, 0);	

		$amount = warquest_db_player_stock_add($pid, $sid, $amount1, $cost1);
		$this->assertEquals($amount, 100);
	
		$amount = warquest_db_player_stock_add($pid, $sid, $amount1, $cost1);
		$this->assertEquals($amount, 200);
		
		$amount = warquest_db_player_stock_assest($pid);
		$this->assertEquals($amount, 400);
		
		$result = warquest_db_player_stock_delete($pid, $sid, $amount2);
		$this->assertEquals($result, 1);

		$result = warquest_db_player_stock_delete($pid, $sid, $amount3);
		$this->assertEquals($result, 1);
					
		$amount = warquest_db_player_stock_add($pid, $sid, $amount1, $cost1);
		$this->assertEquals($amount, 100);
	
		$amount = warquest_db_player_stock_add($pid, $sid, $amount1, $cost1);
		$this->assertEquals($amount, 200);
		
		$result = warquest_db_player_stock_delete_all($pid);
		$this->assertEquals($result, 1);	
					
		$result = warquest_db_close();
		$this->assertEquals($result, 1);	
   }
	
	/**
	* @test bank api
	*/ 
   public function testBankAPI() {

		echo "testBankAPI()\r\n";
		
		global $config;
		global $popup;

		/* test data */
		$pid1 = 1;
		$pid2 = 2;
		$bgid = 1;
		$amount = 100;
		$balance = 100;
		$action = 1;
				
		$_SERVER["REMOTE_ADDR"] = "127.0.0.1";
						
		$result = warquest_db_connect($config["dbhost"], $config["dbuser"], $config["dbpass"], $config["dbname"]);
		$this->assertEquals($result, 1);

		$id = warquest_db_bank_insert($pid1, $pid2, $bgid, $amount, $balance, $action);
		$this->assertNotEquals($id, 0);

		$result = warquest_db_bank_delete_pid($pid1);
		$this->assertEquals($result, 1);	
		
		$id = warquest_db_bank_insert($pid1, $pid2, $bgid, $amount, $balance, $action);
		$this->assertNotEquals($id, 0);
		
		$result = warquest_db_bank_delete($id);
		$this->assertEquals($result, 1);
		
		$result = warquest_db_close();
		$this->assertEquals($result, 1);	
   }
	
	/**
	* @test level api
	*/ 
   public function testLevelAPI() {

		echo "testLevelAPI()\r\n";
		
		global $config;
		global $popup;

		/* test data */
		$level = 1;				
		$_SERVER["REMOTE_ADDR"] = "127.0.0.1";
						
		$result = warquest_db_connect($config["dbhost"], $config["dbuser"], $config["dbpass"], $config["dbname"]);
		$this->assertEquals($result, 1);

		$level = warquest_db_level($level);
		$this->assertNotEquals($level->lid, $level);
		
		$result = warquest_db_close();
		$this->assertEquals($result, 1);	
   }	

	/**
	* @test PlayerPlayer api
	*/ 
   public function testPlayerPlayerAPI() {

		echo "testPlayerPlayerAPI()\r\n";
		
		global $config;
		global $popup;

		/* test data */
		$pid1 = 1;				
		$pid2 = 1;
		$approved1 = 0;
		$approved2 = 1;
		$_SERVER["REMOTE_ADDR"] = "127.0.0.1";
						
		$result = warquest_db_connect($config["dbhost"], $config["dbuser"], $config["dbpass"], $config["dbname"]);
		$this->assertEquals($result, 1);

		$result = warquest_db_alliance_insert($pid1, $pid2, $approved1);
		$this->assertEquals($result, 1);	

		$value = warquest_db_invite_size($pid1);
		$this->assertEquals($value, 1);	

		$result = warquest_db_alliance_update($pid1, $pid2, $approved2);
		$this->assertEquals($result, 1);	 
				
		$value = warquest_db_invite_size($pid1);
		$this->assertEquals($value, 0);	

		$value = warquest_db_ally($pid1, $pid2);
		$this->assertEquals($value, 1);	
		
		$value = warquest_db_alliance_size($pid1);
		$this->assertEquals($value, 2);	

		$result = warquest_db_alliance_delete($pid1, $pid2);
		$this->assertEquals($result, 1);	
		
		$value = warquest_db_alliance_size($pid1);
		$this->assertEquals($value, 1);	
		
		$result = warquest_db_alliance_insert($pid1, $pid2, $approved1);
		$this->assertEquals($result, 1);	
		
		$result = warquest_db_alliance_delete_all($pid1);
		$this->assertEquals($result, 1);	
		
		$value = warquest_db_alliance_size($pid1);
		$this->assertEquals($value, 1);	
		
		$result = warquest_db_close();
		$this->assertEquals($result, 1);	
   }
	
	/**
	* @test PlayerMission api
	*/ 
   public function testPlayerMissionAPI() {

		echo "testPlayerMissionAPI()\r\n";
		
		global $config;
		global $popup;

		/* test data */
		$pid = 1;				
		$mid = 1;
		$progress = 10;
		$part = 1;
		$part2 = 1;
	
		$_SERVER["REMOTE_ADDR"] = "127.0.0.1";
						
		$result = warquest_db_connect($config["dbhost"], $config["dbuser"], $config["dbpass"], $config["dbname"]);
		$this->assertEquals($result, 1);

		$result = warquest_db_player_mission_update($pid, $mid, $progress, $part, $part2);
		$this->assertEquals($result, 1);	
		
		$data = warquest_db_player_mission($pid, $mid);
		$this->assertEquals($data->progress, $progress);	
		$this->assertEquals($data->part, $part);	
				
		$result = warquest_db_player_mission_delete_all($pid);
		$this->assertEquals($result, 1);	
		
		$result = warquest_db_close();
		$this->assertEquals($result, 1);	
   }
	
	/**
	* @test BuildingGroup api
	*/ 
   public function testBuildingGroupAPI() {

		echo "testBuildingGroupAPI()\r\n";
		
		global $config;
		global $popup;

		/* test data */
		$bgid = 1;				
		$_SERVER["REMOTE_ADDR"] = "127.0.0.1";
						
		$result = warquest_db_connect($config["dbhost"], $config["dbuser"], $config["dbpass"], $config["dbname"]);
		$this->assertEquals($result, 1);

		$building_group = warquest_db_building_group($bgid);
		$this->assertEquals($building_group->planet, 1);	
		
		$result = warquest_db_close();
		$this->assertEquals($result, 1);	
   }
	
	/**
	* @test UnitGroup api
	*/ 
   public function testUnitGroupAPI() {

		echo "testUnitGroupAPI()\r\n";
		
		global $config;
		global $popup;

		/* test data */
		$ugid = 2;				
		$_SERVER["REMOTE_ADDR"] = "127.0.0.1";
						
		$result = warquest_db_connect($config["dbhost"], $config["dbuser"], $config["dbpass"], $config["dbname"]);
		$this->assertEquals($result, 1);

		$unit_group = warquest_db_unit_group($ugid);
		$this->assertEquals($unit_group->planet, 1);	
		
		$result = warquest_db_close();
		$this->assertEquals($result, 1);	
   }
	
	/**
	 * @test Topic api
	 */ 
   public function testTopicAPI() {

		echo "testTopicAPI()\r\n";
		
		global $config;
		global $popup;

		/* test data */
		$pid = 1;
		$fid = 2;
		$description1 = "Test Description 1";
		$description2 = "Test Description 2";
				
		$_SERVER["REMOTE_ADDR"] = "127.0.0.1";
						
		$result = warquest_db_connect($config["dbhost"], $config["dbuser"], $config["dbpass"], $config["dbname"]);
		$this->assertEquals($result, 1);

		$tid = warquest_db_topic_insert($pid, $fid, $description1);
		$this->assertNotEquals($tid, 0);

		$result = warquest_db_topic_update($tid, $description2);
		$this->assertEquals($result, 1);	
		
		$result = warquest_db_topic_delete($tid);
		$this->assertEquals($result, 1);
				
		$result = warquest_db_close();
		$this->assertEquals($result, 1);	
   }
	
	/**
	 * @test Comment api
	 */ 
   public function testCommentAPI() {

		echo "testCommentAPI()\r\n";
		
		global $config;
		global $popup;

		/* test data */
		$tid = 1;
		$pid1 = 1;
		$pid2 = 2;
		$comment1 = "Test 1";
		$comment2 = "Test 2";
				
		$_SERVER["REMOTE_ADDR"] = "127.0.0.1";
						
		$result = warquest_db_connect($config["dbhost"], $config["dbuser"], $config["dbpass"], $config["dbname"]);
		$this->assertEquals($result, 1);

		$id = warquest_db_comment_insert($tid, $pid1, $pid2, $comment1);
		$this->assertNotEquals($tid, 0);
		
		$result = warquest_db_comment_update($id, $comment2);
		$this->assertEquals($result, 1);	
		
		$result = warquest_db_comment_delete($id);
		$this->assertEquals($result, 1);
		
		$id = warquest_db_comment_insert($tid, $pid1, $pid2, $comment1);
		$this->assertNotEquals($tid, 0);
				
		$result = warquest_db_comment_delete_all($pid1);
		$this->assertEquals($result, 1);
				
		$result = warquest_db_close();
		$this->assertEquals($result, 1);	
   }
	
	/**
	 * @test Chat api
	 */ 
   public function testChatAPI() {

		echo "testChatAPI()\r\n";
		
		global $config;
		global $popup;

		/* test data */
		$pid1 = 1;
		$pid2 = 2;
		$message = "THis is a test";
		$_SERVER["REMOTE_ADDR"] = "127.0.0.1";
						
		$result = warquest_db_connect($config["dbhost"], $config["dbuser"], $config["dbpass"], $config["dbname"]);
		$this->assertEquals($result, 1);

		$result = warquest_db_chat_insert($pid1, $pid2, $message);
		$this->assertEquals($result, 1);	
						
		$result = warquest_db_close();
		$this->assertEquals($result, 1);	
   }

	/**
	 * @test PlayerPoll api
	 */ 
   public function testPlayerPollAPI() {

		echo "testPlayerPollAPI()\r\n";
		
		global $config;
		global $popup;

		/* test data */
		$pid = 1;
		$poll_id = 2;
		$answer_id = 4;
		$_SERVER["REMOTE_ADDR"] = "127.0.0.1";
						
		$result = warquest_db_connect($config["dbhost"], $config["dbuser"], $config["dbpass"], $config["dbname"]);
		$this->assertEquals($result, 1);

		$result = warquest_db_player_poll_vote_add($pid, $poll_id, $answer_id);
		$this->assertEquals($result, 1);	
		
		$id = warquest_db_player_poll_voted($pid, $poll_id);
		$this->assertEquals($id, $answer_id);	
						
		$result = warquest_db_player_poll_vote_remove($pid, $poll_id);
		$this->assertEquals($result, 1);	
						
		$id = warquest_db_player_poll_voted($pid, $poll_id);
		$this->assertEquals($id, 0);	
		
		$result = warquest_db_close();
		$this->assertEquals($result, 1);	
   }
	
	/**
	 * @test Statistics api
	 */ 
   public function testStatisticsAPI() {

		echo "testStatisticsAPI()\r\n";
		
		global $config;
		global $popup;

		/* test data */
		$now = mktime(date("H"), date("i"), date("s"), date("m"), date("d")-1, date("Y"));
		$request1 = 1;
		$fights1 = 2;
		$fights2 = 20;
		$players1 = 3;
		$logins1 = 4;
		$missions1 = 5;
		$casino1 = 6;
		$gold1 = 6;
		$_SERVER["REMOTE_ADDR"] = "127.0.0.1";
						
		$result = warquest_db_connect($config["dbhost"], $config["dbuser"], $config["dbpass"], $config["dbname"]);
		$this->assertEquals($result, 1);

		$id = warquest_db_statistics_insert($now, $request1, $fights1, $players1, $logins1, $missions1, $gold1, $casino1);
		$this->assertNotEquals($id, 0);	
		
		$stats1 = warquest_db_statistics($now);
		$this->assertEquals($stats1->fights, $fights1);	
					
		$stats1->fights=$fights2;		
		$result = warquest_db_statistics_update($stats1);
		$this->assertEquals($result, 1);	
		
		$stats2 = warquest_db_statistics($now);
		$this->assertEquals($stats2->fights, $fights2);
								
		$value = warquest_db_statistics_count();
		$this->assertEquals($value, 1);	
		
		$result = warquest_db_close();
		$this->assertEquals($result, 1);	
   }
	
	/**
	 * @test Player Unit api
	 */ 
   public function testPlayerUnitAPI() {

		echo "testPlayerUnitAPI()\r\n";
		
		global $config;
		global $popup;

		/* test data */
		$pid = 1;
		$uid = 2;
		$amount1 = 20;
		$amount2 = 30;
		$_SERVER["REMOTE_ADDR"] = "127.0.0.1";
						
		$result = warquest_db_connect($config["dbhost"], $config["dbuser"], $config["dbpass"], $config["dbname"]);
		$this->assertEquals($result, 1);

		$amount = warquest_db_unit_add($pid, $uid, $amount1);
		$this->assertEquals($amount, $amount1);	
		
		$amount = warquest_db_unit_add($pid, $uid, $amount2);
		$this->assertEquals($amount, $amount1+$amount2);	
				
		$result = warquest_db_unit_delete($pid, $uid, $amount2);
		$this->assertEquals($result, 1);	
		
		$result = warquest_db_unit_delete($pid, $uid, $amount1);
		$this->assertEquals($result, 1);	
		
		$amount = warquest_db_unit_add($pid, $uid, $amount1);
		$this->assertEquals($amount, $amount1);	
		
		$amount = warquest_db_unit_add($pid, $uid, $amount2);
		$this->assertEquals($amount, $amount1+$amount2);	
		
		$result = warquest_db_player_unit_delete_all($pid);
		$this->assertEquals($result, 1);	
		
		$result = warquest_db_close();
		$this->assertEquals($result, 1);	
   }
	
	/**
	 * @test Player Building api
	 */ 
   public function testPlayerBuildingAPI() {

		echo "testPlayerBuildingAPI()\r\n";
		
		global $config;
		global $popup;

		/* test data */
		$pid = 1;
		$bid = 2;
		$amount1 = 20;
		$amount2 = 30;
		$name = "test";
		$planet = 1;
		$_SERVER["REMOTE_ADDR"] = "127.0.0.1";
						
		$result = warquest_db_connect($config["dbhost"], $config["dbuser"], $config["dbpass"], $config["dbname"]);
		$this->assertEquals($result, 1);

		$amount = warquest_db_building_add($pid, $bid, $amount1);
		$this->assertEquals($amount, $amount1);	
		
		$amount = warquest_db_building_add($pid, $bid, $amount2);
		$this->assertEquals($amount, $amount1+$amount2);	
								
		$result = warquest_db_player_insert($name, $pid);
		$this->assertEquals($result, 1);	
		
		$player = warquest_db_player($pid);
		
		$value = warquest_db_discount($player, $planet);
		$this->assertEquals($value, 0);
		
		$value = warquest_db_maintenance($player, $planet);
		$this->assertEquals($value, 0);
				
		$result = warquest_db_building_delete($pid, $bid, $amount2);
		$this->assertEquals($result, 1);	
		
		$result = warquest_db_building_delete($pid, $bid, $amount1);
		$this->assertEquals($result, 1);	
				
		$amount = warquest_db_building_add($pid, $bid, $amount1);
		$this->assertEquals($amount, $amount1);	
		
		$amount = warquest_db_building_add($pid, $bid, $amount2);
		$this->assertEquals($amount, $amount1+$amount2);
		
		$result = warquest_db_player_building_delete_all($pid);
		$this->assertEquals($result, 1);	
		
		$result = warquest_db_close();
		$this->assertEquals($result, 1);	
   }
	
	/**
	 * @test invite api
	 */ 
   public function testInviteAPI() {

		echo "testinviteAPI()\r\n";
		
		global $config;
		global $popup;

		/* test data */
		$email = "test@plaatsoft.nl";
		$approved1 = 0;	
		$approved2 = 1;
		$pid = 1;
		
		$_SERVER["REMOTE_ADDR"] = "127.0.0.1";
						
		$result = warquest_db_connect($config["dbhost"], $config["dbuser"], $config["dbpass"], $config["dbname"]);
		$this->assertEquals($result, 1);

		$id = warquest_db_invite_insert($email, $approved1, $pid);
		$this->assertNotEquals($id, 0);	
		
		$data = warquest_db_invite($id);
		$this->assertEquals($data->approved, $approved1);	
		
		$data->approved = $approved2;
		
		$result = warquest_db_invite_update($data);
		$this->assertEquals($result, 1);	
		
		$data = warquest_db_invite($id);
		$this->assertEquals($data->approved, $approved2);	
		
		$count = warquest_db_invite_check($email);
		$this->assertEquals($count, 1);	
		
		$result = warquest_db_close();
		$this->assertEquals($result, 1);	
   }
	
	/**
	* @test ClanMission api
	*/ 
   public function testClanMissionAPI() {

		echo "testClanMissionAPI()\r\n";
		
		global $config;
		global $popup;

		/* test data */
		$cid = 1;				
		$mid = 1;
		$progress = 10;
		
		$_SERVER["REMOTE_ADDR"] = "127.0.0.1";
						
		$result = warquest_db_connect($config["dbhost"], $config["dbuser"], $config["dbpass"], $config["dbname"]);
		$this->assertEquals($result, 1);

		$result = warquest_db_clan_mission_update($cid, $mid, $progress);		
		$this->assertEquals($result, 1);	
		
		$data = warquest_db_clan_mission($cid, $mid);
		$this->assertEquals($data->progress, $progress);	
				
		$result = warquest_db_clan_mission_delete($cid, $mid);
		$this->assertEquals($result, 1);	
		
		$result = warquest_db_close();
		$this->assertEquals($result, 1);	
   }
	
	/**
	 * @test SQL error
	 */ 
   public function testSQLerrror() {

		echo "testErrorAPI()\r\n";
		
		global $config;
		global $popup;

		/* test data */	
		$_SERVER["REMOTE_ADDR"] = "127.0.0.1";
		$level = 3000;
						
		$result = warquest_db_connect($config["dbhost"], $config["dbuser"], $config["dbpass"], $config["dbname"]);
		$this->assertEquals($result, 1);

		$result = warquest_db_level( $level);
		$this->assertEquals($result, 0);	
				
		$result = warquest_db_close();
		$this->assertEquals($result, 1);	
   }
	
	/**
	 * @test drop database tables
	 */ 
   public function testDropDatabaseTables() {
		
		echo "testDropDatabaseTables()\r\n";
		
		global $config;
		global $popup;
		
		/* test data */
		$_SERVER["REMOTE_ADDR"] = "127.0.0.1";
		
		$query = 'DROP TABLE bank, bank_group, battle, battle_award, bonus, bounty, bounty_award, building, building_group, building_unit, 	
			chat, clan, cron, level, member, mission, mission_group, mission_unit, news, player, player_building, player_clan,
			player_mission, player_player, player_poll, player_stock, player_unit, poll, poll_answer, rebel_award, sector, session, skill,
			statistics, stock, stock_group, topic, unit, unit_group, invite, clan_bank, comment, planet, clan_mission, views'; 
			
		$result = warquest_db_connect($config["dbhost"], $config["dbuser"], $config["dbpass"], $config["dbname"]);
		$this->assertEquals($result, 1);
		
		$result = warquest_db_query($query);
		$this->assertEquals($result, 1);	
		
		$result = warquest_db_close();
		$this->assertEquals($result, 1);
	}
}

?>