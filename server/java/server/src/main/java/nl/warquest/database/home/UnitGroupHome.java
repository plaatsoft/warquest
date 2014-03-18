package nl.warquest.database.home;
// Generated 18-mrt-2014 21:03:52 by Hibernate Tools 3.2.2.GA


import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * Home object for domain model class UnitGroup.
 * @see nl.warquest.database.home.UnitGroup
 * @author Hibernate Tools
 */
@Stateless
public class UnitGroupHome {

    private static final Log log = LogFactory.getLog(UnitGroupHome.class);

    @PersistenceContext private EntityManager entityManager;
    
    public void persist(UnitGroup transientInstance) {
        log.debug("persisting UnitGroup instance");
        try {
            entityManager.persist(transientInstance);
            log.debug("persist successful");
        }
        catch (RuntimeException re) {
            log.error("persist failed", re);
            throw re;
        }
    }
    
    public void remove(UnitGroup persistentInstance) {
        log.debug("removing UnitGroup instance");
        try {
            entityManager.remove(persistentInstance);
            log.debug("remove successful");
        }
        catch (RuntimeException re) {
            log.error("remove failed", re);
            throw re;
        }
    }
    
    public UnitGroup merge(UnitGroup detachedInstance) {
        log.debug("merging UnitGroup instance");
        try {
            UnitGroup result = entityManager.merge(detachedInstance);
            log.debug("merge successful");
            return result;
        }
        catch (RuntimeException re) {
            log.error("merge failed", re);
            throw re;
        }
    }
    
    public UnitGroup findById( int id) {
        log.debug("getting UnitGroup instance with id: " + id);
        try {
            UnitGroup instance = entityManager.find(UnitGroup.class, id);
            log.debug("get successful");
            return instance;
        }
        catch (RuntimeException re) {
            log.error("get failed", re);
            throw re;
        }
    }
}

