package nl.plaatsoft.warquest.server;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.ServletException;
 
import java.io.IOException;
 
import java.sql.ResultSet;

import org.apache.log4j.Logger;

import org.eclipse.jetty.server.Request;
import org.eclipse.jetty.server.Server;
import org.eclipse.jetty.server.handler.AbstractHandler;

public class Loader extends AbstractHandler {

	static Logger log = Logger.getLogger(Database.class.getName());
	static int counter = 0;
	
	public void handle(String target, Request baseRequest, HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
		
		log.debug("-------");
		
		String content = "";
		
		long startTime = System.nanoTime();
		
		response.setContentType("text/html;charset=utf-8");
		response.setStatus(HttpServletResponse.SC_OK);
		
		baseRequest.setHandled(true);
		
		content += "<h1>Clans</h1>";
		
		content += "<table border=1>";
		
		Database db = new Database();
		
		db.loadDBsettings();
		
		if (db.connectDB()==0) {		 
		
			try {
				ResultSet rs = db.getClan();
			
				while (rs.next()) {
					content += "<tr>";
					content += "<td>"+rs.getString("cid")+"</td>";
					content += "<td>"+rs.getString("name")+"</td>";
					content += "</tr>";
				}
			
			} catch (Exception ex){
				log.error(ex.getMessage());
			}
		
			content += "</table>";
		}
		
		response.getWriter().println(content);		
		db.closeDB();
		
		long endTime = System.nanoTime();
		long duration = endTime - startTime;
		counter++;
		
		log.debug("Action "+counter+" took "+duration/1000000+"ms");
    }
	 
	public static void main(String[] args) throws Exception {
		
		Server server = new Server(8082);
		server.setHandler(new Loader());
		 
		server.start();
		server.join();
	}
}
