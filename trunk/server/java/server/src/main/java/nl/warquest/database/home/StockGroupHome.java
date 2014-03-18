package nl.warquest.database.home;
// Generated Mar 18, 2014 8:01:56 PM by Hibernate Tools 3.2.2.GA


import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * Home object for domain model class StockGroup.
 * @see nl.warquest.database.home.StockGroup
 * @author Hibernate Tools
 */
@Stateless
public class StockGroupHome {

    private static final Log log = LogFactory.getLog(StockGroupHome.class);

    @PersistenceContext private EntityManager entityManager;
    
    public void persist(StockGroup transientInstance) {
        log.debug("persisting StockGroup instance");
        try {
            entityManager.persist(transientInstance);
            log.debug("persist successful");
        }
        catch (RuntimeException re) {
            log.error("persist failed", re);
            throw re;
        }
    }
    
    public void remove(StockGroup persistentInstance) {
        log.debug("removing StockGroup instance");
        try {
            entityManager.remove(persistentInstance);
            log.debug("remove successful");
        }
        catch (RuntimeException re) {
            log.error("remove failed", re);
            throw re;
        }
    }
    
    public StockGroup merge(StockGroup detachedInstance) {
        log.debug("merging StockGroup instance");
        try {
            StockGroup result = entityManager.merge(detachedInstance);
            log.debug("merge successful");
            return result;
        }
        catch (RuntimeException re) {
            log.error("merge failed", re);
            throw re;
        }
    }
    
    public StockGroup findById( int id) {
        log.debug("getting StockGroup instance with id: " + id);
        try {
            StockGroup instance = entityManager.find(StockGroup.class, id);
            log.debug("get successful");
            return instance;
        }
        catch (RuntimeException re) {
            log.error("get failed", re);
            throw re;
        }
    }
}

