package nl.warquest.database;
// Generated 17-mrt-2014 21:30:46 by Hibernate Tools 3.2.2.GA


import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * Home object for domain model class Building.
 * @see nl.warquest.database.Building
 * @author Hibernate Tools
 */
@Stateless
public class BuildingHome {

    private static final Log log = LogFactory.getLog(BuildingHome.class);

    @PersistenceContext private EntityManager entityManager;
    
    public void persist(Building transientInstance) {
        log.debug("persisting Building instance");
        try {
            entityManager.persist(transientInstance);
            log.debug("persist successful");
        }
        catch (RuntimeException re) {
            log.error("persist failed", re);
            throw re;
        }
    }
    
    public void remove(Building persistentInstance) {
        log.debug("removing Building instance");
        try {
            entityManager.remove(persistentInstance);
            log.debug("remove successful");
        }
        catch (RuntimeException re) {
            log.error("remove failed", re);
            throw re;
        }
    }
    
    public Building merge(Building detachedInstance) {
        log.debug("merging Building instance");
        try {
            Building result = entityManager.merge(detachedInstance);
            log.debug("merge successful");
            return result;
        }
        catch (RuntimeException re) {
            log.error("merge failed", re);
            throw re;
        }
    }
    
    public Building findById( int id) {
        log.debug("getting Building instance with id: " + id);
        try {
            Building instance = entityManager.find(Building.class, id);
            log.debug("get successful");
            return instance;
        }
        catch (RuntimeException re) {
            log.error("get failed", re);
            throw re;
        }
    }
}

