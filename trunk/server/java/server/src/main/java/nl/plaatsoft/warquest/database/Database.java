package nl.plaatsoft.warquest.database;

import java.io.IOException;
import java.io.InputStream;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.Properties;

import org.apache.log4j.Logger;

public class Database {

	static Logger log = Logger.getLogger(Database.class.getName());
	
	Connection conn = null;
	Properties properties = null;
	
	public Clan clan;
	public Member member;
	
	private int loadConfiguration() {
	
		log.debug("loadConfiguration - enter");
		
		properties = new Properties();
		int returnValue=0;
				
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
			returnValue = 1;
		}
		
		log.debug("loadConfiguration - leave ["+returnValue+"]");
		return returnValue;
	}
		
	public int connect() {
		
		int returnValue = 0;
		
		log.debug("connect - enter");
			
		loadConfiguration();
		 
		String url = "";
		String driver = "com.mysql.jdbc.Driver";
		String userName = properties.getProperty("dbusername"); 
		String password = properties.getProperty("dbpassword");
		
		try {			
			Class.forName(driver).newInstance();

			url = "jdbc:mysql://"+properties.getProperty("dbhost")+":"+properties.getProperty("dbport")+"/"+properties.getProperty("dbname");		
			conn = DriverManager.getConnection(url, userName, password);
			
			clan = new Clan(conn);
			member = new Member(conn);			
			
		} catch (Exception ex) {
			log.error(ex.getMessage());
			
			returnValue = 1;			
		}
		
		log.debug("connect - leave ["+returnValue+"]");
		return returnValue;
	}
					
	public int close() {
		
		int returnValue = 0;
		
		log.debug("close - enter");
				
		try {		
			
			conn.close();
			
		} catch (SQLException ex) {
			
			log.error(ex.getMessage());
			returnValue = 1;
		}
		
		log.debug("close - leave ["+returnValue+"]");
		return returnValue;
	}	
}
