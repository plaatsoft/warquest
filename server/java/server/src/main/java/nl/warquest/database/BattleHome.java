package nl.warquest.database;
// Generated 17-mrt-2014 21:30:46 by Hibernate Tools 3.2.2.GA


import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * Home object for domain model class Battle.
 * @see nl.warquest.database.Battle
 * @author Hibernate Tools
 */
@Stateless
public class BattleHome {

    private static final Log log = LogFactory.getLog(BattleHome.class);

    @PersistenceContext private EntityManager entityManager;
    
    public void persist(Battle transientInstance) {
        log.debug("persisting Battle instance");
        try {
            entityManager.persist(transientInstance);
            log.debug("persist successful");
        }
        catch (RuntimeException re) {
            log.error("persist failed", re);
            throw re;
        }
    }
    
    public void remove(Battle persistentInstance) {
        log.debug("removing Battle instance");
        try {
            entityManager.remove(persistentInstance);
            log.debug("remove successful");
        }
        catch (RuntimeException re) {
            log.error("remove failed", re);
            throw re;
        }
    }
    
    public Battle merge(Battle detachedInstance) {
        log.debug("merging Battle instance");
        try {
            Battle result = entityManager.merge(detachedInstance);
            log.debug("merge successful");
            return result;
        }
        catch (RuntimeException re) {
            log.error("merge failed", re);
            throw re;
        }
    }
    
    public Battle findById( Integer id) {
        log.debug("getting Battle instance with id: " + id);
        try {
            Battle instance = entityManager.find(Battle.class, id);
            log.debug("get successful");
            return instance;
        }
        catch (RuntimeException re) {
            log.error("get failed", re);
            throw re;
        }
    }
}

