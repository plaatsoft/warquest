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
** ---------------------
** PDF Report
** ---------------------
*/

function warquest_player_report_do($id) {
	
	class PDF extends FPDF
	{
		function Header() {
			$this->SetFont('Arial','B', 30);
			$this->Ln(4);
			$this->Cell(0,10,'WarQuest',0,0,'C');
			$this->Ln();
			$this->Cell(0,10,'Player Overview',0,0,'C');
			$this->Ln(13);
		}

		function Footer() {
			/* Position at 1.5 cm from bottom */ 
			$this->SetY(-15);
			$this->SetFont('Arial','I',8);
			$this->Cell(0,10,'Page '.$this->PageNo().'/{nb}',0,0,'C');
		}
			
		function Overview($data) {
				
			$height = 5.2;
			$width = 90;
			
			$this->SetLeftMargin(15);
			
			$this->SetFillColor(255,255,255);
			$this->SetFont('Arial','I', 12);
			
			$this->Cell(0,$height,t('PLAYER_OVERVIEW'),0,0,'L',true);		
			$this->Ln();
			
			$this->SetFont('','B');
			$this->Cell($width,$height,t('PLAYER_RANK'),1, 0, 'L',true);			
			$this->SetFont('','');
			$this->Cell($width,$height,warquest_rank($data->lid), 1, 0,'L',true);
			$this->Ln();
			
			$this->SetFont('','B');
			$this->Cell($width,$height,t('PLAYER_NAME'),1, 0, 'L',true);
			$this->SetFont('','');
			$this->Cell($width,$height,$data->name, 1, 0, 'L',true);
			$this->Ln();
						
			$this->SetFont('','B');
			$this->Cell($width,$height,t('GENERAL_COUNTRY'), 1, 0, 'L',true);
			$this->SetFont('','');
			$land = html_entity_decode(warquest_landcode($data->country));
			$this->Cell($width,$height, $land, 1, 0,'L',true);
			$this->Ln();
			
			$this->SetFont('','B');
			$this->Cell($width,$height,t('GENERAL_LEVEL'), 1, 0, 'L',true);
			$this->SetFont('','');
			$this->Cell($width,$height, $data->lid, 1, 0, 'L',true);
			$this->Ln();
			
			$this->SetFont('','B');
			$this->Cell($width,$height, t('PLAYER_EXP_POINTS'), 1, 0,'L',true);
			$this->SetFont('','');
			$this->Cell($width,$height, number_format($data->experience,0,",","."), 1, 0,'L',true);
			
			$this->Ln(10);
		}
			
		function Statistics($data) {
					
			$height = 5.2;
			$width = 90;
			
			$this->SetFillColor(255,255,255);
			$this->SetFont('Arial','I', 12);
			
			$this->Cell(0,$height, t('PLAYER_STATISTICS'), 0, 0,'L',true);		
			$this->Ln();
			
			$this->SetFont('','B');
			$this->Cell($width,$height, t('PLAYER_FIGHTS_WON'), 1, 0,'L',true);			
			$this->SetFont('','');
			$this->Cell($width,$height, number_format($data->won,0,",","."), 1, 0,'L',true);
			$this->Ln();
			
			$this->SetFont('','B');
			$this->Cell($width,$height, t('PLAYER_FIGHTS_LOST'),1,0,'L',true);
			$this->SetFont('','');
			$this->Cell($width,$height, number_format($data->lost,0,",","."), 1, 0,'L',true);
			$this->Ln();
			
			$value=0;
			if ($data->lost>0) {
				$value = round(($data->won/$data->lost),2);
			}
			
			$this->SetFont('','B');
			$this->Cell($width,$height, t('PLAYER_WIN_LOST_RATE'), 1, 0, 'L', true);
			$this->SetFont('','');
			$this->Cell($width,$height, $value, 1, 0,'L',true);
			$this->Ln();
			
			$this->SetFont('','B');
			$this->Cell($width,$height, t('PLAYER_ALLIANCE_SIZE'), 1, 0,'L',true);
			$this->SetFont('','');
			$this->Cell($width,$height, $data->alliance, 1, 0,'L',true);
			$this->Ln();
			
			$this->SetFont('','B');
			$this->Cell($width,$height, t('PLAYER_MISSION_COMPLETED'), 1, 0,'L',true);
			$this->SetFont('','');
			$this->Cell($width,$height, number_format($data->mission,0,",","."), 1, 0,'L',true);
			$this->Ln();
			
			$this->SetFont('','B');
			$this->Cell($width,$height, t('PLAYER_CASINO_PLAYED'), 1, 0,'L',true);
			$this->SetFont('','');
			$this->Cell($width,$height, number_format($data->casino,0,",","."), 1, 0,'L',true);
			$this->Ln();
		
			$this->SetFont('','B');
			$this->Cell($width,$height, t('PLAYER_SERVER_REQUEST'), 1, 0, 'L', true);
			$this->SetFont('','');
			$this->Cell($width,$height, number_format($data->request,0,",","."), 1, 0,'L',true);
			$this->Ln();
					
			$this->SetFont('','B');
			$this->Cell($width,$height, t('PLAYER_DISCOUNT_RATE'), 1, 0, 'L', true);
			$this->SetFont('','');
			$this->Cell($width,$height, '+'.warquest_db_discount($data, $data->planet).'%', 1, 0,'L',true);
			$this->Ln();
			
			$this->SetFont('','B');
			$this->Cell($width,$height, t('PLAYER_MAINTENANCE_RATE'), 1, 0, 'L', true);
			$this->SetFont('','');
			$this->Cell($width,$height, '+'.warquest_db_maintenance($data, $data->planet).'%', 1, 0,'L',true);
			
			$this->Ln(10);
		}
	
		function Platform($data) {
					
			$height = 5.2;
			$width = 90;
			
			$member = warquest_db_member($data->pid);
			
			$this->SetFillColor(255,255,255);
			$this->SetFont('Arial','I', 12);
			
			$this->Cell(0,$height, t('PLAYER_PLATFORM_BROWSER'), 0, 0,'L',true);		
			$this->Ln();
			
			$this->SetFont('','B');
			$this->Cell($width,$height, t('PLAYER_BROWSER'), 1, 0,'L',true);			
			$this->SetFont('','');
			$this->Cell($width,$height, $member->browser, 1, 0,'L',true);
			$this->Ln();
			
			$this->SetFont('','B');
			$this->Cell($width,$height, t('PLAYER_BROWSER_VERSION'), 1, 0,'L',true);			
			$this->SetFont('','');
			$this->Cell($width,$height, $member->version, 1, 0,'L',true);
			$this->Ln();
			
			$this->SetFont('','B');
			$this->Cell($width,$height, t('PLAYER_PLATFORM'), 1, 0,'L',true);			
			$this->SetFont('','');
			$this->Cell($width,$height, $member->platform, 1, 0,'L',true);
			
			$this->Ln(10);
		}
		
		function Strength($data) {
				
			$height = 5.2;
			$width = 60;
			
			$this->SetFillColor(255,255,255);
			$this->SetFont('Arial','I', 12);
			
			$this->Cell(0,$height, t('PLAYER_FORCE'), 0, 0,'L',true);		
			$this->Ln();
			
			$this->SetFont('','B');
			$this->Cell($width, $height, "", 1, 0,'L',true);			
			$this->Cell($width, $height, t('PLAYER_ATTACK_STRENGTH'), 1, 0,'L',true);
			$this->Cell($width, $height, t('PLAYER_DEFENSE_STRENGTH'), 1, 0,'L',true);
			$this->Ln();
			
			$query2  = 'select ugid, type from unit_group where planet='.$data->planet.' and type!=6 and type!=1 order by type';
			$result2 = warquest_db_query($query2);	
	
			while ($data2=warquest_db_fetch_object($result2)) {
	
				$this->SetFont('','B');
				$this->Cell($width, $height, t('UNIT_GROUP_'.$data2->ugid), 1, 0,'L',true);			
				$this->SetFont('','');
				$this->Cell($width, $height, number_format(warquest_attack_strength($data, $data2->ugid),0,",","."), 1, 0,'L',true);
				$this->Cell($width, $height, number_format(warquest_defense_strength($data, $data2->ugid),0,",","."), 1, 0,'L',true);
				$this->Ln();
			}
			
			$this->Ln(4);
		}

		function CashFlow($data) {
					
			$height = 5.2;
			$width = 60;
			
			$this->SetFillColor(255,255,255);
			$this->SetFont('Arial','I', 12);
			
			$this->Cell($width, $height, t('PLAYER_CASH_FLOW'), 0, 0,'L',true);		
			$this->Ln();
						
			$building_income = warquest_building_income($data, $data->planet);
							
			$this->SetFont('','B');
			$this->Cell($width, $height, t('PLAYER_BUILDING_INCOME'), 1, 0,'L',true);			
			$this->SetFont('','');
			$this->Cell($width, $height, number_format($building_income,0,",",".").' '.t('GENERAL_DOLLAR'), 1, 0,'L',true);
			$this->Ln();
			
			$continent_income = warquest_continent_income($data, $data->planet);
		
			$this->SetFont('','B');
			$this->Cell($width, $height, t('PLAYER_CONTINENT_INCOME'),1,0,'L',true);
			$this->SetFont('','');
			$this->Cell($width, $height, number_format($continent_income ,0,",",".").' '.t('GENERAL_DOLLAR'), 1, 0,'L',true);
			$this->Ln();
			
			$clan_war_income = warquest_clan_war_income($data, $data->planet);
		
			$this->SetFont('','B');
			$this->Cell($width, $height, t('PLAYER_CLAN_WAR_INCOME'),1,0,'L',true);
			$this->SetFont('','');
			$this->Cell($width, $height, number_format($clan_war_income ,0,",",".").' '.t('GENERAL_DOLLAR'), 1, 0,'L',true);
			$this->Ln();
					
			$unit_upkeep = warquest_unit_upkeep($data, $data->planet);
		
			$this->SetFont('','B');
			$this->Cell($width, $height, t('PLAYER_UPKEEP'),1,0,'L',true);
			$this->SetFont('','');
			$this->Cell($width, $height, '-'.number_format($unit_upkeep,0,",",".").' '.t('GENERAL_DOLLAR'), 1, 0,'L',true);
			$this->Ln();
			
			$netto_income = $building_income + $continent_income + $clan_war_income - $unit_upkeep;
		
			$this->SetFont('','B');
			$this->Cell($width, $height, t('PLAYER_NETTO_INCOME'), 1, 0,'L',true);
			$this->SetFont('','');
			$this->Cell($width, $height, number_format($netto_income,0,",",".").' '.t('GENERAL_DOLLAR'), 1, 0,'L',true);
			$this->Ln(10);		
		}
		
		function Assets($data) {
					
			$height = 5.2;
			$width = 90;
			
			$this->SetFillColor(255,255,255);
			$this->SetFont('Arial','I', 12);
			
			$this->Cell($width, $height, t('PLAYER_MONEY_STATUS'), 0, 0,'L',true);		
			$this->Ln();
			
			$this->SetFont('','B');
			$this->Cell($width, $height, t('PLAYER_CASH_MONEY'), 1, 0,'L',true);			
			$this->SetFont('','');
			$this->Cell($width, $height, number_format($data->money,0,",",".").' '.t('GENERAL_DOLLAR'), 1, 0,'L',true);
			$this->Ln();
			
			$this->SetFont('','B');
			$this->Cell($width, $height, t('BANK_GROUP_1').' '.t('PLAYER_BANK'),1,0,'L',true);
			$this->SetFont('','');
			$this->Cell($width, $height, number_format($data->bank1,0,",",".").' '.t('GENERAL_DOLLAR'), 1, 0,'L',true);
			$this->Ln();
			
			$this->SetFont('','B');
			$this->Cell($width, $height, t('BANK_GROUP_2').' '.t('PLAYER_BANK'),1,0,'L',true);
			$this->SetFont('','');
			$this->Cell($width, $height, number_format($data->bank2,0,",",".").' '.t('GENERAL_DOLLAR'), 1, 0,'L',true);
			$this->Ln();
			
			$this->SetFont('','B');
			$this->Cell($width, $height, t('BANK_GROUP_3').' '.t('PLAYER_BANK'),1,0,'L',true);
			$this->SetFont('','');
			$this->Cell($width, $height, number_format($data->bank3,0,",",".").' '.t('GENERAL_DOLLAR'), 1, 0,'L',true);
			$this->Ln();
			
			$this->SetFont('','B');
			$this->Cell($width, $height, t('GENERAL_STOCKS'),1,0,'L',true);
			$this->SetFont('','');
			$this->Cell($width, $height, number_format(warquest_db_bank_assest($data->pid),0,",",".").' '.t('GENERAL_DOLLAR'), 1, 0,'L',true);
			$this->Ln();
					
			$this->Ln(10);
		}
		
		function Units($data) {
		
			global $config;
			
			$page ="";
			$max = 7;
		
			$query1  = 'select ugid from unit_group where planet='.$data->planet.' order by type';
			$result1 = warquest_db_query($query1);	

			while ($data1=warquest_db_fetch_object($result1)) {
	
				$query2  = 'select a.uid, a.attack, a.defense, a.ugid, b.amount ';
				$query2 .= 'from unit a inner join player_unit b ';
				$query2 .= 'ON a.uid=b.uid and b.pid='.$data->pid.' where a.ugid='.$data1->ugid.' ';
				$query2 .= 'order by a.lid';  
				$result2 = warquest_db_query($query2);

				if (warquest_db_num_rows($result2)>0) { 

					$height = 5;
					$width = 45;
			
					$this->SetLeftMargin(10);
					$this->SetY(0);
			
					$this->AddPage();
				
					$this->SetFillColor(255,255,255);
					$this->SetFont('Arial','I', 18);
			
					$this->Cell($width, $height, t('UNIT_GROUP_'.$data1->ugid).' '.t('LINK_UNITS'), 0, 0,'L',true);		
					$this->Ln();
			
					$this->SetFillColor(255,255,255);
					$this->SetFont('Arial','B', 8);
					$this->SetFont('','');
			
					$y = 20;
					$x = 10;
					$count = 0;
					$max = 7;
					
					while ($unit=warquest_db_fetch_object($result2)) {
	
						$this->SetLeftMargin($x);
						$this->SetY($y);
						
						$y+=32;
						$count++;
						
						$this->Image('images/units/unit'.$unit->uid.'.jpg', $x, $y, 35, 27);	
						
						$this->SetY($y + 26);
						$value = t('UNIT_'.$unit->uid).' ['.number_format2($unit->amount).'x]';
						$this->Cell($width, $height, $value, 0, 0,'L',true);
					
						if (($count % $max)==0) {
							$y = 20;
							$x += 50;
						}
					}
				}
			}
		}
		
		function Buildings($data) {
		
			global $config;
			
			$page ="";
			$max = 7;
		
			$query2  = 'select bgid from building_group where planet='.$data->planet.' order by bgid';
			$result2 = warquest_db_query($query2);	
	
			while ($data2=warquest_db_fetch_object($result2)) {
		
				$query  = 'select a.bid, a.ugid, a.income, a.defense, a.energy, b.pid, b.amount ';
				$query .= 'from building a inner join player_building b ';
				$query .= 'ON a.bid=b.bid and b.pid='.$data->pid.' ';
				$query .= 'where a.bgid='.$data2->bgid.' ';
				$query .= 'order by a.lid';  
				$result = warquest_db_query($query);
			
				if (warquest_db_num_rows($result)>0) { 

					$height = 5;
					$width = 45;
			
					$this->SetLeftMargin(10);
					$this->SetY(0);
			
					$this->AddPage();
				
					$this->SetFillColor(255,255,255);
					$this->SetFont('Arial','I', 18);
			
					$this->Cell($width, $height, t('BUILDING_GROUP_'.$data2->bgid).' '.t('PLAYER_BUILDINGS'), 0, 0,'L',true);		
					$this->Ln();
			
					$this->SetFillColor(255,255,255);
					$this->SetFont('Arial','B', 8);
					$this->SetFont('','');
			
					$y = 20;
					$x = 10;
					$count = 0;
					$max = 7;
					
					while ($building=warquest_db_fetch_object($result)) {
	
						$this->SetLeftMargin($x);
						$this->SetY($y);
						
						$y+=32;
						$count++;
						
						$this->Image('images/buildings/building'.$building->bid.'.jpg', $x, $y, 35, 27);	
						
						$this->SetY($y + 26);
						$value = t('BUILDING_'.$building->bid).' ['.number_format2($building->amount).'x]';
						$this->Cell($width, $height, $value, 0, 0,'L',true);
					
						if (($count % $max)==0) {
							$y = 20;
							$x += 50;
						}
					}
				}
			}	
		}
	}
	
	$data=warquest_db_player($id);
	
	/* Instanciation of inherited class */
	$pdf=new PDF();
	$pdf->SetTitle("WarQuest Player Overview");
	$pdf->SetAuthor('PlaatSoft');
	$pdf->AliasNbPages();
	$pdf->AddPage();
	
	$pdf->Overview($data);
	$pdf->Statistics($data);
	$pdf->Platform($data);
	$pdf->Strength($data);
	$pdf->CashFlow($data);	
	$pdf->Assets($data);	
	
	$pdf->Units($data);	
	$pdf->Buildings($data);
	
	$pdf->Output('WarQuest.pdf','D');
}


?>