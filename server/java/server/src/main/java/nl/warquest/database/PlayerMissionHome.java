package nl.warquest.database;
// Generated 17-mrt-2014 21:30:46 by Hibernate Tools 3.2.2.GA


import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * Home object for domain model class PlayerMission.
 * @see nl.warquest.database.PlayerMission
 * @author Hibernate Tools
 */
@Stateless
public class PlayerMissionHome {

    private static final Log log = LogFactory.getLog(PlayerMissionHome.class);

    @PersistenceContext private EntityManager entityManager;
    
    public void persist(PlayerMission transientInstance) {
        log.debug("persisting PlayerMission instance");
        try {
            entityManager.persist(transientInstance);
            log.debug("persist successful");
        }
        catch (RuntimeException re) {
            log.error("persist failed", re);
            throw re;
        }
    }
    
    public void remove(PlayerMission persistentInstance) {
        log.debug("removing PlayerMission instance");
        try {
            entityManager.remove(persistentInstance);
            log.debug("remove successful");
        }
        catch (RuntimeException re) {
            log.error("remove failed", re);
            throw re;
        }
    }
    
    public PlayerMission merge(PlayerMission detachedInstance) {
        log.debug("merging PlayerMission instance");
        try {
            PlayerMission result = entityManager.merge(detachedInstance);
            log.debug("merge successful");
            return result;
        }
        catch (RuntimeException re) {
            log.error("merge failed", re);
            throw re;
        }
    }
    
    public PlayerMission findById( PlayerMissionId id) {
        log.debug("getting PlayerMission instance with id: " + id);
        try {
            PlayerMission instance = entityManager.find(PlayerMission.class, id);
            log.debug("get successful");
            return instance;
        }
        catch (RuntimeException re) {
            log.error("get failed", re);
            throw re;
        }
    }
}

