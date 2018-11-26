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
**  All copyrights reserved (c) 1996-2016 PlaatSoft
*/

include "constants.inc";
include "general.inc";

function process_earth_data($data, $image) {

	$border = ImageColorAt($image, 320, 65); 

	if (strlen($data)>0) {
	
		$codes = preg_split('/,/',$data);
		
		foreach($codes as $code) {

			list($country, $progress) = preg_split('/-/',$code);

			/* Green (0% conquered) */
			$color = ImageColorAllocate($image, 0, 255, 0);

			if ($progress==0) {
				
				/* Red (Rebel state) */
				$color = ImageColorAllocate($image, 255, 0, 0);
			
			} else if (($progress>=100) && ($progress<200)) {		
			
				/* Yellow (33% conquered) */
				$color = ImageColorAllocate($image, 255, 255, 20);
		
			} else if (($progress>=200) && ($progress<300)) {
			
				/* Purple (66% conquered) */
				$color = ImageColorAllocate($image, 255, 51, 255);
		
			} else if ($progress==300) {
			
				/* Orange (100% conquered) */
				$color = ImageColorAllocate($image, 255, 165, 0);	
			} 
			
	
		switch ($country) {

	/* 
	** --------------------------
	** Europa (1)
	** --------------------------
	*/

	/* UK + Ireland (1) */
	case 1:
		ImageFillToBorder($image, 440, 100, $border, $color);
		ImageFillToBorder($image, 423, 108, $border, $color);
		ImageFillToBorder($image, 427, 101, $border, $color);
		break;

	/* Benelux (2) */
	case 2:
		ImageFillToBorder($image, 463, 110, $border, $color);
		ImageFillToBorder($image, 460, 117, $border, $color);
		ImageFillToBorder($image, 462, 121, $border, $color);
		break;

	/* France + Malta (3) */
	case 3:
		ImageFillToBorder($image, 455, 132, $border, $color);
		ImageFillToBorder($image, 471, 159, $border, $color);
		ImageFillToBorder($image, 472, 151, $border, $color);
		break;

	/* Central Europe (4) */
	case 4:
		ImageFillToBorder($image, 475, 115, $border, $color);
		ImageFillToBorder($image, 486, 129, $border, $color);
		ImageFillToBorder($image, 467, 133, $border, $color);
		break;

	/* Scandinavia (5) */
	case 5:
		ImageFillToBorder($image, 472, 96, $border, $color);
		ImageFillToBorder($image, 479, 98, $border, $color);
		ImageFillToBorder($image, 475, 99, $border, $color);
		ImageFillToBorder($image, 470, 81, $border, $color);
		ImageFillToBorder($image, 487, 77, $border, $color);
		ImageFillToBorder($image, 401, 63, $border, $color);
		ImageFillToBorder($image, 486, 19, $border, $color);
		ImageFillToBorder($image, 520, 65, $border, $color);
		break;

	/* East Europa (6) */
	case 6:
		ImageFillToBorder($image, 517, 86, $border, $color);
		ImageFillToBorder($image, 517, 92, $border, $color);
		ImageFillToBorder($image, 514, 98, $border, $color);
		ImageFillToBorder($image, 507, 101, $border, $color);
		ImageFillToBorder($image, 500, 110, $border, $color);
		ImageFillToBorder($image, 523, 107, $border, $color);
		ImageFillToBorder($image, 522, 117, $border, $color);
		ImageFillToBorder($image, 489, 120, $border, $color);
		ImageFillToBorder($image, 500, 124, $border, $color);
		ImageFillToBorder($image, 490, 135, $border, $color);
		ImageFillToBorder($image, 501, 131, $border, $color);
		ImageFillToBorder($image, 493, 136, $border, $color);
		ImageFillToBorder($image, 497, 143, $border, $color);
		ImageFillToBorder($image, 506, 142, $border, $color);
		ImageFillToBorder($image, 502, 148, $border, $color);
		ImageFillToBorder($image, 507, 149, $border, $color);
		ImageFillToBorder($image, 504, 156, $border, $color);
		ImageFillToBorder($image, 510, 153, $border, $color);
		ImageFillToBorder($image, 518, 149, $border, $color);
		ImageFillToBorder($image, 528, 130, $border, $color);
		ImageFillToBorder($image, 518, 135, $border, $color);
		break;

	/* Spain + Portugal (7) */
	case 7:
		ImageFillToBorder($image, 434, 154, $border, $color);
		ImageFillToBorder($image, 419, 158, $border, $color);
		break;
	
	/* Italia + Greece + Turkye (8) */
	case 8:
		ImageFillToBorder($image, 481, 149, $border, $color);
		ImageFillToBorder($image, 488, 169, $border, $color);
		ImageFillToBorder($image, 512, 164, $border, $color);
		ImageFillToBorder($image, 520, 178, $border, $color);
		ImageFillToBorder($image, 527, 154, $border, $color);
		ImageFillToBorder($image, 549, 163, $border, $color);
		ImageFillToBorder($image, 547, 179, $border, $color);
		break;
		

	/* 
	** --------------------------
	** North America (2)
	** --------------------------
	*/

	/* Greenland (1)  */
	case 10:		
		ImageFillToBorder($image, 384,35, $border, $color);
		break;

	/* Canada (2) */
	case 11:
		ImageFillToBorder($image, 131,88, $border, $color);
		ImageFillToBorder($image, 180,44, $border, $color);
		ImageFillToBorder($image, 195,28, $border, $color);
		ImageFillToBorder($image, 223,37, $border, $color);
		ImageFillToBorder($image, 215,49, $border, $color);
		ImageFillToBorder($image, 232,28, $border, $color);
		ImageFillToBorder($image, 261,40, $border, $color);
		ImageFillToBorder($image, 236,35, $border, $color);
		ImageFillToBorder($image, 251,29, $border, $color);
		ImageFillToBorder($image, 234,19, $border, $color);
		ImageFillToBorder($image, 248,21, $border, $color);
		ImageFillToBorder($image, 270,19, $border, $color);
		ImageFillToBorder($image, 281,125, $border, $color);
		ImageFillToBorder($image, 254,139, $border, $color);
		break;

	/* United States (3) */
	case 12:
		ImageFillToBorder($image, 80, 60, $border, $color);
		ImageFillToBorder($image, 81, 123, $border, $color);
		ImageFillToBorder($image, 133, 166, $border, $color);
		break;

	/* Mexico (4) */
	case 13:
		ImageFillToBorder($image, 105, 231, $border, $color);
		break;

	/* Guatemala + Honduras (5) */
	case 14:
		ImageFillToBorder($image, 142, 260, $border, $color);
		ImageFillToBorder($image, 153, 260, $border, $color);
		break;

	/* Nicaragua + Costa Rica (6) */
	case 15:
		ImageFillToBorder($image, 157, 269, $border, $color);
		ImageFillToBorder($image, 161, 279, $border, $color);
		break;

	/* Cuba (7) */
	case 16:
		ImageFillToBorder($image, 176, 229, $border, $color);
		ImageFillToBorder($image, 188, 247, $border, $color);
		break;

	/* Caribbean Islands (8) */
	case 17:
		ImageFillToBorder($image, 204, 243, $border, $color);
		ImageFillToBorder($image, 208, 244, $border, $color);
		ImageFillToBorder($image, 221, 246, $border, $color);
		ImageFillToBorder($image, 148, 253, $border, $color);
		ImageFillToBorder($image, 147, 265, $border, $color);
		ImageFillToBorder($image, 171, 287, $border, $color);
		break;

	/* 
	** --------------------------
	** South America (3)
	** --------------------------
	*/

	/* Middle America (1) */
	case 20:
		ImageFillToBorder($image, 193, 303, $border, $color);
		ImageFillToBorder($image, 220, 292, $border, $color);
		ImageFillToBorder($image, 244, 298, $border, $color);
		ImageFillToBorder($image, 254, 305, $border, $color);
		ImageFillToBorder($image, 265, 308, $border, $color);
		break;

	/* Ecuador + Peru (2) */
	case 21:
		ImageFillToBorder($image, 180, 329, $border, $color);
		ImageFillToBorder($image, 195, 340, $border, $color);
		break;

	/* Bolivia (3) */
	case 22:
		ImageFillToBorder($image, 228, 388, $border, $color);
		break;

	/* Paraguay (4) */
	case 23:
		ImageFillToBorder($image, 244, 407, $border, $color);
		break;

	/* Chile (5) */
	case 24:
		ImageFillToBorder($image, 214, 413, $border, $color);
		break;

	/* Argentina (6) */
	case 25:
		ImageFillToBorder($image, 238, 446, $border, $color);
		break;

	/* Uruguay (7) */
	case 26:
		ImageFillToBorder($image, 266, 455, $border, $color);
		break;

	/* Brasil (8) */
	case 27:
		ImageFillToBorder($image, 288, 385, $border, $color);
		break;

	/* 
	** --------------------------
	** Africa (4)
	** --------------------------
	*/

	/* Morocco + Algeria (1) */
	case 30:
		ImageFillToBorder($image, 449, 205, $border, $color);
		ImageFillToBorder($image, 421, 191, $border, $color);
		break;

	/* Libya + Tunisia + Egypt (2) */
	case 31:
		ImageFillToBorder($image, 485, 205, $border, $color);
		ImageFillToBorder($image, 470, 183, $border, $color);
		ImageFillToBorder($image, 536, 212, $border, $color);
		break;

	/* West Africa (3) */
	case 32:
		ImageFillToBorder($image, 396, 221, $border, $color);
		ImageFillToBorder($image, 404, 242, $border, $color);
		ImageFillToBorder($image, 393, 261, $border, $color);
		ImageFillToBorder($image, 414, 264, $border, $color);
		ImageFillToBorder($image, 471, 252, $border, $color);
		ImageFillToBorder($image, 391, 272, $border, $color);
		ImageFillToBorder($image, 400, 275, $border, $color);
		ImageFillToBorder($image, 400, 287, $border, $color);
		ImageFillToBorder($image, 409, 294, $border, $color);
		ImageFillToBorder($image, 421, 290, $border, $color);
		ImageFillToBorder($image, 434, 270, $border, $color);
		ImageFillToBorder($image, 437, 285, $border, $color);
		ImageFillToBorder($image, 444, 285, $border, $color);
		ImageFillToBorder($image, 448, 285, $border, $color);
		ImageFillToBorder($image, 465, 285, $border, $color);
		break;

	/* Central Africa (4) */
	case 33:
		ImageFillToBorder($image, 480, 300, $border, $color);
		ImageFillToBorder($image, 500, 265, $border, $color);
		ImageFillToBorder($image, 503, 296, $border, $color);
		ImageFillToBorder($image, 535, 275, $border, $color);
		ImageFillToBorder($image, 566, 257, $border, $color);
		ImageFillToBorder($image, 476, 315, $border, $color);
		ImageFillToBorder($image, 481, 314, $border, $color);
		ImageFillToBorder($image, 497, 314, $border, $color);
		ImageFillToBorder($image, 515, 306, $border, $color);
		break;

	/* East Africa (5) */
	case 34:
		ImageFillToBorder($image, 568, 281, $border, $color);
		ImageFillToBorder($image, 600, 281, $border, $color);
		ImageFillToBorder($image, 548, 312, $border, $color);
		ImageFillToBorder($image, 540, 328, $border, $color);
		ImageFillToBorder($image, 540, 335, $border, $color);
		ImageFillToBorder($image, 566, 317, $border, $color);
		ImageFillToBorder($image, 555, 344, $border, $color);
		break;

	/* Angola + Zambia + Mozambique (6) */
	case 35:
		ImageFillToBorder($image, 494, 370, $border, $color);
		ImageFillToBorder($image, 530, 378, $border, $color);
		ImageFillToBorder($image, 556, 382, $border, $color);
		ImageFillToBorder($image, 554, 393, $border, $color);
		break;

	/* Namibia + Botswana + Zimbabwe (7) */
	case 36:
		ImageFillToBorder($image, 495, 407, $border, $color);
		ImageFillToBorder($image, 517, 407, $border, $color);
		ImageFillToBorder($image, 536, 402, $border, $color);
		break;

	/* South Africa + Madagascar (8) */
	case 37:
		ImageFillToBorder($image, 517, 440, $border, $color);
		ImageFillToBorder($image, 532, 441, $border, $color);
		ImageFillToBorder($image, 543, 428, $border, $color);
		ImageFillToBorder($image, 590, 412, $border, $color);
		break;

	/* 
	** --------------------------
	** North Asia (5)
	** --------------------------
	*/

	/* Russia (1) */
	case 40:
		ImageFillToBorder($image, 665, 80, $border, $color);
		ImageFillToBorder($image, 583, 32, $border, $color);
		ImageFillToBorder($image, 650, 15, $border, $color);
		ImageFillToBorder($image, 670, 19, $border, $color);
		ImageFillToBorder($image, 764, 29, $border, $color);
		ImageFillToBorder($image, 786, 29, $border, $color);
		ImageFillToBorder($image, 858, 119, $border, $color);
		ImageFillToBorder($image, 866, 132, $border, $color);
		break;

	/* Mongolia (2) */
	case 41:
		ImageFillToBorder($image, 747, 133, $border, $color);
		break;

	/* Kazakhstan (3) */
	case 42:
		ImageFillToBorder($image, 643, 125, $border, $color);
		break;

	/* Uzbekihstan (4) */
	case 43:
		ImageFillToBorder($image, 636, 153, $border, $color);
		ImageFillToBorder($image, 670, 153, $border, $color);
		break;

	/* Takikistan (5) */
	case 44:
		ImageFillToBorder($image, 656, 164, $border, $color);
		break;

	/* Turkmenistan (6) */
	case 45:
		ImageFillToBorder($image, 623, 162, $border, $color);
		break;

	/* Georgia (7) */
	case 46:
		ImageFillToBorder($image, 576, 150, $border, $color);
		break;

	/* Armenia + Azerbaijan (8) */
	case 47:
		ImageFillToBorder($image, 580, 157, $border, $color);
		ImageFillToBorder($image, 589, 157, $border, $color);
		break;

	/* 
	** --------------------------
	** South Asia (6)
	** --------------------------
	*/

	/* Iran (1) */
	case 50:
		ImageFillToBorder($image, 612, 189, $border, $color);
		break;

	/* Afghanistan (2) */
	case 51:
		ImageFillToBorder($image, 650, 184, $border, $color);
		break;

	/* Pakistan (3) */
	case 52:
		ImageFillToBorder($image, 663, 201, $border, $color);
		break;

	/* India + Srilanka (4) */
	case 53:
		ImageFillToBorder($image, 696, 232, $border, $color);
		ImageFillToBorder($image, 708, 291, $border, $color);
		break;

	/* Nepal (5) */
	case 54:
		ImageFillToBorder($image, 708, 206, $border, $color);
		break;

	/* Bangladesh + Bhutan (6) */
	case 55:
		ImageFillToBorder($image, 731, 224, $border, $color);
		ImageFillToBorder($image, 731, 216, $border, $color);
		ImageFillToBorder($image, 733, 211, $border, $color);
		break;

	/* Myanmar + Thailand  (7) */
	case 56:
		ImageFillToBorder($image, 753, 235, $border, $color);
		ImageFillToBorder($image, 773, 257, $border, $color);
		break;

	/* Loa (8) */
	case 57:		
		ImageFillToBorder($image, 775, 246, $border, $color);

		break;

	/* 
	** --------------------------
	** East Asia (7)
	** --------------------------
	*/

	/* China (1) */
	case 60:
		ImageFillToBorder($image, 766, 184, $border, $color);
		break;

	/* North Korea (2) */
	case 61:
		ImageFillToBorder($image, 832, 162, $border, $color);
		break;

	/* South Korea (3) */
	case 62:
		ImageFillToBorder($image, 842, 175, $border, $color);
		break;

	/* Japan (4) */
	case 63:
		ImageFillToBorder($image, 877, 173, $border, $color);
		ImageFillToBorder($image, 876, 146, $border, $color);
		ImageFillToBorder($image, 858, 189, $border, $color);
		ImageFillToBorder($image, 864, 185, $border, $color);
		break;

	/* Taiwan (5) */
	case 64:
		ImageFillToBorder($image, 834, 226, $border, $color);
		break;

	/* Cambodia (6) */
	case 65:
		ImageFillToBorder($image, 787, 271, $border, $color);
		break;

	/* VietNam (7) */
	case 66:
		ImageFillToBorder($image, 798, 267, $border, $color);
		break;

	/* Malaysia (8) */
	case 67:
		ImageFillToBorder($image, 780, 302, $border, $color);
		ImageFillToBorder($image, 817, 309, $border, $color);
		break;

	/* 
	** --------------------------
	** Oceania (8)
	** --------------------------
	*/

	/* (1) West Indonesia  */
	case 70:
		ImageFillToBorder($image, 781, 327, $border, $color);
		ImageFillToBorder($image, 808, 350, $border, $color);
		ImageFillToBorder($image, 823, 354, $border, $color);
		ImageFillToBorder($image, 830, 356, $border, $color);		
		break;
	
	/* (2) East Indonesia  */
	case 71:
		ImageFillToBorder($image, 818, 323, $border, $color);
		ImageFillToBorder($image, 838, 360, $border, $color);
		ImageFillToBorder($image, 842, 355, $border, $color);
		ImageFillToBorder($image, 853, 359, $border, $color);
		ImageFillToBorder($image, 839, 331, $border, $color);
		ImageFillToBorder($image, 844, 317, $border, $color);
		ImageFillToBorder($image, 867, 317, $border, $color);		
		ImageFillToBorder($image, 861, 334, $border, $color);
		ImageFillToBorder($image, 871, 333, $border, $color);
		ImageFillToBorder($image, 901, 337, $border, $color);
				
		break;

	/* (3) Philipines */
	case 72:
		ImageFillToBorder($image, 839, 255, $border, $color);
		ImageFillToBorder($image, 841, 268, $border, $color);
		ImageFillToBorder($image, 845, 265, $border, $color);
		ImageFillToBorder($image, 849, 266, $border, $color);
		ImageFillToBorder($image, 846, 274, $border, $color);
		ImageFillToBorder($image, 854, 273, $border, $color);
		ImageFillToBorder($image, 849, 280, $border, $color);
		ImageFillToBorder($image, 852, 278, $border, $color);
		ImageFillToBorder($image, 855, 288, $border, $color);		
		break;
		
	/* (4) Papua New Guinea */
	case 73:
		ImageFillToBorder($image, 919, 343, $border, $color);
		ImageFillToBorder($image, 941, 344, $border, $color);
		ImageFillToBorder($image, 949, 336, $border, $color);
		break;
	
	/* (5) Timor */
	case 74:
		ImageFillToBorder($image, 856, 357, $border, $color);
		break;	
		
	/* (7) North Australia */
	case 75:
		ImageFillToBorder($image, 900, 453, $border, $color);
		break;
		
	/* (6) South Australia */
	case 76:
		ImageFillToBorder($image, 891, 490, $border, $color);
		break;
		
	/* (8) New Zealand */
	case 77:
		ImageFillToBorder($image, 984, 477, $border, $color);
		ImageFillToBorder($image, 955, 498, $border, $color);
		break;
				
	/* 
	** --------------------------
	** Middleast (9)
	** --------------------------
	*/
	
	/* (1) Syrian + Lebonon */
	case 80:
		ImageFillToBorder($image, 563, 181, $border, $color);
		ImageFillToBorder($image, 556, 184, $border, $color);
		break;
	
	/* (2) Iraq */
	case 81:
		ImageFillToBorder($image, 576, 185, $border, $color);
		break;

	/* (3) Saudi Arabia */
	case 82:
		ImageFillToBorder($image, 578, 220, $border, $color);
		break;
		
	/* (4) Kuwait */
	case 83:
		ImageFillToBorder($image, 593, 202, $border, $color);		
		break;
	
	/* (5) Yemen */
	case 84:
		ImageFillToBorder($image, 602, 256, $border, $color);
		break;	
		
	/* (6) Oman + Arab Emirates */
	case 85:
		ImageFillToBorder($image, 624, 245, $border, $color);
		ImageFillToBorder($image, 619, 226, $border, $color);
		break;
		
	/* (7) Jordan */
	case 86:
		ImageFillToBorder($image, 558, 196, $border, $color);
		break;
		
	/* (8) Israel */
	case 87:
		ImageFillToBorder($image, 552, 197, $border, $color);
		ImageFillToBorder($image, 554, 194, $border, $color);
		break;
			}
		}
	}
}

function process_default_data($data, $image) {
	
	if (strlen($data)>0) {

		$codes = preg_split('/,/',$data);
		foreach($codes as $code) {

			list($x, $y, $progress) = preg_split('/-/',$code);
			
			/* Transparent (0% conquered) */
			$color = ImageColorAllocatealpha($image, 255, 255, 255, 127);		
			
			if ($progress==0) {
			
				/* Red (Rebel state) */
				$color = ImageColorAllocatealpha($image, 255, 0, 0, 80);		
				
			} else if (($progress>=100) && ($progress<200)) {
			
				/* Yellow (33% conquered) */
				$color = ImageColorAllocatealpha($image, 255, 255, 20, 80);		
				
			} else if (($progress>=200) && ($progress<300)) {
			
				/* Purple (66% conquered) */
				$color = ImageColorAllocatealpha($image, 255, 51, 255, 80);		
				
			} else if ($progress>=300) {
			
				/* Orange (100% conquered) */
				$color = ImageColorAllocatealpha($image, 255, 165, 0, 80);	
			} 
			
			fillPologon($image, $color, $x, $y);	 
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

switch($planet) {

	case PLANET_EARTH:
			$image = ImageCreateFromGIF('images/planet/global'.$planet.'.gif');
			process_earth_data($data, $image);
			break;

	default: 
			$image = ImageCreateFromPNG('images/planet/global'.$planet.'.png');
			AddPologonRaster($image);
			process_default_data($data, $image);
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