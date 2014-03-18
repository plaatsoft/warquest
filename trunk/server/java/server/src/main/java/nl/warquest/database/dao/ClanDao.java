package nl.warquest.database.dao;

import java.util.List;

import javax.persistence.EntityManager;

import nl.warquest.database.entity.Clan;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

public class ClanDao {

	private static final Log log = LogFactory.getLog(Clan.class);
	 
    private EntityManager entityManager;
    
    public ClanDao(EntityManager entityManager) {
    	this.entityManager = entityManager;
    }
    
    public void persist(Clan transientInstance) {
        log.debug("persisting Clan instance");
        try {
            entityManager.persist(transientInstance);
            log.debug("persist successful");
        }
        catch (RuntimeException re) {
            log.error("persist failed", re);
            throw re;
        }
    }
    
    public void remove(Clan persistentInstance) {
        log.debug("removing Clan instance");
        try {
            entityManager.remove(persistentInstance);
            log.debug("remove successful");
        }
        catch (RuntimeException re) {
            log.error("remove failed", re);
            throw re;
        }
    }
    
    public Clan merge(Clan detachedInstance) {
        log.debug("merging Clan instance");
        try {
            Clan result = entityManager.merge(detachedInstance);
            log.debug("merge successful");
            return result;
        }
        catch (RuntimeException re) {
            log.error("merge failed", re);
            throw re;
        }
    }
    
    public Clan findById( Integer id) {
        log.debug("getting Clan instance with id: " + id);
        try {
            Clan instance = entityManager.find(Clan.class, id);
            log.debug("get successful");
            return instance;
        }
        catch (RuntimeException re) {
            log.error("get failed", re);
            throw re;
        }
    }
    
    public List <Clan> findAll() {
        log.debug("getting all Clan");
        try {
            List <Clan> result = entityManager.createQuery("SELECT c from Clan c").getResultList();
            log.debug("get successful");
            return result;
        }
        catch (RuntimeException re) {
            log.error("get failed", re);
            throw re;
        }
    }
    
}
