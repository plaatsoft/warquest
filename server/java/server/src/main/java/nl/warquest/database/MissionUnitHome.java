package nl.warquest.database;
// Generated 17-mrt-2014 21:30:46 by Hibernate Tools 3.2.2.GA


import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * Home object for domain model class MissionUnit.
 * @see nl.warquest.database.MissionUnit
 * @author Hibernate Tools
 */
@Stateless
public class MissionUnitHome {

    private static final Log log = LogFactory.getLog(MissionUnitHome.class);

    @PersistenceContext private EntityManager entityManager;
    
    public void persist(MissionUnit transientInstance) {
        log.debug("persisting MissionUnit instance");
        try {
            entityManager.persist(transientInstance);
            log.debug("persist successful");
        }
        catch (RuntimeException re) {
            log.error("persist failed", re);
            throw re;
        }
    }
    
    public void remove(MissionUnit persistentInstance) {
        log.debug("removing MissionUnit instance");
        try {
            entityManager.remove(persistentInstance);
            log.debug("remove successful");
        }
        catch (RuntimeException re) {
            log.error("remove failed", re);
            throw re;
        }
    }
    
    public MissionUnit merge(MissionUnit detachedInstance) {
        log.debug("merging MissionUnit instance");
        try {
            MissionUnit result = entityManager.merge(detachedInstance);
            log.debug("merge successful");
            return result;
        }
        catch (RuntimeException re) {
            log.error("merge failed", re);
            throw re;
        }
    }
    
    public MissionUnit findById( MissionUnitId id) {
        log.debug("getting MissionUnit instance with id: " + id);
        try {
            MissionUnit instance = entityManager.find(MissionUnit.class, id);
            log.debug("get successful");
            return instance;
        }
        catch (RuntimeException re) {
            log.error("get failed", re);
            throw re;
        }
    }
}

