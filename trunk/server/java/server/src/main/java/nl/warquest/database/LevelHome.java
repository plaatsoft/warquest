package nl.warquest.database;
// Generated 17-mrt-2014 21:30:46 by Hibernate Tools 3.2.2.GA


import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * Home object for domain model class Level.
 * @see nl.warquest.database.Level
 * @author Hibernate Tools
 */
@Stateless
public class LevelHome {

    private static final Log log = LogFactory.getLog(LevelHome.class);

    @PersistenceContext private EntityManager entityManager;
    
    public void persist(Level transientInstance) {
        log.debug("persisting Level instance");
        try {
            entityManager.persist(transientInstance);
            log.debug("persist successful");
        }
        catch (RuntimeException re) {
            log.error("persist failed", re);
            throw re;
        }
    }
    
    public void remove(Level persistentInstance) {
        log.debug("removing Level instance");
        try {
            entityManager.remove(persistentInstance);
            log.debug("remove successful");
        }
        catch (RuntimeException re) {
            log.error("remove failed", re);
            throw re;
        }
    }
    
    public Level merge(Level detachedInstance) {
        log.debug("merging Level instance");
        try {
            Level result = entityManager.merge(detachedInstance);
            log.debug("merge successful");
            return result;
        }
        catch (RuntimeException re) {
            log.error("merge failed", re);
            throw re;
        }
    }
    
    public Level findById( int id) {
        log.debug("getting Level instance with id: " + id);
        try {
            Level instance = entityManager.find(Level.class, id);
            log.debug("get successful");
            return instance;
        }
        catch (RuntimeException re) {
            log.error("get failed", re);
            throw re;
        }
    }
}

