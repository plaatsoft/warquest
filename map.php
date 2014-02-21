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

include "constants.inc";
include "config.inc";
include "general.inc";

/* 
** -------
** General
** -------
*/

function process_data($data, $image) {
	
	$white = imagecolorallocatealpha($image, 0xff, 0xff, 0xff, 20);
	
	if (strlen($data)>0) {

		$codes = preg_split('/,/',$data);
		foreach($codes as $code) {

			@list($x, $y, $name, $owner, $damage) = preg_split('/-/',$code);
			
			$yoffset=4;
			$xoffset=6;
			if (($y % 2)==0) {
				$xoffset+=44;
			}
								
			$color = 0;	
			if ($owner==1) {
				/* Own area */
				$color = ImageColorAllocatealpha($image, 255, 0, 0, 60);
			} else if ($owner==2) {
				/* Enemy area */
				$color = ImageColorAllocatealpha($image, 0, 255, 0, 60);	
			} else if ($owner==3) {		
				/* Selectable area */
				$color = ImageColorAllocatealpha($image, 255, 165, 0, 60);
			}

			if ($color>0) {
				fillPologon($image, $color, $x, $y);
			}
			
			if (strlen($name)>0) {
				if ($damage>0) {	
					$yoffset-=3;
				}
				imagefttext($image, 7, 0, 20+($x*88)+$xoffset, 20+($y*18)+$yoffset, $white, 'ttf/font.ttf', $name);
			}
							
			if ($damage>0) {
				if (strlen($name)>0) {
					$yoffset+=12;
				}
				imagefttext($image, 7, 0, 27+($x*88)+$xoffset, 20+($y*18)+$yoffset, $white, 'ttf/font.ttf', $damage.'%');	
			}
		}
	}
}

/* 
** ------
** Output 
** ------
*/

$planet = warquest_get('planet', 1);

if ($planet>$config["max_planets"]) {
	$planet=PLANET_EARTH;
}

$data = warquest_get('data', '');

if (isset($_GET['data'])) {

	/* Create server side - PNG image map */

	$image = ImageCreateFromPNG('images/planet/map'.$planet.'a.png');
	AddPologonRaster($image);
	process_data($data, $image);
			
	header('Content-type: image/gif');
	imagegif($image);
	imagedestroy($image);
	
} else {

	/* Create client side - HTML5 canvas map */
	
	$page  = '<html>';
	$page .= '<head>';
	$page .= '</head>';
	$page .= '<body>'; 
	$page .= '<canvas id="myCanvas" width="483" height="300" >HTML5 canvas features are not supported!</canvas>';
	$page .= '<script language="JavaScript" src="js/map.js?version=2"></script>';
	$page .= '<script language="JavaScript">';
	$page .= 'initMap('.$planet.',"'.$config["base_url"].'",'.MENU_SERVICE.');';
	$page .= '</script>';
	$page .= '</body>';
	$page .= '</html>';

	echo $page;
}
	
/* 
** --------------------------
** The End
** --------------------------
*/

?>