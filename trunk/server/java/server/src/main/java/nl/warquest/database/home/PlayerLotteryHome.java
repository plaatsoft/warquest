package nl.warquest.database.home;
// Generated Mar 18, 2014 8:01:56 PM by Hibernate Tools 3.2.2.GA


import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * Home object for domain model class PlayerLottery.
 * @see nl.warquest.database.home.PlayerLottery
 * @author Hibernate Tools
 */
@Stateless
public class PlayerLotteryHome {

    private static final Log log = LogFactory.getLog(PlayerLotteryHome.class);

    @PersistenceContext private EntityManager entityManager;
    
    public void persist(PlayerLottery transientInstance) {
        log.debug("persisting PlayerLottery instance");
        try {
            entityManager.persist(transientInstance);
            log.debug("persist successful");
        }
        catch (RuntimeException re) {
            log.error("persist failed", re);
            throw re;
        }
    }
    
    public void remove(PlayerLottery persistentInstance) {
        log.debug("removing PlayerLottery instance");
        try {
            entityManager.remove(persistentInstance);
            log.debug("remove successful");
        }
        catch (RuntimeException re) {
            log.error("remove failed", re);
            throw re;
        }
    }
    
    public PlayerLottery merge(PlayerLottery detachedInstance) {
        log.debug("merging PlayerLottery instance");
        try {
            PlayerLottery result = entityManager.merge(detachedInstance);
            log.debug("merge successful");
            return result;
        }
        catch (RuntimeException re) {
            log.error("merge failed", re);
            throw re;
        }
    }
    
    public PlayerLottery findById( Integer id) {
        log.debug("getting PlayerLottery instance with id: " + id);
        try {
            PlayerLottery instance = entityManager.find(PlayerLottery.class, id);
            log.debug("get successful");
            return instance;
        }
        catch (RuntimeException re) {
            log.error("get failed", re);
            throw re;
        }
    }
}

