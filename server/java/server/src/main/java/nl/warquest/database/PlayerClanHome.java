package nl.warquest.database;
// Generated 17-mrt-2014 21:30:46 by Hibernate Tools 3.2.2.GA


import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * Home object for domain model class PlayerClan.
 * @see nl.warquest.database.PlayerClan
 * @author Hibernate Tools
 */
@Stateless
public class PlayerClanHome {

    private static final Log log = LogFactory.getLog(PlayerClanHome.class);

    @PersistenceContext private EntityManager entityManager;
    
    public void persist(PlayerClan transientInstance) {
        log.debug("persisting PlayerClan instance");
        try {
            entityManager.persist(transientInstance);
            log.debug("persist successful");
        }
        catch (RuntimeException re) {
            log.error("persist failed", re);
            throw re;
        }
    }
    
    public void remove(PlayerClan persistentInstance) {
        log.debug("removing PlayerClan instance");
        try {
            entityManager.remove(persistentInstance);
            log.debug("remove successful");
        }
        catch (RuntimeException re) {
            log.error("remove failed", re);
            throw re;
        }
    }
    
    public PlayerClan merge(PlayerClan detachedInstance) {
        log.debug("merging PlayerClan instance");
        try {
            PlayerClan result = entityManager.merge(detachedInstance);
            log.debug("merge successful");
            return result;
        }
        catch (RuntimeException re) {
            log.error("merge failed", re);
            throw re;
        }
    }
    
    public PlayerClan findById( PlayerClanId id) {
        log.debug("getting PlayerClan instance with id: " + id);
        try {
            PlayerClan instance = entityManager.find(PlayerClan.class, id);
            log.debug("get successful");
            return instance;
        }
        catch (RuntimeException re) {
            log.error("get failed", re);
            throw re;
        }
    }
}

