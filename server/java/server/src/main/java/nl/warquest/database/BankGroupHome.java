package nl.warquest.database;
// Generated 17-mrt-2014 21:30:46 by Hibernate Tools 3.2.2.GA


import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * Home object for domain model class BankGroup.
 * @see nl.warquest.database.BankGroup
 * @author Hibernate Tools
 */
@Stateless
public class BankGroupHome {

    private static final Log log = LogFactory.getLog(BankGroupHome.class);

    @PersistenceContext private EntityManager entityManager;
    
    public void persist(BankGroup transientInstance) {
        log.debug("persisting BankGroup instance");
        try {
            entityManager.persist(transientInstance);
            log.debug("persist successful");
        }
        catch (RuntimeException re) {
            log.error("persist failed", re);
            throw re;
        }
    }
    
    public void remove(BankGroup persistentInstance) {
        log.debug("removing BankGroup instance");
        try {
            entityManager.remove(persistentInstance);
            log.debug("remove successful");
        }
        catch (RuntimeException re) {
            log.error("remove failed", re);
            throw re;
        }
    }
    
    public BankGroup merge(BankGroup detachedInstance) {
        log.debug("merging BankGroup instance");
        try {
            BankGroup result = entityManager.merge(detachedInstance);
            log.debug("merge successful");
            return result;
        }
        catch (RuntimeException re) {
            log.error("merge failed", re);
            throw re;
        }
    }
    
    public BankGroup findById( int id) {
        log.debug("getting BankGroup instance with id: " + id);
        try {
            BankGroup instance = entityManager.find(BankGroup.class, id);
            log.debug("get successful");
            return instance;
        }
        catch (RuntimeException re) {
            log.error("get failed", re);
            throw re;
        }
    }
}

