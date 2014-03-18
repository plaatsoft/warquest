package nl.warquest.server;

import java.util.Date;
import java.util.List;

import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;
import javax.persistence.Persistence;

import nl.warquest.database.entity.Clan;
import nl.warquest.database.dao.ClanDao;
import nl.warquest.database.dao.MemberDao;

public class Main {

	private static EntityManagerFactory entityManagerFactory;
	
	private static EntityManager entityManager;
	
	  public static void main(String args[]) {
		  
		  entityManagerFactory = Persistence.createEntityManagerFactory( "warquest" );
	      entityManager = entityManagerFactory.createEntityManager();	      
	      
	      entityManager.getTransaction().begin(); 
	        
	      ClanDao clanDao = new ClanDao(entityManager);
	    
	      Clan clan2 = clanDao.findById(18);
	      System.out.println( "Clan name:" + clan2.getName() + " id="+clan2.getCid());
	      
	      /*clanDao.remove(clan2);
	      entityManager.getTransaction().commit();*/
	    
          Clan clan3 = new Clan();
          clan3.setName("test12");  
          clan3.setCreated(new Date());
          clan3.setLastActivity(new Date());
          clan3.setSlogan("Slogan 21");
          clanDao.persist(clan3);
          
		  entityManager.getTransaction().commit();
		  		  
		  List<Clan> result = clanDao.findAll();
		  for ( Clan clan1 : result ) {
		      System.out.println( "Clan name:" + clan1.getName() + " id="+clan1.getCid());
		  }
		  
		  MemberDao memberDao = new MemberDao(entityManager);
		  Integer pid = memberDao.doLogin("test1", "test1");
		  System.out.println( "PID:" + pid);
		  			 
		  entityManager.close();
      }
	  
	  
}
