package nl.warquest.database;
// Generated 17-mrt-2014 21:30:46 by Hibernate Tools 3.2.2.GA


import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * Home object for domain model class PlayerStock.
 * @see nl.warquest.database.PlayerStock
 * @author Hibernate Tools
 */
@Stateless
public class PlayerStockHome {

    private static final Log log = LogFactory.getLog(PlayerStockHome.class);

    @PersistenceContext private EntityManager entityManager;
    
    public void persist(PlayerStock transientInstance) {
        log.debug("persisting PlayerStock instance");
        try {
            entityManager.persist(transientInstance);
            log.debug("persist successful");
        }
        catch (RuntimeException re) {
            log.error("persist failed", re);
            throw re;
        }
    }
    
    public void remove(PlayerStock persistentInstance) {
        log.debug("removing PlayerStock instance");
        try {
            entityManager.remove(persistentInstance);
            log.debug("remove successful");
        }
        catch (RuntimeException re) {
            log.error("remove failed", re);
            throw re;
        }
    }
    
    public PlayerStock merge(PlayerStock detachedInstance) {
        log.debug("merging PlayerStock instance");
        try {
            PlayerStock result = entityManager.merge(detachedInstance);
            log.debug("merge successful");
            return result;
        }
        catch (RuntimeException re) {
            log.error("merge failed", re);
            throw re;
        }
    }
    
    public PlayerStock findById( PlayerStockId id) {
        log.debug("getting PlayerStock instance with id: " + id);
        try {
            PlayerStock instance = entityManager.find(PlayerStock.class, id);
            log.debug("get successful");
            return instance;
        }
        catch (RuntimeException re) {
            log.error("get failed", re);
            throw re;
        }
    }
}
