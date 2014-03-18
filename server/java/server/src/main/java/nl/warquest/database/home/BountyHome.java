package nl.warquest.database.home;
// Generated 18-mrt-2014 21:03:52 by Hibernate Tools 3.2.2.GA


import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * Home object for domain model class Bounty.
 * @see nl.warquest.database.home.Bounty
 * @author Hibernate Tools
 */
@Stateless
public class BountyHome {

    private static final Log log = LogFactory.getLog(BountyHome.class);

    @PersistenceContext private EntityManager entityManager;
    
    public void persist(Bounty transientInstance) {
        log.debug("persisting Bounty instance");
        try {
            entityManager.persist(transientInstance);
            log.debug("persist successful");
        }
        catch (RuntimeException re) {
            log.error("persist failed", re);
            throw re;
        }
    }
    
    public void remove(Bounty persistentInstance) {
        log.debug("removing Bounty instance");
        try {
            entityManager.remove(persistentInstance);
            log.debug("remove successful");
        }
        catch (RuntimeException re) {
            log.error("remove failed", re);
            throw re;
        }
    }
    
    public Bounty merge(Bounty detachedInstance) {
        log.debug("merging Bounty instance");
        try {
            Bounty result = entityManager.merge(detachedInstance);
            log.debug("merge successful");
            return result;
        }
        catch (RuntimeException re) {
            log.error("merge failed", re);
            throw re;
        }
    }
    
    public Bounty findById( Integer id) {
        log.debug("getting Bounty instance with id: " + id);
        try {
            Bounty instance = entityManager.find(Bounty.class, id);
            log.debug("get successful");
            return instance;
        }
        catch (RuntimeException re) {
            log.error("get failed", re);
            throw re;
        }
    }
}

