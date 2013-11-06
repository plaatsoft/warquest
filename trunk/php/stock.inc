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
** ----------
** PARAMETERS
** ----------
*/

if (isset($_POST['symbol']) && $_POST['symbol'] != "") {
	$symbol = $_POST['symbol'];
	$symbol = stripslashes($symbol);
	$symbol = warquest_db_escape($symbol);
	$symbol = strtoupper($symbol);
}
	
/*
** ----------
** UTILS
** ----------
*/

function warquest_stockarray($data,$delim=',',$enclosure='"') {

	$enclosed=false;
	$fldcount=0;
	$linecount=0;
	$fldval='';
	for($i=0;$i<strlen($data);$i++) {
		$chr=$data{$i};
		switch($chr)
		{
			case $enclosure:
				if($enclosed&&$data{$i+1}==$enclosure) {
					$fldval.=$chr;
					++$i; 
				} else {
					$enclosed=!$enclosed;
				}
				break;
   
			case $delim:
				if(!$enclosed) {
					$ret_array[$linecount][$fldcount++]=$fldval;
					$fldval='';
				} else {
					$fldval.=$chr;
				}
				break;
			
			case "\r":
				if (!$enclosed&&$data{$i+1}=="\n") continue;
				
			case "\n":
				if(!$enclosed) {
					$ret_array[$linecount++][$fldcount]=$fldval;
					$fldcount=0;
					$fldval='';
				} else {
					$fldval.=$chr;
				}
				break;
				
			default:
				$fldval.=$chr;
		}
	}
	if($fldval) {
		$ret_array[$linecount][$fldcount]=$fldval;
	}
	return $ret_array;
}

function warquest_stocklist($stocksymbols) {		
	
	ini_set('default_socket_timeout', 5);
	
	$stock="";	
	$url = sprintf("http://download.finance.yahoo.com/d/quotes.csv?s=%s&f=snl1d1t1c1ohgvp", $stocksymbols);	
	
	if ( function_exists('curl_init') ) {
		
		$ch = curl_init();
		curl_setopt($ch, CURLOPT_URL, $url);
		curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
		curl_setopt($ch, CURLOPT_USERAGENT, 'WarQuest');
		$response = curl_exec($ch);
		curl_close($ch);
			
	} else if ( ini_get('allow_url_fopen') ) {
				
		$response = @file_get_contents($url, 'r');
	}
				
	if (strlen($response)>50) {
		$stocklist=warquest_stockarray($response);
	
		for($i=0;$i<count($stocklist);$i++) {
		
			$stocksymbol=trim($stocklist[$i][0], '\"');
			$stock[$stocksymbol]["stocksymbol"] = trim($stocklist[$i][0], '\"');
			$stock[$stocksymbol]["company"] = trim($stocklist[$i][1], '\"');
			$stock[$stocksymbol]["last"] = $stocklist[$i][2];
			$stock[$stocksymbol]["date"] = trim($stocklist[$i][3], '\"');	
			$stock[$stocksymbol]["time"] = trim($stocklist[$i][4], '\"');					
			$stock[$stocksymbol]["change"] = $stocklist[$i][5];
			$stock[$stocksymbol]["open"] = $stocklist[$i][6];
			$stock[$stocksymbol]["high"] = $stocklist[$i][7];
			$stock[$stocksymbol]["low"] = $stocklist[$i][8];
			$stock[$stocksymbol]["volume"] = $stocklist[$i][9];
			$stock[$stocksymbol]["prevclose"] = $stocklist[$i][10];	
		}
	}
	
	ini_set('default_socket_timeout', 30);
	
	return $stock;
}


/** 
 * Show html combobox with stockamount options
 */
function warquest_stock_amount_selected($max=0) {
	
	global $amount;
			
	$page = '<script>';
	$page .= '$(function() {';
	$page .= 'var availableTags = [';
	$page .= '"100","200","300", "400", "500", "600", "700", "800", "900", ';
	$page .= '"1.000","2.000","3.000", "4.000", "5.000", "6.000", "7.000", "8.000", "9.000", ';
	$page .= '"10.000","20.000","30.000", "40.000", "50.000", "60.000", "70.000", "80.000", "90.000", ';
	$page .= '"100.000","200.000","300.000", "400.000", "500.000", "600.000", "700.000", "800.000", "900.000", ';
	$page .= '"1.000.000","2.000.000","3.000.000", "4.000.000", "5.000.000", "6.000.000", "7.000.000", "8.000.000", "9.000.000", ';
	$page .= '"10.000.000","20.000.000","30.000.000", "40.000.000", "50.000.000", "60.000.000", "70.000.000", "80.000.000", "90.000.000", ';
	$page .= '"'.number_format2($max).'" ];';
	$page .= '$( "#amount" ).autocomplete({ source: availableTags }); });'; 
	$page .= '</script>';
	$page .= '<input id="amount" name="amount" size="10" maxlength="10" value="'.$amount.'" >';
	
	return $page;
}

/*
** --------
** ACTIONS
** --------
*/

function warquest_stock_add_do() {

	/* input */
	global $symbol;
	global $player;
	
	/* output */
	global $popup;
	
	$stock = warquest_stocklist($symbol);
		
	if (warquest_db_check($symbol, $player->pid)>0) {
	
		$message = t('STOCK_SYMBOL_AVAILABLE', $symbol);
		$popup .= warquest_box_icon("warning", $message);
	
	} else if ((isset($stock[$symbol]["company"])) && ($symbol!=$stock[$symbol]["company"])) {
			
		warquest_db_stock_insert($symbol, $player->pid);
		
		$message = t('STOCK_SYMBOL_ADDED', $stock[$symbol]["company"]);
		$popup .= warquest_box_icon("info", $message);
		
	} else {
		
		$message = t('STOCK_SYMBOL_NOT_FOUND', $symbol);
		$popup .= warquest_box_icon("warning", $message);
	}
}

function warquest_stock_remove_do() {

	/* input */
	global $symbol;
	global $player;
	global $uid;
				
	/* output */
	global $popup;
	
	if ($uid>0) {
	
		warquest_db_stock_delete($uid);
			
		$message = t('STOCK_SYMBOL_REMOVED');
		$popup .= warquest_box_icon("info", $message);
	}
}

function warquest_stock_buy_do() {
   
	/* input */
	global $mid;
	global $sid;
	global $cid;
	
	global $eid;
	global $gid;	
	global $player;
	global $uid;
	global $amount;
	
	/* output */
	global $popup;
	global $page; 
	global $player;
	
	/* Remove dots */
	$amount2 = str_replace(".", "", $amount);
	
	if ($amount2==1) {
		$amount2=100;
		$amount=100;
	}
	
	if ($amount2<=0) {
		return;
	}
			
	/* Get stock information */
	$query  = 'select sid, symbol from stock where sid='.$uid;
	$result = warquest_db_query($query);	
 
 	$stock=warquest_db_fetch_object($result); 		
	$stocklist=warquest_stocklist($stock->symbol);
	
	/* Get amount of stocks */
	$query  = "select amount, cost from player_stock where sid=".$uid." and pid=".$player->pid;
	$result = warquest_db_query($query);	
	
	$amountOld=0;
	$costOld=0;
	if ($data=warquest_db_fetch_object($result)) {
		$amountOld=$data->amount;	
		$costOld=$data->cost;	
	} 
	
	/* Calculate total price of buying stock transaction */
	$price = $stocklist[$stock->symbol]["last"];
	$total = $price * $amount2;
	
	if ($price < 4) {
		
		$message = t('STOCK_PRICE_TO_LOW');
		$popup .= warquest_box("warning", $message);	
		
	} else if ($total == 0) {
	
		$message = '<table>';
		$message .= '<tr>';
		$message .= '<td width="100">';
		$message .= warquest_stock_image($stock);
		$message .= '</td>';
		$message .= '<td>';
		$message .= t('STOCK_BROKER_ERROR');
		$message .= '</td>';
		$message .= '</tr>';
		$message .= '</table>';

		$link  = warquest_link('mid='.$mid.'&sid='.$sid.'&cid='.$cid.'&uid='.$uid.'&eid='.$eid.'&gid='.$gid, t('LINK_BUY_AGAIN'), 'buy-0');
		$link .= '<br/><br/>Amount<br/>';
		$link .= warquest_stock_amount_selected();
		
		$popup .= warquest_box("warning", $message, $link);	
	
	} else if ($player->money < $total) {
	
		$message = '<table>';
		$message .= '<tr>';
		$message .= '<td width="100">';
		$message .= warquest_stock_image($stock);
		$message .= '</td>';
		$message .= '<td>';
		$message .= t('STOCK_NO_MONEY', 
			number_format2($amount2), 
			$stocklist[$stock->symbol]["company"], 
			money_format1($total));
		$message .= '</td>';
		$message .= '</tr>';
		$message .= '</table>';

		$link  = warquest_link('mid='.$mid.'&sid='.$sid.'&cid='.$cid.'&uid='.$uid.'&eid='.$eid.'&gid='.$gid, t('LINK_BUY_AGAIN'), 'buy-0');
		$link .= '<br/><br/>Amount<br/>';
		$link .= warquest_stock_amount_selected();
		
		$link  = warquest_link('mid='.$mid.'&sid='.$sid.'&cid='.$cid.'&uid='.$uid.'&eid='.$eid.'&gid='.$gid, t('LINK_BUY_AGAIN'), 'buy-0');
	
		$popup .= warquest_box("warning", $message, $link);		
	
	} else {		
	
		$player->money -= $total; 
		
		$log = 'Buy '.number_format2($amount2).' '.$stocklist[$stock->symbol]["company"].' stocks for '.number_format2($total);		
		warquest_user_log($player, $log);
		
		$cost = $costOld + $total;
		 
		if ($amountOld==0)	{	
			$query  = 'insert into player_stock (sid, pid, amount, cost) ';
			$query .= "values (".$uid.",".$player->pid.",".$amount2.",".$cost.")";	
		} else {
			$query  = 'update player_stock set amount=';
			$query .= ($amountOld+$amount2).', cost='.$cost.' where pid='.$player->pid.' and sid='.$uid; 		
		} 
		warquest_db_query($query);
				
		$message = '<table>';
		$message .= '<tr>';
		$message .= '<td width="100">';
		$message .= warquest_stock_image($stock);
		$message .= '</td>';
		$message .= '<td>';
		$message .= t('STOCK_BUY', 
			number_format2($amount2), 
			$stocklist[$stock->symbol]["company"], 
			money_format1($total), 
			number_format2(($amountOld + $amount2)));
		$message .= '</td>';
		$message .= '</tr>';
		$message .= '</table>';
		
		$link  = warquest_link('mid='.$mid.'&sid='.$sid.'&cid='.$cid.'&uid='.$uid.'&eid='.$eid.'&gid='.$gid, t('LINK_BUY_AGAIN'), 'buy-0');
		$link .= '<br/><br/>'.t('GENERAL_AMOUNT').'<br/>';
		$link .= warquest_stock_amount_selected();
			
		$popup .= warquest_box("info", $message, $link);
	}
}
	
function warquest_stock_sell_do() {
   
	/* input */
	global $mid;
	global $sid;
	global $cid;
	global $eid;
	
	global $gid;
	global $uid;
	global $amount;
	global $config;
	
	/* output */
	global $page; 
	global $player;
	global $popup;
	
	/* Remove dots */
	$amount2 = str_replace(".", "", $amount);
	
	if ($amount2==1) {
		$amount2=100;
		$amount=100;
	}
	
	if ($amount2<=0) {
		return;
	}
			
	/* Get stock information */
	$query  = 'select sid, symbol from stock where sid='.$uid;
	$result = warquest_db_query($query);	
	
 	$stock=warquest_db_fetch_object($result); 		
	$stocklist=warquest_stocklist($stock->symbol);
			
	/* Get amount of stocks */
	$query  = "select amount, cost from player_stock where sid=".$uid." and pid=".$player->pid;
	$result = warquest_db_query($query);	
	
	$amountOld=0;
	$costOld=0;
	if ($data=warquest_db_fetch_object($result)) {
		$amountOld=$data->amount;	
		$costOld=$data->cost;	
	} 

	/* Calculate total price of stock transaction */
	$price = $stocklist[$stock->symbol]["last"];
	$total = $price * $amount2;
		
	/* If stocks exist */
	if (($amountOld-$amount2) < 0) {
	
		$message = '<table>';
		$message .= '<tr>';
		$message .= '<td width="100">';
		$message .= warquest_stock_image($stock);
		$message .= '</td>';
		$message .= '<td>';
		$message .= t('STOCK_NOT_OWNED', number_format2($amount2) , $stocklist[$stock->symbol]["company"]);
		$message .= '</td>';
		$message .= '</tr>';
		$message .= '</table>';

		$link = warquest_link('mid='.$mid.'&sid='.$sid.'&cid='.$cid.'&uid='.$uid.'&eid='.$eid.'&gid='.$gid, t('LINK_SELL_AGAIN'), 'sell-0');
		$link .= '<br/><br/>'.t('GENERAL_AMOUNT').'<br/>';
		$link .= warquest_stock_amount_selected($amountOld);
		
		if (($cid==4) && ($amountOld==0)) {
			$link = warquest_link('mid='.$mid.'&sid='.$sid.'&cid='.$cid.'&uid='.$uid.'&eid=6', t('STOCK_REMOVE'), 'remove');
		}
				
		$popup .= warquest_box("warning", $message, $link);
				
	} else if ($total == 0) {
	
		$message = '<table>';
		$message .= '<tr>';
		$message .= '<td width="100">';
		$message .= warquest_stock_image($stock);
		$message .= '</td>';
		$message .= '<td>';
		$message .= t('STOCK_BROKER_ERROR');
		$message .= '</td>';
		$message .= '</tr>';
		$message .= '</table>';

		$link  = warquest_link('mid='.$mid.'&sid='.$sid.'&cid='.$cid.'&uid='.$uid.'&eid='.$eid.'&gid='.$gid, t('LINK_BUY_AGAIN'), 'buy-0');
		$link .= '<br/><br/>Amount<br/>';
		$link .= warquest_stock_amount_selected($amountOld);
		
		$popup .= warquest_box("warning", $message, $link);	
			
	} else {
		
		$fee = round(($config["init_stock_fee"]/100)*$total);			
		$player->money += $total - $fee;
		
		$log = 'Sell '.number_format2($amount2).' '.$stocklist[$stock->symbol]["company"].' stocks for '.number_format2($total-$fee);		
		warquest_user_log($player, $log);
		
		$cost = $data->cost - (($data->cost / $amountOld) * $amount2);
			
		if (($amountOld-$amount2)>0) {
			$query  = "update player_stock set amount=".($amountOld-$amount2).", cost=".$cost." where pid=".$player->pid." and sid=".$uid; 
		} else {
			$query = "delete from player_stock where pid=".$player->pid." and sid=".$uid; 
		}
		warquest_db_query($query);
 
		$message = '<table>';
		$message .= '<tr>';
		$message .= '<td width="100">';
		$message .= warquest_stock_image($stock);
		$message .= '</td>';
		$message .= '<td>';
		$message .= t('STOCK_SELL', 
						number_format2($amount2), 
						$stocklist[$stock->symbol]["company"], 
						money_format1($total), 
						money_format1($fee),
						number_format2($amountOld-$amount2));
		$message .= '</td>';
		$message .= '</tr>';
		$message .= '</table>';
		
		$link = "";
		if (($amountOld-$amount2)>0) {
			$link = warquest_link('mid='.$mid.'&sid='.$sid.'&cid='.$cid.'&uid='.$uid.'&eid='.$eid.'&gid='.$gid, t('LINK_SELL_AGAIN'), 'sell-0');
			$link .= '<br/><br/>'.t('GENERAL_AMOUNT').'<br/>';
			$link .= warquest_stock_amount_selected($amountOld-$amount2);
		}

		if (($cid==4) && (($amountOld-$amount2)==0)) {
			$link = warquest_link('mid='.$mid.'&sid='.$sid.'&cid='.$cid.'&uid='.$uid.'&eid=6', t('STOCK_REMOVE'), 'remove');
		}
					
		$popup .= warquest_box("info", $message, $link);
	}
}

/*
** --------
** UI
** --------
*/

function warquest_stock_add_form() {

	/* input */
	global $mid;
	global $sid;
	global $cid;

	global $uid;
	global $player;
	global $config;
	
	/* output */
	global $page; 
		
	$page .= '<div class="box">';
	$page .= t('STOCK_SYMBOL').':';	
	$page .= ' ';	
	$page .= '<input name="symbol" type="text" id="symbol" size="15" maxlength="10" />';	
	$page .= ' ';
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&cid='.$cid.'&eid=5', t('STOCK_ADD'), 'add');
	$page .= '</div>';
	
	$page .= '<div class="note">';
	$page .= t('STOCK_SYMBOL_INFO');
	$page .= '</div>';
}


function warquest_stock_form() {
	
	/* input */
	global $mid;
	global $sid;
	global $cid;

	global $uid;
	global $player;
	global $config;
	
	/* output */
	global $page; 
	global $title;

	$title = t('STOCK_GROUP_'.$cid);

	$page .= '<div class="subparagraph">';	
	$page .= t('STOCK_GROUP_'.$cid).' '.t('GENERAL_STOCKS');
	$page .= '</div>';
	
	/* Get player data */	
	$query  = 'select symbol from stock where gsid='.$cid;
	if ($cid==4) {
		$query .= ' and pid='.$player->pid;
	}
	$query .= ' order by sid asc'; 
	
	$result = warquest_db_query($query);	
	$count = warquest_db_num_rows($result);
	$ads_pos = rand(1,$count);
	
	$symbols="";
	while ($data=warquest_db_fetch_object($result)) {
	
		if ($symbols!="") $symbols .= ",";
		$symbols .= $data->symbol;
	}

	if ($cid==4) {
		$page .= warquest_stock_add_form();
	}
	
	$stocklist="";
	if (strlen($symbols)==0) {
	
		$message = t('STOCK_NO_SYMBOLS');
		$page .= warquest_box_icon("info", $message);
		
		return;
	}

	/* Fetch stock ticker data */
	$stocklist=warquest_stocklist($symbols);	
	if ($stocklist!="") {
			
		/* Get player data */
		$query  = "select a.sid, a.symbol, IFNULL(b.amount, 0) as amount, IFNULL(b.cost, 0) as cost ";
		$query .= 'from stock a left join player_stock b ';
		$query .= 'on a.sid=b.sid and b.pid='.$player->pid.' where a.gsid='.$cid;		
		if ($cid==4) {
			$query .= ' and a.pid='.$player->pid;
		}
		$query .= ' order by a.symbol asc';  
			
		$result = warquest_db_query($query);	
	
		$page .= '<div class="box">';
		$page .= '<table>';
		$count = 0;
		while ($data=warquest_db_fetch_object($result)) {
			
			$price = $stocklist[$data->symbol]["last"];			
			$change = $stocklist[$data->symbol]["change"];
		
			$count++;
			$page .= '<tr>';
		
			$page .= '<td width="100">';		
			$page .= warquest_stock_image($data);			
			$page .= '</td>';
			
			$page .= '<td width="200"><b>';
			$page .= $stocklist[$data->symbol]["company"];
			$page .= '</b><br/><div class="stock">';
			
			$diff = $price - $change;
			if ($diff>0) {
				$tmp = ($change/$diff)*100;
			} else {
				$tmp = 0;
			}
			
			$page .= t('STOCK_PRICE', money_format3($price), procent_format($tmp));
			$page .= '<br/>';
			$tmp=0;
			if ($data->amount>0) {
				$tmp = (($data->amount * $price)-$data->cost) / $data->amount;				
				$tmp2 = (($tmp * $data->amount)/ $data->cost)*100;				
				$page .= t('STOCK_PROFIT', money_format3($tmp), procent_format($tmp2));
			}
			$page .= '</div></td>';
			
			$page .= '<td width="100" >';		
			$page .= money_format2($price*100);
			$page .= '<br/>'.warquest_link('mid='.$mid.'&sid='.$sid.'&cid='.$cid.'&uid='.$data->sid.'&eid=3', t('LINK_BUY'),"buy-".$count);
			$page .= '</td>';
			
			$page .= '<td width="150" >';		
			$page .= t('GENERAL_AMOUNT').': '.number_format2($data->amount).'<br/>';	
			$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&cid='.$cid.'&uid='.$data->sid.'&eid=4', t('LINK_SELL'), "sell-".($count+100));
						
			$page .= '</td>';
		
			$page .= '</tr>';
			
			if ($count==$ads_pos) {
		
				$begin = '<tr><td colspan="4"><br/>';
				$end = '<br/></td></tr>';	
				$page .= warquest_show_ads($begin, $end);		
			}
		}
	
		$page .= "</table>";	
		$page .= '</div>';
		
	} else {
	
		/* broker connection failed */		
		$message = t('STOCK_BROKER_ERROR');	 
	 	$page .= warquest_box_icon("warning", $message);	
	}

	$page .= '<div class="note">';
	$page .= t('STOCK_NOTE', $config["init_stock_fee"]);
	$page .= '</div>';
}

/*
** -------------
** HANDLER
** -------------
*/

function warquest_stock() {

	/* input */
	global $eid;
	global $cid;
			
	/* Event handler */
	switch ($eid ) {
	
		case 3:	warquest_stock_buy_do();
					break;		
				
		case 4:	warquest_stock_sell_do();
					break;		
					
		case 5:	warquest_stock_add_do();
					break;	
					
		case 6:	warquest_stock_remove_do();
					break;	
	}
	
	/* Page handler */		
	warquest_stock_form();
}

/*
** --------
** THE END
** --------
*/

?>

