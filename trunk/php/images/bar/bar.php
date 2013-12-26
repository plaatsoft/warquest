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
** Create all needed warquest progress bars. 
*/

$offset=0;
for ($value=0; $value<=100; $value++) {

	$filename = 'bar'.$value.'.png';

	echo 'Create '.$filename.'<br/>';
	
	$pos = floor((69 / 100) * ($value-($offset*100)));
	
	$im = imagecreate(71, 12);

	$white = imagecolorallocate($im, 255, 255, 255);
	$black = imagecolorallocate($im, 0, 0, 0);
	$orange = imagecolorallocate($im, 255, 165, 0);

	imagesetthickness($im, 2);	
	imagerectangle($im, 0, 0, 71, 12, $white);		
	imagefilledrectangle($im, 1, 1, $pos, 10, $orange);
	imagestring($im, 2, 28, -1, ($value-($offset*100)).'%', $black);
	
	imagepng($im, $filename);

	imagedestroy($im);
	
	if (($value>=100) && ($value%100)==0) {
		$offset++;
	}
}