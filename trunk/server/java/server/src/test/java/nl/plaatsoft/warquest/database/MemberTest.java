package nl.plaatsoft.warquest.database;

import static org.junit.Assert.assertEquals;
import nl.plaatsoft.warquest.database.Database;

import org.junit.Test;

public class MemberTest {

	
	
	@Test
	public void testMultiply() {
		 
		Database db = new Database();
			
		db.connect();	

		int pid = db.member.doLogin("test", "test");
		
		assertEquals("Pid not 0", pid, 0);
		 
		db.close();
	 } 
}
