package nl.warquest.database.home;
// Generated 18-mrt-2014 21:03:52 by Hibernate Tools 3.2.2.GA


import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * Home object for domain model class BountyAward.
 * @see nl.warquest.database.home.BountyAward
 * @author Hibernate Tools
 */
@Stateless
public class BountyAwardHome {

    private static final Log log = LogFactory.getLog(BountyAwardHome.class);

    @PersistenceContext private EntityManager entityManager;
    
    public void persist(BountyAward transientInstance) {
        log.debug("persisting BountyAward instance");
        try {
            entityManager.persist(transientInstance);
            log.debug("persist successful");
        }
        catch (RuntimeException re) {
            log.error("persist failed", re);
            throw re;
        }
    }
    
    public void remove(BountyAward persistentInstance) {
        log.debug("removing BountyAward instance");
        try {
            entityManager.remove(persistentInstance);
            log.debug("remove successful");
        }
        catch (RuntimeException re) {
            log.error("remove failed", re);
            throw re;
        }
    }
    
    public BountyAward merge(BountyAward detachedInstance) {
        log.debug("merging BountyAward instance");
        try {
            BountyAward result = entityManager.merge(detachedInstance);
            log.debug("merge successful");
            return result;
        }
        catch (RuntimeException re) {
            log.error("merge failed", re);
            throw re;
        }
    }
    
    public BountyAward findById( int id) {
        log.debug("getting BountyAward instance with id: " + id);
        try {
            BountyAward instance = entityManager.find(BountyAward.class, id);
            log.debug("get successful");
            return instance;
        }
        catch (RuntimeException re) {
            log.error("get failed", re);
            throw re;
        }
    }
}

