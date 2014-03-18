package nl.warquest.database.home;
// Generated 18-mrt-2014 21:03:52 by Hibernate Tools 3.2.2.GA


import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * Home object for domain model class Skill.
 * @see nl.warquest.database.home.Skill
 * @author Hibernate Tools
 */
@Stateless
public class SkillHome {

    private static final Log log = LogFactory.getLog(SkillHome.class);

    @PersistenceContext private EntityManager entityManager;
    
    public void persist(Skill transientInstance) {
        log.debug("persisting Skill instance");
        try {
            entityManager.persist(transientInstance);
            log.debug("persist successful");
        }
        catch (RuntimeException re) {
            log.error("persist failed", re);
            throw re;
        }
    }
    
    public void remove(Skill persistentInstance) {
        log.debug("removing Skill instance");
        try {
            entityManager.remove(persistentInstance);
            log.debug("remove successful");
        }
        catch (RuntimeException re) {
            log.error("remove failed", re);
            throw re;
        }
    }
    
    public Skill merge(Skill detachedInstance) {
        log.debug("merging Skill instance");
        try {
            Skill result = entityManager.merge(detachedInstance);
            log.debug("merge successful");
            return result;
        }
        catch (RuntimeException re) {
            log.error("merge failed", re);
            throw re;
        }
    }
    
    public Skill findById( int id) {
        log.debug("getting Skill instance with id: " + id);
        try {
            Skill instance = entityManager.find(Skill.class, id);
            log.debug("get successful");
            return instance;
        }
        catch (RuntimeException re) {
            log.error("get failed", re);
            throw re;
        }
    }
}

