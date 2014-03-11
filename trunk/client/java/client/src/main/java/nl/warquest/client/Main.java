package nl.warquest.client;

import nl.warquest.service.warquest.Alliance;
import nl.warquest.service.warquest.Battle;
import nl.warquest.service.warquest.Force;
import nl.warquest.service.warquest.Mission;
import nl.warquest.service.warquest.Planet;
import nl.warquest.service.warquest_wsdl.WarQuest;
import nl.warquest.service.warquest_wsdl.WarQuestPort;

public class Main {

	public static void main(String[] args) {
        		
		WarQuest warquest = new WarQuest();
		WarQuestPort port = warquest.getWarQuestPort();
		long startTime;
		long endTime;
		long duration;
		
		/* Max robot nr. is 2506 */		
		for (int i=2506; i>=1; i--) {
		
			String username = "robot"+i;
			String password = "robot"+i;
			
			System.out.print("------------------\n");			
			startTime = System.currentTimeMillis();
			        
			Mission mission = port.doMission(username, password, true, false);
			System.out.println("username="+username);
			System.out.println("mission.result="+mission.isResult());
			System.out.println("mission.popup="+mission.getPopup());
						
			endTime = System.currentTimeMillis();
			
			duration = endTime - startTime;
			System.out.print("duration "+duration+" ms\n");
			
			System.out.print("------------------\n");						
			startTime = System.currentTimeMillis();
						
			Battle battle = port.doBattle(username, password, Planet.EARTH, Force.AIRFORCE);
			System.out.println("username="+username);
			System.out.println("battle.result="+battle.isResult());
			System.out.println("battle.popup="+battle.getPopup());
			
			endTime = System.currentTimeMillis();
			
			duration = endTime - startTime;
			System.out.print("duration "+duration+" ms\n");
			
			System.out.print("------------------\n");						
			startTime = System.currentTimeMillis();
						
			Alliance alliance = port.doAlliance(username, password);
			System.out.println("username="+username);
			System.out.println("alliance.result="+alliance.isResult());
			System.out.println("alliance.popup="+alliance.getPopup());
			
			endTime = System.currentTimeMillis();
			
			duration = endTime - startTime;
			System.out.print("duration "+duration+" ms\n");		
		}
	}
}
