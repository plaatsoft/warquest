<?php

include 'database.inc';
include 'config.inc';
include 'general.inc';

ini_set('soap.wsdl_cache_enabled', '0');

$server = new SoapServer('test.wsdl');
$server->addFunction('sayHelloWorld');
$server->handle();
 

function sayHelloWorld($string)
{
	global $config;
	
	/* Connect to database */
	warquest_db_connect($config["dbhost"], $config["dbuser"], $config["dbpass"], $config["dbname"]);
			
	$player = warquest_db_player($string);

	return "Hello [" . $player->name . "]";
}
?>