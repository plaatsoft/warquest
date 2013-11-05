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

include "general.inc";

function addPologonRaster($image) {

	$black = imagecolorallocatealpha($image, 0, 0, 0, 20);
	$yoffset=0;
	
	for ($y=0; $y<15; $y++) {

		$xoffset=-10;
		if (($y % 2)==0) {
			$xoffset+=50;
		}
			
		for ($x=0; $x<5; $x++) {
		
			$poly = array(	20+($x*100)+$xoffset, 0+($y*20)+$yoffset,
								50+($x*100)+$xoffset, 0+($y*20)+$yoffset,
								70+($x*100)+$xoffset, 20+($y*20)+$yoffset,
								50+($x*100)+$xoffset, 40+($y*20)+$yoffset,
								20+($x*100)+$xoffset, 40+($y*20)+$yoffset,
								0+($x*100)+$xoffset,  20+($y*20)+$yoffset );		  
		  
			/* Draw the polygon */
			imagepolygon($image, $poly, 6, $black);
		}
	}	
}

function fillPologon($image, $color, $x, $y) {

	$black = imagecolorallocatealpha($image, 0, 0, 0, 20); 
	
	$yoffset=0;
	$xoffset=-10;
	if (($y % 2)==0) {
		$xoffset+=50;
	}
	
	$poly = array(	20+($x*100)+$xoffset, 0+($y*20)+$yoffset,
						50+($x*100)+$xoffset, 0+($y*20)+$yoffset,
						70+($x*100)+$xoffset, 20+($y*20)+$yoffset,
						50+($x*100)+$xoffset, 40+($y*20)+$yoffset,
						20+($x*100)+$xoffset, 40+($y*20)+$yoffset,
						0+($x*100)+$xoffset,  20+($y*20)+$yoffset );		  
		 
	imagefilledpolygon($image, $poly, 6, $color);
	imagepolygon($image, $poly, 6, $black);
}


function process_earth_data($data, $image) {

	$border = ImageColorAt($image, 320, 65); 

	$codes = preg_split('/,/',$data);
	foreach($codes as $code) {

	if (strlen($data)>0) {
	
		list($country, $progress) = preg_split('/-/',$code);

		$fill = ImageColorAllocate($image, 0, 255, 0);

		if ($progress==0) {
			$fill = ImageColorAllocate($image, 255, 0, 0);
		}
		
		if (($progress>=100) && ($progress<200)) {
			$fill = ImageColorAllocate($image, 255, 255, 20);
		
		} else if (($progress>=200) && ($progress<300)) {
			$fill = ImageColorAllocate($image, 255, 51, 255);
		
		} else if ($progress==300) {
			$fill = ImageColorAllocate($image, 255, 165, 0);
	
		} 
	}		
	switch ($code) {

	/* 
	** --------------------------
	** Europa (1)
	** --------------------------
	*/

	/* UK + Ireland (1) */
	case 1:
		ImageFillToBorder($image, 440, 100, $border, $fill);
		ImageFillToBorder($image, 423, 108, $border, $fill);
		ImageFillToBorder($image, 427, 101, $border, $fill);
		break;

	/* Benelux (2) */
	case 2:
		ImageFillToBorder($image, 463, 110, $border, $fill);
		ImageFillToBorder($image, 460, 117, $border, $fill);
		ImageFillToBorder($image, 462, 121, $border, $fill);
		break;

	/* France + Malta (3) */
	case 3:
		ImageFillToBorder($image, 455, 132, $border, $fill);
		ImageFillToBorder($image, 471, 159, $border, $fill);
		ImageFillToBorder($image, 472, 151, $border, $fill);
		break;

	/* Central Europe (4) */
	case 4:
		ImageFillToBorder($image, 475, 115, $border, $fill);
		ImageFillToBorder($image, 486, 129, $border, $fill);
		ImageFillToBorder($image, 467, 133, $border, $fill);
		break;

	/* Scandinavia (5) */
	case 5:
		ImageFillToBorder($image, 472, 96, $border, $fill);
		ImageFillToBorder($image, 479, 98, $border, $fill);
		ImageFillToBorder($image, 475, 99, $border, $fill);
		ImageFillToBorder($image, 470, 81, $border, $fill);
		ImageFillToBorder($image, 487, 77, $border, $fill);
		ImageFillToBorder($image, 401, 63, $border, $fill);
		ImageFillToBorder($image, 486, 19, $border, $fill);
		ImageFillToBorder($image, 520, 65, $border, $fill);
		break;

	/* East Europa (6) */
	case 6:
		ImageFillToBorder($image, 517, 86, $border, $fill);
		ImageFillToBorder($image, 517, 92, $border, $fill);
		ImageFillToBorder($image, 514, 98, $border, $fill);
		ImageFillToBorder($image, 507, 101, $border, $fill);
		ImageFillToBorder($image, 500, 110, $border, $fill);
		ImageFillToBorder($image, 523, 107, $border, $fill);
		ImageFillToBorder($image, 522, 117, $border, $fill);
		ImageFillToBorder($image, 489, 120, $border, $fill);
		ImageFillToBorder($image, 500, 124, $border, $fill);
		ImageFillToBorder($image, 490, 135, $border, $fill);
		ImageFillToBorder($image, 501, 131, $border, $fill);
		ImageFillToBorder($image, 493, 136, $border, $fill);
		ImageFillToBorder($image, 497, 143, $border, $fill);
		ImageFillToBorder($image, 506, 142, $border, $fill);
		ImageFillToBorder($image, 502, 148, $border, $fill);
		ImageFillToBorder($image, 507, 149, $border, $fill);
		ImageFillToBorder($image, 504, 156, $border, $fill);
		ImageFillToBorder($image, 510, 153, $border, $fill);
		ImageFillToBorder($image, 518, 149, $border, $fill);
		ImageFillToBorder($image, 528, 130, $border, $fill);
		ImageFillToBorder($image, 518, 135, $border, $fill);
		break;

	/* Spain + Portugal (7) */
	case 7:
		ImageFillToBorder($image, 434, 154, $border, $fill);
		ImageFillToBorder($image, 419, 158, $border, $fill);
		break;
	
	/* Italia + Greece + Turkye (8) */
	case 8:
		ImageFillToBorder($image, 481, 149, $border, $fill);
		ImageFillToBorder($image, 488, 169, $border, $fill);
		ImageFillToBorder($image, 512, 164, $border, $fill);
		ImageFillToBorder($image, 520, 178, $border, $fill);
		ImageFillToBorder($image, 527, 154, $border, $fill);
		ImageFillToBorder($image, 549, 163, $border, $fill);
		ImageFillToBorder($image, 547, 179, $border, $fill);
		break;
		

	/* 
	** --------------------------
	** North America (2)
	** --------------------------
	*/

	/* Greenland (1)  */
	case 10:		
		ImageFillToBorder($image, 384,35, $border, $fill);
		break;

	/* Canada (2) */
	case 11:
		ImageFillToBorder($image, 131,88, $border, $fill);
		ImageFillToBorder($image, 180,44, $border, $fill);
		ImageFillToBorder($image, 195,28, $border, $fill);
		ImageFillToBorder($image, 223,37, $border, $fill);
		ImageFillToBorder($image, 215,49, $border, $fill);
		ImageFillToBorder($image, 232,28, $border, $fill);
		ImageFillToBorder($image, 261,40, $border, $fill);
		ImageFillToBorder($image, 236,35, $border, $fill);
		ImageFillToBorder($image, 251,29, $border, $fill);
		ImageFillToBorder($image, 234,19, $border, $fill);
		ImageFillToBorder($image, 248,21, $border, $fill);
		ImageFillToBorder($image, 270,19, $border, $fill);
		ImageFillToBorder($image, 281,125, $border, $fill);
		ImageFillToBorder($image, 254,139, $border, $fill);
		break;

	/* United States (3) */
	case 12:
		ImageFillToBorder($image, 80, 60, $border, $fill);
		ImageFillToBorder($image, 81, 123, $border, $fill);
		ImageFillToBorder($image, 133, 166, $border, $fill);
		break;

	/* Mexico (4) */
	case 13:
		ImageFillToBorder($image, 105, 231, $border, $fill);
		break;

	/* Guatemala + Honduras (5) */
	case 14:
		ImageFillToBorder($image, 142, 260, $border, $fill);
		ImageFillToBorder($image, 153, 260, $border, $fill);
		break;

	/* Nicaragua + Costa Rica (6) */
	case 15:
		ImageFillToBorder($image, 157, 269, $border, $fill);
		ImageFillToBorder($image, 161, 279, $border, $fill);
		break;

	/* Cuba (7) */
	case 16:
		ImageFillToBorder($image, 176, 229, $border, $fill);
		ImageFillToBorder($image, 188, 247, $border, $fill);
		break;

	/* Caribbean Islands (8) */
	case 17:
		ImageFillToBorder($image, 204, 243, $border, $fill);
		ImageFillToBorder($image, 208, 244, $border, $fill);
		ImageFillToBorder($image, 221, 246, $border, $fill);
		ImageFillToBorder($image, 148, 253, $border, $fill);
		ImageFillToBorder($image, 147, 265, $border, $fill);
		ImageFillToBorder($image, 171, 287, $border, $fill);
		break;

	/* 
	** --------------------------
	** South America (3)
	** --------------------------
	*/

	/* Middle America (1) */
	case 20:
		ImageFillToBorder($image, 193, 303, $border, $fill);
		ImageFillToBorder($image, 220, 292, $border, $fill);
		ImageFillToBorder($image, 244, 298, $border, $fill);
		ImageFillToBorder($image, 254, 305, $border, $fill);
		ImageFillToBorder($image, 265, 308, $border, $fill);
		break;

	/* Ecuador + Peru (2) */
	case 21:
		ImageFillToBorder($image, 180, 329, $border, $fill);
		ImageFillToBorder($image, 195, 340, $border, $fill);
		break;

	/* Bolivia (3) */
	case 22:
		ImageFillToBorder($image, 228, 388, $border, $fill);
		break;

	/* Paraguay (4) */
	case 23:
		ImageFillToBorder($image, 244, 407, $border, $fill);
		break;

	/* Chile (5) */
	case 24:
		ImageFillToBorder($image, 214, 413, $border, $fill);
		break;

	/* Argentina (6) */
	case 25:
		ImageFillToBorder($image, 238, 446, $border, $fill);
		break;

	/* Uruguay (7) */
	case 26:
		ImageFillToBorder($image, 266, 455, $border, $fill);
		break;

	/* Brasil (8) */
	case 27:
		ImageFillToBorder($image, 288, 385, $border, $fill);
		break;

	/* 
	** --------------------------
	** Africa (4)
	** --------------------------
	*/

	/* Morocco + Algeria (1) */
	case 30:
		ImageFillToBorder($image, 449, 205, $border, $fill);
		ImageFillToBorder($image, 421, 191, $border, $fill);
		break;

	/* Libya + Tunisia + Egypt (2) */
	case 31:
		ImageFillToBorder($image, 485, 205, $border, $fill);
		ImageFillToBorder($image, 470, 183, $border, $fill);
		ImageFillToBorder($image, 536, 212, $border, $fill);
		break;

	/* West Africa (3) */
	case 32:
		ImageFillToBorder($image, 396, 221, $border, $fill);
		ImageFillToBorder($image, 404, 242, $border, $fill);
		ImageFillToBorder($image, 393, 261, $border, $fill);
		ImageFillToBorder($image, 414, 264, $border, $fill);
		ImageFillToBorder($image, 471, 252, $border, $fill);
		ImageFillToBorder($image, 391, 272, $border, $fill);
		ImageFillToBorder($image, 400, 275, $border, $fill);
		ImageFillToBorder($image, 400, 287, $border, $fill);
		ImageFillToBorder($image, 409, 294, $border, $fill);
		ImageFillToBorder($image, 421, 290, $border, $fill);
		ImageFillToBorder($image, 434, 270, $border, $fill);
		ImageFillToBorder($image, 437, 285, $border, $fill);
		ImageFillToBorder($image, 444, 285, $border, $fill);
		ImageFillToBorder($image, 448, 285, $border, $fill);
		ImageFillToBorder($image, 465, 285, $border, $fill);
		break;

	/* Central Africa (4) */
	case 33:
		ImageFillToBorder($image, 480, 300, $border, $fill);
		ImageFillToBorder($image, 500, 265, $border, $fill);
		ImageFillToBorder($image, 503, 296, $border, $fill);
		ImageFillToBorder($image, 535, 275, $border, $fill);
		ImageFillToBorder($image, 566, 257, $border, $fill);
		ImageFillToBorder($image, 476, 315, $border, $fill);
		ImageFillToBorder($image, 481, 314, $border, $fill);
		ImageFillToBorder($image, 497, 314, $border, $fill);
		ImageFillToBorder($image, 515, 306, $border, $fill);
		break;

	/* East Africa (5) */
	case 34:
		ImageFillToBorder($image, 568, 281, $border, $fill);
		ImageFillToBorder($image, 600, 281, $border, $fill);
		ImageFillToBorder($image, 548, 312, $border, $fill);
		ImageFillToBorder($image, 540, 328, $border, $fill);
		ImageFillToBorder($image, 540, 335, $border, $fill);
		ImageFillToBorder($image, 566, 317, $border, $fill);
		ImageFillToBorder($image, 555, 344, $border, $fill);
		break;

	/* Angola + Zambia + Mozambique (6) */
	case 35:
		ImageFillToBorder($image, 494, 370, $border, $fill);
		ImageFillToBorder($image, 530, 378, $border, $fill);
		ImageFillToBorder($image, 556, 382, $border, $fill);
		ImageFillToBorder($image, 554, 393, $border, $fill);
		break;

	/* Namibia + Botswana + Zimbabwe (7) */
	case 36:
		ImageFillToBorder($image, 495, 407, $border, $fill);
		ImageFillToBorder($image, 517, 407, $border, $fill);
		ImageFillToBorder($image, 536, 402, $border, $fill);
		break;

	/* South Africa + Madagascar (8) */
	case 37:
		ImageFillToBorder($image, 517, 440, $border, $fill);
		ImageFillToBorder($image, 532, 441, $border, $fill);
		ImageFillToBorder($image, 543, 428, $border, $fill);
		ImageFillToBorder($image, 590, 412, $border, $fill);
		break;

	/* 
	** --------------------------
	** North Asia (5)
	** --------------------------
	*/

	/* Russia (1) */
	case 40:
		ImageFillToBorder($image, 665, 80, $border, $fill);
		ImageFillToBorder($image, 583, 32, $border, $fill);
		ImageFillToBorder($image, 650, 15, $border, $fill);
		ImageFillToBorder($image, 670, 19, $border, $fill);
		ImageFillToBorder($image, 764, 29, $border, $fill);
		ImageFillToBorder($image, 786, 29, $border, $fill);
		ImageFillToBorder($image, 858, 119, $border, $fill);
		ImageFillToBorder($image, 866, 132, $border, $fill);
		break;

	/* Mongolia (2) */
	case 41:
		ImageFillToBorder($image, 747, 133, $border, $fill);
		break;

	/* Kazakhstan (3) */
	case 42:
		ImageFillToBorder($image, 643, 125, $border, $fill);
		break;

	/* Uzbekihstan (4) */
	case 43:
		ImageFillToBorder($image, 636, 153, $border, $fill);
		ImageFillToBorder($image, 670, 153, $border, $fill);
		break;

	/* Takikistan (5) */
	case 44:
		ImageFillToBorder($image, 656, 164, $border, $fill);
		break;

	/* Turkmenistan (6) */
	case 45:
		ImageFillToBorder($image, 623, 162, $border, $fill);
		break;

	/* Georgia (7) */
	case 46:
		ImageFillToBorder($image, 576, 150, $border, $fill);
		break;

	/* Armenia + Azerbaijan (8) */
	case 47:
		ImageFillToBorder($image, 580, 157, $border, $fill);
		ImageFillToBorder($image, 589, 157, $border, $fill);
		break;

	/* 
	** --------------------------
	** South Asia (6)
	** --------------------------
	*/

	/* Iran (1) */
	case 50:
		ImageFillToBorder($image, 612, 189, $border, $fill);
		break;

	/* Afghanistan (2) */
	case 51:
		ImageFillToBorder($image, 650, 184, $border, $fill);
		break;

	/* Pakistan (3) */
	case 52:
		ImageFillToBorder($image, 663, 201, $border, $fill);
		break;

	/* India + Srilanka (4) */
	case 53:
		ImageFillToBorder($image, 696, 232, $border, $fill);
		ImageFillToBorder($image, 708, 291, $border, $fill);
		break;

	/* Nepal (5) */
	case 54:
		ImageFillToBorder($image, 708, 206, $border, $fill);
		break;

	/* Bangladesh + Bhutan (6) */
	case 55:
		ImageFillToBorder($image, 731, 224, $border, $fill);
		ImageFillToBorder($image, 731, 216, $border, $fill);
		ImageFillToBorder($image, 733, 211, $border, $fill);
		break;

	/* Myanmar + Thailand  (7) */
	case 56:
		ImageFillToBorder($image, 753, 235, $border, $fill);
		ImageFillToBorder($image, 773, 257, $border, $fill);
		break;

	/* Loa (8) */
	case 57:		
		ImageFillToBorder($image, 775, 246, $border, $fill);

		break;

	/* 
	** --------------------------
	** East Asia (7)
	** --------------------------
	*/

	/* China (1) */
	case 60:
		ImageFillToBorder($image, 766, 184, $border, $fill);
		break;

	/* North Korea (2) */
	case 61:
		ImageFillToBorder($image, 832, 162, $border, $fill);
		break;

	/* South Korea (3) */
	case 62:
		ImageFillToBorder($image, 842, 175, $border, $fill);
		break;

	/* Japan (4) */
	case 63:
		ImageFillToBorder($image, 877, 173, $border, $fill);
		ImageFillToBorder($image, 876, 146, $border, $fill);
		ImageFillToBorder($image, 858, 189, $border, $fill);
		ImageFillToBorder($image, 864, 185, $border, $fill);
		break;

	/* Taiwan (5) */
	case 64:
		ImageFillToBorder($image, 834, 226, $border, $fill);
		break;

	/* Cambodia (6) */
	case 65:
		ImageFillToBorder($image, 787, 271, $border, $fill);
		break;

	/* VietNam (7) */
	case 66:
		ImageFillToBorder($image, 798, 267, $border, $fill);
		break;

	/* Malaysia (8) */
	case 67:
		ImageFillToBorder($image, 780, 302, $border, $fill);
		ImageFillToBorder($image, 817, 309, $border, $fill);
		break;

	/* 
	** --------------------------
	** Oceania (8)
	** --------------------------
	*/

	/* (1) West Indonesia  */
	case 70:
		ImageFillToBorder($image, 781, 327, $border, $fill);
		ImageFillToBorder($image, 808, 350, $border, $fill);
		ImageFillToBorder($image, 823, 354, $border, $fill);
		ImageFillToBorder($image, 830, 356, $border, $fill);		
		break;
	
	/* (2) East Indonesia  */
	case 71:
		ImageFillToBorder($image, 818, 323, $border, $fill);
		ImageFillToBorder($image, 838, 360, $border, $fill);
		ImageFillToBorder($image, 842, 355, $border, $fill);
		ImageFillToBorder($image, 853, 359, $border, $fill);
		ImageFillToBorder($image, 839, 331, $border, $fill);
		ImageFillToBorder($image, 844, 317, $border, $fill);
		ImageFillToBorder($image, 867, 317, $border, $fill);		
		ImageFillToBorder($image, 861, 334, $border, $fill);
		ImageFillToBorder($image, 871, 333, $border, $fill);
		ImageFillToBorder($image, 901, 337, $border, $fill);
				
		break;

	/* (3) Philipines */
	case 72:
		ImageFillToBorder($image, 839, 255, $border, $fill);
		ImageFillToBorder($image, 841, 268, $border, $fill);
		ImageFillToBorder($image, 845, 265, $border, $fill);
		ImageFillToBorder($image, 849, 266, $border, $fill);
		ImageFillToBorder($image, 846, 274, $border, $fill);
		ImageFillToBorder($image, 854, 273, $border, $fill);
		ImageFillToBorder($image, 849, 280, $border, $fill);
		ImageFillToBorder($image, 852, 278, $border, $fill);
		ImageFillToBorder($image, 855, 288, $border, $fill);		
		break;
		
	/* (4) Papua New Guinea */
	case 73:
		ImageFillToBorder($image, 919, 343, $border, $fill);
		ImageFillToBorder($image, 941, 344, $border, $fill);
		ImageFillToBorder($image, 949, 336, $border, $fill);
		break;
	
	/* (5) Timor */
	case 74:
		ImageFillToBorder($image, 856, 357, $border, $fill);
		break;	
		
	/* (7) North Australia */
	case 75:
		ImageFillToBorder($image, 900, 453, $border, $fill);
		break;
		
	/* (6) South Australia */
	case 76:
		ImageFillToBorder($image, 891, 490, $border, $fill);
		break;
		
	/* (8) New Zealand */
	case 77:
		ImageFillToBorder($image, 984, 477, $border, $fill);
		ImageFillToBorder($image, 955, 498, $border, $fill);
		break;
				
	/* 
	** --------------------------
	** Middleast (9)
	** --------------------------
	*/
	
	/* (1) Syrian + Lebonon */
	case 80:
		ImageFillToBorder($image, 563, 181, $border, $fill);
		ImageFillToBorder($image, 556, 184, $border, $fill);
		break;
	
	/* (2) Iraq */
	case 81:
		ImageFillToBorder($image, 576, 185, $border, $fill);
		break;

	/* (3) Saudi Arabia */
	case 82:
		ImageFillToBorder($image, 578, 220, $border, $fill);
		break;
		
	/* (4) Kuwait */
	case 83:
		ImageFillToBorder($image, 593, 202, $border, $fill);		
		break;
	
	/* (5) Yemen */
	case 84:
		ImageFillToBorder($image, 602, 256, $border, $fill);
		break;	
		
	/* (6) Oman + Arab Emirates */
	case 85:
		ImageFillToBorder($image, 624, 245, $border, $fill);
		ImageFillToBorder($image, 619, 226, $border, $fill);
		break;
		
	/* (7) Jordan */
	case 86:
		ImageFillToBorder($image, 558, 196, $border, $fill);
		break;
		
	/* (8) Israel */
	case 87:
		ImageFillToBorder($image, 552, 197, $border, $fill);
		ImageFillToBorder($image, 554, 194, $border, $fill);
		break;
	}
		
	}
}

function process_moon_data($data, $image) {
	
	if (strlen($data)>0) {

		$codes = preg_split('/,/',$data);
		foreach($codes as $code) {

			list($country, $progress) = preg_split('/-/',$code);

			if ($progress==0) {
				$fill = ImageColorAllocatealpha($image, 255, 0, 0, 80);		
			} else if (($progress>0) && ($progress<100)) {
				continue;
			} else if (($progress>=100) && ($progress<200)) {
				$fill = ImageColorAllocatealpha($image, 255, 255, 20, 80);		
			} else if (($progress>=200) && ($progress<300)) {
				$fill = ImageColorAllocatealpha($image, 255, 51, 255, 80);		
			} else if ($progress>=300) {
				$fill = ImageColorAllocatealpha($image, 255, 165, 0, 80);	
			} 
			
		switch ($country) {
			
			/* Alfa */
			case 100: fillPologon($image, $fill, 0, 0);
						 break;

			case 101: fillPologon($image, $fill, 1, 1);
						 break;
						 
	 		case 102: fillPologon($image, $fill, 0, 1);
						 break;
						 
			case 103: fillPologon($image, $fill, 1, 3);
						 break;
						 
			case 104: fillPologon($image, $fill, 0, 2);
						 break;
						 
			case 105: fillPologon($image, $fill, 0, 4);
						 break;

			case 106: fillPologon($image, $fill, 1, 0);
						 break;
						 
			case 107: fillPologon($image, $fill, 0, 3);
						 break;
						 
			
			/* Beta */
			case 110: fillPologon($image, $fill, 0, 5);
						 break;

			case 111: fillPologon($image, $fill, 0, 6);
						 break;
						 
	 		case 112: fillPologon($image, $fill, 1, 5);
						 break;
						 
			case 113: fillPologon($image, $fill, 1, 2);
						 break;
						 
			case 114: fillPologon($image, $fill, 1, 4);
						 break;
						 
			case 115: fillPologon($image, $fill, 0, 7);
						 break;

			case 116: fillPologon($image, $fill, 0, 8);
						 break;
						 
			case 117: fillPologon($image, $fill, 1, 7);
						 break;
						 
						 
			/* Carlie */
			case 120: fillPologon($image, $fill, 0, 9);
						 break;

			case 121: fillPologon($image, $fill, 0, 11);
						 break;
						 
	 		case 122: fillPologon($image, $fill, 0, 13);
						 break;
						 
			case 123: fillPologon($image, $fill, 0, 10);
						 break;
						 
			case 124: fillPologon($image, $fill, 0, 12);
						 break;
						 
			case 125: fillPologon($image, $fill, 0, 14);
						 break;

			case 126: fillPologon($image, $fill, 1, 9);
						 break;
						 
			case 127: fillPologon($image, $fill, 1, 11);
						 break;
						 
			/* Delta */
			case 130: fillPologon($image, $fill, 2, 1);
						 break;

			case 131: fillPologon($image, $fill, 2, 3);
						 break;
						 
	 		case 132: fillPologon($image, $fill, 2, 5);
						 break;
						 
			case 133: fillPologon($image, $fill, 1, 6);
						 break;
						 
			case 134: fillPologon($image, $fill, 2, 7);
						 break;
						 
			case 135: fillPologon($image, $fill, 1, 8);
						 break;

			case 136: fillPologon($image, $fill, 1, 10);
						 break;
						 
			case 137: fillPologon($image, $fill, 1, 12);
						 break;
						 
			/* E cho */
			case 140: fillPologon($image, $fill, 1, 13);
						 break;

			case 141: fillPologon($image, $fill, 1, 14);
						 break;
						 
	 		case 142: fillPologon($image, $fill, 2, 13);
						 break;
						 
			case 143: fillPologon($image, $fill, 2, 11);
						 break;
						 
			case 144: fillPologon($image, $fill, 2, 9);
						 break;
						 
			case 145: fillPologon($image, $fill, 2, 8);
						 break;

			case 146: fillPologon($image, $fill, 2, 6);
						 break;
						 
			case 147: fillPologon($image, $fill, 3, 7);
						 break;
						 
			/* Foxtrot */
			case 150: fillPologon($image, $fill, 2, 14);
						 break;

			case 151: fillPologon($image, $fill, 3, 13);
						 break;
						 
	 		case 152: fillPologon($image, $fill, 2, 12);
						 break;
						 
			case 153: fillPologon($image, $fill, 3, 11);
						 break;
						 
			case 154: fillPologon($image, $fill, 2, 10);
						 break;
						 
			case 155: fillPologon($image, $fill, 3, 9);
						 break;

			case 156: fillPologon($image, $fill, 3, 10);
						 break;
						 
			case 157: fillPologon($image, $fill, 3, 12);
						 break;
						 
			/* Golf */
			case 160: fillPologon($image, $fill, 3, 14);
						 break;

			case 161: fillPologon($image, $fill, 4, 13);
						 break;
						 
	 		case 162: fillPologon($image, $fill, 4, 14);
						 break;
						 
			case 163: fillPologon($image, $fill, 4, 12);
						 break;
						 
			case 164: fillPologon($image, $fill, 4, 11);
						 break;
						 
			case 165: fillPologon($image, $fill, 4, 10);
						 break;

			case 166: fillPologon($image, $fill, 4, 9);
						 break;
						 
			case 167: fillPologon($image, $fill, 4, 8);
						 break;
						 
			/* Hotel */
			case 170: fillPologon($image, $fill, 3, 8);
						 break;

			case 171: fillPologon($image, $fill, 4, 7);
						 break;
						 
	 		case 172: fillPologon($image, $fill, 4, 6);
						 break;
						 
			case 173: fillPologon($image, $fill, 4, 4);
						 break;
						 
			case 174: fillPologon($image, $fill, 4, 5);
						 break;
						 
			case 175: fillPologon($image, $fill, 3, 6);
						 break;

			case 176: fillPologon($image, $fill, 4, 3);
						 fillPologon($image, $fill, 4, 1);
						 break;
						 
			case 177: fillPologon($image, $fill, 4, 2);
						 fillPologon($image, $fill, 4, 0);
						 break;

			/* Lima */
			case 180: fillPologon($image, $fill, 2, 0);
						 break;

			case 181: fillPologon($image, $fill, 2, 2);
						 break;
						 
	 		case 182: fillPologon($image, $fill, 2, 4);
						 break;
						 
			case 183: fillPologon($image, $fill, 3, 1);
						 break;
						 
			case 184: fillPologon($image, $fill, 3, 3);
						 break;
						 
			case 185: fillPologon($image, $fill, 3, 5);
						 break;

			case 186: fillPologon($image, $fill, 3, 0);
						 break;
						 
			case 187: fillPologon($image, $fill, 3, 2);
						 fillPologon($image, $fill, 3, 4);
						 break;
						 
			}		 
		}
	}
}

function process_mars_data($data, $image) {
	
	if (strlen($data)>0) {

		$codes = preg_split('/,/',$data);
		foreach($codes as $code) {

			list($country, $progress) = preg_split('/-/',$code);

			if ($progress==0) {
				$fill = ImageColorAllocatealpha($image, 255, 0, 0, 80);		
			} else if (($progress>0) && ($progress<100)) {
				continue;
			} else if (($progress>=100) && ($progress<200)) {
				$fill = ImageColorAllocatealpha($image, 255, 255, 20, 80);		
			} else if (($progress>=200) && ($progress<300)) {
				$fill = ImageColorAllocatealpha($image, 255, 51, 255, 80);		
			} else if ($progress>=300) {
				$fill = ImageColorAllocatealpha($image, 255, 165, 0, 80);	
			} 
			
		switch ($country) {
			
			/* Alfa */
			case 200: fillPologon($image, $fill, 0, 0);
						 break;

			case 201: fillPologon($image, $fill, 1, 1);
						 break;
						 
	 		case 202: fillPologon($image, $fill, 0, 1);
						 break;
						 
			case 203: fillPologon($image, $fill, 1, 3);
						 break;
						 
			case 204: fillPologon($image, $fill, 0, 2);
						 break;
						 
			case 205: fillPologon($image, $fill, 0, 4);
						 break;

			case 206: fillPologon($image, $fill, 1, 0);
						 break;
						 
			case 207: fillPologon($image, $fill, 0, 3);
						 break;
						 
			
			/* Beta */
			case 210: fillPologon($image, $fill, 0, 5);
						 break;

			case 211: fillPologon($image, $fill, 0, 6);
						 break;
						 
	 		case 212: fillPologon($image, $fill, 1, 5);
						 break;
						 
			case 213: fillPologon($image, $fill, 1, 2);
						 break;
						 
			case 214: fillPologon($image, $fill, 1, 4);
						 break;
						 
			case 215: fillPologon($image, $fill, 0, 7);
						 break;

			case 216: fillPologon($image, $fill, 0, 8);
						 break;
						 
			case 217: fillPologon($image, $fill, 1, 7);
						 break;
						 
						 
			/* Carlie */
			case 220: fillPologon($image, $fill, 0, 9);
						 break;

			case 221: fillPologon($image, $fill, 0, 11);
						 break;
						 
	 		case 222: fillPologon($image, $fill, 0, 13);
						 break;
						 
			case 223: fillPologon($image, $fill, 0, 10);
						 break;
						 
			case 224: fillPologon($image, $fill, 0, 12);
						 break;
						 
			case 225: fillPologon($image, $fill, 0, 14);
						 break;

			case 226: fillPologon($image, $fill, 1, 9);
						 break;
						 
			case 227: fillPologon($image, $fill, 1, 11);
						 break;
						 
			/* Delta */
			case 230: fillPologon($image, $fill, 2, 1);
						 break;

			case 231: fillPologon($image, $fill, 2, 3);
						 break;
						 
	 		case 232: fillPologon($image, $fill, 2, 5);
						 break;
						 
			case 233: fillPologon($image, $fill, 1, 6);
						 break;
						 
			case 234: fillPologon($image, $fill, 2, 7);
						 break;
						 
			case 235: fillPologon($image, $fill, 1, 8);
						 break;

			case 236: fillPologon($image, $fill, 1, 10);
					    break;
						 
			case 237: fillPologon($image, $fill, 1, 12);
						 break;
						 
			/* Echo */
			case 240: fillPologon($image, $fill, 1, 13);
						 break;

			case 241: fillPologon($image, $fill, 1, 14);
						 break;
						 
	 		case 242: fillPologon($image, $fill, 2, 13);
						 break;
						 
			case 243: fillPologon($image, $fill, 2, 11);
						 break;
						 
			case 244: fillPologon($image, $fill, 2, 9);
						 break;
						 
			case 245: fillPologon($image, $fill, 2, 8);
						 break;

			case 246: fillPologon($image, $fill, 2, 6);
						 break;
						 
			case 247: fillPologon($image, $fill, 3, 7);
						 break;
						 
			/* Foxtrot */
			case 250: fillPologon($image, $fill, 2, 14);
						 break;

			case 251: fillPologon($image, $fill, 3, 13);
						 break;
						 
	 		case 252: fillPologon($image, $fill, 2, 12);
						 break;
						 
			case 253: fillPologon($image, $fill, 3, 11);
						 break;
						 
			case 254: fillPologon($image, $fill, 2, 10);
						 break;
						 
			case 255: fillPologon($image, $fill, 3, 9);
						 break;

			case 256: fillPologon($image, $fill, 3, 10);
						 break;
						 
			case 257: fillPologon($image, $fill, 3, 12);
						 break;
						 
			/* Golf */
			case 260: fillPologon($image, $fill, 3, 14);
						 break;

			case 261: fillPologon($image, $fill, 4, 13);
						 break;
						 
	 		case 262: fillPologon($image, $fill, 4, 14);
						 break;
						 
			case 263: fillPologon($image, $fill, 4, 12);
						 break;
						 
			case 264: fillPologon($image, $fill, 4, 11);
						 break;
						 
			case 265: fillPologon($image, $fill, 4, 10);
						 break;

			case 266: fillPologon($image, $fill, 4, 9);
						 break;
						 
			case 267: fillPologon($image, $fill, 4, 8);
						 break;
						 
			/* Hotel */
			case 270: fillPologon($image, $fill, 3, 8);
						 break;

			case 271: fillPologon($image, $fill, 4, 7);
						 break;
						 
	 		case 272: fillPologon($image, $fill, 4, 6);
						 break;
						 
			case 273: fillPologon($image, $fill, 4, 4);
						 break;
						 
			case 274: fillPologon($image, $fill, 4, 5);
						 break;
						 
			case 275: fillPologon($image, $fill, 3, 6);
						 break;

			case 276: fillPologon($image, $fill, 4, 3);
						 fillPologon($image, $fill, 4, 1);
						 break;
						 
			case 277: fillPologon($image, $fill, 4, 2);
						 fillPologon($image, $fill, 4, 0);
						 break;

			/* Lima */
			case 280: fillPologon($image, $fill, 2, 0);
						 break;

			case 281: fillPologon($image, $fill, 2, 2);
						 break;
						 
	 		case 282: fillPologon($image, $fill, 2, 4);
						 break;
						 
			case 283: fillPologon($image, $fill, 3, 1);
						 break;
						 
			case 284: fillPologon($image, $fill, 3, 3);
						 break;
						 
			case 285: fillPologon($image, $fill, 3, 5);
						 break;

			case 286: fillPologon($image, $fill, 3, 0);
						 break;
						 
			case 287: fillPologon($image, $fill, 3, 2);
						 fillPologon($image, $fill, 3, 4);
						 break;
						 
			}		 
		}
	}
}

function process_astroid_data($data, $image) {
	
	if (strlen($data)>0) {

		$codes = preg_split('/,/',$data);
		foreach($codes as $code) {

			list($country, $progress) = preg_split('/-/',$code);

			if ($progress==0) {
				$fill = ImageColorAllocatealpha($image, 255, 0, 0, 80);		
			} else if (($progress>0) && ($progress<100)) {
				continue;
			} else if (($progress>=100) && ($progress<200)) {
				$fill = ImageColorAllocatealpha($image, 255, 255, 20, 80);		
			} else if (($progress>=200) && ($progress<300)) {
				$fill = ImageColorAllocatealpha($image, 255, 51, 255, 80);		
			} else if ($progress>=300) {
				$fill = ImageColorAllocatealpha($image, 255, 165, 0, 80);	
			} 
			
		switch ($country) {
			
			/* Alfa */
			case 300: fillPologon($image, $fill, 0, 0);
						 break;

			case 301: fillPologon($image, $fill, 1, 1);
						 break;
						 
	 		case 302: fillPologon($image, $fill, 0, 1);
						 break;
						 
			case 303: fillPologon($image, $fill, 1, 3);
						 break;
						 
			case 304: fillPologon($image, $fill, 0, 2);
						 break;
						 
			case 305: fillPologon($image, $fill, 0, 4);
						 break;

			case 306: fillPologon($image, $fill, 1, 0);
						 break;
						 
			case 307: fillPologon($image, $fill, 0, 3);
						 break;
						 
			
			/* Beta */
			case 310: fillPologon($image, $fill, 0, 5);
						 break;

			case 311: fillPologon($image, $fill, 0, 6);
						 break;
						 
	 		case 312: fillPologon($image, $fill, 1, 5);
						 break;
						 
			case 313: fillPologon($image, $fill, 1, 2);
						 break;
						 
			case 314: fillPologon($image, $fill, 1, 4);
						 break;
						 
			case 315: fillPologon($image, $fill, 0, 7);
						 break;

			case 316: fillPologon($image, $fill, 0, 8);
						 break;
						 
			case 317: fillPologon($image, $fill, 1, 7);
						 break;
						 
						 
			/* Carlie */
			case 320: fillPologon($image, $fill, 0, 9);
						 break;

			case 321: fillPologon($image, $fill, 0, 11);
						 break;
						 
	 		case 322: fillPologon($image, $fill, 0, 13);
						 break;
						 
			case 323: fillPologon($image, $fill, 0, 10);
						 break;
						 
			case 324: fillPologon($image, $fill, 0, 12);
						 break;
						 
			case 325: fillPologon($image, $fill, 0, 14);
						 break;

			case 326: fillPologon($image, $fill, 1, 9);
						 break;
						 
			case 327: fillPologon($image, $fill, 1, 11);
						 break;
						 
			/* Delta */
			case 330: fillPologon($image, $fill, 2, 1);
						 break;

			case 331: fillPologon($image, $fill, 2, 3);
						 break;
						 
	 		case 332: fillPologon($image, $fill, 2, 5);
						 break;
						 
			case 333: fillPologon($image, $fill, 1, 6);
						 break;
						 
			case 334: fillPologon($image, $fill, 2, 7);
						 break;
						 
			case 335: fillPologon($image, $fill, 1, 8);
						 break;

			case 336: fillPologon($image, $fill, 1, 10);
					    break;
						 
			case 337: fillPologon($image, $fill, 1, 12);
						 break;
						 
			/* Echo */
			case 340: fillPologon($image, $fill, 1, 13);
						 break;

			case 341: fillPologon($image, $fill, 1, 14);
						 break;
						 
	 		case 342: fillPologon($image, $fill, 2, 13);
						 break;
						 
			case 343: fillPologon($image, $fill, 2, 11);
						 break;
						 
			case 344: fillPologon($image, $fill, 2, 9);
						 break;
						 
			case 345: fillPologon($image, $fill, 2, 8);
						 break;

			case 346: fillPologon($image, $fill, 2, 6);
						 break;
						 
			case 347: fillPologon($image, $fill, 3, 7);
						 break;
						 
			/* Foxtrot */
			case 350: fillPologon($image, $fill, 2, 14);
						 break;

			case 351: fillPologon($image, $fill, 3, 13);
						 break;
						 
	 		case 352: fillPologon($image, $fill, 2, 12);
						 break;
						 
			case 353: fillPologon($image, $fill, 3, 11);
						 break;
						 
			case 354: fillPologon($image, $fill, 2, 10);
						 break;
						 
			case 355: fillPologon($image, $fill, 3, 9);
						 break;

			case 356: fillPologon($image, $fill, 3, 10);
						 break;
						 
			case 357: fillPologon($image, $fill, 3, 12);
						 break;
						 
						 
			/* Golf */
			case 360: fillPologon($image, $fill, 3, 14);
						 break;

			case 361: fillPologon($image, $fill, 4, 13);
						 break;
						 
	 		case 362: fillPologon($image, $fill, 4, 14);
						 break;
						 
			case 363: fillPologon($image, $fill, 4, 12);
						 break;
						 
			case 364: fillPologon($image, $fill, 4, 11);
						 break;
						 
			case 365: fillPologon($image, $fill, 4, 10);
						 break;

			case 366: fillPologon($image, $fill, 4, 9);
						 break;
						 
			case 367: fillPologon($image, $fill, 4, 8);
						 break;
						 
			/* Hotel */
			case 370: fillPologon($image, $fill, 3, 8);
						 break;

			case 371: fillPologon($image, $fill, 4, 7);
						 break;
						 
	 		case 372: fillPologon($image, $fill, 4, 6);
						 break;
						 
			case 373: fillPologon($image, $fill, 4, 4);
						 break;
						 
			case 374: fillPologon($image, $fill, 4, 5);
						 break;
						 
			case 375: fillPologon($image, $fill, 3, 6);
						 break;

			case 376: fillPologon($image, $fill, 4, 3);
						 fillPologon($image, $fill, 4, 1);
						 break;
						 
			case 377: fillPologon($image, $fill, 4, 2);
						 fillPologon($image, $fill, 4, 0);
						 break;

			/* Lima */
			case 380: fillPologon($image, $fill, 2, 0);
						 break;

			case 381: fillPologon($image, $fill, 2, 2);
						 break;
						 
	 		case 382: fillPologon($image, $fill, 2, 4);
						 break;
						 
			case 383: fillPologon($image, $fill, 3, 1);
						 break;
						 
			case 384: fillPologon($image, $fill, 3, 3);
						 break;
						 
			case 385: fillPologon($image, $fill, 3, 5);
						 break;

			case 386: fillPologon($image, $fill, 3, 0);
						 break;
						 
			case 387: fillPologon($image, $fill, 3, 2);
						 fillPologon($image, $fill, 3, 4);
						 break;
						 
			}		 
		}
	}
}

function process_sun_data($data, $image) {
	
	if (strlen($data)>0) {

		$codes = preg_split('/,/',$data);
		foreach($codes as $code) {

			list($country, $progress) = preg_split('/-/',$code);

			if ($progress==0) {
				$fill = ImageColorAllocatealpha($image, 255, 0, 0, 80);		
			} else if (($progress>0) && ($progress<100)) {
				continue;
			} else if (($progress>=100) && ($progress<200)) {
				$fill = ImageColorAllocatealpha($image, 255, 255, 20, 80);		
			} else if (($progress>=200) && ($progress<300)) {
				$fill = ImageColorAllocatealpha($image, 255, 51, 255, 80);		
			} else if ($progress>=300) {
				$fill = ImageColorAllocatealpha($image, 255, 165, 0, 80);	
			} 
			
		switch ($country) {
			
			/* Alfa */
			case 400: fillPologon($image, $fill, 0, 0);
						 break;

			case 401: fillPologon($image, $fill, 1, 1);
						 break;
						 
	 		case 402: fillPologon($image, $fill, 0, 1);
						 break;
						 
			case 403: fillPologon($image, $fill, 1, 3);
						 break;
						 
			case 404: fillPologon($image, $fill, 0, 2);
						 break;
						 
			case 405: fillPologon($image, $fill, 0, 4);
						 break;

			case 406: fillPologon($image, $fill, 1, 0);
						 break;
						 
			case 407: fillPologon($image, $fill, 0, 3);
						 break;
						 
			
			/* Beta */
			case 410: fillPologon($image, $fill, 0, 5);
						 break;

			case 411: fillPologon($image, $fill, 0, 6);
						 break;
						 
	 		case 412: fillPologon($image, $fill, 1, 5);
						 break;
						 
			case 413: fillPologon($image, $fill, 1, 2);
						 break;
						 
			case 414: fillPologon($image, $fill, 1, 4);
						 break;
						 
			case 415: fillPologon($image, $fill, 0, 7);
						 break;

			case 416: fillPologon($image, $fill, 0, 8);
						 break;
						 
			case 417: fillPologon($image, $fill, 1, 7);
						 break;
						 
						 
			/* Carlie */
			case 420: fillPologon($image, $fill, 0, 9);
						 break;

			case 421: fillPologon($image, $fill, 0, 11);
						 break;
						 
	 		case 422: fillPologon($image, $fill, 0, 13);
						 break;
						 
			case 423: fillPologon($image, $fill, 0, 10);
						 break;
						 
			case 424: fillPologon($image, $fill, 0, 12);
						 break;
						 
			case 425: fillPologon($image, $fill, 0, 14);
						 break;

			case 426: fillPologon($image, $fill, 1, 9);
						 break;
						 
			case 427: fillPologon($image, $fill, 1, 11);
						 break;
						 
			/* Delta */
			case 430: fillPologon($image, $fill, 2, 1);
						 break;

			case 431: fillPologon($image, $fill, 2, 3);
						 break;
						 
	 		case 432: fillPologon($image, $fill, 2, 5);
						 break;
						 
			case 433: fillPologon($image, $fill, 1, 6);
						 break;
						 
			case 434: fillPologon($image, $fill, 2, 7);
						 break;
						 
			case 435: fillPologon($image, $fill, 1, 8);
						 break;

			case 436: fillPologon($image, $fill, 1, 10);
					    break;
						 
			case 437: fillPologon($image, $fill, 1, 12);
						 break;
						 
			/* Echo */
			case 440: fillPologon($image, $fill, 1, 13);
						 break;

			case 441: fillPologon($image, $fill, 1, 14);
						 break;
						 
	 		case 442: fillPologon($image, $fill, 2, 13);
						 break;
						 
			case 443: fillPologon($image, $fill, 2, 11);
						 break;
						 
			case 444: fillPologon($image, $fill, 2, 9);
						 break;
						 
			case 445: fillPologon($image, $fill, 2, 8);
						 break;

			case 446: fillPologon($image, $fill, 2, 6);
						 break;
						 
			case 447: fillPologon($image, $fill, 3, 7);
						 break;
						 
			/* Foxtrot */
			case 450: fillPologon($image, $fill, 2, 14);
						 break;

			case 451: fillPologon($image, $fill, 3, 13);
						 break;
						 
	 		case 452: fillPologon($image, $fill, 2, 12);
						 break;
						 
			case 453: fillPologon($image, $fill, 3, 11);
						 break;
						 
			case 454: fillPologon($image, $fill, 2, 10);
						 break;
						 
			case 455: fillPologon($image, $fill, 3, 9);
						 break;

			case 456: fillPologon($image, $fill, 3, 10);
						 break;
						 
			case 457: fillPologon($image, $fill, 3, 12);
						 break;
						 
						 
			/* Golf */
			case 460: fillPologon($image, $fill, 3, 14);
						 break;

			case 461: fillPologon($image, $fill, 4, 13);
						 break;
						 
	 		case 462: fillPologon($image, $fill, 4, 14);
						 break;
						 
			case 463: fillPologon($image, $fill, 4, 12);
						 break;
						 
			case 464: fillPologon($image, $fill, 4, 11);
						 break;
						 
			case 465: fillPologon($image, $fill, 4, 10);
						 break;

			case 466: fillPologon($image, $fill, 4, 9);
						 break;
						 
			case 467: fillPologon($image, $fill, 4, 8);
						 break;
						 
			/* Hotel */
			case 470: fillPologon($image, $fill, 3, 8);
						 break;

			case 471: fillPologon($image, $fill, 4, 7);
						 break;
						 
	 		case 472: fillPologon($image, $fill, 4, 6);
						 break;
						 
			case 473: fillPologon($image, $fill, 4, 4);
						 break;
						 
			case 474: fillPologon($image, $fill, 4, 5);
						 break;
						 
			case 475: fillPologon($image, $fill, 3, 6);
						 break;

			case 476: fillPologon($image, $fill, 4, 3);
						 fillPologon($image, $fill, 4, 1);
						 break;
						 
			case 477: fillPologon($image, $fill, 4, 2);
						 fillPologon($image, $fill, 4, 0);
						 break;

			/* Lima */
			case 480: fillPologon($image, $fill, 2, 0);
						 break;

			case 481: fillPologon($image, $fill, 2, 2);
						break;
						 
	 		case 482: fillPologon($image, $fill, 2, 4);
						 break;
						 
			case 483: fillPologon($image, $fill, 3, 1);
						 break;
						 
			case 484: fillPologon($image, $fill, 3, 3);
						 break;
						 
			case 485: fillPologon($image, $fill, 3, 5);
						 break;

			case 486: fillPologon($image, $fill, 3, 0);
						 break;
						 
			case 487: fillPologon($image, $fill, 3, 2);
						 fillPologon($image, $fill, 3, 4);
						 break;
			}		 
		}
	}
}

/* 
** --------------------------
** Output image as PNG
** --------------------------
*/

$planet = 0;
if (isset($_GET['planet'])) {
	$planet = $_GET['planet'];
}

$data = "";
if (isset($_GET['data'])) {
	$data = $_GET['data'];
}

switch($planet) {

	case PLANET_EARTH:
			$image = ImageCreateFromGIF('images/planet/planet_big'.$planet.'.gif');
			process_earth_data($data, $image);
			break;

	case PLANET_MOON:
			$image = ImageCreateFromPNG('images/planet/planet_big'.$planet.'.png');
			AddPologonRaster($image);
			process_moon_data($data, $image);
			break;
	
	case PLANET_MARS:
			$image = ImageCreateFromPNG('images/planet/planet_big'.$planet.'.png');
			AddPologonRaster($image);
			process_mars_data($data, $image);
			break;
			
	case PLANET_ASTEROID:
			$image = ImageCreateFromPNG('images/planet/planet_big'.$planet.'.png');
			AddPologonRaster($image);
			process_astroid_data($data, $image);
			break;
			
	case PLANET_SUN:
			$image = ImageCreateFromPNG('images/planet/planet_big'.$planet.'.png');
			AddPologonRaster($image);
			process_sun_data($data, $image);
			break;
}

header('Content-type: image/gif');
imagegif($image);
imagedestroy($image);

/* 
** --------------------------
** The End
** --------------------------
*/

?>