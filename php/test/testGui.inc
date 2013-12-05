<?php
class WebTest extends PHPUnit_Extensions_Selenium2TestCase
{	 
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
	
		/* test data */
		$username = "test1";
		$password = "test1";
	
      $this->url($this->website);
       		 
		$this->clickOnElement('login');     
		$this->assertEquals('WarQuest - Member login', $this->title());

		$this->clickOnElement('registration'); 
		$this->assertEquals('WarQuest - Free registration', $this->title());

		$this->clickOnElement('recovery');     
		$this->assertEquals('WarQuest - Password recovery', $this->title());
		 
		$this->clickOnElement('facebook'); 
		$this->assertEquals('WarQuest - Facebook', $this->title());

		$this->clickOnElement('login'); 
		$this->assertEquals('WarQuest - Member login', $this->title());
		
		$input = $this->byId('myusername');
		$input->value($username);		
		$input = $this->byId('mypassword');
		$input->value($password);		
		$this->clickOnElement('do');  		
		$this->assertEquals('WarQuest - Overview', $this->title());
	}

}
?>