package nl.warquest.database.home;
// Generated Mar 18, 2014 8:01:56 PM by Hibernate Tools 3.2.2.GA


import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * Home object for domain model class Lottery.
 * @see nl.warquest.database.home.Lottery
 * @author Hibernate Tools
 */
@Stateless
public class LotteryHome {

    private static final Log log = LogFactory.getLog(LotteryHome.class);

    @PersistenceContext private EntityManager entityManager;
    
    public void persist(Lottery transientInstance) {
        log.debug("persisting Lottery instance");
        try {
            entityManager.persist(transientInstance);
            log.debug("persist successful");
        }
        catch (RuntimeException re) {
            log.error("persist failed", re);
            throw re;
        }
    }
    
    public void remove(Lottery persistentInstance) {
        log.debug("removing Lottery instance");
        try {
            entityManager.remove(persistentInstance);
            log.debug("remove successful");
        }
        catch (RuntimeException re) {
            log.error("remove failed", re);
            throw re;
        }
    }
    
    public Lottery merge(Lottery detachedInstance) {
        log.debug("merging Lottery instance");
        try {
            Lottery result = entityManager.merge(detachedInstance);
            log.debug("merge successful");
            return result;
        }
        catch (RuntimeException re) {
            log.error("merge failed", re);
            throw re;
        }
    }
    
    public Lottery findById( Integer id) {
        log.debug("getting Lottery instance with id: " + id);
        try {
            Lottery instance = entityManager.find(Lottery.class, id);
            log.debug("get successful");
            return instance;
        }
        catch (RuntimeException re) {
            log.error("get failed", re);
            throw re;
        }
    }
}

