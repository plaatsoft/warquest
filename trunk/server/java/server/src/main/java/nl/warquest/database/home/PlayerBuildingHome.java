package nl.warquest.database.home;
// Generated Mar 18, 2014 8:01:56 PM by Hibernate Tools 3.2.2.GA


import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * Home object for domain model class PlayerBuilding.
 * @see nl.warquest.database.home.PlayerBuilding
 * @author Hibernate Tools
 */
@Stateless
public class PlayerBuildingHome {

    private static final Log log = LogFactory.getLog(PlayerBuildingHome.class);

    @PersistenceContext private EntityManager entityManager;
    
    public void persist(PlayerBuilding transientInstance) {
        log.debug("persisting PlayerBuilding instance");
        try {
            entityManager.persist(transientInstance);
            log.debug("persist successful");
        }
        catch (RuntimeException re) {
            log.error("persist failed", re);
            throw re;
        }
    }
    
    public void remove(PlayerBuilding persistentInstance) {
        log.debug("removing PlayerBuilding instance");
        try {
            entityManager.remove(persistentInstance);
            log.debug("remove successful");
        }
        catch (RuntimeException re) {
            log.error("remove failed", re);
            throw re;
        }
    }
    
    public PlayerBuilding merge(PlayerBuilding detachedInstance) {
        log.debug("merging PlayerBuilding instance");
        try {
            PlayerBuilding result = entityManager.merge(detachedInstance);
            log.debug("merge successful");
            return result;
        }
        catch (RuntimeException re) {
            log.error("merge failed", re);
            throw re;
        }
    }
    
    public PlayerBuilding findById( PlayerBuildingId id) {
        log.debug("getting PlayerBuilding instance with id: " + id);
        try {
            PlayerBuilding instance = entityManager.find(PlayerBuilding.class, id);
            log.debug("get successful");
            return instance;
        }
        catch (RuntimeException re) {
            log.error("get failed", re);
            throw re;
        }
    }
}

