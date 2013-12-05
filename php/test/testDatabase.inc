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

require_once "../general.inc";
require_once "../config.inc";
require_once "config.inc";
require_once "../database.inc";

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
		$password  = "1234567";
		$email     = "test@plaatsoft.nl";
		$_SERVER["REMOTE_ADDR"] = "127.0.0.1";
				
		$result = warquest_db_connect($config["dbhost"], $config["dbuser"], $config["dbpass"], $config["dbname"]);
		$this->assertEquals($result, 1);
		
		$pid = warquest_db_member_insert($username1, $password, $email);
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
		$_SERVER["REMOTE_ADDR"] = "127.0.0.1";
						
		$result = warquest_db_connect($config["dbhost"], $config["dbuser"], $config["dbpass"], $config["dbname"]);
		$this->assertEquals($result, 1);
		
		$result = warquest_db_player_clan_insert($pid, $cid);
		$this->assertEquals($result, 1);
		
		$player_clan = warquest_db_player_clan($pid);
		$this->assertEquals($player_clan->cid, $cid);
		
		$result = warquest_db_player_clan_delete($pid, $cid);
		$this->assertEquals($result, 1);
		
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
		
		$query = 'DROP TABLE `bank`, `bank_group`, `battle`, `battle_award`, `bonus`, `bounty`, `bounty_award`, `building`, `building_group`, `building_unit`, 	
			`chat`, `clan`, `cron`, `level`, `member`, `mission`, `mission_group`, `mission_unit`, `news`, `player`, `player_building`, `player_clan`,
			`player_mission`, `player_player`, `player_poll`, `player_stock`, `player_unit`, `poll`, `poll_answer`, `rebel_award`, `sector`, `session`, `skill`,
			`statistics`, `stock`, `stock_group`, `topic`, `unit`, `unit_group`;'; 
			
		$result = warquest_db_connect($config["dbhost"], $config["dbuser"], $config["dbpass"], $config["dbname"]);
		$this->assertEquals($result, 1);
		
		$result = warquest_db_query($query);
		$this->assertEquals($result, 1);	
		
		$result = warquest_db_close();
		$this->assertEquals($result, 1);	
	}
}

?>