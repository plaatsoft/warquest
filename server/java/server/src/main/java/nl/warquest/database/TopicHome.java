package nl.warquest.database;
// Generated 17-mrt-2014 21:30:46 by Hibernate Tools 3.2.2.GA


import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * Home object for domain model class Topic.
 * @see nl.warquest.database.Topic
 * @author Hibernate Tools
 */
@Stateless
public class TopicHome {

    private static final Log log = LogFactory.getLog(TopicHome.class);

    @PersistenceContext private EntityManager entityManager;
    
    public void persist(Topic transientInstance) {
        log.debug("persisting Topic instance");
        try {
            entityManager.persist(transientInstance);
            log.debug("persist successful");
        }
        catch (RuntimeException re) {
            log.error("persist failed", re);
            throw re;
        }
    }
    
    public void remove(Topic persistentInstance) {
        log.debug("removing Topic instance");
        try {
            entityManager.remove(persistentInstance);
            log.debug("remove successful");
        }
        catch (RuntimeException re) {
            log.error("remove failed", re);
            throw re;
        }
    }
    
    public Topic merge(Topic detachedInstance) {
        log.debug("merging Topic instance");
        try {
            Topic result = entityManager.merge(detachedInstance);
            log.debug("merge successful");
            return result;
        }
        catch (RuntimeException re) {
            log.error("merge failed", re);
            throw re;
        }
    }
    
    public Topic findById( Integer id) {
        log.debug("getting Topic instance with id: " + id);
        try {
            Topic instance = entityManager.find(Topic.class, id);
            log.debug("get successful");
            return instance;
        }
        catch (RuntimeException re) {
            log.error("get failed", re);
            throw re;
        }
    }
}

