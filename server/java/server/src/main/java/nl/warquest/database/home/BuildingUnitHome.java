package nl.warquest.database.home;
// Generated Mar 18, 2014 8:01:56 PM by Hibernate Tools 3.2.2.GA


import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * Home object for domain model class BuildingUnit.
 * @see nl.warquest.database.home.BuildingUnit
 * @author Hibernate Tools
 */
@Stateless
public class BuildingUnitHome {

    private static final Log log = LogFactory.getLog(BuildingUnitHome.class);

    @PersistenceContext private EntityManager entityManager;
    
    public void persist(BuildingUnit transientInstance) {
        log.debug("persisting BuildingUnit instance");
        try {
            entityManager.persist(transientInstance);
            log.debug("persist successful");
        }
        catch (RuntimeException re) {
            log.error("persist failed", re);
            throw re;
        }
    }
    
    public void remove(BuildingUnit persistentInstance) {
        log.debug("removing BuildingUnit instance");
        try {
            entityManager.remove(persistentInstance);
            log.debug("remove successful");
        }
        catch (RuntimeException re) {
            log.error("remove failed", re);
            throw re;
        }
    }
    
    public BuildingUnit merge(BuildingUnit detachedInstance) {
        log.debug("merging BuildingUnit instance");
        try {
            BuildingUnit result = entityManager.merge(detachedInstance);
            log.debug("merge successful");
            return result;
        }
        catch (RuntimeException re) {
            log.error("merge failed", re);
            throw re;
        }
    }
    
    public BuildingUnit findById( BuildingUnitId id) {
        log.debug("getting BuildingUnit instance with id: " + id);
        try {
            BuildingUnit instance = entityManager.find(BuildingUnit.class, id);
            log.debug("get successful");
            return instance;
        }
        catch (RuntimeException re) {
            log.error("get failed", re);
            throw re;
        }
    }
}

