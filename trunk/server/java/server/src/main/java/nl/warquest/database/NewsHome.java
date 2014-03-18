package nl.warquest.database;
// Generated 17-mrt-2014 21:30:46 by Hibernate Tools 3.2.2.GA


import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * Home object for domain model class News.
 * @see nl.warquest.database.News
 * @author Hibernate Tools
 */
@Stateless
public class NewsHome {

    private static final Log log = LogFactory.getLog(NewsHome.class);

    @PersistenceContext private EntityManager entityManager;
    
    public void persist(News transientInstance) {
        log.debug("persisting News instance");
        try {
            entityManager.persist(transientInstance);
            log.debug("persist successful");
        }
        catch (RuntimeException re) {
            log.error("persist failed", re);
            throw re;
        }
    }
    
    public void remove(News persistentInstance) {
        log.debug("removing News instance");
        try {
            entityManager.remove(persistentInstance);
            log.debug("remove successful");
        }
        catch (RuntimeException re) {
            log.error("remove failed", re);
            throw re;
        }
    }
    
    public News merge(News detachedInstance) {
        log.debug("merging News instance");
        try {
            News result = entityManager.merge(detachedInstance);
            log.debug("merge successful");
            return result;
        }
        catch (RuntimeException re) {
            log.error("merge failed", re);
            throw re;
        }
    }
    
    public News findById( Integer id) {
        log.debug("getting News instance with id: " + id);
        try {
            News instance = entityManager.find(News.class, id);
            log.debug("get successful");
            return instance;
        }
        catch (RuntimeException re) {
            log.error("get failed", re);
            throw re;
        }
    }
}
