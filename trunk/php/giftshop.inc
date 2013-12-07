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
** ---------------
** Post Parameters
** ---------------
*/

/*
** ----------
** ACTIONS
** ----------
*/


/*<form action="https://www.paypal.com/cgi-bin/webscr" method="post" target="_top">
<input type="hidden" name="cmd" value="_s-xclick">
<input type="hidden" name="hosted_button_id" value="F625JH8Z9EXXQ">
<input type="image" src="https://www.paypalobjects.com/nl_NL/NL/i/btn/btn_buynowCC_LG.gif" border="0" name="submit" alt="PayPal, de veilige en complete manier van online betalen.">
<img alt="" border="0" src="https://www.paypalobjects.com/nl_NL/i/scr/pixel.gif" width="1" height="1">
</form>*/




/*
** ----------
** UI
** ----------
*/

function warquest_paypal($gold, $price, $key) {

	global $config;
	global $player;

	$tag = 'WarQuest - '.$player->name.' ['.$player->pid.']';
	
	$page =	'<form action="https://www.paypal.com/cgi-bin/webscr" method="post">';	  
	$page .=	'<input type="hidden" name="cmd" value="_s-xclick">';
	$page .=	'<input type="hidden" name="item_name" value="'.$tag.'">';
	$page .=	'<input type="hidden" name="hosted_button_id" value="'.$config['paypal_buy_key'.$key].'">';
	$page .=	'<input type="image" src="https://www.paypalobjects.com/en_US/i/btn/btn_buynow_LG.gif" border="0" name="submit" alt="">';
	$page .=	'<img alt="" border="0" src="https://www.paypalobjects.com/en_US/i/scr/pixel.gif" width="1" height="1">';
	$page .=	'</form>';
	
	return $page;
}

	
/** 
 * Gift shop form
 */
function warquest_giftshop_form() {

	/* input */
	global $mid;
	global $sid;
	global $id;
	global $player;
	global $config;
	
	/* output */
	global $page;
	
	$page .=	'</form>';	
		
	$page .= '<div class="subparagraph">';	
	$page .= t('GIFT_SHOP_TITLE');
	$page .= '</div>';
												
	$gold = array(1000,2500,5500,12000,25000);
	$price = array(1.95, 4.95, 9.95, 19.95, 39.95);

	$page .= '<div class="box">';	

	$page .= '<table class="shop">';

	for($i=1; $i<6; $i++) {
	
		if ($i>1) {
			$page .= '<tr>';
			$page .= '<td colspan="2"><hr></td>';
			$page .= '</tr>';			
		}
			
		$page .= '<tr>';
		$page .= '<td>';
		$page .= warquest_image('gold/gold'.$i.'.jpg', 'width="225" height="160"');
		$page .= '</td>';
		$page .= '<td width="300" align="center">';
		$page .= gold_format($gold[$i-1]);
		$page .= '<br/>';
		$page .= stock_format($price[$i-1]).' '.t("GENERAL_USD");
		$page .= '<br/>'; 
		$page .= '<br/>';
		$page .= warquest_paypal($gold[$i-1], $price[$i-1], $i);	
		$page .= '</td>';		
		$page .= '</tr>';
	}
	
	$page .= '</table>';
	$page .= '</div>';
	
	$page .= t('GIFT_SHOP_NOTE');
}

/*
** ---------
** HANDLER
** ---------
*/


/*
** ---------
** THE END
** ---------
*/

?>