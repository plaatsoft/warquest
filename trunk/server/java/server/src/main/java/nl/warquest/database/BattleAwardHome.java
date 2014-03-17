package nl.warquest.database;
// Generated 17-mrt-2014 21:30:46 by Hibernate Tools 3.2.2.GA


import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * Home object for domain model class BattleAward.
 * @see nl.warquest.database.BattleAward
 * @author Hibernate Tools
 */
@Stateless
public class BattleAwardHome {

    private static final Log log = LogFactory.getLog(BattleAwardHome.class);

    @PersistenceContext private EntityManager entityManager;
    
    public void persist(BattleAward transientInstance) {
        log.debug("persisting BattleAward instance");
        try {
            entityManager.persist(transientInstance);
            log.debug("persist successful");
        }
        catch (RuntimeException re) {
            log.error("persist failed", re);
            throw re;
        }
    }
    
    public void remove(BattleAward persistentInstance) {
        log.debug("removing BattleAward instance");
        try {
            entityManager.remove(persistentInstance);
            log.debug("remove successful");
        }
        catch (RuntimeException re) {
            log.error("remove failed", re);
            throw re;
        }
    }
    
    public BattleAward merge(BattleAward detachedInstance) {
        log.debug("merging BattleAward instance");
        try {
            BattleAward result = entityManager.merge(detachedInstance);
            log.debug("merge successful");
            return result;
        }
        catch (RuntimeException re) {
            log.error("merge failed", re);
            throw re;
        }
    }
    
    public BattleAward findById( int id) {
        log.debug("getting BattleAward instance with id: " + id);
        try {
            BattleAward instance = entityManager.find(BattleAward.class, id);
            log.debug("get successful");
            return instance;
        }
        catch (RuntimeException re) {
            log.error("get failed", re);
            throw re;
        }
    }
}

