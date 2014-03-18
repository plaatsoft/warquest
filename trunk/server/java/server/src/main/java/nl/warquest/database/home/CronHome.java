package nl.warquest.database.home;
// Generated Mar 18, 2014 8:01:56 PM by Hibernate Tools 3.2.2.GA


import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * Home object for domain model class Cron.
 * @see nl.warquest.database.home.Cron
 * @author Hibernate Tools
 */
@Stateless
public class CronHome {

    private static final Log log = LogFactory.getLog(CronHome.class);

    @PersistenceContext private EntityManager entityManager;
    
    public void persist(Cron transientInstance) {
        log.debug("persisting Cron instance");
        try {
            entityManager.persist(transientInstance);
            log.debug("persist successful");
        }
        catch (RuntimeException re) {
            log.error("persist failed", re);
            throw re;
        }
    }
    
    public void remove(Cron persistentInstance) {
        log.debug("removing Cron instance");
        try {
            entityManager.remove(persistentInstance);
            log.debug("remove successful");
        }
        catch (RuntimeException re) {
            log.error("remove failed", re);
            throw re;
        }
    }
    
    public Cron merge(Cron detachedInstance) {
        log.debug("merging Cron instance");
        try {
            Cron result = entityManager.merge(detachedInstance);
            log.debug("merge successful");
            return result;
        }
        catch (RuntimeException re) {
            log.error("merge failed", re);
            throw re;
        }
    }
    
    public Cron findById( Integer id) {
        log.debug("getting Cron instance with id: " + id);
        try {
            Cron instance = entityManager.find(Cron.class, id);
            log.debug("get successful");
            return instance;
        }
        catch (RuntimeException re) {
            log.error("get failed", re);
            throw re;
        }
    }
}

