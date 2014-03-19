package nl.warquest.database.dao;

import static org.junit.Assert.assertEquals;

import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;
import javax.persistence.Persistence;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

public class MemberDaoTest {

	private EntityManagerFactory entityManagerFactory;	
	private EntityManager entityManager;
	private MemberDao memberDao;
	
	@Before 
	public void testBefore() {
		
		 entityManagerFactory = Persistence.createEntityManagerFactory( "warquest" );
	     entityManager = entityManagerFactory.createEntityManager();
	     memberDao = new MemberDao(entityManager);
	}
	
	
	@Test
	public void testLoginInvalid() {
		
		Integer pid = memberDao.doLogin("test1", "test1");
		assertEquals("Login must fail!", new Integer(0), pid);
    } 
	
	@After 
	public void testAfter() {
		
		entityManager.close();
	}
}
