package nl.warquest.database.home;
// Generated Mar 18, 2014 8:01:56 PM by Hibernate Tools 3.2.2.GA


import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * Home object for domain model class BuildingGroup.
 * @see nl.warquest.database.home.BuildingGroup
 * @author Hibernate Tools
 */
@Stateless
public class BuildingGroupHome {

    private static final Log log = LogFactory.getLog(BuildingGroupHome.class);

    @PersistenceContext private EntityManager entityManager;
    
    public void persist(BuildingGroup transientInstance) {
        log.debug("persisting BuildingGroup instance");
        try {
            entityManager.persist(transientInstance);
            log.debug("persist successful");
        }
        catch (RuntimeException re) {
            log.error("persist failed", re);
            throw re;
        }
    }
    
    public void remove(BuildingGroup persistentInstance) {
        log.debug("removing BuildingGroup instance");
        try {
            entityManager.remove(persistentInstance);
            log.debug("remove successful");
        }
        catch (RuntimeException re) {
            log.error("remove failed", re);
            throw re;
        }
    }
    
    public BuildingGroup merge(BuildingGroup detachedInstance) {
        log.debug("merging BuildingGroup instance");
        try {
            BuildingGroup result = entityManager.merge(detachedInstance);
            log.debug("merge successful");
            return result;
        }
        catch (RuntimeException re) {
            log.error("merge failed", re);
            throw re;
        }
    }
    
    public BuildingGroup findById( int id) {
        log.debug("getting BuildingGroup instance with id: " + id);
        try {
            BuildingGroup instance = entityManager.find(BuildingGroup.class, id);
            log.debug("get successful");
            return instance;
        }
        catch (RuntimeException re) {
            log.error("get failed", re);
            throw re;
        }
    }
}

