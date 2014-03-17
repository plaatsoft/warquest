package nl.warquest.database;
// Generated 17-mrt-2014 21:30:46 by Hibernate Tools 3.2.2.GA


import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * Home object for domain model class Clan.
 * @see nl.warquest.database.Clan
 * @author Hibernate Tools
 */
@Stateless
public class ClanHome {

    private static final Log log = LogFactory.getLog(ClanHome.class);

    @PersistenceContext private EntityManager entityManager;
    
    public void persist(Clan transientInstance) {
        log.debug("persisting Clan instance");
        try {
            entityManager.persist(transientInstance);
            log.debug("persist successful");
        }
        catch (RuntimeException re) {
            log.error("persist failed", re);
            throw re;
        }
    }
    
    public void remove(Clan persistentInstance) {
        log.debug("removing Clan instance");
        try {
            entityManager.remove(persistentInstance);
            log.debug("remove successful");
        }
        catch (RuntimeException re) {
            log.error("remove failed", re);
            throw re;
        }
    }
    
    public Clan merge(Clan detachedInstance) {
        log.debug("merging Clan instance");
        try {
            Clan result = entityManager.merge(detachedInstance);
            log.debug("merge successful");
            return result;
        }
        catch (RuntimeException re) {
            log.error("merge failed", re);
            throw re;
        }
    }
    
    public Clan findById( Integer id) {
        log.debug("getting Clan instance with id: " + id);
        try {
            Clan instance = entityManager.find(Clan.class, id);
            log.debug("get successful");
            return instance;
        }
        catch (RuntimeException re) {
            log.error("get failed", re);
            throw re;
        }
    }
}

