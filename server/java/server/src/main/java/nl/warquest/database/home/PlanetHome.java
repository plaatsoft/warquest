package nl.warquest.database.home;
// Generated 18-mrt-2014 21:03:52 by Hibernate Tools 3.2.2.GA


import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * Home object for domain model class Planet.
 * @see nl.warquest.database.home.Planet
 * @author Hibernate Tools
 */
@Stateless
public class PlanetHome {

    private static final Log log = LogFactory.getLog(PlanetHome.class);

    @PersistenceContext private EntityManager entityManager;
    
    public void persist(Planet transientInstance) {
        log.debug("persisting Planet instance");
        try {
            entityManager.persist(transientInstance);
            log.debug("persist successful");
        }
        catch (RuntimeException re) {
            log.error("persist failed", re);
            throw re;
        }
    }
    
    public void remove(Planet persistentInstance) {
        log.debug("removing Planet instance");
        try {
            entityManager.remove(persistentInstance);
            log.debug("remove successful");
        }
        catch (RuntimeException re) {
            log.error("remove failed", re);
            throw re;
        }
    }
    
    public Planet merge(Planet detachedInstance) {
        log.debug("merging Planet instance");
        try {
            Planet result = entityManager.merge(detachedInstance);
            log.debug("merge successful");
            return result;
        }
        catch (RuntimeException re) {
            log.error("merge failed", re);
            throw re;
        }
    }
    
    public Planet findById( int id) {
        log.debug("getting Planet instance with id: " + id);
        try {
            Planet instance = entityManager.find(Planet.class, id);
            log.debug("get successful");
            return instance;
        }
        catch (RuntimeException re) {
            log.error("get failed", re);
            throw re;
        }
    }
}

