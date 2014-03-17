package nl.warquest.database;
// Generated 17-mrt-2014 21:30:46 by Hibernate Tools 3.2.2.GA


import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * Home object for domain model class RebelAward.
 * @see nl.warquest.database.RebelAward
 * @author Hibernate Tools
 */
@Stateless
public class RebelAwardHome {

    private static final Log log = LogFactory.getLog(RebelAwardHome.class);

    @PersistenceContext private EntityManager entityManager;
    
    public void persist(RebelAward transientInstance) {
        log.debug("persisting RebelAward instance");
        try {
            entityManager.persist(transientInstance);
            log.debug("persist successful");
        }
        catch (RuntimeException re) {
            log.error("persist failed", re);
            throw re;
        }
    }
    
    public void remove(RebelAward persistentInstance) {
        log.debug("removing RebelAward instance");
        try {
            entityManager.remove(persistentInstance);
            log.debug("remove successful");
        }
        catch (RuntimeException re) {
            log.error("remove failed", re);
            throw re;
        }
    }
    
    public RebelAward merge(RebelAward detachedInstance) {
        log.debug("merging RebelAward instance");
        try {
            RebelAward result = entityManager.merge(detachedInstance);
            log.debug("merge successful");
            return result;
        }
        catch (RuntimeException re) {
            log.error("merge failed", re);
            throw re;
        }
    }
    
    public RebelAward findById( int id) {
        log.debug("getting RebelAward instance with id: " + id);
        try {
            RebelAward instance = entityManager.find(RebelAward.class, id);
            log.debug("get successful");
            return instance;
        }
        catch (RuntimeException re) {
            log.error("get failed", re);
            throw re;
        }
    }
}

