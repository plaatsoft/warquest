package nl.warquest.database;
// Generated 17-mrt-2014 21:30:46 by Hibernate Tools 3.2.2.GA


import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * Home object for domain model class PollAnswer.
 * @see nl.warquest.database.PollAnswer
 * @author Hibernate Tools
 */
@Stateless
public class PollAnswerHome {

    private static final Log log = LogFactory.getLog(PollAnswerHome.class);

    @PersistenceContext private EntityManager entityManager;
    
    public void persist(PollAnswer transientInstance) {
        log.debug("persisting PollAnswer instance");
        try {
            entityManager.persist(transientInstance);
            log.debug("persist successful");
        }
        catch (RuntimeException re) {
            log.error("persist failed", re);
            throw re;
        }
    }
    
    public void remove(PollAnswer persistentInstance) {
        log.debug("removing PollAnswer instance");
        try {
            entityManager.remove(persistentInstance);
            log.debug("remove successful");
        }
        catch (RuntimeException re) {
            log.error("remove failed", re);
            throw re;
        }
    }
    
    public PollAnswer merge(PollAnswer detachedInstance) {
        log.debug("merging PollAnswer instance");
        try {
            PollAnswer result = entityManager.merge(detachedInstance);
            log.debug("merge successful");
            return result;
        }
        catch (RuntimeException re) {
            log.error("merge failed", re);
            throw re;
        }
    }
    
    public PollAnswer findById( Integer id) {
        log.debug("getting PollAnswer instance with id: " + id);
        try {
            PollAnswer instance = entityManager.find(PollAnswer.class, id);
            log.debug("get successful");
            return instance;
        }
        catch (RuntimeException re) {
            log.error("get failed", re);
            throw re;
        }
    }
}

