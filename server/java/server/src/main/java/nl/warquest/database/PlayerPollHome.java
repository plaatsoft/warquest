package nl.warquest.database;
// Generated 17-mrt-2014 21:30:46 by Hibernate Tools 3.2.2.GA


import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * Home object for domain model class PlayerPoll.
 * @see nl.warquest.database.PlayerPoll
 * @author Hibernate Tools
 */
@Stateless
public class PlayerPollHome {

    private static final Log log = LogFactory.getLog(PlayerPollHome.class);

    @PersistenceContext private EntityManager entityManager;
    
    public void persist(PlayerPoll transientInstance) {
        log.debug("persisting PlayerPoll instance");
        try {
            entityManager.persist(transientInstance);
            log.debug("persist successful");
        }
        catch (RuntimeException re) {
            log.error("persist failed", re);
            throw re;
        }
    }
    
    public void remove(PlayerPoll persistentInstance) {
        log.debug("removing PlayerPoll instance");
        try {
            entityManager.remove(persistentInstance);
            log.debug("remove successful");
        }
        catch (RuntimeException re) {
            log.error("remove failed", re);
            throw re;
        }
    }
    
    public PlayerPoll merge(PlayerPoll detachedInstance) {
        log.debug("merging PlayerPoll instance");
        try {
            PlayerPoll result = entityManager.merge(detachedInstance);
            log.debug("merge successful");
            return result;
        }
        catch (RuntimeException re) {
            log.error("merge failed", re);
            throw re;
        }
    }
    
    public PlayerPoll findById( PlayerPollId id) {
        log.debug("getting PlayerPoll instance with id: " + id);
        try {
            PlayerPoll instance = entityManager.find(PlayerPoll.class, id);
            log.debug("get successful");
            return instance;
        }
        catch (RuntimeException re) {
            log.error("get failed", re);
            throw re;
        }
    }
}

