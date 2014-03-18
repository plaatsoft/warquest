package nl.warquest.database.home;
// Generated 18-mrt-2014 21:03:52 by Hibernate Tools 3.2.2.GA


import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * Home object for domain model class MissionAward.
 * @see nl.warquest.database.home.MissionAward
 * @author Hibernate Tools
 */
@Stateless
public class MissionAwardHome {

    private static final Log log = LogFactory.getLog(MissionAwardHome.class);

    @PersistenceContext private EntityManager entityManager;
    
    public void persist(MissionAward transientInstance) {
        log.debug("persisting MissionAward instance");
        try {
            entityManager.persist(transientInstance);
            log.debug("persist successful");
        }
        catch (RuntimeException re) {
            log.error("persist failed", re);
            throw re;
        }
    }
    
    public void remove(MissionAward persistentInstance) {
        log.debug("removing MissionAward instance");
        try {
            entityManager.remove(persistentInstance);
            log.debug("remove successful");
        }
        catch (RuntimeException re) {
            log.error("remove failed", re);
            throw re;
        }
    }
    
    public MissionAward merge(MissionAward detachedInstance) {
        log.debug("merging MissionAward instance");
        try {
            MissionAward result = entityManager.merge(detachedInstance);
            log.debug("merge successful");
            return result;
        }
        catch (RuntimeException re) {
            log.error("merge failed", re);
            throw re;
        }
    }
    
    public MissionAward findById( int id) {
        log.debug("getting MissionAward instance with id: " + id);
        try {
            MissionAward instance = entityManager.find(MissionAward.class, id);
            log.debug("get successful");
            return instance;
        }
        catch (RuntimeException re) {
            log.error("get failed", re);
            throw re;
        }
    }
}

