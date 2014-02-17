package nl.plaatsoft.warquest.server;

import java.io.IOException;
import java.io.InputStream;
import java.sql.*;
import java.util.Properties;

import org.apache.log4j.Logger;

public class Database {

	static Logger log = Logger.getLogger(Database.class.getName());
	
	Connection conn = null;
	Properties properties = null;
	
	public int loadDBsettings() {
	
		log.info("Load custom server.properties file");
		
		properties = new Properties();
				
		try {
			ClassLoader classLoader = Thread.currentThread().getContextClassLoader();
			InputStream input = classLoader.getResourceAsStream("server.properties");
					
			properties.load(input);
			log.debug("Host:" + properties.getProperty("dbhost"));
			log.debug("Port:" + properties.getProperty("dbport"));
			log.debug("Name:" + properties.getProperty("dbname"));
			log.debug("Username:" + properties.getProperty("dbusername"));
			log.debug("Password:" + properties.getProperty("dbpassword"));
			
		} catch (IOException e) {
			log.error("Exception Occurred" + e.getMessage());
			return 1;
		}
		return 0;
	}
		
	public int connectDB() {
		
		log.info("Connected to the mysql database");
	
		String url = "";
		String driver = "com.mysql.jdbc.Driver";
		String userName = properties.getProperty("dbusername"); 
		String password = properties.getProperty("dbpassword");
		
		try {			
			Class.forName(driver).newInstance();
			
			url = "jdbc:mysql://"+properties.getProperty("dbhost")+"/Test?connectTimeout=1000";			
			conn = DriverManager.getConnection(url, userName, password);			
			
			url = "jdbc:mysql://"+properties.getProperty("dbhost")+":"+properties.getProperty("dbport")+"/"+properties.getProperty("dbname");		
			conn = DriverManager.getConnection(url, userName, password);
			
		} catch (Exception ex) {
			log.error(ex.getMessage());
			return 1;
		}
		
		return 0;
	}
					
	public int closeDB() {
				
		log.info("Disconnected from mysql database");
		
		try {		
			
			conn.close();
			
		} catch (SQLException ex) {
			
			log.error(ex.getMessage());
			return 1;
		}
		
		return 0;
	}
	
	public ResultSet getClan() {
	    
		log.info("Execute mysql database query");
		
		ResultSet rs=null; 
		 
		String query = "select cid, name from clan";
		log.debug(query);
	    
	    try {
	      Statement st = conn.createStatement();
	      rs = st.executeQuery(query);
	      
	    } catch (SQLException ex) {
	    	
	    	log.error(ex.getMessage());
	    }
	    return rs;
	}
	
	 public static void main(String[] args) {
	      
		long startTime = System.nanoTime();
		 
		Database db = new Database();
		
		db.loadDBsettings();
		db.connectDB();		 
		db.getClan();
		db.closeDB();
		
		long endTime = System.nanoTime();

		long duration = endTime - startTime;

		log.debug("Action took "+duration/1000000+"ms");
	}
}
