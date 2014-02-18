package nl.plaatsoft.warquest.database;

import java.math.BigInteger;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.sql.ResultSet;
import java.sql.Statement;

import org.apache.log4j.Logger;

import java.sql.Connection;

public class Member {

	private Connection conn;
	static Logger log = Logger.getLogger(Member.class.getName());
	
	public Member(Connection conn) {
				  
		  this.conn = conn;
	}
	
	public static String md5(String input) throws NoSuchAlgorithmException {
	    String result = input;
	    if(input != null) {
	        MessageDigest md = MessageDigest.getInstance("MD5"); 
	        md.update(input.getBytes());
	        BigInteger hash = new BigInteger(1, md.digest());
	        result = hash.toString(16);
	        while(result.length() < 32) { 
	            result = "0" + result;
	        }
	    }
	    return result;
	}
	
	public int doLogin(String username, String password) {
	    	
		log.debug("doLogin - enter");
		
		int pid=0;
		
		try {		
			String query = "select pid from member where username=\""+username+"\" and password=\""+ md5(password) +"\"";
			log.debug(query);
	    			
			Statement st = conn.createStatement();
			ResultSet rs = st.executeQuery(query);
				
			while (rs.next()) {
					
				pid = rs.getInt("pid");
			}
				
		} catch (Exception ex) {
	    	
	    	log.error(ex.getMessage());
	    }
	    
	    log.debug("doLogin - leave ["+pid+"]");
	    
	    return pid;
	}	
}
