package nl.warquest.database;
// Generated 17-mrt-2014 21:30:46 by Hibernate Tools 3.2.2.GA


import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * Home object for domain model class Poll.
 * @see nl.warquest.database.Poll
 * @author Hibernate Tools
 */
@Stateless
public class PollHome {

    private static final Log log = LogFactory.getLog(PollHome.class);

    @PersistenceContext private EntityManager entityManager;
    
    public void persist(Poll transientInstance) {
        log.debug("persisting Poll instance");
        try {
            entityManager.persist(transientInstance);
            log.debug("persist successful");
        }
        catch (RuntimeException re) {
            log.error("persist failed", re);
            throw re;
        }
    }
    
    public void remove(Poll persistentInstance) {
        log.debug("removing Poll instance");
        try {
            entityManager.remove(persistentInstance);
            log.debug("remove successful");
        }
        catch (RuntimeException re) {
            log.error("remove failed", re);
            throw re;
        }
    }
    
    public Poll merge(Poll detachedInstance) {
        log.debug("merging Poll instance");
        try {
            Poll result = entityManager.merge(detachedInstance);
            log.debug("merge successful");
            return result;
        }
        catch (RuntimeException re) {
            log.error("merge failed", re);
            throw re;
        }
    }
    
    public Poll findById( int id) {
        log.debug("getting Poll instance with id: " + id);
        try {
            Poll instance = entityManager.find(Poll.class, id);
            log.debug("get successful");
            return instance;
        }
        catch (RuntimeException re) {
            log.error("get failed", re);
            throw re;
        }
    }
}

