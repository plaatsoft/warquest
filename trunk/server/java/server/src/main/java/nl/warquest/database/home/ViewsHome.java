package nl.warquest.database.home;
// Generated Mar 18, 2014 8:01:56 PM by Hibernate Tools 3.2.2.GA


import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * Home object for domain model class Views.
 * @see nl.warquest.database.home.Views
 * @author Hibernate Tools
 */
@Stateless
public class ViewsHome {

    private static final Log log = LogFactory.getLog(ViewsHome.class);

    @PersistenceContext private EntityManager entityManager;
    
    public void persist(Views transientInstance) {
        log.debug("persisting Views instance");
        try {
            entityManager.persist(transientInstance);
            log.debug("persist successful");
        }
        catch (RuntimeException re) {
            log.error("persist failed", re);
            throw re;
        }
    }
    
    public void remove(Views persistentInstance) {
        log.debug("removing Views instance");
        try {
            entityManager.remove(persistentInstance);
            log.debug("remove successful");
        }
        catch (RuntimeException re) {
            log.error("remove failed", re);
            throw re;
        }
    }
    
    public Views merge(Views detachedInstance) {
        log.debug("merging Views instance");
        try {
            Views result = entityManager.merge(detachedInstance);
            log.debug("merge successful");
            return result;
        }
        catch (RuntimeException re) {
            log.error("merge failed", re);
            throw re;
        }
    }
    
    public Views findById( ViewsId id) {
        log.debug("getting Views instance with id: " + id);
        try {
            Views instance = entityManager.find(Views.class, id);
            log.debug("get successful");
            return instance;
        }
        catch (RuntimeException re) {
            log.error("get failed", re);
            throw re;
        }
    }
}

