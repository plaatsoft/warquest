package nl.warquest.database;
// Generated 17-mrt-2014 21:30:46 by Hibernate Tools 3.2.2.GA


import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * Home object for domain model class Bonus.
 * @see nl.warquest.database.Bonus
 * @author Hibernate Tools
 */
@Stateless
public class BonusHome {

    private static final Log log = LogFactory.getLog(BonusHome.class);

    @PersistenceContext private EntityManager entityManager;
    
    public void persist(Bonus transientInstance) {
        log.debug("persisting Bonus instance");
        try {
            entityManager.persist(transientInstance);
            log.debug("persist successful");
        }
        catch (RuntimeException re) {
            log.error("persist failed", re);
            throw re;
        }
    }
    
    public void remove(Bonus persistentInstance) {
        log.debug("removing Bonus instance");
        try {
            entityManager.remove(persistentInstance);
            log.debug("remove successful");
        }
        catch (RuntimeException re) {
            log.error("remove failed", re);
            throw re;
        }
    }
    
    public Bonus merge(Bonus detachedInstance) {
        log.debug("merging Bonus instance");
        try {
            Bonus result = entityManager.merge(detachedInstance);
            log.debug("merge successful");
            return result;
        }
        catch (RuntimeException re) {
            log.error("merge failed", re);
            throw re;
        }
    }
    
    public Bonus findById( BonusId id) {
        log.debug("getting Bonus instance with id: " + id);
        try {
            Bonus instance = entityManager.find(Bonus.class, id);
            log.debug("get successful");
            return instance;
        }
        catch (RuntimeException re) {
            log.error("get failed", re);
            throw re;
        }
    }
}

