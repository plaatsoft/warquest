package nl.plaatsoft.warquest.client;

import javax.xml.soap.*;
import javax.xml.transform.*;
import javax.xml.transform.stream.*;

public class Soap {

	public static void main(String args[]) {
		
		String username = "test";
		String password = "test";
		String planet = "earth";
		String force = "navy";
		String buy = "true";
		
		for (int i=1; i<300; i++) {
						 
			try {

				long startTime = System.currentTimeMillis();
				 
				SOAPConnectionFactory soapConnectionFactory = SOAPConnectionFactory.newInstance();
				SOAPConnection soapConnection = soapConnectionFactory.createConnection();

				String url = "http://www.warquest.nl/service/";
				
				SOAPMessage soapResponse = soapConnection.call(doBattle(username+i, password, planet, force),url);
				printSOAPResponse(soapResponse);
				
				System.out.print("\n");
				
				soapResponse = soapConnection.call(doMission(username+i, password, planet, buy),url);
				printSOAPResponse(soapResponse);
				
				soapConnection.close();
				 
				long endTime = System.currentTimeMillis();

				long duration = endTime - startTime;
				System.out.print("duration "+duration+" ms\n");
				System.out.print("------------------------------------------------------\n");
			
			 } catch (Exception e) {
				 System.err.println("Error occurred while sending SOAP Request to Server");
				 e.printStackTrace();
			 }
		}
	}

	/**
	 * SOAP doBattle Request
	 */
	private static SOAPMessage doBattle(String username, String password, String planet, String force) throws Exception {
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
		
		System.out.print("REQUEST:\n");
		StreamResult result = new StreamResult(System.out);
		transformer.transform(soapMessage.getSOAPPart().getContent(), result);
	
		return soapMessage;
	}

	/**
	 * SOAP doMission Request
	 */
	private static SOAPMessage doMission(String username, String password, String planet, String buy) throws Exception {
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
		SOAPElement soapBodyElem3 = soapBodyElem.addChildElement("planet","war");
		soapBodyElem3.addTextNode(planet);
		SOAPElement soapBodyElem4 = soapBodyElem.addChildElement("buy", "war");
		soapBodyElem4.addTextNode(buy);

		MimeHeaders headers = soapMessage.getMimeHeaders();
		headers.addHeader("SOAPAction", serverURI);
		soapMessage.saveChanges();
		
		TransformerFactory transformerFactory = TransformerFactory.newInstance();
		Transformer transformer = transformerFactory.newTransformer();
		transformer.setOutputProperty("{http://xml.apache.org/xslt}indent-amount", "2");
		transformer.setOutputProperty(OutputKeys.INDENT, "yes");
		
		System.out.print("REQUEST:\n");
		StreamResult result = new StreamResult(System.out);
		transformer.transform(soapMessage.getSOAPPart().getContent(), result);
	
		return soapMessage;
	}
	
	/**
	 * Method used to print the SOAP Response
	 */
	private static void printSOAPResponse(SOAPMessage soapResponse) throws Exception {
		TransformerFactory transformerFactory = TransformerFactory.newInstance();
		Transformer transformer = transformerFactory.newTransformer();
		transformer.setOutputProperty("{http://xml.apache.org/xslt}indent-amount", "2");
		transformer.setOutputProperty(OutputKeys.INDENT, "yes");

		Source sourceContent = soapResponse.getSOAPPart().getContent();
		System.out.print("\nRESPONSE:\n");
		StreamResult result = new StreamResult(System.out);
		transformer.transform(sourceContent, result);		
	}
}
