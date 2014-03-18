package nl.warquest.server;

import javax.jws.WebService;
import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;
import javax.persistence.Persistence;

import nl.warquest.database.dao.ClanDao;
import nl.warquest.database.entity.Clan;

@WebService()
public class ClanService {

	private static EntityManagerFactory entityManagerFactory;	
	private static EntityManager entityManager;
	
	public ClanService() {
		entityManagerFactory = Persistence.createEntityManagerFactory( "warquest" );
	    entityManager = entityManagerFactory.createEntityManager();	      
	}
		
	public Clan getClan(int cid) {
			      
		ClanDao clanDao = new ClanDao(entityManager);
		Clan clan = clanDao.findById(cid);
		
		return clan;
	}	 
}
