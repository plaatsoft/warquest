package nl.warquest.database.home;
// Generated 18-mrt-2014 21:03:52 by Hibernate Tools 3.2.2.GA


import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * Home object for domain model class Chat.
 * @see nl.warquest.database.home.Chat
 * @author Hibernate Tools
 */
@Stateless
public class ChatHome {

    private static final Log log = LogFactory.getLog(ChatHome.class);

    @PersistenceContext private EntityManager entityManager;
    
    public void persist(Chat transientInstance) {
        log.debug("persisting Chat instance");
        try {
            entityManager.persist(transientInstance);
            log.debug("persist successful");
        }
        catch (RuntimeException re) {
            log.error("persist failed", re);
            throw re;
        }
    }
    
    public void remove(Chat persistentInstance) {
        log.debug("removing Chat instance");
        try {
            entityManager.remove(persistentInstance);
            log.debug("remove successful");
        }
        catch (RuntimeException re) {
            log.error("remove failed", re);
            throw re;
        }
    }
    
    public Chat merge(Chat detachedInstance) {
        log.debug("merging Chat instance");
        try {
            Chat result = entityManager.merge(detachedInstance);
            log.debug("merge successful");
            return result;
        }
        catch (RuntimeException re) {
            log.error("merge failed", re);
            throw re;
        }
    }
    
    public Chat findById( Integer id) {
        log.debug("getting Chat instance with id: " + id);
        try {
            Chat instance = entityManager.find(Chat.class, id);
            log.debug("get successful");
            return instance;
        }
        catch (RuntimeException re) {
            log.error("get failed", re);
            throw re;
        }
    }
}

