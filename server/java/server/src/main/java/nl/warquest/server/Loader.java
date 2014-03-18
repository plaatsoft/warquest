package nl.warquest.server;

import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;
import javax.persistence.Persistence;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.ServletException;
 
import java.io.IOException;
import java.util.List;

import nl.warquest.database.dao.ClanDao;
import nl.warquest.database.entity.Clan;

import org.apache.log4j.Logger;
import org.eclipse.jetty.server.Request;
import org.eclipse.jetty.server.Server;
import org.eclipse.jetty.server.handler.AbstractHandler;

public class Loader extends AbstractHandler {

	private static EntityManagerFactory entityManagerFactory;	
	private static EntityManager entityManager;
	
	static Logger log = Logger.getLogger(Loader.class.getName());
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
		
		ClanDao clanDao = new ClanDao(entityManager);
		List<Clan> result = clanDao.findAll();
		for ( Clan clan : result ) {
			
			content += "<tr>";
			content += "<td>"+clan.getCid()+"</td>";
			content += "<td>"+clan.getName()+"</td>";
			content += "<td>"+clan.getSlogan()+"</td>";
			content += "</tr>";
		}
		content += "</table>";
		
		response.getWriter().println(content);		
			
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
