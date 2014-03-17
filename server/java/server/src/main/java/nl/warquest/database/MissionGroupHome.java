package nl.warquest.database;
// Generated 17-mrt-2014 21:30:46 by Hibernate Tools 3.2.2.GA


import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * Home object for domain model class MissionGroup.
 * @see nl.warquest.database.MissionGroup
 * @author Hibernate Tools
 */
@Stateless
public class MissionGroupHome {

    private static final Log log = LogFactory.getLog(MissionGroupHome.class);

    @PersistenceContext private EntityManager entityManager;
    
    public void persist(MissionGroup transientInstance) {
        log.debug("persisting MissionGroup instance");
        try {
            entityManager.persist(transientInstance);
            log.debug("persist successful");
        }
        catch (RuntimeException re) {
            log.error("persist failed", re);
            throw re;
        }
    }
    
    public void remove(MissionGroup persistentInstance) {
        log.debug("removing MissionGroup instance");
        try {
            entityManager.remove(persistentInstance);
            log.debug("remove successful");
        }
        catch (RuntimeException re) {
            log.error("remove failed", re);
            throw re;
        }
    }
    
    public MissionGroup merge(MissionGroup detachedInstance) {
        log.debug("merging MissionGroup instance");
        try {
            MissionGroup result = entityManager.merge(detachedInstance);
            log.debug("merge successful");
            return result;
        }
        catch (RuntimeException re) {
            log.error("merge failed", re);
            throw re;
        }
    }
    
    public MissionGroup findById( int id) {
        log.debug("getting MissionGroup instance with id: " + id);
        try {
            MissionGroup instance = entityManager.find(MissionGroup.class, id);
            log.debug("get successful");
            return instance;
        }
        catch (RuntimeException re) {
            log.error("get failed", re);
            throw re;
        }
    }
}

