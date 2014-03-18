package nl.warquest.database.home;
// Generated 18-mrt-2014 21:03:52 by Hibernate Tools 3.2.2.GA


import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * Home object for domain model class Statistics.
 * @see nl.warquest.database.home.Statistics
 * @author Hibernate Tools
 */
@Stateless
public class StatisticsHome {

    private static final Log log = LogFactory.getLog(StatisticsHome.class);

    @PersistenceContext private EntityManager entityManager;
    
    public void persist(Statistics transientInstance) {
        log.debug("persisting Statistics instance");
        try {
            entityManager.persist(transientInstance);
            log.debug("persist successful");
        }
        catch (RuntimeException re) {
            log.error("persist failed", re);
            throw re;
        }
    }
    
    public void remove(Statistics persistentInstance) {
        log.debug("removing Statistics instance");
        try {
            entityManager.remove(persistentInstance);
            log.debug("remove successful");
        }
        catch (RuntimeException re) {
            log.error("remove failed", re);
            throw re;
        }
    }
    
    public Statistics merge(Statistics detachedInstance) {
        log.debug("merging Statistics instance");
        try {
            Statistics result = entityManager.merge(detachedInstance);
            log.debug("merge successful");
            return result;
        }
        catch (RuntimeException re) {
            log.error("merge failed", re);
            throw re;
        }
    }
    
    public Statistics findById( Integer id) {
        log.debug("getting Statistics instance with id: " + id);
        try {
            Statistics instance = entityManager.find(Statistics.class, id);
            log.debug("get successful");
            return instance;
        }
        catch (RuntimeException re) {
            log.error("get failed", re);
            throw re;
        }
    }
}

