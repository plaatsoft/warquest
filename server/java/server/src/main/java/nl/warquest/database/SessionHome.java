package nl.warquest.database;
// Generated 17-mrt-2014 21:30:46 by Hibernate Tools 3.2.2.GA


import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * Home object for domain model class Session.
 * @see nl.warquest.database.Session
 * @author Hibernate Tools
 */
@Stateless
public class SessionHome {

    private static final Log log = LogFactory.getLog(SessionHome.class);

    @PersistenceContext private EntityManager entityManager;
    
    public void persist(Session transientInstance) {
        log.debug("persisting Session instance");
        try {
            entityManager.persist(transientInstance);
            log.debug("persist successful");
        }
        catch (RuntimeException re) {
            log.error("persist failed", re);
            throw re;
        }
    }
    
    public void remove(Session persistentInstance) {
        log.debug("removing Session instance");
        try {
            entityManager.remove(persistentInstance);
            log.debug("remove successful");
        }
        catch (RuntimeException re) {
            log.error("remove failed", re);
            throw re;
        }
    }
    
    public Session merge(Session detachedInstance) {
        log.debug("merging Session instance");
        try {
            Session result = entityManager.merge(detachedInstance);
            log.debug("merge successful");
            return result;
        }
        catch (RuntimeException re) {
            log.error("merge failed", re);
            throw re;
        }
    }
    
    public Session findById( Integer id) {
        log.debug("getting Session instance with id: " + id);
        try {
            Session instance = entityManager.find(Session.class, id);
            log.debug("get successful");
            return instance;
        }
        catch (RuntimeException re) {
            log.error("get failed", re);
            throw re;
        }
    }
}

