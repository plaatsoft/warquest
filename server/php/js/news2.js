/* 
**  ========
**  WarQuest
**  ========
**
**  Created by wplaat
**
**  For more information visit the following website.
**  Website : www.plaatsoft.nl 
**
**  Or send an email to the following address.
**  Email   : info@plaatsoft.nl
**
**  All copyrights reserved (c) 2008-2016 PlaatSoft
*/

var newsMid;
var newsEid;

function newsInit(mid, eid) {
	this.newsMid = mid;
	this.newsEid = eid;
}

function newsURL() {
	var url = location.href;  
	var baseURL = url.substring(0, url.indexOf('/', 14));

	if (baseURL.indexOf('http://127.0.0.1') != -1) {

		var url = location.href;  
		var pathname = location.pathname;  
		var index1 = url.indexOf(pathname);
		var index2 = url.indexOf("/", index1 + 1);
		var baseLocalUrl = url.substr(0, index2);
	
		return baseLocalUrl + "/";
		
	} else {

		return baseURL + "/";
	}
}

function newsCall() {

	if (window.XMLHttpRequest) {
		// code for IE7+, Firefox, Chrome, Opera, Safari
		xmlhttp=new XMLHttpRequest();
	} else {
		// code for IE6, IE5
		xmlhttp=new ActiveXObject('Microsoft.XMLHTTP');
	}
	
	xmlhttp.onreadystatechange=function() {
		if (xmlhttp.readyState==4 && xmlhttp.status==200) {
		
			document.getElementById("breakingnews").innerHTML += xmlhttp.responseText;
		}
	}
	
	xmlhttp.open('POST',  newsURL() ,true);
	xmlhttp.setRequestHeader('Content-type','application/x-www-form-urlencoded');
	xmlhttp.send('mid='+newsMid+'&eid='+newsEid);
}