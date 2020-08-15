<?php

/*
**  ========
**  WarQuest
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
**  All copyrights reserved (c) PlaatSoft
*/

class WebTest extends PHPUnit_Extensions_Selenium2TestCase {

	private $website = 'http://127.0.0.1/warquest';

   protected function setUp() {
      $this->setBrowser('firefox');
      $this->setBrowserUrl($this->website);
   }

	public function testSourceCanBeRead() {
       $this->url($this->website);
       $source = $this->source();
       $this->assertContains('<body>', $source);
		 $this->assertContains('</body>', $source);
       $this->assertStringEndsWith('</html>', $source);
   }

	public function testLoginPage() {

		$username = "test1";
		$password = "test1";

      $this->url($this->website);

		$this->clickOnElementOnElement('login');
		$this->assertEquals('WarQuest - Member login', $this->title());

		$this->clickOnElementOnElement('registration');
		$this->assertEquals('WarQuest - Free registration', $this->title());

		$this->clickOnElementOnElement('recovery');
		$this->assertEquals('WarQuest - Password recovery', $this->title());

		$this->clickOnElementOnElement('facebook');
		$this->assertEquals('WarQuest - Facebook', $this->title());

		$this->clickOnElementOnElement('login');
		$this->assertEquals('WarQuest - Member login', $this->title());

		$input = $this->byId('myusername');
		$input->value($username);
		$input = $this->byId('mypassword');
		$input->value($password);
		$this->clickOnElementOnElement('do');
		$this->assertEquals('WarQuest - Overview', $this->title());
	}

	 public function testMyTestCase() {


		$username = "test1";
		$password = "test1";

    $this->url($this->website);

	$input = $this->byId('myusername');
	$input->value($username);
	$input = $this->byId('mypassword');
	$input->value($password);

    $this->clickOnElement("do");

    $this->clickOnElement("missions");

    $this->clickOnElement("battle");

    $this->clickOnElement("units");

    $this->clickOnElement("money");

    $this->clickOnElement("alliance");

    $this->clickOnElement("forums");

    $this->clickOnElement("help");

    $this->clickOnElement("release-notes");

    $this->clickOnElement("ranks");

    $this->clickOnElement("awards");

    $this->clickOnElement("levels");

    $this->clickOnElement("stats");

    $this->clickOnElement("donate");

    $this->clickOnElement("about");

    $this->clickOnElement("home");

    $this->clickOnElement("settings");

    $this->clickOnElement("help");

    $this->clickOnElement("release-notes");

    $this->clickOnElement("ranks");

    $this->clickOnElement("awards");

    $this->clickOnElement("levels");

    $this->clickOnElement("stats");

    $this->clickOnElement("donate");

    $this->clickOnElement("about");

    $this->clickOnElement("home");

    $this->clickOnElement("logout");

  }

}
