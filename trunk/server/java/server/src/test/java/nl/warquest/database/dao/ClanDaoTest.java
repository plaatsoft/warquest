package nl.warquest.database.dao;

import static org.junit.Assert.*;

import java.util.Date;
import java.util.List;

import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;
import javax.persistence.Persistence;

import nl.warquest.database.entity.Clan;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

public class ClanDaoTest {

	private EntityManagerFactory entityManagerFactory;	
	private EntityManager entityManager;
	private ClanDao clanDao;
	
	@Before 
	public void testBefore() {
		
		 entityManagerFactory = Persistence.createEntityManagerFactory( "warquest" );
	     entityManager = entityManagerFactory.createEntityManager();
	     clanDao = new ClanDao(entityManager);
	}
	
	@Test
	public void testFindByIdy() {
	    
	      Clan clan = clanDao.findById(18);
	      
	      assertEquals("Clan findbyId", new Integer(18), clan.getCid());
    } 
	
	@Test
	public void testCommit() {
	    
		 entityManager.getTransaction().begin(); 
		 
		 Clan clan = new Clan();
         clan.setName("test12");  
         clan.setCreated(new Date());
         clan.setLastActivity(new Date());
         clan.setSlogan("Slogan 21");
         clanDao.persist(clan);
         
         entityManager.getTransaction().commit();
    } 
	
	
	@Test
	public void testFindAll() {
	    
		 List<Clan> result = clanDao.findAll();
		 for ( Clan clan : result ) {
		    
			 assertTrue(clan.getCid()!=0);
		}
    } 
	
	@After 
	public void testAfter() {
		
		entityManager.close();
	}
	
}
