package nl.warquest.database.home;
// Generated Mar 18, 2014 8:01:56 PM by Hibernate Tools 3.2.2.GA


import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * Home object for domain model class PlayerPlayer.
 * @see nl.warquest.database.home.PlayerPlayer
 * @author Hibernate Tools
 */
@Stateless
public class PlayerPlayerHome {

    private static final Log log = LogFactory.getLog(PlayerPlayerHome.class);

    @PersistenceContext private EntityManager entityManager;
    
    public void persist(PlayerPlayer transientInstance) {
        log.debug("persisting PlayerPlayer instance");
        try {
            entityManager.persist(transientInstance);
            log.debug("persist successful");
        }
        catch (RuntimeException re) {
            log.error("persist failed", re);
            throw re;
        }
    }
    
    public void remove(PlayerPlayer persistentInstance) {
        log.debug("removing PlayerPlayer instance");
        try {
            entityManager.remove(persistentInstance);
            log.debug("remove successful");
        }
        catch (RuntimeException re) {
            log.error("remove failed", re);
            throw re;
        }
    }
    
    public PlayerPlayer merge(PlayerPlayer detachedInstance) {
        log.debug("merging PlayerPlayer instance");
        try {
            PlayerPlayer result = entityManager.merge(detachedInstance);
            log.debug("merge successful");
            return result;
        }
        catch (RuntimeException re) {
            log.error("merge failed", re);
            throw re;
        }
    }
    
    public PlayerPlayer findById( PlayerPlayerId id) {
        log.debug("getting PlayerPlayer instance with id: " + id);
        try {
            PlayerPlayer instance = entityManager.find(PlayerPlayer.class, id);
            log.debug("get successful");
            return instance;
        }
        catch (RuntimeException re) {
            log.error("get failed", re);
            throw re;
        }
    }
}

