package nl.plaatsoft.warquest.database;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

import org.apache.log4j.Logger;

import java.sql.Connection;

public class Clan {

	private Connection conn;	
	static Logger log = Logger.getLogger(Clan.class.getName());
	
	public Clan(Connection conn) {
			    
		this.conn = conn;
	}
	
	public ResultSet getClan() {
	    
		log.debug("getClan - enter");
		
		ResultSet rs=null; 
		 
		String query = "select cid, name from clan";
		log.debug(query);
	    
	    try {
	      Statement st = conn.createStatement();
	      rs = st.executeQuery(query);
	      
	    } catch (SQLException ex) {
	    	
	    	log.error(ex.getMessage());
	    }
	    
	    log.debug("getClan - leave");
	    return rs;
	}

}
