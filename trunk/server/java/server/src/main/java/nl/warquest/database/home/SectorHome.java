package nl.warquest.database.home;
// Generated 18-mrt-2014 21:03:52 by Hibernate Tools 3.2.2.GA


import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * Home object for domain model class Sector.
 * @see nl.warquest.database.home.Sector
 * @author Hibernate Tools
 */
@Stateless
public class SectorHome {

    private static final Log log = LogFactory.getLog(SectorHome.class);

    @PersistenceContext private EntityManager entityManager;
    
    public void persist(Sector transientInstance) {
        log.debug("persisting Sector instance");
        try {
            entityManager.persist(transientInstance);
            log.debug("persist successful");
        }
        catch (RuntimeException re) {
            log.error("persist failed", re);
            throw re;
        }
    }
    
    public void remove(Sector persistentInstance) {
        log.debug("removing Sector instance");
        try {
            entityManager.remove(persistentInstance);
            log.debug("remove successful");
        }
        catch (RuntimeException re) {
            log.error("remove failed", re);
            throw re;
        }
    }
    
    public Sector merge(Sector detachedInstance) {
        log.debug("merging Sector instance");
        try {
            Sector result = entityManager.merge(detachedInstance);
            log.debug("merge successful");
            return result;
        }
        catch (RuntimeException re) {
            log.error("merge failed", re);
            throw re;
        }
    }
    
    public Sector findById( Integer id) {
        log.debug("getting Sector instance with id: " + id);
        try {
            Sector instance = entityManager.find(Sector.class, id);
            log.debug("get successful");
            return instance;
        }
        catch (RuntimeException re) {
            log.error("get failed", re);
            throw re;
        }
    }
}

