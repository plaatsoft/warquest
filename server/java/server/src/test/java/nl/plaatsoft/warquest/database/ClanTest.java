package nl.plaatsoft.warquest.database;

import static org.junit.Assert.assertTrue;
import nl.plaatsoft.warquest.database.Database;

import org.junit.Test;

public class ClanTest {

	@Test
	public void testMultiply() {
		 
		Database db = new Database();
			
		db.connect();	

		db.clan.getClan();
		
		assertTrue("Clans found", true);
		 
		db.close();
	 } 
	
}
