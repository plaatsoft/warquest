package nl.warquest.database.dao;

import java.math.BigInteger;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.sql.ResultSet;
import java.sql.Statement;
import java.util.List;

import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;

import nl.warquest.database.entity.Clan;
import nl.warquest.database.entity.Member;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

public class MemberDao {

    private static final Log log = LogFactory.getLog(MemberDao.class);

    @PersistenceContext private EntityManager entityManager;
    
    public MemberDao(EntityManager entityManager) {
    	this.entityManager = entityManager;
    }
    
    public void persist(Member transientInstance) {
        log.debug("persisting Member instance");
        try {
            entityManager.persist(transientInstance);
            log.debug("persist successful");
        }
        catch (RuntimeException re) {
            log.error("persist failed", re);
            throw re;
        }
    }
    
    public void remove(Member persistentInstance) {
        log.debug("removing Member instance");
        try {
            entityManager.remove(persistentInstance);
            log.debug("remove successful");
        }
        catch (RuntimeException re) {
            log.error("remove failed", re);
            throw re;
        }
    }
    
    public Member merge(Member detachedInstance) {
        log.debug("merging Member instance");
        try {
            Member result = entityManager.merge(detachedInstance);
            log.debug("merge successful");
            return result;
        }
        catch (RuntimeException re) {
            log.error("merge failed", re);
            throw re;
        }
    }
    
    public Member findById( Integer id) {
        log.debug("getting Member instance with id: " + id);
        try {
            Member instance = entityManager.find(Member.class, id);
            log.debug("get successful");
            return instance;
        }
        catch (RuntimeException re) {
            log.error("get failed", re);
            throw re;
        }
    }
    
    private static String md5(String input) {
	    String result = input;
	    if(input != null) {
	        MessageDigest md;
			try {
				md = MessageDigest.getInstance("MD5");
				md.update(input.getBytes());
			    BigInteger hash = new BigInteger(1, md.digest());
			    result = hash.toString(16);
			    while(result.length() < 32) { 
			       result = "0" + result;
			    }
			} catch (NoSuchAlgorithmException e) {				
				log.error(e);
			}
	    }
	    return result;
	}
	
	public Integer doLogin(String username, String password) {
	    			
		Integer pid=0;
				
		List <Member> result = entityManager.createQuery("SELECT m from Member m where m.username=:username and m.password=:password").
			setParameter("username", username).setParameter("password", md5(password)).getResultList();
			
		for ( Member member : result ) {
		      pid = member.getPid();
		}
	    
	    log.debug("doLogin - leave ["+pid+"]");
	    
	    return pid;
	}	   
}

