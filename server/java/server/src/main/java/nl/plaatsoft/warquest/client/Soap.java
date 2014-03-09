package nl.plaatsoft.warquest.client;

import javax.xml.soap.*;
import javax.xml.transform.*;
import javax.xml.transform.stream.*;

import org.w3c.dom.NodeList;

@SuppressWarnings("restriction")
public class Soap {

	public static void main(String args[]) {
					
		String username = "robot";
		String password = "robot";
				
		String planet = "earth";
		String force = "airforce";
		
		String buy = "true";
		String clan = "false";
		
		/* Max robot nr. is 2506 */
		for (int j=1; j<=2506; j++) {
			for (int i=1; i<=5; i++) {
				if (!doBattle(username+j, password+j, planet, force)) break;
			}			
			for (int i=1; i<=10; i++) {
				if (!doMission(username+j, password+j, buy, clan)) break;
			}
			for (int i=1; i<=2; i++) {
				if (!doAlliance(username+j, password+j)) break;
			}
		}
	}
	
	private static boolean doBattle(String username, String password, String planet, String force) {
			
	
		boolean result = false;
		try {

			long startTime = System.currentTimeMillis();
				 
			SOAPConnectionFactory soapConnectionFactory = SOAPConnectionFactory.newInstance();
			SOAPConnection soapConnection = soapConnectionFactory.createConnection();

			String url = "http://www.warquest.nl/service/";
				
			SOAPMessage soapResponse = soapConnection.call(doBattleCall(username, password, planet, force),url);
			result = printSOAPResponse(soapResponse, "battle");
								
			soapConnection.close();
				 
			long endTime = System.currentTimeMillis();

			long duration = endTime - startTime;
			System.out.print("duration "+duration+" ms\n");
			System.out.print("------------------\n");
			
		} catch (Exception e) {
			System.err.println("Error occurred while sending SOAP Request to Server");
			e.printStackTrace();
		}
		return result;
	}

	private static boolean doMission(String username, String password, String buy, String clan) {

		boolean result = false;
		try {
			long startTime = System.currentTimeMillis();
			 
			SOAPConnectionFactory soapConnectionFactory = SOAPConnectionFactory.newInstance();
			SOAPConnection soapConnection = soapConnectionFactory.createConnection();

			String url = "http://www.warquest.nl/service/";
							
			SOAPMessage soapResponse = soapConnection.call(doMissionCall(username, password, buy, clan),url);
			result = printSOAPResponse(soapResponse, "mission");
			
			soapConnection.close();
			 
			long endTime = System.currentTimeMillis();

			long duration = endTime - startTime;
			System.out.print("duration "+duration+" ms\n");
			System.out.print("------------------\n");
		
		 } catch (Exception e) {
			 System.err.println("Error occurred while sending SOAP Request to Server");
			 e.printStackTrace();
		 }
		return result;
	}
	
	private static boolean doAlliance(String username, String password) {
		 
		boolean result = false;
		try {

			long startTime = System.currentTimeMillis();
				 
			SOAPConnectionFactory soapConnectionFactory = SOAPConnectionFactory.newInstance();
			SOAPConnection soapConnection = soapConnectionFactory.createConnection();

			String url = "http://www.warquest.nl/service/";
				
			SOAPMessage soapResponse = soapConnection.call(doAllianceCall(username, password),url);
			result = printSOAPResponse(soapResponse, "alliance");
								
			soapConnection.close();
				 
			long endTime = System.currentTimeMillis();

			long duration = endTime - startTime;
			System.out.print("duration "+duration+" ms\n");
			System.out.print("------------------\n");
			
		} catch (Exception e) {
			System.err.println("Error occurred while sending SOAP Request to Server");
			e.printStackTrace();
		}
		
		return result;
	}
	
	/**
	 * SOAP doBattle Request
	 */
	private static SOAPMessage doBattleCall(String username, String password, String planet, String force) throws Exception {
		MessageFactory messageFactory = MessageFactory.newInstance();
		SOAPMessage soapMessage = messageFactory.createMessage();
		SOAPPart soapPart = soapMessage.getSOAPPart();

		String serverURI = "http://www.warquest.nl/service/warquest.wsdl";

		// SOAP Envelope
		SOAPEnvelope envelope = soapPart.getEnvelope();
		envelope.addNamespaceDeclaration("war", serverURI);

		// SOAP Body
		SOAPBody soapBody = envelope.getBody();
		SOAPElement soapBodyElem = soapBody.addChildElement("doBattle", "war");
		SOAPElement soapBodyElem1 = soapBodyElem.addChildElement("login", "war");
		soapBodyElem1.addTextNode(username);
		SOAPElement soapBodyElem2 = soapBodyElem.addChildElement("password","war");
		soapBodyElem2.addTextNode(password);
		SOAPElement soapBodyElem3 = soapBodyElem.addChildElement("planet","war");
		soapBodyElem3.addTextNode(planet);
		SOAPElement soapBodyElem4 = soapBodyElem.addChildElement("force", "war");
		soapBodyElem4.addTextNode(force);

		MimeHeaders headers = soapMessage.getMimeHeaders();
		headers.addHeader("SOAPAction", serverURI);
		soapMessage.saveChanges();
		
		TransformerFactory transformerFactory = TransformerFactory.newInstance();
		Transformer transformer = transformerFactory.newTransformer();
		transformer.setOutputProperty("{http://xml.apache.org/xslt}indent-amount", "2");
		transformer.setOutputProperty(OutputKeys.INDENT, "yes");
		
		System.out.print("REQUEST: doBattle ["+username+"]\n");
		
		//System.out.print("REQUEST:\n");
		//StreamResult result = new StreamResult(System.out);
		//transformer.transform(soapMessage.getSOAPPart().getContent(), result);
	
		return soapMessage;
	}

	/**
	 * SOAP doMission Request
	 */
	private static SOAPMessage doMissionCall(String username, String password, String buy, String clan) throws Exception {
		MessageFactory messageFactory = MessageFactory.newInstance();
		SOAPMessage soapMessage = messageFactory.createMessage();
		SOAPPart soapPart = soapMessage.getSOAPPart();

		String serverURI = "http://www.warquest.nl/service/warquest.wsdl";

		// SOAP Envelope		
		SOAPEnvelope envelope = soapPart.getEnvelope();
		envelope.addNamespaceDeclaration("war", serverURI);

		// SOAP Body
		SOAPBody soapBody = envelope.getBody();
		SOAPElement soapBodyElem = soapBody.addChildElement("doMission", "war");
		SOAPElement soapBodyElem1 = soapBodyElem.addChildElement("login", "war");
		soapBodyElem1.addTextNode(username);
		SOAPElement soapBodyElem2 = soapBodyElem.addChildElement("password","war");
		soapBodyElem2.addTextNode(password);
		SOAPElement soapBodyElem3 = soapBodyElem.addChildElement("buy", "war");
		soapBodyElem3.addTextNode(buy);
		SOAPElement soapBodyElem4 = soapBodyElem.addChildElement("clan", "war");
		soapBodyElem4.addTextNode(clan);

		MimeHeaders headers = soapMessage.getMimeHeaders();
		headers.addHeader("SOAPAction", serverURI);
		soapMessage.saveChanges();
		
		TransformerFactory transformerFactory = TransformerFactory.newInstance();
		Transformer transformer = transformerFactory.newTransformer();
		transformer.setOutputProperty("{http://xml.apache.org/xslt}indent-amount", "2");
		transformer.setOutputProperty(OutputKeys.INDENT, "yes");
		
		System.out.print("REQUEST: domission ["+username+"]\n");
		
		//System.out.print("REQUEST:\n");
		//StreamResult result = new StreamResult(System.out);
		//transformer.transform(soapMessage.getSOAPPart().getContent(), result);
	
		return soapMessage;
	}
	
	/**
	 * SOAP doAlliance Request
	 */
	private static SOAPMessage doAllianceCall(String username, String password) throws Exception {
		MessageFactory messageFactory = MessageFactory.newInstance();
		SOAPMessage soapMessage = messageFactory.createMessage();
		SOAPPart soapPart = soapMessage.getSOAPPart();
		
		String serverURI = "http://www.warquest.nl/service/warquest.wsdl";

		// SOAP Envelope		
		SOAPEnvelope envelope = soapPart.getEnvelope();
		envelope.addNamespaceDeclaration("war", serverURI);

		// SOAP Body
		SOAPBody soapBody = envelope.getBody();
		SOAPElement soapBodyElem = soapBody.addChildElement("doAlliance", "war");
		SOAPElement soapBodyElem1 = soapBodyElem.addChildElement("login", "war");
		soapBodyElem1.addTextNode(username);
		SOAPElement soapBodyElem2 = soapBodyElem.addChildElement("password","war");
		soapBodyElem2.addTextNode(password);

		System.out.print("REQUEST: doAlliance ["+username+"]\n");
		
		MimeHeaders headers = soapMessage.getMimeHeaders();
		headers.addHeader("SOAPAction", serverURI);
		soapMessage.saveChanges();
		
		TransformerFactory transformerFactory = TransformerFactory.newInstance();
		Transformer transformer = transformerFactory.newTransformer();
		transformer.setOutputProperty("{http://xml.apache.org/xslt}indent-amount", "2");
		transformer.setOutputProperty(OutputKeys.INDENT, "yes");
		
		
		//StreamResult result = new StreamResult(System.out);
		//transformer.transform(soapMessage.getSOAPPart().getContent(), result);
	
		return soapMessage;
	}
	
	
	/**
	 * Method used to print the SOAP Response
	 */
	private static boolean printSOAPResponse(SOAPMessage soapResponse, String tag) throws Exception {
		
		boolean result = false;
		
		TransformerFactory transformerFactory = TransformerFactory.newInstance();
		Transformer transformer = transformerFactory.newTransformer();
		transformer.setOutputProperty("{http://xml.apache.org/xslt}indent-amount", "2");
		transformer.setOutputProperty(OutputKeys.INDENT, "yes");

		Source sourceContent = soapResponse.getSOAPPart().getContent();
		
		SOAPBody body =  soapResponse.getSOAPBody();
		 
		StreamResult result1 = new StreamResult(System.out);
		//transformer.transform(sourceContent, result1);
		
	    NodeList list = body.getElementsByTagName(tag);

		for (int i = 0; i < list.getLength(); i++) {
		    NodeList innerList = list.item(i).getChildNodes();

		    for (int j = 0; j < innerList.getLength(); j++) {
		    	
		          if (innerList.item(j).getNodeName()=="result") {
		        	 
		        	  if(Boolean.valueOf(innerList.item(j).getTextContent())) {
		        		  result = true;
		        	  }
		          }
		          
		          if (innerList.item(j).getNodeName()=="popup") {
			        	 
		        	  System.out.print("RESPONSE: "+innerList.item(j).getTextContent()+"\n");		        	
		          }
		    }
		}
		return result; 
	}
}
