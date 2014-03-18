package nl.warquest.database.home;
// Generated Mar 18, 2014 8:01:56 PM by Hibernate Tools 3.2.2.GA


import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * Home object for domain model class PlayerUnit.
 * @see nl.warquest.database.home.PlayerUnit
 * @author Hibernate Tools
 */
@Stateless
public class PlayerUnitHome {

    private static final Log log = LogFactory.getLog(PlayerUnitHome.class);

    @PersistenceContext private EntityManager entityManager;
    
    public void persist(PlayerUnit transientInstance) {
        log.debug("persisting PlayerUnit instance");
        try {
            entityManager.persist(transientInstance);
            log.debug("persist successful");
        }
        catch (RuntimeException re) {
            log.error("persist failed", re);
            throw re;
        }
    }
    
    public void remove(PlayerUnit persistentInstance) {
        log.debug("removing PlayerUnit instance");
        try {
            entityManager.remove(persistentInstance);
            log.debug("remove successful");
        }
        catch (RuntimeException re) {
            log.error("remove failed", re);
            throw re;
        }
    }
    
    public PlayerUnit merge(PlayerUnit detachedInstance) {
        log.debug("merging PlayerUnit instance");
        try {
            PlayerUnit result = entityManager.merge(detachedInstance);
            log.debug("merge successful");
            return result;
        }
        catch (RuntimeException re) {
            log.error("merge failed", re);
            throw re;
        }
    }
    
    public PlayerUnit findById( PlayerUnitId id) {
        log.debug("getting PlayerUnit instance with id: " + id);
        try {
            PlayerUnit instance = entityManager.find(PlayerUnit.class, id);
            log.debug("get successful");
            return instance;
        }
        catch (RuntimeException re) {
            log.error("get failed", re);
            throw re;
        }
    }
}

