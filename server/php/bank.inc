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

/*
** ---------------
** Post Parameters
** ---------------
*/

$deposit = warquest_post('deposit', '0');
$withdraw = warquest_post('withdraw', '0');

/*
** ----------
** ACTIONS
** ----------
*/

/**
 * Deposit money on bank.
 */
function warquest_bank_deposit_do() {

	/* input */
	global $player;
	global $id;
	global $config;
	global $deposit;

	/* output */
	global $output;

	/* Remove dots */
	$deposit = str_replace(".", "", $deposit);

	$price = $deposit;

	if ($price>0) {

		if ($player->money >= $price) {

			$player->money-=$price;
			$balance=0;

			switch ($id) {
				case 1: 	$player->bank1+=$deposit;
							$balance=$player->bank1;
							$init_bank_deposit = $config["init_bank1_deposit"];
							break;

				case 2: 	$player->bank2+=$deposit;
							$balance=$player->bank2;
							$init_bank_deposit = $config["init_bank2_deposit"];
							break;

				case 3: 	$player->bank3+=$deposit;
							$balance=$player->bank3;
							$init_bank_deposit = $config["init_bank3_deposit"];
							break;
			}

			/* Update transaction log.	*/
			warquest_db_bank_insert($player->pid, 0, $id, $deposit, $balance, 1);

			$handleFee = (round($deposit * ($init_bank_deposit/100)) * -1);
			$balance=0;
			switch ($id) {
				case 1: 	$player->bank1 += $handleFee;
							$balance=$player->bank1;
							break;

				case 2: 	$player->bank2 += $handleFee;
							$balance=$player->bank2;
							break;

				case 3: 	$player->bank3 += $handleFee;
							$balance=$player->bank3;
							break;
			}

			/* Update transaction log. */
			warquest_db_bank_insert($player->pid, 0, $id, $handleFee, $balance, 2);

			$message = t('BANK_DEPOSIT', money_format1($deposit), t('BANK_GROUP_'.$id));
			$output->popup .= warquest_box_icon("info", $message);

			$log = 'Deposit '.number_format2($deposit).' to '.t('BANK_GROUP_'.$id);
			warquest_user_log($player, $log);

		} else {

			$message = t('BANK_DEPOSIT_FAILED', money_format1($price));
			$output->popup .= warquest_box_icon("warning", $message);

		}
	}
}

/**
 * Withdraw money of bank.
 */
function warquest_bank_withdraw_do() {

	/* input */
	global $player;
	global $id;
	global $withdraw;
	global $id;

	/* output */
	global $output;

	/* Remove dots */
	$withdraw = str_replace(".", "", $withdraw);

	$balance=0;
	switch ($id) {
		case 1: $balance=$player->bank1;
				break;

		case 2: $balance=$player->bank2;
				break;

		case 3: $balance=$player->bank3;
				break;
	}

	if ($withdraw>0) {

		if ($balance >= $withdraw) {

			/* Calculate new values	*/
			$player->money += $withdraw;

			switch ($id) {
				case 1: 	$player->bank1 -= $withdraw;
							break;

				case 2: 	$player->bank2 -= $withdraw;
							break;

				case 3: 	$player->bank3 -= $withdraw;
							break;
			}

			warquest_db_bank_insert($player->pid, 0, $id, ($withdraw*-1), ($balance-$withdraw), 0);

			$message = t('BANK_WITHDRAW', money_format1($withdraw), t('BANK_GROUP_'.$id));
			$output->popup .= warquest_box_icon("info", $message);

			$log = 'Withdraw '.number_format2($withdraw).' for '.t('BANK_GROUP_'.$id);
			warquest_user_log($player, $log);

		} else {

			$message = t('BANK_WITHDRAW_FAILED', money_format1($withdraw));
			$output->popup .= warquest_box_icon("warning", $message);
		}
	}
}

/**
 * Clan member & Commander desposit money on clan bank.
 */
function warquest_clan_deposit_do() {

	/* input */
	global $player;
	global $cid;
	global $deposit;
	global $config;

	/* output */
	global $output;

	$old = mktime(date("H"), date("i"), date("s"), date("m"), date("d")-1, date("Y"));

	$query = 'select date from clan_bank where pid='.$player->pid.' and action=2 and date>"'.date("Y-m-d H:i:s", $old).'" order by date desc limit 0,1 ';
	$result = warquest_db_query($query);
	$data = warquest_db_fetch_object($result);

	/* Remove dots */
	$deposit = str_replace(".", "", $deposit);

	$clan = warquest_db_clan($cid);

	if ($deposit > $player->money) {

		$message = t('BANK_DEPOSIT_FAILED', money_format1($deposit));
		$output->popup .= warquest_box_icon("warning", $message);

	} else if ($deposit > ($player->money_step*10)) {

		$message = t('CLAN_DEPOSIT_TOO_HIGH', money_format1($player->money_step*10));
		$output->popup .= warquest_box_icon("warning", $message);

	} else if (isset($data->date)) {

		$new = mktime(date("H"), date("i"), date("s"), date("m"), date("d"), date("Y"));
		$value = (24*60*60) - ($new - strtotime($data->date));

		$tmp = '<script src="'.$config["content_url"].'js/countdown4.js"></script>';

		$tmp .= '<div class="countdown"><div id="countdown_time4"></div></div>';
		$tmp .= '<script>';
		$tmp .= "countdown4.init(".$value.", 'countdown_time4', '00:00:00');";
		$tmp .= '</script>';

		$message = t('CLAN_DEPOSIT_MAX',$tmp );
		$output->popup .= warquest_box_icon("warning", $message);

	} else {

		$clan->money += $deposit;
		warquest_db_clan_bank_insert($clan->cid, $player->pid, $deposit, $clan->money, 10);

		$fee = $deposit * ($config["init_clan_bank_deposit"]/100);

		$clan->money -= $fee;
		$clan->last_activity = date('Y-m-d H:i:s');
		warquest_db_clan_update($clan);

		warquest_db_clan_bank_insert($clan->cid, $player->pid, ($fee*-1), $clan->money, 2);




		$player->money -= $deposit;

		$message = t('BANK_DEPOSIT', money_format1($deposit), t('BANK_GROUP_4'));
		$output->popup .= warquest_box_icon("info", $message);

		$log = 'Deposit '.number_format2($deposit).' to clan bank';
		warquest_user_log($player, $log);
	}
}

/*
** ---------------------
** UI
** ---------------------
*/

/**
 * Show bank transaction log
 */
function warquest_bank_log($id) {

	/* input	*/
	global $mid;
	global $sid;
	global $player;
	global $config;
	global $offset;

	/* output */
	global $page;

	$limit=25;

	$query1  = 'select id from bank where bgid='.$id.' and pid1='.$player->pid;
	$result1 = warquest_db_query($query1);
	$total = warquest_db_num_rows($result1);

	$page .= '<div class="subparagraph">'.t('BANK_TRANSACTION_LOG').'</div>';

	if ($total == 0) {

		$message = t('BANK_NO_LOG');
		$page .= warquest_box_icon('info', $message);

	} else {

		/* show bank transactions. */
		$query2  = 'select a.id, a.pid1, a.pid2, a.amount, a.action, a.balance, ';
		$query2 .= 'date_format(a.date , "%d-%m-%Y %H:%i:%s") as date, ';
		$query2 .= '(select name from player where pid=a.pid2) as name ';
		$query2 .= 'from bank a where a.pid1='.$player->pid.' and a.bgid='.$id.' ';
		$query2 .= 'order by a.id desc ';
		$query2 .= 'limit '.$offset.','.$limit;

		$result2 = warquest_db_query($query2);

		$page .= '<div class="box rows">';

		$page .= warquest_page_control($offset, $limit, $total, 1);

		$page .= '<table>';

		$page .= '<tr>';
		$page .= '<th width="80">'.t('GENERAL_AGO').'</th>';
		$page .= '<th width="310">'.t('GENERAL_TRANSACTION').'</th>';
		$page .= '<th width="110">'.t('GENERAL_BALANCE').'</th>';
		$page .= '</tr>';

		while ($data2=warquest_db_fetch_object($result2)) {

			$page .= '<tr>';
			$page .= '<td>'.warquest_ui_ago($data2->date).'</td>';
			$page .= '<td>';

			if ($data2->action == 5) {
				$page .= warquest_link('mid='.$mid.'&sid='.PAGE_PROFILE.'&oid='.$data2->pid2, $data2->name).' ';
				$page .= t('BANK_TRANSACTION_TYPE_'.$data2->action);
				$page .= ' '.dollar_format($data2->amount).'.';
			} else {
				$page .= t('BANK_TRANSACTION_TYPE_'.$data2->action);
				$page .= ' '.dollar_format($data2->amount).'.';
			}

			$page .= '</td>';
			$page .= '<td>'.money_format1($data2->balance).'</td>';
			$page .= '</tr>';
		}

		$page .= '</table>';

		$page .= warquest_page_control($offset, $limit, $total, 0);
	}

	$page .= '</div>';
}


/**
 * Clan profile bank part
 */
function warquest_clan_bank() {

	/* input	*/
	global $mid;
	global $sid;
	global $ssid;

	global $player;
	global $config;
	global $offset;

	/* output */
	global $page;

	$player_clan = warquest_db_player_clan($player->pid);

	if ( !isset($player_clan->cid) || ($player_clan->approved==0)) {

		$page .= '<div class="subparagraph">';
		$page .= t('CLAN_BANK');
		$page .= '</div>';

		$message = t('CLAN_BANK_NO_CLAN');
		$page .= warquest_box_icon("warning", $message);

	} else {

		$clan = warquest_db_clan($player_clan->cid);

		$page .= '<div class="subparagraph">';
		$page .= $clan->name.'  '.t('CLAN_BANK');
		$page .= '</div>';

		$page .= '<div class="box">';

		$page .= '<table>';
		$page .= '<tr>';
		$page .= '<td width="160" >';
		$page .= warquest_bank_image(4, 140, 100);
		$page .= '</td>';

		$page .= '<td>';

		$page .= '<table>';

		$page .= '<tr>';
		$page .= '<td colspan="2">';
		$page .= t('LINK_BALANCE').":<br>";
		$page .= money_format1($clan->money);
		$page .= "</td>";

		$page .= "</tr>";

		$page .= "<tr>";

		$page .= '<td width="160">';
		if ( isset($player_clan->cid) && ($clan->cid==$player_clan->cid) ) {
			$page .= t('LINK_DEPOSIT').":<br>";
			$page .= '<input id="text" name="deposit" size="19" maxlength="32" type="text" value="';
			$tmp = $player->money_step * 10;
			if ( $tmp > $player->money ) {
				$tmp = $player->money;
			}
			$page .= number_format($tmp,0,",",".");
			$page .= '"><br>';
			$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&ssid='.$ssid.'&cid='.$clan->cid.'&eid='.EVENT_CLAN_DEPOSIT, t('LINK_DEPOSIT'));
		}
		$page .= "</td>";

		$page .= "</table>";

		$page .= '</td>';
		$page .= '</tr>';
		$page .= "</table>";

		$page .= '</div>';

		$page .= '<div class="note">';
		$page .= t('CLAN_BANK_INFO', $config["init_clan_bank_deposit"], $config["init_clan_bank_interest"]);
		$page .= '</div>';


		$page .= '<div class="subparagraph">'.t('CLAN_BANK_TRANSACTION').'</div>' ;
		$limit=20;

		$query1  = 'select cid from clan_bank where cid='.$clan->cid;
		$result1 = warquest_db_query($query1);
		$total = warquest_db_num_rows($result1);

		if ($total == 0) {

			$message = t('CLAN_BANK_NO_LOG');
			$page .= warquest_box_icon('info', $message);

		} else {

			/* show bank transactions. */
			$query2  = 'select a.pid, a.amount, a.action, a.balance, ';
			$query2 .= 'date_format(a.date , "%d-%m-%Y %H:%i:%s") as date, ';
			$query2 .= '(select name from player where pid=a.pid) as name, ';
			$query2 .= '(select country from player where pid=a.pid) as country ';
			$query2 .= 'from clan_bank a where a.cid='.$clan->cid.' order by a.cbid desc ';
			$query2 .= 'limit '.$offset.','.$limit;

			$result2 = warquest_db_query($query2);

			$page .= '<div class="box rows">';

			$page .= warquest_page_control($offset, $limit, $total, 1, '&cid='.$clan->cid);

			$page .= '<table>';

			$page .= '<tr>';
			$page .= '<th width="80">'.t('GENERAL_AGO').'</th>';
			$page .= '<th width="310">'.t('GENERAL_TRANSACTION').'</th>';
			$page .= '<th width="110">'.t('GENERAL_BALANCE').'</th>';
			$page .= '</tr>';

			while ($data2=warquest_db_fetch_object($result2)) {

				$page .= '<tr>';
				$page .= '<td>'.warquest_ui_ago($data2->date).'</td>';
				$page .= '<td>';

				switch ($data2->action) {

					case 10:
						$page .= player_format($data2->pid, $data2->name, $data2->country).' '.t('BANK_TRANSACTION_TYPE_'.$data2->action);
						$page .= ' '.dollar_format($data2->amount).'.';
						break;

					case 11:
						$page .= t('BANK_TRANSACTION_TYPE_'.$data2->action,t('GENERAL_PLANET_'.$data2->pid)).' ';
						$page .= ' '.dollar_format($data2->amount).'.';
						break;

					default:
						$page .= t('BANK_TRANSACTION_TYPE_'.$data2->action);
						$page .= ' '.dollar_format($data2->amount).'.';
						break;
				}

				$page .= '</td>';
				$page .= '<td>'.money_format1($data2->balance).'</td>';
				$page .= '</tr>';
			}

			$page .= '</table>';

			$page .= warquest_page_control($offset, $limit, $total, 0, '&cid='.$clan->cid);

			$page .= '</div>';
		}
	}

	$page .= '<div class="note">';
	$page .= t('CLAN_BANK_NOTE');
	$page .= '</div>';
}


/**
 * Bank form
 */
function warquest_bank_form($id) {

	/* input */
	global $mid;
	global $sid;
	global $ssid;

	global $player;
	global $config;

	/* output */
	global $page;
	global $output;

	$output->title = t('BANK_GROUP_'.$id);

	$page .= '<div class="subparagraph">';
	$page .= t('BANK_GROUP_'.$id).' '.t('GENERAL_BANK');
	$page .= '</div>';

	$balance=0;

	switch ($ssid) {
		case PAGE_BANK_NATIONAL:
				$balance=$player->bank1;
				break;

		case PAGE_BANK_UNION:
				$balance=$player->bank2;
				break;

		case PAGE_BANK_SWISSCORE:
				$balance=$player->bank3;
				break;
	}

	$page .= '<div class="box">';

	$page .= '<table>';
	$page .= '<tr>';
	$page .= '<td width="160" >';
	$page .= warquest_bank_image($id, 140, 100);
	$page .= '</td>';

	$page .= '<td>';

	$page .= "<table>";

	$page .= "<tr>";
	$page .= '<td colspan="2">';
	$page .= t('LINK_BALANCE').":<br>";
	$page .= money_format1($balance);
	$page .= "</td>";

	$page .= "</tr>";

	$page .= '<tr>';
	$page .= '<td width="160">';
	$page .= t('LINK_DEPOSIT').":<br>";
	$page .= '<input id="text" name="deposit" size="19" maxlength="32" type="text" value="';
	$page .= number_format($player->money,0,",",".").'">';
	$page .= '<br>';
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&ssid='.$ssid.'&id='.$id.'&eid='.EVENT_BANK_DEPOSIT, t('LINK_DEPOSIT'), 'deposit-0');
	$page .= "</td>";

	$page .= '<td>';
	$page .= t('LINK_WITHDRAW').":<br>";
	$page .= '<input id="text" name="withdraw" size="19" maxlength="32" type="text" value="'.number_format($balance,0,",",".").'"><br>';
	$page .= warquest_link('mid='.$mid.'&sid='.$sid.'&ssid='.$ssid.'&id='.$id.'&eid='.EVENT_BANK_WITHDRAW, t('LINK_WITHDRAW'), 'withdraw-1');
	$page .= "</td>";
	$page .= "</tr>";

	$page .= "</table>";

	$page .= '</td>';
	$page .= '</tr>';
	$page .= "</table>";

	$page .= '</div>';

	switch ($ssid) {
		case PAGE_BANK_NATIONAL:
					$init_bank_deposit = $config["init_bank1_deposit"];
				   $init_bank_interest = $config["init_bank1_interest"];
					break;

		case PAGE_BANK_UNION:
					$init_bank_deposit = $config["init_bank2_deposit"];
					$init_bank_interest = $config["init_bank2_interest"];
					break;

		case PAGE_BANK_SWISSCORE:
					$init_bank_deposit = $config["init_bank3_deposit"];
					$init_bank_interest = $config["init_bank3_interest"];
					break;
	}

	$page .= '<div class="note">';
	$page .= t('BANK_NOTE', $init_bank_deposit, $init_bank_interest);
	if (($ssid==PAGE_BANK_UNION) || ($ssid==PAGE_BANK_SWISSCORE)) {
		$page .= '<br>'.t('BANK_WARNING');
	}
	$page .= '</div>';
}

/*
** -------------
** HANDLER
** -------------
*/

function warquest_bank() {

	/* input */
	global $eid;
	global $ssid;

	/* Event handler */
	switch ($eid) {

		case EVENT_BANK_DEPOSIT:
				warquest_bank_deposit_do();
				break;

		case EVENT_BANK_WITHDRAW:
				warquest_bank_withdraw_do();
				break;

		case EVENT_CLAN_DEPOSIT:
				warquest_clan_deposit_do();
				break;
	}

	/* Page handler */

	switch ($ssid) {

		case PAGE_BANK_NATIONAL:
					warquest_bank_form(1);
					warquest_bank_log(1);
					break;

		case PAGE_BANK_UNION:
					warquest_bank_form(2);
					warquest_bank_log(2);
					break;

		case PAGE_BANK_SWISSCORE:
					warquest_bank_form(3);
					warquest_bank_log(3);
					break;

		case PAGE_BANK_CLAN:
					warquest_clan_bank();
					break;
	}

	warquest_player();
}
