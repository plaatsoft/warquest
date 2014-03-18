package nl.warquest.database.home;
// Generated 18-mrt-2014 21:03:52 by Hibernate Tools 3.2.2.GA


import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * Home object for domain model class ClanMission.
 * @see nl.warquest.database.home.ClanMission
 * @author Hibernate Tools
 */
@Stateless
public class ClanMissionHome {

    private static final Log log = LogFactory.getLog(ClanMissionHome.class);

    @PersistenceContext private EntityManager entityManager;
    
    public void persist(ClanMission transientInstance) {
        log.debug("persisting ClanMission instance");
        try {
            entityManager.persist(transientInstance);
            log.debug("persist successful");
        }
        catch (RuntimeException re) {
            log.error("persist failed", re);
            throw re;
        }
    }
    
    public void remove(ClanMission persistentInstance) {
        log.debug("removing ClanMission instance");
        try {
            entityManager.remove(persistentInstance);
            log.debug("remove successful");
        }
        catch (RuntimeException re) {
            log.error("remove failed", re);
            throw re;
        }
    }
    
    public ClanMission merge(ClanMission detachedInstance) {
        log.debug("merging ClanMission instance");
        try {
            ClanMission result = entityManager.merge(detachedInstance);
            log.debug("merge successful");
            return result;
        }
        catch (RuntimeException re) {
            log.error("merge failed", re);
            throw re;
        }
    }
    
    public ClanMission findById( ClanMissionId id) {
        log.debug("getting ClanMission instance with id: " + id);
        try {
            ClanMission instance = entityManager.find(ClanMission.class, id);
            log.debug("get successful");
            return instance;
        }
        catch (RuntimeException re) {
            log.error("get failed", re);
            throw re;
        }
    }
}

