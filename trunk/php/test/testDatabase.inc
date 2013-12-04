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
require_once "../database.inc";

class TestDatabase extends PHPUnit_Framework_TestCase {
	 
	/**
	* @test member database api
	*/ 
   public function testMemberAPI() {
		
		global $config;
		global $popup;

		/* test data */
		$username1 = "test1";
		$username2 = "test2";
		$password  = "1234567";
		$email     = "test@plaatsoft.nl";
		
		$result = warquest_db_connect($config["dbhost"], $config["dbuser"], $config["dbpass"], $config["dbname"]);
		$this->assertEquals($result, 0);
						
		$pid = warquest_db_member_insert($username1, $password, $email);
		$this->assertNotEquals($pid, 0);
					
		$member1 = warquest_db_member($pid);
		$this->assertEquals($member1->username, $username1);
		$this->assertEquals($member1->pid, $pid);
		$this->assertEquals($member1->email_valid,0);
		
		$member1->username = $username2;
		warquest_db_member_update($member1);
		
		$member2 = warquest_db_member($pid);
		$this->assertEquals($member2->username, $username2);
					
		warquest_db_member_delete($pid);		
		$this->assertEquals(strlen($popup),0);
		
		warquest_db_close();
   }
	
	/**
	* @test player database api
	*/ 
   public function testPlayerAPI() {
		
		global $config;
		global $popup;

		/* test data */
		$name1 = "test1";
		$name2 = "test2";
		$pid = 100000000;
		$_SERVER["REMOTE_ADDR"] = "127.0.0.1";
						
		$result = warquest_db_connect($config["dbhost"], $config["dbuser"], $config["dbpass"], $config["dbname"]);
		$this->assertEquals($result, 0);
		
		/* Clear old data, if any */
		warquest_db_player_delete($pid);	
						
		warquest_db_player_insert($name1, $pid);

		$player1 = warquest_db_player($pid);
		$this->assertEquals($player1->name, $name1);
		$this->assertEquals($player1->pid, $pid);
		
		$player1->name = $name2;
		warquest_db_player_update($player1);
		
		$player2 = warquest_db_player($pid);
		$this->assertEquals($player2->name, $name2);
					
		warquest_db_player_delete($pid);		
		$this->assertEquals(0, strlen($popup));
		
		warquest_db_close();
   }
	
	/**
	* @test skill database api
	*/ 
   public function testSkillAPI() {
		
		global $config;
		global $popup;

		/* test data */
		$pid = 100000000;
		$skill_points1 = 10;
		$skill_points2 = 15;
		$_SERVER["REMOTE_ADDR"] = "127.0.0.1";
						
		$result = warquest_db_connect($config["dbhost"], $config["dbuser"], $config["dbpass"], $config["dbname"]);
		$this->assertEquals($result, 0);
	
		/* Clear old data, if any */
		warquest_db_skill_delete($pid);		
	
		warquest_db_skill_insert($pid, $skill_points1);
		
		$skill1 = warquest_db_skill($pid);
		$this->assertEquals($skill1->skill_points, $skill_points1);
		
		$skill1->skill_points = $skill_points2;
		warquest_db_skill_update($skill1);
		
		$skill2 = warquest_db_skill($pid);
		$this->assertEquals($skill2->skill_points, $skill_points2);
					
		warquest_db_skill_delete($pid);		
		$this->assertEquals(0, strlen($popup));
		
		warquest_db_close();
   }
	
	/**
	* @test news database api
	*/ 
   public function testNewsAPI() {
		
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
		$this->assertEquals($result, 0);
	
		$id = warquest_db_news_insert($body1, $content1, $language1);
		$this->assertNotEquals($id, 0);
		
		$news1 = warquest_db_news($id);
		$this->assertEquals($news1->body, $body1);
		$this->assertEquals($news1->content, $content1);
		$this->assertEquals($news1->language, $language1);
		
		$news1->body = $body2;
		$news1->content = $content2;
		$news1->language = $language2;
		warquest_db_news_update($news1);
		
		$news2 = warquest_db_news($id);
		$this->assertEquals($news2->body, $body2);
		$this->assertEquals($news2->content, $content2);
		$this->assertEquals($news2->language, $language2);	

		warquest_db_news_delete($id);		
		$this->assertEquals(0, strlen($popup));
		
		warquest_db_close();
   }
	
		/**
	* @test news database api
	*/ 
   public function testNewsAPI() {
		
		global $config;
		global $popup;
		
		/* test data */
		$cid = 1;
		$damage = 100;
		$_SERVER["REMOTE_ADDR"] = "127.0.0.1";
						
		$result = warquest_db_connect($config["dbhost"], $config["dbuser"], $config["dbpass"], $config["dbname"]);
		$this->assertEquals($result, 0);
	
		$sector1 = warquest_db_sector($cid);
			
		$sector2 = warquest_db_sector($cid);
		$sector2->cid = $cid;
		$sector2->damage = $damage;
		
		warquest_db_sector_update($sector2);
		
		$sector3 = warquest_db_sector($cid);	
		$this->assertEquals($sector3->cid,$cid);
		$this->assertEquals($sector3->damage,$damage);
		
		warquest_db_sector_update($sector1);
		
		warquest_db_close();
   }
}

?>