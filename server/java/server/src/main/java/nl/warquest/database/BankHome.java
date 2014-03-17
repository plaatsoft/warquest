package nl.warquest.database;
// Generated 17-mrt-2014 21:30:46 by Hibernate Tools 3.2.2.GA


import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * Home object for domain model class Bank.
 * @see nl.warquest.database.Bank
 * @author Hibernate Tools
 */
@Stateless
public class BankHome {

    private static final Log log = LogFactory.getLog(BankHome.class);

    @PersistenceContext private EntityManager entityManager;
    
    public void persist(Bank transientInstance) {
        log.debug("persisting Bank instance");
        try {
            entityManager.persist(transientInstance);
            log.debug("persist successful");
        }
        catch (RuntimeException re) {
            log.error("persist failed", re);
            throw re;
        }
    }
    
    public void remove(Bank persistentInstance) {
        log.debug("removing Bank instance");
        try {
            entityManager.remove(persistentInstance);
            log.debug("remove successful");
        }
        catch (RuntimeException re) {
            log.error("remove failed", re);
            throw re;
        }
    }
    
    public Bank merge(Bank detachedInstance) {
        log.debug("merging Bank instance");
        try {
            Bank result = entityManager.merge(detachedInstance);
            log.debug("merge successful");
            return result;
        }
        catch (RuntimeException re) {
            log.error("merge failed", re);
            throw re;
        }
    }
    
    public Bank findById( Integer id) {
        log.debug("getting Bank instance with id: " + id);
        try {
            Bank instance = entityManager.find(Bank.class, id);
            log.debug("get successful");
            return instance;
        }
        catch (RuntimeException re) {
            log.error("get failed", re);
            throw re;
        }
    }
}

