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

include "constants.inc";
include "general.inc";

function process_data($data, $image) {
	
	$white = imagecolorallocatealpha($image, 0xff, 0xff, 0xff, 20);
	
	if (strlen($data)>0) {

		$codes = preg_split('/,/',$data);
		foreach($codes as $code) {

			@list($x, $y, $name, $owner, $damage) = preg_split('/-/',$code);
			
			if (strlen($name)>0) {
			
				$yoffset=4;
				$xoffset=6;
				if (($y % 2)==0) {
					$xoffset+=44;
				}
								
				if ($owner==1) {
					$color = ImageColorAllocatealpha($image, 0, 255, 0, 60);	
				} else if ($owner==2) {
					$color = ImageColorAllocatealpha($image, 255, 165, 0, 80);
				} else {				
					$color = ImageColorAllocatealpha($image, 255, 0, 0, 80);	
				}

				fillPologon($image, $color, $x, $y);
			
				if ($damage>0) {
				
					$yoffset-=3;
				}

				imagefttext($image, 7, 0, 20+($x*88)+$xoffset, 20+($y*18)+$yoffset, $white, 'ttf/font.ttf', $name);
							
				if ($damage>0) {
					imagefttext($image, 7, 0, 27+($x*88)+$xoffset, 30+($y*18)+$yoffset+2, $white, 'ttf/font.ttf', $damage.'%');	
				}
			}
		}
	}
}

/* 
** --------------------------
** Output image as PNG
** --------------------------
*/

$planet = warquest_get('planet', 1);
$data = warquest_get('data', '');

$image = ImageCreateFromPNG('images/planet/map'.$planet.'.png');
AddPologonRaster($image);
process_data($data, $image);
			
header('Content-type: image/gif');
imagegif($image);
imagedestroy($image);

/* 
** --------------------------
** The End
** --------------------------
*/

?>